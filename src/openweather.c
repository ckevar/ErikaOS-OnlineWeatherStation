/*
 * Created Apr 7, 2022
 *  - by ckevar
 */

#include "openweather.h"
#include "json_parser.h"

#include <string.h>

char OWAPI_get_weather(char *json, char **vals, unsigned short *vals_len) {
	char *JSON_KEYS[OWAPI_PARAMS_COUNT] = {OWAPI_TIMEZONE, OWAPI_TIME, 
        OWAPI_FEELS_LIKE, OWAPI_TEMP, OWAPI_ICON, OWAPI_DESCRIPTION};

	unsigned short KEYS_LEN[OWAPI_PARAMS_COUNT] = {OWAPI_TIMEZONE_LEN,
        OWAPI_TIME_LEN, OWAPI_FEELS_LIKE_LEN, OWAPI_TEMP_LEN, OWAPI_ICON_LEN, 
        OWAPI_DESCRIPTION_LEN};

	vals[0] = json_query_key_ValPtr(json, OWAPI_JSON_COD, OWAPI_JSON_COD_LEN);

	if(memcmp(OWAPI_JSON_200, vals[0], OWAPI_JSON_200_LEN))
		return 1;
	
	json_query_mulKey_ValPtrLen(json, OWAPI_PARAMS_COUNT, JSON_KEYS,\
									KEYS_LEN, vals, vals_len);

	if(*(vals[iOWAPI_FEELS_LIKE]) < '0' || *(vals[iOWAPI_FEELS_LIKE]) > '9')
		vals[iOWAPI_FEELS_LIKE] = "0\0";

	return 0;
}
