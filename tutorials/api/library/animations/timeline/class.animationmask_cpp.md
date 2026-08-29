# Unigine::AnimationMask Class (CPP)

**Header:** #include <UnigineAnimation.h>


Этот класс позволяет управлять [animation masks](../../../../principles/animations/index.md#animation_mask). Маска — это набор [objects](../../../../principles/animations/index.md#animation_object) и модификаторов, обрабатываемых дорожкой.


## AnimationMask Class

### Методы класса

## bool isEmpty () const

Возвращает текущее значение, указывающее, пуста ли маска.
### Возвращаемое значение

**true**, если маска пуста; иначе **false**.
## getNumModifiers () const

Возвращает текущее количество модификаторов, принадлежащих маске.
### Возвращаемое значение

Текущее количество модификаторов, принадлежащих маске.
---

## AnimationMask ( )

Конструктор. Создаёт пустой *AnimationMask* с параметрами по умолчанию.
## void addInfo ( const Ptr < AnimationModifierInfo > & info )

Добавляет новое описание модификатора анимации в маску.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationModifierInfo](../../../../api/library/animations/timeline/class.animationmodifierinfo_cpp.md)> &* **info** - Описание модификатора анимации.

## void removeInfo ( const Ptr < AnimationModifierInfo > & info )

Удаляет указанное описание модификатора анимации из маски.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationModifierInfo](../../../../api/library/animations/timeline/class.animationmodifierinfo_cpp.md)> &* **info** - Описание удаляемого модификатора анимации.

## bool containsInfo ( const Ptr < AnimationModifierInfo > & info ) const

Возвращает значение, указывающее, содержит ли маска указанное описание модификатора анимации.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationModifierInfo](../../../../api/library/animations/timeline/class.animationmodifierinfo_cpp.md)> &* **info** - Описание проверяемого модификатора анимации.

### Возвращаемое значение

true, если маска содержит указанное описание модификатора анимации; иначе false.
## Ptr < AnimationModifierInfo > getInfoByIndex ( int index ) const

Возвращает описание [animation modifier](../../../../principles/animations/index.md#animation_modifier) с указанным индексом.
### Аргументы

- *int* **index** - Индекс описания модификатора анимации.

### Возвращаемое значение

Описание модификатора анимации с указанным индексом.
