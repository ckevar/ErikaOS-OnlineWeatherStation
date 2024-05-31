#include "network.h"
#include "esp8266_settings.h"
#include "esp8266_server.h"
#include "esp8266_client.h"
#include "esp8266_driver.h"

#include <string.h>
#include <stdio.h>

#include "wapp.h"
#include "state.h"
#include "wifi_supplicant.h"

#include "openweather.h"
#include "ipapi_json.h"
#include "spotify.h"

#include "WidgetConfig.h"

#define MATCH(str, res)				if(memcmp(str, res, res##_LEN) == 0)

WebAppBuilder_t webAppOptions;
static char		spotify_auth_content[SPOTIFY_AUTH_CONTENT_SIZE];
static int16_t	spotify_code;

static void app_spotify_conf(uint8_t *success, char *http, void *arg) {

	struct Socket *sock = (struct Socket *) arg;
	char *code;

	MATCH(http, SPOTY_REQ_CALLBACK) {
		memset(http, 0, SPOTY_REQ_CALLBACK_LEN);
		http += SPOTY_REQ_CALLBACK_LEN;

		webAppOptions.content_type = HTTP_CONTTYPE_TXTHTML;
		webAppOptions.status = HTTP_OK;
		webAppOptions.connection = HTTP_CONN_CLOSE;
		webAppOptions.content = SPOTY_CALLBACK_RESP;

		mkHTTP_SpotySupplicant(&webAppOptions, NULL);

		sock->rsize = webAppOptions.http_len_str;
		esp8266_load_html(webAppOptions.http, webAppOptions.http_len);

		*success = 1;

		code = (char *)sock->arg;
		
		/* copy code */
		while(*http) {
			*code = *http;
			*http = 0; 
			http++; code++;
			spotify_code++;
		}

		return;
	}

	MATCH(http, SPOTY_REQ) {
		memset(http, 0, SPOTY_REQ_LEN);

		webAppOptions.content_type = HTTP_CONTTYPE_TXTHTML;
		webAppOptions.status = HTTP_OK;
		webAppOptions.connection = HTTP_CONN_CLOSE;	
		webAppOptions.content = SPOTY_RESP;

		mkHTTP_SpotySupplicant(&webAppOptions, ESP8266_IPv4.ip);

		sock->rsize = webAppOptions.http_len_str;
		esp8266_load_html(webAppOptions.http, webAppOptions.http_len);

		*success = 1;
		return;
	
	}

	

	*success = 0;
}

void mkHTMLx(const char icontent, const char status) {
	/* Head */
	webAppOptions.content_type = HTTP_CONTTYPE_TXTHTML;
	webAppOptions.status = status;
	webAppOptions.connection = HTTP_CONN_CLOSE;	

	/* Content */
	webAppOptions.content = icontent;

	mkHTTP_WSupplicant(&webAppOptions);
}

void app_http_from_WebApp(uint8_t *success, char *http,  void *arg) {
    struct Socket *sock = (struct Socket *) arg;
    SSIDnPSWD_t *snp = (SSIDnPSWD_t *) sock->arg;

	MATCH(http, WRES_INDEX) {	
		// /index.html
		*http = 0; 

		mkHTMLx(WSUPP_INDEX, HTTP_OK);
        sock->rsize = webAppOptions.http_len_str;
		esp8266_load_html(webAppOptions.http, webAppOptions.http_len);

        *success = 1;
		return;

	} 
	MATCH(http, WRES_FAVICON) {
		// /favicon
		memset(http, '\0', WRES_FAVICON_LEN);

		mkHTMLx(WSUPP_NOT_FOUND, HTTP_NOT_FOUND);
        sock->rsize = webAppOptions.http_len_str;
	    esp8266_load_html(webAppOptions.http, webAppOptions.http_len);
        *success = 1;
		return;
		
	}
	MATCH(http, WRES_SETWiFi) {
		// /set_wifi
		memset(http, '\0', WRES_SETWiFi_LEN);
		char i = WRES_SETWiFi_LEN;

		mkHTMLx(WEBAPP_ALLDONE, HTTP_OK);
		sock->rsize = webAppOptions.http_len_str;
		esp8266_load_html(webAppOptions.http, webAppOptions.http_len);
		*success = 1;

		// Fast cleaning of the SSID and Password buffer
		snp->size = 0;
		snp->ssidNpassword[0] = 0;

		// Parsing ssid and password
		MATCH(http + i, WSUPP_SSID) {
			i += WSUPP_SSID_LEN;

			snp->ssidNpassword[snp->size] = '\"';
			snp->size++;

			// Iterate until 
			while(http[i] != '&') {
				// Replacing '+'s by ' ' (spaces)
				snp->ssidNpassword[snp->size] = (http[i] == '+') \
                                               ? ' '\
                                               : http[i];
				snp->size++;
				i++;
			}
			// Composing <ssid>","<password> 
			memcpy(snp->ssidNpassword + snp->size, "\",\"", 3);
			snp->size += 3;		// Skip '","'
			i++;				// SKip '&'

			MATCH(http + i, WSUPP_PSWD) {
				i += WSUPP_PSWD_LEN;
				while(http[i]) {
					snp->ssidNpassword[snp->size] = http[i];
					i++;
					snp->size++;
				}
				snp->ssidNpassword[snp->size] = '\"';
				snp->size++;
				snp->ssidNpassword[snp->size] = 0;
			}

		}
	}
}

#define iOW_STR				0
#define iOW_LEN				1
#define TMP_RESOURCE_SIZE	700

static void IPAPI_process_result(uint8_t *success, char *tmp, void *arg) {	
	uint16_t msg_size;
	char *IPAPI_VALS[IPAPI_JSON_MEMBERS];
	unsigned short IPAPI_VALS_LEN[IPAPI_JSON_MEMBERS];
	char **ow_resource = (char **)arg;
	char *ow_http = ow_resource[iOW_STR];
    
	if (IPAPI_get_location_PtrLen(tmp, IPAPI_VALS, IPAPI_VALS_LEN)) {
        *success = 1;
        return;
    }
		
    /* Show information on LCD */
	// clear the last '"'
	*(IPAPI_VALS[IPAPI_JSON_CITY_Idx] + IPAPI_VALS_LEN[IPAPI_JSON_CITY_Idx] - 1) = 0; 
	// skip the first '"'
	IPAPI_VALS[IPAPI_JSON_CITY_Idx]++;

	UI_writeCity(IPAPI_VALS[IPAPI_JSON_CITY_Idx]);
	UI_LocationAvailable();

	// Clear memory
	memset(ow_http, '\0', TMP_RESOURCE_SIZE);
		
	/* Form New package to retrieve weather data */
	// Set Latitud
	memcpy(ow_http, OWAPI_GET_LAT, OWAPI_GET_LAT_LEN);
	ow_http += OWAPI_GET_LAT_LEN;

	memcpy(ow_http, IPAPI_VALS[IPAPI_JSON_LAT_Idx],\
		   			IPAPI_VALS_LEN[IPAPI_JSON_LAT_Idx]);
	ow_http += IPAPI_VALS_LEN[IPAPI_JSON_LAT_Idx];

	// Set Longitud
	memcpy(ow_http, OWAPI_GET_LON, OWAPI_GET_LON_LEN);
	ow_http += OWAPI_GET_LON_LEN;

	memcpy(ow_http, IPAPI_VALS[IPAPI_JSON_LON_Idx],\
		            IPAPI_VALS_LEN[IPAPI_JSON_LON_Idx]);
	ow_http += IPAPI_VALS_LEN[IPAPI_JSON_LON_Idx];

	// Set Units and API Key
	memcpy(ow_http, OWAPI_GET_UNITSnKEY, OWAPI_GET_UNITSnKEY_LEN);
	ow_http += OWAPI_GET_UNITSnKEY_LEN;
	

	msg_size = ow_http - ow_resource[iOW_STR];
	sprintf(ow_resource[iOW_LEN], "%d", msg_size);

	*success = 0;
}

static void OWAPI_process_result(uint8_t *success, char *tmp, void *arg) {
	char *weather[OWAPI_PARAMS_COUNT];
	unsigned short sizes[OWAPI_PARAMS_COUNT];
    
	if(OWAPI_get_weather(tmp, weather, sizes)) {
        *success = 1;
        return;
    }

    /* Weather Description */
	*(weather[iOWAPI_DESCRIPTION] + sizes[iOWAPI_DESCRIPTION] - 1) = 0;
	weather[iOWAPI_DESCRIPTION]++;
	UI_writeWeatherDescription(weather[iOWAPI_DESCRIPTION]);

    /* Temperature and Feeling Temperature */
	UI_writeWeatherFeelsLike(weather[iOWAPI_FEELS_LIKE]);
	UI_writeWeatherCurrTemp(weather[iOWAPI_TEMP]);

    /* Weather Icon */
	*(weather[iOWAPI_ICON] + sizes[iOWAPI_ICON] - 1) = 0;
	weather[iOWAPI_ICON]++;
	UI_setWeatherIcon((unsigned short *) weather[iOWAPI_ICON]);

    /* Request Time */
    *(weather[iOWAPI_TIMEZONE] + sizes[iOWAPI_TIMEZONE]) = 0;
    *(weather[iOWAPI_TIME] + sizes[iOWAPI_TIME]) = 0;
    UI_setTime(weather[iOWAPI_TIMEZONE], weather[iOWAPI_TIME]);

	*success = 0;
}

static void spotify_token_processor(uint8_t *success, char *http, void *arg) {
	char *tokens_ptr[SPOTIFY_TOKEN_COUNT];
	uint16_t sizes[SPOTIFY_TOKEN_COUNT];
	char **token = (char **)arg;

	if(spotify_get_token(http, tokens_ptr, sizes)) {
		*success = 1;
		return;
	}

	memcpy(token[iSPOTIFY_TOKEN],\
			tokens_ptr[iSPOTIFY_TOKEN] + 1,\
			sizes[iSPOTIFY_TOKEN] - 2);

	memcpy(token[iSPOTIFY_RTOKEN],\
			tokens_ptr[iSPOTIFY_RTOKEN] + 1,\
			sizes[iSPOTIFY_RTOKEN] - 2);

	*success = 0;
}

static void spotify_track_processor(uint8_t *success, char *http, void *arg) {
	char *track_ptr[2];
	uint16_t sizes[2];

	if (esp8_status.http == HTTP_204) {
		*success = 0;
		return;
	}

	if(spotify_get_track(http, track_ptr, sizes)) {
		*success = 1;
		return;
	}
	
	*(track_ptr[1] + sizes[1]) = 0;
	UI_set_track(track_ptr[1]);

	*success = 0;
}


/******** Server Function *********/
enum AppServerState {
	SERVER_CONF,
	SERVER_RUNNING,
};

enum ServersID {
	WIFI_SUPPLICANT,
	SPOTIFY_CODE,
};

void server_function(struct StateS *s, enum ServersID server_id) {
    static struct Socket socket;
    static SSIDnPSWD_t wifi_credentials;
	static enum AppServerState server_state = SERVER_CONF;
	
	switch(server_id) {
	case WIFI_SUPPLICANT:
		switch(server_state) {
		case SERVER_CONF:
			socket.callback = &app_http_from_WebApp;
			socket.arg = (void *)&wifi_credentials;
			server_state = SERVER_RUNNING;
			esp8_status.wifi = WiFi_NO_CONNECTED;
			break;
		}
	
		// case SERVER_RUNNING:
		fsm_server(s, &socket);

		if (wifi_credentials.size > 0 && SUBSTATE(*s->state) == ESP8S_LISTENING)
			fsm_station_credentials(s, &wifi_credentials);

		break;

	case SPOTIFY_CODE:
		switch(server_state) {
		case SERVER_CONF:
			spotify_code = snprintf(spotify_auth_content,\
					SPOTIFY_AUTH_CONTENT_SIZE,\
					SPOTIFY_AUTH_CONTENT, ESP8266_IPv4.ip);
			
			if (spotify_code < 0) {
				*s->nx_state = MKSTATE(ESP8SS_READY, 0);
				break;
			}
		
			socket.callback = &app_spotify_conf;
			socket.arg = (void *)(spotify_auth_content + spotify_code);
			server_state = SERVER_RUNNING;
			*(spotify_auth_content + SPOTIFY_AUTH_RANDOM_POS) = 0;
			break;
		}
		
		// case SERVER_RUNNING:
		fsm_server(s, &socket);

		if(*(spotify_auth_content + SPOTIFY_AUTH_RANDOM_POS) > ' ' && \
			SUBSTATE(*s->state) == ESP8S_LISTENING)
		{
			*s->nx_state = MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART); 
		}

	}

	if (SUBSTATE(*s->state) == ESP8S_SERVER_OFF)
		server_state = SERVER_CONF;

}


enum AppClientState {
	CLIENT_CONF,
	CLIENT_EXEC,
};

enum ClientIDs {
	LOCATION,
	WEATHER,
	SPOTIFY_AUTH,
	SPOTIFY_PLAYER,
};

void client_function(struct StateS *state)  {
    static enum AppClientState client_state = CLIENT_CONF;
	static enum ClientIDs client_id;
    static struct Socket sock;
	static char tmp_resource[TMP_RESOURCE_SIZE];
	static char tmp_resource_len[OWAPI_GET_RESOURCE_STR_LEN + 1];
	static char *tmp_ptr[2];
	static char spotify_token[SPOTIFY_TOKEN_SIZE];
	static char spotify_rtoken[SPOTIFY_RTOKEN_SIZE];
	int16_t size;

	switch(client_id) {
	case LOCATION:
		switch(client_state) {
		case CLIENT_CONF:
			UI_LocationUnavailable();
		
			tmp_ptr[iOW_STR] = tmp_resource;
			tmp_ptr[iOW_LEN] = tmp_resource_len;

			sock.link = 0,
			sock.domain_port = IPAPI_JSON_DNS_PORT,
			sock.dsize = IPAPI_JSON_DNS_PORT_LEN,
			sock.request = IPAPI_GET_RESOURCE,
			sock.rsize = IPAPI_GET_RESOURCE_LEN,
			sock.callback = &IPAPI_process_result,
			sock.arg = (void *)tmp_ptr;
			client_state = CLIENT_EXEC;

		case CLIENT_EXEC:
			fsm_client(state, &sock);

			if (SUPERSTATE(*state->nx_state) == ESP8SS_READY) {
				client_state = CLIENT_CONF;
				client_id =	WEATHER;
				*state->nx_state = MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT_TCP);
				UI_LocationAvailable();
			}
		}
		break;

	case WEATHER:
		switch(client_state) {
		case CLIENT_CONF:

			sock.link = 1;
			sock.domain_port = OWAPI_DNS_PORT;
			sock.dsize = OWAPI_DNS_PORT_LEN;
			sock.request = tmp_resource;
			sock.rsize = tmp_resource_len;
			sock.callback = &OWAPI_process_result,
			sock.arg = NULL;
			client_state = CLIENT_EXEC;

		case CLIENT_EXEC:
			fsm_client(state, &sock);
		
			if(SUPERSTATE(*state->nx_state) == ESP8SS_READY) {
				if (*(spotify_auth_content + SPOTIFY_AUTH_RANDOM_POS) > ' ') {
					client_id = SPOTIFY_AUTH;
					*state->nx_state = MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT_SSL);
				}
				else {
					client_id = LOCATION;
				}

				client_state = CLIENT_CONF;
			}
		}
		break;
	
	case SPOTIFY_AUTH:
		switch(client_state) {
		case CLIENT_CONF:
			size = snprintf(tmp_resource, TMP_RESOURCE_SIZE,\
				   SPOTIFY_AUTH_HEAD, spotify_code, spotify_auth_content);
		
			if(size < 0 || size > TMP_RESOURCE_SIZE) {
				client_state = CLIENT_CONF;
				client_id = LOCATION;
				*state->nx_state = MKSTATE(ESP8SS_READY, 0);
				break;
			}

			if(snprintf(tmp_resource_len, 4, "%d", size) < 0) {
				client_state = CLIENT_CONF;
				client_id = LOCATION;
				*state->nx_state = MKSTATE(ESP8SS_READY, 0);
				break;		
			} 

			memset(spotify_token, 0, SPOTIFY_TOKEN_SIZE);
			memset(spotify_rtoken, 0, SPOTIFY_RTOKEN_SIZE);

			tmp_ptr[iSPOTIFY_TOKEN] = spotify_token;
			tmp_ptr[iSPOTIFY_RTOKEN] = spotify_rtoken;

			sock.link = 0;
			sock.domain_port = SPOTIFY_AUTH_HOST,
			sock.dsize = SPOTIFY_AUTH_LEN,
			sock.request = tmp_resource,
			sock.rsize = tmp_resource_len;
			sock.callback = &spotify_token_processor,
			sock.arg = (void *)tmp_ptr;

			client_state = CLIENT_EXEC;

		case CLIENT_EXEC:
			if (SUBSTATE(*state->nx_state) == ESP8S_CONNECT_TCP)
				*state->nx_state = MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT_SSL);

			fsm_client(state, &sock);

			if(SUPERSTATE(*state->nx_state) == ESP8SS_READY && \
				*spotify_token > ' ') {
				client_state = CLIENT_CONF;
				client_id = SPOTIFY_PLAYER;
				*state->nx_state = MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT_SSL);
			}
		}
		break;

	case SPOTIFY_PLAYER:
		switch(client_state) {
		case CLIENT_CONF:
		
			size = snprintf(tmp_resource, TMP_RESOURCE_SIZE,\
					SPOTIFY_GET_PLAYER SPOTIFY_API_HEAD, spotify_token);

			if(size < 0 || size > TMP_RESOURCE_SIZE) {
				client_state = CLIENT_CONF;
				client_id = LOCATION;
				*state->nx_state = MKSTATE(ESP8SS_READY, 0);
				break;
			}
		
			if(snprintf(tmp_resource_len, 4, "%d", size) < 0) {
				client_state = CLIENT_CONF;
				client_id = LOCATION;
				*state->nx_state = MKSTATE(ESP8SS_READY, 0);
				break;
			}

			sock.link = 0,
			sock.domain_port = SPOTIFY_API,
			sock.dsize = SPOTIFY_API_LEN,
			sock.request = tmp_resource,
			sock.rsize = tmp_resource_len,
			sock.callback = &spotify_track_processor,
			sock.arg = NULL,

			client_state = CLIENT_EXEC;

		case CLIENT_EXEC:
			if(SUBSTATE(*state->nx_state) == ESP8S_CONNECT_TCP)
				*state->nx_state = MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT_SSL);

			fsm_client(state, &sock);

			if (SUPERSTATE(*state->nx_state) == ESP8SS_READY) {
				if (esp8_status.http == HTTP_401) {
					client_state = CLIENT_CONF;
					// When the Token is expired a renewal is asked
					// using the refreshing token.
					spotify_code = snprintf(spotify_auth_content,\
									SPOTIFY_AUTH_CONTENT_SIZE,\
									SPOTIFY_REFRESH_CONTENT, spotify_rtoken);
				
					if (spotify_code < 0 ||\
						spotify_code > SPOTIFY_AUTH_CONTENT_SIZE)
					{
						memset(spotify_auth_content, 0,\
								SPOTIFY_AUTH_CONTENT_SIZE);
						client_id = LOCATION;
						break;
					}

					client_id = SPOTIFY_AUTH;
					*state->nx_state = MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT_SSL);
				}
			}
		}
		// break;
    }   

}

