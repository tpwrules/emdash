#ifndef CRC_32_H
#define CRC_32_H

// implementation of CRC32
// taken from http://www.hackersdelight.org/hdcodetxt/crc.c.txt

#include <inttypes.h>

uint32_t crc32_calc(const uint8_t* data, uint32_t len);

#endif