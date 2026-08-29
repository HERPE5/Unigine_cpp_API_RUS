# Unigine::AnimationObjectNode Class (CPP)

**Header:** #include <UnigineAnimation.h>

**Inherits from:** AnimationObject


Этот класс позволяет управлять прокси-[animation objects](../../../../principles/animations/index.md#animation_object), используемыми для анимирования узлов. Привязка к конкретному узлу в рамках конкретного [playback](../../../../principles/animations/index.md#animation_playback) выполняется через экземпляр класса *[AnimationBindNode](../../../../api/library/animations/timeline/class.animationbindnode_cpp.md)*.


## AnimationObjectNode Class

### Методы класса

## void setBind ( const Ptr < AnimationBindNode >& bind )

Задаёт новую привязку этого прокси-объекта к конкретному анимируемому узлу.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationBindNode](../../../../api/library/animations/timeline/class.animationbindnode_cpp.md)>&* **bind** - Привязка к конкретному анимируемому узлу.

## Ptr < AnimationBindNode > getBind () const

Возвращает текущую привязку этого прокси-объекта к конкретному анимируемому узлу.
### Возвращаемое значение

Текущая привязка к конкретному анимируемому узлу.
---

## AnimationObjectNode ( const char * name )

Конструктор. Создаёт новый объект анимации узла с указанным именем.
### Аргументы

- *const char ** **name** - Имя объекта анимации узла.

## void setPlaybackOverriddenBind ( const Ptr < AnimationPlayback > & playback , const Ptr < AnimationBindNode > & bind )

Задаёт новую привязку объекта анимации к конкретному узлу для указанного [playback](../../../../principles/animations/index.md#animation_playback) (переопределение привязки).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationPlayback](../../../../api/library/animations/timeline/class.animationplayback_cpp.md)> &* **playback** - Воспроизведение анимации, для которого добавляется новая привязка объекта анимации.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationBindNode](../../../../api/library/animations/timeline/class.animationbindnode_cpp.md)> &* **bind** - Привязка к конкретному анимируемому узлу.

## Ptr < AnimationBindNode > getPlaybackOverriddenBind ( const Ptr < AnimationPlayback > & playback )

Возвращает текущую привязку объекта анимации к конкретному узлу для указанного [playback](../../../../principles/animations/index.md#animation_playback) (переопределение привязки).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationPlayback](../../../../api/library/animations/timeline/class.animationplayback_cpp.md)> &* **playback** - Воспроизведение анимации, для которого запрашивается привязка узла объекта анимации.

### Возвращаемое значение

Переопределённая привязка к конкретному анимируемому узлу.
