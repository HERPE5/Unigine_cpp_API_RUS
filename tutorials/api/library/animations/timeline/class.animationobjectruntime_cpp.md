# Unigine::AnimationObjectRuntime Class (CPP)

**Header:** #include <UnigineAnimation.h>

**Inherits from:** AnimationObject


Этот класс позволяет управлять прокси-[animation objects](../../../../principles/animations/index.md#animation_object), используемыми для анимирования runtime-объектов. Привязка к конкретному runtime-объекту в рамках конкретного [playback](../../../../principles/animations/index.md#animation_playback) выполняется через экземпляр класса *[AnimationBindRuntime](../../../../api/library/animations/timeline/class.animationbindruntime_cpp.md)*.


## AnimationObjectRuntime Class

### Методы класса

## void setBind ( const Ptr < AnimationBindRuntime >& bind )

Задаёт новую привязку этого прокси-объекта к конкретному анимируемому runtime-объекту.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationBindRuntime](../../../../api/library/animations/timeline/class.animationbindruntime_cpp.md)>&* **bind** - Привязка к конкретному анимируемому runtime-объекту.

## Ptr < AnimationBindRuntime > getBind () const

Возвращает текущую привязку этого прокси-объекта к конкретному анимируемому runtime-объекту.
### Возвращаемое значение

Текущая привязка к конкретному анимируемому runtime-объекту.
---

## AnimationObjectRuntime ( const char * name )

Конструктор. Создаёт новый объект анимации runtime-объекта с указанным именем.
### Аргументы

- *const char ** **name** - Имя объекта анимации параметра свойства.

## void setPlaybackOverriddenBind ( const Ptr < AnimationPlayback > & playback , const Ptr < AnimationBindRuntime > & bind )

Задаёт новую привязку объекта анимации к конкретному runtime-объекту для указанного [playback](../../../../principles/animations/index.md#animation_playback) (переопределение привязки).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationPlayback](../../../../api/library/animations/timeline/class.animationplayback_cpp.md)> &* **playback** - Воспроизведение анимации, для которого добавляется новая привязка объекта анимации.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationBindRuntime](../../../../api/library/animations/timeline/class.animationbindruntime_cpp.md)> &* **bind** - Привязка к конкретному анимируемому runtime-объекту.

## Ptr < AnimationBindRuntime > getPlaybackOverriddenBind ( const Ptr < AnimationPlayback > & playback )

Возвращает текущую привязку объекта анимации к конкретному runtime-объекту для указанного [playback](../../../../principles/animations/index.md#animation_playback) (переопределение привязки).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationPlayback](../../../../api/library/animations/timeline/class.animationplayback_cpp.md)> &* **playback** - Воспроизведение анимации, для которого запрашивается привязка runtime-объекта объекта анимации.

### Возвращаемое значение

Переопределённая привязка к конкретному анимируемому runtime-объекту.
