# Unigine::AnimationModifierFVec4 Class (CPP)

**Header:** #include <UnigineAnimation.h>

**Inherits from:** AnimationModifier


## AnimationModifierFVec4 Class

### Методы класса

## Math:: vec4 getDefaultValue () const

Возвращает текущее значение по умолчанию для всех элементов модификатора.
### Возвращаемое значение

Текущее значение по умолчанию для всех элементов модификатора.
## void setCurveX ( const Ptr < AnimationCurveFloat >& x )

Задаёт новую кривую, хранящую значения, используемые модификатором для оси X.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveFloat](../../../../api/library/animations/timeline/class.animationcurvefloat_cpp.md)>&* **x** - The curve storing the values used by the modifier for the X axis.

## Ptr < AnimationCurveFloat > getCurveX () const

Возвращает текущую кривую, хранящую значения, используемые модификатором для оси X.
### Возвращаемое значение

Текущая кривая, хранящая значения, используемые модификатором для оси X.
## void setCurveY ( const Ptr < AnimationCurveFloat >& y )

Задаёт новую кривую, хранящую значения, используемые модификатором для оси Y.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveFloat](../../../../api/library/animations/timeline/class.animationcurvefloat_cpp.md)>&* **y** - The curve storing the values used by the modifier for the Y axis.

## Ptr < AnimationCurveFloat > getCurveY () const

Возвращает текущую кривую, хранящую значения, используемые модификатором для оси Y.
### Возвращаемое значение

Текущая кривая, хранящая значения, используемые модификатором для оси Y.
## void setCurveZ ( const Ptr < AnimationCurveFloat >& z )

Задаёт новую кривую, хранящую значения, используемые модификатором для оси Z.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveFloat](../../../../api/library/animations/timeline/class.animationcurvefloat_cpp.md)>&* **z** - The curve storing the values used by the modifier for the Z axis.

## Ptr < AnimationCurveFloat > getCurveZ () const

Возвращает текущую кривую, хранящую значения, используемые модификатором для оси Z.
### Возвращаемое значение

Текущая кривая, хранящая значения, используемые модификатором для оси Z.
## void setCurveW ( const Ptr < AnimationCurveFloat >& w )

Задаёт новую кривую, хранящую значения, используемые модификатором для оси W.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveFloat](../../../../api/library/animations/timeline/class.animationcurvefloat_cpp.md)>&* **w** - The curve storing the values used by the modifier for the W axis.

## Ptr < AnimationCurveFloat > getCurveW () const

Возвращает текущую кривую, хранящую значения, используемые модификатором для оси W.
### Возвращаемое значение

Текущая кривая, хранящая значения, используемые модификатором для оси W.
## bool isUniformTime () const

Возвращает текущее значение, показывающее, изменяются ли значения модификатора равномерно вдоль временной шкалы.
### Возвращаемое значение

**true** if value showing if the modifier values are changed uniformly along the timeline. is enabled; otherwise **false**.
---

## AnimationModifierFVec4 ( AnimParams::PARAM param )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *AnimParams::PARAM* **param** - Параметр, анимируемый модификатором.

## AnimationModifierFVec4 ( AnimParams::PARAM param , int param_index )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *AnimParams::PARAM* **param** - Параметр, анимируемый модификатором.
- *int* **param_index** - Индекс параметра.

## AnimationModifierFVec4 ( AnimParams::PARAM param , const char * param_name )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *AnimParams::PARAM* **param** - Параметр, анимируемый модификатором.
- *const char ** **param_name** - Имя параметра.

## AnimationModifierFVec4 ( const char * param )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *const char ** **param** - Параметр, анимируемый модификатором.

## AnimationModifierFVec4 ( const char * param , int param_index )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *const char ** **param** - Параметр, анимируемый модификатором.
- *int* **param_index** - Индекс параметра.

## AnimationModifierFVec4 ( const char * param , const char * param_name )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *const char ** **param** - Параметр, анимируемый модификатором.
- *const char ** **param_name** - Имя параметра.

## void copy ( const Ptr < AnimationModifierFVec4 > & modifier )

Копирует все данные из указанного исходного модификатора анимации.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationModifierFVec4](../../../../api/library/animations/timeline/class.animationmodifierfvec4_cpp.md)> &* **modifier** - Исходный модификатор анимации.

## Math:: vec4 getValueByTime ( float time )

Возвращает значение модификатора в указанный момент времени.
### Аргументы

- *float* **time** - Время ключа на временной шкале, в секундах.

### Возвращаемое значение

Значение модификатора в указанный момент времени.
## Math:: vec4 getValueByNormalizedTime ( float normalized_time )

Возвращает нормализованное значение модификатора в указанный момент времени.
### Аргументы

- *float* **normalized_time** - Нормализованное значение времени.

### Возвращаемое значение

Значение модификатора в указанный момент времени.
## void addValue ( float time , const Math:: vec4 & value , AnimationCurve::KEY_TYPE type = Enum.AnimationCurve.KEY_TYPE.LINEAR )

Добавляет значение в модификатор в указанный момент времени.
### Аргументы

- *float* **time** - Время ключа на временной шкале, в секундах.
- *const  Math::[vec4](../../../../api/library/math/class.vec4_cpp.md) &* **value** - Значение модификатора в указанный момент времени.
- *[AnimationCurve::KEY_TYPE](../../../../api/library/animations/timeline/class.animationcurve_cpp.md#KEY_TYPE)* **type** - Тип интерполяции, заданный для ключа, одно из значений [KEY_TYPE_*](../../../../api/library/animations/timeline/class.animationcurve_cpp.md#KEY_TYPE_CONSTANT).

## void updateUniformTime ( bool enabled , bool force_update = false )

Changes the value that defines if the modifier values are changed uniformly along the timeline. Enabling the uniform time allows avoiding such cases as speeding up or slowing down due to the curve shape.
### Аргументы

- *bool* **enabled** - The current value.
- *bool* **force_update** - The target value.
