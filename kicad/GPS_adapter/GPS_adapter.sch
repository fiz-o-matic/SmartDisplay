EESchema Schematic File Version 4
EELAYER 30 0
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
L Connector_Generic:Conn_01x05 J1
U 1 1 606DFC67
P 6000 2800
F 0 "J1" H 6080 2842 50  0000 L CNN
F 1 "Conn_01x05" H 6080 2751 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Horizontal" H 6000 2800 50  0001 C CNN
F 3 "~" H 6000 2800 50  0001 C CNN
	1    6000 2800
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J2
U 1 1 606E095D
P 6000 3850
F 0 "J2" H 6080 3842 50  0000 L CNN
F 1 "Conn_01x04" H 6080 3751 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 6000 3850 50  0001 C CNN
F 3 "~" H 6000 3850 50  0001 C CNN
	1    6000 3850
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0101
U 1 1 606E19F5
P 5800 2600
F 0 "#PWR0101" H 5800 2450 50  0001 C CNN
F 1 "VCC" V 5815 2727 50  0000 L CNN
F 2 "" H 5800 2600 50  0001 C CNN
F 3 "" H 5800 2600 50  0001 C CNN
	1    5800 2600
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 606E2338
P 5800 2700
F 0 "#PWR0102" H 5800 2450 50  0001 C CNN
F 1 "GND" V 5805 2572 50  0000 R CNN
F 2 "" H 5800 2700 50  0001 C CNN
F 3 "" H 5800 2700 50  0001 C CNN
	1    5800 2700
	0    1    1    0   
$EndComp
Text GLabel 5800 2800 0    50   Input ~ 0
TXD
Text GLabel 5800 2900 0    50   Input ~ 0
RXD
Text GLabel 5800 3000 0    50   Input ~ 0
RTS
$Comp
L power:VCC #PWR0103
U 1 1 606E299E
P 5800 3750
F 0 "#PWR0103" H 5800 3600 50  0001 C CNN
F 1 "VCC" V 5815 3877 50  0000 L CNN
F 2 "" H 5800 3750 50  0001 C CNN
F 3 "" H 5800 3750 50  0001 C CNN
	1    5800 3750
	0    -1   -1   0   
$EndComp
Text GLabel 5800 3850 0    50   Input ~ 0
RXD
Text GLabel 5800 3950 0    50   Input ~ 0
TXD
$Comp
L power:GND #PWR0104
U 1 1 606E307D
P 5800 4050
F 0 "#PWR0104" H 5800 3800 50  0001 C CNN
F 1 "GND" V 5805 3922 50  0000 R CNN
F 2 "" H 5800 4050 50  0001 C CNN
F 3 "" H 5800 4050 50  0001 C CNN
	1    5800 4050
	0    1    1    0   
$EndComp
$EndSCHEMATC
