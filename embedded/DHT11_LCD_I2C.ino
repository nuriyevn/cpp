//Вимірювач температури і вологості на DHT11

#include <DHT.h>
#include <Wire.h> //
#include <LiquidCrystal_I2C.h>

// встановлюємо адресу 0x27(або іншу: 0x20,0x3F), і дисплей 16 символів
//в 2 рядки (16х2)
LiquidCrystal_I2C lcd (0x27,16,2);
// змінна для збереження даних про час роботи LCD
int interval = 0;

#define DHTPIN 2 // номер піну, до якого підключений давач

//DHT dht(DHTPIN, DHT22);
 
DHT dht(DHTPIN, DHT11);

void setup ()
{
  lcd.begin (); // ініціалізація LCD
  lcd.backlight (); // включаємо підсвічування
  lcd.clear (); // очищення дисплея
  Serial.begin(9600);
  dht.begin();
}


// Виконання програми
void loop() {

  delay(1000);



  //Зчитуємо вологість

  float h = dht.readHumidity();

  // Зчитуємо температуру

  float t = dht.readTemperature();

  // Провірка чи вдало пройшло зчитування.

  lcd.clear (); // очищення дисплея
  if (isnan(h) || isnan(t)) {
    lcd.setCursor (1,0);
    lcd.println("Can not print");
  } 
  else {
    lcd.setCursor (1,0);
    lcd.print ("Hum: ");
    lcd.setCursor (6,0);
    lcd.print (h);
    lcd.setCursor (1,1);
    lcd.print ("Temp: ");
    lcd.setCursor (7,1);
    lcd.print (t);
    Serial.print("\n");
    Serial.print(t);
    Serial.print("\n");
    Serial.print(h);
    Serial.print("\n");
    
  }
  

}
