#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "TESR_SmartFarm_mini.h"

#define OLED_RESET -1

Adafruit_SSD1306 OLED(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

TESR_SmartFarm_mini SmartFarm_mini;

byte TestingPin[7] = {Relay1,Relay2,Relay3,Relay4,RED,GREEN,BLUE};
String Message[7] = {"Relay1","Relay2","Relay3","Relay4","Red","Green","Blue"};

void setup() 
{
  SmartFarm_mini.begin();
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
}

void loop() 
{
  for(int count = 0 ; count < sizeof(TestingPin) ; count ++)
  {
    OLED.clearDisplay();       // clear display
    OLED.setTextColor(WHITE);  // set text color
    OLED.setCursor(0,0);
    OLED.setTextSize(2);
    OLED.println("Board");
    OLED.println("Testing");
    OLED.println(Message[count]);
    OLED.display(); 
    SmartFarm_mini.digitalWrite(TestingPin[count],ON);
    delay(150);
    SmartFarm_mini.digitalWrite(TestingPin[count],OFF);
    delay(150);
  }
  OLED.clearDisplay();       // clear display
  OLED.setTextColor(WHITE);  // set text color
  OLED.setCursor(0,0);
  OLED.setTextSize(2);
  OLED.println("Board");
  OLED.println("Testing");
  OLED.println("White");
  OLED.display(); 
  SmartFarm_mini.writeGPIO(0x00); // ON white color
  delay(150);
  SmartFarm_mini.writeGPIO(0x07); // OFF white color
  delay(150);
}
