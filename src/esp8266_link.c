#include "esp8266_link.h"
#include "esp8266_driver.h"
#include "esp8266_client.h"
#include "esp8266_settings.h"
#include "esp8266_server.h"

#include "state.h"

uint16_t LUT_link_pullin(enum ESP8NetManagerState supers) {
    if(supers == ESP8SS_CLIENT)
        return MKSTATE(supers, ESP8S_CREAD);

    else if (supers == ESP8SS_SERVER)
        return MKSTATE(supers, ESP8S_SREAD);
    
    else
        return MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART);
}

uint8_t app_http_process(enum ESP8NetManagerState supers, \
		void (*callback)(uint8_t*, char*, void*), \
		void *arg)
{
	char link_id, i = 0;
	char *tmp;
    uint8_t success;

	while((ESP8266_link.open[i] == 0) && (i < 5)) i++;

	link_id = ESP8266_link.open[i] - 1;
	tmp = ESP8266_link.buffXlink[link_id];
    
    if (supers == ESP8SS_CLIENT)
        (*callback)(&success, tmp, arg);
    
    else if (supers == ESP8SS_SERVER) {
        (*callback)(&success, tmp, arg);
        if (success) success = link_id;
    }

    return success;
}

/* 
 * ESP8266 replies the '>' character when a CIPSEND command is sent and 
 * and tells the STM that it's ready to receive the http content (or data)
 * to be transmitted.
 */ 
uint16_t esp8266_fsm_prev_OnWrap(const uint16_t prev_state) {
    enum ESP8NetManagerState supers = SUPERSTATE(prev_state);

    switch(supers) {
    case ESP8SS_CLIENT:
        return MKSTATE(ESP8SS_CLIENT, ESP8S_CWRITE);
    case ESP8SS_SERVER:
        return MKSTATE(ESP8SS_SERVER, ESP8S_SWRITE);
    }
}
