/*
===============================================================================
 Name        : boot_11c24.c
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

#include "bootload.h"
#include "can_hw.h"

// TODO: insert other definitions and declarations here
int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
    // Set the LED to the state of "On"
    Board_LED_Set(0, true);
#endif
#endif

    // initialize hardware
    can_hw_init();
    // configure systick to fire every millisecond
    // configure reload register
    SysTick->LOAD = ((SystemCoreClock/1000) & SysTick_LOAD_RELOAD_Msk)-1;
    // initialize the counter itself
    SysTick->VAL = 0;
    // and turn it on
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;

    // run the bootloader
    bootload();

    return 0;
}
