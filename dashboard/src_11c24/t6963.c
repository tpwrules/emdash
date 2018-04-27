// this file drives a t6963 compatible LCD

#include <stdbool.h>

#include "chip.h"

#include "t6963.h"

#define set_nWR(to) Chip_GPIO_WritePortBit(LPC_GPIO, 2, 8, to)
#define set_nRD(to) Chip_GPIO_WritePortBit(LPC_GPIO, 2, 7, to)
#define set_nCE(to) Chip_GPIO_WritePortBit(LPC_GPIO, 2, 6, to)
#define set_CD(to) Chip_GPIO_WritePortBit(LPC_GPIO, 2, 3, to)
#define set_nRESET(to) Chip_GPIO_WritePortBit(LPC_GPIO, 3, 3, to)
#define set_FS(to) Chip_GPIO_WritePortBit(LPC_GPIO, 1, 10, to)

#define set_DB(to) do { LPC_GPIO[0].DATA[0x3FC] = to << 2; \
    Chip_GPIO_WritePortBit(LPC_GPIO, 1, 8, !!(to & 4)); \
    Chip_GPIO_WritePortBit(LPC_GPIO, 1, 5, !!(to & 8));} while(0)
#define set_DB_output(to) do {\
    if (to) {LPC_GPIO[0].DIR |= 0x3FC;Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 5);Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 8);} \
    else {LPC_GPIO[0].DIR &= ~(0x3FC); Chip_GPIO_SetPinDIRInput(LPC_GPIO, 1, 5);Chip_GPIO_SetPinDIRInput(LPC_GPIO, 1, 8);}} while(0)
#define get_DB() (LPC_GPIO[0].DATA[0x3FC] >> 2)

// read the S0 and S1 status bits to determine if the
// display is ready
static void wait_S0S1(void) {
    set_CD(true);
    set_DB_output(false);
    //set_nCE(false);
    set_nRD(false);
    uint8_t status;
    do {
        volatile int i;
        for (i=0; i<100; i++);
        status = get_DB();
    } while ((status & 3) != 3);
    set_nRD(true);
    set_DB_output(true);
    set_DB(0);
    //set_nCE(true);
}

static void wait_S3(void) {
    set_CD(true);
    set_DB_output(false);
    //set_nCE(false);
    set_nRD(false);
    uint8_t status;
    do {
        volatile int i;
        for (i=0; i<100; i++);
        status = get_DB();
    } while ((status & 8) != 8);
    set_nRD(true);
    set_DB_output(true);
    set_DB(0);
    //set_nCE(true);
}

static void send_data(uint8_t data) {
    wait_S0S1();
    set_CD(false);
    set_DB_output(true);
    set_DB(data);
    //set_nCE(false);
    set_nWR(false);
    volatile int i;
    for (i=0; i<100; i++);
    set_nWR(true);
    //set_nCE(true);
    //set_DB_output(false);
}

static void send_command(uint8_t data) {
    wait_S0S1();
    set_CD(true);
    set_DB_output(true);
    set_DB(data);
    //set_nCE(false);
    set_nWR(false);
    volatile int i;
    for (i=0; i<100; i++);
    set_nWR(true);
    //set_nCE(true);
    //set_DB_output(false);
    wait_S0S1();
    //for(i=0; i<10000; i++);
}

// command with no arguments
static void send_0cmd(uint8_t cmd) {
    send_command(cmd);
}

// command with one argument
static void send_1cmd(uint8_t cmd, uint8_t arg) {
    send_data(arg);
    send_command(cmd);
}

// command with two arguments
static void send_2cmd(uint8_t cmd, uint8_t arg1, uint8_t arg2) {
    send_data(arg1);
    send_data(arg2);
    send_command(cmd);
}

void t6963_init(void) {
    // start by initializing the pins

    // /WR
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO2_8,
        IOCON_FUNC0 | IOCON_MODE_INACT);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, 2, 8);
    set_nWR(true);

    // /RD
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO2_7,
        IOCON_FUNC0 | IOCON_MODE_INACT);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, 2, 7);
    set_nRD(true);

    // /CE
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO2_6,
        IOCON_FUNC0 | IOCON_MODE_INACT);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, 2, 6);
    set_nCE(true);

    // C/D
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO2_3,
        IOCON_FUNC0 | IOCON_MODE_INACT);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, 2, 3);
    set_CD(true);

    // /RESET
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO3_3,
        IOCON_FUNC0 | IOCON_MODE_INACT);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, 3, 3);
    set_nRESET(true);

    // FS
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_10,
        IOCON_FUNC0 | IOCON_MODE_INACT | IOCON_DIGMODE_EN);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 10);
    set_FS(true); // 6x8 fonts

    // DB0-DB7
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_2,
        IOCON_FUNC0 | IOCON_MODE_INACT);
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_3,
        IOCON_FUNC0 | IOCON_MODE_INACT);
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_8,
        IOCON_FUNC0 | IOCON_MODE_INACT);
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_5,
        IOCON_FUNC0 | IOCON_MODE_INACT);
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_6,
        IOCON_FUNC0 | IOCON_MODE_INACT);
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_7,
        IOCON_FUNC0 | IOCON_MODE_INACT);
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_8,
        IOCON_FUNC0 | IOCON_MODE_INACT);
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_9,
        IOCON_FUNC0 | IOCON_MODE_INACT);

    set_DB_output(true);
    set_DB(0xFF);

    // now we can begin actually initializing the chip
    set_nCE(true);
    set_nRESET(true);
    // wait a while
    volatile int i;
    for (i=0; i<1000; i++);
    // assert reset
    set_nRESET(false);
    // wait again
    for (i=0; i<1000; i++);
    // deassert RESET
    set_nRESET(true);
    // wait some more
    for (i=0; i<1000; i++);

    set_nCE(false);
    for (i=0; i<1000; i++);
    // okay now that that is over
    // we can do something with the rest of the screen

    /*
    // set text home address, i.e. start of text
    send_2cmd(0x40, 0, 0);
    // set text area, we want all 32 columns
    send_2cmd(0x41, 30, 0);
    // set internal character generator and text OR mode
    send_0cmd(0x80);
    // set 8 line cursor
    send_0cmd(0xA7);
    // set cursor to 0, 0
    send_2cmd(0x21, 0, 0);
    // set address to 0
    send_2cmd(0x24, 0, 0);
    // write a string
    const char *hi = "Hello, world!";
    for (int j = 0; j<10; j++)
        send_1cmd(0xC0, hi[j]-0x20);
    // turn on display with cursor, blink, and text only
    send_0cmd(0x9C);

    */

    send_2cmd(0x40, 0, 0);
    send_2cmd(0x41, 30, 0);
    send_2cmd(0x42, 0, 8);
    send_2cmd(0x43, 30, 0);
    send_0cmd(0xa7);
    send_0cmd(0x80);
    send_0cmd(0x97);

    send_2cmd(0x24, 0, 0);

    const char *hi = "Hello, world!";
    for (int j = 0; j<13; j++)
        send_1cmd(0xC0, hi[j]-0x20);

    /*

    // invert display
    while (1) {
        //send_0cmd(0x9C);
        send_2cmd(0xD0, 1, 0);
        //send_2cmd(0xD0, 1, 0);
        for (i=0; i<200000; i++);
        send_2cmd(0xD0, 0, 0);
        for (i=0; i<1000000; i++);
    }
    */
    
    wait_S0S1();
    // do nothing for now
    while(1);
}
