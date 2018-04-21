#include "platform.h"
#include "app.h"
#include "screen.h"
#include "canvar.h"
#include "warn.h"
#include "drive.h"
#include "version.h"

#include <stdio.h>

volatile int timer_val = 0;

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
    while (timer_val < 120);

    // now clear and build the main screen
    scr_clear_page(false, 0);
    scr_clear_page(true, 0);

    // initialize the various display modules
    drive_init();
    warn_init();
    version_init();

    while (1) {
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

        uint32_t timer_now = timer_val;
        interrupt_enable();
        // update the drive blink timers
        drive_blink(timer_now);

        interrupt_disable();
        interrupt_wait();
    }
}

void app_timer_interrupt(void) {
    timer_val++;
}

void app_wb_dash_mode_update(uint32_t val) {
    
}
