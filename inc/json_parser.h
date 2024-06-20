/*
 * Created Mar 7, 2022
 *  - by ckevar
 */

#ifndef JSON_PARSER_H
#define JSON_PARSER_H 

#include <stdint.h>

char *json_get_value_ptr(char *json, char *key, unsigned short key_len);
unsigned char json_query_mulKey_ValPtrLen(char *json, int16_t n,
										  char **key, uint16_t *key_len,
										  char **val, uint16_t *val_len);
#endif
