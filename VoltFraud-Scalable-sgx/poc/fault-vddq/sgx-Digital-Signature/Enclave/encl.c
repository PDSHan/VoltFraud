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
    
    int length = 4096*2;
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
        if(memcmp(&pattern, &data[iter], sizeof(cl64_t)) != 0){
            eprintf("[fault] idx=%d: ", iter);
            for (int j = 0; j < 64; j++) {
                eprintf("%02X ", data[iter].bytes[j]);
            }
            eprintf("\n");
        }
    }  

    return SGX_SUCCESS;
}

int get_filesize(char *modelname, long *f_size){
    int ret;
    if (ocall_get_filesize(&ret, modelname, f_size) != SGX_SUCCESS)
        return -1;
    return ret;
}

int load_file(char *modelname, long f_size, unsigned char *data){
    int ret;
    if (ocall_load_file(&ret, modelname, f_size, data) != SGX_SUCCESS)
        return -1;
    return ret;
}

int write_file(char *filename, long f_size, unsigned char *data){
    int ret;
    if (ocall_write_file(&ret, filename, f_size, data) != SGX_SUCCESS)
        return -1;
    return ret;
}

static void record(const char *fmt, ...)
{
    char buf[1000] = {'\0'};
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, 1000, fmt, ap);
    va_end(ap);
    ocall_record_string(buf);
}

IppsECCPState* newStd_256_ECP(void)
{
    int ctxSize = 0;

    ippsECCPGetSize(256, &ctxSize);

    IppsECCPState* pCtx = (IppsECCPState*)malloc(ctxSize);
    if (!pCtx) return NULL;

    ippsECCPInit(256, pCtx);
    ippsECCPSetStd(IppECCPStd256r1, pCtx);

    return pCtx;
}
 
IppsECCPPointState* newECP_256_Point(void)
{
    int ctxSize = 0;

    ippsECCPPointGetSize(256, &ctxSize);

    IppsECCPPointState* pPoint = (IppsECCPPointState*)malloc(ctxSize);
    if (!pPoint) return NULL;

    ippsECCPPointInit(256, pPoint);

    return pPoint;
}
 
IppsBigNumState* newBN(int len, const Ipp32u* pData)
{
    int ctxSize = 0;

    ippsBigNumGetSize(len, &ctxSize);

    IppsBigNumState* pBN = (IppsBigNumState*)malloc(ctxSize);
    if (!pBN) return NULL;

    ippsBigNumInit(len, pBN);

    if (pData)
        ippsSet_BN(IppsBigNumPOS, len, pData, pBN);

    return pBN;
}


IppsPRNGState* newPRNG(void)
{
    int ctxSize = 0;

    ippsPRNGGetSize(&ctxSize);

    IppsPRNGState* pCtx = (IppsPRNGState*)malloc(ctxSize);
    if (!pCtx) return NULL;

    ippsPRNGInit(160, pCtx);

    return pCtx;
}

void flush_array(void *addr, size_t size)
{
    char *p = (char*)addr;

    for (size_t i = 0; i < size; i += 64) {
        _mm_clflush(p + i);
    }

    _mm_mfence();
}

void generate_file_ecall(const char* out_path) {
    int msg_len = 4096 * 128;

    unsigned char *msg = (unsigned char*)malloc(msg_len);
    unsigned char *cipher = (unsigned char*)malloc(msg_len);
    unsigned char *out = (unsigned char*)malloc(msg_len + 32);

    for (int off = 0; off < msg_len; off += 64) {
        memset(msg + off, 0, 64);
        uint64_t v = 1000000ULL;        // some arbitrary non-zero value to make the hash non-trivial
        memcpy(msg + off + 56, &v, 8); 
    }

    // ===== AES-CTR =====
    Ipp8u key[16] = {
        0x2b, 0x7e, 0x15, 0x16,
        0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88,
        0x09, 0xcf, 0x4f, 0x3c
    };

    Ipp8u ctr[16] = {
        0xf0, 0xf1, 0xf2, 0xf3,
        0xf4, 0xf5, 0xf6, 0xf7,
        0xf8, 0xf9, 0xfa, 0xfb,
        0xfc, 0xfd, 0xfe, 0xff
    };

    IppsAESSpec *pAES = NULL;
    int ctxSize = 0;

    ippsAESGetSize(&ctxSize);
    pAES = (IppsAESSpec*)malloc(ctxSize);
    ippsAESInit(key, 16, pAES, ctxSize);

    IppStatus status = ippsAESEncryptCTR(
        msg,
        cipher,
        msg_len,
        pAES,
        ctr,
        128
    );

    if (status != ippStsNoErr) {
        record("AES failed: %d\n", status);
        return;
    }

    free(pAES);

    // ===== HMAC over ciphertext =====
    IppsHMACState* ctx;
    int hmacSize = 0;
    ippsHMAC_GetSize(&hmacSize);
    ctx = (IppsHMACState*)malloc(hmacSize);

    Ipp8u hkey[] = "secret";
    int keyLen = sizeof(hkey) - 1;

    Ipp8u mac[32];

    ippsHMAC_Init(hkey, keyLen, ctx, ippHashAlg_SHA256);
    ippsHMAC_Update(cipher, msg_len, ctx);
    ippsHMAC_Final(mac, 32, ctx);

    free(ctx);

    memcpy(out, cipher, msg_len);
    memcpy(out + msg_len, mac, 32);

    write_file(out_path, msg_len + 32, out);

    free(msg);
    free(cipher);
    free(out);
}


Ipp8u *ciphertext;
int len;
Ipp8u *decrypted;
int load_verify_msg_ecall(char *file_path){
    //load file
    int res = get_filesize(file_path, &len);
    if (res < 0)
    {
        eprintf("failed to read model file\n");
        return -1;
    }
    // eprintf("len = %d\n", len);


    // ciphertext = (Ipp8u*)malloc(len);
    size_t aligned_len = ((len + 63) / 64) * 64;
    if (posix_memalign((void**)&ciphertext, 64, aligned_len) != 0) {
        record("ciphertext is not 64-byte aligned\n");
    }
    decrypted = (Ipp8u*)malloc(len - 32 + 129); // -32 for hmac, +129 for signature hex

    int res1 = load_file(file_path, len, ciphertext);
    if (res1 < 0)
    {
        eprintf("failed to read model file\n");
        return -1;
    }

    //Verify
    IppsHMACState* ctx;
    Ipp8u key[] = "secret";
    int keyLen = sizeof(key) - 1;
    int ctxSize = 0;
    Ipp8u mac[32]; // SHA256 → 32 bytes
    ippsHMAC_GetSize(&ctxSize);
    ctx = (IppsHMACState*)malloc(ctxSize);
    ippsHMAC_Init(key, keyLen, ctx, ippHashAlg_SHA256);
    ippsHMAC_Update(ciphertext, len - 32, ctx);
    ippsHMAC_Final(mac, 32, ctx);

    if (memcmp(mac, ciphertext + len - 32, 32) != 0) {
        eprintf("HMAC verification failed!\n");
        for (int i = 0; i < 32; i++) {
            eprintf("%02X ", mac[i]);
        }
        eprintf("\n");
        return -1;
    }

    free(ctx);


    // flush_array(ciphertext, len);

    _mm_mfence();

    return 0;
}


void decrypt_msg(){
    Ipp8u key[16] = {
        0x2b, 0x7e, 0x15, 0x16,
        0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88,
        0x09, 0xcf, 0x4f, 0x3c
    };

    Ipp8u ctr[16] = {
        0xf0, 0xf1, 0xf2, 0xf3,
        0xf4, 0xf5, 0xf6, 0xf7,
        0xf8, 0xf9, 0xfa, 0xfb,
        0xfc, 0xfd, 0xfe, 0xff
    };

    IppsAESSpec *pAES = NULL;
    int ctxSize = 0;

    ippsAESGetSize(&ctxSize);
    pAES = (IppsAESSpec*)malloc(ctxSize);

    ippsAESInit(key, 16, pAES, ctxSize);

    IppStatus status = ippsAESEncryptCTR(
        ciphertext,
        decrypted,
        len - 32,
        pAES,
        ctr,
        128
    );
    if (status != ippStsNoErr) {
        eprintf("AES CTR encrypt failed: %d\n", status);
    }   

    free(pAES);

}

unsigned char correct_hash[64] = {
0xB9, 0x22, 0xF6, 0xBA, 0x1B, 0xFF, 0x6A, 0xB6, 
0x7E, 0x4C, 0x6E, 0xC8, 0x64, 0x24, 0x5C, 0x53,
0x5B, 0x33, 0xEE, 0xE0, 0xA5, 0xC3, 0x36, 0x47,
0x9F, 0x90, 0xA1, 0x81, 0x16, 0xE0, 0xA1, 0x89,
0x34, 0xCB, 0xF7, 0x5F, 0x2E, 0x1A, 0x1F, 0x7A,
0xE0, 0x28, 0x87, 0x56, 0x10, 0x6F, 0xFE, 0x8F,
0xFE, 0x9E, 0x4D, 0x50, 0x67, 0x89, 0xAD, 0x22,
0x2B, 0xE2, 0x95, 0xB4, 0x10, 0x03, 0x8C, 0x09
};
int mismatch = 0;
void SHA512(unsigned char hash_SHA512[64])
{
    decrypt_msg();

    //generate SHA512 hash of decrypted data
    int stateSize = 0;
    IppsHashState* pState;
    ippsHashGetSize(&stateSize);
    unsigned char buffer[stateSize];
    pState = (IppsHashState*)buffer;
    ippsHashInit(pState, ippHashAlg_SHA512);
    ippsHashUpdate((const Ipp8u*)decrypted, len - 32, pState);
    ippsHashFinal(hash_SHA512, pState);

    //check whether the hash matches the correct hash
    if(memcmp(hash_SHA512, correct_hash, 64)!=0){
        record("Fault Injection Detected!\n");
        for (int i = 0; i < 64; i++) {
            record("%02X ", hash_SHA512[i]);
        }
        record("\n");
        mismatch = 1;
    }
}

void fault_injection_ecall(const char* out_path)
{
    unsigned char hash_SHA512[64];
    SHA512(hash_SHA512);

    Sign(hash_SHA512, decrypted+len-32); // store signature hex in decrypted buffer after hash


    if(mismatch == 1){
        write_file(out_path, len-32+129, decrypted);
        mismatch = 0;
    }
    free(ciphertext);
    free(decrypted);
}


int Sign(unsigned char hash[64], char signature_hex[129])
{
    if (signature_hex == NULL) {
        eprintf("signature_hex is NULL\n");
        return -1;
    }

    // define standard 256-bit EC
    IppsECCPState* pECP = newStd_256_ECP();

    // order of secp256r1
    const Ipp32u secp256r1_r[] = {
        0xFC632551, 0xF3B9CAC2, 0xA7179E84, 0xBCE6FAAD,
        0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF
    };
    const int ordSize = sizeof(secp256r1_r) / sizeof(Ipp32u);
    IppsBigNumState* pECPorder = newBN(ordSize, secp256r1_r);

    IppsPRNGState* pRandGen = newPRNG();
    IppsBigNumState* pMsg = newBN(ordSize, NULL);
    IppsBigNumState* pHashTrunc = newBN(ordSize, NULL);

    // ECDSA-P256 uses up to 256 bits of the hash as message representative.
    if (ippsSetOctString_BN(hash, 32, pHashTrunc) != ippStsNoErr) {
        eprintf("Failed to set hash BN\n");
        return -1;
    }
    if (ippsMod_BN(pHashTrunc, pECPorder, pMsg) != ippStsNoErr) {
        eprintf("Failed to reduce hash modulo curve order\n");
        return -1;
    }

    // declare key containers
    const Ipp32u fixedPriv[] = {
        0x12345678, 0x9ABCDEF0, 0x13572468, 0x24681357,
        0x11111111, 0x22222222, 0x33333333, 0x44444444
    };
    IppsBigNumState* regPrivate = newBN(ordSize, fixedPriv);
    IppsECCPPointState* regPublic = newECP_256_Point();
    ippsECCPPublicKey(
        regPrivate,
        regPublic,
        pECP
    );

    IppsBigNumState* ephPrivate = newBN(ordSize, NULL);
    IppsECCPPointState* ephPublic = newECP_256_Point();

    // generate key pairs
    ippsECCPGenKeyPair(
        ephPrivate,
        ephPublic,
        pECP,
        ippsPRNGen,
        pRandGen
    );

    // signature
    ippsECCPSetKeyPair(
        ephPrivate,
        ephPublic,
        ippFalse,
        pECP
    );

    IppsBigNumState* signX = newBN(ordSize, NULL);
    IppsBigNumState* signY = newBN(ordSize, NULL);

    if (ippsECCPSignDSA(
        pMsg,
        regPrivate,
        signX,
        signY,
        pECP
    ) != ippStsNoErr) {
        eprintf("ippsECCPSignDSA failed\n");
        return -1;
    }

    unsigned char r_bytes[32];
    unsigned char s_bytes[32];
    if (ippsGetOctString_BN(r_bytes, sizeof(r_bytes), signX) != ippStsNoErr ||
        ippsGetOctString_BN(s_bytes, sizeof(s_bytes), signY) != ippStsNoErr) {
        eprintf("failed to export signature\n");
        return -1;
    }

    static const char hex_digits[] = "0123456789abcdef";
    for (int i = 0; i < 32; i++) {
        signature_hex[i * 2] = hex_digits[(r_bytes[i] >> 4) & 0x0F];
        signature_hex[i * 2 + 1] = hex_digits[r_bytes[i] & 0x0F];
        signature_hex[64 + i * 2] = hex_digits[(s_bytes[i] >> 4) & 0x0F];
        signature_hex[64 + i * 2 + 1] = hex_digits[s_bytes[i] & 0x0F];
    }
    signature_hex[128] = '\0';


    // eprintf("ECDSA signature generated.\n");
    return 0;
}



