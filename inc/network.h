#ifndef ESP8266_NETWORK_H
#define ESP8266_NETWORK_H

#include <stdint.h>

#include "net_credentials_conf.h"

enum ESP8NetManagerState {
	ESP8SS_INIT,
    ESP8SS_INITIAL_SETUP,
    ESP8SS_NETSTATUS,
    ESP8SS_AP,
    ESP8SS_CLIENT,
    ESP8SS_SERVER,
    ESP8SS_ON_HOLD,
    ESP8SS_ERROR,
    ESP8SS_READY,
	ESP8SS_STATION_CREDENTIALS,
};

struct Network {
	uint16_t *nx_state;
	uint16_t state;
	int8_t wifi_mode;
	uint8_t timeout;
	uint8_t  client_id;
	uint8_t server_id;
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
enum WifiStatus {
	WiFi_NO_CONNECTED,
	WiFi_SETTINGUP,
	WiFi_CONNECTED,
};

#define update_state(curr_state, prev_state) \
	esp8_status.cmd = ESP8_UNKNOWN; \
    prev_state = curr_state; \
	curr_state = MKSTATE(ESP8SS_ON_HOLD, 0); \

void network(void);		// runs the Finite-State Machine
void app_fsm_restart(void);
void server_function(struct Network *net);
void client_function(struct Network *net);
void NetEventHandler(struct Network *net);

#endif
