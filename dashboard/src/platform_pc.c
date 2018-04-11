#include "platform.h"

// callback registration handlers
void pc_reg_interrupt_wait(void (*cb)()) {
    interrupt_wait = cb;
}