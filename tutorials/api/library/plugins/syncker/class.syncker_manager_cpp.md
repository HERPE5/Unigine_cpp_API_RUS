# Unigine::Plugins::Syncker::Manager Class (CPP)

**Header:** #include <plugins/Unigine/Syncker/UnigineSyncker.h>

> **Notice:** Этот класс является одиночкой (singleton).


> **Notice:** Плагин [Syncker](../../../../code/plugins/syncker/index.md) должен быть загружен.


Этот класс представляет интерфейс менеджера Syncker, используемый для инициализации и уничтожения Syncker в главных (master) и подчинённых (slave) приложениях.


## Manager Class

### Перечисления

## SPIDER_VISION_EASYBLEND_SYNC_TYPE

| Name | Description |
|---|---|
| **NETWORK** = 0 | Экземпляр отправляет по сети полные данные [EasyBlend](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#easyblend): меш искажения, имя исходного файла, все соответствующие параметры EasyBlend и любые дополнительные связанные метаданные. Используйте этот режим, когда экземпляр должен выступать источником полных данных конфигурации EasyBlend. |
| **LOAD_FROM_LOCAL_STORAGE** = 1 | Экземпляр отправляет только ссылку (обычно путь к файлу) на файл конфигурации [EasyBlend](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#easyblend). Ожидается, что принимающие экземпляры перезагрузят необходимые данные EasyBlend из своего локального хранилища. Это снижает сетевой трафик, поскольку передаётся только путь к файлу, а не полные данные конфигурации. |

### Методы класса

## void setDebugWindow ( bool window )

Задаёт новое значение, указывающее, включено ли отладочное окно syncker.
### Аргументы

- *bool* **window** - Установите **true**, чтобы включить отладочное окно Syncker; **false** - чтобы отключить его.

## bool isDebugWindow () const

Возвращает текущее значение, указывающее, включено ли отладочное окно syncker.
### Возвращаемое значение

**true**, если отладочное окно Syncker включено; иначе **false**.
## Syncker * getSyncker () const

Возвращает текущий [Syncker interface](../../../../api/library/plugins/syncker/class.syncker_syncker_cpp.md).
### Возвращаемое значение

Текущий указатель на [Syncker interface](../../../../api/library/plugins/syncker/class.syncker_syncker_cpp.md). Это базовый класс для Master и Slave.
## bool isSynckerInitialized () const

Возвращает текущее значение, указывающее, был ли инициализирован Syncker (Master или Slave).
### Возвращаемое значение

**true**, если Syncker (master или slave) был инициализирован; иначе **false**.
## Slave * getSlave () const

Возвращает текущий [Slave interface](../../../../api/library/plugins/syncker/class.syncker_slave_cpp.md).
### Возвращаемое значение

Текущий указатель на интерфейс Slave.
## bool isSlaveInitialized () const

Возвращает текущее значение, указывающее, был ли инициализирован Slave.
### Возвращаемое значение

**true**, если Slave был инициализирован; иначе **false**.
## Master * getMaster () const

Возвращает текущий [Master interface](../../../../api/library/plugins/syncker/class.syncker_master_cpp.md).
### Возвращаемое значение

Текущий указатель на [Master interface](../../../../api/library/plugins/syncker/class.syncker_master_cpp.md).
## bool isMasterInitialized () const

Возвращает текущее значение, указывающее, был ли инициализирован Master.
### Возвращаемое значение

**true**, если Master был инициализирован; иначе **false**.
## bool getArgAllowExtraSlaves () const

Возвращает текущее значение, указывающее, могут ли подключаться дополнительные Slave после начала сессии, заданное аргументом командной строки "[-sync_allow_extra_slaves](../../../../code/plugins/syncker/options.md#sync_allow_extra_slaves)".
> **Notice:** Доступно только для Slave.

### Возвращаемое значение

**true**, если дополнительные Slave могут подключаться после начала сессии; иначе **false**.
## int getArgUdpSlavePort () const

Возвращает текущий порт UDP, используемый Slave, заданный аргументом командной строки "[-sync_slave_port](../../../../code/plugins/syncker/options.md#sync_slave_port)".
> **Notice:** Доступно только для Slave.

### Возвращаемое значение

Текущий порт UDP, используемый Slave. Значение по умолчанию — 0 (любой доступный неиспользуемый порт).
## int getArgUdpPort () const

Возвращает текущее значение порта UDP, заданное аргументом командной строки "[-sync_port](../../../../code/plugins/syncker/options.md#sync_port)".
### Возвращаемое значение

Текущий номер порта UDP. Значение по умолчанию — 8890.
## const char * getArgMasterAddress () const

Возвращает текущий IP-адрес Master, заданный аргументом командной строки "[-sync_master_address](../../../../code/plugins/syncker/options.md#sync_master_address)".
> **Notice:** Доступно только для Slave.

### Возвращаемое значение

Текущий IP-адрес Master.
## const char * getArgMulticastAddress () const

Возвращает текущий multicast-адрес Master, заданный аргументом командной строки "[-sync_multicast_address](../../../../code/plugins/syncker/options.md#sync_multicast_address)".
### Возвращаемое значение

Текущий multicast-адрес Master. Значение по умолчанию — 239.0.0.1
## const char * getArgBroadcastAddress () const

Возвращает текущий broadcast-адрес Master, заданный аргументом командной строки "[-sync_broadcast_address](../../../../code/plugins/syncker/options.md#sync_broadcast_address)".
### Возвращаемое значение

Текущий broadcast-адрес Master.
## int getArgPeersCount () const

Возвращает текущее количество узлов, заданное аргументом командной строки "[-sync_count](../../../../code/plugins/syncker/options.md#sync_count)".
### Возвращаемое значение

Текущее количество узлов. Значение по умолчанию — 1. Количество узлов включает всех Slave в сети + Master.
## Syncker::SWAP_SYNC_MODE getArgSwapSyncMode () const

Возвращает текущий режим синхронизации swap, заданный аргументом командной строки `-sync_swap`.
### Возвращаемое значение

Текущий режим синхронизации swap.
## Syncker::ADDRESSING_METHOD getArgAddressingMethod () const

Возвращает текущее значение режима адресации, заданное аргументом командной строки "[-sync_method](../../../../code/plugins/syncker/options.md#sync_method)".
### Возвращаемое значение

Текущий режим адресации: одно из значений перечисления [ADDRESSING_METHOD](../../../../api/library/plugins/syncker/class.syncker_syncker_cpp.md#ADDRESSING_METHOD).
## bool getArgIsMaster () const

Возвращает текущее значение, указывающее, равен ли 1 аргумент командной строки "[-sync_master](../../../../code/plugins/syncker/options.md#sync_master)".
### Возвращаемое значение

**true**, если аргумент командной строки "-sync_master" равен 1; иначе **false**.
## bool getArgInitSyncker () const

Возвращает текущее значение, указывающее, равен ли 1 аргумент командной строки "[-sync_init](../../../../code/plugins/syncker/options.md#sync_master)".
### Возвращаемое значение

**true**, если аргумент командной строки "-sync_init" равен 1; иначе **false**.
## void setEasyblendSyncType ( Manager::SPIDER_VISION_EASYBLEND_SYNC_TYPE type )

Задаёт новую стратегию синхронизации [EasyBlend](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#easyblend), используемую этим экземпляром при отправке обновлений другим устройствам.
### Аргументы

- *Manager::SPIDER_VISION_EASYBLEND_SYNC_TYPE* **type** -

## Manager::SPIDER_VISION_EASYBLEND_SYNC_TYPE getEasyblendSyncType () const

Возвращает текущую стратегию синхронизации [EasyBlend](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#easyblend), используемую этим экземпляром при отправке обновлений другим устройствам.
### Возвращаемое значение

Текущая
---

## Master * initMaster ( )

Инициализирует Syncker как приложение Master, используя значения, заданные через [command-line arguments](../../../../code/plugins/syncker/options.md).
### Возвращаемое значение

Указатель на [Master interface](../../../../api/library/plugins/syncker/class.syncker_master_cpp.md).
## Master * initMasterBroadcast ( int peers_count , const char * broadcast_address , unsigned short udp_port , Syncker::SWAP_SYNC_MODE swap_mode = Syncker.SWAP_SYNC_MODE.DEFAULT )

Инициализирует Syncker как приложение Master с включённым [broadcast mode](../../../../code/plugins/syncker/index.md#addressing_broadcast).
> **Notice:** Slave также должны быть [initialized with broadcast mode enabled](#initSlaveBroadcast_ushort_int_Slave).

### Аргументы

- *int* **peers_count** - Общее количество узлов Syncker в сети (включая сам Master). Аналогично заданию аргумента командной строки [-sync_count](../../../../code/plugins/syncker/options.md#sync_count).
- *const char ** **broadcast_address** - Используемый broadcast-адрес. Аналогично заданию аргумента командной строки [-sync_broadcast_address](../../../../code/plugins/syncker/options.md#sync_broadcast_address).
- *unsigned short* **udp_port** - Используемый порт UDP. Аналогично заданию аргумента командной строки [-sync_port](../../../../code/plugins/syncker/options.md#sync_port).
- *Syncker::SWAP_SYNC_MODE* **swap_mode** - Режим синхронизации swap, используемый Syncker. Аналогично заданию аргумента командной строки [-sync_swap](../../../../code/plugins/syncker/options.md#sync_swap).

### Возвращаемое значение

Указатель на [Master interface](../../../../api/library/plugins/syncker/class.syncker_master_cpp.md).
## Master * initMasterMulticast ( int peers_count , const char * multicast_address , unsigned short udp_port , Syncker::SWAP_SYNC_MODE swap_mode = Syncker.SWAP_SYNC_MODE.DEFAULT )

Инициализирует Syncker как приложение Master с включённым [multicast mode](../../../../code/plugins/syncker/index.md#addressing_multicast).
### Аргументы

- *int* **peers_count** - Общее количество узлов Syncker в сети (включая сам Master). Аналогично заданию аргумента командной строки [-sync_count](../../../../code/plugins/syncker/options.md#sync_count).
- *const char ** **multicast_address** - Используемый multicast-адрес. Аналогично заданию аргумента командной строки [-sync_multicast_address](../../../../code/plugins/syncker/options.md#sync_multicast_address).
- *unsigned short* **udp_port** - Используемый порт UDP. Аналогично заданию аргумента командной строки [-sync_port](../../../../code/plugins/syncker/options.md#sync_port).
- *Syncker::SWAP_SYNC_MODE* **swap_mode** - Режим синхронизации swap, используемый Syncker. Аналогично заданию аргумента командной строки [-sync_swap](../../../../code/plugins/syncker/options.md#sync_swap).

### Возвращаемое значение

Указатель на [Master interface](../../../../api/library/plugins/syncker/class.syncker_master_cpp.md).
## Master * initMasterUnicast ( int peers_count , unsigned short udp_port , Syncker::SWAP_SYNC_MODE swap_mode = Syncker.SWAP_SYNC_MODE.DEFAULT )

Инициализирует Syncker как приложение Master с включённым [unicast mode](../../../../code/plugins/syncker/index.md#addressing_unicast).
> **Notice:** Slave также должны быть [initialized with unicast mode enabled](#initSlaveUnicast_ushort_ushort_int_Slave).

### Аргументы

- *int* **peers_count** - Общее количество узлов Syncker в сети (включая сам Master). Аналогично заданию аргумента командной строки [-sync_count](../../../../code/plugins/syncker/options.md#sync_count).
- *unsigned short* **udp_port** - Используемый порт UDP. Аналогично заданию аргумента командной строки [-sync_port](../../../../code/plugins/syncker/options.md#sync_port).
- *Syncker::SWAP_SYNC_MODE* **swap_mode** - Режим синхронизации swap, используемый Syncker. Аналогично заданию аргумента командной строки [-sync_swap](../../../../code/plugins/syncker/options.md#sync_swap).

### Возвращаемое значение

Указатель на [Master interface](../../../../api/library/plugins/syncker/class.syncker_master_cpp.md).
## Slave * initSlave ( )

Инициализирует Syncker как приложение Slave, используя значения, заданные через [command-line arguments](../../../../code/plugins/syncker/options.md).
### Возвращаемое значение

Указатель на [Slave interface](../../../../api/library/plugins/syncker/class.syncker_slave_cpp.md).
## void destroySyncker ( )

Выполняет завершение работы и уничтожает Syncker.
> **Notice:** Вызывается автоматически при выгрузке плагина.


## Slave * initSlaveBroadcast ( unsigned short udp_port , Syncker::SWAP_SYNC_MODE swap_mode = Syncker.SWAP_SYNC_MODE.DEFAULT )

Инициализирует Syncker как приложение Slave с включённым [broadcast mode](../../../../code/plugins/syncker/index.md#addressing_broadcast). IP-адрес Master будет определён автоматически.
> **Notice:** Master также должен быть инициализирован с включённым режимом broadcast.

### Аргументы

- *unsigned short* **udp_port** - Используемый порт UDP. Аналогично заданию аргумента командной строки [-sync_port](../../../../code/plugins/syncker/options.md#sync_port).
- *Syncker::SWAP_SYNC_MODE* **swap_mode** - Режим синхронизации swap, используемый Syncker. Аналогично заданию аргумента командной строки [-sync_swap](../../../../code/plugins/syncker/options.md#sync_swap).

### Возвращаемое значение

Указатель на [slave interface](../../../../api/library/plugins/syncker/class.syncker_slave_cpp.md).
## Slave * initSlaveBroadcast ( const char * master_address , unsigned short udp_port , Syncker::SWAP_SYNC_MODE swap_mode = Syncker.SWAP_SYNC_MODE.DEFAULT )

Инициализирует Syncker как приложение Slave с указанными параметрами и включённым [broadcast mode](../../../../code/plugins/syncker/index.md#addressing_broadcast). IP-адрес Master задаётся явно.
> **Notice:** Master также должен быть инициализирован с включённым режимом broadcast.

### Аргументы

- *const char ** **master_address** - Используемый IP-адрес Master. Аналогично заданию аргумента командной строки [-sync_master_address](../../../../code/plugins/syncker/options.md#sync_master_address).
- *unsigned short* **udp_port** - Используемый порт UDP. Аналогично заданию аргумента командной строки [-sync_port](../../../../code/plugins/syncker/options.md#sync_port).
- *Syncker::SWAP_SYNC_MODE* **swap_mode** - Режим синхронизации swap, используемый Syncker. Аналогично заданию аргумента командной строки [-sync_swap](../../../../code/plugins/syncker/options.md#sync_swap).

### Возвращаемое значение

Указатель на [slave interface](../../../../api/library/plugins/syncker/class.syncker_slave_cpp.md).
## Slave * initSlaveMulticast ( const char * multicast_address , unsigned short udp_port , Syncker::SWAP_SYNC_MODE swap_mode = Syncker.SWAP_SYNC_MODE.DEFAULT )

Инициализирует Syncker как приложение Slave с указанными параметрами и включённым [multicast mode](../../../../code/plugins/syncker/index.md#addressing_multicast). IP-адрес Master будет определён автоматически.
> **Notice:** Master также должен быть инициализирован с включённым режимом broadcast.

### Аргументы

- *const char ** **multicast_address** - Используемый multicast-адрес. Аналогично заданию аргумента командной строки [-sync_multicast_address](../../../../code/plugins/syncker/options.md#sync_multicast_address).
- *unsigned short* **udp_port** - Используемый порт UDP. Аналогично заданию аргумента командной строки [-sync_port](../../../../code/plugins/syncker/options.md#sync_port).
- *Syncker::SWAP_SYNC_MODE* **swap_mode** - Режим синхронизации swap, используемый Syncker. Аналогично заданию аргумента командной строки [-sync_swap](../../../../code/plugins/syncker/options.md#sync_swap).

### Возвращаемое значение

Указатель на [slave interface](../../../../api/library/plugins/syncker/class.syncker_slave_cpp.md).
## Slave * initSlaveMulticast ( const char * master_address , const char * multicast_address , unsigned short udp_port , Syncker::SWAP_SYNC_MODE swap_mode = Syncker.SWAP_SYNC_MODE.DEFAULT )

Инициализирует Syncker как приложение Slave с указанными параметрами и включённым [multicast mode](../../../../code/plugins/syncker/index.md#addressing_multicast). IP-адрес Master задаётся явно.
> **Notice:** Master также должен быть инициализирован с включённым режимом broadcast.

### Аргументы

- *const char ** **master_address** - Используемый IP-адрес Master. Аналогично заданию аргумента командной строки [-sync_master_address](../../../../code/plugins/syncker/options.md#sync_master_address).
- *const char ** **multicast_address** - Используемый multicast-адрес. Аналогично заданию аргумента командной строки [-sync_multicast_address](../../../../code/plugins/syncker/options.md#sync_multicast_address).
- *unsigned short* **udp_port** - Используемый порт UDP. Аналогично заданию аргумента командной строки [-sync_port](../../../../code/plugins/syncker/options.md#sync_port).
- *Syncker::SWAP_SYNC_MODE* **swap_mode** - Режим синхронизации swap, используемый Syncker. Аналогично заданию аргумента командной строки [-sync_swap](../../../../code/plugins/syncker/options.md#sync_swap).

### Возвращаемое значение

Указатель на [slave interface](../../../../api/library/plugins/syncker/class.syncker_slave_cpp.md).
## Slave * initSlaveUnicast ( unsigned short master_udp_port , unsigned short slave_udp_port = 0 , Syncker::SWAP_SYNC_MODE swap_mode = Syncker.SWAP_SYNC_MODE.DEFAULT )

Инициализирует Syncker как приложение Slave с указанными параметрами и включённым [unicast mode](../../../../code/plugins/syncker/index.md#addressing_unicast). IP-адрес Master будет определён автоматически.
> **Notice:** Master также должен быть инициализирован с включённым режимом broadcast.

### Аргументы

- *unsigned short* **master_udp_port** - Используемый порт UDP для Master.
- *unsigned short* **slave_udp_port** - Используемый порт UDP для Slave. Аналогично заданию аргумента командной строки [-sync_slave_port](../../../../code/plugins/syncker/options.md#sync_slave_port).
- *Syncker::SWAP_SYNC_MODE* **swap_mode** - Режим синхронизации swap, используемый Syncker. Аналогично заданию аргумента командной строки [-sync_swap](../../../../code/plugins/syncker/options.md#sync_swap).

### Возвращаемое значение

Указатель на [slave interface](../../../../api/library/plugins/syncker/class.syncker_slave_cpp.md).
## Slave * initSlaveUnicast ( const char * master_address , unsigned short master_udp_port , unsigned short slave_udp_port = 0 , Syncker::SWAP_SYNC_MODE swap_mode = Syncker.SWAP_SYNC_MODE.DEFAULT )

Инициализирует Syncker как приложение Slave с указанными параметрами и включённым [unicast mode](../../../../code/plugins/syncker/index.md#addressing_unicast). IP-адрес Master задаётся явно.
> **Notice:** Master также должен быть инициализирован с включённым режимом broadcast.

### Аргументы

- *const char ** **master_address** - Используемый IP-адрес Master. Аналогично заданию аргумента командной строки [-sync_master_address](../../../../code/plugins/syncker/options.md#sync_master_address).
- *unsigned short* **master_udp_port** - Используемый порт UDP для Master.
- *unsigned short* **slave_udp_port** - Используемый порт UDP для Slave. Аналогично заданию аргумента командной строки [-sync_slave_port](../../../../code/plugins/syncker/options.md#sync_slave_port).
- *Syncker::SWAP_SYNC_MODE* **swap_mode** - Режим синхронизации swap, используемый Syncker. Аналогично заданию аргумента командной строки [-sync_swap](../../../../code/plugins/syncker/options.md#sync_swap).

### Возвращаемое значение

Указатель на [slave interface](../../../../api/library/plugins/syncker/class.syncker_slave_cpp.md).
## Syncker * initSyncker ( )

Инициализирует Syncker как приложение Master или Slave в зависимости от значений, заданных через [command-line arguments](../../../../code/plugins/syncker/options.md).
### Возвращаемое значение

Указатель на [syncker interface](../../../../api/library/plugins/syncker/class.syncker_syncker_cpp.md). Это базовый класс для Master и Slave.
## Manager * get ( )

Возвращает [Manager interface](../../../../api/library/plugins/syncker/class.syncker_manager_cpp.md).
### Возвращаемое значение

Указатель на [manager interface](../../../../api/library/plugins/syncker/class.syncker_manager_cpp.md).
