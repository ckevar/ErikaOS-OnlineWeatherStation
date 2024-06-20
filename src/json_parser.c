/*
 * Created Mar 7, 2022
 *  - by ckevar
 */
#include "json_parser.h"
#include <string.h>

// tmp headers
#include "lcd_log.h"

/*********************************************************************
 * This replies back the pointer in the json buffer where the value of
 * the key is stored. This is rudimentary, we're not checking parenthesis
 * or square brackets. Inspired by strtok
 *********************************************************************/
char *json_get_value_ptr(char *json, char *key, unsigned short key_len) {
	register char *c;
	register char *sholder;

goto_FUNC_json_get_value_ptr_FILE_json_parser:
	for (c = key; *json; json++) {
		if (*json == '"' && *(json + key_len + 1) == '"') {
			sholder = ++json;
		
			while((*json++ == *c++) && (*c != 0));

			if (*c != 0) {
				json = sholder + key_len + 1;
				goto goto_FUNC_json_get_value_ptr_FILE_json_parser;
			}

			return json + 2;

		}
	}

	return NULL;
}

/******************************************************************
 * It looks up many key at one pass across json.
 * In the array, the keys shall be in INVERTED order of appearance.
 * It replies back where the values of the keys in vals
 * it returns the number of missing fields
 ******************************************************************/
unsigned char json_query_mulKey_ValPtrLen(char *json, int16_t n,\
										char **key,  uint16_t *key_len,\
										char **val,  uint16_t *val_len) 
{
	register char *_json;
	register char *c;
	char *sholder; 
	_json = json;
	n--;

goto_FUNC_json_query_mulKey_ValPtrLen_FILE_json_parser:
	for (c = key[n]; *json; json++) {
		if ((*json == '"') && (*(json + key_len[n] + 1) == '"')) {
			sholder = ++json;	// skip '"'

			while ((*json++ == *c++) && (*c != 0));
			if (*c != 0) {
				json = sholder + key_len[n] + 1;
				goto goto_FUNC_json_query_mulKey_ValPtrLen_FILE_json_parser;
			}

			json += 2; // skips "":"
					
			// Grabs Value
			val[n] = json;
			for (;(*json != ',') && (*json != '}'); json++);

			val_len[n] = json - val[n];

			// Checks if all values were found
			if ((--n) > -1) 
				goto goto_FUNC_json_query_mulKey_ValPtrLen_FILE_json_parser;

			return 0;

		}
		// This is a safe in case the buffer is full and the iteration
		// keeps going.
		if(json - _json > 6000) {
			return n;
		}
	}
	return n;
}
