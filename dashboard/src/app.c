#include "platform.h"
#include "app.h"

#include <stdio.h>

volatile int timer_val = 0;
volatile uint16_t rpm = 0;

void app_entry() {
    // draw RPM border
    scr_draw_rect(0, 7, 240-56, 1, 0);
    scr_draw_rect(240-56, 0, 1, 8, 0);
    // draw RPM text
    scr_draw_text(31, 0, "RPM:", 0);

    // and gear indicator
    scr_draw_pic(13, 16, 0, 0);

    char text[50];
    uint16_t old_rpm = 65535;
    while (1) {
        if (rpm > 7800) {
            // start flashing gear as a warning
            if (timer_val % 20 == 0) {
                scr_draw_pic(13, 16, 0, timer_val % 40 < 20);
            }
        } else if (old_rpm > 7800) {
            // reset gear
            scr_draw_pic(13, 16, 0, 0);
        }

        if (rpm != old_rpm) {
            // erase RPM bar
            scr_draw_rect(0, 0, 240-56, 7, 1);
            // calculate new position and draw bar
            uint32_t bar_rpm = rpm;
            if (bar_rpm > 12000) {
                bar_rpm = 12000;
            }
            scr_draw_rect(0, 0, bar_rpm*(240-56)/12000, 7, 0);

            sprintf(text, "%5d", rpm);
            scr_draw_text(35, 0, text, 0);
            old_rpm = rpm;
        }

        interrupt_wait();
    }
}

void app_timer_interrupt() {
    timer_val++;
}

void app_can_interrupt(uint32_t msgid, uint8_t dlc, uint8_t *data) {
    if (msgid == 0x121) {
        rpm = data[3] << 8 | data[2];
    }
}