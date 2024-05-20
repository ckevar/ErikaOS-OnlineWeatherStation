#include "state.h"
#include "esp8266_driver.h"
#include "esp8266_responses.h"
#include "esp8266_powerup.h"
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
		UI_WriteState("Restarting");
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


void fsm_ap_config(struct StateS *state) {
    enum ESP8AccessPointState nx_state;
    nx_state = SUBSTATE(*state->nx_state);

    switch(nx_state) {
    case ESP8S_RESTART_4AP:
		esp8266_restart();
		*state->wifi_mode = WiFi_SETTINGUP;
		UI_WriteState("Restarting...");
		UI_clear_progress();
		UI_SettingsOn();
		break;

    case ESP8S_ENABLE_AP:
		esp8266_set_CWMODE(ESP8266_CWMODE_STATION_N_SOFTAP);
		UI_clear_progress();
		UI_WriteState("Enabling WiFi");
		break;

    case ESP8S_SET_CREDENTIALS:
		esp8266_set_CWSAP(AP_CREDENTIALS, AP_CREDENTIALS_LEN);
		UI_WriteState("Configurations on WiFi");
		break;
    }
    *state->timeout = 0;
	update_state(*state->nx_state, *state->state);
	UI_set_progress(nx_state, ESP8_ACCESS_POINT_COUNT - 1);
}
