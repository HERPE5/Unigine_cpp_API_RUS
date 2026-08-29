# Unigine::AnimationModifierUGUID Class (CPP)

**Header:** #include <UnigineAnimation.h>

**Inherits from:** AnimationModifier


## AnimationModifierUGUID Class

### Методы класса

## UGUID getDefaultValue () const

Возвращает текущее значение по умолчанию для всех элементов модификатора.
### Возвращаемое значение

Текущее значение по умолчанию для всех элементов модификатора.
## void setCurve ( const Ptr < AnimationCurveUGUID >& curve )

Задаёт новую кривую, хранящую значения, используемые модификатором.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveUGUID](../../../../api/library/animations/timeline/class.animationcurveuguid_cpp.md)>&* **curve** - Кривая, хранящая значения, используемые модификатором.

## Ptr < AnimationCurveUGUID > getCurve () const

Возвращает текущую кривую, хранящую значения, используемые модификатором.
### Возвращаемое значение

Текущая кривая, хранящая значения, используемые модификатором.
---

## AnimationModifierUGUID ( AnimParams::PARAM param )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *AnimParams::PARAM* **param** - Параметр, анимируемый модификатором.

## AnimationModifierUGUID ( AnimParams::PARAM param , int param_index )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *AnimParams::PARAM* **param** - Параметр, анимируемый модификатором.
- *int* **param_index** - Индекс параметра.

## AnimationModifierUGUID ( AnimParams::PARAM param , const char * param_name )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *AnimParams::PARAM* **param** - Параметр, анимируемый модификатором.
- *const char ** **param_name** - Имя параметра.

## AnimationModifierUGUID ( const char * param )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *const char ** **param** - Параметр, анимируемый модификатором.

## AnimationModifierUGUID ( const char * param , int param_index )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *const char ** **param** - Параметр, анимируемый модификатором.
- *int* **param_index** - Индекс параметра.

## AnimationModifierUGUID ( const char * param , const char * param_name )

Создаёт модификатор анимации для анимирования указанного параметра.
### Аргументы

- *const char ** **param** - Параметр, анимируемый модификатором.
- *const char ** **param_name** - Имя параметра.

## void copy ( const Ptr < AnimationModifierUGUID > & modifier )

Копирует все данные из указанного исходного модификатора анимации.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationModifierUGUID](../../../../api/library/animations/timeline/class.animationmodifieruguid_cpp.md)> &* **modifier** - Исходный модификатор анимации.

## UGUID getValueByTime ( float time )

Возвращает значение модификатора в указанный момент времени.
### Аргументы

- *float* **time** - Время ключа на временной шкале, в секундах.

### Возвращаемое значение

Значение модификатора в указанный момент времени.
## UGUID getValueByNormalizedTime ( float normalized_time )

Возвращает нормализованное значение модификатора в указанный момент времени.
### Аргументы

- *float* **normalized_time** - Нормализованное значение времени.

### Возвращаемое значение

Значение модификатора в указанный момент времени.
## void addValue ( float time , const UGUID & value )

Добавляет значение в модификатор в указанный момент времени.
### Аргументы

- *float* **time** - Время ключа на временной шкале, в секундах.
- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **value** - Значение модификатора в указанный момент времени.
