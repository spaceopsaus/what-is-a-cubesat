//Buzzer

int buzzerPin = 6;               // Buzzer connected to digital pin 6
unsigned char val = 128;         // variable to store loudness of buzzer 0 -> 255

void setup() {
  pinMode(buzzerPin, OUTPUT);  // sets the pin as output
}

void loop() {
  analogWrite(buzzerPin, val); //on a loop send a signal to the buzzer to produce a sound.
}
