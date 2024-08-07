#ifndef SPOTIFY_H
#define SPOTIFY_H

#include "spotify_private.h"
#include "http.h"

#include <string.h>

/* Server: Supplicant {												*/
#define SPOTY_REQ				"/spotify"
#define SPOTY_REQ_LEN			strlen(SPOTY_REQ)
#define SPOTY_REQ_CALLBACK		"/spotify_code?code="
#define SPOTY_REQ_CALLBACK_LEN	strlen(SPOTY_REQ_CALLBACK)

#define SPOTY_HTML0		\
"<head><title>Erika Spotify</title></head>"\
"<body>"\
	"<center>"\
	"<a href=\"https://accounts.spotify.com/authorize"\
		"?response_type=code"\
		"&client_id="

#define SPOTY_HTML1		\
		"&redirect_uri=http://%s/spotify_code"\
		"&scope"\
			"=user-modify-playback-state"\
			"+user-read-currently-playing"\
			"+user-read-playback-state"\
			"+user-library-modify"\
			"+user-library-read"\
		"\">Log in to <b>Spotify</b></a>"\
	"</center>"\
"</body>"\

#define SPOTY_HTML		SPOTY_HTML0 SPOTIFY_CLIENT_ID SPOTY_HTML1
#define SPOTY_HTML_SZ	(sizeof(SPOTY_HTML) - 3)	// 2 is due to "%s"

char spotify_on_root(struct outHTTP *http, char *ip);

/* }																*/

/* Client {															*/
	/*** Token Request ***/
#define	SPOTIFY_AUTH_HOST		"\"accounts.spotify.com\",443"
#define	SPOTIFY_AUTH_LEN		(sizeof(SPOTIFY_AUTH_HOST) - 1)
#define	SPOTIFY_AUTH_HEAD		"POST /api/token HTTP/1.1\r\n"\
								"Host: accounts.spotify.com\r\n"\
								"User-Agent: ERIKA RTOS/ESP8266/v1.0\r\n"\
								"Authorization: Basic " SPOTIFY_SECRET "\r\n"\
								"Content-Type: application/x-www-form-urlencoded\r\n"\
								"Content-Length: %d\r\n"\
								"\r\n"\
								"%s"
#define SPOTIFY_AUTH_CONTENT	"grant_type=authorization_code&"\
								"redirect_uri=http://%s/spotify_code&"\
								"code="
#define SPOTIFY_AUTH_RANDOM_POS	100	// THis has to be larger than 84 
									// because the position being checked 
									// is larger than strlen(SPOTIFY_AUTH_CONTENT)

	/*** Token Refresh ***/
#define SPOTIFY_REFRESH_CONTENT	"grant_type=refresh_token&"\
								"refresh_token=%s"

	/*** Token Utilities ***/
enum {
	iSPOTIFY_RTOKEN,
	iSPOTIFY_TOKEN,
	SPOTIFY_TOKEN_COUNT,
};

#define SPOTIFY_TOKEN_SIZE			250
#define SPOTIFY_RTOKEN_SIZE			150
#define SPOTIFY_AUTH_CONTENT_SIZE	430

char spotify_get_token(char *http, char **vals, uint16_t *sizes);

	/*** API ***/
#define SPOTIFY_API				"\"api.spotify.com\",443"
#define SPOTIFY_API_LEN			(sizeof(SPOTIFY_API) - 1)

#define SPOTIFY_GET_PLAYER		"GET /v1/me/player/currently-playing?market=IT "
#define SPOTIFY_API_HEAD		"HTTP/1.1\r\n"\
								"Host: api.spotify.com\r\n"\
								"User-Agent: ERIKA RTOS/ESP8266/v1.0\r\n"\
								"Authorization: Bearer %s\r\n\r\n"

enum {
	iSPOTIFY_ARTIST,
	iSPOTIFY_SONG,
	iSPOTIFY_PROGRESS,
	iSPOTIFY_DURATION,
	iSPOTIFY_TIME,
	SPOTIFY_TRACK_COUNT
};

#define SPOTIFY_PROGRESS_OFFSET	2
#define SPOTIFY_PROGRESS_DELIM	','

#define SPOTIFY_ARTIST_OFFSET	3
#define SPOTIFY_ARTIST_DELIM	'"'

#define SPOTIFY_SONG_OFFSET		3
#define SPOTIFY_SONG_DELIM		'"'

#define SPOTIFY_DURATION_OFFSET	2
#define SPOTIFY_DURATION_DELIM	','

#define SPOTIFY_TIME_OFFSET		2
#define SPOTIFY_TIME_DELIM		','

char spotify_get_track(char *json, char **vals, uint16_t *sizes);
/* }																*/
#endif
