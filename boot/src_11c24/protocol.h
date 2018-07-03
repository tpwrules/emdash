#ifndef PROTOCOL_H
#define PROTOCOL_H

// this file contains definitions of the commands
// and responses used in the bootloading protocol
// plus other stuff

// address which the bootloader receives commands at
#define CAN_CMD_ADDR (0x7EF)

// address which the bootloader sends responses from
#define CAN_RESP_ADDR (0x7EE)

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

// Connecting
// when the bootloader is entered, a response is sent approximately
// every 100ms with CMD of CMD_HELLO and RESP of RESP_HELLO
// send a CMD_HELLO and wait for RESP_SUCCESS
// no other commands will have a response
// now the bootloader is ready

// Error Handling
// the bootloader verifies the CRC32 of flash before booting it
// if the checksum fails, the bootloader will be entered automatically
//
// the correct action to error responses is detailed with the command
// and response
//
// message integrity and delivery is ensured by the CAN bus. if the CAN engine
// enters error passive or busoff state, message integrity and delivery is no
// longer guaranteed, so the bootloader will reset and the process must be
// restarted

// the Hello command
// send this to connect to the bootloader
#define CMD_HELLO (0)
#define CMDLEN_HELLO (1)

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