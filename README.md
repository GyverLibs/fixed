![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)
![author](https://img.shields.io/badge/author-AlexGyver-informational.svg)
# fixed
Реализация вычислений с фиксированной точкой для Arduino

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

## Содержание
- [Установка](#install)
- [Инициализация](#init)
- [Использование](#usage)
- [Пример](#example)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **fixed** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/fixed/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Инициализация
Нет

<a id="usage"></a>
## Использование
См. пример

<a id="example"></a>
## Пример
```cpp
#include <fixed.h>

void setup() {
  Serial.begin(9600);
  
  volatile fixed value(3, 100);    // 0.03
  value *= 100;           // 3.0 
  value /= 2;             // 1.5
  value += toFix(3, 10);  // 1.8 (+0.3) 
  Serial.println(value.toFloat());
  // 1730/188
  
  /*
  volatile float value = 0.03;
  value *= 100;           // 3.0 
  value /= 2;             // 1.5
  value += 0.3;           // 1.8 (+0.3) 
  Serial.println(value);
  // 3046/200
  */
  
  //Serial.println((int32_t&)value);  // вывод fixed числа
  //Serial.println(value.fix);        // вывод fixed числа
  //Serial.println(value.toInt());      // перевод в int
  //Serial.println(value.toFloat());  // перевод в float
  //Serial.println(expandFix(value)); // раскрывающий макрос
}

void loop() {
}
```

<a id="versions"></a>
## Версии
- v1.0

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!