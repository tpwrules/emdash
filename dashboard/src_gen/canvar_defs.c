#include "../src/canvar.h"
#include "canvar_defs.h"
volatile canvar_state_t canvar_states[21];

void modes_m1_ath_update(uint32_t val);
void drive_B_autoshiften_ems_update(uint32_t val);
void drive_B_launch_update(uint32_t val);
void drive_gear_update(uint32_t val);
void drive_speed_update(uint32_t val);
void version_wb_commit_update(uint32_t val);
void version_wb_build_update(uint32_t val);
void drive_wb_upshift_update(uint32_t val);
void drive_wb_downshift_update(uint32_t val);
void app_wb_dash_mode_update(uint32_t val);
void drive_wb_radio_update(uint32_t val);
void drive_wb_traction_knob_update(uint32_t val);
void modes_m1_pclutch_update(uint32_t val);
void drive_rpm_update(uint32_t val);
void warn_ub_update(uint32_t val);
void warn_tmot_update(uint32_t val);
void warn_tfuel_update(uint32_t val);
void warn_poil_update(uint32_t val);
void warn_toil_update(uint32_t val);
void warn_pfuel_update(uint32_t val);
void warn_tmot2_update(uint32_t val);

const canvar_def_t canvar_defs[21] = {
{modes_m1_ath_update, 257, 0, 2, 0, 0, 255},
{drive_B_autoshiften_ems_update, 257, 2, 1, 0, 0, 255},
{drive_B_launch_update, 281, 2, 1, 0, 0, 255},
{drive_gear_update, 281, 7, 1, 0, 0, 255},
{drive_speed_update, 289, 6, 2, 0, 0, 255},
{version_wb_commit_update, 304, 0, 4, 0, 0, 255},
{version_wb_build_update, 304, 4, 4, 0, 0, 255},
{drive_wb_upshift_update, 305, 1, 1, 0, 0, 255},
{drive_wb_downshift_update, 305, 2, 1, 0, 0, 255},
{app_wb_dash_mode_update, 305, 3, 1, 0, 0, 255},
{drive_wb_radio_update, 305, 4, 1, 0, 0, 255},
{drive_wb_traction_knob_update, 305, 6, 1, 0, 0, 255},
{modes_m1_pclutch_update, 892, 0, 2, 0, 0, 255},
{drive_rpm_update, 1907, 2, 2, 0, 0, 255},
{warn_ub_update, 1913, 0, 2, 0, 0, 255},
{warn_tmot_update, 1914, 4, 1, 0, 0, 5},
{warn_tfuel_update, 1914, 4, 1, 0, 0, 4},
{warn_poil_update, 1914, 5, 1, 0, 0, 1},
{warn_toil_update, 1914, 5, 1, 0, 0, 4},
{warn_pfuel_update, 1914, 7, 1, 0, 0, 1},
{warn_tmot2_update, 1914, 7, 1, 0, 0, 2},
};

const uint8_t canvar_id_map[18] = {
13,
4,
255,
255,
255,
0,
14,
15,
255,
255,
12,
2,
255,
255,
255,
255,
5,
7,
};
