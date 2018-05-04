// this file manages the dashboard CAN hardware

#include <inttypes.h>
#include <stdbool.h>

#include "../src/platform.h"
#include "can_hw.h"
#include "../src/canvar.h"

#include "chip.h"

// calculate can timing from baudrate
// stolen directly from ccan_rom example
static void baudrateCalculate(uint32_t baud_rate, uint32_t *can_api_timing_cfg)
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

    // and give it to application interrupt
    app_can_interrupt(msg_obj.mode_id,
        msg_obj.dlc, msg_obj.data);
}

// called after a message was transmitted
static void CAN_tx(uint8_t msg_obj_num) {
    // we don't transmit messages so there's not
    // much to do
}

// called when a bus error has happened
static void CAN_error(uint32_t error_info) {
    // TODO: really need to make this do something
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
    baudrateCalculate(1000000, timing_data);
    // now inititalize the CAN driver with that data
    // (and tell it to enable interrupts)
    LPC_CCAN_API->init_can(&timing_data[0], true);

    // now configure the CAN callback functions
    CCAN_CALLBACKS_T callbacks = {
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
    LPC_CCAN_API->config_calb(&callbacks);

    // now enable CAN interrupts
    NVIC_EnableIRQ(CAN_IRQn);

    // configure message object 1 to receive all
    // 11 bit ID messages
    CCAN_MSG_OBJ_T msg_obj;
	msg_obj.msgobj = 1;
	msg_obj.mode_id = 0;
	msg_obj.mask = 0;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);
}
