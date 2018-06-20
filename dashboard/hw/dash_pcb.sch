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
LIBS:lmz21700
LIBS:tps6217x
LIBS:switches
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
F 2 "Housings_QFP:LQFP-48_7x7mm_Pitch0.5mm" H 6550 2900 50  0001 C CNN
F 3 "https://www.mouser.de/ProductDetail/NXP-Semiconductors/LPC11C24FBD48-301?qs=sGAEpiMZZMs6aXpkJqPL7JC431%2fJReX5" H 5600 2625 50  0001 C CNN
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
F 3 "https://www.mouser.de/ProductDetail/Harwin/M20-7831046?qs=sGAEpiMZZMs%252bGHln7q6pmzlZUuX%2f53qjDVwOyP4FoWY%3d" H 9200 3200 50  0001 C CNN
	1    9200 3200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5ADCA1A0
P 9250 2600
F 0 "#PWR01" H 9250 2350 50  0001 C CNN
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
L GND #PWR02
U 1 1 5ADCA50B
P 5450 5450
F 0 "#PWR02" H 5450 5200 50  0001 C CNN
F 1 "GND" H 5450 5300 50  0000 C CNN
F 2 "" H 5450 5450 50  0001 C CNN
F 3 "" H 5450 5450 50  0001 C CNN
	1    5450 5450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 5ADCA542
P 7300 4850
F 0 "#PWR03" H 7300 4600 50  0001 C CNN
F 1 "GND" H 7300 4700 50  0000 C CNN
F 2 "" H 7300 4850 50  0001 C CNN
F 3 "" H 7300 4850 50  0001 C CNN
	1    7300 4850
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR04
U 1 1 5ADCA654
P 5600 1800
F 0 "#PWR04" H 5600 1650 50  0001 C CNN
F 1 "+3V3" H 5600 1940 50  0000 C CNN
F 2 "" H 5600 1800 50  0001 C CNN
F 3 "" H 5600 1800 50  0001 C CNN
	1    5600 1800
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR05
U 1 1 5ADCA762
P 7300 4550
F 0 "#PWR05" H 7300 4400 50  0001 C CNN
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
Text Label 6800 3300 0    60   ~ 0
LCD_DB2
Text Label 6800 3400 0    60   ~ 0
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
Text Label 4250 2800 2    60   ~ 0
MCU_~RESET
$Comp
L Conn_02x05_Odd_Even J2
U 1 1 5ADCAA88
P 9700 6100
F 0 "J2" H 9750 6400 50  0000 C CNN
F 1 "DEBUG" H 9750 5800 50  0000 C CNN
F 2 "custom_footprints:Pin_Header_Angled_2x05_Pitch1.27mm_AMPHENOL_SHROUDED" H 9700 6100 50  0001 C CNN
F 3 "https://www.mouser.de/ProductDetail/Amphenol-FCI/20021512-00010T4LF?qs=sGAEpiMZZMs%252bGHln7q6pmwodwKqstCemugheqdGIyCk%3d" H 9700 6100 50  0001 C CNN
	1    9700 6100
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR06
U 1 1 5ADCAB0C
P 9500 5650
F 0 "#PWR06" H 9500 5500 50  0001 C CNN
F 1 "+3V3" H 9500 5790 50  0000 C CNN
F 2 "" H 9500 5650 50  0001 C CNN
F 3 "" H 9500 5650 50  0001 C CNN
	1    9500 5650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 5ADCAB42
P 9350 6300
F 0 "#PWR07" H 9350 6050 50  0001 C CNN
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
Text Label 4400 4800 2    60   ~ 0
LCD_~RST
Text Label 6800 3200 0    60   ~ 0
LCD_~WR
Text Label 6800 2800 0    60   ~ 0
LCD_~RD
$Comp
L +3V3 #PWR08
U 1 1 5AE5BC1B
P 8800 2600
F 0 "#PWR08" H 8800 2450 50  0001 C CNN
F 1 "+3V3" H 8800 2740 50  0000 C CNN
F 2 "" H 8800 2600 50  0001 C CNN
F 3 "" H 8800 2600 50  0001 C CNN
	1    8800 2600
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR09
U 1 1 5AE5BE05
P 8450 3700
F 0 "#PWR09" H 8450 3550 50  0001 C CNN
F 1 "+3V3" H 8450 3840 50  0000 C CNN
F 2 "" H 8450 3700 50  0001 C CNN
F 3 "" H 8450 3700 50  0001 C CNN
	1    8450 3700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 5AE5BE6A
P 8450 3100
F 0 "#PWR010" H 8450 2850 50  0001 C CNN
F 1 "GND" H 8450 2950 50  0000 C CNN
F 2 "" H 8450 3100 50  0001 C CNN
F 3 "" H 8450 3100 50  0001 C CNN
	1    8450 3100
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x03 J3
U 1 1 5AE5C0EF
P 10750 2950
F 0 "J3" H 10750 3150 50  0000 C CNN
F 1 "LCD_BL" H 10750 2750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x03_Pitch2.54mm" H 10750 2950 50  0001 C CNN
F 3 "https://www.mouser.de/ProductDetail/TE-Connectivity-AMP/281698-3?qs=sGAEpiMZZMs%252bGHln7q6pm5RYho2xCXYA8YIXmNK49H8%3d" H 10750 2950 50  0001 C CNN
	1    10750 2950
	1    0    0    -1  
$EndComp
$Comp
L POT RV1
U 1 1 5AE5C369
P 10550 3600
F 0 "RV1" V 10375 3600 50  0000 C CNN
F 1 "10k" V 10450 3600 50  0000 C CNN
F 2 "custom_footprints:Bourns_3362X" H 10550 3600 50  0001 C CNN
F 3 "https://www.mouser.de/ProductDetail/Bourns/3362X-1-103LF?qs=sGAEpiMZZMtC25l1F4XBUxECHfqDmxl1ITAi%252bn07c9o%3d" H 10550 3600 50  0001 C CNN
	1    10550 3600
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR011
U 1 1 5AE5C42C
P 10850 3600
F 0 "#PWR011" H 10850 3350 50  0001 C CNN
F 1 "GND" H 10850 3450 50  0000 C CNN
F 2 "" H 10850 3600 50  0001 C CNN
F 3 "" H 10850 3600 50  0001 C CNN
	1    10850 3600
	1    0    0    -1  
$EndComp
Text Label 10550 3450 0    60   ~ 0
LCD_V0
Text Label 10400 3600 2    60   ~ 0
LCD_VEE
$Comp
L R R2
U 1 1 5AED7DC7
P 7750 4500
F 0 "R2" V 7830 4500 50  0000 C CNN
F 1 "62" V 7750 4500 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 7680 4500 50  0001 C CNN
F 3 "https://www.mouser.de/ProductDetail/Bourns/CR0603-FX-62R0ELF?qs=0nF2VnfAjXnEYbikTYe9aw%3d%3d" H 7750 4500 50  0001 C CNN
	1    7750 4500
	-1   0    0    1   
$EndComp
$Comp
L R R4
U 1 1 5AED7E2A
P 7950 4500
F 0 "R4" V 8030 4500 50  0000 C CNN
F 1 "62" V 7950 4500 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 7880 4500 50  0001 C CNN
F 3 "https://www.mouser.de/ProductDetail/Bourns/CR0603-FX-62R0ELF?qs=0nF2VnfAjXnEYbikTYe9aw%3d%3d" H 7950 4500 50  0001 C CNN
	1    7950 4500
	-1   0    0    1   
$EndComp
Text Label 8050 4200 0    60   ~ 0
CANH
$Comp
L C_Small C7
U 1 1 5AED813D
P 10700 4400
F 0 "C7" H 10710 4470 50  0000 L CNN
F 1 "1n" H 10710 4320 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 10700 4400 50  0001 C CNN
F 3 "" H 10700 4400 50  0001 C CNN
	1    10700 4400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 5AED81B0
P 10700 4500
F 0 "#PWR012" H 10700 4250 50  0001 C CNN
F 1 "GND" H 10700 4350 50  0000 C CNN
F 2 "" H 10700 4500 50  0001 C CNN
F 3 "" H 10700 4500 50  0001 C CNN
	1    10700 4500
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
F 1 "100" V 10350 5900 50  0000 C CNN
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
F 1 "100" V 10350 6000 50  0000 C CNN
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
F 1 "100" V 10350 6300 50  0000 C CNN
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
L GND #PWR013
U 1 1 5AED9C6E
P 6900 4400
F 0 "#PWR013" H 6900 4150 50  0001 C CNN
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
L GND #PWR014
U 1 1 5AEDA2F6
P 6050 2550
F 0 "#PWR014" H 6050 2300 50  0001 C CNN
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
L GND #PWR015
U 1 1 5AEDA60D
P 5050 2550
F 0 "#PWR015" H 5050 2300 50  0001 C CNN
F 1 "GND" H 5050 2400 50  0000 C CNN
F 2 "" H 5050 2550 50  0001 C CNN
F 3 "" H 5050 2550 50  0001 C CNN
	1    5050 2550
	0    1    1    0   
$EndComp
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
$Comp
L +3V3 #PWR016
U 1 1 5ADCA97A
P 3550 2850
F 0 "#PWR016" H 3550 2700 50  0001 C CNN
F 1 "+3V3" H 3550 2990 50  0000 C CNN
F 2 "" H 3550 2850 50  0001 C CNN
F 3 "" H 3550 2850 50  0001 C CNN
	1    3550 2850
	1    0    0    -1  
$EndComp
$Comp
L TPS62175 U2
U 1 1 5AF00B83
P 2700 1150
F 0 "U2" H 2450 650 60  0000 C CNN
F 1 "TPS62175" H 2700 1100 60  0000 C CNN
F 2 "custom_footprints:DQC" H 2700 1200 60  0001 C CNN
F 3 "https://www.mouser.de/ProductDetail/Texas-Instruments/TPS62175DQCR?qs=sGAEpiMZZMtD8yQon44BRtpT62hWKGFK" H 2700 1200 60  0001 C CNN
	1    2700 1150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 5AF0114C
P 750 1500
F 0 "#PWR017" H 750 1250 50  0001 C CNN
F 1 "GND" H 750 1350 50  0000 C CNN
F 2 "" H 750 1500 50  0001 C CNN
F 3 "" H 750 1500 50  0001 C CNN
	1    750  1500
	1    0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 5AF015E3
P 4300 2600
F 0 "R8" V 4380 2600 50  0000 C CNN
F 1 "100k" V 4300 2600 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 4230 2600 50  0001 C CNN
F 3 "" H 4300 2600 50  0001 C CNN
	1    4300 2600
	1    0    0    -1  
$EndComp
$Comp
L L L1
U 1 1 5AF01A06
P 3400 750
F 0 "L1" V 3350 750 50  0000 C CNN
F 1 "10u" V 3475 750 50  0000 C CNN
F 2 "custom_footprints:Coilcraft_LPS4018" H 3400 750 50  0001 C CNN
F 3 "https://www.mouser.de/ProductDetail/Coilcraft/LPS4018-103MRB?qs=sGAEpiMZZMsg%252by3WlYCkU2oPBW0WnPwqnL16yXxQPg0%3d" H 3400 750 50  0001 C CNN
	1    3400 750 
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR018
U 1 1 5AF01C77
P 4450 750
F 0 "#PWR018" H 4450 600 50  0001 C CNN
F 1 "+5V" H 4450 890 50  0000 C CNN
F 2 "" H 4450 750 50  0001 C CNN
F 3 "" H 4450 750 50  0001 C CNN
	1    4450 750 
	1    0    0    -1  
$EndComp
$Comp
L R R9
U 1 1 5AF01CEB
P 3750 950
F 0 "R9" V 3830 950 50  0000 C CNN
F 1 "2M" V 3750 950 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 3680 950 50  0001 C CNN
F 3 "https://www.mouser.de/ProductDetail/Vishay/CRCW06032M00FKEB?qs=sGAEpiMZZMu61qfTUdNhG2DpbjADlD3GbbexSTWJF00%3d" H 3750 950 50  0001 C CNN
	1    3750 950 
	1    0    0    -1  
$EndComp
$Comp
L R R10
U 1 1 5AF01D6C
P 3750 1350
F 0 "R10" V 3830 1350 50  0000 C CNN
F 1 "383k" V 3750 1350 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 3680 1350 50  0001 C CNN
F 3 "https://www.mouser.de/ProductDetail/Yageo/AC0603FR-07383KL?qs=sGAEpiMZZMu61qfTUdNhG2gsBIEdmNIDnxIzWWHZb3U%3d" H 3750 1350 50  0001 C CNN
	1    3750 1350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR019
U 1 1 5AF028D7
P 3750 1550
F 0 "#PWR019" H 3750 1300 50  0001 C CNN
F 1 "GND" H 3750 1400 50  0000 C CNN
F 2 "" H 3750 1550 50  0001 C CNN
F 3 "" H 3750 1550 50  0001 C CNN
	1    3750 1550
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 5AF02D59
P 1600 1100
F 0 "C8" H 1625 1200 50  0000 L CNN
F 1 "2.2u" H 1625 1000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 1638 950 50  0001 C CNN
F 3 "https://www.mouser.de/ProductDetail/Murata-Electronics/GRM188R61E225ME84D?qs=sGAEpiMZZMs0AnBnWHyRQKFZIQ7b73cdnYopqDynRzTqa0oaFCyatQ%3d%3d" H 1600 1100 50  0001 C CNN
	1    1600 1100
	1    0    0    -1  
$EndComp
$Comp
L C C9
U 1 1 5AF03359
P 4300 1100
F 0 "C9" H 4325 1200 50  0000 L CNN
F 1 "22u" H 4325 1000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 4338 950 50  0001 C CNN
F 3 "https://www.mouser.de/ProductDetail/Murata-Electronics/GRM188R61A226ME15D?qs=sGAEpiMZZMs0AnBnWHyRQKFZIQ7b73cdtpPVJorxB72AagkQ6fvzJA%3d%3d" H 4300 1100 50  0001 C CNN
	1    4300 1100
	1    0    0    -1  
$EndComp
$Comp
L TLV70233_SOT23-5 U3
U 1 1 5AF0174A
P 1450 2500
F 0 "U3" H 1300 2725 50  0000 C CNN
F 1 "TLV70233_SOT23-5" H 1100 2850 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5" H 1450 2825 50  0001 C CIN
F 3 "https://www.mouser.de/ProductDetail/Texas-Instruments/TLV70233QDBVRQ1?qs=sGAEpiMZZMsGz1a6aV8DcHTv34nsPVHgey%2fBkWCnhrg%3d" H 1450 2550 50  0001 C CNN
	1    1450 2500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 5AF0183D
P 1450 2900
F 0 "#PWR020" H 1450 2650 50  0001 C CNN
F 1 "GND" H 1450 2750 50  0000 C CNN
F 2 "" H 1450 2900 50  0001 C CNN
F 3 "" H 1450 2900 50  0001 C CNN
	1    1450 2900
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR021
U 1 1 5AF01B37
P 650 2400
F 0 "#PWR021" H 650 2250 50  0001 C CNN
F 1 "+5V" H 650 2540 50  0000 C CNN
F 2 "" H 650 2400 50  0001 C CNN
F 3 "" H 650 2400 50  0001 C CNN
	1    650  2400
	1    0    0    -1  
$EndComp
$Comp
L C C10
U 1 1 5AF01BBD
P 750 2650
F 0 "C10" H 775 2750 50  0000 L CNN
F 1 "2.2u" H 775 2550 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 788 2500 50  0001 C CNN
F 3 "https://www.mouser.de/ProductDetail/Murata-Electronics/GRM188R61E225ME84D?qs=sGAEpiMZZMs0AnBnWHyRQKFZIQ7b73cdnYopqDynRzTqa0oaFCyatQ%3d%3d" H 750 2650 50  0001 C CNN
	1    750  2650
	1    0    0    -1  
$EndComp
$Comp
L C C11
U 1 1 5AF01EAD
P 2150 2650
F 0 "C11" H 2175 2750 50  0000 L CNN
F 1 "2.2u" H 2175 2550 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 2188 2500 50  0001 C CNN
F 3 "https://www.mouser.de/ProductDetail/Murata-Electronics/GRM188R61E225ME84D?qs=sGAEpiMZZMs0AnBnWHyRQKFZIQ7b73cdnYopqDynRzTqa0oaFCyatQ%3d%3d" H 2150 2650 50  0001 C CNN
	1    2150 2650
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR022
U 1 1 5AF0216E
P 2250 2400
F 0 "#PWR022" H 2250 2250 50  0001 C CNN
F 1 "+3V3" H 2250 2540 50  0000 C CNN
F 2 "" H 2250 2400 50  0001 C CNN
F 3 "" H 2250 2400 50  0001 C CNN
	1    2250 2400
	1    0    0    -1  
$EndComp
$Comp
L Crystal Y1
U 1 1 5AF03EF6
P 6950 5600
F 0 "Y1" H 6950 5750 50  0000 C CNN
F 1 "12MHz" H 6950 5450 50  0000 C CNN
F 2 "Crystals:Crystal_SMD_HC49-SD" H 6950 5600 50  0001 C CNN
F 3 "https://www.mouser.de/ProductDetail/ABRACON/ABLS-12000MHZ-B2-T?qs=sGAEpiMZZMsBj6bBr9Q9aUe%252bp9Tek3UMlRk4loR5aNA%3d" H 6950 5600 50  0001 C CNN
	1    6950 5600
	-1   0    0    -1  
$EndComp
$Comp
L C_Small C12
U 1 1 5AF03D68
P 7100 5900
F 0 "C12" H 7110 5970 50  0000 L CNN
F 1 "39p" H 7110 5820 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 7100 5900 50  0001 C CNN
F 3 "https://www.mouser.de/ProductDetail/Vishay-Vitramon/VJ0603A390GXJPW1BC?qs=sGAEpiMZZMs0AnBnWHyRQHefeAIkSpb%2fcNZL%252bGiscRY%3d" H 7100 5900 50  0001 C CNN
	1    7100 5900
	1    0    0    1   
$EndComp
$Comp
L C_Small C13
U 1 1 5AF04127
P 6800 5900
F 0 "C13" H 6810 5970 50  0000 L CNN
F 1 "39p" H 6810 5820 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 6800 5900 50  0001 C CNN
F 3 "https://www.mouser.de/ProductDetail/Vishay-Vitramon/VJ0603A390GXJPW1BC?qs=sGAEpiMZZMs0AnBnWHyRQHefeAIkSpb%2fcNZL%252bGiscRY%3d" H 6800 5900 50  0001 C CNN
	1    6800 5900
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR023
U 1 1 5AF045C8
P 6950 6000
F 0 "#PWR023" H 6950 5750 50  0001 C CNN
F 1 "GND" H 6950 5850 50  0000 C CNN
F 2 "" H 6950 6000 50  0001 C CNN
F 3 "" H 6950 6000 50  0001 C CNN
	1    6950 6000
	-1   0    0    -1  
$EndComp
Text Label 7100 5400 1    60   ~ 0
XTALIN
Text Label 6800 5150 3    60   ~ 0
XTALOUT
$Comp
L GND #PWR024
U 1 1 5AF17E60
P 10500 3100
F 0 "#PWR024" H 10500 2850 50  0001 C CNN
F 1 "GND" H 10500 2950 50  0000 C CNN
F 2 "" H 10500 3100 50  0001 C CNN
F 3 "" H 10500 3100 50  0001 C CNN
	1    10500 3100
	1    0    0    -1  
$EndComp
Text Label 10500 3050 2    60   ~ 0
LCD_LED_K
Text Label 10500 2850 2    60   ~ 0
LCD_LED_A
$Comp
L R R11
U 1 1 5AF1A31D
P 10600 2500
F 0 "R11" V 10680 2500 50  0000 C CNN
F 1 "36" V 10600 2500 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 10530 2500 50  0001 C CNN
F 3 "https://www.mouser.de/ProductDetail/Vishay/CRCW120636R0FKEA?qs=sGAEpiMZZMtlubZbdhIBIIDYYWLC5QWgMrFcVuisbCE%3d" H 10600 2500 50  0001 C CNN
	1    10600 2500
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR025
U 1 1 5AF1A42C
P 10500 2300
F 0 "#PWR025" H 10500 2150 50  0001 C CNN
F 1 "+5V" H 10500 2440 50  0000 C CNN
F 2 "" H 10500 2300 50  0001 C CNN
F 3 "" H 10500 2300 50  0001 C CNN
	1    10500 2300
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR026
U 1 1 5AF2F5B2
P 750 750
F 0 "#PWR026" H 750 600 50  0001 C CNN
F 1 "+BATT" H 750 890 50  0000 C CNN
F 2 "" H 750 750 50  0001 C CNN
F 3 "" H 750 750 50  0001 C CNN
	1    750  750 
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x04 J4
U 1 1 5AF30641
P 10700 1100
F 0 "J4" H 10700 1300 50  0000 C CNN
F 1 "CAR" H 10700 800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x04_Pitch2.54mm" H 10700 1100 50  0001 C CNN
F 3 "https://www.mouser.de/ProductDetail/TE-Connectivity-AMP/281698-4?qs=%2fha2pyFadugOWSnGxX0tdzch1lu8VUuW2SzrxAWts0w%3d" H 10700 1100 50  0001 C CNN
	1    10700 1100
	1    0    0    -1  
$EndComp
Text Label 10500 1000 2    60   ~ 0
CANH
Text Label 10500 1100 2    60   ~ 0
CANL
$Comp
L +BATT #PWR027
U 1 1 5AF308D1
P 10100 1050
F 0 "#PWR027" H 10100 900 50  0001 C CNN
F 1 "+BATT" H 10100 1190 50  0000 C CNN
F 2 "" H 10100 1050 50  0001 C CNN
F 3 "" H 10100 1050 50  0001 C CNN
	1    10100 1050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR028
U 1 1 5AF313E9
P 10400 1400
F 0 "#PWR028" H 10400 1150 50  0001 C CNN
F 1 "GND" H 10400 1250 50  0000 C CNN
F 2 "" H 10400 1400 50  0001 C CNN
F 3 "" H 10400 1400 50  0001 C CNN
	1    10400 1400
	1    0    0    -1  
$EndComp
Text Label 8050 4300 0    60   ~ 0
CANL
$Comp
L R R12
U 1 1 5AF38BC5
P 10400 2500
F 0 "R12" V 10480 2500 50  0000 C CNN
F 1 "36" V 10400 2500 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 10330 2500 50  0001 C CNN
F 3 "https://www.mouser.de/ProductDetail/Vishay/CRCW120636R0FKEA?qs=sGAEpiMZZMtlubZbdhIBIIDYYWLC5QWgMrFcVuisbCE%3d" H 10400 2500 50  0001 C CNN
	1    10400 2500
	1    0    0    -1  
$EndComp
Text Label 3750 1900 0    60   ~ 0
MCU_~RESET
$Comp
L +3V3 #PWR029
U 1 1 5AFC1DF1
P 4300 2450
F 0 "#PWR029" H 4300 2300 50  0001 C CNN
F 1 "+3V3" H 4300 2590 50  0000 C CNN
F 2 "" H 4300 2450 50  0001 C CNN
F 3 "" H 4300 2450 50  0001 C CNN
	1    4300 2450
	1    0    0    -1  
$EndComp
$Comp
L SW_DIP_x04 SW1
U 1 1 5AFC4E3D
P 9900 4450
F 0 "SW1" H 9900 4800 50  0000 C CNN
F 1 "CONFIG" H 9900 4200 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_DIP_x4_W7.62mm_Slide" H 9900 4450 50  0001 C CNN
F 3 "https://www.mouser.de/ProductDetail/TE-Connectivity-Alcoswitch/ADE0404?qs=sGAEpiMZZMv%2f%252b2JhlA6ysER62VlXw6iZ4HTlb4kKXdw%3d" H 9900 4450 50  0001 C CNN
	1    9900 4450
	1    0    0    -1  
$EndComp
$Comp
L D_TVS_x2_AAC D3
U 1 1 5B2AE753
P 9550 1200
F 0 "D3" H 9550 1375 50  0000 C CNN
F 1 "PESD1CAN-U" H 9550 1300 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 9400 1200 50  0001 C CNN
F 3 "https://www.mouser.de/ProductDetail/Nexperia/PESD1CAN-UX?qs=sGAEpiMZZMsoIvTP6m9%252bn17u26dJac3S" H 9400 1200 50  0001 C CNN
	1    9550 1200
	0    1    1    0   
$EndComp
$Comp
L D D1
U 1 1 5B2AB9B8
P 1050 750
F 0 "D1" H 1050 850 50  0000 C CNN
F 1 "SS14" H 1050 650 50  0000 C CNN
F 2 "Diodes_SMD:D_SMA_Handsoldering" H 1050 750 50  0001 C CNN
F 3 "https://www.mouser.de/ProductDetail/ON-Semiconductor-Fairchild/SS14?qs=sGAEpiMZZMv%252bkWzvOmGqmqvWeZDNRb1d" H 1050 750 50  0001 C CNN
	1    1050 750 
	-1   0    0    1   
$EndComp
$Comp
L D_Zener D2
U 1 1 5B2AD52F
P 1350 1100
F 0 "D2" H 1350 1200 50  0000 C CNN
F 1 "SMLJ22A-Q" H 1350 1000 50  0000 C CNN
F 2 "Diodes_SMD:D_SMC" H 1350 1100 50  0001 C CNN
F 3 "https://www.mouser.de/ProductDetail/Bourns/SMLJ22A-Q?qs=sGAEpiMZZMvxHShE6Whpu9pBowPIygZNmK45BVf1nKk%3d" H 1350 1100 50  0001 C CNN
	1    1350 1100
	0    1    1    0   
$EndComp
Text Label 7750 4650 3    60   ~ 0
CANH_TERM
Text Label 7950 4650 3    60   ~ 0
CANL_TERM
Text Label 9600 4350 2    60   ~ 0
CANH_TERM
Text Label 9600 4250 2    60   ~ 0
CANL_TERM
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
	10700 3600 10850 3600
Wire Wire Line
	7750 4200 7750 4350
Connection ~ 7750 4200
Wire Wire Line
	7950 4350 7950 4300
Connection ~ 7950 4300
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
Wire Wire Line
	3950 2900 4400 2900
Wire Wire Line
	3550 2850 3550 2900
Wire Wire Line
	3550 2900 3650 2900
Wire Wire Line
	2200 900  2100 900 
Wire Wire Line
	2100 900  2100 750 
Connection ~ 2100 750 
Wire Wire Line
	2100 1050 2200 1050
Wire Wire Line
	2200 1350 2100 1350
Connection ~ 2100 1350
Connection ~ 2100 1500
Wire Wire Line
	3200 1500 3500 1500
Wire Wire Line
	3200 750  3250 750 
Wire Wire Line
	3550 750  4450 750 
Wire Wire Line
	3600 750  3600 1050
Wire Wire Line
	3600 900  3200 900 
Wire Wire Line
	3600 1050 3200 1050
Connection ~ 3600 900 
Connection ~ 3600 750 
Wire Wire Line
	3200 1350 3350 1350
Wire Wire Line
	3350 1350 3350 1150
Wire Wire Line
	3350 1150 3750 1150
Wire Wire Line
	3750 1100 3750 1200
Connection ~ 3750 1150
Wire Wire Line
	3750 800  3750 750 
Connection ~ 3750 750 
Wire Wire Line
	3750 1500 3750 1550
Wire Wire Line
	1600 750  1600 950 
Connection ~ 1600 750 
Wire Wire Line
	1600 1500 1600 1250
Connection ~ 1600 1500
Wire Wire Line
	4000 950  4000 750 
Connection ~ 4000 750 
Wire Wire Line
	4000 1250 4000 1550
Wire Wire Line
	3750 1550 4300 1550
Wire Wire Line
	1450 2800 1450 2900
Wire Wire Line
	1150 2400 1150 2500
Wire Wire Line
	650  2400 1150 2400
Wire Wire Line
	1050 2500 1050 2400
Connection ~ 1050 2400
Wire Wire Line
	1050 2800 1050 2850
Wire Wire Line
	750  2850 2150 2850
Connection ~ 1450 2850
Wire Wire Line
	1850 2400 1850 2500
Wire Wire Line
	1850 2850 1850 2800
Connection ~ 1850 2400
Wire Wire Line
	7100 4950 7100 5800
Wire Wire Line
	6800 5100 6800 5800
Wire Wire Line
	6800 6000 7100 6000
Connection ~ 6950 6000
Connection ~ 7100 5600
Connection ~ 6800 5600
Wire Wire Line
	10500 3050 10550 3050
Wire Wire Line
	10500 2850 10550 2850
Wire Wire Line
	10500 2650 10500 2850
Wire Wire Line
	10500 3100 10500 3050
Wire Wire Line
	1200 750  2200 750 
Wire Wire Line
	6800 4300 8050 4300
Wire Wire Line
	6800 4200 8050 4200
Wire Wire Line
	6800 4950 7100 4950
Wire Wire Line
	750  1500 2200 1500
Wire Wire Line
	2100 1050 2100 1500
Wire Wire Line
	10400 2350 10600 2350
Wire Wire Line
	10500 2350 10500 2300
Connection ~ 10500 2350
Wire Wire Line
	10400 2650 10600 2650
Connection ~ 10500 2650
Wire Wire Line
	3500 1500 3500 1900
Wire Wire Line
	3500 1900 3750 1900
Wire Wire Line
	1750 2600 1700 2600
Wire Wire Line
	1700 2600 1700 2850
Connection ~ 1700 2850
Wire Wire Line
	1750 2600 1750 2500
Wire Wire Line
	4250 2800 4400 2800
Connection ~ 4300 2800
Wire Wire Line
	4300 2750 4300 2800
Wire Wire Line
	10200 4250 10250 4250
Wire Wire Line
	10250 4250 10250 4350
Wire Wire Line
	10250 4350 10200 4350
Wire Wire Line
	10250 4300 10700 4300
Connection ~ 10250 4300
Wire Wire Line
	10100 1050 10100 1200
Wire Wire Line
	10100 1200 10500 1200
Wire Wire Line
	10500 1300 10400 1300
Wire Wire Line
	10400 1300 10400 1400
Wire Wire Line
	750  750  900  750 
Wire Wire Line
	1350 950  1350 750 
Connection ~ 1350 750 
Wire Wire Line
	1350 1250 1350 1500
Connection ~ 1350 1500
$Comp
L C C15
U 1 1 5B2ACAD3
P 1850 1100
F 0 "C15" H 1875 1200 50  0000 L CNN
F 1 "100n" H 1875 1000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 1888 950 50  0001 C CNN
F 3 "" H 1850 1100 50  0001 C CNN
	1    1850 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 950  1850 750 
Connection ~ 1850 750 
Wire Wire Line
	1850 1250 1850 1500
Connection ~ 1850 1500
$Comp
L C C17
U 1 1 5B2AD381
P 4000 1100
F 0 "C17" H 4025 1200 50  0000 L CNN
F 1 "100n" H 4025 1000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 4038 950 50  0001 C CNN
F 3 "" H 4000 1100 50  0001 C CNN
	1    4000 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 750  4300 950 
Connection ~ 4300 750 
Wire Wire Line
	4300 1550 4300 1250
Connection ~ 4000 1550
$Comp
L C C16
U 1 1 5B2ADC33
P 1850 2650
F 0 "C16" H 1875 2750 50  0000 L CNN
F 1 "100n" H 1875 2550 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 1888 2500 50  0001 C CNN
F 3 "" H 1850 2650 50  0001 C CNN
	1    1850 2650
	1    0    0    -1  
$EndComp
Connection ~ 2150 2400
Wire Wire Line
	2150 2400 2150 2500
Wire Wire Line
	2150 2850 2150 2800
Connection ~ 1850 2850
Wire Wire Line
	1750 2400 2250 2400
$Comp
L C C14
U 1 1 5B2AE3C8
P 1050 2650
F 0 "C14" H 1075 2750 50  0000 L CNN
F 1 "100n" H 1075 2550 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 1088 2500 50  0001 C CNN
F 3 "" H 1050 2650 50  0001 C CNN
	1    1050 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	750  2400 750  2500
Connection ~ 750  2400
Wire Wire Line
	750  2800 750  2850
Connection ~ 1050 2850
$Comp
L GND #PWR030
U 1 1 5B2AECBE
P 9250 1200
F 0 "#PWR030" H 9250 950 50  0001 C CNN
F 1 "GND" H 9250 1050 50  0000 C CNN
F 2 "" H 9250 1200 50  0001 C CNN
F 3 "" H 9250 1200 50  0001 C CNN
	1    9250 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 1200 9400 1200
Text Label 9700 850  0    60   ~ 0
CANH
Wire Wire Line
	9550 850  9700 850 
Text Label 9700 1550 0    60   ~ 0
CANL
Wire Wire Line
	9700 1550 9550 1550
$EndSCHEMATC
