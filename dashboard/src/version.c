// this file displays the versions of the dashboard
// and wheel on the right area of the screen

#include <stdio.h>

#include "platform.h"
#include "version.h"
#include "app.h"
#include "canvar.h"
#include "screen.h"
#include "modes.h"
#include "../misc/build_version.h"

void version_init(void) {
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

    // set the first modal page as the next one
    app_next_mode_func = modes_m1_init;

    // set can messages to new so that they will be redrawn
    interrupt_disable();
    if (cv_wb_version_commit.st != CV_ST_INVALID)
        cv_wb_version_commit.st = CV_ST_NEW;
    if (cv_wb_version_build.st != CV_ST_INVALID)
        cv_wb_version_build.st = CV_ST_NEW;
    interrupt_enable();
}

void version_wb_commit_update(uint32_t val) {
    char str[20];
    sprintf(str, "%08x", val);
    scr_draw_text(SCR_TEXT_ADDR(0, 32, 5), str);
}

void version_wb_build_update(uint32_t val) {
    char str[20];
    sprintf(str, "%010u", val);
    scr_draw_text(SCR_TEXT_ADDR(0, 30, 6), str);
}