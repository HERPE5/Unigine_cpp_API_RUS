# Unigine::AnimationModifierDVec3 Class (CPP)

**Header:** #include <UnigineAnimation.h>

**Inherits from:** AnimationModifier


## AnimationModifierDVec3 Class

### Методы класса

## Math:: dvec3 getDefaultValue () const

Возвращает текущее значение по умолчанию для всех элементов модификатора.
### Возвращаемое значение

Текущее значение по умолчанию для всех элементов модификатора.
## void setCurveX ( const Ptr < AnimationCurveDouble >& x )

Задаёт новую кривую, хранящую значения, используемые модификатором для оси X.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveDouble](../../../../api/library/animations/timeline/class.animationcurvedouble_cpp.md)>&* **x** - The curve storing the values used by the modifier for the X axis.

## Ptr < AnimationCurveDouble > getCurveX () const

Возвращает текущую кривую, хранящую значения, используемые модификатором для оси X.
### Возвращаемое значение

Текущая кривая, хранящая значения, используемые модификатором для оси X.
## void setCurveY ( const Ptr < AnimationCurveDouble >& y )

Задаёт новую кривую, хранящую значения, используемые модификатором для оси Y.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveDouble](../../../../api/library/animations/timeline/class.animationcurvedouble_cpp.md)>&* **y** - The curve storing the values used by the modifier for the Y axis.

## Ptr < AnimationCurveDouble > getCurveY () const

Возвращает текущую кривую, хранящую значения, используемые модификатором для оси Y.
### Возвращаемое значение

Текущая кривая, хранящая значения, используемые модификатором для оси Y.
## void setCurveZ ( const Ptr < AnimationCurveDouble >& z )

Задаёт новую кривую, хранящую значения, используемые модификатором для оси Z.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveDouble](../../../../api/library/animations/timeline/class.animationcurvedouble_cpp.md)>&* **z** - The curve storing the values used by the modifier for the Z axis.

## Ptr < AnimationCurveDouble > getCurveZ () const

Возвращает текущую кривую, хранящую значения, используемые модификатором для оси Z.
### Возвращаемое значение

Текущая кривая, хранящая значения, используемые модификатором для оси Z.
## bool isUniformTime () const

Возвращает текущее значение, показывающее, изменяются ли значения модификатора равномерно вдоль временной шкалы.
### Возвращаемое значение

**true** if value showing if the modifier values are changed uniformly along the timeline. is enabled; otherwise **false**.
---

## AnimationModifierDVec3 ( AnimParams::PARAM param )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *AnimParams::PARAM* **param** - Параметр, анимируемый модификатором.

## AnimationModifierDVec3 ( AnimParams::PARAM param , int param_index )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *AnimParams::PARAM* **param** - Параметр, анимируемый модификатором.
- *int* **param_index** - Индекс параметра.

## AnimationModifierDVec3 ( AnimParams::PARAM param , const char * param_name )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *AnimParams::PARAM* **param** - Параметр, анимируемый модификатором.
- *const char ** **param_name** - Имя параметра.

## AnimationModifierDVec3 ( const char * param )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *const char ** **param** - Параметр, анимируемый модификатором.

## AnimationModifierDVec3 ( const char * param , int param_index )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *const char ** **param** - Параметр, анимируемый модификатором.
- *int* **param_index** - Индекс параметра.

## AnimationModifierDVec3 ( const char * param , const char * param_name )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *const char ** **param** - Параметр, анимируемый модификатором.
- *const char ** **param_name** - Имя параметра.

## void copy ( const Ptr < AnimationModifierDVec3 > & modifier )

Копирует все данные из указанного исходного модификатора анимации.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationModifierDVec3](../../../../api/library/animations/timeline/class.animationmodifierdvec3_cpp.md)> &* **modifier** - Исходный модификатор анимации.

## Math:: dvec3 getValueByTime ( float time )

Возвращает значение модификатора в указанный момент времени.
### Аргументы

- *float* **time** - Время ключа на временной шкале, в секундах.

### Возвращаемое значение

Значение модификатора в указанный момент времени.
## Math:: dvec3 getValueByNormalizedTime ( float normalized_time )

Возвращает нормализованное значение модификатора в указанный момент времени.
### Аргументы

- *float* **normalized_time** - Нормализованное значение времени.

### Возвращаемое значение

Значение модификатора в указанный момент времени.
## void addValue ( float time , const Math:: dvec3 & value , AnimationCurve::KEY_TYPE type = Enum.AnimationCurve.KEY_TYPE.LINEAR )

Добавляет значение в модификатор в указанный момент времени.
### Аргументы

- *float* **time** - Время ключа на временной шкале, в секундах.
- *const  Math::[dvec3](../../../../api/library/math/class.dvec3_cpp.md) &* **value** - Значение модификатора в указанный момент времени.
- *[AnimationCurve::KEY_TYPE](../../../../api/library/animations/timeline/class.animationcurve_cpp.md#KEY_TYPE)* **type** - Тип интерполяции, заданный для ключа, одно из значений [KEY_TYPE_*](../../../../api/library/animations/timeline/class.animationcurve_cpp.md#KEY_TYPE_CONSTANT).

## void updateUniformTime ( bool enabled , bool force_update = false )

Changes the value that defines if the modifier values are changed uniformly along the timeline. Enabling the uniform time allows avoiding such cases as speeding up or slowing down due to the curve shape.
### Аргументы

- *bool* **enabled** - The current value.
- *bool* **force_update** - The target value.
