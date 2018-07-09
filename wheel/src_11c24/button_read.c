// functions that actually read the button states for the button processor

// the simple reader covers the following case:
//  * button is normally open
//  * button is connected between an input and ground
// in such a case, put a BR_SIMPLE_INIT(<name>, PIN_<pin>)
// in the init function and a BR_SIMPLE(<name>, PIN_<pin>)
// above it. just make your button's update function the same
// name as above and it will be 1 when pressed and 0 when not pressed

#include <inttypes.h>

#include "button_read.h"
#include "chip.h"

BR_SIMPLE(br_clutch, PIN_B1);
BR_SIMPLE(br_upshift, PIN_B2);
BR_SIMPLE(br_downshift, PIN_B3);
BR_SIMPLE(br_radio, PIN_B4);
BR_SIMPLE(br_launch, PIN_B5);

BR_SIMPLE(br_dash_mode, PIN_C1);
BR_SIMPLE(br_lap, PIN_C2);
BR_SIMPLE(br_autoshift, PIN_C3);


static inline void br_traction_knob_init(void) {
    // initialize the IO pin (A1)
    // set it to analog input
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_11,
        IOCON_FUNC2 | IOCON_ADMODE_EN);
    // configure pin as input
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, 0, 11);
}

// traction knob has 12 distinct positions
#define TRACTION_NUM_POS (12)

uint8_t br_traction_knob(void) {
    static uint8_t val = 0;

    // read value from ADC
    // TODO: do it without chip library
    uint16_t now = 0;
    Chip_ADC_EnableChannel(LPC_ADC, ADC_CH0, ENABLE);
    // start conversion
    Chip_ADC_SetStartMode(LPC_ADC, ADC_START_NOW, ADC_TRIGGERMODE_RISING);
    // wait for it to finish
    while (Chip_ADC_ReadStatus(
        LPC_ADC, ADC_CH0, ADC_DR_DONE_STAT) != SET);
    // capture value
    Chip_ADC_ReadValue(LPC_ADC, ADC_CH0, &now);
    Chip_ADC_EnableChannel(LPC_ADC, ADC_CH0, DISABLE);

    // split up current value into 4 numbers per switch position
    uint16_t switch_pos = (now * ((TRACTION_NUM_POS-1)*4)) / 1024;

    // act on that with hysteresis
    switch (switch_pos & 3) {
        case 0: // definitely at current value
            val = switch_pos >> 2;
            break;
        case 1: // should be current value
            // as long as it's not the next higher value
            if (val != (switch_pos >> 2) + 1)
                val = switch_pos >> 2;
            break;
        case 2: // should be next higher value
            // as long as it's not current value
            if (val != switch_pos >> 2)
                val = (switch_pos >> 2) + 1;
            break;
        case 3: // definitely at next higher value
            val = (switch_pos >> 2) + 1;
            break;
    }
    
    // return the switch position with hysteresis
    return val;
}


void br_init(void) {
    // initialize the ADC so it can be used for the A pins
    // TODO: do it without chip library
    ADC_CLOCK_SETUP_T ADCSetup;
    Chip_ADC_Init(LPC_ADC, &ADCSetup);

    // SET PIN I/O STATE HERE

    BR_SIMPLE_INIT(br_clutch, PIN_B1);
    BR_SIMPLE_INIT(br_upshift, PIN_B2);
    BR_SIMPLE_INIT(br_downshift, PIN_B3);
    BR_SIMPLE_INIT(br_radio, PIN_B4);
    BR_SIMPLE_INIT(br_launch, PIN_B5);

    BR_SIMPLE_INIT(br_dash_mode, PIN_C1);
    BR_SIMPLE_INIT(br_lap, PIN_C2);
    BR_SIMPLE_INIT(br_autoshift, PIN_C3);

    br_traction_knob_init();
}