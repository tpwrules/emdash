// this file draws the display for the various modes
// so far:
//  Mode 1:
//      * throttle position
//      * gas pedal position
//      * clutch pressure

#include "platform.h"
#include "modes.h"
#include "app.h"
#include "canvar.h"
#include "screen.h"

#include <stdio.h>

#define NEXT_MODE (app_blank_mode)

void modes_m1_init(void) {
    // draw the placeholder values
    scr_draw_text(SCR_TEXT_ADDR(0, 25, 2), "Clutch: ????bar");

    scr_draw_text(SCR_TEXT_ADDR(0, 30, 4), "Plate:???%");
    scr_draw_text(SCR_TEXT_ADDR(0, 30, 5), "Pedal:???%");

    // set the next mode
    app_next_mode_func = NEXT_MODE;

    // set can messages to new so that they will be redrawn
    interrupt_disable();
    if (cv_ath.st != CV_ST_INVALID)
        cv_ath.st = CV_ST_NEW;
    if (cv_pclutch.st != CV_ST_INVALID)
        cv_pclutch.st = CV_ST_NEW;
    interrupt_enable();
}

 void modes_m1_ath_update(uint32_t val) {
    char str[10];
    if (app_next_mode_func == NEXT_MODE) {
        sprintf(str, "%3d", val);
        scr_draw_text(SCR_TEXT_ADDR(0, 36, 4), str);
    }
 }

 void modes_m1_pclutch_update(uint32_t val) {
    char str[10];
    if (app_next_mode_func == NEXT_MODE) {
        sprintf(str, "%4d", val);
        scr_draw_text(SCR_TEXT_ADDR(0, 33, 2), str);
    }
 }