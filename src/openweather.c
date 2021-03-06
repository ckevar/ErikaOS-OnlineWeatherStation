/*
 * Created Apr 7, 2022
 *  - by ckevar
 */

#include "openweather.h"
#include "json_parser.h"

#include <string.h>

// tmp header
#include "lcd_log.h"

char OWAPI_get_weather(char *json, char **vals, unsigned short *vals_len) {
	char *JSON_KEYS[OWAPI_MEMBERS] = {OWAPI_FEELS_LIKE,\
									  OWAPI_TEMP,\
									  OWAPI_ICON,\
									  OWAPI_DESCRIPTION};

	unsigned short KEYS_LEN[OWAPI_MEMBERS] = {OWAPI_FEELS_LIKE_LEN,\
											  OWAPI_TEMP_LEN,\
											  OWAPI_ICON_LEN,\
											  OWAPI_DESCRIPTION_LEN};

	vals[0] = json_query_key_ValPtr(json, OWAPI_JSON_COD, OWAPI_JSON_COD_LEN);

	if(memcmp(OWAPI_JSON_200, vals[0], OWAPI_JSON_200_LEN) == 0) {

		json_query_mulKey_ValPtrLen(json, OWAPI_MEMBERS, JSON_KEYS,\
									KEYS_LEN, vals, vals_len);
		
		return 0;
	}
	return 1;
}