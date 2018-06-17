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

void br_init(void) {
    // SET PIN I/O STATE HERE

    BR_SIMPLE_INIT(br_clutch, PIN_B1);
    BR_SIMPLE_INIT(br_upshift, PIN_B2);
    BR_SIMPLE_INIT(br_downshift, PIN_B3);
    BR_SIMPLE_INIT(br_radio, PIN_B4);
    BR_SIMPLE_INIT(br_launch, PIN_B5);

    BR_SIMPLE_INIT(br_dash_mode, PIN_C1);
    BR_SIMPLE_INIT(br_lap, PIN_C2);
    BR_SIMPLE_INIT(br_autoshift, PIN_C3);
}