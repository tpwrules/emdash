#ifndef CAN_HW_H
#define CAN_HW_H

#include <stdbool.h>

void can_hw_init(void);

void CAN_IRQHandler(void);

extern bool can_busoff_happened;

#endif