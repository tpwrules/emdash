// this file manages the dashboard CAN hardware

#include <inttypes.h>
#include <stdbool.h>
#include <string.h>

#include "../src/platform.h"
#include "can_hw.h"
#include "../src/canvar.h"
#include "../src_gen/canvar_defs.h"

#include "chip.h"

#include "bootload_integrate.h"

// calculate can timing from baudrate
// stolen directly from ccan_rom example
static inline void baudrateCalculate(uint32_t baud_rate, 
    uint32_t *can_api_timing_cfg)
{
    uint32_t pClk, div, quanta, segs, seg1, seg2, clk_per_bit, can_sjw;
    Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_CAN);
    pClk = Chip_Clock_GetMainClockRate();

    clk_per_bit = pClk / baud_rate;

    for (div = 0; div <= 15; div++) {
        for (quanta = 1; quanta <= 32; quanta++) {
            for (segs = 3; segs <= 17; segs++) {
                if (clk_per_bit == (segs * quanta * (div + 1))) {
                    segs -= 3;
                    seg1 = segs / 2;
                    seg2 = segs - seg1;
                    can_sjw = seg1 > 3 ? 3 : seg1;
                    can_api_timing_cfg[0] = div;
                    can_api_timing_cfg[1] =
                        ((quanta - 1) & 0x3F) |
                        (can_sjw & 0x03) << 6 |
                        (seg1 & 0x0F) << 8 |
                        (seg2 & 0x07) << 12;
                    return;
                }
            }
        }
    }
}

// CAN driver callbacks
// called when a message is received
static void CAN_rx(uint8_t msg_obj_num) {
    // read out message from hardware
    CCAN_MSG_OBJ_T msg_obj;
    msg_obj.msgobj = msg_obj_num;
    LPC_CCAN_API->can_receive(&msg_obj);

    // check if this is a bootloader related message
    if (msg_obj.mode_id == BOOTLOAD_CAN_CMD_ADDR) {
        // check if this message is asking us to reboot
        // into the bootloader
        if (msg_obj.dlc == BOOTLOAD_CMDLEN_HELLO &&
                msg_obj.data[0] == BOOTLOAD_CMD_HELLO) {
            // it seems to be. let's verify the parameters
            uint16_t system_id;
            uint32_t hello_key;
            memcpy(&system_id, &msg_obj.data[1], 2);
            memcpy(&hello_key, &msg_obj.data[3], 4);
            if (system_id == BOOTLOAD_SYSTEM_ID_DASHBOARD &&
                    hello_key == BOOTLOAD_CMD_HELLO_KEY) {
                // do what they want
                reboot_into_bootloader();
            }
        }
        // if it's not just ignore it
    } else if (msg_obj.mode_id != BOOTLOAD_CAN_RESP_ADDR) {
        // it's some other message, which the application
        // might be interested in
        app_can_interrupt(msg_obj.mode_id,
            msg_obj.dlc, msg_obj.data);
    }
}

// called after a message was transmitted
static void CAN_tx(uint8_t msg_obj_num) {
    // we don't transmit messages so there's not
    // much to do
}

// called when a bus error has happened
static void CAN_error(uint32_t error_info) {
    // tell the app what happened
    app_canvar_interrupt(CV_ID_NOBUS_CAN_STATUS, error_info);
}

// CAN hardware interrupt
void CAN_IRQHandler(void) {
    // just call the ROM API and let that handle it
    LPC_CCAN_API->isr();
}

// called to get everything started for CAN
void can_hw_init(void) {
    // calculate timing data from baudrate
    uint32_t timing_data[2];
    baudrateCalculate(500000, timing_data);
    // now inititalize the CAN driver with that data
    // (and tell it to enable interrupts)
    LPC_CCAN_API->init_can(&timing_data[0], true);

    // now configure the CAN callback functions
    static const CCAN_CALLBACKS_T callbacks = {
        // basic can message
        CAN_rx,
        CAN_tx,
        CAN_error,
        // canopen stuff we don't use
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    };
    // tell the driver the above list
    LPC_CCAN_API->config_calb((CCAN_CALLBACKS_T*)&callbacks);

    // now enable CAN interrupts
    NVIC_EnableIRQ(CAN_IRQn);

    // configure message object 1 to receive all
    // messages with 11 bit IDs
    CCAN_MSG_OBJ_T msg_obj;
	msg_obj.msgobj = 1;
	msg_obj.mode_id = 0;
	msg_obj.mask = 0;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);
}
