/*
 * Created Mar 24, 2022
 *  - by C. Alvarado
 */
#ifndef WEB_APP_H
#define WEB_APP_H 

#include <stdint.h>

/* code status */
#define HTTP_NOT_FOUND				0
#define HTTP_NOT_FOUND_STR			"HTTP/1.1 404 Not Found\r\n" 
#define HTTP_NOT_FOUND_LEN			24

#define HTTP_OK						1
#define HTTP_OK_STR					"HTTP/1.1 200 OK\r\n"
#define HTTP_OK_LEN					17

/* content-type */
#define HTTP_NO_CONTENT_TYPE		0
#define HTTP_CONTTYPE_TXTHTML 		1
#define HTTP_CONTTYPE_TXTHTML_STR 	"Content-type: text/html\r\n"
#define HTTP_CONTTYPE_TXTHTML_LEN 	25

#define HTTP_CONTTYPE_APPFORM		2
#define HTTP_CONTTYPE_APPFORM_STR	"Content-type: application/x-www-form-urlencoded\r\n"
#define HTTP_CONTTYPE_APPFORM_LEN	49

/* Connection */
#define HTTP_NON_CONNECTION			0
#define HTTP_CONN_CLOSE				1
#define HTTP_CONN_CLOSE_STR			"Connection: close\r\n"
#define HTTP_CONN_CLOSE_LEN			19

#define HTTP_CONN_KEEP_ALIVE		2
#define HTTP_CONN_KEEP_ALIVE_STR	"Connection: keep-alive\r\n"
#define HTTP_CONN_KEEP_ALIVE_LEN	24

/* Authorization */
#define HTTP_AUTH_BASIC				0
#define HTTP_AUTH_BASIC_STR			"Authorization: Basic %s\r\n"
#define HTTP_AUTH_BASIC_LEN			21

/* Content-Length
#define HTTP_CONTENT_LEN
#define HTTP_CONTENT_LEN_STR		"Content-length: "
#define HTTP_CONTENT_LEN_LEN		16
*/
#define HTTP_LEN_DIGITS				4

typedef struct WebAppBuilder_t {
	char status;
	char content_type;
	char connection;
	char content;
	char *http;
	unsigned short http_len;
	char http_len_str[HTTP_LEN_DIGITS];
	char http_len2;
} WebAppBuilder_t;


#define HTTPHEADERcpy(dest, head)	memcpy(dest, head##_STR, head##_LEN);\
									dest += head##_LEN

#define HTTPCONTENTcpy(dest, cont)	addcontent(dest, cont##_STR,\
									cont##_LEN)

extern WebAppBuilder_t webAppOptions;

int16_t mkHTTPHeader(WebAppBuilder_t *WAOpt);
char mkHTTP(WebAppBuilder_t *WAOpt);
uint16_t addcontent(char *http, char *html, uint16_t size);

#endif
