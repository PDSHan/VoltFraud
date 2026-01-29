#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <smmintrin.h>
#include <wmmintrin.h>
#include <immintrin.h>
#include <immintrin.h>
#include "sgx_tcrypto.h"
#include "sgx_trts.h"
#include "encl_t.h" // for ocall
#include <ipp/ippcp.h>
#include <stdio.h>

static void eprintf(const char *fmt, ...)
{
    char buf[1000] = {'\0'};
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, 1000, fmt, ap);
    va_end(ap);
    ocall_print_string(buf);
}



typedef struct {
    uint8_t bytes[64];
} __attribute__((aligned(64))) cl64_t;


sgx_status_t memory_access_ecall()
{
    
    int length = 12288;
    cl64_t data[length];
    cl64_t data2[length];

    cl64_t pattern;
    uint8_t val = (uint8_t)0xAC;
    memset(&pattern, val, sizeof(cl64_t));


    for (int iter = 0; iter < length; iter++) {
        memcpy(&data[iter], &pattern, sizeof(cl64_t));
    }
    _mm_sfence();

    for(int iter = 0; iter < length; iter++){
        _mm_clflush(&data[iter]);
    }
    _mm_sfence();


    for(int iter = 0; iter < length; iter++){
        memcpy(&data2[iter], &data[iter], sizeof(cl64_t));
    }

    for(int iter = 0; iter < length; iter++){
        if(memcmp(&pattern, &data2[iter], sizeof(cl64_t)) != 0){
            eprintf("[fault] idx=%d: ", iter);
            for (int j = 0; j < 64; j++) {
                eprintf("%02X ", data2[iter].bytes[j]);
            }
            eprintf('\n');
        }
    }  

    return SGX_SUCCESS;
}