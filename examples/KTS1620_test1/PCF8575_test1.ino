//
//    FILE: KTS1620.h
//  AUTHOR: Miguel Tomas
//    DATE: 2024-06-15
// VERSION: 0.0.1
// PURPOSE: Arduino library for KTS1620 - 24 channel I2C IO expander
//     URL: https://github.com/aeonSolutions/AeonLabs-KTS1620


#include "KTS1620.h"

//  adjust addresses if needed
KTS1620 KTS_20(0x20);  //  add switches to lines  (used as input)
KTS1620 KTS_21(0x21);  //  add LEDs to lines      (used as output)


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("KTS1620_LIB_VERSION:\t");
  Serial.println(KTS1620_LIB_VERSION);

  Wire.begin();

  KTS_20.begin();
  KTS_21.begin();

  uint16_t value = KTS_20.read16();
  Serial.print("#38:\t");
  Serial.println(value);

  for (int i = 0; i < 255; i++)
  {
    KTS_21.write16(i);
    delay(100);
  }

  KTS_21.write(0, 1);
  for (int i = 0; i < 15; i++)
  {
    KTS_21.shiftLeft();
    delay(100);
  }

  for (int i = 0; i < 15; i++)
  {
    KTS_21.shiftRight();
    delay(100);
  }

  for (int i = 0; i < 16; i++)
  {
    KTS_21.write(i, 1);
    delay(100);
    KTS_21.write(i, 0);
    delay(100);
  }

  for (int i = 0; i < 16; i++)
  {
    KTS_21.toggle(i);
    delay(100);
    KTS_21.toggle(i);
    delay(100);
  }
}


void loop()
{
  //  echoes the lines
  uint16_t value = KTS_20.read16();
  KTS_21.write16(value);
  delay(100);
}


//  -- END OF FILE --

