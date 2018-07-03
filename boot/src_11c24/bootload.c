#include <stdint.h>
#include <stdbool.h>

#include "bootload.h"
#include "protocol.h"
#include "chip.h"
#include "can_hw.h"
#include "boot.h"

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

bool msg_was_received = false;
bool msg_was_transmitted = false;

// CAN driver callbacks
// called when a message is received
__attribute__ ((section(".after_vectors")))
void CAN_rx(uint8_t msg_obj_num) {
    if (msg_obj_num == 1) {
        LPC_CCAN_API->can_receive(&rxmsg);
        msg_was_received = true;
    }
}

// called after a message was transmitted
__attribute__ ((section(".after_vectors")))
void CAN_tx(uint8_t msg_obj_num) {
    if (msg_obj_num == 2) {
        msg_was_transmitted = true;
    }
}

// called when a bus error has happened
__attribute__ ((section(".after_vectors")))
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
__attribute__ ((section(".after_vectors")))
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

void bootload(void) {
    // program message receive filter
    LPC_CCAN_API->config_rxmsgobj(&rxmsg);

    say_hello();

    volatile int i=0;
    while (1) {
        i++;
    }
}