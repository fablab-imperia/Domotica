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
  { 255,9,0,0,0,236,0,6,8,1,
  2,0,44,5,17,8,2,79,78,0,
  79,70,70,0,2,0,44,15,17,8,
  2,79,78,0,79,70,70,0,2,0,
  44,25,17,8,2,79,78,0,79,70,
  70,0,2,0,44,35,17,8,2,79,
  78,0,79,70,70,0,1,0,24,85,
  14,14,1,71,101,110,101,114,97,108,
  101,0,2,0,44,45,17,8,2,79,
  78,0,79,70,70,0,2,0,44,55,
  17,8,2,79,78,0,79,70,70,0,
  2,0,44,65,17,8,2,79,78,0,
  79,70,70,0,2,0,44,75,17,8,
  2,79,78,0,79,70,70,0,129,0,
  6,7,29,5,5,76,117,99,105,32,
  73,110,116,101,114,110,101,0,129,0,
  5,19,31,5,4,76,117,99,105,32,
  69,115,116,101,114,110,101,0,129,0,
  7,28,18,5,6,86,101,110,116,111,
  108,97,0,129,0,6,46,25,5,0,
  71,97,114,97,103,101,32,83,117,0,
  129,0,7,37,16,5,1,83,116,101,
  114,101,111,0,129,0,5,56,27,5,
  0,71,97,114,97,103,101,32,71,105,
  195,185,0 }; 
   
// this structure defines all the variables of your control interface  
struct _remotexy { 

    // input variable
  uint8_t lights_in; // =1 if switch ON and =0 if OFF 
  uint8_t lights_out; // =1 if switch ON and =0 if OFF 
  uint8_t fan; // =1 if switch ON and =0 if OFF 
  uint8_t stereo; // =1 if switch ON and =0 if OFF 
  uint8_t general; // =1 if button pressed, else =0 
  uint8_t garage_up; // =1 if switch ON and =0 if OFF 
  uint8_t garage_down; // =1 if switch ON and =0 if OFF 
  uint8_t rele7; // =1 if switch ON and =0 if OFF 
  uint8_t rele8; // =1 if switch ON and =0 if OFF 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY; 
#pragma pack(pop) 

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_LIGHTS_IN 5
#define PIN_LIGHTS_OUT 6
#define PIN_FAN 7
#define PIN_STEREO 8
#define PIN_GARAGE_UP 9
#define PIN_GARAGE_DOWN 10
#define PIN_RELE_7 11
#define PIN_RELE_8 12

#define VALORE_RELAY_ON LOW
#define VALORE_RELAY_OFF HIGH



#define PIN_TEMPERATURE_SENSOR 4

//LCD per mostrare temperatura e messaggi
LiquidCrystal_I2C lcd(0x3F,16,2);

//Sensore temperatura
DHT sensore_temperatura(PIN_TEMPERATURE_SENSOR,DHT11);


/////////////////////////////////////////////
//           FUNZIONI DI UTILITA           //
/////////////////////////////////////////////

void processa_comandi(struct _remotexy&  cmd) 
{

  digitalWrite( PIN_LIGHTS_IN, (cmd.lights_in == 1) ?  VALORE_RELAY_ON : VALORE_RELAY_OFF); 
  digitalWrite( PIN_LIGHTS_OUT, (cmd.lights_out == 1) ?  VALORE_RELAY_ON : VALORE_RELAY_OFF);    
  digitalWrite( PIN_FAN, (cmd.fan == 1) ?  VALORE_RELAY_ON : VALORE_RELAY_OFF); 
  digitalWrite( PIN_STEREO, (cmd.stereo == 1) ?  VALORE_RELAY_ON : VALORE_RELAY_OFF); 
  digitalWrite( PIN_GARAGE_UP, (cmd.garage_up == 1) ?  VALORE_RELAY_ON : VALORE_RELAY_OFF);    
  digitalWrite( PIN_GARAGE_DOWN, (cmd.garage_down == 1) ?  VALORE_RELAY_ON : VALORE_RELAY_OFF); 
  digitalWrite( PIN_RELE_7, (cmd.rele7 == 1) ?  VALORE_RELAY_ON : VALORE_RELAY_OFF); 
  digitalWrite( PIN_RELE_8, (cmd.rele8 == 1) ?  VALORE_RELAY_ON : VALORE_RELAY_OFF);    
  
}

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
  pinMode (PIN_STEREO, OUTPUT);
  pinMode (PIN_GARAGE_UP, OUTPUT);
  pinMode (PIN_GARAGE_DOWN, OUTPUT);
  pinMode (PIN_RELE_7, OUTPUT);
  pinMode (PIN_RELE_8, OUTPUT);

  
  Serial.begin(9600);
  
  // Inizializzazione display LCD e SENSORE TEMPERATURA
  lcd.init();
  lcd.backlight();
  sensore_temperatura.begin();
  
}

void loop() 
{ 
  //legge comandi da bluetooth
  RemoteXY_Handler ();
  


  float temp = sensore_temperatura.readTemperature();
  float hum = sensore_temperatura.readHumidity();
  
  // use the RemoteXY structure for data transfer
  aggiorna_lcd(temp,hum);

  //processa comandi (aziona relays e pin vari)
  processa_comandi(RemoteXY);


}
