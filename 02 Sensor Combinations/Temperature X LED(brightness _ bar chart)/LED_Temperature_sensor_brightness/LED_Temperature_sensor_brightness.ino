 //Reference(Packages can be downloaded from links below)
//6 axis accelerometer& gyro: http://wiki.seeedstudio.com/Grove-6-Axis_Accelerometer&Gyroscope(BMI088)/
//LED strip: http://wiki.seeedstudio.com/Grove-RGB_LED_Stick-10-WS2813_Mini/

#include "Adafruit_NeoPixel.h"//RGB LEDs library
#include "DHT.h"// Temperature sensor library

#define DHTPIN 2 // temperature sensor connect to pin D2
#define DHTTYPE DHT11
#define PIN            6 // LED connect to pin D6
#define NUMPIXELS      10 // number of LEDs

//LED variables initiation
int blueLedVal = 0;
int greenLedVal = 0;
int redLedVal = 0;

//temperature sensor variables
float h, t;
int delayval = 50; // delay for half a second

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);//LED global initialisation
DHT dht(DHTPIN, DHTTYPE);//Temperature sensor global initialisation

void setup() {
  //LED setup
  pixels.setBrightness(255);
  pixels.begin();
  //Temperature sensor setup
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
        //Assume temperature reading in range 15-45 degree celsius
        t = (t-15)*25.6;//scale up the temperature values(You can change it to whatever scalig method you like)
        // Effect: Red@>35 -> Green@>25 -> Blue@<=25(deday due to the slow sensor)
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
          pixels.setPixelColor(i, pixels.Color(redLedVal,greenLedVal,blueLedVal)); 
        }
    
        pixels.show(); // This sends the updated pixel color to the hardware.
    }
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  
}
