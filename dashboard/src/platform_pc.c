#include "platform.h"

// interrupt interface routines
void (*interrupt_wait)(void);

// graphics emulation routines
void (*scr_draw_text)(uint8_t x, uint8_t y, char* text, uint8_t inverted);
void (*scr_draw_rect)(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t white);
void (*scr_draw_pic)(uint8_t x, uint8_t y, uint32_t pic, uint8_t inverted);
