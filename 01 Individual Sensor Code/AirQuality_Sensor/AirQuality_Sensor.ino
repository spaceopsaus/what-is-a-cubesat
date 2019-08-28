/*
  AirQuality Demo V1.0.
  connect to A0 to start testing. it will needs about 20s to start 
  Further information from http://wiki.seeedstudio.com/Grove-Air_Quality_Sensor_v1.3/
* By: http://www.seeedstudio.com
*/
#include"AirQuality.h"
#include"Arduino.h"

AirQuality airqualitysensor;
int current_quality = -1;

void setup()
{
  //Be sure to adjust the baudrate in Serial Monitor to match 9600
    Serial.begin(9600);
    //This sensor uses analog input to provide a value
    //Connect the sensor to port A0.
    airqualitysensor.init(A0);
}
void loop()
{
  //The sensor works with ranges to determine the quality of air
  //The ranges are based on voltage readings from the board.
  //These ranges can be found inside the AirQuality.cpp file starting from line 88.
  //By blowing air over the sensor or walking it outdoors you can see the value change.
  
    current_quality=airqualitysensor.slope();
    if (current_quality >= 0)// if a valid data returned.
    {
        if (current_quality==0)
            Serial.println("High pollution! Force signal active");
        else if (current_quality==1)
            Serial.println("High pollution!");
        else if (current_quality==2)
            Serial.println("Low pollution!");
        else if (current_quality ==3)
            Serial.println("Fresh air");
    }
}

ISR(TIMER1_OVF_vect)
{
	if(airqualitysensor.counter==61)//set 2 seconds as a detected duty
	{
			airqualitysensor.last_vol=airqualitysensor.first_vol;
			airqualitysensor.first_vol=analogRead(A0);
			airqualitysensor.counter=0;
			airqualitysensor.timer_index=1;
			PORTB=PORTB^0x20;
	}
	else
	{
		airqualitysensor.counter++;
	}
}
