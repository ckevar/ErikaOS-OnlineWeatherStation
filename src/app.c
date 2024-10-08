#include "network.h"
#include "esp8266_settings.h"
#include "esp8266_server.h"
#include "esp8266_client.h"
#include "esp8266_driver.h"

#include <string.h>
#include <stdio.h>

#include "state.h"
#include "wifi_supplicant.h"

#include "openweather.h"
#include "ipapi_json.h"
#include "spotify.h"

#include "WidgetConfig.h"

#define MATCH(str, res)			if(0 == memcmp(str, res, res##_LEN))

#define SPOTIFY_UPDATE_EVENT		0b001
#define WEATHER_UPDATE_EVENT		0b010
#define WEATHER_UPDATE_EVENT_CORE	0b100

#define SPOTIFY_AUTH_EMPTY			0
#define SPOTIFY_AUTH_NON_EMPTY		' '

static char		spotify_auth_content[SPOTIFY_AUTH_CONTENT_SIZE];
static int16_t	spotify_code;
static uint8_t	internal_events = 0;
static char		timezone[7];

char *bind_http_esp8266(struct outHTTP *out) {
	static char size_str[] = "\0\0\0\0";
	uint16_t size = out->eof - out->data - out->free_space;

	sprintf(size_str, "%d", size);
	esp8266_load_html(out->data, size);
	return size_str;
}

static void app_spotify_conf(uint8_t *success, char *http, void *arg) {

	struct Socket *sock = (struct Socket *) arg;
	char *code;
	struct outHTTP out;
	uint16_t size;
	
	outHTTPv11_start(&out);

	MATCH(http, SPOTY_REQ_CALLBACK) {
		memset(http, 0, SPOTY_REQ_CALLBACK_LEN);
		http += SPOTY_REQ_CALLBACK_LEN;

		outHTTP_basice_header(&out, HTTP_200);
		outHTTP_body(&out, "", 0);
		
		sock->rsize = bind_http_esp8266(&out);
		
		/* copy code */
		code = (char *)sock->arg;
		while(*http) {
			*code = *http;
			*http = 0; 
			http++; code++;
			spotify_code++;
		}

		*success = 1;
		return;
	}

	MATCH(http, SPOTY_REQ) {
		memset(http, 0, SPOTY_REQ_LEN);
		
		if(0 == spotify_on_root(&out, ESP8266_IPv4.ip)) {
			*success = 0;
			return;
		}

		sock->rsize = bind_http_esp8266(&out);

		*success = 1;
		return;
	
	}

	*success = 0;
}

void app_http_from_WebApp(uint8_t *success, char *http,  void *arg) {
    struct Socket *sock = (struct Socket *) arg;
    SSIDnPSWD_t *snp = (SSIDnPSWD_t *) sock->arg;
	struct outHTTP out;

	outHTTPv11_start(&out);

	MATCH(http, WRES_INDEX) {	
		*http = 0; 
		
		wifi_supplicant_http(&out, HTTP_200, WEBAPP_INDEX);
		sock->rsize = bind_http_esp8266(&out);

        *success = 1;
		return;

	} 
	MATCH(http, WRES_FAVICON) {
		// /favicon
		memset(http, '\0', WRES_FAVICON_LEN);

		wifi_supplicant_http(&out, HTTP_404, WEBAPP_NOT_FOUND);
		sock->rsize = bind_http_esp8266(&out);

        *success = 1;
		return;
		
	}
	MATCH(http, WRES_SETWiFi) {
		// /set_wifi
		memset(http, '\0', WRES_SETWiFi_LEN);
		char i = WRES_SETWiFi_LEN;

		wifi_supplicant_http(&out, HTTP_200, WEBAPP_ALLDONE);
		sock->rsize = bind_http_esp8266(&out);
		
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
				snp->ssidNpassword[snp->size] = ('+' == http[i]) \
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
				while(http[i] != '\r') {
					snp->ssidNpassword[snp->size] = http[i];
					i++;
					snp->size++;
				}
				snp->ssidNpassword[snp->size] = '\"';
				snp->size++;
				snp->ssidNpassword[snp->size] = 0;
			}

		}
		return;
	}
}

#define iOW_STR				0
#define iOW_LEN				1
#define TMP_RESOURCE_SIZE	700

static void IPAPI_process_result(uint8_t *success, char *json, void *arg) {	
	uint16_t msg_size;
	char *IPAPI_VALS[IPAPI_JSON_MEMBERS];
	unsigned short IPAPI_VALS_LEN[IPAPI_JSON_MEMBERS];
	char **ow_resource = (char **)arg;
	char *ow_http = ow_resource[iOW_STR];
    
	if (IPAPI_get_location_PtrLen(json, IPAPI_VALS, IPAPI_VALS_LEN)) {
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

static void OWAPI_process_result(uint8_t *success, char *json, void *arg) {
	char *weather[OWAPI_PARAMS_COUNT];
	unsigned short sizes[OWAPI_PARAMS_COUNT];
    
	if(OWAPI_get_weather(json, weather, sizes)) {
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
	memcpy(timezone, weather[iOWAPI_TIMEZONE], sizes[iOWAPI_TIMEZONE]);
    UI_setTime(timezone, weather[iOWAPI_TIME]);

	*success = 0;
}

static void spotify_token_processor(uint8_t *success, char *json, void *arg) {
	char *tokens_ptr[SPOTIFY_TOKEN_COUNT];
	uint16_t sizes[SPOTIFY_TOKEN_COUNT];
	char **token = (char **)arg;

	if(spotify_get_token(json, tokens_ptr, sizes)) {
		*success = 1;
		return;
	}

	memcpy(token[iSPOTIFY_TOKEN],\
			tokens_ptr[iSPOTIFY_TOKEN] + 1,\
			sizes[iSPOTIFY_TOKEN] - 2);

	if(sizes[iSPOTIFY_RTOKEN] > 0) {
		memcpy(token[iSPOTIFY_RTOKEN],\
				tokens_ptr[iSPOTIFY_RTOKEN] + 1,\
				sizes[iSPOTIFY_RTOKEN] - 2);
	}

	*success = 0;
}

#define TRACK_INFO_SIZE	38

static void spotify_track_processor(uint8_t *success, char *json, void *arg) {
	char *track_ptr[SPOTIFY_TRACK_COUNT];
	uint16_t sizes[SPOTIFY_TRACK_COUNT];
	char track_info[TRACK_INFO_SIZE];

	if (HTTP_204 == esp8_status.http) {
		*success = 0; 
		UI_set_track("Spotify Player off");
		return;
	}
	*success = spotify_get_track(json, track_ptr, sizes);
	if(*success) {
		*success = 1;
		return;
	}
	
	*(track_ptr[iSPOTIFY_SONG] + sizes[iSPOTIFY_SONG]) = 0;
	*(track_ptr[iSPOTIFY_ARTIST] + sizes[iSPOTIFY_ARTIST]) = 0;
	*(track_ptr[iSPOTIFY_PROGRESS] + sizes[iSPOTIFY_PROGRESS]) = 0;
	*(track_ptr[iSPOTIFY_DURATION] + sizes[iSPOTIFY_DURATION]) = 0;
	*(track_ptr[iSPOTIFY_TIME] + 10) = 0;

	UI_set_track_progress(track_ptr[iSPOTIFY_PROGRESS], track_ptr[iSPOTIFY_DURATION]);

	sizes[iSPOTIFY_SONG] = snprintf(track_info, TRACK_INFO_SIZE, "%s:%s",\
			track_ptr[iSPOTIFY_ARTIST], track_ptr[iSPOTIFY_SONG]);
	
	if(sizes[iSPOTIFY_SONG] > TRACK_INFO_SIZE)
		track_info[TRACK_INFO_SIZE - 1] = 0;

	UI_set_track(track_info);
	UI_setTime(timezone, track_ptr[iSPOTIFY_TIME]);

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

// void server_function(struct Network *s, enum ServersID _server_id) {
void server_function(struct Network *s) {
    static struct Socket socket;
    static SSIDnPSWD_t wifi_credentials;
	static enum AppServerState server_state = SERVER_CONF;
	static enum ServersID server_id = WIFI_SUPPLICANT;

	if(s->server_id != server_id) {
		server_id = s->server_id;
		server_state = SERVER_CONF;
	}
	
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

		if ((wifi_credentials.size > 0) && (ESP8S_LISTENING == SUBSTATE(s->state)))
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
			*(spotify_auth_content + SPOTIFY_AUTH_RANDOM_POS) = SPOTIFY_AUTH_EMPTY;
			break;
		}
		
		// case SERVER_RUNNING:
		fsm_server(s, &socket);

		if((spotify_auth_content[SPOTIFY_AUTH_RANDOM_POS] > SPOTIFY_AUTH_NON_EMPTY) && \
		   (ESP8S_LISTENING == SUBSTATE(s->state)))
		{
			*s->nx_state = MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART); 
		}

	}

	if (ESP8S_SERVER_OFF == SUBSTATE(s->state))
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
	AUTOMATIC,
};

void client_function(struct Network *state)  {
    static enum AppClientState client_state = CLIENT_CONF;
	static enum ClientIDs client_id;
    static struct Socket sock;
	static char tmp_resource[TMP_RESOURCE_SIZE];
	static char tmp_resource_len[OWAPI_GET_RESOURCE_STR_LEN + 1];
	static char *tmp_ptr[2];
	static char spotify_token[SPOTIFY_TOKEN_SIZE];
	static char spotify_rtoken[SPOTIFY_RTOKEN_SIZE];
	int16_t size;

	if(state->client_id != AUTOMATIC) {
		client_id = state->client_id;
		state->client_id = AUTOMATIC;
		client_state = CLIENT_CONF;
	}

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

			if (ESP8SS_READY == SUPERSTATE(*state->nx_state)) {
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
		
			if((ESP8SS_READY == SUPERSTATE(*state->nx_state)) ||
			   (HTTP_401 == esp8_status.http))
			{
				if (*spotify_token > ' ') {
					client_id = SPOTIFY_PLAYER;
					*state->nx_state = MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT_SSL);

				} else if (*(spotify_auth_content + SPOTIFY_AUTH_RANDOM_POS) > SPOTIFY_AUTH_NON_EMPTY) {
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
			if(*spotify_rtoken < ' ')
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
			if (ESP8S_CONNECT_TCP == SUBSTATE(*state->nx_state))
				*state->nx_state = MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT_SSL);

			if (esp8_status.http > HTTP_500) {
				*state->nx_state = MKSTATE(ESP8SS_CLIENT, ESP8S_CLOSE);
				UI_set_track("Token failed");
			}

			fsm_client(state, &sock);

			if(ESP8SS_READY == SUPERSTATE(*state->nx_state)) {
				client_state = CLIENT_CONF;
				if (*spotify_token > ' ') {
					client_id = SPOTIFY_PLAYER;
					*state->nx_state = MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT_SSL);
				} else {
					client_id = LOCATION;
				}
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
			if(ESP8S_CONNECT_TCP == SUBSTATE(*state->nx_state))
				*state->nx_state = MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT_SSL);
			
			if(esp8_status.http > HTTP_500) {
				*state->nx_state = MKSTATE(ESP8SS_CLIENT, ESP8S_CLOSE);
				esp8_status.http = HTTP_XXX;
			}

			fsm_client(state, &sock);

			if (HTTP_401 == esp8_status.http) {
				client_state = CLIENT_CONF;
				// When the Token is expired a renewal is asked
				// using the refreshing token.
				spotify_code = snprintf(spotify_auth_content,\
								SPOTIFY_AUTH_CONTENT_SIZE,\
								SPOTIFY_REFRESH_CONTENT, spotify_rtoken);
				
				if (spotify_code < 0 ||\
					spotify_code > SPOTIFY_AUTH_CONTENT_SIZE)
				{
					memset(spotify_auth_content, SPOTIFY_AUTH_EMPTY,\
							SPOTIFY_AUTH_CONTENT_SIZE);
					client_id = LOCATION;
					break;
				}

				client_id = SPOTIFY_AUTH;
				*state->nx_state = MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT_SSL);
			}
			else if ((HTTP_200 == esp8_status.http) || (HTTP_204 == esp8_status.http)) {
				if(ESP8S_CLOSE == SUBSTATE(*state->nx_state)) {
					*state->nx_state = MKSTATE(ESP8SS_READY, 0);
				}
			}
		}
		// break;
    }   

}

/***** Event Handler *****/


void NetEventHandler(struct Network *s) {
	if (IsEvent(SPOTIFY_CONF_EVENT)) {
		*s->nx_state = MKSTATE(ESP8SS_SERVER, 0);
		s->state = *s->nx_state;
		s->server_id = SPOTIFY_CODE;
		ClearEvents();
		return;
	}

	if (IsEvent(SET_AP_ESP8266_EVNT)) {
        *s->nx_state = MKSTATE(ESP8SS_AP, 0);
		s->state =  *s->nx_state;
		s->server_id = WIFI_SUPPLICANT;
		ClearEvents();
		return;
	}
	
	if	((internal_events) &&
		(SUPERSTATE(s->state) != ESP8SS_AP) &&
        (SUPERSTATE(s->state) != ESP8SS_SERVER) &&
		(SUPERSTATE(s->state) != ESP8SS_STATION_CREDENTIALS) &&
		(ESP8SS_READY == SUPERSTATE(*s->nx_state))) 
	{
		if (internal_events & WEATHER_UPDATE_EVENT_CORE) {
			internal_events &= ~WEATHER_UPDATE_EVENT_CORE;
			*s->nx_state = MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT_TCP);
			s->client_id = LOCATION;

		} else if (internal_events & WEATHER_UPDATE_EVENT) {
			if (*spotify_auth_content > SPOTIFY_AUTH_NON_EMPTY) {
				*s->nx_state = MKSTATE(ESP8SS_CLIENT, ESP8S_CLOSE);
			}
			internal_events &= ~WEATHER_UPDATE_EVENT;
			internal_events = WEATHER_UPDATE_EVENT_CORE;

		} else if(internal_events & SPOTIFY_UPDATE_EVENT) {
			if(SPOTIFY_AUTH_EMPTY == *spotify_auth_content)
				return;
			
			internal_events &= ~SPOTIFY_UPDATE_EVENT;
			*s->nx_state = MKSTATE(ESP8SS_CLIENT, ESP8S_RMALLOC);
			s->client_id = SPOTIFY;

		}
	
		s->state = *s->nx_state;
	}

}

/*
 * This is called by other Tasks that will restart the APP FSM to 
 * update the weather info.
 */
void spotify_update_player(void) {
	internal_events |= SPOTIFY_UPDATE_EVENT;
}

void weather_update(void) {
	internal_events |= WEATHER_UPDATE_EVENT;
}

