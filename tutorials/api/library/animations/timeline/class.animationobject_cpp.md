# Unigine::AnimationObject Class (CPP)

**Header:** #include <UnigineAnimation.h>


Этот класс используется для управления [animation objects](../../../../principles/animations/index.md#animation_object) из кода.


## AnimationObject Class

### Перечисления

## TYPE

Тип объекта анимации.
| Name | Description |
|---|---|
| **ANIMATION_OBJECT** = 0 | Обобщённый объект анимации. |
| **ANIMATION_OBJECT_NODE** = 1 | Объект анимации, используемый для анимирования узла (см. класс *[AnimationObjectNode](../../../../api/library/animations/timeline/class.animationobjectnode_cpp.md)*). |
| **ANIMATION_OBJECT_MATERIAL** = 2 | Объект анимации, используемый для анимирования материала (см. класс *[AnimationObjectMaterial](../../../../api/library/animations/timeline/class.animationobjectmaterial_cpp.md)*). |
| **ANIMATION_OBJECT_PROPERTY_PARAMETER** = 3 | Объект анимации, используемый для анимирования параметра свойства (см. класс *[AnimationObjectPropertyParameter](../../../../api/library/animations/timeline/class.animationobjectpropertyparameter_cpp.md)*). |
| **ANIMATION_OBJECT_RUNTIME** = 4 | Объект анимации, используемый для анимирования runtime-объекта (см. класс *[AnimationObjectRuntime](../../../../api/library/animations/timeline/class.animationobjectruntime_cpp.md)*). |
| **ANIMATION_OBJECT_TRACK** = 5 | Объект анимации, используемый для анимирования трека анимации (см. класс *[AnimationObjectTrack](../../../../api/library/animations/timeline/class.animationobjecttrack_cpp.md)*). |

### Методы класса

## AnimationObject::TYPE getType () const

Возвращает текущий тип объекта анимации.
### Возвращаемое значение

Текущий тип объекта анимации.
## const char * getTypeName () const

Возвращает текущее имя типа объекта анимации.
### Возвращаемое значение

Текущее имя типа объекта анимации.
## getID () const

Возвращает текущий идентификатор объекта анимации.
### Возвращаемое значение

Текущий идентификатор объекта анимации.
## void setName ( const char * name )

Задаёт новое имя объекта анимации.
### Аргументы

- *const char ** **name** - Имя объекта анимации.

## const char * getName () const

Возвращает текущее имя объекта анимации.
### Возвращаемое значение

Текущее имя объекта анимации.
