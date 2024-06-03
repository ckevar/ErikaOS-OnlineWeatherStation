#include "wifi_supplicant.h"
#include "http.h"

#include <string.h>
#include <stdio.h>

char mkHTTP_WSupplicant(struct Http *http) {
	char *tmp;
	int16_t size;

	size = mkHTTPHeader(http);
	if(size < 0)
		return -1;

	tmp = http->http + size;

	// Set "Content-Length: "
	HTTPHEADERcpy(tmp, HTTP_CONTENT_LEN);

	// Set the content length and the content
	switch(http->content) {
	case WSUPP_INDEX:
		HTTPHEADERcpy(tmp, WEBAPP_INDEX_H);
		tmp += HTTPCONTENTcpy(tmp, WEBAPP_INDEX);
		break;

	case WEBAPP_ALLDONE:
		HTTPHEADERcpy(tmp, WEBAPP_ALLDONE_H);
		tmp += HTTPCONTENTcpy(tmp, WEBAPP_ALLDONE);
		break;

	default: // if (http->content == WEBAPP_CONTENT_NOT_FOUND) 
		HTTPHEADERcpy(tmp, WEBAPP_NOT_FOUND_H);
		tmp += HTTPCONTENTcpy(tmp, WEBAPP_NOT_FOUND); 
	}

	tmp++;
	*tmp = 0;
	
	http->size = tmp - http->http;
	size = snprintf(http->size_str, HTTP_LEN_DIGITS, "%d", http->size);

	if(size < 0 || size > HTTP_LEN_DIGITS)
		return -1;

	return 0;
}
