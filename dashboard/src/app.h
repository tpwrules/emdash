#ifndef APP_H
#define APP_H

#include "platform.h"

void app_entry(void);
void app_timer_interrupt(void);

// canvar callbacks
void gear_rpm_update(void);
void gear_gear_update(void);

#endif