#include "platform.h"
#include "app.h"
#include "screen.h"
#include "canvar.h"
#include "warn.h"
#include "drive.h"
#include "version.h"
#include "limits.h"

#include <stdio.h>

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

    // set up version screen as next mode
    app_next_mode_func = version_init;
    // and now show it
    app_show_next_mode();
    mode_was_ever_switched = 0;

    while (1) {
        // switch away from version mode if a certain
        // amount of time has elapsed and the user hasn't done anything
        if (!mode_was_ever_switched && timer_val >= LIM_VERSION_DISP_TIME)
            app_show_next_mode();

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
                    if (canvar_defs[vi].callback) {
                        // call the callback without interrupts
                        // so that work can get done in the background
                        interrupt_enable();
                        canvar_defs[vi].callback(val);
                        interrupt_disable();
                    }
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
    if (val)
        app_show_next_mode();
}

app_mode_t app_next_mode_func;

void app_show_next_mode(void) {
    mode_was_ever_switched = 1;
    // erase the modal area
    for (int r=2; r<7; r++)
        scr_draw_text(SCR_TEXT_ADDR(0, 25, r), "               ");
    scr_draw_rect(SCR_PIXEL_ADDR(0, 19*8, 16), 11*8, 5*8, 0);

    // call next mode function
    app_next_mode_func();

    // assume it changed some CAN stuff, so claim it was updated
    canvar_was_updated = 1;
}

void app_blank_mode(void) {
    // mode that just sets up the next one
    // in case that area needs to be clear
    app_next_mode_func = version_init;
}