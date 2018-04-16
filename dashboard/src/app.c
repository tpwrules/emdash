#include "platform.h"
#include "app.h"
#include "screen.h"
#include "canvar.h"

#include <stdio.h>

volatile int timer_val = 0;
volatile uint16_t rpm = 0;

void app_entry(void) {
    // show page 0 for text and graphics
    // (we'll draw the splash here)
    scr_show_page(false, 0);
    scr_show_page(true, 0);

    // clear all pages
    for (int i=0; i<2; i++) {
        scr_clear_page(false, i);
        scr_clear_page(true, i);
    }

    // draw splash onto first page
    scr_draw_pic(SCR_BYTE_ADDR(0, 0, 0), PIC_ID_BOOTSPLASH, false);
    scr_draw_text(SCR_TEXT_ADDR(0, 24, 0), "by Thomas Watson");

    // second page is used for flashing when to upshift
    // fill it with black
    scr_draw_rect(SCR_PIXEL_ADDR(1, 0, 0), 240, 64, 1);
    // draw the gear indicator inverted
    scr_draw_pic(SCR_BYTE_ADDR(1, 13, 16), PIC_ID_DEMO_GEAR_FOUR, true);

    // turn on interrupts
    interrupt_enable();
    // wait a bit of time for the splash to be shown
    while (timer_val < 120);

    // now clear and build the main screen
    scr_clear_page(false, 0);
    scr_clear_page(true, 0);

    // draw RPM border
    scr_draw_rect(SCR_PIXEL_ADDR(0, 0, 7), 240-56, 1, 1);
    scr_draw_rect(SCR_PIXEL_ADDR(0, 240-56, 0), 1, 8, 1);
    // draw RPM text
    scr_draw_text(SCR_TEXT_ADDR(0, 31, 0), "RPM:");

    // and gear indicator
    scr_draw_pic(SCR_BYTE_ADDR(0, 13, 16), PIC_ID_DEMO_GEAR_FOUR, false);

    char text[50];
    uint16_t old_rpm = 0;
    uint8_t old_bar_val = 0;

    while (1) {
        interrupt_disable();
        if (rpm > 7800) {
            // start flashing screen as a warning
            if (timer_val % 20 == 0) {
                uint8_t flash = timer_val % 40 < 20;
                scr_show_page(false, flash);
                scr_show_page(true, flash);
            }
        } else if (old_rpm > 7800) {
            // reset screen to regular display
            scr_show_page(false, 0);
            scr_show_page(true, 0);
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

void gear_rpm_update(void) {
    rpm = (uint16_t)cv_nmot.u;
}

void gear_gear_update(void) {

}