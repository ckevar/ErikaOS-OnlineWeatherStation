#ifndef ESP8266_SERVER_H
#define ESP8266_SERVER_H

#include "esp8266_network.h"

enum ESP8ServerState {
    ESP8S_MULTI_CONN_AP,
    ESP8S_SERVER_ON,
    ESP8S_LISTENING,
    ESP8S_SREAD,
	ESP8S_RMALLOC_S,
    ESP8S_SWRITE,
    ESP8S_PURGE_BUFF,
    ESP8S_SERVER_OFF,
    ESP8_SERVER_COUNT,
};


uint16_t LUT_OK_server(enum ESP8ServerState prev_subs);
void fsm_server(struct StateS *state, struct Socket *ss);
#endif
