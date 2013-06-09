LTM8328PKR04
============

An Arduino library for LiteOn LTM-8328PKR-04 4x7 segments LED display.

2 pins are required to interface to the device.

Demo video :
http://www.youtube.com/watch?v=Hbep5Jvee7k

Part datasheet :
http://optoelectronics.liteon.com/en-us/api/DwonloadFileHandler.ashx?txtSpecNo=DS30-2001-090


To download, click the ZIP button above. Extract the zip file and  rename the uncompressed folder to LTM8328PKR04. Check that it contains  LTM8328PKR04.cpp,  LTM8328PKR04.h and keywords.txt.

Place the LTM8328PKR04 library folder in your &lt;arduinosketchfolder&gt;/libraries/ folder. Restart the IDE.


Example usage:
```c
/*

Example of LTM8328PKR04 library usage.

Connection:
  LTM8328PKR04 pins 3 & 8  --> to ground
  LTM8328PKR04 pin 4 (data) --> to Arduino pin 8 
  LTM8328PKR04 pin 5 (clock) --> to Arduino pin 9
  LTM8328PKR04 pin 6 (Vcc) --> to +5V
  LTM8328PKR04 pin 7 (dimmer) --> to +5V via 15kOhm resistor + 1nF capacitor if flickering occurs
  LTM8328PKR04 pin 9 (VLeds) --> to +3.3V

*/

#include <LTM8328PKR04.h>

const byte dataPin = 8;
const byte clockPin = 9;

LTM8328PKR04 counter(dataPin,clockPin);

void setup()
{

}

void loop()
{
  for(int i=-999;i<10000;i++)
  {
    counter.print(i);
    delay(100);
  }
}
```

