#ifndef DCBIAS_H
#define DCBIAS_H

#include <sys/ioctl.h>   // ioctl()
#include <termios.h>	 // POSIX Terminal Control Definitions
#include <unistd.h>      // for usleep()
#include <time.h>
#include <string.h>
#include <stdint.h>
#include <linux/ioctl.h>
#include <linux/serial.h>
#include <sched.h>
#include <assert.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>


extern int channel;


#define msleep(tms) ({usleep(tms * 1000);})

#define TRIGGER_BUS_CMD     "*TRG\n"
#define TRIGGER_BUS viWrite(instr_DCpower, (ViBuf)TRIGGER_BUS_CMD, strlen(TRIGGER_BUS_CMD), &retCount_DCpower); 

static inline uint64_t rdtsc() {
    unsigned hi, lo;
    __asm__ volatile ("rdtsc" : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}

void delay_us(double us, double tsc_ghz);

int configure_glitch_with_delay(int repeat, int ch, float v1, float d1, float v2, float d2, float delay);

int start_DCpower_type1();

int end_DCpower_type1();

int destroy_DCpower();

int close_BNC_Arb();

void print_affinity();

void set_freq(char* freq);

void log_sensors_output(int log_fd);

int configurae_for_vddq(int repeat, int ch, float prep_volt, float prep_width, float fault_volt, float falut_width, float delay);

int dmesg_init(size_t *offset);
int dmesg_poll_and_log(int log_fd, size_t *offset);

int kmsg_init(int *init_byte_num);
int kmsg_poll_and_log(int *old_byte_num, int log_fd);

int setup_dtr();

#endif