//In this little experiment, the RGB LED gradually changes its colour from blueish purple to red
//base on the reading of the gx value of the gyro(row).
//The buzzer will be activated as the row surpass the threshold.

//Reference(Packages can be downloaded from links below)
//Buzzer: http://wiki.seeedstudio.com/Grove-Buzzer/
//6 axis accelerometer& gyro: http://wiki.seeedstudio.com/Grove-6-Axis_Accelerometer&Gyroscope(BMI088)/
//LED strip: http://wiki.seeedstudio.com/Grove-RGB_LED_Stick-10-WS2813_Mini/  

#include "BMI088.h" //Accelerometer & gyroscope library
#include "Adafruit_NeoPixel.h" //RGB LEDs library
#define PIN            6// plug LED in pin D6
#define NUMPIXELS      10

//variables from 6axis accelerometer & gyro
float ax = 0, ay = 0, az = 0;
float gx = 0, gy = 0, gz = 0;
int16_t temp = 0;
int red = 0, green = 0, blue = 0;

//LED global initialisation
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup(void){
  // gyro setup(pin I2C)
    Wire.begin();
    Serial.begin(115200);// Please be aware of the baud rate.
    
    while(!Serial);
    Serial.println("BMI088 Raw Data");
    
    while(1)
    {
        if(bmi088.isConnection())
        {
            bmi088.initialize();
            Serial.println("BMI088 is connected");
            break;
        }
        else Serial.println("BMI088 is not connected");
        
        delay(2000);
        
    }
  //LED setup(pin D6)
  pixels.setBrightness(255);
  pixels.begin(); // This initializes the NeoPixel library.
  //buzzer setup(pin D5)
  pinMode(5, OUTPUT);
}

void loop(void)
{  //Get values from gyroscope
    bmi088.getAcceleration(&ax, &ay, &az);
    bmi088.getGyroscope(&gx, &gy, &gz);
    temp = bmi088.getTemperature();
    //row angular velocity more than 511: buzzer on LED red at all time
    if(abs(gx)>511){
        //brightest red
        red = 255;
        green = 0;
        blue = 0;
        //Buzzer on
        digitalWrite(5, HIGH);
    }
    //Otherwise LED colour changes gradually base on the row(in deg/sec)
    //colour range can be obtained from colour picker websites such as
    //https://www.w3schools.com/colors/colors_picker.asp?color=%23ffab00
    else {
      digitalWrite(5, LOW);
      if(abs(gx)>383){
        red = 255;
        green = 255*(1-(abs(gx)-383)/128);//green from 255 to 0
        blue = 0;
      }
      if(abs(gx)> 255){
          red = 255*(abs(gx)-255)/128;//red from 0 to 255
          green = 255;
          blue = 0;   
      }
      else if(abs(gx)>127){
          red = 0;
          green = 255;
          blue = 255*(1-(abs(gx)-127)/128); //blue from 0 to 255
      }
      else {
          red = 0;
          green = 255*(abs(gx)/128);//green from 255 to 0
          blue = 255;
    }
  }
    // Hardware update for the LED
    for(int i = 0; i<10; i++){ 
    pixels.setPixelColor(i, pixels.Color(red,green,blue)); 
    }
    // Counting starts at zero
    // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

    pixels.show(); // This sends the updated pixel color to the hardware.
    Serial.print(ax/1000*9.81);Serial.print("m/s/s\t");
    Serial.print(ay/1000*9.81);Serial.print("m/s/s\t");
    Serial.print(az/1000*9.81);Serial.print("m/s/s\t");
    
    Serial.print(gx);Serial.print("deg/s\t");
    Serial.print(gy);Serial.print("deg/s\t");
    Serial.print(gz);Serial.print("deg/s\t");
    
    Serial.println(temp);
    
    delay(50);
 }



