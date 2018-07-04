#ifndef SYSTEM_IDS_H
#define SYSTEM_IDS_H

// this file defines the system IDs for the
// places this bootloader is deployed
// you must uncomment the correct one before programming the bootloader

//#define CURR_SYSTEM_ID (1) // dashboard
//#define CURR_SYSTEM_ID (2) // wheelboard

#ifndef CURR_SYSTEM_ID
#error "system ID not defined!"
#endif

#endif