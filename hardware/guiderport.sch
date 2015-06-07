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
LIBS:special
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
LIBS:guiderport-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "22 oct 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L USB J1
U 1 1 544669F1
P 1600 3850
F 0 "J1" H 1550 4250 60  0000 C CNN
F 1 "USB" V 1350 4000 60  0000 C CNN
F 2 "" H 1600 3850 60  0000 C CNN
F 3 "" H 1600 3850 60  0000 C CNN
	1    1600 3850
	1    0    0    -1  
$EndComp
$Comp
L CONN_6 P2
U 1 1 54466A0E
P 10800 4750
F 0 "P2" V 10750 4750 60  0000 C CNN
F 1 "Autoguide" V 10850 4750 60  0000 C CNN
F 2 "" H 10800 4750 60  0000 C CNN
F 3 "" H 10800 4750 60  0000 C CNN
	1    10800 4750
	1    0    0    1   
$EndComp
$Comp
L LED D1
U 1 1 54466A21
P 7650 2900
F 0 "D1" H 7650 3000 50  0000 C CNN
F 1 "LED" H 7650 2800 50  0000 C CNN
F 2 "~" H 7650 2900 60  0000 C CNN
F 3 "~" H 7650 2900 60  0000 C CNN
	1    7650 2900
	0    1    1    0   
$EndComp
$Comp
L LED D2
U 1 1 54466A39
P 8050 2900
F 0 "D2" H 8050 3000 50  0000 C CNN
F 1 "LED" H 8050 2800 50  0000 C CNN
F 2 "~" H 8050 2900 60  0000 C CNN
F 3 "~" H 8050 2900 60  0000 C CNN
	1    8050 2900
	0    1    1    0   
$EndComp
$Comp
L LED D3
U 1 1 54466A3F
P 8450 2900
F 0 "D3" H 8450 3000 50  0000 C CNN
F 1 "LED" H 8450 2800 50  0000 C CNN
F 2 "~" H 8450 2900 60  0000 C CNN
F 3 "~" H 8450 2900 60  0000 C CNN
	1    8450 2900
	0    1    1    0   
$EndComp
$Comp
L LED D4
U 1 1 54466A45
P 8850 2900
F 0 "D4" H 8850 3000 50  0000 C CNN
F 1 "LED" H 8850 2800 50  0000 C CNN
F 2 "~" H 8850 2900 60  0000 C CNN
F 3 "~" H 8850 2900 60  0000 C CNN
	1    8850 2900
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 54466A4D
P 7650 2450
F 0 "R1" V 7730 2450 40  0000 C CNN
F 1 "390" V 7657 2451 40  0000 C CNN
F 2 "~" V 7580 2450 30  0000 C CNN
F 3 "~" H 7650 2450 30  0000 C CNN
	1    7650 2450
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 54466A5F
P 8050 2450
F 0 "R2" V 8130 2450 40  0000 C CNN
F 1 "390" V 8057 2451 40  0000 C CNN
F 2 "~" V 7980 2450 30  0000 C CNN
F 3 "~" H 8050 2450 30  0000 C CNN
	1    8050 2450
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 54466A69
P 8450 2450
F 0 "R3" V 8530 2450 40  0000 C CNN
F 1 "390" V 8457 2451 40  0000 C CNN
F 2 "~" V 8380 2450 30  0000 C CNN
F 3 "~" H 8450 2450 30  0000 C CNN
	1    8450 2450
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 54466A70
P 8850 2450
F 0 "R4" V 8930 2450 40  0000 C CNN
F 1 "390" V 8857 2451 40  0000 C CNN
F 2 "~" V 8780 2450 30  0000 C CNN
F 3 "~" H 8850 2450 30  0000 C CNN
	1    8850 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 2200 8850 2200
Connection ~ 8050 2200
Connection ~ 8450 2200
$Comp
L PC847 IC1
U 4 1 54466BD8
P 9200 3600
F 0 "IC1" H 9010 3790 40  0000 C CNN
F 1 "PC847" H 9350 3410 40  0000 C CNN
F 2 "DIP16" H 9010 3420 30  0000 C CIN
F 3 "~" H 9200 3600 60  0000 C CNN
	4    9200 3600
	1    0    0    -1  
$EndComp
$Comp
L PC847 IC1
U 3 1 54466C1C
P 8800 4100
F 0 "IC1" H 8610 4290 40  0000 C CNN
F 1 "PC847" H 8950 3910 40  0000 C CNN
F 2 "DIP16" H 8610 3920 30  0000 C CIN
F 3 "~" H 8800 4100 60  0000 C CNN
	3    8800 4100
	1    0    0    -1  
$EndComp
$Comp
L PC847 IC1
U 2 1 54466C24
P 8400 4600
F 0 "IC1" H 8210 4790 40  0000 C CNN
F 1 "PC847" H 8550 4410 40  0000 C CNN
F 2 "DIP16" H 8210 4420 30  0000 C CIN
F 3 "~" H 8400 4600 60  0000 C CNN
	2    8400 4600
	1    0    0    -1  
$EndComp
$Comp
L PC847 IC1
U 1 1 54466C36
P 8000 5100
F 0 "IC1" H 7810 5290 40  0000 C CNN
F 1 "PC847" H 8150 4910 40  0000 C CNN
F 2 "DIP16" H 7810 4920 30  0000 C CIN
F 3 "~" H 8000 5100 60  0000 C CNN
	1    8000 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 3100 7650 5000
Wire Wire Line
	8050 3100 8050 4500
Wire Wire Line
	8450 3100 8450 4000
Wire Wire Line
	8850 3100 8850 3500
Wire Wire Line
	8350 5200 10200 5200
Wire Wire Line
	8750 4700 8750 5200
Connection ~ 8750 5200
Wire Wire Line
	9150 4200 9150 5200
Connection ~ 9150 5200
Wire Wire Line
	9550 3700 9550 5200
Connection ~ 9550 5200
Wire Wire Line
	8350 5000 10050 5000
Wire Wire Line
	10050 5000 10050 4800
Wire Wire Line
	10050 4800 10450 4800
Wire Wire Line
	9550 3500 10050 3500
Wire Wire Line
	10050 3500 10050 4500
Wire Wire Line
	10050 4500 10450 4500
Wire Wire Line
	9150 4000 9950 4000
Wire Wire Line
	9950 4000 9950 4600
Wire Wire Line
	9950 4600 10450 4600
Wire Wire Line
	8750 4500 9850 4500
Wire Wire Line
	9850 4500 9850 4700
Wire Wire Line
	9850 4700 10450 4700
$Comp
L +5V #PWR01
U 1 1 54466E30
P 7650 2200
F 0 "#PWR01" H 7650 2290 20  0001 C CNN
F 1 "+5V" H 7650 2290 30  0000 C CNN
F 2 "" H 7650 2200 60  0000 C CNN
F 3 "" H 7650 2200 60  0000 C CNN
	1    7650 2200
	1    0    0    -1  
$EndComp
$Comp
L AT90USB162-A IC2
U 1 1 54467322
P 4150 4050
F 0 "IC2" H 3250 5325 40  0000 L BNN
F 1 "AT90USB162-A" H 4575 2725 40  0000 L BNN
F 2 "TQFP32" H 4150 4050 30  0000 C CIN
F 3 "" H 4150 4050 60  0000 C CNN
	1    4150 4050
	1    0    0    -1  
$EndComp
$Comp
L CONN_3X2 P1
U 1 1 54467369
P 6400 2550
F 0 "P1" H 6400 2800 50  0000 C CNN
F 1 "ISP" V 6400 2600 40  0000 C CNN
F 2 "" H 6400 2550 60  0000 C CNN
F 3 "" H 6400 2550 60  0000 C CNN
	1    6400 2550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 544673A4
P 4150 5450
F 0 "#PWR02" H 4150 5450 30  0001 C CNN
F 1 "GND" H 4150 5380 30  0001 C CNN
F 2 "" H 4150 5450 60  0000 C CNN
F 3 "" H 4150 5450 60  0000 C CNN
	1    4150 5450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 544673B3
P 900 4450
F 0 "#PWR03" H 900 4450 30  0001 C CNN
F 1 "GND" H 900 4380 30  0001 C CNN
F 2 "" H 900 4450 60  0000 C CNN
F 3 "" H 900 4450 60  0000 C CNN
	1    900  4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 4200 900  4200
Wire Wire Line
	900  4200 900  4450
Wire Wire Line
	5200 4400 6450 4400
Wire Wire Line
	6450 4400 6450 3700
Wire Wire Line
	6450 3700 8850 3700
Wire Wire Line
	5200 4500 6550 4500
Wire Wire Line
	6550 4500 6550 4200
Wire Wire Line
	6550 4200 8450 4200
Wire Wire Line
	5200 4600 6550 4600
Wire Wire Line
	6550 4600 6550 4700
Wire Wire Line
	6550 4700 8050 4700
Wire Wire Line
	5200 4700 6450 4700
Wire Wire Line
	6450 4700 6450 5200
Wire Wire Line
	6450 5200 7650 5200
$Comp
L C C2
U 1 1 544674BC
P 3650 2300
F 0 "C2" H 3650 2400 40  0000 L CNN
F 1 "0.1u" H 3656 2215 40  0000 L CNN
F 2 "~" H 3688 2150 30  0000 C CNN
F 3 "~" H 3650 2300 60  0000 C CNN
	1    3650 2300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 544674CB
P 3650 2500
F 0 "#PWR04" H 3650 2500 30  0001 C CNN
F 1 "GND" H 3650 2430 30  0001 C CNN
F 2 "" H 3650 2500 60  0000 C CNN
F 3 "" H 3650 2500 60  0000 C CNN
	1    3650 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 2100 4300 2100
Wire Wire Line
	4000 2100 4000 2650
$Comp
L +5V #PWR05
U 1 1 5446759D
P 3650 2100
F 0 "#PWR05" H 3650 2190 20  0001 C CNN
F 1 "+5V" H 3650 2190 30  0000 C CNN
F 2 "" H 3650 2100 60  0000 C CNN
F 3 "" H 3650 2100 60  0000 C CNN
	1    3650 2100
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR06
U 1 1 544675AC
P 900 3900
F 0 "#PWR06" H 900 3990 20  0001 C CNN
F 1 "+5V" H 900 3990 30  0000 C CNN
F 2 "" H 900 3900 60  0000 C CNN
F 3 "" H 900 3900 60  0000 C CNN
	1    900  3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 4050 900  4050
Wire Wire Line
	900  4050 900  3900
$Comp
L GND #PWR07
U 1 1 5446761A
P 3000 4900
F 0 "#PWR07" H 3000 4900 30  0001 C CNN
F 1 "GND" H 3000 4830 30  0001 C CNN
F 2 "" H 3000 4900 60  0000 C CNN
F 3 "" H 3000 4900 60  0000 C CNN
	1    3000 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 4600 3000 4600
Wire Wire Line
	3000 4600 3000 4900
$Comp
L +5V #PWR08
U 1 1 5446765B
P 2850 3750
F 0 "#PWR08" H 2850 3840 20  0001 C CNN
F 1 "+5V" H 2850 3840 30  0000 C CNN
F 2 "" H 2850 3750 60  0000 C CNN
F 3 "" H 2850 3750 60  0000 C CNN
	1    2850 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 3850 2850 3850
Wire Wire Line
	2850 3850 2850 3750
$Comp
L C C3
U 1 1 5446769E
P 2600 4600
F 0 "C3" H 2600 4700 40  0000 L CNN
F 1 "1u" H 2606 4515 40  0000 L CNN
F 2 "~" H 2638 4450 30  0000 C CNN
F 3 "~" H 2600 4600 60  0000 C CNN
	1    2600 4600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 544676AD
P 2600 4800
F 0 "#PWR09" H 2600 4800 30  0001 C CNN
F 1 "GND" H 2600 4730 30  0001 C CNN
F 2 "" H 2600 4800 60  0000 C CNN
F 3 "" H 2600 4800 60  0000 C CNN
	1    2600 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 4400 2600 4400
$Comp
L R R5
U 1 1 544677BF
P 2200 4050
F 0 "R5" V 2280 4050 40  0000 C CNN
F 1 "22" V 2207 4051 40  0000 C CNN
F 2 "~" V 2130 4050 30  0000 C CNN
F 3 "~" H 2200 4050 30  0000 C CNN
	1    2200 4050
	0    1    1    0   
$EndComp
$Comp
L R R6
U 1 1 544677CE
P 2200 4200
F 0 "R6" V 2280 4200 40  0000 C CNN
F 1 "22" V 2207 4201 40  0000 C CNN
F 2 "~" V 2130 4200 30  0000 C CNN
F 3 "~" H 2200 4200 30  0000 C CNN
	1    2200 4200
	0    1    1    0   
$EndComp
Wire Wire Line
	2450 4050 3100 4050
Wire Wire Line
	2450 4200 2750 4200
Wire Wire Line
	2750 4200 2750 4150
Wire Wire Line
	2750 4150 3100 4150
$Comp
L CAPAPOL C1
U 1 1 5446788F
P 1200 2300
F 0 "C1" H 1250 2400 40  0000 L CNN
F 1 "10u" H 1250 2200 40  0000 L CNN
F 2 "~" H 1300 2150 30  0000 C CNN
F 3 "~" H 1200 2300 300 0000 C CNN
	1    1200 2300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 544678A8
P 1200 2500
F 0 "#PWR010" H 1200 2500 30  0001 C CNN
F 1 "GND" H 1200 2430 30  0001 C CNN
F 2 "" H 1200 2500 60  0000 C CNN
F 3 "" H 1200 2500 60  0000 C CNN
	1    1200 2500
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR011
U 1 1 544678B7
P 1200 2100
F 0 "#PWR011" H 1200 2190 20  0001 C CNN
F 1 "+5V" H 1200 2190 30  0000 C CNN
F 2 "" H 1200 2100 60  0000 C CNN
F 3 "" H 1200 2100 60  0000 C CNN
	1    1200 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 2600 2900 2600
Wire Wire Line
	2900 2600 2900 3000
Wire Wire Line
	2900 3000 3100 3000
Wire Wire Line
	6000 2500 5300 2500
Wire Wire Line
	5300 2500 5300 3100
Wire Wire Line
	5300 3100 5200 3100
$Comp
L +5V #PWR012
U 1 1 5446D357
P 6800 2200
F 0 "#PWR012" H 6800 2290 20  0001 C CNN
F 1 "+5V" H 6800 2290 30  0000 C CNN
F 2 "" H 6800 2200 60  0000 C CNN
F 3 "" H 6800 2200 60  0000 C CNN
	1    6800 2200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 5446D366
P 6800 2800
F 0 "#PWR013" H 6800 2800 30  0001 C CNN
F 1 "GND" H 6800 2730 30  0001 C CNN
F 2 "" H 6800 2800 60  0000 C CNN
F 3 "" H 6800 2800 60  0000 C CNN
	1    6800 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 2600 6800 2800
Wire Wire Line
	6800 2200 6800 2400
Wire Wire Line
	6000 2400 5400 2400
Wire Wire Line
	5400 2400 5400 3300
Wire Wire Line
	5400 3300 5200 3300
Wire Wire Line
	5200 3200 6950 3200
Wire Wire Line
	6950 3200 6950 2500
Wire Wire Line
	6950 2500 6800 2500
$Comp
L CRYSTAL X1
U 1 1 5446D478
P 2600 3200
F 0 "X1" H 2600 3350 60  0000 C CNN
F 1 "8MHz" H 2600 3050 60  0000 C CNN
F 2 "~" H 2600 3200 60  0000 C CNN
F 3 "~" H 2600 3200 60  0000 C CNN
	1    2600 3200
	0    1    1    0   
$EndComp
Wire Wire Line
	2600 2900 2800 2900
Wire Wire Line
	2800 2900 2800 3300
Wire Wire Line
	2800 3300 3100 3300
Wire Wire Line
	3100 3500 2600 3500
$Comp
L C C4
U 1 1 5446D536
P 2400 2900
F 0 "C4" H 2400 3000 40  0000 L CNN
F 1 "22p" H 2406 2815 40  0000 L CNN
F 2 "~" H 2438 2750 30  0000 C CNN
F 3 "~" H 2400 2900 60  0000 C CNN
	1    2400 2900
	0    1    1    0   
$EndComp
$Comp
L C C5
U 1 1 5446D545
P 2400 3500
F 0 "C5" H 2400 3600 40  0000 L CNN
F 1 "22p" H 2406 3415 40  0000 L CNN
F 2 "~" H 2438 3350 30  0000 C CNN
F 3 "~" H 2400 3500 60  0000 C CNN
	1    2400 3500
	0    1    1    0   
$EndComp
$Comp
L GND #PWR014
U 1 1 5446D554
P 2200 3650
F 0 "#PWR014" H 2200 3650 30  0001 C CNN
F 1 "GND" H 2200 3580 30  0001 C CNN
F 2 "" H 2200 3650 60  0000 C CNN
F 3 "" H 2200 3650 60  0000 C CNN
	1    2200 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 2900 2200 3650
Connection ~ 2200 3500
Wire Wire Line
	4300 2100 4300 2650
Connection ~ 4000 2100
$Comp
L GND #PWR015
U 1 1 5446DE84
P 1200 4450
F 0 "#PWR015" H 1200 4450 30  0001 C CNN
F 1 "GND" H 1200 4380 30  0001 C CNN
F 2 "" H 1200 4450 60  0000 C CNN
F 3 "" H 1200 4450 60  0000 C CNN
	1    1200 4450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 5446DE93
P 1950 4450
F 0 "#PWR016" H 1950 4450 30  0001 C CNN
F 1 "GND" H 1950 4380 30  0001 C CNN
F 2 "" H 1950 4450 60  0000 C CNN
F 3 "" H 1950 4450 60  0000 C CNN
	1    1950 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 4300 1200 4450
Wire Wire Line
	1950 4300 1950 4450
Wire Wire Line
	10450 4900 10200 4900
Wire Wire Line
	10200 4900 10200 5200
$EndSCHEMATC
