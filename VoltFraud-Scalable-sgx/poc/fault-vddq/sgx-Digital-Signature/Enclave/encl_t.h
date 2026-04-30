#ifndef ENCL_T_H__
#define ENCL_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "tlibc/string.h"
#include "tlibc/stdio.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

sgx_status_t memory_access_ecall(void);
void fault_injection_ecall(const char* out_path);
void generate_file_ecall(const char* out_path);
int load_verify_msg_ecall(char* file_path);

sgx_status_t SGX_CDECL ocall_print_string(const char* str);
sgx_status_t SGX_CDECL ocall_record_string(const char* str);
sgx_status_t SGX_CDECL ocall_get_filesize(int* retval, const char* fname, long int* fsize);
sgx_status_t SGX_CDECL ocall_load_file(int* retval, const char* fname, long int fsize, unsigned char* data);
sgx_status_t SGX_CDECL ocall_write_file(int* retval, const char* fname, long int fsize, unsigned char* data);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
