//Please see LED_Temperature _sensor_brightness for detail explanation
#include "Adafruit_NeoPixel.h"
#include "DHT.h"

#define DHTPIN 2 //Temperature sensor pin nunber
#define DHTTYPE DHT11
#define PIN            6 // LED pin number
#define NUMPIXELS      10
#define NUM_LEDS 10

int blueLedVal = 0;
int greenLedVal = 0;
int redLedVal = 0;
int light;

float h, t;
int delayval = 50; // delay for half a second

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);//Global initialisation for saparate LEDs
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

    if(t > 45){
      blueLedVal = 0;
      greenLedVal = 0;
      redLedVal = 255;
          
      for(int i = 0; i<10; i++){
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
        pixels.setPixelColor(i, pixels.Color(redLedVal,greenLedVal,blueLedVal)); 
      } 
        }
    else if(t < 5){//t<5 blue
      blueLedVal = 255;
      greenLedVal = 0;
      redLedVal = 0;
          
        for(int i = 0; i<10; i++){
          pixels.setPixelColor(i, pixels.Color(redLedVal,greenLedVal,blueLedVal)); 
        }
    }
    else{
      light = round((t-5)/4);//An LED lid up with every 4 deg celsius increase
      for(int i = 0; i<light ; i++){
        pixels.setPixelColor(i, pixels.Color(0,150,0)); 
      }
    }
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(100);
  for(int i = 0; i<NUMPIXELS ; i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0)); 
  }
}
