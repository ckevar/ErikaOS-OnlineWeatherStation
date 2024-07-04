
#include <string.h>

#include "state.h"
#include "esp8266_driver.h"
#include "network.h"
#include "esp8266_responses.h"
#include "esp8266_settings.h"
#include "esp8266_netstat.h"
#include "esp8266_client.h"

#include "WidgetConfig.h"

uint16_t LUT_OK_netstat(const enum ESP8NetManagerState superstate) {

    switch(esp8_status.wifi) {
    case WiFi_Ready:
    case TCP_UDP_Lost:
        switch(superstate) {
        case ESP8SS_NETSTATUS:  
        case ESP8SS_CLIENT:
            return MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT_TCP);

        default:
		    return MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART);
        }

    case TCP_UDP_Ready:
		 return MKSTATE(ESP8SS_NETSTATUS, ESP8S_NETKILL);

    case WiFi_No_AP:
        return MKSTATE(ESP8SS_NETSTATUS, ESP8S_IFCONFIG);

	default:
        return MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART);
    }
}

/*
 * If ESP8266 isnt connected to an access point, it retrieves 0.0.0.0 as
 * IP address. However it doesnt tell anything about whether it has internet
 * access or not.
 */ 
uint16_t on_WiFiStatus(const enum ESP8NetstatState prev_subs, char *wifi_state) {

	static char attempts = 0;

	if (prev_subs == ESP8S_IFCONFIG) {
		if (memcmp(ESP8266_IPv4.ip, "0.0.0.0", 7) == 0) {

			*wifi_state = WiFi_NO_CONNECTED;
			attempts++;

			if (attempts > MAX_ATTEMPTS_NETSTAT) {
                attempts = 0;
		        return MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART);
            }

            return MKSTATE(ESP8SS_NETSTATUS, ESP8S_IFCONFIG);
		
		}
		else {
			attempts = 0;
            *wifi_state = WiFi_CONNECTED;
			return MKSTATE(ESP8SS_NETSTATUS, ESP8S_NETSTAT);
		}
	}
}


/******** Finite State Machine *******/

void fsm_netstat(struct StateS *state) {
    enum ESP8NetstatState nx_state;
    nx_state = SUBSTATE(*state->nx_state);

    switch(nx_state) {
    case ESP8S_IFCONFIG: // IFCONFIG
		esp8266_get_CIPSTA();
        UI_WriteState("Getting IP");
        UI_clear_progress();
		UI_WiFiSettingUp();
		break;

	case ESP8S_NETSTAT: // CONN_STATUS
		esp8266_get_CIPSTATUS();
		UI_WriteState("Getting Open Ports");
		UI_WiFiConnected();
		break;

	case ESP8S_NETKILL:
		esp8266_close_tcp(esp8_status.link);
		UI_WriteState("Kill ports");
    }

    *state->timeout = 0;
	UI_set_progress(nx_state, ESP8_NETSTATUS_COUNT - 1);
	update_state(*state->nx_state, *state->state);
}
