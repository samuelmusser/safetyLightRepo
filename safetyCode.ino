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

//Included Libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SPI.h>

//--------------------------------------------------------------------
//Project Methods

//Object Structure with Identifier and temp data holder
struct information
{
    int temp;
    int identity;

};

/*
Temeperature Conversion Method reads in voltage values, takes the average
of those voltages and converts the resulting voltage into a temperature
*/
int tempConversion()
{
    float temp = 0;
    float voltage = 0;
    
    //taking 50 voltage samples from thermistor and finding their sum
    for (int i = 0; i < 50; i++)
    {
        int sensorValue = analogRead(A0);
        //converting the analog reading to a voltage
        voltage += sensorValue * (5.0/1023.0);
    }

    //take average of voltage sample
    voltage = voltage/50.0;

    //TODO: convert averaged voltage into temperature
    //temp = (insert formula)
    
    return temp;
}


/*
Sleep Method takes an input from the output of the Receiver's checkTemp Method and
waits a predetermined amount of time
*/
void sleep(int x)
{
    //turning off MOSFET
    digitalWrite(20,LOW);
    
    switch(x)
    {
        case 0:
        //power off for 30 mins
        delay(1800000);
        break;
        case 1:
        //power off for 15 mins
        delay(900000);
        break;
        case 2:
        //power off for 5 mins
        delay(300000);
        break; 
    }

    //turning on MOSFET
    digitalWrite(20,HIGH);
}

//------------------------------------------------------------------
//Arduino implementation Structure

struct information info;

void setup() 
{
    info.identity = rand();

    //begins SPI clock
    SPI.begin();

    //setting for ss pin
    pinMode(28, OUTPUT);

    //setting voltage divider as input, and mosfet as output:
    pinMode(4,INPUT);
    pinMode(20,OUTPUT);
}

void loop() 
{
        info.temp = tempConversion();

        //TODO send temp data to LoRa

        //TODO read wait data from LoRa

        //sleep(data from TODO above );
}

/*
void writeLora()
{
    ss low
    
    SPI.transfer(info);

    ss high
}

void readLora()
{
    

    
}
*/

// miso pin 30
// mosi pin  29
// clk spi pin 1
// ss spi pin 28
// reset digital 9