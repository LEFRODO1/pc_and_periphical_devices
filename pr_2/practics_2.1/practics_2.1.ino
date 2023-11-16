#include <Servo.h>

Servo servo;


void setup() {
  servo.attach(D0, 600, 2600);
}

void loop() 
{
  int potValue = analogRead(A0);
  
  
  int angle = map(potValue, 0, 1023, 0, 180);
  
  servo.write(angle);
  
  delay(15); 