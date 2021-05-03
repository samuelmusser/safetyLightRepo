/*
-----------------------------------------------------------------------
Project: Safety Light (Device/Receiver)
Authors: Chris Bharucha, Sam Musser
Due Date: May 9, 2021
Version: 0.9
Objective:
[Receiver]
Collect temperature data and network microcontrollers via Arduino
nano and LoRa module within embedded road light to receiver on road signs
to then implement power save options or display message
----------------------------------------------------------------------
*/

//Included Libraries
#include <stdlib.h>
#include <stdio.h>
#include <SPI.h>
#include <LoRa.h>

//Object Structure with Identifier and temp data holder
struct information
{
    int temp;
    int identity = 0;
};

float getTemp(struct information light)
{
    return light.temp;
}

/*
This method is used in the functionalityCheck method to sort the array of temperatures in ascending order
*/
static int intCompare(const void *x1, const void *x2)
{
    int int_1 = *((int*)x1);
    int int_2 = *((int*)x2);

    if (int_1 == int_2)
    {
        return 0;
    }
    else if (int_1 < int_2)
    {
        return -1;
    }
    else 
    {
        return 1;
    }
}

/*
The functionalityCheck method takes the array of safety light objects and computes the range of 
the temperatures to determine whether or not there is an error in a Safety Light.
*/
void functionalityCheck(struct information lights[])
{
    float temps[15];
    int range = 0;

    for (int i=0; i<15; i++)
    {
        temps[i] = getTemp(lights[i]);
    }

    //sorting the array
    qsort(temps, 15,sizeof(int),intCompare);

    int tempsSize = sizeof(temps);
    range = temps[tempsSize - 1] - temps[0];

    if (range > 8)
    {
        Serial.println("*****");
        Serial.println("ERROR");
        Serial.println("*****");
    }
    else
    {
        //do nothing (no error)
    }

}

/*
The tempAverage method takes the array of safety light objects and computes and returns the average 
of their temperatures.
*/
float tempAverage(struct information lights[])
{
    float average = 0;
    for (int i=0; i<sizeof(lights); i++)
    {
        average += getTemp(lights[i]);
    }
    return average / sizeof(lights);
}

/*
The tempCheck method takes the averaged temperatures as an input and determines how long the
safety lights should power off for and whether or not to display to the VMS road sign.
*/
int tempCheck(float tempAverage)
{
    if (tempAverage > 50)
    {
        return 0;
    }
    else if ((tempAverage > 40) && (tempAverage < 50))
    {
        return 1;
    }
    else
    {
      //if had testing with actual VMS sign would work, but for now prints to serial
      //(ie would be Ethernet to sign)
        Serial.print("Roads maybe icy, don't drive spicy!");
        return 2;
    }
}

//------------------------------------------------------------------
//Arduino implementation Structure and LoRa read/write
struct information slights[20];

void setup() {
  Serial.begin(9600);
  while (!Serial);

}

void loop() {
  //parses safety Light information and responds
  communicate(LoRa.parsePacket());

}

//tells safety Lights how long to save battery life and then does the same
void talk(int waitNum)
{
  // send packet with key phrase and power number
    LoRa.beginPacket();
    LoRa.print("PowerSave," + String(waitNum));
    LoRa.endPacket();
  
}

//listens for LoRa from Safety Lights and saves data for parsing
void communicate(int packetSize)
{
  String message = "";
  String pass;
  int ident;
  int tempTemp;
  
  int index;
  int index2;
  
  //where there is a message or not
  if (packetSize) {

    // read packet
    while (LoRa.available()) {
      message += (char)LoRa.read();
    }
  
    index = message.indexOf(',');
    index2 = message.indexOf(',', index + 1);
  
    pass = message.substring(0, index);
    ident = (message.substring(index + 1, index2)).toInt();
    tempTemp = (message.substring(index2 + 1)).toInt();
  
    //if code and ID matches or is new, it is added to data storage
    if (pass.equals("ReadMe"))
    {
      for (int h = 0; h < 20; h++)
      {
        if ((slights[h].identity = 0) || (slights[h].identity = ident)){
          slights[h].identity = ident;
          slights[h].temp = tempTemp;
        }
      }
    
    }
    
    //averages the data and then sends out number correlating to power saving on lights
    talk(tempCheck(tempAverage(slights)));
  }
}
