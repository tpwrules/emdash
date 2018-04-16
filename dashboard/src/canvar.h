#ifndef CANVAR_H
#define CANVAR_H

#include <inttypes.h>

// canvar system definitions
typedef void (*canvar_callback_t)();

#define CV_ST_SAME (2) // value is not new
#define CV_ST_NEW (1) // value is new since the last read
#define CV_ST_INVALID (0) // value is not yet valid

typedef struct {
    // current value of the variable
    // this may secretly be a signed value, but it will be
    // sign-extended if canvar_def_t.is_signed is set
    uint32_t val;
    // state of the value, see above
    uint8_t st;
} canvar_state_t;

// structure kept in ROM detailing the variable information
typedef struct {
    canvar_callback_t callback;
    uint16_t msg_id;
    uint8_t start;
    uint8_t size;
    uint8_t is_signed;
    uint8_t call_every_time;
} canvar_def_t;

// the canvar engine handles the CAN interrupt
void app_can_interrupt(uint32_t msgid, uint8_t dlc, uint8_t *data);

#include "../can/canvar_defs.h"

#endif