[![latest](https://img.shields.io/github/v/release/GyverLibs/fixed.svg?color=brightgreen)](https://github.com/GyverLibs/fixed/releases/latest/download/fixed.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/fixed.svg)](https://registry.platformio.org/libraries/gyverlibs/fixed)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/fixed?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# fixed
Реализация 32-бит типа с фиксированной точкой для Arduino
- Размер дробной части (точность) на выбор
- Перегружены все операторы для удобства
- Все методы сделаны `constexpr`
- Литеральные суффиксы для цифр в программе
- Вычисления в 1.5 раза быстрее float
- Поддержка всех операций занимает на 1.5 кБ меньше float

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

## Содержание
- [Использование](#usage)
- [Пример](#example)
- [Версии](#versions)
- [Установка](#install)
- [Баги и обратная связь](#feedback)

<a id="usage"></a>

## Использование
Тип `fixed` можно просто использовать как тип данных вместо `float`.

### Класс
```cpp
fixed(любой тип);

int32_t getRaw();
int32_t toInt();
float toFloat();
```

### Точность
По умолчанию `fixed` имеет 16 бит под целое и 16 бит под дробное, но есть варианты:

|                       | Точность, бит | Точность, мин. | Целая часть, +-макс. |
|-----------------------|---------------|----------------|----------------------|
| `fixedT<дробных_бит>` | На выбор      | `1 / 2^бит`    | `2^(31 - бит)`       |
| `fixed8`              | 8             | `0.0039`       | `8'388'608`          |
| `fixed16`             | 16            | `0.000015`     | `32'768`             |
| `fixed24`             | 24            | `0.00000006`   | `128`                |

### Литералы
В программе можно добавлять к числам литералы, например `3.14_fx8` это число `3.14` сразу в формате `fixed8`, т.е. аналог вызова `fixed8(3.14)`, а `123_fx16` - в формате `fixed16`.

<a id="example"></a>

## Пример
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
}

void loop() {
}
```

<a id="versions"></a>

## Версии
- v1.0
- v2.0 - библиотека переписана, улучшена, добавлены операторы и constexpt

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
### Обновление
- Рекомендую всегда обновлять библиотеку: в новых версиях исправляются ошибки и баги, а также проводится оптимизация и добавляются новые фичи
- Через менеджер библиотек IDE: найти библиотеку как при установке и нажать "Обновить"
- Вручную: **удалить папку со старой версией**, а затем положить на её место новую. "Замену" делать нельзя: иногда в новых версиях удаляются файлы, которые останутся при замене и могут привести к ошибкам!

<a id="feedback"></a>

## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!


При сообщении о багах или некорректной работе библиотеки нужно обязательно указывать:
- Версия библиотеки
- Какой используется МК
- Версия SDK (для ESP)
- Версия Arduino IDE
- Корректно ли работают ли встроенные примеры, в которых используются функции и конструкции, приводящие к багу в вашем коде
- Какой код загружался, какая работа от него ожидалась и как он работает в реальности
- В идеале приложить минимальный код, в котором наблюдается баг. Не полотно из тысячи строк, а минимальный код