#include "Adafruit_NeoPixel.h"
#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT11
#define PIN            6
#define NUMPIXELS      10

int blueLedVal = 0;
int greenLedVal = 0;
int redLedVal = 0;

float h, t;
int delayval = 50; // delay for half a second

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  pixels.setBrightness(255);
  pixels.begin();
  Serial.begin(9600); 
  Serial.println("DHTxx test!");
  dht.begin();
}

void loop() {

   // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    h = dht.readHumidity();
    t = dht.readTemperature();

    // check if returns are valid, if they are NaN (not a number) then something went wrong!
    if (isnan(t) || isnan(h)) {
        Serial.println("Failed to read from DHT");
    } 
    else {
        Serial.print("Humidity: "); 
        Serial.print(h);
        Serial.print(" %\t");
        Serial.print("Temperature: "); 
        Serial.print(t);
        Serial.println(" *C");

        t = (t-15)*25.6;

        if(t > 768){
          blueLedVal = 0;
          greenLedVal = 0;
          redLedVal = 255;
        }else if(t < 0){
          blueLedVal = 0;
          greenLedVal = 0;
          redLedVal = 0;
        }else{
          if(t>=485){
            blueLedVal = 0;
            greenLedVal = 0;
            redLedVal = t-460;
          }else if(t >255){
            blueLedVal = 0;
            greenLedVal = t-230;
            redLedVal = 0;
          }else{
            blueLedVal = t;
            greenLedVal = 0;
            redLedVal = 0;
          }
        }

        for(int i = 0; i<10; i++){
          pixels.setPixelColor(i, pixels.Color(redLedVal,greenLedVal,blueLedVal)); // Moderately bright green color.
        }
    
        pixels.show(); // This sends the updated pixel color to the hardware.
    }
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  
}
