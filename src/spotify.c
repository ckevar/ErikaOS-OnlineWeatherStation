#include "spotify.h"
#include <stdio.h>

#include "json_parser.h"

char mkHTTP_SpotySupplicant(WebAppBuilder_t *WAOpt, char *ipv4) {
	char *tmp;
	int16_t size;

	size = mkHTTPHeader(WAOpt);
	if(size < 0)
		return -1;

	tmp = WAOpt->http + size;
	HTTPHEADERcpy(tmp, HTTP_CONTENT_LEN);

	switch(WAOpt->content) {
	case SPOTY_RESP:
		size = snprintf(tmp + 7, 512, SPOTY_HTML, ipv4);
		
		if (size < 0) 
			return -1;

		if(snprintf(tmp, 512, "%03d\r\n\r\n", size) < 0)
			return -1;

		tmp += size + 7;

	case SPOTY_CALLBACK_RESP:
		memcpy(tmp, "0\r\n\r\n", 5);
		tmp += 5;
	}
	tmp++;
	*tmp = 0;

	WAOpt->http_len = tmp - WAOpt->http;
	WAOpt->http_len2 = snprintf(WAOpt->http_len_str,HTTP_LEN_DIGITS, "%d", WAOpt->http_len);

	return 0;
}


char spotify_get_token(char *json, char **vals, uint16_t *vals_sizes) {
	char *keys[SPOTIFY_TOKEN_COUNT] = {"refresh_token", "access_token"};
	uint16_t keys_sizes[SPOTIFY_TOKEN_COUNT] = {13, 12};


	if(json_get_value_ptr(json, "error", 5) != NULL)
		return 1;

	if(json_get_value_ptr(json, "refresh_token", 13) == NULL) {
		json_query_mulKey_ValPtrLen(json, 1, keys + 1,\
				keys_sizes + 1, vals + 1, vals_sizes + 1);
		vals_sizes[iSPOTIFY_RTOKEN] = 0;
	} else {
		json_query_mulKey_ValPtrLen(json, 2, keys,\
				keys_sizes, vals, vals_sizes);
	}

	if(vals_sizes[iSPOTIFY_TOKEN] == 0)
		return 1;
	
	return 0;

}

#define JSON_get_panic(dest, src, key, key_len)	\
	dest = json_get_value_ptr(src, key, key_len); \
	if (dest == NULL)\
		return 1

char spotify_get_track(char *json, char **vals, uint16_t *vals_sizes) {
	char *keys[SPOTIFY_TRACK_COUNT] = {"name",  "name", "name", "name"};
	uint16_t keys_sizes[SPOTIFY_TRACK_COUNT] = {4, 4, 4, 4};
	char *dest;
	
	vals[iSPOTIFY_ARTIST] = "Null";
	vals[iSPOTIFY_SONG] = "Null";
	vals_sizes[iSPOTIFY_ARTIST] = 4;
	vals_sizes[iSPOTIFY_SONG] = 4;

	/* Artist */
	JSON_get_panic(dest, json, "artists", 7);
	JSON_get_panic(dest, dest, "name", 4);
	
	dest += 3;
	vals[iSPOTIFY_ARTIST] = dest;
	while(*dest != '"') 
		dest++;

	vals_sizes[iSPOTIFY_ARTIST] = dest - vals[iSPOTIFY_ARTIST];

	/* Track */
	do {
		JSON_get_panic(vals[iSPOTIFY_SONG], dest, "name", 4);
		JSON_get_panic(dest, vals[iSPOTIFY_SONG], "type", 4);
	} while(memcmp(dest, ": \"track\",", 10));
	

	dest = vals[iSPOTIFY_SONG];
	dest += 3;
	vals[iSPOTIFY_SONG] = dest;
	while(*dest != '"')
		dest++;

	vals_sizes[iSPOTIFY_SONG] = dest - vals[iSPOTIFY_SONG];
	
	/*
	if(json_query_mulKey_ValPtrLen(json, SPOTIFY_TRACK_COUNT,\
			keys, keys_sizes, vals, vals_sizes) > 0) {
		return 1;
	}
	*/
	
	return 0;
}
