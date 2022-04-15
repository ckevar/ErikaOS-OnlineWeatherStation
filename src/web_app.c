/*
 * Created Apr 9, 2022
 *  - by C. Alvarado
 */
#include "web_app.h"

#include <string.h>

// tmp header
#include "lcd_log.h"

static char webAppBuff[512];

static unsigned short addCL_and_html(char *http, char *cl, char cll,\
									 char *html, unsigned short html_len)
{
		memcpy(http, cl, cll);
		http += cll;
		memcpy(http, "\r\n\r\n", 4);
		http += 4;
		memcpy(http, html, html_len);
		http += html_len;
		return cll + 4 + html_len;
}
char build_HTTP(WebAppBuilder_t *WAOpt)
{
	WAOpt->http = webAppBuff;  
	char *tmp = WAOpt->http;

	// HTTP STATUS CODE / HTTP/1.1 <code>
	if (WAOpt->status == WEBAPP_STATUS_NOT_FOUND) {
		memcpy(tmp, WEBAPP_STATUS_NOT_FOUND_STR, WEBAPP_STATUS_NOT_FOUND_LEN);
		tmp += WEBAPP_STATUS_NOT_FOUND_LEN;
	}
	else if (WAOpt->status == WEBAPP_STATUS_OK) {
		memcpy(tmp, WEBAPP_STATUS_OK_STR, WEBAPP_STATUS_OK_LEN);
		tmp += WEBAPP_STATUS_OK_LEN;
	}
	else return -1;

	// Set content type
	if (WAOpt->content_type == WEBAPP_CONTENT_TYPE_TEXT_HTML) {
		memcpy(tmp, WEBAPP_CONTENT_TYPE_TEXT_HTML_STR, WEBAPP_CONTENT_TYPE_TEXT_HTML_LEN);
		tmp += WEBAPP_CONTENT_TYPE_TEXT_HTML_LEN;
	}

	// Set connection
	if (WAOpt->connection == WEBAPP_CONN_KEEP_ALIVE) {
		memcpy(tmp, WEBAPP_CONN_KEEP_ALIVE_STR, WEBAPP_CONN_KEEP_ALIVE_LEN);
		tmp += WEBAPP_CONN_KEEP_ALIVE_LEN;
	} else {
		// By default the connection sent will be closed
		memcpy(tmp, WEBAPP_CONN_CLOSE_STR, WEBAPP_CONN_CLOSE_LEN);
		tmp += WEBAPP_CONN_CLOSE_LEN;
	}

	// Set "Content-Length: "
	memcpy(tmp, WEBAPP_CONTENT_LEN_STR, WEBAPP_CONTENT_LEN_LEN);
	tmp += WEBAPP_CONTENT_LEN_LEN;

	// Set the content length and the content
	if (WAOpt->content == WEBAPP_CONTENT_INDEX) {
		tmp += addCL_and_html(tmp, WEBAPP_CONTENT_INDEX_CL,\
							  WEBAPP_CONTENT_INDEX_CLL,\
							  WEBAPP_CONTENT_INDEX_STR,\
							  WEBAPP_CONTENT_INDEX_LEN);

	} else if (WAOpt->content == WEBAPP_CONTENT_TRYAGAIN) {
		tmp += addCL_and_html(tmp, WEBAPP_CONTENT_TRYAGAIN_CL,\
							  WEBAPP_CONTENT_TRYAGAIN_CLL,\
							  WEBAPP_CONTENT_TRYAGAIN_STR,\
							  WEBAPP_CONTENT_TRYAGAIN_LEN);

	} else if (WAOpt->content == WEBAPP_CONTENT_ALLDONE) {
		tmp += addCL_and_html(tmp, WEBAPP_CONTENT_ALLDONE_CL,\
							  WEBAPP_CONTENT_ALLDONE_CLL,\
							  WEBAPP_CONTENT_ALLDONE_STR,\
							  WEBAPP_CONTENT_ALLDONE_LEN);

	} else { // if (WAOpt->content == WEBAPP_CONTENT_NOT_FOUND) 
		tmp += addCL_and_html(tmp, WEBAPP_CONTENT_NOT_FOUND_CL,\
							  WEBAPP_CONTENT_NOT_FOUND_CLL,\
							  WEBAPP_CONTENT_NOT_FOUND_STR,\
							  WEBAPP_CONTENT_NOT_FOUND_LEN);
	}
	tmp++;
	*tmp = 0;
	
	WAOpt->http_len = tmp - WAOpt->http;
	WAOpt->http_len2 = sprintf(WAOpt->http_len_str,"%d", WAOpt->http_len);

	return 0;
}
