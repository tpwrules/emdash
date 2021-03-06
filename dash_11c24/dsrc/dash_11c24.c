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
#include "../src_11c24/t6963.h"
#include "../src_11c24/can_log.h"
#include "../src_11c24/can_hw.h"

// TODO: insert other definitions and declarations here

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
    // (handler is in platform_11c24.c)
    SysTick_Config(SystemCoreClock/100);

    // initialize CAN hardware
#ifndef CAN_LOG_DISPLAY_ENABLED
    can_hw_init();
#endif

    app_entry();

    return 0;
}
