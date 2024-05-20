#ifndef ESP8266_POWERUP_H
#define ESP8266_POWERUP_H

#include "esp8266_network.h"

enum ESP8PowerupState {
    ESP8S_RESTART,
    ESP8S_CHECK_DEV,
    ESP8S_STATION_MODE,
    ESP8S_MULTI_CONN,
    ESP8_INITIAL_SETUP_COUNT,
};

enum ESP8AccessPointState {
    ESP8S_RESTART_4AP,
    ESP8S_ENABLE_AP,
    ESP8S_SET_CREDENTIALS,
    ESP8_ACCESS_POINT_COUNT,  
};

uint16_t LUT_OK_powerup(enum ESP8PowerupState prev_state);
uint16_t LUT_timeout_powerup(enum ESP8PowerupState prev_subs);
uint16_t LUT_on_err_powerup(enum ESP8PowerupState prev_subs);
void fsm_powerup(struct StateS *state);
void fsm_ap_config(struct StateS *state);

#endif
