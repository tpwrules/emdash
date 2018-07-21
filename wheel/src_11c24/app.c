#include <inttypes.h>
#include <stdbool.h>

#include "app.h"
#include "button_read.h"
#include "chip.h"
#include "button_processor.h"
#include "../src_gen/button_defs.h"
#include "can_hw.h"

#define DEFINE_BUILD_VERSION_MSG
#include "../src_gen/build_version_msg.h"

void app_timer_interrupt() {
    // happens every ms

    // debounce all the buttons and build all the messages
    bp_process();

    // make sure we're not in busoff
    if (can_busoff_happened) {
        // oops, we are for some reason
        // but we're about to fix that
        can_busoff_happened = false;
        // reinitialize the CAN bus
        can_hw_init();
    }

    // send messages out, if necessary
    // starting with the version message
    static int version_timer = 1;
    if (--version_timer == 0) {
        LPC_CCAN_API->can_transmit((CCAN_MSG_OBJ_T*)&build_version_msg);
        version_timer = 1000; // ms
    }

    // transmit updated button states
    msg_state_t *st = &msg_states[0];
    for (int i=0; i<BP_NUM_CAN_MESSAGES; i++) {
        if (st->send_timeout == 0) {
            // it is time: transmit message
            LPC_CCAN_API->can_transmit(&st->msg);
            // transmit again even if there is no change
            st->send_timeout = 50; // ms
        } else {
            --st->send_timeout;
        }

        st++;
    }
}

void app_entry() {
    // initialize CAN hardware
    can_hw_init();

    // initialize button readers
    br_init();

    // turn on interrupts and let everything happen
    __enable_irq();
    while (1) {
        // sleep until interrupt to reduce power consumption
        __WFI();
    }
}