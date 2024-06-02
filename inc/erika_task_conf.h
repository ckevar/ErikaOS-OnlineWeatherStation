#ifndef TASK_TIMES_H
#define TASK_TIMES_H

#define WEATHER_UPDATE_PERIOD	600000
#define WEATHER_UPDATE_OFFSET	WEATHER_UPDATE_PERIOD

#define LCD_IN_PERIOD			20
#define LCD_IN_OFFSET			1

#define ESP8266_POLL_PERIOD		40
#define ESP8266_POLL_OFFSET		1

#define NETWORK_PERIOD			80
#define NETWORK_OFFSET			15

#define SPOTIFY_UPDATE_PERIOD	20000
#define SPOTIFY_UPDATE_OFFSET	SPOTIFY_UPDATE_PERIOD

#define EXEC(task)				\
	SetRelAlarm(task##_ALARM, task##_OFFSET, task##_PERIOD);

#endif
