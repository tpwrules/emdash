![boot screen](https://github.com/tpwrules/emdash/raw/master/dashboard/docs/boot_screen.png)

## Introduction

Welcome to the user manual for the Einstein Motorsport Dashboard. The dashboard is designed to be easy to use and customize. This User Manual shows you how to use the dashboard. Customizing it is covered elsewhere.

## Main Screen

![main screen](https://github.com/tpwrules/emdash/raw/master/dashboard/docs/main_screen.png)

The main screen is divided into three areas:
* Car Information (green)
* Driver Information (blue)
* Misc. Information (red)

### Car Information

This area displays the status of the car systems. The following parameters are monitored: oil temperature and pressure, fuel temperature and pressure, motor temperature, and battery voltage. Warning icons illuminate when certain thresholds are exceeded. When an icon is illuminated, the corresponding measurement is drawn with inverted color.

#### Warning Icon Description
The meaning of each icon is described below. The table is in left to right, top to bottom order. The "Meaning" colummn describes when the warning icon illuminates and the "Limit" column is the constant in `the limits file` which controls the value at which it should happen.

Icon | Limit | Meaning
---- | ----- | -------
No. 1 | LIM_OIL_PRESSURE_MIN | Illuminates when oil pressure is too low
No. 2 | LIM_WATER_TEMP_MAX | Illuminates when cooling water temperature (Tmot2) is too high.
No. 3 | LIM_FUEL_PRESSURE_MIN | Illuminates when fuel pressure is too low
No. 4 | LIM_BATTERY_MIN | Illuminates when battery voltage is too low (as measured by ECU)
No. 5 | LIM_OIL_TEMP_MAX | Illuminates when oil temperature is too high
No. 6 | LIM_BLOCK_TEMP_MAX | Illuminates when engine temperature (Tmot) is too high.
No. 7 | LIM_FUEL_TEMP_MAX | Illuminates when fuel temperature is too high.
No. 8 | LIM_OIL_TEMP_MIN | Illuminates when engine oil temperature is too low.

### Driver Information

This area displays measurements important to the driver. The following measurements are displayed:

* The RPM bar and current engine RPM are displayed the top of the screen. When the current RPM exceeds the optimal RPM (illustrated by the black line), the entire screen flashes to prompt the driver to upshift. This is configurable in `the limits file` as well.
* Current gear is displayed in the center of the screen.
* If the upshift paddle on the wheel is pressed, an up arrow is displayed next to the gear indicator.
* If the downshift paddle on the wheel is pressed, a down arrow is displayed next to the gear indicator.
* If automatic shifting is enabled, AUTO is displayed below the gear indicator.
* Current speed is displayed above the gear indicator.
* If launch control is active, LAUNCH is displayed next to the current speed.
* If the radio button on the wheel is pressed, a headset icon is displayed.
* Current traction control level is displayed at the bottom center of the screen.

### Misc. Information

This area displayes several pages of miscellaneous information. The pages are switched using the dash mode button on the wheel. The available pages are described below, in selection order.

#### Firmware Version

This page displays the firmware versions of the dashboard and wheelboard. The first number is the Git commit hash the firmware was built from, and the second number is the time it was built in YYYYMMddhhmm format. It is displayed briefly at startup, then the dashboard automatically switches to the next page.

#### Clutch and Throttle

This page displays the clutch system pressure. It also displays the position of the throttle pedal and the throttle plate.

#### CAN Status

This page displays the status of the CANBUS engine. If there is an error, this page is automatically shown.