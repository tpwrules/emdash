#ifndef BOOT_MAGIC_H
#define BOOT_MAGIC_H

// this file contains the magic numbers to get into the bootloader

#define BOOT_MAGIC_VAL (0xb00710ad)
#define BOOT_MAGIC_ADDR (0x10000000) // first address in RAM

// if BOOT_MAGIC_VAL is at BOOT_MAGIC_ADDR when the system resets
// the bootloader will be entered

#endif