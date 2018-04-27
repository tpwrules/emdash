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

#define busywait(t) do {\
    volatile int i;\
    for (i=0; i<t; i++);} while(0)

// read the S0 and S1 status bits to determine if the
// display is ready
static void wait_S0S1(void) {
    set_CD(true); // command
    set_DB_output(false); // get ready to read status
    set_nRD(false); // assert read
    uint8_t status;
    do { 
        busywait(1);
        status = get_DB();
    } while ((status & 3) != 3);
    set_nRD(true); // deassert read
}

static void send_data(uint8_t data) {
    wait_S0S1(); // wait for display to be ready
    set_CD(false); // data
    set_DB_output(true); // output the new data
    set_DB(data);
    // and write it
    set_nWR(false);
    busywait(1);
    set_nWR(true);
}

static void send_command(uint8_t data) {
    wait_S0S1(); // wait for display to be ready
    set_CD(true); // command
    set_DB_output(true); // put it on the bus
    set_DB(data);
    // and write it
    set_nWR(false);
    busywait(1);
    set_nWR(true);
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

// command that takes an address
static inline void send_acmd(uint8_t cmd, uint16_t addr) {
    send_data(addr & 0xFF);
    send_data(addr >> 8);
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

    // now we can begin actually initializing the chip
    set_nCE(true);
    set_nRESET(true);
    // assert reset
    set_nRESET(false);
    // wait for it to happen
    busywait(1000);
    // deassert RESET
    set_nRESET(true);
    // wait some more
    busywait(1000);

    set_nCE(false); // left asserted forever
    busywait(100);
    // okay now that that is over
    // we can do something with the rest of the screen

    // set text window
    // this address defines the width of each line in bytes
    send_acmd(0x41, 64);
    // and same for graphics
    send_acmd(0x43, 32);
    // set text to be XORed with graphics
    // and enable internal CG ROM
    send_0cmd(0x80);
    // turn on text and graphics and turn off cursor
    send_0cmd(0x9C);

    // LITTLE DEMO
    // set text and graphics data position
    send_acmd(0x40, 0);
    send_acmd(0x42, 0x800);
    // clear some display memory
    send_acmd(0x24, 0);

    for (int j = 0; j<5000; j++)
        send_1cmd(0xC0, 0);

    send_acmd(0x24, 0);

    const char *hi = "Hello, world!ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (int j = 0; j<65; j++)
        send_1cmd(0xC0, hi[j]-0x20);

    wait_S0S1();
    // do nothing for now
    while(1);
}
