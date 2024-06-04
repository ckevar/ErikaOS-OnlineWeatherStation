#include "spotify.h"
#include <stdio.h>

#include "json_parser.h"

char mkHTTP_SpotySupplicant(struct Http *http, char *ipv4) {
	char *tmp;
	int16_t size;

	size = mkHTTPHeader(http);
	if(size < 0)
		return -1;

	tmp = http->http + size;
	HTTPHEADERcpy(tmp, HTTP_CONTENT_LEN);

	switch(http->content) {
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

	http->size = tmp - http->http;
	size = snprintf(http->size_str,HTTP_LEN_DIGITS, "%d", http->size);
	
	if(size < 0 || size > HTTP_LEN_DIGITS)
		return -1;

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


#define JSON_get_panic(dest, src, key, key_len)		\
	dest = json_get_value_ptr(src, key, key_len);\
	if (dest == NULL)\
		return 1

#define json_get_value(dest, destsz, src, key_id)	\
	src += key_id##_OFFSET;\
	*(dest + i##key_id) = src;\
	while(*(src) != key_id##_DELIM)\
		src++;\
	destsz[i##key_id] = src - dest[i##key_id]

char spotify_get_track(char *json, char **vals, uint16_t *vals_sz) {
	char *dest;
	
	vals[iSPOTIFY_ARTIST] = "Null";
	vals[iSPOTIFY_SONG] = "Null";
	vals_sz[iSPOTIFY_ARTIST] = 4;
	vals_sz[iSPOTIFY_SONG] = 4;

	/* */
	dest = json_get_value_ptr(json, "timestamp", 9);
	if (dest == NULL) {
		dest = json;
		vals_sz[iSPOTIFY_TIME] = 0;
	} else {
		json_get_value(vals, vals_sz, dest, SPOTIFY_TIME);
	}

	/* progress ms */
	dest = json_get_value_ptr(json, "progress_ms", 11);
	if (dest == NULL)
		dest = json;
	else {
		json_get_value(vals, vals_sz, dest, SPOTIFY_PROGRESS);
	}

	/* Artist */
	JSON_get_panic(dest, dest, "artists", 7);
	JSON_get_panic(dest, dest, "name", 4);
	json_get_value(vals, vals_sz, dest, SPOTIFY_ARTIST);

	/* duration_ms */
	dest = json_get_value_ptr(dest, "duration_ms", 11);
	if (dest == NULL) {
		dest = json;
	
		/* Track */
		do {
			JSON_get_panic(vals[iSPOTIFY_SONG], dest, "name", 4);
			JSON_get_panic(dest, vals[iSPOTIFY_SONG], "type", 4);
		} while(memcmp(dest, ": \"track\",", 10));
	
		dest = vals[iSPOTIFY_SONG];
		json_get_value(vals, vals_sz, dest, SPOTIFY_SONG);
		return 0;
	}

	json_get_value(vals, vals_sz, dest, SPOTIFY_DURATION);
	
	/* Track */
	JSON_get_panic(dest, dest, "name", 4);
	json_get_value(vals, vals_sz, dest, SPOTIFY_SONG);

	return 0;
}
