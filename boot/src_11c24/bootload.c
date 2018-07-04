#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "bootload.h"
#include "protocol.h"
#include "chip.h"
#include "crc32.h"
#include "can_hw.h"
#include "boot.h"
#include "iap.h"

// CAN message buffers
// configure first message object to only receive commands
static CCAN_MSG_OBJ_T rxmsg = {
    CAN_CMD_ADDR, 0x7FF,
    {0, 0, 0, 0, 0, 0, 0, 0}, 0,
    1
};

// configure second message object to transmit responses
// default response is HELLO
static CCAN_MSG_OBJ_T txmsg = {
    CAN_RESP_ADDR, 0,
    {CMD_HELLO, RESP_HELLO, 0, 0, 0, 0, 0, 0}, 2,
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
//__attribute__ ((section(".after_vectors")))
static void can_wait_rx(void) {
    while (!msg_was_received) {
        LPC_CCAN_API->isr();
    }
    msg_was_received = false;
}

// send a message, then wait for successful transmission
static void can_do_tx(void) {
    LPC_CCAN_API->can_transmit(&txmsg);
    while (!msg_was_transmitted) {
        LPC_CCAN_API->isr();
    }
    msg_was_transmitted = false;
}

// shout hello until someone answers
static void say_hello(void) {
    int timer = 0; // 100ms per hello
    while (1) {
        if (timer == 0) {
            can_do_tx(); // message object is already all set up
            timer = 100;
        }

        // decrement timer if systick elapsed
        if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) {
            timer--;
        }

        // process CAN and check if we got a response
        LPC_CCAN_API->isr();
        if (msg_was_received) {
            msg_was_received = false;
            if (rxmsg.data[0] == 0 && rxmsg.dlc == 1) {
                // hello message is correct, send response
                txmsg.data[1] = RESP_SUCCESS;
                can_do_tx();
                break;
            }
        }
    }
}

// preprogrammed responses
static void bl_respond(uint8_t response) {
    txmsg.data[1] = response;
    can_do_tx();
}

// page buffer data and pointer
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
    memset(page_buf, 0xFF, 256);
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
    // and now do it
    reboot(into_app);
}

void bootload(void) {
    // program message receive filter
    LPC_CCAN_API->config_rxmsgobj(&rxmsg);

    say_hello();

    // now enter main loop
    while (1) {
        // receive a command
        can_wait_rx();
        // update command for response
        if (rxmsg.dlc > 0) {
            txmsg.data[0] = rxmsg.data[0];
        } else {
            // invalid command if DLC is 0
            txmsg.data[0] = 0xFF;
            bl_respond(RESP_INVALID_COMMAND);
            continue;
        }

        // if it's a DLC of 8, we process it as a page data command
        if (rxmsg.dlc == 8) {
            bl_cmd_page_data();
            continue;
        }

        // otherwise, look it up in switch statement
        switch (rxmsg.data[0]) {
            case CMD_HELLO:
                // send successful response
                bl_respond(RESP_SUCCESS);
                break;

            case CMD_ERASE_ALL:
                if (rxmsg.dlc != 1) {
                    bl_respond(RESP_INVALID_COMMAND);
                } else {
                    bl_respond(bl_cmd_erase_all());
                }
                break;

            case CMD_EMPTY:
                if (rxmsg.dlc != 1) {
                    bl_respond(RESP_INVALID_COMMAND);
                } else {
                    bl_cmd_empty(); // can't fail
                    bl_respond(RESP_SUCCESS);
                }
                break;

            case CMD_PROGRAM_VERIFY:
                if (rxmsg.dlc != 7) {
                    bl_respond(RESP_INVALID_COMMAND);
                } else {
                    // extract parameters
                    uint16_t page_num;
                    uint32_t expected_crc;
                    memcpy(&page_num, &rxmsg.data[1], 2);
                    memcpy(&expected_crc, &rxmsg.data[3], 4);
                    bl_respond(bl_cmd_program_verify(page_num, expected_crc));
                }
                break;

            case CMD_REBOOT:
                if (rxmsg.dlc != 2) {
                    bl_respond(RESP_INVALID_COMMAND);
                } else {
                    bl_cmd_reboot(rxmsg.data[1] != 0);
                    // response is handled within command
                }
                break;

            default:
                // invalid command, sorry
                bl_respond(RESP_INVALID_COMMAND);
                break;
        }

    }
}