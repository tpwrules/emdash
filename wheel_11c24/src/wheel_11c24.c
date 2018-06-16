/*
===============================================================================
 Name        : wheel_11c24.c
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
#include "../src_11c24/can_hw.h"
#include "../src_11c24/app.h"

// TODO: insert other definitions and declarations here

void SysTick_Handler(void) {
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

    // configure SysTick timer to fire every millisecond
    SysTick_Config(SystemCoreClock/1000);

    // initialize CAN hardware
    can_hw_init();

    app_entry();

    return 0;
}
