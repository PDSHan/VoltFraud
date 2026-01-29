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

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "string.h"
#include "stdio.h"
#include "sgx_trts.h"
#include "sgx_tcrypto.h"
#include "encl_t.h"	// for ocall
#include <ipp/ippcp.h>
#include <time.h>

#define RSA_LEN 256

#define MAX(a,b) (((a)>(b))?(a):(b))

static void eprintf(const char *fmt, ...)
{
    char buf[1000] = {'\0'};
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, 1000, fmt, ap);
    va_end(ap);
    ocall_print_string(buf);
}

void check_ipp_features() {
    Ipp64u features = ippcpGetEnabledCpuFeatures();

    if (features & ippCPUID_SSE2) eprintf("SSE2 supported\n");
    if (features & ippCPUID_SSE3) eprintf("SSE3 supported\n");
    if (features & ippCPUID_SSSE3) eprintf("SSSE3 supported\n");
    if (features & ippCPUID_SSE41) eprintf("SSE4.1 supported\n");
    if (features & ippCPUID_SSE42) eprintf("SSE4.2 supported\n");
    if (features & ippCPUID_AVX) eprintf("AVX supported\n");
    if (features & ippCPUID_AVX2) eprintf("AVX2 supported\n");
}


sgx_status_t SHA512_ecall(unsigned char fault_hash[65])
{
    unsigned char diff = 0;
    unsigned char hash[64];
    unsigned char msg[10*1024*1024];
    int stateSize = 0;
    unsigned char correct_hash[64] = {
        0xf4, 0x9f, 0x7b, 0x19, 0xd4, 0x03, 0x73, 0x0e, 0x03, 0x2b, 0x6f, 0x07, 0xa1, 0x7b, 0xb3, 0x82, 0x4c, 0xa5, 0xbb, 0x43, 0xb2, 0x3f, 0xe9, 0x2a, 0x77, 0x8d, 0xfc, 0x1f, 0x7a, 0x50, 0x51, 0x78, 0x43, 0x61, 0xbb, 0x13, 0x81, 0x9e, 0x3b, 0xd5, 0x76, 0x24, 0x1f, 0x1b, 0xdd, 0xce, 0x31, 0x92, 0x33, 0x50, 0x61, 0xe5, 0xcb, 0xd6, 0x09, 0x76, 0x46, 0x1a, 0xe9, 0x56, 0xe8, 0x04, 0xc2, 0x9b 
    };

    const char *pattern = "abcdefabcdefabcdefabcdefabcdefabcdef";
    size_t pattern_len = strlen(pattern);


    for (size_t i = 0; i < sizeof(msg); i++) {
        msg[i] = pattern[i % pattern_len];
    }

    volatile uint64_t sink;
    for (uint64_t i = 0; i < 0xFFFFFF; i++) {
        sink += i;
    }





    IppsHashState* pState;
    ippsHashGetSize(&stateSize);
    unsigned char buffer[stateSize];
    pState = (IppsHashState*)buffer;
    ippsHashInit(pState, ippHashAlg_SHA512);
    ippsHashUpdate((const Ipp8u*)msg, sizeof(msg), pState);
    ippsHashFinal(hash, pState);


    if(memcmp(hash, correct_hash, 64)!=0){
        fault_hash[0]=1;
        memcpy(fault_hash+1, hash, 64);
    }



    return SGX_SUCCESS;
}
