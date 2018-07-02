#include <inttypes.h>

#include "crc32.h"

__attribute__ ((section(".after_vectors")))
uint32_t crc32_calc(const uint8_t* data, uint32_t len) {
    static uint32_t table[256];

    uint32_t crc;

    // calculate table if necessary
    if (table[1] == 0) {
        for(int i=0; i<256; i++) {
            crc = i;
            for (int j=7; j>=0; j--) {
                uint32_t mask = -(crc & 1);
                crc = (crc >> 1) ^ (0xEDB88320 & mask);
            }
            table[i] = crc;
        }
    }

    // now that we have the table
    // we can calculate the CRC
    crc = 0xFFFFFFFF;
    for(int i=0; i<len; i++) {
        crc = (crc >> 8) ^ table[(crc ^ data[i]) & 0xFF];
    }

    return ~crc;
}