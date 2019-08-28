//Code for the 6 Axis Accelerometer and Gyroscope
//Also known as the BMI088.
//More info at http://wiki.seeedstudio.com/Grove-6-Axis_Accelerometer&Gyroscope(BMI088)/

#include "BMI088.h"

//declare variables for acceleration x,y,z
float ax = 0, ay = 0, az = 0;

//delcare variables for gyro or also known as the rate of rotation for x,y,z axis
float gx = 0, gy = 0, gz = 0;

//delcare variable for the temperature which is built into the sensor
//typically used as part of calibration
int16_t temp = 0;

void setup(void)
{
    //This sensor will connect to the I2C line.
    Wire.begin();

    //Be sure to update the baud rate in the Serial monitor when viewing
    //Higher baudrate means more sampling of sensor and more data
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

    //Display out the acceleration. Acceleration is measured in metres per second squared.
    Serial.print(ax/1000*9.81);Serial.print("m/s/s\t");
    Serial.print(ay/1000*9.81);Serial.print("m/s/s\t");
    Serial.print(az/1000*9.81);Serial.print("m/s/s\t");

    //Display out the rotational velocity. Meaasured in degrees per second.
    Serial.print(gx);Serial.print("deg/s\t");
    Serial.print(gy);Serial.print("deg/s\t");
    Serial.print(gz);Serial.print("deg/s\t");

    //Display out the temperature. Measured in degrees Centigrade.
    Serial.println(temp);
    
    delay(50);
}
