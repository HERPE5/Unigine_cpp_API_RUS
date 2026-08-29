# Unigine::Plugins::FMOD::Bus Class (CPP)

**Header:** #include <plugins/Unigine/FMOD/UnigineFMOD.h>


> **Notice:** Этот набор функций доступен, если загружен плагин [FMOD](../../../../code/plugins/fmod/index.md).


Представляет глобальную шину микшера.


## Bus Class

### Методы класса

## void setPaused ( bool paused )

Задаёт новое состояние паузы для шины.
### Аргументы

- *bool* **paused** - Установите **true**, чтобы включить состояние паузы для шины; **false** - чтобы отключить его.

## bool isPaused () const

Возвращает текущее состояние паузы шины.
### Возвращаемое значение

**true**, если состояние паузы шины включено; иначе **false**.
## void setVolume ( float volume )

Задаёт новый уровень громкости в диапазоне [-inf; inf].
### Аргументы

- *float* **volume** - Уровень громкости в диапазоне [-inf; inf].

## float getVolume () const

Возвращает текущий уровень громкости в диапазоне [-inf; inf].
### Возвращаемое значение

Текущий уровень громкости в диапазоне [-inf; inf].
## void setMuted ( bool muted )

Задаёт новое состояние отключения звука для шины.
### Аргументы

- *bool* **muted** - Установите **true**, чтобы включить состояние отключения звука для шины; **false** - чтобы отключить его.

## bool isMuted () const

Возвращает текущее состояние отключения звука шины.
### Возвращаемое значение

**true**, если состояние отключения звука шины включено; иначе **false**.
## bool isValid () const

Возвращает текущее значение, указывающее, действительна ли ссылка на шину.
### Возвращаемое значение

**true**, если ссылка на шину действительна; иначе **false**.
---

## void stopAllEvents ( )

Останавливает все экземпляры событий, направленные в шину.
## void release ( )

Освобождает объект шины.
## String getPath ( ) const

Возвращает путь объекта шины.
### Возвращаемое значение

Путь объекта.
## ChannelGroup * getChannelGroup ( ) const

Возвращает базовый [ChannelGroup](../../../../api/library/plugins/fmod/class.channelgroup_cpp.md). По умолчанию ChannelGroup существует только тогда, когда это необходимо. Если ChannelGroup не существует, эта функция вернёт [ERR_STUDIO_NOT_LOADED](../../../../api/library/plugins/fmod/class.fmodenums_cpp.md#ERR_STUDIO_NOT_LOADED).
### Возвращаемое значение

Базовый ChannelGroup.
## void lockChannelGroup ( )

Блокирует базовый [ChannelGroup](../../../../api/library/plugins/fmod/class.channelgroup_cpp.md). Эта функция заставляет систему создать ChannelGroup и удерживать его доступным до вызова [unlockChannelGroup](#unlockChannelGroup_void).
## void unlockChannelGroup ( )

Разблокирует базовый [ChannelGroup](../../../../api/library/plugins/fmod/class.channelgroup_cpp.md). Эта функция позволяет системе уничтожить ChannelGroup, когда он больше не нужен.
