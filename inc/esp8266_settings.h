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
    ESP8S_SET_AP_CREDENTIALS,
    ESP8_ACCESS_POINT_COUNT,  
};

enum ESP8StationCredentials {
	ESP8S_SET_STA_CREDENTIALS,
	ESP8_STATION_CREDENTIALS_COUNT,
};

typedef struct SSIDnPSWD_t {
	char ssidNpassword[128];
	uint8_t size;
} SSIDnPSWD_t;

uint16_t LUT_OK_powerup(enum ESP8PowerupState prev_state);
uint16_t LUT_timeout_powerup(enum ESP8PowerupState prev_subs);
uint16_t LUT_on_err_powerup(enum ESP8PowerupState prev_subs);
void fsm_powerup(struct StateS *state);

uint16_t LUT_OK_access_point(enum ESP8AccessPointState prev_subs);
void fsm_ap_config(struct StateS *state);



#ifdef CREDENTIALS_BY_WEP_APP
#	define LUT_OK_station_credentials()		MKSTATE(ESP8SS_SERVER, ESP8S_SERVER_OFF)
#	define LUT_ERR_station_credentials()	MKSTATE(ESP8SS_AP, ESP8S_RESTART_4AP)
#else
#	define LUT_OK_station_credentials()		MKSTATE(ESP8SS_READY, 0)
#	define LUT_ERR_station_credentials()	MKSTATE(ESP8SS_ERROR, 0)
#endif
uint16_t fsm_station_credentials(struct StateS *s, SSIDnPSWD_t *credentials);

#endif
