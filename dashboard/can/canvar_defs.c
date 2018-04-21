#include "../src/canvar.h"
#include "canvar_defs.h"
volatile canvar_state_t canvar_states[14];

void drive_B_autoshiften_ems_update(uint32_t val);
void warn_tfuel_update(uint32_t val);
void drive_B_launch_update(uint32_t val);
void drive_gear_update(uint32_t val);
void drive_rpm_update(uint32_t val);
void warn_pfuel_update(uint32_t val);
void warn_poil_update(uint32_t val);
void drive_speed_update(uint32_t val);
void warn_tmot_update(uint32_t val);
void warn_tmot2_update(uint32_t val);
void warn_toil_update(uint32_t val);
void warn_ub_update(uint32_t val);
void version_wb_commit_update(uint32_t val);
void version_wb_build_update(uint32_t val);

const canvar_def_t canvar_defs[14] = {
{drive_B_autoshiften_ems_update, 257, 2, 1, 0, 0},
{warn_tfuel_update, 276, 6, 1, 0, 0},
{drive_B_launch_update, 281, 2, 1, 0, 0},
{drive_gear_update, 281, 7, 1, 0, 0},
{drive_rpm_update, 289, 2, 2, 0, 0},
{warn_pfuel_update, 289, 4, 1, 0, 0},
{warn_poil_update, 289, 5, 1, 0, 0},
{drive_speed_update, 289, 6, 2, 0, 0},
{warn_tmot_update, 290, 0, 1, 0, 0},
{warn_tmot2_update, 290, 1, 1, 0, 0},
{warn_toil_update, 290, 2, 1, 0, 0},
{warn_ub_update, 290, 3, 2, 0, 0},
{version_wb_commit_update, 304, 0, 4, 0, 0},
{version_wb_build_update, 304, 4, 4, 0, 0},
};

const uint8_t canvar_id_map[48] = {
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
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
2,
0,
0,
0,
0,
0,
0,
0,
4,
8,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
12,
};
