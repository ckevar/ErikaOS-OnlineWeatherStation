#include "CUnit/Basic.h"

#include "state.h"
#include "network.h"
#include "esp8266_driver.h"
#include "esp8266_netstat.h"
#include "esp8266_settings.h"
#include "esp8266_client.h"

struct ESP8266Status esp8_status;

uint16_t LUT_OK_netstat(const enum ESP8NetManagerState superstate) {

    switch(esp8_status.wifi) {
    case WiFi_Ready:
    case TCP_UDP_Lost:
        switch(superstate) {
        case ESP8SS_NETSTATUS:  
        case ESP8SS_CLIENT:
            return MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT_TCP);

        default:
		    return MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART);
        }

    case TCP_UDP_Ready:
		 return MKSTATE(ESP8SS_NETSTATUS, ESP8S_NETKILL);

    case WiFi_No_AP:
        return MKSTATE(ESP8SS_NETSTATUS, ESP8S_IFCONFIG);

	default:
        return MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART);
    }
}

void LUT_OK_netstat_ASSERT_WiFi_Ready___TCP_UDP_Lost(enum WiFiStatus status) {
	esp8_status.wifi = status;
	CU_ASSERT(MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT_TCP) == LUT_OK_netstat(ESP8SS_NETSTATUS));
	CU_ASSERT(MKSTATE(ESP8SS_CLIENT, ESP8S_CONNECT_TCP) == LUT_OK_netstat(ESP8SS_CLIENT));
	CU_ASSERT(MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART) == LUT_OK_netstat(ESP8SS_INIT));
	CU_ASSERT(MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART) == LUT_OK_netstat(ESP8SS_INITIAL_SETUP));
	CU_ASSERT(MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART) == LUT_OK_netstat(ESP8SS_AP));
	CU_ASSERT(MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART) == LUT_OK_netstat(ESP8SS_SERVER));
	CU_ASSERT(MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART) == LUT_OK_netstat(ESP8SS_ON_HOLD));
	CU_ASSERT(MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART) == LUT_OK_netstat(ESP8SS_ERROR));
	CU_ASSERT(MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART) == LUT_OK_netstat(ESP8SS_READY));
	CU_ASSERT(MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART) == LUT_OK_netstat(ESP8SS_STATION_CREDENTIALS));
}

void LUT_OK_netstat_ASSERT_TCP_UDP_Ready___WiFi_No_AP___default(uint16_t output, enum WiFiStatus status) {
	esp8_status.wifi = status;
	CU_ASSERT(output == LUT_OK_netstat(ESP8SS_NETSTATUS));
	CU_ASSERT(output == LUT_OK_netstat(ESP8SS_CLIENT));
	CU_ASSERT(output == LUT_OK_netstat(ESP8SS_INIT));
	CU_ASSERT(output == LUT_OK_netstat(ESP8SS_INITIAL_SETUP));
	CU_ASSERT(output == LUT_OK_netstat(ESP8SS_AP));
	CU_ASSERT(output == LUT_OK_netstat(ESP8SS_SERVER));
	CU_ASSERT(output == LUT_OK_netstat(ESP8SS_ON_HOLD));
	CU_ASSERT(output == LUT_OK_netstat(ESP8SS_ERROR));
	CU_ASSERT(output == LUT_OK_netstat(ESP8SS_READY));
	CU_ASSERT(output == LUT_OK_netstat(ESP8SS_STATION_CREDENTIALS));
}

void LUT_OK_netstat_test(void) {
	LUT_OK_netstat_ASSERT_WiFi_Ready___TCP_UDP_Lost(WiFi_Ready);
	LUT_OK_netstat_ASSERT_WiFi_Ready___TCP_UDP_Lost(TCP_UDP_Lost);
	
	LUT_OK_netstat_ASSERT_TCP_UDP_Ready___WiFi_No_AP___default(
			MKSTATE(ESP8SS_NETSTATUS, ESP8S_NETKILL),
			TCP_UDP_Ready);

	LUT_OK_netstat_ASSERT_TCP_UDP_Ready___WiFi_No_AP___default(
			MKSTATE(ESP8SS_NETSTATUS, ESP8S_IFCONFIG),
			WiFi_No_AP);

	LUT_OK_netstat_ASSERT_TCP_UDP_Ready___WiFi_No_AP___default(
			MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART),
			'1');

	LUT_OK_netstat_ASSERT_TCP_UDP_Ready___WiFi_No_AP___default(
			MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART),
			0);

	LUT_OK_netstat_ASSERT_TCP_UDP_Ready___WiFi_No_AP___default(
			MKSTATE(ESP8SS_INITIAL_SETUP, ESP8S_RESTART),
			'6');
}
