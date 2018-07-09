#ifndef BOOT_H
#define BOOT_H

#include <stdbool.h>

// called before system init to boot application if that's possible
// (i.e. checksums match, not asked to bootload, etc)
// if it returns, something went wrong
void boot_app_if_possible(void);

// called to reboot into application or the bootloader again
void reboot(bool into_app);

#endif