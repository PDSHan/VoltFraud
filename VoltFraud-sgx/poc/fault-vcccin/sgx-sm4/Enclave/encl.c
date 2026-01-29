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


static void eprintf(const char *fmt, ...)
{
    char buf[1000] = {'\0'};
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, 1000, fmt, ap);
    va_end(ap);
    ocall_print_string(buf);
}

sgx_status_t sm4_ecall(unsigned char *plaintext, unsigned char *ciphertext, int length)
{
    uint8_t key[16] = {0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0xaa,0xab,0xac,0xad,0xae,0xaf};
    int pSize = 0;
    IppsSMS4Spec *pCtx;

    static const Ipp8u iv[16] = {
        0x00,0x01,0x02,0x03, 0x04,0x05,0x06,0x07,
        0x08,0x09,0x0A,0x0B, 0x0C,0x0D,0x0E,0x0F
    };

    ippsSMS4GetSize(&pSize);
    unsigned char buffer[pSize];
    pCtx = (IppsSMS4Spec *)buffer;

    ippsSMS4Init((const Ipp8u*)key, 16, pCtx, pSize);
    ippsSMS4EncryptECB(plaintext, ciphertext, length, pCtx);

    return SGX_SUCCESS;
}