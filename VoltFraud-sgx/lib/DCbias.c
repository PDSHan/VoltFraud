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

void func_error(char* msg)
{
	fprintf(stderr, "%s\n",msg);
	exit(-1);
}


//voltage format is X.XXXXX(V), time format is X.XXXX(s).
int float2int(float v){
    return (int)(v * 10000 + 0.5f);
}


int configurae_for_mc(int repeat, int ch, float prep_volt, float prep_width, float fault_volt, float falut_width, float delay){
    char cmd[256];
    if(float2int(fault_volt) == 0){
        prep_volt = prep_volt * 0.6666;
        snprintf(cmd, sizeof(cmd), "python3 /home/xxx/VoltFraud-sgx/lib/DCpower_ctr.py cfg_type1 %.4f", prep_volt);
    }
    else{
        prep_volt = prep_volt * 0.6666;
        fault_volt = fault_volt * 0.6666;
        snprintf(cmd, sizeof(cmd), "python3 /home/xxx/VoltFraud-sgx/lib/DCpower_ctr.py cfg_type2 %d %.4f %.6f %.4f %.6f 1", repeat, prep_volt, prep_width, fault_volt, falut_width);
    }
    printf("%s\n", cmd);
    system(cmd);
    return 0;
}

int configurae_for_sa(int repeat, int ch, float prep_volt, float prep_width, float fault_volt, float falut_width, float delay){
    char cmd[256];
    if(float2int(fault_volt) == 0){
        prep_volt = prep_volt * 0.6666;
        snprintf(cmd, sizeof(cmd), "python3 /home/xxx/VoltFraud-sgx/lib/DCpower_ctr.py cfg_type1 %.4f", prep_volt);
    }
    else{
        prep_volt = prep_volt * 0.6666;
        fault_volt = fault_volt * 0.6666;
        snprintf(cmd, sizeof(cmd), "python3 /home/xxx/VoltFraud-sgx/lib/DCpower_ctr.py cfg_type2 %d %.4f %.6f %.4f %.6f 1", repeat, prep_volt, prep_width, fault_volt, falut_width);
    }
    printf("%s\n", cmd);
    system(cmd);
    return 0;
}


// VCORE = Vnom - VSPbias
// VSPbias = 0.65 * DCpower
int configure_glitch_with_delay(int repeat, int ch, float prep_volt, float prep_width, float fault_volt, float falut_width, float delay){
    float DCpower_v1, DCpower_v2;
    channel=ch;
    char cmd[256];
    // we need special method to trigger type1 configurations.
    if(float2int(fault_volt) == 0){
        DCpower_v1 = prep_volt  / 0.65;
        snprintf(cmd, sizeof(cmd), "python3 /home/xxx/VoltFraud-sgx/lib/DCpower_ctr.py cfg_type1 %.4f", DCpower_v1);
        printf("%s\n", cmd);
        system(cmd);
    }
    else{
        DCpower_v1 = prep_volt / 0.65; //v1 and v2 must greater than 0.016.
        DCpower_v2 = fault_volt / 0.65;
        if(float2int(prep_volt) == 0)
            snprintf(cmd, sizeof(cmd), "python3 /home/xxx/VoltFraud-sgx/lib/DCpower_ctr.py cfg_type2 %d %.4f %.6f %.4f %.6f 0", repeat, DCpower_v1, prep_width, DCpower_v2, falut_width);
        else
            snprintf(cmd, sizeof(cmd), "python3 /home/xxx/VoltFraud-sgx/lib/DCpower_ctr.py cfg_type2 %d %.4f %.6f %.4f %.6f 1", repeat, DCpower_v1, prep_width, DCpower_v2, falut_width);
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

int start_DCpower_type1(){
    system("python3 /home/xxx/VoltFraud-sgx/lib/DCpower_ctr.py cmd ON");

    return 0;
}

int end_DCpower_type1(){   
    system("python3 /home/xxx/VoltFraud-sgx/lib/DCpower_ctr.py cmd OFF");

    return 0;
}

int close_BNC_Arb(){
    system("python3 /home/xxx/VoltFraud-sgx/lib/DCpower_ctr.py close_BNC_Arb");
    return 0;
}
