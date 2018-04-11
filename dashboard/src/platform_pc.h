#ifndef PLATFORM_PC_H
#define PLATFORM_PC_H

// interrupt interface routines
void (*interrupt_wait)();

// Python registers callbacks to implement most of the
// platform-specific stuff
// so define functions that accept these registrations
// and store them in the function pointers above

void pc_reg_interrupt_wait(void (*cb)());

#endif