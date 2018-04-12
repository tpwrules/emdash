#include "platform.h"
#include "app.h"

#include <stdio.h>

volatile int timer_val = 0;
volatile uint16_t rpm = 0;

void app_entry() {
    printf("we made it!\n");
    char text[50];
    while (1) {
        sprintf(text, "amount of seconds: %d", timer_val);
        scr_draw_text(0, 0, text, timer_val & 1);
        sprintf(text, "current rpm: %d", rpm);
        scr_draw_text(0, 1, text, 0);
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