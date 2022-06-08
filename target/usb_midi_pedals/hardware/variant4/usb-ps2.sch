EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "USB-to-PS2 adapter (Digispark-compatible)"
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Microchip_ATtiny:ATtiny85-20PU U1
U 1 1 62763A1D
P 5000 3750
F 0 "U1" H 4471 3796 50  0000 R CNN
F 1 "ATtiny85-20PU" H 4471 3705 50  0000 R CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 5000 3750 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf" H 5000 3750 50  0001 C CNN
	1    5000 3750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 62764714
P 4250 5000
F 0 "R1" V 4150 4925 50  0000 C CNN
F 1 "68" V 4150 5050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 4180 5000 50  0001 C CNN
F 3 "~" H 4250 5000 50  0001 C CNN
	1    4250 5000
	0    1    1    0   
$EndComp
Wire Wire Line
	4400 5000 4750 5000
Wire Wire Line
	5600 3750 6000 3750
Wire Wire Line
	5600 3850 6000 3850
Wire Wire Line
	5600 3650 6000 3650
Wire Wire Line
	5600 3550 6000 3550
Wire Wire Line
	5600 3450 6000 3450
Wire Wire Line
	5600 3950 6000 3950
Text Label 5750 3450 0    50   ~ 0
PB0
Text Label 5750 3750 0    50   ~ 0
PB3
Text Label 5750 3850 0    50   ~ 0
PB4
Text Label 4475 5000 0    50   ~ 0
PB3
Text Label 3825 5000 0    50   ~ 0
USB_M
$Comp
L Device:R R2
U 1 1 6276B8DD
P 4250 5250
F 0 "R2" V 4150 5175 50  0000 C CNN
F 1 "68" V 4150 5300 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 4180 5250 50  0001 C CNN
F 3 "~" H 4250 5250 50  0001 C CNN
	1    4250 5250
	0    1    1    0   
$EndComp
Wire Wire Line
	4400 5250 4750 5250
Wire Wire Line
	4100 5250 3800 5250
Text Label 4475 5250 0    50   ~ 0
PB4
Text Label 3825 5250 0    50   ~ 0
USB_P
$Comp
L Device:D_Zener D1
U 1 1 6276C5B7
P 4225 4750
F 0 "D1" H 4150 4850 50  0000 C CNN
F 1 "3.6V" H 4325 4850 50  0000 C CNN
F 2 "Diode_THT:D_DO-34_SOD68_P7.62mm_Horizontal" H 4225 4750 50  0001 C CNN
F 3 "~" H 4225 4750 50  0001 C CNN
	1    4225 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Zener D2
U 1 1 6276D36A
P 4250 5500
F 0 "D2" H 4175 5600 50  0000 C CNN
F 1 "3.6V" H 4325 5600 50  0000 C CNN
F 2 "Diode_THT:D_DO-34_SOD68_P7.62mm_Horizontal" H 4250 5500 50  0001 C CNN
F 3 "~" H 4250 5500 50  0001 C CNN
	1    4250 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 5000 3800 5000
Wire Wire Line
	4075 4750 3800 4750
Connection ~ 3800 5000
Wire Wire Line
	3800 5000 3750 5000
Wire Wire Line
	4100 5500 3800 5500
Wire Wire Line
	3800 5500 3800 5250
Connection ~ 3800 5250
Wire Wire Line
	3800 5250 3750 5250
Wire Wire Line
	4375 4750 4750 4750
Wire Wire Line
	4400 5500 4750 5500
Text Label 4475 4750 0    50   ~ 0
GND
Text Label 4475 5500 0    50   ~ 0
GND
Wire Wire Line
	5000 4350 5000 4500
Wire Wire Line
	5000 3150 5000 3000
$Comp
L Device:R R3
U 1 1 627790F2
P 4250 4500
F 0 "R3" V 4150 4425 50  0000 C CNN
F 1 "1.5K" V 4150 4575 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 4180 4500 50  0001 C CNN
F 3 "~" H 4250 4500 50  0001 C CNN
	1    4250 4500
	0    1    1    0   
$EndComp
Wire Wire Line
	4400 4500 4750 4500
Wire Wire Line
	4100 4500 3800 4500
Wire Wire Line
	3800 4500 3800 4750
Connection ~ 3800 4750
Wire Wire Line
	3800 4750 3800 5000
$Comp
L Connector:Conn_01x04_Male J2
U 1 1 6277B054
P 1300 3675
F 0 "J2" H 1408 3864 50  0000 C CNN
F 1 "Conn_01x04_Male" H 1408 3865 50  0001 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 1300 3675 50  0001 C CNN
F 3 "~" H 1300 3675 50  0001 C CNN
	1    1300 3675
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 3575 2000 3575
Wire Wire Line
	1500 3675 2000 3675
Wire Wire Line
	1500 3775 2000 3775
Wire Wire Line
	1500 3875 2000 3875
Text Label 1550 3575 0    50   ~ 0
GND
Text Label 1550 3875 0    50   ~ 0
VCC
Text Label 1550 3775 0    50   ~ 0
USB_M
Text Label 1550 3675 0    50   ~ 0
USB_P
Text Label 4475 4500 0    50   ~ 0
VCC
Text Label 5000 4450 0    50   ~ 0
GND
Text Label 5000 3100 0    50   ~ 0
VCC
Text Label 5750 3550 0    50   ~ 0
PB1
Text Label 5750 3650 0    50   ~ 0
PB2
Text Label 5750 3950 0    50   ~ 0
PB5
$Comp
L Device:R R4
U 1 1 62788AB8
P 6000 5000
F 0 "R4" V 5900 4925 50  0000 C CNN
F 1 "68" V 5900 5050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 5930 5000 50  0001 C CNN
F 3 "~" H 6000 5000 50  0001 C CNN
	1    6000 5000
	0    1    1    0   
$EndComp
$Comp
L Device:R R5
U 1 1 62789461
P 6000 5250
F 0 "R5" V 5900 5175 50  0000 C CNN
F 1 "68" V 5900 5300 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 5930 5250 50  0001 C CNN
F 3 "~" H 6000 5250 50  0001 C CNN
	1    6000 5250
	0    1    1    0   
$EndComp
$Comp
L Device:R R6
U 1 1 627898E6
P 6000 5500
F 0 "R6" V 5900 5425 50  0000 C CNN
F 1 "68" V 5900 5550 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 5930 5500 50  0001 C CNN
F 3 "~" H 6000 5500 50  0001 C CNN
	1    6000 5500
	0    1    1    0   
$EndComp
Wire Wire Line
	5850 5000 5500 5000
Wire Wire Line
	5850 5250 5500 5250
Wire Wire Line
	5850 5500 5500 5500
Wire Wire Line
	6150 5000 6500 5000
Wire Wire Line
	6150 5250 6500 5250
Wire Wire Line
	6150 5500 6500 5500
Text Label 5600 5000 0    50   ~ 0
PB0
Text Label 5600 5250 0    50   ~ 0
PB1
Text Label 5600 5500 0    50   ~ 0
PB2
$Comp
L Connector:Conn_01x06_Male J1
U 1 1 6279132D
P 7700 3800
F 0 "J1" H 7672 3682 50  0000 R CNN
F 1 "Conn_01x06_Male" H 7672 3773 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 7700 3800 50  0001 C CNN
F 3 "~" H 7700 3800 50  0001 C CNN
	1    7700 3800
	-1   0    0    1   
$EndComp
Wire Wire Line
	7500 3500 7250 3500
Wire Wire Line
	7500 3600 7250 3600
Wire Wire Line
	7500 3700 7250 3700
Wire Wire Line
	7500 3800 7250 3800
Wire Wire Line
	7500 3900 7250 3900
Wire Wire Line
	7500 4000 7250 4000
$Comp
L Connector:Conn_01x01_Male J3
U 1 1 62798652
P 7700 4250
F 0 "J3" H 7672 4182 50  0000 R CNN
F 1 "Conn_01x01_Male" H 7672 4273 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 7700 4250 50  0001 C CNN
F 3 "~" H 7700 4250 50  0001 C CNN
	1    7700 4250
	-1   0    0    1   
$EndComp
Wire Wire Line
	7500 4250 7250 4250
Text Label 7325 4250 0    50   ~ 0
VCC
$Comp
L Connector:Conn_01x01_Male J4
U 1 1 6279C71C
P 7700 4500
F 0 "J4" H 7672 4432 50  0000 R CNN
F 1 "Conn_01x01_Male" H 7672 4523 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 7700 4500 50  0001 C CNN
F 3 "~" H 7700 4500 50  0001 C CNN
	1    7700 4500
	-1   0    0    1   
$EndComp
Wire Wire Line
	7500 4500 7250 4500
Text Label 7325 4500 0    50   ~ 0
VCC
Text Label 7325 3500 0    50   ~ 0
VCC
Text Label 7325 4000 0    50   ~ 0
GND
Text Label 6250 5000 0    50   ~ 0
D0
Text Label 6250 5250 0    50   ~ 0
D1
Text Label 6250 5500 0    50   ~ 0
D2
Text Label 7350 3900 0    50   ~ 0
D0
Text Label 7350 3800 0    50   ~ 0
D1
Text Label 7350 3700 0    50   ~ 0
D2
Text Label 7325 3600 0    50   ~ 0
VCC
$Comp
L Connector:Conn_01x01_Male J5
U 1 1 627A192F
P 7700 4750
F 0 "J5" H 7672 4682 50  0000 R CNN
F 1 "Conn_01x01_Male" H 7672 4773 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 7700 4750 50  0001 C CNN
F 3 "~" H 7700 4750 50  0001 C CNN
	1    7700 4750
	-1   0    0    1   
$EndComp
Wire Wire Line
	7500 4750 7250 4750
Text Label 7325 4750 0    50   ~ 0
VCC
$Comp
L Connector:Conn_01x01_Male J6
U 1 1 627A3517
P 7700 5000
F 0 "J6" H 7672 4932 50  0000 R CNN
F 1 "Conn_01x01_Male" H 7672 5023 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 7700 5000 50  0001 C CNN
F 3 "~" H 7700 5000 50  0001 C CNN
	1    7700 5000
	-1   0    0    1   
$EndComp
Wire Wire Line
	7500 5000 7250 5000
Text Label 7325 5000 0    50   ~ 0
GND
$Comp
L Device:C C1
U 1 1 627A51BE
P 6000 4500
F 0 "C1" H 6115 4546 50  0000 L CNN
F 1 "0.1" H 6115 4455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 6038 4350 50  0001 C CNN
F 3 "~" H 6000 4500 50  0001 C CNN
	1    6000 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 4650 6000 4750
Wire Wire Line
	6000 4350 6000 4250
Text Label 6000 4350 0    50   ~ 0
VCC
Text Label 6000 4725 0    50   ~ 0
GND
Text Notes 5275 5725 0    50   ~ 0
Optional resistors for shorts protection
$EndSCHEMATC
