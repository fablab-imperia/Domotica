/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 2.3.1 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.0.1 or later version;
     - for iOS 1.1.0 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL_RX 2
#define REMOTEXY_SERIAL_TX 3
#define REMOTEXY_SERIAL_SPEED 9600


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,6,0,0,0,92,0,6,5,0,
  2,0,7,36,18,8,2,79,78,0,
  79,70,70,0,2,0,7,48,18,8,
  2,79,78,0,79,70,70,0,2,0,
  7,6,18,8,2,79,78,0,79,70,
  70,0,3,3,79,13,8,22,2,1,
  0,76,48,12,12,1,83,84,79,80,
  0,2,0,47,6,18,8,2,79,78,
  0,79,70,70,0,130,1,1,46,97,
  16,4,130,1,67,1,30,44,9 };
  
// this structure defines all the variables of your control interface 
struct {

    // input variable
  uint8_t luci_interne; // =1 if switch ON and =0 if OFF 
  uint8_t luci_esterne; // =1 if switch ON and =0 if OFF 
  uint8_t ventola; // =1 if switch ON and =0 if OFF 
  uint8_t garage; // =0 if select position A, =1 if position B, =2 if position C, ... 
  uint8_t generale; // =1 if button pressed, else =0 
  uint8_t stereo; // =1 if switch ON and =0 if OFF 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////



void setup() 
{
  RemoteXY_Init (); 
  
  
  // TODO you setup code
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer


}