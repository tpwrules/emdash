#include "platform.h"
#include "canvar.h"
#include "../src_gen/canvar_defs.h"

volatile int canvar_was_updated = 0;

void app_can_interrupt(uint32_t msg_id, uint8_t dlc, const uint8_t *data) {
    // step 1: find the first variable in this message
    int msg_idx = msg_id - CANVAR_ID_MAP_FIRST;
    if (msg_idx < 0 || msg_idx >= CANVAR_ID_MAP_COUNT)
        return; // we def don't have any handlers for it

    int var_idx = canvar_id_map[msg_idx];
    const canvar_def_t *def = &canvar_defs[var_idx];
    volatile canvar_state_t *st = &canvar_states[var_idx];

    // step 2: loop over all the vars with this message ID
    while (def->msg_id == msg_id) {
        // step 3: make sure this can message has this variable
        if (def->multiplex != 0xFF && def->multiplex != data[0]) {
            def++;
            st++;
            continue;
        }
        
        // step 4: extract the value for this variable
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

        // step 5: update canvar state
        if (def->call_every_time ||
                st->val != val || st->st == CV_ST_INVALID) {
            st->val = val;
            st->st = CV_ST_NEW;
            canvar_was_updated = 1;
        }

        // increment to next variable
        def++;
        st++;
    }
}