#include "../src/canvar.h"
#include "canvar_defs.h"
volatile canvar_state_t canvar_states[2];

void gear_gear_update(uint32_t val);
void gear_rpm_update(uint32_t val);

const canvar_def_t canvar_defs[2] = {
{gear_gear_update, 281, 7, 1, 0, 0},
{gear_rpm_update, 289, 2, 2, 0, 0},
};

const uint8_t canvar_id_map[9] = {
0,
255,
255,
255,
255,
255,
255,
255,
1,
};
