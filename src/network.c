#include <string.h>
#include <stdlib.h>

#include "state.h"
#include "esp8266_driver.h"
#include "network.h"
#include "esp8266_settings.h"
#include "esp8266_netstat.h"
#include "esp8266_client.h"
#include "esp8266_link.h"
#include "esp8266_server.h"

// #include "web_app.h"
#include "WidgetConfig.h"

// Temp header
#include "lcd_log.h"
#include "stm32f4_discovery.h"

#define TIMEOUT_ON_WAITING                  128


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
	
    case ESP8SS_AP:
        return LUT_OK_access_point(SUBSTATE(*s->state));

    case ESP8SS_SERVER:
        return LUT_OK_server(SUBSTATE(*s->state));

	case ESP8SS_STATION_CREDENTIALS:
		esp8_status.wifi = WiFi_CONNECTED;
		UI_SettingsOff();
		UI_WiFiConnected();
		return LUT_OK_station_credentials();
	}
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
	case ESP8SS_INITIAL_SETUP:
        return MKSTATE(ESP8SS_ON_HOLD, 0);
    }
}

static uint16_t fsm_on_waiting_state(struct StateS *s) {
    switch(esp8_status.cmd) {
    case ESP8_OK: 
	    esp8_status.cmd = ESP8_UNKNOWN;
		return LUT_onOK(s);

    case ESP8_ERROR:
    case ESP8_FAIL: 
        esp8_status.cmd = ESP8_UNKNOWN;
		return MKSTATE(ESP8SS_ERROR, 0);

    case ESP8_WRAP:
	    esp8_status.cmd = ESP8_UNKNOWN;
	    return esp8266_fsm_prev_OnWrap(*s->state);

    case ESP8_DATA_PULLIN:
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
		if (esp8_status.http == HTTP_200)
			return MKSTATE(ESP8SS_CLIENT, ESP8S_CLOSE);

        return MKSTATE(ESP8SS_NETSTATUS, ESP8S_CHECK_DEV);
    
    case ESP8SS_SERVER:
	case ESP8SS_AP:
	case ESP8SS_STATION_CREDENTIALS:
        return MKSTATE(ESP8SS_ON_HOLD, 0);

    default:
        return MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART);
    }
}

__attribute__((weak)) void client_function(struct StateS *s)  {
	
	static struct Socket sock;
	
	/*
	 * It is adviced to implement a double state FSM here, in order to
	 * avoid definitions in a repetitive way.
	 *
	sock.link = 0,
    sock.domain_port = "\"example.com\",80",	// Port 443 is not recommended
    sock.dsize = 16,							// Length of (domain port)
    sock.request = "GET / HTTP/1.1\r\n<someheader>",// HTTP header
    sock.rsize = "16",							// Length in str of (HTTP header)
    sock.callback = &foo,						// Callback function that process
												// the server's reply
    sock.arg = NULL;							// Argument for the callback function
	
	 * foo shall be defined as:
	 * void foo(uint8_t *success, char *http, void *arg) {
	 *  // DO something here
	 *	// ...
	 *
	 *	if <some error>
	 *		*sucess = 0;
	 *
	 *  // Do something else here
	 *	// ...
	 *
	 *	// else <everything good>
	 *		
	 *	*success = 1;
	 * }
    
	fsm_client(s, &sock);
	if(SUPERSTATE(s->nx_state) == ESP8SS_READY)
		return MKSTATE(TO SOME OTHER STATE);
	*/
	*s->nx_state = MKSTATE(ESP8SS_READY, 0);
}

__attribute__((weak)) void server_function(struct StateS *s, uint8_t server_id) {

	static struct Socket sock;
	
	/*
	 * 1. Read client function for more information. 
	 * 2. Other parameters of sock are ignored or
	 * used for the internal FSM.
	 *
	socket.callback = &foo;
	socket.arg = (void *)&wifi_credentials;
	
	fsm_server(s, &sock);
	
	if (SUBSTATE(*s->state) == ESP8S_LISTENING)
		return MKSTATE(TO SOME OTHER STATE);
	*/
	*s->nx_state = MKSTATE(ESP8SS_READY, 0);
}

__attribute__((weak)) void NetEventHandler(struct StateS *s, \
		uint8_t *server_id, uint8_t *client_id) 
{

}

void network(void) {
	static uint16_t nx_state = MKSTATE(ESP8SS_POWER_UP, 0);
	static uint16_t state;
    static char wifi_status = WiFi_NO_CONNECTED;
    static uint8_t timeout_waiting;
    static struct StateS nu_state;
	static uint8_t server_id = 0;
	static uint8_t client_id = 0;
    enum ESP8NetManagerState supers;

	NetEventHandler(&nu_state, &server_id, &client_id);
	/*
	if (IsEvent(SPOTIFY_CONF_EVENT)) {
		nx_state = MKSTATE(ESP8SS_SERVER, 0);
		state = nx_state;
		server_id = 1;
		ClearEvents();
	}

	if (IsEvent(SET_AP_ESP8266_EVNT)) {
        nx_state = MKSTATE(ESP8SS_AP, 0);
		state =  MKSTATE(ESP8SS_AP, 0);
		server_id = 0;
		ClearEvents();
	}
	
	if	(INTERNAL_EVENT_UPDATE &&\
		(SUPERSTATE(state) != ESP8SS_AP) &&\
        (SUPERSTATE(state) != ESP8SS_SERVER) &&\
		(SUPERSTATE(state) != ESP8SS_STATION_CREDENTIALS))
	{
		INTERNAL_EVENT_UPDATE = 0;
        nx_state = MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT_TCP);
		state =  MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT_TCP);
	}
	*/
    supers = SUPERSTATE(*nu_state.nx_state);
	switch (supers) {
		case ESP8SS_POWER_UP:
			nu_state.nx_state = &nx_state;
			nu_state.state = &state;
			nu_state.wifi_mode = &wifi_status;
			nu_state.timeout = &timeout_waiting;
			nx_state = MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_CHECK_DEV);
			state = nx_state;		

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
            server_function(&nu_state, server_id);
            break;
		
        case ESP8SS_ON_HOLD:
            nx_state = fsm_on_waiting_state(&nu_state);
            
            timeout_waiting++;
            if (timeout_waiting == TIMEOUT_ON_WAITING) {
                timeout_waiting = 0;
                nx_state = fsm_on_timeout(state);
            }

			if(*nu_state.nx_state == 65535)
				*nu_state.nx_state = 0;

			break;

        case ESP8SS_ERROR:
			UI_set_err_progress(1, 1);
            nx_state = fsm_on_err_fail(&nu_state);
			break;

	}

}


