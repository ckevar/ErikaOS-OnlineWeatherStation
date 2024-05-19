#ifndef ESP8266_NETWORK_H
#define ESP8266_NETWORK_H

#include <stdint.h>

enum ESP8Server {
    ESP8S_SWRITE,
    ESP8S_SREAD,
};

enum ESP8NetManagerState {
    ESP8SS_INITIAL_SETUP,
    ESP8SS_NETSTATUS,
    ESP8SS_AP,
    ESP8SS_CLIENT,
    ESP8SS_SERVER,
    ESP8SS_ON_HOLD,
    ESP8SS_ERROR,
    ESP8SS_READY,
};


struct StateS {
    uint16_t *nx_state;
    uint16_t *state;
    uint8_t *timeout;
    int8_t *wifi_mode;
};

struct Socket {
    uint8_t link;
    char *domain_port;
    uint8_t dsize;
    char *request;
    char *rsize;
    void (*callback)(uint8_t*, char*, void*);
    void *arg;
};

// WiFi states
#define WiFi_NO_CONNECTED	0
#define WiFi_SETTINGUP		1
#define WiFi_CONNECTED 		2

#define update_state(curr_state, prev_state) \
	esp8_status.cmd = ESP8_UNKNOWN; \
    prev_state = curr_state; \
	curr_state = MKSTATE(ESP8SS_ON_HOLD, 0); \
    timeout_waiting = 0


#endif
