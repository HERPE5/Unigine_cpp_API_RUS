# Unigine::AnimationModifierTrack Class (CPP)

**Header:** #include <UnigineAnimation.h>

**Inherits from:** AnimationModifier


Этот класс представляет собой интерфейс, позволяющий использовать треки в анимации.


## AnimationModifierTrack Class

---

## AnimationModifierTrack ( )

Конструктор. Создаёт новый модификатор для анимирования объектов с помощью треков.
## void addTrack ( const char * path , float begin_time )

Добавляет трек в указанной точке временной шкалы.
### Аргументы

- *const char ** **path** - Путь к треку.
- *float* **begin_time** - Время на временной шкале, в секундах, начала этого трека.

## void setTrackTimeCurve ( const Ptr < AnimationCurveFloat > & curve )

Задаёт временную кривую, используемую треком.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveFloat](../../../../api/library/animations/timeline/class.animationcurvefloat_cpp.md)> &* **curve** - Временная кривая для трека.
