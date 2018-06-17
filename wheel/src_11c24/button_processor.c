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
        if (st->state == st->raw && st->last_raw == st->raw) {
            // state hasn't changed, so clear the debounce timer
            st->debounce = 0;
        } else {
            // it has changed, we need to start counting
            if (st->debounce == 0) {
                // load the timer
                if (st->raw)
                    st->debounce = def->debounce_press;
                else
                    st->debounce = def->debounce_release;
            } else {
                // decrement the timer and update button state if now zero
                if (--st->debounce == 0) {
                    st->state = st->raw;
                    st->last_raw = st->raw;
                    msg_states[def->msg_idx].send_timeout = 0; // message is dirty
                    // update message with new value
                    msg_states[def->msg_idx].msg.data[def->msg_byte] = st->raw;
                }
            }
        }

        st++;
        def++;
    }
}