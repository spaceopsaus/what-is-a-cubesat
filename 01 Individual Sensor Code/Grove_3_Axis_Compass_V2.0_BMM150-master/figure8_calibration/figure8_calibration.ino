// The aim of this code is to calibrate the compass base on local magnetism. 
//It is suggested that the compass should be placed as far away from unwanted interference as possible
// which includes all electronics and wires. During the calibration process, 
//the user should draw an infinity symbol with the compass sensor as shown in figure 8 under img folder.
#include <Arduino.h>
#include <Wire.h>
//import sensor calibration libraries
#include "bmm150.h"
#include "bmm150_defs.h"

BMM150 bmm = BMM150();//Starts a new BMM150 object
bmm150_mag_data value_offset;

void setup()
{
  Serial.begin(9600);

  if(bmm.initialize() == BMM150_E_ID_NOT_CONFORM) {
    Serial.println("Chip ID can not read!");
    while(1);
  } else {
    Serial.println("Initialize done!");
  }

  Serial.println("Start figure-8 calibration after 3 seconds.");
  delay(3000);
  calibrate(10000);
  Serial.print("\n\rCalibrate done..");

}

/**
 * @brief Do figure-8 calibration for a limited time to get offset values of x/y/z axis.
 * @param timeout - seconds of calibration period.
*/
void calibrate(uint32_t timeout)
{//Initialise all variables
  int16_t value_x_min = 0;
  int16_t value_x_max = 0;
  int16_t value_y_min = 0;
  int16_t value_y_max = 0;
  int16_t value_z_min = 0;
  int16_t value_z_max = 0;
  uint32_t timeStart = 0;

  bmm.read_mag_data();  //read coresponding values and assign
  value_x_min = bmm.raw_mag_data.raw_datax;
  value_x_max = bmm.raw_mag_data.raw_datax;
  value_y_min = bmm.raw_mag_data.raw_datay;
  value_y_max = bmm.raw_mag_data.raw_datay;
  value_z_min = bmm.raw_mag_data.raw_dataz;
  value_z_max = bmm.raw_mag_data.raw_dataz;
  delay(100);

  timeStart = millis();//count milliseconds from the moment it starts

  //This while loop perform calibration on the sensor to retreive raw data.
  //It starts the timer function(Arduiono built-in) 
  //and continueously updates the max and min xyz orientations in degrees.
  //At the end of the loop, the value of offset data from each direction
  //will be calculated from the raw data.
  while((millis() - timeStart) < timeout)
  {
    bmm.read_mag_data();
    
    /* Update x-Axis max/min value */
    if(value_x_min > bmm.raw_mag_data.raw_datax)
    {
      value_x_min = bmm.raw_mag_data.raw_datax;
      // Serial.print("Update value_x_min: ");
      // Serial.println(value_x_min);

    } 
    else if(value_x_max < bmm.raw_mag_data.raw_datax)
    {
      value_x_max = bmm.raw_mag_data.raw_datax;
      // Serial.print("update value_x_max: ");
      // Serial.println(value_x_max);
    }

    /* Update y-Axis max/min value */
    if(value_y_min > bmm.raw_mag_data.raw_datay)
    {
      value_y_min = bmm.raw_mag_data.raw_datay;
      // Serial.print("Update value_y_min: ");
      // Serial.println(value_y_min);

    } 
    else if(value_y_max < bmm.raw_mag_data.raw_datay)
    {
      value_y_max = bmm.raw_mag_data.raw_datay;
      // Serial.print("update value_y_max: ");
      // Serial.println(value_y_max);
    }

    /* Update z-Axis max/min value */
    if(value_z_min > bmm.raw_mag_data.raw_dataz)
    {
      value_z_min = bmm.raw_mag_data.raw_dataz;
      // Serial.print("Update value_z_min: ");
      // Serial.println(value_z_min);

    } 
    else if(value_z_max < bmm.raw_mag_data.raw_dataz)
    {
      value_z_max = bmm.raw_mag_data.raw_dataz;
      // Serial.print("update value_z_max: ");
      // Serial.println(value_z_max);
    }
    
    Serial.print(".");
    delay(100);

  }

  value_offset.x = value_x_min + (value_x_max - value_x_min)/2;
  value_offset.y = value_y_min + (value_y_max - value_y_min)/2;
  value_offset.z = value_z_min + (value_z_max - value_z_min)/2;
}

//In the loop below, the calibrated heading data will be calculated
//by substracting the offset value.
void loop()
{
  bmm150_mag_data value;
  bmm.read_mag_data();

  value.x = bmm.raw_mag_data.raw_datax - value_offset.x;
  value.y = bmm.raw_mag_data.raw_datay - value_offset.y;
  value.z = bmm.raw_mag_data.raw_dataz - value_offset.z;

  float xyHeading = atan2(value.x, value.y);
  float zxHeading = atan2(value.z, value.x);
  float heading = xyHeading;

  if(heading < 0)
    heading += 2*PI;
  if(heading > 2*PI)
    heading -= 2*PI;
  float headingDegrees = heading * 180/M_PI; 
  float xyHeadingDegrees = xyHeading * 180 / M_PI;
  float zxHeadingDegrees = zxHeading * 180 / M_PI;

//Please comment and uncomment the following lines out to print the heading value you want
  Serial.print("Heading: ");
  //The heading is base on the negative z-axis 
  //and it should conrespond to N of a real compass
  Serial.println(headingDegrees);
  //Serial.print("xyHeading: ");
  //Serial.println(xyHeadingDegrees);
  //Serial.print("zxHeading: ");
  //Serial.println(zxHeadingDegrees);
  
  delay(100);
}
