#include "wapp.h"
#include "wifi_supplicant.h"

#include <string.h>
#include <stdio.h>

char mkHTTP_WSupplicant(WebAppBuilder_t *WAOpt) {
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
	case WSUPP_INDEX:
		HTTPHEADERcpy(tmp, WEBAPP_INDEX_H);
		tmp += HTTPCONTENTcpy(tmp, WEBAPP_INDEX);
		break;

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
