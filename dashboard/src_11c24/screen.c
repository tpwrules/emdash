#include "platform.h"
#include "screen.h"
#include "pic_data.h"
#include "../src_gen/pic_ids.h"

#include "t6963.h"

void scr_show_page(uint8_t text, uint8_t page) {
    if (text) {
        // set text home address
        // upper left of desired page
        lcd_send_acmd(0x40, SCR_TEXT_ADDR(page, 0, 0));
    } else {
        // set graphics home address
        // upper left of desired page
        lcd_send_acmd(0x42, SCR_BYTE_ADDR(page, 0, 0));
    }
}

void scr_clear_page(uint8_t text, uint8_t page) {
    // fill desired page with zeros
    int size, addr;
    if (text) {
        size = 64*8;
        addr = SCR_TEXT_ADDR(page, 0, 0);
    } else {
        size = 32*64;
        addr = SCR_BYTE_ADDR(page, 0, 0);
    }

    // set LCD address to clear region start
    lcd_send_acmd(0x24, addr);
    for (int i=0; i<size; i++)
        lcd_send_1cmd(0xC0, 0);
}

void scr_draw_rect(uint32_t pixel_addr, uint8_t w, uint8_t h, uint8_t color) {

}

void scr_draw_pic(uint32_t byte_addr, uint32_t pic_id, uint8_t inverted) {

}

void scr_draw_text(uint32_t text_addr, char *text) {

}