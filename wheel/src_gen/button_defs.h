#ifndef BUTTON_DEFS_H
#define BUTTON_DEFS_H

#include <inttypes.h>
#include "../src_11c24/button_processor.h"

#define WHEEL_VERSION_MESSAGE_ID (0x130)

#define BP_NUM_BUTTONS (1)
#define BP_NUM_CAN_MESSAGES (1)

#define BTN_ID_WB_DASH_MODE (0)
#define btn_wb_dash_mode (button_states[0])

extern msg_state_t msg_states[BP_NUM_CAN_MESSAGES];
extern button_state_t button_states[BP_NUM_BUTTONS];
extern const button_def_t button_defs[BP_NUM_BUTTONS];

#endif
