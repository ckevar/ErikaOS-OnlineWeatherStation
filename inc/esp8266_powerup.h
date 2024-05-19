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

uint16_t LUT_OK_powerup(enum ESP8PowerupState prev_state);
uint16_t LUT_timeout_powerup(enum ESP8PowerupState prev_subs);
uint16_t LUT_on_err_powerup(enum ESP8PowerupState prev_subs);
void fsm_powerup(struct StateS *state);

#endif
