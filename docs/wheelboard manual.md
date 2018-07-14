Welcome to the manual for the Einstein Motorsport Wheelboard. The wheelboard is designed to be easy to use, and customizable for any application. This manual is divided into three sections. [Usage](#usage) describes how to use the wheelboard's hardware and current firmware. [Customizing](#customizing) describes how to customize the wheelboard. [Programming](#programming) describes the architecture of the firmware and the functions available to customizers.

# Usage

## Wiring

Input buttons should be wired between GND and the corresponding input pin. The traction control knob should be wired with the 0 side connected to GND, the 11 side connected to 3.3V, and the switch output connected to the corresponding input pin.

The current input assignments are as follows:

Input | Button
----- | ------
A1 | Traction control knob
A2 | Unused
A3 | Unused
A4 | Unused
B1 | Clutch
B2 | Upshift
B3 | Downshift
B4 | Radio
B5 | Launch
C1 | Dash mode
C2 | Lap
C3 | Autoshift
C4 | Unused
C5 | Unused

## Hardware

The wheelboard has three input ports: A (four pins), B (five pins), and C (five pins). All pins support input between 0V and 3.3V in all cases. Voltages outside this range may damage the wheelboard.

Each input has configurable pull-up and pull-down resistors. Pins on port A can also be read by a 12 bit analog-to-digital converter. All pins can be configured for output mode, but this functionality is not used in the current firmware or exposed to the CAN bus.

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