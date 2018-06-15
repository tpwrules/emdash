#include "platform.h"
#include "screen.h"
#include "../src/pic_data.h"
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

    // start auto send mode
    lcd_send_0cmd(0xB0);
    for (int i=0; i<size; i++)
        lcd_send_auto(0, false);
    // end auto mode
    lcd_send_auto(0xB2, true);
}

void scr_draw_rect(uint32_t pixel_addr, uint8_t w, uint8_t h, uint8_t color) {
    color = color ? 0x3f : 0; // normalize rectangle color

    // offset of the first pixel within the first byte
    uint32_t start_offset = pixel_addr >> 16;
    // and address of the first byte
    uint32_t byte_addr = pixel_addr & 0xFFFF;

    // precalculate starting mask
    uint8_t mask_start = 0x3f >> start_offset;
    // if we end in the starting byte, we have to
    // remove the rectangle at the end
    if (start_offset + w < 6) {
        mask_start &= ~(0x3f >> (start_offset+w));
    }

    for (; h>0; h--) {
        // position at the start of the line
        lcd_send_acmd(0x24, byte_addr);
        byte_addr += 64;
        int x = w;
        if (start_offset) {
            // we're not starting exactly on a byte
            // so we have to modify the byte in the LCD
            uint8_t b = lcd_send_readcmd(0xC5);
            // set or clear rectangle bits, depending on color
            if (color) {
                b |= mask_start;
            } else {
                b &= ~mask_start;
            }
            // and write byte back to LCD
            lcd_send_1cmd(0xC0, b);

            x -= (6-start_offset);
        }

        // now fill up the main area
        if (x >= 6) {
            lcd_send_0cmd(0xB0); // start auto mode
            while (x >= 6) {
                lcd_send_auto(color, false); // fill this byte
                x -= 6;
            }
            // end auto mode
            lcd_send_auto(0xB2, true);
        }

        // now deal with the end
        if (x > 0) {
            // again, not ending on a byte. so rmw time
            uint8_t b = lcd_send_readcmd(0xC5);
            uint8_t mask_end = 0x3f << (6-x);
            if (color) {
                b |= mask_end;
            } else {
                b &= ~mask_end;
            }
            // write byte back to LCD
            lcd_send_1cmd(0xC0, b);
        }
    }
}

void scr_draw_pic(uint32_t byte_addr, uint32_t pic_id, uint8_t inverted) {
    // get pic data
    const pic_data_t *pic = &picture_data_records[pic_id];

    // set up decompression context
    uint8_t din = 0xC0; // input compressed byte
    uint8_t out = 0; // byte to output
    int zeros = 0; // number of zeros remaining before output

    const uint8_t *data = pic->data;

    // loop over rows in picture
    for (int y=0; y<pic->height; y++) {
        // set LCD address to the start of this row
        lcd_send_acmd(0x24, byte_addr);
        // increment to next row
        byte_addr += 64;
        // start auto send mode
        lcd_send_0cmd(0xB0);

        for (int x=0; x<pic->width; x++) {
            out = 0xFF; // we need to output a byte
            do {
                if (zeros > 0) {
                    // output another zero
                    out = 0;
                    zeros--;
                } else {
                    // no zeros remaining, output the data byte
                    if ((din & 0xC0) != 0xC0) {
                        // if it's not just a zero count!
                        out = din & 0x3F;
                    }
                    // now read and process the next byte
                    din = *data++;
                    if ((din & 0xC0) == 0xC0) {
                        // just a zero run
                        zeros = (din & 0x3F) + 1;
                    } else {
                        zeros = (din & 0xC0) >> 6;
                    }
                }
            } while (out == 0xFF);

            // invert byte if asked
            if (inverted) out ^= 0xFF;

            // output the byte
            lcd_send_auto(out, false);
        }

        // end auto mode
        lcd_send_auto(0xB2, true);
    }
}

void scr_draw_text(uint32_t text_addr, char *text) {
    // go to the requested address
    lcd_send_acmd(0x24, text_addr);
    // start auto mode
    lcd_send_0cmd(0xB0);
    // and output text
    while (1) {
        char c = *text++;
        if (!c) break;
        lcd_send_auto(c, false);
    }
    // end auto mode
    lcd_send_auto(0xB2, true);
}