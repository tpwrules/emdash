Welcome to the manual for the Einstein Motorsport Wheelboard. The wheelboard is designed to be easy to use, and customizable for any application. This manual is divided into three sections. [Usage](#usage) describes how to use the wheelboard's hardware and current firmware. [Customizing](#customizing) describes how to customize the wheelboard. [Programming](#programming) describes the architecture of the firmware and the functions available to customizers.

# Usage

## Wiring

Input buttons should be wired between GND and the corresponding input pin. The traction control knob should be wired with the 0 side connected to GND, the 11 side connected to 3.3V, and the switch output connected to the corresponding input pin.

The current input assignments are as follows:

Input | Button | Message
----- | ------ | -------
A1 | Traction control knob | wb_traction_knob
A2 | Unused | N/A
A3 | Unused | N/A
A4 | Unused | N/A
B1 | Clutch | wb_clutch
B2 | Upshift | wb_upshift
B3 | Downshift | wb_downshift
B4 | Radio | wb_radio
B5 | Launch | wb_launch
C1 | Dash mode | wb_dash_mode
C2 | Lap | wb_lap
C3 | Autoshift | wb_autoshift
C4 | Unused | N/A
C5 | Unused | N/A

## Hardware

The wheelboard has three input ports: A (four pins), B (five pins), and C (five pins). All pins support input between 0V and 3.3V. Voltages outside this range may damage the wheelboard.

Each input has configurable pull-up and pull-down resistors. Pins on port A can also be read by a 10 bit analog-to-digital converter. All pins can be configured for output mode, but this functionality is not used in the current firmware or exposed to the CAN bus.

The inputs are connnected to the processor according to the following table:

Input | Processor Pin | ADC Channel
----- | ------------- | -----------
A1 | PIO0_11 | ADC_CH0
A2 | PIO1_0 | ADC_CH1
A3 | PIO1_1 | ADC_CH2
A4 | PIO1_2 | ADC_CH3
B1 | PIO2_8 | ADC unsupported
B2 | PIO0_6 | ADC unsupported
B3 | PIO0_7 | ADC unsupported
B4 | PIO0_8 | ADC unsupported
B5 | PIO0_9 | ADC unsupported
C1 | PIO2_1 | ADC unsupported
C2 | PIO0_3 | ADC unsupported
C3 | PIO1_8 | ADC unsupported
C4 | PIO0_2 | ADC unsupported
C5 | PIO2_7 | ADC unsupported



# Programming

This section explains how the firmware works and the functions available to customizers.

The following topics are covered:
* Application and Main Loop
* Button Processor
* Button Reading

## Application and Main Loop

The application receives the timer interrupt and contains the main loop. When the application starts up, the buttons are initialized by calling `br_read()`. Then, the main loop waits for interrupts.

When the timer interrupt is received every millisecond, the button processor `bp_process()` is called. Then, the CAN messages are transmitted, if necessary. The version message is sent every second and the button messages are sent as soon as they change, or every 50 milliseconds if there is no change.

The application code is contained in `src_11c24/app.c`.

## Button Processor

The button processor is the heart of the application. Every button has an unsigned 8 bit value representing the button's current state. When the timer elapses, the processor reads the new state of each button by calling its update function. It then debounces each button and transmits the new state, if any, on the CAN bus. All buttons are read every millisecond, so the time spent in button update functions cannot exceed one millisecond.

Buttons do not have assigned inputs. The update function for a button may read multiple inputs, or multiple update functions may read the same input.

### Debouncing

The debounce algorithm helps remove electrical and contact noise from the input. It operates on the button's current state (what is sent over CAN), the new state (what the processor measured this millisecond), and the previous new state (what the processor measured last millisecond). The algorithm waits until the button's new state has been consistent for a period of time before accepting it as the current state.

If the current state does not match the new state, and the new state is non-0 and matches the previous new state for 10 consecutive milliseconds (default debounce press time), the current state becomes the new state.

If the current state does not match the new state, and the new state is 0 and matches the previous new state for 50 consecutive milliseconds (default debounce release time), the current state becomes the new state.

The debounce press and release times are configurable per-button. Once the current state has changed, it is scheduled for immediate transmission on the CAN bus.

## Button Reading

Reading the value of the board inputs is done using hardware-specific functions for the LPC11C24's IOCON, GPIO, and ADC peripherals. Covering these functions is outside the scope of this documentation. You can consult the BLALAH for information on using the peripherals. The implemention of the traction knob may be useful as a reference for the ADC peripheral.

The input hardware for all buttons is initialized in `br_init()`. This function is called once when the board starts up. The button's input hardware is then read in the button's update function.

For the case of a "simple" button, macros are provided to handle initialization and updating. A "simple" button is defined as the following:

* The physical switch connects one input to GND when pressed.
* The physical switch disconnects that input when released (or connects it to 3.3V).
* The button's state is 1 when pressed and 0 when released.

If the button has an update function called `<update>` and the physical switch is connected to input `<pin>` (e.g. A3 or C5), then the following macros are available:

* `BR_SIMPLE_INIT(<update>, PIN_<pin>)` initializes the button's input. Put this macro in the `br_init()` function.
* `BR_SIMPLE(<update>, PIN_<pin>)` creates a button update function. Put this macro in the `button_read.c` file. 

# Customizing

This section contains the specific steps required to perform customizations to the firmware.

The following tasks are covered:

* Adding a Button

## Adding a Button

Button definitions are stored in `buttons/buttons.py` as Python objects. Adding a button is done by instantiating a Python `Button` object and adding it to the list of `buttons` in the file. If `<name>` is the button's name, then `btn_<name>` is the data structure which holds its value (a `button_state_t`) and `BTN_ID_<name in uppercase>` is defined as its ID in the data structure array.

The `Button` constructor has the following arguments:
* `name` is the name of the button.
* `msg_id` is the 11-bit CAN message ID which contains the button's state.
* `byte` is the byte within the message which contains the button's state.
* `update` is the C function to call to update this button.
* `debounce_press` is the debounce press time in milliseconds. Consult the Debouncing section.
* `debounce_release` is the debounce release time in milliseconds. Consult the Debouncing section.