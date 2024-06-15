[![Telegram](https://img.shields.io/badge/join-telegram-blue.svg?style=for-the-badge)](https://t.me/+W4rVVa0_VLEzYmI0)
 [![WhatsApp](https://img.shields.io/badge/join-whatsapp-green.svg?style=for-the-badge)](https://chat.whatsapp.com/FkNC7u83kuy2QRA5sqjBVg) 
 [![Donate](https://img.shields.io/badge/donate-$-brown.svg?style=for-the-badge)](http://paypal.me/mtpsilva)
 [![Say Thanks](https://img.shields.io/badge/Say%20Thanks-!-yellow.svg?style=for-the-badge)](https://saythanks.io/to/mtpsilva)
![](https://img.shields.io/github/last-commit/aeonSolutions/aeonlabs-open-software-catalogue?style=for-the-badge)
<a href="https://trackgit.com">
<img src="https://us-central1-trackgit-analytics.cloudfunctions.net/token/ping/lgeu3mh7autbw0q1rjhl" alt="trackgit-views" />
</a>
![](https://views.whatilearened.today/views/github/aeonSolutions/aeonlabs-open-software-catalogue.svg)
[![Open Source Love svg1](https://badges.frapsoft.com/os/v1/open-source.svg?v=103)](#)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat&label=Contributions&colorA=red&colorB=black	)](#)
[<img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" data-canonical-src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" height="30" />](https://www.buymeacoffee.com/migueltomas)

[Open Software Catalogue](https://github.com/aeonSolutions/aeonlabs-open-software-catalogue)  >> KTS1620 C++ Class Library

<p align="right">
 <a href="https://github-com.translate.goog/aeonSolutions/AeonLabs-WCH-Vendor-ID-Programming?_x_tr_sl=nl&_x_tr_tl=en&_x_tr_hl=en&_x_tr_pto=wapp">Change Language</a> <br>
Last update: 23-12-2023
</p>


# KTS1620 C++ Class Library 

Arduino library for KTS1620 - 24 channel I2C IO expander.


[![Arduino CI](https://github.com/RobTillaart/PCF8575/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PCF8575/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PCF8575/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PCF8575/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PCF8575/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PCF8575.svg)](https://github.com/RobTillaart/PCF8575/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PCF8575/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PCF8575.svg?maxAge=3600)](https://github.com/RobTillaart/PCF8575/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PCF8575.svg)](https://registry.platformio.org/libraries/robtillaart/PCF8575)

<br>

## Description

The library gives easy control over the 24 pins of the KTS1620 IC from Kinetic Technologies.

Base address = 0x20 + 0..3 depending on how the address pin is connected.

|  type      | address-range  |  notes                    |
|:-----------|:--------------:|:-------------------------:|
|  KTS1620   |  0x20 to 0x23  |                           |


\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
To be updated below
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


## Interface

```cpp
#include "PCF8575.h"
```

**PCF8575_INITIAL_VALUE** is a define that can be set compile time or before
the include of "pcf8575.h" to overrule the default value used with the 
**begin()** call.


#### Constructor

- **PCF8575(uint8_t deviceAddress = 0x20, TwoWire \*wire = &Wire)** Constructor with the optional 
I2C device address, default 0x20, and the optional Wire interface as parameter.
- **bool begin(uint8_t value = PCF8575_INITIAL_VALUE)** set the initial value for the pins and masks.
- **bool isConnected()** checks if the address is visible on the I2C bus.
- **bool setAddress(const uint8_t deviceAddress)** sets the device address after construction. 
Can be used to switch between PCF8575 modules runtime. Note this corrupts internal buffered values, 
so one might need to call **read16()** and/or **write16()**. 
Returns false if address is out of range 0x20..0x27 or if the address could not be found on I2C bus.
Returns true if address can be found on I2C bus.
- **uint8_t getAddress()** returns the device address.


#### Read and Write

- **uint16_t read16()** reads all 16 pins at once. This one does the actual reading.
- **uint8_t read(uint8_t pin)** reads a single pin; pin = 0..15.
- **uint16_t value()** returns the last read inputs again, as this information is buffered 
in the class this is faster than reread the pins.
- **void write16(uint16_t value)** writes all 16 pins at once. This one does the actual reading.
- **void write(uint8_t pin, uint8_t value)** writes a single pin; pin = 0..15; value is HIGH(1) or LOW (0).
- **uint16_t valueOut()** returns the last written data.


#### Button

The **"button"** functions are to be used when you mix input and output on one IC.
It does not change / affect the pins used for output by masking these.
Typical usage is to call **setButtonMask()** once in setup as pins do not (often) change
during program execution. 

- **void setButtonMask(const uint16_t mask)** sets the (bit) mask which lines are input.
- **uint16_t getButtonMask()** returns the set buttonMask.
- **uint16_t readButton16()** use the mask set by setButtonMask to select specific input pins.
- **uint16_t readButton16(uint16_t mask)** use a specific mask to select specific input pins.
Note this can be a subset of the pins set with **setButtonMask()** if one wants to process not all.
- **uint8_t readButton(uint8_t pin)** read a singe input pin.

Background - https://github.com/RobTillaart/Arduino/issues/38


#### Special

- **void toggle(uint8_t pin)** toggles a single pin.
- **void toggleMask(uint16_t mask)** toggles a selection of pins, 
if you want to invert all pins use 0xFFFF (default value).
- **void shiftRight(uint8_t n = 1)** shifts output channels n pins (default 1) pins right (e.g. LEDs ).
Fills the higher lines with zero's.
- **void shiftLeft(uint8_t n = 1)**  shifts output channels n pins (default 1) pins left (e.g. LEDs ).
Fills the lower lines with zero's.
- **void rotateRight(uint8_t n = 1)** rotates output channels to right, moving lowest line to highest line.
- **void rotateLeft(uint8_t n = 1)** rotates output channels to left, moving highest line to lowest line.
- **void reverse()** reverse the "bit pattern" of the lines, swapping pin 15 with 0, 14 with 1, 13 with 2 etc..


#### Select

Some convenience wrappers.

- **void select(const uint8_t pin)** sets a single pin to HIGH, all others are set to LOW.
If pin > 15 all pins are set to LOW.
Can be used to select one of n devices.
- **void selectN(const uint8_t pin)** sets pins 0..pin to HIGH, all others are set to LOW.
If pin > 15 all pins are set to LOW.
This can typical be used to implement a VU meter.
- **void selectNone()** sets all pins to LOW.
- **void selectAll()** sets all pins to HIGH.


#### Miscellaneous

- **int lastError()** returns the last error from the lib. (see .h file).


## Error codes

|  name               |  value  |  description              |
|:--------------------|:-------:|:--------------------------|
|  PCF8575_OK         |  0x00   |  no error                 |
|  PCF8575_PIN_ERROR  |  0x81   |  pin number out of range  |
|  PCF8575_I2C_ERROR  |  0x82   |  I2C communication error  |


## Testing

Testing the initial library is done by Colin Mackay (thanks!).
Platforms used for testing include: Nano, ESP32 and Seeed Xiao.


## Operation

See examples.

It is advised to use pull-up or pull-down resistors so the lines have a defined state at startup.




## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


