# Unigine::Plugins::FMOD::ChannelGroup Class (CPP)

**Header:** #include <plugins/Unigine/FMOD/UnigineFMOD.h>


> **Notice:** Этот набор функций доступен, если загружен плагин [FMOD](../../../../code/plugins/fmod/index.md).


Субмикс в иерархии микширования, который может содержать объекты Channel и ChannelGroup.


## ChannelGroup Class

---

## Channel * getChannel ( int id )

Возвращает канал по указанному индексу.
### Аргументы

- *int* **id** - Индекс канала.

### Возвращаемое значение

Канал по указанному индексу.
## int getChannelCount ( )

Возвращает количество каналов, направляемых в эту группу.
### Возвращаемое значение

Количество каналов.
## void setVolume ( float volume )

Задаёт уровень громкости для группы.
### Аргументы

- *float* **volume** - Уровень громкости.

## void addChannel ( Channel * OUT_channel )

Добавляет канал в группу.
### Аргументы

- *[Channel](../../../../api/library/plugins/fmod/class.channel_cpp.md) ** **OUT_channel** - Добавляемый канал. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## DSP * addDSP ( int index , DSPType::TYPE dsp_type )

Добавляет DSP-модуль по указанному индексу в цепочке DSP.
### Аргументы

- *int* **index** - Смещение в цепочке DSP.
- *[DSPType::TYPE](../../../../api/library/plugins/fmod/class.dsptype_cpp.md#TYPE)* **dsp_type** - [Type](../../../../api/library/plugins/fmod/class.dsptype_cpp.md) добавляемого DSP-модуля.

### Возвращаемое значение

Добавленный DSP-модуль.
## void addDSP ( DSP * fmod_dsp )

Добавляет указанный DSP-модуль в цепочку DSP.
### Аргументы

- *[DSP](../../../../api/library/plugins/fmod/class.dsp_cpp.md) ** **fmod_dsp** - Добавляемый DSP-модуль.

## bool containsDSP ( void * fmod_dsp )

Проверяет, содержит ли цепочка DSP указанный DSP-модуль.
### Аргументы

- *void ** **fmod_dsp** - Проверяемый DSP-модуль.

## void removeDSP ( int index )

Удаляет указанный DSP-модуль из цепочки DSP.
### Аргументы

- *int* **index** - Индекс удаляемого DSP-модуля.

## void unregisterDSP ( void * fmod_dsp )

Отменяет регистрацию плагина DSP.
### Аргументы

- *void ** **fmod_dsp** - Плагин DSP, регистрация которого отменяется.

## DSP * getDSP ( int index )

Возвращает DSP-модуль по указанному индексу в цепочке DSP.
### Аргументы

- *int* **index** - Смещение в цепочке DSP.

### Возвращаемое значение

DSP-модуль по указанному индексу.
## DSP * getDSP ( void * fmod_dsp )

Возвращает внутренний DSP-модуль FMOD по его указателю.
### Аргументы

- *void ** **fmod_dsp** - Указатель на внутренний DSP-модуль FMOD.

### Возвращаемое значение

DSP-модуль.
## int getNumDSPs ( ) const

Возвращает количество DSP-модулей в цепочке DSP.
### Возвращаемое значение

Количество DSP-модулей в цепочке DSP.
## void release ( )

Завершает работу и освобождает объект.
