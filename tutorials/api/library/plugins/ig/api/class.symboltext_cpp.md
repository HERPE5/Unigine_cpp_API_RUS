# Unigine::Plugins::IG::SymbolText Class (CPP)

**Header:** #include <plugins/Unigine/IG/UnigineIG.h>


## SymbolText Class

### Перечисления

## Orientation

| Name | Description |
|---|---|
| **LEFT_TO_RIGHT** = 0 | Горизонтальная ориентация текста слева направо. |
| **RIGHT_TO_LEFT** = 2 | Горизонтальная ориентация текста справа налево. |
| **TOP_TO_BOTTOM** = 1 | Вертикальная ориентация текста сверху вниз. |
| **BOTTOM_TO_TOP** = 3 | Вертикальная ориентация текста снизу вверх. |

## AlignHorizontal

| Name | Description |
|---|---|
| **LEFT** = 0 | Выравнивание текста по левому краю. |
| **CENTER** = 1 | Выравнивание текста по центру. |
| **RIGHT** = 2 | Выравнивание текста по правому краю. |

## AlignVertical

| Name | Description |
|---|---|
| **TOP** = 0 | Выравнивание текста по верхнему краю. |
| **CENTER** = 1 | Выравнивание текста по центру. |
| **BOTTOM** = 2 | Выравнивание текста по нижнему краю. |

### Методы класса

---

## void setText ( const char * text )

Задаёт отображаемый текст.
### Аргументы

- *const char ** **text** - Отображаемый текст.

## void setFont ( const String & path )

Задаёт шрифт, хранящийся в указанном файле.
### Аргументы

- *const [String](../../../../../api/library/common/class.string_cpp.md) &* **path** - Путь к файлу шрифта.

## void setFontSize ( float font_size )

Задаёт размер шрифта.
### Аргументы

- *float* **font_size** - Размер шрифта.

## void setAlign ( SymbolText.AlignHorizontal align_horizontal , SymbolText.AlignVertical align_vertical )

Задаёт горизонтальное и вертикальное выравнивание отображаемого текста.
### Аргументы

- *[SymbolText.AlignHorizontal](../../../../../api/library/plugins/ig/api/class.symboltext_cpp.md#AlignHorizontal)* **align_horizontal** - Горизонтальное выравнивание текста.
- *[SymbolText.AlignVertical](../../../../../api/library/plugins/ig/api/class.symboltext_cpp.md#AlignVertical)* **align_vertical** - Вертикальное выравнивание текста.

## void setOrientation ( SymbolText.Orientation orientation )

Задаёт ориентацию отображаемого текста (горизонтальную: *слева направо / справа налево* или вертикальную: *снизу вверх / сверху вниз*).
### Аргументы

- *[SymbolText.Orientation](../../../../../api/library/plugins/ig/api/class.symboltext_cpp.md#Orientation)* **orientation** - Задаваемая ориентация текста.
