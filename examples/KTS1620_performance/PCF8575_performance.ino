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

volatile uint16_t x;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("KTS1620_LIB_VERSION:\t");
  Serial.println(KTS1620_LIB_VERSION);

  Wire.begin();

  KTS.begin();
  Serial.println(KTS.isConnected());
  delay(100);  //  time to flush Serial 


  for (long clk = 100000; clk < 600000; clk += 50000)
  {
    //  setup and measure
    Wire.setClock(clk);
    start = micros();
    x = KTS.read16();
    stop = micros();

    //  output results
    Serial.println(clk);
    Serial.print("Read:\t");
    Serial.print(stop - start);
    Serial.print("\t");
    Serial.println(x);             //  keep build CI compiler happy
    delay(1000);

    //  measure
    start = micros();
    KTS.write16(0xFFFF);
    stop = micros();

    //  output results
    Serial.print("Write:\t ");
    Serial.println(stop - start);
    delay(1000);
  }
}


void loop()
{
}


//  -- END OF FILE --

