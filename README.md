# safetyLightRepo

## Overview
The software side of the project is an implementation of power saving features, temperature data recording, processing, parsing, and finally the networking between itself and the receiver on the road sign. It provides communication capabilities between the Lora module of each safety light and the Lora module of the receiver. 

It uses this communication to send data between the safety light and the receiver. Namely, it sends an identification number and the temperature average of each saftey light to the receiver, the receiver sends back a value for the safety light to determine how long to wait until the next temperature check.

The safety light software handles taking in voltages from a thermistor and calculating the average temperature based on this, generating a unique identification number, scheduling wait times between measurements, and sending the data to the receiver. The receiver software handles storing temperature data from each saftey light, deciding the wait-time value for the safety lights and message to send to the road sign, and sending the wait-time value to the safety lights.

## Usage
For the current set up, assuming hardware is assembled accordingly, both the receiver and safety light devices need to have the software downloaded onto them from a computer to run. We used the arduino online IDE to create and run the software on the device. 

Libraries Used:
1. Standard C libraries 
2. Arduino LoRa library by sandeepmistry (MIT LICENSE)
