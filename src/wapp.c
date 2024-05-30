/*
 * Created Apr 9, 2022
 *  - by C. Alvarado
 */
#include "wapp.h"

#include <string.h>

// tmp header
#include "lcd_log.h"

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

int16_t mkHTTPHeader(WebAppBuilder_t *wbuilder) {
	char *tmp;
   	wbuilder->http = tmp = webAppBuff;

	// HTTP STATUS CODE / HTTP/1.1 <code>
	if (wbuilder->status == HTTP_NOT_FOUND) {
		HTTPHEADERcpy(tmp, HTTP_NOT_FOUND);
	}
	else if (wbuilder->status == HTTP_OK) {
		HTTPHEADERcpy(tmp, HTTP_OK);
	}
	else {
		return -1;
	}

	// Set content type
	if (wbuilder->content_type == HTTP_CONTTYPE_TXTHTML) {
		HTTPHEADERcpy(tmp, HTTP_CONTTYPE_TXTHTML);
	} else {
		return -1;
	}

	// Set connection
	if (wbuilder->connection == HTTP_CONN_KEEP_ALIVE) {
		HTTPHEADERcpy(tmp, HTTP_CONN_KEEP_ALIVE);
	} else {
		HTTPHEADERcpy(tmp, HTTP_CONN_CLOSE);
	}
	
	return tmp - wbuilder->http;
}


