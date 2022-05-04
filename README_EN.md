# fixed
Implementing Fixed Point Calculations for Arduino

### Compatibility
Compatible with all Arduino platforms (using Arduino functions)

## Content
- [Install](#install)
- [Initialization](#init)
- [Usage](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found by the name **fixed** and installed via the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download library](https://github.com/GyverLibs/fixed/archive/refs/heads/main.zip) .zip archive for manual installation:
    - Unzip and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unzip and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/*
    - (Arduino IDE) automatic installation from .zip: *Sketch/Include library/Add .ZIP library…* and specify the downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE% D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Initialization
Not

<a id="usage"></a>
## Usage
See example

<a id="example"></a>
## Example
```cpp
#include <fixed.h>

void setup() {
  Serial.begin(9600);
  
  volatile fixed valuee(3, 100); // 0.03
  value *= 100; // 3.0
  value /= 2; // 1.5
  value += toFix(3, 10); // 1.8 (+0.3)
  Serial.println(value.toFloat());
  // 1730/188
  
  /*
  volatile float value = 0.03;
  value *= 100; // 3.0
  value /= 2; // 1.5
  value += 0.3; // 1.8 (+0.3)
  Serial println(value);
  // 3046/200
  */
  
  //Serial.println((int32_t&)value); // output fixed number
  //Serial.println(value.fix); // output fixed number
  //Serial.println(value.toInt()); // transfer to int
  //Serial.println(value.toFloat()); // transfer to float
  //Serial.println(expandFix(value)); // expanding macro
}

void loop() {
}
```

<a id="versions"></a>
## Versions
- v1.0

<a id="feedback"></a>
## Bugs and feedback
When you find bugs, create an **Issue**, or better, immediately write to the mail [alex@alexgyver.ru](mailto:alex@alexgyver.ru)
The library is open for revision and your **Pull Request**'s!