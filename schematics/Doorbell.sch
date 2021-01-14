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
L Device:Battery VCC
U 1 1 5FFFC771
P 1600 2550
F 0 "VCC" H 1708 2596 50  0000 L CNN
F 1 "3.3V" H 1708 2505 50  0000 L CNN
F 2 "" V 1600 2610 50  0001 C CNN
F 3 "~" V 1600 2610 50  0001 C CNN
	1    1600 2550
	1    0    0    -1  
$EndComp
$Comp
L RF_Module:ESP32-WROOM-32 ESP32_1
U 1 1 5FFFDB6B
P 3900 2600
F 0 "ESP32_1" H 3900 4181 50  0000 C CNN
F 1 "ESP32-WROOM-32" H 3900 4090 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 3900 1100 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf" H 3600 2650 50  0001 C CNN
	1    3900 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 1200 3900 1200
Wire Wire Line
	1600 2750 1600 4000
Wire Wire Line
	1600 4000 3900 4000
Wire Wire Line
	1600 1200 1600 2350
$Comp
L Device:R R1
U 1 1 600138B5
P 5400 2550
F 0 "R1" V 5193 2550 50  0000 C CNN
F 1 "100Ω" V 5284 2550 50  0000 C CNN
F 2 "" V 5330 2550 50  0001 C CNN
F 3 "~" H 5400 2550 50  0001 C CNN
	1    5400 2550
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push_LED SW1
U 1 1 60027558
P 5900 2250
F 0 "SW1" H 5900 2635 50  0000 C CNN
F 1 "SW_Push_LED_NO" H 5900 2544 50  0000 C CNN
F 2 "" H 5900 2550 50  0001 C CNN
F 3 "~" H 5900 2550 50  0001 C CNN
	1    5900 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 2300 5250 2300
Wire Wire Line
	5250 2300 5250 2550
Wire Wire Line
	5550 2550 5700 2550
Wire Wire Line
	5700 2550 5700 2250
Wire Wire Line
	6100 2250 6100 2700
Wire Wire Line
	6100 2700 4750 2700
Wire Wire Line
	4750 2700 4750 2400
Wire Wire Line
	4750 2400 4500 2400
Wire Wire Line
	4500 2100 5700 2100
Wire Wire Line
	5700 2100 5700 2150
Wire Wire Line
	4500 2200 4950 2200
Wire Wire Line
	4950 2200 4950 1750
Wire Wire Line
	4950 1750 6400 1750
Wire Wire Line
	6400 1750 6400 2150
Wire Wire Line
	6400 2150 6100 2150
Text Notes 7350 7500 0    50   ~ 0
ESP32 Doorbell with Slack integration
Text Notes 8200 7650 0    50   ~ 0
14 January 2021
$EndSCHEMATC
