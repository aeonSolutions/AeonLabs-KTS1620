#pragma once
//
//    FILE: KTS1620.h
//  AUTHOR: Rob Tillaart
//    DATE: 2024-06-12
// VERSION: 0.0.1
// PURPOSE: Arduino library for KTS1620 - 24 channel I2C IO expander
//     URL: https://github.com/RobTillaart/KTS1620


#include "Arduino.h"
#include "Wire.h"


#define KTS1620_LIB_VERSION      (F("0.0.1"))


#ifndef KTS1620_DEFAULT_ADDR
#define KTS1620_DEFAULT_ADDR    0x20
#endif

#define KTS1620_OK               0x00
#define KTS1620_PIN_ERROR        0x81
#define KTS1620_I2C_ERROR        0x82
#define KTS1620_PORT_ERROR       0x03
#define KTS1620_NOT_CONNECTED    0x04

class KTS1620
{
public:
  //  deviceAddress base = 0x20 + depends on address bits
  explicit KTS1620(const uint8_t deviceAddress = 0x20, TwoWire *wire = &Wire);

  bool     begin(uint16_t value = KTS1620_DEFAULT_ADDR);
  bool     isConnected();


  //  note: setting the address may corrupt internal buffer values
  //        and should not be used unless it is needed.
  //  a read16() / write16() call updates them.
  bool     setAddress(const uint8_t deviceAddress);
  uint8_t  getAddress();


void setInputPort (uint8_t port, const char* str);
void setOutputPort (uint8_t port, const char* str);

void polarityInputInversion(uint8_t port, const char* str);
void configInputOutput(uint8_t port, const char* str);
void outputDriveStrength(uint8_t cfgReg, const char* powerLevelStr);

void inputLatchIO(uint8_t port, const char* str);

void setPullUpPullDown(uint8_t port, const char* str);
void pullUpEnable(uint8_t port, const char* str);

void outputPortConfig(bool openDrain[3]);
void individualPinOutputConfig(uint8_t port, const char* str);

void sendCommand(uint8_t reg, uint8_t val);
uint8_t byteAddress( const char* str);
///////////////////////////////////////////////////////////

  uint16_t read16();
  uint8_t  read(uint8_t pin);
  uint16_t value();


  void     write16(const uint16_t value);
  void     write(const uint8_t pin, const uint8_t value);
  uint16_t valueOut();


  //  added 0.1.07/08 Septillion
  uint16_t readButton16();
  uint16_t readButton16(const uint16_t mask);
  uint8_t  readButton(const uint8_t pin);
  void     setButtonMask(uint16_t mask);
  uint16_t getButtonMask();


  //  rotate, shift, toggle, reverse expect all lines are output
  void     toggle(const uint8_t pin);
  void     toggleMask(const uint16_t mask = 0xFFFF);  //  0xFFFF == invertAll()
  void     shiftRight(const uint8_t n = 1);
  void     shiftLeft(const uint8_t n = 1);
  void     rotateRight(const uint8_t n = 1);
  void     rotateLeft(const uint8_t n = 1);
  void     reverse();


  void     select(const uint8_t pin);
  void     selectN(const uint8_t pin);
  void     selectNone();
  void     selectAll();


  int      lastError();
  String msg;


private:
  uint8_t  _address;
  uint16_t _dataIn;
  uint16_t _dataOut;
  uint16_t _buttonMask;
  int      _error;

  TwoWire*  _wire;
};


//  -- END OF FILE --

