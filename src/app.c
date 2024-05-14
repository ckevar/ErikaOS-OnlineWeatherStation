#include <string.h>

#include "esp8266_driver.h"
#include "ipapi_json.h"
#include "openweather.h"
#include "json_parser.h"

#include "app.h"
#include "web_app.h"
#include "WidgetConfig.h"

// Temp header
#include "lcd_log.h"
#include "stm32f4_discovery.h"

#define TIMEOUT_ON_WAITING                  64

#define update_state(curr_state, prev_state) \
	esp8_status.cmd = ESP8_UNKNOWN; \
    prev_state = curr_state; \
	curr_state = APP_FSM_WAITING; \
    timeout_waiting = 0

WebAppBuilder_t webAppOptions;

static char OWAPI_HTTP_MSG2REQ[250];
static char OWAPI_HTTP_MSG2REQ_LEN_STR[OWAPI_GET_RESOURCE_STR_LEN+1];
static unsigned short OWAPI_HTTP_MSG2REQ_LEN = 0;
static char INTERNAL_EVENT_UPDATE = 0;
static char APP_FSM_SUPER_STATE = 0;


static char IPAPI_process_result(char *tmp)
{	
	char *IPAPI_VALS[IPAPI_JSON_MEMBERS];
	unsigned short IPAPI_VALS_LEN[IPAPI_JSON_MEMBERS];
	char *ow_http = OWAPI_HTTP_MSG2REQ;

	if (IPAPI_get_location_PtrLen(tmp, IPAPI_VALS, IPAPI_VALS_LEN) == 0) 
	{
		
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

		return 0;
	}

	return 1;
}


static char OWAPI_process_result(char *tmp)
{
	char *weather[OWAPI_PARAMS_COUNT];
	unsigned short sizes[OWAPI_PARAMS_COUNT];

	if(OWAPI_get_weather(tmp, weather, sizes) == 0) {
		
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

		return 0;
	}
	return 1;
}

static short fsm_on_tcp_connection(void) {

    switch(esp8_status.wifi) {
    case WiFi_Ready:
    case TCP_UDP_Lost:
        switch(APP_FSM_SUPER_STATE) {
        case APP_FSM_SUPER_NORMAL:
        case APP_FSM_IPAPI_CIPSTART:
		    return APP_FSM_IPAPI_CIPSTART;

        case APP_FSM_OW_API_CIPSTART:
		    return APP_FSM_OW_API_CIPSTART;

        default:
		    return APP_FSM_RESTART_AT_NORMAL;
        }

    case TCP_UDP_Ready:
		 return APP_FSM_CLOSE_TCP_CONNS_IF_OPEN;

    case WiFi_No_AP:
        return APP_FSM_WIFI_CONN;

	default:
        return APP_FSM_RESTART_AT_NORMAL;
    }
}

/*
 * After each AT command sent to the ESP8266, it replies with an OK
 * so the APP FSM is held until an 'OK' reply is given back. Sometimes 
 * other replies are considered, such as: '>', '+IPD', etc.
 */
static short esp8266_fsm_prev_OnOK(short *prev_state) {
	switch (*prev_state) {			
	case APP_FSM_START:
	    return APP_FSM_SET_CWMODE_STATION;

	case APP_FSM_SET_CWMODE_STATION:
		return APP_FSM_SET_CIPMUX;

	case APP_FSM_SET_CIPMUX:
		return APP_FSM_WIFI_CONN;

	case APP_FSM_CHECK_TCP_CONNECTION:
        return fsm_on_tcp_connection();

	case APP_FSM_CLOSE_IPAPI: 
	    return APP_FSM_OW_API_CIPSTART;

	case APP_FSM_IPAPI_CIPSTART:
        return APP_FSM_IPAPI_CIPSEND;

	case APP_FSM_OW_API_CIPSTART:
	    return APP_FSM_OW_API_CIPSEND;

    case APP_FSM_IPAPI_CIPSEND:
    case APP_FSM_OW_API_CIPSEND:
        return APP_FSM_WAITING;

	case APP_FSM_CLOSE_OW_API:
        return APP_FSM_IDLE;

    case APP_FSM_RESTART_AT_NORMAL:
        return APP_FSM_WAITING;

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
	    return APP_FSM_SET_CWMODE_STATION;

    case APP_FSM_IPAPI_REQ_LOCATION:
    case APP_FSM_OW_API_REQ_WEATHER:
        return APP_FSM_WAITING;

	/********************/
	}
}


/* 
 * ESP8266 replies the '>' character when a CIPSEND command is sent and 
 * and tells the STM that it's ready to receive the http content (or data)
 * to be transmitted.
 */ 
static short esp8266_fsm_prev_OnWrap(const short prev_state) {
    switch(prev_state) {
    case APP_FSM_IPAPI_CIPSEND:
		return APP_FSM_IPAPI_REQ_LOCATION;

    case APP_FSM_OW_API_CIPSEND:
        return APP_FSM_OW_API_REQ_WEATHER;

    case APP_FSM_WEBAPP_OK_CLIENT0:
    case APP_FSM_NEW_SSIDnPSWD_CONNECTED:
    case APP_FSM_TRY_AGAIN_WA_SSID_AND_PASSWORD:
		return APP_FSM_WEBAPP_OK_CLIENT1;
    }
}


/*
 * If ESP8266 isnt connected to an access point, it retrieves 0.0.0.0 as
 * IP address. However it doesnt tell anything about whether it has internet
 * access or not.
 */ 
static char esp8266_fsm_prev_WiFiStatus(const short *prev_state, char *wifi_state) {

	static char attempts = 0;

	if (*prev_state == APP_FSM_WIFI_CONN) {
		if (memcmp(ESP8266_IPv4.ip, "0.0.0.0", 7) == 0) {

			*wifi_state = WiFi_NO_CONNECTED;
			attempts++;

			if (attempts > 100) {
                attempts = 0;
		        return APP_FSM_RESTART_AT_NORMAL;
            }

            return APP_FSM_WIFI_CONN;
		
		}
		else {
			attempts = 0;
            *wifi_state = WiFi_CONNECTED;
			return APP_FSM_CHECK_TCP_CONNECTION;
		}
	}
}

/* 
 * Processes arrival data from the APIs 
 */
static void app_http_from_APIs(char *http, short *prev_state, short *curr_state)
{
	// From the IP-API to know lgeographic location of 
	// the ESP8266.
	if (*prev_state == APP_FSM_IPAPI_REQ_LOCATION) {
		*curr_state = (IPAPI_process_result(http) == 0) ?\
 					   APP_FSM_CLOSE_IPAPI : APP_FSM_IPAPI_CIPSTART;

	} 
	// From the OpenWeather to parse weather information
	else if (*prev_state == APP_FSM_OW_API_REQ_WEATHER) {
		*curr_state = (OWAPI_process_result(http) == 0) ? APP_FSM_CLOSE_OW_API\
					   : APP_FSM_OW_API_CIPSTART;
	}
}

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
static void app_http_process(short *prev_state, short *curr_state, SSIDnPSWD_t *snp) 
{
	char link_id, i = 0;
	char *tmp;

	while((ESP8266_link.open[i] == 0) && (i < 5)) i++;

	link_id = ESP8266_link.open[i] - 1;
	tmp = ESP8266_link.buffXlink[link_id];

	app_http_from_APIs(tmp, prev_state, curr_state);
	app_http_from_WebApp(tmp, link_id, prev_state, curr_state, snp);

}


/*
 * This is called by a another Taks that will restart the APP FSM to 
 * update the weather info.
 */
void app_fsm_restart(void) {
	INTERNAL_EVENT_UPDATE = 1;
}

static short fsm_on_http_close(short *prev_state, char *wifi) {
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
}

static short fsm_on_waiting_state(short *prev_state, char *wifi) {
    switch(esp8_status.cmd) {
    case ESP8_OK: 
	    esp8_status.cmd = ESP8_UNKNOWN;
		return esp8266_fsm_prev_OnOK(prev_state);

    case ESP8_ERROR:
    case ESP8_FAIL: 
        esp8_status.cmd = ESP8_UNKNOWN;
        return APP_FSM_ERR_FAIL;

    case ESP8_WRAP:
	    esp8_status.cmd = ESP8_UNKNOWN;
	    return esp8266_fsm_prev_OnWrap(*prev_state);

    case ESP8_LINK_CLOSED:
	    esp8_status.cmd = ESP8_UNKNOWN;
        return  fsm_on_http_close(prev_state, wifi);

    case ESP8_IP:
	    esp8_status.cmd = ESP8_UNKNOWN;
	    return esp8266_fsm_prev_WiFiStatus(prev_state, wifi);

    case ESP8_READY:
        esp8_status.cmd = ESP8_UNKNOWN;

		if (*prev_state == APP_FSM_AP_RESTART)
		    return APP_FSM_SET_AP;

        return APP_FSM_START;
    
    default:
        return APP_FSM_WAITING;
    }

}

static short fsm_on_err_fail(const short state, const char wifi_state) {
    switch(state) {
    case APP_FSM_TRY_NEW_SSID_AND_PASSWORD:
	    return APP_FSM_TRY_AGAIN_WA_SSID_AND_PASSWORD;
			
    case APP_FSM_TRY_AGAIN_WA_SSID_AND_PASSWORD:
	    return APP_FSM_WAITING;
			
    case APP_FSM_SHUTDOWN_WEBSERVER:
	    return APP_FSM_SHUTDOWN_WEBSERVER;

    case  APP_FSM_WEBAPP_OK_CLIENT1:
	    if (wifi_state == WiFi_CONNECTED)
		    return APP_FSM_SHUTDOWN_WEBSERVER;

        else if (wifi_state == WiFi_SETTINGUP)
            return APP_FSM_CLEAN_AP_BUFFER;

    case APP_FSM_IPAPI_CIPSTART:
    case APP_FSM_OW_API_CIPSTART:
	    return APP_FSM_WIFI_CONN;
    
    case APP_FSM_OW_API_REQ_WEATHER: 
    case APP_FSM_IPAPI_REQ_LOCATION:
    case APP_FSM_SET_CIPMUX:
        return APP_FSM_WAITING; 

    default:
        return APP_FSM_RESTART_AT_NORMAL;
    }
}

static short fsm_on_timeout(unsigned short prev_state) {
    switch(prev_state) {
    case APP_FSM_IPAPI_REQ_LOCATION:
    case APP_FSM_IPAPI_CIPSTART:
    case APP_FSM_SET_CIPMUX:
        return APP_FSM_START;

    case APP_FSM_WEBAPP_OK_CLIENT0:
    case APP_FSM_CLEAN_AP_BUFFER:
    case APP_FSM_TRY_NEW_SSID_AND_PASSWORD:
    case APP_FSM_OW_API_REQ_WEATHER:
        return APP_FSM_WAITING;

    default:
        return APP_FSM_RESTART_AT_NORMAL;
    }
}

/*
 * Finiste-State Machine, this evaluates external events, ESP8266 events
 * (replies) in order to get the weather info and/or set the configurations
 * to connect with an Access Point.
 */
void app_fsm_app(void) {
	static short nx_state = APP_FSM_START;
	static short state = APP_FSM_START;
    static char wifi_status = WiFi_NO_CONNECTED;
    static uint8_t timeout_waiting;

	/* SSID AND PSW for ESP */
	static SSIDnPSWD_t ssidNpswd;

	/**** CHECK EVENTS (Screen touched?) ****/
	// if(IsEvent(RESET_ESP8266_EVNT)) {
	// 	nx_state = APP_FSM_START;
	// 	state = APP_FSM_START;
	// 	ClearEvents();

	// } else 
	if (IsEvent(SET_AP_ESP8266_EVNT)) {
		nx_state = APP_FSM_SET_AP;
		state = APP_FSM_SET_AP;
		ClearEvents();
	}
	if (INTERNAL_EVENT_UPDATE && (APP_FSM_SUPER_STATE != APP_FSM_SUPER_SETTINGS)) {
		INTERNAL_EVENT_UPDATE = 0;
		nx_state = APP_FSM_WIFI_CONN;
		state = APP_FSM_WIFI_CONN;
	}
	/****************************************/

	switch (nx_state) {

		/*********************** INITIAL SETUP FSMs **********************/
		case APP_FSM_RESTART_AT_NORMAL:
			// Restarts the ESP8266
			UI_WriteState("Restarting");
			esp8266_restart();
			wifi_status = WiFi_SETTINGUP;
			UI_clear_progress();
			UI_WiFiNo();
			update_state(nx_state, state);
			APP_FSM_SUPER_STATE =  APP_FSM_SUPER_NORMAL;
			break;

		case APP_FSM_START:
			// Sends AT to know if the ESP8266 is available
			UI_WriteState("Check WiFi Dev");
			esp8266_at();

			UI_clear_progress();
			UI_WiFiNo();
			update_state(nx_state, state);
			APP_FSM_SUPER_STATE =  APP_FSM_SUPER_NORMAL;
			break;

		case APP_FSM_SET_CWMODE_STATION:
			// Sets the ESP8266 to work as a WiFi station
            UI_clear_progress();
			UI_WriteState("Station mode");
			esp8266_set_CWMODE(ESP8266_CWMODE_STATION);
			UI_set_progress(nx_state, APP_FSM_IDLE);
			update_state(nx_state, state);		
			break;

		case APP_FSM_SET_CIPMUX:
			UI_WriteState("Force Multi Connection");
			esp8266_set_CIPMUX(ESP8266_CIPMUX_MULTI_CON);
			UI_set_progress(nx_state, APP_FSM_IDLE);
			update_state(nx_state, state);
			break;

		/*****************************************************************/

		/************************ CHECKING CONNs *************************/
		case APP_FSM_WIFI_CONN:
			// Checks if the ESP8266 is connected to an Access Point
			UI_WriteState("Check WiFi Conn");
            UI_clear_progress();
			esp8266_get_CIPSTA_CUR();

			UI_set_progress(nx_state, APP_FSM_IDLE);
			UI_WiFiSettingUp();
			update_state(nx_state, state);
			break;

		case APP_FSM_CHECK_TCP_CONNECTION:
			// Check if there's an open port on the ESP8266.
			UI_WriteState("Check TCP Conn");
			esp8266_get_CIPSTATUS();
			UI_WiFiConnected();
			UI_set_progress(nx_state, APP_FSM_IDLE);
			update_state(nx_state, state);
			break;

		case APP_FSM_CLOSE_TCP_CONNS_IF_OPEN:
			// If there's an open port, it should be closed.
			UI_WriteState("Close TCP Conn");
			esp8266_close_tcp(0); // 0 for Single connections CMUX = 0
			UI_set_progress(nx_state, APP_FSM_IDLE);
			update_state(nx_state, state);
		/*****************************************************************/

		/*************************** HTML FSMs ***************************/
		case APP_FSM_IPAPI_CIPSTART:
			// Sends the DNSS of the IP-API to know the location of the
			// ESP8266 based on its public IP.
			UI_WriteState("Connect to IP-API");
			esp8266_set_DNS(0, IPAPI_JSON_DNS_PORT, IPAPI_JSON_DNS_PORT_LEN);

			UI_LocationUnavailable();
			UI_set_progress(nx_state, APP_FSM_IDLE);
			update_state(nx_state, state);
			APP_FSM_SUPER_STATE = APP_FSM_IPAPI_CIPSTART;
			break;	

		case APP_FSM_IPAPI_CIPSEND:
			// Tells the ESP8266 how long the HTTP data will be
			UI_WriteState("Request MEM alloc for IP-API");
			esp8266_set_CIPSEND_link(0, IPAPI_GET_RESOURCE_LEN_STR, IPAPI_GET_RESOURCE_LEN_STR_LEN);
			UI_set_progress(nx_state, APP_FSM_IDLE);
			update_state(nx_state, state);
			break;
							
		case APP_FSM_IPAPI_REQ_LOCATION:
			// Sends the REST request to IP-API
			UI_WriteState("Request Location on IP-API");
			esp8266_req_HTML(IPAPI_GET_RESOURCE, IPAPI_GET_RESOURCE_LEN);
			UI_set_progress(nx_state, APP_FSM_IDLE);
			update_state(nx_state, state);
			break;

		case APP_FSM_CLOSE_IPAPI:
			// Closes the connection with IP-API
			UI_WriteState("Terminate conn with IP-API");
			UI_set_progress(nx_state, APP_FSM_IDLE);
            if(esp8_status.cmd != ESP8_LINK_CLOSED) {
			    esp8266_close_tcp(0); // 0 for Single connections CMUX = 0
			    update_state(nx_state, state);
			    break;
            }
            esp8_status.cmd = ESP8_UNKNOWN;
            nx_state = APP_FSM_OW_API_CIPSTART;
            break;

		case APP_FSM_OW_API_CIPSTART:
			// Starts the connection the OpenWeather server
			UI_WriteState("Connect to OW");
			esp8266_set_DNS(1, OWAPI_DNS_PORT, OWAPI_DNS_PORT_LEN);
			UI_set_progress(nx_state, APP_FSM_IDLE);
			update_state(nx_state, state);
			APP_FSM_SUPER_STATE = APP_FSM_OW_API_CIPSTART;
			break;

		case APP_FSM_OW_API_CIPSEND:
			// Tells ESP8266 length of the HTTP request
			UI_WriteState("Request MEM alloc for OW");
			esp8266_set_CIPSEND_link(1, OWAPI_HTTP_MSG2REQ_LEN_STR, strlen(OWAPI_HTTP_MSG2REQ_LEN_STR)); 
			UI_set_progress(nx_state, APP_FSM_IDLE);
			update_state(nx_state, state);
			break;

        case APP_FSM_OW_API_REQ_WEATHER:
			// Sends the HTTP request
			UI_WriteState("Request Weather info on OW");
			esp8266_req_HTML(OWAPI_HTTP_MSG2REQ, OWAPI_HTTP_MSG2REQ_LEN);
			UI_set_progress(nx_state, APP_FSM_IDLE);
			update_state(nx_state, state);
			break;

		case APP_FSM_CLOSE_OW_API:
			// Closes connection with OpenWeather
			UI_WriteState("Terminate conn with OW");
            UI_set_progress(nx_state, APP_FSM_IDLE);
            if (esp8_status.cmd != ESP8_LINK_CLOSED) {
			    esp8266_close_tcp(1); 
			    update_state(nx_state, state);
                break;
            }
            esp8_status.cmd = ESP8_UNKNOWN;
			nx_state = APP_FSM_IDLE;
			break;

		case APP_FSM_IDLE:
			// Doesn't do anything, it just waits
			UI_WriteState("ALL GOOD");
			UI_set_progress(nx_state, APP_FSM_IDLE);
			break;
		/*****************************************************************/

		/************************* SETTINGS FSMs *************************/
		case APP_FSM_AP_RESTART:
			// Restarts the ESP8266
			UI_WriteState("Restarting...");
			esp8266_restart();
			wifi_status = WiFi_SETTINGUP;
			UI_clear_progress();
			UI_SettingsOn();
			UI_set_progress(nx_state - APP_FSM_IDLE,\
							APP_FSM_SHUTDOWN_WEBSERVER - APP_FSM_IDLE);
			update_state(nx_state, state);
			APP_FSM_SUPER_STATE = APP_FSM_SUPER_SETTINGS;
			break;

		case APP_FSM_SET_AP:
			// Sets ESP8266 as station mode and as Access Point
			UI_clear_progress();
			UI_WriteState("Enabling WiFi");
			esp8266_set_CWMODE(ESP8266_CWMODE_STATION_N_SOFTAP);
			UI_set_progress(nx_state - APP_FSM_IDLE,\
							APP_FSM_SHUTDOWN_WEBSERVER - APP_FSM_IDLE);
			update_state(nx_state, state);
            APP_FSM_SUPER_STATE = APP_FSM_SUPER_SETTINGS;
			break;

		case APP_FSM_SET_WPA:
			// Sets the ESP8266 Access Point SSID and Password
			UI_WriteState("Configurations on WiFi");
			esp8266_set_CWSAP(APP_AP_CONFIGURATION, APP_AP_CONFIGURATION_LEN);
			UI_set_progress(nx_state - APP_FSM_IDLE,\
							APP_FSM_SHUTDOWN_WEBSERVER - APP_FSM_IDLE);
			update_state(nx_state, state);
			break;

		case APP_FSM_SET_AP_CIPMUX:
			// Sends to allow multiplce connection on the ESP8266
			UI_WriteState("Enabling multiple connection");
			esp8266_set_CIPMUX(ESP8266_CIPMUX_MULTI_CON);

			UI_set_progress(nx_state - APP_FSM_IDLE,\
							APP_FSM_SHUTDOWN_WEBSERVER - APP_FSM_IDLE);
			update_state(nx_state, state);
			break;

		case APP_FSM_SET_AP_SERVER:
			// Asks the ESP8266 to create a webserver at port 80
			UI_WriteState("Enabling web server");
			esp8266_clean_link_buff(0);
			esp8266_enable_HTTPServer_P80();
			UI_set_progress(nx_state - APP_FSM_IDLE,\
							APP_FSM_SHUTDOWN_WEBSERVER - APP_FSM_IDLE);
			update_state(nx_state, state);
			esp8_status.tcp = ESP8_UNKNOWN;
			break;

		case APP_FSM_WEBAPP_OK_CLIENT0:
			// Idle state waiting for clients to request or submit 
			// HTTP information on the webserver
			UI_WriteState("Waiting for connections");
			UI_set_progress(nx_state - APP_FSM_IDLE,\
							APP_FSM_SHUTDOWN_WEBSERVER - APP_FSM_IDLE);
			state = nx_state;
			nx_state = APP_FSM_WAITING;
			break;

		case APP_FSM_WEBAPP_OK_CLIENT1:
			// Sends the requested HTML
			UI_WriteState("Replying");
			esp8266_send_html();
			UI_set_progress(nx_state - APP_FSM_IDLE,\
							APP_FSM_SHUTDOWN_WEBSERVER - APP_FSM_IDLE);
			esp8_status.tcp = ESP8_UNKNOWN;
			update_state(nx_state, state);
			break;

		case APP_FSM_CLEAN_AP_BUFFER:
			// Idle state to get out, i think it's useless 
			UI_WriteState("Transition state");
			UI_set_progress(nx_state - APP_FSM_IDLE,\
							APP_FSM_SHUTDOWN_WEBSERVER - APP_FSM_IDLE);
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
			UI_set_progress(nx_state - APP_FSM_IDLE,\
							APP_FSM_SHUTDOWN_WEBSERVER - APP_FSM_IDLE);

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
			UI_set_progress(nx_state - APP_FSM_IDLE,\
							APP_FSM_SHUTDOWN_WEBSERVER - APP_FSM_IDLE);

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
			UI_set_progress(nx_state - APP_FSM_IDLE,\
							APP_FSM_SHUTDOWN_WEBSERVER - APP_FSM_IDLE);
			update_state(nx_state, state);
			break;

		case APP_FSM_SHUTDOWN_WEBSERVER:
			// The webserver on the ESP8266 is shutdown
			UI_WriteState("Shutting down server");
			esp8266_disable_HTTPServer_P80();

			UI_SettingsOff();
			UI_set_progress(nx_state - APP_FSM_IDLE,\
							APP_FSM_SHUTDOWN_WEBSERVER - APP_FSM_IDLE);
			update_state(nx_state, state);
			break;
		/****************************************/

		case APP_FSM_WAITING:
            
            nx_state = fsm_on_waiting_state(&state, &wifi_status);

			if (esp8_status.tcp & TCP_BUFF_FULL) {
				app_http_process(&state, &nx_state, &ssidNpswd);
				esp8_status.tcp &= ~TCP_BUFF_FULL;
			}

            timeout_waiting++;
            if (timeout_waiting == TIMEOUT_ON_WAITING) {
                timeout_waiting = 0;
                nx_state = fsm_on_timeout(state);
            }

			break;

		case APP_FSM_ERR_FAIL:
			UI_set_err_progress(state, APP_FSM_IDLE);
            nx_state = fsm_on_err_fail(state, wifi_status);
			break;

	}

}


