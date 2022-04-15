GNU_ARM_ROOT = $(HOME)/Apps/gcc-arm-none-eabi-9-2019-q4-major

vpath %.c src ui/src img/src

CFLAGS += -Iinc -Iui/inc -Iimg/inc
APP_SRCS += esp8266_driver.c app.c ui.c json_parser.c ipapi_json.c openweather.c web_app.c\
Widget.c Event.c Touch.c STMPE811QTR.c\
OW01d.c OW02d.c OW03d.c OW04d.c OW09d.c OW10d.c OW11d.c OW12d.c OW13d.c OW50d.c\
zero.c one.c two.c three.c four.c five.c six.c seven.c eight.c nine.c\
location.c no_location.c \
WiFi_no.c WiFi_settingup.c WiFi_connected.c\
settings_on.c settings_off.c