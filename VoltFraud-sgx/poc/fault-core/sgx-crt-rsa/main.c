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

#include "DCbias.h"
#define DEBUG_OUTPUT

/* OCall functions */
void ocall_print_string(const char *str)
{
    /* Proxy/Bridge will check the length and null-terminate 
     * the input string to prevent buffer overflow. 
     */
    printf("Enclave: %s", str);
}



int64_t my_round(float num)
{
    return num < 0 ? num - 0.5 : num + 0.5;
}

volatile int fault_fired = 0;

// Handle the page fault in thread dummy_page
void fault_handler(int signal)
{
	// Restore memory permissions, this will continue the thread when the fault handler returns
    if(fault_fired == 0)
    {
    }

	fault_fired++;
}

#define RSA_LEN 256
#define test_len 5

const uint8_t result_exp[RSA_LEN] = {0x2d, 0x3e, 0x35, 0x4d, 0x6d, 0xb7, 0xf1, 0xd2, 0x32, 0xce, 0x81, 0x52, 0x19, 0x75, 0xc2, 0x7b, 0x4f, 0xc1, 0x3a, 0x2f, 0x97, 0xdb, 0x48, 0x04, 0xb4, 0xae, 0x95, 0xd0, 0x87, 0x3e, 0xfb, 0x82, 0xf9, 0x92, 0xe3, 0x1b, 0x59, 0x11, 0x58, 0x43, 0x21, 0x41, 0x02, 0xd5, 0x69, 0x28, 0x8d, 0xb4, 0x9a, 0xd2, 0xaa, 0x2b, 0x36, 0xc1, 0xb7, 0xa1, 0xb4, 0x28, 0x77, 0xf4, 0x4f, 0xfe, 0xdc, 0x4c, 0xdb, 0x2d, 0x9a, 0x83, 0x0e, 0xe1, 0x8a, 0xff, 0xb3, 0xc2, 0xc9, 0x25, 0xfb, 0xdc, 0x3e, 0xf9, 0xaf, 0xf5, 0x26, 0x46, 0xc0, 0xb2, 0xe0, 0xd7, 0x84, 0x1f, 0x25, 0xb4, 0x8b, 0x2e, 0x1b, 0xc3, 0x67, 0x52, 0xf5, 0xa8, 0xee, 0xf1, 0x68, 0x5c, 0x7d, 0xd8, 0xdc, 0x26, 0x0b, 0x31, 0x82, 0xca, 0xe2, 0x45, 0x4b, 0x50, 0x29, 0xe3, 0x50, 0x63, 0x00, 0xe3, 0xe9, 0xac, 0x19, 0x7a, 0xeb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

volatile int flag1 = 0, flag2 = 0;
int fd0 = 0;

uint64_t val_plane0 = 0;
uint64_t val_plane2 = 0;
uint64_t val_zero_plane0 = 0;
uint64_t val_zero_plane2 = 0;
uint64_t tick = 0;

int sgx_ret = -1;

#define TICK_MAX (5347771/3)


int main( int argc, char **argv )
{
    int DTR = TIOCM_DTR;
    int fd_trigger = -1;
    int log_fd = -1;

    log_fd = open("./log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (log_fd == -1) {
        exit(EXIT_FAILURE);
    }

    cpu_set_t my_set;        // Define your cpu_set bit mask.
    CPU_ZERO(&my_set);       // Initialize it all to 0, i.e. no CPUs selected.
    CPU_SET(1, &my_set);     // set the bit that represents core 1.
    sched_setaffinity(0, sizeof(cpu_set_t), &my_set); // Set affinity of tihs process to
    print_affinity();       // CPU core mask, indicating which core this process will be running on.


	sgx_launch_token_t token = {0};
	int retval = 0, i = 0, updated = 0;
    sgx_enclave_id_t eid = 0;
    uint8_t buffer[RSA_LEN] = { 0 };
    fault_fired = 0;
    pthread_t t1;

   	printf("Creating enclave...\n");

	sgx_ret = sgx_create_enclave( "./Enclave/encl.so", /*debug=*/ 1,
                                    &token, &updated, &eid, NULL );
	if (SGX_SUCCESS != sgx_ret){
		printf("[ERROR]: sgx error 0x%x\n", sgx_ret);
	}


    int j = 0;
    const char* program = argv[0];

    if (argc != 9)
    {
        printf("Need 8 args: %s <iterations> <frequency> <DC_pre_volt> <volt_prep> <width_prep> <volt_fault> <width_fault> <delay>\n",program);
        exit (-1);
    }

    
    char log_info[512];
    
    // Target ecall
    snprintf(log_info, sizeof(log_info), "init RSA...\n");
    write(log_fd, log_info, strlen(log_info));


    uint8_t res_var = 0;
    sgx_ret = rsa_init_ecall(eid, &res_var);
	if (SGX_SUCCESS != sgx_ret){
        snprintf(log_info, sizeof(log_info), "[ERROR]: sgx error 0x%x\n", sgx_ret);
        write(log_fd, log_info, strlen(log_info));
	}

    if(res_var != 1)
    {
        snprintf(log_info, sizeof(log_info), "[ERROR]: Could not init RSA!\n");
        write(log_fd, log_info, strlen(log_info));
        goto done;
    }

    uint32_t iterations = atoi(argv[1]);
    // uint32_t iterations_50k = 50000-iterations;

    set_freq(argv[2]);
    char *endptr;
    double freq = strtod(argv[2], &endptr);
    
    double DC_volt = atof(argv[3]);
    double volt_prep = atof(argv[4]);
    double width_prep = atof(argv[5]);
    double volt_fault = atof(argv[6]);
    double width_fault = atof(argv[7]);  
    double delay = atof(argv[8]);


    close_BNC_Arb();
    configure_glitch_with_delay(1,1,DC_volt,0,0,0,0);
    start_DCpower_type1();
    int find_fault[2] = {0};
    uint64_t fault[test_len] = {0};
    for (int i=0;i<200;i++){
        volt_fault += 0.003;
        snprintf(log_info, sizeof(log_info), "pre_volt %.4f, pre_width %.6f, fault_volt %.4f, fault_width %.6f, delay %.6f\n", volt_prep, width_prep, volt_fault, width_fault, delay);
        write(log_fd, log_info, strlen(log_info));
        configure_glitch_with_delay(1, 1, volt_prep, width_prep, volt_fault, width_fault, delay);
        // Target ecall
        for (uint32_t cnt=0; cnt < iterations; cnt++){
            struct timespec start, end1, end2, end3, end4;
            // clock_gettime(CLOCK_MONOTONIC, &start);

            fd_trigger = open("/dev/ttyS0", O_RDWR | O_NOCTTY );
            if( fd_trigger == -1 ) {
                snprintf(log_info, sizeof(log_info), "[ERROR]: Trigger serial: could not open port\n");
                write(log_fd, log_info, strlen(log_info));
                return -1;
            }
            ioctl(fd_trigger, TIOCMBIC, &DTR);

            // clock_gettime(CLOCK_MONOTONIC, &end1);
            asm volatile("" ::: "memory");
            
            //wait undervoltage 
            delay_us(delay, freq);
            // clock_gettime(CLOCK_MONOTONIC, &end2);
            sgx_ret = rsa_dec_ecall(eid, &res_var, buffer);
            // clock_gettime(CLOCK_MONOTONIC, &end3);
            if (SGX_SUCCESS != sgx_ret){
                snprintf(log_info, sizeof(log_info), "[ERROR]: multiply_ecall error 0x%x\n", sgx_ret);
                write(log_fd, log_info, strlen(log_info));
                return -1;
            }
            
            asm volatile("" ::: "memory");
            close(fd_trigger);

            if(memcmp(buffer, result_exp, RSA_LEN) != 0)
            {
                snprintf(log_info, sizeof(log_info), "[Enclave]: iterations %d:\n", cnt);
                write(log_fd, log_info, strlen(log_info));
                snprintf(log_info, sizeof(log_info), "[Enclave]: Noooo!!!!1111elfoelf\n");
                write(log_fd, log_info, strlen(log_info));
                log_sensors_output(log_fd);
                for(i = 0; i < RSA_LEN; i++)
                {
                    snprintf(log_info, sizeof(log_info), "0x%02x, ", buffer[i]);
                    write(log_fd, log_info, strlen(log_info));
                }
                // close(log_fd);
                // break;
            }
            msleep(20);
            // clock_gettime(CLOCK_MONOTONIC, &end4);
            // double duration1 = (end2.tv_sec - end1.tv_sec) + (end2.tv_nsec - end1.tv_nsec) / 1e9;
            // double duration2 = (end3.tv_sec - end2.tv_sec) + (end3.tv_nsec - end2.tv_nsec) / 1e9;
            // double duration3 = (end4.tv_sec - start.tv_sec) + (end4.tv_nsec - start.tv_nsec) / 1e9;
            // printf("flush memory time is %.9f second.\n", duration1);
            // printf("rsa_dec_ecall time is %.9f second.\n", duration2);
            // printf("iterations time is %.9f second.\n", duration3);
        }
        msleep(1000);
        close_BNC_Arb();
    }

    close(log_fd);

    sgx_ret = rsa_clean_ecall(eid, &res_var);
    if (SGX_SUCCESS != sgx_ret){
        snprintf(log_info, sizeof(log_info), "[ERROR]: rsa_clean_ecall error 0x%x\n", sgx_ret);
        write(log_fd, log_info, strlen(log_info));
        return -1;
    }

done:
    sgx_ret = sgx_destroy_enclave(eid);
	if (SGX_SUCCESS != sgx_ret){
        snprintf(log_info, sizeof(log_fd), "[ERROR]: sgx_destroy_enclave error 0x%x\n", sgx_ret);
        write(log_fd, log_info, strlen(log_info));       
	}
    snprintf(log_info, sizeof(log_info), "Exiting...\n");
    write(log_fd, log_info, strlen(log_info));
	return 0;
}
