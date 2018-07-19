#ifndef BOOT_H
#define BOOT_H

#include <stdbool.h>

// if BOOTLOAD_RESCUE_KEY is present at BOOTLOAD_RESCUE_KEY_ADDR
// after reset, rescue mode has finished and the application
// is booted (if possible)
#define BOOTLOAD_RESCUE_KEY (0x1235c173)
// fourth address in RAM. not used by ROM bootloader, our bootloader,
// or any application
#define BOOTLOAD_RESCUE_KEY_ADDR (0x10000004)

// called before system init to boot application if that's possible
// (i.e. checksums match, not asked to bootload, etc)
// if it returns, something went wrong
void boot_app_if_possible(void);

// returns true if application in flash is valid
bool boot_check_app_validity(void);

// called to reboot into application or the bootloader again
void reboot(bool into_app);

extern bool rescue_mode;

#endif