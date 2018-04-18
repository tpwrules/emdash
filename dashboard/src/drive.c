// this file handles the driving related variables
// this includes:
//  * RPM
//  * current gear
//  * current speed

#include <stdio.h>

#include "platform.h"
#include "canvar.h"
#include "drive.h"
#include "screen.h"

void drive_init(void) {
    // draw RPM border
    scr_draw_rect(SCR_PIXEL_ADDR(0, 0, 6), 240-56, 1, 1);
    scr_draw_rect(SCR_PIXEL_ADDR(0, 240-56, 0), 1, 7, 1);
    // draw RPM text
    scr_draw_text(SCR_TEXT_ADDR(0, 31, 0), "RPM:?????");

    scr_draw_text(SCR_TEXT_ADDR(0, 34, 1), "???kph");

    // second page is used for flashing when to upshift
    // fill it with black
    scr_draw_rect(SCR_PIXEL_ADDR(1, 0, 0), 240, 64, 1);
}

void drive_rpm_update(uint32_t val) {
    static uint16_t old_rpm = 0;
    static uint8_t old_bar_val = 0;

    uint16_t rpm = (uint16_t)val;

    char text[10];

    /*
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
    */

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
                bar_val-old_bar_val, 6, 3);
        } else if (bar_val < old_bar_val) {
            // take pixels away from the bar
            // left is black, middle and right are white
            scr_draw_rect(SCR_PIXEL_ADDR(0, bar_val, 0),
                old_bar_val-bar_val, 6, 2);
        }

        sprintf(text, "%5d", rpm);
        scr_draw_text(SCR_TEXT_ADDR(0, 35, 0), text);
        old_rpm = rpm;
        old_bar_val = bar_val;
    }
}

void drive_gear_update(uint32_t val) {
    if (val < 12) {
        scr_draw_pic(SCR_BYTE_ADDR(0, 13, 16), PIC_ID_GEAR_PARK+val, 0);
    }
}

void drive_speed_update(uint32_t val) {
    char str[8];
    sprintf(str, "%3d", val);
    scr_draw_text(SCR_TEXT_ADDR(0, 34, 1), str);
}
