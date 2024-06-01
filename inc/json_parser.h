/*
 * Created Mar 7, 2022
 *  - by ckevar
 */

#ifndef JSON_PARSER_H
#define JSON_PARSER_H 

char *json_get_value_ptr(char *json, char *key, unsigned short key_len);
unsigned char json_query_mulKey_ValPtrLen(char *json, char n, char **key,\
										  unsigned short *key_len,\
										  char **val, unsigned short *val_len);
#endif
