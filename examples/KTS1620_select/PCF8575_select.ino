//
//    FILE: KTS1620.h
//  AUTHOR: Miguel Tomas
//    DATE: 2024-06-15
// VERSION: 0.0.1
// PURPOSE: Arduino library for KTS1620 - 24 channel I2C IO expander
//     URL: https://github.com/aeonSolutions/AeonLabs-KTS1620


#include "KTS1620.h"

KTS1620 KTS(0x20);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("KTS1620_LIB_VERSION:\t");
  Serial.println(KTS1620_LIB_VERSION);

  Wire.begin();

  KTS.begin();
  Serial.println(KTS.isConnected());
  Serial.println();

  KTS.selectAll();
  delay(1000);
  KTS.selectNone();
  delay(1000);
  
  //  VU meter up
  for (int i = 0; i < 15; i++)
  {
    KTS.selectN(i);
    delay(100);
  }

  //  VU meter down
  for (int i = 15; i >= 0; i--)
  {
    KTS.selectN(i);
    delay(100);
  }
}


void loop()
{
  //  night rider
  for (int i = 0; i < 15; i++)
  {
    KTS.select(i);
    delay(100);
  }
  for (int i = 15; i >= 0; i--)
  {
    KTS.select(i);
    delay(100);
  }
}


//  -- END OF FILE --

