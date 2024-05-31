# This file should be included in the first line of the Makefile as: include usr.mk
GNU_ARM_ROOT = $(HOME)/.local/gcc-arm-none-eabi-10.3-2021.10

vpath %.c src ui/src img/src

CFLAGS += -Iinc -Iui/inc -Iimg/inc
APP_SRCS += esp8266_driver.c app.c wapp.c ui.c json_parser.c ipapi_json.c openweather.c\
			wifi_supplicant.c spotify.c network.c\
esp8266_settings.c esp8266_netstat.c esp8266_client.c esp8266_link.c esp8266_server.c\
Widget.c Event.c Touch.c  STMPE811QTR.c\
OW01d.c OW02d.c OW03d.c OW04d.c OW09d.c OW10d.c OW11d.c OW12d.c OW13d.c OW50d.c\
zero.c one.c two.c three.c four.c five.c six.c seven.c eight.c nine.c\
location.c no_location.c \
WiFi_no.c WiFi_settingup.c WiFi_connected.c\
settings_on.c settings_off.c
