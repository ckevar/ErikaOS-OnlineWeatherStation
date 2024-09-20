#include "CUnit/Basic.h"

#include "state.h"
#include "network.h"
#include "esp8266_settings.h"
#include "esp8266_client.h"

/* 
 * UNIT: esp8266_client.c
 **/
uint16_t LUT_OK_client(enum ESP8Client prev_subs) {
    uint16_t LUT[ESP8_CLIENT_COUNT] = {
		[ESP8S_CONNECT_SSL] = MKSTATE(ESP8SS_CLIENT, ESP8S_RMALLOC),
        [ESP8S_CONNECT_TCP] = MKSTATE(ESP8SS_CLIENT, ESP8S_RMALLOC),
        [ESP8S_RMALLOC]		= MKSTATE(ESP8SS_ON_HOLD, 0),
        [ESP8S_CWRITE]		= MKSTATE(ESP8SS_ON_HOLD, 0),
        [ESP8S_CLOSE]		= MKSTATE(ESP8SS_CLIENT, ESP8S_DONE),
    };

    if (prev_subs >= ESP8_CLIENT_COUNT)
        return MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART);

    return LUT[prev_subs];
}

void LUT_OK_client_test(void) {
	CU_ASSERT(MKSTATE(ESP8SS_CLIENT, ESP8S_RMALLOC) == LUT_OK_client(ESP8S_CONNECT_SSL));
	CU_ASSERT(MKSTATE(ESP8SS_CLIENT, ESP8S_RMALLOC) == LUT_OK_client(ESP8S_CONNECT_TCP));
	CU_ASSERT(MKSTATE(ESP8SS_ON_HOLD, 0) == LUT_OK_client(ESP8S_RMALLOC));
	CU_ASSERT(MKSTATE(ESP8SS_ON_HOLD, 0) == LUT_OK_client(ESP8S_CWRITE));
	CU_ASSERT(MKSTATE(ESP8SS_CLIENT, ESP8S_DONE) == LUT_OK_client(ESP8S_CLOSE));
	CU_ASSERT(MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART) == LUT_OK_client(ESP8_CLIENT_COUNT));
	CU_ASSERT(MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART) == LUT_OK_client(-1));
}

