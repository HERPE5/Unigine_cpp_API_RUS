# Unigine::Plugins::FMOD::FMODCore Class (CPP)

**Header:** #include <plugins/Unigine/FMOD/UnigineFMOD.h>


> **Notice:** Этот набор функций доступен, если загружен плагин [FMOD](../../../../code/plugins/fmod/index.md).


Этот класс предназначен для работы с базовыми примитивами звука.


## FMODCore Class

---

## void close ( )

Закрывает соединение с выходом и возвращается в неинициализированное состояние без освобождения объекта.
## void release ( )

Закрывает и освобождает этот объект и его ресурсы.
## void update ( )

Обновляет систему FMOD.
## void initCore ( int max_channels , FMODEnums::INIT_FLAGS flags )

Инициализирует системный объект и подготавливает FMOD к воспроизведению.
### Аргументы

- *int* **max_channels** - Максимальное количество объектов Channel, доступных для воспроизведения, также известных как виртуальные каналы. Виртуальные каналы воспроизводятся с минимальными накладными расходами, с подмножеством 'реальных' голосов, которые микшируются и выбираются на основе приоритета и слышимости. Диапазон: [0; 4095]
- *[FMODEnums::INIT_FLAGS](../../../../api/library/plugins/fmod/class.fmodenums_cpp.md#INIT_FLAGS)* **flags** - Флаги инициализации. Можно задать сразу несколько режимов, объединив их оператором OR.

## Sound * createSound ( const char * name_of_data , FMODEnums::FMOD_MODE mode )

Загружает звук в память, открывает его для потоковой передачи или настраивает для звуков на основе колбэков.
### Аргументы

- *const char ** **name_of_data** - Имя открываемого файла или URL (строка UTF-8), либо указатель на предзагруженный блок памяти звука.
- *[FMODEnums::FMOD_MODE](../../../../api/library/plugins/fmod/class.fmodenums_cpp.md#FMOD_MODE)* **mode** - Модификатор поведения для открытия звука.

### Возвращаемое значение

Вновь созданный объект Sound.
## Sound * createStream ( const char * url )

Создаёт поток, например, интернет-поток, используемый как радио.
### Аргументы

- *const char ** **url** - URL ресурса.

### Возвращаемое значение

Вновь созданный объект Sound.
## Channel * playSound ( Sound * OUT_sound , ChannelGroup * OUT_channel_group , bool paused )

Воспроизводит звук на канале.
### Аргументы

- *[Sound](../../../../api/library/engine/class.sound_cpp.md) ** **OUT_sound** - Воспроизводимый звук. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.
- *[ChannelGroup](../../../../api/library/plugins/fmod/class.channelgroup_cpp.md) ** **OUT_channel_group** - Группа для вывода вместо мастера. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.
- *bool* **paused** - Определяет, следует ли запускать в состоянии паузы. Запустите канал приостановленным, чтобы можно было изменить атрибуты, не делая его слышимым, а затем вызовите *ChannelControl::setPaused* с *paused* = False.

### Возвращаемое значение

Вновь воспроизводящий канал.
## void setListener3DAttributes ( int listener , const Math:: Vec3 & position , const Math:: Vec3 & up , const Math:: Vec3 & forward , const Math:: Vec3 & velocity )

Задаёт 3D-атрибуты слушателя. Векторы должны быть заданы с правильной ориентацией системы координат.
### Аргументы

- *int* **listener** - Индекс слушателя.
- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **position** - Положение в мировом пространстве, используемое для панорамирования и затухания.
- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **up** - Ориентация вверх, должна иметь единичную длину (1.0) и быть перпендикулярна forward.
- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **forward** - Ориентация вперёд, должна иметь единичную длину (1.0) и быть перпендикулярна up.
- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **velocity** - Скорость в мировом пространстве, используемая для эффекта Доплера.

## void getListener3DAttributes ( int listener , Math:: Vec3 & position , Math:: Vec3 & up , Math:: Vec3 & forward , Math:: Vec3 & velocity )

Возвращает 3D-атрибуты слушателя.
### Аргументы

- *int* **listener** - Индекс слушателя.
- *Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **position** - Положение в мировом пространстве.
- *Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **up** - Ориентация вверх.
- *Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **forward** - Ориентация вперёд.
- *Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **velocity** - Скорость в мировом пространстве.

## Channel * getChannel ( int index )

Возвращает объект канала по указанному индексу.
### Аргументы

- *int* **index** - Индекс канала.

### Возвращаемое значение

Объект канала.
## ChannelGroup * createChannelGroup ( const char * name )

Создаёт объект ChannelGroup.
### Аргументы

- *const char ** **name** - Метка для идентификации, в формате UTF-8.

### Возвращаемое значение

Вновь созданная группа.
