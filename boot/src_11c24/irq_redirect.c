// redirects for all valid IRQs
// note that WAKEUP_IRQHandler is redirected only once!
// to PIO0_0's call. This is not a problem in the default LPC code

#include "irq_redirect.h"

IRQ_REDIRECT(NMI_Handler, 2)
IRQ_REDIRECT(HardFault_Handler, 3)
IRQ_REDIRECT(SVC_Handler, 11)
IRQ_REDIRECT(PendSV_Handler, 14)
IRQ_REDIRECT(SysTick_Handler, 15)

IRQ_REDIRECT(WAKEUP_IRQHandler, 16)
IRQ_REDIRECT(CAN_IRQHandler, 29)
IRQ_REDIRECT(SSP1_IRQHandler, 30)
IRQ_REDIRECT(I2C_IRQHandler, 31)

// IRQs >= 32 require different macro
IRQ_REDIRECT2(TIMER16_0_IRQHandler, 32)
IRQ_REDIRECT2(TIMER16_1_IRQHandler, 33)
IRQ_REDIRECT2(TIMER32_0_IRQHandler, 34)
IRQ_REDIRECT2(TIMER32_1_IRQHandler, 35)

IRQ_REDIRECT2(SSP0_IRQHandler, 36)
IRQ_REDIRECT2(UART_IRQHandler, 37)

IRQ_REDIRECT2(ADC_IRQHandler, 40)
IRQ_REDIRECT2(WDT_IRQHandler, 41)
IRQ_REDIRECT2(BOD_IRQHandler, 42)

IRQ_REDIRECT2(PIOINT3_IRQHandler, 44)
IRQ_REDIRECT2(PIOINT2_IRQHandler, 45)
IRQ_REDIRECT2(PIOINT1_IRQHandler, 46)
IRQ_REDIRECT2(PIOINT0_IRQHandler, 47)