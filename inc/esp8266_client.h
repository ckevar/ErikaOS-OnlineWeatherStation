#ifndef ESP8266_CLIENT_H
#define ESP8266_CLIENT_H

#include "state.h"

enum ESP8Client {
	ESP8S_CONNECT_SSL,
    ESP8S_CONNECT_TCP,
    ESP8S_RMALLOC,  // Remote Malloc
    ESP8S_CWRITE,   // Client Write
    ESP8S_CREAD,    // Client Read
    ESP8S_CLOSE,
    ESP8S_DONE,
    ESP8_CLIENT_COUNT
};


uint16_t esp8266_fsm_prev_OnWrap(const uint16_t prev_state);
uint16_t LUT_OK_client(enum ESP8Client prev_subs);
void fsm_client(struct Network *state, struct Socket *so);

#endif
