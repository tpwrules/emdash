#ifndef BUTTON_DEFS_H
#define BUTTON_DEFS_H

#include <inttypes.h>
#include "../src_11c24/button_processor.h"

#define WHEEL_VERSION_MESSAGE_ID (0x130)

#define BP_NUM_BUTTONS (8)
#define BP_NUM_CAN_MESSAGES (2)

#define BTN_ID_WB_DASH_MODE (0)
#define btn_wb_dash_mode (button_states[0])
#define BTN_ID_WB_CLUTCH (1)
#define btn_wb_clutch (button_states[1])
#define BTN_ID_WB_UPSHIFT (2)
#define btn_wb_upshift (button_states[2])
#define BTN_ID_WB_DOWNSHIFT (3)
#define btn_wb_downshift (button_states[3])
#define BTN_ID_WB_RADIO (4)
#define btn_wb_radio (button_states[4])
#define BTN_ID_WB_AUTOSHIFT (5)
#define btn_wb_autoshift (button_states[5])
#define BTN_ID_WB_LAUNCH (6)
#define btn_wb_launch (button_states[6])
#define BTN_ID_WB_LAP (7)
#define btn_wb_lap (button_states[7])

extern msg_state_t msg_states[BP_NUM_CAN_MESSAGES];
extern button_state_t button_states[BP_NUM_BUTTONS];
extern const button_def_t button_defs[BP_NUM_BUTTONS];

#endif
