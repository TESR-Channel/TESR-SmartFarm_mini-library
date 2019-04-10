/*************************************************** 
  This is a library for the TESR Smart Farm mini Board

  Written by Anoney Potter from TESR
 ****************************************************/

#include "Arduino.h"
#include <Wire.h>
#include <pgmspace.h>
#include "TESR_SmartFarm_mini.h"

void TESR_SmartFarm_mini::begin(uint8_t addr) 
{
  if (addr > 7) 
  {
    addr = 7;
  }
  i2caddr = addr;

  Wire.begin();

  // set defaults!
  Wire.beginTransmission(MCP23008_ADDRESS | i2caddr);
  Wire.write((byte)MCP23008_IODIR);
  Wire.write((byte)0x00);  
  Wire.endTransmission();

  Wire.beginTransmission(MCP23008_ADDRESS | i2caddr);
  Wire.write((byte)MCP23008_GPIO);
  Wire.write((byte)0x0F);  
  Wire.endTransmission();
}

void TESR_SmartFarm_mini::begin(void) 
{
  begin(0);
}


void TESR_SmartFarm_mini::digitalWrite(uint8_t pin, uint8_t logic) {
  uint8_t gpio;
  
  // only 8 bits!
  if (pin > 7)
    return;

  // read the current GPIO output latches
  gpio = readGPIO();

  if (pin > 2) // for Relay Active High
  {
    // set the pin and direction
    if (logic == HIGH) 
    {
      gpio |= 1 << pin; 
    } 
    else 
    {
      gpio &= ~(1 << pin);
    }
  }
  else // for RGB Active LOW
  {
    // set the pin and direction
    if (logic == LOW) 
    {
      gpio |= 1 << pin; 
    } 
    else 
    {
      gpio &= ~(1 << pin);
    }
  }
  
  

  // write the new GPIO
  writeGPIO(gpio);
}

uint8_t TESR_SmartFarm_mini::digitalRead(uint8_t pin) 
{
  // only 8 bits!
  if (pin > 7)
    return 0;

  // read the current GPIO
  return (readGPIO() >> pin) & 0x1;
}

void TESR_SmartFarm_mini::writeGPIO(uint8_t gpio) 
{
  write8(MCP23008_GPIO, gpio);
}

void TESR_SmartFarm_mini::write8(uint8_t addr, uint8_t data) 
{
  Wire.beginTransmission(MCP23008_ADDRESS | i2caddr);
  Wire.write((byte)addr);
  Wire.write((byte)data);
  Wire.endTransmission();
}

uint8_t TESR_SmartFarm_mini::readGPIO(void) 
{
  // read the current GPIO input 
  return read8(MCP23008_GPIO);
}

uint8_t TESR_SmartFarm_mini::read8(uint8_t addr) 
{
  Wire.beginTransmission(MCP23008_ADDRESS | i2caddr);
  Wire.write((byte)addr);	
  Wire.endTransmission();
  Wire.requestFrom(MCP23008_ADDRESS | i2caddr, 1);
  return Wire.read();
}
