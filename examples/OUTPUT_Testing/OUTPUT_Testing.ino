#include "TESR_SmartFarm_mini.h"

TESR_SmartFarm_mini SmartFarm_mini;

byte TestingPin[7] = {Relay1,Relay2,Relay3,Relay4,RED,GREEN,BLUE};

void setup() 
{
  SmartFarm_mini.begin();
}

void loop() 
{
  for(int count = 0 ; count < sizeof(TestingPin) ; count ++)
  {
    SmartFarm_mini.digitalWrite(TestingPin[count],ON);
    delay(150);
    SmartFarm_mini.digitalWrite(TestingPin[count],OFF);
    delay(150);
  }
  SmartFarm_mini.writeGPIO(0x00); // ON white color
  delay(150);
  SmartFarm_mini.writeGPIO(0x07); // OFF white color
  delay(150);
}
