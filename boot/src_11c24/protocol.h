#ifndef PROTOCOL_H
#define PROTOCOL_H

// this file contains definitions of the commands
// and responses used in the bootloading protocol

#include "bootload_integrate.h"

// Command Processing
// commands are sent to BOOTLOAD_CAN_CMD_ADDR
// and a response is sent from BOOTLOAD_CAN_RESP_ADDR
// (unless the command was Page Data)

// Command Format
// the first byte of a command is its ID and the next are its arguments
// the command DLC (data length code) must exactly equal the CMDLEN given
// once a command is processed, a response is generated
// first byte is the command ID, the second byte is the response code,
// and the next four bytes are the 32 bit little endian response data
// all commands can send the following responses:
// RESP_SUCCESS:
//      everything went fine. send next command
// RESP_INVALID_COMMAND:
//      invalid ID, length, or out of range arguments. fix command
//      and send again
// RESP_ERROR:
//      something unexpected happened internally and the command failed.
//      reset bootloader and start programming again
// if the response is not RESP_SUCCESS (or RESP_HELLO in the case of CMD_HELLO)
// the response data will be 0

// Page Data
// The page data command fills the page buffer with data
// there is no ID, a Page Data command is recognized by having a DLC of 8
// all 8 bytes are put into the page buffer at the position specified
// by the page pointer
// no response is ever generated and this command cannot fail
// however the bootloader may have reset due to CAN bus state
#define CMDLEN_PAGE_DATA (8)

// Connecting
// Connecting is done by sending CMD_HELLO to the bootloader. When the
// bootloader responds with RESP_HELLO, the connection has been made. There
// may not be a respone if the application is not listening, the application
// receives the connection attempt, the bootloader is busy initializing, etc.
// The suggested method is to send CMD_HELLO every 100ms until the bootloader
// responds. If the bootloader responds with RESP_HELLO, the connection is
// successful. If there is another response, the connection failed.

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

// the Hello command (actual definitions in bootload_integrate.h)
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
// response data: 1 if the flash currently contains a valid
// application, 0 otherwise

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

// the Read Flash command
// send this to read a 32 bit word from Flash
// argument is a 32 bit little endian address to read from. the address must
//      be within Flash region but does not need to be 32 bit aligned.
// response data is the 32 bit little endian word at the given location
#define CMD_READ_FLASH (5)
#define CMDLEN_READ_FLASH (5)

// response definitions
#define RESP_SUCCESS (0)
#define RESP_HELLO (1)
#define RESP_INVALID_COMMAND (2)
#define RESP_ERROR (3)
#define RESP_PROGRAM_FAILURE (4)
#define RESP_CHECKSUM_INCORRECT (5)

#endif