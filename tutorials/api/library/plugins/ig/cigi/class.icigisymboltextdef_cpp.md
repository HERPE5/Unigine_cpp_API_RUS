# CigiSymbolTextDef Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>

**Inherits from:** CigiHostPacket


## CigiSymbolTextDef Class

### Перечисления

## CIGI_TEXT_ALIGN

| Name | Description |
|---|---|
| **CIGI_TEXT_ALIGN_TOP_LEFT** = 0 | Выравнивание текста в верхнем левом углу. |
| **CIGI_TEXT_ALIGN_TOP_CENTER** = 1 | Выравнивание текста по верхнему центру. |
| **CIGI_TEXT_ALIGN_TOP_RIGHT** = 2 | Выравнивание текста в верхнем правом углу. |
| **CIGI_TEXT_ALIGN_CENTER_LEFT** = 3 | Выравнивание текста по среднему левому краю. |
| **CIGI_TEXT_ALIGN_CENTER** = 4 | Выравнивание текста по центру поля. |
| **CIGI_TEXT_ALIGN_CENTER_RIGHT** = 5 | Выравнивание текста по среднему правому краю. |
| **CIGI_TEXT_ALIGN_BOTTOM_LEFT** = 6 | Выравнивание текста в нижнем левом углу. |
| **CIGI_TEXT_ALIGN_BOTTOM_CENTER** = 7 | Выравнивание текста по нижнему центру. |
| **CIGI_TEXT_ALIGN_BOTTOM_RIGHT** = 8 | Выравнивание текста в нижнем правом углу. |

## CIGI_TEXT_ORIENT

| Name | Description |
|---|---|
| **CIGI_TEXT_ORIENT_LEFT_TO_RIGHT** = 0 | Ориентация текста слева направо. |
| **CIGI_TEXT_ORIENT_TOP_TO_BOTTOM** = 1 | Ориентация текста сверху вниз. |
| **CIGI_TEXT_ORIENT_RIGHT_TO_LEFT** = 2 | Ориентация текста справа налево. |
| **CIGI_TEXT_ORIENT_BOTTOM_TO_TOP** = 3 | Ориентация текста снизу вверх. |

### Методы класса

---

## int getSymbolID ( ) const

Возвращает Symbol ID, указанный в пакете.
### Возвращаемое значение

Symbol ID.
## int getFontID ( ) const

Возвращает значение параметра **Font ID**, указанное в пакете. Определяет шрифт, используемый для этого текстового символа.
### Возвращаемое значение

Значение параметра Font ID. Поддерживаются следующие значения:

- 0 - IG Default.

Пропорциональный:
- 1 - Sans Serif.
- 2 - **Sans Serif Bold**.
- 3 - *Sans Serif Italic*.
- 4 - ***Sans Serif Bold Italic***.
- 5 - Serif.
- 6 - **Serif Bold**.
- 7 - *Serif Italic*.
- 8 - ***Serif Bold Italic***.

Моноширинный:
- 9 - Sans Serif.
- 10 - **Sans Serif Bold**.
- 11 - *Sans Serif Italic*.
- 12 - ***Sans Serif Bold Italic***.
- 13 - Serif.
- 14 - **Serif Bold**.
- 15 - *Serif Italic*.
- 16 - ***Serif Bold Italic***.
- 17-255 - Определяется IG.


## int getAlignment ( ) const

Returns the value of the **Alignment** parameter specified in the packet. Specifies the position at which the IG shall place the symbol’s reference point in relation to the text.
### Возвращаемое значение

Значение параметра **Alignment**. Одно из значений [CIGI_TEXT_ALIGN_*](#CIGI_TEXT_ALIGN_TOP_LEFT).
## int getOrientation ( ) const

Возвращает значение параметра **Orientation**, указанное в пакете. Определяет ориентацию текста.
### Возвращаемое значение

Значение параметра **Orientation**. Одно из значений [CIGI_TEXT_ORIENT_*_TO_*](#CIGI_TEXT_ORIENT_LEFT_TO_RIGHT).
## float getFontSize ( ) const

Возвращает значение параметра **Font Size**, указанное в пакете. Определяет размер шрифта в вертикальных единицах, заданных 2D-системой координат поверхности символов.
### Возвращаемое значение

Значение параметра **Font Size**.
## const char * getText ( ) const

Возвращает значение параметра **Octet**, указанное в пакете.
### Возвращаемое значение

Значение параметра Octet.
> **Notice:** Максимальная длина строки, включая завершающий NULL, составляет 236 байт.
