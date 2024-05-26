#include "esp8266_server.h"
#include "esp8266_driver.h"
#include "esp8266_link.h"
#include "state.h"
#include "WidgetConfig.h"

#include <string.h>

#define MAX_OK_ON_SERVER    6

uint16_t LUT_OK_server(enum ESP8ServerState prev_subs) {
    uint16_t LUT[MAX_OK_ON_SERVER] = {
        [ESP8S_MULTI_CONN_AP]   = MKSTATE(ESP8SS_SERVER, ESP8S_SERVER_ON),
        [ESP8S_SERVER_ON]       = MKSTATE(ESP8SS_SERVER, ESP8S_LISTENING),
        [ESP8S_SREAD]           = MKSTATE(ESP8SS_ON_HOLD, 0),
		[ESP8S_RMALLOC_S]		= MKSTATE(ESP8SS_ON_HOLD, 0),
        [ESP8S_SWRITE]          = MKSTATE(ESP8SS_SERVER, ESP8S_LISTENING),
    };
    if (prev_subs > MAX_OK_ON_SERVER)
        return MKSTATE(0,0);

    return LUT[prev_subs];
}

void fsm_server(struct StateS *state, struct Socket *ss) {
    enum ESP8ServerState nx_state;

    nx_state = SUBSTATE(*state->nx_state);
    switch(nx_state) {
    // case APP_FSM_SET_AP_CIPMUX:
    case ESP8S_MULTI_CONN_AP:
		esp8266_set_CIPMUX(ESP8266_CIPMUX_MULTI_CON);
	    UI_WriteState("Enabling multiple connection");
		break;

	// case APP_FSM_SET_AP_SERVER:
	case ESP8S_SERVER_ON:
		esp8266_clean_link_buff(0);
		esp8266_enable_HTTPServer_P80();
		UI_WriteState("Enabling web server");
		break;

    // case APP_FSM_WEBAPP_OK_CLIENT0:
    case ESP8S_LISTENING:
		*state->state = *state->nx_state;
		*state->nx_state = MKSTATE(ESP8SS_ON_HOLD, 0);
        *state->timeout = 0;
		UI_WriteState("Listening");
        UI_set_progress(nx_state, ESP8_SERVER_COUNT - 1);
		return;

	// case APP_FSM_WEBAPP_OK_CLIENT1:
	case ESP8S_SREAD:
        ss->link = app_http_process(ESP8SS_SERVER, ss->callback, (void *) ss);
        UI_WriteState("Reading");

		if (ss->rsize == 0)
			break;
	
	case ESP8S_RMALLOC_S:
		esp8266_set_CIPSEND_link(ss->link, ss->rsize, strnlen(ss->rsize, 3));
        break;
	
    case ESP8S_SWRITE:
		esp8266_send_html();
		UI_WriteState("Replying");
        break;
    
    case ESP8S_SERVER_OFF:
    // case APP_FSM_SHUTDOWN_WEBSERVER:
		esp8266_disable_HTTPServer_P80();
		UI_SettingsOff();
		UI_WriteState("Shutting down server");
    }

    *state->timeout = 0;
    UI_set_progress(nx_state, ESP8_SERVER_COUNT - 1);
    update_state(*state->nx_state, *state->state);
}
