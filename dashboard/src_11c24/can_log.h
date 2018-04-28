#ifndef CAN_LOG_H
#define CAN_LOG_H

#include "../src/platform.h"

#ifndef PLATFORM_PC
#define CAN_LOG_DISPLAY_ENABLED
#endif

typedef struct {
    uint32_t time; // 10ms units
    uint16_t id;
    uint8_t dlc;
    uint8_t data[8];
} can_log_entry_t;

#ifdef CAN_LOG_DISPLAY_ENABLED
extern const can_log_entry_t can_log_entries[];
#endif

#endif