#include "../src/canvar.h"
#include "canvar_defs.h"
volatile canvar_state_t canvar_states[8];

void var_tfuel_update(uint32_t val);
void drive_gear_update(uint32_t val);
void drive_rpm_update(uint32_t val);
void var_pfuel_update(uint32_t val);
void var_poil_update(uint32_t val);
void var_tmot_update(uint32_t val);
void var_tmot2_update(uint32_t val);
void var_toil_update(uint32_t val);

const canvar_def_t canvar_defs[8] = {
{var_tfuel_update, 276, 6, 1, 0, 0},
{drive_gear_update, 281, 7, 1, 0, 0},
{drive_rpm_update, 289, 2, 2, 0, 0},
{var_pfuel_update, 289, 4, 1, 0, 0},
{var_poil_update, 289, 5, 1, 0, 0},
{var_tmot_update, 290, 0, 1, 0, 0},
{var_tmot2_update, 290, 1, 1, 0, 0},
{var_toil_update, 290, 2, 1, 0, 0},
};

const uint8_t canvar_id_map[15] = {
0,
0,
0,
0,
0,
1,
0,
0,
0,
0,
0,
0,
0,
2,
5,
};
