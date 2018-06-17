#ifndef BUTTON_READ_H
#define BUTTON_READ_H

// PIN HARDWARE MAPPINGS
// first param is GPIO port number
// second param is pin on that port
// third param is IOCON pin mux value for the simple setup

#define IOCON_PORT_A (IOCON_FUNC1 | IOCON_MODE_PULLUP | \
    IOCON_DIGMODE_EN | IOCON_HYS_EN)

#define IOCON_PORT_B_C (IOCON_FUNC0 | IOCON_MODE_PULLUP | IOCON_HYS_EN)

#define PIN_A1 0,11, IOCON_PORT_A
#define PIN_A2 1, 0, IOCON_PORT_A
#define PIN_A3 1, 1, IOCON_PORT_A
#define PIN_A4 1, 2, IOCON_PORT_A

#define PIN_B1 2, 8, IOCON_PORT_B_C // clutch
#define PIN_B2 0, 6, IOCON_PORT_B_C // upshift
#define PIN_B3 0, 7, IOCON_PORT_B_C // downshift
#define PIN_B4 0, 8, IOCON_PORT_B_C // radio
#define PIN_B5 0, 9, IOCON_PORT_B_C // launch

#define PIN_C1 2, 1, IOCON_PORT_B_C // dash_mode
#define PIN_C2 0, 3, IOCON_PORT_B_C // lap
#define PIN_C3 1, 8, IOCON_PORT_B_C // autoshift
#define PIN_C4 0, 2, IOCON_PORT_B_C
#define PIN_C5 2, 7, IOCON_PORT_B_C


// expands to an update function called name that just returns
// the inverted state of the given pin, so that 0 = released and 1 = pressed
#define BR_SIMPLE(...) BR_SIMPLE_real(__VA_ARGS__)
#define BR_SIMPLE_real(name, port, pin, iocon) uint8_t name (void) {\
        return !Chip_GPIO_GetPinState(LPC_GPIO, (port), (pin));\
    }

// expands to setting the pin to input and configuring it
// to digital input mode with a pullup and hysteresis
// according to the definitions above
#define BR_SIMPLE_INIT(...) BR_SIMPLE_INIT_real(__VA_ARGS__)
#define BR_SIMPLE_INIT_real(name, port, pin, iocon) do {\
    /* set default pin function, enable pullup,*/ \
    /* and enable hysteresis*/ \
    Chip_IOCON_PinMuxSet(LPC_IOCON,\
        IOCON_PIO ## port ## _ ## pin, \
        (iocon));\
    /* set pin direction to input */ \
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, (port), (pin));\
    } while (0)

void br_init(void);

#endif