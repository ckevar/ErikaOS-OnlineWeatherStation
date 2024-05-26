/*
 * Created Apr 9, 2022
 *  - by C. Alvarado
 */
#include "web_app.h"

#include <string.h>

// tmp header
#include "lcd_log.h"

static char webAppBuff[750];

static unsigned short addcontent(char *http, char *html, uint16_t size)
{
		/* Set header ending */
		memcpy(http, "\r\n\r\n", 4);
		http += 4;

		/* Set content */
		memcpy(http, html, size);
		http += size;

		return 4 + size;
}

#define HTTPHEADERcpy(dest, head)	memcpy(dest, head##_STR, head##_LEN);\
									dest += head##_LEN

#define HTTPCONTENTcpy(dest, cont)	addcontent(dest, cont##_STR,\
									cont##_LEN)

static int16_t mkHTTPHeader(WebAppBuilder_t *wbuilder) {
	char *tmp = wbuilder->http;

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
	if (wbuilder->content_type == HTTP_CONTENT_TYPE_TEXT_HTML) {
		HTTPHEADERcpy(tmp, HTTP_CONTENT_TYPE_TEXT_HTML);
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

char mkHTTP(WebAppBuilder_t *WAOpt) {
	WAOpt->http = webAppBuff;  
	char *tmp;
	int16_t size;

	size = mkHTTPHeader(WAOpt);
	if(size < 0)
		return -1;

	tmp = WAOpt->http + size;

	// Set "Content-Length: "
	HTTPHEADERcpy(tmp, HTTP_CONTENT_LEN);

	// Set the content length and the content
	switch(WAOpt->content) {
	case WEBAPP_INDEX:
		HTTPHEADERcpy(tmp, WEBAPP_INDEX_H);
		tmp += HTTPCONTENTcpy(tmp, WEBAPP_INDEX);
		break;
	/*
	case WEBAPP_TRYAGAIN:
		HTTPHEADERcpy(tmp, WEBAPP_TRYAGAIN_H);
		tmp += HTTPCONTENTcpy(tmp, WEBAPP_TRYAGAIN);
		break;
	*/
	case WEBAPP_ALLDONE:
		HTTPHEADERcpy(tmp, WEBAPP_ALLDONE_H);
		tmp += HTTPCONTENTcpy(tmp, WEBAPP_ALLDONE);
		break;

	default: // if (WAOpt->content == WEBAPP_CONTENT_NOT_FOUND) 
		HTTPHEADERcpy(tmp, WEBAPP_NOT_FOUND_H);
		tmp += HTTPCONTENTcpy(tmp, WEBAPP_NOT_FOUND); 
	}

	tmp++;
	*tmp = 0;
	
	WAOpt->http_len = tmp - WAOpt->http;
	WAOpt->http_len2 = sprintf(WAOpt->http_len_str,"%d", WAOpt->http_len);

	return 0;
}
