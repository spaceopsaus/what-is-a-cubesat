//The loudness sensor from Seeedstudio
//More info from http://wiki.seeedstudio.com/Grove-Loudness_Sensor/

//variable to hold the voltage.
int loudness;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
  //The loudness sensor is based on reading the voltage of the A0 channel.
  //The louder the sound, the greater voltage is output from A0.

  //When you blow over the sensor, you may get values above 600
  //Amdbient office environment will be near 200.

  //A dial on the board can help tune maximum values recieved.
  
    loudness = analogRead(0); //Using port A0 or analog zero. Connect the sensor to A0 as marked.
    Serial.println(loudness);
    delay(200);
}
