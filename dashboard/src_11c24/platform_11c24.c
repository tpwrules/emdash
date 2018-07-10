#include <stdint.h>

#include "chip.h"
#include "cmsis.h"

#include "../src/app.h"
#include "../src/canvar.h"

uint32_t cycles_asleep = 0;

#ifdef CAN_LOG_DISPLAY_ENABLED
uint32_t systicks = 0;
static const can_log_entry_t *curr_log_entry = &can_log_entries[0];
#endif

void SysTick_Handler(void) {
    // call the application 10ms timer interrupt
    app_timer_interrupt();

    // inform the app of CPU usage every 500ms
    static uint32_t cpu_usage_timeout = 50;
    if (--cpu_usage_timeout == 0) {
        cpu_usage_timeout = 50;
        uint32_t percent = cycles_asleep * 100 / (48000000/2);
        cycles_asleep = 0;
        app_canvar_interrupt(CV_ID_NOBUS_CPU_IDLE_PERCENT, percent);
    }

    // play back can log if allowed
#ifdef CAN_LOG_DISPLAY_ENABLED
    systicks++;
    while (1) {
        // if dlc is 0xFF, the log is at the end
        if (curr_log_entry->dlc == 0xFF) {
            systicks = 0;
            curr_log_entry = &can_log_entries[0];
        }

        // check if it's time for this message yet
        if (curr_log_entry->time > systicks) break;

        // awesome, send it on
        app_can_interrupt(curr_log_entry->id,
            curr_log_entry->dlc,
            curr_log_entry->data);

        // and process next entry
        curr_log_entry++;
    }
#endif
}

void interrupt_wait(void) {
    // cycles before sleep
    uint32_t start = SysTick->VAL;
    __WFI(); // do the sleeping
    uint32_t end = SysTick->VAL;
    // SysTick->VAL counts down toward 0
    // we can't miss a reload since the interrupt would wake us up
    // the only possibilities are that it wraps around 0 or 1 times
    if (end > start) // handle wrapping around once
        start += SysTick->LOAD;
    cycles_asleep += (start - end);
    __enable_irq(); // enable interrupts to let the one that woke us up happen
}