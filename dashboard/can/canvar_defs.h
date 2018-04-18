#ifndef CANVAR_DEFS_H
#define CANVAR_DEFS_H

#include <inttypes.h>
#include "../src/canvar.h"

#define cv_tfuel (canvar_states[0])
#define cv_gear (canvar_states[1])
#define cv_nmot (canvar_states[2])
#define cv_pfuel (canvar_states[3])
#define cv_poil (canvar_states[4])
#define cv_speed (canvar_states[5])
#define cv_tmot (canvar_states[6])
#define cv_tmot2 (canvar_states[7])
#define cv_toil (canvar_states[8])

extern volatile canvar_state_t canvar_states[9];
extern const canvar_def_t canvar_defs[9];

#define CANVAR_NUM_VARS (9)
#define CANVAR_ID_MAP_FIRST (276)
#define CANVAR_ID_MAP_COUNT (15)
extern const uint8_t canvar_id_map[15];

#endif
