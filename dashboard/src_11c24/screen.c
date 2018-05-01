#include "platform.h"
#include "screen.h"
#include "../src/pic_data.h"
#include "../src_gen/pic_ids.h"

#include "t6963.h"

#define USE_AUTO_MODE

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

#ifdef USE_AUTO_MODE
    // start auto send mode
    lcd_send_0cmd(0xB0);
    for (int i=0; i<size; i++)
        lcd_send_auto(0, false);
    // end auto mode
    lcd_send_auto(0xB2, true);
#else
    for (int i=0; i<size; i++)
        lcd_send_1cmd(0xC0, 0);
#endif
}

void scr_draw_rect(uint32_t byte_addr, uint8_t w, uint8_t h, uint8_t color) {
    uint8_t main_color = color ? 0x3f : 0; // build main rectangle color
    // build the byte at the end by putting in 0s where the rectangle
    // is not
    uint8_t end_color = main_color << (6-(w%6));

    for (int y=0; y<h; y++) {
        // position at the start of the line
        lcd_send_acmd(0x24, byte_addr);
        byte_addr += 64; // go to next row
#ifdef USE_AUTO_MODE
        // start auto send mode
        lcd_send_0cmd(0xB0);
#endif
        // loop pixels backwards
        for (int x=w; x>0; x-=6) {
#ifdef USE_AUTO_MODE
            if (x < 6) // if less than a full byte's worth
                // send end value
                lcd_send_auto(end_color, false);
            else
                // send main value
                lcd_send_auto(main_color, false);
#else
            if (x < 6)
                lcd_send_1cmd(0xC0, end_color);
            else
                lcd_send_1cmd(0xC0, main_color);
#endif
        }
#ifdef USE_AUTO_MODE
        // end auto mode
        lcd_send_auto(0xB2, true);
#endif
    }
}

void scr_draw_pic(uint32_t byte_addr, uint32_t pic_id, uint8_t inverted) {
    // get pic data
    const pic_data_t *pic = &picture_data_records[pic_id];

    // set up decompression context
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
#ifdef USE_AUTO_MODE
        // start auto send mode
        lcd_send_0cmd(0xB0);
#endif
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
            // invert byte if asked
            if (inverted) out ^= 0xFF;
            // output the byte
#ifdef USE_AUTO_MODE
            lcd_send_auto(out, false);
#else
            lcd_send_1cmd(0xC0, out);
#endif
            // update contrl byte
            ctlc--;
            ctl >>= 1;
        }
        // end auto mode
#ifdef USE_AUTO_MODE
        lcd_send_auto(0xB2, true);
#endif
    }
}

void scr_draw_text(uint32_t text_addr, char *text) {
    // go to the requested address
    lcd_send_acmd(0x24, text_addr);
#ifdef USE_AUTO_MODE
    // start auto mode
    lcd_send_0cmd(0xB0);
#endif
    // and output text
    while (1) {
        char c = *text++;
        if (!c) break;
#ifdef USE_AUTO_MODE
        lcd_send_auto(c, false);
#else
        lcd_send_1cmd(0xC0, c);
#endif
    }
#ifdef USE_AUTO_MODE
    // end auto mode
    lcd_send_auto(0xB2, true);
#endif
}