# Unigine::AnimationModifierQuat Class (CPP)

**Header:** #include <UnigineAnimation.h>

**Inherits from:** AnimationModifier


## AnimationModifierQuat Class

### Перечисления

## MODE

| Name | Description |
|---|---|
| **MODE_QUAT** = 0 | Значение поворота получается из *AnimationCurveQuat*. |
| **MODE_ANGLES_XYZ** = 1 | Для каждого угла используются три кривые *AnimationCurveFloat*, их данные используются для составления кватерниона с порядком координат {X, Y, Z}. |
| **MODE_ANGLES_ZYX** = 2 | Для каждого угла используются три кривые *AnimationCurveFloat*, их данные используются для составления кватерниона с порядком координат {Z, Y, X}. |

### Методы класса

## AnimationModifierQuat::MODE getMode () const

Возвращает текущий режим получения данных о повороте.
### Возвращаемое значение

Текущий режим получения данных о повороте.
## Math:: quat getDefaultValue () const

Возвращает текущее значение по умолчанию для всех элементов модификатора.
### Возвращаемое значение

Текущее значение по умолчанию для всех элементов модификатора.
## void setQuatCurve ( const Ptr < AnimationCurveQuat >& curve )

Задаёт новую кривую, хранящую значения, используемые модификатором.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveQuat](../../../../api/library/animations/timeline/class.animationcurvequat_cpp.md)>&* **curve** - Кривая, хранящая значения, используемые модификатором.

## Ptr < AnimationCurveQuat > getQuatCurve () const

Возвращает текущую кривую, хранящую значения, используемые модификатором.
### Возвращаемое значение

Текущая кривая, хранящая значения, используемые модификатором.
## void setCurveX ( const Ptr < AnimationCurveFloat >& x )

Задаёт новую кривую, хранящую значения, используемые модификатором для оси X.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveFloat](../../../../api/library/animations/timeline/class.animationcurvefloat_cpp.md)>&* **x** - Кривая, хранящая значения, используемые модификатором для оси X.

## Ptr < AnimationCurveFloat > getCurveX () const

Возвращает текущую кривую, хранящую значения, используемые модификатором для оси X.
### Возвращаемое значение

Текущая кривая, хранящая значения, используемые модификатором для оси X.
## void setCurveY ( const Ptr < AnimationCurveFloat >& y )

Задаёт новую кривую, хранящую значения, используемые модификатором для оси Y.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveFloat](../../../../api/library/animations/timeline/class.animationcurvefloat_cpp.md)>&* **y** - Кривая, хранящая значения, используемые модификатором для оси Y.

## Ptr < AnimationCurveFloat > getCurveY () const

Возвращает текущую кривую, хранящую значения, используемые модификатором для оси Y.
### Возвращаемое значение

Текущая кривая, хранящая значения, используемые модификатором для оси Y.
## void setCurveZ ( const Ptr < AnimationCurveFloat >& z )

Задаёт новую кривую, хранящую значения, используемые модификатором для оси Z.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveFloat](../../../../api/library/animations/timeline/class.animationcurvefloat_cpp.md)>&* **z** - Кривая, хранящая значения, используемые модификатором для оси Z.

## Ptr < AnimationCurveFloat > getCurveZ () const

Возвращает текущую кривую, хранящую значения, используемые модификатором для оси Z.
### Возвращаемое значение

Текущая кривая, хранящая значения, используемые модификатором для оси Z.
## bool isUniformTime () const

Возвращает текущее значение, показывающее, изменяются ли значения модификатора равномерно вдоль временной шкалы.
### Возвращаемое значение

**true**, если значения модификатора изменяются равномерно вдоль временной шкалы; иначе **false**.
---

## AnimationModifierQuat ( AnimationModifierQuat::MODE mode , AnimParams::PARAM param )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *[AnimationModifierQuat::MODE](../../../../api/library/animations/timeline/class.animationmodifierquat_cpp.md#MODE)* **mode** - Режим получения данных о повороте.
- *AnimParams::PARAM* **param** - Параметр, анимируемый модификатором.

## AnimationModifierQuat ( AnimationModifierQuat::MODE mode , AnimParams::PARAM param , int param_index )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *[AnimationModifierQuat::MODE](../../../../api/library/animations/timeline/class.animationmodifierquat_cpp.md#MODE)* **mode** - Режим получения данных о повороте.
- *AnimParams::PARAM* **param** - Параметр, анимируемый модификатором.
- *int* **param_index** - Индекс параметра.

## AnimationModifierQuat ( AnimationModifierQuat::MODE mode , AnimParams::PARAM param , const char * param_name )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *[AnimationModifierQuat::MODE](../../../../api/library/animations/timeline/class.animationmodifierquat_cpp.md#MODE)* **mode** - Режим получения данных о повороте.
- *AnimParams::PARAM* **param** - Параметр, анимируемый модификатором.
- *const char ** **param_name** - Имя параметра.

## AnimationModifierQuat ( AnimationModifierQuat::MODE mode , const char * param )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *[AnimationModifierQuat::MODE](../../../../api/library/animations/timeline/class.animationmodifierquat_cpp.md#MODE)* **mode** - Режим получения данных о повороте.
- *const char ** **param** - Параметр, анимируемый модификатором.

## AnimationModifierQuat ( AnimationModifierQuat::MODE mode , const char * param , int param_index )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *[AnimationModifierQuat::MODE](../../../../api/library/animations/timeline/class.animationmodifierquat_cpp.md#MODE)* **mode** - Режим получения данных о повороте.
- *const char ** **param** - Параметр, анимируемый модификатором.
- *int* **param_index** - Индекс параметра.

## AnimationModifierQuat ( AnimationModifierQuat::MODE mode , const char * param , const char * param_name )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *[AnimationModifierQuat::MODE](../../../../api/library/animations/timeline/class.animationmodifierquat_cpp.md#MODE)* **mode** - Режим получения данных о повороте.
- *const char ** **param** - Параметр, анимируемый модификатором.
- *const char ** **param_name** - Имя параметра.

## void copy ( const Ptr < AnimationModifierQuat > & modifier )

Копирует все данные из указанного исходного модификатора анимации.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationModifierQuat](../../../../api/library/animations/timeline/class.animationmodifierquat_cpp.md)> &* **modifier** - Исходный модификатор анимации.

## Math:: quat getValueByTime ( float time )

Возвращает значение модификатора в указанный момент времени.
### Аргументы

- *float* **time** - Время ключа на временной шкале, в секундах.

### Возвращаемое значение

Значение модификатора в указанный момент времени.
## Math:: quat getValueByNormalizedTime ( float normalized_time )

Возвращает нормализованное значение модификатора в указанный момент времени.
### Аргументы

- *float* **normalized_time** - Нормализованное значение времени.

### Возвращаемое значение

Значение модификатора в указанный момент времени.
## void addQuatValue ( float time , const Math:: quat & value )

Добавляет значение кватерниона в модификатор в указанный момент времени.
### Аргументы

- *float* **time** - Время ключа на временной шкале, в секундах.
- *const  Math::[quat](../../../../api/library/math/class.quat_cpp.md) &* **value** - Значение модификатора в указанный момент времени.

## void addAnglesValue ( float time , const Math:: vec3 & value , AnimationCurve::KEY_TYPE type = Enum.AnimationCurve.KEY_TYPE.LINEAR )

Добавляет значение углов в модификатор в указанный момент времени.
### Аргументы

- *float* **time** - Время ключа на временной шкале, в секундах.
- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **value** - Значение модификатора в указанный момент времени.
- *[AnimationCurve::KEY_TYPE](../../../../api/library/animations/timeline/class.animationcurve_cpp.md#KEY_TYPE)* **type** - Тип интерполяции, заданный для ключа, одно из значений [KEY_TYPE_*](../../../../api/library/animations/timeline/class.animationcurve_cpp.md#KEY_TYPE_CONSTANT).

## void updateUniformTime ( bool enabled , bool force_update = false )

Изменяет значение, определяющее, изменяются ли значения модификатора равномерно вдоль временной шкалы. Включение равномерного времени позволяет избежать таких случаев, как ускорение или замедление из-за формы кривой.
### Аргументы

- *bool* **enabled** - Текущее значение.
- *bool* **force_update** - Целевое значение.
