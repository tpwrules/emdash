#ifndef IAP_H
#define IAP_H

// number of accessible pages (not taken by bootloader)
// 7 sectors * 0x1000 bytes per sector / 0x100 bytes per page
#define HW_AVAIL_PAGES (0x7000/0x100)

// convert a page number to an address in memory
// there are 256 bytes per page
// and the first sector is skipped
#define PAGE_TO_ADDRESS(page) (0x1000 + ((page) << 8))

// convert a page number to a sector number
// there are 16 pages per sector
// and the first sector is the bootloader, so it is skipped
#define PAGE_TO_SECTOR(page) (1+((page) >> 4))

// in app programming handlers used by the bootloader

// erase and blank check the chip
// returns a protocol response code
uint8_t iap_erase_and_blank_check(void);

// program and verify a specific page
// returns a protocol response code
uint8_t iap_program_and_verify(uint16_t page_num, uint32_t* data);

#endif