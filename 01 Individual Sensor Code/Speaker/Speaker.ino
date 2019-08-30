/*macro definition of Speaker pin*/
//The speaker is able to output at a variety of sounds.
//These sounds can vary from loudness and pitches.

//You can supply different frequency signal to this module with Arduino. 
//Arduino generates these signal via PWM or even digital write and delay.
//Here we are going to show you how to generate these signals using delay(), the speaker sound bass 1~7.
  
#define SPEAKER 3 //For this code, the speaker will use digital pin 3

int BassTab[]={1911,1702,1516,1431,1275,1136,1012};//bass 1~7


void setup()
{
    pinInit();
}
void loop()
{
        /*sound bass 1~7*/
    for(int note_index=0;note_index<7;note_index++)
    {
        sound(note_index);
        delay(500);
    }
}
void pinInit()
{
    pinMode(SPEAKER,OUTPUT);
    digitalWrite(SPEAKER,LOW);
}
void sound(uint8_t note_index)
{
    for(int i=0;i<100;i++)
    {
        digitalWrite(SPEAKER,HIGH);
        delayMicroseconds(BassTab[note_index]);
        digitalWrite(SPEAKER,LOW);
        delayMicroseconds(BassTab[note_index]);
    }
}
