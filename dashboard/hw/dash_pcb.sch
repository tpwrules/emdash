EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:nxp_can
LIBS:dash_pcb-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LPC11C24FBD48 U1
U 1 1 5ADCA005
P 5600 4100
F 0 "U1" H 4550 5550 50  0000 C CNN
F 1 "LPC11C24FBD48" H 4800 2880 50  0000 C CNN
F 2 "Housings_QFP:LQFP-48_7x7mm_Pitch0.5mm" H 6550 2900 50  0000 C CNN
F 3 "" H 5600 2625 50  0001 C CNN
	1    5600 4100
	1    0    0    -1  
$EndComp
$Comp
L Conn_02x11_Odd_Even J1
U 1 1 5ADCA11A
P 9200 3300
F 0 "J1" H 9250 3900 50  0000 C CNN
F 1 "LCD" H 9250 2700 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_2x11_Pitch2.54mm" H 9200 3300 50  0001 C CNN
F 3 "" H 9200 3300 50  0001 C CNN
	1    9200 3300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR7
U 1 1 5ADCA1A0
P 9250 2600
F 0 "#PWR7" H 9250 2350 50  0001 C CNN
F 1 "GND" H 9250 2450 50  0000 C CNN
F 2 "" H 9250 2600 50  0001 C CNN
F 3 "" H 9250 2600 50  0001 C CNN
	1    9250 2600
	-1   0    0    1   
$EndComp
Wire Wire Line
	9000 2600 9500 2600
Wire Wire Line
	9000 2600 9000 2800
Wire Wire Line
	9500 2600 9500 2800
Connection ~ 9250 2600
Text Label 9500 2900 0    60   ~ 0
LCD_V0
Text Label 9000 3000 2    60   ~ 0
LCD_~WR
Text Label 9500 3000 0    60   ~ 0
LCD_~RD
Text Label 9000 3100 2    60   ~ 0
LCD_~CE
Text Label 9500 3100 0    60   ~ 0
LCD_D/~C
Text Label 9500 3200 0    60   ~ 0
LCD_~RST
Text Label 9000 3300 2    60   ~ 0
LCD_DB0
Text Label 9500 3300 0    60   ~ 0
LCD_DB1
Text Label 9000 3400 2    60   ~ 0
LCD_DB2
Text Label 9500 3400 0    60   ~ 0
LCD_DB3
Text Label 9000 3500 2    60   ~ 0
LCD_DB4
Text Label 9500 3500 0    60   ~ 0
LCD_DB5
Text Label 9000 3600 2    60   ~ 0
LCD_DB6
Text Label 9500 3600 0    60   ~ 0
LCD_DB7
Text Label 9000 3700 2    60   ~ 0
LCD_FS
Text Label 9500 3700 0    60   ~ 0
LCD_VEE
Text Label 9000 3800 2    60   ~ 0
LCD_LED_A
Text Label 9500 3800 0    60   ~ 0
LCD_LED_K
$Comp
L GND #PWR2
U 1 1 5ADCA50B
P 5450 5450
F 0 "#PWR2" H 5450 5200 50  0001 C CNN
F 1 "GND" H 5450 5300 50  0000 C CNN
F 2 "" H 5450 5450 50  0001 C CNN
F 3 "" H 5450 5450 50  0001 C CNN
	1    5450 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 5350 5450 5450
Wire Wire Line
	5600 5350 5600 5450
Wire Wire Line
	5600 5450 5450 5450
$Comp
L GND #PWR4
U 1 1 5ADCA542
P 6950 4800
F 0 "#PWR4" H 6950 4550 50  0001 C CNN
F 1 "GND" H 6950 4650 50  0000 C CNN
F 2 "" H 6950 4800 50  0001 C CNN
F 3 "" H 6950 4800 50  0001 C CNN
	1    6950 4800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6800 4800 6950 4800
$Comp
L +5V #PWR6
U 1 1 5ADCA5B6
P 8800 2600
F 0 "#PWR6" H 8800 2450 50  0001 C CNN
F 1 "+5V" H 8800 2740 50  0000 C CNN
F 2 "" H 8800 2600 50  0001 C CNN
F 3 "" H 8800 2600 50  0001 C CNN
	1    8800 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 2600 8800 2900
Wire Wire Line
	8800 2900 9000 2900
$Comp
L +3V3 #PWR3
U 1 1 5ADCA654
P 5600 2250
F 0 "#PWR3" H 5600 2100 50  0001 C CNN
F 1 "+3V3" H 5600 2390 50  0000 C CNN
F 2 "" H 5600 2250 50  0001 C CNN
F 3 "" H 5600 2250 50  0001 C CNN
	1    5600 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 2250 5600 2600
Wire Wire Line
	5450 2350 5750 2350
Wire Wire Line
	5450 2350 5450 2600
Connection ~ 5600 2350
Wire Wire Line
	5750 2350 5750 2600
$Comp
L +5V #PWR5
U 1 1 5ADCA762
P 7000 4600
F 0 "#PWR5" H 7000 4450 50  0001 C CNN
F 1 "+5V" H 7000 4740 50  0000 C CNN
F 2 "" H 7000 4600 50  0001 C CNN
F 3 "" H 7000 4600 50  0001 C CNN
	1    7000 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 4600 6800 4600
Text Label 4400 3000 2    60   ~ 0
LCD_DB0
Text Label 4400 3100 2    60   ~ 0
LCD_DB1
Text Label 4400 3200 2    60   ~ 0
LCD_DB2
Text Label 4400 3300 2    60   ~ 0
LCD_DB3
Text Label 4400 3400 2    60   ~ 0
LCD_DB4
Text Label 4400 3500 2    60   ~ 0
LCD_DB5
Text Label 4400 3600 2    60   ~ 0
LCD_DB6
Text Label 4400 3700 2    60   ~ 0
LCD_DB7
Text Label 4400 3800 2    60   ~ 0
SWCLK
Text Label 4400 4300 2    60   ~ 0
SWDIO
Text Label 4400 2800 2    60   ~ 0
MCU_~RESET
$Comp
L +3V3 #PWR1
U 1 1 5ADCA97A
P 3700 2900
F 0 "#PWR1" H 3700 2750 50  0001 C CNN
F 1 "+3V3" H 3700 3040 50  0000 C CNN
F 2 "" H 3700 2900 50  0001 C CNN
F 3 "" H 3700 2900 50  0001 C CNN
	1    3700 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 2900 4400 2900
$Comp
L Conn_02x05_Odd_Even J2
U 1 1 5ADCAA88
P 9700 6100
F 0 "J2" H 9750 6400 50  0000 C CNN
F 1 "DEBUG" H 9750 5800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x05_Pitch1.27mm" H 9700 6100 50  0001 C CNN
F 3 "" H 9700 6100 50  0001 C CNN
	1    9700 6100
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR9
U 1 1 5ADCAB0C
P 9500 5800
F 0 "#PWR9" H 9500 5650 50  0001 C CNN
F 1 "+3V3" H 9500 5940 50  0000 C CNN
F 2 "" H 9500 5800 50  0001 C CNN
F 3 "" H 9500 5800 50  0001 C CNN
	1    9500 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 5800 9500 5900
$Comp
L GND #PWR8
U 1 1 5ADCAB42
P 9350 6300
F 0 "#PWR8" H 9350 6050 50  0001 C CNN
F 1 "GND" H 9350 6150 50  0000 C CNN
F 2 "" H 9350 6300 50  0001 C CNN
F 3 "" H 9350 6300 50  0001 C CNN
	1    9350 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9350 6300 9500 6300
Wire Wire Line
	9500 6100 9350 6100
Wire Wire Line
	9350 6000 9350 6300
Wire Wire Line
	9500 6000 9350 6000
Connection ~ 9350 6100
Text Label 10000 6300 0    60   ~ 0
MCU_~RESET
Text Label 10000 5900 0    60   ~ 0
SWDIO
Text Label 10000 6000 0    60   ~ 0
SWCLK
Text Label 6800 2900 0    60   ~ 0
LCD_D/~C
Text Label 6800 3400 0    60   ~ 0
LCD_~CE
Text Label 6800 3300 0    60   ~ 0
LCD_~RST
Text Label 6800 4000 0    60   ~ 0
LCD_FS
Text Label 6800 3200 0    60   ~ 0
LCD_~WR
Text Label 6800 2800 0    60   ~ 0
LCD_~RD
Wire Wire Line
	6800 4400 6850 4400
Wire Wire Line
	6850 4400 6850 4800
Connection ~ 6850 4800
Text Label 6800 4950 0    60   ~ 0
XTALIN
Text Label 6800 5100 0    60   ~ 0
XTALOUT
Text Label 6800 4200 0    60   ~ 0
CANH
Text Label 6800 4300 0    60   ~ 0
CANL
$EndSCHEMATC
