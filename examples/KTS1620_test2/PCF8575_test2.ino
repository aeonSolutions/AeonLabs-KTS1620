//
//    FILE: KTS1620.h
//  AUTHOR: Miguel Tomas
//    DATE: 2024-06-15
// VERSION: 0.0.1
// PURPOSE: Arduino library for KTS1620 - 24 channel I2C IO expander
//     URL: https://github.com/aeonSolutions/AeonLabs-KTS1620


#include "KTS1620.h"

//  adjust addresses if needed
KTS1620 KTS(0x21);  //  add LEDs to lines      (used as output)


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("KTS1620_LIB_VERSION:\t");
  Serial.println(KTS1620_LIB_VERSION);

  Wire.begin();

  KTS.begin();

  KTS.write(0, 1);
  for (int i = 0; i < 15; i++)
  {
    KTS.rotateLeft();
    delay(100);
  }

  for (int i = 0; i < 15; i++)
  {
    KTS.rotateRight();
    delay(100);
  }

  for (int i = 0; i < 15; i++)
  {
    KTS.rotateLeft(3);
    delay(100);
  }

  for (int i = 0; i < 15; i++)
  {
    KTS.rotateRight(2);
    delay(100);
  }

  for (uint16_t i = 0; i < 65535; i += 253)
  {
    KTS.toggleMask(i);
    delay(100);
  }

  //  0010 0111  -> 0x27
  //  1110 0100
  KTS.write16(0x2755);
  for (int i = 0; i < 255; i++)
  {
    KTS.reverse();
    delay(100);
  }
}


void loop()
{
}


//  -- END OF FILE --

