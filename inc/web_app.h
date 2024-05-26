/*
 * Created Mar 24, 2022
 *  - by C. Alvarado
 */
#ifndef WEB_APP_H
#define WEB_APP_H 

#define WEBAPP_FAVICON_STR			"/favicon.ico"
#define WEBAPP_FAVICON_LEN			12
/*************************************************/

/******************* /set_wifi *******************/
#define WEBAPP_SETWiFi_STR			"/set_wifi\0"
#define WEBAPP_SETWiFi_LEN			10

#define WEBAPP_SSID_STR				"ssid="
#define WEBAPP_SSID_LEN				5

#define WEBAPP_PSWD_STR				"psw="
#define WEBAPP_PSWD_LEN				4
/*************************************************/

/* code status */
#define HTTP_NOT_FOUND				0
#define HTTP_NOT_FOUND_STR			"HTTP/1.1 404 Not Found\r\n" 
#define HTTP_NOT_FOUND_LEN			24

#define HTTP_OK						1
#define HTTP_OK_STR					"HTTP/1.1 200 OK\r\n"
#define HTTP_OK_LEN					17

/* content-type */
#define HTTP_NO_CONTENT_TYPE 				0
#define HTTP_CONTENT_TYPE_TEXT_HTML 		1
#define HTTP_CONTENT_TYPE_TEXT_HTML_STR 	"Content-type: text/html\r\n"
#define HTTP_CONTENT_TYPE_TEXT_HTML_LEN 	25

/* Connection */
#define HTTP_NON_CONNECTION			0
#define HTTP_CONN_CLOSE				1
#define HTTP_CONN_CLOSE_STR			"Connection: close\r\n"
#define HTTP_CONN_CLOSE_LEN			19

#define HTTP_CONN_KEEP_ALIVE		2
#define HTTP_CONN_KEEP_ALIVE_STR	"Connection: keep-alive\r\n"
#define HTTP_CONN_KEEP_ALIVE_LEN	24

/* Content-Length */
#define HTTP_CONTENT_LEN
#define HTTP_CONTENT_LEN_STR		"Content-length: "
#define HTTP_CONTENT_LEN_LEN		16

/*************************************** HTML ***********************/
/* Content to send */
	
	// INDEX
#define WEBAPP_INDEX				1
#define WEBAPP_INDEX_STR			\
	"<html>"\
		"<head><title>Erika WiFi</title></head>"\
		"<body style=margin-block:3rem;>"\
			"<h2 style=text-align:center;>Erika WiFi Credentials</h2>"\
			"<form style=border-radius:1em;margin:auto;width:320px;background:#b1f1c2;padding:1rem action=set_wifi method=post>"\
				"<label for=ssid>SSID:</label><br>"\
				"<input style=border:none type=text id=ssid name=ssid><br>"\
				"<label for=psw>Password:</label><br>"\
				"<input style=border:none type=password id=psw name=psw><br>"\
				"<input style=background:#2d6a44;border:none;border-radius:0.5em;padding:0.7em;margin-top:1em;color:white type=submit value=Submit>"\
			"</form>"\
		"</body>"\
		"</html>"

#define WEBAPP_INDEX_LEN			581
#define WEBAPP_INDEX_H_STR			"581" 
#define WEBAPP_INDEX_H_LEN			3	// Length of *_CL

	// Not found
#define WEBAPP_NOT_FOUND			2
#define WEBAPP_NOT_FOUND_STR		""
#define WEBAPP_NOT_FOUND_LEN		0
#define WEBAPP_NOT_FOUND_H_STR		"0"
#define WEBAPP_NOT_FOUND_H_LEN		1

	// All done
#define WEBAPP_ALLDONE				4
#define WEBAPP_ALLDONE_STR			\
	"<html>"\
		"<head><title>Erika WiFi</title></head>"\
		"<body style=margin-block:3rem;>"\
			"<h2 style=text-align:center;>Erika WiFi Credentials</h2>"\
			"<div style=border-radius:5em;margin:auto;width:320px;background:#b1f1c2;padding:1rem ><b>Connecting...</b><br><br>Shutting down server...</div>"\
			"<div style=border-radius:5em;margin:auto;width:320px;background:#b1f1c2;padding:1rem ><b>Connecting...</b><br><br>Check device or try again</div>"\
		"</body>"\
	"</html>"

#define WEBAPP_ALLDONE_LEN			290
#define WEBAPP_ALLDONE_H_STR		"290"
#define WEBAPP_ALLDONE_H_LEN		3
/********************************************************************/

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

char mkHTTP(WebAppBuilder_t *WAOpt);
#endif
