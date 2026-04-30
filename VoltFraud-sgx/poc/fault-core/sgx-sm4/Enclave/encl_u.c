#include "encl_u.h"
#include <errno.h>

typedef struct ms_sm4_ecall_t {
	sgx_status_t ms_retval;
	unsigned char* ms_plaintext;
	unsigned char* ms_ciphertext;
	int ms_length;
} ms_sm4_ecall_t;

typedef struct ms_ocall_print_string_t {
	const char* ms_str;
} ms_ocall_print_string_t;

static sgx_status_t SGX_CDECL encl_ocall_print_string(void* pms)
{
	ms_ocall_print_string_t* ms = SGX_CAST(ms_ocall_print_string_t*, pms);
	ocall_print_string(ms->ms_str);

	return SGX_SUCCESS;
}

static const struct {
	size_t nr_ocall;
	void * table[1];
} ocall_table_encl = {
	1,
	{
		(void*)encl_ocall_print_string,
	}
};
sgx_status_t sm4_ecall(sgx_enclave_id_t eid, sgx_status_t* retval, unsigned char* plaintext, unsigned char* ciphertext, int length)
{
	sgx_status_t status;
	ms_sm4_ecall_t ms;
	ms.ms_plaintext = plaintext;
	ms.ms_ciphertext = ciphertext;
	ms.ms_length = length;
	status = sgx_ecall(eid, 0, &ocall_table_encl, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

