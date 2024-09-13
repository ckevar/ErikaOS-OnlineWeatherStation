#ifndef HTTP_H
#define HTTP_H

#include <stdint.h>

enum HTTPMethods {
	/* This values are get xor-ing 0th ^ 3rd*/
	HTTP_Method_UNKNOWN = 0,
	HTTP_Method_GET = 103,
	HTTP_Method_POST = 4,
	HTTP_RESPONSE = 24,
};

enum HTTPStatusCode {
	HTTP_XXX = 0,
	HTTP_200 = '2' << 8,
	HTTP_204 = '2' << 8 | 4,
	HTTP_401 = '4' << 8 | 1,
	HTTP_500 = '5' << 8,
	HTTP_520 = '5' << 8 | 2 << 4,
	HTTP_522 = '5' << 8 | 2 << 4 | 2,
};

struct outHTTP {
	char *data;
	char *eof;
	int32_t free_space;
};

#define outHTTP_code(out, method)	\
	outHTTP_memcpy(out, method##_STR, method##_SZ);

#define outHTTP_header(out, header, sz)	\
	outHTTP_memcpy(out, header, sz)

void outHTTPv11_start(struct outHTTP *out);
uint16_t outHTTP_memcpy(struct outHTTP *out, const char *str, uint16_t size);
uint16_t outHTTP_body(struct outHTTP *out, const char *str, uint16_t size);

#define	outHTTP_basice_header(out, code)	\
	outHTTP_code(out, code);\
	outHTTP_memcpy(out,\
		HTTP_CONN_CLOSE_STR HTTP_CONTTYPE_TXTHTML_STR,\
		HTTP_CONN_CLOSE_LEN + HTTP_CONTTYPE_TXTHTML_LEN)

/**** HEADER *****/
#define HTTP_STRLEN(x)				(sizeof(x) - 1)
#define HTTP_v11					"HTTP/1.1 "
#define HTTP_v11_SZ					HTTP_STRLEN(HTTP_v11)

	/* code status */
#define HTTP_404_STR				"404 Not Found\r\n"
#define	HTTP_404_SZ					HTTP_STRLEN(HTTP_404_STR)

#define HTTP_200_STR				"200 OK\r\n"
#define HTTP_200_SZ					HTTP_STRLEN(HTTP_200_STR)

	/* content-type */
#define HTTP_CONTTYPE_TXTHTML_STR 	"Content-type: text/html\r\n"
#define HTTP_CONTTYPE_TXTHTML_LEN 	HTTP_STRLEN(HTTP_CONTTYPE_TXTHTML_STR)

#define HTTP_CONTTYPE_APPFORM_STR	"Content-type: application/x-www-form-urlencoded\r\n"
#define HTTP_CONTTYPE_APPFORM_LEN	HTTP_STRLEN(HTTP_CONTTYPE_APPFORM_STR)

	/* Connection */
#define HTTP_CONN_STR				"Connection: "
#define HTTP_CONN_CLOSE_0			"close\r\n"
#define HTTP_CONN_CLOSE_STR			HTTP_CONN_STR HTTP_CONN_CLOSE_0
#define HTTP_CONN_CLOSE_LEN			HTTP_STRLEN(HTTP_CONN_CLOSE_STR)

#define HTTP_CONN_KEEP_ALIVE_0		"keep-alive\r\n"
#define HTTP_CONN_KEEP_ALIVE_STR	HTTP_CONN_STR HTTP_CONN_KEEP_ALIVE_0
#define HTTP_CONN_KEEP_ALIVE_LEN	HTTP_STRLEN(HTTP_CONN_KEEP_ALIVE_STR)

	/* Authorization */
//#define HTTP_AUTH_BASIC_STR			"Authorization: Basic %s\r\n"
//#define HTTP_AUTH_BASIC_LEN			21

	/* Content-Length */
#define HTTP_CONTENT_LEN_STR		"Content-Length: "
#define HTTP_CONTENT_LEN_LEN		16
#define HTTP_CONTENT_LENGTH			HTTP_CONTENT_LEN_STR "%d\r\n\r\n"


#endif
