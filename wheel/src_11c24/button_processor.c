// read buttons, debounce them, and build messages

#include <inttypes.h>

#include "button_processor.h"
#include "../src_gen/button_defs.h"

void bp_process(void) {
    button_state_t *st = &button_states[0];
    const button_def_t *def = &button_defs[0];

    // loop over all the buttons
    for (int i=0; i<BP_NUM_BUTTONS; i++) {
        // step 1: read this button
        st->last_raw = st->raw;
        st->raw = def->update_func();

        // step 2: debounce it, if necessary
        if (st->state == st->raw || st->last_raw != st->raw) {
            // either the current state matches the raw state
            // and we should reset the debounce timer cause there's
            // nothing to debounce,
            // or the raw state does not match the previous raw state
            // and we should reset the debounce timer cause the
            // raw state bounced
            if (st->raw)
                st->debounce = def->debounce_press;
            else
                st->debounce = def->debounce_release;
        } else {
            // decrement the timer and update button state if now zero
            if (--st->debounce == 0) {
                st->state = st->raw;
                // update message with new value
                msg_states[def->msg_idx].msg.data[def->msg_byte] = st->state;
                // zero timeout so message is sent asap
                msg_states[def->msg_idx].send_timeout = 0;
            }
        }

        st++;
        def++;
    }
}