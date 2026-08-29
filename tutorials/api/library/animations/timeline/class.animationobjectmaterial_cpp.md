# Unigine::AnimationObjectMaterial Class (CPP)

**Header:** #include <UnigineAnimation.h>

**Inherits from:** AnimationObject


Этот класс позволяет управлять прокси-[animation objects](../../../../principles/animations/index.md#animation_object), используемыми для анимирования материалов. Привязка к конкретному материалу в рамках конкретного [playback](../../../../principles/animations/index.md#animation_playback) выполняется через экземпляр класса *[AnimationBindMaterial](../../../../api/library/animations/timeline/class.animationbindmaterial_cpp.md)*.


## AnimationObjectMaterial Class

### Методы класса

## void setBind ( const Ptr < AnimationBindMaterial >& bind )

Задаёт новую привязку этого прокси-объекта к конкретному анимируемому материалу.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationBindMaterial](../../../../api/library/animations/timeline/class.animationbindmaterial_cpp.md)>&* **bind** - Привязка к конкретному анимируемому материалу.

## Ptr < AnimationBindMaterial > getBind () const

Возвращает текущую привязку этого прокси-объекта к конкретному анимируемому материалу.
### Возвращаемое значение

Текущая привязка к конкретному анимируемому материалу.
---

## AnimationObjectMaterial ( const char * name )

Конструктор. Создаёт новый объект анимации материала с указанным именем.
### Аргументы

- *const char ** **name** - Имя объекта анимации материала.

## void setPlaybackOverriddenBind ( const Ptr < AnimationPlayback > & playback , const Ptr < AnimationBindMaterial > & bind )

Задаёт новую привязку объекта анимации к конкретному материалу для указанного [playback](../../../../principles/animations/index.md#animation_playback) (переопределение привязки).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationPlayback](../../../../api/library/animations/timeline/class.animationplayback_cpp.md)> &* **playback** - Воспроизведение анимации, для которого добавляется новая привязка объекта анимации.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationBindMaterial](../../../../api/library/animations/timeline/class.animationbindmaterial_cpp.md)> &* **bind** - Привязка к конкретному анимируемому материалу.

## Ptr < AnimationBindMaterial > getPlaybackOverriddenBind ( const Ptr < AnimationPlayback > & playback )

Возвращает текущую привязку объекта анимации к конкретному материалу для указанного [playback](../../../../principles/animations/index.md#animation_playback) (переопределение привязки).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationPlayback](../../../../api/library/animations/timeline/class.animationplayback_cpp.md)> &* **playback** - Воспроизведение анимации, для которого запрашивается привязка материала объекта анимации.

### Возвращаемое значение

Переопределённая привязка к конкретному анимируемому материалу.
