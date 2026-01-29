#define _GNU_SOURCE
#include <stdio.h>
#include <errno.h>   	 // ERROR Number Definitions
#include <fcntl.h>   	 // File Control Definitions
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sched.h>
#include <linux/serial.h>
#include "DCbias.h"




int channel;

void log_sensors_output(int log_fd) {
    FILE *fp = popen("sensors", "r");
    if (!fp) return;

    FILE *log = fdopen(dup(log_fd), "a");
    if (!log) {
        pclose(fp);
        return;
    }

    char buf[256];
    while (fgets(buf, sizeof(buf), fp)) {
        fputs(buf, log);
    }

    fclose(log);
    pclose(fp);
}

void print_affinity() {
    cpu_set_t mask;
    long nproc, i;

    if (sched_getaffinity(0, sizeof(cpu_set_t), &mask) == -1) {
        perror("sched_getaffinity");
        assert(0);
    }
    nproc = sysconf(_SC_NPROCESSORS_ONLN);
    printf("sched_getaffinity = ");
    for (i = 0; i < nproc; i++) {
        printf("%d ", CPU_ISSET(i, &mask));
    }
    printf("\n");
}

void set_freq(char* freq){
    char cmd[200];
    sprintf(cmd, "cpupower -c all frequency-set -u %s", freq);
    system(cmd);
    sprintf(cmd, "cpupower -c all frequency-set -d %s", freq);
    system(cmd);

    sleep(2);
    system("grep \"cpu MHz\" /proc/cpuinfo");
}

void delay_us(double us, double tsc_ghz) {
    uint64_t cycles = (uint64_t)(us * tsc_ghz * 1000.0); // us→cycles
    uint64_t start = rdtsc();
    while (rdtsc() - start < cycles) {
        // busy wait
    }
}



//voltage format is X.XXXXX(V), time format is X.XXXX(s).
int float2int(float v){
    return (int)(v * 10000 + 0.5f);
}


int configurae_for_vddq(int repeat, int ch, float prep_volt, float prep_width, float fault_volt, float falut_width, float delay){
    char cmd[256];
    if(float2int(fault_volt) == 0){
        snprintf(cmd, sizeof(cmd), "python3 /home/xxx/VoltFraud-Scalable-sgx/lib/DCpower_ctr.py cfg_type1 %.4f %d", prep_volt, ch);
    }
    else{
        snprintf(cmd, sizeof(cmd), "python3 /home/xxx/VoltFraud-Scalable-sgx/lib/DCpower_ctr.py cfg_type2 %d %.4f %.6f %.4f %.6f 1 %d", repeat, prep_volt, prep_width, fault_volt, falut_width, ch);
    }
    printf("%s\n", cmd);
    system(cmd);
    return 0;
}


int configure_glitch_with_delay(int repeat, int ch, float prep_volt, float prep_width, float fault_volt, float falut_width, float delay){
    float DCpower_v1, DCpower_v2;
    channel=ch;
    char cmd[256];
    // we need special method to trigger type1 configurations.
    if(float2int(fault_volt) == 0){
        // DCpower_v1 = prep_volt  / 0.65;
        DCpower_v1 = prep_volt;
        snprintf(cmd, sizeof(cmd), "python3 /home/xxx/VoltFraud-Scalable-sgx/lib/DCpower_ctr.py cfg_type1 %.4f", DCpower_v1);
        printf("%s\n", cmd);
        system(cmd);
    }
    else{
        // DCpower_v1 = prep_volt / 0.65; //v1 and v2 must greater than 0.016.
        // DCpower_v2 = fault_volt / 0.65;
        DCpower_v1 = prep_volt;
        DCpower_v2 = fault_volt;   
        if(float2int(prep_volt) == 0)
            snprintf(cmd, sizeof(cmd), "python3 /home/xxx/VoltFraud-Scalable-sgx/lib/DCpower_ctr.py cfg_type2 %d %.4f %.6f %.4f %.6f 0", repeat, DCpower_v1, prep_width, DCpower_v2, falut_width);
        else
            snprintf(cmd, sizeof(cmd), "python3 /home/xxx/VoltFraud-Scalable-sgx/lib/DCpower_ctr.py cfg_type2 %d %.4f %.6f %.4f %.6f 1", repeat, DCpower_v1, prep_width, DCpower_v2, falut_width);
        printf("%s\n", cmd);
        system(cmd);
        // ret = configure_DCpower_type2(DCpower_v1, d1, DCpower_v2, d2, delay);
        // if(ret < 0){
        //     func_error("Configure DC power type2 error!\n");
        // }
        // ret = configure_DCpower_trigger(repeat);
        // if(ret < 0){
        //     func_error("Configure DC power trigger error!\n");
        // }
    }

    return 0;
}

int start_DCpower_type1(int channel){
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "python3 /home/xxx/VoltFraud-Scalable-sgx/lib/DCpower_ctr.py cmd ON %d", channel);
    system(cmd);

    return 0;
}

int end_DCpower_type1(int channel){   
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "python3 /home/xxx/VoltFraud-Scalable-sgx/lib/DCpower_ctr.py cmd OFF %d", channel);
    system(cmd);

    return 0;
}

int close_BNC_Arb(int channel){
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "python3 /home/xxx/VoltFraud-Scalable-sgx/lib/DCpower_ctr.py close_BNC_Arb %d", channel);
    system(cmd);

    return 0;
}


int dmesg_init(size_t *offset)
{
    FILE *fp = popen("dmesg", "r");
    if (!fp) return -1;

    char buf[4096];
    size_t total = 0;

    while (fgets(buf, sizeof(buf), fp)) {
        total += strlen(buf);
    }
    pclose(fp);

    *offset = total;
    return 0;
}

int dmesg_poll_and_log(int log_fd, size_t *offset)
{
    FILE *fp = popen("dmesg", "r");
    if (!fp) return -1;

    char buf[4096];
    size_t cur = 0;

    while (fgets(buf, sizeof(buf), fp)) {
        size_t len = strlen(buf);
        if (cur >= *offset) {
            write(log_fd, buf, len);
        }
        cur += len;
    }
    pclose(fp);
    *offset = cur;
    return 0;
}


int kmsg_init(int *init_byte_num)
{
    int fd = open("/dev/kmsg", O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    char buf[4096];
    ssize_t n;
    *init_byte_num=0;
    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        *init_byte_num += n;
    }
    close(fd);

    return 0;
}


int kmsg_poll_and_log(int *old_byte_num, int log_fd)
{
    int fd = open("/dev/kmsg", O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    char buf[4096];
    ssize_t n;
    int skipped = 0;

    while ((n = read(fd, buf, sizeof(buf))) > 0) {

        if (skipped + n <= *old_byte_num) {
            skipped += n;
            continue;
        }

        if (skipped < *old_byte_num) {
            ssize_t start = *old_byte_num - skipped;
            write(log_fd, buf + start, n - start);
            skipped += n;
            continue;
        }

        write(log_fd, buf, n);
        skipped += n;
    }

    *old_byte_num = skipped;
    close(fd);
    return 0;
}


int setup_dtr(){
    int fd_trigger;
	//// Configure on-board serial (to be used as trigger)
	fd_trigger = open("/dev/ttyS0", O_RDWR | O_NOCTTY );
	if( fd_trigger==-1 ) {
		printf("Trigger serial: could not open port\n");
		return -1;
	}
	printf("Trigger serial: opened port %s\n","/dev/ttyS0");


	// Create new termios struc, we call it 'tty' for convention
	struct termios tty;
	memset(&tty, 0, sizeof tty);

	// Read in existing settings, and handle any error
	if(tcgetattr(fd_trigger, &tty) != 0) {
		printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
	}

	tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
	tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
	tty.c_cflag |= CS8; // 8 bits per byte (most common)
	tty.c_cflag &= ~CRTSCTS;
	tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

	tty.c_lflag &= ~ICANON;
	tty.c_lflag &= ~ECHO; // Disable echo
	tty.c_lflag &= ~ECHOE; // Disable erasure
	tty.c_lflag &= ~ECHONL; // Disable new-line echo
	tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
	tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

	tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
	tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
	//tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
	//tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

	tty.c_cc[VTIME] = 0;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
	tty.c_cc[VMIN] = 0;

	// Set in/out baud rate to be 9600
	cfsetispeed(&tty, B38400);
	cfsetospeed(&tty, B38400);


	struct serial_struct kernel_serial_settings;
	int r = ioctl(fd_trigger, TIOCGSERIAL, &kernel_serial_settings);
	if (r >= 0) {
		kernel_serial_settings.flags |= ASYNC_LOW_LATENCY;
		r = ioctl(fd_trigger, TIOCSSERIAL, &kernel_serial_settings);
		if (r >= 0) printf("set linux low latency mode\n");
	}

	tcsetattr(fd_trigger, TCSANOW, &tty);
	if( tcsetattr(fd_trigger, TCSAFLUSH, &tty) < 0) {
		perror("init_serialport: Couldn't set term attributes");
		return -1;
	}

    return 0;
}
