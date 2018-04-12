#include "platform.h"

// callback registration handlers
void pc_reg_interrupt_wait(void (*cb)()) {
    interrupt_wait = cb;
}

void pc_reg_scr_draw_text(void (*cb)(uint8_t x, uint8_t y, char* text, uint8_t inverted)) {
    scr_draw_text = cb;
}