#ifndef BUTTON_PROCESSOR_H
#define BUTTON_PROCESSOR_H

#include <inttypes.h>

#include "chip.h"

// callback used to read a button
// should return the current state of the button quickly
// called every ms
typedef uint8_t (*button_update_t)(void);

// used to hold the state of a particular CAN message
typedef struct {
    CCAN_MSG_OBJ_T msg;
    uint8_t send_timeout; // message is sent once this timer reaches 0
} msg_state_t;

// used to hold the state of a particular button
typedef struct {
    uint8_t state; // current accepted state
    uint8_t last_raw; // last state
    uint8_t raw; // current state
    uint8_t debounce; // debounce acceptance timer
} button_state_t;

// defines a button in ROM
typedef struct {
    button_update_t update_func;
    uint8_t msg_idx;
    uint8_t msg_byte;
    uint8_t debounce_press;
    uint8_t debounce_release;
} button_def_t;

// do the magic
void bp_process(void);

#endif