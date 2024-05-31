#ifndef ESP8266_LINK_H
#define ESP8266_LINK_H

#include "network.h"

uint16_t LUT_link_pullin(enum ESP8NetManagerState supers);
uint8_t app_http_process(enum ESP8NetManagerState supers, void (*callback)(uint8_t*, char*, void*), void *arg);

#endif
