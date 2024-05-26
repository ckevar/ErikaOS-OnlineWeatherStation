/*
 * Created Mar 20, 2022
 *  - by ckevar
 */

#ifndef APP_H
#define APP_H 

// FSM States
#define APP_FSM_WAITING					35	// Waiting state 
#define APP_FSM_ERR_FAIL 				34 	// Error and fail state
#define APP_FSM_ERROR 					33 	// Error state
#define APP_FSM_FAIL 	 				32 	// Fail state

/*
#define APP_FSM_RESTART_AT_NORMAL 		0
#define APP_FSM_START					1	// Initial state 

#define APP_FSM_SET_CWMODE_STATION 		2	// set WiFi as station mode
#define APP_FSM_SET_CIPMUX				3	// State as single connection
#define APP_FSM_WIFI_CONN				4	// State to connect to a WiFi
#define APP_FSM_CHECK_TCP_CONNECTION 	5
#define APP_FSM_CLOSE_TCP_CONNS_IF_OPEN 6

	// States to get IP Location
#define APP_FSM_IPAPI_CIPSTART		    7	// State where connection with Ip-api stablishes
#define APP_FSM_IPAPI_CIPSEND		    8 	// State where length of the data to submit is set
#define APP_FSM_IPAPI_REQ_LOCATION 	    9 	// State where location of the IP is set 
#define APP_FSM_CLOSE_IPAPI 	        10

	// States to get weather info
#define APP_FSM_OW_API_CIPSTART 	    11 	// State where connection with openweather.org
#define APP_FSM_OW_API_CIPSEND 		    12 	// state where length of data to submit is set
#define APP_FSM_OW_API_REQ_WEATHER 	    13 	// states where weather info is required
#define APP_FSM_CLOSE_OW_API            14

    // states to get spotify info

#define APP_FSM_IDLE 					15
*/
#define APP_FSM_AP_RESET 				16 	// State to enable ESP8266 as WiFi
#define APP_FSM_AP_RESTART 				17 	// State to enable ESP8266 as WiFi
#define APP_FSM_AP_DUMMY_WAIT 			18
#define APP_FSM_SET_AP 					19 	// State to enable ESP8266 as WiFi
#define APP_FSM_SET_WPA 				20 	// state to set WPA SSID and Password
#define APP_FSM_SET_AP_CISTATUS 		21 	// State to enable multiple connections
#define APP_FSM_SET_AP_CIPMUX 			22 	// State to enable multiple connections
#define APP_FSM_SET_AP_SERVER 			23  // State to enable HTTP server
#define APP_FSM_WEBAPP_OK_CLIENT0   	24 	// to sent the welcome page
#define APP_FSM_WEBAPP_OK_CLIENT1   	25 	// to sent the welcome page
#define APP_FSM_CLEAN_AP_BUFFER 		26
#define APP_FSM_TRY_NEW_SSID_AND_PASSWORD 	27
#define APP_FSM_NEW_SSIDnPSWD_CONNECTED		28
#define APP_FSM_TRY_AGAIN_WA_SSID_AND_PASSWORD 29
#define APP_FSM_SHUTDOWN_WEBSERVER		30

#define APP_FSM_SUPER_NORMAL			0
#define APP_FSM_SUPER_SETTINGS 			1

void app_fsm_app(void);		// runs the Finite-State Machine
void app_fsm_restart(void);

#endif
