//
//    FILE: unit_test_001.cpp
//  AUTHOR: Miguel Tomas
//    DATE: 2024-06-15
// PURPOSE: unit tests for the KTS1620 - 24 channel I2C IO expander.
//          https://github.com/aeonSolutions/AeonLabs-KTS1620
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual);               // a == b
// assertNotEqual(unwanted, actual);            // a != b
// assertComparativeEquivalent(expected, actual);    // abs(a - b) == 0 or (!(a > b) && !(a < b))
// assertComparativeNotEquivalent(unwanted, actual); // abs(a - b) > 0  or ((a > b) || (a < b))
// assertLess(upperBound, actual);              // a < b
// assertMore(lowerBound, actual);              // a > b
// assertLessOrEqual(upperBound, actual);       // a <= b
// assertMoreOrEqual(lowerBound, actual);       // a >= b
// assertTrue(actual);
// assertFalse(actual);
// assertNull(actual);

// // special cases for floats
// assertEqualFloat(expected, actual, epsilon);    // fabs(a - b) <= epsilon
// assertNotEqualFloat(unwanted, actual, epsilon); // fabs(a - b) >= epsilon
// assertInfinity(actual);                         // isinf(a)
// assertNotInfinity(actual);                      // !isinf(a)
// assertNAN(arg);                                 // isnan(a)
// assertNotNAN(arg);                              // !isnan(a)

#include <ArduinoUnitTests.h>


#include "Arduino.h"
#include "KTS1620.h"


KTS1620 PCF(0x38);


unittest_setup()
{
  fprintf(stderr, "KTS1620_LIB_VERSION: %s\n", (char *) KTS1620_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(KTS1620_INITIAL_VALUE, 0xFFFF);
  assertEqual(KTS1620_OK           , 0x00);
  assertEqual(KTS1620_PIN_ERROR    , 0x81);
  assertEqual(KTS1620_I2C_ERROR    , 0x82);
}


unittest(test_begin)
{
  KTS1620 PCF(0x38);

  Wire.begin();
  PCF.begin();

  int readValue = PCF.read16();
  assertEqual(0, readValue);

  int I2Cerror = KTS1620_I2C_ERROR;
  assertEqual(I2Cerror, PCF.lastError());
}


unittest(test_read)
{
  KTS1620 PCF(0x38);
  int readValue;

  Wire.begin();

  PCF.begin();
  for (int i = 0; i < 8; i++)
  {
    fprintf(stderr, "line %d\n", i);
    readValue = PCF.read(i);
    assertEqual(0, readValue);

    int I2Cerror = KTS1620_I2C_ERROR;
    assertEqual(I2Cerror, PCF.lastError());
  }

  fprintf(stderr, "test KTS1620_PIN_ERROR\n");
  readValue = PCF.read(16);
  assertEqual(0, readValue);
  int PINerror = KTS1620_PIN_ERROR;
  assertEqual(PINerror, PCF.lastError());
}


unittest_main()


//  -- END OF FILE --

