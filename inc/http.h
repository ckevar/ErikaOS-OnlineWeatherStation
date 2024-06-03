#ifndef HTTP_H
#define HTTP_H

#include <stdint.h>

#define HTTP_METHOD_GET_SIZE	3
#define HTTP_METHOD_POST_SIZE	4
#define HTTP_METHOD_RESPONSE	8

enum HTTPMethods {
	HTTP_Method_UNKNOWN = 0,
	HTTP_Method_GET = HTTP_METHOD_GET_SIZE,
	HTTP_Method_POST = HTTP_METHOD_POST_SIZE,
	HTTP_RESPONSE = HTTP_METHOD_RESPONSE,
};

enum HTTPStatusCode {
	HTTP_XXX,
	HTTP_1XX,
	HTTP_2XX,
	HTTP_200,
	HTTP_204,
	HTTP_3XX,
	HTTP_4XX,
	HTTP_401,
	HTTP_5XX,
	HTTP_520,
	HTTP_522,
};


/**** HEADER *****/
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

	/* Content-Length */
#define HTTP_CONTENT_LEN
#define HTTP_CONTENT_LEN_STR		"Content-Length: "
#define HTTP_CONTENT_LEN_LEN		16


/**** Builder *****/
#define HTTP_LEN_DIGITS				4

struct Http {
	char status;
	char content_type;
	char connection;
	char content;
	char *http;
	unsigned short size;
	char size_str[HTTP_LEN_DIGITS];
};


#define HTTPHEADERcpy(dest, head)	memcpy(dest, head##_STR, head##_LEN);\
									dest += head##_LEN

#define HTTPCONTENTcpy(dest, cont)	addcontent(dest, cont##_STR,\
									cont##_LEN)


int16_t mkHTTPHeader(struct Http *http);
char mkHTTP(struct Http *http);
uint16_t addcontent(char *http, char *html, uint16_t size);

extern struct Http http_conf;

#endif
