#include "TESR_SmartFarm_mini.h"

TESR_SmartFarm_mini SmartFarm_mini;

void setup() 
{
  SmartFarm_mini.begin();
}

void loop() 
{
  SmartFarm_mini.digitalWrite(Relay1,ON);
  delay(1000);
  SmartFarm_mini.digitalWrite(Relay1,OFF);
  delay(1000);
}
