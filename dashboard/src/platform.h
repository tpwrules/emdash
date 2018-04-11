#ifndef PLATFORM_H
#define PLATFORM_H

// include the headers that every file needs
#include <inttypes.h>

// include the platform-specific interface file
#ifdef PLATFORM_PC
#include "platform_pc.h"
#endif

#endif