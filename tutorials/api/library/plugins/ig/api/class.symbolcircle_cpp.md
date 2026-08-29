# Unigine::Plugins::IG::SymbolCircle Class (CPP)

**Header:** #include <plugins/Unigine/IG/UnigineIG.h>


## SymbolCircle Class

### Методы класса

---

## void setFill ( bool value )

Включает или отключает заливку символа круга.
### Аргументы

- *bool* **value** - true, чтобы сделать символ круга залитым, иначе false.

## void setCenter ( float x , float y )

Задаёт центр символа круга относительно плоскости в [plane's UV coordinates](../../../../../api/library/plugins/ig/api/class.symbolsplane_cpp.md#setUVSize_float_float_float_float_void).
### Аргументы

- *float* **x** - Горизонтальное смещение от опорной точки плоскости в UV-координатах.
- *float* **y** - Вертикальное смещение от опорной точки плоскости в UV-координатах.

## void setRadius ( float value )

Задаёт радиус символа круга в [plane's UV coordinates](../../../../../api/library/plugins/ig/api/class.symbolsplane_cpp.md#setUVSize_float_float_float_float_void).
### Аргументы

- *float* **value** - Радиус круга в UV-координатах.

## void setInnerRadius ( float value )

Задаёт внутренний радиус символа круга в [plane's UV coordinates](../../../../../api/library/plugins/ig/api/class.symbolsplane_cpp.md#setUVSize_float_float_float_float_void).
### Аргументы

- *float* **value** - Внутренний радиус круга в UV-координатах.

## void setSector ( float start_angle , float end_angle )

Создаёт сектор круга (дугу), задавая два угла, определяющих его границы.
### Аргументы

- *float* **start_angle** - Начальный угол сектора.
- *float* **end_angle** - Конечный угол сектора.
