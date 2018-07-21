#ifndef LIMITS_H
#define LIMITS_H

// this file contains various limits and definitions for the dashboard

// warn.c limits
// if the value is outside of the range (larger or smaller),
// the corresponding light will be turned on

// minimum safe oil pressure, in 0.1 bar increments
#define LIM_OIL_PRESSURE_MIN (5) // 0.5bar

// maximum safe oil temperature, in 1 C increments
#define LIM_OIL_TEMP_MAX (120) // 120C

// minimum safe oil temperature, in 1 C increments
#define LIM_OIL_TEMP_MIN (60) // 60C

// maximum safe water temperature, in 1 C increments
#define LIM_WATER_TEMP_MAX (100) // 100C

// maximum safe block temperature, in 1 C increments
#define LIM_BLOCK_TEMP_MAX (110) // 110C

// minimum safe fuel pressure, in 0.1 bar increments
#define LIM_FUEL_PRESSURE_MIN (40) // 4bar

// maximum safe fuel temperature, in 1 C increments
#define LIM_FUEL_TEMP_MAX (50) // 50C

// minimum safe battery voltage, in 100 mV increments
#define LIM_BATTERY_MIN (120) // 12.0V


// drive.c limits

// maximum RPM of the RPM bar
// greater RPMs are still displayed as text
#define LIM_RPM_BAR_MAX (10000)
// RPM at which to start blinking for upshift
#define LIM_UPSHIFT_BLINK_RPM_START (8500)
// RPM at which to stop blinking for upshift
#define LIM_UPSHIFT_BLINK_RPM_STOP (8450)
// period of blinks in 10ms increments
#define LIM_UPSHIFT_BLINK_PERIOD (40)

// app.c limits

// time to display splash screen, timed from boot, in 10ms units
#define LIM_BOOT_SPLASH_TIME (200)

// time to display version mode, timed from boot, in 10ms units
#define LIM_VERSION_DISP_TIME (LIM_BOOT_SPLASH_TIME+300)

#endif