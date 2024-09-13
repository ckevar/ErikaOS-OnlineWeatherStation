#include <stdint.h>

#include "CUnit/Automated.h"
#include "CUnit/Basic.h"
#include "LUT_test.h"

#define TEST_FILE "/tmp/test.txt"

static FILE *tmp_file = NULL;

int init_suite(void) {
	if(NULL == (tmp_file = fopen(TEST_FILE, "w+")))
		return -1;
	return 0;
}

int clean_suite(void) {
	if(0 != fclose(tmp_file)) 
		return -1;
	
	tmp_file = NULL;
	return 0;
}


int main(void) {
	CU_pSuite pSuite = NULL;

	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	pSuite = CU_add_suite("fsm client", init_suite, clean_suite);

	if(NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if ((NULL == CU_add_test(pSuite, "LUT_OK_client test", LUT_OK_client_test)) ||
		(NULL == CU_add_test(pSuite, "LUT_OK_initial_setup test", LUT_OK_initial_setup_test)) ||
		(NULL == CU_add_test(pSuite, "LUT_timeout_initial_setup test", LUT_timeout_initial_setup_test)) ||
		(NULL == CU_add_test(pSuite, "LUT_on_err_initial_setup test", LUT_on_err_test)) || 
		(NULL == CU_add_test(pSuite, "LUT_OK_netstat test", LUT_OK_netstat_test)) ||
		(NULL == CU_add_test(pSuite, "LUT_OK_server test", LUT_OK_server_test))
			) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	CU_set_error_action(CUEA_IGNORE);
	CU_set_output_filename("LUT_results");
	CU_list_tests_to_file();
	CU_automated_run_tests();

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	
	CU_cleanup_registry();
	return CU_get_error();
}
