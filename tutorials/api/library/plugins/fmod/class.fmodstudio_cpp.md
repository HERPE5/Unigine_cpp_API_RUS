# Unigine::Plugins::FMOD::FMODStudio Class (CPP)

**Header:** #include <plugins/Unigine/FMOD/UnigineFMOD.h>


> **Notice:** Этот набор функций доступен, если загружен плагин [FMOD](../../../../code/plugins/fmod/index.md).


Этот класс предназначен для взаимодействия с управляемыми данными проектами, созданными в FMOD Studio, во время выполнения.


## FMODStudio Class

---

## Bank * loadBank ( const char * path )

Загружает банк по указанному пути.
### Аргументы

- *const char ** **path** - Путь к файлу банка.

### Возвращаемое значение

Объект банка.
## Bank * loadBankFromMemory ( const char * buffer , int size )

Загружает банк из указанного буфера в памяти.
### Аргументы

- *const char ** **buffer** - Буфер, содержащий загружаемый банк.
- *int* **size** - Размер загружаемого банка, в байтах.

### Возвращаемое значение

Объект банка.
## VCA * getVCA ( const char * path )

Вспомогательная функция, не должна использоваться напрямую.
### Аргументы

- *const char ** **path**

## Bus * getBus ( const char * path )

Вспомогательная функция, не должна использоваться напрямую.
### Аргументы

- *const char ** **path**

## EventInstance * getEvent ( const char * path )

Возвращает объект EventInstance по указанному пути.
### Аргументы

- *const char ** **path** - Путь к EventInstance.

### Возвращаемое значение

Объект EventInstance.
## EventDescription * getEventDescription ( const char * path )

Вспомогательная функция, не должна использоваться напрямую.
### Аргументы

- *const char ** **path**

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

## void setListenerVelocity ( const Math:: Vec3 & velocity )

Задаёт скорость слушателя.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **velocity** - Скорость в мировом пространстве.

## void setListenerTransform ( const Math:: Mat4 & transform )

Задаёт матрицу трансформации слушателя. В настоящее время слушатель работает только со стандартной камерой.
### Аргументы

- *const  Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации.

## void setParentForListener ( const Ptr < Node > & parent )

Задаёт родительский узел для слушателя.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **parent** - Узел, задаваемый в качестве родителя.

## void useStudioLiveUpdateFlag ( )

Включает живое обновление.
## void useStudioSyncUpdateFlag ( )

Отключает асинхронную обработку и выполняет всю обработку в вызывающем потоке.
## void useStudioLoadFromUpdateFlag ( )

Для загрузки банков и ресурсов дополнительные потоки не создаются.
## void useCoreStreamFromUpdateFlag ( )

Внутренний поток для стриминга не создаётся. В основном используется с выходами не в реальном времени.
## void update ( )

Обновляет систему FMOD.
## void initStudio ( )

Инициализация Studio.
## Bank * getBank ( int id )

Вспомогательная функция, не должна использоваться напрямую.
### Аргументы

- *int* **id**

## EventDescription * getEventDescription ( int id )

Вспомогательная функция, не должна использоваться напрямую.
### Аргументы

- *int* **id**

## Bus * getBus ( int id )

Вспомогательная функция, не должна использоваться напрямую.
### Аргументы

- *int* **id**

## VCA * getVCA ( int id )

Вспомогательная функция, не должна использоваться напрямую.
### Аргументы

- *int* **id**

## int getBankCount ( )

Возвращает количество загруженных банков.
### Возвращаемое значение

Количество банков.
## int getEventDescriptionCount ( )

Возвращает количество описаний событий.
### Возвращаемое значение

Количество описаний событий.
## int getBusCount ( )

Возвращает количество шин.
### Возвращаемое значение

Количество шин.
## int getVCACount ( )

Возвращает количество VCA.
### Возвращаемое значение

Количество VCA.
## FMODStudio::BufferUsage getBufferUsage ( )

Возвращает информацию об использовании буферов.
### Возвращаемое значение

Информация об использовании буферов.
## void resetBufferUsage ( )

Сбрасывает статистику использования буферов памяти.
## FMODStudio::CPUUsageTotal getCPUUsageTotal ( )

Возвращает общий объём использования ЦП.
### Возвращаемое значение

Общее использование ЦП.
## void getMemoryUsage ( int & exclusive , int & inclusive , int & sample_data )

Возвращает статистику использования памяти.
### Аргументы

- *int &* **exclusive** - Размер памяти, принадлежащей шине или экземпляру события.
- *int &* **inclusive** - Размер памяти, принадлежащей исключительно шине или событию, плюс включённые размеры памяти всех шин и экземпляров событий, направляемых в неё.
- *int &* **sample_data** - Размер общей памяти сэмплов, на которую ссылается шина или экземпляр события, включая всю память сэмплов, на которую ссылаются все шины и экземпляры событий, направляемые в неё.

## void release ( )

Завершает работу и освобождает объект Studio System.
## void releaseBuses ( )

Освобождает объекты шин.
## void releaseVCAs ( )

Освобождает объекты VCA.
## void releaseEventDescriptions ( )

Освобождает объекты описаний событий.
## void releaseBanks ( )

Освобождает объекты банков.
## void useChannelsCount ( int count )

Обновляет максимальное количество каналов (виртуальных и реальных), используемых в системе FMOD.
### Аргументы

- *int* **count** - Количество каналов.

## bool unloadBank ( const char * path )

Уничтожает все объекты, созданные из банка, выгружает все данные сэмплов внутри банка и делает недействительными все дескрипторы API, ссылающиеся на банк.
### Аргументы

- *const char ** **path** - Путь к банку, который следует выгрузить.

### Возвращаемое значение

true, если банк успешно выгружен; иначе false.
