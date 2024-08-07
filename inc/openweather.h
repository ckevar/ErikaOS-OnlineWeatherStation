/*
 * Created Mar 19, 2022
 *  - by ckevar
 */
#ifndef OPEN_WEATHER_H
#define OPEN_WEATHER_H 

#include "openweather_private.h"

/*** Request Parameters **/
#define OWAPI_STRLEN(x)			(sizeof(x) - 1)
#define OWAPI_DNS_PORT 	        "\"api.openweathermap.org\",80"
#define OWAPI_DNS_PORT_LEN      OWAPI_STRLEN(OWAPI_DNS_PORT)

// LATITUD
#define OWAPI_GET_LAT 	        "GET /data/2.5/weather?lat="
#define OWAPI_GET_LAT_LEN	    OWAPI_STRLEN(OWAPI_GET_LAT)

// LONGITUD
#define OWAPI_GET_LON 	        "&lon="
#define OWAPI_GET_LON_LEN 	    OWAPI_STRLEN(OWAPI_GET_LON)

// UNITS, METRICS and
#define OWAPI_GET_UNITSnKEY 	"&units=metric"\
								"&appid=" OPENWEATHER_APP_ID " HTTP/1.1\r\n"\
								"Host: api.openweathermap.org\r\n"\
								"User-Agent: ERIKA RTOS/ESP8266/v1.0\r\n\r\n"
#define OWAPI_GET_UNITSnKEY_LEN OWAPI_STRLEN(OWAPI_GET_UNITSnKEY)
#define OWAPI_GET_RESOURCE_STR_LEN 	3

/*** Response Parameters ***/
// JSON Members
#define OWAPI_BUFFER_LENGTH     50	// numbers of parameters it's interesting

enum OWAPIParameters {
    iOWAPI_TIMEZONE,
    iOWAPI_TIME,
    iOWAPI_FEELS_LIKE,
    iOWAPI_TEMP,
    iOWAPI_ICON,
    iOWAPI_DESCRIPTION,
    OWAPI_PARAMS_COUNT,
};

#define OWAPI_DESCRIPTION 		"description"
#define OWAPI_DESCRIPTION_LEN 	OWAPI_STRLEN(OWAPI_DESCRIPTION)

#define OWAPI_ICON 			    "icon"
#define OWAPI_ICON_LEN 		    OWAPI_STRLEN(OWAPI_ICON)
								
#define OWAPI_TEMP			    "temp" 
#define OWAPI_TEMP_LEN 		    OWAPI_STRLEN(OWAPI_TEMP)

#define OWAPI_FEELS_LIKE 		"feels_like"
#define OWAPI_FEELS_LIKE_LEN	OWAPI_STRLEN(OWAPI_FEELS_LIKE)

#define OWAPI_TIME              "dt"
#define OWAPI_TIME_LEN          2

#define OWAPI_TIMEZONE          "timezone"
#define OWAPI_TIMEZONE_LEN      OWAPI_STRLEN(OWAPI_TIMEZONE)

#define OWAPI_JSON_COD 	 	    "cod"
#define OWAPI_JSON_COD_LEN	    3
#define OWAPI_JSON_200		    "200"
#define OWAPI_JSON_200_LEN 	    3

char OWAPI_get_weather(char *json, char **vals, unsigned short *vals_len);

#endif
