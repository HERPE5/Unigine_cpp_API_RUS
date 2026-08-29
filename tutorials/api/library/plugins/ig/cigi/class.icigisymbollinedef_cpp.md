# CigiSymbolLineDef Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>

**Inherits from:** CigiHostPacket


## CigiSymbolLineDef Class

### Перечисления

## CIGI_LINE

| Name | Description |
|---|---|
| **CIGI_LINE_POINT** = 0 | Тип примитива: точка. |
| **CIGI_LINE_LINE** = 1 | Тип примитива: линия. |
| **CIGI_LINE_LINE_STRIP** = 2 | Тип примитива: полоса линий (Line Strip). |
| **CIGI_LINE_LINE_LOOP** = 3 | Тип примитива: замкнутая линия (Line Loop). |
| **CIGI_LINE_TRIANGLE** = 4 | Тип примитива: треугольник. |
| **CIGI_LINE_TRIANGLE_STRIP** = 5 | Тип примитива: полоса треугольников (Triangle Strip). |
| **CIGI_LINE_TRIANGLE_FAN** = 6 | Тип примитива: веер треугольников (Triangle Fan). |

### Методы класса

---

## int getSymbolID ( ) const

Возвращает Symbol ID, указанный в пакете.
### Возвращаемое значение

Symbol ID.
## int getPrimitiveType ( ) const

Возвращает **Primitive Type**, указанный в пакете. Определяет тип точечного или линейного примитива, заданного этим пакетом.
### Возвращаемое значение

Значение параметра Primitive Type. Одно из значений [CIGI_LINE_*](#CIGI_LINE_POINT).
## int getStipplePattern ( ) const

Возвращает значение параметра **Stipple Pattern**, указанное в пакете. Определяет узор штриховой линии, используемый при отрисовке линии.
### Возвращаемое значение

Значение параметра Stipple Pattern.
> **Notice:** Если значение этого параметра равно 0xFFFF, IG рисует сплошную линию. Если значение равно 0x00, IG не рисует линию.


## float getPatternLength ( ) const

Возвращает значение параметра **Stipple Pattern Length**, указанное в пакете. Определяет длину одного полного повторения узора штриховой линии.
### Возвращаемое значение

Значение параметра Pattern Length.
## float getLineWidth ( ) const

Возвращает значение параметра **Line Width**, указанное в пакете. Определяет толщину линии, используемую IG при отрисовке примитивов, заданных в этом пакете.
### Возвращаемое значение

Значение параметра Line Width.
## int getNumVertex ( ) const

Возвращает количество вершин линии. Определяет количество вершин, которыми задаётся линия
### Возвращаемое значение

**Num Vertex**.
## Math:: vec3 getVertex ( int num ) const

Возвращает трёхкомпонентный вектор UV-координат указанной вершины. Этот вектор объединяет значения параметров **Center U** и **Center V**, указанных в пакете.
### Аргументы

- *int* **num** - Индекс вершины.

### Возвращаемое значение

Трёхкомпонентный вектор с UV-координатами указанной вершины **(Center U, Center V, Z)**, в локальной системе координат символа.
> **Notice:** Третий компонент вектора игнорируется.
