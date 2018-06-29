#include "../src/canvar.h"
#include "canvar_defs.h"
volatile canvar_state_t canvar_states[23];

void modes_m1_aps_update(uint32_t val);
void version_wb_commit_update(uint32_t val);
void version_wb_build_update(uint32_t val);
void drive_wb_upshift_update(uint32_t val);
void drive_wb_downshift_update(uint32_t val);
void app_wb_dash_mode_update(uint32_t val);
void drive_wb_radio_update(uint32_t val);
void drive_wb_traction_knob_update(uint32_t val);
void modes_m1_pclutch_update(uint32_t val);
void drive_B_autoshiften_ems_update(uint32_t val);
void drive_B_launch_update(uint32_t val);
void drive_speed_update(uint32_t val);
void drive_rpm_update(uint32_t val);
void modes_m1_ath_update(uint32_t val);
void drive_gear_update(uint32_t val);
void warn_ub_update(uint32_t val);
void warn_tmot_update(uint32_t val);
void warn_tfuel_update(uint32_t val);
void warn_poil_update(uint32_t val);
void warn_toil_update(uint32_t val);
void warn_pfuel_update(uint32_t val);
void warn_tmot2_update(uint32_t val);
void cv_can_status_update(uint32_t val);

const canvar_def_t canvar_defs[23] = {
{modes_m1_aps_update, 274, 0, 16, 0, 255},
{version_wb_commit_update, 304, 0, 32, 0, 255},
{version_wb_build_update, 304, 32, 32, 0, 255},
{drive_wb_upshift_update, 305, 8, 8, 0, 255},
{drive_wb_downshift_update, 305, 16, 8, 0, 255},
{app_wb_dash_mode_update, 305, 24, 8, 0, 255},
{drive_wb_radio_update, 305, 32, 8, 0, 255},
{drive_wb_traction_knob_update, 305, 48, 8, 0, 255},
{modes_m1_pclutch_update, 1280, 32, 16, 0, 255},
{drive_B_autoshiften_ems_update, 1872, 24, 8, 0, 255},
{drive_B_launch_update, 1872, 32, 8, 0, 255},
{drive_speed_update, 1907, 0, 16, 0, 255},
{drive_rpm_update, 1907, 16, 16, 0, 255},
{modes_m1_ath_update, 1907, 32, 16, 0, 255},
{drive_gear_update, 1911, 0, 8, 0, 255},
{warn_ub_update, 1913, 0, 16, 0, 255},
{warn_tmot_update, 1914, 32, 8, 0, 5},
{warn_tfuel_update, 1914, 32, 8, 0, 4},
{warn_poil_update, 1914, 40, 8, 0, 1},
{warn_toil_update, 1914, 40, 8, 0, 4},
{warn_pfuel_update, 1914, 56, 8, 0, 1},
{warn_tmot2_update, 1914, 56, 8, 0, 2},
{cv_can_status_update, 65535, 0, 32, 0, 255},
};

const uint8_t canvar_id_map[18] = {
9,
11,
8,
14,
0,
15,
16,
255,
255,
255,
255,
255,
255,
255,
255,
255,
1,
3,
};
