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

static sgx_status_t SGX_CDECL sgx_memory_access_ecall(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_memory_access_ecall_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_memory_access_ecall_t* ms = SGX_CAST(ms_memory_access_ecall_t*, pms);
	ms_memory_access_ecall_t __in_ms;
	if (memcpy_s(&__in_ms, sizeof(ms_memory_access_ecall_t), ms, sizeof(ms_memory_access_ecall_t))) {
		return SGX_ERROR_UNEXPECTED;
	}
	sgx_status_t status = SGX_SUCCESS;
	sgx_status_t _in_retval;


	_in_retval = memory_access_ecall();
	if (memcpy_verw_s(&ms->ms_retval, sizeof(ms->ms_retval), &_in_retval, sizeof(_in_retval))) {
		status = SGX_ERROR_UNEXPECTED;
		goto err;
	}

err:
	return status;
}

static sgx_status_t SGX_CDECL sgx_fault_injection_ecall(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_fault_injection_ecall_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_fault_injection_ecall_t* ms = SGX_CAST(ms_fault_injection_ecall_t*, pms);
	ms_fault_injection_ecall_t __in_ms;
	if (memcpy_s(&__in_ms, sizeof(ms_fault_injection_ecall_t), ms, sizeof(ms_fault_injection_ecall_t))) {
		return SGX_ERROR_UNEXPECTED;
	}
	sgx_status_t status = SGX_SUCCESS;
	const char* _tmp_out_path = __in_ms.ms_out_path;
	size_t _len_out_path = __in_ms.ms_out_path_len ;
	char* _in_out_path = NULL;

	CHECK_UNIQUE_POINTER(_tmp_out_path, _len_out_path);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_out_path != NULL && _len_out_path != 0) {
		_in_out_path = (char*)malloc(_len_out_path);
		if (_in_out_path == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_out_path, _len_out_path, _tmp_out_path, _len_out_path)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

		_in_out_path[_len_out_path - 1] = '\0';
		if (_len_out_path != strlen(_in_out_path) + 1)
		{
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}
	}
	fault_injection_ecall((const char*)_in_out_path);

err:
	if (_in_out_path) free(_in_out_path);
	return status;
}

static sgx_status_t SGX_CDECL sgx_generate_file_ecall(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_generate_file_ecall_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_generate_file_ecall_t* ms = SGX_CAST(ms_generate_file_ecall_t*, pms);
	ms_generate_file_ecall_t __in_ms;
	if (memcpy_s(&__in_ms, sizeof(ms_generate_file_ecall_t), ms, sizeof(ms_generate_file_ecall_t))) {
		return SGX_ERROR_UNEXPECTED;
	}
	sgx_status_t status = SGX_SUCCESS;
	const char* _tmp_out_path = __in_ms.ms_out_path;
	size_t _len_out_path = __in_ms.ms_out_path_len ;
	char* _in_out_path = NULL;

	CHECK_UNIQUE_POINTER(_tmp_out_path, _len_out_path);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_out_path != NULL && _len_out_path != 0) {
		_in_out_path = (char*)malloc(_len_out_path);
		if (_in_out_path == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_out_path, _len_out_path, _tmp_out_path, _len_out_path)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

		_in_out_path[_len_out_path - 1] = '\0';
		if (_len_out_path != strlen(_in_out_path) + 1)
		{
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}
	}
	generate_file_ecall((const char*)_in_out_path);

err:
	if (_in_out_path) free(_in_out_path);
	return status;
}

static sgx_status_t SGX_CDECL sgx_load_verify_msg_ecall(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_load_verify_msg_ecall_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_load_verify_msg_ecall_t* ms = SGX_CAST(ms_load_verify_msg_ecall_t*, pms);
	ms_load_verify_msg_ecall_t __in_ms;
	if (memcpy_s(&__in_ms, sizeof(ms_load_verify_msg_ecall_t), ms, sizeof(ms_load_verify_msg_ecall_t))) {
		return SGX_ERROR_UNEXPECTED;
	}
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_file_path = __in_ms.ms_file_path;
	size_t _len_file_path = __in_ms.ms_file_path_len ;
	char* _in_file_path = NULL;
	int _in_retval;

	CHECK_UNIQUE_POINTER(_tmp_file_path, _len_file_path);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_file_path != NULL && _len_file_path != 0) {
		_in_file_path = (char*)malloc(_len_file_path);
		if (_in_file_path == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_file_path, _len_file_path, _tmp_file_path, _len_file_path)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

		_in_file_path[_len_file_path - 1] = '\0';
		if (_len_file_path != strlen(_in_file_path) + 1)
		{
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}
	}
	_in_retval = load_verify_msg_ecall(_in_file_path);
	if (memcpy_verw_s(&ms->ms_retval, sizeof(ms->ms_retval), &_in_retval, sizeof(_in_retval))) {
		status = SGX_ERROR_UNEXPECTED;
		goto err;
	}

err:
	if (_in_file_path) free(_in_file_path);
	return status;
}

SGX_EXTERNC const struct {
	size_t nr_ecall;
	struct {void* ecall_addr; uint8_t is_priv; uint8_t is_switchless;} ecall_table[4];
} g_ecall_table = {
	4,
	{
		{(void*)(uintptr_t)sgx_memory_access_ecall, 0, 0},
		{(void*)(uintptr_t)sgx_fault_injection_ecall, 0, 0},
		{(void*)(uintptr_t)sgx_generate_file_ecall, 0, 0},
		{(void*)(uintptr_t)sgx_load_verify_msg_ecall, 0, 0},
	}
};

SGX_EXTERNC const struct {
	size_t nr_ocall;
	uint8_t entry_table[5][4];
} g_dyn_entry_table = {
	5,
	{
		{0, 0, 0, 0, },
		{0, 0, 0, 0, },
		{0, 0, 0, 0, },
		{0, 0, 0, 0, },
		{0, 0, 0, 0, },
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

sgx_status_t SGX_CDECL ocall_record_string(const char* str)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_str = str ? strlen(str) + 1 : 0;

	ms_ocall_record_string_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_record_string_t);
	void *__tmp = NULL;


	CHECK_ENCLAVE_POINTER(str, _len_str);

	if (ADD_ASSIGN_OVERFLOW(ocalloc_size, (str != NULL) ? _len_str : 0))
		return SGX_ERROR_INVALID_PARAMETER;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_record_string_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_record_string_t));
	ocalloc_size -= sizeof(ms_ocall_record_string_t);

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

	status = sgx_ocall(1, ms);

	if (status == SGX_SUCCESS) {
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_get_filesize(int* retval, const char* fname, long int* fsize)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_fname = fname ? strlen(fname) + 1 : 0;
	size_t _len_fsize = sizeof(long int);

	ms_ocall_get_filesize_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_get_filesize_t);
	void *__tmp = NULL;

	void *__tmp_fsize = NULL;

	CHECK_ENCLAVE_POINTER(fname, _len_fname);
	CHECK_ENCLAVE_POINTER(fsize, _len_fsize);

	if (ADD_ASSIGN_OVERFLOW(ocalloc_size, (fname != NULL) ? _len_fname : 0))
		return SGX_ERROR_INVALID_PARAMETER;
	if (ADD_ASSIGN_OVERFLOW(ocalloc_size, (fsize != NULL) ? _len_fsize : 0))
		return SGX_ERROR_INVALID_PARAMETER;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_get_filesize_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_get_filesize_t));
	ocalloc_size -= sizeof(ms_ocall_get_filesize_t);

	if (fname != NULL) {
		if (memcpy_verw_s(&ms->ms_fname, sizeof(const char*), &__tmp, sizeof(const char*))) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		if (_len_fname % sizeof(*fname) != 0) {
			sgx_ocfree();
			return SGX_ERROR_INVALID_PARAMETER;
		}
		if (memcpy_verw_s(__tmp, ocalloc_size, fname, _len_fname)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_fname);
		ocalloc_size -= _len_fname;
	} else {
		ms->ms_fname = NULL;
	}

	if (fsize != NULL) {
		if (memcpy_verw_s(&ms->ms_fsize, sizeof(long int*), &__tmp, sizeof(long int*))) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp_fsize = __tmp;
		if (_len_fsize % sizeof(*fsize) != 0) {
			sgx_ocfree();
			return SGX_ERROR_INVALID_PARAMETER;
		}
		memset_verw(__tmp_fsize, 0, _len_fsize);
		__tmp = (void *)((size_t)__tmp + _len_fsize);
		ocalloc_size -= _len_fsize;
	} else {
		ms->ms_fsize = NULL;
	}

	status = sgx_ocall(2, ms);

	if (status == SGX_SUCCESS) {
		if (retval) {
			if (memcpy_s((void*)retval, sizeof(*retval), &ms->ms_retval, sizeof(ms->ms_retval))) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
		if (fsize) {
			if (memcpy_s((void*)fsize, _len_fsize, __tmp_fsize, _len_fsize)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_load_file(int* retval, const char* fname, long int fsize, unsigned char* data)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_fname = fname ? strlen(fname) + 1 : 0;
	size_t _len_data = fsize;

	ms_ocall_load_file_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_load_file_t);
	void *__tmp = NULL;

	void *__tmp_data = NULL;

	CHECK_ENCLAVE_POINTER(fname, _len_fname);
	CHECK_ENCLAVE_POINTER(data, _len_data);

	if (ADD_ASSIGN_OVERFLOW(ocalloc_size, (fname != NULL) ? _len_fname : 0))
		return SGX_ERROR_INVALID_PARAMETER;
	if (ADD_ASSIGN_OVERFLOW(ocalloc_size, (data != NULL) ? _len_data : 0))
		return SGX_ERROR_INVALID_PARAMETER;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_load_file_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_load_file_t));
	ocalloc_size -= sizeof(ms_ocall_load_file_t);

	if (fname != NULL) {
		if (memcpy_verw_s(&ms->ms_fname, sizeof(const char*), &__tmp, sizeof(const char*))) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		if (_len_fname % sizeof(*fname) != 0) {
			sgx_ocfree();
			return SGX_ERROR_INVALID_PARAMETER;
		}
		if (memcpy_verw_s(__tmp, ocalloc_size, fname, _len_fname)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_fname);
		ocalloc_size -= _len_fname;
	} else {
		ms->ms_fname = NULL;
	}

	if (memcpy_verw_s(&ms->ms_fsize, sizeof(ms->ms_fsize), &fsize, sizeof(fsize))) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}

	if (data != NULL) {
		if (memcpy_verw_s(&ms->ms_data, sizeof(unsigned char*), &__tmp, sizeof(unsigned char*))) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp_data = __tmp;
		if (_len_data % sizeof(*data) != 0) {
			sgx_ocfree();
			return SGX_ERROR_INVALID_PARAMETER;
		}
		memset_verw(__tmp_data, 0, _len_data);
		__tmp = (void *)((size_t)__tmp + _len_data);
		ocalloc_size -= _len_data;
	} else {
		ms->ms_data = NULL;
	}

	status = sgx_ocall(3, ms);

	if (status == SGX_SUCCESS) {
		if (retval) {
			if (memcpy_s((void*)retval, sizeof(*retval), &ms->ms_retval, sizeof(ms->ms_retval))) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
		if (data) {
			if (memcpy_s((void*)data, _len_data, __tmp_data, _len_data)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_write_file(int* retval, const char* fname, long int fsize, unsigned char* data)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_fname = fname ? strlen(fname) + 1 : 0;
	size_t _len_data = fsize;

	ms_ocall_write_file_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_write_file_t);
	void *__tmp = NULL;


	CHECK_ENCLAVE_POINTER(fname, _len_fname);
	CHECK_ENCLAVE_POINTER(data, _len_data);

	if (ADD_ASSIGN_OVERFLOW(ocalloc_size, (fname != NULL) ? _len_fname : 0))
		return SGX_ERROR_INVALID_PARAMETER;
	if (ADD_ASSIGN_OVERFLOW(ocalloc_size, (data != NULL) ? _len_data : 0))
		return SGX_ERROR_INVALID_PARAMETER;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_write_file_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_write_file_t));
	ocalloc_size -= sizeof(ms_ocall_write_file_t);

	if (fname != NULL) {
		if (memcpy_verw_s(&ms->ms_fname, sizeof(const char*), &__tmp, sizeof(const char*))) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		if (_len_fname % sizeof(*fname) != 0) {
			sgx_ocfree();
			return SGX_ERROR_INVALID_PARAMETER;
		}
		if (memcpy_verw_s(__tmp, ocalloc_size, fname, _len_fname)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_fname);
		ocalloc_size -= _len_fname;
	} else {
		ms->ms_fname = NULL;
	}

	if (memcpy_verw_s(&ms->ms_fsize, sizeof(ms->ms_fsize), &fsize, sizeof(fsize))) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}

	if (data != NULL) {
		if (memcpy_verw_s(&ms->ms_data, sizeof(unsigned char*), &__tmp, sizeof(unsigned char*))) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		if (_len_data % sizeof(*data) != 0) {
			sgx_ocfree();
			return SGX_ERROR_INVALID_PARAMETER;
		}
		if (memcpy_verw_s(__tmp, ocalloc_size, data, _len_data)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_data);
		ocalloc_size -= _len_data;
	} else {
		ms->ms_data = NULL;
	}

	status = sgx_ocall(4, ms);

	if (status == SGX_SUCCESS) {
		if (retval) {
			if (memcpy_s((void*)retval, sizeof(*retval), &ms->ms_retval, sizeof(ms->ms_retval))) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
	}
	sgx_ocfree();
	return status;
}

