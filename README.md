[![](https://dcbadge.vercel.app/api/server/hw3j3RwfJf) ](https://discord.gg/hw3j3RwfJf)
 [![Donate](https://img.shields.io/badge/donate-$-brown.svg?style=for-the-badge)](http://paypal.me/mtpsilva)
<a href="https://github.com/sponsors/aeonSolutions">
   <img height="40" src="https://github.com/aeonSolutions/PCB-Prototyping-Catalogue/blob/main/media/become_a_github_sponsor.png">
</a>
[<img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" data-canonical-src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" height="30" />](https://www.buymeacoffee.com/migueltomas)
![](https://img.shields.io/github/last-commit/aeonSolutions/aeonlabs-open-software-catalogue?style=for-the-badge)
<a href="https://trackgit.com">
<img src="https://us-central1-trackgit-analytics.cloudfunctions.net/token/ping/lgeu3mh7autbw0q1rjhl" alt="trackgit-views" />
</a>
![](https://views.whatilearened.today/views/github/aeonSolutions/aeonlabs-open-software-catalogue.svg)
[![Open Source Love svg1](https://badges.frapsoft.com/os/v1/open-source.svg?v=103)](#)

[Open Software Catalogue](https://github.com/aeonSolutions/aeonlabs-open-software-catalogue)  >> KTS1620 C++ Class Library

<p align="right">
 <a href="https://github-com.translate.goog/aeonSolutions/AeonLabs-WCH-Vendor-ID-Programming?_x_tr_sl=nl&_x_tr_tl=en&_x_tr_hl=en&_x_tr_pto=wapp">Change Language</a> <br>
Last update: 15-06-2024
</p>


# KTS1620 C++ Class Library 

Arduino library for KTS1620 - 24 channel I2C IO expander.


[![Arduino CI](https://github.com/aeonSolutions/AeonLabs-KTS1620/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/aeonSolutions/AeonLabs-KTS1620/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/aeonSolutions/AeonLabs-KTS1620/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/aeonSolutions/AeonLabs-KTS1620/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/aeonSolutions/AeonLabs-KTS1620/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/aeonSolutions/AeonLabs-KTS1620.svg)](https://github.com/aeonSolutions/AeonLabs-KTS1620/issues)


<br>

## Description

The library gives easy control over the 24 pins of the KTS1620 IC from Kinetic Technologies.

Base address = 0x20 + 0..3 depending on how the address pin is connected.

|  type      | address-range  |  notes                    |
|:-----------|:--------------:|:-------------------------:|
|  KTS1620   |  0x20 to 0x23  |                           |


## Interface

```cpp
#include "KTS1620.h"
```

**KTS1620_INITIAL_VALUE** is a define that can be set at compile time or before
the include of "KTS1620.h" to overrule the default value used with the 
**begin()** call.


#### Constructor

- **KTS1620(uint8_t deviceAddress = 0x20, TwoWire \*wire = &Wire)** Constructor with the optional 
I2C device address, default 0x20, and the optional Wire interface as a parameter.
- **bool begin(uint8_t value = KTS1620_INITIAL_VALUE)** set the initial value for the pins and masks.
- **bool isConnected()** checks if the address is visible on the I2C bus.
- **bool setAddress(const uint8_t deviceAddress)** sets the device address after construction. 
Returns false if the address is out of range 0x20..0x23 or if the address cannot be found on the I2C bus.
Returns true if the address can be found on the I2C bus.
- **uint8_t getAddress()** returns the device address.
- 
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
To be updated below
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\





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




<br />
<br />


## Author

You can get in touch with me on my LinkedIn Profile:

#### Miguel Tomas

[![LinkedIn Link](https://img.shields.io/badge/Connect-Miguel--Tomas-blue.svg?logo=linkedin&longCache=true&style=social&label=Connect)](https://www.linkedin.com/in/migueltomas/)

<a href="https://stackexchange.com/users/18907312/miguel-silva"><img src="https://stackexchange.com/users/flair/18907312.png" width="208" height="58" alt="profile for Miguel Silva on Stack Exchange, a network of free, community-driven Q&amp;A sites" title="profile for Miguel Silva on Stack Exchange, a network of free, community-driven Q&amp;A sites" /></a>

<a href="https://app.userfeel.com/t/2f6cb1e0" target="_blank"><img src="https://app.userfeel.com/tester/737648/image?.png" width="257" class="no-b-lazy"></a>

You can also follow my GitHub Profile to stay updated about my latest projects: [![GitHub Follow](https://img.shields.io/badge/Connect-Miguel--Tomas-blue.svg?logo=Github&longCache=true&style=social&label=Follow)](https://github.com/aeonSolutions)

<br>

**Hire me** <br>
See [here](https://github.com/aeonSolutions/PCB-Prototyping-Catalogue/wiki/How-to-Hire-AeonLabs) how to hire AeonLabs.

<br>

### Be supportive of my dedication and work towards technology education and buy me a cup of coffee
The PCB design Files I provide here for anyone to use are free. If you like this Smart Device or use it, please consider buying me a cup of coffee, a slice of pizza, or a book to help me study, eat, and think new PCB design files.

<p align="center">
    <a href="https://www.buymeacoffee.com/migueltomas">
        <img height="35" src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png">
    </a>
</p>


### Make a donation on PayPal
Make a donation on PayPal and get a TAX refund*.

<p align="center">
    <a href="http://paypal.me/mtpsilva">
        <img height="35" src="https://github.com/aeonSolutions/PCB-Prototyping-Catalogue/blob/main/media/paypal_small.png">
    </a>
</p>

### Support all these open hardware projects and become a GitHub sponsor  
Did you like any of my PCB KiCad Designs? Help and Support my open work to all by becoming a GitHub sponsor.

<p align="center">
    <a href="https://github.com/aeonSolutions/PCB-Prototyping-Catalogue/blob/main/become_a_sponsor/aeonlabs-github-sponsorship-agreement.docx">
        <img height="50" src="https://github.com/aeonSolutions/PCB-Prototyping-Catalogue/blob/main/media/want_to_become_a_sponsor.png">
    </a>
    <a href="https://github.com/sponsors/aeonSolutions">
        <img height="50" src="https://github.com/aeonSolutions/PCB-Prototyping-Catalogue/blob/main/media/become_a_github_sponsor.png">
    </a>
</p>

# 

### License

Before proceeding to download any of AeonLabs software solutions for open-source development and/or PCB hardware electronics development make sure you are choosing the right license for your project. See [AeonLabs Solutions for Open Hardware & Source Development](https://github.com/aeonSolutions/PCB-Prototyping-Catalogue/wiki/AeonLabs-Solutions-for-Open-Hardware-&-Source-Development) for more information. 


