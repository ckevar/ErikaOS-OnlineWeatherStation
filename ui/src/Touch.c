/*
 * touch.c
 *
 *  Created on: 20/ott/2015
 *      Author: admim
 */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_lcd.h"
#include "STMPE811QTR.h"
#include "Touch.h"
#include <stdio.h>
#include <string.h>

#define TOUCH_AD_VALUE_MAX    (4500)
#define TOUCH_AD_VALUE_MIN    (30)
#define CALIBRATION_RANGE      (10)
#define CURSOR_LEN    (10)

#define xScreenSize (320)
#define yScreenSize (240)
#define xCalMargin (20)
#define yCalMargin (20)

TCal tcs;

static TPoint point_Base[5] = {
  {xCalMargin,yCalMargin},
  {xScreenSize-xCalMargin,yCalMargin},
  {xCalMargin,yScreenSize-yCalMargin},
  {xScreenSize-xCalMargin,yScreenSize-yCalMargin},
  {xScreenSize/2,yScreenSize/2}
};

TPoint touch_points[5];

/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
void delay(volatile uint32_t nCount)
{
  volatile uint32_t index = 0;
  for (index = (100000 * nCount); index != 0; index--);
}

void Draw_Calibration_Mark(unsigned int xm, unsigned int ym)
{
	LCD_DrawUniLine( xm - CURSOR_LEN, ym, xm + CURSOR_LEN, ym);
	LCD_DrawUniLine( xm, ym - CURSOR_LEN, xm, ym + CURSOR_LEN);
}

extern void delay(__IO uint32_t nCount);

unsigned char  Lcd_Touch_Calibration()
{
	int xt, yt;
	unsigned char res;
	float dCalTouch, dCalScreen;
	unsigned char k;

    delay(200);
	/* 4 Calibration points at extremes */
	for (k = 0;k < 4;k++) {
		Draw_Calibration_Mark(point_Base[k].x, point_Base[k].y);
	    res = GetTouch_TC_Sync(&xt, &yt);
	    touch_points[k].x = xt;
	    touch_points[k].y = yt;
	    delay(200);
	}

	dCalScreen = xScreenSize - 2.0*xCalMargin;
	dCalTouch = (float)((touch_points[1].x - touch_points[0].x) + (touch_points[3].x - touch_points[2].x)) / 2.0;
	tcs.xScale = dCalScreen / dCalTouch;

	dCalScreen = yScreenSize - 2.0*yCalMargin;
	dCalTouch = (float)((touch_points[2].y - touch_points[0].y) + (touch_points[3].y - touch_points[1].y)) / 2.0;
	tcs.yScale = dCalScreen / dCalTouch;

	tcs.xOffset = (((float)touch_points[1].x * tcs.xScale - (float)point_Base[1].x)
	             + ((float)touch_points[0].x * tcs.xScale - (float)point_Base[0].x)) / 2.0;

	tcs.yOffset = (((float)touch_points[1].y * tcs.yScale - (float)point_Base[1].y)
	             + ((float)touch_points[0].y * tcs.yScale - (float)point_Base[0].y)) / 2.0;

	/*Draw cross sign for calibration points*/
	Draw_Calibration_Mark(point_Base[4].x, point_Base[4].y);
	res = GetTouch_SC_Sync(&xt, &yt);
	if (xt > (point_Base[4].x + CALIBRATION_RANGE)
	    || xt < (point_Base[4].x - CALIBRATION_RANGE)
	    || yt > (point_Base[4].y + CALIBRATION_RANGE)
	    || yt < (point_Base[4].y - CALIBRATION_RANGE)) {
		return 0;
	} else {
	    return 1;
	}
}

/* 
 * FILTER:
 * ------
 * This module runs two filter, based on updated state equation:
 *
 *      X_hat[k] = X_hat[k - 1] + alpha * (x_measured - X_hat[k - 1])
 *
 *  Y-Axis
 *  ------
 * Data analysis shows that the points on Y-axis are easily denoised
 * with the previous equation with an alpha value (0.2) such that the
 * trade-off between a settling time less than a second and a precision
 * that ranges 6 pixels.
 *
 *  X-Axis
 *  ------
 * On the other hand, the x-axis data requires a lower alpha in order
 * to have a precision comparable to y-axis' behaviour. Keep in mind
 * a lower alpha rises the settling time, in this case up to 2.4 
 * seconds with a precision that ranges 20 pixels. (smaller than the
 * sizes of the buttons we have - 30x30px -).
 * In order to get rid of the 2.4 sec response, alpha was made variable
 * over time. and it's restarted everytime there's a touch event.
 *
 *           alpha0 - alpha1
 * alpha_t = --------------- + alpha1
 *            sigma * t + 1
 * 
 * such that alpha1 > 0, alpha0 > alpha1, sigma > 0,
 *
 * alpha_0: The initial alpha and it's recomended to be larger than
 *          alpha_1, so the filter has a faster response but poor
 *          denoising ability. 
 *
 * alpha_1: The target alpha, it's the value that performs well over
 *			time.
 * 
 * sigma:   The rate of decrease, how fast alpha0 is going to alpha1.
 *
 * author: C. Alvarado
 *
 * { */
#define ALPHA10_X   5.799 // alpha1 - alpha0
#define ALPHA1_X    0.001
#define SIGMA_X     260.0
#define DELTA_T		0.02

static void state_update_extended(int *x, uint8_t *trigger) {
    static int16_t x_estimated = 0;
    static float t = 0.0;
    float alpha_x;
	
	if (*trigger) { 
		t = t + DELTA_T;
	} else {
		t = 0.0;
		x_estimated = 0;
	}

    *trigger = 1;

    alpha_x = ALPHA1_X + ALPHA10_X / (SIGMA_X * t + 1.0);
    x_estimated = x_estimated + alpha_x * (*x - x_estimated);
    *x = (int) x_estimated;
}

/* } */

unsigned char  GetTouch_TC_Async(int *xs, int *ys) {
    static uint8_t trigger = 0;
	TS_STATE *pstate = NULL;

    pstate = IOE_TS_GetState();

   	if (pstate->TouchDetected) {
	    /*Read AD convert result*/
	    *xs = IOE_TS_Read_X();
	    *ys = IOE_TS_Read_Y();
        
		/* State Update Filtering */
        state_update_extended(xs, &trigger);

        if ((*xs > TOUCH_AD_VALUE_MAX)
	        || (*xs < TOUCH_AD_VALUE_MIN)
	        || (*ys > TOUCH_AD_VALUE_MAX)
	        || (*ys < TOUCH_AD_VALUE_MIN)) 
		{
	    	return 0;
		}

	    return 1;
    }

    trigger = 0;

    return 0;
}

unsigned char  GetTouch_TC_Sync(int *xs, int *ys)
{
	TS_STATE *pstate = NULL;
    do {
      pstate = IOE_TS_GetState();
      delay(5);
    } while(!pstate->TouchDetected);

    /*Read AD convert result*/
    /* no filtering */
    *xs = IOE_TS_Read_X();
    *ys = IOE_TS_Read_Y();
    if ((*xs > TOUCH_AD_VALUE_MAX)
        || (*xs < TOUCH_AD_VALUE_MIN)
        || (*ys > TOUCH_AD_VALUE_MAX)
        || (*ys < TOUCH_AD_VALUE_MIN))
    	return 0;
    else
    	return 1;
}


unsigned char  GetTouch_SC_Async(unsigned int *xs, unsigned int *ys)
{
	int tpx, tpy;
	TS_STATE *pstate = NULL;

	if (GetTouch_TC_Async(&tpx, &tpy)) {
	    tpx = tpx * tcs.xScale - tcs.xOffset;
	    tpy = tpy * tcs.yScale - tcs.yOffset;
        *ys = (unsigned int) tpy;
        *xs = (unsigned int) tpx;

        if ((*xs > xScreenSize) || \
            (*xs < 0) || \
            (*ys > yScreenSize) || \
            (*ys < 0)) {
	    	return 0;
        }

	    return 1;
    }

    return 0;
}

unsigned char  GetTouch_SC_Sync(unsigned int *xs, unsigned int *ys)
{
	int tpx, tpy;

	if (GetTouch_TC_Sync(&tpx, &tpy)) {
		*xs = (int)(tpx * tcs.xScale - tcs.xOffset);
		*ys = (int)(tpy * tcs.yScale - tcs.yOffset);
		if ((*xs > xScreenSize) || (*xs < 0)
        || (*ys > yScreenSize) || (*ys < 0))
			return 0;
		else
			return 1;
	} else
		return 0;
}

void InitTouch(float xs, float ys, int16_t xo, int16_t yo)
{
	tcs.xOffset = xo;
	tcs.yOffset = yo;
	tcs.xScale = xs;
	tcs.yScale = ys;
}
