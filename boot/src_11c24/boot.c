#include <inttypes.h>
#include <stdbool.h>

#include "chip.h"
#include "boot.h"
#include "crc32.h"

// set up CPU and jump to application code
__attribute__ ((naked, noreturn, section(".after_vectors")))
static void boot_app(void) {
    __asm__("ldr r3, =0x1000\n\t" // app vector table is at 0x1000
            "ldr r2, [r3]\n\t" // first word in table
            "mov sp, r2\n\t" // is boot stack pointer
            "ldr r2, [r3, #4]\n\t" // and the second word
            "bx r2"); // is the address of the first instruction
}

void boot_app_if_possible(void) {
    // boot into bootloader if the appropriate memory is poked
    uint32_t* boot_flag = (uint32_t*)(0x10000000);
    if (*boot_flag == 0xb00410ad) {
        *boot_flag = 0; // clear boot flag for next boot
        return; // magic value met, enter bootloader
    }

    // verify application and boot if it's okay

    // application vectors start at the beginning of sector 1
    const uint32_t* app_vectors = (const uint32_t*)(0x1000);
    // sum of first 8 entries should be 0
    uint32_t sum = 0;
    for (int i=0; i<8; i++)
        sum += app_vectors[i];
    if (sum) // it's not, abandon booting
        return;

    // pull expected crc and image size from the vectors
    uint32_t expected_crc = app_vectors[4];
    uint32_t app_size = app_vectors[5];
    // make sure the size is plausible
    if (app_size > (0x7000-(4*8)) || app_size < 40*8)
        return;
    // calculate CRC based on above data
    // it starts at the 9th header entry
    uint32_t calculated_crc = crc32_calc((const uint8_t*)&app_vectors[8], app_size);
    // and boot if it matches what was stored
    if (calculated_crc == expected_crc) {
        boot_app();
    }

    // hm, it doesn't match
    return; // start the bootloader itself
}

// reboot, into application if asked
__attribute__ ((noreturn, section(".after_vectors")))
void reboot(bool into_app) {
    // set up magic boot flag to specific value to change boot type
    uint32_t* boot_flag = (uint32_t*)(0x10000000);
    *boot_flag = into_app ? 0 : 0xb00410ad;
    // and reset system
    NVIC_SystemReset();
}