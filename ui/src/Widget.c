/*
 * Widget.c
 *
 *  Created on: 21/ott/2015
 *      Author: admim
 */

#include "Widget.h"
#include "WidgetConfig.h"
#include "Event.h"
#include "debug.h"

unsigned char contains(Widget *w, TPoint *point){
	if	((point->x >= w->xl) && (point->x <= w->xl + w->xw) &&
		 (point->y >= w->yt) && (point->y <= w->yt + w->yh)) {
/*		debuginfo(5, point->x, point->y, 0);
		debuginfo(6, w->xl, w->yt, 0); */
		return 1;
	}
	else
		return 0;
}

unsigned char OnTouch(Widget ws[], TPoint *press){
	unsigned char i;

	for(i = 0; i < NUMWIDGETS; i++) {
		if (ws[i].wt == BUTTONICON) {
			if(contains(&ws[i], press)) {
				SetEvent(biconinfo(&ws[i])->onpress);
                return 1;
 			}
		}
	}
	return 0;
}

unsigned char DrawInit(Widget ws[])
{
	unsigned char i;
	for(i=0; i<NUMWIDGETS; i++) {
		DrawOff(&ws[i]);
	}
	return 1;
}

unsigned char DrawOn(Widget *w)
{
	char *imgptr = 0;

	switch (w->wt) {
	case BUTTONICON:
		imgptr = biconinfo(w)->iconp;
		break;
	case BACKGROUND:
	case IMAGE:
		imgptr = imginfo(w)->image;
		break;
	}
	if (imgptr != 0) {
		LCD_DrawPicture(w->xl, w->yt, w->xw, w->yh, imgptr);
		return 1;
	} else
		return 0;
}

unsigned char DrawOff(Widget *w)
{
	char *imgptr = 0;

	switch (w->wt) {
		case BUTTONICON:
			imgptr = biconinfo(w)->iconr;
			break;
		case BACKGROUND:
		case IMAGE:
			imgptr = imginfo(w)->image;
			break;
	}
	if (imgptr != 0) {
		LCD_DrawPicture(w->xl, w->yt, w->xw, w->yh, imgptr);
		return 1;
	}
		return 0;
}

void LCD_DisplayStringXY(uint16_t xpos, uint16_t ypos, uint8_t *ascii) {
	while(*ascii != 0) {
		LCD_DisplayChar(xpos, ypos, *ascii);
		ypos += 16;
		if(ypos >= LCD_PIXEL_WIDTH)
			break;
		ascii++;
	}
}

unsigned char WPrint(Widget *w, char *s)
{
	if (w->wt == TEXT) {
		LCD_SetTextColor(txtinfo(w)->color);
		LCD_SetFont(txtinfo(w)->font);
		LCD_DisplayStringXY(w->xl, w->yt, s);
		return 1;
	} else
		return 0;
}

static void LCD_DisplayStringXYLog(uint16_t xpos, uint16_t ypos, uint8_t *ascii) {
	while(*ascii != 0) {
		LCD_DisplayChar(xpos, ypos, *ascii);
		ypos += 8;
		if(ypos >= LCD_PIXEL_WIDTH)
			break;
		ascii++;
	}
}

unsigned char WPrintLog(Widget *w, char *s)
{
	if (w->wt == TEXT) {
		LCD_SetTextColor(txtinfo(w)->color);
		LCD_SetFont(txtinfo(w)->font);
		LCD_DisplayStringXYLog(w->xl, w->yt, s);
		return 1;
	} else
		return 0;
}

