/*
 * Created Apr 9, 2022
 *  - by C. Alvarado
 */
#include "http.h"

#include <string.h>
#include <stdio.h>

#define WEBSERVER_SZ	750
static char webAppBuff[WEBSERVER_SZ];

void outHTTPv11_start(struct outHTTP *out) {
	out->data = webAppBuff;
	out->eof = webAppBuff + WEBSERVER_SZ;
	memcpy(out->data, HTTP_v11, HTTP_v11_SZ);
	out->free_space = WEBSERVER_SZ - HTTP_v11_SZ;
}

uint16_t outHTTP_memcpy(struct outHTTP *out, const char *str, uint16_t size) {
	if(size > out->free_space)
		return 0;

	memcpy(out->eof - out->free_space, str, size);
	out->free_space -= size;
	return size;
}

uint16_t outHTTP_body(struct outHTTP *out, const char *str, uint16_t size) {
	uint16_t nu_size;

	nu_size = snprintf(out->eof - out->free_space, out->free_space, \
			HTTP_CONTENT_LENGTH, size);

	if(nu_size > out->free_space)
		return 0;

	out->free_space -= nu_size;
	return outHTTP_memcpy(out, str, size);
}
