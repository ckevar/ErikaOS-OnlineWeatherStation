
/* ui_ap.c
 *
 *  Created on: 21/Mar/2022
 *      Author: C. Alvarado
 */

#include "WidgetConfig.h"

#include "Widget.h"
#include "fonts.h"

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

// tmp header
#include "lcd_log.h"


static unsigned char *temp_number[10] = {zero, one, two, three, four, five, six, seven, eight, nine};

Image location_icon = {
	.image = (unsigned char *)no_location
};

Text city = {
	&Font16x24, Black
};

Text description = {
	// &Font12x12, Black
	&Font8x8, Black
};

ButtonIcon WiFi_icon = {
		WiFi_settingup, WiFi_connected, RESET_ESP8266_EVNT
};

ButtonIcon WiFi_AP_icon = {
		settings_on, settings_off, SET_AP_ESP8266_EVNT
};

// Image WiFi_AP_icon = {
// 	.image = (unsigned char *) settings_off
// };

Text temp_val = {
	&Font16x24, Black
};

Text temp_degree = {
	&Font16x24, Black
};


Text feels = {
	&Font12x12, Black
};

Text like = {
	&Font12x12, Black
};

Text feels_like_tmp = {
	&Font16x24, Black
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

Text state_dev = {
	&Font8x8, Black
};

Widget weather_ui[NUMWIDGETS] = {
	// Pos Y, pos X, dim x, dim y, type, pointer of the text
	{18, 23, 20, 20, IMAGE, (void *)&location_icon},
	{24, 43, 24, 24, TEXT, (void *)&city},
	{224, 24, 30, 30, BUTTONICON, (void *)&WiFi_icon},
	{270, 24, 30, 30, BUTTONICON, (void *)&WiFi_AP_icon},
	{61, 17, 8, 8, TEXT, (void *)&description},
	{144, 285, 24, 24, TEXT, (void *)&temp_degree},
	{189, 141, 12, 12, TEXT, (void *)&feels},
	{201, 141, 12, 12, TEXT, (void *)&like},
	{189, 220, 12, 12, TEXT, (void *)&feels_like_tmp},
	{189, 285, 24, 24, TEXT, (void *)&temp_val},
	{17, 86, 100, 100, IMAGE, (void *)&OW_description_img},
	{123, 110, 54, 54, IMAGE, (void *)&temp_sign}, 
	{177, 110, 54, 54, IMAGE, (void *)&temp_dec_img},
	{231, 110, 54, 54, IMAGE, (void *)&temp_uni_img},
	{201, 23, 8, 8, TEXT, (void *) &state_dev},

};

void DrawFixWidgets(){
	WPrint(&weather_ui[TEMP_DEGREE_STR], "C");	
	WPrint(&weather_ui[FEELS_STR], "feels");	
	WPrint(&weather_ui[LIKE_STR], " like");	
	WPrint(&weather_ui[TEMP_DEGREE2_STR], "C");	

}

/**************** PROGRESS BAR FUNCTIONS ***************/
static void set_progress_bar(short state, short max_state, unsigned short colors_bar) {
	unsigned short bar = (state * 320) / max_state; 
	LCD_SetColors(colors_bar, colors_bar);
	LCD_DrawFullRect(0, 79, bar, 3);
	LCD_SetColors(APP_BACKGROUND_COLOR, APP_BACKGROUND_COLOR);
}

void UI_clear_progress() {
	LCD_SetColors(UI_CLEAN_PROGRESS_BAR_COLOR, UI_CLEAN_PROGRESS_BAR_COLOR);
	LCD_DrawFullRect(0, 79, 320, 3);
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
	WPrint(&weather_ui[DESCRIPTION_STR], weatherDescription);
}

void UI_writeWeatherFeelsLike(char *feels_like_val) {
	char temp[3] = {0,0,0};
	unsigned char i = 0;
	LCD_UsrLog("%s\r\n", feels_like_val);
	while (*feels_like_val != '.') {
		temp[i++] = *feels_like_val;
		feels_like_val++;
	}

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

	while (*curr_temp != '.'){
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
/*******************************************************/


/**************** SETTINGS AP FUNCTIONS ****************/
void UI_SettingsOn(void) {
	// biconinfo(&weather_ui[WiFi_AP_SET])->iconr = (unsigned char *)settings_on;
	DrawOn(&weather_ui[WiFi_AP_SET]);
}

void UI_SettingsOff(void) { 
	// biconinfo(&weather_ui[WiFi_AP_SET])->iconr = (unsigned char *)settings_off;
	DrawOff(&weather_ui[WiFi_AP_SET]);
}
/*******************************************************/

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