/*
 * Created Mar 16, 2022
 *  - by ckevar
 */
#include <string.h>
#include "stm32f4_discovery.h"

#include "esp8266_driver.h"
#include "esp8266_responses.h"
#include "http.h"

#include "lcd_log.h"

// Disable DMA for transmission
#define esp82266_dma_TX_disable()					DMA2_Stream6->CR &= ~0x01;\
													while((DMA2_Stream6->CR & 0x01));
// Set length for DMA and Enables it
#define esp8266_dma_set_length_and_enableTX(length) DMA2_Stream6->NDTR = (uint32_t) length;\
													while((~DMA2_Stream6->CR & 0x01)) DMA2_Stream6->CR |= DMA_SxCR_EN;

struct ESP8266Status esp8_status;
static Buffer esp8;
static char esp8_TX[750];
static char esp8_RX[ESP8266_BUFF_RX_LEN];
static char ESP8266_SET_RESTART = 0; 
ESP8266_Link_t ESP8266_link;
ESP8266_IPv4_t ESP8266_IPv4;

static void esp8266_USART_RX_DMA_Init(char *BUFF_L, uint16_t size);
static void esp8266_USART_TX_DMA_Init(void);

void esp8266_init(void) {
	USART_InitTypeDef USART_InitStructure;
	/* USARTx configured as follow:
		- BaudRate = 115200 baud
		- Word Length = 8 Bits
		- One Stop Bit
		- No parity
		- Hardware flow control disabled (RTS and CTS signals)
		- Receive and transmit enabled
	*/
	USART_InitStructure.USART_BaudRate = 115273;
	// 115200 by default 116641 to 116666 109600 to 121000 // 115273
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;


	STM_EVAL_COMInit(COM1, &USART_InitStructure);

	/* DMA for Reception on COM1/USART6 */
	EVAL_COM1->CR3 |= USART_CR3_DMAT;	
	esp8266_USART_TX_DMA_Init();

	/* DMA for Transmision on COM1/USART6 */
	EVAL_COM1->CR3 |= USART_CR3_DMAR;
    esp8.data = esp8_RX;
	esp8.read = esp8.data;
	esp8.size = ESP8266_BUFF_RX_LEN;
	esp8.eof = esp8.data + esp8.size - 1;
	esp8266_USART_RX_DMA_Init(esp8.data, esp8.size);

	/* Start Link Buffer */
	memset(ESP8266_link.open, '\0', ESP8266_NUM_LINK);
	memset(ESP8266_link.buff_in, '\0', ESP8266_NUM_LINK * ESP8266_BUFF_PER_LINK);

	for (unsigned char i = 0; i < ESP8266_NUM_LINK; ++i) 
		ESP8266_link.buffXlink[i] = ESP8266_link.buff_in + i * ESP8266_BUFF_PER_LINK;
	ESP8266_link.n_links = 0;

	/* start IP type */
	memset(ESP8266_IPv4.ip, '\0', ESP8266_IP_LEN);
	memset(ESP8266_IPv4.gateway, '\0', ESP8266_IP_LEN);
	memset(ESP8266_IPv4.netmask, '\0', ESP8266_IP_LEN);

    esp8_status.cmd = ESP8_UNKNOWN;
    esp8_status.wifi = Unknown;

}

static void esp8266_USART_TX_DMA_Init(void) {
	/* DMA for USART6_TX -> DMA2, stream 6, channel 5 */
	
	/* Enable Clock for DMA2 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	DMA2_Stream6->CR = 0x0;					
	while(DMA2_Stream6->CR);
	DMA2_Stream6->CR |= 0x0A000000;			// SPI2_RX on DMA2 stream 6 channel 5
	DMA2_Stream6->CR &= 0xFFFF9FFF;			// USART data size is 8 bits
	DMA2_Stream6->CR &= 0xFFFFE7FF;			// Memory data size is 8 bits
	DMA2_Stream6->CR &= ~DMA_SxCR_DBM;		// No buffer switching
	DMA2_Stream6->CR |= DMA_SxCR_MINC;		// Automatic Memory Increment
	DMA2_Stream6->CR &= ~DMA_SxCR_CIRC;		// No Circular Mode on transmision
	DMA2_Stream6->CR |= 0x1 << 6;			// Memory to Peripheral
	DMA2_Stream6->CR |= DMA_SxCR_PL;		// Priority High;
	DMA2_Stream6->FCR &= ~DMA_SxFCR_DMDIS;	// Direct Mode (FIFO Disabled)

	DMA2_Stream6->PAR = (uint32_t) &(EVAL_COM1->DR);	// Peripheral Base Address
	DMA2_Stream6->M0AR = (uint32_t) esp8_TX;// Memory base address 0
	DMA2_Stream6->NDTR = 0;					// NUmber of data per transfer
	
	/* This is important, because it's not a one time sent but many. */
	DMA2_Stream6->CR |= DMA_SxCR_TCIE;		// Enable complete interruption
	/* Inturruptions, uncomment for debugging */
	// DMA2_Stream6->CR |= DMA_SxCR_TEIE;	// Enable Error Transfer interruption
	// DMA2_Stream6->CR |= DMA_SxCR_DMEIE;	// Enable Error Transfer interruption
	/******************************************/
	
	DMA2_Stream6->CR |= DMA_SxCR_EN;	// Disable Configuration Register
}

static void esp8266_USART_RX_DMA_Init(char *BUFF_L, uint16_t size) {
	/* DMA for USART6_RX -> DMA 2, Stream 1, Channel 5 */
	
	/* Enable DMA1 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	DMA2_Stream1->CR = 0x0;				
	while(DMA2_Stream1->CR);

	DMA2_Stream1->CR |= 0x0A000000;			// SPI2_RX on DMA2 stream 1 channel 5
	DMA2_Stream1->CR &= 0xFFFF9FFF;			// USART data size is 8 bits
	DMA2_Stream1->CR &= 0xFFFFE7FF;			// Memory data size is 8 bits
	DMA2_Stream1->CR &= ~DMA_SxCR_DBM;		// No buffer switching
	DMA2_Stream1->CR |= DMA_SxCR_MINC;		// Automatic Memory Increment
	DMA2_Stream1->CR |= DMA_SxCR_CIRC;		// Circular Mode at Reception
	DMA2_Stream1->CR &= ~DMA_SxCR_DIR;		// Peripheral to Memory
	DMA2_Stream1->CR |= DMA_SxCR_PL;		// Priority High;
	DMA2_Stream1->FCR &= ~DMA_SxFCR_DMDIS;	// Direct Mode (FIFO Disabled)

	DMA2_Stream1->PAR = (uint32_t) &(EVAL_COM1->DR);	// Peripheral Base Address
	DMA2_Stream1->M0AR = (uint32_t) BUFF_L;	// Memory base address 0
	DMA2_Stream1->NDTR = (uint32_t) size;	// NUmber of data per transfer
	
	/* Interruptions, uncomment for debugging */
	// DMA2_Stream1->CR |= DMA_SxCR_TCIE; 	// Transfer full interrupt
	// DMA2_Stream1->CR |= DMA_SxCR_TEIE; 	// Transfer error interrupt
	// DMA2_Stream1->CR |= DMA_SxCR_DMEIE; 	// Transfer error interrupt
	/******************************************/

	DMA2_Stream1->CR |= DMA_SxCR_EN;			// Disable Configuration Register
}


static void esp8266_dma_cmd(char *str, unsigned short length) {
	esp82266_dma_TX_disable();
	memcpy(esp8_TX, str, length);
	esp8266_dma_set_length_and_enableTX(length);
} 

#define esp8266_cmd(cmd, arg, arg_len) esp8266_dma_cmd_mul_param(cmd, cmd##_LEN, arg, arg_len)

/*
 * Forms a command to be sent, appending \r\n, when no parameter is sent
 * arg_len has to be 0.
 * if arg_len is smaller than zero, \r\n wont be appende to the message,
 * this makes when suppling HTML data to the ESP8266
 ************************************************************************/ 
static void
esp8266_dma_cmd_mul_param(char *cmd, unsigned short cmd_len, char *arg, short arg_len)
{
	esp82266_dma_TX_disable();

	memcpy(esp8_TX, cmd, cmd_len);

	if (arg_len >= 0) {
		if (1 == arg_len)
			// No need to use memcpy when the parameter is only one char
			*(esp8_TX + cmd_len) = *arg;

		else if (arg_len > 1)
			memcpy(esp8_TX + cmd_len, arg, arg_len);

		cmd_len += arg_len;
		*(esp8_TX + cmd_len) = 13;
		cmd_len++;
		*(esp8_TX + cmd_len) = 10;
		cmd_len++;
	} 

	esp8266_dma_set_length_and_enableTX(cmd_len);	
}

void esp8266_at(void) {
	esp8266_cmd(ESP8266_AT, NULL, 0);
}

void esp8266_restart(void) {
    memset(esp8.data, 0, ESP8266_BUFF_RX_LEN);
	esp8266_cmd(ESP8266_AT_RST, NULL, 0);
	ESP8266_SET_RESTART = 1;
}

void esp8266_restore(void) {
	esp8266_cmd(ESP8266_AT_RESTORE, NULL, 0);	
	ESP8266_SET_RESTART = 1;
}

void esp8266_gmr(void){
	esp8266_cmd(ESP8266_AT_GMR, NULL, 0);
}

void esp8266_get_CIPSTA(void) {
	esp8266_cmd(ESP8266_AT_CIPSTA_GET, NULL, 0);	
}

void esp8266_set_CWMODE(char mode) {
	// "mode" can be '0', '1', '2', '3'
	esp8266_cmd(ESP8266_AT_CWMODE, &mode, 1);
}


void esp8266_set_CIPMUX(char mux) {
	// "mux" shall be '0', '1'
	esp8266_cmd(ESP8266_AT_CIPMUX, &mux, 1);
}

void esp8266_close_tcp(char link){
	// 'link' shall be: 0, '0', '1', '2', '3' or '4'
    if (link >= 0) {
        link += 48;
        esp8266_cmd(ESP8266_AT_CIPCLOSE, &link, 1);
    }
    else 
        esp8266_dma_cmd_mul_param(ESP8266_AT_CIPCLOSE, ESP8266_AT_CIPCLOSE_SINGLE_LEN, NULL, 0);
}

void esp8266_enable_HTTPServer_P80(void) {
	// Enables HTTP server at port 80
	esp8266_cmd(ESP8266_AT_CIPSERVER_ON_P80, NULL, 0);
}

void esp8266_disable_HTTPServer_P80(void) {
	// Disable HTTP server at port 80
	esp8266_cmd(ESP8266_AT_CIPSERVER_OFF, NULL, 0);
}

void esp8266_set_SSID_and_PASS(char *ssid_and_pass, unsigned short len) {
	// "len" is  the length of the SSID and password including quotes 
	// and comas
	esp8266_cmd(ESP8266_AT_CWJAP, ssid_and_pass, len);
}


void esp8266_cipstart(char *type, char linkid, char *host, unsigned short len) {
	char tmp[ESP8266_AT_CIPSTART_LEN];

	memcpy(tmp, type, ESP8266_AT_CIPSTART_LEN);
	tmp[ESP8266_AT_CIPSTART_LINK] = linkid + 48;
	esp8266_dma_cmd_mul_param(tmp, ESP8266_AT_CIPSTART_LEN,\
		host, len);
}

void esp8266_set_CIPSEND(char *len_of_data, unsigned short len) {
	// CIPSEND for single connection setting
	esp8266_cmd(ESP8266_AT_CIPSEND_NONMUX, len_of_data, len);
}

void esp8266_set_CIPSEND_link(char link, char *len_of_data, unsigned short len) {
	// char "link" shall a number 0, 1, 2, 3, or 4 
	char tmp[ESP8266_AT_CIPSEND_MUX_LEN] = ESP8266_AT_CIPSEND_MUX;
	tmp[ESP8266_AT_CIPSEND_MUX_X] = link + 48; 	// cast number value to char
	esp8266_dma_cmd_mul_param(tmp, ESP8266_AT_CIPSEND_MUX_LEN, len_of_data, len);
}

void esp8266_set_CWSAP(char *cmd, unsigned short len) {
	esp8266_cmd(ESP8266_AT_CWSAP, cmd, len);
}

void esp8266_set_baudrate_9600(void){
	/* Dangerous AT command, even some official firmwares can brick 
	 * the ESP, so, they have to be re-flashed. This command works 
	 * with the following firmware AT_firmware_1.6.2.0.bin post it by
	 * Adafruit. Even though, currently the ESP8266 are running AT 
	 * v2.2.1 no risks are taken in bricking the modules.
	 */ 
	esp8266_cmd(ESP8266_AT_UART_DEF_9600, NULL, 0);
}

void esp8266_get_CIPSTATUS(void) {
	esp8266_cmd(ESP8266_AT_CIPSTATUS, NULL, 0);
}


void esp8266_req_HTML(char *http_req, unsigned short len) {
	esp8266_dma_cmd_mul_param(http_req, len, NULL, -1);
}

void esp8266_load_html(char *html, unsigned short len) {
	ESP8266_link.buff_out = html;
	ESP8266_link.len_out = len;
}

void esp8266_send_html(void) {
	esp8266_dma_cmd_mul_param(ESP8266_link.buff_out, ESP8266_link.len_out, NULL, -1);
}


void esp8266_clean_link_buff(char link) {
	// Link can be a num 0, 1, 2, 3 o 4
	memset(ESP8266_link.buffXlink[link], '\0', ESP8266_BUFF_PER_LINK);
}

void esp8266_purge_link_buff(void) {
	memset(ESP8266_link.buffXlink[0], 0, ESP8266_BUFF_PER_LINK * ESP8266_NUM_LINK);
}

/************************ RESPONSE PARSER ***************************/
#define esp8266_rx_pop() \
    *esp8.read = 0; \
	esp8.read = esp8.eof == esp8.read \
                ? esp8.data \
                : esp8.read + 1

static void esp8266_rx_N_pop(uint16_t it) {
    while (it) { 
        esp8266_rx_pop();
		it--;
	}
}

static uint16_t es8266_rx_pop_til(char const *str, int const size) {
	char *sn;
	int ni, i;	
	i = esp8.read - esp8.data;

goto_FUNC_es8266_rx_pop_til_FILE_esp8266_driver:
	ni = (i + size + 1) % ESP8266_BUFF_RX_LEN;
	for(sn = (char *)str; *(esp8.data + ni - 1) && *sn;) {
		i++;
		esp8266_rx_pop(); 
		if(*esp8.read != *sn) {
			goto goto_FUNC_es8266_rx_pop_til_FILE_esp8266_driver;
		}
		sn++;
	}

	esp8266_rx_pop();

	if (*sn != 0) {
		return 1;
	}

	/* Found it */
	return 0;
}

#define MAX_TICKOUT			65535    // Experimental value, it's like time out
#define RECOMMENDED_TICKOUT	2048
static uint16_t 
esp8266_rx_wait_ahead(uint16_t const size, uint16_t const tickout) {
	/* This doesn't need performance, instead we need to buy some time
	 * in order to catch the data, that's why the variables arent tag 
	 * as *register*. So basically, in ipd, it's just there to buy some
	 * time and in content length to really wait. */
	char *sc;
	uint16_t multi_use;

    multi_use = esp8.read - esp8.data;
    multi_use = (multi_use + size) % ESP8266_BUFF_RX_LEN;
	
	if (!multi_use) 
		multi_use = esp8.size;

	sc = esp8.data + multi_use - 1;
    for(multi_use = 0; (0 == *sc) && (multi_use < tickout); multi_use++);

	if(0 == *sc)
		return size;

	return 0;
}

#define esp8266_rx_to_uint(num)	\
	num = 0; \
	while(*esp8.read >= '0' && *esp8.read <= '9') {\
		num = num * 10 + *esp8.read - 48;\
		esp8266_rx_pop();\
	}\

/*
 * gets method on the http arrival data, only GET and POST supported
 */
char tmp_test[128];
static unsigned char esp8266_http_get_method(void) {
	uint8_t method;
	
	if (*esp8.read < 'A' || *esp8.read > 'Z')
		return HTTP_Method_UNKNOWN;
	
	/* Hashin method */
	method = *esp8.read;
	esp8266_rx_N_pop(3);
	method ^= *esp8.read;

	while(*esp8.read != ' ') {
		esp8266_rx_pop();
	}

	esp8266_rx_pop();

	return method;
}

static uint16_t esp8266_http_get_Resource(char *res) {
	uint16_t i = 0;
	// Forward cursors until to catch the resource needed started
	while(*esp8.read != '/') {
        esp8266_rx_pop();
    }
	// Forward cursor until all resource requested are acquired;
	while(*esp8.read != ' ') {
		res[i] = *esp8.read;
		i++;
        esp8266_rx_pop();
	}

	res[i] = 0;

	return i + 1;
}

static uint16_t esp8266_http_get_ContentLength(void) {
	uint16_t size;

	if(es8266_rx_pop_til(HTTP_CONTENT_LEN_STR, strlen(HTTP_CONTENT_LEN_STR)))
		return 0;
	
	esp8266_rx_wait_ahead(5, MAX_TICKOUT);

	esp8266_rx_to_uint(size);

	return size;
}


static void esp8266_http_skip_header(void) {
	es8266_rx_pop_til("\r\n\r\n", 4);

	/*
	 * ESP8266's message starts with "\r\n\r\n", as well as HTTP header
	 * ending. So, in case it's not the header that ended but and error
	 * due to transmition or splitted data:
	 *	"\r\n\r\nERROR\r\n" or "\r\n\r\n+IPD,X,X:"	
	 * */

	if ('E' == *esp8.read) {
		if(0 == es8266_rx_pop_til("Error\r\n", 7)) 
			esp8_status.http = HTTP_522;	// Connection Time-Out

		return;
	}
	if ('+' == *esp8.read) {
		if(0 == es8266_rx_pop_til("+IPD,", 5)) {
			esp8_status.http = HTTP_520;	// Something went wrong with header

			while(*esp8.read != 0) {
				esp8266_rx_pop();
			}
		}

	}
}

uint16_t test_rns;
static void esp8266_http_get_Content(char *content, unsigned short len) {
	uint16_t rns;
	test_rns = 0;
	while(len--) {
		*content = *esp8.read;
		esp8266_rx_pop();
		content++;
	}
	rns = 0;

	/* When the webserver (such as spotify's) is responding with large
	 * sizes of data (more than 1 kilo byte), that reponse itself
	 * arrives in chunks and each chunk has a header, so far that 
	 * header was being ingnored and count as part of the content, so
	 * when the content is copied out, there are some remaining actual
	 * content that has to be copied as well, for future, the header of
	 * the chunks has to be parsed, so far this copying of the remainings
	 * work	
	 * */
	
	while (*esp8.read != 0) {
		*content = *esp8.read;
		esp8266_rx_pop();
		content++;
		test_rns++;
	}

	*content = 0;
}


/*
 * -- http_get_code HTTP Status Code --
 *	it has the minimum functionality to parse the most used codes
 *	for the web the main project is implemented for:
 *		IP-API, OpenWeatherMap, and Spotify
 */
static void http_get_code(void) {

	esp8_status.http = *esp8.read << 8;
	esp8266_rx_pop();

	esp8_status.http |= (*esp8.read & 0x0F) << 4;
	esp8266_rx_pop();

	esp8_status.http |= *esp8.read & 0x0F;
	esp8266_rx_N_pop(2);
	
}

/********************************************************
 * HTTP data shall be:
 * 		<method> /<resource> HTTP<version>
 * 		<header>
 ********************************************************/

static int16_t esp8266_http_get_ContentLength_and_skip_header(void) {
	int16_t content_length;
	
	content_length = esp8266_http_get_ContentLength();
	if(0 == content_length)
		return -2;

	esp8266_http_skip_header();

	if (esp8_status.http != HTTP_200) {
		esp8_status.cmd = ESP8_DATA_PULLIN;
		return 0;
	}
	return content_length;
}

static int16_t esp8266_http_parse(char *out_buff) {
	enum HTTPMethods rest_method = HTTP_Method_UNKNOWN; 
	static int16_t content_length;
	uint16_t cursor, esp8_i, tickout;
	
	rest_method = esp8266_http_get_method();
	tickout = 0;
	cursor = 0;

	switch(rest_method) {
	case HTTP_Method_GET:
		cursor = esp8266_http_get_Resource(out_buff);
		esp8266_http_skip_header();
		esp8_status.cmd = ESP8_DATA_PULLIN;
		return 0;

	case HTTP_Method_POST:
		cursor = esp8266_http_get_Resource(out_buff);
		esp8_status.http = HTTP_200;

	case HTTP_RESPONSE:

		if (HTTP_XXX == esp8_status.http)
			http_get_code();

		if (esp8_status.http != HTTP_200) {
			esp8266_http_skip_header();
			esp8_status.cmd = ESP8_DATA_PULLIN;
			return 0;
		}

		content_length = esp8266_http_get_ContentLength_and_skip_header();
		if(content_length <= 0)
			return content_length;

		if (esp8266_rx_wait_ahead(content_length, RECOMMENDED_TICKOUT))
			return content_length;

		esp8266_http_get_Content(out_buff + cursor, content_length);
	
		esp8_status.cmd = ESP8_DATA_PULLIN;

		return 0;
	}
	return -1;
}

/*****************************************************
 * IPD format shall be:
 * 		+IPD,<link id>,<data length>:<data>
 *****************************************************/
static uint16_t esp8266_ipd_parse(char *out_buff) {
	unsigned char link_queue;
	uint16_t ipd_len;
    char link;

	link_queue = 0;
	while(esp8266_rx_wait_ahead(15, MAX_TICKOUT)); // this is just to wait for 
												   // some data ahead
	if (',' == *(esp8.read + 1)) {
		// >> This is for Multiple Connection <<
		
		// "-47" because ascii "1" (=49), the link 0 wil be 1
		link = *esp8.read - 47;

		while(ESP8266_link.open[link_queue] != link && link_queue < 4) 
			link_queue++;
		
		if (4 == link_queue) {
			link_queue = ESP8266_link.n_links;
			ESP8266_link.n_links = (ESP8266_link.n_links + 1) % 4;
		}
		
		ESP8266_link.open[link_queue] = link; 
		
		// includes both commas: "<link_id:8bits>,"
		esp8266_rx_N_pop(2);

	} else {
		// >> This is for Single Connection <<
		ESP8266_link.open[link_queue] = 1;  	
	}

	*out_buff = ESP8266_link.open[link_queue] - 1;

	/* get IPData length */
	esp8266_rx_to_uint(ipd_len);
	if(0 == *esp8.read)
		return ipd_len;

	esp8266_rx_pop();
	if(esp8266_rx_wait_ahead(ipd_len, MAX_TICKOUT))
		return ipd_len;
	
	return 1;
}

/*****************************************************
 * CIPSTA format shall be: ATv2.2.1
 * 		+CIPSTA:ip:"<IPv4>"\r\n
 * 		+CIPSTA:gateway:"<Gateway IPv4>"\r\n
 * 		+CIPSTA:netmask:"<netmask IPV4>" 
 *****************************************************/
static void esp8266_cipstate_parse(void) {
	char *ch;
	
	esp8266_rx_N_pop(2); // skip ":\""
	ch = ESP8266_IPv4.ip;
	while(*esp8.read != '"') {
		*ch = *esp8.read;
		ch++;
		esp8266_rx_pop(); 
	} 
	*ch = 0;

	esp8266_rx_N_pop(20); // skip "\"\r\n+CIPSTA:gateway:\""
	ch = ESP8266_IPv4.gateway;
	while(*esp8.read != '"') {
		*ch = *esp8.read;
		ch++;
		esp8266_rx_pop(); 
	}
	*ch = 0;

	esp8266_rx_N_pop(20); // skip "\"\r\n+CIPSTA:netmask:\""
	ch = ESP8266_IPv4.netmask;
	while(*esp8.read != '"') {
		*ch = *esp8.read;
		ch++;
		esp8266_rx_pop(); 
	}
	*ch = 0;
}

static uint8_t on_closing_link(void) {
	/* 5 are the maximum connections the ESP8266 can work with */
    uint8_t i;
    
    if(ESP8_DATA_PULLIN == esp8_status.cmd)
        return 1;

    esp8_status.tcp |= TCP_PORT_CLOSE;
    
    i = 0;
    while(ESP8266_link.open[i] != esp8_status.link && (i < 5)) 
        ++i;

    if (5 == i)
		return 0;

	ESP8266_link.open[i] = 0; // 0,CLOSED
    return 0;
}

static int16_t
esp8266_wait_for_IPData(char *out_buff, const int16_t content_length)
{
	if(esp8266_rx_wait_ahead(content_length, RECOMMENDED_TICKOUT))
		return content_length;

	esp8266_http_get_Content(out_buff, content_length);
    esp8_status.cmd = ESP8_DATA_PULLIN;
	return 0;
}

static uint8_t check_on_ipdata(struct ESP8IPData *ipd) {
	static int16_t content_length = 0;

	switch(ipd->status) {
	
	case IPData_DUMMY:
		ipd->status = IPData_DUMMY2;
		return 1;
	
	/* When large amaount of data is being received, the parser is faster
	 * that the USART transmission so, there are elements of the HTTP
	 * that are not being found */
	case IPData_DUMMY2:
		ipd->status = IPData_OK2PARSE;
		return 1;
	
	case IPData_OK2PARSE:

		content_length = esp8266_http_parse(ipd->buff_link);
		
		switch(content_length) {
		case 0:
			ipd->status = IPData_UKNOWN;
			break;

		case -1:
			esp8_status.cmd = ESP8_ERROR;
			ipd->status = IPData_UKNOWN;
			break;

		case -2:
			ipd->status = IPData_WAIT_FOR_CONTENT_LENGTH;
			break;
		
		default:  // case: content_length > 0 
			ipd->status = IPData_WAIT;
		}
        
		return 1;
	
	case IPData_WAIT_FOR_CONTENT_LENGTH:
		memcpy(tmp_test, esp8.read, 20);
		content_length = esp8266_http_get_ContentLength_and_skip_header();
		if (content_length <= 0) {
			esp8_status.cmd = ESP8_ERROR;
			ipd->status = IPData_UKNOWN;
			return 1;
		}


	case IPData_WAIT:
		content_length = esp8266_wait_for_IPData(ipd->buff_link, content_length);
		ipd->status = 0 == content_length
					  ? IPData_UKNOWN
					  : IPData_WAIT;
		return 1;
	}

	return 0;
}

#define IPD_SIZE_THRESHOLD	1000

void esp8266_poll(void) {
	char *tokens[] = {ESP8_TOKENS};
	static enum ESP8Resp i = ESP8_UNKNOWN;
	static char *token;
	static struct ESP8IPData ipd;

	if(check_on_ipdata(&ipd))
		return;

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
			if(ESP8_UNKNOWN == i)
				esp8_status.link = ((*esp8.read & 0x0F) + 1);

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
				if(on_closing_link());
					break;

				esp8266_rx_pop();
				esp8_status.cmd = i;
				i = ESP8_UNKNOWN;
				break;
		
			case ESP8_IPData:
				esp8266_rx_pop();
				i = ESP8_UNKNOWN;		

				ipd.size = esp8266_ipd_parse(ipd.buff_link);
				ipd.buff_link = ESP8266_link.buffXlink[*ipd.buff_link];
				 if (ipd.size > 0 && ipd.size <= IPD_SIZE_THRESHOLD) {
                    ipd.status = IPData_OK2PARSE;
                } else if (ipd.size > IPD_SIZE_THRESHOLD) {
					// Just to buy some time
					ipd.status = IPData_DUMMY;
				}

				break;

			case ESP8_IP:
				esp8266_rx_pop();
				esp8_status.cmd = i;
				i = ESP8_UNKNOWN;
				esp8266_cipstate_parse();
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

	// Skip 0s on restart
	for(uint8_t i = 100; ESP8266_SET_RESTART && (0 == *esp8.read) && i; i--) {
			esp8266_rx_pop();
	}
}


