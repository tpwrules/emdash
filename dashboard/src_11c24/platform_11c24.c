#include <stdint.h>

#include "chip.h"
#include "cmsis.h"

uint32_t cycles_asleep = 0;

void interrupt_wait(void) {
    // cycles before sleep
    uint32_t start = SysTick->VAL;
    __WFI(); // do the waiting
    uint32_t end = SysTick->VAL;
    // we won't miss a reload since the interrupt would wake us up
    if (end > start)
        start += SysTick->LOAD;
    cycles_asleep += (start - end);
    __enable_irq(); // enable interrupts to let the pending one happen
}