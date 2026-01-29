/*
 *  This file is part of the SGX-Step enclave execution control framework.
 *
 *  Copyright (C) 2017 Jo Van Bulck <jo.vanbulck@cs.kuleuven.be>,
 *                     Raoul Strackx <raoul.strackx@cs.kuleuven.be>
 *
 *  SGX-Step is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SGX-Step is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with SGX-Step. If not, see <http://www.gnu.org/licenses/>.
 */

#include <sgx_urts.h>
#include "Enclave/encl_u.h"
#include <sys/mman.h>
#include <signal.h>

#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <pthread.h>
#include <sched.h>
#include <assert.h>
#include <linux/ioctl.h>
#include <linux/serial.h>
#include <openssl/sha.h>
#include "DCbias.h"
#define DEBUG_OUTPUT

/* OCall functions */
void ocall_print_string(const char *str)
{
    /* Proxy/Bridge will check the length and null-terminate 
     * the input string to prevent buffer overflow. 
     */
    printf("%s", str);
}



int64_t my_round(float num)
{
    return num < 0 ? num - 0.5 : num + 0.5;
}


#define RSA_LEN 256
#define test_len 5

sgx_status_t sgx_ret = -1;


unsigned char *data;
size_t data_size = 84 * 1024 * 1024; //2*LLC
void *worker_thread(void *arg) {
    int core_id = *(int*)arg;

    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);
    if(pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) != 0) {
        perror("pthread_setaffinity_np");
        return NULL;
    }

    printf("Thread running on core %d\n", core_id);

    while(1) {
        for(size_t i = 0; i < data_size; i++) {
            data[i] += 1;
        }
    }

    return NULL;
}




int main( int argc, char **argv )
{
    int DTR = TIOCM_DTR;
    int fd_trigger = -1;
    int log_fd = -1;
    char log_info[512];
    log_fd = open("./log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (log_fd == -1) {
        exit(EXIT_FAILURE);
    }
    uint64_t result;
  
    cpu_set_t my_set;        // Define your cpu_set bit mask.
    CPU_ZERO(&my_set);       // Initialize it all to 0, i.e. no CPUs selected.
    CPU_SET(1, &my_set);     // set the bit that represents core 1.
    sched_setaffinity(0, sizeof(cpu_set_t), &my_set); // Set affinity of tihs process to
    print_affinity();       // CPU core mask, indicating which core this process will be running on.


	sgx_launch_token_t token = {0};
	int retval = 0, updated = 0;
    sgx_enclave_id_t eid = 0;
    uint8_t buffer[RSA_LEN] = { 0 };

    const char* program = argv[0];
    if (argc != 9)
    {
        printf("Need 8 args: %s <iterations> <frequency> <DC_volt> <volt_prep> <width_prep> <volt_fault> <width_fault> <delay>\n",program);
        exit (-1);
    }

   	
	sgx_ret = sgx_create_enclave( "./Enclave/encl.so", /*debug=*/ 1,
                                    &token, &updated, &eid, NULL );
	if (SGX_SUCCESS != sgx_ret){
        printf("[ERROR]: sgx error 0x%x\n", sgx_ret);
        return -1;
    }
    snprintf(log_info, sizeof(log_info), "Creating enclave...\n\n");
    write(log_fd, log_info, strlen(log_info));  

    uint8_t res_var = 0;
    uint32_t iterations = atoi(argv[1]);

    set_freq(argv[2]);
    char *endptr;
    double freq = strtod(argv[2], &endptr);
    double DC_volt = atof(argv[3]);
    double volt_prep = atof(argv[4]);
    double width_prep = atof(argv[5]);
    double volt_fault = atof(argv[6]);
    double width_fault = atof(argv[7]);  
    double delay = atof(argv[8]);

    unsigned char fault_hash[66];

    data = malloc(data_size);
    if (!data) {
        perror("malloc");
        return 1;
    }
    memset(data, 0, data_size);

    pthread_t tid;
    int core_id = 29; //sibling core of 1.
    if(pthread_create(&tid, NULL, worker_thread, &core_id) != 0) {
        perror("pthread_create");
        return 1;
    }


    close_BNC_Arb(1);
    close_BNC_Arb(2);
    configurae_for_vddq(1,1,DC_volt,0,0,0,0);
    configurae_for_vddq(1,2,DC_volt,0,0,0,0);
    start_DCpower_type1(1);
    start_DCpower_type1(2);
    struct timespec start, end1, end2, end3, end4;

    for (int i=0;i<200;i++){
        volt_fault += 0.005;
        snprintf(log_info, sizeof(log_info), "pre_volt %.4f, pre_width %.6f, fault_volt %.4f, fault_width %.6f, delay %.6f\n", volt_prep, width_prep, volt_fault, width_fault, delay);
        write(log_fd, log_info, strlen(log_info));
        configurae_for_vddq(1, 1, volt_prep, width_prep, volt_fault, width_fault, delay);
        configurae_for_vddq(1, 2, volt_prep, width_prep, volt_fault, width_fault, delay);
        // Target ecall
        for (uint32_t cnt=0; cnt < iterations; cnt++){
            fd_trigger = open("/dev/ttyS0", O_RDWR | O_NOCTTY );
            if( fd_trigger == -1 ) {
                snprintf(log_info, sizeof(log_info), "[ERROR]: Trigger serial: could not open port\n");
                write(log_fd, log_info, strlen(log_info));
                return -1;
            }
            ioctl(fd_trigger, TIOCMBIC, &DTR);

            clock_gettime(CLOCK_MONOTONIC, &end2);
            sgx_ret = SHA512_ecall(eid, &res_var, fault_hash);
            clock_gettime(CLOCK_MONOTONIC, &end3);

            if (SGX_SUCCESS != sgx_ret){
                snprintf(log_info, sizeof(log_info), "[ERROR]: SHA512_ecall error 0x%x\n", sgx_ret);
                write(log_fd, log_info, strlen(log_info));
                return -1;
            }


            asm volatile("" ::: "memory");
            msleep(20);
            
            close(fd_trigger);
            if(fault_hash[0] == 1){
                snprintf(log_info, sizeof(log_info), "[Enclave]: find fault at iterations %d\n",cnt);
                write(log_fd, log_info, strlen(log_info));
                for(int j=1;j<65;j++){
                    snprintf(log_info, sizeof(log_info), "0x%02x ", fault_hash[j]);
                    write(log_fd, log_info, strlen(log_info));
                }
                write(log_fd, "\n\n", strlen("\n\n"));
                fault_hash[0] = 0;
            }
            
            // double duration2 = (end3.tv_sec - end2.tv_sec) + (end3.tv_nsec - end2.tv_nsec) / 1e9;
            // printf("SHA512_ecall time2 is %.9f second.\n", duration2);
        }
        close_BNC_Arb(1);
        close_BNC_Arb(2);
    }

done:
    sgx_ret = sgx_destroy_enclave(eid);
	if (SGX_SUCCESS != sgx_ret){
        snprintf(log_info, sizeof(log_fd), "[ERROR]: sgx_destroy_enclave error 0x%x\n", sgx_ret);
        write(log_fd, log_info, strlen(log_info));       
	}
    snprintf(log_info, sizeof(log_info), "Exiting...\n");
    write(log_fd, log_info, strlen(log_info));
    close(log_fd);

	return 0;
}
