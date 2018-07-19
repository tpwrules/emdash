#ifndef IRQ_REDIRECT_H
#define IRQ_REDIRECT_H

// redirect an IRQ into the bootloaded code

#define IRQ_REDIRECT(handler, which) IRQ_REDIRECT_real(handler, (which*4))

#define IRQ_REDIRECT_real(handler, addr) \
__attribute__  ((naked, noreturn, section(".after_vectors")))\
void handler (void) {\
    __asm__("ldr r3, =0x1000\n\t"\
            "ldr r3, [r3, #" #addr "]\n\t"\
            "bx r3");\
}

// second version for address >= 128 (which first version cannot reach)
#define IRQ_REDIRECT2(handler, which) IRQ_REDIRECT_real(handler, (which*4)-0x80)

#define IRQ_REDIRECT2_real(handler, addr) \
__attribute__  ((naked, noreturn, section(".after_vectors")))\
void handler (void) {\
    __asm__("ldr r3, =0x1080\n\t"\
            "ldr r3, [r3, #" #addr "]\n\t"\
            "bx r3");\
}

#define IRQ_REDIRECT_PROTOTYPE(handler, which) void handler (void);


IRQ_REDIRECT_PROTOTYPE(NMI_Handler, 2)
IRQ_REDIRECT_PROTOTYPE(HardFault_Handler, 3)
IRQ_REDIRECT_PROTOTYPE(SVC_Handler, 11)
IRQ_REDIRECT_PROTOTYPE(PendSV_Handler, 14)
IRQ_REDIRECT_PROTOTYPE(SysTick_Handler, 15)

IRQ_REDIRECT_PROTOTYPE(WAKEUP_IRQHandler, 16)
IRQ_REDIRECT_PROTOTYPE(CAN_IRQHandler, 29)
IRQ_REDIRECT_PROTOTYPE(SSP1_IRQHandler, 30)
IRQ_REDIRECT_PROTOTYPE(I2C_IRQHandler, 31)

IRQ_REDIRECT_PROTOTYPE(TIMER16_0_IRQHandler, 32)
IRQ_REDIRECT_PROTOTYPE(TIMER16_1_IRQHandler, 33)
IRQ_REDIRECT_PROTOTYPE(TIMER32_0_IRQHandler, 34)
IRQ_REDIRECT_PROTOTYPE(TIMER32_1_IRQHandler, 35)

IRQ_REDIRECT_PROTOTYPE(SSP0_IRQHandler, 36)
IRQ_REDIRECT_PROTOTYPE(UART_IRQHandler, 37)

IRQ_REDIRECT_PROTOTYPE(ADC_IRQHandler, 40)
IRQ_REDIRECT_PROTOTYPE(WDT_IRQHandler, 41)
IRQ_REDIRECT_PROTOTYPE(BOD_IRQHandler, 42)

IRQ_REDIRECT_PROTOTYPE(PIOINT3_IRQHandler, 44)
IRQ_REDIRECT_PROTOTYPE(PIOINT2_IRQHandler, 45)
IRQ_REDIRECT_PROTOTYPE(PIOINT1_IRQHandler, 46)
IRQ_REDIRECT_PROTOTYPE(PIOINT0_IRQHandler, 47)


#endif