//
//    FILE: KTS1620.h
//  AUTHOR: Miguel Tomas
//    DATE: 2024-06-15
// VERSION: 0.0.1
// PURPOSE: Arduino library for KTS1620 - 24 channel I2C IO expander
//     URL: https://github.com/aeonSolutions/AeonLabs-KTS1620


#include "KTS1620.h"

//  adjust addresses if needed
KTS1620 KTS(0x21, &Wire1);  //  or Wire2 if supported


void doHigh()
{
  KTS.write(4, HIGH);
  int x = KTS.read16();
  Serial.print("Read ");
  Serial.println(x, HEX);
}


void doLow()
{
  KTS.write(4, LOW);
  int x = KTS.read16();
  Serial.print("Read ");
  Serial.println(x, HEX);
}


void doToggle()
{
  KTS.toggle(4);
  int x = KTS.read16();
  Serial.print("Read ");
  Serial.println(x, HEX);
}


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("KTS1620_LIB_VERSION:\t");
  Serial.println(KTS1620_LIB_VERSION);

  Wire.begin();

  if (!KTS.begin())
  {
    Serial.println("could not initialize...");
  }
  if (!KTS.isConnected())
  {
    Serial.println("=> not connected");
    while(1);
  }

  int x = KTS.read16();
  Serial.print("Read ");
  Serial.println(x, HEX);
  delay(1000);
}


void loop()
{
  Serial.println("HLT");
  while (Serial.available() == 0);
  switch (Serial.read())
  {
    case 'H': doHigh(); break;
    case 'L': doLow(); break;
    case 'T': doToggle(); break;
  }
}


//  -- END OF FILE --

