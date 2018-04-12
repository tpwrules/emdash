#ifndef PLATFORM_PC_H
#define PLATFORM_PC_H

// interrupt interface routines
void (*interrupt_wait)();

// graphics emulation routines
void (*scr_draw_text)(uint8_t x, uint8_t y, char* text, uint8_t inverted);
void (*scr_draw_rect)(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t white);

// Python registers callbacks to implement most of the
// platform-specific stuff
// so define functions that accept these registrations
// and store them in the function pointers above

void pc_reg_interrupt_wait(void (*cb)());

#endif