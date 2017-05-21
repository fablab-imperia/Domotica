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
// RemoteXY configurate   
#pragma pack(push, 1) 
uint8_t RemoteXY_CONF[] = 
  { 255,8,0,22,0,36,1,6,8,1,
  2,0,43,2,17,8,2,79,78,0,
  79,70,70,0,2,0,43,12,17,8,
  2,79,78,0,79,70,70,0,2,0,
  43,22,17,8,2,79,78,0,79,70,
  70,0,2,0,43,32,17,8,2,79,
  78,0,79,70,70,0,1,0,46,83,
  12,12,1,71,101,110,101,114,97,108,
  101,0,2,0,43,42,17,8,2,79,
  78,0,79,70,70,0,2,0,43,52,
  17,8,2,79,78,0,79,70,70,0,
  3,2,50,62,9,17,2,67,4,3,
  81,20,5,2,11,67,4,3,93,20,
  5,2,11,129,0,5,4,29,5,5,
  76,117,99,105,32,71,97,114,97,103,
  101,0,129,0,4,14,32,5,4,76,
  117,99,101,32,67,97,109,101,114,97,
  0,129,0,7,24,29,5,6,76,117,
  99,101,32,66,97,103,110,111,0,129,
  0,7,43,30,5,0,76,117,99,105,
  32,69,115,116,101,114,110,101,0,129,
  0,8,33,24,5,1,76,117,99,101,
  32,83,97,108,97,0,129,0,8,66,
  30,5,0,0,129,0,12,53,18,5,
  3,86,101,110,116,111,108,97,0,129,
  0,30,64,17,5,7,71,97,114,97,
  103,101,0,129,0,2,74,30,5,5,
  84,101,109,112,46,0,129,0,2,87,
  30,5,5,85,109,105,100,105,116,195,
  160,0,130,1,-1,73,28,28,11 }; 
   
// this structure defines all the variables of your control interface  
struct _remotexy { 

    // input variable
  uint8_t lights_garage; // =1 if switch ON and =0 if OFF 
  uint8_t lights_bedroom; // =1 if switch ON and =0 if OFF 
  uint8_t light_bath; // =1 if switch ON and =0 if OFF 
  uint8_t light_living; // =1 if switch ON and =0 if OFF 
  uint8_t general; // =1 if button pressed, else =0 
  uint8_t light_garden; // =1 if switch ON and =0 if OFF 
  uint8_t fan; // =1 if switch ON and =0 if OFF 
  uint8_t garage_up_down; // =0 if select position A, =1 if position B, =2 if position C, ... 

    // output variable
  char txt_temp[11];  // string UTF8 end zero 
  char txt_humid[11];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY, old_remotexy; 


#pragma pack(pop) 


/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_LIGHTS_GARAGE 5
#define PIN_LIGHTS_BEDROOM 6
#define PIN_LIGHT_BATH 7
#define PIN_LIGHT_LIVING 8
#define PIN_LIGHT_GARDEN 9
#define PIN_FAN 12
#define PIN_GARAGE_UP 11
#define PIN_GARAGE_DOWN 10


#define VALORE_RELAY_ON LOW
#define VALORE_RELAY_OFF HIGH

#define SERRANDA_UP 0
#define SERRANDA_DOWN 1
#define TEMPO_AZIONE_MOTORE_SERRANDA_MS 600 


#define PIN_TEMPERATURE_SENSOR 4

//LCD per mostrare temperatura e messaggi
LiquidCrystal_I2C lcd(0x3F,16,2);

//Sensore temperatura
DHT sensore_temperatura(PIN_TEMPERATURE_SENSOR,DHT11);

int posizione_precedente_serranda = SERRANDA_UP;


/////////////////////////////////////////////
//           FUNZIONI DI UTILITA           //
/////////////////////////////////////////////

//Fai qualcosa solo se il valore ricevuto da bluetooth e' diverso dal precedente

void processa_comandi(struct _remotexy&  old, struct _remotexy&  current) 
{

  if (current.lights_garage != old.lights_garage) 
  {
    digitalWrite( PIN_LIGHTS_GARAGE, (current.lights_garage == 1) ?  VALORE_RELAY_ON : VALORE_RELAY_OFF); 
  }
  
  if (current.lights_bedroom != old.lights_bedroom)  
  {
    digitalWrite( PIN_LIGHTS_BEDROOM, (current.lights_bedroom == 1) ?  VALORE_RELAY_ON : VALORE_RELAY_OFF);    
  }
  
  if (current.light_bath != old.light_bath)  
  {
    digitalWrite( PIN_LIGHT_BATH, (current.light_bath == 1) ?  VALORE_RELAY_ON: VALORE_RELAY_OFF); 
  }
  
  if (current.light_living != old.light_living) 
  { 
    digitalWrite( PIN_LIGHT_LIVING, (current.light_living == 1) ?  VALORE_RELAY_ON : VALORE_RELAY_OFF); 
  }
    
  if (current.light_garden != old.light_garden) 
  {
    digitalWrite( PIN_LIGHT_GARDEN, (current.light_garden == 1) ?  VALORE_RELAY_ON : VALORE_RELAY_OFF); 
  }
  
  if (current.fan != old.fan) 
  {
    digitalWrite( PIN_FAN, (current.fan == 1) ?  VALORE_RELAY_ON : VALORE_RELAY_OFF);    
  }
  //se  posizione della serranda diversa
  if (old.garage_up_down != current.garage_up_down)
  {
    muovi_serranda_garage(current.garage_up_down);
  }

  if (current.general != old.general && current.general == 1) 
  {
    spegni_tutto();
  
  }
  
 
}


//Salva i valori correnti ricevuti da bluetooth in una struttura temporanea
void salva_stato(struct _remotexy& oldRemotexy, struct _remotexy& currentRemotexy) 
{
     oldRemotexy.lights_garage = currentRemotexy.lights_garage;
     oldRemotexy.lights_bedroom = currentRemotexy.lights_bedroom;
     oldRemotexy.light_bath = currentRemotexy.light_bath;
     oldRemotexy.light_living = currentRemotexy.light_living; 
     oldRemotexy.general = currentRemotexy.general;
     oldRemotexy.light_garden = currentRemotexy.light_garden;
     oldRemotexy.fan = currentRemotexy.fan;
     oldRemotexy.garage_up_down = currentRemotexy.garage_up_down; 
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

void spegni_tutto() 
{
  digitalWrite (PIN_LIGHTS_GARAGE, VALORE_RELAY_OFF);
  digitalWrite (PIN_LIGHTS_BEDROOM, VALORE_RELAY_OFF);
  digitalWrite (PIN_LIGHT_BATH, VALORE_RELAY_OFF);
  digitalWrite (PIN_LIGHT_LIVING, VALORE_RELAY_OFF);
  digitalWrite (PIN_LIGHT_GARDEN, VALORE_RELAY_OFF);
  digitalWrite (PIN_FAN, VALORE_RELAY_OFF);
  digitalWrite (PIN_GARAGE_UP, VALORE_RELAY_OFF);
  digitalWrite (PIN_GARAGE_DOWN, VALORE_RELAY_OFF);
}

void setup() 
{
  RemoteXY_Init (); 
  
  pinMode (PIN_LIGHTS_GARAGE, OUTPUT);
  pinMode (PIN_LIGHTS_BEDROOM, OUTPUT);
  pinMode (PIN_LIGHT_BATH, OUTPUT);
  pinMode (PIN_LIGHT_LIVING, OUTPUT);
  pinMode (PIN_LIGHT_GARDEN, OUTPUT);
  pinMode (PIN_FAN, OUTPUT);
  pinMode (PIN_GARAGE_UP, OUTPUT);
  pinMode (PIN_GARAGE_DOWN, OUTPUT);

  //Inizializzo tutti i rele a OFF
  spegni_tutto();
  
  Serial.begin(9600);
  
  // Inizializzazione display LCD e SENSORE TEMPERATURA
  lcd.init();
  lcd.backlight();
  sensore_temperatura.begin();
  
}

void muovi_serranda_garage(int direzione) 
{
    if (direzione == SERRANDA_UP) 
    {
      digitalWrite(PIN_GARAGE_UP, VALORE_RELAY_ON);
      delay(TEMPO_AZIONE_MOTORE_SERRANDA_MS);
      digitalWrite(PIN_GARAGE_UP, VALORE_RELAY_OFF);
    } 
    else 
    {
      digitalWrite(PIN_GARAGE_DOWN, VALORE_RELAY_ON);
      delay(TEMPO_AZIONE_MOTORE_SERRANDA_MS);
      digitalWrite(PIN_GARAGE_DOWN, VALORE_RELAY_OFF);
    }
}

void loop() 
{ 
  //legge comandi da bluetooth
  RemoteXY_Handler ();
  


  float temp = sensore_temperatura.readTemperature();
  float hum = sensore_temperatura.readHumidity();
  String temp_str="";
  temp_str+=temp;
  temp_str += " C";
  String hum_str="";
  hum_str+=hum;
  hum_str += " %";
  temp_str.toCharArray(RemoteXY.txt_temp, 11);
  hum_str.toCharArray(RemoteXY.txt_humid, 11);
  // use the RemoteXY structure for data transfer
  aggiorna_lcd(temp,hum);

  //processa comandi (aziona relays e pin vari)
  processa_comandi(old_remotexy,RemoteXY);

  salva_stato(old_remotexy,RemoteXY);

}
