//
//    FILE: KTS1620.h
//  AUTHOR: Rob Tillaart
//    DATE: 2024-06-12
// VERSION: 0.0.1
// PURPOSE: Arduino library for KTS1620 - 24 channel I2C IO expander
//     URL: https://github.com/RobTillaart/KTS1620


#include "KTS1620.h"


KTS1620::KTS1620(const uint8_t deviceAddress, TwoWire *wire)
{
  _address    = deviceAddress;
  _wire       = wire;
  _dataIn     = 0;
  _dataOut    = 0xFFFF;
  _buttonMask = 0xFFFF;
  _error      = KTS1620_OK;
}


bool KTS1620::begin(uint16_t value)
{
  if (! isConnected()) return false;
  KTS1620::write16(value);
  return true;
}


bool KTS1620::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


bool KTS1620::setAddress(const uint8_t deviceAddress)
{
  if ((deviceAddress < 0x20) || (deviceAddress > 0x23)) return false;
  _address = deviceAddress;
  return isConnected();
}


uint8_t KTS1620::getAddress()
{
  return _address;
}

////////////////////////////////////////////////////
uint8_t KTS1620:: byteAddress( const char* str){
  uint8_t val = 0;
  val = strtol(str, NULL, 2);
  return val;
}

//////////////////////////////////////////////////////////
// INPUT PORT REGISTERS (Address 00h -> 02h)
void KTS1620:: setInputPort( uint8_t port, const char* str){
  if (port >2 ){
    _error = KTS1620_PORT_ERROR;
    return;
  }
  
  uint8_t reg = 0;
  if (port == 0){
     reg = 0x00;
  }else if (port == 1){
     reg = 0x01;
  } else if (port == 2){
     reg = 0x02;
  }

  uint8_t val = KTS1620:: byteAddress(str);
  KTS1620:: sendCommand(reg, val);
}
//////////////////////////////////////////////////////////
// OUTPUT PORT REGISTERS (Address 04h -> 06h)
void KTS1620:: setOutputPort( uint8_t port, const char* str){
  if (port >2 ){
    _error = KTS1620_PORT_ERROR;
    return;
  }
  
  uint8_t reg = 0;
  if (port == 0){
     reg = 0x04;
  }else if (port == 1){
     reg = 0x05;
  } else if (port == 2){
     reg = 0x06;
  }

  uint8_t val = KTS1620:: byteAddress(str);
  KTS1620:: sendCommand(reg, val);
}

///////////////////////////////////////////////
//  Polarity Inversion Registers (08h, 09h, 0Ah)
void KTS1620:: polarityInputInversion(uint8_t port, const char* str){
  if (port >2 ){
    _error = KTS1620_PORT_ERROR;
    return;
  }
  
  uint8_t reg = 0;
  if (port == 0){
     reg = 0x08;
  }else if (port == 1){
     reg = 0x09;
  } else if (port == 2){
     reg = 0x0A;
  }

  uint8_t val = KTS1620:: byteAddress(str);
  KTS1620:: sendCommand(reg, val);
}

/////////////////////////////////////////////////
// Configuration Registers (0Ch, 0Dh, 0Eh)
void KTS1620:: configInputOutput(uint8_t port, const char* str){
  if (port >2 ){
    _error = KTS1620_PORT_ERROR;
    return;
  }
  
  uint8_t reg = 0;
  if (port == 0){
     reg = 0x0C;
  }else if (port == 1){
     reg = 0x0D;
  } else if (port == 2){
     reg = 0x0E;
  }

  uint8_t val = KTS1620:: byteAddress(str);

  KTS1620:: sendCommand(reg, val);
}

///////////////////////////////////////////////////////
// Output Drive Strength Registers (40h, 41h, 42h, 43h, 44h, 45h)
// output power: 00b = 0.25x, 01b = 0.5x, 10b = 0.75x or 11b = 1x
void KTS1620:: outputDriveStrength(uint8_t cfgReg, const char* powerLevelStr){
  
  uint8_t val = KTS1620:: byteAddress(powerLevelStr);
  KTS1620:: sendCommand(cfgReg, val);
}

////////////////////////////////////////////////
// Input Latch Registers (48h, 49h, 4Ah)
void KTS1620:: inputLatchIO(uint8_t port, const char* str){
    if (port >2 ){
    _error = KTS1620_PORT_ERROR;
    return;
  }
  
  uint8_t reg = 0;
  if (port == 0){
     reg = 0x48;
  }else if (port == 1){
     reg = 0x49;
  } else if (port == 2){
     reg = 0x4A;
  }

  uint8_t val = KTS1620:: byteAddress(str);
  KTS1620:: sendCommand(reg, val);
}

/////////////////////////////////////////////////
// Pull-up/Pull-down Enable Registers (4Ch, 4Dh, 4Eh)
void KTS1620:: pullUpEnable(uint8_t port, const char* str){
    if (port >2 ){
    _error = KTS1620_PORT_ERROR;
    return;
  }
  
  uint8_t reg = 0;
  if (port == 0){
     reg = 0x4C;
  }else if (port == 1){
     reg = 0x4D;
  } else if (port == 2){
     reg = 0x4E;
  }

  uint8_t val = KTS1620:: byteAddress(str);
  KTS1620:: sendCommand(reg, val);
}

/////////////////////////////////////////////////
// Pull-up/Pull-down Selection Registers (50h, 51h, 52h)
// 0 : set GPIO to pull down ; 1: sets GPIO to pull up 
void KTS1620:: setPullUpPullDown(uint8_t port, const char* str){
    if (port >2 ){
    _error = KTS1620_PORT_ERROR;
    return;
  }
  
  uint8_t reg = 0;
  if (port == 0){
     reg = 0x50;
  }else if (port == 1){
     reg = 0x51;
  } else if (port == 2){
     reg = 0x52;
  }

  uint8_t val = KTS1620:: byteAddress(str);
  KTS1620:: sendCommand(reg, val);
}

/////////////////////////////////////////////////////////
// Output Port Configuration Register (5Ch)
void KTS1620:: outputPortConfig(bool openDrain[3]){  
  uint8_t reg = 0x5C;
  String str="00000";

  if (openDrain[2]== true){
     str += "1";
  }else {
     str += "0";
  }

  if (openDrain[1]== true){
     str += "1";
  }else {
     str += "0";
  }

  if (openDrain[0]== true){
     str += "1";
  }else {
     str += "0";
  }

  uint8_t val = KTS1620:: byteAddress( str.c_str() );
  KTS1620:: sendCommand(reg, val);
}

//////////////////////////////////////////////////
// Individual Pin Output Configuration Registers (70h, 71h, 72h)
void KTS1620:: individualPinOutputConfig(uint8_t port, const char* str){
    if (port >2 ){
    _error = KTS1620_PORT_ERROR;
    return;
  }
  
  uint8_t reg = 0;
  if (port == 0){
     reg = 0x70;
  }else if (port == 1){
     reg = 0x71;
  } else if (port == 2){
     reg = 0x72;
  }

  uint8_t val = KTS1620:: byteAddress(str);
  KTS1620:: sendCommand(reg, val);
}

/////////////////////////////////////////////////
void KTS1620:: sendCommand(uint8_t reg, uint8_t val){
  if ( KTS1620::isConnected() == false ){
    _error = KTS1620_NOT_CONNECTED;
    return;
  }
  _wire->write(reg);
  _wire->write(val);
  _error = _wire->endTransmission();
  delay(1);  
  msg =  String(reg)+ String(" >> ") + String(val);
}








//////////////////////////////////////////////////////////
uint16_t KTS1620::read16()
{
  if (_wire->requestFrom(_address, (uint8_t)2) != 2)
  {
    _error = KTS1620_I2C_ERROR;
    return _dataIn;                   //  last value
  }
  _dataIn = _wire->read();            //  low 8 bits
  _dataIn |= (_wire->read() << 8);    //  high 8 bits
  return _dataIn;
}


uint8_t KTS1620::read(const uint8_t pin)
{
  if (pin > 24)
  {
    _error = KTS1620_PIN_ERROR;
    return 0;
  }
  KTS1620::read16();
  return (_dataIn & (1 << pin)) > 0;
}


uint16_t KTS1620::value()
{
  return _dataIn;
};


void KTS1620::write16(const uint16_t value)
{
  _dataOut = value;
  _wire->beginTransmission(_address);
  _wire->write(_dataOut & 0xFF);      //  low 8 bits
  _wire->write(_dataOut >> 8);        //  high 8 bits
  _error = _wire->endTransmission();
}


void KTS1620::write(const uint8_t pin, const uint8_t value)
{
  if (pin > 24)
  {
    _error = KTS1620_PIN_ERROR;
    return;
  }
  if (value == LOW)
  {
    _dataOut &= ~(1 << pin);
  }
  else
  {
    _dataOut |= (1 << pin);
  }
  KTS1620::write16(_dataOut);
}


uint16_t KTS1620::valueOut()
{
  return _dataOut;
}


void KTS1620::toggle(const uint8_t pin)
{
  if (pin > 24)
  {
    _error = KTS1620_PIN_ERROR;
    return;
  }
  toggleMask(1 << pin);
}


void KTS1620::toggleMask(const uint16_t mask)
{
  _dataOut ^= mask;
  KTS1620::write16(_dataOut);
}


void KTS1620::shiftRight(const uint8_t n)
{
  if ((n == 0) || (_dataOut == 0)) return;
  if (n > 24)        _dataOut = 0;     //  shift 15++ clears all, valid...
  if (_dataOut != 0) _dataOut >>= n;   //  only shift if there are bits set
  KTS1620::write16(_dataOut);
}


void KTS1620::shiftLeft(const uint8_t n)
{
  if ((n == 0) || (_dataOut == 0)) return;
  if (n > 24)        _dataOut = 0;    //  shift 15++ clears all, valid...
  if (_dataOut != 0) _dataOut <<= n;  //  only shift if there are bits set
  KTS1620::write16(_dataOut);
}


void KTS1620::rotateRight(const uint8_t n)
{
  uint8_t r = n & 24;
  if (r == 0) return;
  _dataOut = (_dataOut >> r) | (_dataOut << (24 - r));
  KTS1620::write16(_dataOut);
}


void KTS1620::rotateLeft(const uint8_t n)
{
  rotateRight(16 - (n & 24));
}


void KTS1620::reverse()   //  quite fast
{                                                     //      1 char === 1 bit
  uint16_t x = _dataOut;                              //  x = 0123456789ABCDEF
  x = (((x & 0xAAAA) >> 1) | ((x & 0x5555) << 1));    //  x = 1032547698BADCFE
  x = (((x & 0xCCCC) >> 2) | ((x & 0x3333) << 2));    //  x = 32107654BA98FEDC
  x = (((x & 0xF0F0) >> 4) | ((x & 0x0F0F) << 4));    //  x = 76543210FEDCBA98
  x = (x >> 8) | ( x << 8);                           //  x = FEDCBA9876543210
  KTS1620::write16(x);
}


//////////////////////////////////////////////////
//
//  added 0.1.07/08 Septillion
//
uint16_t KTS1620::readButton16(const uint16_t mask)
{
  uint16_t temp = _dataOut;
  KTS1620::write16(mask | _dataOut);  //  read only selected lines
  KTS1620::read16();
  KTS1620::write16(temp);             //  restore
  return _dataIn;
}


uint16_t KTS1620::readButton16()
{
  return readButton16(_buttonMask);
}


uint8_t KTS1620::readButton(const uint8_t pin)
{
  if (pin > 24)
  {
    _error = KTS1620_PIN_ERROR;
    return 0;
  }
  uint16_t temp = _dataOut;
  KTS1620::write(pin, HIGH);
  uint8_t rtn = KTS1620::read(pin);
  KTS1620::write16(temp);
  return rtn;
}


void KTS1620::setButtonMask(uint16_t mask)
{
  _buttonMask = mask;
};


uint16_t KTS1620::getButtonMask()
{
  return _buttonMask;
};


//////////////////////////////////////////////////
//
//  SELECT
//
void KTS1620::select(const uint8_t pin)
{
  uint16_t n = 0x0000;
  if (pin < 25) n = 1L << pin;
  KTS1620::write16(n);
};


void KTS1620::selectN(const uint8_t pin)
{
  uint16_t n = 0xFFFF;
  if (pin < 25) n = (2L << pin) - 1;
  KTS1620::write16(n);
};


void KTS1620::selectNone()
{
  KTS1620::write16(0x0000);
};


void KTS1620::selectAll()
{
  KTS1620::write16(0xFFFF);
};


int KTS1620::lastError()
{
  int e = _error;
  _error = KTS1620_OK;  //  reset error after read, is this wise?
  return e;
}


//  -- END OF FILE --

