#include "platform.h"
#include "app.h"
#include "screen.h"
#include "canvar.h"
#include "warn.h"
#include "drive.h"
#include "version.h"
#include "limits.h"

#include <stdio.h>
#include <stdbool.h>

volatile int timer_val = 0;
volatile static int timer_was_updated = 0;

// set to 1 the first time the mode is switched
// to disable the auto switch at beginning
static int mode_was_ever_switched = 0;

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

#ifndef PLATFORM_PC
    // if we are on real hardware, we need to decompress the font
    // into display RAM
    scr_draw_pic(0x7800, PIC_ID_FONT_6X8, false);
#endif

    // turn on interrupts
    interrupt_enable();
    // wait a bit of time for the splash to be shown
    while (timer_val < LIM_BOOT_SPLASH_TIME);

    // now clear and build the main screen
    scr_clear_page(false, 0);
    scr_clear_page(true, 0);

    // initialize the main display modules
    drive_init();
    warn_init();

    // show the version mode
    app_mode_change_func = version_mode_change;
    // and now show it
    app_show_next_mode();
    mode_was_ever_switched = 0;

    while (1) {
        // switch away from version mode if a certain
        // amount of time has elapsed and the user hasn't
        // switched modes themselves
        if (!mode_was_ever_switched && timer_val >= LIM_VERSION_DISP_TIME) {
            app_mode_change_func(true);
            app_show_next_mode();
        }

        interrupt_disable();

        if (canvar_was_updated) {
            canvar_was_updated = 0;
            for (uint8_t vi=0; vi<CANVAR_NUM_VARS; vi++) {
                // pull value and state while interrupts are disabled
                uint32_t val = canvar_states[vi].val;
                uint8_t st = canvar_states[vi].st;
                // is this value new?
                if (st == CV_ST_NEW) {
                    // well now it's not
                    canvar_states[vi].st = CV_ST_SAME;
                    // call the callback with interrupts enabled
                    // so that work can get done in the background
                    interrupt_enable();
                    canvar_defs[vi].callback(val);
                    interrupt_disable();
                }
            }
        }

        if (timer_was_updated) {
            timer_was_updated = 0;

            uint32_t timer_now = timer_val;

            interrupt_enable();
            // update the drive blink timers
            drive_blink(timer_now);
            interrupt_disable();
        }

        if (!canvar_was_updated && !timer_was_updated) {
            interrupt_wait();
        } else {
            interrupt_enable();
        }
    }
}

void app_timer_interrupt(void) {
    timer_was_updated = 1;
    timer_val++;
}

void app_wb_dash_mode_update(uint32_t val) {
    // go to next mode if button is pressed
    if (val) {
        // update the mode change func pointer
        // by asking the current function to update it
        app_mode_change_func(true);
        app_show_next_mode();
    }
}

app_mode_t app_mode_change_func;

void app_show_next_mode(void) {
    mode_was_ever_switched = 1;

    // erase the modal area
    for (int r=2; r<7; r++)
        scr_draw_text(SCR_TEXT_ADDR(0, 25, r), "               ");
    scr_draw_rect(SCR_PIXEL_ADDR(0, 19*8, 16), 11*8, 5*8, 0);

    // call the change func to draw the screen
    app_mode_change_func(false);

    // assume it changed some CAN stuff, so claim that was updated
    canvar_was_updated = 1;
}

void app_blank_mode(bool next) {
    // mode that just shows a blank area in case
    // it's distracting or smth
    if (next) {
        app_mode_change_func = version_mode_change;
    }
}

// part of CAN status page (in canvar.c)
void app_cpu_idle_percent_update(uint32_t val) {
    char str[8];
    if (app_mode_change_func == cv_status_mode_change) {
        sprintf(str, "%3u", (unsigned int)(100-val));
        scr_draw_text(SCR_TEXT_ADDR(0, 36, 6), str);
    }
}