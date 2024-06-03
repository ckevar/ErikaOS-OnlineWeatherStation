/*
 * Created Apr 9, 2022
 *  - by C. Alvarado
 */
#include "http.h"

#include <string.h>

static char webAppBuff[750];

uint16_t addcontent(char *http, char *html, uint16_t size) {
		/* Set header ending */
		memcpy(http, "\r\n\r\n", 4);
		http += 4;

		/* Set content */
		memcpy(http, html, size);
		http += size;

		return 4 + size;
}

int16_t mkHTTPHeader(struct Http *http) {
	char *tmp;
   	http->http = tmp = webAppBuff;

	// HTTP STATUS CODE / HTTP/1.1 <code>
	if (http->status == HTTP_NOT_FOUND) {
		HTTPHEADERcpy(tmp, HTTP_NOT_FOUND);
	}
	else if (http->status == HTTP_OK) {
		HTTPHEADERcpy(tmp, HTTP_OK);
	}
	else {
		return -1;
	}

	// Set content type
	if (http->content_type == HTTP_CONTTYPE_TXTHTML) {
		HTTPHEADERcpy(tmp, HTTP_CONTTYPE_TXTHTML);
	} else {
		return -1;
	}

	// Set connection
	if (http->connection == HTTP_CONN_KEEP_ALIVE) {
		HTTPHEADERcpy(tmp, HTTP_CONN_KEEP_ALIVE);
	} else {
		HTTPHEADERcpy(tmp, HTTP_CONN_CLOSE);
	}
	
	return tmp - http->http;
}


