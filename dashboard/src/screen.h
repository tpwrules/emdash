#ifndef SCREEN_H
#define SCREEN_H

#include "platform.h"

// this file defines the operations that can be done on the
// graphic screen

// Screen Addressing
// The screen has two layers: graphics and text. Each layer
// has two pages. One graphics page and one text page are shown.

// The text layer has one byte per character and is 40x8.
#ifndef PLATFORM_PC
#define SCR_TEXT_ADDR(page, x, y) \
    (0x8000+((page)*0x200)+((y)*40)+(x))
#else
#define SCR_TEXT_ADDR(page, x, y) \
    (((page)*0x200)+((y)<<6)+(x))
#endif

// The graphics layer can be addressed in byte or pixel mode.
// in byte mode, each address is an 8x1 block of pixels
// the screen is thus 30x64 bytes
#define SCR_BYTE_ADDR(page, x, y) \
    (((page)*0x800)+((y)<<5)+(x))

// in pixel mode, the screen is 240x64 pixels
#define SCR_PIXEL_ADDR(page, x, y) \
    (((page)*0x4000)+((y)<<8)+(x))

// Screen Operations

// switch currently displayed page
// text: if true, the text page is switched.
//      otherwise, the graphics page is switched
// page: the new page to display
PCFUNC(void, scr_show_page)(uint8_t text, uint8_t page);

// clear a page (to white for graphics, all blank chars for text)
// text: if true, a text page is cleared.
//      otherwise, a graphics page is cleared
// page: the page to clear
PCFUNC(void, scr_clear_page)(uint8_t text, uint8_t page);

// draw a rectangle
// the display can only update one 8x1 block at a time
// let's say you wish to draw a w=4 wide rectangle at pixel x=2
// the 'color' byte is as follows
//  * 1 is black, 0 is white
//  * bit 0 is color of the middle, i.e. pixels 2,3,4,5
//  * bit 1 is the color of the left, i.e. pixels 0,1
//  * bit 2 is the color of the right, i.e. pixels 6,7
PCFUNC(void, scr_draw_rect)(uint32_t pixel_addr, uint8_t w, uint8_t h, uint8_t color);

// draw a picture
PCFUNC(void, scr_draw_pic)(uint32_t byte_addr, uint32_t pic_id, uint8_t inverted);

// draw some text
// the font is DOS CP437 (https://en.wikipedia.org/wiki/Code_page_437)
// \x84 -> ä   \x94 -> ö   \x81 -> ü
// \x8E -> Ä   \x99 -> Ö   \x9A -> Ü
PCFUNC(void, scr_draw_text)(uint32_t text_addr, char *text);

#endif
