#include "CUnit/Automated.h"
#include "CUnit/Basic.h"

#include "esp8266_driver_test.h"

#define TEST_FILE	"/tmp/test"
static FILE *tmp_file_poll = NULL;
static FILE *tmp_file_html = NULL;

int init_suite_poll(void) {
	if(NULL == (tmp_file_poll = fopen(TEST_FILE "_poll.txt", "w+"))) 
		return -1;
	return 0;
}

int clean_suite_poll(void) {
	if(0 != fclose(tmp_file_poll))
		return -1;

	tmp_file_poll = NULL;
	return 0;
}

int init_suite_html(void) {
	if(NULL == (tmp_file_html = fopen(TEST_FILE "_html.txt", "w+")))
		return -1;
	return 0;
}

int clean_suite_html(void) {
	if(0 != fclose(tmp_file_html))
		return -1;

	tmp_file_html = NULL;
	return 0;
}

int main(void) {
	CU_pSuite pSuite_html = NULL;
	CU_pSuite pSuite_poll = NULL;

	if (CUE_SUCCESS != CU_initialize_registry()) 
		return CU_get_error();


	pSuite_html = CU_add_suite("html modules on es8266_driver", init_suite_html, clean_suite_html);
	if (NULL == pSuite_html) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	pSuite_poll = CU_add_suite("poll module on esp8266_driver", init_suite_poll, clean_suite_poll);
	if(NULL == pSuite_poll) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if ((NULL == CU_add_test(pSuite_html, "HTTP Method hash", HTTP_Method_hash_test)) ||
		(NULL == CU_add_test(pSuite_html, "HTTP Status code hash", HTTP_Status_Code_test)) ||
		(NULL == CU_add_test(pSuite_poll, "ESP8266 poll", ESP8266_driver_poll_test))
		) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_set_error_action(CUEA_IGNORE);
	CU_set_output_filename("esp8266_driver_results");
	CU_list_tests_to_file();
	CU_automated_run_tests();

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();
	return CU_get_error();
}


