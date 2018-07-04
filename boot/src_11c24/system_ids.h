#ifndef SYSTEM_IDS_H
#define SYSTEM_IDS_H

// this file defines the system IDs for the
// places this bootloader is deployed
// you must uncomment the correct one before programming the bootloader

#include "bootload_integrate.h"

//#define CURR_SYSTEM_ID (BOOTLOAD_SYSTEM_ID_DASHBOARD)
//#define CURR_SYSTEM_ID (BOOTLOAD_SYSTEM_ID_WHEELBOARD)

#ifndef CURR_SYSTEM_ID
#error "system ID not defined!"
#endif

#endif