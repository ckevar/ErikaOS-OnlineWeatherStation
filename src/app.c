#include "esp8266_network.h"
#include "esp8266_settings.h"
#include "esp8266_server.h"
#include "esp8266_client.h"
#include "esp8266_driver.h"

#include <string.h>
#include <stdio.h>

#include "web_app.h"
#include "state.h"

#include "openweather.h"
#include "ipapi_json.h"

#include "WidgetConfig.h"



static char OWAPI_HTTP_MSG2REQ[250];
static char OWAPI_HTTP_MSG2REQ_LEN_STR[OWAPI_GET_RESOURCE_STR_LEN+1];

void mkHTMLx(const char icontent, const char status) {
	/* Head */
	webAppOptions.content_type = HTTP_CONTENT_TYPE_TEXT_HTML;
	webAppOptions.status = status;
	webAppOptions.connection = HTTP_CONN_CLOSE;	

	/* Content */
	webAppOptions.content = icontent;

	mkHTTP(&webAppOptions);
}

void app_http_from_WebApp(uint8_t *success, char *http,  void *arg) {
    struct Socket *sock = (struct Socket *) arg;
    SSIDnPSWD_t *snp = (SSIDnPSWD_t *) sock->arg;

	if (memcmp(http, "/\0", 2) == 0) {
		// MAIN PAGE ("index") //
		// Clean requested resource
		*http = 0; 

		mkHTMLx(WEBAPP_INDEX, HTTP_OK);
        sock->rsize = webAppOptions.http_len_str;
		esp8266_load_html(webAppOptions.http, webAppOptions.http_len);
        *success = 1;

	} else if (memcmp(http, WEBAPP_FAVICON_STR, WEBAPP_FAVICON_LEN) == 0) {
		// Icon asked from the browser //
		// Clean requested resources
		memset(http, '\0', WEBAPP_FAVICON_LEN);

		mkHTMLx(WEBAPP_NOT_FOUND, HTTP_NOT_FOUND);
        sock->rsize = webAppOptions.http_len_str;
	    esp8266_load_html(webAppOptions.http, webAppOptions.http_len);
        *success = 1;
		
	} else if (memcmp(http, WEBAPP_SETWiFi_STR, WEBAPP_SETWiFi_LEN) == 0) {
		/* Submitted SSID and password for tne new Access Point to connect to */
		// Clean posted resources
		memset(http, '\0', WEBAPP_SETWiFi_LEN);
		char i = WEBAPP_SETWiFi_LEN;

		mkHTMLx(WEBAPP_ALLDONE, HTTP_OK);
		sock->rsize = webAppOptions.http_len_str;
		esp8266_load_html(webAppOptions.http, webAppOptions.http_len);
		*success = 1;

		// Fast cleaning of the SSID and Password buffer
		snp->size = 0;
		snp->ssidNpassword[0] = 0;

		// Parsing ssid and password
		if(memcmp(http + i, WEBAPP_SSID_STR, WEBAPP_SSID_LEN) == 0) {
			i += WEBAPP_SSID_LEN;

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

			if (memcmp(http + i, WEBAPP_PSWD_STR, WEBAPP_PSWD_LEN) == 0) {
				i += WEBAPP_PSWD_LEN;
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



static void IPAPI_process_result(uint8_t *success, char *tmp, void *arg) {	
	uint16_t msg_size;
	char *IPAPI_VALS[IPAPI_JSON_MEMBERS];
	unsigned short IPAPI_VALS_LEN[IPAPI_JSON_MEMBERS];
	char *ow_http = OWAPI_HTTP_MSG2REQ;
    
	if (IPAPI_get_location_PtrLen(tmp, IPAPI_VALS, IPAPI_VALS_LEN)) {
        *success = 1;
        return;
    }
		
    /* Show information on LCD */
	*(IPAPI_VALS[IPAPI_JSON_CITY_Idx] + IPAPI_VALS_LEN[IPAPI_JSON_CITY_Idx] - 1) = 0; // clear the last '"'
	IPAPI_VALS[IPAPI_JSON_CITY_Idx]++; 							  // skip the first '"'
	UI_writeCity(IPAPI_VALS[IPAPI_JSON_CITY_Idx]);
	UI_LocationAvailable();

	// Clear memory
	memset(ow_http, '\0', 250);
		
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

	msg_size = ow_http - OWAPI_HTTP_MSG2REQ;
	sprintf(OWAPI_HTTP_MSG2REQ_LEN_STR, "%d", msg_size);

	*success = 0;
}

static void OWAPI_process_result(uint8_t *success, char *tmp, void *arg)
{
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

enum AppServerState {
	SERVER_CONF,
	SERVER_RUNNING,
};

void server_function(struct StateS *s) {
    static struct Socket socket;
    static SSIDnPSWD_t wifi_credentials;
	static enum AppServerState server_state = SERVER_CONF;

	switch(server_state){
	case SERVER_CONF:
		socket.callback = &app_http_from_WebApp;
		socket.arg = (void *)&wifi_credentials;
		server_state = SERVER_RUNNING;
		esp8_status.wifi = WiFi_NO_CONNECTED;
		break;
	}

	fsm_server(s, &socket);

	if (wifi_credentials.size > 0 && SUBSTATE(*s->state) == ESP8S_LISTENING) {
		fsm_station_credentials(s, &wifi_credentials);
	}

}

enum AppClientState {
	CLIENT0_CONF,
	CLIENT0_EXEC,
	CLIENT1_CONF,
	CLIENT1_EXEC
};

void client_function(struct StateS *s)  {

    static enum AppClientState client_state;
    static struct Socket socket0;

    switch(client_state) {
    case CLIENT0_CONF:
        UI_LocationUnavailable();
        socket0.link = 0,
        socket0.domain_port = IPAPI_JSON_DNS_PORT,
        socket0.dsize = IPAPI_JSON_DNS_PORT_LEN,
        socket0.request = IPAPI_GET_RESOURCE,
        socket0.rsize = IPAPI_GET_RESOURCE_LEN,
        socket0.callback = &IPAPI_process_result,
        socket0.arg = NULL,
		client_state = CLIENT0_EXEC;

	case CLIENT0_EXEC:
        fsm_client(s, &socket0);

        if (SUPERSTATE(*s->nx_state) == ESP8SS_READY) {
            client_state = CLIENT1_CONF;
            *s->nx_state = MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT);
			UI_LocationAvailable();
        }
        
		break;

    case CLIENT1_CONF:
        socket0.link = 1;
        socket0.domain_port = OWAPI_DNS_PORT;
        socket0.dsize = OWAPI_DNS_PORT_LEN;
        socket0.request = OWAPI_HTTP_MSG2REQ;
        socket0.rsize = OWAPI_HTTP_MSG2REQ_LEN_STR;
        socket0.callback = &OWAPI_process_result,
		client_state = CLIENT1_EXEC;

	case CLIENT1_EXEC:
        fsm_client(s, &socket0);

        if(SUPERSTATE(*s->nx_state) == ESP8SS_READY)
            client_state = CLIENT0_CONF;
    }   

}
