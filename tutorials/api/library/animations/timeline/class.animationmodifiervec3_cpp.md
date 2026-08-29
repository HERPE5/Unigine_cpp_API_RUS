# Unigine::AnimationModifierVec3 Class (CPP)

**Header:** #include <UnigineAnimation.h>

**Inherits from:** AnimationModifier


## AnimationModifierVec3 Class

### Методы класса

## Math:: Vec3 getDefaultValue () const

Возвращает текущее значение по умолчанию для всех элементов модификатора.
### Возвращаемое значение

Текущее значение по умолчанию для всех элементов модификатора.
## void setCurveX ( const Ptr < AnimationCurveScalar >& x )

Задаёт новую кривую, хранящую значения, используемые модификатором для оси X.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveScalar](../../../../api/library/animations/timeline/class.animationcurvescalar_cpp.md)>&* **x** - Кривая, хранящая значения, используемые модификатором для оси X.

## Ptr < AnimationCurveScalar > getCurveX () const

Возвращает текущую кривую, хранящую значения, используемые модификатором для оси X.
### Возвращаемое значение

Текущая кривая, хранящая значения, используемые модификатором для оси X.
## void setCurveY ( const Ptr < AnimationCurveScalar >& y )

Задаёт новую кривую, хранящую значения, используемые модификатором для оси Y.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveScalar](../../../../api/library/animations/timeline/class.animationcurvescalar_cpp.md)>&* **y** - Кривая, хранящая значения, используемые модификатором для оси Y.

## Ptr < AnimationCurveScalar > getCurveY () const

Возвращает текущую кривую, хранящую значения, используемые модификатором для оси Y.
### Возвращаемое значение

Текущая кривая, хранящая значения, используемые модификатором для оси Y.
## void setCurveZ ( const Ptr < AnimationCurveScalar >& z )

Задаёт новую кривую, хранящую значения, используемые модификатором для оси Z.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveScalar](../../../../api/library/animations/timeline/class.animationcurvescalar_cpp.md)>&* **z** - Кривая, хранящая значения, используемые модификатором для оси Z.

## Ptr < AnimationCurveScalar > getCurveZ () const

Возвращает текущую кривую, хранящую значения, используемые модификатором для оси Z.
### Возвращаемое значение

Текущая кривая, хранящая значения, используемые модификатором для оси Z.
## bool isUniformTime () const

Возвращает текущее значение, показывающее, изменяются ли значения модификатора равномерно вдоль временной шкалы.
### Возвращаемое значение

**true**, если значения модификатора изменяются равномерно вдоль временной шкалы; иначе **false**.
---

## AnimationModifierVec3 ( AnimParams::PARAM param )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *AnimParams::PARAM* **param** - Параметр, анимируемый модификатором.

## AnimationModifierVec3 ( AnimParams::PARAM param , int param_index )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *AnimParams::PARAM* **param** - Параметр, анимируемый модификатором.
- *int* **param_index** - Индекс параметра.

## AnimationModifierVec3 ( AnimParams::PARAM param , const char * param_name )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *AnimParams::PARAM* **param** - Параметр, анимируемый модификатором.
- *const char ** **param_name** - Имя параметра.

## AnimationModifierVec3 ( const char * param )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *const char ** **param** - Параметр, анимируемый модификатором.

## AnimationModifierVec3 ( const char * param , int param_index )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *const char ** **param** - Параметр, анимируемый модификатором.
- *int* **param_index** - Индекс параметра.

## AnimationModifierVec3 ( const char * param , const char * param_name )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *const char ** **param** - Параметр, анимируемый модификатором.
- *const char ** **param_name** - Имя параметра.

## void copy ( const Ptr < AnimationModifierVec3 > & modifier )

Копирует все данные из указанного исходного модификатора анимации.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationModifierVec3](../../../../api/library/animations/timeline/class.animationmodifiervec3_cpp.md)> &* **modifier** - Исходный модификатор анимации.

## Math:: Vec3 getValueByTime ( float time )

Возвращает значение модификатора в указанный момент времени.
### Аргументы

- *float* **time** - Время ключа на временной шкале, в секундах.

### Возвращаемое значение

Значение модификатора в указанный момент времени.
## Math:: Vec3 getValueByNormalizedTime ( float normalized_time )

Возвращает нормализованное значение модификатора в указанный момент времени.
### Аргументы

- *float* **normalized_time** - Нормализованное значение времени.

### Возвращаемое значение

Значение модификатора в указанный момент времени.
## void addValue ( float time , const Math:: Vec3 & value , AnimationCurve::KEY_TYPE type = Enum.AnimationCurve.KEY_TYPE.LINEAR )

Добавляет значение в модификатор в указанный момент времени.
### Аргументы

- *float* **time** - Время ключа на временной шкале, в секундах.
- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **value** - Значение модификатора в указанный момент времени.
- *[AnimationCurve::KEY_TYPE](../../../../api/library/animations/timeline/class.animationcurve_cpp.md#KEY_TYPE)* **type** - Тип интерполяции, заданный для ключа, одно из значений [KEY_TYPE_*](../../../../api/library/animations/timeline/class.animationcurve_cpp.md#KEY_TYPE_CONSTANT).

## void updateUniformTime ( bool enabled , bool force_update = false )

Изменяет значение, определяющее, изменяются ли значения модификатора равномерно вдоль временной шкалы. Включение равномерного времени позволяет избежать таких случаев, как ускорение или замедление из-за формы кривой.
### Аргументы

- *bool* **enabled** - Текущее значение.
- *bool* **force_update** - Целевое значение.
