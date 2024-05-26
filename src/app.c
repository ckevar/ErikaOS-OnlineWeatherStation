#include <string.h>
#include <stdlib.h>

#include "state.h"
#include "esp8266_driver.h"
#include "esp8266_network.h"
#include "esp8266_settings.h"
#include "esp8266_netstat.h"
#include "esp8266_client.h"
#include "esp8266_link.h"
#include "esp8266_server.h"
#include "ipapi_json.h"
#include "openweather.h"
#include "json_parser.h"

#include "app.h"
#include "web_app.h"
#include "WidgetConfig.h"

// Temp header
#include "lcd_log.h"
#include "stm32f4_discovery.h"

#define TIMEOUT_ON_WAITING                  128

WebAppBuilder_t webAppOptions;

static char OWAPI_HTTP_MSG2REQ[250];
static char OWAPI_HTTP_MSG2REQ_LEN_STR[OWAPI_GET_RESOURCE_STR_LEN+1];
static unsigned short OWAPI_HTTP_MSG2REQ_LEN = 0;
static char INTERNAL_EVENT_UPDATE = 0;
static char APP_FSM_SUPER_STATE = 0;


static void IPAPI_process_result(uint8_t *success, char *tmp, void *arg) {	
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

	OWAPI_HTTP_MSG2REQ_LEN = ow_http - OWAPI_HTTP_MSG2REQ;
	sprintf(OWAPI_HTTP_MSG2REQ_LEN_STR, "%d", OWAPI_HTTP_MSG2REQ_LEN);

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

/*
 * After each AT command sent to the ESP8266, it replies with an OK
 * so the APP FSM is held until an 'OK' reply is given back. Sometimes 
 * other replies are considered, such as: '>', '+IPD', etc.
 */

static uint16_t LUT_onOK(struct StateS *s) {
    enum ESP8NetManagerState supers;
    supers = SUPERSTATE(*s->state);

	switch (supers) {
    case ESP8SS_INITIAL_SETUP:
        return LUT_OK_powerup(SUBSTATE(*s->state));

    case ESP8SS_NETSTATUS:
        if(SUBSTATE(*s->state) == ESP8S_NETSTAT)
            return LUT_OK_netstat(SUPERSTATE(*s->state));

        return MKSTATE(ESP8SS_ON_HOLD, 0);
    
    case ESP8SS_CLIENT:
        return LUT_OK_client(SUBSTATE(*s->state));
	
	/***** settings *****/
    case ESP8SS_AP:
        return LUT_OK_access_point(SUBSTATE(*s->state));

    case ESP8SS_SERVER:
        return LUT_OK_server(SUBSTATE(*s->state));

	case ESP8SS_STATION_CREDENTIALS:
		esp8_status.wifi = WiFi_CONNECTED;
		return LUT_OK_station_credentials();
	/*
    case APP_FSM_SHUTDOWN_WEBSERVER:
	    return MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_STATION_MODE);
	*/
	/********************/
	}
}


/* 
 * ESP8266 replies the '>' character when a CIPSEND command is sent and 
 * and tells the STM that it's ready to receive the http content (or data)
 * to be transmitted.
 */ 

/* 
 * Processes arrival data from the APIs 
 */
/*
 * Processes requested or submitted data on WebPage
 */
void mkHTMLx(const char icontent, const char status) {
	/* Head */
	webAppOptions.content_type = HTTP_CONTENT_TYPE_TEXT_HTML;
	webAppOptions.status = status;
	webAppOptions.connection = HTTP_CONN_CLOSE;	

	/* Content */
	webAppOptions.content = icontent;

	mkHTTP(&webAppOptions);
}
// static void app_http_from_WebApp(char *arriving_http, char link_id, short *curr_state, SSIDnPSWD_t *snp)
void app_http_from_WebApp(uint8_t *success, char *http,  void *arg) {
    struct Socket *sock = (struct Socket *) arg;
    SSIDnPSWD_t *snp = (SSIDnPSWD_t *) sock->arg;

	if (memcmp(http, "/\0", 2) == 0) {
		/* MAIN PAGE ("index") */
		// Clean requested resource
		*http = 0; 

		mkHTMLx(WEBAPP_INDEX, HTTP_OK);
        sock->rsize = webAppOptions.http_len_str;
		esp8266_load_html(webAppOptions.http, webAppOptions.http_len);
        *success = 1;

	} else if (memcmp(http, WEBAPP_FAVICON_STR, WEBAPP_FAVICON_LEN) == 0) {
		/* Icon asked from the browser */
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

/*
 * Function to process the incoming requested or arrival HTTP data 
 */

/*
 * This is called by a another Taks that will restart the APP FSM to 
 * update the weather info.
 */
void app_fsm_restart(void) {
	INTERNAL_EVENT_UPDATE = 1;
}

static uint16_t fsm_on_http_close(uint16_t *prev_state, char *wifi) {
    enum ESP8NetManagerState supers = SUPERSTATE(*prev_state);

    switch(supers) {
    case ESP8SS_CLIENT:
        switch(SUBSTATE(*prev_state)) {
        case ESP8S_CLOSE:
            return MKSTATE(ESP8SS_ON_HOLD, 0);
        }
    case ESP8SS_SERVER:
    case ESP8SS_NETSTATUS:
	case ESP8SS_STATION_CREDENTIALS:
        return MKSTATE(ESP8SS_ON_HOLD, 0);
    }
    /*
    switch(*prev_state) {
        case APP_FSM_CLEAN_AP_BUFFER:
            if (*wifi == WiFi_CONNECTED)
                return APP_FSM_SHUTDOWN_WEBSERVER;
            return APP_FSM_WAITING;

        default:
            return APP_FSM_WAITING;
    } 
    */  
}

static uint16_t fsm_on_waiting_state(struct StateS *s) {
    switch(esp8_status.cmd) {
    case ESP8_OK: 
	    esp8_status.cmd = ESP8_UNKNOWN;
		return LUT_onOK(s);

    case ESP8_ERROR:
    case ESP8_FAIL: 
        esp8_status.cmd = ESP8_UNKNOWN;
        return APP_FSM_ERR_FAIL;

    case ESP8_WRAP:
	    esp8_status.cmd = ESP8_UNKNOWN;
	    return esp8266_fsm_prev_OnWrap(*s->state);

    case ESP8_TCP_PULLIN:
        return LUT_link_pullin(SUPERSTATE(*s->state));

    case ESP8_LINK_CLOSED:
	    esp8_status.cmd = ESP8_UNKNOWN;
        return  fsm_on_http_close(s->state, s->wifi_mode);

    case ESP8_IP:
	    esp8_status.cmd = ESP8_UNKNOWN;
	    return on_WiFiStatus(SUBSTATE(*s->state), s->wifi_mode);

    case ESP8_READY:
        esp8_status.cmd = ESP8_UNKNOWN;

		if (SUPERSTATE(*s->state) == ESP8SS_AP)
		    return MKSTATE(ESP8SS_AP, ESP8S_ENABLE_AP);

        // else
        return MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_CHECK_DEV);
    
    default:
        return MKSTATE(ESP8SS_ON_HOLD, 0);
    }

}

static short fsm_on_err_fail(struct StateS *s) {
    enum ESP8NetManagerState supers;

    supers = SUPERSTATE(*s->state);
    
    switch(supers) {

    case ESP8SS_INITIAL_SETUP:
        return LUT_on_err_powerup(SUBSTATE(*s->state));

	case ESP8SS_STATION_CREDENTIALS:
		esp8_status.wifi = WiFi_NO_CONNECTED;
		return LUT_ERR_station_credentials();

    case ESP8SS_CLIENT:
	    return MKSTATE(ESP8SS_NETSTATUS, ESP8S_IFCONFIG);
	
	#ifdef AP_WITH_SERVER
	case ESP8SS_SERVER:
		return MKSTATE(ESP8SS_AP, ESP8S_RESTART_4AP);
	#endif
    
    default:
        return MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART);
    }
}



static short fsm_on_timeout(unsigned short prev_state) {
    enum ESP8NetManagerState supers;
    supers = SUPERSTATE(prev_state);

    switch(supers) {
    case ESP8SS_INITIAL_SETUP:
        return LUT_timeout_powerup(SUBSTATE(prev_state));

    case ESP8SS_CLIENT:
        return MKSTATE(ESP8SS_NETSTATUS, ESP8S_CHECK_DEV);
    
    case ESP8SS_SERVER:
	case ESP8SS_AP:
	case ESP8SS_STATION_CREDENTIALS:
        return MKSTATE(ESP8SS_ON_HOLD, 0);

    default:
        return MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART);
    }
}

/*
 * Finiste-State Machine, this evaluates external events, ESP8266 events
 * (replies) in order to get the weather info and/or set the configurations
 * to connect with an Access Point.
 */
__attribute__((weak)) void client_function(struct StateS *s)  {
    static uint8_t request;
    struct Socket socket0;

    switch(request) {
    case 0:
        UI_LocationUnavailable();
        socket0.link = 0,
        socket0.domain_port = IPAPI_JSON_DNS_PORT,
        socket0.dsize = IPAPI_JSON_DNS_PORT_LEN,
        socket0.request = IPAPI_GET_RESOURCE,
        socket0.rsize = IPAPI_GET_RESOURCE_LEN,
        socket0.callback = &IPAPI_process_result,
        socket0.arg = NULL,
        fsm_client(s, &socket0);

        if (SUPERSTATE(*s->nx_state) == ESP8SS_READY) {
            request++;
            *s->nx_state = MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT);
        }
        break;
    case 1:
        socket0.link = 1;
        socket0.domain_port = OWAPI_DNS_PORT;
        socket0.dsize = OWAPI_DNS_PORT_LEN;
        socket0.request = OWAPI_HTTP_MSG2REQ;
        socket0.rsize = OWAPI_HTTP_MSG2REQ_LEN_STR;
        socket0.callback = &OWAPI_process_result,
        fsm_client(s, &socket0);

        if(SUPERSTATE(*s->nx_state) == ESP8SS_READY)
            request = 0;
    }   
}



enum AppServerState {
	SERVER_START,
	SERVER_RUNNING,
};


__attribute__((weak)) void server_function(struct StateS *s) {
    static struct Socket socket;
    static SSIDnPSWD_t wifi_credentials;
	static enum AppServerState server_state = SERVER_START;
    

	switch(server_state){
	case SERVER_START:
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

void app_fsm_app(void) {
	static short nx_state = MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_CHECK_DEV);
	static short state = MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_CHECK_DEV);
    static char wifi_status = WiFi_NO_CONNECTED;
    static uint8_t timeout_waiting;
    static struct StateS nu_state;
    enum ESP8NetManagerState supers;
    /* SSID AND PSW for ESP */
	static SSIDnPSWD_t ssidNpswd;

    nu_state.nx_state = &nx_state;
    nu_state.state = &state;
    nu_state.wifi_mode = &wifi_status;
    nu_state.timeout = &timeout_waiting;
	
	/**** CHECK EVENTS (Screen touched?) ****/
	// if(IsEvent(RESET_ESP8266_EVNT)) {
	// 	nx_state = ESP8S_CHECK_DEV;
	// 	state = ESP8S_CHECK_DEV;
	// 	ClearEvents();

	// } else 
	if (IsEvent(SET_AP_ESP8266_EVNT)) {
        nx_state = MKSTATE(ESP8SS_AP, 0);
		state =  MKSTATE(ESP8SS_AP, 0);
		ClearEvents();
	}
	if	(INTERNAL_EVENT_UPDATE &&\
		(SUPERSTATE(state) != ESP8SS_AP) &&\
        (SUPERSTATE(state) != ESP8SS_SERVER) &&\
		(SUPERSTATE(state) != ESP8SS_STATION_CREDENTIALS))
	{
		INTERNAL_EVENT_UPDATE = 0;
        nx_state = MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT);
		state =  MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT);
	}
	/****************************************/
    supers = SUPERSTATE(*nu_state.nx_state);
	switch (supers) {
      
        case ESP8SS_INITIAL_SETUP:
            fsm_powerup(&nu_state);
            break;

        case ESP8SS_NETSTATUS:
            fsm_netstat(&nu_state);
            break;

        case ESP8SS_CLIENT:
            client_function(&nu_state);
            break;
        
        case ESP8SS_READY:
            UI_WriteState("READY");
            timeout_waiting = 0;
            break;
        
        case ESP8SS_AP:
            fsm_ap_config(&nu_state);
            break;
        
        case ESP8SS_SERVER:
            server_function(&nu_state);
            break;
		
        case ESP8SS_ON_HOLD:
            nx_state = fsm_on_waiting_state(&nu_state);
            
            timeout_waiting++;
            if (timeout_waiting == TIMEOUT_ON_WAITING) {
                timeout_waiting = 0;
                nx_state = fsm_on_timeout(state);
            }

			break;

        case ESP8SS_ERROR:
		case APP_FSM_ERR_FAIL:
			UI_set_err_progress(1, 1);
            nx_state = fsm_on_err_fail(&nu_state);
			break;

	}

}


