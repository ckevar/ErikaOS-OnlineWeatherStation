#include "CUnit/Basic.h"

#include "esp8266_responses.h"
#include "esp8266_driver.h"

static Buffer esp8;
static char ESP8266_SET_RESTART = 0;
struct ESP8266Status esp8_status;

#define esp8266_rx_pop() \
    *esp8.read = 0; \
	esp8.read = esp8.eof == esp8.read \
                ? esp8.data \
                : esp8.read + 1


#define IPD_SIZE_THRESHOLD	1000

#define ESP8266_RESP_WRAP			"\r\n>"
#define ESP8266_RESP_IPD			"\r\n+IPD,x,z:"
#define ESP8266_RESP_ERROR			"\r\nERROR\r\n"
#define ESP8266_RESP_FAIL			"\nFAIL"
#define ESP8266_RESP_OK				"OK\r\n"
#define ESP8266_RESP_ready			"\r\nready"
#define ESP8266_RESP_STATUS			"\r\nSTATUS:X\r\n+CIPSTA:ip "
#define ESP8266_RESP_LINK_CLOSED	"0,CLOSED "

#define LOAD_ESP8266_RESP(resp)		strcpy(esp8.data, resp);\
									esp8.read = esp8.data


void esp8266_poll(void) {
	char *tokens[] = {ESP8_TOKENS};
	static enum ESP8Resp i = ESP8_UNKNOWN;
	static char *token;

	while(*esp8.read != 0) {
		
		switch(i) {
		case ESP8_UNKNOWN:
			/* Order of comparison matters */
			for(i = 0; (i < ESP8_UNKNOWN) && (*esp8.read != *tokens[i]); i++);
			token = tokens[i] + 1;

			/* This holds the unmmatched character, useful when links/
			 * sockets are closed from the remote server, and not by 
			 * command, the ESP8 sends: 
			 *		<x>,CLOSED
			 *	<x> is held */
			if(ESP8_UNKNOWN == i) {
				esp8_status.link = ((*esp8.read & 0x0F) + 1);
			}
			
			break;

		default:
			if (*esp8.read != *token++) {
				i = ESP8_UNKNOWN;
				continue;
			}

			if (*token != 0)
				break;
			
			switch(i) {
			case ESP8_STATUS:
				esp8266_rx_pop();
				i = ESP8_UNKNOWN;
				esp8_status.wifi = *esp8.read;
				continue;

			case ESP8_LINK_CLOSED:
				esp8266_rx_pop();
				esp8_status.cmd = i;
				i = ESP8_UNKNOWN;
				break;
		
			case ESP8_IPData:
				/* 
				 * For the sake of the test: esp8_status.cmd = i; 
				 * On Application, this response has a different
				 * behaviour, unpack the arriving data.
				 * */
				esp8_status.cmd = i;
				esp8266_rx_pop();
				i = ESP8_UNKNOWN;		
				
				break;

			case ESP8_IP:
				esp8266_rx_pop();
				esp8_status.cmd = i;
				i = ESP8_UNKNOWN;
				break;
			
			case ESP8_READY:
				ESP8266_SET_RESTART = 0;

			default:
				esp8266_rx_pop();
				esp8_status.cmd = i;	
				i = ESP8_UNKNOWN;

			}

			return;
			
		}
	
		esp8266_rx_pop();
	}
}

void ESP8266_driver_poll_test(void) {
	char buffer[512] = {0};
	esp8.data = buffer;
	esp8.size = 512;
	esp8.eof = esp8.data + esp8.size - 1;

	LOAD_ESP8266_RESP(ESP8266_RESP_WRAP);
	esp8266_poll();
	CU_ASSERT(ESP8_WRAP == esp8_status.cmd);
	
	LOAD_ESP8266_RESP(ESP8266_RESP_IPD);
	esp8266_poll();
	CU_ASSERT(ESP8_IPData == esp8_status.cmd);
	
	LOAD_ESP8266_RESP(ESP8266_RESP_STATUS);
	esp8266_poll();
	CU_ASSERT('X' == esp8_status.wifi);
	CU_ASSERT(ESP8_IP == esp8_status.cmd);

	LOAD_ESP8266_RESP(ESP8266_RESP_LINK_CLOSED);
	esp8266_poll();
	CU_ASSERT(1 == esp8_status.link);
	CU_ASSERT(ESP8_LINK_CLOSED == esp8_status.cmd);

	LOAD_ESP8266_RESP(ESP8266_RESP_ERROR);
	esp8266_poll();
	CU_ASSERT(ESP8_ERROR == esp8_status.cmd);

	LOAD_ESP8266_RESP(ESP8266_RESP_FAIL);
	esp8266_poll();
	CU_ASSERT(ESP8_FAIL == esp8_status.cmd);

	LOAD_ESP8266_RESP(ESP8266_RESP_OK);
	esp8266_poll();
	CU_ASSERT(ESP8_OK == esp8_status.cmd);

	LOAD_ESP8266_RESP(ESP8266_RESP_ready);
	esp8266_poll();
	CU_ASSERT(ESP8_READY == esp8_status.cmd);
}

