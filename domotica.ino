/*
   -- Domotica --
   
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


#include "RemoteXY.h"
#include "DHT.h"
#include "LiquidCrystal_I2C.h"

// RemoteXY connection settings 
#define REMOTEXY_SERIAL_RX 2
#define REMOTEXY_SERIAL_TX 3
#define REMOTEXY_SERIAL_SPEED 9600


// RemoteXY configurate   
#pragma pack(push, 1) 
uint8_t RemoteXY_CONF[] = 
  { 255,4,0,0,0,106,0,6,8,0,
  4,0,87,21,5,28,2,2,0,2,
  24,16,7,2,79,78,0,79,70,70,
  0,2,0,28,24,16,7,2,79,78,
  0,79,70,70,0,2,0,58,24,16,
  7,2,79,78,0,79,70,70,0,129,
  0,1,17,97,5,4,76,117,99,105,
  32,73,110,32,32,32,32,32,32,76,
  117,99,105,32,79,117,116,32,32,32,
  32,32,32,32,86,101,110,116,111,108,
  97,32,32,32,32,32,71,97,114,97,
  103,101,0 }; 
   
// this structure defines all the variables of your control interface  
struct { 

    // input variable
  int8_t garage_door; // =0..100 slider position 
  uint8_t lights_in; // =1 if switch ON and =0 if OFF 
  uint8_t lights_out; // =1 if switch ON and =0 if OFF 
  uint8_t fan; // =1 if switch ON and =0 if OFF 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY; 
#pragma pack(pop) 

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_LIGHTS_IN 4
#define PIN_LIGHTS_OUT 5
#define PIN_FAN 6


#define PIN_TEMPERATURE_SENSOR 4

//LCD per mostrare temperatura e messaggi
LiquidCrystal_I2C lcd(0x3F,16,2);

//Sensore temperatura
DHT sensore_temperatura(PIN_TEMPERATURE_SENSOR,DHT11);


/////////////////////////////////////////////
//           FUNZIONI DI UTILITA           //
/////////////////////////////////////////////


// STAMPA MESSAGGIO MESSAGGIO VISUALIZZATO SU LCD
// Temperatura e Umidita passati da fuori
void aggiorna_lcd(float temperatura, float umidita)  
{
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.setCursor(6,0);
  lcd.print(temperatura);
  lcd.setCursor(12,0);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Umid:");
  lcd.setCursor(6,1);
  lcd.print(umidita);
  lcd.setCursor(12,1);
  lcd.print("%");
}



void setup() 
{
  RemoteXY_Init (); 
  
  pinMode (PIN_LIGHTS_IN, OUTPUT);
  pinMode (PIN_LIGHTS_OUT, OUTPUT);
  pinMode (PIN_FAN, OUTPUT);

  
  // Inizializzazione display LCD e SENSORE TEMPERATURA
  lcd.init();
  lcd.backlight();
  sensore_temperatura.begin();
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  
  digitalWrite(PIN_LIGHTS_IN, (RemoteXY.lights_in==0)?LOW:HIGH);
  digitalWrite(PIN_LIGHTS_OUT, (RemoteXY.lights_out==0)?LOW:HIGH);
  digitalWrite(PIN_FAN, (RemoteXY.fan==0)?LOW:HIGH);

  float temp = sensore_temperatura.readTemperature();
  float hum = sensore_temperatura.readHumidity();
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  aggiorna_lcd(temp,hum);
  delay(500);
}
