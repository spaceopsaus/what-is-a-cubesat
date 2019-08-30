// Mashup of DHT humidity/temperature sensors and buzzer
// Based of ladyada, public domain
// The following code combines the temperature sensor readings to then turn the buzzer on and off
// When the buzzer turns on and off will depend on the temperature of the environment.

#include "DHT.h"

#define DHTPIN 2         //Connect the temp sensor to digital pin 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int buzzerPin = 6;      // Buzzer connected to digital pin 6
unsigned char val = 5;  // variable to store the read value


void setup() 
{
    pinMode(buzzerPin, OUTPUT);  // sets the pin as output
    Serial.begin(9600); 
    Serial.println("DHTxx test!");

    /*if using WIO link,must pull up the power pin.*/
    // pinMode(PIN_GROVE_POWER, OUTPUT);
    // digitalWrite(PIN_GROVE_POWER, 1);

    dht.begin();
}


void loop() 
{
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    // check if returns are valid, if they are NaN (not a number) then something went wrong!
    if (isnan(t) || isnan(h)) 
    {
        Serial.println("Failed to read from DHT");
    } 
    else 
    {
      //if the temperature is greater than set value, buzz at define val.
      //else, set buzz to zero. This almost means, make no sound!
      if (t>28)
      {
        analogWrite(buzzerPin, val);
      }
      else
      {
        analogWrite(buzzerPin, 0);
      }
      //Using serial monitor will display values as well.
        Serial.print("Humidity: "); 
        Serial.print(h);
        Serial.print(" %\t");
        Serial.print("Temperature: "); 
        Serial.print(t);
        Serial.println(" *C");
    }
}
