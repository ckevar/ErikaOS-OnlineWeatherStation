#ifndef ESP8266_RESPONSES_H
#define ESP8266_RESPONSES_H

#include "http.h"

enum ESP8Resp {
    ESP8_WRAP, 	        // Wrap symbol
    ESP8_IPData,	    // Arriving data from link
    ESP8_IP, 	        // Data contains IP
    ESP8_LINK_CLOSED,   // Link Closed
    ESP8_ERROR,       	// ESP8266 ERROR internal status ID
    ESP8_FAIL, 	        // ESP8266 FAIL internal status ID
    ESP8_OK, 		    // ESP8266 OK internal status ID
    ESP8_STATUS,        // WiFI connection status 
    ESP8_READY,         // Device is ready
    ESP8_UNKNOWN,   
    ESP8_DATA_PULLIN,    // Data itself
};

/*																	*
 * CONDITIONS FOR TOKENS:											*
 * ----------------------											*
 * 1. All tokens shall start with different characters 
 * 2. No token shall start with a NULL character 
 * 3. the last token (ESP8_UNKNOWN) us a NULL character				
 *																	*/
#define ESP8_TOKENS		[ESP8_WRAP]			= "\n>",\
						[ESP8_IPData]		= "IPD,",\
						[ESP8_IP]			= "+CIPSTA:ip",\
						[ESP8_LINK_CLOSED]	= ",CLOSED",\
						[ESP8_ERROR]		= "ERROR",\
						[ESP8_FAIL]			= "FAIL",\
						[ESP8_OK]			= "OK",\
						[ESP8_STATUS]		= "STATUS:",\
						[ESP8_READY]		= "ready",\
						[ESP8_UNKNOWN]		= NULL


enum WiFiStatus {
    Unknown = 0,
    WiFi_Ready = '2',
    TCP_UDP_Ready,
    TCP_UDP_Lost,
    WiFi_No_AP,
};

enum ESP8Tcp {
    TCP_BUFF_FULL = 0b01,
    TCP_PORT_CLOSE = 0b10,
};


struct ESP8266Status {
    enum ESP8Resp cmd;
    enum WiFiStatus wifi;
	enum HTTPStatusCode http;
    unsigned char tcp;
    char link;
};

struct ESP8IPData {
	uint16_t size;
	uint8_t status;
	char *buff_link;
};

#endif

/* 
List of Reponses to AT commands:

>   -> <wrap symbol>
+   -> "+IPD", "+CIPSTA_CUR:ip"
,   -> "X,CLOSED"
_   -> "+CIPSTA_CUR:ip"
:   -> "+CIPSTA_CUR:ip", "STATUS:"end
0   -> "X,CLOSED"
1   -> "X,CLOSED"
2   -> "X,CLOSED"
3   -> "X,CLOSED"
4   -> "X,CLOSED"
A   -> "FAIL", "+CIPSTA_CUR:ip", "STATUS:"
C   -> "X,CLOSED", "+CIPSTA_CUR:ip"
D   -> "X,CLOSED"end, "+IPD"end
E   -> "ERROR", "X,CLOSED"
F   -> "FAIL"
I   -> "FAIL", "+IPD", "+CIPSTA_CUR:ip"
L   -> "FAIL"end, "X,CLOSED"
O   -> "OK", "ERROR", "X,CLOSED"
P   -> "+IPD", "+CIPSTA_CUR:ip"
R   -> "+CIPSTA_CUR:ip"
S   -> "X,CLOSED", "+CIPSTA_CUR:ip", "STATUS:"
T   -> "+CIPSTA_CUR:ip", "STATUS:"
U   -> "+CIPSTA_CUR:ip", "STATUS:"
K   -> "OK"end
R   -> "ERROR", "ERROR"end
a   -> "ready"
e   -> "ready"
d   -> "ready"
i   -> "+CIPSTA_CUR:ip"
p   -> "+CIPSTA_CUR:ip"end
r   -> "ready"
y   -> "ready"

*/


