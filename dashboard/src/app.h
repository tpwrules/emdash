#ifndef APP_H
#define APP_H

#include <stdbool.h>
#include "platform.h"

void app_entry(void);
void app_timer_interrupt(void);

// app mode!

typedef void (*app_mode_t)(bool next);
// pointer to function which represents the current mode
// if this function is called with next = false
// then set up the screen for the mode
// else, set app_mode_change_func to the function for the next mode
extern app_mode_t app_mode_change_func;
// mode button being pressed calls this function
void app_show_next_mode(void);

void app_blank_mode(bool next);

// this applies hysteresis to a value
// if abs(old - new) > max_delta, new is returned
// else, old is returned
uint32_t hysteresis(uint32_t old, uint32_t new, uint32_t max_delta);

#endif