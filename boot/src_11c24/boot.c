#include <inttypes.h>
#include <stdbool.h>

#include "chip.h"
#include "boot.h"
#include "bootload_integrate.h"
#include "crc32.h"

// set up stack and jump to application code
__attribute__ ((naked, noreturn, section(".after_vectors")))
static void boot_app(void) {
    __asm__("ldr r3, =0x1000\n\t" // app vector table is at 0x1000
            "ldr r2, [r3]\n\t" // first word in table
            "mov sp, r2\n\t" // is boot stack pointer
            "ldr r2, [r3, #4]\n\t" // and the second word
            "bx r2"); // is the address of the first instruction
}

// if this function returns, something went wrong
void boot_app_if_possible(void) {
    // boot into bootloader if the enter key is at the correct address
    uint32_t* boot_enter_key = (uint32_t*)(BOOTLOAD_ENTER_KEY_ADDR);
    if (*boot_enter_key == BOOTLOAD_ENTER_KEY) {
        // clear enter key so that a reboot won't automatically
        // enter the bootloader
        *boot_enter_key = 0;
        return;
    }

    // if the enter key isn't correct, we verify the application
    // and boot it if it checks out
    if (boot_check_app_validity()) {
        // all checks passed!
        // boot into the application
        boot_app();
    }
}

// returns true if application in flash is valid
// currently just checks checksums
bool boot_check_app_validity() {
    // application vectors start at the beginning of sector 1
    const uint32_t* app_vectors = (const uint32_t*)(0x1000);
    // sum of first 8 entries should be 0
    uint32_t sum = 0;
    for (int i=0; i<8; i++)
        sum += app_vectors[i];
    if (sum != 0)
        return false;

    // pull expected crc and image size from the vectors
    uint32_t expected_crc = app_vectors[4];
    uint32_t app_size = app_vectors[5];
    // make sure the size is plausible
    if (app_size > (0x7000-(4*8)) || app_size < 40*8)
        return false;
    // calculate CRC based on above data
    // it starts calculating at the 9th header entry
    uint32_t calculated_crc = crc32_calc((const uint8_t*)&app_vectors[8], app_size);
    if (calculated_crc != expected_crc)
        return false;
    return true;
}

// reboot either into application (if possible) or bootloader
void reboot(bool into_app) {
    // set enter key to enter bootloader if we're not booting into the application
    if (!into_app) {
        uint32_t* boot_enter_key = (uint32_t*)(BOOTLOAD_ENTER_KEY_ADDR);
        *boot_enter_key = BOOTLOAD_ENTER_KEY;
    }
    // and reset system
    NVIC_SystemReset();
}