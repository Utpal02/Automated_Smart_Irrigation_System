/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.10 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.13.1 or later version;
     - for iOS 1.10.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// you can enable debug logging to Serial at 115200
//#define REMOTEXY__DEBUGLOG    

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 9600
#define REMOTEXY_WIFI_SSID "Soil_Sensor_CSE"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377



// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 66 bytes
  { 255,1,0,5,0,59,0,17,0,0,0,58,1,106,200,1,1,3,0,2,
  31,69,43,22,0,24,27,135,36,79,78,0,79,70,70,0,72,24,11,56,
  56,12,148,60,150,41,0,0,0,0,0,0,200,66,0,0,0,0,68,6,
  101,95,91,17,25,136 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t Water_Controller; // =1 if switch ON and =0 if OFF

    // output variables
  int8_t Moisture_Percentage; // from 0 to 100
  float Moisture_Plot;

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;
#pragma pack(pop)
 
/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_WATER_CONTROLLER 3
int sensor_pin = A0;
int output_value;

void setup() 
{
  RemoteXY_Init (); 
  pinMode (PIN_WATER_CONTROLLER, OUTPUT);
  // REMOTEXY_SERIAL.begin(REMOTEXY_SERIAL_SPEED);
  // REMOTEXY_SERIAL.println("Reading from the Moisture sensor…");
  // RemoteXY_delay(2000);
}

void loop() 
{ 
  RemoteXY_Handler ();
  output_value= analogRead (sensor_pin);
  output_value= map (output_value,550,10,0,100);
  REMOTEXY_SERIAL.print("Moisture:");
  REMOTEXY_SERIAL.print(output_value);
  REMOTEXY_SERIAL.println("%");

  if(RemoteXY.Water_Controller)
  {
    digitalWrite(PIN_WATER_CONTROLLER, HIGH);
  }
  else 
  {
    if (output_value < 0)
    {
      RemoteXY_delay(100);
      digitalWrite(PIN_WATER_CONTROLLER, HIGH);
    }

    else
    {
      RemoteXY_delay(100);
      digitalWrite(PIN_WATER_CONTROLLER,LOW);  
    }
  }

  RemoteXY_delay(100);
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay(), use instead RemoteXY_delay() 


}