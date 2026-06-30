This is an automatic translation and may be incorrect in some places. See the source README and examples for authoritative information.

[![latest](https://img.shields.io/github/v/release/GyverLibs/fixed.svg?color=brightgreen)](https://github.com/GyverLibs/fixed/releases/latest/download/fixed.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/fixed.svg)](https://registry.platformio.org/libraries/gyverlibs/fixed)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/fixed?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# fixed
32-bit fixed-point type implementation for Arduino
- Partition size (accuracy) to choose from
- Overloaded all operators for convenience
- All methods are done.`constexpr`
- Literal suffixes for numbers in the program
- Calculations 2-4 times faster than float
- Support for all operations takes 1.5 kB less than float

### Compatibility
Compatible with all Arduino platforms (Arduino features are used)

## Contents
- [Use of use](#usage)
- [Example](#example)
- [Versions](#versions)
- [Installation](#install)
- [Bugs and feedback](#feedback)

<a id="usage"></a>

## Use of use
Type`fixed`It can be used as a data type instead of`float`.

### Class class
```cpp
fixed(любой тип);

int32_t getRaw();
int32_t toInt();
float toFloat();

static int32_t MAX_INT;
static int32_t MIN_INT;
```

### precision
By default.`fixed`It has 16 bits for integer and 16 bits for fractional, but there are options:

| | Precision, bit | Precision, min. | Entire part, +-max. |
|------------------- |---------- |------------ |-------------------------------------------------------------- |
|`fixedT<дробных_бит>`| To choose from |`1 / 2^бит`    | `2^(31 - бит)`       |
| `fixed8`              | 8             | `0.0039`       | `8'388'608`          |
| `fixed16`             | 16            | `0.000015`     | `32'768`             |
| `fixed24`             | 24            | `0.00000006`   | `128`                |

### Overflow * and /
For formats with fewer than 16 fractional bits, division and multiplication use a fast 32-bit intermediate value by default, which may overflow. `fixed16`, `fixed24`, and more precise formats automatically use 64-bit intermediates. You can force 64-bit calculations for every format:

```cpp
#define FIXED_USE_64
#include <fixed.h>
```

This prevents intermediate overflow, but the result must still fit the selected format. On some platforms, code size and execution speed may become close to `float`.

### Literatures
In the program can be added to the number of literals, for example.`3.14_fx8`number`3.14`straight-up`fixed8`, i.e. analogue call`fixed8(3.14)`eh`123_fx16`- in format`fixed16`.

<a id="example"></a>

## Example
```cpp
#include <fixed.h>

void setup() {
  Serial.begin(115200);

  fixed f;
  f = 123;
  f += 0.456;

  Serial.println(f.toFloat());

  fixed f2 = (12.34 + f * 123) / 12;

  Serial.println(f2.toInt());

  // autoconversion
  int iv = f2;
  float fv = f2;

  // comparison
  if (f2) {}
  f2 == 123;
  f2 > 3.14;

  // action
  f2 = -f2;
  f2 += 123;
  f2 += f;
}

void loop() {
}
```

<a id="versions"></a>

## Versions
- v1.0
- v2.0 - library rewritten, improved, added operators and constexpt

<a id="install"></a>

## Installation
- The library can be found by the name **fixed** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download the library](https://github.com/GyverLibs/fixed/archive/refs/heads/main.zip).zip archive for manual installation:
    - Unpack and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unpack and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/ *
    - (Arduino IDE) Automatic installation from .zip: *Sketch/Connect library/Add .ZIP library...* and specify downloaded archive
- Read more detailed instructions for installing libraries[here](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: new versions fix errors and bugs, as well as optimize and add new features.
- Through the library manager IDE: find the library as when installing and click "Update"
- Manually: **Delete the folder with the old version** and then put the new one in its place. “Replacement” can not be done: sometimes new versions delete files that will remain when replaced and can lead to errors!

<a id="feedback"></a>

## Bugs and feedback
If you find bugs, create **Issue**, or better write to the mail immediately.[alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
The library is open for revision and your **Pull Requests*!

When reporting bugs or incorrect work of the library, it is necessary to specify:
- Library version
- What is used by the IC
- SDK version (for ESP)
- Arduino IDE version
- Are embedded examples that use features and designs that cause bugs in your code working correctly?
- What code was downloaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed. Not a canvas of a thousand lines, but a minimum code.
