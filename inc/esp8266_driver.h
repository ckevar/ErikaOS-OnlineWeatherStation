/*
 * Created Mar 16, 2022
 *  - by ckevar
 * Based on the following documentation: 
 * 		ESP-AT release/v2.2.0.0_esp8266 
 * 		at https://ieee-sensors.org/wp-content/uploads/2018/05/4a-esp8266_at_instruction_set_en.pdf
 */

#ifndef ESP8266_DRIVER_H
#define ESP8266_DRIVER_H 

// ESP8266 Software definitions
#define ESP8266_NUM_LINK 		5
#define ESP8266_BUFF_PER_LINK 	256
#define ESP8266_BUFF_RX_LEN 	1024
#define ESP8266_IP_LEN 			16

#define ESP8266_ST_UNKNOWN_CODE 0	// ESP8266 is in Uknown state ID

/* ESP8266 AT commands */
#define ESP8266_AT 				"AT"
#define ESP8266_AT_LEN 			2

#define ESP8266_AT_RST 			"AT+RST"
#define ESP8266_AT_RST_LEN 		6

#define ESP8266_AT_RESTORE 		"AT+RESTORE"
#define ESP8266_AT_RESTORE_LEN 	10

#define ESP8266_AT_GMR			"AT+GMR"
#define ESP8266_AT_GMR_LEN		6

#define ESP8266_AT_UART_DEF_9600 		"AT+UART_DEF=9600,8,1,0,0"
#define ESP8266_AT_UART_DEF_9600_LEN 	24

#define ESP8266_AT_CIPMUX 				"AT+CIPMUX="
#define ESP8266_AT_CIPMUX_LEN 			10

#define ESP8266_AT_CIPSTART_TCP 		"AT+CIPSTART=\"TCP\","
#define ESP8266_AT_CIPSTART_TCP_LEN 	18

#define ESP8266_AT_CIPSEND_NONMUX 		"AT+CIPSEND="
#define ESP8266_AT_CIPSEND_NONMUX_LEN 	11

#define ESP8266_AT_CIPSEND_MUX 			"AT+CIPSEND=X,"
#define ESP8266_AT_CIPSEND_MUX_X 		11
#define ESP8266_AT_CIPSEND_MUX_LEN 		13

#define ESP8266_AT_CIPCLOSE 			"AT+CIPCLOSE="
#define ESP8266_AT_CIPCLOSE_LEN 		12
#define ESP8266_AT_CIPCLOSE_SINGLE_LEN 	11

#define ESP8266_AT_CIPSERVER_ON_P80 	"AT+CIPSERVER=1,80"
#define ESP8266_AT_CIPSERVER_ON_P80_LEN 17

// Aparently without sending the port, it deletes the web server
#define ESP8266_AT_CIPSERVER_OFF 		"AT+CIPSERVER=0" 
#define ESP8266_AT_CIPSERVER_OFF_LEN 	14

#define ESP8266_AT_CIPSTATUS 			"AT+CIPSTATUS"
#define ESP8266_AT_CIPSTATUS_LEN 		12

#define ESP8266_AT_CWJAP_DEF 			"AT+CWJAP_DEF="
#define ESP8266_AT_CWJAP_DEF_LEN 		13

#define ESP8266_AT_CWMODE 				"AT+CWMODE_DEF="
#define ESP8266_AT_CWMODE_LEN 			14

#define ESP8266_AT_CIPSTA_CUR_GET 		"AT+CIPSTA_CUR?"
#define ESP8266_AT_CIPSTA_CUR_GET_LEN 	14

#define ESP8266_AT_CWSAP 				"AT+CWSAP_DEF="
#define ESP8266_AT_CWSAP_LEN			13

/* ESP8266 AT command responses */
#define ESP8266_ST_OK 			"OK" 	// ESP8266 OK reply
#define ESP8266_ST_OK_LEN 		2		// ESP8266 OK's length
#define ESP8266_ST_OK_CODE 		1		// ESP8266 OK internal status ID


#define ESP8266_ST_ERROR 		"ERROR"	// ESP8266 ERROR reply
#define ESP8266_ST_ERROR_LEN 	5		// ESP8266 ERROR's length 
#define ESP8266_ST_ERROR_CODE 	2		// ESP8266 ERROR internal status ID

#define ESP8266_ST_FAIL 		"FAIL"	// ESP8266 FAIL reply
#define ESP8266_ST_FAIL_LEN 	4		// ESP8266 FAIL's lengh
#define ESP8266_ST_FAIL_CODE 	3		// ESP8266 FAIL internal status ID

#define ESP8266_ST_GOT_IP 		"GOT IP"	// ESP8266 WIFI GOT IP reply
#define ESP8266_ST_GOT_IP_LEN 	6		// ESP8266 WIFI GOT IP reply
#define ESP8266_ST_GOT_IP_CODE 	4		// ESP8266 WIFI GOT IP reply

#define ESP8266_ST_WRAP_CODE 	5		// Wrap symbol

#define ESP8266_ST_HTTP_CLOSED 		"CLOSED" // HTTP Closed
#define ESP8266_ST_HTTP_CLOSED_LEN 	6 	// HTTP Closed
#define ESP8266_ST_HTTP_CLOSED_CODE 6 	// HTTP Closed

#define ESP8266_ST_IPD 			"+IPD"
#define ESP8266_ST_IPD_LEN 		4
#define ESP8266_ST_IPD_CODE		7

#define ESP8266_ST_READY 		"ready"
#define ESP8266_ST_READY_LEN 	5
#define ESP8266_ST_RESTART_CODE 8

#define ESP8266_ST_CIPSTATE_CUR_IP 		"+CIPSTA_CUR:ip"
#define ESP8266_ST_CIPSTATE_CUR_IP_LEN 	14
#define ESP8266_ST_CIPSTATE_CUR_CODE 	9

#define ESP8266_ST_CIPSTATUS_STATUS_STR "STATUS:"
#define ESP8266_ST_CIPSTATUS_STATUS_LEN 7
#define ESP8266_CIPSTATUS_APnIP_READY 	'2'
#define ESP8266_CIPSTATUS_TcpUdp_READY 	'3'
#define ESP8266_CIPSTATUS_TcpUdp_DISCON '4'
#define ESP8266_CIPSTATUS_AP_NO_CONN 	'5'

/* Settings values */
#define ESP8266_CWMODE_STATION 			'1'	
#define ESP8266_CWMODE_SOFTAP 			'2'	
#define ESP8266_CWMODE_STATION_N_SOFTAP '3'
	
#define ESP8266_CIPMUX_SINGLE_CON 	'0' 	// single connection mode
#define ESP8266_CIPMUX_MULTI_CON 	'1'	// Multiple connection mode

/* HTTP Definitions */
#define ESP8266_RESTMethod_UNKNOWN 	 0
#define ESP8266_RESTMethod_GET 		 1
#define ESP8266_RESTMethod_POST 	 2
#define ESP8266_RESTMethod_NO_METHOD 3

/* +IPD STATUS Definitions */
#define ESP8266_IPD_DATA_UKNOWN  	0
#define ESP8266_IPD_DATA_MISSING 	1
#define ESP8266_IPD_DATA_OK2PARSE 	2

/* ESP8266 Types */
typedef struct ESP8266_BUFF_t {
	char RX0[ESP8266_BUFF_RX_LEN];
	char *RX_READ;
	char *RX_END;
	unsigned short RX_LENGTH;
} ESP8266_BUFF_t;

typedef struct ESP8266_Link_t
{
	unsigned char open[ESP8266_NUM_LINK + 1]; 	// max links is 5, so open can only take vals as 0,1,2,3,4
	char buff_in[ESP8266_NUM_LINK * ESP8266_BUFF_PER_LINK]; 	// 256 per link
	char *buff_out;  
	char *buffXlink[ESP8266_NUM_LINK]; 		// the head of each link;
	unsigned short len_out;
	unsigned char n_links;
} ESP8266_Link_t;

typedef struct ESP8266_IPv4_t
{
	char ip[ESP8266_IP_LEN];
	char gateway[ESP8266_IP_LEN];
	char netmask[ESP8266_IP_LEN];
} ESP8266_IPv4_t;

/* ESP8266 Variables */
extern char ESP8266_AT_STATUS;
extern char ESP8266_STATUS_TCP;
extern char ESP8266_STATUS;
extern ESP8266_Link_t ESP8266_link;
extern ESP8266_IPv4_t ESP8266_IPv4;

/* Functions */
void esp8266_init(ESP8266_BUFF_t *buff);
void esp8266_cmd(char *str);

void esp8266_at(void);
void esp8266_restart(void);
void esp8266_restore(void);
void esp8266_gmr(void);

void esp8266_set_CWMODE(char mode);
void esp8266_set_CIPMUX(char mux);
void esp8266_set_SSID_and_PASS(char *ssid_and_pass, unsigned short len);
void esp8266_set_DNS(char *dns, unsigned short len);
void esp8266_set_CIPSEND(char *len_of_data, unsigned short len);
void esp8266_set_CIPSEND_link(char link, char *len_of_data, unsigned short len);
void esp8266_set_CWSAP(char *cmd, unsigned short len);
void esp8266_set_baudrate();
void esp8266_close_tcp(char link);
void esp8266_get_CIPSTATUS(void);
void esp8266_get_CIPSTA_CUR(void);

void esp8266_enable_HTTPServer_P80(void);
void esp8266_disable_HTTPServer_P80(void);
void esp8266_req_HTML(char *http_req, unsigned short len);
void esp8266_load_html(char *html, unsigned short len);
void esp8266_send_html(void);

void esp8266_clean_link_buff(char link);

void esp8266_response(void);

#endif
