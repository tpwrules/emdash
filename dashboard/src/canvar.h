#ifndef CANVAR_H
#define CANVAR_H

#include <inttypes.h>

// canvar system definitions
typedef void (*canvar_callback_t)(uint32_t val);

// force a variable to new as long as it's not invalid
#define CV_RENEW(var) do {\
    if (var.st != CV_ST_INVALID) var.st = CV_ST_NEW;\
    } while (0)

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
    uint8_t multiplex;
} canvar_def_t;

// the canvar engine handles the CAN interrupt
void app_can_interrupt(uint32_t msg_id, uint8_t dlc, const uint8_t *data);
// it can also handle an 'interrupt' which just sets a specific canvar
void app_canvar_interrupt(uint8_t cv_id, uint32_t val);

// variable set to 1 when some canvar was updated to trigger
// the main loop
extern volatile int canvar_was_updated;

#include "../src_gen/canvar_defs.h"

#endif