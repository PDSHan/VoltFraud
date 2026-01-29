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

sgx_status_t rsa_dec_ecall(sgx_enclave_id_t eid, uint8_t* retval, uint8_t result[256]);
sgx_status_t rsa_init_ecall(sgx_enclave_id_t eid, uint8_t* retval);
sgx_status_t rsa_clean_ecall(sgx_enclave_id_t eid, uint8_t* retval);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
