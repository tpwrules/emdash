#include <inttypes.h>
#include <stdbool.h>
#include <string.h>

#include "app.h"
#include "chip.h"

void app_timer_interrupt() {
    // happens every ms
    // construct a CAN message and send it

    static int time = 0;
    CCAN_MSG_OBJ_T msg_obj;
    memset(&msg_obj, 0, sizeof(msg_obj));
    msg_obj.msgobj = 1;
    msg_obj.mode_id = 0x130;
    msg_obj.dlc = 8;
    memcpy(&msg_obj.data[4], &time, 4);
    LPC_CCAN_API->can_transmit(&msg_obj);
    time++;
}

void app_entry() {
    // turn on interrupts and let everything happen
    __enable_irq();
    while (1);
}