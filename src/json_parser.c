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
 * the key is stored.
 *********************************************************************/
char *json_get_value_ptr(char *json, char *key, unsigned short key_len) {
	while (*json) {
		// Getting the Fragment of interest
		if (*json == '"' && *(json + key_len + 2) == ':') {
			// There's a risk that the json + key_len + 1 equals is 
			// different than '"'
			if (memcmp(json + 1, key, key_len) == 0)
				return json + key_len + 3;
			else
				json += key_len + 2;
		}
		json++;
	}
	return NULL;
}

/******************************************************************
 * It looks up many key at one pass across json.
 * In the array, the keys shall be in INVERTED order of appearance.
 * It replies back where the values of the keys in vals
 * it returns the number of missing fields
 ******************************************************************/
unsigned char json_query_mulKey_ValPtrLen(char *json, char n, char **key,\
										  unsigned short *key_len, char **val,\
										  unsigned short *val_len) {
	char *_json = json;

	while (*json) {
		if ((*json == '"') && (*(json + key_len[n - 1] + 1) == '"')) {
			json++;	// skip '"'
			if (memcmp(json, key[n - 1], key_len[n - 1]) == 0) {
				json += key_len[n - 1] + 2; // skips "":"
					
				val[n - 1] = json;
				while ((*json != ',') && (*json != '}')) json++; // Grabs the key's value
				val_len[n - 1] = json - val[n - 1];

				n--;
				if (n == 0) return 0;
			}
		}
		json++;
		if(json - _json > 6000) {
			return n;
		}
	}
	return n;
}
