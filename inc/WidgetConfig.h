/*
 * WidgetConfig.h
 *
 *  Created on: 22/ott/2015
 *      Author: admim
 * 		Modified: c. Alvarado - Mar 21, 2022
 */

#ifndef WIDGETCONFIG_H_
#define WIDGETCONFIG_H_

#include "Widget.h"
#include "stm32f4_discovery_lcd.h"


enum WidgetID{
LOCATION_IMG,
CITY_STR,		
WiFi_IMG,		
WiFi_AP_SET,
SPOTIFY,
DESCRIPTION_STR,		
TEMP_DEGREE_STR,	
FEELS_STR,	
LIKE_STR,	
FEELS_LIKE_VAL_STR,	
TEMP_DEGREE2_STR,	
OW01D_IMG,	
TEMP_SIGN_IMG,	
TEMP_DEC_IMG,	
TEMP_UNI_IMG,	
STATE_DEV_STR,	
REQ_TIME,   
SPOTIFY_STATUS,
MUSIC_CAST,
NUMWIDGETS,	
};

#define SET_AP_ESP8266_EVNT			0x02
#define SPOTIFY_CONF_EVENT			0x01

// 0xb798 -> This is background color in a lazy way
#define APP_BACKGROUND_COLOR 		0x7f12
#define APP_ON_PRIMARY_CONTAINER	0x0962

#define UI_CLEAN_PROGRESS_BAR_COLOR 0xffff
#define UI_PROGRESS_BAR_COLOR 		0x0962
#define UI_ERR_PROGRESS_BAR_COLOR 	0x8020

extern Widget weather_ui[NUMWIDGETS];

void DrawFixWidgets();

void UI_init(void);
void UI_clear_progress(void);
void UI_set_progress(short state, short max_state);
void UI_set_err_progress(short state, short max_state);

void UI_WiFiNo(void);
void UI_WiFiSettingUp(void);
void UI_WiFiConnected(void);

void UI_writeCity(char *cityName);
void UI_LocationAvailable(void);
void UI_LocationUnavailable(void);

void UI_writeWeatherDescription(char *weatherDescription);
void UI_writeWeatherFeelsLike(char *feels_like_val);
void UI_setWeatherIcon(unsigned short *iconID);
void UI_writeWeatherCurrTemp(char *curr_temp);
void UI_setTime(char *timezone, char *time);
void UI_set_track(char *track);

void UI_SettingsOn(void);
void UI_SettingsOff(void);
void UI_WriteState(char *str);

#endif /* WIDGETCONFIG_H_ */
