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
        size = 64*64;
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
    // get pic data
    const pic_data_t *pic = &picture_data_records[pic_id];

    // set up decompression context
    uint8_t last = 0; // last output byte
    uint8_t out = 0; // this output byte
    uint8_t ctl = 0; // control byte
    uint8_t ctlc = 0; // bits remaining in control byte
    const uint8_t *data = pic->data;

    // loop over rows in picture
    for (int y=0; y<pic->height; y++) {
        // set LCD address to the start of this row
        lcd_send_acmd(0x24, byte_addr);
        // increment to next row
        byte_addr += 64;
        for (int x=0; x<pic->width; x++) {
            // make sure there is a bit in the control byte
            if (ctlc == 0) {
                ctl = *data++;
                ctlc = 8;
            }
            if (ctl & 1) {
                // if the LSB is 1, the next output byte is the next input byte
                out = *data++;
            } else {
                // otherwise, it's just 0
                out = 0;
            }
            // output the byte
            lcd_send_1cmd(0xC0, out);
            // update contrl byte
            ctlc--;
            ctl >>= 1;
        }
    }
}

void scr_draw_text(uint32_t text_addr, char *text) {
    // go to the requested address
    lcd_send_acmd(0x24, text_addr);

    // and output text
    while (1) {
        char c = *text++;
        if (!c) break;
        lcd_send_1cmd(0xC0, c-0x20);
    }
}