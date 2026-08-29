# Unigine::UlonArg Class (CPP)

**Header:** #include <UnigineUlon.h>


Этот класс используется для представления аргумента [ULON](../../../code/formats/ulon_format.md) — пары *имя - значение*. Аргументы — это дополнительные параметры, которые могут быть связаны с узлами и использоваться для различных целей (например, для определения всплывающей подсказки или заголовка для объявления параметра материала). Аргументы заключаются в угловые скобки < > и могут разделяться символами "\t","\n","\r", а также запятыми и пробелами.


**Пример:** Node node = value <**arg0** = *value0* **arg1** = *value1*,**arg2** = *value2*>


## UlonArg Class

### Методы класса

## String getName () const

Возвращает текущее имя аргумента ULON.
### Возвращаемое значение

Текущее имя аргумента ULON.
## Ptr < UlonValue > getValue () const

Возвращает текущее [value](../../../api/library/common/class.ulonvalue_cpp.md) аргумента ULON.
### Возвращаемое значение

Текущее [value](../../../api/library/common/class.ulonvalue_cpp.md) аргумента ULON.
---

## static UlonArgPtr create ( )

Конструктор. Создаёт аргумент ULON.
