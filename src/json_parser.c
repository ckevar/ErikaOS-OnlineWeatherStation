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
char *json_query_key_ValPtr(char *json, char *key, unsigned short key_len) {
	char key2search[key_len + 3];
	*key2search = '"';
	memcpy(key2search + 1, key, key_len);
	memcpy(key2search + 1 + key_len, "\":", 2);

	while (*json) {
		if (*json == '"') {
			if (memcmp(json, key2search, key_len + 3) == 0)
				return json + key_len + 3;
		}
		json++;
	}
	return NULL;
}

/******************************************************************
 * It looks up many key at one pass across json.
 * In the array, the keys shall be in INVERTED order of appearance.
 * It replies back where the values of the keys in vals
 ******************************************************************/
unsigned char json_query_mulKey_ValPtrLen(char *json, char n, char **key,\
										  unsigned short *key_len, char **val,\
										  unsigned short *val_len) {
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
	}
	return n;
}
