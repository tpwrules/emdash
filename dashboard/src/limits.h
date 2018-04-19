#ifndef LIMITS_H
#define LIMITS_H

// this file contains various limits and definitions for the display

// warn.c limits
// if the value is outside of the range,
// the corresponding light will be turned on

// minimum safe oil pressure, in bar
#define LIM_OIL_PRESSURE_MIN (50) // 0.5bar

// maximum safe oil temperature, in C
#define LIM_OIL_TEMP_MAX (128) // 120C

// minimum safe oil temperature, in C
#define LIM_OIL_TEMP_MIN (64) // 60C

// maximum safe water temperature, in C
#define LIM_WATER_TEMP_MAX (128) // 100C

// maximum safe block temperature, in C
#define LIM_BLOCK_TEMP_MAX (128) // 110C

// minimum safe fuel pressure, in bar
#define LIM_FUEL_PRESSURE_MIN (50) // 4bar

// maximum safe fuel temperature, in C
#define LIM_FUEL_PRESSURE_MAX (128) // 50C

// minimum safe battery voltage, in V
#define LIM_BATTERY_MIN (13) // 12.8V


// drive.c limits

// RPM at which to start blinking for upshift
#define LIM_UPSHIFT_BLINK_RPM_START (7800)
// RPM at which to stop blinking for upshift
#define LIM_UPSHIFT_BLINK_RPM_STOP (7400)
// period of blinks in 10ms increments
#define LIM_UPSHIFT_BLINK_PERIOD (40)

#endif