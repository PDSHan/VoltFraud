#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <emmintrin.h>
#include <x86intrin.h>
#include "DCbias.h"
#include <sched.h>
#include <stdatomic.h>
#include <sys/mman.h>
#include <stdint.h>

// #define ARRAY_SIZE (4096*3)
#define ARRAY_SIZE (4096*2)
int log_fd;
int fd_trigger = -1;
int DTR = TIOCM_DTR;
char log_info[1024];

typedef struct {
    uint8_t bytes[64];
} __attribute__((aligned(64))) cl64_t;

typedef struct {
    double freq;
    int retries;
    double volt_prep;
    double width_prep;
    double volt_fault;
    double width_fault;
    int index;
}fault_params;

#define HPAGE_SIZE   (2UL * 1024 * 1024)
#define NUM_HPAGES    128
#define REGION_SIZE  (ARRAY_SIZE * sizeof(cl64_t))   // 512KB
#define REGIONS_PER_HP (NUM_HPAGES * HPAGE_SIZE / REGION_SIZE)

uintptr_t translate_va2pa(uintptr_t va){
    uint64_t entry;
    int fd = open("/proc/self/pagemap", O_RDONLY);
    if (fd < 0) {
        perror("open pagemap error");
        return 0;
    }
    off_t off = ((va >> 12) * 8);
    lseek(fd, off, SEEK_SET);

    read(fd, &entry, 8);
    if (!(entry & (1ULL << 63))) {
        perror("page not present");
        return 0;
    }
    uint64_t pfn = entry & ((1ULL << 55) - 1);
    close(fd);

    return (pfn << 12);
}

void* check_hugepage(int index){
    if(index > (REGIONS_PER_HP - 1)){
        perror("index error");      
    }

    void *p = mmap(NULL,
                NUM_HPAGES * HPAGE_SIZE,
                PROT_READ | PROT_WRITE,
                MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB,
                -1, 0);
    if (p == MAP_FAILED) {
        perror("mmap hugepage error");
        return NULL;
    }
    memset(p, 0, NUM_HPAGES * HPAGE_SIZE);
    memset(p, 0, NUM_HPAGES * HPAGE_SIZE);

    uintptr_t vaddr = (uintptr_t)p;
    uintptr_t paddr = translate_va2pa(vaddr);
    if(paddr == 0)
        return NULL;
    
    int i=1;
    while(paddr != 0x101800000){
        vaddr = (uintptr_t)p + (i*HPAGE_SIZE);
        paddr = translate_va2pa(vaddr);
        if(paddr == 0)
            return NULL;
        i++;
        if(i>NUM_HPAGES){
            return NULL;
        }
    }

    uintptr_t va_start = vaddr;
    uintptr_t vaddr1 = (uintptr_t)va_start + ((index/4)*HPAGE_SIZE);
    uintptr_t paddr1 = translate_va2pa(vaddr1);
    if(paddr1 == 0)
        return NULL;

    uintptr_t vaddr2 = (uintptr_t)va_start + (index*REGION_SIZE);
    uintptr_t paddr2 = translate_va2pa(vaddr2);
    if(paddr2 == 0)
        return NULL;

    snprintf(log_info, sizeof(log_info), "Array region pa: 0x%lx, belong to hugepage: 0x%lx, index: %d\n", paddr2, paddr1, index);
    write(log_fd, log_info, strlen(log_info));

    return (void *)va_start;
}


void memory_read(fault_params *params){
    struct timespec end1, end2;

    int index = params->index;
    char *base = (char *)check_hugepage(index);
    if(base==NULL){
        return;
    }

    cl64_t *data = (cl64_t *)(base + index * REGION_SIZE);
    cl64_t *data2 = aligned_alloc(64, ARRAY_SIZE * sizeof(cl64_t));
    if (!data || !data2) {
        perror("aligned_alloc");
        return;
    }

    snprintf(log_info, sizeof(log_info), "memory read test\nretries is %d\nindex is %d\n", params->retries, index);
    write(log_fd, log_info, strlen(log_info));

    double volt_fault = params->volt_fault;
    double volt_prep = params->volt_prep;
    cl64_t pattern;
    memset(&pattern, 0xAC, sizeof(cl64_t));
    for (int iter = 0; iter < ARRAY_SIZE; iter++) {
        memset(&data[iter], 0x00, sizeof(cl64_t));
    }
    _mm_sfence();

    for(int i=0; i<50; i++) {
        volt_fault = volt_fault + 0.005;
        snprintf(log_info, sizeof(log_info), "pre_volt %.4f, pre_width %.6f, fault_volt %.4f, fault_width %.6f, index %d\n", volt_prep, params->width_prep, volt_fault, params->width_fault, params->index);
        write(log_fd, log_info, strlen(log_info));
        configurae_for_sa(1, 1, volt_prep, params->width_prep, volt_fault, params->width_fault, params->index);

        for (int ii=0; ii<params->retries; ii++){
            // uint8_t val = (uint8_t)(0xAC ^ (ii & 0xff));
            // memset(&pattern, val, sizeof(cl64_t));
            for (int iter = 0; iter < ARRAY_SIZE; iter++) {
                memcpy(&data[iter], &pattern, sizeof(cl64_t));
            }
            _mm_sfence();

            for(int iter = 0; iter < ARRAY_SIZE; iter++){
                _mm_clflush(&data[iter]);
            }
            _mm_sfence();

            //trigger before read
            fd_trigger = open("/dev/ttyS0", O_RDWR | O_NOCTTY );
            if( fd_trigger == -1 ) {
                snprintf(log_info, sizeof(log_info), "[ERROR]: Trigger serial: could not open port\n");
                write(log_fd, log_info, strlen(log_info));
                // write(log_fd, log_info, strlen(log_info));
                perror("open fd_trigger error!\n");
                return;
            }
            ioctl(fd_trigger, TIOCMBIC, &DTR);


            // start_DCpower_type1();
            // delay_us(300, 0.8);
            // clock_gettime(CLOCK_MONOTONIC, &end1);
            for(int iter = 0; iter < ARRAY_SIZE; iter++){
                memcpy(&data2[iter], &data[iter], sizeof(cl64_t));
            }
            // clock_gettime(CLOCK_MONOTONIC, &end2);
            // end_DCpower_type1();
            close(fd_trigger);
            msleep(20);

            for(int iter = 0; iter < ARRAY_SIZE; iter++){
                if(memcmp(&pattern, &data2[iter], sizeof(cl64_t)) != 0){
                    int pos = 0;
                    pos += snprintf(log_info + pos, sizeof(log_info), "[data2 fault at %d retries]   idx=%d: ", ii, iter);
                    for (int j = 0; j < 64; j++) {
                        pos += snprintf(log_info + pos, sizeof(log_info) - pos, "%02X ", data2[iter].bytes[j]);
                        if (pos >= sizeof(log_info) - 4) break;
                    }
                    pos += snprintf(log_info + pos, sizeof(log_info) - pos, "\n");
                    write(log_fd, log_info, strlen(log_info));
                }
            }   

            // test where fault happens.
            // for(int iter = 0; iter < ARRAY_SIZE; iter++){
            //     _mm_clflush(&data[iter]);
            // }
            // _mm_sfence();
            // for(int iter = 0; iter < ARRAY_SIZE; iter++){
            //     if(memcmp(&pattern, &data[iter], sizeof(cl64_t)) != 0){
            //         int pos = 0;
            //         pos += snprintf(log_info + pos, sizeof(log_info), "[data1 fault at %d retries] idx=%d: ", ii, iter);
            //         for (int j = 0; j < 64; j++) {
            //             pos += snprintf(log_info + pos, sizeof(log_info) - pos, "%02X ", data2[iter].bytes[j]);
            //             if (pos >= sizeof(log_info) - 4) break;
            //         }
            //         pos += snprintf(log_info + pos, sizeof(log_info) - pos, "\n");
            //         write(log_fd, log_info, strlen(log_info));
            //     }
            // }        

            for (int iter = 0; iter < ARRAY_SIZE; iter++) {
                memset(&data[iter], 0x00, sizeof(cl64_t));
            }
            _mm_sfence();

            // double duration1 = (end2.tv_sec - end1.tv_sec) + (end2.tv_nsec - end1.tv_nsec) / 1e9;
            // printf("memory access is %.9f second.\n", duration1);
        }
        close_BNC_Arb();
        msleep(1000);
    }

    snprintf(log_info, sizeof(log_info), "\n\n\nEnd momery test\n");
    write(log_fd, log_info, strlen(log_info));

    munmap(base, HPAGE_SIZE);
    free(data2);
}


void memory_write(fault_params *params){
    struct timespec end1, end2;
    cl64_t *data = aligned_alloc(64,  ARRAY_SIZE * sizeof(cl64_t));
    cl64_t *data2 = aligned_alloc(64, ARRAY_SIZE * sizeof(cl64_t));
    if (!data || !data2) {
        perror("aligned_alloc");
    }

    snprintf(log_info, sizeof(log_info), "memory write test\nretries is %d\n\n", params->retries); 
    write(log_fd, log_info, strlen(log_info));

    double volt_fault = params->volt_fault;
    cl64_t pattern;
    memset(&pattern, 0xAC, sizeof(cl64_t));
    for (int iter = 0; iter < ARRAY_SIZE; iter++) {
        memset(&data[iter], 0x00, sizeof(cl64_t));
    }
    _mm_sfence();

    for(int i=0; i<1000; i++) {
        volt_fault = volt_fault + 0.003;
        snprintf(log_info, sizeof(log_info), "pre_volt %.4f, pre_width %.6f, fault_volt %.4f, fault_width %.6f, index %d\n", params->volt_prep, params->width_prep, volt_fault, params->width_fault, params->index);
        write(log_fd, log_info, strlen(log_info));
        configurae_for_sa(1, 1, params->volt_prep, params->width_prep, volt_fault, params->width_fault, params->index);

        for (int ii=0; ii<params->retries; ii++){
            // uint8_t val = (uint8_t)(0xAC ^ (ii & 0xff));
            // memset(&pattern, val, sizeof(cl64_t));
            for (int iter = 0; iter < ARRAY_SIZE; iter++) {
                memset(&data[iter], 0x00, sizeof(cl64_t));
            }
            _mm_sfence();
            for (int iter = 0; iter < ARRAY_SIZE; iter++) {
                memcpy(&data[iter], &pattern, sizeof(cl64_t));
            }
            _mm_sfence();


            //trigger before write
            fd_trigger = open("/dev/ttyS0", O_RDWR | O_NOCTTY );
            if( fd_trigger == -1 ) {
                snprintf(log_info, sizeof(log_info), "[ERROR]: Trigger serial: could not open port\n");
                write(log_fd, log_info, strlen(log_info));
                // write(log_fd, log_info, strlen(log_info));
                perror("open fd_trigger error!\n");
            }
            ioctl(fd_trigger, TIOCMBIC, &DTR);

            for(int iter = 0; iter < ARRAY_SIZE; iter++){
                _mm_clflush(&data[iter]);
            }
            _mm_sfence();

            close(fd_trigger);
            msleep(20);

            // clock_gettime(CLOCK_MONOTONIC, &end1);
            for(int iter = 0; iter < ARRAY_SIZE; iter++){
                memcpy(&data2[iter], &data[iter], sizeof(cl64_t));
            }
            // clock_gettime(CLOCK_MONOTONIC, &end2);

            for(int iter = 0; iter < ARRAY_SIZE; iter++){
                if(memcmp(&pattern, &data2[iter], sizeof(cl64_t)) != 0){
                    int pos = 0;
                    pos += snprintf(log_info + pos, sizeof(log_info), "[fault at %d retries] idx=%d: ", ii, iter);
                    for (int j = 0; j < 64; j++) {
                        pos += snprintf(log_info + pos, sizeof(log_info) - pos, "%02X ", data2[iter].bytes[j]);
                        if (pos >= sizeof(log_info) - 4) break;
                    }
                    pos += snprintf(log_info + pos, sizeof(log_info) - pos, "\n");
                    write(log_fd, log_info, strlen(log_info));
                }
            }          

            for (int iter = 0; iter < ARRAY_SIZE; iter++) {
                memset(&data[iter], 0x00, sizeof(cl64_t));
            }
            _mm_sfence();

            // double duration1 = (end2.tv_sec - end1.tv_sec) + (end2.tv_nsec - end1.tv_nsec) / 1e9;
            // printf("memory access is %.9f second.\n", duration1);
        }
        close_BNC_Arb();
        msleep(1000);
    }

    snprintf(log_info, sizeof(log_info), "\n\n\nEnd momery test\n");
    write(log_fd, log_info, strlen(log_info));

    free(data);
    free(data2);

}




int main(int argc, char **argv) {
    const char *program = argv[0];
    if (argc != 9)
    {
        printf("Need 8 args: %s <iterations> <frequency> <DC_pre_volt> <volt_prep> <width_prep> <volt_fault> <width_fault> <index>\n",program);
        return -1;
    }
    fault_params params;

    params.retries = atoi(argv[1]);
    set_freq(argv[2]);
    char *endptr;
    params.freq = strtod(argv[2], &endptr);
    double DC_pre_volt = atof(argv[3]);
    params.volt_prep = atof(argv[4]);
    params.width_prep = atof(argv[5]);
    params.volt_fault = atof(argv[6]);
    params.width_fault = atof(argv[7]);
    params.index = atoi(argv[8]);

    cpu_set_t my_set;        // Define your cpu_set bit mask.
    CPU_ZERO(&my_set);       // Initialize it all to 0, i.e. no CPUs selected.
    CPU_SET(1, &my_set);     // set the bit that represents core 1.
    sched_setaffinity(0, sizeof(cpu_set_t), &my_set); // Set affinity of tihs process to
    print_affinity();

    close_BNC_Arb();
    configurae_for_sa(1,1,DC_pre_volt,0,0,0,0);
    start_DCpower_type1();

    log_fd = open("./log.txt", O_WRONLY | O_CREAT | O_APPEND | O_SYNC, 0666);
    if (log_fd == -1){
        perror("open log.txt error!\n");
    }

    memory_read(&params);

    // memory_write(&params);




    close(log_fd);

    return 0;
}
