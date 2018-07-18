#include <inttypes.h>
#include <stdbool.h>

#include "app.h"
#include "button_read.h"
#include "chip.h"
#include "button_processor.h"
#include "../src_gen/button_defs.h"

#define DEFINE_BUILD_VERSION_MSG
#include "../src_gen/build_version_msg.h"

void app_timer_interrupt() {
    // happens every ms

    // debounce all the buttons and build all the messages
    bp_process();

    // send messages out, if necessary
    // starting with the version message
    static int version_timer = 1;
    if (--version_timer == 0) {
        LPC_CCAN_API->can_transmit((CCAN_MSG_OBJ_T*)&build_version_msg);
        version_timer = 1000; // ms
    }

    // and also all of the others
    msg_state_t *st = &msg_states[0];
    for (int i=0; i<BP_NUM_CAN_MESSAGES; i++) {
        if (st->send_timeout == 0) {
            // transmit the message if it is time
            LPC_CCAN_API->can_transmit(&st->msg);
            st->send_timeout = 50;
        } else {
            --st->send_timeout;
        }

        st++;
    }
}

void app_entry() {
    // initialize button readers
    br_init();

    // turn on interrupts and let everything happen
    __enable_irq();
    while (1) {
        // sleep until interrupt to reduce power consumption
        __WFI();
    }
}