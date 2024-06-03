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
#define esp82266_dma_TX_disable() 	DMA2_Stream6->CR &= ~0x01;\
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

#define esp8266_cmd_at_add_CR_NL(x) *(esp8_TX + x) = 13;\
									*(esp8_TX + x + 1) = 10;

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
	//DMA2_Stream1->CR |= DMA_SxCR_TCIE; 	// Transfer full interrupt
	//DMA2_Stream1->CR |= DMA_SxCR_TEIE; 	// Transfer error interrupt
	//DMA2_Stream1->CR |= DMA_SxCR_DMEIE; 	// Transfer error interrupt
	/******************************************/

	DMA2_Stream1->CR |= DMA_SxCR_EN;			// Disable Configuration Register
}


/* 
 * Former way to send commands without DMA enabled */
/*
void esp8266_cmd(char *str) {
	unsigned char i = 0;

	while (str[i] != '\0') {
		//Loop until the end of transmission 
		while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET);

		USART_SendData(EVAL_COM1, (uint16_t) str[i]);
		i++;
	}
}
*/
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
static void esp8266_dma_cmd_mul_param(char *cmd, unsigned short cmd_len, \
		char *arg, short arg_len)
{
	esp82266_dma_TX_disable();

	memcpy(esp8_TX, cmd, cmd_len);

	if (arg_len >= 0) {
		if (arg_len == 1)
			// No need to use memcpy when the parametere is only one char
			*(esp8_TX + cmd_len) = *arg;

		else if (arg_len > 1)
			memcpy(esp8_TX + cmd_len, arg, arg_len);

		cmd_len += arg_len;
		*(esp8_TX + cmd_len) = 13;
		*(esp8_TX + cmd_len + 1) = 10;
		cmd_len += 2;
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
	esp8_status.http = HTTP_XXX;
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
    esp8.read = esp8.read == esp8.eof \
                ? esp8.data \
                : esp8.read + 1

static void esp8266_rx_N_pop(uint16_t it) {
    while (it) { 
        esp8266_rx_pop();
		it--;
	}
}


/*
 * gets method on the html arrival data, only GET and POST supported
 */
static unsigned char esp8266_http_get_method(void) {
	unsigned char get_method = 0, post_method = 0;
	unsigned char no_method = 0;
	
	while(*esp8.read != ' ') {
		switch(*esp8.read) {
		case '0':
		case '1':
			no_method++;
			if (no_method == HTTP_RESPONSE) {
				esp8266_rx_N_pop(2);
				return HTTP_RESPONSE;
			}
			break;

		case '/': case '.':
			no_method++;
			break;

		case 'G': case 'E':
			get_method++;
			break;

		case 'T':
			get_method++;

			if(get_method == HTTP_Method_GET) {
				esp8266_rx_N_pop(2);
				return HTTP_Method_GET;
			}

			post_method++;

			if (post_method == HTTP_Method_POST) {
				esp8266_rx_N_pop(2);
				return HTTP_Method_POST;
			}

			no_method++;
			break;
		
		case 'P':
			post_method++;
			no_method++;
			break;

		case 'O': case 'S':
			post_method++;
			break;

		case 'H':
			no_method++;
			break;
		}
		esp8266_rx_pop();
	}

	esp8266_rx_pop();
	return HTTP_Method_UNKNOWN;
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

static unsigned short esp8266_http_get_ContentLength(void) {
	static unsigned short sizecmp_offset = 0;
	unsigned short dist;
	unsigned short sizecmp;
	char *content_length = HTTP_CONTENT_LEN_STR;

	while((sizecmp_offset < HTTP_CONTENT_LEN_LEN) && (*esp8.read != 0)) {

		dist = esp8.eof - esp8.read + 1;

		sizecmp = (dist > HTTP_CONTENT_LEN_LEN) \
                 ? HTTP_CONTENT_LEN_LEN - sizecmp_offset \
                 : dist;

		if (memcmp(esp8.read, content_length + sizecmp_offset, sizecmp) == 0){
			sizecmp_offset += sizecmp; 
			esp8266_rx_N_pop(sizecmp);
		
		} else {
			sizecmp_offset = 0;
            esp8266_rx_pop();
		}
	}

	if (sizecmp_offset == HTTP_CONTENT_LEN_LEN) {
		sizecmp = 0;

		while(*esp8.read != '\r') {
			sizecmp = sizecmp * 10 + *esp8.read - 48;
			esp8266_rx_pop();
		}

		sizecmp_offset = 0;
		return sizecmp;
	}

	return 0;
}

static void esp8266_html_skip_header(void) {
	uint16_t rns = 0;
	uint8_t anon = 1;

	while(rns < 4) {
		rns = ((*esp8.read == '\r') || (*esp8.read == '\n')) \
			  ? rns + 1 \
			  : 0;
		esp8266_rx_pop();
	}
	
	/*
	 * ESP8266's message starts with "\r\n\r\n", so in case it's not
	 * the header that ended but and error due to transmition or 
	 * splitted data:
	 *	"\r\n\r\nERROR\r\n" or "\r\n\r\n+IPD,X,X:"	
	 * */

	if (*esp8.read == 'E') {
		rns = 7;
		while(rns && anon == 1) {
			anon = (*esp8.read == 'E') || (*esp8.read == 'R') ||
				(*esp8.read == 'O') || (*esp8.read == '\r') ||
				(*esp8.read == '\n') 
				? 1
				: 0;
			rns--;
			esp8266_rx_pop();
		}

		if (rns == 0 && anon == 1)
			esp8_status.http = HTTP_522; // Connection Time-out

		return;
	}
	if (*esp8.read == '+') {
		rns = 5;
		while(rns && anon == 1) {
			anon = (*esp8.read == '+') || (*esp8.read == 'I') ||
				(*esp8.read == 'P') || (*esp8.read == 'D') ||
				(*esp8.read == ',') 
				? 1
				: 0;
			rns--;
			esp8266_rx_pop();
		}

		if (rns == 0 && anon == 1) {
			esp8_status.http = HTTP_520;	// Something went wrong with header

			while(*esp8.read != 0) 
				esp8266_rx_pop();
		}

	}
}

static void esp8266_http_get_Content(char *content, unsigned short len) {
	uint16_t rns = 0;

	// If there's plenty of available space in the buffer, the content
	// can be copied out in a single big chunk, otherwise, it gotta be
	// copied in two chuncks.
	rns = esp8.eof - esp8.read + 1;

	if (len > rns) {
		memcpy(content, esp8.read, rns);
		memset(esp8.read, 0, rns);
		esp8.read = esp8.data;
		content += rns;
		len -= rns;		
	}

	memcpy(content, esp8.read, len);
	memset(esp8.read, 0, len);
	esp8.read += len;
	content += len;

	rns = 0;
	while (*esp8.read != 0 && rns < 4) {
		rns = ((*esp8.read == '\r') || (*esp8.read == '\n')) \
			  ? rns + 1 \
			  : 0;
		*content = *esp8.read;
		esp8266_rx_pop();
		content++;
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
	switch(*esp8.read) {
		case '1':
			esp8_status.http = HTTP_1XX;
			break;

		case '2':
			esp8266_rx_N_pop(2);

			if (*esp8.read == '0')
				esp8_status.http = HTTP_200;

			else if (*esp8.read == '4')
				esp8_status.http = HTTP_204;
			else
				esp8_status.http = HTTP_2XX;

			esp8266_rx_pop();
			return;

		case '3':
			esp8_status.http = HTTP_3XX;
			break;

		case '4':
			esp8266_rx_N_pop(2);

			esp8_status.http = *esp8.read == '1'\
							   ? HTTP_401 \
							   : HTTP_4XX;

			esp8266_rx_pop();
			return;

		case '5':
			esp8_status.http = HTTP_2XX;
			break;

		default:
			esp8_status.http = HTTP_XXX;
	}

	esp8266_rx_N_pop(3);
}

/********************************************************
 * HTTP data shall be:
 * 		<method> /<resource> HTTP<version>
 * 		<header>
 ********************************************************/
#define MAX_TICKOUT     2048    // Experimental value

static int16_t esp8266_http_parse(char *out_buff) {
	char rest_method = HTTP_Method_UNKNOWN; 
	uint16_t cursor, content_length, esp8_i, tickout;
	

	rest_method = esp8266_http_get_method();
	if (rest_method == 0) 
		return -1;

	tickout = 0;
	cursor = 0;

	switch(rest_method) {
	case HTTP_Method_GET:
		cursor = esp8266_http_get_Resource(out_buff);
		/* skip header */
		while(*esp8.read != 0 && (tickout < MAX_TICKOUT)) {
			esp8266_rx_pop();
			tickout++;    
		}

		if(tickout == MAX_TICKOUT)
			return -1;

		esp8_status.cmd = ESP8_DATA_PULLIN;
		return 0;

	case HTTP_Method_POST:
		cursor = esp8266_http_get_Resource(out_buff);
		esp8_status.http = HTTP_200;

	case HTTP_RESPONSE:

		if (esp8_status.http == HTTP_XXX)
			http_get_code();

		if (esp8_status.http != HTTP_200) {
			esp8266_html_skip_header();
			esp8_status.cmd = ESP8_DATA_PULLIN;
			return 0;
		}

		content_length = esp8266_http_get_ContentLength();
		esp8266_html_skip_header();

		if (content_length > ESP8266_NUM_LINK * ESP8266_BUFF_PER_LINK) {
			esp8_status.http = HTTP_2XX;
		}

		if (esp8_status.http != HTTP_200) {
			esp8_status.cmd = ESP8_DATA_PULLIN;
			return 0;
		}

		/* An approximation to know if all data from request has
		 * already arrived */
		esp8_i = esp8.read - esp8.data;
		esp8_i = (esp8_i + content_length) % ESP8266_BUFF_RX_LEN;

		while((*(esp8_i + esp8.data - 1) == 0) && (tickout < MAX_TICKOUT))
			tickout++;

		if(tickout == MAX_TICKOUT)
			return content_length;

		esp8266_http_get_Content(out_buff + cursor, content_length);
	}

	esp8_status.cmd = ESP8_DATA_PULLIN;

	return 0;
}

/*****************************************************
 * IPD format shall be:
 * 		+IPD,<link id>,<data length>:<data>
 *****************************************************/
static unsigned short esp8266_ipd_parse(char *out_buff) {
	unsigned char link_queue;
	unsigned short ipd_len = 0;
    char *multi_conn, link;

	link_queue = ESP8266_link.n_links;
    
    // FIXME: *esp.read can lead to segmentation fault.
	if (*(esp8.read + 2) == ',') {
		// >> This is for Multiple Connection <<
		
		// "-47" because ascii "1" (=49), the link 0 wil be 1
		ESP8266_link.open[link_queue] = *(esp8.read + 1) - 47; 

		// includes both commas: ",<link_id:8bits>,"
		esp8266_rx_N_pop(3);

	} else {
		// >> This is for Single Connection <<
		ESP8266_link.open[link_queue] = 1;  	
		esp8266_rx_pop(); 	// includes only one comma: ","
	}

	ESP8266_link.n_links++;

	if (ESP8266_link.n_links > 4) {
		ESP8266_link.n_links = 0;
	}

	*out_buff = ESP8266_link.open[link_queue] - 1;

	/* get IPData length */
	while(*esp8.read != ':') {
		ipd_len = ipd_len * 10 + *esp8.read - 48;
		esp8266_rx_pop(); 
	}
	return ipd_len;
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

static uint8_t on_closing_link() {
    uint8_t i;
    
    if(esp8_status.cmd == ESP8_DATA_PULLIN)
        return 1;

	esp8_status.cmd = ESP8_LINK_CLOSED;
    esp8_status.tcp |= TCP_PORT_CLOSE;
    
    i = 0;
    while(ESP8266_link.open[i] != esp8_status.link && (i < 5)) 
        ++i;

    if (i == 5) {
        esp8_status.cmd = ESP8_UNKNOWN;
        return 0;
    }

	ESP8266_link.open[i] = 0; // 0,CLOSED
    return 0;
}

static int16_t esp8266_wait_for_IPData(char *out_buff, const int16_t content_length) {
	uint16_t tickout, esp8_i;

	tickout = 0;
    esp8_i = esp8.read - esp8.data;
    esp8_i = (esp8_i + content_length) % ESP8266_BUFF_RX_LEN;
		
    while((*(esp8_i + esp8.data - 1) == 0) && (tickout < MAX_TICKOUT))
		tickout++;

	if(tickout == MAX_TICKOUT)
        return content_length;
	
	esp8266_http_get_Content(out_buff, content_length);
    esp8_status.cmd = ESP8_DATA_PULLIN;
	return 0;
}

static uint8_t check_on_ipdata(uint8_t *ipd_status, char *buff_link) {
	static uint16_t content_length = 0;

	switch(*ipd_status) {
	case IPData_DUMMY:
		*ipd_status = IPData_OK2PARSE;
		return 1;
	
	case IPData_OK2PARSE:
		content_length = esp8266_http_parse(buff_link);
		
		if (content_length == 0)
			*ipd_status = IPData_UKNOWN;

		else if (content_length > 0)
			*ipd_status = IPData_WAIT;

		else {
			esp8_status.cmd = ESP8_ERROR;
			*ipd_status = IPData_UKNOWN;
		}
        
		return 1;
	
	case IPData_WAIT:
		content_length = esp8266_wait_for_IPData(buff_link, content_length);
		*ipd_status = content_length == 0\
					  ? IPData_UKNOWN
					  : IPData_WAIT;
		return 1;
	}

	return 0;
}

#define MATCH(resp)     if (counter[resp] == resp##_LEN)

#define RESET_MATCH()   esp8266_rx_pop(); \
                        memset(counter, 0, ESP8_RESP_COUNT)

void esp8266_response(void) {
    static uint8_t counter[ESP8_RESP_COUNT] = {0};
	static uint8_t ipdata_status = IPData_UKNOWN;
	static char *buff_link;
	uint16_t ipd_len;

	if(check_on_ipdata(&ipdata_status, buff_link))
		return;
	
	while(*esp8.read != 0) {

        switch(*esp8.read) {
        case '>': // "<wrap symbol>"end
            esp8_status.cmd = ESP8_WRAP;
            RESET_MATCH();
            return;

        case '+': // "+IPD", "+CIPSTA:ip"
            counter[ESP8_IPData]++;
            counter[ESP8_IP]++;
            break;

        case ',': // "<X>,CLOSED"
            counter[ESP8_LINK_CLOSED]++;
            break;

        case ':': // "+CIPSTA:ip", "STATUS:"end
            counter[ESP8_IP]++;
            counter[ESP8_STATUS]++;

            MATCH(ESP8_STATUS) {
                RESET_MATCH();
                esp8_status.wifi = *esp8.read;
				if (esp8_status.wifi == '3') {
					while (*esp8.read != 'K') {
						esp8266_rx_pop();
					}
				}
				else
					esp8266_rx_N_pop(7);
                esp8_status.cmd = ESP8_OK;
                return;
            }

            break;

        case '0': // "<X>,CLOSED"
        case '1': // "<X>,CLOSED"
        case '2': // "<X>,CLOSED"
        case '3': // "<X>,CLOSED"
        case '4': // "<X>,CLOSED"
            counter[ESP8_LINK_CLOSED]++;
            esp8_status.link = *esp8.read - 47;
            break;
        case '5':
      
        case 'A': // "FAIL", "+CIPSTA:ip", "STATUS:"
            counter[ESP8_FAIL]++;
            counter[ESP8_IP]++;
            counter[ESP8_STATUS]++;
            break;
        
        case 'C': // "<X>,CLOSED", "+CIPSTA:ip"
            counter[ESP8_LINK_CLOSED]++;
            counter[ESP8_IP]++;
            break;

        case 'D': // "<X>,CLOSED"end, "+IPD"end
            counter[ESP8_LINK_CLOSED]++;
            counter[ESP8_IPData]++;
            
            MATCH(ESP8_LINK_CLOSED) {
                if (on_closing_link() == 0) {
                    RESET_MATCH();
                } else {
                    counter[ESP8_LINK_CLOSED]--;
                }
                return;
            }

            MATCH(ESP8_IPData) {
                RESET_MATCH();
                esp8_status.cmd = ESP8_UNKNOWN;
				ipd_len = esp8266_ipd_parse(buff_link);
                if (ipd_len > 0 && ipd_len <= 1000) {
                    buff_link = ESP8266_link.buffXlink[*buff_link];
                    ipdata_status = IPData_OK2PARSE;
                    return;
                } else if (ipd_len > 1000) {
					// Just to buy some time
                    buff_link = ESP8266_link.buffXlink[*buff_link];
					ipdata_status = IPData_DUMMY;
					return;
				}

            }
            break;
        case 'E': // "ERROR", "X,CLOSED"
            counter[ESP8_ERROR]++;
            counter[ESP8_LINK_CLOSED]++;
            break;

        case 'F': // "FAIL"
            counter[ESP8_FAIL]++;
            break;
        
        case 'I': // "FAIL", "+IPD", "+CIPSTA:ip"
            counter[ESP8_FAIL]++;
            counter[ESP8_IPData]++;
            counter[ESP8_IP]++;
            break;
        
        case 'K': // "OK"end
            counter[ESP8_OK]++;
            
            MATCH(ESP8_OK) {
                RESET_MATCH();
                esp8_status.cmd = ESP8_OK;
                return;
            }

            break;

        case 'L': // "FAIL"end, "X,CLOSED"
            counter[ESP8_FAIL]++;
            counter[ESP8_LINK_CLOSED]++;
            
            MATCH(ESP8_FAIL) {
                RESET_MATCH();
                esp8_status.cmd = ESP8_FAIL;
                return;
            }
            break;

        case 'O': // "OK", "ERROR", "X,CLOSED"
            counter[ESP8_OK]++;
            counter[ESP8_ERROR]++;
            counter[ESP8_LINK_CLOSED]++;
            break;
        
        case 'P': // "+IPD", "+CIPSTA:ip"
            counter[ESP8_IPData]++;
            counter[ESP8_IP]++;
            break;

        case 'R': // "+CIPSTA:ip", "ERROR", "ERROR"end
            counter[ESP8_ERROR]++;

            MATCH(ESP8_ERROR) {
                RESET_MATCH();
                esp8_status.cmd = ESP8_ERROR;
                return;
            }
            break;

        case 'S': // "X,CLOSED", "+CIPSTA:ip", "STATUS:"
            counter[ESP8_LINK_CLOSED]++;
            counter[ESP8_IP]++;
            counter[ESP8_STATUS]++;
            break;
        
        case 'T': // "+CIPSTA:ip", "STATUS:"
			counter[ESP8_IP]++;
			counter[ESP8_STATUS]++;
			break;
			
        case 'U': // "+CIPSTA:ip", "STATUS:"
            counter[ESP8_STATUS]++;
            break;
        
        case 'a': // "ready"
        case 'e': // "ready"
        case 'd': // "ready"
            counter[ESP8_READY]++;
            break;
        
        case 'i': // "+CIPSTA:ip"
            counter[ESP8_IP]++;
            break;
        
        case 'p': // "+CIPSTA:ip"end
            counter[ESP8_IP]++;

            MATCH(ESP8_IP) {
                RESET_MATCH();
                esp8_status.cmd = ESP8_IP;

                esp8266_cipstate_parse();
                return;
            }
            break;
        
        case 'r': // "ready"
            counter[ESP8_READY]++;
            break;
        
        case 'y': // "ready"end
            counter[ESP8_READY]++;

            MATCH(ESP8_READY) {
                RESET_MATCH();
                esp8_status.cmd = ESP8_READY;
                ESP8266_SET_RESTART = 0;
                return;
            }
            break;
        
        default:
            memset(counter, 0, ESP8_RESP_COUNT);
        }

		esp8266_rx_pop();
	}

	if (ESP8266_SET_RESTART) {
		// Skip 0s on restart
        uint8_t i = 100; // -> To avoid getting stuck
		while((*esp8.read == 0) && i) {
			esp8266_rx_pop();
            i--;
        }
	}

}
