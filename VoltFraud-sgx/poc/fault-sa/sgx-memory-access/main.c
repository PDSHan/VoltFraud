#include <sgx_urts.h>
#include "Enclave/encl_u.h"
#include <sys/mman.h>
#include <signal.h>
#include <curses.h>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>
#include "DCbias.h"
#include <linux/ioctl.h>
#include <linux/serial.h>


#define BUFLEN 2048
#define SGX_AESGCM_MAC_SIZE 16
#define SGX_AESGCM_IV_SIZE 12

#define ENCLAVE_FILE "CryptoEnclave.signed.so"

int log_fd = -1;
char log_info[1024];
int fd_trigger = -1;

void write_log(const char *str)
{
    if (log_fd == -1) {
        perror("open log");
        exit(EXIT_FAILURE);
    }

    write(log_fd, str, strlen(str));
}


/* OCall functions */
void ocall_print_string(const char *str)
{
	/* Proxy/Bridge will check the length and null-terminate 
	 * the input string to prevent buffer overflow. 
	 */
	write_log(str);
    
}


int main(int argc, char **argv)
{
	log_fd = open("./log.txt", O_WRONLY | O_CREAT | O_APPEND | O_SYNC, 0666);
    if (log_fd == -1) {
        exit(EXIT_FAILURE);
    }

    cpu_set_t my_set;        // Define your cpu_set bit mask.
    CPU_ZERO(&my_set);       // Initialize it all to 0, i.e. no CPUs selected.
    CPU_SET(1, &my_set);     // set the bit that represents core 1.
    sched_setaffinity(0, sizeof(cpu_set_t), &my_set); // Set affinity of tihs process to
    print_affinity();

	sgx_launch_token_t token = {0};
	int retval = 0, updated = 0;
    sgx_status_t sgx_ret = -1;
	sgx_enclave_id_t eid = 0;
	uint64_t ret;
	const char *program = argv[0];

    if (argc != 9)
    {
        printf("Need 8 args: %s <iterations> <frequency> <DC_pre_volt> <volt_prep> <width_prep> <volt_fault> <width_fault> <delay>\n",program);
        exit (-1);
    }

	sgx_ret = sgx_create_enclave("./Enclave/encl.so", /*debug=*/1, &token, &updated, &eid, NULL);
    if (SGX_SUCCESS != sgx_ret){
        snprintf(log_info, sizeof(log_info), "[ERROR]: sgx_create_enclave error 0x%x\n", sgx_ret);
        write_log(log_info);
        return -1;
    }
    snprintf(log_info, sizeof(log_info), "Create Enclave...\n\n");
    write_log(log_info);


	int DTR = TIOCM_DTR;
    uint8_t res_var = 0;

    uint32_t iterations = atoi(argv[1]);
    set_freq(argv[2]);
    char *endptr;
    double freq = strtod(argv[2], &endptr);
    double DC_pre_volt = atof(argv[3]);
    double volt_prep = atof(argv[4]);
    double width_prep = atof(argv[5]);
    double volt_fault = atof(argv[6]);
    double width_fault = atof(argv[7]);  
    double delay = atof(argv[8]);

    close_BNC_Arb();
    configure_glitch_with_delay(1,1,DC_pre_volt,0,0,0,0);
    start_DCpower_type1();
	struct timespec start, end1, end2, end3, end4;

	for(int i=0; i<1000; i++) {
		volt_fault += 0.003;
        snprintf(log_info, sizeof(log_info), "pre_volt %.4f, pre_width %.6f, fault_volt %.4f, fault_width %.6f, delay %.6f\n", volt_prep, width_prep, volt_fault, width_fault, delay);
        write_log(log_info);
        configurae_for_mc(1, 1, volt_prep, width_prep, volt_fault, width_fault, delay);
        
        // Target ecall
		for (int ii =0; ii< iterations; ii++) {
            fd_trigger = open("/dev/ttyS0", O_RDWR | O_NOCTTY );
            if( fd_trigger == -1 ) {
                snprintf(log_info, sizeof(log_info), "[ERROR]: Trigger serial: could not open port\n");
                write_log(log_info);
                return -1;
            }
            ioctl(fd_trigger, TIOCMBIC, &DTR);

            // clock_gettime(CLOCK_MONOTONIC, &end2);
			sgx_ret = memory_access_ecall(eid, &res_var);
            // clock_gettime(CLOCK_MONOTONIC, &end3);
            if (SGX_SUCCESS != sgx_ret){
                snprintf(log_info, sizeof(log_info), "[ERROR]: memory_access_ecall error 0x%x\n", sgx_ret);
                write_log(log_info);
                return -1;
            }
            close(fd_trigger);
            msleep(20);

            // double duration2 = (end3.tv_sec - end2.tv_sec) + (end3.tv_nsec - end2.tv_nsec) / 1e9;
            // printf("memory_access_ecall time is %.9f second.\n", duration2);
		}
        msleep(1000);
        close_BNC_Arb();
	}

    close(log_fd);
	sgx_destroy_enclave(eid);


	return 0;
}
