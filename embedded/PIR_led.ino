int led = 11;
int PIR = 10;
int state = LOW;             // by default, no motion detected
int val = 0;   

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(PIR, INPUT);
  Serial.begin(9600);    
}

void loop() {
  
  val = digitalRead(PIR);   // read sensor value
  
  if (val == HIGH) {           // check if the sensor is HIGH
    digitalWrite(led, HIGH);   // turn LED ON
    delay(500);                // delay 100 milliseconds 
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
    }
  } 
  else {
      digitalWrite(led, LOW); // turn LED OFF
      delay(500);             // delay 200 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
    }
  }
}
