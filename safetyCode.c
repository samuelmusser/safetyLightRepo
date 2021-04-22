/*
-----------------------------------------------------------------------
Project: Safety Light (Device/Receiver)
Authors: Chris Bharucha, Sam Musser
Due Date: May 9, 2021
Version: 0.2
Objective:
Parse temperature data and network microcontrollers via Arduino
nano and LoRa module within embedded road light to receiver on road signs
----------------------------------------------------------------------
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <SPI.h>

//TODO Arduino register definitions


/* Possible find ID functions for Arduino site:
char sID[7];

void setup()
{
    Serial.begin(9600);
    for (int i=0; i<6; i++)
    {
        sID[i] = EEPROM.read(i);
    }
}

void loop()
{
    Serial.printlnsID(sID);
}
*/

//Object Structure with Identifier and temp data holder
struct information
{
    int temp;
    int identity;

};


/*
Tick function to be called in wait
*/
void tick(int ticks)
{
    volatile int cntDwn;
    for (cntDwn = 0; cntDwn < ticks; cntDwn++)
    {}
}


/*
Wait function with input of seconds
*/
void wait(int sec)
{
    //TODO
}


/*
Initialization Method opens access to all necessary devices
and interfaces necessary
*/
void system_init()
{

    //TODO init inner interfacing for #ArduinoNanoMC
    //MOSI/D11 pin 29, MISO/D12 = pin 30 , SCK/D13 = pin 1
    
    //TODO init pins for Temp Sensor
    //MOSFET in = INT0/D2 pin 20, input in ADC0/A0 pin 4
    
    //TODO init LoRa Module
    //reset pin on Arduino to lora is pin 27

}


/*
Read and Write Functions for the Interfacing
*/
void read()
{

    //TODO

}


void write()
{
    //TODO
}


/*
Temeperature Conversion Method reads in voltage values, takes the average
of those voltages and converts the resulting voltage into a temperature
*/
int tempConversion()
{
    int temp = 0;
    int R0 = 100000;    //resistor in series with thermistor is 100k ohm
    int Rt = 5000;  //NTC thermistor resistance value at 25 degrees C
    

    /*
    Calculates The Temperature Directly:
    temp = 1/(1/T0 + 1/B * ln(R/R0));

    Calculates Ouput Voltage:
    Vo = Vs * (R0 / ( Rt + R0 ));
    */

    //TODO: get 50 voltage samples and take average
    for (int i = 0; i < 50; i++)
    {
        
    }
    //TODO: convert averaged voltage into temperature
    
    
    return temp;
}


/*
Sleep Method takes an input from the output of the Receiver's checkTemp Method and
waits a predetermined amount of time
*/
void sleep(int x)
{
    //TODO: turn off MOSFET
    
    switch(x)
    {
        case 0:
        //power off for 30 mins
        wait(1800);
        break;
        case 1:
        //power off for 15 mins
        wait(900);
        break;
        case 2:
        //power off for 5 mins
        wait(300);
        break; 
    }

    //TODO: turn on MOSFET
}


int main (int argc, int argv[])
{
    struct information info;

    info.identity = rand();

    while(1)
    {
        info.temp = tempConversion();

        //TODO read and write to LoRa

    }
    return 0;
}
