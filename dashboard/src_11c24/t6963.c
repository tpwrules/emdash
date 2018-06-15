// this file drives a t6963 compatible LCD

#include <stdbool.h>

#include "chip.h"

#include "t6963.h"

#include <stdbool.h>

#define set_nWR(to) Chip_GPIO_WritePortBit(LPC_GPIO, 2, 6, to)
#define set_nRD(to) Chip_GPIO_WritePortBit(LPC_GPIO, 2, 0, to)
#define set_CD(to) Chip_GPIO_WritePortBit(LPC_GPIO, 2, 1, to)
#define set_nRESET(to) Chip_GPIO_WritePortBit(LPC_GPIO, 1, 8, to)

#define set_DB(to) do { LPC_GPIO[0].DATA[0x3CC] = to << 2; \
    LPC_GPIO[2].DATA[0x180] = to << 5;} while(0)
#define set_DB_output(to) do {\
    if (to) {LPC_GPIO[0].DIR |= 0x3CC; LPC_GPIO[2].DIR |= 0x180;} \
    else {LPC_GPIO[0].DIR &= ~(0x3CC); LPC_GPIO[2].DIR &= ~(0x180);}} while(0)

#define get_DB() ((LPC_GPIO[0].DATA[0x3CC]>>2) | (LPC_GPIO[2].DATA[0x180]>>5))

#define busywait(t) do {\
    volatile int i;\
    for (i=0; i<t; i++);} while(0)

// read the S0 and S1 status bits to determine if the
// display is ready
static inline void lcd_wait_S0S1(void) {
    set_CD(true); // command
    set_DB_output(false); // get ready to read status
    uint8_t status;
    do {
        // assert read
        set_nRD(false);
        busywait(2); // wait for access time
        // save data bits 0 and 1
        status = LPC_GPIO[0].DATA[0xC];
        // and deassert
        set_nRD(true);
        busywait(2);
    } while (status != 0xC);
}

void lcd_send(uint8_t data, bool command) {
    lcd_wait_S0S1(); // wait for display to be ready
    set_CD(command); // send as command or data depending on input
    set_DB_output(true); // output the new data
    set_DB(data);
    // and write it
    set_nWR(false);
    busywait(2);
    set_nWR(true);
    busywait(2);
}

uint8_t lcd_get() {
    lcd_wait_S0S1(); // wait for display to be ready
    set_CD(false); // it's always gonna be data
    set_DB_output(false); // receive data on bus
    // and do the read
    set_nRD(false);
    busywait(2);
    uint8_t data = get_DB();
    set_nRD(true);
    busywait(2);
    return data;
}

// read the S3 status bit to determine if the
// display is ready
static inline void lcd_wait_S3(void) {
    set_CD(true); // command
    set_DB_output(false); // get ready to read status
    uint8_t status;
    do {
        // assert read
        set_nRD(false);
        busywait(2); // wait for access time
        // save data bit 3
        status = Chip_GPIO_GetPinState(LPC_GPIO, 2, 8);
        // and deassert
        set_nRD(true);
        busywait(2);
    } while (!status);
}

void lcd_send_auto(uint8_t data, bool command) {
    lcd_wait_S3(); // wait for display to be ready
    set_CD(command); // send as command or data depending on input
    set_DB_output(true); // output the new data
    set_DB(data);
    // and write it
    set_nWR(false);
    busywait(2);
    set_nWR(true);
    busywait(2);
}

void lcd_init(void) {
    // start by initializing the pins

    // /WR
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO2_6,
        IOCON_FUNC0 | IOCON_MODE_INACT);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, 2, 6);
    set_nWR(true);

    // /RD
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO2_0,
        IOCON_FUNC0 | IOCON_MODE_INACT);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, 2, 0);
    set_nRD(true);

    // C/D
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO2_1,
        IOCON_FUNC0 | IOCON_MODE_INACT);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, 2, 1);
    set_CD(true);

    // /RESET
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_8,
        IOCON_FUNC0 | IOCON_MODE_INACT);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 8);
    set_nRESET(true);

    // DB0-DB7
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_2,
        IOCON_FUNC0 | IOCON_MODE_INACT);
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_3,
        IOCON_FUNC0 | IOCON_MODE_INACT);
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO2_7,
        IOCON_FUNC0 | IOCON_MODE_INACT);
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO2_8,
        IOCON_FUNC0 | IOCON_MODE_INACT);
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_6,
        IOCON_FUNC0 | IOCON_MODE_INACT);
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_7,
        IOCON_FUNC0 | IOCON_MODE_INACT);
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_8,
        IOCON_FUNC0 | IOCON_MODE_INACT);
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_9,
        IOCON_FUNC0 | IOCON_MODE_INACT);

    // now we can begin actually initializing the chip

    // assert reset
    set_nRESET(false);
    // wait for it to happen
    busywait(1000);
    // deassert RESET
    set_nRESET(true);
    // wait some more
    busywait(1000);

    // okay now that that is over
    // we can do something with the rest of the screen

    // set text window
    // this address defines the width of each line in bytes
    lcd_send_acmd(0x41, 64);
    // and same for graphics
    lcd_send_acmd(0x43, 64);
    // set text to be XORed with graphics
    // and enable external CG RAM
    lcd_send_0cmd(0x89);
    // turn on text and graphics and turn off cursor
    lcd_send_0cmd(0x9C);
    // set CG RAM to start at 0x7800, the end of RAM
    lcd_send_acmd(0x22, 0x7800>>11);
}
