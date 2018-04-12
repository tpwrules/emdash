#include "platform.h"
#include "app.h"

#include <stdio.h>

volatile int timer_val = 0;

void app_entry() {
    printf("we made it!\n");
    char text[50];
    while (1) {
        sprintf(text, "amount of seconds: %d", timer_val);
        scr_draw_text(0, 0, text, timer_val & 1);
        interrupt_wait();
    }
}

void app_timer_interrupt() {
    timer_val++;
}