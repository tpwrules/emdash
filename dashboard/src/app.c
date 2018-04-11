#include "platform.h"
#include "app.h"

#include <stdio.h>

void app_entry() {
    printf("we made it!\n");

    while (1) {
        interrupt_wait();
        printf("looped\n");
    }
}

void app_timer_interrupt() {
    printf("timer interrupted\n");
}