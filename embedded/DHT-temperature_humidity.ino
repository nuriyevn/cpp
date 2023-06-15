#include "DHT.h"

#define DHTPIN 7
#define DHTTYPE DHT11
#include <LiquidCrystal.h>
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
  
    // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Initilizing1");
    // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  
  lcd.clear();
  lcd.setCursor(0, 0);
  // print the number of seconds since reset:
  String temperature = String(t);
  lcd.print("Temp:" + temperature);
  
  lcd.setCursor(0, 1);
  String humidity = String(h);
  lcd.print("Humidity:" + humidity);
  
}

//zelectro.cc/LCD1602
//https://www.arduino.cc/en/Tutorial/HelloWorld

//www.arduino.cc/en/Tutorial/HelloWorld

//LiquidCrystal(rs, enable, d4, d5, d6, d7) 
//LiquidCrystal(rs, rw, enable, d4, d5, d6, d7) 
//LiquidCrystal(rs, enable, d0, d1, d2, d3, d4, d5, d6, d7) 
//LiquidCrystal(rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7)

// (RS, E, DB4, DB5, DB6, DB7)

