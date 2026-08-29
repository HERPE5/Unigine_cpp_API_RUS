# Unigine::AnimationObjectPropertyParameter Class (CPP)

**Header:** #include <UnigineAnimation.h>

**Inherits from:** AnimationObject


Этот класс позволяет управлять прокси-[animation objects](../../../../principles/animations/index.md#animation_object), используемыми для анимирования параметров свойств. Привязка к конкретному параметру свойства в рамках конкретного [playback](../../../../principles/animations/index.md#animation_playback) выполняется через экземпляр класса *[AnimationBindPropertyParameter](../../../../api/library/animations/timeline/class.animationbindpropertyparameter_cpp.md)*.


## AnimationObjectPropertyParameter Class

### Методы класса

## void setBind ( const Ptr < AnimationBindPropertyParameter >& bind )

Задаёт новую привязку этого прокси-объекта к конкретному анимируемому параметру свойства.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationBindPropertyParameter](../../../../api/library/animations/timeline/class.animationbindpropertyparameter_cpp.md)>&* **bind** - Привязка к конкретному анимируемому параметру свойства.

## Ptr < AnimationBindPropertyParameter > getBind () const

Возвращает текущую привязку этого прокси-объекта к конкретному анимируемому параметру свойства.
### Возвращаемое значение

Текущая привязка к конкретному анимируемому параметру свойства.
---

## AnimationObjectPropertyParameter ( const char * name )

Конструктор. Создаёт новый объект анимации параметра свойства с указанным именем.
### Аргументы

- *const char ** **name** - Имя объекта анимации параметра свойства.

## void setPlaybackOverriddenBind ( const Ptr < AnimationPlayback > & playback , const Ptr < AnimationBindPropertyParameter > & bind )

Задаёт новую привязку объекта анимации к конкретному параметру свойства для указанного [playback](../../../../principles/animations/index.md#animation_playback) (переопределение привязки).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationPlayback](../../../../api/library/animations/timeline/class.animationplayback_cpp.md)> &* **playback** - Воспроизведение анимации, для которого добавляется новая привязка объекта анимации.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationBindPropertyParameter](../../../../api/library/animations/timeline/class.animationbindpropertyparameter_cpp.md)> &* **bind** - Привязка к конкретному анимируемому параметру свойства.

## Ptr < AnimationBindPropertyParameter > getPlaybackOverriddenBind ( const Ptr < AnimationPlayback > & playback )

Возвращает текущую привязку объекта анимации к конкретному параметру свойства для указанного [playback](../../../../principles/animations/index.md#animation_playback) (переопределение привязки).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationPlayback](../../../../api/library/animations/timeline/class.animationplayback_cpp.md)> &* **playback** - Воспроизведение анимации, для которого запрашивается привязка параметра свойства объекта анимации.

### Возвращаемое значение

Переопределённая привязка к конкретному анимируемому параметру свойства.
