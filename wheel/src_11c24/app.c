#include <inttypes.h>
#include <stdbool.h>

#include "app.h"
#include "chip.h"
#include "../src_gen/build_version_msg.h"

void app_timer_interrupt() {
    // happens every ms

    LPC_CCAN_API->can_transmit(&build_version_msg);
}

void app_entry() {
    // turn on interrupts and let everything happen
    __enable_irq();
    while (1) {
        // sleep until interrupt to reduce power consumption
        __WFI();
    }
}