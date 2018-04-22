#ifndef PLATFORM_H
#define PLATFORM_H

// include the headers that every file needs
#include <inttypes.h>
#include <stdbool.h>

// define a macro so that a function prototype can be switched between
// a real function and a function pointer depending on if we're being
// compiled for PC

#ifndef PLATFORM_PC
#define PCFUNC(type, name) type name
#else
#define PCFUNC(type, name) extern type (*name)
#endif

// include the platform-specific interface file
#ifdef PLATFORM_PC
#include "../pc/platform_pc.h"
#endif

#ifdef PLATFORM_11C24
#include "../src_11c24/platform_11c24.h"
#endif

#endif