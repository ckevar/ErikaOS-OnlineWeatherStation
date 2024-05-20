#include <string.h>
#include <stdlib.h>

#include "state.h"
#include "esp8266_driver.h"
#include "esp8266_network.h"
#include "esp8266_powerup.h"
#include "esp8266_netstat.h"
#include "esp8266_client.h"
#include "esp8266_link.h"
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

/*
#define update_state(curr_state, prev_state) \
	esp8_status.cmd = ESP8_UNKNOWN; \
    prev_state = curr_state; \
	curr_state = APP_FSM_WAITING; \
    timeout_waiting = 0
*/
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

        return MKSTATE(APP_FSM_WAITING, 0);
    
    case ESP8SS_CLIENT:
        return LUT_OK_client(SUBSTATE(*s->state));
	
	/***** settings *****/
	case APP_FSM_SET_AP:
		return APP_FSM_SET_WPA;

    case APP_FSM_SET_WPA:
	    return APP_FSM_SET_AP_CIPMUX;

	case APP_FSM_SET_AP_CIPMUX:
	    return APP_FSM_SET_AP_SERVER;
    
    case APP_FSM_SET_AP_SERVER:
        return APP_FSM_WEBAPP_OK_CLIENT0;

	case APP_FSM_WEBAPP_OK_CLIENT1:
	    return APP_FSM_CLEAN_AP_BUFFER;

	case APP_FSM_TRY_NEW_SSID_AND_PASSWORD:
	    return APP_FSM_NEW_SSIDnPSWD_CONNECTED;

    case APP_FSM_SHUTDOWN_WEBSERVER:
	    return MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_STATION_MODE);
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
static void app_http_from_WebApp(char *arriving_http, char link_id, short *prev_state, short *curr_state, SSIDnPSWD_t *snp)
{
	// So far, it'll always be text/html
	webAppOptions.content_type = WEBAPP_CONTENT_TYPE_TEXT_HTML;

	// So far, it'll always be closed
	webAppOptions.connection = WEBAPP_CONN_CLOSE;	

	if (memcmp(arriving_http, "/\0", 2) == 0)
	{
		/* MAIN PAGE ("index") */
		// Clean requested resource
		*arriving_http = 0; 

		// Ack esp8_status.cmd and set next app state
		esp8_status.cmd = ESP8_UNKNOWN;
		*curr_state = APP_FSM_WEBAPP_OK_CLIENT0;

		// Buil HTTP to send back
		webAppOptions.status = WEBAPP_STATUS_OK;
		webAppOptions.content = WEBAPP_CONTENT_INDEX;
		build_HTTP(&webAppOptions);

		// Prepare ESP8266 to send main WEB page 
		esp8266_set_CIPSEND_link(link_id, webAppOptions.http_len_str, webAppOptions.http_len2);

		// Load WEB page into buffer
		esp8266_load_html(webAppOptions.http, webAppOptions.http_len);


	}
	else if (memcmp(arriving_http, WEBAPP_FAVICON_STR, WEBAPP_FAVICON_LEN) == 0) 
	{
		/* Icon asked from the browser */
		// Clean requested resources
		memset(arriving_http, '\0', WEBAPP_FAVICON_LEN);

		// Acknowledge ESP8266_status and set next app state
		esp8_status.cmd = ESP8_UNKNOWN;
		*curr_state = APP_FSM_WEBAPP_OK_CLIENT0;

		// Build
		webAppOptions.status = WEBAPP_STATUS_NOT_FOUND;
		webAppOptions.content = WEBAPP_CONTENT_NOT_FOUND;
		build_HTTP(&webAppOptions);

		// Prepare ESP8266 to send not found page
		esp8266_set_CIPSEND_link(link_id, webAppOptions.http_len_str, webAppOptions.http_len2);

		// Load not found page into buffer
		esp8266_load_html(webAppOptions.http, webAppOptions.http_len);
		
	} 
	else if (memcmp(arriving_http, WEBAPP_SETWiFi_STR, WEBAPP_SETWiFi_LEN) == 0) 
	{
		/* Submitted SSID and password for tne new Access Point to connect to */
		// Clean posted resources
		memset(arriving_http, '\0', WEBAPP_SETWiFi_LEN);
		char i = WEBAPP_SETWiFi_LEN;

		// Fast cleaning of the SSID and Password buffer
		snp->len = 0;
		snp->ssidNpassword[0] = 0;

		// Parsing ssid and password
		if(memcmp(arriving_http + i, WEBAPP_SSID_STR, WEBAPP_SSID_LEN) == 0) {
			i += WEBAPP_SSID_LEN;

			snp->ssidNpassword[snp->len] = '\"';
			snp->len++;

			// Iterate until 
			while(arriving_http[i] != '&') {
				// Replacing '+'s by ' ' (spaces)
				snp->ssidNpassword[snp->len] = (arriving_http[i] == '+') ? ' ' : arriving_http[i];
				snp->len++;
				i++;
			}
			// Composing <ssid>","<password> 
			memcpy(snp->ssidNpassword + snp->len, "\",\"", 3);
			snp->len += 3;		// Skip '","'
			i++;				// SKip '&'

			if (memcmp(arriving_http + i, WEBAPP_PSWD_STR, WEBAPP_PSWD_LEN) == 0) {
				i += WEBAPP_PSWD_LEN;
				while(arriving_http[i]) {
					snp->ssidNpassword[snp->len] = arriving_http[i];
					i++;
					snp->len++;
				}
				snp->ssidNpassword[snp->len] = '\"';
				snp->len++;
				snp->ssidNpassword[snp->len] = 0;
			}

		}

		snp->link_OnHold = link_id;

		esp8_status.cmd = ESP8_UNKNOWN;
		*curr_state = APP_FSM_TRY_NEW_SSID_AND_PASSWORD;
					
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
            return MKSTATE(APP_FSM_WAITING, 0);
        }
    // case ESP8SS_SERVER:
    case ESP8SS_NETSTATUS:
        return MKSTATE(APP_FSM_WAITING, 0);
    }
    /*
    switch(*prev_state) {
        case APP_FSM_CLEAN_AP_BUFFER:
            if (*wifi == WiFi_CONNECTED)
                return APP_FSM_SHUTDOWN_WEBSERVER;
            return APP_FSM_WAITING;

        case APP_FSM_IPAPI_REQ_LOCATION:
        case APP_FSM_OW_API_REQ_WEATHER:
            if (esp8_status.tcp & TCP_BUFF_FULL)
                return APP_FSM_WAITING;

            return APP_FSM_OW_API_CIPSTART;

        case APP_FSM_OW_API_CIPSTART:
            return APP_FSM_OW_API_CIPSTART;

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

		if (SUBSTATE(*s->state) == APP_FSM_AP_RESTART)
		    return APP_FSM_SET_AP;

        return ESP8S_CHECK_DEV;
    
    default:
        return APP_FSM_WAITING;
    }

}

static short fsm_on_err_fail(struct StateS *s) {
    enum ESP8NetManagerState supers;

    supers = SUPERSTATE(*s->state);
    
    switch(supers) {

    case ESP8SS_INITIAL_SETUP:
        return LUT_on_err_powerup(SUBSTATE(*s->state));

    /*case APP_FSM_TRY_NEW_SSID_AND_PASSWORD:
	    return APP_FSM_TRY_AGAIN_WA_SSID_AND_PASSWORD;
			
    case APP_FSM_TRY_AGAIN_WA_SSID_AND_PASSWORD:
	    return APP_FSM_WAITING;
			
    case APP_FSM_SHUTDOWN_WEBSERVER:
	    return APP_FSM_SHUTDOWN_WEBSERVER;

    case  APP_FSM_WEBAPP_OK_CLIENT1:
	    if (*s->wifi_mode == WiFi_CONNECTED)
		    return APP_FSM_SHUTDOWN_WEBSERVER;

        else if (*s->wifi_mode == WiFi_SETTINGUP)
            return APP_FSM_CLEAN_AP_BUFFER;

    case APP_FSM_IPAPI_CIPSTART:*/
    case ESP8SS_CLIENT:
	    return MKSTATE(ESP8SS_NETSTATUS, ESP8S_IFCONFIG);
    
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

    /*
    case APP_FSM_IPAPI_REQ_LOCATION:        9
    case APP_FSM_IPAPI_CIPSTART:            7
        return MKESP8S_CHECK_DEV;
    */
    case ESP8SS_CLIENT:
        return MKSTATE(ESP8SS_NETSTATUS, ESP8S_CHECK_DEV);
    /*
    case APP_FSM_WEBAPP_OK_CLIENT0:         24
    case APP_FSM_CLEAN_AP_BUFFER:           26
    case APP_FSM_TRY_NEW_SSID_AND_PASSWORD: 27
    case APP_FSM_OW_API_REQ_WEATHER:        13 
    */
        return APP_FSM_WAITING;
        // return MKSTATE(WAITING, 0)

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
        nx_state = MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT);
		state =  MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT);
		ClearEvents();
	}
	if (INTERNAL_EVENT_UPDATE && (APP_FSM_SUPER_STATE != APP_FSM_SUPER_SETTINGS)) {
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

		/************************* SETTINGS FSMs *************************/
        /* Access Point */
		/*case APP_FSM_AP_RESTART:
			// Restarts the ESP8266
			UI_WriteState("Restarting...");
			esp8266_restart();
			wifi_status = WiFi_SETTINGUP;
			UI_clear_progress();
			UI_SettingsOn();
			// UI_set_progress(nx_state - APP_FSM_IDLE,\
			//				APP_FSM_SHUTDOWN_WEBSERVER - APP_FSM_IDLE);
			update_state(nx_state, state);
			break;

		case APP_FSM_SET_AP:
			// Sets ESP8266 as station mode and as Access Point
			UI_clear_progress();
			UI_WriteState("Enabling WiFi");
			esp8266_set_CWMODE(ESP8266_CWMODE_STATION_N_SOFTAP);
			// UI_set_progress(nx_state - APP_FSM_IDLE,\
			//				APP_FSM_SHUTDOWN_WEBSERVER - APP_FSM_IDLE);
			update_state(nx_state, state);
			break;

		case APP_FSM_SET_WPA:
			// Sets the ESP8266 Access Point SSID and Password
			UI_WriteState("Configurations on WiFi");
			esp8266_set_CWSAP(APP_AP_CONFIGURATION, APP_AP_CONFIGURATION_LEN);
            // UI_set_progress(nx_state - APP_FSM_IDLE,\
			//				APP_FSM_SHUTDOWN_WEBSERVER - APP_FSM_IDLE);
			update_state(nx_state, state);
			break;
        */
        /* Server */
		case APP_FSM_SET_AP_CIPMUX:
			// Sends to allow multiplce connection on the ESP8266
			UI_WriteState("Enabling multiple connection");
			esp8266_set_CIPMUX(ESP8266_CIPMUX_MULTI_CON);
            /*
			UI_set_progress(nx_state - APP_FSM_IDLE,\
							APP_FSM_SHUTDOWN_WEBSERVER - APP_FSM_IDLE);
            */
			update_state(nx_state, state);
			break;


		case APP_FSM_SET_AP_SERVER:
			// Asks the ESP8266 to create a webserver at port 80
			UI_WriteState("Enabling web server");
			esp8266_clean_link_buff(0);
			esp8266_enable_HTTPServer_P80();
			/*
            UI_set_progress(nx_state - APP_FSM_IDLE,\
							APP_FSM_SHUTDOWN_WEBSERVER - APP_FSM_IDLE);
            */
			update_state(nx_state, state);
			esp8_status.tcp = ESP8_UNKNOWN;
			break;

		case APP_FSM_WEBAPP_OK_CLIENT0:
			// Idle state waiting for clients to request or submit 
			// HTTP information on the webserver
			UI_WriteState("Waiting for connections");
			/*
            UI_set_progress(nx_state - APP_FSM_IDLE,\
							APP_FSM_SHUTDOWN_WEBSERVER - APP_FSM_IDLE);
            */
			state = nx_state;
			nx_state = APP_FSM_WAITING;
			break;

		case APP_FSM_WEBAPP_OK_CLIENT1:
			// Sends the requested HTML
			UI_WriteState("Replying");
			esp8266_send_html();
            /*
			UI_set_progress(nx_state - APP_FSM_IDLE,\
							APP_FSM_SHUTDOWN_WEBSERVER - APP_FSM_IDLE);
            */
			esp8_status.tcp = ESP8_UNKNOWN;
			update_state(nx_state, state);
			break;

		case APP_FSM_CLEAN_AP_BUFFER:
			// Idle state to get out, i think it's useless 
			UI_WriteState("Transition state");
            /*
			UI_set_progress(nx_state - APP_FSM_IDLE,\
							APP_FSM_SHUTDOWN_WEBSERVER - APP_FSM_IDLE);
            */
			state = nx_state;
			nx_state = APP_FSM_WAITING;
			esp8_status.tcp = ESP8_UNKNOWN;
			break;

		case APP_FSM_TRY_NEW_SSID_AND_PASSWORD:
			// Asks the ESP8266 to connect to a giving Access Point on the
			// webserver
			UI_WriteState("Trying new SSID");
			esp8266_set_SSID_and_PASS(ssidNpswd.ssidNpassword, ssidNpswd.len);
			UI_WiFiSettingUp();
            /*
			UI_set_progress(nx_state - APP_FSM_IDLE,\
							APP_FSM_SHUTDOWN_WEBSERVER - APP_FSM_IDLE);
            */
			update_state(nx_state, state);
			break;

		case APP_FSM_NEW_SSIDnPSWD_CONNECTED:
			// Connection to new AP has been successful, it retrieves
			// a webpage to the user telling 'DONE'
			UI_WriteState("Connected to new SSID");
			wifi_status = WiFi_CONNECTED;
			
			// set MYME Type TEXT/HTML
			webAppOptions.content_type = WEBAPP_CONTENT_TYPE_TEXT_HTML;

			// Buil HTTP to send back
			webAppOptions.status = WEBAPP_STATUS_OK;
			webAppOptions.content = WEBAPP_CONTENT_ALLDONE;
			build_HTTP(&webAppOptions);

			esp8266_set_CIPSEND_link(ssidNpswd.link_OnHold, webAppOptions.http_len_str, webAppOptions.http_len2);

			// Load WEB page into buffer
			esp8266_load_html(webAppOptions.http, webAppOptions.http_len);

			UI_WiFiConnected();

            /*
			UI_set_progress(nx_state - APP_FSM_IDLE,\
							APP_FSM_SHUTDOWN_WEBSERVER - APP_FSM_IDLE);
            */
			update_state(nx_state, state);
			break;

		case APP_FSM_TRY_AGAIN_WA_SSID_AND_PASSWORD:
			// Connection to new APP has been successful, it retrieves
			// a webpage telling the user to try again.

			UI_WriteState("New SSID failed, try again");
			// set MYME Type TEXT/HTML
			webAppOptions.content_type = WEBAPP_CONTENT_TYPE_TEXT_HTML;

			// Buil HTTP to send back
			webAppOptions.status = WEBAPP_STATUS_OK;
			webAppOptions.content = WEBAPP_CONTENT_TRYAGAIN;
			build_HTTP(&webAppOptions);

			esp8266_set_CIPSEND_link(ssidNpswd.link_OnHold, webAppOptions.http_len_str, webAppOptions.http_len2);

			// Load WEB page into buffer
			esp8266_load_html(webAppOptions.http, webAppOptions.http_len);

			UI_WiFiNo();
			// LCD_UsrLog("New SSID and Password Failed\r\n");
            /*
			UI_set_progress(nx_state - APP_FSM_IDLE,\
							APP_FSM_SHUTDOWN_WEBSERVER - APP_FSM_IDLE);
            */
			update_state(nx_state, state);
			break;

		case APP_FSM_SHUTDOWN_WEBSERVER:
			// The webserver on the ESP8266 is shutdown
			UI_WriteState("Shutting down server");
			esp8266_disable_HTTPServer_P80();

			UI_SettingsOff();
            /*
			UI_set_progress(nx_state - APP_FSM_IDLE,\
							APP_FSM_SHUTDOWN_WEBSERVER - APP_FSM_IDLE);
            */
			update_state(nx_state, state);
			break;
		/****************************************/
        case ESP8SS_ON_HOLD:
		case APP_FSM_WAITING:
            
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


