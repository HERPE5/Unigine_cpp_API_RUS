# Unigine::AnimationPlayback Class (CPP)

**Header:** #include <UnigineAnimation.h>


Этот класс используется для управления [animation playbacks](../../../../principles/animations/index.md#animation_playback) из кода.


## AnimationPlayback Class

### Методы класса

## getNumObjects () const

Возвращает текущее общее количество [animation objects](../../../../principles/animations/index.md#animation_object), управляемых во всех [tracks](../../../../principles/animations/index.md#animation_track) воспроизведения.
### Возвращаемое значение

Текущее количество объектов анимации, управляемых во всех треках воспроизведения.
## bool isPlaying () const

Возвращает текущее значение, указывающее, воспроизводится ли в данный момент это воспроизведение.
### Возвращаемое значение

**true**, если воспроизведение в данный момент проигрывается; иначе **false**.
## bool isStopped () const

Возвращает текущее значение, указывающее, остановлено ли в данный момент это воспроизведение.
### Возвращаемое значение

**true**, если воспроизведение в данный момент остановлено; иначе **false**.
## getDuration () const

Возвращает текущую общую длительность воспроизведения, в секундах.
### Возвращаемое значение

Текущая длительность воспроизведения, в секундах.
## void setTimeTo ( float to )

Задаёт новое время окончания воспроизведения, в секундах.
### Аргументы

- *float* **to** - Время окончания воспроизведения, в секундах.

## float getTimeTo () const

Возвращает текущее время окончания воспроизведения, в секундах.
### Возвращаемое значение

Текущее время окончания воспроизведения, в секундах.
## void setTimeFrom ( float from )

Задаёт новое время начала воспроизведения, в секундах.
### Аргументы

- *float* **from** - Время начала воспроизведения, в секундах.

## float getTimeFrom () const

Возвращает текущее время начала воспроизведения, в секундах.
### Возвращаемое значение

Текущее время начала воспроизведения, в секундах.
## void setSpeed ( )

Задаёт новый коэффициент скорости для воспроизведения анимации. Этот параметр позволяет управлять тем, насколько быстро проигрывается конкретное воспроизведение, предоставляя больше гибкости и контроля (например, его можно использовать для эффекта замедленной съёмки).
### Аргументы

- **speed** - Коэффициент скорости воспроизведения (значение 2 означает, что трек проигрывается в 2 раза быстрее, а 0.5f замедлит его в 2 раза).

## getSpeed () const

Возвращает текущий коэффициент скорости для воспроизведения анимации. Этот параметр позволяет управлять тем, насколько быстро проигрывается конкретное воспроизведение, предоставляя больше гибкости и контроля (например, его можно использовать для эффекта замедленной съёмки).
### Возвращаемое значение

Текущий коэффициент скорости воспроизведения (значение 2 означает, что трек проигрывается в 2 раза быстрее, а 0.5f замедлит его в 2 раза).
## void setLoop ( bool loop )

Задаёт новое значение, указывающее, зациклено ли воспроизведение.
### Аргументы

- *bool* **loop** - **true**, чтобы включить зацикливание воспроизведения; **false** - чтобы отключить его.

## bool isLoop () const

Возвращает текущее значение, указывающее, зациклено ли воспроизведение.
### Возвращаемое значение

**true**, если воспроизведение зациклено; иначе **false**.
---

## AnimationPlayback ( )

Конструктор. Создаёт пустое воспроизведение с настройками по умолчанию.
## Ptr < AnimationObject > getObject ( int index ) const

Возвращает [animation object](../../../../principles/animations/index.md#animation_object) по его индексу.
### Аргументы

- *int* **index** - Индекс объекта анимации.

### Возвращаемое значение

Объект анимации с указанным индексом.
## bool containsObject ( const Ptr < AnimationObject > & anim_obj ) const

Возвращает значение, указывающее, содержит ли воспроизведение анимации указанный [animation object](../../../../principles/animations/index.md#animation_object).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationObject](../../../../api/library/animations/timeline/class.animationobject_cpp.md)> &* **anim_obj** - Объект анимации для проверки.

### Возвращаемое значение

true, если воспроизведение анимации содержит указанный объект анимации; иначе false.
## void clear ( )

Очищает воспроизведение анимации, удаляя из него все объекты анимации, слои и треки.
## void apply ( float time )

Вычисляет фактические значения для всех модификаторов всех треков, проигрываемых в указанный момент (с учётом весов), и применяет их к реальным анимируемым объектам (переопределения объектов анимации для этого воспроизведения).
### Аргументы

- *float* **time** - Значение времени, для которого должны быть вычислены и применены к анимируемым объектам результирующие изменения.

## void apply ( const Ptr < AnimationFrame > & frame )

Применяет указанный кадр анимации - для всех модификаторов всех треков, проигрываемых в этом кадре, вычисляются фактические значения (с учётом весов) и применяются к реальным анимируемым объектам (переопределения объектов анимации для этого воспроизведения).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationFrame](../../../../api/library/animations/timeline/class.animationframe_cpp.md)> &* **frame** - Кадр анимации для применения.

## void play ( )

Воспроизводит анимацию либо с начала, либо с момента, когда воспроизведение было приостановлено (см. *[pause()](../../../...md#pause_void)*).
## void pause ( )

Приостанавливает воспроизведение анимации, так что оно может быть возобновлено с этого момента при вызове *[play()](../../../...md#play_void)*.
## void stop ( )

Останавливает воспроизведение анимации.
## void setTrack ( const Ptr < AnimationTrack > & track )

Задаёт первый [track](../../../../principles/animations/index.md#animation_track) анимации первого [layer](../../../../principles/animations/index.md#animation_layer).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationTrack](../../../../api/library/animations/timeline/class.animationtrack_cpp.md)> &* **track** - Новый трек анимации, задаваемый как первый трек первого слоя.

## Ptr < AnimationTrack > getTrack ( ) const

Возвращает первый [track](../../../../principles/animations/index.md#animation_track) анимации первого [layer](../../../../principles/animations/index.md#animation_layer).
### Возвращаемое значение

Первый трек анимации первого слоя.
## int addLayer ( )

Добавляет новый [layer](../../../../principles/animations/index.md#animation_layer) анимации в воспроизведение.
### Возвращаемое значение

Индекс нового добавленного слоя.
## int addLayer ( const Ptr < AnimationTrack > & track )

Добавляет новый [layer](../../../../principles/animations/index.md#animation_layer) анимации в воспроизведение и добавляет указанный [track](../../../../principles/animations/index.md#animation_track) анимации в этот новый слой.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationTrack](../../../../api/library/animations/timeline/class.animationtrack_cpp.md)> &* **track** - Трек анимации для добавления в новый созданный слой.

### Возвращаемое значение

Индекс нового добавленного слоя.
## void removeLayer ( int index )

Удаляет из воспроизведения [layer](../../../../principles/animations/index.md#animation_layer) анимации с указанным индексом.
### Аргументы

- *int* **index** - Индекс слоя для удаления.

## int getNumLayers ( ) const

Возвращает общее количество [layers](../../../../principles/animations/index.md#animation_layer) анимации в воспроизведении.
## int addLayerTrack ( int layer_index )

Добавляет новый пустой трек анимации в [layer](../../../../principles/animations/index.md#animation_layer) с указанным индексом.
### Аргументы

- *int* **layer_index** - Индекс слоя.

### Возвращаемое значение

Индекс нового добавленного трека анимации.
## int addLayerTrack ( int layer_index , const Ptr < AnimationTrack > & track )

Добавляет указанный [track](../../../../principles/animations/index.md#animation_track) анимации в [layer](../../../../principles/animations/index.md#animation_layer) с указанным индексом.
### Аргументы

- *int* **layer_index** - Индекс слоя.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationTrack](../../../../api/library/animations/timeline/class.animationtrack_cpp.md)> &* **track** - Новый трек для добавления в слой.

### Возвращаемое значение

Индекс нового добавленного трека анимации.
## void removeLayerTrack ( int layer_index , int track_index )

Удаляет [track](../../../../principles/animations/index.md#animation_track) анимации с указанным индексом из указанного [layer](../../../../principles/animations/index.md#animation_layer).
### Аргументы

- *int* **layer_index** - Индекс слоя, содержащего трек для удаления.
- *int* **track_index** - Индекс трека для удаления.

## int getNumLayerTracks ( int layer_index ) const

Возвращает количество [tracks](../../../../principles/animations/index.md#animation_track) анимации для [layer](../../../../principles/animations/index.md#animation_layer) с указанным индексом.
### Аргументы

- *int* **layer_index** - Индекс слоя.

### Возвращаемое значение

Количество треков анимации для слоя.
## void setLayerTrack ( int layer_index , int track_index , const Ptr < AnimationTrack > & track )

Задаёт указанный [track](../../../../principles/animations/index.md#animation_track) анимации по индексу для указанного [layer](../../../../principles/animations/index.md#animation_layer).
### Аргументы

- *int* **layer_index** - Индекс слоя.
- *int* **track_index** - Индекс трека.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationTrack](../../../../api/library/animations/timeline/class.animationtrack_cpp.md)> &* **track** - Трек анимации для установки в указанном слое.

## Ptr < AnimationTrack > getLayerTrack ( int layer_index , int track_index ) const

Возвращает [track](../../../../principles/animations/index.md#animation_track) анимации по индексу для указанного [layer](../../../../principles/animations/index.md#animation_layer).
### Аргументы

- *int* **layer_index** - Индекс слоя.
- *int* **track_index** - Индекс трека.

### Возвращаемое значение

Трек анимации, установленный для указанного слоя.
## void setLayerTrackBeginTime ( int layer_index , int track_index , float offest )

Задаёт новое время смещения (от начала воспроизведения) для указанного [track](../../../../principles/animations/index.md#animation_track) указанного [layer](../../../../principles/animations/index.md#animation_layer).
### Аргументы

- *int* **layer_index** - Индекс слоя.
- *int* **track_index** - Индекс трека.
- *float* **offest** - Время смещения для установки, в секундах.

## float getLayerTrackBeginTime ( int layer_index , int track_index ) const

Возвращает текущее время смещения (от начала воспроизведения) для указанного [track](../../../../principles/animations/index.md#animation_track) указанного [layer](../../../../principles/animations/index.md#animation_layer).
### Аргументы

- *int* **layer_index** - Индекс слоя.
- *int* **track_index** - Индекс трека.

### Возвращаемое значение

Текущее время смещения, в секундах.
## void setLayerTrackSpeed ( int layer_index , int track_index , float speed )

Задаёт новое значение коэффициента скорости для указанного [track](../../../../principles/animations/index.md#animation_track) указанного [layer](../../../../principles/animations/index.md#animation_layer).
### Аргументы

- *int* **layer_index** - Индекс слоя.
- *int* **track_index** - Индекс трека.
- *float* **speed** - Новое значение коэффициента скорости для установки (значение 2 означает, что трек проигрывается в 2 раза быстрее, а 0.5f замедлит его в 2 раза).

## float getLayerTrackSpeed ( int layer_index , int track_index ) const

Возвращает текущее значение коэффициента скорости для указанного [track](../../../../principles/animations/index.md#animation_track) указанного [layer](../../../../principles/animations/index.md#animation_layer).
### Аргументы

- *int* **layer_index** - Индекс слоя.
- *int* **track_index** - Индекс трека.

### Возвращаемое значение

Текущее значение коэффициента скорости (значение 2 означает, что трек проигрывается в 2 раза быстрее, а 0.5f замедлит его в 2 раза).
## void setLayerTrackApplyBefore ( int layer_index , int track_index , bool is_apply )

Задаёт флаг, определяющий, применяется ли начальный кадр трека к воспроизведению до начала трека.
### Аргументы

- *int* **layer_index** - Индекс слоя.
- *int* **track_index** - Индекс трека.
- *bool* **is_apply** - true, чтобы включить применение начального кадра трека до начала трека; false - чтобы отключить его.

## bool isLayerTrackApplyBefore ( int layer_index , int track_index ) const

Возвращает флаг, определяющий, применяется ли начальный кадр трека к воспроизведению до начала трека.
### Аргументы

- *int* **layer_index** - Индекс слоя.
- *int* **track_index** - Индекс трека.

### Возвращаемое значение

true, если начальный кадр трека применяется к воспроизведению до начала трека; иначе false.
## void setLayerTrackApplyAfter ( int layer_index , int track_index , bool is_apply )

Задаёт флаг, определяющий, применяется ли конечный кадр трека к воспроизведению после окончания трека.
### Аргументы

- *int* **layer_index** - Индекс слоя.
- *int* **track_index** - Индекс трека.
- *bool* **is_apply** - true, чтобы включить применение конечного кадра трека после окончания трека; false - чтобы отключить его.

## bool isLayerTrackApplyAfter ( int layer_index , int track_index ) const

Возвращает флаг, определяющий, применяется ли конечный кадр трека к воспроизведению после окончания трека.
### Аргументы

- *int* **layer_index** - Индекс слоя.
- *int* **track_index** - Индекс трека.

### Возвращаемое значение

true, если конечный кадр трека применяется к воспроизведению после окончания трека; false - если отключено.
## void setLayerTrackWeightCurve ( int layer_index , int track_index , const Ptr < AnimationCurveFloat > & curve )

Задаёт новую кривую веса для указанного [track](../../../../principles/animations/index.md#animation_track) указанного [layer](../../../../principles/animations/index.md#animation_layer). Веса используются для [mixing](../../../../principles/animations/index.md#animation_track_blending) нескольких одновременно проигрываемых треков вместе. Кривая веса определяет динамику изменения веса трека во времени.
### Аргументы

- *int* **layer_index** - Индекс слоя.
- *int* **track_index** - Индекс трека.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveFloat](../../../../api/library/animations/timeline/class.animationcurvefloat_cpp.md)> &* **curve** - Кривая веса для установки для указанного трека.

## Ptr < AnimationCurveFloat > getLayerTrackWeightCurve ( int layer_index , int track_index ) const

Возвращает текущую кривую веса для указанного [track](../../../../principles/animations/index.md#animation_track) указанного [layer](../../../../principles/animations/index.md#animation_layer). Веса используются для [mixing](../../../../principles/animations/index.md#animation_track_blending) нескольких одновременно проигрываемых треков вместе. Кривая веса определяет динамику изменения веса трека во времени.
### Аргументы

- *int* **layer_index** - Индекс слоя.
- *int* **track_index** - Индекс трека.

### Возвращаемое значение

Кривая веса для указанного трека.
## void setLayerTrackLinearFade ( int layer_index , int track_index , float effect_time , bool use_fade_in , bool use_fade_out )

Включает линейное затухание (появление, исчезание или оба) для трека в течение указанного временного интервала эффекта. Этот метод автоматически обновляет кривую [weight](../../../../principles/animations/index.md#animation_track_blending) для трека.
### Аргументы

- *int* **layer_index** - Индекс слоя.
- *int* **track_index** - Индекс трека.
- *float* **effect_time** - Временной интервал (в секундах), в течение которого применяется эффект затухания. Интервалы появления и исчезания (если используются вместе) равны этому значению.
- *bool* **use_fade_in** - true, чтобы включить эффект появления для трека; false - чтобы отключить его.
- *bool* **use_fade_out** - true, чтобы включить эффект исчезания для трека; false - чтобы отключить его.

## float getLayerTrackDuration ( int layer_index , int track_index ) const

Возвращает текущую длительность для указанного [track](../../../../principles/animations/index.md#animation_track) указанного [layer](../../../../principles/animations/index.md#animation_layer).
### Аргументы

- *int* **layer_index** - Индекс слоя.
- *int* **track_index** - Индекс трека.

### Возвращаемое значение

Длительность трека, в секундах.
## float getLayerTrackEndTime ( int layer_index , int track_index ) const

Возвращает текущее время окончания для указанного [track](../../../../principles/animations/index.md#animation_track) указанного [layer](../../../../principles/animations/index.md#animation_layer).
### Аргументы

- *int* **layer_index** - Индекс слоя.
- *int* **track_index** - Индекс трека.

### Возвращаемое значение

Время окончания трека, в секундах.
## float getLayerDuration ( int layer_index ) const

Возвращает длительность [layer](../../../../principles/animations/index.md#animation_layer) анимации с указанным индексом.
### Аргументы

- *int* **layer_index** - Индекс слоя.

### Возвращаемое значение

Длительность слоя, в секундах.
## void setTime ( float time , float from = -1.0f , float to = -1.0f )

Задаёт текущее время воспроизведения и опциональные ограничения from и to.
### Аргументы

- *float* **time** - Текущее время воспроизведения для установки, в секундах.
- *float* **from** - Время начала для установки, в секундах.
- *float* **to** - Время окончания для установки, в секундах.

## float getTime ( ) const

Возвращает текущее время воспроизведения, в секундах.
### Возвращаемое значение

Текущее время воспроизведения, в секундах.
