//
//    FILE: KTS1620.h
//  AUTHOR: Miguel Tomas
//    DATE: 2024-06-15
// VERSION: 0.0.1
// PURPOSE: Arduino library for KTS1620 - 24 channel I2C IO expander
//     URL: https://github.com/aeonSolutions/AeonLabs-KTS1620


#include "KTS1620.h"

KTS1620 KTS(0x20);


void doHigh()
{
  KTS.write(4, HIGH);
  int x = KTS.read16();
  Serial.print("Read ");
  printHex(x);
}


void doLow()
{
  KTS.write(4, LOW);
  int x = KTS.read16();
  Serial.print("Read ");
  printHex(x);
}


void doToggle()
{
  KTS.toggle(4);
  int x = KTS.read16();
  Serial.print("Read ");
  printHex(x);
}


void printHex(uint16_t x)
{
  if (x < 0x1000) Serial.print('0');
  if (x < 0x100)  Serial.print('0');
  if (x < 0x10)   Serial.print('0');
  Serial.println(x, HEX);
}



void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("KTS1620_LIB_VERSION:\t");
  Serial.println(KTS1620_LIB_VERSION);

  Wire.begin();

  KTS.begin();

  uint16_t x = KTS.read16();
  Serial.print("Read ");
  printHex(x);
  delay(1000);
}


void loop()
{
  Serial.println("HLT");
  while (Serial.available() == 0);
  switch(Serial.read())
  {
    case 'H': doHigh(); break;
    case 'L': doLow(); break;
    case 'T': doToggle(); break;
  }
}


//  -- END OF FILE --

