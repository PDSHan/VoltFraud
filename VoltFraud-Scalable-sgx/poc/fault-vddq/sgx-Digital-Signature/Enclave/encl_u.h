#ifndef ENCL_U_H__
#define ENCL_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_status_t etc. */


#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

#ifndef OCALL_PRINT_STRING_DEFINED__
#define OCALL_PRINT_STRING_DEFINED__
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_print_string, (const char* str));
#endif
#ifndef OCALL_RECORD_STRING_DEFINED__
#define OCALL_RECORD_STRING_DEFINED__
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_record_string, (const char* str));
#endif
#ifndef OCALL_GET_FILESIZE_DEFINED__
#define OCALL_GET_FILESIZE_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_get_filesize, (const char* fname, long int* fsize));
#endif
#ifndef OCALL_LOAD_FILE_DEFINED__
#define OCALL_LOAD_FILE_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_load_file, (const char* fname, long int fsize, unsigned char* data));
#endif
#ifndef OCALL_WRITE_FILE_DEFINED__
#define OCALL_WRITE_FILE_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_write_file, (const char* fname, long int fsize, unsigned char* data));
#endif

sgx_status_t memory_access_ecall(sgx_enclave_id_t eid, sgx_status_t* retval);
sgx_status_t fault_injection_ecall(sgx_enclave_id_t eid, const char* out_path);
sgx_status_t generate_file_ecall(sgx_enclave_id_t eid, const char* out_path);
sgx_status_t load_verify_msg_ecall(sgx_enclave_id_t eid, int* retval, char* file_path);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
