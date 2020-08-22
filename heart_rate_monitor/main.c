
#include<reg51.h>
#include<lcd.h>	
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// -=-=-=-=- Hardware Defines -=-=-=-=-=-=-=
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
sbit SENSOR = P1^0; //sensor is connected to this pin
unsigned int beatms;
float bpm;
char buf[20];
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// -=-=-=-=- Main Program -=-=-=-=-=-=-=
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void main()
{
// -=-=- Intialize variables -=-=-=
lcdInit();
// -=-=- Welcome LCD Message -=-=-=
lcdClear();
lcdGotoXY(0,0); // 1st Line of LCD
// "xxxxxxxxxxxxxxxx"
lcdPrint("DIGITAL HEART");
lcdGotoXY(0,1); // 2nd Line of LCD
// "xxxxxxxxxxxxxxxx"
lcdPrint("BEAT MONITOR");
beatms=0; // will store duration between two pulses
// -=-=- Program Loop -=-=-=
while(1)
{
while(SENSOR==0);// wait for high pulse from sensor
DelayNmS(10); // 10ms delay so that it does not listen to any noise
beatms = 10; // start counting beatms from 10ms since we have delay after pulse
while(SENSOR==1)// wait until signal is high
{
DelayNmS(1); //wait 1msec
beatms++; //keep incrementing counter each 1ms
}
while(SENSOR==0) //keep looping till signal goes back high, wait for next
{
DelayNmS(1); //wait 1msec
beatms++; //keep incrementing counter each 1ms
}
// beatms variable will now have time in ms between two high edge pulse
lcdClear();
lcdGotoXY(0,0);
lcdPrint("HEART RATE : ");
bpm = (float)60000/beatms; // see document of #1157 for this calculation
if(bpm > 200)
{
lcdGotoXY(0,1);
sprintf (buf, "Processing......"); // Invalid, Wait for next cycle
lcdPrint(buf);
} else {
lcdGotoXY(0,1);
sprintf (buf, "%0.0f BPM", bpm); // Display reading in BPM
lcdPrint(buf);
}
}
}
 