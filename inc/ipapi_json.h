/*
 * Created Mar 19, 2022
 *  - by ckevar
 */

#ifndef IP_API_JSON_H
#define IP_API_JSON_H 

#define IPAPI_STRLEN(x)			(sizeof(x) - 1)
#define IPAPI_JSON_DNS_PORT 	"\"ip-api.com\",80"
#define IPAPI_JSON_DNS_PORT_LEN IPAPI_STRLEN(IPAPI_JSON_DNS_PORT)
#define IPAPI_GET_RESOURCE 		"GET /json HTTP/1.1\r\n"\
								"Host: ip-api.com\r\n"\
								"User-Agent: ERIKA RTOS/ESP8266/v1.0\r\n\r\n"
								
#define IPAPI_GET_RESOURCE_LEN 	"77"	// length of requested resources

/// JSON members
#define IPAPI_JSON_MEMBERS 		3 	// number of variables required from arrival
#define IPAPI_JSON_BUFFER_LENGTH 50 //								
#define IPAPI_JSON_STATUS 		"status"
#define IPAPI_JSON_STATUS_LEN 	IPAPI_STRLEN(IPAPI_JSON_STATUS)

#define IPAPI_JSON_SUCCESS 		"\"success\""
#define IPAPI_JSON_SUCCESS_LEN 	IPAPI_STRLEN(IPAPI_JSON_SUCCESS)

#define IPAPI_JSON_CITY			"city"
#define IPAPI_JSON_CITY_LEN		IPAPI_STRLEN(IPAPI_JSON_CITY)
#define IPAPI_JSON_CITY_Idx 	2

#define IPAPI_JSON_LAT 			"lat"
#define IPAPI_JSON_LAT_LEN 		IPAPI_STRLEN(IPAPI_JSON_LAT)
#define IPAPI_JSON_LAT_Idx 		1

#define IPAPI_JSON_LON 			"lon"
#define IPAPI_JSON_LON_LEN 		IPAPI_STRLEN(IPAPI_JSON_LON)
#define IPAPI_JSON_LON_Idx 		0


char IPAPI_get_location_PtrLen(char *json, char **vals, unsigned short *vals_len);

#endif
