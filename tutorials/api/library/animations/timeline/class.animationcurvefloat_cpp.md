# Unigine::AnimationCurveFloat Class (CPP)

**Header:** #include <UnigineAnimation.h>

**Inherits from:** AnimationCurve


Этот класс представляет собой интерфейс, позволяющий создавать кривые анимации, содержащие значения типа float, и управлять ими.


## AnimationCurveFloat Class

### Методы класса

## float getDefaultKeyValue () const

Возвращает текущее значение по умолчанию для всех ключей на кривой.
### Возвращаемое значение

Текущее значение по умолчанию для всех ключей на кривой.
## getNumKeys () const

Возвращает текущее общее число ключевых точек на кривой.
### Возвращаемое значение

Текущее общее число ключевых точек на кривой.
## getMinTime () const

Возвращает текущую точку общей временной шкалы анимации, начиная с которой применяется эта кривая, в единицах измерения.
### Возвращаемое значение

Текущая точка общей временной шкалы анимации, начиная с которой применяется эта кривая, в единицах измерения.
## getMaxTime () const

Возвращает текущую точку общей временной шкалы анимации, до которой применяется эта кривая, в единицах измерения.
### Возвращаемое значение

Текущая точка общей временной шкалы анимации, до которой применяется эта кривая, в единицах измерения.
---

## AnimationCurveFloat ( )

Конструктор. Создаёт новый экземпляр кривой анимации, содержащей значения типа float.
## void copy ( const Ptr < AnimationCurveFloat > & curve )

Копирует все данные (ключевые точки и касательные) из указанной исходной кривой.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveFloat](../../../../api/library/animations/timeline/class.animationcurvefloat_cpp.md)> &* **curve** - Исходная кривая.

## int addKey ( float time , float value )

Добавляет на кривую новую ключевую точку с указанным значением в указанной точке временной шкалы.
### Аргументы

- *float* **time** - Время ключа на временной шкале, в секундах.
- *float* **value** - Значение ключа типа float.

### Возвращаемое значение

Индекс добавленной ключевой точки.
## int addKey ( float time , float value , AnimationCurve::KEY_TYPE type )

Добавляет на кривую новую ключевую точку с указанным значением и типом в указанной точке временной шкалы.
### Аргументы

- *float* **time** - Время ключа на временной шкале, в секундах.
- *float* **value** - Значение ключа типа float.
- *[AnimationCurve::KEY_TYPE](../../../../api/library/animations/timeline/class.animationcurve_cpp.md#KEY_TYPE)* **type** - Тип интерполяции, заданный для ключа, одно из значений [KEY_TYPE_*](../../../../api/library/animations/timeline/class.animationcurve_cpp.md#KEY_TYPE_CONSTANT) values.

### Возвращаемое значение

Индекс добавленной ключевой точки.
## int addKey ( float time , float value , AnimationCurve::KEY_TYPE type , const Math:: vec2 & left_tangent , const Math:: vec2 & right_tangent )

Добавляет на кривую новую ключевую точку с указанным значением, типом и касательными в указанной точке временной шкалы.
### Аргументы

- *float* **time** - Время ключа на временной шкале, в секундах.
- *float* **value** - Значение ключа типа float.
- *[AnimationCurve::KEY_TYPE](../../../../api/library/animations/timeline/class.animationcurve_cpp.md#KEY_TYPE)* **type** - Тип интерполяции, заданный для ключа, одно из значений [KEY_TYPE_*](../../../../api/library/animations/timeline/class.animationcurve_cpp.md#KEY_TYPE_CONSTANT) values.
- *const  Math::[vec2](../../../../api/library/math/class.vec2_cpp.md) &* **left_tangent** - Координаты левой касательной в ключевой точке.
- *const  Math::[vec2](../../../../api/library/math/class.vec2_cpp.md) &* **right_tangent** - Координаты правой касательной в ключевой точке.

### Возвращаемое значение

Индекс добавленной ключевой точки.
## void removeKey ( int index )

Удаляет с кривой ключевую точку с указанным индексом.
### Аргументы

- *int* **index** - Номер ключевой точки в диапазоне от 0 до [total number of key points](#getNumKeys_int) на кривой.

## int moveKey ( int index , float new_time )

Перемещает ключевую точку с указанным номером в новую позицию по времени (с сохранением касательных). Индекс ключевой точки обновляется автоматически. Этот метод можно использовать для реализации перетаскивания ключей на кривой.
### Аргументы

- *int* **index** - Номер ключевой точки в диапазоне от 0 до [total number of key points](#getNumKeys_int) на кривой.
- *float* **new_time** - Время ключа на временной шкале, в секундах.

### Возвращаемое значение

Новый индекс ключа.
## void setKeyType ( int index , AnimationCurve::KEY_TYPE type )

Устанавливает тип интерполяции для указанного ключа на кривой.
### Аргументы

- *int* **index** - Номер ключевой точки в диапазоне от 0 до [total number of key points](#getNumKeys_int) на кривой.
- *[AnimationCurve::KEY_TYPE](../../../../api/library/animations/timeline/class.animationcurve_cpp.md#KEY_TYPE)* **type** - Тип интерполяции, заданный для ключа, одно из значений [KEY_TYPE_*](../../../../api/library/animations/timeline/class.animationcurve_cpp.md#KEY_TYPE_CONSTANT) values.

## AnimationCurve::KEY_TYPE getKeyType ( int index ) const

Возвращает тип интерполяции указанного ключа на кривой.
### Аргументы

- *int* **index** - Номер ключевой точки в диапазоне от 0 до [total number of key points](#getNumKeys_int) на кривой.

### Возвращаемое значение

Тип интерполяции, заданный для ключа, одно из значений [KEY_TYPE_*](../../../../api/library/animations/timeline/class.animationcurve_cpp.md#KEY_TYPE_CONSTANT) values.
## float getKeyTime ( int index ) const

Возвращает текущее время ключевой точки с указанным индексом.
### Аргументы

- *int* **index** - Номер ключевой точки в диапазоне от 0 до [total number of key points](#getNumKeys_int) на кривой.

### Возвращаемое значение

Время указанной ключевой точки на временной шкале, в секундах.
## void setKeyValue ( int index , float value )

Устанавливает значение для указанного ключа на кривой.
### Аргументы

- *int* **index** - Номер ключевой точки в диапазоне от 0 до [total number of key points](#getNumKeys_int) на кривой.
- *float* **value** - Значение ключа типа float.

## float getKeyValue ( int index ) const

Возвращает текущее значение указанного ключа на кривой.
### Аргументы

- *int* **index** - Номер ключевой точки в диапазоне от 0 до [total number of key points](#getNumKeys_int) на кривой.

### Возвращаемое значение

Значение ключа типа float.
## void setKeyLeftTangent ( int index , const Math:: vec2 & left_tangent )

Устанавливает новые координаты левой касательной в указанной ключевой точке кривой.
### Аргументы

- *int* **index** - Номер ключевой точки в диапазоне от 0 до [total number of key points](#getNumKeys_int) на кривой.
- *const  Math::[vec2](../../../../api/library/math/class.vec2_cpp.md) &* **left_tangent** - Координаты левой касательной в указанной ключевой точке.

## Math:: vec2 getKeyLeftTangent ( int index ) const

Возвращает текущие координаты левой касательной в указанной ключевой точке кривой.
### Аргументы

- *int* **index** - Номер ключевой точки в диапазоне от 0 до [total number of key points](#getNumKeys_int) на кривой.

### Возвращаемое значение

Координаты левой касательной в указанной ключевой точке.
## void setKeyRightTangent ( int index , const Math:: vec2 & right_tangent )

Устанавливает новые координаты правой касательной в указанной ключевой точке кривой.
### Аргументы

- *int* **index** - Номер ключевой точки в диапазоне от 0 до [total number of key points](#getNumKeys_int) на кривой.
- *const  Math::[vec2](../../../../api/library/math/class.vec2_cpp.md) &* **right_tangent** - Координаты правой касательной в указанной ключевой точке.

## Math:: vec2 getKeyRightTangent ( int index ) const

Возвращает текущие координаты правой касательной в указанной ключевой точке кривой.
### Аргументы

- *int* **index** - Номер ключевой точки в диапазоне от 0 до [total number of key points](#getNumKeys_int) на кривой.

### Возвращаемое значение

Координаты правой касательной в указанной ключевой точке.
## void setTypeOfAllKeys ( AnimationCurve::KEY_TYPE type )

Устанавливает тип интерполяции для всех ключей кривой.
### Аргументы

- *[AnimationCurve::KEY_TYPE](../../../../api/library/animations/timeline/class.animationcurve_cpp.md#KEY_TYPE)* **type** - Тип интерполяции, заданный для ключа, одно из значений [KEY_TYPE_*](../../../../api/library/animations/timeline/class.animationcurve_cpp.md#KEY_TYPE_CONSTANT) values.

## void clear ( )

Очищает кривую, удаляя все ключевые точки и касательные.
## float getValueByTime ( float time )

Возвращает значение ключа в указанной точке кривой.
### Аргументы

- *float* **time** - Время ключа на временной шкале, в секундах.

### Возвращаемое значение

Значение ключа типа float.
## float getValueByNormalizedTime ( float normalized_time )

Возвращает значение ключа с использованием нормализованного значения времени ключа.
### Аргументы

- *float* **normalized_time** - Нормализованное значение времени ключа.

### Возвращаемое значение

Значение ключа типа float.
## void save ( const Ptr < Blob > & blob ) const

Сохраняет данные кривой в blob.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Blob](../../../../api/library/common/class.blob_cpp.md)> &* **blob** - Blob, в который будут сохранены данные кривой.

## void load ( const Ptr < Blob > & blob )

Загружает данные кривой из blob.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Blob](../../../../api/library/common/class.blob_cpp.md)> &* **blob** - Blob, содержащий данные кривой.
