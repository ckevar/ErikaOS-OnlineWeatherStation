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


#define NUMWIDGETS 			15 

#define LOCATION_IMG 		0
#define CITY_STR			1
#define WiFi_IMG 			2
#define WiFi_AP_SET 		3
#define DESCRIPTION_STR		4
#define TEMP_DEGREE_STR		5
#define FEELS_STR			6
#define LIKE_STR			7
#define FEELS_LIKE_VAL_STR	8
#define TEMP_DEGREE2_STR	9

#define OW01D_IMG			10

#define TEMP_SIGN_IMG 		11
#define TEMP_DEC_IMG		12
#define TEMP_UNI_IMG		13
#define STATE_DEV_STR 		14

#define RESET_ESP8266_EVNT 	0x01
#define SET_AP_ESP8266_EVNT 0x02

// #define TIMEMODE 	0x00
// #define TIMESETMODE 0x01
// #define ALARMMODE 	0x02
// #define SWATCHMODE 	0x04
// #define PLUS 		0x10
// #define MINUS 		0x20

#define APP_BACKGROUND_COLOR 		0x7E97
#define UI_CLEAN_PROGRESS_BAR_COLOR 0xDFFB
#define UI_PROGRESS_BAR_COLOR 		0x11A5
#define UI_ERR_PROGRESS_BAR_COLOR 	0xB962

extern Widget weather_ui[NUMWIDGETS];

void DrawFixWidgets();

// void set_ImageWidget(Image *Img_w, unsigned char *img_ptr);

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

void UI_SettingsOn(void);
void UI_SettingsOff(void);
void UI_WriteState(char *str);

#endif /* WIDGETCONFIG_H_ */