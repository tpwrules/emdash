#include "../src_11c24/button_processor.h"
#include "button_defs.h"

msg_state_t msg_states[BP_NUM_CAN_MESSAGES] = {
    {{0x131, 0, {0,0,0,0,0,0,0,0}, 8, 2}, 0},
};

uint8_t br_dash_mode(void);

const button_def_t button_defs[BP_NUM_BUTTONS] = {
    {br_dash_mode, 0, 3, 10, 50},
};

button_state_t button_states[BP_NUM_BUTTONS];
