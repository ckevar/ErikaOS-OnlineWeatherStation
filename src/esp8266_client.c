#include <string.h>
#include <stdlib.h>

#include "esp8266_driver.h"
#include "esp8266_network.h"
#include "esp8266_client.h"
#include "esp8266_link.h"
#include "esp8266_powerup.h"

#include "WidgetConfig.h"

#define UI_WRITESTATE(a, a_len, b, b_len)   memcpy(msg, a, a_len); \
                                            memcpy(msg + a_len, b, b_len); \
                                            UI_WriteState(msg)


uint16_t LUT_OK_client(enum ESP8Client prev_subs) {
    uint16_t LUT[ESP8_CLIENT_COUNT] = {
        [ESP8S_CONNECT] = MKSTATE(ESP8SS_CLIENT, ESP8S_RMALLOC),
        [ESP8S_RMALLOC] = MKSTATE(ESP8SS_ON_HOLD, 0),
        [ESP8S_CWRITE]   = MKSTATE(ESP8SS_ON_HOLD, 0),
        [ESP8S_CLOSE]   = MKSTATE(ESP8SS_CLIENT, ESP8S_DONE),
    };

    if (prev_subs > ESP8_CLIENT_COUNT)
        return MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART);

    return LUT[prev_subs];
}

void fsm_client(struct StateS *state, struct Socket *so) {
    uint16_t nx_state;
    uint8_t timeout_waiting;
    char msg[64] = {0};
    uint8_t sucess;

    nx_state = SUBSTATE(*state->nx_state);
    switch(nx_state) {
    case ESP8S_CONNECT:
        UI_clear_progress();
        UI_WRITESTATE("Connect to ", 11, so->domain_port, so->dsize);
		esp8266_set_DNS(so->link, so->domain_port, so->dsize);
		UI_set_progress(nx_state, ESP8_CLIENT_COUNT - 1);
		update_state(*state->nx_state, *state->state);
		break;

    case ESP8S_RMALLOC:
        UI_WRITESTATE("Remote malloc ", 14, so->domain_port, so->dsize); 
		esp8266_set_CIPSEND_link(so->link, so->rsize, strnlen(so->rsize, 3));
		UI_set_progress(nx_state, ESP8_CLIENT_COUNT - 1);
		update_state(*state->nx_state, *state->state);
        break;

    case ESP8S_CWRITE:
        UI_WRITESTATE("Request ", 6, so->domain_port, so->dsize); 
		esp8266_req_HTML(so->request, atoi(so->rsize));
		UI_set_progress(nx_state, ESP8_CLIENT_COUNT - 1);
		update_state(*state->nx_state, *state->state);
        break;

    case ESP8S_CREAD:
        UI_WRITESTATE("Read ", 5, so->domain_port, so->dsize);
        UI_set_progress(nx_state, ESP8_CLIENT_COUNT - 1);
        timeout_waiting = 0;
        esp8_status.cmd = ESP8_UNKNOWN;
        if (app_http_process(ESP8SS_CLIENT, so->callback, so->arg) == 0)
            *state->nx_state = MKSTATE(ESP8SS_CLIENT, ESP8S_CLOSE);
        else
            *state->nx_state = MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT);

        break;

    case ESP8S_CLOSE:
        // Closes connection with OpenWeather
		UI_WRITESTATE("Close ", 6, so->domain_port, so->dsize);
        UI_set_progress(nx_state, ESP8_CLIENT_COUNT - 1);
        if (esp8_status.cmd != ESP8_LINK_CLOSED) {
		    esp8266_close_tcp(so->link);
			update_state(*state->nx_state, *state->state);
            break;
        }

    case ESP8S_DONE:
        esp8_status.cmd = ESP8_UNKNOWN;
        UI_set_progress(ESP8S_DONE, ESP8_CLIENT_COUNT - 1);
		*state->nx_state = MKSTATE(ESP8SS_READY, 0);
		break;

    }
}
