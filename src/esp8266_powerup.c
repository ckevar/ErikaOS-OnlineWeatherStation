#include "state.h"
#include "esp8266_driver.h"
#include "esp8266_responses.h"
#include "esp8266_powerup.h"
#include "WidgetConfig.h"

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

void fsm_powerup(struct StateS *state) {
    enum ESP8NetManagerState nx_state;
    uint8_t timeout_waiting;
    nx_state = SUBSTATE(*state->nx_state);
    
    switch(nx_state) {
    case ESP8S_RESTART:
		// Restarts the ESP8266
		UI_WriteState("Restarting");
		esp8266_restart();
		*state->wifi_mode = WiFi_SETTINGUP;
		UI_clear_progress();
		UI_WiFiNo();
		update_state(*state->nx_state, *state->state);
		break;

	case ESP8S_CHECK_DEV:
		// Sends AT to know if the ESP8266 is available
		UI_WriteState("Check WiFi Dev");
		UI_set_progress(nx_state, ESP8_INITIAL_SETUP_COUNT - 1);
		UI_WiFiNo();
		esp8266_at();
		update_state(*state->nx_state, *state->state);
		break;

    case ESP8S_STATION_MODE:
		// Sets the ESP8266 to work as a WiFi station
        UI_clear_progress();
		UI_WriteState("Station mode");
		esp8266_set_CWMODE(ESP8266_CWMODE_STATION);
		UI_set_progress(nx_state, ESP8_INITIAL_SETUP_COUNT - 1);
		update_state(*state->nx_state, *state->state);		
		break;

	case ESP8S_MULTI_CONN:
	    UI_WriteState("Force Multi Connection");
		esp8266_set_CIPMUX(ESP8266_CIPMUX_MULTI_CON);
		UI_set_progress(nx_state, ESP8_INITIAL_SETUP_COUNT - 1);
		update_state(*state->nx_state, *state->state);
		break;
    }
    *state->timeout = timeout_waiting;
}
