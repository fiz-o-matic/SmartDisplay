EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "DOGS102"
Date "2022-04-11"
Rev "0.9.1"
Comp "fiz-o-matic.net"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L dogs102:DINA4_L #FRAME1
U 1 1 5A96C787
P 1250 8150
F 0 "#FRAME1" H 1300 8200 60  0001 C CNN
F 1 "~" H 1250 8150 60  0001 C CNN
F 2 "" H 1250 8150 60  0001 C CNN
F 3 "" H 1250 8150 60  0001 C CNN
	1    1250 8150
	1    0    0    -1  
$EndComp
$Comp
L dogs102-rescue:EA_DOGS102W-6-dogs102_n DS1
U 1 1 5E9C647E
P 6950 2750
F 0 "DS1" H 7550 3015 50  0000 C CNN
F 1 "EA_DOGS102W-6" H 7550 2924 50  0000 C CNN
F 2 "fiz-o-matic:EA-DOGS102W-6" H 8000 2850 50  0001 L CNN
F 3 "http://www.lcd-module.com/eng/pdf/grafik/dogs102-6e.pdf" H 8000 2750 50  0001 L CNN
F 4 "LCD Graphic Display Modules & Accessories FSTN (+) Transflect White Background" H 8000 2650 50  0001 L CNN "Description"
F 5 "" H 8000 2550 50  0001 L CNN "Height"
F 6 "ELECTRONIC ASSEMBLY" H 8000 2450 50  0001 L CNN "Manufacturer_Name"
F 7 "EA DOGS102W-6" H 8000 2350 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "790-EADOGS102W-6" H 8000 2250 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.com/Search/Refine.aspx?Keyword=790-EADOGS102W-6" H 8000 2150 50  0001 L CNN "Mouser Price/Stock"
F 10 "" H 8000 2050 50  0001 L CNN "RS Part Number"
F 11 "" H 8000 1950 50  0001 L CNN "RS Price/Stock"
	1    6950 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5E9D12AB
P 8450 3850
F 0 "C2" V 8198 3850 50  0000 C CNN
F 1 "C" V 8289 3850 50  0000 C CNN
F 2 "Capacitor_SMD:C_1210_3225Metric_Pad1.33x2.70mm_HandSolder" H 8488 3700 50  0001 C CNN
F 3 "~" H 8450 3850 50  0001 C CNN
	1    8450 3850
	0    1    1    0   
$EndComp
$Comp
L Device:C C1
U 1 1 5E9D2623
P 8450 3650
F 0 "C1" V 8198 3650 50  0000 C CNN
F 1 "C" V 8289 3650 50  0000 C CNN
F 2 "Capacitor_SMD:C_1210_3225Metric_Pad1.33x2.70mm_HandSolder" H 8488 3500 50  0001 C CNN
F 3 "~" H 8450 3650 50  0001 C CNN
	1    8450 3650
	0    1    1    0   
$EndComp
$Comp
L Device:C C3
U 1 1 5E9D351B
P 8450 4050
F 0 "C3" V 8198 4050 50  0000 C CNN
F 1 "C" V 8289 4050 50  0000 C CNN
F 2 "Capacitor_SMD:C_1210_3225Metric_Pad1.33x2.70mm_HandSolder" H 8488 3900 50  0001 C CNN
F 3 "~" H 8450 4050 50  0001 C CNN
	1    8450 4050
	0    1    1    0   
$EndComp
Wire Wire Line
	8150 4050 8300 4050
Wire Wire Line
	8150 3850 8300 3850
Wire Wire Line
	8150 3650 8300 3650
Wire Wire Line
	8150 3950 8750 3950
Wire Wire Line
	8750 3950 8750 3650
Wire Wire Line
	8750 3650 8600 3650
Wire Wire Line
	8600 3850 8650 3850
Wire Wire Line
	8650 3850 8650 3750
Wire Wire Line
	8650 3750 8150 3750
Wire Wire Line
	8150 3550 8850 3550
Wire Wire Line
	8850 3550 8850 4050
Wire Wire Line
	8850 4050 8600 4050
Wire Wire Line
	8150 3450 8850 3450
Wire Wire Line
	8850 3450 8850 3550
Connection ~ 8850 3550
$Comp
L power:+3.3V #PWR0102
U 1 1 5E9DCF9A
P 8650 3250
F 0 "#PWR0102" H 8650 3100 50  0001 C CNN
F 1 "+3.3V" V 8665 3378 50  0000 L CNN
F 2 "" H 8650 3250 50  0001 C CNN
F 3 "" H 8650 3250 50  0001 C CNN
	1    8650 3250
	0    1    1    0   
$EndComp
Wire Wire Line
	8150 3250 8350 3250
Wire Wire Line
	8150 3350 8350 3350
Wire Wire Line
	8350 3350 8350 3250
Connection ~ 8350 3250
Wire Wire Line
	8350 3250 8650 3250
$Comp
L power:+3.3V #PWR0105
U 1 1 5E9F5B6A
P 8500 2100
F 0 "#PWR0105" H 8500 1950 50  0001 C CNN
F 1 "+3.3V" V 8515 2228 50  0000 L CNN
F 2 "" H 8500 2100 50  0001 C CNN
F 3 "" H 8500 2100 50  0001 C CNN
	1    8500 2100
	0    1    1    0   
$EndComp
Wire Wire Line
	8150 2750 8750 2750
Wire Wire Line
	8150 2950 8750 2950
Wire Wire Line
	8150 3050 8750 3050
Wire Wire Line
	8150 3150 8750 3150
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 5EA236FD
P 8400 950
F 0 "H1" H 8500 999 50  0000 L CNN
F 1 "MountingHole_Pad" H 8500 908 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 8400 950 50  0001 C CNN
F 3 "~" H 8400 950 50  0001 C CNN
	1    8400 950 
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 5EA23C46
P 8650 950
F 0 "H2" H 8750 999 50  0000 L CNN
F 1 "MountingHole_Pad" H 8750 908 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 8650 950 50  0001 C CNN
F 3 "~" H 8650 950 50  0001 C CNN
	1    8650 950 
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LD1117S33TR_SOT223 U2
U 1 1 60D0ECB1
P 4450 5400
F 0 "U2" H 4450 5642 50  0000 C CNN
F 1 "LD1117S33TR_SOT223" H 4450 5551 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 4450 5600 50  0001 C CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00000544.pdf" H 4550 5150 50  0001 C CNN
	1    4450 5400
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C6
U 1 1 60D106B1
P 3650 5600
F 0 "C6" H 3768 5646 50  0000 L CNN
F 1 "CP" H 3768 5555 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_5x3" H 3688 5450 50  0001 C CNN
F 3 "~" H 3650 5600 50  0001 C CNN
	1    3650 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C7
U 1 1 60D10D9C
P 5150 5600
F 0 "C7" H 5268 5646 50  0000 L CNN
F 1 "CP" H 5268 5555 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_5x3" H 5188 5450 50  0001 C CNN
F 3 "~" H 5150 5600 50  0001 C CNN
	1    5150 5600
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0101
U 1 1 60D11636
P 3300 5400
F 0 "#PWR0101" H 3300 5250 50  0001 C CNN
F 1 "+5V" V 3315 5528 50  0000 L CNN
F 2 "" H 3300 5400 50  0001 C CNN
F 3 "" H 3300 5400 50  0001 C CNN
	1    3300 5400
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR0106
U 1 1 60D11C4E
P 5550 5400
F 0 "#PWR0106" H 5550 5250 50  0001 C CNN
F 1 "+3.3V" V 5565 5528 50  0000 L CNN
F 2 "" H 5550 5400 50  0001 C CNN
F 3 "" H 5550 5400 50  0001 C CNN
	1    5550 5400
	0    1    1    0   
$EndComp
Wire Wire Line
	3300 5400 3650 5400
Wire Wire Line
	4750 5400 5150 5400
Wire Wire Line
	5150 5450 5150 5400
Connection ~ 5150 5400
Wire Wire Line
	5150 5400 5550 5400
Wire Wire Line
	3650 5450 3650 5400
Connection ~ 3650 5400
Wire Wire Line
	3650 5400 4150 5400
$Comp
L power:GND #PWR0107
U 1 1 60D166E3
P 5150 5750
F 0 "#PWR0107" H 5150 5500 50  0001 C CNN
F 1 "GND" H 5155 5577 50  0000 C CNN
F 2 "" H 5150 5750 50  0001 C CNN
F 3 "" H 5150 5750 50  0001 C CNN
	1    5150 5750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 60D16B7F
P 4450 5700
F 0 "#PWR0108" H 4450 5450 50  0001 C CNN
F 1 "GND" H 4455 5527 50  0000 C CNN
F 2 "" H 4450 5700 50  0001 C CNN
F 3 "" H 4450 5700 50  0001 C CNN
	1    4450 5700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 60D16D7B
P 3650 5750
F 0 "#PWR0109" H 3650 5500 50  0001 C CNN
F 1 "GND" H 3655 5577 50  0000 C CNN
F 2 "" H 3650 5750 50  0001 C CNN
F 3 "" H 3650 5750 50  0001 C CNN
	1    3650 5750
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC245 U1
U 1 1 609A4FDF
P 4000 1650
F 0 "U1" H 4000 2631 50  0000 C CNN
F 1 "74HC245" H 4000 2540 50  0000 C CNN
F 2 "Package_SO:SO-20_12.8x7.5mm_P1.27mm" H 4000 1650 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC245" H 4000 1650 50  0001 C CNN
	1    4000 1650
	1    0    0    -1  
$EndComp
Text GLabel 3500 1550 0    50   Input ~ 0
MOSI
Text GLabel 3500 1450 0    50   Input ~ 0
SCK
Text GLabel 4500 1550 2    50   Input ~ 0
DIS_MOSI
Text GLabel 4500 1450 2    50   Input ~ 0
DIS_SCK
Text GLabel 4500 1150 2    50   Input ~ 0
DIS_CS0
Text GLabel 4500 1250 2    50   Input ~ 0
DIS_RST
Text GLabel 4500 1350 2    50   Input ~ 0
DIS_CD
Text GLabel 8750 3150 2    50   Input ~ 0
DIS_MOSI
Text GLabel 8750 3050 2    50   Input ~ 0
DIS_SCK
Text GLabel 8750 2750 2    50   Input ~ 0
DIS_CS0
Text GLabel 8750 2850 2    50   Input ~ 0
DIS_RST
Text GLabel 8750 2950 2    50   Input ~ 0
DIS_CD
$Comp
L power:GND #PWR0110
U 1 1 609AA903
P 4000 2600
F 0 "#PWR0110" H 4000 2350 50  0001 C CNN
F 1 "GND" V 4005 2472 50  0000 R CNN
F 2 "" H 4000 2600 50  0001 C CNN
F 3 "" H 4000 2600 50  0001 C CNN
	1    4000 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 2450 4000 2600
Wire Wire Line
	3500 1850 3450 1850
Wire Wire Line
	3450 1850 3450 2150
Wire Wire Line
	3450 2450 4000 2450
Connection ~ 4000 2450
Wire Wire Line
	3500 1750 3450 1750
Wire Wire Line
	3450 1750 3450 1850
Connection ~ 3450 1850
Wire Wire Line
	3500 1650 3450 1650
Wire Wire Line
	3450 1650 3450 1750
Connection ~ 3450 1750
Wire Wire Line
	3500 2150 3450 2150
Connection ~ 3450 2150
Wire Wire Line
	3450 2150 3450 2450
$Comp
L power:+3.3V #PWR0111
U 1 1 609AF89A
P 4000 850
F 0 "#PWR0111" H 4000 700 50  0001 C CNN
F 1 "+3.3V" V 4015 978 50  0000 L CNN
F 2 "" H 4000 850 50  0001 C CNN
F 3 "" H 4000 850 50  0001 C CNN
	1    4000 850 
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0112
U 1 1 609B0588
P 3250 2050
F 0 "#PWR0112" H 3250 1900 50  0001 C CNN
F 1 "+3.3V" V 3265 2178 50  0000 L CNN
F 2 "" H 3250 2050 50  0001 C CNN
F 3 "" H 3250 2050 50  0001 C CNN
	1    3250 2050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3250 2050 3500 2050
Wire Wire Line
	8150 2850 8750 2850
$Comp
L Device:C C4
U 1 1 609B3978
P 6450 1150
F 0 "C4" V 6198 1150 50  0000 C CNN
F 1 "100n" V 6289 1150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6488 1000 50  0001 C CNN
F 3 "~" H 6450 1150 50  0001 C CNN
	1    6450 1150
	0    1    1    0   
$EndComp
$Comp
L Device:C C5
U 1 1 609B3F47
P 6450 1550
F 0 "C5" V 6198 1550 50  0000 C CNN
F 1 "100n" V 6289 1550 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6488 1400 50  0001 C CNN
F 3 "~" H 6450 1550 50  0001 C CNN
	1    6450 1550
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR0113
U 1 1 609B42A0
P 6300 1150
F 0 "#PWR0113" H 6300 1000 50  0001 C CNN
F 1 "+3.3V" V 6315 1278 50  0000 L CNN
F 2 "" H 6300 1150 50  0001 C CNN
F 3 "" H 6300 1150 50  0001 C CNN
	1    6300 1150
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR0114
U 1 1 609B488B
P 6300 1550
F 0 "#PWR0114" H 6300 1400 50  0001 C CNN
F 1 "+3.3V" V 6315 1678 50  0000 L CNN
F 2 "" H 6300 1550 50  0001 C CNN
F 3 "" H 6300 1550 50  0001 C CNN
	1    6300 1550
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 609B4E9D
P 9000 3550
F 0 "#PWR0115" H 9000 3300 50  0001 C CNN
F 1 "GND" V 9005 3422 50  0000 R CNN
F 2 "" H 9000 3550 50  0001 C CNN
F 3 "" H 9000 3550 50  0001 C CNN
	1    9000 3550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8850 3550 9000 3550
$Comp
L power:GND #PWR0116
U 1 1 609B6E62
P 6600 1150
F 0 "#PWR0116" H 6600 900 50  0001 C CNN
F 1 "GND" V 6605 1022 50  0000 R CNN
F 2 "" H 6600 1150 50  0001 C CNN
F 3 "" H 6600 1150 50  0001 C CNN
	1    6600 1150
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0117
U 1 1 609B73B5
P 6600 1550
F 0 "#PWR0117" H 6600 1300 50  0001 C CNN
F 1 "GND" V 6605 1422 50  0000 R CNN
F 2 "" H 6600 1550 50  0001 C CNN
F 3 "" H 6600 1550 50  0001 C CNN
	1    6600 1550
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x10 J1
U 1 1 609CAE21
P 1250 3500
F 0 "J1" H 1168 2775 50  0000 C CNN
F 1 "Conn_01x10" H 1168 2866 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x10_P2.54mm_Vertical" H 1250 3500 50  0001 C CNN
F 3 "~" H 1250 3500 50  0001 C CNN
	1    1250 3500
	-1   0    0    1   
$EndComp
Text GLabel 1450 3900 2    50   Input ~ 0
INSTR.BEL
Text GLabel 1450 3700 2    50   Input ~ 0
MOSI
Text GLabel 1450 3600 2    50   Input ~ 0
SCK
Text GLabel 1450 3400 2    50   Input ~ 0
D6
Text GLabel 1450 3300 2    50   Input ~ 0
D7
Text GLabel 1450 3200 2    50   Input ~ 0
D8
$Comp
L power:GND #PWR0118
U 1 1 609CE379
P 1700 3500
F 0 "#PWR0118" H 1700 3250 50  0001 C CNN
F 1 "GND" V 1705 3372 50  0000 R CNN
F 2 "" H 1700 3500 50  0001 C CNN
F 3 "" H 1700 3500 50  0001 C CNN
	1    1700 3500
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR0119
U 1 1 609CED7C
P 1700 3800
F 0 "#PWR0119" H 1700 3650 50  0001 C CNN
F 1 "+5V" V 1715 3928 50  0000 L CNN
F 2 "" H 1700 3800 50  0001 C CNN
F 3 "" H 1700 3800 50  0001 C CNN
	1    1700 3800
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0120
U 1 1 609CF5F9
P 6600 2850
F 0 "#PWR0120" H 6600 2600 50  0001 C CNN
F 1 "GND" V 6605 2722 50  0000 R CNN
F 2 "" H 6600 2850 50  0001 C CNN
F 3 "" H 6600 2850 50  0001 C CNN
	1    6600 2850
	0    1    1    0   
$EndComp
Wire Wire Line
	6950 2850 6800 2850
Wire Wire Line
	6950 2950 6800 2950
Wire Wire Line
	6800 2950 6800 2850
Connection ~ 6800 2850
Wire Wire Line
	6800 2850 6600 2850
$Comp
L Device:CP C8
U 1 1 609D25A1
P 3650 4600
F 0 "C8" H 3768 4646 50  0000 L CNN
F 1 "CP" H 3768 4555 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_5x3" H 3688 4450 50  0001 C CNN
F 3 "~" H 3650 4600 50  0001 C CNN
	1    3650 4600
	1    0    0    -1  
$EndComp
$Comp
L Device:C C9
U 1 1 609D2E32
P 4100 4600
F 0 "C9" H 4215 4646 50  0000 L CNN
F 1 "100n" H 4215 4555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4138 4450 50  0001 C CNN
F 3 "~" H 4100 4600 50  0001 C CNN
	1    4100 4600
	1    0    0    -1  
$EndComp
$Comp
L Device:D_TVS D1
U 1 1 609D436D
P 3000 4600
F 0 "D1" V 2954 4680 50  0000 L CNN
F 1 "SMBJ15CA" V 3045 4680 50  0000 L CNN
F 2 "Diode_SMD:D_SMB" H 3000 4600 50  0001 C CNN
F 3 "~" H 3000 4600 50  0001 C CNN
	1    3000 4600
	0    1    1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 609D53B1
P 6700 2750
F 0 "R1" V 6493 2750 50  0000 C CNN
F 1 "R" V 6584 2750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6630 2750 50  0001 C CNN
F 3 "~" H 6700 2750 50  0001 C CNN
	1    6700 2750
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 609D5D07
P 6700 3050
F 0 "R2" V 6493 3050 50  0000 C CNN
F 1 "R" V 6584 3050 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6630 3050 50  0001 C CNN
F 3 "~" H 6700 3050 50  0001 C CNN
	1    6700 3050
	0    1    1    0   
$EndComp
Wire Wire Line
	6850 2750 6950 2750
Wire Wire Line
	6850 3050 6950 3050
Text GLabel 2650 4350 0    50   Input ~ 0
INSTR.BEL
Wire Wire Line
	1450 3500 1700 3500
Wire Wire Line
	1450 3800 1700 3800
$Comp
L power:GND #PWR0121
U 1 1 609DB96A
P 3000 4800
F 0 "#PWR0121" H 3000 4550 50  0001 C CNN
F 1 "GND" V 3005 4672 50  0000 R CNN
F 2 "" H 3000 4800 50  0001 C CNN
F 3 "" H 3000 4800 50  0001 C CNN
	1    3000 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0122
U 1 1 609DBE75
P 3650 4800
F 0 "#PWR0122" H 3650 4550 50  0001 C CNN
F 1 "GND" V 3655 4672 50  0000 R CNN
F 2 "" H 3650 4800 50  0001 C CNN
F 3 "" H 3650 4800 50  0001 C CNN
	1    3650 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0123
U 1 1 609DC145
P 4100 4800
F 0 "#PWR0123" H 4100 4550 50  0001 C CNN
F 1 "GND" V 4105 4672 50  0000 R CNN
F 2 "" H 4100 4800 50  0001 C CNN
F 3 "" H 4100 4800 50  0001 C CNN
	1    4100 4800
	1    0    0    -1  
$EndComp
Text GLabel 6100 2750 0    50   Input ~ 0
INSTR.BEL
Wire Wire Line
	6100 2750 6300 2750
Wire Wire Line
	6550 3050 6300 3050
Wire Wire Line
	6300 3050 6300 2750
Connection ~ 6300 2750
Wire Wire Line
	6300 2750 6550 2750
Wire Wire Line
	2650 4350 3000 4350
Wire Wire Line
	3000 4350 3000 4450
Wire Wire Line
	3000 4350 3650 4350
Wire Wire Line
	3650 4350 3650 4450
Connection ~ 3000 4350
Wire Wire Line
	3650 4350 4100 4350
Wire Wire Line
	4100 4350 4100 4450
Connection ~ 3650 4350
Wire Wire Line
	4100 4750 4100 4800
Wire Wire Line
	3650 4750 3650 4800
Wire Wire Line
	3000 4750 3000 4800
Text GLabel 3500 1350 0    50   Input ~ 0
D6
Text GLabel 3500 1250 0    50   Input ~ 0
D7
Text GLabel 3500 1150 0    50   Input ~ 0
D8
$Comp
L Connector_Generic:Conn_02x10_Odd_Even J2
U 1 1 60A0C959
P 1550 6550
F 0 "J2" H 1600 7167 50  0000 C CNN
F 1 "Conn_02x10_Odd_Even" H 1600 7076 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x10_P2.54mm_Vertical" H 1550 6550 50  0001 C CNN
F 3 "~" H 1550 6550 50  0001 C CNN
	1    1550 6550
	1    0    0    -1  
$EndComp
Text GLabel 1850 6150 2    50   Input ~ 0
INSTR.BEL
$Comp
L power:+5V #PWR0103
U 1 1 60A10534
P 1850 6250
F 0 "#PWR0103" H 1850 6100 50  0001 C CNN
F 1 "+5V" V 1865 6378 50  0000 L CNN
F 2 "" H 1850 6250 50  0001 C CNN
F 3 "" H 1850 6250 50  0001 C CNN
	1    1850 6250
	0    1    1    0   
$EndComp
Text GLabel 1850 6350 2    50   Input ~ 0
MOSI
Text GLabel 1350 6350 0    50   Input ~ 0
SCK
$Comp
L power:GND #PWR0104
U 1 1 60A10BC8
P 1850 6450
F 0 "#PWR0104" H 1850 6200 50  0001 C CNN
F 1 "GND" V 1855 6322 50  0000 R CNN
F 2 "" H 1850 6450 50  0001 C CNN
F 3 "" H 1850 6450 50  0001 C CNN
	1    1850 6450
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0124
U 1 1 60A11165
P 1350 7050
F 0 "#PWR0124" H 1350 6800 50  0001 C CNN
F 1 "GND" V 1355 6922 50  0000 R CNN
F 2 "" H 1350 7050 50  0001 C CNN
F 3 "" H 1350 7050 50  0001 C CNN
	1    1350 7050
	0    1    1    0   
$EndComp
Text GLabel 1350 6550 0    50   Input ~ 0
D6
Text GLabel 1850 6550 2    50   Input ~ 0
D7
Text GLabel 1350 6650 0    50   Input ~ 0
D8
$EndSCHEMATC
