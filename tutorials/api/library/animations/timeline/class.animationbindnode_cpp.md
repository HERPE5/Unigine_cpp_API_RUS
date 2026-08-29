# Unigine::AnimationBindNode Class (CPP)

**Header:** #include <UnigineAnimation.h>

**Inherits from:** AnimationBind


Этот класс используется для управления привязками узлов [bindings](../../../../principles/animations/index.md#animation_binding) у [animation objects](../../../../principles/animations/index.md#animation_object) из кода. Объекты анимации служат прокси в последовательностях анимации и привязываются к конкретным объектам (материалам, узлам, параметрам свойств или runtime-объектам, таким как виджеты и окна) на этапе воспроизведения.


Привязки используются для хранения, поиска и получения реальных объектов движка, которые фактически анимируются.


## AnimationBindNode Class

### Методы класса

## void setNode ( const Ptr < Node >& node )

Устанавливает новый анимируемый узел.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)>&* **node** - Анимируемый узел.

## Ptr < Node > getNode () const

Возвращает текущий анимируемый узел.
### Возвращаемое значение

Текущий анимируемый узел.
## getNodeDescriptionID () const

Возвращает текущий ID анимируемого узла.
### Возвращаемое значение

Текущий ID узла.
## const char * getNodeDescriptionName () const

Возвращает текущее имя анимируемого узла.
### Возвращаемое значение

Текущее имя узла.
---

## AnimationBindNode ( )

Конструктор. Создаёт пустую привязку узла.
## void setNodeDescription ( int id , const char * name )

Устанавливает компоненты описания анимируемого узла.
### Аргументы

- *int* **id** - ID анимируемого узла.
- *const char ** **name** - имя анимируемого узла.
