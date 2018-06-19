// this file displays the versions of the dashboard
// and wheel on the right area of the screen

#include <stdio.h>
#include <stdbool.h>

#include "platform.h"
#include "version.h"
#include "app.h"
#include "canvar.h"
#include "screen.h"
#include "modes.h"
#include "../src_gen/build_version.h"

#define OUR_MODE_FUNC (version_mode_change)

void version_mode_change(bool next) {
    if (next) {
        // set the next mode
        app_mode_change_func = modes_m1_change;
        return;
    }

    // draw the dashboard version
    char str[20];
    scr_draw_text(SCR_TEXT_ADDR(0, 27, 2), "FW VERSIONS");
    sprintf(str, "Dash: %08x", BUILD_VERSION_COMMIT);
    scr_draw_text(SCR_TEXT_ADDR(0, 26, 3), str);
    sprintf(str, "20%010u", BUILD_VERSION_TIME);
    scr_draw_text(SCR_TEXT_ADDR(0, 28, 4), str);

    // and put placeholders for the wheel version
    // we can't draw it until it comes in over CAN
    scr_draw_text(SCR_TEXT_ADDR(0, 26, 5), "Wheel:????????");
    scr_draw_text(SCR_TEXT_ADDR(0, 28, 6), "20??????????");

    // set can messages to new so that they will be redrawn
    interrupt_disable();
    CV_RENEW(cv_wb_version_commit);
    CV_RENEW(cv_wb_version_build);
}

void version_wb_commit_update(uint32_t val) {
    char str[20];
    if (app_mode_change_func == OUR_MODE_FUNC) {
        sprintf(str, "%08x", (unsigned int)val);
        scr_draw_text(SCR_TEXT_ADDR(0, 32, 5), str);
    }
}

void version_wb_build_update(uint32_t val) {
    char str[20];
    if (app_mode_change_func == OUR_MODE_FUNC) {
        sprintf(str, "%010u", (unsigned int)val);
        scr_draw_text(SCR_TEXT_ADDR(0, 30, 6), str);
    }
}