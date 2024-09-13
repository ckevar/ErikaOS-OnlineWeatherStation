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
#include "erika_task_conf.h"

#include <stdio.h>
#include <string.h>


/*
 * SysTick ISR2
 */

ISR2(systick_handler)
{
	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}

TASK(LCD_IN) {
    static unsigned int px, py;
    static uint32_t burst = 0;
	TPoint p;
	
	if(GetTouch_SC_Async(&px, &py)) {
		burst |= 1; 

		/* Draw touches */
		LCD_SetColors(0xf800, 0xf800);
		LCD_DrawFullRect(px, py, 1, 1);
		LCD_SetColors(APP_BACKGROUND_COLOR, APP_BACKGROUND_COLOR);
		
    }

    if ((burst & 3) == 2) {
        p.x = px;
        p.y = py;
		OnTouch(weather_ui, &p);
		burst = 0;
    }

	burst <<= 1;
}
TASK(ESP8266_POLL) {
	if (esp8_status.cmd != ESP8_UNKNOWN)
		return;

	esp8266_poll();
}

TASK(NETWORK) {
	network();
}

TASK(WEATHER_UPDATE) {
	weather_update();
}

TASK(SPOTIFY_UPDATE) {
	spotify_update_player();
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

	UI_init();
	esp8266_init();
	
	EXEC(LCD_IN);
	EXEC(ESP8266_POLL);
	EXEC(NETWORK);
	EXEC(WEATHER_UPDATE);
	EXEC(SPOTIFY_UPDATE);

	for (;;) {
	}

}

