#ifndef CANVAR_DEFS_H
#define CANVAR_DEFS_H

#include <inttypes.h>
#include "../src/canvar.h"

#define CV_ID_APS (0)
#define cv_aps (canvar_states[0])
#define CV_ID_WB_VERSION_COMMIT (1)
#define cv_wb_version_commit (canvar_states[1])
#define CV_ID_WB_VERSION_BUILD (2)
#define cv_wb_version_build (canvar_states[2])
#define CV_ID_WB_UPSHIFT (3)
#define cv_wb_upshift (canvar_states[3])
#define CV_ID_WB_DOWNSHIFT (4)
#define cv_wb_downshift (canvar_states[4])
#define CV_ID_WB_DASH_MODE (5)
#define cv_wb_dash_mode (canvar_states[5])
#define CV_ID_WB_RADIO (6)
#define cv_wb_radio (canvar_states[6])
#define CV_ID_WB_TRACTION_KNOB (7)
#define cv_wb_traction_knob (canvar_states[7])
#define CV_ID_PCLUTCH (8)
#define cv_pclutch (canvar_states[8])
#define CV_ID_B_AUTOSHIFTEN_EMS (9)
#define cv_B_autoshiften_ems (canvar_states[9])
#define CV_ID_B_LAUNCH (10)
#define cv_B_launch (canvar_states[10])
#define CV_ID_SPEED (11)
#define cv_speed (canvar_states[11])
#define CV_ID_NMOT (12)
#define cv_nmot (canvar_states[12])
#define CV_ID_ATH (13)
#define cv_ath (canvar_states[13])
#define CV_ID_GEAR (14)
#define cv_gear (canvar_states[14])
#define CV_ID_UB (15)
#define cv_ub (canvar_states[15])
#define CV_ID_TMOT (16)
#define cv_tmot (canvar_states[16])
#define CV_ID_TFUEL (17)
#define cv_tfuel (canvar_states[17])
#define CV_ID_POIL (18)
#define cv_poil (canvar_states[18])
#define CV_ID_TOIL (19)
#define cv_toil (canvar_states[19])
#define CV_ID_PFUEL (20)
#define cv_pfuel (canvar_states[20])
#define CV_ID_TMOT2 (21)
#define cv_tmot2 (canvar_states[21])
#define CV_ID_NOBUS_CAN_STATUS (22)
#define cv_nobus_can_status (canvar_states[22])
#define CV_ID_NOBUS_CPU_IDLE_PERCENT (23)
#define cv_nobus_cpu_idle_percent (canvar_states[23])

extern volatile canvar_state_t canvar_states[24];
extern const canvar_def_t canvar_defs[24];

#define CANVAR_NUM_VARS (24)
#define CANVAR_ID_MAP_COUNT (18)
extern const uint8_t canvar_id_map[18];

#endif
