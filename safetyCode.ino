/*
-----------------------------------------------------------------------
Project: Safety Light (Device/Receiver)
Authors: Chris Bharucha, Sam Musser
Due Date: May 9, 2021
Version: 0.9
Objective:
[Device]
Sense temperature data and network microcontrollers via Arduino
nano and LoRa module within embedded road light to receiver on road signs
----------------------------------------------------------------------
*/

//Included Libraries
#include <stdlib.h>
#include <stdio.h>
#include <SPI.h>
#include <LoRa.h>

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
    float voltage = 0;
    float kelvin = 0;
    float fahrenheit = 0;
    float adcVal = 0;

    const float B = 1.0/3984.0; //Beta of thermistor
    const float adcMax = 1023.0;
    const float initialTemp = 1.0 / 298.15; //room temperature (Kelvin)
    
    //taking 50 voltage samples from thermistor and finding their sum
    for (int i = 0; i < 50; i++)
    {
        //reading in from the analog pin AO
        adcVal += analogRead(A0);
        delay(50);
    }

    //take average of voltage sample
    adcVal = adcVal/50.0;

    //convert averaged voltage into temperature (Kelvin)
    kelvin = 1.0/(initialTemp + B*(log(adcMax / adcVal-1.0)));

    //convert from Kelvin to Fahrenheit
    fahrenheit = ((9.0 * (kelvin - 273.15))/5.0) + 32.0;
    
    return fahrenheit;
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
//Arduino implementation Structure and LoRa read/write

struct information info;
String sendMe;

void setup() 
{
    info.identity = rand();

    Serial.begin(9600);
    while (!Serial);

    Serial.println("LoRa Safety Light");
    LoRa.setPins(LORA_DEFAULT_SS_PIN, LORA_DEFAULT_RESET_PIN, 3);

    //setting voltage divider as input, and mosfet control as output:
    pinMode(14,INPUT);
    pinMode(2,OUTPUT);
}

void loop() 
{
    info.temp = tempConversion();

    Serial.print("Sending temp and ID");
    sendMe = "ReadMe," + String(info.identity) + "," + String(info.temp);

    // send packet
    LoRa.beginPacket();
    LoRa.print(sendMe);
    LoRa.endPacket();

    communicate(LoRa.parsePacket());
}

//listens for LoRa from Safety Lights and saves data for parsing
void communicate(int packetSize)
{
  String message = "";
  String pass;
  int wtTm;
  
  int index;
  
  //where there is a message or not
  if (packetSize) {

    // read packet
    while (LoRa.available()) {
      message += (char)LoRa.read();
    }
  
    index = message.indexOf(',');
  
    pass = message.substring(0, index);
    wtTm = (message.substring(index + 1)).toInt();
  
    //if code and ID matches or is new, it is added to data storage
    if (pass.equals("PowerSave"))
    {
      sleep(wtTm);
    }
    
  }
    
}
