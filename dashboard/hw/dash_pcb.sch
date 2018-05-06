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
L Conn_02x10_Odd_Even J1
U 1 1 5ADCA11A
P 9200 3200
F 0 "J1" H 9250 3700 50  0000 C CNN
F 1 "LCD" H 9250 2600 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_2x10_Pitch2.54mm" H 9200 3200 50  0001 C CNN
F 3 "" H 9200 3200 50  0001 C CNN
	1    9200 3200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR12
U 1 1 5ADCA1A0
P 9250 2600
F 0 "#PWR12" H 9250 2350 50  0001 C CNN
F 1 "GND" H 9250 2450 50  0000 C CNN
F 2 "" H 9250 2600 50  0001 C CNN
F 3 "" H 9250 2600 50  0001 C CNN
	1    9250 2600
	-1   0    0    1   
$EndComp
Text Label 9500 2900 0    60   ~ 0
LCD_V0
Text Label 9000 3000 2    60   ~ 0
LCD_~WR
Text Label 9500 3000 0    60   ~ 0
LCD_~RD
Text Label 9000 3100 2    60   ~ 0
LCD_~CE
Text Label 9500 3100 0    60   ~ 0
LCD_C/~D
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
Text Label 9000 3200 2    60   ~ 0
LCD_VEE
$Comp
L GND #PWR3
U 1 1 5ADCA50B
P 5450 5450
F 0 "#PWR3" H 5450 5200 50  0001 C CNN
F 1 "GND" H 5450 5300 50  0000 C CNN
F 2 "" H 5450 5450 50  0001 C CNN
F 3 "" H 5450 5450 50  0001 C CNN
	1    5450 5450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR8
U 1 1 5ADCA542
P 7300 4850
F 0 "#PWR8" H 7300 4600 50  0001 C CNN
F 1 "GND" H 7300 4700 50  0000 C CNN
F 2 "" H 7300 4850 50  0001 C CNN
F 3 "" H 7300 4850 50  0001 C CNN
	1    7300 4850
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR4
U 1 1 5ADCA654
P 5600 1800
F 0 "#PWR4" H 5600 1650 50  0001 C CNN
F 1 "+3V3" H 5600 1940 50  0000 C CNN
F 2 "" H 5600 1800 50  0001 C CNN
F 3 "" H 5600 1800 50  0001 C CNN
	1    5600 1800
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR7
U 1 1 5ADCA762
P 7300 4550
F 0 "#PWR7" H 7300 4400 50  0001 C CNN
F 1 "+5V" H 7300 4690 50  0000 C CNN
F 2 "" H 7300 4550 50  0001 C CNN
F 3 "" H 7300 4550 50  0001 C CNN
	1    7300 4550
	1    0    0    -1  
$EndComp
Text Label 4400 3000 2    60   ~ 0
LCD_DB0
Text Label 4400 3100 2    60   ~ 0
LCD_DB1
Text Label 4400 4800 2    60   ~ 0
LCD_DB2
Text Label 4400 4500 2    60   ~ 0
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
L Conn_02x05_Odd_Even J2
U 1 1 5ADCAA88
P 9700 6100
F 0 "J2" H 9750 6400 50  0000 C CNN
F 1 "DEBUG" H 9750 5800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_2x05_Pitch1.27mm" H 9700 6100 50  0001 C CNN
F 3 "" H 9700 6100 50  0001 C CNN
	1    9700 6100
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR14
U 1 1 5ADCAB0C
P 9500 5650
F 0 "#PWR14" H 9500 5500 50  0001 C CNN
F 1 "+3V3" H 9500 5790 50  0000 C CNN
F 2 "" H 9500 5650 50  0001 C CNN
F 3 "" H 9500 5650 50  0001 C CNN
	1    9500 5650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR13
U 1 1 5ADCAB42
P 9350 6300
F 0 "#PWR13" H 9350 6050 50  0001 C CNN
F 1 "GND" H 9350 6150 50  0000 C CNN
F 2 "" H 9350 6300 50  0001 C CNN
F 3 "" H 9350 6300 50  0001 C CNN
	1    9350 6300
	1    0    0    -1  
$EndComp
Text Label 10650 6300 0    60   ~ 0
MCU_~RESET
Text Label 10650 5900 0    60   ~ 0
SWDIO
Text Label 10650 6000 0    60   ~ 0
SWCLK
Text Label 6800 2900 0    60   ~ 0
LCD_C/~D
Text Label 6800 3300 0    60   ~ 0
LCD_~RST
Text Label 6800 3200 0    60   ~ 0
LCD_~WR
Text Label 6800 2800 0    60   ~ 0
LCD_~RD
Text Label 6800 4950 0    60   ~ 0
XTALIN
Text Label 6800 5100 0    60   ~ 0
XTALOUT
Text Label 6800 4200 0    60   ~ 0
CANH
Text Label 6800 4300 0    60   ~ 0
CANL
$Comp
L +3V3 #PWR11
U 1 1 5AE5BC1B
P 8800 2600
F 0 "#PWR11" H 8800 2450 50  0001 C CNN
F 1 "+3V3" H 8800 2740 50  0000 C CNN
F 2 "" H 8800 2600 50  0001 C CNN
F 3 "" H 8800 2600 50  0001 C CNN
	1    8800 2600
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR10
U 1 1 5AE5BE05
P 8450 3700
F 0 "#PWR10" H 8450 3550 50  0001 C CNN
F 1 "+3V3" H 8450 3840 50  0000 C CNN
F 2 "" H 8450 3700 50  0001 C CNN
F 3 "" H 8450 3700 50  0001 C CNN
	1    8450 3700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR9
U 1 1 5AE5BE6A
P 8450 3100
F 0 "#PWR9" H 8450 2850 50  0001 C CNN
F 1 "GND" H 8450 2950 50  0000 C CNN
F 2 "" H 8450 3100 50  0001 C CNN
F 3 "" H 8450 3100 50  0001 C CNN
	1    8450 3100
	1    0    0    -1  
$EndComp
Text Label 10650 3500 2    60   ~ 0
LCD_LED_A
Text Label 10650 3700 2    60   ~ 0
LCD_LED_K
$Comp
L Conn_01x03 J3
U 1 1 5AE5C0EF
P 10850 3600
F 0 "J3" H 10850 3800 50  0000 C CNN
F 1 "LCD_BL" H 10850 3400 50  0000 C CNN
F 2 "Connectors_JST:JST_XH_S03B-XH-A_03x2.50mm_Angled" H 10850 3600 50  0001 C CNN
F 3 "" H 10850 3600 50  0001 C CNN
	1    10850 3600
	1    0    0    -1  
$EndComp
$Comp
L POT RV1
U 1 1 5AE5C369
P 10550 2800
F 0 "RV1" V 10375 2800 50  0000 C CNN
F 1 "10k" V 10450 2800 50  0000 C CNN
F 2 "Potentiometers:Potentiometer_Trimmer_ACP_CA6v_Horizontal" H 10550 2800 50  0001 C CNN
F 3 "" H 10550 2800 50  0001 C CNN
	1    10550 2800
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR17
U 1 1 5AE5C42C
P 10850 2800
F 0 "#PWR17" H 10850 2550 50  0001 C CNN
F 1 "GND" H 10850 2650 50  0000 C CNN
F 2 "" H 10850 2800 50  0001 C CNN
F 3 "" H 10850 2800 50  0001 C CNN
	1    10850 2800
	1    0    0    -1  
$EndComp
Text Label 10550 2650 0    60   ~ 0
LCD_V0
Text Label 10400 2800 2    60   ~ 0
LCD_VEE
$Comp
L R R2
U 1 1 5AED7DC7
P 9900 4550
F 0 "R2" V 9980 4550 50  0000 C CNN
F 1 "60" V 9900 4550 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 9830 4550 50  0001 C CNN
F 3 "" H 9900 4550 50  0001 C CNN
	1    9900 4550
	-1   0    0    1   
$EndComp
$Comp
L R R4
U 1 1 5AED7E2A
P 10100 4550
F 0 "R4" V 10180 4550 50  0000 C CNN
F 1 "60" V 10100 4550 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 10030 4550 50  0001 C CNN
F 3 "" H 10100 4550 50  0001 C CNN
	1    10100 4550
	-1   0    0    1   
$EndComp
$Comp
L Conn_01x03 J4
U 1 1 5AED7F27
P 10650 4350
F 0 "J4" H 10650 4550 50  0000 C CNN
F 1 "CAN" H 10650 4150 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x03_Pitch2.54mm" H 10650 4350 50  0001 C CNN
F 3 "" H 10650 4350 50  0001 C CNN
	1    10650 4350
	1    0    0    -1  
$EndComp
Text Label 9700 4250 2    60   ~ 0
CANH
Text Label 9700 4350 2    60   ~ 0
CANL
$Comp
L C_Small C7
U 1 1 5AED813D
P 10000 4850
F 0 "C7" H 10010 4920 50  0000 L CNN
F 1 "1n" H 10010 4770 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 10000 4850 50  0001 C CNN
F 3 "" H 10000 4850 50  0001 C CNN
	1    10000 4850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR15
U 1 1 5AED81B0
P 10000 4950
F 0 "#PWR15" H 10000 4700 50  0001 C CNN
F 1 "GND" H 10000 4800 50  0000 C CNN
F 2 "" H 10000 4950 50  0001 C CNN
F 3 "" H 10000 4950 50  0001 C CNN
	1    10000 4950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR16
U 1 1 5AED81E8
P 10450 4450
F 0 "#PWR16" H 10450 4200 50  0001 C CNN
F 1 "GND" H 10450 4300 50  0000 C CNN
F 2 "" H 10450 4450 50  0001 C CNN
F 3 "" H 10450 4450 50  0001 C CNN
	1    10450 4450
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 5AED89D4
P 9950 5700
F 0 "R3" V 10030 5700 50  0000 C CNN
F 1 "10k" V 9950 5700 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 9880 5700 50  0001 C CNN
F 3 "" H 9950 5700 50  0001 C CNN
	1    9950 5700
	0    -1   -1   0   
$EndComp
$Comp
L R R5
U 1 1 5AED8B98
P 10350 5900
F 0 "R5" V 10430 5900 50  0000 C CNN
F 1 "60" V 10350 5900 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 10280 5900 50  0001 C CNN
F 3 "" H 10350 5900 50  0001 C CNN
	1    10350 5900
	0    -1   -1   0   
$EndComp
$Comp
L R R6
U 1 1 5AED8BD0
P 10350 6000
F 0 "R6" V 10430 6000 50  0000 C CNN
F 1 "60" V 10350 6000 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 10280 6000 50  0001 C CNN
F 3 "" H 10350 6000 50  0001 C CNN
	1    10350 6000
	0    1    1    0   
$EndComp
$Comp
L R R7
U 1 1 5AED8C25
P 10350 6300
F 0 "R7" V 10430 6300 50  0000 C CNN
F 1 "60" V 10350 6300 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 10280 6300 50  0001 C CNN
F 3 "" H 10350 6300 50  0001 C CNN
	1    10350 6300
	0    1    1    0   
$EndComp
$Comp
L C_Small C6
U 1 1 5AED960A
P 7150 4700
F 0 "C6" H 7160 4770 50  0000 L CNN
F 1 "100n" H 7160 4620 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 7150 4700 50  0001 C CNN
F 3 "" H 7150 4700 50  0001 C CNN
	1    7150 4700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR6
U 1 1 5AED9C6E
P 6900 4400
F 0 "#PWR6" H 6900 4150 50  0001 C CNN
F 1 "GND" H 6900 4250 50  0000 C CNN
F 2 "" H 6900 4400 50  0001 C CNN
F 3 "" H 6900 4400 50  0001 C CNN
	1    6900 4400
	1    0    0    -1  
$EndComp
$Comp
L C_Small C5
U 1 1 5AEDA26F
P 5900 2550
F 0 "C5" H 5910 2620 50  0000 L CNN
F 1 "10n" H 5910 2470 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5900 2550 50  0001 C CNN
F 3 "" H 5900 2550 50  0001 C CNN
	1    5900 2550
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR5
U 1 1 5AEDA2F6
P 6050 2550
F 0 "#PWR5" H 6050 2300 50  0001 C CNN
F 1 "GND" H 6050 2400 50  0000 C CNN
F 2 "" H 6050 2550 50  0001 C CNN
F 3 "" H 6050 2550 50  0001 C CNN
	1    6050 2550
	0    -1   -1   0   
$EndComp
$Comp
L C_Small C4
U 1 1 5AEDA40D
P 5300 2550
F 0 "C4" H 5310 2620 50  0000 L CNN
F 1 "10n" H 5310 2470 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5300 2550 50  0001 C CNN
F 3 "" H 5300 2550 50  0001 C CNN
	1    5300 2550
	0    1    -1   0   
$EndComp
$Comp
L C_Small C3
U 1 1 5AEDA480
P 5300 2350
F 0 "C3" H 5310 2420 50  0000 L CNN
F 1 "100n" H 5310 2270 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5300 2350 50  0001 C CNN
F 3 "" H 5300 2350 50  0001 C CNN
	1    5300 2350
	0    1    -1   0   
$EndComp
$Comp
L C_Small C2
U 1 1 5AEDA510
P 5300 2100
F 0 "C2" H 5310 2170 50  0000 L CNN
F 1 "10n" H 5310 2020 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5300 2100 50  0001 C CNN
F 3 "" H 5300 2100 50  0001 C CNN
	1    5300 2100
	0    1    -1   0   
$EndComp
$Comp
L C_Small C1
U 1 1 5AEDA55A
P 5300 1900
F 0 "C1" H 5310 1970 50  0000 L CNN
F 1 "100n" H 5310 1820 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5300 1900 50  0001 C CNN
F 3 "" H 5300 1900 50  0001 C CNN
	1    5300 1900
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR2
U 1 1 5AEDA60D
P 5050 2550
F 0 "#PWR2" H 5050 2300 50  0001 C CNN
F 1 "GND" H 5050 2400 50  0000 C CNN
F 2 "" H 5050 2550 50  0001 C CNN
F 3 "" H 5050 2550 50  0001 C CNN
	1    5050 2550
	0    1    1    0   
$EndComp
Wire Wire Line
	9000 2600 9500 2600
Wire Wire Line
	9000 2600 9000 2800
Wire Wire Line
	9500 2600 9500 2800
Connection ~ 9250 2600
Wire Wire Line
	5450 5350 5450 5450
Wire Wire Line
	5600 5350 5600 5450
Wire Wire Line
	5600 5450 5450 5450
Wire Wire Line
	8800 2600 8800 2900
Wire Wire Line
	8800 2900 9000 2900
Wire Wire Line
	5600 1800 5600 2600
Wire Wire Line
	5450 1800 5450 2600
Wire Wire Line
	5750 1800 5750 2600
Wire Wire Line
	9500 5650 9500 5900
Wire Wire Line
	9350 6300 9500 6300
Wire Wire Line
	9500 6100 9350 6100
Wire Wire Line
	9350 6000 9350 6300
Wire Wire Line
	9500 6000 9350 6000
Connection ~ 9350 6100
Wire Wire Line
	6800 4400 6900 4400
Wire Wire Line
	8450 3700 9000 3700
Wire Wire Line
	8450 3100 9000 3100
Wire Wire Line
	10700 2800 10850 2800
Wire Wire Line
	9700 4250 10450 4250
Wire Wire Line
	9900 4250 9900 4400
Connection ~ 9900 4250
Wire Wire Line
	9700 4350 10450 4350
Wire Wire Line
	10100 4400 10100 4350
Connection ~ 10100 4350
Wire Wire Line
	9900 4700 10100 4700
Wire Wire Line
	10000 4700 10000 4750
Connection ~ 10000 4700
Wire Wire Line
	10650 6300 10500 6300
Wire Wire Line
	10200 6300 10000 6300
Wire Wire Line
	10100 5700 10100 6000
Wire Wire Line
	10000 6000 10200 6000
Connection ~ 10100 6000
Wire Wire Line
	10500 6000 10650 6000
Wire Wire Line
	10650 5900 10500 5900
Wire Wire Line
	10200 5900 10000 5900
Wire Wire Line
	9800 5700 9500 5700
Connection ~ 9500 5700
Wire Wire Line
	6800 4600 7050 4600
Wire Wire Line
	7050 4600 7050 4550
Wire Wire Line
	6800 4800 7050 4800
Wire Wire Line
	7050 4800 7050 4850
Wire Wire Line
	7150 4600 7150 4550
Connection ~ 7150 4550
Wire Wire Line
	7150 4800 7150 4850
Connection ~ 7150 4850
Wire Wire Line
	7050 4550 7300 4550
Wire Wire Line
	7050 4850 7300 4850
Wire Wire Line
	6000 2550 6050 2550
Wire Wire Line
	5800 2550 5750 2550
Connection ~ 5750 2550
Wire Wire Line
	5200 1900 5150 1900
Wire Wire Line
	5150 1900 5150 2550
Wire Wire Line
	5050 2550 5200 2550
Connection ~ 5150 2550
Wire Wire Line
	5200 2350 5150 2350
Connection ~ 5150 2350
Wire Wire Line
	5200 2100 5150 2100
Connection ~ 5150 2100
Connection ~ 5450 2350
Wire Wire Line
	5400 2550 5450 2550
Connection ~ 5450 2550
Wire Wire Line
	5400 2350 5450 2350
Wire Wire Line
	5450 1800 5750 1800
Wire Wire Line
	5600 2100 5400 2100
Wire Wire Line
	5600 1900 5400 1900
Connection ~ 5600 2100
Connection ~ 5600 1900
Connection ~ 5600 1800
Connection ~ 5750 2350
$Comp
L R R1
U 1 1 5AEF367A
P 3800 2900
F 0 "R1" V 3880 2900 50  0000 C CNN
F 1 "10k" V 3800 2900 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 3730 2900 50  0001 C CNN
F 3 "" H 3800 2900 50  0001 C CNN
	1    3800 2900
	0    1    1    0   
$EndComp
Wire Wire Line
	3950 2900 4400 2900
$Comp
L +3V3 #PWR1
U 1 1 5ADCA97A
P 3550 2850
F 0 "#PWR1" H 3550 2700 50  0001 C CNN
F 1 "+3V3" H 3550 2990 50  0000 C CNN
F 2 "" H 3550 2850 50  0001 C CNN
F 3 "" H 3550 2850 50  0001 C CNN
	1    3550 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 2850 3550 2900
Wire Wire Line
	3550 2900 3650 2900
$EndSCHEMATC
