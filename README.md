# Contactless Car Unlocking System [ECE 4180 Final Project]

Pearl Park \
Lawrence Ro \
Swarna Shah 

## Overview

The Contactless Car Unlocking System allows a user to unlock a car with a specific NFC card instead of using a physical key. In the following demonstration, a Buzzcard student ID is scanned at the sensor location to remotely press the unlock button inside of the car using a 5V relay. The system is powered by the car’s battery which is stepped down to a low enough voltage with a voltage regulator. All components are interfaced through a custom printed circuit board (PCB) and housed in a 3D printed enclosure.

![alt text](https://github.com/jinjupk/4180-Final-Project/blob/main/media/Finished_enclosure.jpeg)

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

## Video Demo

