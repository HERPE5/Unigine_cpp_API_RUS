# Unigine.VRHand Class (CPP)

**Header:** #include <UnigineVRHandTracking.h>


## VRHand Class

### Перечисления

## TYPE

| Name | Description |
|---|---|
| **TYPE_LEFT** = 0 | Левая рука. |
| **TYPE_RIGHT** = 1 | Правая рука. |
| **NUM_TYPES** = 2 | Общее количество типов рук. |

### Методы класса

## VRHand::TYPE getType () const

Возвращает текущий тип руки: левая или правая.
### Возвращаемое значение

Текущий тип руки: левая или правая.
## Ptr < VRBone > getRootBone () const

Возвращает текущую корневую кость руки - соответствующую кость [wrist](../../../api/library/vr/class.vrbone_cpp.md#TYPE_WRIST).
### Возвращаемое значение

Текущая корневая кость руки - соответствующая кость [wrist](../../../api/library/vr/class.vrbone_cpp.md#TYPE_WRIST).
## bool isHoldingController () const

Возвращает текущее значение, указывающее, удерживается ли контроллер в руке. Не поддерживается на Varjo.
### Возвращаемое значение

**true**, если контроллер удерживается в руке; иначе **false**.
## bool isTracking () const

Возвращает текущее значение, указывающее, активен ли контроллер.
### Возвращаемое значение

**true**, если контроллер активен; иначе **false**.
---

## Ptr < VRBone > getBone ( VRBone::TYPE type )

Возвращает кость указанного типа для текущей руки.
### Аргументы

- *[VRBone::TYPE](../../../api/library/vr/class.vrbone_cpp.md#TYPE)* **type** - Тип кости руки, одно из значений [VRBone::TYPE](../../../api/library/vr/class.vrbone_cpp.md#TYPE_PALM).

### Возвращаемое значение

Кость указанного типа.
## void renderVisualizer ( ) const

Рендерит визуализатор.
