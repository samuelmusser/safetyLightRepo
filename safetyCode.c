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

//TODO Arduino register definitions

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

    
    //TODO init pins for Temp Sensor
    
    //TODO init LoRa Module

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

    //TODO: get 50 voltage samples and take average

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
        //TODO: power off for 30 mins
        break;
        case 1:
        //TODO: power off for 15 mins
        break;
        case 2:
        //TODO: power off for 5 mins
        break; 
    }

    //TODO: turn on MOSFET
}


int main (int argc, int argv[])
{

    

    return 0;
}
