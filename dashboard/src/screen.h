#ifndef SCREEN_H
#define SCREEN_H

#include "platform.h"
#include "../src_gen/pic_ids.h"

// this file defines the operations that can be done on the
// graphic screen

// Screen Addressing
// The screen has two layers: graphics and text. Each layer
// has two pages. One graphics page and one text page are shown.

// The text layer has one byte per character and is 40x8 visible,
// 64x8 in memory
#ifndef PLATFORM_PC
#define SCR_TEXT_ADDR(page, x, y) \
    (0x4000+((page)*0x200)+((y)<<6)+(x))
#else
#define SCR_TEXT_ADDR(page, x, y) \
    (((page)*0x200)+((y)<<6)+(x))
#endif

// The graphics layer can be addressed in byte or pixel mode.
// in byte mode, each address is an 6x1 block of pixels
// the screen is thus 40x64 bytes visible, 64x64 in memory
#define SCR_BYTE_ADDR(page, x, y) \
    (((page)*0x1000)+((y)<<6)+(x))
#define SCR_PIXEL_ADDR(page, x, y) \
    (SCR_BYTE_ADDR((page),(x)/6,(y)) | (((x)%6)<<16))

// sometimes we want to place graphics lined up with text
// this returns the byte addr for text at a specific location
#define SCR_BYTE_ADDR_AT_TEXT(page, x, y) \
    (SCR_BYTE_ADDR((page), (x), (y)*8))
// maybe we want to place rectangles aligned with text also
#define SCR_PIXEL_ADDR_AT_TEXT(page, x, y) \
    (SCR_BYTE_ADDR((page), (x), (y)*8)) // conveniently the same!

// Screen Operations

// switch currently displayed page
// text: if true, the text page is switched.
//      otherwise, the graphics page is switched
// page: the new page to display
PCFUNC(void, scr_show_page)(uint8_t text, uint8_t page);
#define scr_show_graphics_page(page) scr_show_page(false, (page))
#define scr_show_text_page(page) scr_show_page(true, (page))

// clear a page (to white for graphics, all blank chars for text)
// text: if true, a text page is cleared.
//      otherwise, a graphics page is cleared
// page: the page to clear
PCFUNC(void, scr_clear_page)(uint8_t text, uint8_t page);
#define scr_clear_graphics_page(page) scr_clear_page(false, (page))
#define scr_clear_text_page(page) scr_clear_page(true, (page))

// draw a rectangle
// the color is non-zero for a black rectangle and 0 for white
PCFUNC(void, scr_draw_rect)(uint32_t pixel_addr, uint8_t w, uint8_t h, uint8_t color);

// draw a picture
PCFUNC(void, scr_draw_pic)(uint32_t byte_addr, uint32_t pic_id, uint8_t inverted);

// draw some text
// the font is DOS CP437 (https://en.wikipedia.org/wiki/Code_page_437)
// \x84"" -> ä   \x94"" -> ö   \x81"" -> ü   \xE1"" -> ß
// \x8E"" -> Ä   \x99"" -> Ö   \x9A"" -> Ü
// To draw: Knäckebrotkrümel Straße
// scr_draw_text(SCR_TEXT_ADDR(0, 0, 0), "Kn\x84""ckebrotkr\x81""mel Stra\xE1""e");
PCFUNC(void, scr_draw_text)(uint32_t text_addr, char *text);

#endif
