#ifndef APP_H
#define APP_H

#include "platform.h"

void app_entry(void);
void app_timer_interrupt(void);
void app_can_interrupt(uint32_t msgid, uint8_t dlc, uint8_t *data);

#endif