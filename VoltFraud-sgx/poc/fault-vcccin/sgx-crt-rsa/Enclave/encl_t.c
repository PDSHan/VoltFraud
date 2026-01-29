#include "encl_t.h"

#include "sgx_trts.h" /* for sgx_ocalloc, sgx_is_outside_enclave */
#include "sgx_lfence.h" /* for sgx_lfence */

#include <errno.h>
#include <mbusafecrt.h> /* for memcpy_s etc */
#include <stdlib.h> /* for malloc/free etc */

#define CHECK_REF_POINTER(ptr, siz) do {	\
	if (!(ptr) || ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define CHECK_UNIQUE_POINTER(ptr, siz) do {	\
	if ((ptr) && ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define CHECK_ENCLAVE_POINTER(ptr, siz) do {	\
	if ((ptr) && ! sgx_is_within_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define ADD_ASSIGN_OVERFLOW(a, b) (	\
	((a) += (b)) < (b)	\
)


typedef struct ms_rsa_dec_ecall_t {
	uint8_t ms_retval;
	uint8_t* ms_result;
} ms_rsa_dec_ecall_t;

typedef struct ms_rsa_init_ecall_t {
	uint8_t ms_retval;
} ms_rsa_init_ecall_t;

typedef struct ms_rsa_clean_ecall_t {
	uint8_t ms_retval;
} ms_rsa_clean_ecall_t;

typedef struct ms_ocall_print_string_t {
	const char* ms_str;
} ms_ocall_print_string_t;

static sgx_status_t SGX_CDECL sgx_rsa_dec_ecall(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_rsa_dec_ecall_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_rsa_dec_ecall_t* ms = SGX_CAST(ms_rsa_dec_ecall_t*, pms);
	ms_rsa_dec_ecall_t __in_ms;
	if (memcpy_s(&__in_ms, sizeof(ms_rsa_dec_ecall_t), ms, sizeof(ms_rsa_dec_ecall_t))) {
		return SGX_ERROR_UNEXPECTED;
	}
	sgx_status_t status = SGX_SUCCESS;
	uint8_t* _tmp_result = __in_ms.ms_result;
	size_t _len_result = 256 * sizeof(uint8_t);
	uint8_t* _in_result = NULL;
	uint8_t _in_retval;

	CHECK_UNIQUE_POINTER(_tmp_result, _len_result);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_result != NULL && _len_result != 0) {
		if ( _len_result % sizeof(*_tmp_result) != 0)
		{
			status = SGX_ERROR_INVALID_PARAMETER;
			goto err;
		}
		if ((_in_result = (uint8_t*)malloc(_len_result)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_result, 0, _len_result);
	}
	_in_retval = rsa_dec_ecall(_in_result);
	if (memcpy_verw_s(&ms->ms_retval, sizeof(ms->ms_retval), &_in_retval, sizeof(_in_retval))) {
		status = SGX_ERROR_UNEXPECTED;
		goto err;
	}
	if (_in_result) {
		if (memcpy_verw_s(_tmp_result, _len_result, _in_result, _len_result)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}
	}

err:
	if (_in_result) free(_in_result);
	return status;
}

static sgx_status_t SGX_CDECL sgx_rsa_init_ecall(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_rsa_init_ecall_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_rsa_init_ecall_t* ms = SGX_CAST(ms_rsa_init_ecall_t*, pms);
	ms_rsa_init_ecall_t __in_ms;
	if (memcpy_s(&__in_ms, sizeof(ms_rsa_init_ecall_t), ms, sizeof(ms_rsa_init_ecall_t))) {
		return SGX_ERROR_UNEXPECTED;
	}
	sgx_status_t status = SGX_SUCCESS;
	uint8_t _in_retval;


	_in_retval = rsa_init_ecall();
	if (memcpy_verw_s(&ms->ms_retval, sizeof(ms->ms_retval), &_in_retval, sizeof(_in_retval))) {
		status = SGX_ERROR_UNEXPECTED;
		goto err;
	}

err:
	return status;
}

static sgx_status_t SGX_CDECL sgx_rsa_clean_ecall(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_rsa_clean_ecall_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_rsa_clean_ecall_t* ms = SGX_CAST(ms_rsa_clean_ecall_t*, pms);
	ms_rsa_clean_ecall_t __in_ms;
	if (memcpy_s(&__in_ms, sizeof(ms_rsa_clean_ecall_t), ms, sizeof(ms_rsa_clean_ecall_t))) {
		return SGX_ERROR_UNEXPECTED;
	}
	sgx_status_t status = SGX_SUCCESS;
	uint8_t _in_retval;


	_in_retval = rsa_clean_ecall();
	if (memcpy_verw_s(&ms->ms_retval, sizeof(ms->ms_retval), &_in_retval, sizeof(_in_retval))) {
		status = SGX_ERROR_UNEXPECTED;
		goto err;
	}

err:
	return status;
}

SGX_EXTERNC const struct {
	size_t nr_ecall;
	struct {void* ecall_addr; uint8_t is_priv; uint8_t is_switchless;} ecall_table[3];
} g_ecall_table = {
	3,
	{
		{(void*)(uintptr_t)sgx_rsa_dec_ecall, 0, 0},
		{(void*)(uintptr_t)sgx_rsa_init_ecall, 0, 0},
		{(void*)(uintptr_t)sgx_rsa_clean_ecall, 0, 0},
	}
};

SGX_EXTERNC const struct {
	size_t nr_ocall;
	uint8_t entry_table[1][3];
} g_dyn_entry_table = {
	1,
	{
		{0, 0, 0, },
	}
};


sgx_status_t SGX_CDECL ocall_print_string(const char* str)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_str = str ? strlen(str) + 1 : 0;

	ms_ocall_print_string_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_print_string_t);
	void *__tmp = NULL;


	CHECK_ENCLAVE_POINTER(str, _len_str);

	if (ADD_ASSIGN_OVERFLOW(ocalloc_size, (str != NULL) ? _len_str : 0))
		return SGX_ERROR_INVALID_PARAMETER;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_print_string_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_print_string_t));
	ocalloc_size -= sizeof(ms_ocall_print_string_t);

	if (str != NULL) {
		if (memcpy_verw_s(&ms->ms_str, sizeof(const char*), &__tmp, sizeof(const char*))) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		if (_len_str % sizeof(*str) != 0) {
			sgx_ocfree();
			return SGX_ERROR_INVALID_PARAMETER;
		}
		if (memcpy_verw_s(__tmp, ocalloc_size, str, _len_str)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_str);
		ocalloc_size -= _len_str;
	} else {
		ms->ms_str = NULL;
	}

	status = sgx_ocall(0, ms);

	if (status == SGX_SUCCESS) {
	}
	sgx_ocfree();
	return status;
}

