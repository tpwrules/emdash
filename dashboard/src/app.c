#include "platform.h"
#include "app.h"
#include "screen.h"

#include <stdio.h>

volatile int timer_val = 0;
volatile uint16_t rpm = 0;

void app_entry(void) {
    // show page 0 for text and graphics
    scr_show_page(false, 0);
    scr_show_page(true, 0);

    // clear all pages
    for (int i=0; i<2; i++) {
        scr_clear_page(false, i);
        scr_clear_page(true, i);
    }

    // draw RPM border
    scr_draw_rect(SCR_PIXEL_ADDR(0, 0, 7), 240-56, 1, 1);
    scr_draw_rect(SCR_PIXEL_ADDR(0, 240-56, 0), 1, 8, 1);
    // draw RPM text
    scr_draw_text(SCR_TEXT_ADDR(0, 31, 0), "RPM:");

    // and gear indicator
    scr_draw_pic(SCR_BYTE_ADDR(0, 13, 16), 0, false);

    char text[50];
    uint16_t old_rpm = 0;
    uint8_t old_bar_val = 0;
    while (1) {
        if (rpm > 7800) {
            // start flashing gear as a warning
            if (timer_val % 20 == 0) {
                scr_draw_pic(SCR_BYTE_ADDR(0, 13, 16),
                    0, timer_val % 40 < 20);
            }
        } else if (old_rpm > 7800) {
            // reset gear
            scr_draw_pic(SCR_BYTE_ADDR(0, 13, 16),
                0, 0);
        }

        if (rpm != old_rpm) {
            // calculate new position and draw bar
            uint32_t bar_rpm = rpm;
            if (bar_rpm > 12000) {
                bar_rpm = 12000;
            }
            uint8_t bar_val = bar_rpm*(240-56)/12000;
            if (bar_val > old_bar_val) {
                // add more pixels to bar
                // left and middle are black, right is white
                scr_draw_rect(SCR_PIXEL_ADDR(0, old_bar_val, 0),
                    bar_val-old_bar_val, 7, 3);
            } else if (bar_val < old_bar_val) {
                // take pixels away from the bar
                // left is black, middle and right are white
                scr_draw_rect(SCR_PIXEL_ADDR(0, bar_val, 0),
                    old_bar_val-bar_val, 7, 2);
            }

            sprintf(text, "%5d", rpm);
            scr_draw_text(SCR_TEXT_ADDR(0, 35, 0), text);
            old_rpm = rpm;
            old_bar_val = bar_val;
        }

        interrupt_wait();
    }
}

void app_timer_interrupt(void) {
    timer_val++;
}

void app_can_interrupt(uint32_t msgid, uint8_t dlc, uint8_t *data) {
    if (msgid == 0x121) {
        rpm = data[3] << 8 | data[2];
    }
}