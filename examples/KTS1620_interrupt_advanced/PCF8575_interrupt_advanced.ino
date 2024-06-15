//
//    FILE: KTS1620.h
//  AUTHOR: Miguel Tomas
//    DATE: 2024-06-15
// VERSION: 0.0.1
// PURPOSE: Arduino library for KTS1620 - 24 channel I2C IO expander
//     URL: https://github.com/aeonSolutions/AeonLabs-KTS1620
//
//  TEST SETUP
//   Connect INT pin of the KTS1620 to UNO pin 2
//
//   (from figure 4 datasheet
//   Place a pull up resistor 4K7 between pin and 5V
//   Place a capacitor 10-400 pF between pin and GND


#include "KTS1620.h"

KTS1620 KTS(0x20);


////////////////////////////////////
//
//  INTERRUPT ROUTINE + FLAG
//
const int IRQPIN = 2;

volatile uint8_t interruptCount = 0;

void KTS_irq()
{
  interruptCount++;
}


////////////////////////////////////
//
//  MAIN CODE
//
void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("KTS1620_LIB_VERSION: ");
  Serial.println(KTS1620_LIB_VERSION);

  Wire.begin();
  KTS.begin();

  pinMode(IRQPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IRQPIN), KTS_irq, FALLING);
}


void loop()
{
  uint32_t now = millis();

  //  make a local copy of the counter.
  noInterrupts();
  uint8_t irq_count = interruptCount;
  interruptCount = 0;
  interrupts();

  if (irq_count > 0)
  {
    if (irq_count > 1)
    {
      Serial.print("IRQ missed: ");
      Serial.println(irq_count - 1);  //  as last will be handled
    }
    uint16_t x = KTS.read16();
    Serial.print("READ:\t");
    Serial.print('\t');
    Serial.print(now);
    Serial.print('\t');
    Serial.println(x, HEX);
  }

  //  simulate doing other things here.
  //  uses to a large delay to miss IRQ's on purpose.
  delay(1000);
}


//  -- END OF FILE --

