#include "platform.h"

// this file is mostly the definition of all the PC function pointers

#undef PCFUNC
#define PCFUNC(type, name) type (*name)

// interrupt interface routines
PCFUNC(void, interrupt_wait)(void);

// screen emulation routines
PCFUNC(void, scr_show_page)(uint8_t text, uint8_t page);
PCFUNC(void, scr_clear_page)(uint8_t text, uint8_t page);
PCFUNC(void, scr_draw_rect)(uint32_t pixel_addr, uint8_t w, uint8_t h, uint8_t color);
PCFUNC(void, scr_draw_pic)(uint32_t byte_addr, uint32_t pic_id, uint8_t inverted);
PCFUNC(void, scr_draw_text)(uint32_t text_addr, char *text);
