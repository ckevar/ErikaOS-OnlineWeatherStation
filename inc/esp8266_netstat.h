#ifndef ESP8266_NETSTAT_H
#define ESP8266_NETSTAT_H


#define MAX_ATTEMPTS_NETSTAT    100

enum ESP8NetstatState {
    ESP8S_IFCONFIG,
    ESP8S_NETSTAT,
    ESP8S_NETKILL,
    ESP8_NETSTATUS_COUNT,
};

uint16_t LUT_OK_netstat(const enum ESP8NetManagerState superstate);

/*
 * If ESP8266 isnt connected to an access point, it retrieves 0.0.0.0 as
 * IP address. However it doesnt tell anything about whether it has internet
 * access or not.
 */ 
uint16_t on_WiFiStatus(const enum ESP8NetstatState prev_state, char *wifi_state);

void fsm_netstat(struct Network *state);


#endif
