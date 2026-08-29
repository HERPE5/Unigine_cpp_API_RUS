# Unigine::AnimationBindRuntime Class (CPP)

**Header:** #include <UnigineAnimation.h>

**Inherits from:** AnimationBind


Этот класс используется для управления runtime-привязками [bindings](../../../../principles/animations/index.md#animation_binding) у [animation objects](../../../../principles/animations/index.md#animation_object) из кода. Объекты анимации служат прокси в последовательностях анимации и привязываются к конкретным объектам (материалам, узлам, параметрам свойств или runtime-объектам, таким как виджеты и окна) на этапе воспроизведения.


Привязки используются для хранения, поиска и получения реальных объектов движка, которые фактически анимируются. Runtime-объекты (такие как виджеты, окна и т.д.) не могут быть сохранены — они создаются и назначаются привязкам во время выполнения.


## AnimationBindRuntime Class

### Методы класса

## void setWidget ( const Ptr < Widget >& widget )

Устанавливает новый анимируемый виджет.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Widget](../../../../api/library/gui/class.widget_cpp.md)>&* **widget** - Анимируемый виджет.

## Ptr < Widget > getWidget () const

Возвращает текущий анимируемый виджет.
### Возвращаемое значение

Текущий анимируемый виджет.
---

## AnimationBindRuntime ( )

Конструктор. Создаёт пустую привязку runtime-объекта.
