
#include "BMI088.h"

float ax = 0, ay = 0, az = 0;
float gx = 0, gy = 0, gz = 0;
int16_t temp = 0;

void setup(void)
{
    Wire.begin();
    Serial.begin(115200);
    
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
}

void loop(void)
{    
    bmi088.getAcceleration(&ax, &ay, &az);
    bmi088.getGyroscope(&gx, &gy, &gz);
    temp = bmi088.getTemperature();
    
    Serial.print(ax/1000*9.81);Serial.print("m/s/s\t");
    Serial.print(ay/1000*9.81);Serial.print("m/s/s\t");
    Serial.print(az/1000*9.81);Serial.print("m/s/s\t");
    
    Serial.print(gx);Serial.print("deg/s\t");
    Serial.print(gy);Serial.print("deg/s\t");
    Serial.print(gz);Serial.print("deg/s\t");
    
    Serial.println(temp);
    
    delay(50);
}
