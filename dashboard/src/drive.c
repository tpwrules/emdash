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
#include "limits.h"

void drive_init(void) {
    // draw RPM border
    scr_draw_rect(SCR_BYTE_ADDR(0, 0, 6), 240-60+1, 1, 1);
    scr_draw_rect(SCR_BYTE_ADDR(0, (240-60)/6, 0), 1, 6, 1);
    // draw RPM text on normal and inverted screen
    scr_draw_text(SCR_TEXT_ADDR(0, 31, 0), "RPM:?????");
    scr_draw_text(SCR_TEXT_ADDR(1, 31, 0), "RPM:?????");

    scr_draw_text(SCR_TEXT_ADDR(0, 17, 1), "???kph");

    // second page is used for flashing when to upshift
    // fill it with black
    scr_draw_rect(SCR_BYTE_ADDR(1, 0, 0), 240, 64, 1);

    // drive mode text placeholders
    scr_draw_text(SCR_TEXT_ADDR(0, 18, 7), "TC??");

    // draw upshift marker on RPM bar
    scr_draw_text(SCR_TEXT_ADDR(0, 
        LIM_UPSHIFT_BLINK_RPM_START*((240-60)/6)/LIM_RPM_BAR_MAX, 0),
        "|"); // vertical bar
}

static uint16_t old_rpm = 0;

void drive_blink(uint32_t timer_val) {
    // manage blinking the screen

    // countdown to reverse blink state
    static uint32_t blink_ctr = 0;
    // 1 if screen is inverted for blinking
    static uint8_t inverted = 0;
    // 1 if actively blinking
    static uint8_t blinking = 0;

    static uint32_t last_timer_val = 0;

    // update if we should be blinking or not based on RPM
    if (!blinking && old_rpm >= LIM_UPSHIFT_BLINK_RPM_START) {
        blinking = 1;
        inverted = 0;
        blink_ctr = 0;
    } else if (blinking && old_rpm <= LIM_UPSHIFT_BLINK_RPM_STOP) {
        blinking = 0;
    }

    uint32_t dt = timer_val - last_timer_val;
    last_timer_val = timer_val;

    // subtract passed time from counter
    // (this function might not be called for every timer_val change!)
    if (dt > blink_ctr)
        blink_ctr = 0;
    else
        blink_ctr -= dt;
    
    if (blink_ctr == 0) {
        if (!inverted && !blinking)
            return;
        if (inverted) {
            // switch to main pages
            scr_show_page(false, 0);
            scr_show_page(true, 0);
        } else {
            // switch to inverted pages
            scr_show_page(false, 1);
            scr_show_page(true, 1);
        }
        inverted = !inverted;
        blink_ctr = LIM_UPSHIFT_BLINK_PERIOD/2;
    }
}

void drive_rpm_update(uint32_t val) {
    static uint8_t old_bar_val = 0;

    uint16_t rpm = (uint16_t)val;

    char text[10];

    // calculate new position and draw bar
    uint32_t bar_rpm = rpm;
    if (bar_rpm > LIM_RPM_BAR_MAX) {
        bar_rpm = LIM_RPM_BAR_MAX;
    }
    uint8_t bar_val = bar_rpm*(240-60)/LIM_RPM_BAR_MAX;

    if (bar_val < old_bar_val) {
        uint8_t col = bar_val/6;
        // erase up to the byte of the new val
        scr_draw_rect(SCR_BYTE_ADDR(0, col, 0), old_bar_val-(col*6), 6, 0);
        // let next statement take care of finishing it
        old_bar_val = col*6;
    }
    if (bar_val > old_bar_val) {
        uint8_t col = old_bar_val/6;
        scr_draw_rect(SCR_BYTE_ADDR(0, col, 0), bar_val-(col*6), 6, 1);
        old_bar_val = bar_val;
    }

    sprintf(text, "%5d", rpm);
    scr_draw_text(SCR_TEXT_ADDR(0, 35, 0), text);
    // also put it on the inverted screen
    scr_draw_text(SCR_TEXT_ADDR(1, 35, 0), text);

    old_rpm = rpm;
    old_bar_val = bar_val;
}

void drive_gear_update(uint32_t val) {
    if (val < 5) {
        // draw gear on main page
        scr_draw_pic(SCR_BYTE_ADDR(0, 17, 16), PIC_ID_GEAR_NEUTRAL+val, 0);
        // and inverted on inverted page
        scr_draw_pic(SCR_BYTE_ADDR(1, 17, 16), PIC_ID_GEAR_NEUTRAL+val, 1);
    }
}

void drive_speed_update(uint32_t val) {
    char str[8];
    val /= 100;
    sprintf(str, "%3u", (unsigned int)val);
    scr_draw_text(SCR_TEXT_ADDR(0, 17, 1), str);
}

void drive_B_autoshiften_ems_update(uint32_t val) {
    if (val) {
        scr_draw_text(SCR_TEXT_ADDR(0, 18, 6), "AUTO");
    } else {
        scr_draw_text(SCR_TEXT_ADDR(0, 18, 6), "    ");
    }
}

void drive_B_launch_update(uint32_t val) {
    if (val) {
        scr_draw_text(SCR_TEXT_ADDR(0, 24, 1), "LAUNCH");
    } else {
        scr_draw_text(SCR_TEXT_ADDR(0, 24, 1), "      ");
    }
}

void drive_wb_upshift_update(uint32_t val) {
    if (val) {
        scr_draw_pic(SCR_BYTE_ADDR(0, 22, 16), PIC_ID_UPSHIFT_BTN, 0);
    } else {
        scr_draw_rect(SCR_BYTE_ADDR(0, 22, 16), 16, 15, 0);
    }
}

void drive_wb_downshift_update(uint32_t val) {
    if (val) {
        scr_draw_pic(SCR_BYTE_ADDR(0, 22, 32), PIC_ID_DOWNSHIFT_BTN, 0);
    } else {
        scr_draw_rect(SCR_BYTE_ADDR(0, 22, 32), 16, 15, 0);
    }
}

void drive_wb_radio_update(uint32_t val) {
    if (val) {
        scr_draw_pic(SCR_BYTE_ADDR(0, 22, 48), PIC_ID_RADIO, 0);
    } else {
        scr_draw_rect(SCR_BYTE_ADDR(0, 22, 48), 16, 15, 0);
    }
}

void drive_wb_traction_knob_update(uint32_t val) {
    char str[10];
    sprintf(str, "%02u", (unsigned int)val);
    scr_draw_text(SCR_TEXT_ADDR(0, 20, 7), str);
}