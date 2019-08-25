int buzzerPin = 6;      // LED connected to digital pin 9
unsigned char val = 128;         // variable to store the read value

void setup() {
  pinMode(buzzerPin, OUTPUT);  // sets the pin as output
}

void loop() {
  
  analogWrite(buzzerPin, val);
}
