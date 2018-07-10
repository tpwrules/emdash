#ifndef PLATFORM_11C24_H
#define PLATFORM_11C24_H

#include <stdint.h>

#include "cmsis.h"

// define the interrupt interface routines
#define interrupt_disable() (__disable_irq())
#define interrupt_enable() (__enable_irq())

// must be called with interrupts disabled to avoid waiting forever
void interrupt_wait(void);

void SysTick_Handler(void);

#endif