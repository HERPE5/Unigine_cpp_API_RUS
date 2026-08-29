# Unigine::Plugins::Syncker::Slave Class (CPP)

**Header:** #include <plugins/Unigine/Syncker/UnigineSyncker.h>


Этот класс представляет интерфейс slave Syncker.


> **Notice:** Плагин [Syncker](../../../../code/plugins/syncker/index.md) должен быть загружен.


## Slave Class

### Перечисления

## CALLBACK_INDEX

| Name | Description |
|---|---|
| **SESSION_STARTED** = 0 | Функция callback, вызываемая при начале сессии. Сигнатура callback: ```text callback_function_name(void) ``` |
| **SESSION_FINISHED** = 1 | Функция callback, вызываемая при закрытии сессии. Сигнатура callback: ```text callback_function_name(void) ``` |
| **MASTER_CONNECTED** = 2 | Функция callback, вызываемая при успешном подключении к Master. Сигнатура callback: ```text callback_function_name(void) ``` |
| **MASTER_DISCONNECTED** = 3 | Функция callback, вызываемая при отключении от Master. Причина отключения задаётся в строковом формате ("disconnected by master", "timeout" и т.д.). Сигнатура callback: ```text callback_function_name(const char *reason) ``` |
| **NODE_LOADED** = 4 | Функция callback, вызываемая при создании узла Master на Slave через *loadNode() / loadNodeReference() / createNode()*. Сигнатура callback: ```text callback_function_name(const NodePtr &node) ``` |
| **NODE_CLONED** = 5 | Функция callback, вызываемая при клонировании узла Master на Slave через *cloneNode()*. Сигнатура callback: ```text callback_function_name(const NodePtr &node) ``` |

## SKIP_FLAGS

Флаги, определяющие данные от Master, которые должны игнорироваться Slave.
| Name | Description |
|---|---|
| **WORLD_LOAD** = 1 | Загрузка миров. |
| **GAME** = 1 << 1 | Класс Game (время и скорость), для частиц — ifps и seed. |
| **PLAYER** = 1 << 2 | Синхронизация текущей камеры Master (каждый кадр). |
| **RENDER** = 1 << 3 | Настройки рендеринга и пост-эффектов. |
| **NODES** = 1 << 4 | Узлы. |
| **MATERIALS** = 1 << 5 | Материалы. |
| **SET_PLAYER** = 1 << 6 | Игнорирование вызовов [setCustomPlayer()](../../../../api/library/plugins/syncker/class.syncker_master_cpp.md#setCustomPlayer_cstr_Player_void) от Master. |
| **VIEW_OFFSET** = 1 << 7 | Изменение параметров смещения обзора. |
| **USER_DATA** = 1 << 8 | Обработка пользовательских пакетов, отправленных через [*sendMessage()*](../../../../api/library/plugins/syncker/class.syncker_syncker_cpp.md#sendMessage_cstr_Blob_int_bool). |
| **NODE_LOAD** = 1 << 9 | Загрузка узлов из файлов `*.node`. |
| **NODEREF_LOAD** = 1 << 10 | Загрузка ссылок на узлы из файлов `*.node`. |
| **NODE_CREATE** = 1 << 11 | Создание узлов. |
| **NODE_ID_REGISTER** = 1 << 12 | Связи между динамическими узлами Master и Slave (по ID), созданные через *loadNode()*, *createNode()* и т.д. |
| **NODE_DELETE** = 1 << 13 | Удаление узлов. |
| **RUN_CONSOLE** = 1 << 14 | Выполнение консольных команд. |
| **PROJECTIONS** = 1 << 15 | Конфигурация проекций. |
| **NODE_CLONE** = 1 << 16 | Клонирование узлов. |

### Методы класса

---

## int getMasterNodeID ( int slave_node_id )

Возвращает ID динамического узла на Master по его локальному ID на Slave. Slave не создаёт точную копию узла, созданного на Master, их ID не совпадают. Таким образом, зная ID локальной копии узла, созданного на Master, можно легко найти его оригинал на Master. Это может использоваться в [user messages](../../../../api/library/plugins/syncker/class.syncker_syncker_cpp.md#sendMessage_cstr_Blob_int_bool), когда нужно применить определённые изменения к исходному узлу на Master.
### Аргументы

- *int* **slave_node_id** - ID узла на Slave.

### Возвращаемое значение

ID узла на Master.
## int getSlaveNodeID ( int master_node_id )

Возвращает локальный ID динамического узла на Slave по его ID на Master. Slave не создаёт точную копию узла, созданного на Master, их ID не совпадают. Таким образом, если узел был создан на Master, а затем был вызван метод [*Syncker::Master::createNode()*](../../../../api/library/plugins/syncker/class.syncker_master_cpp.md#createNode_Node_uchar_bool), можно легко найти его копию на текущем Slave. Это может использоваться в [user messages](../../../../api/library/plugins/syncker/class.syncker_syncker_cpp.md#sendMessage_cstr_Blob_int_bool), когда нужно применить определённые изменения к копии узла на Slave, созданного на Master.
### Аргументы

- *int* **master_node_id** - ID узла на Master.

### Возвращаемое значение

ID узла на Slave.
## void addSyncNode ( const Ptr < Node > & node , int master_node_id )

Включает синхронизацию параметров указанного узла через протокол UDP.
> **Notice:** Узлы сцены не синхронизируются по умолчанию, этот метод используется для добавления конкретного узла в очередь синхронизации.


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **node** - Узел для синхронизации.
- *int* **master_node_id** - ID узла на Master.

## void addSyncNodeID ( int slave_node_id , int master_node_id )

Включает синхронизацию параметров указанного узла через протокол UDP.
> **Notice:** Узлы сцены не синхронизируются по умолчанию, этот метод используется для добавления конкретного узла (по его id) в очередь синхронизации.


### Аргументы

- *int* **slave_node_id** - ID узла на Slave.
- *int* **master_node_id** - ID узла на Master.

## bool removeSyncNode ( const Ptr < Node > & node )

Удаляет указанный узел из очереди синхронизации.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **node** - Узел для удаления.

### Возвращаемое значение

true, если узел был успешно удалён из очереди синхронизации; иначе false.
## bool removeSyncNodeID ( int slave_node_id )

Удаляет узел с указанным номером из очереди синхронизации.
### Аргументы

- *int* **slave_node_id** - Номер узла в очереди синхронизации.

### Возвращаемое значение

true, если узел был успешно удалён из очереди синхронизации; иначе false.
## long long getID ( ) const

Возвращает текущий ID Slave.
### Возвращаемое значение

ID slave, состоящий из: IP-адреса (32 бита) + номера порта (16 бит).
## void setSkipFlags ( int flags )

Задаёт [skip flags](#SKIP_FLAGS), позволяющие игнорировать определённую информацию от Master.
### Аргументы

- *int* **flags** - Используемая комбинация [skip flags](#SKIP_FLAGS), например: ```cpp slave->setSkipFlags(GAME | WORLD_LOAD | USER_DATA); ```

## int getSkipFlags ( ) const

Возвращает текущую комбинацию [skip flags](#SKIP_FLAGS), позволяющих игнорировать определённую информацию от Master.
### Возвращаемое значение

Комбинация используемых в данный момент [skip flags](#SKIP_FLAGS).
## void * addCallback ( Slave::CALLBACK_INDEX callback , Unigine:: CallbackBase * func )

Добавляет callback указанного типа. Функции callback могут использоваться для определения действий, выполняемых при отправке или получении пользовательских сообщений, а также при изменении настроек на Master или Slave. Сигнатура функции callback может быть одной из следующих:
```cpp
// для типа Syncker::Slave::SESSION_STARTED
void callback_function_name(void);

// для типа Syncker::Slave::SESSION_FINISHED
void callback_function_name(void);

// для типа Syncker::Slave::MASTER_CONNECTED
void callback_function_name(void);

// для типа Syncker::Slave::MASTER_DISCONNECTED
void callback_function_name(const char *reason);

// для типа Syncker::Slave::NODE_LOADED
void callback_function_name(const NodePtr &node);

// для типа Syncker::Slave::NODE_CLONED
void callback_function_name(const NodePtr &node);

```


### Аргументы

- *Slave::CALLBACK_INDEX* **callback** - Тип callback. Одно из следующих значений:

  - [SESSION_STARTED](#SESSION_STARTED)
  - [SESSION_FINISHED](#SESSION_FINISHED)
  - [MASTER_CONNECTED](#MASTER_CONNECTED)
  - [MASTER_DISCONNECTED](#MASTER_DISCONNECTED)
  - [NODE_LOADED](#NODE_LOADED)
  - [NODE_CLONED](#NODE_CLONED)
- *Unigine::[CallbackBase](../../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **func** - Указатель на callback.

### Возвращаемое значение

Номер последнего добавленного callback указанного типа, если callback был успешно добавлен; иначе **-1**.
## bool removeCallback ( Slave::CALLBACK_INDEX callback , void * func )

Удаляет указанный callback из списка callback указанного типа. Функции callback могут использоваться для определения действий, выполняемых при отправке или получении пользовательских сообщений, а также при изменении настроек на Master или Slave.
### Аргументы

- *Slave::CALLBACK_INDEX* **callback** - Тип callback. Одно из следующих значений:

  - [SESSION_STARTED](#SESSION_STARTED)
  - [SESSION_FINISHED](#SESSION_FINISHED)
  - [MASTER_CONNECTED](#MASTER_CONNECTED)
  - [MASTER_DISCONNECTED](#MASTER_DISCONNECTED)
  - [NODE_LOADED](#NODE_LOADED)
  - [NODE_CLONED](#NODE_CLONED)
- *void ** **func** - Указатель на callback.

### Возвращаемое значение

true, если callback позиции с указанным ID был успешно удалён; иначе false.
## void clearCallbacks ( Slave::CALLBACK_INDEX callback )

Очищает все добавленные callback указанного типа. Функции callback могут использоваться для определения действий, выполняемых при отправке или получении пользовательских сообщений, а также при изменении настроек на Master или Slave.
### Аргументы

- *Slave::CALLBACK_INDEX* **callback** - Тип callback. Одно из следующих значений:

  - [SESSION_STARTED](#SESSION_STARTED)
  - [SESSION_FINISHED](#SESSION_FINISHED)
  - [MASTER_CONNECTED](#MASTER_CONNECTED)
  - [MASTER_DISCONNECTED](#MASTER_DISCONNECTED)
  - [NODE_LOADED](#NODE_LOADED)
  - [NODE_CLONED](#NODE_CLONED)

## void reconnect ( )

Позволяет отключённому компьютеру slave повторно подключиться к компьютеру master.
> **Notice:** Для обеспечения корректной работы этого метода [setAllowExtraSlaves()](../../../../api/library/plugins/syncker/class.syncker_master_cpp.md#setAllowExtraSlaves_int_void) должен быть задан равным false.
