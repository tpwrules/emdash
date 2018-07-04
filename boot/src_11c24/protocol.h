#ifndef PROTOCOL_H
#define PROTOCOL_H

// this file contains definitions of the commands
// and responses used in the bootloading protocol
// plus other stuff

#include "bootload_integrate.h"

// address which the bootloader receives commands at
#define CAN_CMD_ADDR (BOOTLOAD_CAN_CMD_ADDR)

// address which the bootloader sends responses from
#define CAN_RESP_ADDR (BOOTLOAD_CAN_RESP_ADDR)

// number of sectors in the flash
#define HW_TOTAL_SECTORS (8)

// number of accessible pages (not taken by bootloader)
#define HW_AVAIL_PAGES (0x7000/0x100)

// Command Processing
// commands are sent to CAN_CMD_ADDR above
// and a response is sent from CAN_RESP_ADDR
// with the exception of Page Data

// Command Format
// the first byte of a command is its ID and the next are its arguments
// the command DLC (data length code) must exactly equal the CMDLEN given
// once a command is processed, a response is generated
// first byte is the command ID and the second byte is the response code
// all commands can send the following responses:
// RESP_SUCCESS:
//      everything went fine. send next command
// RESP_INVALID_COMMAND:
//      invalid ID, length, or out of range arguments. fix command
//      and send again
// RESP_ERROR:
//      something unexpected happened internally and the command failed.
//      reset bootloader and start programming again

// Page Data
// The page data command fills the page buffer with data
// there is no ID, a Page Data command is recognized by having a DLC of 8
// all 8 bytes are put into the page buffer at the position specified
// by the page pointer
// no response is ever generated and this command cannot fail
// however the bootloader may have reset due to CAN bus state
#define CMDLEN_PAGE_DATA (8)

// Error Handling
// the bootloader verifies the CRC32 of flash before booting it
// if the checksum fails, the bootloader will be entered automatically
//
// the correct action to error responses is detailed with the command
// and response
//
// if the bootloader does not receive any message for 10 seconds,
// it will attempt to reboot into the application
//
// message integrity and delivery is ensured by the CAN bus. if the CAN engine
// enters error passive or busoff state, message integrity and delivery is no
// longer guaranteed, so the bootloader will reset and the connection must be
// re-established

// Connecting
// the CMD_HELLO command must be sent to enter and connect to the
// bootloader. if the application is running, it will reboot into
// the bootloader without a response. so this command must be sent
// multiple times. perhaps resend if there is no response after 100ms
// and abort after 10 tries.

// the Hello command
// send this to connect to the bootloader
// first argument is 16 bit little endian system ID
// second argument is 32 bit little endian key which must be equal to
// CMD_HELLO_KEY
// if the system ID or key are incorrect, there will be no response
// may need to be sent multiple times, if bootloader is not active or is
// rebooting when command is sent
#define CMD_HELLO (BOOTLOAD_CMD_HELLO)
#define CMDLEN_HELLO (BOOTLOAD_CMDLEN_HELLO)
#define CMD_HELLO_KEY (BOOTLOAD_CMD_HELLO_KEY)
// possible responses
// RESP_HELLO:
//      connection successful

// the Erase All command
// send this to erase the chip
#define CMD_ERASE_ALL (1)
#define CMDLEN_ERASE_ALL (1)
// possible responses
// RESP_PROGRAM_FAILURE:
//      erase succeeded but chip is not erased. retry command. if retry fails,
//      reset bootloader and restart programming. chip may have damaged flash

// the Empty command
// send this to empty the page buffer
// this sets the page pointer to 0 and fills the page with 0xFF
// after this, Page Data commands can be sent to set the page buffer contents
#define CMD_EMPTY (2)
#define CMDLEN_EMPTY (1)

// the Program and Verify command
// send this to program a page with the contents of the page buffer
// first argument is 16 bit little endian page number
// second argument is 32 bit little endian expected CRC32 of page buffer
#define CMD_PROGRAM_VERIFY (3)
#define CMDLEN_PROGRAM_VERIFY (7)
// possible responses
// RESP_CHECKSUM_INCORRECT
//      page buffer checksum does not match expected value. empty page buffer
//      and send page data again, then retry programming
// RESP_PROGRAM_FAILURE:
//      verification of programmed page failed. retry command. if retry fails,
//      reset bootloader and restart programming. chip may have damaged flash

// the Reboot command
// send this to reboot the chip
// first argument is 8 bit boolean boot mode. if zero, the bootloader reboots
//      into bootloader mode. if nonzero, the bootloader attemps to boot the
//      application, then re-enters bootloader mode if that failed
// a response is sent before the chip reboots
#define CMD_REBOOT (4)
#define CMDLEN_REBOOT (2)

// response definitions
#define RESP_SUCCESS (0)
#define RESP_HELLO (1)
#define RESP_INVALID_COMMAND (2)
#define RESP_ERROR (3)
#define RESP_PROGRAM_FAILURE (4)
#define RESP_CHECKSUM_INCORRECT (5)

#endif