# Unigine::AnimationModifierMat4 Class (CPP)

**Header:** #include <UnigineAnimation.h>

**Inherits from:** AnimationModifier


## AnimationModifierMat4 Class

### Перечисления

## FOLLOW_MODE

| Name | Description |
|---|---|
| **FOLLOW_MODE_NONE** = 0 | Изменяемый объект вращается с использованием результата интерполяции между ключами. |
| **FOLLOW_MODE_X** = 1 | Ось X изменяемого объекта следует за кривой преобразования. |
| **FOLLOW_MODE_Y** = 2 | Ось Y изменяемого объекта следует за кривой преобразования. |
| **FOLLOW_MODE_Z** = 3 | Ось Z изменяемого объекта следует за кривой преобразования. |

### Методы класса

## void setFollowMode ( )

Задаёт новый режим преобразования для изменяемого объекта.
### Аргументы

- **mode** - Режим преобразования для изменяемого объекта.

## getFollowMode () const

Возвращает текущий режим преобразования для изменяемого объекта.
### Возвращаемое значение

Текущий режим преобразования для изменяемого объекта.
## void setFollowPositionOffset ( )

Задаёт новое смещение позиции вдоль оси следования.
### Аргументы

- **offset** - Смещение позиции вдоль оси следования.

## getFollowPositionOffset () const

Возвращает текущее смещение позиции вдоль оси следования.
### Возвращаемое значение

Текущее смещение позиции вдоль оси следования.
## bool isUniformTime () const

Возвращает текущее значение, показывающее, изменяются ли значения модификатора равномерно вдоль временной шкалы.
### Возвращаемое значение

**true**, если значение, показывающее, изменяются ли значения модификатора равномерно вдоль временной шкалы, включено; иначе **false**.
---

## AnimationModifierMat4 ( AnimParams::PARAM param )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *AnimParams::PARAM* **param** - Параметр, анимируемый модификатором.

## AnimationModifierMat4 ( AnimParams::PARAM param , int param_index )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *AnimParams::PARAM* **param** - Параметр, анимируемый модификатором.
- *int* **param_index** - Индекс параметра.

## AnimationModifierMat4 ( AnimParams::PARAM param , const char * param_name )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *AnimParams::PARAM* **param** - Параметр, анимируемый модификатором.
- *const char ** **param_name** - Имя параметра.

## AnimationModifierMat4 ( const char * param )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *const char ** **param** - Параметр, анимируемый модификатором.

## AnimationModifierMat4 ( const char * param , int param_index )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *const char ** **param** - Параметр, анимируемый модификатором.
- *int* **param_index** - Индекс параметра.

## AnimationModifierMat4 ( const char * param , const char * param_name )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *const char ** **param** - Параметр, анимируемый модификатором.
- *const char ** **param_name** - Имя параметра.

## void copy ( const Ptr < AnimationModifierMat4 > & modifier )

Копирует все данные из указанного исходного модификатора анимации.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationModifierMat4](../../../../api/library/animations/timeline/class.animationmodifiermat4_cpp.md)> &* **modifier** - Исходный модификатор анимации.

## void addValue ( float time , const Math:: Mat4 & value )

Добавляет значение в модификатор в указанный момент времени.
### Аргументы

- *float* **time** - Время ключа на временной шкале, в секундах.
- *const  Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **value** - Значение модификатора в указанный момент времени.

## void updateUniformTime ( bool enabled , bool force_update = false )

Изменяет значение, определяющее, изменяются ли значения модификатора равномерно вдоль временной шкалы. Включение равномерного времени позволяет избежать таких эффектов, как ускорение или замедление из-за формы кривой.
### Аргументы

- *bool* **enabled** - Текущее значение.
- *bool* **force_update** - Целевое значение.
