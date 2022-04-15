/*
 * Created Mar 24, 2022
 *  - by C. Alvarado
 */
#ifndef WEB_APP_H
#define WEB_APP_H 

/**************** NOT FOUND HTTP ****************/
 // header 72 characters 
#define WEBAPP_404 		"HTTP/1.1 404 Not Found\r\n"\
						"Content-type: text/html\r\n"\
						"Connection: close\r\n"\
						"Content-length: 151\r\n\r\n"\
						"<html>"\
							"<head>"\
								"<title>Not Found</title>"\
							"</head>"\
							"<body>"\
								"<h1 style=\"position:fixed;top:50%;left:50%;margin-top:-50px;margin-left:-100px\">404</h1>"\
							"</body>"\
						"</html>"

#define WEBAPP_404_LEN	242
#define WEBAPP_404_LEN_STR	"242"
#define WEBAPP_404_LEN_STR_LEN	3

#define WEBAPP_FAVICON_STR 	"/favicon.ico"
#define WEBAPP_FAVICON_LEN 	12
/*************************************************/


/******************* Index HTTP ******************/
// Header 407
#define WEBAPP_SSIDnPASS 	"HTTP/1.1 200 OK\r\n"\
							"Content-type: text/html\r\n"\
							"Connection: close\r\n"\
							"Content-length: 337\r\n\r\n"\
							"<html>"\
								"<head>"\
									"<title>Erika WiFi</title>"\
								"</head>"\
								"<body>"\
									"<h2>Erika WiFi Settings</h2>"\
									"<form action=\"set_wifi\" method=\"post\">"\
										"<label for=\"ssid\">SSID:</label><br>"\
										"<input type=\"text\" id=\"ssid\" name=\"ssid\"><br>"\
										"<label for=\"psw\">Password:</label><br>"\
										"<input type=\"password\" id=\"psw\" name=\"psw\"><br>"\
										"<input type=\"submit\" value=\"Submit\">"\
									"</form>"\
								"</body>"\
							"</html>"

#define WEBAPP_SSIDnPASS_LEN_STR		"421"
#define WEBAPP_SSIDnPASS_LEN_STR_LEN	3
#define WEBAPP_SSIDnPASS_LEN 			421
/*************************************************/

/***************** try again HTTP ****************/
#define WEBAPP_SSIDnPASS_TA "HTTP/1.1 200 OK\r\n"\
							"Content-type: text/html\r\n"\
							"Connection: close\r\n"\
							"Content-length: 338\r\n\r\n"\
							"<html>"\
								"<head>"\
									"<title>Erika WiFi</title>"\
								"</head>"\
								"<body>"\
									"<h2>Erika WiFi Try Again</h2>"\
									"<form action=\"set_wifi\" method=\"post\">"\
										"<label for=\"ssid\">SSID:</label><br>"\
										"<input type=\"text\" id=\"ssid\" name=\"ssid\"><br>"\
										"<label for=\"psw\">Password:</label><br>"\
										"<input type=\"password\" id=\"psw\" name=\"psw\"><br>"\
										"<input type=\"submit\" value=\"Submit\">"\
									"</form>"\
								"</body>"\
							"</html>"

#define WEBAPP_SSIDnPASS_TA_LEN_STR		"422"
#define WEBAPP_SSIDnPASS_TA_LEN_STR_LEN	3
#define WEBAPP_SSIDnPASS_TA_LEN 		422
/*************************************************/

/******************* /set_wifi *******************/
#define WEBAPP_SETWiFi_STR 	"/set_wifi\0"
#define WEBAPP_SETWiFi_LEN	10

#define WEBAPP_SSID_STR 	"ssid="
#define WEBAPP_SSID_LEN 	5

#define WEBAPP_PSWD_STR 	"psw="
#define WEBAPP_PSWD_LEN 	4
/*************************************************/

/*************** ALL DONE HTTP *******************/
// All done 83
#define WEBAPP_DONE 	"HTTP/1.1 200 OK\r\n"\
						"Content-type: text/html\r\n"\
						"Connection: close\r\n"\
						"Content-length: 77\r\n\r\n"\
						"<html>"\
							"<head>"\
								"<title>Erika WiFi</title>"\
							"</head>"\
							"<body>"\
								"<h2>DONE</h2>"\
							"</body>"\
						"</html>"

#define WEBAPP_DONE_LEN_STR "160"
#define WEBAPP_DONE_LEN_STR_LEN 3
#define WEBAPP_DONE_LEN 160
/*************************************************/

/* code status */
#define WEBAPP_STATUS_NOT_FOUND			0
#define WEBAPP_STATUS_NOT_FOUND_STR 	"HTTP/1.1 404 Not Found\r\n" 
#define WEBAPP_STATUS_NOT_FOUND_LEN 	24

#define WEBAPP_STATUS_OK				1
#define WEBAPP_STATUS_OK_STR			"HTTP/1.1 200 OK\r\n"
#define WEBAPP_STATUS_OK_LEN			17

/* content-type */
#define WEBAPP_NO_CONTENT_TYPE 				0

#define WEBAPP_CONTENT_TYPE_TEXT_HTML 		1
#define WEBAPP_CONTENT_TYPE_TEXT_HTML_STR 	"Content-type: text/html\r\n"
#define WEBAPP_CONTENT_TYPE_TEXT_HTML_LEN 	25

/* Connection */
#define WEBAPP_NON_CONNECTION 	0
#define WEBAPP_CONN_CLOSE 		1
#define WEBAPP_CONN_CLOSE_STR 	"Connection: close\r\n"
#define WEBAPP_CONN_CLOSE_LEN 	19

#define WEBAPP_CONN_KEEP_ALIVE 	2
#define WEBAPP_CONN_KEEP_ALIVE_STR 	"Connection: keep-alive\r\n"
#define WEBAPP_CONN_KEEP_ALIVE_LEN 	24

/* Content-Length */
#define WEBAPP_CONTENT_LEN_STR	"Content-length: "
#define WEBAPP_CONTENT_LEN_LEN 	16

/**************************************** HTML ****************************************/
/* Content to send */
	// INDEX
#define WEBAPP_CONTENT_INDEX   		1
#define WEBAPP_CONTENT_INDEX_STR	"<html>"\
										"<head>"\
											"<title>Erika WiFi</title>"\
										"</head>"\
										"<body>"\
											"<h2>Erika WiFi Settings</h2>"\
											"<form action=\"set_wifi\" method=\"post\">"\
												"<label for=\"ssid\">SSID:</label><br>"\
												"<input type=\"text\" id=\"ssid\" name=\"ssid\"><br>"\
												"<label for=\"psw\">Password:</label><br>"\
												"<input type=\"password\" id=\"psw\" name=\"psw\"><br>"\
												"<input type=\"submit\" value=\"Submit\">"\
											"</form>"\
										"</body>"\
									"</html>"
#define WEBAPP_CONTENT_INDEX_LEN 	337
#define WEBAPP_CONTENT_INDEX_CL 	"337"
#define WEBAPP_CONTENT_INDEX_CLL 	3	// Length of *_CL

	// Not found
#define WEBAPP_CONTENT_NOT_FOUND 		2
#define WEBAPP_CONTENT_NOT_FOUND_STR 	"<html>"\
											"<head>"\
												"<title>Not Found</title>"\
											"</head>"\
											"<body>"\
												"<h1 style=\"position:fixed;top:50%;left:50%;margin-top:-50px;margin-left:-100px\">404</h1>"\
											"</body>"\
										"</html>"	
#define WEBAPP_CONTENT_NOT_FOUND_LEN	151
#define WEBAPP_CONTENT_NOT_FOUND_CL		"151"
#define WEBAPP_CONTENT_NOT_FOUND_CLL	3

	// Try Again
#define WEBAPP_CONTENT_TRYAGAIN 		3
#define WEBAPP_CONTENT_TRYAGAIN_STR		"<html>"\
											"<head>"\
												"<title>Erika WiFi</title>"\
											"</head>"\
											"<body>"\
												"<h2>Erika WiFi Try Again</h2>"\
												"<form action=\"set_wifi\" method=\"post\">"\
													"<label for=\"ssid\">SSID:</label><br>"\
													"<input type=\"text\" id=\"ssid\" name=\"ssid\"><br>"\
													"<label for=\"psw\">Password:</label><br>"\
													"<input type=\"password\" id=\"psw\" name=\"psw\"><br>"\
													"<input type=\"submit\" value=\"Submit\">"\
												"</form>"\
											"</body>"\
										"</html>"
#define WEBAPP_CONTENT_TRYAGAIN_LEN 	338
#define WEBAPP_CONTENT_TRYAGAIN_CL 		"338"
#define WEBAPP_CONTENT_TRYAGAIN_CLL 	3

	// All done
#define WEBAPP_CONTENT_ALLDONE 			4
#define WEBAPP_CONTENT_ALLDONE_STR 		"<html>"\
											"<head>"\
												"<title>Erika WiFi</title>"\
											"</head>"\
											"<body>"\
												"<h2>DONE</h2>"\
											"</body>"\
										"</html>"
#define WEBAPP_CONTENT_ALLDONE_LEN 		77
#define WEBAPP_CONTENT_ALLDONE_CL 		"77"
#define WEBAPP_CONTENT_ALLDONE_CLL 	2
/**************************************************************************************/


typedef struct WebAppBuilder_t {
	char status;
	char content_type;
	char connection;
	char content;
	char *http;
	unsigned short http_len;
	char http_len_str[4];
	char http_len2;
} WebAppBuilder_t;

extern WebAppBuilder_t webAppOptions;

char build_HTTP(WebAppBuilder_t *WAOpt);
#endif
