/*
===============================================================================
 Name        : dash_11c24.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here

#include "../src/app.h"
#include "../src/canvar.h"
#include "../src_11c24/t6963.h"
#include "../src_11c24/can_log.h"
#include "../src_11c24/can_hw.h"

// TODO: insert other definitions and declarations here

uint32_t systicks = 0;

#ifdef CAN_LOG_DISPLAY_ENABLED
static const can_log_entry_t *curr_log_entry = &can_log_entries[0];
#endif

void SysTick_Handler(void) {
    systicks++;
	// call the application 10ms timer interrupt
	app_timer_interrupt();

    // play back can log if allowed
#ifdef CAN_LOG_DISPLAY_ENABLED
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

int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#endif


    __disable_irq();

    // initialize GPIO
    Chip_GPIO_Init(LPC_GPIO);

    // initialize the lcd controller
    lcd_init();

    // configure SysTick timer to fire every 10ms
    SysTick_Config(SystemCoreClock/100);

    // initialize CAN hardware
#ifndef CAN_LOG_DISPLAY_ENABLED
    can_hw_init();
#endif

    app_entry();

    // TODO: insert code here

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        i++ ;
    }
    return 0 ;
}
