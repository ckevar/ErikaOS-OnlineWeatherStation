/*
 * Created Apr 7, 2022
 *  - by ckevar
 */
#include "ipapi_json.h"
#include "json_parser.h"

#include <string.h>

char IPAPI_get_location_PtrLen(char *json, char **vals, unsigned short *vals_len) {
	char *IPAPI_KEYS[IPAPI_JSON_MEMBERS] = {IPAPI_JSON_LON,\
											IPAPI_JSON_LAT,\
											IPAPI_JSON_CITY};
	unsigned short IPAPI_KEYS_LEN[IPAPI_JSON_MEMBERS] = {IPAPI_JSON_LON_LEN,\
														 IPAPI_JSON_LAT_LEN,\
														 IPAPI_JSON_CITY_LEN};

	vals[0] = json_get_value_ptr(json, IPAPI_JSON_STATUS, IPAPI_JSON_STATUS_LEN);
	if (memcmp(IPAPI_JSON_SUCCESS, vals[0], IPAPI_JSON_SUCCESS_LEN) == 0) {

		json_query_mulKey_ValPtrLen(json, IPAPI_JSON_MEMBERS, IPAPI_KEYS,\
									IPAPI_KEYS_LEN, vals, vals_len);

		return 0;
	}
	return 1;
}
