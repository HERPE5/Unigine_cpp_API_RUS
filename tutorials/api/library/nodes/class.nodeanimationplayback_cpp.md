# Класс NodeAnimationPlayback (CPP)

**Header:** #include <UnigineNodes.h>

**Inherits from:** Node


Этот класс используется для воспроизведения [tracks](../../../principles/animations/index.md#animation_track) (`.utrack`). Он позволяет клонировать анимированные объекты в иерархии, а также преобразовывать подготовленные анимации и объекты в *NodeReferences*. Каждый узел *AnimationPlayback* добавляет переопределения для своего внутреннего [playback](../../../principles/animations/index.md#animation_playback) к [animation objects](../../../principles/animations/index.md#animation_object) (треки анимации не копируются).


## Класс NodeAnimationPlayback

### Методы класса

## bool isPlaying () const

Возвращает текущее значение, указывающее, воспроизводится ли в данный момент playback.
### Возвращаемое значение

**true**, если playback воспроизводится в данный момент; иначе **false**.
## void setLoop ( bool loop )

Задаёт новое значение, указывающее, зациклен ли playback.
### Аргументы

- *bool* **loop** - Установите **true**, чтобы включить зацикливание playback; **false** - чтобы отключить.

## bool isLoop () const

Возвращает текущее значение, указывающее, зациклен ли playback.
### Возвращаемое значение

**true**, если playback зациклен; иначе **false**.
## void setSpeed ( float speed )

Задаёт новый коэффициент скорости для воспроизведения анимации. Этот параметр позволяет управлять скоростью воспроизведения конкретного playback, предоставляя больше гибкости и контроля (например, его можно использовать для эффекта замедленной съёмки).
### Аргументы

- *float* **speed** - Коэффициент скорости playback (значение 2 означает, что трек воспроизводится в 2 раза быстрее, а 0.5f замедлит его в 2 раза).

## float getSpeed () const

Возвращает текущий коэффициент скорости для воспроизведения анимации. Этот параметр позволяет управлять скоростью воспроизведения конкретного playback, предоставляя больше гибкости и контроля (например, его можно использовать для эффекта замедленной съёмки).
### Возвращаемое значение

Текущий коэффициент скорости playback (значение 2 означает, что трек воспроизводится в 2 раза быстрее, а 0.5f замедлит его в 2 раза).
## void setTrackFileGUID ( const UGUID & guid )

Задаёт новый GUID файла `.utrack`.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - GUID файла `.utrack`.

## const UGUID & getTrackFileGUID () const

Возвращает текущий GUID файла `.utrack`.
### Возвращаемое значение

Текущий GUID файла `.utrack`.
## void setTrackPath ( const char * path )

Задаёт новый путь к файлу `.utrack`.
### Аргументы

- *const char ** **path** - Путь к файлу `.utrack`.

## const char * getTrackPath () const

Возвращает текущий путь к файлу `.utrack`.
### Возвращаемое значение

Текущий путь к файлу `.utrack`.
## void setPlayOnEnable ( bool enable )

Задаёт новое значение, указывающее, запускается ли playback при включении узла.
### Аргументы

- *bool* **enable** - Установите **true**, чтобы включить возобновление playback при включении узла; **false** - чтобы отключить.

## bool isPlayOnEnable () const

Возвращает текущее значение, указывающее, запускается ли playback при включении узла.
### Возвращаемое значение

**true**, если playback возобновляется при включении узла; иначе **false**.
## void setRestartOnEnable ( bool enable )

Задаёт новое значение, указывающее, перезапускается ли playback при включении узла.
### Аргументы

- *bool* **enable** - Установите **true**, чтобы включить перезапуск playback при включении узла; **false** - чтобы отключить.

## bool isRestartOnEnable () const

Возвращает текущее значение, указывающее, перезапускается ли playback при включении узла.
### Возвращаемое значение

**true**, если playback перезапускается при включении узла; иначе **false**.
## void setTimeFrom ( float from )

Задаёт новое время начала playback, в секундах.
### Аргументы

- *float* **from** - Время начала playback, в секундах.

## float getTimeFrom () const

Возвращает текущее время начала playback, в секундах.
### Возвращаемое значение

Текущее время начала playback, в секундах.
## void setTimeTo ( float to )

Задаёт новое время окончания playback, в секундах.
### Аргументы

- *float* **to** - Время окончания playback, в секундах.

## float getTimeTo () const

Возвращает текущее время окончания playback, в секундах.
### Возвращаемое значение

Текущее время окончания playback, в секундах.
---

## static NodeAnimationPlaybackPtr create ( )

Конструктор. Создаёт экземпляр класса с параметрами по умолчанию.
## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [NodeAnimationPlayback](../../../api/library/nodes/class.node_cpp.md#NODE_ANIMATION_PLAYBACK).
## void play ( )

Воспроизводит анимацию либо с начала, либо с момента, когда playback был приостановлен (см. *[pause()](../../...md#pause_void)*).
## void pause ( )

Приостанавливает воспроизведение анимации, так что playback может быть возобновлён с этого момента при вызове *[play()](../../...md#play_void)*.
## void stop ( )

Останавливает воспроизведение анимации.
## void setTime ( float time , float from = -1.0f , float to = -1.0f )

Задаёт текущее время playback и опциональные пределы from и to.
### Аргументы

- *float* **time** - Задаваемое текущее время playback, в секундах.
- *float* **from** - Задаваемое время начала, в секундах.
- *float* **to** - Задаваемое время окончания, в секундах.

## float getTime ( ) const

Возвращает текущее время playback, в секундах.
### Возвращаемое значение

Текущее время playback, в секундах.
