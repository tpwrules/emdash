#include "platform.h"
#include "canvar.h"
#include "../can/canvar_defs.h"

volatile int canvar_was_updated = 0;

void app_can_interrupt(uint32_t msgid, uint8_t dlc, uint8_t *data) {
    // where the magic happens

    // step 1: look up which var def this is
    uint8_t var_def_idx = canvar_id_map[msgid - CANVAR_ID_MAP_FIRST];
    const canvar_def_t *def = &canvar_defs[var_def_idx];

    // step 2: extract the value
    uint32_t val = 0;
    int bi;
    for (bi = 0; bi<def->size; bi++)
        // value is little endian
        val |= data[bi+def->start] << (8*bi);
    // sign extend if required
    if (def->is_signed && def->size < 4) {
        uint32_t sign = (val >> ((8*bi)-1)) ? 0xFFFFFFFF : 0;
        val |= sign << (8*bi);
    }

    // step 3: update the canvar state
    volatile canvar_state_t *st = &canvar_states[var_def_idx];
    if (def->call_every_time ||
            st->val != val || st->st == CV_ST_INVALID) {
        st->val = val;
        st->st = CV_ST_NEW;
        canvar_was_updated = 1;
    }
}