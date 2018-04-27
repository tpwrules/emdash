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

// TODO: insert other definitions and declarations here

void SysTick_Handler(void) {
	// call the application 10ms timer interrupt
	app_timer_interrupt();
}

int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#endif


    __disable_irq();

    // initialize GPIO
    Chip_GPIO_Init(LPC_GPIO);

    // configure SysTick timer to fire every 10ms
    SysTick_Config(SystemCoreClock/100);

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
