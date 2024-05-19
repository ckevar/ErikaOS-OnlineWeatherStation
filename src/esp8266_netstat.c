
#include <string.h>

#include "state.h"
#include "esp8266_driver.h"
#include "esp8266_network.h"
#include "esp8266_responses.h"
#include "esp8266_powerup.h"
#include "esp8266_netstat.h"
#include "esp8266_client.h"

#include "WidgetConfig.h"

uint16_t LUT_OK_netstat(const enum ESP8NetManagerState superstate) {

    switch(esp8_status.wifi) {
    case WiFi_Ready:
    case TCP_UDP_Lost:
        // switch(APP_FSM_SUPER_STATE) {
        switch(superstate) {
        case ESP8SS_NETSTATUS:  // case APP_FSM_SUPER_NORMAL:
        case ESP8SS_CLIENT:
            return MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT);

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

void fsm_netstat(struct StateS *state) {
    uint16_t nx_state;
    uint8_t timeout_waiting;
    nx_state = SUBSTATE(*state->nx_state);

    switch(nx_state) {
    case ESP8S_IFCONFIG: // IFCONFIG
        // Checks if the ESP8266 is connected to an Access Point
		UI_WriteState("Getting IP");
        UI_clear_progress();
		esp8266_get_CIPSTA_CUR();

	    UI_set_progress(nx_state, ESP8_NETSTATUS_COUNT - 1);
		UI_WiFiSettingUp();
		update_state(*state->nx_state, *state->state);
		break;

	case ESP8S_NETSTAT: // CONN_STATUS
		// Check if there's an open port on the ESP8266.
		UI_WriteState("Getting Open Ports");
		esp8266_get_CIPSTATUS();
		UI_WiFiConnected();
		UI_set_progress(nx_state, ESP8_NETSTATUS_COUNT - 1);
		update_state(*state->nx_state, *state->state);
		break;

	case ESP8S_NETKILL:
		// If there's an open port, it should be closed.
		UI_WriteState("Kill ports");
		esp8266_close_tcp(0); // 0 for Single connections CMUX = 0
		UI_set_progress(nx_state, ESP8_NETSTATUS_COUNT - 1);
		update_state(*state->nx_state, *state->state);
    }
    *state->timeout = timeout_waiting;
}
