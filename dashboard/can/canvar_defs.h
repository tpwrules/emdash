#ifndef CANVAR_DEFS_H
#define CANVAR_DEFS_H

#include <inttypes.h>
#include "canvar.h"

#define cv_gear (canvar_states[0])
#define cv_nmot (canvar_states[1])

extern canvar_state_t canvar_states[2];
extern const canvar_def_t canvar_defs[2];

#define CANVAR_ID_MAP_FIRST (281)
#define CANVAR_ID_MAP_COUNT (9)
extern const uint8_t canvar_id_map[9];

#endif
