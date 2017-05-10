#include <DHT.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);

DHT dht(2,DHT11);

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  dht.begin();
  lcd.backlight();
   
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0);
  float temperatura = dht.readTemperature();
  float humidity = dht.readHumidity();
  lcd.print("Temp: ");
  lcd.setCursor(6,0);
  lcd.print(temperatura);
  lcd.setCursor(12,0);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Umid:");
  lcd.setCursor(6,1);
  lcd.print(humidity);
  lcd.setCursor(12,1);
  lcd.print("%");
  delay(2000);
}
