/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation,
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/*
 * Simple demo that shows how to use the USART peripheral.
 *
 * Author: 2013  Gianluca Franchino.
 *
 */


#include "ee.h"

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_lcd.h"
#include "lcd_log.h"

#include "esp8266_driver.h"
#include "network.h"
#include "app.h"

#include "Widget.h"
#include "WidgetConfig.h"
#include "Touch.h"
#include "STMPE811QTR.h"

#include <stdio.h>
#include <string.h>


// ESP8266_BUFF_t ESP8266_Buff;

/*
 * SysTick ISR2
 */
ISR2(systick_handler)
{
	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}

uint32_t xarray[512];
uint32_t yarray[512];

TASK(TaskLCDTouch) {
    static unsigned int px, py;
    static uint8_t pv_sw = 0;
    uint8_t sw = 0;
	TPoint p;
    static uint16_t i = 0;

	if(GetTouch_SC_Async(&px, &py)) {
        sw = 1;
        xarray[i] = px;
        yarray[i] = py;
        i = i + 1;
        if (i == 512) {
            i = 0;
            memset(xarray, 0, 512);
            memset(yarray, 0, 512);
        }
    }

    if (pv_sw > sw) {
        p.x = px;
        p.y = py;
		OnTouch(weather_ui, &p);
        memset(xarray, 0, 512);
        memset(yarray, 0, 512);
    }
        
    pv_sw = sw;
}
/**
 * This search for specific words in the message received, but it looks
 * for them, starting in the begging of the buffer until where there's
 * no more chars, and everytime this task is executed, the RX_READ starts
 *.where the last search ended in the buffer.
 */
TASK(Task_ESP82266_RevResponse)
{
	// LCD_UsrLog("%s", ESP8266_Buff.RX_READ);
	if (esp8_status.cmd == ESP8_UNKNOWN) {
		esp8266_response();
	}
	STM_EVAL_LEDToggle(LED4);

}

/**
 * Task used for FSM.
 */
TASK(Task_ESP8266_FSM) {
	network();
}

TASK(Task_Weather_Update) {
	app_fsm_restart();
}

/*
 * ESP8266 TRANSMITTER
 */
void __IRQ EE_CORTEX_MX_DMA2_STREAM6_ISR(void) {
	if (DMA2->HISR & DMA_HISR_TCIF6) {
		// If interruption is because transfer is completed
		DMA2->HIFCR = DMA_HIFCR_CTCIF6;	// Ack interruptions
	} else if (DMA2->HISR & DMA_HISR_DMEIF6) {
		// If interruption on Direct Mode went wrong
		LCD_UsrLog("ERROR on sending\r\n");
		DMA2->HIFCR = DMA_HIFCR_CDMEIF6;	// Ack interruption
	}
}

/*
 * ESP8266 RECEIVER
 */
void __IRQ EE_CORTEX_MX_DMA2_STREAM1_ISR(void) {
	// LCD_UsrLog("CR:%d\r\n", DMA2_Stream1->CR);
	if (DMA2->LISR & DMA_LISR_TCIF1) { 	// Interruption if reception is
										// completed.
		DMA2->LIFCR = DMA_LIFCR_CTCIF1;	// Ack interruptions
	} 
	else if (DMA2->LISR & DMA_LISR_TEIF1) {
		// If interruption on transfer went wrong
		DMA2->LIFCR = DMA_LIFCR_CTEIF1;	// Ack interruption
		LCD_UsrLog("ERROR transfer\r\n");
	}
	else if (DMA2->LISR & DMA_LISR_DMEIF1) {
		// If interruption on Direct Mode went wrong
		DMA2->LIFCR = DMA_LIFCR_CDMEIF1;	// Ack interruption
		LCD_UsrLog("ERROR Direct Mode\r\n");
	}
}

int main(void)
{
	/*
	 * Setup the microcontroller system.
	 * Initialize the Embedded Flash Interface, the PLL and update the
	 * SystemFrequency variable.
	 * For default settings look at:
	 * pkg/mcu/st_stm32_stm32f4xx/src/system_stm32f4xx.c
	 */
	SystemInit();

	/*Initialize Erika related stuffs*/
	EE_system_init();

	/*Initialize systick */
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, SystemCoreClock));
	EE_systick_enable_int();
	EE_systick_start();

	STM_EVAL_LEDInit(LED4);

	/* ESP8266 init */
	esp8266_init(); 	// Loads the buffer into the driver
									// module. 

	/* Init Touchscreen */
	IOE_Config();

	/*Init the LCD*/
	STM32f4_Discovery_LCD_Init();
	// LCD_LOG_Init();

	/**** LCD Calibration Data got with : lcd_touch project ***/
	//InitTouch(-0.096, 0.0650, -367, 15);
	InitTouch(-0.1247, 0.0650, -348, 15);


	/*********************************************************** 
	 * Tool to choose color in 16 bits RGB (5:6:5) 
	 * https://ee-programming-notepad.blogspot.com/2016/10/16-bit-color-generator-picker.html
	 **********************************************************/

	LCD_Clear(APP_BACKGROUND_COLOR);
	LCD_SetColors(APP_BACKGROUND_COLOR, APP_BACKGROUND_COLOR);
	DrawInit(weather_ui);
	DrawFixWidgets();
	LCD_SetFont(&Font8x12);

	SetRelAlarm(AlarmTaskLCDTouch, 1, 50);
	SetRelAlarm(Alarm_ESP82266_RevResponse, 1, 40);
	SetRelAlarm(Alarm_ESP8266_FSM, 15, 80);
	// SetRelAlarm(Alarm_Weather_Update, 180000, 180000);
	SetRelAlarm(Alarm_Weather_Update, 45000, 20000);

	for (;;) {
	}

}

/*
48
01 07

33
5.17 - 5.29
0.30 - 
1.A
15
*/
