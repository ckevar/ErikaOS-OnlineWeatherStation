#include "spotify.h"
#include <stdio.h>

#include "json_parser.h"

/* As server */
char spotify_on_root(struct outHTTP *out, char *ip) {
	uint16_t size;

	outHTTP_basice_header(out, HTTP_200);
	size = snprintf(out->eof - out->free_space,
			out->free_space, HTTP_CONTENT_LENGTH,
			strlen(ip) + SPOTY_HTML_SZ);

	if(size > out->free_space)
		return 0;

	out->free_space -= size;

	size = snprintf(out->eof - out->free_space, 
			out->free_space, SPOTY_HTML, ip);

	if(size > out->free_space)
		return 0;
	
	out->free_space -= size;
	return 1;
}
/* As client */
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
		return key_len;

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
	
	/* Get the timestamp */
	dest = json_get_value_ptr(json, "timestamp", 9);
	if (dest == NULL) {
		dest = json;
		vals_sz[iSPOTIFY_TIME] = 0;
	} else {
		json_get_value(vals, vals_sz, dest, SPOTIFY_TIME);
	}

	/* Get the progress */
	dest = json_get_value_ptr(json, "progress_ms", 11);
	if (dest == NULL)
		dest = json;
	else {
		json_get_value(vals, vals_sz, dest, SPOTIFY_PROGRESS);
	}

	/* Get thre artist */
	JSON_get_panic(dest, dest, "artists", 7);
	JSON_get_panic(dest, dest, "name", 4);

	json_get_value(vals, vals_sz, dest, SPOTIFY_ARTIST);
	
	/* get the duration */
	dest = json_get_value_ptr(dest, "duration_ms", 11);
	if (dest == NULL) {
		dest = json;
	
		do {
			// JSON_get_panic(vals[iSPOTIFY_SONG], dest, "name", 4);
			vals[iSPOTIFY_SONG] = json_get_value_ptr(dest, "name" , 4);
			if (vals[iSPOTIFY_SONG] == NULL)
				return 4;
			JSON_get_panic(dest, vals[iSPOTIFY_SONG], "type", 4);
		} while(memcmp(dest, ": \"track\",", 10));
	
		dest = vals[iSPOTIFY_SONG];
		json_get_value(vals, vals_sz, dest, SPOTIFY_SONG);
		return 0;
	}

	json_get_value(vals, vals_sz, dest, SPOTIFY_DURATION);
	
	/* get Track */
	JSON_get_panic(dest, dest, "name", 4);
	json_get_value(vals, vals_sz, dest, SPOTIFY_SONG);

	return 0;
}
