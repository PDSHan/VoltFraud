#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>
#include <string.h>

#define ARRAY_SIZE (4096*2)
typedef struct {
    uint8_t bytes[64];
} __attribute__((aligned(64))) cl64_t;
#define HPAGE_SIZE (2UL * 1024 * 1024)
#define NUM_HPAGES 128
#define REGION_SIZE  (ARRAY_SIZE * sizeof(cl64_t))   // 512KB
#define REGIONS_PER_HP (NUM_HPAGES * HPAGE_SIZE / REGION_SIZE)


int main() {
    void *p = mmap(NULL,
                   NUM_HPAGES * HPAGE_SIZE,
                   PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB,
                   -1, 0);
    if (p == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    memset(p, 0, NUM_HPAGES * HPAGE_SIZE);

    int fd = open("/proc/self/pagemap", O_RDONLY);
    if (fd < 0) {
        perror("open pagemap");
        return 1;
    }

    for (int i = 0; i < NUM_HPAGES; i++) {
        uintptr_t HPAGE_start = (uintptr_t)p + i * HPAGE_SIZE;

        for(int j=0;j<4;j++){
            uintptr_t vaddr = HPAGE_start + j * REGION_SIZE;
            uint64_t entry;
            off_t off = ((vaddr >> 12) * 8);
            lseek(fd, off, SEEK_SET);
            read(fd, &entry, 8);

            if (!(entry & (1ULL << 63))) {
                printf("hugepage %d: not present\n", i);
                continue;
            }

            uint64_t pfn = entry & ((1ULL << 55) - 1);
            uint64_t phys = pfn << 12;

            printf("hugepage %d:\n", i);
            printf("  vaddr = 0x%lx\n", vaddr);
            printf("  pfn   = 0x%lx\n", pfn);
            printf("  phys  = 0x%lx\n", phys);
        }
    }

    munmap(p, NUM_HPAGES * HPAGE_SIZE);
    
    return 0;
}
