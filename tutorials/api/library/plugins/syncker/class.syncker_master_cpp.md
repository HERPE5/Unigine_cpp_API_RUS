# Unigine::Plugins::Syncker::Master Class (CPP)

**Header:** #include <plugins/Unigine/Syncker/UnigineSyncker.h>

**Inherits from:** Syncker


Этот класс представляет интерфейс master Syncker.


> **Notice:** Плагин [Syncker](../../../../code/plugins/syncker/index.md) должен быть загружен.


## Master Class

### Перечисления

## CALLBACK_INDEX

Типы callback.
| Name | Description |
|---|---|
| **SESSION_STARTED** = 0 | Функция callback, вызываемая при начале сессии (все Slave подключены, MTU определён). Сигнатура callback: ```text callback_function_name(void) ``` |
| **SESSION_CONTINUED** = | Функция callback, вызываемая при продолжении сессии. Сигнатура callback: ```text callback_function_name(Vector <long long> slaves_id) ``` |
| **SESSION_FINISHED** = 2 | Функция callback, вызываемая при закрытии сессии. Сигнатура callback: ```text callback_function_name(void) ``` |
| **SLAVE_CONNECTED** = 3 | Функция callback, вызываемая при успешном подключении нового Slave. Сигнатура callback: ```text callback_function_name(int slave_num) ``` |
| **SLAVE_DISCONNECTED** = 4 | Функция callback, вызываемая перед отключением Slave. Причина отключения задаётся в строковом формате ("disconnected by slave", "timeout" и т.д.). Сигнатура callback: ```text callback_function_name(int slave_num, const char *reason) ``` |
| **MASTER_SETUP_CHANGED** = 5 | Callback, вызываемый при изменении настроек на Master. Сигнатура callback: ```text void callback_function_name(void); ``` |
| **SLAVE_SETUP_CHANGED** = 6 | Callback, вызываемый при изменении настроек на Slave. Сигнатура callback: ```text void callback_function_name(int slave_num); ``` |

## SYNC_MASK

Маска синхронизации узла.
| Name | Description |
|---|---|
| **NODE_FLAGS** = 1 | Обновлять только простой флаг узла (*enabled*, *immovable* и т.д.) |
| **TRANSFORM** = 1 << 1 | Обновлять трансформацию узла (с интерполяцией). |
| **BASE** = 3 | Обновлять базовую информацию NODEFLAGS & TRANSFORM. |
| **DERIVED** = 31 << 3 | Обновлять информацию производного класса (11111000 - без первых 3 битов). Эта маска позволяет синхронизировать параметры подтипа узла (такие как player, light, decal и т.д.). |
| **OBJECT** = 1 << 3 | Обновлять параметры объекта. Все остальные параметры объектов, кроме NODE_FLAGS и TRANSFORM (трансформация частиц для object particles, трансформация костей для object skinned) |
| **OBJECT_SURFACE** = 1 << 4 | Обновлять все параметры поверхностей (флаги поверхности и информацию об унаследованных материалах для каждой поверхности). |

## DEFAULT_SYNC_NODES

Типы узлов, которые будут синхронизированы автоматически после загрузки мира.
| Name | Description |
|---|---|
| **LIGHT_WORLD** = 1 | Мировой источник света. См. класс [LightWorld](../../../../api/library/lights/class.lightworld_cpp.md). |
| **WATER_GLOBAL** = 1 << 1 | Глобальная вода. См. класс [ObjectWaterGlobal](../../../../api/library/objects/class.objectwaterglobal_cpp.md). |
| **CLOUD_LAYER** = 1 << 2 | Слой облаков. См. класс [ObjectCloudLayer](../../../../api/library/objects/class.objectcloudlayer_cpp.md). |
| **OBJECT_PARTICLES** = 1 << 3 | Система частиц. См. класс [ObjectParticles](../../../../api/library/objects/class.objectparticles_cpp.md). |

### Методы класса

---

## int getNumSlaves ( ) const

Возвращает общее количество Slave, подключённых к Master.
### Возвращаемое значение

Общее количество Slave, подключённых к Master.
## const char * getSlaveAddress ( int num ) const

Возвращает сетевой адрес указанного компьютера slave.
### Аргументы

- *int* **num** - Номер slave.

### Возвращаемое значение

Сетевой адрес компьютера slave.
## int getSlavePort ( int num ) const

Возвращает порт UDP, используемый slave с указанным номером.
### Аргументы

- *int* **num** - Номер slave.

### Возвращаемое значение

Порт UDP указанного компьютера slave. 0 означает любой доступный неиспользуемый порт.
## long long getSlaveID ( int num ) const

Возвращает ID slave с указанным номером. Уникальный ID Slave состоит из двух частей: IP (32 бита) + порт (16 бит)
### Аргументы

- *int* **num** - Номер slave.

### Возвращаемое значение

ID slave с указанным номером.
## const char * getSlaveWorldName ( int num ) const

Возвращает имя файла мира, в данный момент загруженного на указанном slave.
### Аргументы

- *int* **num** - Номер slave.

### Возвращаемое значение

Имя файла мира, в данный момент загруженного на указанном slave.
## void setSyncPlayer ( bool enabled )

Включает синхронизацию параметров текущего player через протокол UDP:
- Его трансформация
- Матрица проекции
- Маска viewport
- Маска отражений
- Применённые пост-материалы (если есть)


> **Notice:** Синхронизация текущего player используется только когда все slave используют одну и ту же камеру.


### Аргументы

- *bool* **enabled** - true, чтобы включить синхронизацию; false - чтобы отключить её.

## bool isSyncPlayer ( ) const

Возвращает значение, указывающее, включена ли синхронизация текущего player.
> **Notice:** Синхронизация текущего player используется только когда все slave используют одну и ту же камеру.


### Возвращаемое значение

true, если синхронизация текущего player включена; иначе false.
## void setSyncRender ( bool enabled )

Включает синхронизацию всех параметров рендеринга через протокол UDP: рассеивание света, occlusion и т.д.
> **Notice:** Когда все slave используют одинаковые настройки рендеринга, синхронизацию параметров рендеринга можно отключить.


### Аргументы

- *bool* **enabled** - true, чтобы включить синхронизацию; false - чтобы отключить её.

## bool isSyncRender ( ) const

Возвращает значение, указывающее, включена ли синхронизация всех параметров рендеринга.
> **Notice:** Когда все slave используют одинаковые настройки рендеринга, синхронизацию параметров рендеринга можно отключить.


### Возвращаемое значение

true, если синхронизация всех параметров рендеринга включена; иначе false.
## void addSyncNode ( const Ptr < Node > & node , unsigned char sync_mask = SYNC_MASK::NODE_FLAGS | SYNC_MASK::TRANSFORM )

Включает синхронизацию параметров указанного узла через протокол UDP.
> **Notice:** Узлы сцены не синхронизируются по умолчанию, этот метод используется для добавления конкретного узла в очередь синхронизации.


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **node** - Узел для синхронизации.
- *unsigned char* **sync_mask** - Маска синхронизации, одно из значений [SYNC_MASK](#SYNC_MASK). По умолчанию синхронизируется только трансформация узла. Чтобы синхронизировать другие параметры, выберите соответствующую маску.

## void addSyncNodes ( const Vector < Ptr < Node >> & nodes , unsigned char sync_mask = SYNC_MASK::NODE_FLAGS | SYNC_MASK::TRANSFORM )

Включает синхронизацию параметров указанных узлов через протокол UDP.
> **Notice:** Узлы сцены не синхронизируются по умолчанию, этот метод используется для добавления конкретных узлов в очередь синхронизации.


### Аргументы

- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)>> &* **nodes** - Список узлов для синхронизации.
- *unsigned char* **sync_mask** - Маска синхронизации, одно из значений [SYNC_MASK](#SYNC_MASK). По умолчанию синхронизируется только трансформация узла. Чтобы синхронизировать другие параметры, выберите соответствующую маску.

## void setSyncNodeMask ( const Ptr < Node > & node , unsigned char sync_mask )

Задаёт новую маску синхронизации для указанного узла. Маска синхронизации может использоваться в целях оптимизации, ограничивая объём синхронизируемых данных и тем самым снижая сетевую нагрузку. Например, для движущихся частей вертолёта можно задать маску для синхронизации только трансформаций узлов:
```cpp
master->setSyncNodeMask(fan_small, Syncker::Master::TRANSFORM);
master->setSyncNodeMask(fan_big, Syncker::Master::TRANSFORM);

```


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **node** - Узел, для которого задаётся новая маска синхронизации.
- *unsigned char* **sync_mask** - Новая маска синхронизации, задаваемая для указанного узла, одно из значений [SYNC_MASK](#SYNC_MASK).

## unsigned char getSyncNodeMask ( const Ptr < Node > & node ) const

Возвращает маску синхронизации для указанного узла.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **node** - Узел, для которого нужно получить маску синхронизации.

### Возвращаемое значение

Маска синхронизации указанного узла, одно из значений [SYNC_MASK](#SYNC_MASK).
## bool isSyncNode ( const Ptr < Node > & node ) const

Возвращает значение, указывающее, включена ли синхронизация указанного узла. С помощью этого метода можно быстро проверить, отслеживается ли узел Syncker (состояния узла передаются Slave по сети).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **node** - Узел для проверки.

### Возвращаемое значение

true, если синхронизация указанного узла включена; иначе false.
## int getNumSyncNodes ( ) const

Возвращает общее количество узлов в очереди синхронизации.
### Возвращаемое значение

Общее количество узлов в очереди синхронизации.
## Ptr < Node > getSyncNode ( int num ) const

Возвращает синхронизированный узел с указанным номером.
### Аргументы

- *int* **num** - Номер узла в очереди синхронизации.

### Возвращаемое значение

Синхронизированный узел.
## void removeSyncNode ( int num )

Удаляет указанный узел из очереди синхронизации.
### Аргументы

- *int* **num** - Номер узла в очереди синхронизации.

## void removeSyncNode ( const Ptr < Node > & node )

Удаляет указанный узел из очереди синхронизации.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **node** - Узел, который нужно удалить из синхронизации.

## void removeSyncNodeID ( int node_id )

Удаляет указанный узел из очереди синхронизации по его ID.
### Аргументы

- *int* **node_id** - ID узла, который нужно удалить из очереди синхронизации.

## void removeSyncNodes ( const Vector < Ptr < Node >> & nodes )

Удаляет указанные узлы из очереди синхронизации.
### Аргументы

- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)>> &* **nodes** - Список узлов, которые нужно удалить из очереди синхронизации.

## void clearSyncNodes ( )

Удаляет все узлы из очереди синхронизации.
## void addSyncMaterial ( const Ptr < Material > & material )

Включает синхронизацию указанного материала через протокол UDP.
> **Notice:** Материалы сцены не синхронизируются по умолчанию, этот метод используется для добавления конкретного материала в очередь синхронизации.


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Material](../../../../api/library/rendering/class.material_cpp.md)> &* **material** - Материал для синхронизации.

## void addSyncMaterials ( const Vector < Ptr < Material >> & materials )

Включает синхронизацию указанных материалов через протокол UDP.
> **Notice:** Материалы сцены не синхронизируются по умолчанию, этот метод используется для добавления конкретных материалов в очередь синхронизации.


### Аргументы

- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Material](../../../../api/library/rendering/class.material_cpp.md)>> &* **materials** - Список материалов для синхронизации.

## bool isSyncMaterial ( const Ptr < Material > & mat ) const

Возвращает значение, указывающее, включена ли синхронизация указанного материала. С помощью этого метода можно быстро проверить, отслеживается ли материал Syncker (состояния материала передаются Slave по сети).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Material](../../../../api/library/rendering/class.material_cpp.md)> &* **mat** - Материал для проверки.

### Возвращаемое значение

true, если синхронизация указанного материала включена; иначе false.
## int getNumSyncMaterials ( ) const

Возвращает общее количество материалов в очереди синхронизации.
### Возвращаемое значение

Общее количество материалов в очереди синхронизации.
## Ptr < Material > getSyncMaterial ( int num ) const

Возвращает синхронизированный материал с указанным номером.
### Аргументы

- *int* **num** - Номер материала в очереди синхронизации.

### Возвращаемое значение

Синхронизированный материал.
## void removeSyncMaterial ( int num )

Удаляет материал с указанным номером из очереди синхронизации.
### Аргументы

- *int* **num** - Номер материала в очереди синхронизации.

## void removeSyncMaterial ( const Ptr < Material > & material )

Удаляет указанный материал из очереди синхронизации.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Material](../../../../api/library/rendering/class.material_cpp.md)> &* **material** - Материал, который нужно удалить из очереди синхронизации.

## void removeSyncMaterials ( const Vector < Ptr < Material >> & materials )

Удаляет указанные материалы из очереди синхронизации.
### Аргументы

- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Material](../../../../api/library/rendering/class.material_cpp.md)>> &* **materials** - Список материалов, которые нужно удалить из очереди синхронизации.

## void clearSyncMaterials ( )

Удаляет все материалы из очереди синхронизации.
## bool createNode ( const Ptr < Node > & node , unsigned char sync_mask = 0 )

Синхронизирует создание указанного узла на всех Slave. Этот метод **должен вызываться после создания узла на Master**.
> **Notice:** Рекомендуется по возможности использовать методы [*loadNode()*](#loadNode_cstr_uchar_Mat4_Node) или [*loadNodereference()*](#loadNodeReference_cstr_uchar_Mat4_NodeReference), поскольку этот подход **позволяет добавлять узлы всех типов**, в отличие от метода [*createNode()*](#createNode_Node_uchar_bool), который поддерживает лишь ограниченное их количество.

 **Пример:**
```cpp
NodePtr node = NodeDummy::create();
master->createNode(node);

```


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **node** - Узел для создания.
- *unsigned char* **sync_mask** - Маска синхронизации, одно из значений [SYNC_MASK](#SYNC_MASK).

### Возвращаемое значение

true, если узел был успешно создан; иначе false.
## void deleteNode ( const Ptr < Node > & node )

Синхронизирует удаление указанного узла (со всеми его дочерними узлами) на Master и всех Slave. Аналогично вызову *deleteLater()* для узла.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **node** - Узел для удаления.

## bool isNodeCreatedBySyncker ( const Ptr < Node > & node ) const

Возвращает значение, указывающее, был ли указанный узел создан методом [*createNode()*](#createNode_Node_uchar_bool). С помощью этого метода можно быстро проверить, находится ли узел в буфере создания объектов времени выполнения.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **node** - Узел для проверки.

### Возвращаемое значение

true, если указанный узел был создан методом [*createNode()*](#createNode_Node_uchar_bool); иначе false.
## void setCustomPlayer ( const char * name , const Ptr < Player > & player )

Задаёт указанный player для view, группы view или компьютера с указанным именем.
> **Notice:** Синхронизация [main master camera](../../../../code/plugins/syncker/index.md#main_camera) отключена.


### Аргументы

- *const char ** **name** - Имя view, группы view или компьютера, для которого задаётся пользовательский player. > **Notice:** Указанное имя будет проверено в следующем порядке: *view, группа view, компьютер*. Указанный player будет задан для первого найденного элемента.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Player](../../../../api/library/players/class.player_cpp.md)> &* **player** - Player для задания.

## void setSendRate ( float rate )


Задаёт частоту отправки пакетов Slave. Используйте этот метод, когда сетевая нагрузка слишком высока и замедляет всю систему IG. Рекомендуется использовать этот метод с включённой [interpolation](../../../../api/library/plugins/syncker/class.syncker_syncker_cpp.md#setInterpolation_int_void).


```cpp
//На Master
master->setSendRate(15.0f); // отправлять пакеты 15 раз в секунду

//Как на Master, так и на всех Slave
syncker->setInterpolationPeriod(0.1f); // задержка 100 мс

```


### Аргументы

- *float* **rate** - Частота отправки пакетов Slave. Значение по умолчанию — -1 (каждый кадр). > **Notice:** Значение не должно быть меньше ***1 / [getInterpolationPeriod()](../../../../api/library/plugins/syncker/class.syncker_syncker_cpp.md#getInterpolationPeriod_double)***, иначе изображение будет "дёргаться".

## float getSendRate ( ) const

Возвращает текущую частоту отправки пакетов Slave. Используйте этот метод, когда сетевая нагрузка слишком высока и замедляет всю систему IG. Рекомендуется использовать этот метод с включённой [interpolation](../../../../api/library/plugins/syncker/class.syncker_syncker_cpp.md#setInterpolation_int_void).
### Возвращаемое значение

Частота отправки пакетов Slave.
## void setAllowExtraSlaves ( bool slaves )

Задаёт значение, указывающее, могут ли новые Slave подключаться к Master после начала сессии. Это может использоваться, например, для подключения Slave, применяемого в качестве инструмента для настройки проекций и не функционирующего как IG.
### Аргументы

- *bool* **slaves** - true, чтобы разрешить подключение новых Slave к Master после начала сессии; false - чтобы запретить это.

## bool isAllowExtraSlaves ( ) const

Возвращает значение, указывающее, могут ли новые Slave подключаться к Master после начала сессии. Это может использоваться, например, для подключения Slave, применяемого в качестве инструмента для настройки проекций и не функционирующего как IG.
### Возвращаемое значение

true, если новые Slave могут подключаться к Master после начала сессии; иначе false.
## void setViewOffset ( const Math:: vec3 & offset )

Задаёт новую позицию головы player на Master.
### Аргументы

- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **offset** - Новые координаты позиции головы player для задания.

## void setSyncViewOffset ( bool offset )

Включает синхронизацию смещения обзора для проекций через протокол UDP.
### Аргументы

- *bool* **offset** - true, чтобы включить синхронизацию; false - чтобы отключить её.

## bool isSyncViewOffset ( ) const

Возвращает значение, указывающее, включена ли синхронизация смещения обзора для проекций.
### Возвращаемое значение

true, если синхронизация смещения обзора для проекций включена; иначе false.
## void setSyncWorldLoad ( bool load )

Включает синхронизацию загрузки мира через протокол UDP.
### Аргументы

- *bool* **load** - true, чтобы включить синхронизацию; false - чтобы отключить её.

## bool isSyncWorldLoad ( ) const

Возвращает значение, указывающее, включена ли синхронизация загрузки мира.
### Возвращаемое значение

true, если синхронизация загрузки мира включена; иначе false.
## void setDefaultSyncNodes ( unsigned char nodes )

Задаёт новую маску, определяющую типы узлов, которые будут синхронизированы автоматически после загрузки мира. Эта маска может использоваться в целях оптимизации, ограничивая количество синхронизируемых узлов и тем самым снижая сетевую нагрузку. Например, можно ограничить автоматическую синхронизацию только глобальной водой и облаками:
```cpp
master->setDefaultSyncNodes(Syncker::Master::WATER_GLOBAL | Syncker::Master::CLOUD_LAYER);
```


### Аргументы

- *unsigned char* **nodes** - Маска, определяющая типы узлов, которые будут синхронизированы автоматически после загрузки мира.

## unsigned char getDefaultSyncNodes ( ) const

Возвращает текущую маску, определяющую типы узлов, которые будут синхронизированы автоматически после загрузки мира. Эта маска может использоваться в целях оптимизации, ограничивая количество синхронизируемых узлов и тем самым снижая сетевую нагрузку.
### Возвращаемое значение

Текущая маска, определяющая типы узлов, которые будут синхронизированы автоматически после загрузки мира.
## void loadWorld ( const char * name )

Загружает мир из указанного файла на Master и всех Slave. Syncker может автоматически синхронизировать текущий мир, но это работает следующим образом: Slave начинают загрузку нового мира только после того, как он полностью загружен на Master. Этот метод обеспечивает 2-кратное ускорение процесса загрузки мира, поскольку заставляет все узлы начинать загрузку мира почти одновременно.
### Аргументы

- *const char ** **name** - Путь к загружаемому файлу `*.world`.

## Ptr < Node > loadNode ( const char * path , unsigned char sync_mask = 0 , Math:: Mat4 & init_transform )

Загружает узел из указанного файла в мир на Master и всех Slave и размещает его с указанной начальной трансформацией. Это сетевой аналог метода [loadNode()](../../../../api/library/engine/class.world_cpp.md#loadNode_cstr_int_Node) класса *World*. По умолчанию загруженный узел не синхронизируется, что подходит для статических объектов во время выполнения и одновременно экономит производительность. Чтобы синхронизировать динамические объекты, следует задать подходящую маску синхронизации.
### Аргументы

- *const char ** **path** - Путь к файлу `*.node`.
- *unsigned char* **sync_mask** - Маска синхронизации, одно из значений [SYNC_MASK](#SYNC_MASK).
- *Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **init_transform** - Начальная трансформация узла.

### Возвращаемое значение

Загруженный узел или nullptr, если произошла ошибка.
## Ptr < Node > loadNode ( const char * path , unsigned char sync_mask = 0 )

Загружает узел из указанного файла в мир на Master и всех Slave и размещает его в начале координат со стандартной трансформацией. Это сетевой аналог метода [loadNode()](../../../../api/library/engine/class.world_cpp.md#loadNode_cstr_int_Node) класса *World*. По умолчанию загруженный узел не синхронизируется, что подходит для статических объектов во время выполнения и одновременно экономит производительность. Чтобы синхронизировать динамические объекты, следует задать подходящую маску синхронизации.
### Аргументы

- *const char ** **path** - Путь к файлу `*.node`.
- *unsigned char* **sync_mask** - Маска синхронизации, одно из значений [SYNC_MASK](#SYNC_MASK).

### Возвращаемое значение

Загруженный узел или nullptr, если произошла ошибка.
## Ptr < NodeReference > loadNodeReference ( const char * path , unsigned char sync_mask = 0 , Math:: Mat4 & init_transform )

Загружает ссылку на узел из указанного файла в мир на Master и всех Slave и размещает её с указанной начальной трансформацией. Это сетевой аналог [NodeReference class constructor](../../../../api/library/nodes/class.nodereference_cpp.md#NodeReference_constchar). По умолчанию загруженный узел не синхронизируется, что подходит для статических объектов во время выполнения и одновременно экономит производительность. Чтобы синхронизировать динамические объекты, следует задать подходящую маску синхронизации.
### Аргументы

- *const char ** **path** - Путь к файлу `*.node`.
- *unsigned char* **sync_mask** - Маска синхронизации, одно из значений [SYNC_MASK](#SYNC_MASK).
- *Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **init_transform** - Начальная трансформация узла.

### Возвращаемое значение

Экземпляр Node Reference, если он был успешно загружен; иначе nullptr.
## Ptr < NodeReference > loadNodeReference ( const char * path , unsigned char sync_mask = 0 )

Загружает ссылку на узел из указанного файла в мир на Master и всех Slave и размещает её в начале координат со стандартной трансформацией. Это сетевой аналог [NodeReference class constructor](../../../../api/library/nodes/class.nodereference_cpp.md#NodeReference_constchar). По умолчанию загруженный узел не синхронизируется, что подходит для статических объектов во время выполнения и одновременно экономит производительность. Чтобы синхронизировать динамические объекты, следует задать подходящую маску синхронизации.
### Аргументы

- *const char ** **path** - Путь к файлу `*.node`.
- *unsigned char* **sync_mask** - Маска синхронизации, одно из значений [SYNC_MASK](#SYNC_MASK).

### Возвращаемое значение

Экземпляр Node Reference, если он был успешно загружен; иначе nullptr.
## bool isNodeLoadedBySyncker ( const Ptr < Node > & node ) const

Возвращает значение, указывающее, был ли указанный узел загружен Syncker методом [*loadNode()*](#loadNode_cstr_uchar_Mat4_Node) или [*loadNodeReference()*](#loadNodeReference_cstr_uchar_Mat4_NodeReference).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **node** - Узел для проверки.

### Возвращаемое значение

true, если указанный узел был создан методом [*createNode()*](#createNode_Node_uchar_bool); иначе false.
## void * addCallback ( Master::CALLBACK_INDEX callback , Unigine:: CallbackBase * func )

Добавляет callback указанного типа. Функции callback могут использоваться для определения действий, выполняемых при отправке или получении пользовательских сообщений, а также при изменении настроек на Master или Slave. Сигнатура функции callback может быть одной из следующих:
```cpp
// для типа Syncker::Master::SESSION_STARTED
void callback_function_name(void);

// для типа Syncker::Master::SESSION_FINISHED
void callback_function_name(void);

// для типа Syncker::Master::SLAVE_CONNECTED
void callback_function_name(int slave_num);

// для типа Syncker::Master::SLAVE_DISCONNECTED
void callback_function_name(int slave_num);

// для типа Syncker::Master::MASTER_SETUP_CHANGED
void callback_function_name(void);

// для типа Syncker::Master::SLAVE_SETUP_CHANGED
void callback_function_name(int slave_num);

```


### Аргументы

- *Master::CALLBACK_INDEX* **callback** - Тип callback. Одно из следующих значений:

  - [SESSION_STARTED](#SESSION_STARTED)
  - [SESSION_CONTINUED](#SESSION_CONTINUED)
  - [SESSION_FINISHED](#SESSION_FINISHED)
  - [SLAVE_CONNECTED](#SLAVE_CONNECTED)
  - [SLAVE_DISCONNECTED](#SLAVE_DISCONNECTED)
  - [MASTER_SETUP_CHANGED](#MASTER_SETUP_CHANGED)
  - [SLAVE_SETUP_CHANGED](#SLAVE_SETUP_CHANGED)
- *Unigine::[CallbackBase](../../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **func** - Указатель на callback.

### Возвращаемое значение

Номер последнего добавленного callback указанного типа, если callback был успешно добавлен; иначе **-1**.
## bool removeCallback ( Master::CALLBACK_INDEX callback , void * func )

Удаляет указанный callback из списка callback указанного типа. Функции callback могут использоваться для определения действий, выполняемых при отправке или получении пользовательских сообщений, а также при изменении настроек на Master или Slave.
### Аргументы

- *Master::CALLBACK_INDEX* **callback** - Тип callback. Одно из следующих значений:

  - [SESSION_STARTED](#SESSION_STARTED)
  - [SESSION_CONTINUED](#SESSION_CONTINUED)
  - [SESSION_FINISHED](#SESSION_FINISHED)
  - [SLAVE_CONNECTED](#SLAVE_CONNECTED)
  - [SLAVE_DISCONNECTED](#SLAVE_DISCONNECTED)
  - [MASTER_SETUP_CHANGED](#MASTER_SETUP_CHANGED)
  - [SLAVE_SETUP_CHANGED](#SLAVE_SETUP_CHANGED)
- *void ** **func** - Указатель на callback.

### Возвращаемое значение

true, если callback позиции с указанным ID был успешно удалён; иначе false.
## void clearCallbacks ( Master::CALLBACK_INDEX callback )

Очищает все добавленные callback указанного типа. Функции callback могут использоваться для определения действий, выполняемых при отправке или получении пользовательских сообщений, а также при изменении настроек на Master или Slave.
### Аргументы

- *Master::CALLBACK_INDEX* **callback** - Тип callback. Одно из следующих значений:

  - [SESSION_STARTED](#SESSION_STARTED)
  - [SESSION_CONTINUED](#SESSION_CONTINUED)
  - [SESSION_FINISHED](#SESSION_FINISHED)
  - [SLAVE_CONNECTED](#SLAVE_CONNECTED)
  - [SLAVE_DISCONNECTED](#SLAVE_DISCONNECTED)
  - [MASTER_SETUP_CHANGED](#MASTER_SETUP_CHANGED)
  - [SLAVE_SETUP_CHANGED](#SLAVE_SETUP_CHANGED)

## int addMessageToBuffer ( const char * channel , const Ptr < Blob > & message )

Добавляет сообщение в буфер, которое будет получено [additional slaves](#setAllowExtraSlaves_int_void) сразу после подключения.
### Аргументы

- *const char ** **channel** - Имя канала. Несколько систем могут одновременно использовать сеть Syncker (например, [IG](../../../../ig/index.md) и приложение пользователя). Для удобства все сообщения отправляются и принимаются через именованные каналы.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Blob](../../../../api/library/common/class.blob_cpp.md)> &* **message** - Буфер, содержащий пользовательское сообщение.

### Возвращаемое значение

ID сообщения.
## int getNumBufferedMessages ( const char * channel ) const

Возвращает общее количество буферизованных сообщений.
### Аргументы

- *const char ** **channel** - Имя канала. Несколько систем могут одновременно использовать сеть Syncker (например, [IG](../../../../ig/index.md) и приложение пользователя). Для удобства все сообщения отправляются и принимаются через именованные каналы.

### Возвращаемое значение

Общее количество буферизованных сообщений.
## int getBufferedMessageID ( const char * channel , int index ) const

Возвращает ID буферизованного сообщения по его индексу.
### Аргументы

- *const char ** **channel** - Имя канала. Несколько систем могут одновременно использовать сеть Syncker (например, [IG](../../../../ig/index.md) и приложение пользователя). Для удобства все сообщения отправляются и принимаются через именованные каналы.
- *int* **index** - Номер индекса сообщения.

### Возвращаемое значение

ID сообщения.
## Ptr < Blob > getBufferedMessage ( const char * channel , int id ) const

Возвращает буфер, содержащий сообщение.
### Аргументы

- *const char ** **channel** - Имя канала. Несколько систем могут одновременно использовать сеть Syncker (например, [IG](../../../../ig/index.md) и приложение пользователя). Для удобства все сообщения отправляются и принимаются через именованные каналы.
- *int* **id** - ID сообщения.

### Возвращаемое значение

Буфер, содержащий пользовательское сообщение.
## void removeBufferedMessage ( const char * channel , int id )

Удаляет указанное сообщение из буфера.
### Аргументы

- *const char ** **channel** - Имя канала. Несколько систем могут одновременно использовать сеть Syncker (например, [IG](../../../../ig/index.md) и приложение пользователя). Для удобства все сообщения отправляются и принимаются через именованные каналы.
- *int* **id** - ID сообщения.

## void clearBufferedMessages ( const char * channel )

Удаляет все сообщения из буфера.
### Аргументы

- *const char ** **channel** - Имя канала. Несколько систем могут одновременно использовать сеть Syncker (например, [IG](../../../../ig/index.md) и приложение пользователя). Для удобства все сообщения отправляются и принимаются через именованные каналы.

## const char * getSlaveComputerName ( int num ) const

Возвращает имя компьютера slave с указанным индексом. Если для компьютера slave не задано имя с помощью аргумента запуска `-computer_name`, возвращается системное имя.
### Аргументы

- *int* **num** - Индекс slave.

### Возвращаемое значение

Имя компьютера slave.
## Ptr < Node > cloneNode ( const Ptr < Node > & node , unsigned char sync_mask = 0 )

Клонирует указанный узел и синхронизирует его клонирование на всех Slave.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **node** - Узел для клонирования.
- *unsigned char* **sync_mask** - Маска синхронизации, одно из значений [SYNC_MASK](#SYNC_MASK).

### Возвращаемое значение

Клонированный узел.
## Ptr < Node > cloneNode ( const Ptr < Node > & node , unsigned char sync_mask , const Math:: Mat4 & init_transform )

Клонирует указанный узел с заданной трансформацией и синхронизирует его клонирование на всех Slave.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **node** - Узел для клонирования.
- *unsigned char* **sync_mask** - Маска синхронизации, одно из значений [SYNC_MASK](#SYNC_MASK).
- *const  Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **init_transform** - Позиция и поворот клонированного узла (если не указано, используется трансформация исходного узла).

### Возвращаемое значение

Клонированный узел.
