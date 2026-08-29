# CigiSymbolShortControl Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>

**Inherits from:** CigiHostPacket


## CigiSymbolShortControl Class

### Перечисления

## CIGI_SYMBOL

| Name | Description |
|---|---|
| **CIGI_SYMBOL_NONE** = 0 | Attribute Select None в Short Symbol Control. |
| **CIGI_SYMBOL_SURFACE_ID** = 1 | Attribute Select ID в Short Symbol Control. |
| **CIGI_SYMBOL_PARENT_SYMBOL_ID** = 2 | Attribute Select Parent Symbol ID в Short Symbol Control. |
| **CIGI_SYMBOL_LAYER** = 3 | Attribute Select Layer в Short Symbol Control. |
| **CIGI_SYMBOL_FLASH_DUTY** = 4 | Attribute Select Flash Duty в Short Symbol Control. |
| **CIGI_SYMBOL_FLASH_PERIOD** = 5 | Attribute Select Flash Period в Short Symbol Control. |
| **CIGI_SYMBOL_POSITION_X** = 6 | Attribute Select Position X (U) в Short Symbol Control. |
| **CIGI_SYMBOL_POSITION_Y** = 7 | Attribute Select Position Y (V) в Short Symbol Control. |
| **CIGI_SYMBOL_ROTATION** = 8 | Attribute Select Rotation в Short Symbol Control. |
| **CIGI_SYMBOL_COLOR** = 9 | Attribute Select Color в Short Symbol Control. |
| **CIGI_SYMBOL_SCALE_X** = 10 | Attribute Select Scale X (U) в Short Symbol Control. |
| **CIGI_SYMBOL_SCALE_Y** = 11 | Attribute Select Scale Y (V) в Short Symbol Control. |

### Методы класса

---

## int getSymbolID ( ) const

Возвращает **Symbol ID**, указанный в пакете. Определяет символ, к которому применяется этот пакет.
### Возвращаемое значение

Значение параметра Symbol ID.
## int getSymbolState ( ) const

Возвращает **Symbol State**, указанный в пакете.
### Возвращаемое значение

Значение параметра Symbol State. Поддерживаются следующие значения:
- 0 - Скрыт.
- 1 - Видим.
- 2 - Уничтожен.


## int getAttachState ( ) const

Возвращает значение параметра **Attach State**, указанное в пакете. Определяет, будет ли символ присоединён как дочерний к родительскому символу.
### Возвращаемое значение

Значение параметра Attach State. 1 - символ присоединён как дочерний; иначе 0.
## int getFlashControl ( ) const

Возвращает значение параметра **Flash Control**, указанное в пакете. Определяет, должен ли IG продолжить цикл мигания символа с текущего состояния или перезапустить его с начала.
### Возвращаемое значение

Значение параметра Flash Control: 0, если Continue; иначе 1.
## int getInheritColor ( ) const

Возвращает значение параметра **Inherit Color**, указанное в пакете. Определяет, наследует ли этот символ свой цвет от символа, к которому он присоединён.
### Возвращаемое значение

Значение параметра **Inherit Color**: 1, если цвет наследуется; иначе 0.
## int getSelect1 ( ) const

Возвращает значение параметра **Attribute Select 1**, указанное в пакете. Идентифицирует атрибут, значение которого возвращается функцией [**getData1**](#getData1_uint).
### Возвращаемое значение

Значение параметра **Select 1**. Одно из значений [CIGI_SYMBOL_*](#CIGI_SYMBOL_NONE).
## int getSelect2 ( ) const

Возвращает значение параметра **Attribute Select 2**, указанное в пакете. Идентифицирует атрибут, значение которого возвращается функцией [**getData2**](#getData2_uint).
### Возвращаемое значение

Значение параметра **Select 2**. Одно из значений [CIGI_SYMBOL_*](#CIGI_SYMBOL_NONE).
## unsigned int getData1 ( ) const

Возвращает значение параметра **Attribute Value 1**, указанное в пакете. Определяет значение атрибута, идентифицированного функцией [**getAttribute1**](#getSelect1_int).
### Возвращаемое значение

Значение параметра **Data 1**.
## unsigned int getData2 ( ) const

Возвращает значение параметра **Attribute Value 2**, указанное в пакете. Определяет значение атрибута, идентифицированного функцией [**getAttribute2**](#getSelect2_int).
### Возвращаемое значение

Значение параметра **Data 2**.
