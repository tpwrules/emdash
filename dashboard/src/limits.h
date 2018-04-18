#ifndef LIMITS_H
#define LIMITS_H

// this file contains various limits and definitions for the display

// warn.c limits
// if the value is outside of the range,
// the corresponding light will be turned on

// minimum safe oil pressure, in bar
#define LIM_OIL_PRESSURE_MIN (50)

// maximum safe oil temperature, in C
#define LIM_OIL_TEMP_MAX (128)

// maximum safe water temperature, in C
#define LIM_WATER_TEMP_MAX (128)

// maximum safe block temperature, in C
#define LIM_BLOCK_TEMP_MAX (128)

// minimum safe fuel pressure, in bar
#define LIM_FUEL_PRESSURE_MIN (50)

// maximum safe fuel temperature, in C
#define LIM_FUEL_PRESSURE_MAX (128)

#endif