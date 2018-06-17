// functions that actually read the button states for the button processor

/*
PIN HARDWARE MAPPINGS
A1: PIO0_11, AD0
A2: PIO1_0, AD1
A3: PIO1_1, AD2
A4: PIO1_2, AD3

B1: PIO2_8
B2: PIO0_6
B3: PIO0_7
B4: PIO0_8
B5: PIO0_9

C1: PIO2_1 -> dash_mode
C2: PIO0_3
C3: PIO1_8
C4: PIO0_2

software pullup must be enabled
huysteresis is suggested

*/

#include <inttypes.h>

#include "button_read.h"
#include "chip.h"

static inline void br_dash_mode_init(void) {
    // set default pin function, enable pullup,
    // and enable hysteresis 
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO2_1,
        IOCON_FUNC0 | IOCON_MODE_PULLUP | IOCON_HYS_EN);
    // set pin direction to input
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, 2, 1);
}

uint8_t br_dash_mode(void) {
    return !Chip_GPIO_GetPinState(LPC_GPIO, 2, 1);
}

void br_init(void) {
    // SET PIN I/O STATE HERE

    br_dash_mode_init();
}