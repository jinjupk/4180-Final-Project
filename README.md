# Contactless Car Unlocking System [ECE 4180 Final Project]

Pearl Park \
Lawrence Ro \
Swarna Shah 

## Overview

The Contactless Car Unlocking System allows a user to unlock a car with a specific NFC card instead of using a physical key. In the following demonstration, a Buzzcard student ID is scanned at the sensor location to remotely press the unlock button inside of the car using a 5V relay. The system is powered by the car’s battery which is stepped down to a low enough voltage with a voltage regulator. All components are interfaced through a custom printed circuit board (PCB) and housed in a 3D printed enclosure.

![Finished_enclosure](https://github.com/jinjupk/4180-Final-Project/assets/84649940/3e1d07ac-136f-4941-82bd-13aae0f39d61)

## Components
- MBED LPC1768
- uLCD-144-G2 128 by 128 Smart Color LCD
- 5V Relay
- NFC reader
- Custom PCB
- 3D printed housing

## Hardware
- 4-layer PCB
- LTM8053 Switching Regulator (integrated inductor, 6A max output current)
- Dual LP38692 LDO Voltage Regulator (1A output, separate for servo and microcontroller power)
  
<img width="519" alt="image" src="https://github.com/jinjupk/4180-Final-Project/assets/84649940/daebe276-06e1-489d-957f-789a28a51bac">

<img width="549" alt="image" src="https://github.com/jinjupk/4180-Final-Project/assets/84649940/6131d9c1-6522-4b9e-b837-db9dbf526d21">

<img width="515" alt="image" src="https://github.com/jinjupk/4180-Final-Project/assets/84649940/b8624fc9-eb10-44dd-94dc-f7f1fa32fb53">

<img width="617" alt="image" src="https://github.com/jinjupk/4180-Final-Project/assets/84649940/1662e17f-f3a3-4a4a-bc73-dae7046b8dbb">

## Software

<img width="772" alt="image" src="https://github.com/jinjupk/4180-Final-Project/assets/84649940/6ec4ba2e-4283-4992-b49e-cfa5d3996012">
- Three threads
- Main - Initializes uLCD and NFC scanner threads
- uLCD - Displays invalid card and card accepted messages according to card scanned
- NFC Reader - Asks scanner for ID of card scanned; checks against known ID

## Video Demo
[TO BE ADDED]

