# Unigine::Plugins::IG::SymbolsController Class (CPP)

**Header:** #include <plugins/Unigine/IG/UnigineIG.h>


Этот класс представляет интерфейс SymbolsController IG. Символ — это единичный примитив рисования или группа примитивов рисования, которые могут быть отрисованы на поверхности символов (плоскости) в рамках определённого [view](../../../../../api/library/plugins/ig/api/class.view_cpp.md), либо размещены в 3D-пространстве относительно определённой [entity](../../../../../api/library/plugins/ig/api/class.entity_cpp.md).


Доступны следующие типы символов: Polyline, Text, Circle.

> **Notice:** Плагин IG должен быть загружен.


## SymbolsController Class

### Перечисления

## SYMBOL_TYPE

| Name | Description |
|---|---|
| **SYMBOL_TYPE_POLYLINE** = 0 | Ломаная линия. |
| **SYMBOL_TYPE_TEXT** = 1 | Текст. |
| **SYMBOL_TYPE_CIRCLE** = 2 | Круг. |

### Методы класса

---

## Symbol * createSymbol ( SymbolsController::SYMBOL_TYPE type , int symbol_id )

Создаёт новый [symbol](../../../../../api/library/plugins/ig/api/class.symbol_cpp.md).
> **Notice:** Символ должен быть немедленно добавлен в SymbolsPlane.


### Аргументы

- *[SymbolsController::SYMBOL_TYPE](../../../../../api/library/plugins/ig/api/class.symbolscontroller_cpp.md#SYMBOL_TYPE)* **type** - Тип символа:

  - POLYLINE
  - TEXT
  - CIRCLE
- *int* **symbol_id** - ID символа.

### Возвращаемое значение

Указатель на интерфейс нового созданного символа.
## Symbol * cloneSymbol ( int symbol_id , int new_symbol_id )

Клонирует [symbol](../../../../../api/library/plugins/ig/api/class.symbol_cpp.md) с указанным ID.
### Аргументы

- *int* **symbol_id** - ID клонируемого символа.
- *int* **new_symbol_id** - ID нового символа.

### Возвращаемое значение

Указатель на интерфейс нового клонированного символа.
## SymbolsPlane * createPlane ( int plane_id , View * view )

Создаёт новую [symbols surface](../../../../../api/library/plugins/ig/api/class.symbolsplane_cpp.md) (виртуальную плоскость, на которой отрисовываются символы). Новая поверхность размещается в 3D-пространстве совпадающей с ближней плоскостью отсечения указанного [view](../../../../../api/library/plugins/ig/api/class.view_cpp.md).
### Аргументы

- *int* **plane_id** - ID символа.
- *[View](../../../../../api/library/plugins/ig/api/class.view_cpp.md) ** **view** - View, относительно которого размещается новая поверхность символов.

### Возвращаемое значение

Указатель на интерфейс новой созданной поверхности символов.
## SymbolsPlane * createPlane ( int plane_id , Entity * entity )

Создаёт новую [symbols surface](../../../../../api/library/plugins/ig/api/class.symbolsplane_cpp.md) (виртуальную плоскость, на которой отрисовываются символы). Новая поверхность размещается в 3D-пространстве относительно указанной [entity](../../../../../api/library/plugins/ig/api/class.entity_cpp.md).
### Аргументы

- *int* **plane_id** - ID символа.
- *[Entity](../../../../../api/library/plugins/ig/api/class.entity_cpp.md) ** **entity** - Сущность, относительно которой размещается новая поверхность символов.

### Возвращаемое значение

Указатель на интерфейс новой созданной поверхности символов.
## Symbol * getSymbol ( int symbol_id ) const

Возвращает [interface](../../../../../api/library/plugins/ig/api/class.symbol_cpp.md) указанного символа.
### Аргументы

- *int* **symbol_id** - ID символа.

### Возвращаемое значение

Указатель на интерфейс нового созданного символа.
## SymbolsPlane * getPlane ( int plane_id ) const

Возвращает [interface](../../../../../api/library/plugins/ig/api/class.symbolsplane_cpp.md) указанной поверхности символов (виртуальной плоскости, на которой отрисовываются символы).
### Аргументы

- *int* **plane_id** - ID поверхности символов.

### Возвращаемое значение

Указатель на интерфейс новой созданной поверхности символов.
## void removeSymbol ( int symbol_id )

Удаляет символ с указанным ID.
### Аргументы

- *int* **symbol_id** - ID удаляемого символа.

## void removePlane ( int plane_id )

Удаляет поверхность символов (плоскость) с указанным ID и все связанные с ней символы.
### Аргументы

- *int* **plane_id** - ID удаляемой поверхности символов (плоскости).

## void clear ( )

Удаляет все символы и плоскости.
