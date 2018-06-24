![boot screen](https://github.com/tpwrules/emdash/raw/master/dashboard/docs/boot_screen.png)

## Introduction

Welcome to the user manual for the Einstein Motorsport Dashboard. The dashboard is designed to be easy to use, and customizable for any application. This User Manual describes how to use the dashboard's current firmware. You may also wish to read the [Programmer's Manual](https://github.com/tpwrules/emdash/blob/master/dashboard/docs/programmer%20manual.md) to understand how the firmware works, or the [Customizer's Manual](https://github.com/tpwrules/emdash/blob/master/dashboard/docs/customizer%20manual.md) to understand how to modify it.

## Main Screen

![main screen](https://github.com/tpwrules/emdash/raw/master/dashboard/docs/main_screen.png)

The main screen is divided into three sections:
* Car Information (green)
* Driver Information (blue)
* Mode Area (red)

### Car Information

This sections displays the measurements and status of the car's systems. Warning icons are displayed when certain thresholds are exceeded. When an icon is displayed, the corresponding measurement is drawn with inverted color.

Display of the section is handled by `src/warn.c`.

#### Measurement Description
The meaning of each measurement icon is described below. The table describes the icons in left to right, top to bottom order. The "Variable" column tells which canvar is monitored. The "Limit" column is the constant in `src/limits.h` which controls the value at which it should happen.

Variable | Limit | Displayed when
-------- | ----- | --------------
poil | LIM_OIL_PRESSURE_MIN | Oil pressure is too low.
tmot2 | LIM_WATER_TEMP_MAX | Cooling water temperature is too high.
pfuel | LIM_FUEL_PRESSURE_MIN | Fuel pressure is too low.
ub | LIM_BATTERY_MIN | Battery voltage is too low (as measured by ECU).
toil | LIM_OIL_TEMP_MAX | Oil temperature is too high.
tmot | LIM_BLOCK_TEMP_MAX | Engine temperature is too high.
tfuel | LIM_FUEL_TEMP_MAX | Fuel temperature is too high.
toil | LIM_OIL_TEMP_MIN | Engine oil temperature is too low.

### Driver Information

This area displays status and measurements important to the driver. Display of this section is handled by `src/drive.c`.

The following measurements are displayed:

* The RPM bar and current engine RPM (`nmot`) are displayed the top of the screen. When the current RPM exceeds the optimal RPM (illustrated by the black line), the entire screen flashes to prompt the driver to upshift. This is configurable in `src/limits.h` as well.
* Current gear (`gear`) is displayed in the center of the screen.
* If the upshift paddle on the wheel is pressed (`wb_upshift != 0`), an up arrow is displayed next to the gear indicator.
* If the downshift paddle on the wheel is pressed (`wb_downshift != 0`), a down arrow is displayed next to the gear indicator.
* If automatic shifting is enabled (`B_autoshiften_ems != 0`), AUTO is displayed below the gear indicator.
* Current speed (`speed`) is displayed above the gear indicator.
* If launch control is active (`B_launch != 0`), LAUNCH is displayed next to the current speed.
* If the radio button on the wheel is pressed (`wb_radio != 0`), a headset icon is displayed.
* Current traction control level (`wb_traction_knob`) is displayed at the bottom center of the screen.

### Mode Area

This area displays various other pieces of information, in several different modes. The mode is switched using the dash mode button on the wheel. The available modes are described below, in selection order.

CAN Status mode is handled in `canvar.c`, Firmware Version mode is handled in `src/version.c`, and all other modes are handled in `src/modes.c`.

#### Firmware Version

This page displays the firmware versions of the dashboard and wheelboard. The first number is the Git commit hash the firmware was built from, and the second number is the time it was built in YYYYMMddhhmm format. It is displayed briefly at startup, then the dashboard automatically switches to the next mode.

#### Clutch and Throttle

This page displays the clutch system pressure (`pclutch`). It also displays the position of the throttle pedal (???) and the throttle plate (`ath`).

#### CAN Status

This page displays the status of the CANBUS engine. If there is an error, this page is automatically shown.