//
//    FILE: KTS1620.h
//  AUTHOR: Miguel Tomas
//    DATE: 2024-06-15
// VERSION: 0.0.1
// PURPOSE: Arduino library for KTS1620 - 24 channel I2C IO expander
//     URL: https://github.com/aeonSolutions/AeonLabs-KTS1620


#include "PCF8575.h"

//  adjust addresses if needed
PCF8575 A(0x20);
PCF8575 B(0x21);
PCF8575 C(0x22);

PCF8575 PCF[3] = { A, B, C };


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCF8575_LIB_VERSION:\t");
  Serial.println(PCF8575_LIB_VERSION);

  Wire.begin();

  for (int i = 0; i < 3; i++)
  {
    PCF[i].begin();
  }
}


void loop()
{
  for (int i = 0; i < 3; i++)
  {
    for (uint8_t port = 0; port < 16; port++)
    {
      PCF[i].write(port, 1);
      delay(200);
    }
  }

  for (int i = 0; i < 3; i++)
  {
    for (uint8_t port = 0; port < 16; port++)
    {
      PCF[i].write(port, 0);
      delay(400);
    }
  }

}


//  -- END OF FILE --

