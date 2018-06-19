#ifndef PLATFORM_PC_H
#define PLATFORM_PC_H

// interrupt interface routines
extern void (*interrupt_disable)(void);
extern void (*interrupt_enable)(void);
// must be called with interrupts disabled to avoid waiting forever
// returns with interrupts enabled
extern void (*interrupt_wait)(void);

#endif