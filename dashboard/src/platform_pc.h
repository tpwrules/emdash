#ifndef PLATFORM_PC_H
#define PLATFORM_PC_H

// interrupt interface routines
extern void (*interrupt_wait)();

// graphics emulation routines
extern void (*scr_draw_text)(uint8_t x, uint8_t y, char* text, uint8_t inverted);
extern void (*scr_draw_rect)(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t white);
extern void (*scr_draw_pic)(uint8_t x, uint8_t y, uint32_t pic, uint8_t inverted);

#endif