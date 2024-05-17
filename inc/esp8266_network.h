#ifndef ESP8266_NETWORK_H
#define ESP8266_NETWORK_H

#include <stdint.h>

enum ESP8InitialSetupState {
    ESP8S_RESTART,
    ESP8S_CHECK_DEV,
    ESP8S_STATION_MODE,
    ESP8S_MULTI_CONN,
    ESP8_INITIAL_SETUP_COUNT,
};

enum ESP8CheckConnectionState {
    ESP8S_IFCONFIG,
    ESP8S_NETSTAT,
    ESP8S_NETKILL,
    ESP8_NETSTATUS_COUNT,

};

enum ESP8Client {
    ESP8S_CONNECT,
    ESP8S_RMALLOC,  // Remote Malloc
    ESP8S_CWRITE,   // Client Write
    ESP8S_CREAD,    // Client Read
    ESP8S_CLOSE,
    ESP8S_DONE,
    ESP8_CLIENT_COUNT
};

enum ESP8Server {
    ESP8S_SWRITE,
    ESP8S_SREAD,
};

enum ESP8NetworkState {
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

#endif
