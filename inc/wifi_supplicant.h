#ifndef WIFI_SUPPLICANT_H
#define WIFI_SUPPLICANT_H

#include "http.h"

#define WRES_INDEX			"/\0"
#define WRES_INDEX_LEN		2

#define WRES_FAVICON				"/favicon.ico"
#define WRES_FAVICON_LEN			12
/*******************************************************************/

/******************************** /set_wifi ************************/
#define WRES_SETWiFi				"/set_wifi\0"
#define WRES_SETWiFi_LEN			10

#define WSUPP_SSID					"ssid="
#define WSUPP_SSID_LEN				5

#define WSUPP_PSWD					"psw="
#define WSUPP_PSWD_LEN				4
/********************************************************************/

/********************************** HTML ****************************/
/* Content to send */
	
	// INDEX
#define WSUPP_INDEX					1
#define WEBAPP_INDEX_STR			\
"<head><title>Erika WiFi</title></head>"\
"<body style=margin:3rem>"\
	"<center>"\
		"<h2>Erika WiFi Credentials</h2>"\
		"<form style=border-radius:1em;width:320px;background:#b1f1c2;padding:1rem action=set_wifi method=post>"\
			"<label for=ssid>SSID:</label><br>"\
			"<input style=border:none type=text id=ssid name=ssid><br>"\
			"<label for=psw>Password:</label><br>"\
			"<input style=border:none type=password id=psw name=psw><br>"\
			"<input style=background:#2d6a44;border:none;border-radius:0.5em;padding:0.7em;margin-top:1em;color:white type=submit value=Submit>"\
		"</form>"\
	"</center>"\
"</body>"
	
#define STR_HELPER(num)				#num
#define NUMTOSTR(num)				STR_HELPER(num)
#define WEBAPP_INDEX_LEN			541
#define WEBAPP_INDEX_H_STR			NUMTOSTR(WEBAPP_INDEX_LEN)
#define WEBAPP_INDEX_H_LEN			3	// Length of *_CL

	// Not found
#define WSUPP_NOT_FOUND				2
#define WEBAPP_NOT_FOUND_STR		""
#define WEBAPP_NOT_FOUND_LEN		0
#define WEBAPP_NOT_FOUND_H_STR		NUMTOSTR(WEBAPP_NOT_FOUND_LEN)
#define WEBAPP_NOT_FOUND_H_LEN		1

	// All done
#define WEBAPP_ALLDONE				4
#define WEBAPP_ALLDONE_STR			\
"<head>"\
	"<title>Erika WiFi</title>"\
"</head>"\
"<body style=margin:3rem>"\
"<center>"\
	"<h2>Erika WiFi Credentials</h2>"\
	"<div style=border-radius:1em;width:320px;background:#b1f1c2;padding:1rem>"\
		"<b>Connecting...</b>"\
		"<br><br>Check device or <a href=/>try again<a/>"\
	"</div>"\
"</center>"\
"</body>"

#define WEBAPP_ALLDONE_LEN			263
#define WEBAPP_ALLDONE_H_STR		NUMTOSTR(WEBAPP_ALLDONE_LEN)
#define WEBAPP_ALLDONE_H_LEN		3
/********************************************************************/

#define wifi_supplicant_http(http, method, body)	\
	outHTTP_basice_header(http, method);\
	outHTTP_body(http, body##_STR, body##_LEN)

#endif
