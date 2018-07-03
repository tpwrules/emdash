// this file manages the dashboard CAN hardware

#include <inttypes.h>
#include <stdbool.h>

#include "bootload.h"
#include "can_hw.h"

#include "chip.h"

// calculate can timing from baudrate
// stolen directly from ccan_rom example
static inline void baudrateCalculate(uint32_t baud_rate, 
    uint32_t *can_api_timing_cfg)
{
    uint32_t pClk, div, quanta, segs, seg1, seg2, clk_per_bit, can_sjw;
    Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_CAN);
    pClk = Chip_Clock_GetMainClockRate();

    clk_per_bit = pClk / baud_rate;

    for (div = 0; div <= 15; div++) {
        for (quanta = 1; quanta <= 32; quanta++) {
            for (segs = 3; segs <= 17; segs++) {
                if (clk_per_bit == (segs * quanta * (div + 1))) {
                    segs -= 3;
                    seg1 = segs / 2;
                    seg2 = segs - seg1;
                    can_sjw = seg1 > 3 ? 3 : seg1;
                    can_api_timing_cfg[0] = div;
                    can_api_timing_cfg[1] =
                        ((quanta - 1) & 0x3F) |
                        (can_sjw & 0x03) << 6 |
                        (seg1 & 0x0F) << 8 |
                        (seg2 & 0x07) << 12;
                    return;
                }
            }
        }
    }
}

// called to get everything started for CAN
void can_hw_init(void) {
    // calculate timing data from baudrate
    uint32_t timing_data[2];
    baudrateCalculate(500000, timing_data);
    // now inititalize the CAN driver with that data
    // (and tell it to not enable interrupts)
    LPC_CCAN_API->init_can(&timing_data[0], false);

    // now configure the CAN callback functions
    static const CCAN_CALLBACKS_T callbacks = {
        // basic can message
        CAN_rx,
        CAN_tx,
        CAN_error,
        // canopen stuff we don't use
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    };
    // tell the driver the above list
    LPC_CCAN_API->config_calb((CCAN_CALLBACKS_T*)&callbacks);
}
