//
//    FILE: KTS1620.h
//  AUTHOR: Miguel Tomas
//    DATE: 2024-06-15
// VERSION: 0.0.1
// PURPOSE: Arduino library for KTS1620 - 24 channel I2C IO expander
//     URL: https://github.com/aeonSolutions/AeonLabs-KTS1620
//
//  TEST SETUP
//  Connect INT pin of the PCF8575 to UNO pin 2
//
//  (from figure 4 datasheet
//  Place a pull up resistor 4K7 between pin and 5V
//  Place a capacitor 10-400 pF between pin and GND


#include "PCF8575.h"

PCF8575 PCF(0x20);


////////////////////////////////////
//
//  INTERRUPT ROUTINE + FLAG
//
const int IRQPIN = 2;

volatile bool flag = false;

void pcf_irq()
{
  flag = true;
}


////////////////////////////////////
//
//  MAIN CODE
//
void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCF8575_LIB_VERSION:\t");
  Serial.println(PCF8575_LIB_VERSION);

  Wire.begin();

  PCF.begin();

  pinMode(IRQPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IRQPIN), pcf_irq, FALLING);
}


void loop()
{
  uint32_t now = millis();
  if (flag)
  {
    flag = false;
    uint16_t x = PCF.read16();
    Serial.print("READ:\t");
    Serial.print('\t');
    Serial.print(now);
    Serial.print('\t');
    Serial.println(x, HEX);
  }
  //  do other things here
  delay(10);
}


//  -- END OF FILE --

