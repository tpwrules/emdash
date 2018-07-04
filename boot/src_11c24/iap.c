#include <stdint.h>
#include <stdbool.h>

#include "chip.h"
#include "protocol.h"

// CPU clock in kilohertz
#define CPU_CLK (48000)

// IAP command and response definitions
#define PREPARE_SECTOR (50)
#define RAM_TO_FLASH (51)
#define ERASE_SECTOR (52)
#define BLANK_CHECK (53)
#define READ_PART_ID (54)
#define READ_BOOTCODEVERSION (55)
#define COMPARE (56)
#define REINVOKE_ISP (57)
#define READ_UID (58)
#define ERASE_PAGE (59) //not supported in LPC11C24

#define CMD_SUCCESS (0) //Command is executed successfully.
#define INVALID_COMMAND (1) //Invalid command.
#define SRC_ADDR_ERROR (2) //Source address is not on a word boundary.
#define DST_ADDR_ERROR (3) //Destination address is not on a correct boundary.
#define SRC_ADDR_NOT_MAPPED (4) //Source address is not mapped in the memory map. Count value is taken in to consideration where applicable.
#define DST_ADDR_NOT_MAPPED (5) //Destination address is not mapped in the memory map. Count value is taken in to consideration where applicable.
#define COUNT_ERROR (6) //Byte count is not multiple of 4 or is not a permitted value.
#define INVALID_SECTOR (7) //Sector number is invalid.
#define SECTOR_NOT_BLANK (8) //Sector is not blank.
#define SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION (9) //Command to prepare sector for write operation was not executed.
#define COMPARE_ERROR (10) //Source and destination data is not same.
#define BUSY 11 

// set up magic to jump into IAP
// location of function
#define IAP_LOCATION (0x1fff1ff1)
// command and result array definitions
static uint32_t command[5];
static uint32_t result[4];

typedef void (*IAP)(uint32_t command[], uint32_t result[]);
IAP iap_func = (IAP)(IAP_LOCATION);

// call IAP with a command and return the status code
static uint32_t iap_call(uint32_t cmd) {
    command[0] = cmd;
    iap_func(command, result);
    return result[0];
}

// erase and blank check the chip
// returns a protocol error or success
uint8_t iap_erase_and_blank_check(void) {
    uint32_t status; // result of command

    // set up command table to hit all the sectors
    command[1] = 1; // first sector to operate on
    command[2] = HW_TOTAL_SECTORS-1; // last sector to operate on
    command[3] = CPU_CLK; // erase routine needs to know CPU clock in kHz

    // prepare the sectors for writing
    status = iap_call(PREPARE_SECTOR);
    if (status != CMD_SUCCESS) {
        // this should succeed, so if it doesn't
        // return a general error
        return RESP_ERROR;
    }

    // now erase them
    status = iap_call(ERASE_SECTOR);
    if (status != CMD_SUCCESS) {
        // this should succeed, so if it doesn't
        // return a general error
        return RESP_ERROR;
    }

    // and check to make sure they're actually erased
    status = iap_call(BLANK_CHECK);
    if (status == SECTOR_NOT_BLANK) {
        // all sectors should be blank, indicate a flash program failure
        return RESP_PROGRAM_FAILURE;
    } else if (status == CMD_SUCCESS) {
        return RESP_SUCCESS;
    } else {
        // something else which shouldn't happen happened
        return RESP_ERROR;
    }
}

// program and verify a specific page
// returns a protocol error or success
uint8_t iap_program_and_verify(uint16_t page_num, uint32_t* data) {
    uint32_t status; // result of command

    // first, prepare the appropriate sector for programming
    uint32_t sector = 1 + (page_num >> 4);
    command[1] = sector;
    command[2] = sector;
    status = iap_call(PREPARE_SECTOR);
    if (status != CMD_SUCCESS) {
        // this should succeed, so if it doesn't
        // return a general error
        return RESP_ERROR;
    }

    // now actually do the programming
    command[1] = 0x1000 + (page_num<<8); // destination flash address
    command[2] = (uint32_t)data; // source ram address
    command[3] = 256; // writing 256 bytes
    command[4] = CPU_CLK; // CPU frequency in kHz
    status = iap_call(RAM_TO_FLASH);
    if (status != CMD_SUCCESS) {
        // this should succeed, so if it doesn't
        // return a general error
        return RESP_ERROR;
    }

    // using the same command we can also compare the flash with
    // what we wanted to put there
    status = iap_call(COMPARE);
    if (status == COMPARE_ERROR) {
        // it should match since we just programmed it
        // indicate flash program failure
        return RESP_PROGRAM_FAILURE;
    } else if (status == CMD_SUCCESS) {
        return RESP_SUCCESS;
    } else {
        // something else which shouldn't happen happened
        return RESP_ERROR;
    }
}