#include "../src_11c24/button_processor.h"
#include "button_defs.h"

msg_state_t msg_states[BP_NUM_CAN_MESSAGES] = {
    {{0x131, 0, {0,0,0,0,0,0,0,0}, 8, 2}, 0},
    {{0x132, 0, {0,0,0,0,0,0,0,0}, 8, 3}, 0},
};

uint8_t br_dash_mode(void);
uint8_t br_clutch(void);
uint8_t br_upshift(void);
uint8_t br_downshift(void);
uint8_t br_radio(void);
uint8_t br_autoshift(void);
uint8_t br_launch(void);
uint8_t br_lap(void);
uint8_t br_traction_knob(void);

const button_def_t button_defs[BP_NUM_BUTTONS] = {
    {br_dash_mode, 0, 3, 10, 50},
    {br_clutch, 0, 0, 10, 50},
    {br_upshift, 0, 1, 10, 50},
    {br_downshift, 0, 2, 10, 50},
    {br_radio, 0, 4, 10, 50},
    {br_autoshift, 0, 5, 10, 50},
    {br_launch, 0, 7, 10, 50},
    {br_lap, 1, 0, 10, 50},
    {br_traction_knob, 0, 6, 75, 75},
};

button_state_t button_states[BP_NUM_BUTTONS];
