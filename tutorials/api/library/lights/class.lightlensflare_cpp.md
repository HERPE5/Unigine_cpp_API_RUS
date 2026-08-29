# Unigine.LightLensFlare Class (CPP)

**Header:** #include <UnigineLights.h>


Этот класс используется для управления билбордами, используемыми для эффекта бликов от источника света.

> **Notice:** Эффект бликов должен быть [enabled](../../../api/library/lights/class.light_cpp.md#setLensFlaresEnabled_int_void) для источника света. Эта возможность доступна только для: [Omni Lights](../../../api/library/lights/class.lightomni_cpp.md), [Projected Lights](../../../api/library/lights/class.lightproj_cpp.md) и [World Lights](../../../api/library/lights/class.lightworld_cpp.md).


### См. также


Описание [lens flare settings](../../../objects/lights/parameters/index.md#lens_flares_settings).


## LightLensFlare Class

### Методы класса

## void setIntensity ( float intensity )

Задаёт новую интенсивность билборда блика.
### Аргументы

- *float* **intensity** - Интенсивность билборда блика. [color](#setColor_vec4_void) билборда умножается на это значение. Чем выше значение, тем ярче будет блик.

## float getIntensity () const

Возвращает текущую интенсивность билборда блика.
### Возвращаемое значение

Текущая интенсивность билборда блика. [color](#setColor_vec4_void) билборда умножается на это значение. Чем выше значение, тем ярче будет блик.
## void setColor ( const Math:: vec4 & color )

Задаёт новый цвет билборда блика.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md)&* **color** - Цвет билборда.

## Math:: vec4 getColor () const

Возвращает текущий цвет билборда блика.
### Возвращаемое значение

Текущий цвет билборда.
## void setRotate ( bool rotate = false )

Задаёт новое значение, указывающее, включено ли вращение билборда блика. При включении верх билборда всегда будет обращён к центру экрана.
### Аргументы

- *bool* **rotate** - Значение **true** включает вращение билборда блика; **false** - отключает его.

## bool isRotate () const

Возвращает текущее значение, указывающее, включено ли вращение билборда блика. При включении верх билборда всегда будет обращён к центру экрана.
### Возвращаемое значение

**true**, если вращение билборда блика включено; иначе **false**.
## void setUVUpperRight ( const Math:: vec2 & right )

Задаёт новые UV-координаты [texture](../../../api/library/lights/class.light_cpp.md#setLensFlaresTextureName_cstr_void) верхнего правого угла билборда блика.
### Аргументы

- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md)&* **right** - UV-координаты [texture](../../../api/library/lights/class.light_cpp.md#setLensFlaresTextureName_cstr_void) верхнего правого угла билборда блика.

## Math:: vec2 getUVUpperRight () const

Возвращает текущие UV-координаты [texture](../../../api/library/lights/class.light_cpp.md#setLensFlaresTextureName_cstr_void) верхнего правого угла билборда блика.
### Возвращаемое значение

Текущие UV-координаты [texture](../../../api/library/lights/class.light_cpp.md#setLensFlaresTextureName_cstr_void) верхнего правого угла билборда блика.
## void setUVLowerLeft ( const Math:: vec2 & left )

Задаёт новые UV-координаты [texture](../../../api/library/lights/class.light_cpp.md#setLensFlaresTextureName_cstr_void) нижнего левого угла билборда блика.
### Аргументы

- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md)&* **left** - UV-координаты [texture](../../../api/library/lights/class.light_cpp.md#setLensFlaresTextureName_cstr_void) нижнего левого угла билборда блика.

## Math:: vec2 getUVLowerLeft () const

Возвращает текущие UV-координаты [texture](../../../api/library/lights/class.light_cpp.md#setLensFlaresTextureName_cstr_void) нижнего левого угла билборда блика.
### Возвращаемое значение

Текущие UV-координаты [texture](../../../api/library/lights/class.light_cpp.md#setLensFlaresTextureName_cstr_void) нижнего левого угла билборда блика.
## void setOffsetScale ( float scale )

Задаёт новый коэффициент масштабирования билборда блика, зависящий от [offset](#setOffset_float_void).
### Аргументы

- *float* **scale** - Коэффициент масштабирования. По мере увеличения [offset](#setOffset_float_void) от источника света:

  - значения **меньше** 1.0f уменьшают билборд.
  - значения **больше** 1.0f увеличивают билборд.

## float getOffsetScale () const

Возвращает текущий коэффициент масштабирования билборда блика, зависящий от [offset](#setOffset_float_void).
### Возвращаемое значение

Текущий коэффициент масштабирования. По мере увеличения [offset](#setOffset_float_void) от источника света:
- значения **меньше** 1.0f уменьшают билборд.
- значения **больше** 1.0f увеличивают билборд.


## void setOffset ( float offset )

Задаёт новое значение смещения для билборда блика. Это смещение от источника света вдоль направления луча света.
### Аргументы

- *float* **offset** - Значение смещения билборда. Чем ниже абсолютное значение, тем ближе билборд к источнику света. Отрицательные значения означают, что расстояние измеряется в противоположном направлении.

## float getOffset () const

Возвращает текущее значение смещения для билборда блика. Это смещение от источника света вдоль направления луча света.
### Возвращаемое значение

Текущее значение смещения билборда. Чем ниже абсолютное значение, тем ближе билборд к источнику света. Отрицательные значения означают, что расстояние измеряется в противоположном направлении.
## void setSize ( float size )

Задаёт новый размер билборда блика.
### Аргументы

- *float* **size** - Размер билборда блика.

## float getSize () const

Возвращает текущий размер билборда блика.
### Возвращаемое значение

Текущий размер билборда блика.
## void setName ( const char * name )

Задаёт новое имя билборда блика.
### Аргументы

- *const char ** **name** - Имя билборда блика.

## const char * getName () const

Возвращает текущее имя билборда блика.
### Возвращаемое значение

Текущее имя билборда блика.
