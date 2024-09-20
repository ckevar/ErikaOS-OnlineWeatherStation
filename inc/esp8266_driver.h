/*
 * Created Mar 16, 2022
 *  - by ckevar
 * Based on the following documentation: 
 * 		ESP-AT release/v2.2.0.0_esp8266 
 * 		at https://ieee-sensors.org/wp-content/uploads/2018/05/4a-esp8266_at_instruction_set_en.pdf
 */

#ifndef ESP8266_DRIVER_H
#define ESP8266_DRIVER_H 

#include "esp8266_responses.h"

// ESP8266 Software definitions
#define ESP8266_NUM_LINK				5
#define ESP8266_BUFF_PER_LINK			1840
#define ESP8266_BUFF_RX_LEN				9216
#define ESP8266_IP_LEN					16

/* ESP8266 AT commands */
#define ESP8_AT_STRLEN(x)				(sizeof(x) - 1)
#define ESP8266_AT						"AT"
#define ESP8266_AT_LEN					ESP8_AT_STRLEN(ESP8266_AT)

#define ESP8266_AT_RST					"AT+RST"
#define ESP8266_AT_RST_LEN				ESP8_AT_STRLEN(ESP8266_AT_RST)

#define ESP8266_AT_RESTORE				"AT+RESTORE"
#define ESP8266_AT_RESTORE_LEN			ESP8_AT_STRLEN(ESP8266_AT_RESTORE)

#define ESP8266_AT_GMR					"AT+GMR"
#define ESP8266_AT_GMR_LEN				ESP8_AT_STRLEN(ESP8266_AT_GMR)

#define ESP8266_AT_UART_DEF_9600 		"AT+UART_DEF=9600,8,1,0,0"
#define ESP8266_AT_UART_DEF_9600_LEN 	ESP8_AT_STRLEN(ESP8266_AT_UART_DEF_9600)

#define ESP8266_AT_CIPMUX 				"AT+CIPMUX="
#define ESP8266_AT_CIPMUX_LEN 			ESP8_AT_STRLEN(ESP8266_AT_CIPMUX)

#define ESP8266_AT_CIPSTART_TCP 		"AT+CIPSTART=x,\"TCP\","
#define ESP8266_AT_CIPSTART_LEN			ESP8_AT_STRLEN(ESP8266_AT_CIPSTART_TCP)
#define ESP8266_AT_CIPSTART_LINK		12

#define ESP8266_AT_CIPSTART_SSL			"AT+CIPSTART=x,\"SSL\","

#define ESP8266_AT_CIPSEND_NONMUX 		"AT+CIPSEND="
#define ESP8266_AT_CIPSEND_NONMUX_LEN 	ESP8_AT_STRLEN(ESP8266_AT_CIPSEND_NONMUX)

#define ESP8266_AT_CIPSEND_MUX 			"AT+CIPSEND=X,"
#define ESP8266_AT_CIPSEND_MUX_X 		11
#define ESP8266_AT_CIPSEND_MUX_LEN 		ESP8_AT_STRLEN(ESP8266_AT_CIPSEND_MUX)

#define ESP8266_AT_CIPCLOSE 			"AT+CIPCLOSE="
#define ESP8266_AT_CIPCLOSE_LEN 		ESP8_AT_STRLEN(ESP8266_AT_CIPCLOSE)
#define ESP8266_AT_CIPCLOSE_SINGLE_LEN 	11

#define ESP8266_AT_CIPSERVER_ON_P80 	"AT+CIPSERVER=1,80"
#define ESP8266_AT_CIPSERVER_ON_P80_LEN ESP8_AT_STRLEN(ESP8266_AT_CIPSERVER_ON_P80)

#define ESP8266_AT_CIPSERVER_OFF 		"AT+CIPSERVER=0" 
#define ESP8266_AT_CIPSERVER_OFF_LEN 	ESP8_AT_STRLEN(ESP8266_AT_CIPSERVER_OFF)

#define ESP8266_AT_CIPSTATUS 			"AT+CIPSTATUS"
#define ESP8266_AT_CIPSTATUS_LEN 		ESP8_AT_STRLEN(ESP8266_AT_CIPSTATUS)

/* AT v2.2.1 {														*/
#define ESP8266_AT_CWJAP				"AT+CWJAP="
#define ESP8266_AT_CWJAP_LEN			ESP8_AT_STRLEN(ESP8266_AT_CWJAP)

#define ESP8266_AT_CWMODE 				"AT+CWMODE="
#define ESP8266_AT_CWMODE_LEN 			ESP8_AT_STRLEN(ESP8266_AT_CWMODE)

#define ESP8266_AT_CIPSTA_GET			"AT+CIPSTA?"
#define ESP8266_AT_CIPSTA_GET_LEN		ESP8_AT_STRLEN(ESP8266_AT_CIPSTA_GET)

#define ESP8266_AT_CWSAP 				"AT+CWSAP="
#define ESP8266_AT_CWSAP_LEN			ESP8_AT_STRLEN(ESP8266_AT_CWSAP)
/* }																*/

/* Settings values */
#define ESP8266_CWMODE_STATION 			'1'	
#define ESP8266_CWMODE_SOFTAP 			'2'	
#define ESP8266_CWMODE_STATION_N_SOFTAP '3'
	
#define ESP8266_CIPMUX_SINGLE_CON		'0' 	// single connection mode
#define ESP8266_CIPMUX_MULTI_CON		'1'	// Multiple connection mode

/* +IPD STATUS Definitions */
enum {
	IPData_UKNOWN,
	IPData_WAIT,
	IPData_OK2PARSE,
	IPData_DUMMY,
	IPData_DUMMY2,
	IPData_WAIT_FOR_CONTENT_LENGTH,
};

/* ESP8266 Types */
typedef struct {
	char *data;
	char *read;
	char *eof;
	unsigned short size;
} Buffer;

typedef struct ESP8266_Link_t {
	unsigned char open[ESP8266_NUM_LINK + 1]; 	// max links is 5, so open can only take vals as 0,1,2,3,4
	char buff_in[ESP8266_NUM_LINK * ESP8266_BUFF_PER_LINK]; 	// 256 per link
	char *buff_out;  
	char *buffXlink[ESP8266_NUM_LINK]; 		// the head of each link;
	unsigned short len_out;
	unsigned char n_links;
} ESP8266_Link_t;

typedef struct ESP8266_IPv4_t {
	char ip[ESP8266_IP_LEN];
	char gateway[ESP8266_IP_LEN];
	char netmask[ESP8266_IP_LEN];
} ESP8266_IPv4_t;

/* ESP8266 Variables */
extern struct ESP8266Status esp8_status;
extern ESP8266_Link_t ESP8266_link;
extern ESP8266_IPv4_t ESP8266_IPv4;

/* Functions */
void esp8266_init(void);
void esp8266_cmd(char *str);

void esp8266_at(void);
void esp8266_restart(void);
void esp8266_restore(void);
void esp8266_gmr(void);

void esp8266_set_CWMODE(char mode);
void esp8266_set_CIPMUX(char mux);
void esp8266_set_SSID_and_PASS(char *ssid_and_pass, unsigned short len);

void esp8266_cipstart(char *type, char link, char *host, unsigned short len);
#define esp8266_tcp(link, host, len)	\
	esp8266_cipstart(ESP8266_AT_CIPSTART_TCP, link, host, len);
#define esp8266_ssl(link, host, len)	\
	esp8266_cipstart(ESP8266_AT_CIPSTART_SSL, link, host, len);

void esp8266_set_CIPSEND(char *len_of_data, unsigned short len);
void esp8266_set_CIPSEND_link(char link, char *len_of_data, unsigned short len);
void esp8266_set_CWSAP(char *cmd, unsigned short len);
void esp8266_set_baudrate();
void esp8266_close_tcp(char link);
void esp8266_get_CIPSTATUS(void);
void esp8266_get_CIPSTA(void);

void esp8266_enable_HTTPServer_P80(void);
void esp8266_disable_HTTPServer_P80(void);
void esp8266_req_HTML(char *http_req, unsigned short len);
void esp8266_load_html(char *html, unsigned short len);
void esp8266_send_html(void);

// void esp8266_clean_link_buff(char link);
void esp8266_purge_link_buff(void);

void esp8266_poll(void);

#endif
