
/* ui_ap.c
 *
 *  Created on: 21/Mar/2022
 *      Author: C. Alvarado
 */

#include <time.h>
#include <stdlib.h>

#include "stm32f4_discovery.h"
#include "WidgetConfig.h"

#include "Widget.h"
#include "fonts.h"
#include "STMPE811QTR.h"

#include "OW01d.h"
#include "OW02d.h"
#include "OW03d.h"
#include "OW04d.h"
#include "OW09d.h"
#include "OW10d.h"
#include "OW11d.h"
#include "OW12d.h"
#include "OW13d.h"
#include "OW50d.h"

#include "zero.h"
#include "one.h"
#include "two.h"
#include "three.h"
#include "four.h"
#include "five.h"
#include "six.h"
#include "seven.h"
#include "eight.h"
#include "nine.h"

#include "no_location.h"
#include "location.h"

#include "WiFi_no.h"
#include "WiFi_settingup.h"
#include "WiFi_connected.h"

#include "settings_off.h"
#include "settings_on.h"

#include "spotify_off.h"
#include "music_cast.h"
// tmp header
#include "lcd_log.h"

const static unsigned char *temp_number[10] = {zero, one, two, three, 
    four, five, six, seven, eight, nine};

Image location_icon = {
	.image = (unsigned char *)no_location
};

Text txt16x24_on_primary = {
	&Font16x24, APP_ON_PRIMARY_CONTAINER
};

Text txt8x8_on_primary = {
	&Font8x8, APP_ON_PRIMARY_CONTAINER
};

Text feels_like_txt = {
	&Font12x12, APP_ON_PRIMARY_CONTAINER
};

ButtonIcon WiFi_icon = {
	WiFi_settingup, WiFi_connected, 0
};

ButtonIcon WiFi_AP_icon = {
	settings_on, settings_off, SET_AP_ESP8266_EVNT
};

ButtonIcon spotify_icon = {
	NULL, spotify_off, SPOTIFY_CONF_EVENT
};

Image OW_description_img = {
	.image = (unsigned char *)OW01d
};

Image temp_sign = {
	.image = 0
};

Image temp_dec_img = {
	.image = (unsigned char *)zero
};

Image temp_uni_img = {
	.image = (unsigned char *)zero
};

Image music_cast_icon = {
	.image = (unsigned char *)music_cast_raw
};

#define LEFT_ALIGN_X		13	
#define TEMP_ON_Y			42
#define BUTTON_Y			183
#define FEELS_LIKE_Y		120
#define SPOTIFY_INFO_X		17
#define SPOTIFY_INFO_Y		157

Widget weather_ui[NUMWIDGETS] = {
	// Pos Y, pos X, dim x, dim y, type, pointer of the text
	{12, LEFT_ALIGN_X, 20, 20, IMAGE, (void *)&location_icon},
	{13, 40, 24, 24, TEXT, (void *)&txt16x24_on_primary},
	{63, BUTTON_Y, 42, 30, BUTTONICON, (void *)&WiFi_icon},
	{151, BUTTON_Y, 30, 30, BUTTONICON, (void *)&WiFi_AP_icon},
	{225, BUTTON_Y, 30, 30, BUTTONICON, (void *)&spotify_icon},
	{140, LEFT_ALIGN_X, 8, 8, TEXT, (void *)&txt8x8_on_primary},
	{79, 285, 24, 24, TEXT, (void *)&txt16x24_on_primary},
	{FEELS_LIKE_Y - 12, 141, 12, 12, TEXT, (void *)&feels_like_txt},
	{FEELS_LIKE_Y, 141, 12, 12, TEXT, (void *)&feels_like_txt},
	{FEELS_LIKE_Y - 9, 220, 24, 24, TEXT, (void *)&txt16x24_on_primary},
	{FEELS_LIKE_Y - 9, 285, 24, 24, TEXT, (void *)&txt16x24_on_primary},
	{19, 32, 100, 100, IMAGE, (void *)&OW_description_img},
	{123, TEMP_ON_Y, 54, 54, IMAGE, (void *)&temp_sign}, 
	{177, TEMP_ON_Y, 54, 54, IMAGE, (void *)&temp_dec_img},
	{231, TEMP_ON_Y, 54, 54, IMAGE, (void *)&temp_uni_img},
	{228, 5, 8, 8, TEXT, (void *) &txt8x8_on_primary},
    {14, 251, 8, 8, TEXT, (void *) &txt8x8_on_primary},
    {SPOTIFY_INFO_Y, SPOTIFY_INFO_X, 8, 8, TEXT, (void *) &txt8x8_on_primary},
	{5, SPOTIFY_INFO_Y, 10, 8, IMAGE, (void *)&music_cast_icon}
};

#define BBOX_X	44
#define BBOX_Y	172
#define BBOX_W	233
#define BBOX_H	51

void DrawFixWidgets() {
	WPrint(&weather_ui[TEMP_DEGREE_STR], "C");	
	WPrint(&weather_ui[FEELS_STR], "feels");	
	WPrint(&weather_ui[LIKE_STR], " like");	
	WPrint(&weather_ui[TEMP_DEGREE2_STR], "C");	
	WPrintLog(&weather_ui[SPOTIFY_STATUS], "Spotify Non Connected");

    /* Button Bar */
	LCD_SetColors(0x3b2d, 0x3b2d);
    LCD_DrawFullRect(BBOX_X, BBOX_Y, BBOX_W, BBOX_H);

    LCD_SetColors(APP_BACKGROUND_COLOR, APP_BACKGROUND_COLOR);
	
	/* Upper Right */
	LCD_DrawLine(BBOX_X, BBOX_Y, 4, 0);
	LCD_DrawLine(BBOX_X, BBOX_Y + 1, 2, 0);
	LCD_DrawLine(BBOX_X, BBOX_Y + 2, 2, 1);

	/* Bottom Right */
	LCD_DrawLine(BBOX_X, BBOX_Y + BBOX_H, 4, 0);
	LCD_DrawLine(BBOX_X, BBOX_Y + BBOX_H - 1, 2, 0);
	LCD_DrawLine(BBOX_X, BBOX_Y + BBOX_H - 3, 2, 1);

	/* Bottom Left */
	LCD_DrawLine(BBOX_X + BBOX_W - 4, BBOX_Y + BBOX_H, 4, 0);
	LCD_DrawLine(BBOX_X + BBOX_W - 2, BBOX_Y + BBOX_H - 1, 2, 0);
	LCD_DrawLine(BBOX_X + BBOX_W - 1, BBOX_Y + BBOX_H - 3, 2, 1);

	/* Upper Left */
	LCD_DrawLine(BBOX_X + BBOX_W - 4, BBOX_Y, 4, 0);
	LCD_DrawLine(BBOX_X + BBOX_W - 2, BBOX_Y + 1, 2, 0);
	LCD_DrawLine(BBOX_X + BBOX_W - 1, BBOX_Y + 2, 2, 1);
	/*************/

    DrawOff(&weather_ui[WiFi_AP_SET]);
	DrawOff(&weather_ui[SPOTIFY]);
}
void UI_init(void) {
	STM_EVAL_LEDInit(LED4);
	
	/* Init Touchscreen */
	IOE_Config();
	InitTouch(-0.1247, 0.0650, -340, 5);

	STM32f4_Discovery_LCD_Init();
	// LCD_LOG_Init();
	
	LCD_Clear(APP_BACKGROUND_COLOR);
	LCD_SetColors(APP_BACKGROUND_COLOR, APP_BACKGROUND_COLOR);
	
	DrawInit(weather_ui);
	
	DrawFixWidgets();

	LCD_SetFont(&Font8x12);
}

/**************** PROGRESS BAR FUNCTIONS ***************/
#define PROGRESS_BAR_Y          237
#define PROGRESS_BAR_THICKNESS  3

static void set_progress_bar(short state, short max_state, unsigned short colors_bar) {
	unsigned short bar = (state * 320) / max_state; 
    if (bar > 320)
        bar = 0;
	LCD_SetColors(colors_bar, colors_bar);
	LCD_DrawFullRect(0, PROGRESS_BAR_Y, bar, PROGRESS_BAR_THICKNESS);
	LCD_SetColors(APP_BACKGROUND_COLOR, APP_BACKGROUND_COLOR);
}

void UI_clear_progress() {
	LCD_SetColors(UI_CLEAN_PROGRESS_BAR_COLOR, UI_CLEAN_PROGRESS_BAR_COLOR);
	LCD_DrawFullRect(0, PROGRESS_BAR_Y, 320, PROGRESS_BAR_THICKNESS);
	LCD_SetColors(APP_BACKGROUND_COLOR, APP_BACKGROUND_COLOR);
}

void UI_set_progress(short state, short max_state) {
	set_progress_bar(state, max_state, UI_PROGRESS_BAR_COLOR);
}

void UI_set_err_progress(short state, short max_state) {
	set_progress_bar(state, max_state, UI_ERR_PROGRESS_BAR_COLOR);
}

/*******************************************************/

/****************** WiFi UI FUNCTIONS ******************/
void UI_WiFiNo(void) {
	biconinfo(&weather_ui[WiFi_IMG])->iconr = (unsigned char *)WiFi_no;
	DrawOff(&weather_ui[WiFi_IMG]);
}

void UI_WiFiSettingUp(void) {
	biconinfo(&weather_ui[WiFi_IMG])->iconr = (unsigned char *)WiFi_settingup;
	DrawOff(&weather_ui[WiFi_IMG]);
}

void UI_WiFiConnected(void) {
	biconinfo(&weather_ui[WiFi_IMG])->iconr = (unsigned char *)WiFi_connected;
	DrawOff(&weather_ui[WiFi_IMG]);
}
/*******************************************************/



/***************** LOCATIONS FUNCTIONS *****************/
void UI_writeCity(char *cityName) {
	WPrint(&weather_ui[CITY_STR], cityName);
}
void UI_LocationAvailable(void) {
	imginfo(&weather_ui[LOCATION_IMG])->image = (unsigned char *)location;
	DrawOff(&weather_ui[LOCATION_IMG]);
}
void UI_LocationUnavailable(void) {
	imginfo(&weather_ui[LOCATION_IMG])->image = (unsigned char *)no_location;
	DrawOff(&weather_ui[LOCATION_IMG]);
}
/*******************************************************/


/****************** WEATHER FUNCTIONS ******************/
void UI_writeWeatherDescription(char *weatherDescription) {
	WPrintLog(&weather_ui[DESCRIPTION_STR], weatherDescription);
}

void UI_writeWeatherFeelsLike(char *feels_like_val) {
	char temp[3] = {0,0,0};
	unsigned char i = 0;
	
	while ((*feels_like_val != '.') && (*feels_like_val != ',')) {
		temp[i++] = *feels_like_val;
		feels_like_val++;
	}

	if(i > 5)
		i = 0;

	WPrint(&weather_ui[FEELS_LIKE_VAL_STR], temp);

}

void UI_setWeatherIcon(unsigned short *iconID) {
	switch(*iconID) {
		case 0x3130: // 01
			imginfo(&weather_ui[OW01D_IMG])->image = (unsigned char *) OW01d; 
			break;

		case 0x3230: // 02
			imginfo(&weather_ui[OW01D_IMG])->image = (unsigned char *) OW02d; 
			break;	

		case 0x3330: // 03d
			imginfo(&weather_ui[OW01D_IMG])->image = (unsigned char *) OW03d; 
			break;

		case 0x3430: // 04d
			imginfo(&weather_ui[OW01D_IMG])->image = (unsigned char *) OW04d; 
			break;

		case 0x3930: // 09d
			imginfo(&weather_ui[OW01D_IMG])->image = (unsigned char *) OW09d; 
			break;

		case 0x3031: // 10d
			imginfo(&weather_ui[OW01D_IMG])->image = (unsigned char *) OW10d; 
			break;

		case 0x3131: // 11d
			imginfo(&weather_ui[OW01D_IMG])->image = (unsigned char *) OW11d; 
			break;

		case 0x3231: // 12d
			imginfo(&weather_ui[OW01D_IMG])->image = (unsigned char *) OW12d; 
			break;

		case 0x3331: // 13d
			imginfo(&weather_ui[OW01D_IMG])->image = (unsigned char *) OW13d; 
			break;

		case 0x3035: // 50d
			imginfo(&weather_ui[OW01D_IMG])->image = (unsigned char *) OW50d; 
			break;

	}
	
	DrawOff(&weather_ui[OW01D_IMG]);
}

void UI_writeWeatherCurrTemp(char *curr_temp) {
	static char prev_sig = 0;
	char tmp[3] = {0, 0, 0};
	unsigned char i = 0;

	while ((*curr_temp != '.') && (*curr_temp != ',')){
		tmp[i++] = *curr_temp;
		curr_temp++;
	}

	// Clean the sign section on LCD
	LCD_SetColors(APP_BACKGROUND_COLOR, APP_BACKGROUND_COLOR);
	LCD_DrawFullRect(135, 137, 30, 3);

	if (i == 3) {
		// Draw sign + DEC + UNITS
		LCD_SetColors(Black, Black);
		LCD_DrawFullRect(135, 137, 30, 3);
		LCD_SetColors(APP_BACKGROUND_COLOR, APP_BACKGROUND_COLOR);

		imginfo(&weather_ui[TEMP_DEC_IMG])->image = \
					(unsigned char *)temp_number[tmp[1] - 48];
		imginfo(&weather_ui[TEMP_UNI_IMG])->image = \
					(unsigned char *)temp_number[tmp[2] - 48];

		DrawOff(&weather_ui[TEMP_DEC_IMG]);
		DrawOff(&weather_ui[TEMP_UNI_IMG]);
		prev_sig = 1;

	} 
	else if (i == 2) {
		// Check if there's a sign or a number

		if (tmp[0] == '-') {
			// Clean the sign region tha goes on decimals
			LCD_DrawFullRect(177, 110, 54, 54);

			// Draw sign + UNITS
			LCD_SetColors(Black, Black);
			LCD_DrawFullRect(187, 137, 30, 3);
			LCD_SetColors(APP_BACKGROUND_COLOR, APP_BACKGROUND_COLOR);
			
			imginfo(&weather_ui[TEMP_UNI_IMG])->image = \
					(unsigned char *)temp_number[tmp[1] - 48];
			DrawOff(&weather_ui[TEMP_UNI_IMG]);

		} else {
			// Draw Dec + Units
			imginfo(&weather_ui[TEMP_DEC_IMG])->image = \
					(unsigned char *)temp_number[tmp[0] - 48];
			imginfo(&weather_ui[TEMP_UNI_IMG])->image = \
					(unsigned char *)temp_number[tmp[1] - 48];

			DrawOff(&weather_ui[TEMP_DEC_IMG]);
			DrawOff(&weather_ui[TEMP_UNI_IMG]);
		}
	} else if (i == 1) {
		// Clean the sign region tha goes on decimals
		LCD_DrawFullRect(177, 110, 54, 54);	
			
		imginfo(&weather_ui[TEMP_UNI_IMG])->image = \
			(unsigned char *)temp_number[tmp[0] - 48];
		DrawOff(&weather_ui[TEMP_UNI_IMG]);		
	}

}

void UI_setTime(char *timezone, char *time) {
    time_t epochs;
    struct tm *time_info;
    char buff[8];
    
    epochs = atoi(time) + atoi(timezone);
    time_info = localtime(&epochs);
    strftime(buff, 8, "%I:%M%p", time_info);

    WPrintLog(&weather_ui[REQ_TIME], buff);
}

void UI_set_track(char *msg) {
	LCD_DrawFullRect(SPOTIFY_INFO_X, SPOTIFY_INFO_Y, 300, 8);
	WPrintLog(&weather_ui[SPOTIFY_STATUS], msg);
}

void UI_set_track_progress(char *progress_str, char *duration_str) {
	uint32_t progress, duration;
	progress = atoi(progress_str);
	duration = atoi(duration_str);

	LCD_SetColors(UI_CLEAN_PROGRESS_BAR_COLOR, UI_CLEAN_PROGRESS_BAR_COLOR);
	LCD_DrawFullRect(SPOTIFY_INFO_X, SPOTIFY_INFO_Y + 10, 286, 1);

	if (duration < progress) {
		LCD_SetColors(APP_BACKGROUND_COLOR, APP_BACKGROUND_COLOR);	
		return;
	}

	progress = (progress * 286) / duration;

	LCD_SetColors(UI_PROGRESS_BAR_COLOR, UI_PROGRESS_BAR_COLOR);
	LCD_DrawFullRect(SPOTIFY_INFO_X, SPOTIFY_INFO_Y + 10, progress, 1);
	LCD_SetColors(APP_BACKGROUND_COLOR, APP_BACKGROUND_COLOR);	
}
/*******************************************************/


/**************** SETTINGS AP FUNCTIONS ****************/
void UI_SettingsOn(void) {
	DrawOn(&weather_ui[WiFi_AP_SET]);
}

void UI_SettingsOff(void) { 
	DrawOff(&weather_ui[WiFi_AP_SET]);
}
/*******************************************************/

void UI_WriteState(char *str) {
	LCD_SetColors(APP_BACKGROUND_COLOR, APP_BACKGROUND_COLOR);
	LCD_DrawFullRect(5, 228, 300, 8);
	WPrintLog(&weather_ui[STATE_DEV_STR], str);	
}

/*
 * #bash to conver number file into the desired sizes
 * 	convert p-replace-color.php.png -crop 54x54+200+212 one.png
 * 	convert p-replace-color.php.png -crop 54x54+335+212 two.png
 * 	convert p-replace-color.php.png -crop 54x54+467+212 three.png
 * 	convert p-replace-color.php.png -crop 54x54+612+212 four.png
 * 	convert p-replace-color.php.png -crop 54x54+748+212 five.png
 * 	convert p-replace-color.php.png -crop 54x54+200+325 six.png
 * 	convert p-replace-color.php.png -crop 54x54+335+325 seven.png
 * 	convert p-replace-color.php.png -crop 54x54+471+325 eight.png
 * 	convert p-replace-color.php.png -crop 54x54+612+325 nine.pn
 *	convert p-replace-color.php.png -crop 54x54+753+325 zero.png
*/
