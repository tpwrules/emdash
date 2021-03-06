#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "bootload.h"
#include "protocol.h"
#include "bootload_integrate.h"
#include "system_ids.h"
#include "chip.h"
#include "crc32.h"
#include "can_hw.h"
#include "boot.h"
#include "iap.h"

// CAN message buffers
// configure first message object to only receive commands
static CCAN_MSG_OBJ_T rxmsg = {
    BOOTLOAD_CAN_CMD_ADDR, 0x7FF,
    {0, 0, 0, 0, 0, 0, 0, 0}, 0,
    1
};

// configure second message object to transmit responses
// default response is Hello
static CCAN_MSG_OBJ_T txmsg = {
    BOOTLOAD_CAN_RESP_ADDR, 0,
    {CMD_HELLO, RESP_HELLO, 0, 0, 0, 0, 0, 0}, 6,
    2
};

static bool msg_was_received = false;
static bool msg_was_transmitted = false;

// CAN driver callbacks
// called when a message is received
void CAN_rx(uint8_t msg_obj_num) {
    if (msg_obj_num == 1) {
        LPC_CCAN_API->can_receive(&rxmsg);
        msg_was_received = true;
    }
}

// called after a message was transmitted
void CAN_tx(uint8_t msg_obj_num) {
    if (msg_obj_num == 2) {
        msg_was_transmitted = true;
    }
}

// called when a bus error has happened
void CAN_error(uint32_t error_info) {
    // as promised in protocol, reboot back into the bootloader
    // if we've hit error passive or busoff
    if (error_info & (CAN_ERROR_PASS | CAN_ERROR_BOFF)) {
        reboot(false);
    }
}

// wait for a message to be received
// but reboot if one hasn't been in the last 10 seconds
// it also reboots if rescue mode has timed out after 250ms
static inline void can_wait_rx(void) {
    static uint32_t rescue_mode_timeout = 250; // ms
    uint32_t msg_timeout = 10000; // ms
    while (!msg_was_received) {
        LPC_CCAN_API->isr();
        // decrement timeout if one ms systick elapsed
        if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) {
            msg_timeout--;
            rescue_mode_timeout--;
        }
        if (msg_timeout == 0 || 
                (rescue_mode && rescue_mode_timeout == 0)) {
            // reboot back into the app
            reboot(true);
        }
    }
    msg_was_received = false;
}

// send a response and wait for successful transmission
// (command field has already been populated by main loop)
// if the message isn't transmitted after 5 seconds, the
// bootloader reboots
static void bl_respond(uint8_t response) {
    txmsg.data[1] = response;
    LPC_CCAN_API->can_transmit(&txmsg);

    uint32_t respond_timeout = 5000; // ms
    while (!msg_was_transmitted) {
        LPC_CCAN_API->isr();
        // decrement timeout if one ms systick elapsed
        if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) {
            respond_timeout--;
        }
        if (respond_timeout == 0) {
            // reboot back into the bootloader
            reboot(false);
        }
    }
    msg_was_transmitted = false;
}

// page buffer data and pointer
// data must be 32 bit aligned for IAP routine
static uint32_t page_buf[256/4];
static uint8_t page_buf_ptr;

// command handlers
static inline void bl_cmd_page_data(void) {
    // copy input data to page buffer
    uint8_t* page_buf_byte = (uint8_t*)page_buf;
    for (int i=0; i<8; i++) {
        page_buf_byte[page_buf_ptr++] = rxmsg.data[i];
    }
}

static inline uint8_t bl_cmd_erase_all(void) {
    // ask IAP to do the job
    return iap_erase_and_blank_check();
}

static inline void bl_cmd_empty(void) {
    // clear to FF (which is unprogrammed flash)
    memset(page_buf, 0xFF, 256);
    // and reset data pointer to beginning
    page_buf_ptr = 0;
}

static inline uint8_t bl_cmd_program_verify(uint16_t page_num, uint32_t expected_crc) {
    // verify page number
    if (page_num >= HW_AVAIL_PAGES) {
        return RESP_INVALID_COMMAND;
    }

    // verify CRC of page buffer
    uint32_t crc = crc32_calc((uint8_t*)page_buf, 256);
    if (crc != expected_crc) {
        return RESP_CHECKSUM_INCORRECT;
    }

    // and program the chip
    return iap_program_and_verify(page_num, page_buf);
}

static inline void bl_cmd_reboot(bool into_app) {
    // we're about to successfully reboot
    bl_respond(RESP_SUCCESS);
    // now do it
    reboot(into_app);
}

static inline uint8_t bl_cmd_read_flash(uint32_t addr) {
    // make sure address is within flash
    if (addr >= PAGE_TO_ADDRESS(HW_AVAIL_PAGES) - 3) {
        return RESP_INVALID_COMMAND;
    }

    // do the read. we need memcpy cause both src and dest are unaligned
    memcpy(&txmsg.data[2], (uint8_t*)addr, 4);
    return RESP_SUCCESS;
}

bool said_hello = false;

void bootload(void) {
    // program message receive filter
    LPC_CCAN_API->config_rxmsgobj(&rxmsg);

    while (1) {
        // wait for a command to be received
        can_wait_rx();

        // update response with the command being responded to
        if (rxmsg.dlc > 0) {
            txmsg.data[0] = rxmsg.data[0];
        } else {
            // invalid command if DLC is 0
            txmsg.data[0] = 0xFF;
            if (said_hello)
                bl_respond(RESP_INVALID_COMMAND);
            continue;
        }

        // clear out response data
        memset(&txmsg.data[2], 0, 4);

        // process if it's a Hello command
        if (rxmsg.dlc == CMDLEN_HELLO && rxmsg.data[0] == CMD_HELLO) {
            // extract parameters
            uint16_t system_id;
            uint32_t hello_key;
            memcpy(&system_id, &rxmsg.data[1], 2);
            memcpy(&hello_key, &rxmsg.data[3], 4);
            // make sure the ID and key are valid
            if (system_id == (CURR_SYSTEM_ID) && hello_key == CMD_HELLO_KEY) {
                // they are! mark that someone greeted us
                said_hello = true;
                // and tell them if the flash is valid
                txmsg.data[2] = boot_check_app_validity() ? 1 : 0;
                // once someone's said hi, rescue mode is over
                // and now it's just the bootloader
                rescue_mode = false;
                // say hi back
                bl_respond(RESP_HELLO);
            }
            continue; // done processing this command
        }

        // don't act on a command if nobody's said hi
        if (!said_hello) continue;

        // if it's a DLC of 8, we process it as a page data command
        if (rxmsg.dlc == CMDLEN_PAGE_DATA) {
            bl_cmd_page_data();
            continue;
        }

        // otherwise, process by command number
        switch (rxmsg.data[0]) {
            case CMD_ERASE_ALL:
                if (rxmsg.dlc != CMDLEN_ERASE_ALL) {
                    bl_respond(RESP_INVALID_COMMAND);
                } else {
                    bl_respond(bl_cmd_erase_all());
                }
                break;

            case CMD_EMPTY:
                if (rxmsg.dlc != CMDLEN_EMPTY) {
                    bl_respond(RESP_INVALID_COMMAND);
                } else {
                    bl_cmd_empty();
                    // nothing to fail
                    bl_respond(RESP_SUCCESS);
                }
                break;

            case CMD_PROGRAM_VERIFY:
                if (rxmsg.dlc != CMDLEN_PROGRAM_VERIFY) {
                    bl_respond(RESP_INVALID_COMMAND);
                } else {
                    // extract parameters
                    uint16_t page_num;
                    uint32_t expected_crc;
                    memcpy(&page_num, &rxmsg.data[1], 2);
                    memcpy(&expected_crc, &rxmsg.data[3], 4);
                    // and do the command
                    bl_respond(bl_cmd_program_verify(page_num, expected_crc));
                }
                break;

            case CMD_REBOOT:
                if (rxmsg.dlc != CMDLEN_REBOOT) {
                    bl_respond(RESP_INVALID_COMMAND);
                } else {
                    bl_cmd_reboot(rxmsg.data[1] != 0);
                    // response is handled within command function
                    // because the command function won't return
                }
                break;

            case CMD_READ_FLASH:
                if (rxmsg.dlc != CMDLEN_READ_FLASH) {
                    bl_respond(RESP_INVALID_COMMAND);
                } else {
                    // extract parameters
                    uint32_t addr;
                    memcpy(&addr, &rxmsg.data[1], 4);
                    // and do the command
                    bl_respond(bl_cmd_read_flash(addr));
                }
                break;

            default:
                // don't know what you mean, sorry
                bl_respond(RESP_INVALID_COMMAND);
                break;
        }

    }
}
