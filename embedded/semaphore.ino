/*
  Проект "Миготливий знак пішохідного переходу"
*/
/* Миготіння  LED світлодіоду  покращує бачення знаку
  Включає і вимикає LED світлодіод , приєднаний
  до виходу 12 на модулі Arduino, з інтервалом в 2 секунди
*/
int redPin = 13;//задаємо порт підключення. Це означає,що світлодіод LED      //приєднаний до  цифрового виходу 12
int yellowPin = 12;
int greenPin = 11;
void setup ()    //  Встановлюємо режим роботи цифрового виходу 12 
{
  pinMode (redPin, OUTPUT);// Встановлюємо контакт 12 як вихід(OUTPUT)
  pinMode (yellowPin, OUTPUT);
  pinMode (greenPin, OUTPUT);
}

void light_up(int pin, int d)
{
    digitalWrite (pin, HIGH); // вмикаємо LED,на контакт 12 
    //подаєтья високий рівень//напруги 5В
    delay (d);    // пауза 1 секунда, під час якої світлодіод LED //світиться
    digitalWrite (pin, LOW);// вимикаємо світлодіод LED, на контакт 12 
}

// виконання програми
void loop ()  
{
  while(true){
    light_up(redPin, 1000);
    light_up(yellowPin, 1000);
    light_up(greenPin, 1000);
    light_up(yellowPin, 1000);
  }
}
