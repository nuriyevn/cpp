
// РУХОМИЙ 4-Х КОЛІСНИЙ РОБОТ,КЕРОВАНИЙ ПО BLUETOOTH - КАНАЛУ ІЗ СМАРТФОНА. Канал А - ПРАВІ ДВИГУНИ. Канал В - ЛІВІ ДВИГУНИ.

#include <SoftwareSerial.h>
SoftwareSerial BT(3, 4); 
int max_velocity = 255;

//Змінна для збереження даних  про кодові сигнали керування, 
//що поступають із смартфона
char code;
String bt = "";

//ініціалізація виводів підключення драйвера моторів L298 до Arduino
//канал А-ПРАВІ ДВИГУНИ
int ENA = 5;
int IN1 = 6; 
int IN2 = 7;

//канал В- ЛІВІ ДВИГУНИ
int IN3 = 8;
int IN4 = 9;
int ENB = 10;



void setup()  // Запускається один раз,коли стартує програма
{
 Serial.begin(9600);  // встановлення режиму роботи послідовного порту   
 BT.begin(9600);
 // встановлення режиму роботи портів на вихід (OUTPUT)
 
 //канал А-ПРАВІ ДВИГУНИ
 pinMode(5, OUTPUT);
 pinMode(6, OUTPUT); 
 pinMode(7, OUTPUT);

//канал В- ЛІВІ ДВИГУНИ
 pinMode(8, OUTPUT);
 pinMode(9, OUTPUT); 
 pinMode(10, OUTPUT); 

}

void loop()
{

char buffer[5] = {0};
  if(Serial.available()){
      Serial.readBytes(buffer, 4);
      int velocity = max_velocity;
      sscanf(buffer, "%c%03d", code, &velocity);
      code = buffer[0];

     if (code == 'V') // команда керування швидкістю
     {
        
        int ena = analogRead(ENA);
        int enb = analogRead(ENB);
          
        int new_ena = ena * (float)velocity / max_velocity;
        int new_enb = enb * (float)velocity / max_velocity;

        analogWrite(ENA, new_ena);
        analogWrite(ENB, new_enb);
     }
      
     if(code == 'F'){   //ЯКЩО ПРИЙШЛА КОМАНДА 'F'=  РУХАЄМОСЬ ВПЕРЕД
      digitalWrite(IN1, HIGH); //Встановлює  напрям обертання двигунів  ВПЕРЕД Каналу А
      digitalWrite(IN2, LOW);   //

      int new_ena = 255 * (float)velocity / max_velocity;
      analogWrite(ENA, new_ena);   // двигуни на Каналі А крутяться з максимальною швидкістю
      
      digitalWrite(IN3, LOW); //Встановлює  напрям обертання двигунів  ВПЕРЕД  Каналу B
      digitalWrite(IN4, HIGH);   //

      int new_enb = 255 * (float)velocity / max_velocity;
      analogWrite(ENB, new_enb);   // двигуни на Каналі В крутяться з максимальною швидкістю
    }
     if(code == 'G'){   //ЯКЩО ПРИЙШЛА КОМАНДА 'G'=  РУХАЄМОСЬ  ЛІВОРУЧ ВПЕРЕД
      digitalWrite(IN1, HIGH); //Встановлює  напрям обертання двигунів  ВПЕРЕД Каналу А
      digitalWrite(IN2, LOW);   //
      int new_ena = 255 * (float)velocity / max_velocity;
      analogWrite(ENA, new_ena);   // двигуни на Каналі А крутяться з максимальною швидкістю
      
      digitalWrite(IN3, LOW); //Встановлює  напрям обертання двигунів  ВПЕРЕД  Каналу B
      digitalWrite(IN4, HIGH); //
      int new_enb = 40 * (float)velocity / max_velocity;
      analogWrite(ENB, new_enb);   // двигуни на Каналі В крутяться з мінімальною швидкістю
    }
    
     if(code == 'L'){  // ЯКЩО ПРИЙШЛА КОМАНДА'L'= РУХАЄМОСЬ ЛІВОРУЧ
      digitalWrite(IN1, HIGH); //Встановлює  напрям обертання двигунів  ВПЕРЕД  Каналу А
      digitalWrite(IN2, LOW);   //
      
      int new_ena = 255 * (float)velocity / max_velocity;
      analogWrite(ENA, new_ena);   // двигуни  Каналу B обертаються на половину швидкості
     
      digitalWrite(IN3, HIGH); //Встановлює  напрям обертання двигунів НАЗАД у КаналІ B
      digitalWrite(IN4, LOW);  //
      int new_enb = 127 * (float)velocity / max_velocity;
      analogWrite(ENB, new_enb);   // двигуни  Каналу B обертаються на половину швидкості 127
    }

    if(code == 'I'){   //ЯКЩО ПРИЙШЛА КОМАНДА 'I'=  РУХАЄМОСЬ  ПРАВОРУЧ ВПЕРЕД
      
      digitalWrite(IN1, HIGH); //Встановлює  напрям обертання двигунів  ВПЕРЕД Каналу А
      digitalWrite(IN2, LOW);   //
      int new_ena = 40 * (float)velocity / max_velocity;
      analogWrite(ENA, new_ena);   // двигуни на Каналі А крутяться з мінімальною швидкістю 40
      
      digitalWrite(IN3, LOW); //Встановлює  напрям обертання двигунів  ВПЕРЕД  Каналу B
      digitalWrite(IN4, HIGH); //
      int new_enb = 255 * (float)velocity / max_velocity;
      analogWrite(ENB, new_enb);   // двигуни на Каналі В крутяться з мінімальною швидкістю
    }
    
     if(code == 'R'){  //ЯКЩО ПРИЙШЛА КОМАНДА 'R'= РУХАЄМОСЬ ПРАВОРУЧ
      
      digitalWrite(IN1, LOW); //Встановлює бертання двигунів НАЗАД Каналу А
      digitalWrite(IN2, HIGH);   //
        int new_ena = 127 * (float)velocity / max_velocity;
      analogWrite(ENA, new_ena);   // двигун на Каналі А  обертається на половину швидкості
     
      digitalWrite (IN3, LOW );//Встановлює  напрям обертання двигунів  ВПЕРЕД у КаналІ B
      digitalWrite (IN4, HIGH ); 
      int new_enb = 255 * (float)velocity / max_velocity;
      analogWrite(ENB, new_enb);   // двигун на Каналі В обертається на половину швидкості 127
    }
    
     if(code == 'B'){   // ЯКЩО ПРИЙШЛА КОМАНДА 'B'= РУХАЄМОСЬ НАЗАД
      
       digitalWrite (IN2, HIGH);//Встановлює бертання двигунів НАЗАД Каналу А
       digitalWrite (IN1, LOW);
       int new_ena = 255 * (float)velocity / max_velocity;
       analogWrite(ENA, new_ena);   // двигуни на Каналі А крутяться з максимальною швидкістю 255
       
       digitalWrite (IN4, LOW);//Встановлює  напрям обертання двигунів НАЗАД у КаналІ B
       digitalWrite (IN3, HIGH);
       int new_enb = 255 * (float)velocity / max_velocity;
      analogWrite(ENB, new_enb);   // двигуни на Каналі В крутяться з максимальною швидкістю 255
    }

     if(code == 'H'){   // ЯКЩО ПРИЙШЛА КОМАНДА 'H'= РУХАЄМОСЬ ЛІВОРУЧ НАЗАД
      // Робот рухається НАЗАД
       digitalWrite (IN2, HIGH);//Встановлює напрям обертання двигунів НАЗАД Каналу А
       digitalWrite (IN1, LOW);
       int new_ena = 255 * (float)velocity / max_velocity;
       analogWrite(ENA, new_ena);   // двигуни на Каналі А крутяться з максимальною швидкістю 255
       
       digitalWrite (IN4, LOW);//Встановлює  напрям обертання двигунів НАЗАД у КаналІ B
       digitalWrite (IN3, HIGH);
        int new_enb = 40 * (float)velocity / max_velocity;
       analogWrite(ENB, new_enb);   // двигуни на КаналІ B крутяться з мінімальною швидкістю 40
    }
    

    if(code == 'J'){   // ЯКЩО ПРИЙШЛА КОМАНДА 'J' = РУХАЄМОСЬ ПРАВОРУЧ НАЗАД
      
       digitalWrite (IN2, HIGH);//Встановлює напрям обертання двигунів НАЗАД Каналу А
       digitalWrite (IN1, LOW);
        int new_ena = 40 * (float)velocity / max_velocity;
       analogWrite(ENA, new_ena); // двигуни на Каналі А крутяться з мінімальною швидкістю 40
       
       digitalWrite (IN4, LOW);//Встановлює  напрям обертання двигунів НАЗАД у КаналІ B
       digitalWrite (IN3, HIGH);
       int new_enb = 255 * (float)velocity / max_velocity;
       analogWrite(ENB, new_enb);  // двигуни на КаналІ B крутяться з максимальною швидкістю 255
    }
    if(code == 'S'){  // ЯКЩО ПРИЙШЛА КОМАНДА 'S'= СТОП
      analogWrite(ENA, 0);  //СТОП  ДВИГУНИ каналу  А
      analogWrite(ENB, 0);  //СТОП  ДВИГУНИ каналу  B
    }
  }
 
  delay(10);
}
