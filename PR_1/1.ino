int buttonState = 0;  
void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D1, INPUT);
}

void loop() {
  buttonState = digitalRead(D1);

  if (buttonState == HIGH) {
    
    digitalWrite(D0, HIGH);
  } else {
    
    digitalWrite(D0, LOW);
  }
}