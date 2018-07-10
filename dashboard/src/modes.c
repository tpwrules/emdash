// this file draws the display for the various modes
// so far:
//  Mode 1:
//      * throttle position
//      * gas pedal position
//      * clutch pressure

#include <stdio.h>
#include <stdbool.h>

#include "platform.h"
#include "modes.h"
#include "app.h"
#include "canvar.h"
#include "screen.h"

#define M1_MODE_FUNC (modes_m1_change)

void modes_m1_change(bool next) {
    if (next) {
        // set the next mode
        app_mode_change_func = cv_status_mode_change;
        return;
    }

    // draw the placeholder values
    scr_draw_text(SCR_TEXT_ADDR(0, 25, 2), "Clutch: ??,?bar");

    scr_draw_text(SCR_TEXT_ADDR(0, 32, 4), "ath:???%");
    scr_draw_text(SCR_TEXT_ADDR(0, 32, 5), "aps:???%");

    // set can messages to new so that they will be redrawn
    interrupt_disable();
    CV_RENEW(cv_ath);
    CV_RENEW(cv_aps);
    CV_RENEW(cv_pclutch);
}

void modes_m1_ath_update(uint32_t val) {
    static uint32_t disp_val = 0;
    char str[10];
    if (app_mode_change_func == M1_MODE_FUNC) {
        disp_val = hysteresis_div(disp_val, val, 100);
        sprintf(str, "%3u", (unsigned int)disp_val);
        scr_draw_text(SCR_TEXT_ADDR(0, 36, 4), str);
    }
}

void modes_m1_aps_update(uint32_t val) {
    static uint32_t disp_val = 0;
    char str[10];
    if (app_mode_change_func == M1_MODE_FUNC) {
        disp_val = hysteresis_div(disp_val, val, 100);
        sprintf(str, "%3u", (unsigned int)disp_val);
        scr_draw_text(SCR_TEXT_ADDR(0, 36, 5), str);
    }
}

void modes_m1_pclutch_update(uint32_t val) {
    static uint32_t disp_val = 0;
    char str[10];
    if (app_mode_change_func == M1_MODE_FUNC) {
        disp_val = hysteresis_div(disp_val, val, 20);
        sprintf(str, "%2u,%u",
            (unsigned int)(disp_val/10), (unsigned int)(disp_val%10));
        scr_draw_text(SCR_TEXT_ADDR(0, 33, 2), str);
    }
}
