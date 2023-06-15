// moving forward, backward, left, right, stop via infra red remote control
#include <IRremote.h> // 2.8.1  required - looks like v3.0.0 does not work

const int RECV_PIN = 7;

const char MOVE_FORWARD = '+';
const char STOP_MOVING = 0;
const char MOVE_BACKWARD = '-';
const char TURN_LEFT = '>';
const char TURN_RIGHT = '<';

#define IN1 3 // MOTOR A LEFT WHEELS
#define IN2 4 // MOTOR A LEFT WHEELS
#define IN3 5 // MOTOR B RIGHT WHEELS
#define IN4 6 // MOTOR B RIGHT WHEELS

const int red_light_pin= 11;
const int green_light_pin = 10;
const int blue_light_pin = 9;

IRrecv irrecv(RECV_PIN);
int  moveAll = STOP_MOVING;

/*
                            Cathode - Anode 
  RGB_color(255, 0, 0); //        Red - Cyan
  RGB_color(0, 255, 0); //    Green - Magenta
  RGB_color(0, 0, 255); //    Blue  yellow
  RGB_color(255, 255, 125); // Raspberry - blue
  RGB_color(0, 255, 255); //     Cyan - red
  RGB_color(255, 0, 255); //  Magenta - Green
  RGB_color(255, 255, 0); //    Yellow Blue
  RGB_color(255, 255, 255); // White - notinhg
*/

void RGB_color_cathode(int red_light_value, int green_light_value, int blue_light_value)
{
  if (red_light_value >= 0 && red_light_value <= 255 )
    analogWrite(red_light_pin, red_light_value);
  if (green_light_value >= 0 && green_light_value <= 255 )
    analogWrite(green_light_pin, green_light_value);
  if (blue_light_value >= 0 && blue_light_value <= 255 )
    analogWrite(blue_light_pin, blue_light_value);
}

void RGB_color_anode(int red_light_value, int green_light_value, int blue_light_value)
{
  if (red_light_value >= 0 && red_light_value <= 255 )
    analogWrite(red_light_pin, 255 - red_light_value);
  if (green_light_value >= 0 && green_light_value <= 255 )
    analogWrite(green_light_pin, 255 - green_light_value);
  if (blue_light_value >= 0 && blue_light_value <= 255 )
    analogWrite(blue_light_pin, 255 - blue_light_value);
}

void setup() {
 
  Serial.begin(9600);
  irrecv.enableIRIn();
  //irrecv.blink13(true);
  Serial.println("Crazy Bus is ready to start!");

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);

  Serial.println("STOPPED");
}

void loop() {
  if (moveAll == STOP_MOVING)
  {
        RGB_color_anode(0,0, 0); // Nothing
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);        
  }
  else
  {
    if (moveAll == MOVE_FORWARD)
    {   
        RGB_color_anode(0, 255, 0); // Green
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);

        //digitalWrite(RECV_PIN, HIGH);
        //delay(1000);
    }
    else if (moveAll == MOVE_BACKWARD)
    {
        RGB_color_anode(255, 0, 0); // Red
        //RGB_color_anode(255, 11, 56); //TODO: strangely but any other value for RED except 255 - causes that the futhre irrecv.decode() call is not successfull anymore - infrared does not respond
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);

        
    }
    else if (moveAll == TURN_LEFT)
    {
        /*digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        delay(1000);*/
      
        //digitalWrite(IN1, LOW);  // LEFT WHEELS BACKWARD
        //digitalWrite(IN2, HIGH);  // LEFT WHEELS BACKWARD

        RGB_color_anode(0, 0, 255); // Blue

        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH );
        digitalWrite(IN4, LOW);
        delay(50);

        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH); // RIGHT WHEELS FORWARD
        digitalWrite(IN4, LOW); // RIGHT WHEELS FORWARD
        delay(350);
        
        
        
    }
    else if (moveAll == TURN_RIGHT)
    {
        /*digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);*/
        RGB_color_anode(255, 255, 0); // Yellow
        digitalWrite(IN1, HIGH); // LEFT WHEELS FORWARD
        digitalWrite(IN2, LOW); // LEFT WHEELS FORWARD
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        delay(350);

        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        delay(50);
        
        
        //digitalWrite(IN3, LOW); // RIGHT WHEELS BACKWARD
        //digitalWrite(IN4, HIGH); // RIGHT WHEELS BACKWARD
    }
    
  }  
  
  if (irrecv.decode()){

           switch (irrecv.results.value)
           {
              case 0xFF30CF:
                  Serial.println("1");
                  break;
              case 0xFF18E7:
                  Serial.println("2");
                  moveAll = MOVE_FORWARD;
                  Serial.println("MOVE_FORWARD");
                  
                  break;
              case 0xFF7A85:
                  Serial.println("3");
                  break;
              case 0xFF10EF:
                  Serial.println("4");
                  moveAll = TURN_LEFT;
                  Serial.println("TURN_LEFT");
                  break;
              case 0xFF38C7:
                  Serial.println("5");
                  moveAll = STOP_MOVING;
                  Serial.println("STOPPED");
                  break;
              case 0xFF5AA5:
                  Serial.println("6");
                  moveAll = TURN_RIGHT;
                  Serial.println("TURN_RIGHT");
                  break;
              case 0xFF42BD:
                  Serial.println("7");
                  break;
              case 0xFF4AB5:
                  Serial.println("8");
                  moveAll = MOVE_BACKWARD;
                  Serial.println("MOVE_BACKWARD");
                  break;
              case 0xFF52AD:
                  Serial.println("9");
                  break;
              case 0xFFA25D:
                  Serial.println("CH-");
                  break;
              case 0xFF629D:
                  Serial.println("CH");
                  break;
              case 0xFFE21D:
                  Serial.println("CH+");
                  break;
              case 0xFF22DD:
                  Serial.println("|<<");
                  moveAll = TURN_LEFT;
                  Serial.println("TURN_LEFT");
                  break;
              case 0xFF02FD:
                  Serial.println(">>|");
                  moveAll = TURN_RIGHT;
                  Serial.println("TURN_RIGHT");
                  break;
              case 0xFFC23D:
                  Serial.println(">||");
                  break;
              case 0xFFE01F:
                  Serial.println("-");
                  moveAll = MOVE_BACKWARD;
                  Serial.println("MOVE_BACKWARD");
                  break;
              case 0xFFA857:
                  Serial.println("+");
                  moveAll = MOVE_FORWARD;
                  Serial.println("MOVE_FORWARD");
                  break;
              case 0xFF906F:
                  Serial.println("EQ");
                  break;
              case 0xFF6897:
                  Serial.println("0");
                  moveAll = STOP_MOVING;
                  Serial.println("STOPPED");
                  break;
              case 0xFF9867:
                  Serial.println("100+");
                  break;
              case 0xFFB04F:
                  Serial.println("200+");
                  break;
              default:
                  //Serial.println( irrecv.results.value, HEX);
                  break;
           }
        irrecv.resume();
    }
}
