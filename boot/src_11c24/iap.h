#ifndef IAP_H
#define IAP_H

// in app programming routines used by the bootloader

// erase and blank check the chip
// returns a protocol error or success
uint8_t iap_erase_and_blank_check(void);

// program and verify a specific page
// returns a protocol error or success
uint8_t iap_program_and_verify(uint16_t page_num, uint32_t* data);

#endif