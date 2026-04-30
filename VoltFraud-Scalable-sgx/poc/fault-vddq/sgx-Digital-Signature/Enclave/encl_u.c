#include "encl_u.h"
#include <errno.h>

typedef struct ms_memory_access_ecall_t {
	sgx_status_t ms_retval;
} ms_memory_access_ecall_t;

typedef struct ms_fault_injection_ecall_t {
	const char* ms_out_path;
	size_t ms_out_path_len;
} ms_fault_injection_ecall_t;

typedef struct ms_generate_file_ecall_t {
	const char* ms_out_path;
	size_t ms_out_path_len;
} ms_generate_file_ecall_t;

typedef struct ms_load_verify_msg_ecall_t {
	int ms_retval;
	char* ms_file_path;
	size_t ms_file_path_len;
} ms_load_verify_msg_ecall_t;

typedef struct ms_ocall_print_string_t {
	const char* ms_str;
} ms_ocall_print_string_t;

typedef struct ms_ocall_record_string_t {
	const char* ms_str;
} ms_ocall_record_string_t;

typedef struct ms_ocall_get_filesize_t {
	int ms_retval;
	const char* ms_fname;
	long int* ms_fsize;
} ms_ocall_get_filesize_t;

typedef struct ms_ocall_load_file_t {
	int ms_retval;
	const char* ms_fname;
	long int ms_fsize;
	unsigned char* ms_data;
} ms_ocall_load_file_t;

typedef struct ms_ocall_write_file_t {
	int ms_retval;
	const char* ms_fname;
	long int ms_fsize;
	unsigned char* ms_data;
} ms_ocall_write_file_t;

static sgx_status_t SGX_CDECL encl_ocall_print_string(void* pms)
{
	ms_ocall_print_string_t* ms = SGX_CAST(ms_ocall_print_string_t*, pms);
	ocall_print_string(ms->ms_str);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL encl_ocall_record_string(void* pms)
{
	ms_ocall_record_string_t* ms = SGX_CAST(ms_ocall_record_string_t*, pms);
	ocall_record_string(ms->ms_str);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL encl_ocall_get_filesize(void* pms)
{
	ms_ocall_get_filesize_t* ms = SGX_CAST(ms_ocall_get_filesize_t*, pms);
	ms->ms_retval = ocall_get_filesize(ms->ms_fname, ms->ms_fsize);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL encl_ocall_load_file(void* pms)
{
	ms_ocall_load_file_t* ms = SGX_CAST(ms_ocall_load_file_t*, pms);
	ms->ms_retval = ocall_load_file(ms->ms_fname, ms->ms_fsize, ms->ms_data);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL encl_ocall_write_file(void* pms)
{
	ms_ocall_write_file_t* ms = SGX_CAST(ms_ocall_write_file_t*, pms);
	ms->ms_retval = ocall_write_file(ms->ms_fname, ms->ms_fsize, ms->ms_data);

	return SGX_SUCCESS;
}

static const struct {
	size_t nr_ocall;
	void * table[5];
} ocall_table_encl = {
	5,
	{
		(void*)encl_ocall_print_string,
		(void*)encl_ocall_record_string,
		(void*)encl_ocall_get_filesize,
		(void*)encl_ocall_load_file,
		(void*)encl_ocall_write_file,
	}
};
sgx_status_t memory_access_ecall(sgx_enclave_id_t eid, sgx_status_t* retval)
{
	sgx_status_t status;
	ms_memory_access_ecall_t ms;
	status = sgx_ecall(eid, 0, &ocall_table_encl, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t fault_injection_ecall(sgx_enclave_id_t eid, const char* out_path)
{
	sgx_status_t status;
	ms_fault_injection_ecall_t ms;
	ms.ms_out_path = out_path;
	ms.ms_out_path_len = out_path ? strlen(out_path) + 1 : 0;
	status = sgx_ecall(eid, 1, &ocall_table_encl, &ms);
	return status;
}

sgx_status_t generate_file_ecall(sgx_enclave_id_t eid, const char* out_path)
{
	sgx_status_t status;
	ms_generate_file_ecall_t ms;
	ms.ms_out_path = out_path;
	ms.ms_out_path_len = out_path ? strlen(out_path) + 1 : 0;
	status = sgx_ecall(eid, 2, &ocall_table_encl, &ms);
	return status;
}

sgx_status_t load_verify_msg_ecall(sgx_enclave_id_t eid, int* retval, char* file_path)
{
	sgx_status_t status;
	ms_load_verify_msg_ecall_t ms;
	ms.ms_file_path = file_path;
	ms.ms_file_path_len = file_path ? strlen(file_path) + 1 : 0;
	status = sgx_ecall(eid, 3, &ocall_table_encl, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

