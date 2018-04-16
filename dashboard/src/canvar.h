// this file contains the type definitions for the canvar system

#ifndef CANVAR_H
#define CANVAR_H

#include <inttypes.h>

typedef void (*canvar_callback_t)();

#define CV_ST_SAME (2) // value is not new
#define CV_ST_NEW (1) // value is new since the last read
#define CV_ST_INVALID (0) // value is not yet valid

typedef struct {
    // current value of the variable
    union {
        uint32_t u;
        int32_t s;
    };
    // state of the value, see above
    uint8_t st;
} canvar_state_t;

// structure kept in ROM detailing the variable information
typedef struct {
    canvar_callback_t callback;
    uint16_t msg_id;
    uint8_t start;
    uint8_t size;
    uint8_t signed;
    uint8_t call_every_time;
} canvar_def_t;

#endif