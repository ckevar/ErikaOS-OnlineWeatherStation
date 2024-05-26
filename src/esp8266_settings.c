#include "state.h"
#include "esp8266_driver.h"
#include "esp8266_responses.h"
#include "esp8266_settings.h"
#include "WidgetConfig.h"
#include "net_credentials_conf.h"

uint16_t LUT_OK_powerup(enum ESP8PowerupState prev_subs) {
    uint16_t LUT[ESP8_INITIAL_SETUP_COUNT] = {
        [ESP8S_RESTART]     = MKSTATE(ESP8SS_ON_HOLD, 0),
        [ESP8S_CHECK_DEV]   = MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_STATION_MODE),
        [ESP8S_STATION_MODE]= MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_MULTI_CONN),
        [ESP8S_MULTI_CONN]  = MKSTATE(ESP8SS_NETSTATUS, 0),
    };

    if (prev_subs > ESP8_INITIAL_SETUP_COUNT)
        return MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART);

    return LUT[prev_subs];
}

 uint16_t LUT_timeout_powerup(enum ESP8PowerupState prev_subs) {
    uint16_t LUT[ESP8_INITIAL_SETUP_COUNT] = {
        [ESP8S_RESTART]     = MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART),
        [ESP8S_CHECK_DEV]   = MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART),
        [ESP8S_STATION_MODE]= MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_CHECK_DEV),
        [ESP8S_MULTI_CONN]  = MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_CHECK_DEV),
    };

    if (prev_subs > ESP8_INITIAL_SETUP_COUNT) 
        return MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_CHECK_DEV);
    
    return LUT[prev_subs];
}

uint16_t LUT_on_err_powerup(enum ESP8PowerupState prev_subs) {
    uint16_t LUT[ESP8_INITIAL_SETUP_COUNT] = {
        [ESP8S_RESTART]     = MKSTATE(ESP8SS_ON_HOLD, 0),
        [ESP8S_CHECK_DEV]   = MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART),
        [ESP8S_STATION_MODE]= MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_CHECK_DEV),
        [ESP8S_MULTI_CONN]  = MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_CHECK_DEV)
    };

    if(prev_subs > ESP8_INITIAL_SETUP_COUNT)
        return MKSTATE(ESP8SS_ERROR, 0);

    return LUT[prev_subs];
}




/********* Finite State Machines *********/

void fsm_powerup(struct StateS *state) {
    enum ESP8PowerupState nx_state;
    nx_state = SUBSTATE(*state->nx_state);
    
    switch(nx_state) {
    case ESP8S_RESTART:
		esp8266_restart();
		UI_WriteState("Restart");
		*state->wifi_mode = WiFi_SETTINGUP;
		UI_clear_progress();
		UI_WiFiNo();
		break;

	case ESP8S_CHECK_DEV:
		esp8266_at();
		UI_WriteState("Check WiFi Dev");
		UI_WiFiNo();
		break;

    case ESP8S_STATION_MODE:
		esp8266_set_CWMODE(ESP8266_CWMODE_STATION);
        UI_clear_progress();
		UI_WriteState("Station mode");
		break;

	case ESP8S_MULTI_CONN:
		esp8266_set_CIPMUX(ESP8266_CIPMUX_MULTI_CON);
        UI_WriteState("Force Multi Connection");
		break;
    }
    
    *state->timeout = 0;
    UI_set_progress(nx_state, ESP8_INITIAL_SETUP_COUNT - 1);
	update_state(*state->nx_state, *state->state);
}


uint16_t LUT_OK_access_point(enum ESP8AccessPointState prev_subs) {
    uint16_t LUT[ESP8_ACCESS_POINT_COUNT] = {
        [ESP8S_RESTART_4AP]         = MKSTATE(ESP8SS_ON_HOLD, 0),
        [ESP8S_ENABLE_AP]           = MKSTATE(ESP8SS_AP, ESP8S_SET_AP_CREDENTIALS),
#ifdef AP_WITH_SERVER
        [ESP8S_SET_AP_CREDENTIALS]  = MKSTATE(ESP8SS_SERVER, 0),
#elif
        [ESP8S_SET_AP_CREDENTIALS]  = MKSTATE(ESP8SS_READY, 0),
#endif
    };

    if(prev_subs >= ESP8_ACCESS_POINT_COUNT) 
        return MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART);

    return LUT[prev_subs];
}

void fsm_ap_config(struct StateS *state) {
    enum ESP8AccessPointState nx_state;
    nx_state = SUBSTATE(*state->nx_state);

    switch(nx_state) {
    case ESP8S_RESTART_4AP:
		esp8266_restore();
		*state->wifi_mode = WiFi_SETTINGUP;
		UI_WriteState("Restoring...");
		UI_clear_progress();
		UI_SettingsOn();
		break;

    case ESP8S_ENABLE_AP:
		esp8266_set_CWMODE(ESP8266_CWMODE_STATION_N_SOFTAP);
		UI_clear_progress();
		UI_WriteState("Enabling WiFi");
		break;

    case ESP8S_SET_AP_CREDENTIALS:
		esp8266_set_CWSAP(AP_CREDENTIALS, AP_CREDENTIALS_LEN);
		UI_WriteState("Configurations on WiFi");
		break;
    }
    *state->timeout = 0;
	update_state(*state->nx_state, *state->state);
	UI_set_progress(nx_state, ESP8_ACCESS_POINT_COUNT - 1);
}

uint16_t fsm_station_credentials(struct StateS *s, SSIDnPSWD_t *credentials) {
	esp8266_set_SSID_and_PASS(credentials->ssidNpassword, credentials->size);
	*s->nx_state = MKSTATE(ESP8SS_ON_HOLD, 0);
	*s->state = MKSTATE(ESP8SS_STATION_CREDENTIALS, 0);
	*s->timeout = 0;
	credentials->size = 0;
	UI_WriteState("Trying new SSID");
}
