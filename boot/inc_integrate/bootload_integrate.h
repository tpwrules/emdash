#ifndef BOOTLOAD_INTEGRATE_H
#define BOOTLOAD_INTEGRATE_H

#include "chip.h"

// this file contains the definitions for the application
// running with this bootloader

// if BOOTLOAD_ENTER_KEY is present at BOOTLOADER_ENTER_KEY_ADDR
// after reset, the bootloader is entered regardless of application
// validity
#define BOOTLOAD_ENTER_KEY (0xb00710ad)
// first address in RAM. not used by ROM bootloader, our bootloader,
// or any application
#define BOOTLOAD_ENTER_KEY_ADDR (0x10000000)

// address which the bootloader receives commands at
// known so that the app can parse a Hello
#define BOOTLOAD_CAN_CMD_ADDR (0x7EF)
// defined here for consistency, shouldn't be used by application
#define BOOTLOAD_CAN_RESP_ADDR (0x7EE)

// Hello command definitions
#define BOOTLOAD_CMD_HELLO (0)
#define BOOTLOAD_CMDLEN_HELLO (7)
#define BOOTLOAD_CMD_HELLO_KEY (0xb00710ad)

static inline void reboot_into_bootloader() {
    // set up enter key so that bootloader entrance is forced
    uint32_t* boot_enter_key = (uint32_t*)(BOOTLOAD_ENTER_KEY_ADDR);
    *boot_enter_key = BOOTLOAD_ENTER_KEY;
    // now reset system
    NVIC_SystemReset();
}

#define BOOTLOAD_SYSTEM_ID_DASHBOARD (1)
#define BOOTLOAD_SYSTEM_ID_WHEELBOARD (2)

#endif