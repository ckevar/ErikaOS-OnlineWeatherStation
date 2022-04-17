/*
 * Created Mar 16, 2022
 *  - by ckevar
 */
#include <string.h>
#include "stm32f4_discovery.h"

#include "esp8266_driver.h"

#include "lcd_log.h"

// Disable DMA for transmission
#define esp82266_dma_TX_disable() 	DMA2_Stream6->CR &= ~0x01;\
									while((DMA2_Stream6->CR & 0x01));
// Set length for DMA and Enables it
#define esp8266_dma_set_length_and_enableTX(length) DMA2_Stream6->NDTR = (uint32_t) length;\
													while((~DMA2_Stream6->CR & 0x01)) DMA2_Stream6->CR |= DMA_SxCR_EN;


char ESP8266_AT_STATUS = ESP8266_ST_UNKNOWN_CODE; 
char ESP8266_STATUS_TCP = ESP8266_ST_UNKNOWN_CODE;
char ESP8266_STATUS = ESP8266_ST_UNKNOWN_CODE;

static void esp8266_USART_RX_DMA_Init(char *BUFF_L, uint16_t size);
static void esp8266_USART_TX_DMA_Init(void);

static ESP8266_BUFF_t *buff_tmp;
static char esp8266_dma_buff[512];
static char ESP8266_SET_RESTART = 0; 

#define esp8266_cmd_at_add_CR_NL(x) *(esp8266_dma_buff + x) = 13;\
									*(esp8266_dma_buff + x + 1) = 10;

ESP8266_Link_t ESP8266_link;
ESP8266_IPv4_t ESP8266_IPv4;

void esp8266_init(ESP8266_BUFF_t *buff) {
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
	buff->RX_READ = buff->RX0;
	buff->RX_LENGTH = ESP8266_BUFF_RX_LEN;
	buff->RX_END = buff->RX0 + buff->RX_LENGTH;
	esp8266_USART_RX_DMA_Init(buff->RX0, buff->RX_LENGTH);
	buff_tmp = buff;

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

}

static void esp8266_USART_TX_DMA_Init(void) {
	/* DMA for USART6_TX -> DMA2, stream 6, channel 5 */
	
	/* Enable Clock for DMA2 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	DMA2_Stream6->CR = 0x0;	// Enable COnfiguration Register
	while(DMA2_Stream6->CR);
	DMA2_Stream6->CR |= 0x0A000000;		// SPI2_RX on DMA2 stream 6 channel 5
	DMA2_Stream6->CR &= 0xFFFF9FFF;		// USART data size is 8 bits
	DMA2_Stream6->CR &= 0xFFFFE7FF;		// Memory data size is 8 bits
	DMA2_Stream6->CR &= ~DMA_SxCR_DBM;	// No buffer switching
	DMA2_Stream6->CR |= DMA_SxCR_MINC;	// Automatic Memory Increment
	DMA2_Stream6->CR &= ~DMA_SxCR_CIRC;	// No Circular Mode on transmision
	DMA2_Stream6->CR |= 0x1 << 6;		// Memory to Peripheral
	DMA2_Stream6->CR |= DMA_SxCR_PL;	// Priority High;
	DMA2_Stream6->FCR &= ~DMA_SxFCR_DMDIS;	// Direct Mode (FIFO Disabled)

	DMA2_Stream6->PAR = (uint32_t) &(EVAL_COM1->DR);	// Peripheral Base Address
	DMA2_Stream6->M0AR = (uint32_t) esp8266_dma_buff;	// Memory base address 0
	DMA2_Stream6->NDTR = 0;								// NUmber of data per transfer

	/* Inturruptions, uncomment for debugging */
	DMA2_Stream6->CR |= DMA_SxCR_TCIE;		// Enable complete interruption
	//DMA2_Stream6->CR |= DMA_SxCR_TEIE;	// Enable Error Transfer interruption
	//DMA2_Stream6->CR |= DMA_SxCR_DMEIE;	// Enable Error Transfer interruption
	/******************************************/
	
	DMA2_Stream6->CR |= DMA_SxCR_EN;	// Disable Configuration Register
}

static void esp8266_USART_RX_DMA_Init(char *BUFF_L, uint16_t size) {
	/* DMA for USART6_RX -> DMA 2, Stream 1, Channel 5 */
	
	/* Enable DMA1 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	DMA2_Stream1->CR = 0x0;	// Enable COnfiguration Register
	while(DMA2_Stream1->CR);

	DMA2_Stream1->CR |= 0x0A000000;		// SPI2_RX on DMA2 stream 1 channel 5
	DMA2_Stream1->CR &= 0xFFFF9FFF;		// USART data size is 8 bits
	DMA2_Stream1->CR &= 0xFFFFE7FF;		// Memory data size is 8 bits
	DMA2_Stream1->CR &= ~DMA_SxCR_DBM;	// No buffer switching
	DMA2_Stream1->CR |= DMA_SxCR_MINC;	// Automatic Memory Increment
	DMA2_Stream1->CR |= DMA_SxCR_CIRC;	// Circular Mode at Reception
	// DMA2_Stream1->CR |= DMA_SxCR_PFCTRL;// Peripheral control flows
	DMA2_Stream1->CR &= ~DMA_SxCR_DIR;	// Peripheral to Memory
	DMA2_Stream1->CR |= DMA_SxCR_PL;	// Priority High;
	DMA2_Stream1->FCR &= ~DMA_SxFCR_DMDIS;	// Direct Mode (FIFO Disabled)

	DMA2_Stream1->PAR = (uint32_t) &(EVAL_COM1->DR);	// Peripheral Base Address
	DMA2_Stream1->M0AR = (uint32_t) BUFF_L;		// Memory base address 0
	DMA2_Stream1->NDTR = (uint32_t) size;		// NUmber of data per transfer
	
	/* Interruptions, uncomment for debugging */
	//DMA2_Stream1->CR |= DMA_SxCR_TCIE; 	// Transfer full interrupt
	//DMA2_Stream1->CR |= DMA_SxCR_TEIE; 	// Transfer error interrupt
	//DMA2_Stream1->CR |= DMA_SxCR_DMEIE; 	// Transfer error interrupt
	/******************************************/

	DMA2_Stream1->CR |= DMA_SxCR_EN;			// Disable Configuration Register
}


void esp8266_cmd(char *str) {
	/* former way to send commands without DMA enabled */
	unsigned char i = 0;

	while (str[i] != '\0') {
		/* Loop until the end of transmission */
		while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET);

		USART_SendData(EVAL_COM1, (uint16_t) str[i]);
		i++;
	}
}

static void esp8266_dma_cmd(char *str, unsigned short length) {
	esp82266_dma_TX_disable();
	memcpy(esp8266_dma_buff, str, length);
	esp8266_dma_set_length_and_enableTX(length);
} 

static void esp8266_dma_cmd_mul_param(char *cmd, unsigned short cmd_len, char *arg, short arg_len){
	/************************************************************************
	 * Forms a command to be sent, appending \r\n, when no parameter is sent
	 * arg_len has to be 0.
	 * if arg_len is smaller than zero, \r\n wont be appende to the message,
	 * this makes when suppling HTML data to the ESP8266
	 ************************************************************************/ 

	esp82266_dma_TX_disable();

	memcpy(esp8266_dma_buff, cmd, cmd_len);

	if (arg_len >= 0) {
		if (arg_len == 1)
			// No need to use memcpy when the parametere is only one char
			*(esp8266_dma_buff + cmd_len) = *arg;

		else if (arg_len > 1)
			memcpy(esp8266_dma_buff + cmd_len, arg, arg_len);

		cmd_len += arg_len;
		*(esp8266_dma_buff + cmd_len) = 13;
		*(esp8266_dma_buff + cmd_len + 1) = 10;
		cmd_len += 2;
	} 

	esp8266_dma_set_length_and_enableTX(cmd_len);	
}

void esp8266_at(void) {
	esp8266_dma_cmd_mul_param(ESP8266_AT, ESP8266_AT_LEN, NULL, 0);
}

void esp8266_restart(void) {
	esp8266_dma_cmd_mul_param(ESP8266_AT_RST, ESP8266_AT_RST_LEN, NULL, 0);
	ESP8266_SET_RESTART = 1;
}

void esp8266_restore(void) {
	esp8266_dma_cmd_mul_param(ESP8266_AT_RESTORE, ESP8266_AT_RESTORE_LEN, NULL, 0);	
}

void esp8266_gmr(void){
	esp8266_dma_cmd_mul_param(ESP8266_AT_GMR, ESP8266_AT_GMR_LEN, NULL, 0);
}

void esp8266_get_CIPSTA_CUR(void) {
	esp8266_dma_cmd_mul_param(ESP8266_AT_CIPSTA_CUR_GET, ESP8266_AT_CIPSTA_CUR_GET_LEN, NULL, 0);	
}

void esp8266_set_CWMODE(char mode) {
	// "mux" can be '0', '1'
	esp8266_dma_cmd_mul_param(ESP8266_AT_CWMODE, ESP8266_AT_CWMODE_LEN, &mode, 1);
}


void esp8266_set_CIPMUX(char mux) {
	// "mux" shall be '0', '1'
	esp8266_dma_cmd_mul_param(ESP8266_AT_CIPMUX, ESP8266_AT_CIPMUX_LEN, &mux, 1);
}

void esp8266_close_tcp(char link){
	// 'link' shall be: 0, '0', '1', '2', '3' or '4'
	if (link) esp8266_dma_cmd_mul_param(ESP8266_AT_CIPCLOSE, ESP8266_AT_CIPCLOSE_LEN, &link, 1);
	else esp8266_dma_cmd_mul_param(ESP8266_AT_CIPCLOSE, ESP8266_AT_CIPCLOSE_SINGLE_LEN, NULL, 0);
}

void esp8266_enable_HTTPServer_P80(void) {
	// Enables HTTP server at port 80
	esp8266_dma_cmd_mul_param(ESP8266_AT_CIPSERVER_ON_P80,\
		ESP8266_AT_CIPSERVER_ON_P80_LEN, NULL, 0);
}

void esp8266_disable_HTTPServer_P80(void) {
	// Disable HTTP server at port 80
	esp8266_dma_cmd_mul_param(ESP8266_AT_CIPSERVER_OFF,\
		ESP8266_AT_CIPSERVER_OFF_LEN, NULL, 0);
}

void esp8266_set_SSID_and_PASS(char *ssid_and_pass, unsigned short len) {
	// "len" is  the length of the SSID and password including quotes 
	// and comas
	esp8266_dma_cmd_mul_param(ESP8266_AT_CWJAP_DEF, ESP8266_AT_CWJAP_DEF_LEN,\
		ssid_and_pass, len);
}

void esp8266_set_DNS(char *dns, unsigned short len) {
	// Sets DNS to connect
	esp8266_dma_cmd_mul_param(ESP8266_AT_CIPSTART_TCP, ESP8266_AT_CIPSTART_TCP_LEN,\
		dns, len);
}

void esp8266_set_CIPSEND(char *len_of_data, unsigned short len) {
	// CIPSEND for single connection setting
	esp8266_dma_cmd_mul_param(ESP8266_AT_CIPSEND_NONMUX, ESP8266_AT_CIPSEND_NONMUX_LEN,\
		len_of_data, len);
}

void esp8266_set_CIPSEND_link(char link, char *len_of_data, unsigned short len) {
	// char "link" shall a number 0, 1, 2, 3, or 4 
	char tmp[ESP8266_AT_CIPSEND_MUX_LEN] = ESP8266_AT_CIPSEND_MUX;
	tmp[ESP8266_AT_CIPSEND_MUX_X] = link + 48; 	// cast number value to char
	esp8266_dma_cmd_mul_param(tmp, ESP8266_AT_CIPSEND_MUX_LEN, len_of_data, len);
}

void esp8266_set_CWSAP(char *cmd, unsigned short len) {
	esp8266_dma_cmd_mul_param(ESP8266_AT_CWSAP, ESP8266_AT_CWSAP_LEN, cmd, len);
}

void esp8266_set_baudrate_9600(void){
	/* Dangerous AT command, even some official firmwares can brick the ESP,
	 * so, they have to be re-flashed. This command works with the following firmware
	 * AT_firmware_1.6.2.0.bin post it by Adafruit
	 */ 
	esp8266_dma_cmd_mul_param(ESP8266_AT_UART_DEF_9600, ESP8266_AT_UART_DEF_9600_LEN, NULL, 0);
}

void esp8266_get_CIPSTATUS(void) {
	esp8266_dma_cmd_mul_param(ESP8266_AT_CIPSTATUS, ESP8266_AT_CIPSTATUS_LEN, NULL, 0);
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

static void esp8266_buff_clean_and_increment(unsigned short it) {
	while (it) {	
		*buff_tmp->RX_READ = 0;
		buff_tmp->RX_READ++;

		if (buff_tmp->RX_READ == buff_tmp->RX_END)
			buff_tmp->RX_READ = buff_tmp->RX0;
		it--;
	}
}


/*
 * queries method on the html arrival data, only GET and POST supported
 */
static unsigned char esp8266_http_query_RESTMethod(void) {
	unsigned char get_method = 0, post_method = 0;
	unsigned char no_method = 0;
	
	
	while(*buff_tmp->RX_READ != ' ') {
		get_method = (*buff_tmp->RX_READ == 'G') ||\
					 (*buff_tmp->RX_READ == 'E') ||\
			  		 (*buff_tmp->RX_READ == 'T') ? get_method + 1 : 0;

		post_method = (*buff_tmp->RX_READ == 'P') ||\
				 	  (*buff_tmp->RX_READ == 'O') ||\
				  	  (*buff_tmp->RX_READ == 'S') ||\
				  	  (*buff_tmp->RX_READ == 'T') ? post_method + 1 : 0;

		no_method = (*buff_tmp->RX_READ == 'H') ||\
				 	(*buff_tmp->RX_READ == 'T') ||\
					(*buff_tmp->RX_READ == 'T') ||\
					(*buff_tmp->RX_READ == 'P') ||\
					(*buff_tmp->RX_READ == '/') ||\
					(*buff_tmp->RX_READ == '1') ||\
					(*buff_tmp->RX_READ == '.') ||\
					(*buff_tmp->RX_READ == '1') ? no_method + 1 : 0;
		esp8266_buff_clean_and_increment(1);
	}

	// if all characters were found, then return it the respective method
	if (get_method == 3) return ESP8266_RESTMethod_GET;
	if (post_method == 4) return ESP8266_RESTMethod_POST;
	if (no_method == 8) return ESP8266_RESTMethod_NO_METHOD;

	return ESP8266_RESTMethod_UNKNOWN;
}

static unsigned char esp8266_http_query_Resource(char *res) {
	unsigned char i = 0;
	// Forward cursors until to catch the resource needed started
	while(*buff_tmp->RX_READ != '/')
		esp8266_buff_clean_and_increment(1);

	// Forward cursor until all resource requested is acquiered;
	while(*buff_tmp->RX_READ != ' ') {
		res[i] = *buff_tmp->RX_READ;
		i++;
		esp8266_buff_clean_and_increment(1);
	}

	res[i] = 0;

	return i + 1;
}

static unsigned short esp8266_http_query_ContentLength(void) {
	unsigned short dist;
	unsigned short ch2cmp;
	static unsigned short ch2cmp_offset = 0;
	char *content_length = "Content-Length: ";

	while((ch2cmp_offset < 16) && (*buff_tmp->RX_READ != 0)) {

		dist = buff_tmp->RX_END - buff_tmp->RX_READ;
		ch2cmp = (dist > 16) ? 16 - ch2cmp_offset : dist;

		if (memcmp(buff_tmp->RX_READ, content_length + ch2cmp_offset, ch2cmp) == 0){
			ch2cmp_offset += ch2cmp; 
			esp8266_buff_clean_and_increment(ch2cmp);
		}
		else {
			ch2cmp_offset = 0;
			esp8266_buff_clean_and_increment(1);
		}
	}

	if (ch2cmp_offset == 16) {
		ch2cmp = 0;
		while(*buff_tmp->RX_READ != '\r') {
			ch2cmp = ch2cmp * 10 + *buff_tmp->RX_READ - 48;
			esp8266_buff_clean_and_increment(1); 
		}
		ch2cmp_offset = 0;
		return ch2cmp;
	}
	return 0;
}

static void esp8266_http_query_Content(char *content, unsigned short len) {
	unsigned rns = 0;
	// *content = 0;
	// content++;

	// skip until the end of the http header
	while(rns < 4) {
		rns = ((*buff_tmp->RX_READ == '\r') || (*buff_tmp->RX_READ == '\n')) ? rns + 1 : 0;
		esp8266_buff_clean_and_increment(1);
	}

	// If there's plenty of available space in the buffer, the memory can be copied out
	// in a single big chunk, otherwise, it gotta be copied in two chuncks.
	rns = buff_tmp->RX_END - buff_tmp->RX_READ;

	if (len > rns) {
		memcpy(content, buff_tmp->RX_READ, rns);
		memset(buff_tmp->RX_READ, 0, rns);
		buff_tmp->RX_READ = buff_tmp->RX0;
		content += rns;
		len -= rns;		
	}

	memcpy(content, buff_tmp->RX_READ, len);
	memset(buff_tmp->RX_READ, 0, len);
	buff_tmp->RX_READ += len;
	content += len;
	*content = 0;

}

/********************************************************
 * HTTP data shall be:
 * 		<method> /<resource> HTTP<version>
 * 		<header>
 ********************************************************/
static unsigned char esp8266_http_parse(char *tmp_ptr) {
	char rest_method = ESP8266_RESTMethod_UNKNOWN; 
	unsigned char cursor = 0;
	unsigned short content_length = 0;

	/* Query REST Method */
	rest_method = esp8266_http_query_RESTMethod();

	if (rest_method) {
	
		/* Query Requested resource */
		if (rest_method != ESP8266_RESTMethod_NO_METHOD)
			cursor = esp8266_http_query_Resource(tmp_ptr);

		if (rest_method == ESP8266_RESTMethod_POST ||\
			rest_method == ESP8266_RESTMethod_NO_METHOD) {

			/* Query Content-Length */
			content_length = esp8266_http_query_ContentLength();

			/* Query Content */
			esp8266_http_query_Content(tmp_ptr + cursor, content_length);
		} 

		ESP8266_STATUS_TCP++;
		return 0;
	} 
	return 1;
}

/*****************************************************
 * IPD format shall be:
 * 		+IPD,<link id>,<data length>:<data>
 *****************************************************/
static unsigned short esp8266_ipd_parse(char *tmp_ptr) {
	unsigned char link_queue;
	unsigned short ipd_len = 0;

	/* Cleaning IPD */
	esp8266_buff_clean_and_increment(ESP8266_ST_IPD_LEN);

	/* Query Link ID */
	link_queue = ESP8266_link.n_links;
	// LCD_UsrLog("RX:%s\r\n", buff_tmp->RX_READ);	
	if (*(buff_tmp->RX_READ + 2) == ',') {
		ESP8266_link.open[link_queue] = *(buff_tmp->RX_READ + 1) - 47; // "-47" because ascii "1" (=49), the link 0 wil be 1
		esp8266_buff_clean_and_increment(3); // includes both commas: ",<link_id: 1 character>,"
	} else {
		ESP8266_link.open[link_queue] = 1;  	// This is for Single Connection
		esp8266_buff_clean_and_increment(1); 	// includes only one comma: ","
	}

	ESP8266_link.n_links++;

	if (ESP8266_link.n_links > 4) {
		// TODO: close the connection with the oldest client 
		ESP8266_link.n_links = 0;
	}

	*tmp_ptr = ESP8266_link.open[link_queue] - 1;

	/* Query  IPD data length */
	while(*buff_tmp->RX_READ != ':') {
		ipd_len = ipd_len * 10 + *buff_tmp->RX_READ - 48;
		esp8266_buff_clean_and_increment(1); 
	}
	return ipd_len;
}

/*****************************************************
 * CIPSTA_CUR/DEF format shall be:
 * 		+CIPSTA_CUR/DEF:ip:"<IPv4>"\r\n
 * 		+CIPSTA_CUR/DEF:gateway:"<Gateway IPv4>"\r\n
 * 		+CIPSTA_CUR/DEF:netmask:"<netmask IPV4>" 
 *****************************************************/
static void esp8266_cipstate_parse(void) {
	char *ch;
	
	esp8266_buff_clean_and_increment(16); // skip "+CIPSTA_CUR:ip:\""
	ch = ESP8266_IPv4.ip;
	while(*buff_tmp->RX_READ != '"') {
		*ch = *buff_tmp->RX_READ;
		ch++;
		esp8266_buff_clean_and_increment(1); 
	} 
	*ch = 0;

	esp8266_buff_clean_and_increment(24); // skip "\"\r\n+CIPSTA_CUR<DEF>:gateway:\""
	ch = ESP8266_IPv4.gateway;
	while(*buff_tmp->RX_READ != '"') {
		*ch = *buff_tmp->RX_READ;
		ch++;
		esp8266_buff_clean_and_increment(1); 
	}
	*ch = 0;

	esp8266_buff_clean_and_increment(24); // skip "\"\r\n+CIPSTA_CUR:netmask:\""
	ch = ESP8266_IPv4.netmask;
	while(*buff_tmp->RX_READ != '"') {
		*ch = *buff_tmp->RX_READ;
		ch++;
		esp8266_buff_clean_and_increment(1); 
	}
	*ch = 0;
}

void esp8266_response(void) {
	// parse the receiving data
	static unsigned char ESP8266_IPD_DATA_STATUS = ESP8266_IPD_DATA_UKNOWN;
	static char *buff_link;

	if (ESP8266_IPD_DATA_STATUS == ESP8266_IPD_DATA_OK2PARSE) {
		if(esp8266_http_parse(buff_link))
			ESP8266_AT_STATUS = ESP8266_ST_ERROR_CODE;
		ESP8266_IPD_DATA_STATUS = ESP8266_IPD_DATA_UKNOWN;
	}

	while(*buff_tmp->RX_READ != 0) {

		if (*buff_tmp->RX_READ == '>') {
			ESP8266_AT_STATUS = ESP8266_ST_WRAP_CODE;
		}

		else if (memcmp(buff_tmp->RX_READ, ESP8266_ST_READY, ESP8266_ST_READY_LEN) == 0) {
				ESP8266_AT_STATUS = ESP8266_ST_RESTART_CODE;
				ESP8266_SET_RESTART = 0;
				esp8266_buff_clean_and_increment(5);
				return;
		}

		else if (memcmp(buff_tmp->RX_READ, ESP8266_ST_OK, ESP8266_ST_OK_LEN) == 0) {
			ESP8266_AT_STATUS = ESP8266_ST_OK_CODE;
			esp8266_buff_clean_and_increment(ESP8266_ST_OK_LEN);
			return;
		}

		else if(memcmp(buff_tmp->RX_READ, ESP8266_ST_FAIL, ESP8266_ST_FAIL_LEN) == 0) {
			ESP8266_AT_STATUS = ESP8266_ST_FAIL_CODE;
			esp8266_buff_clean_and_increment(ESP8266_ST_FAIL_LEN);
			return;
		}
		
		else if(memcmp(buff_tmp->RX_READ, ESP8266_ST_ERROR, ESP8266_ST_ERROR_LEN) == 0) {
			ESP8266_AT_STATUS = ESP8266_ST_ERROR_CODE;
			esp8266_buff_clean_and_increment(ESP8266_ST_ERROR_LEN);
			return;
		}

		else if (memcmp(buff_tmp->RX_READ + 2, ESP8266_ST_HTTP_CLOSED, ESP8266_ST_HTTP_CLOSED_LEN) == 0) {
			ESP8266_AT_STATUS = ESP8266_ST_HTTP_CLOSED_CODE;
			char i = 0;
			char link = (*(buff_tmp->RX_READ) < 47) ? 0 : *(buff_tmp->RX_READ) - 47;			
			while(ESP8266_link.open[i] != link) ++i;
			ESP8266_link.open[i] = 0; // 0,CLOSED
			esp8266_buff_clean_and_increment(ESP8266_ST_HTTP_CLOSED_LEN);
			return;
		}

		else if (memcmp(buff_tmp->RX_READ, ESP8266_ST_IPD, ESP8266_ST_IPD_LEN) == 0) {
			if (esp8266_ipd_parse(buff_link)) {
				buff_link = ESP8266_link.buffXlink[*buff_link];
				ESP8266_IPD_DATA_STATUS = ESP8266_IPD_DATA_OK2PARSE;
				return;
			}
		} else if (memcmp(buff_tmp->RX_READ, ESP8266_ST_CIPSTATE_CUR_IP, ESP8266_ST_CIPSTATE_CUR_IP_LEN) == 0) {
			ESP8266_AT_STATUS = ESP8266_ST_CIPSTATE_CUR_CODE;
			esp8266_cipstate_parse();
			return;

		} else if (memcmp(buff_tmp->RX_READ, ESP8266_ST_CIPSTATUS_STATUS_STR, ESP8266_ST_CIPSTATUS_STATUS_LEN) == 0) {
			esp8266_buff_clean_and_increment(ESP8266_ST_CIPSTATUS_STATUS_LEN);
			ESP8266_STATUS = *buff_tmp->RX_READ;
		}

		esp8266_buff_clean_and_increment(1);
	}

	if (ESP8266_SET_RESTART) {
		// Skip 0s on restart
		while(*buff_tmp->RX_READ == 0) 
			esp8266_buff_clean_and_increment(1);
	}

}
