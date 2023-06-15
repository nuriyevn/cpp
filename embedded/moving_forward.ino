#include <IRremote.h>

const int RECV_PIN = 8;
const int FRONT_LEFT_PIN = 4;
const int FRONT_RIGHT_PIN = 2;
const int REAR_RIGHT_PIN = 13;
const int REAR_LEFT_PIN = 7;


#define IN1 3
#define IN2 4
#define IN3 5
#define IN4 6


IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
  Serial.println("Hello!");

  pinMode(REAR_RIGHT_PIN, OUTPUT);
  //pinMode(2, OUTPUT);
  //pinMode(4, OUTPUT);
  pinMode(REAR_LEFT_PIN, OUTPUT);


  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

bool  moveAll = true;

void startAll()
{
  while (moveAll)
  {
    digitalWrite(13, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(7, HIGH);
  }
  stopAll();
}

void stopAll()
{
  digitalWrite(13, LOW);
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(7, LOW);
}


void loop() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  digitalWrite(REAR_RIGHT_PIN, HIGH);
  //digitalWrite(REAR_LEFT_PIN, HIGH);


  /*if (irrecv.decode()){

           switch (irrecv.results.value)
           {
              case 0xFF30CF:
                  Serial.println("1");
                  break;
              case 0xFF18E7:
                  Serial.println("2");
                  break;
              case 0xFF7A85:
                  Serial.println("3");
                  break;
              case 0xFF10EF:
                  Serial.println("4");
                  break;
              case 0xFF38C7:
                  Serial.println("5");
                  break;
              case 0xFF5AA5:
                  Serial.println("6");
                  break;
              case 0xFF42BD:
                  Serial.println("7");
                  break;
              case 0xFF4AB5:
                  Serial.println("8");
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
                  break;
              case 0xFF02FD:
                  Serial.println(">>|");
                  break;
              case 0xFFC23D:
                  Serial.println(">||");
                  break;
              case 0xFFE01F:
                  Serial.println("-");
                  moveAll = false;
                  break;
              case 0xFFA857:
                  Serial.println("+");
                  moveAll = true;
                  startAll();
                  break;
              case 0xFF906F:
                  Serial.println("EQ");
                  break;
              case 0xFF6897:
                  Serial.println("0");
                  break;
              case 0xFF9867:
                  Serial.println("100+");
                  break;
              case 0xFFB04F:
                  Serial.println("200+");
                  break;
              default:
                  Serial.println( irrecv.results.value, HEX);
                  break;
           }
        irrecv.resume();
    }
    else
    {
      delay(1000);
    }*/
}
