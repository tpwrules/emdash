#ifndef APP_H
#define APP_H

#include "platform.h"

void app_entry(void);
void app_timer_interrupt(void);

// app mode!

typedef void (*app_mode_t)(void);
// pointer to function to execute when mode button 
// is pressed
extern app_mode_t app_next_mode_func;
// mode button being pressed calls this function, which
// does stuff then calls the above pointer
void app_show_next_mode(void);

void app_blank_mode(void);

#endif