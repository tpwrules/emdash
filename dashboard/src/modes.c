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

    scr_draw_text(SCR_TEXT_ADDR(0, 30, 4), "Plate:???%");
    scr_draw_text(SCR_TEXT_ADDR(0, 30, 5), "Pedal:???%");

    // set can messages to new so that they will be redrawn
    interrupt_disable();
    CV_RENEW(cv_ath);
    CV_RENEW(cv_pclutch);
}

 void modes_m1_ath_update(uint32_t val) {
    char str[10];
    if (app_mode_change_func == M1_MODE_FUNC) {
        val = (val + 50)/100;
        sprintf(str, "%3u", (unsigned int)val);
        scr_draw_text(SCR_TEXT_ADDR(0, 36, 4), str);
    }
 }

 void modes_m1_pclutch_update(uint32_t val) {
    char str[10];
    if (app_mode_change_func == M1_MODE_FUNC) {
        val /= 20;
        sprintf(str, "%2u,%u",
            (unsigned int)(val/10), (unsigned int)(val%10));
        scr_draw_text(SCR_TEXT_ADDR(0, 33, 2), str);
    }
 }
