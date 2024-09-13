#include "CUnit/Basic.h"

#include "state.h"
#include "network.h"
#include "esp8266_settings.h"

/*
 * UNIT 
 ********************************************************************/
uint16_t LUT_OK_initial_setup(enum ESP8InitialSetup prev_subs) {
    uint16_t LUT[ESP8_INITIAL_SETUP_COUNT] = {
        [ESP8S_RESTART]     = MKSTATE(ESP8SS_ON_HOLD, 0),
        [ESP8S_CHECK_DEV]   = MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_STATION_MODE),
        [ESP8S_STATION_MODE]= MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_MULTI_CONN),
        [ESP8S_MULTI_CONN]  = MKSTATE(ESP8SS_NETSTATUS, 0),
    };

    if (prev_subs >= ESP8_INITIAL_SETUP_COUNT)
        return MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART);

    return LUT[prev_subs];
}

void LUT_OK_initial_setup_test(void) {
	CU_ASSERT(MKSTATE(ESP8SS_ON_HOLD, 0) == LUT_OK_initial_setup(ESP8S_RESTART));
	CU_ASSERT(MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_STATION_MODE) == LUT_OK_initial_setup(ESP8S_CHECK_DEV));
	CU_ASSERT(MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_MULTI_CONN) == LUT_OK_initial_setup(ESP8S_STATION_MODE));
	CU_ASSERT(MKSTATE(ESP8SS_NETSTATUS, 0) == LUT_OK_initial_setup(ESP8S_MULTI_CONN));
	CU_ASSERT(MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART) == LUT_OK_initial_setup(ESP8_INITIAL_SETUP_COUNT));
	CU_ASSERT(MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART) == LUT_OK_initial_setup(-1));
}

/*
 * UNIT
 ********************************************************************/
uint16_t LUT_timeout_initial_setup(enum ESP8InitialSetup prev_subs) {
    uint16_t LUT[ESP8_INITIAL_SETUP_COUNT] = {
        [ESP8S_RESTART]     = MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART),
        [ESP8S_CHECK_DEV]   = MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART),
        [ESP8S_STATION_MODE]= MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_CHECK_DEV),
        [ESP8S_MULTI_CONN]  = MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_CHECK_DEV),
    };

    if (prev_subs >= ESP8_INITIAL_SETUP_COUNT) 
        return MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_CHECK_DEV);
    
    return LUT[prev_subs];
}

void LUT_timeout_initial_setup_test(void) {
	CU_ASSERT(MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART) == LUT_timeout_initial_setup(ESP8S_RESTART));
	CU_ASSERT(MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART) == LUT_timeout_initial_setup(ESP8S_CHECK_DEV));
	CU_ASSERT(MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_CHECK_DEV) == LUT_timeout_initial_setup(ESP8S_STATION_MODE));
	CU_ASSERT(MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_CHECK_DEV) == LUT_timeout_initial_setup(ESP8S_MULTI_CONN));
	CU_ASSERT(MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_CHECK_DEV) == LUT_timeout_initial_setup(ESP8_INITIAL_SETUP_COUNT));
	CU_ASSERT(MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_CHECK_DEV) == LUT_timeout_initial_setup(-1));
}

/*
 * UNIT
 ********************************************************************/
uint16_t LUT_on_err_initial_setup(enum ESP8InitialSetup prev_subs) {
    uint16_t LUT[ESP8_INITIAL_SETUP_COUNT] = {
        [ESP8S_RESTART]     = MKSTATE(ESP8SS_ON_HOLD, 0),
        [ESP8S_CHECK_DEV]   = MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART),
        [ESP8S_STATION_MODE]= MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_CHECK_DEV),
        [ESP8S_MULTI_CONN]  = MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_CHECK_DEV)
    };

    if(prev_subs >= ESP8_INITIAL_SETUP_COUNT) {
        return MKSTATE(ESP8SS_ERROR, 0);
	}

    return LUT[prev_subs];
}

void LUT_on_err_test(void) {
	CU_ASSERT(MKSTATE(ESP8SS_ON_HOLD, 0) == LUT_on_err_initial_setup(ESP8S_RESTART));
	CU_ASSERT(MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART) == LUT_on_err_initial_setup(ESP8S_CHECK_DEV));
	CU_ASSERT(MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_CHECK_DEV) == LUT_on_err_initial_setup(ESP8S_STATION_MODE));
	CU_ASSERT(MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_CHECK_DEV) == LUT_on_err_initial_setup(ESP8S_MULTI_CONN));
	CU_ASSERT(MKSTATE(ESP8SS_ERROR, 0) == LUT_on_err_initial_setup(ESP8_INITIAL_SETUP_COUNT));
	CU_ASSERT(MKSTATE(ESP8SS_ERROR, 0) == LUT_on_err_initial_setup(-1));
}
