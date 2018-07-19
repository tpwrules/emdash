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

bool rescue_mode = false;

// if this function returns, something went wrong
// if it returns true, enter rescue mode
void boot_app_if_possible(void) {
    // make sure the bootloader itself is valid
    // the header must be, or the bootloader couldn't have started

    // avoid creating null pointer
    const uint32_t* boot_vectors = (const uint32_t*)(4);

    // pull expected crc and image size from the vectors
    uint32_t expected_crc = boot_vectors[4-1];
    uint32_t boot_size = boot_vectors[5-1];
    // calculate CRC based on above data
    // it starts calculating at the 9th header entry
    uint32_t calculated_crc = crc32_calc((const uint8_t*)&boot_vectors[8-1], 
        boot_size-32);
    if (calculated_crc != expected_crc) {
        // if the bootloader is corrupt, we can't do too much...
        while (1); 
    }

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
        // but first make sure rescue mode has had a chance

        // We enter rescue mode when app is valid, bootloader entrance wasn't
        // forced, and rescue mode hasn't already been entered. This gives
        // 250ms to connect before the bootloader reboots and starts the
        // application, in case the application is valid but can't enter the
        // bootloader on its own.

        uint32_t* rescue_key = (uint32_t*)BOOTLOAD_RESCUE_KEY_ADDR;
        // if the rescue key is present, rescue mode has executed
        if (*rescue_key == BOOTLOAD_RESCUE_KEY) {
            // clear rescue key for next reset
            *rescue_key = 0;
            // and boot the application
            boot_app();
        }
        // otherwise, rescue mode hasn't happened
        // so set the flag to enter it
        rescue_mode = true;
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
    if (app_size > 0x7000 || app_size < 48*4)
        return false;
    // calculate CRC based on above data
    // it starts calculating at the 9th header entry
    uint32_t calculated_crc = crc32_calc((const uint8_t*)&app_vectors[8], app_size-32);
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

    // if the bootloader reboots, rescue mode must be finished
    // so set the flag to say it happened
    uint32_t* rescue_key = (uint32_t*)BOOTLOAD_RESCUE_KEY_ADDR;
    *rescue_key = BOOTLOAD_RESCUE_KEY;

    // now reset system
    NVIC_SystemReset();
}