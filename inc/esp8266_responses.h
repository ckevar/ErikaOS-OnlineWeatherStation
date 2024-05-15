#ifndef ESP8266_RESPONSES_H
#define ESP8266_RESPONSES_H

#define ESP8_OK_STR		"OK" 	// ESP8266 OK reply
#define ESP8_OK_LEN 	2		// ESP8266 OK's length

#define ESP8_ERROR_STR	"ERROR"	// ESP8266 ERROR reply
#define ESP8_ERROR_LEN 	5		// ESP8266 ERROR's length 

#define ESP8_FAIL_STR 	"FAIL"	// ESP8266 FAIL reply
#define ESP8_FAIL_LEN 	4		// ESP8266 FAIL's lengh

#define ESP8_GOT_IP_STR	"GOT IP"	// ESP8266 WIFI GOT IP reply
#define ESP8_GOT_IP_LEN 6		// ESP8266 WIFI GOT IP reply

#define ESP8_WRAP_STR   '>'
#define ESP8_WRAP_LEN   1

#define ESP8_LINK_CLOSED_STR 	"CLOSED" // HTTP Closed
#define ESP8_LINK_CLOSED_LEN   8       // HTTP Closed

#define ESP8_IPData_STR	"+IPD"
#define ESP8_IPData_LEN 4

#define ESP8_READY_STR 	"ready"
#define ESP8_READY_LEN 	5

#define ESP8_IP_STR 	"+CIPSTA_CUR:ip"
#define ESP8_IP_LEN 	14

#define ESP8_STATUS_STR "STATUS:"
#define ESP8_STATUS_LEN 7

enum ESP8Resp {
    ESP8_UNKNOWN,   
    ESP8_OK, 		    // ESP8266 OK internal status ID
    ESP8_ERROR,       	// ESP8266 ERROR internal status ID
    ESP8_FAIL, 	        // ESP8266 FAIL internal status ID
    ESP8_GOT_IP, 	    // ESP8266 WIFI GOT IP reply
    ESP8_WRAP, 	        // Wrap symbol
    ESP8_LINK_CLOSED,   // Link Closed
    ESP8_IPData,	    // Arriving data from link
    ESP8_READY,         // Device is ready
    ESP8_IP, 	        // Data contains IP
    ESP8_STATUS,        // WiFI connection status 
    ESP8_RESP_COUNT     // Response Count
};

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
    unsigned char tcp;
    char link;
};

/* STATUS TCP */
#endif

/*

#define ESP8_RESP_OK_STR		"OK" 	// ESP8266 OK reply
#define ESP8_RESP_ERROR_STR		"ERROR"	// ESP8266 ERROR reply
#define ESP8_RESP_FAIL_STR 		"FAIL"	// ESP8266 FAIL reply
#define ESP8_RESP_GOT_IP_STR	"GOT IP"	// ESP8266 WIFI GOT IP reply
#define ESP8_RESP_WRAP_STR      '>'
#define ESP8_RESP_LINK_CLOSED_STR 	"CLOSED" // HTTP Closed
#define ESP8_RESP_IPD_STR		"+IPD"
#define ESP8_RESP_READY_STR 	"ready"
#define ESP8_RESP_IP_STR 		"+CIPSTA_CUR:ip"
#define ESP8_RESP_STATUS_STR    "STATUS:"

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


