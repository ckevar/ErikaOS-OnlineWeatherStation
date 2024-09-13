CC=gcc
CFLAGS= -lcunit -Wall -I../inc
BINS=LUT_Test ESP8266_Driver_Test

all: $(BINS)

LUT_Test: LUT_test/LUT_test.c LUT_test/esp8266_client.c LUT_test/esp8266_settings.c LUT_test/esp8266_netstat.c LUT_test/esp8266_server.c
	$(CC) -o $@ $^ $(CFLAGS)

ESP8266_Driver_Test: ESP8266_driver_test/esp8266_driver_test.c ESP8266_driver_test/HTTP_tests.c ESP8266_driver_test/esp8266_driver_poll.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm LUT_Test ESP8266_Driver_Test
