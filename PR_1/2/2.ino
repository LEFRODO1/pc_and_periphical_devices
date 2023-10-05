int buttonState = 0;  
void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, INPUT);
  
}

void loop() {
buttonState = digitalRead(buttonPin);
ledState = digitalRead(D0);
ledState2 = digitalRead(D1);
ledState3 = digitalRead(D3);

if (buttonState == HIGH && ledState == HIGH)
{
  digitalWrite(D0, LOW);
  digitalWrite(D1, HIGH);
}

else if (buttonState == HIGHh && ledState2 == HIGH)
{
  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
}

else if (buttonState == HIGH && ledState3 == HIGH)
{
  digitalWrite(D2, LOW);
  digitalWrite(D0, HIGH);
}
}