#include "CUnit/Basic.h"

#include "http.h"

#define SWAP_PTRS_IN_PTRS_ARRAY(array, i, j, tmp)	tmp = array[i]; \
													array[i] = array[j]; \
													array[j] = tmp

/*
 * UNIT:
 * This has been used to extract the HTTP methdod for both server and
 * Client:
 *	
 *	esp8266_driver.c
 *	--> static unsigned char esp8266_http_get_method
 *
 * ******************************************************************/
#define HTTP_Method_hash(http) (*http ^ *(http + 3))


void HTTP_Method_hash_ASSERT(enum HTTPMethods method, char **str_methods) {
	CU_ASSERT(method == HTTP_Method_hash(str_methods[0]));
	CU_ASSERT(method != HTTP_Method_hash(str_methods[1]));
	CU_ASSERT(method != HTTP_Method_hash(str_methods[2]));
}

void HTTP_Method_hash_test(void) {
	char *methods_supported[] = {"GET ", "POST", "HTTP/1.1"};
	char *tmp;

	HTTP_Method_hash_ASSERT(HTTP_Method_GET, methods_supported);
	
	SWAP_PTRS_IN_PTRS_ARRAY(methods_supported, 0, 1, tmp);
	HTTP_Method_hash_ASSERT(HTTP_Method_POST, methods_supported);

	SWAP_PTRS_IN_PTRS_ARRAY(methods_supported, 0, 2, tmp);
	HTTP_Method_hash_ASSERT(HTTP_RESPONSE, methods_supported);
}

/*
 * UNIT:
 * This has been used to extract the HTTP status code for both Server
 * and Client:
 *	
 *	esp8266_driver.c
 *	--> static void http_get_code
 *
 * ******************************************************************/
#define HTTP_Status_Code(http)	((*http << 8) | \
								((http[1] & 0x0F) << 4) | \
								(http[2] & 0x0F))

void HTTP_Status_Code_ASSERT(enum HTTPStatusCode code, char **str_codes) {
	CU_ASSERT(code == HTTP_Status_Code(str_codes[0]));
	CU_ASSERT(code != HTTP_Status_Code(str_codes[1]));
	CU_ASSERT(code != HTTP_Status_Code(str_codes[2]));
	CU_ASSERT(code != HTTP_Status_Code(str_codes[3]));
	CU_ASSERT(code != HTTP_Status_Code(str_codes[4]));
	CU_ASSERT(code != HTTP_Status_Code(str_codes[5]));
}


void HTTP_Status_Code_test(void) {
	char *codes[] = {"200", "204", "401", "500", "520", "522"};
	char *tmp;
	HTTP_Status_Code_ASSERT(HTTP_200, codes);

	SWAP_PTRS_IN_PTRS_ARRAY(codes, 0, 1, tmp);
	HTTP_Status_Code_ASSERT(HTTP_204, codes);

	SWAP_PTRS_IN_PTRS_ARRAY(codes, 0, 2, tmp);
	HTTP_Status_Code_ASSERT(HTTP_401, codes);

	SWAP_PTRS_IN_PTRS_ARRAY(codes, 0, 3, tmp);
	HTTP_Status_Code_ASSERT(HTTP_500, codes);

	SWAP_PTRS_IN_PTRS_ARRAY(codes, 0, 4, tmp);
	HTTP_Status_Code_ASSERT(HTTP_520, codes);

	SWAP_PTRS_IN_PTRS_ARRAY(codes, 0, 5, tmp);
	HTTP_Status_Code_ASSERT(HTTP_522, codes);
}
