# Unigine::Plugins::DataBridge::NetworkManager Class (CPP)

**Header:** #include <plugins/Unigine/DataBridge/UnigineDataBridge.h>


Этот класс управляет сетью DataBridge.


## NetworkManager Class

### Методы класса

## double getIFps () const

Возвращает текущую длительность последнего кадра. Этот метод точнее, чем аналогичный метод класса [Game](../../../../api/library/engine/class.game_cpp.md#getIFps_float), и возвращает значение двойной точности.
### Возвращаемое значение

Текущая длительность предыдущего кадра, в секундах.
## double getTime () const

Возвращает текущее время кадра сервера, в секундах (даже при вызове с компьютера клиента). Это время последней операции смены буферов (т.е. начало следующего кадра). Это значение точнее, чем аналогичное значение класса [Game](../../../../api/library/engine/class.game_cpp.md#Time).
### Возвращаемое значение

Текущее время кадра сервера, в секундах
## bool isHttpServerInitialized () const

Возвращает текущее значение
### Возвращаемое значение

**true**, если включено; иначе **false**.
---

## Server * initServerBroadcast ( const char * broadcast_address , unsigned short udp_port )

Инициализирует приложение как сервер с включённым [broadcast mode](../../../../code/plugins/syncker/index.md#addressing_broadcast). Клиенты должны быть инициализированы с тем же включённым режимом.
### Аргументы

- *const char ** **broadcast_address** - Широковещательный адрес сервера, используемый для отправки данных клиентам по сети.
- *unsigned short* **udp_port** - Используемый UDP-порт.

### Возвращаемое значение

Указатель на интерфейс сервера.
## Server * initServerMulticast ( const char * multicast_address , unsigned short udp_port )

Инициализирует приложение как сервер с включённым [multicast mode](../../../../code/plugins/syncker/index.md#addressing_multicast). Клиенты должны быть инициализированы с тем же включённым режимом.
### Аргументы

- *const char ** **multicast_address** - Multicast-адрес сервера, используемый для отправки данных клиентам по сети.
- *unsigned short* **udp_port** - Используемый UDP-порт.

### Возвращаемое значение

Указатель на интерфейс сервера.
## Server * initServerUnicast ( unsigned short udp_port )

Инициализирует приложение как сервер с включённым [unicast mode](../../../../code/plugins/syncker/index.md#addressing_unicast). Клиенты должны быть инициализированы с тем же включённым режимом.
### Аргументы

- *unsigned short* **udp_port** - Используемый UDP-порт.

### Возвращаемое значение

Указатель на интерфейс сервера.
## Client * initClientBroadcast ( unsigned short udp_port )

Инициализирует приложение как клиента с включённым [broadcast mode](../../../../code/plugins/syncker/index.md#addressing_broadcast). IP-адрес сервера будет определён автоматически. Сервер должен быть инициализирован с тем же режимом.
### Аргументы

- *unsigned short* **udp_port** - Используемый UDP-порт.

### Возвращаемое значение

Указатель на интерфейс клиента.
## Client * initClientBroadcast ( const char * server_address , unsigned short udp_port )

Инициализирует приложение как клиента с включённым [broadcast mode](../../../../code/plugins/syncker/index.md#addressing_broadcast). IP-адрес сервера указывается явно. Сервер должен быть инициализирован с тем же режимом.
### Аргументы

- *const char ** **server_address** - Используемый IP-адрес сервера.
- *unsigned short* **udp_port** - Используемый UDP-порт.

### Возвращаемое значение

Указатель на интерфейс клиента.
## Client * initClientMulticast ( const char * multicast_address , unsigned short udp_port )

Инициализирует приложение как клиента с включённым [multicast mode](../../../../code/plugins/syncker/index.md#addressing_multicast). IP-адрес сервера будет определён автоматически. Сервер должен быть инициализирован с тем же режимом.
### Аргументы

- *const char ** **multicast_address** - Используемый multicast-адрес.
- *unsigned short* **udp_port** - Используемый UDP-порт.

### Возвращаемое значение

Указатель на интерфейс клиента.
## Client * initClientMulticast ( const char * server_address , const char * multicast_address , unsigned short udp_port )

Инициализирует приложение как клиента с включённым [multicast mode](../../../../code/plugins/syncker/index.md#addressing_multicast). IP-адрес сервера указывается явно. Сервер должен быть инициализирован с тем же режимом.
### Аргументы

- *const char ** **server_address** - Используемый IP-адрес сервера.
- *const char ** **multicast_address** - Используемый multicast-адрес.
- *unsigned short* **udp_port** - Используемый UDP-порт.

### Возвращаемое значение

Указатель на интерфейс клиента.
## Client * initClientUnicast ( unsigned short server_udp_port , unsigned short client_udp_port )

Инициализирует приложение как клиента с включённым [unicast mode](../../../../code/plugins/syncker/index.md#addressing_unicast). IP-адрес сервера будет определён автоматически. Сервер должен быть инициализирован с тем же режимом.
### Аргументы

- *unsigned short* **server_udp_port** - UDP-порт, используемый сервером.
- *unsigned short* **client_udp_port** - UDP-порт, используемый клиентом.

### Возвращаемое значение

Указатель на интерфейс клиента.
## Client * initClientUnicast ( const char * server_address , unsigned short server_udp_port , unsigned short client_udp_port )

Инициализирует приложение как клиента с включённым [unicast mode](../../../../code/plugins/syncker/index.md#addressing_unicast). IP-адрес сервера указывается явно. Сервер должен быть инициализирован с тем же режимом.
### Аргументы

- *const char ** **server_address** - Используемый IP-адрес сервера.
- *unsigned short* **server_udp_port** - UDP-порт, используемый сервером.
- *unsigned short* **client_udp_port** - UDP-порт, используемый клиентом.

### Возвращаемое значение

Указатель на интерфейс клиента.
## bool isInitialized ( ) const

Возвращает значение, указывающее, инициализирован ли сетевой менеджер.
### Возвращаемое значение

true, если сетевой менеджер инициализирован; иначе false.
## bool isServer ( ) const

Возвращает значение, указывающее, является ли приложение сервером.
### Возвращаемое значение

true, если приложение является сервером, иначе false.
## NetworkInstance * getInstance ( ) const

Возвращает [base class interface](../../../../api/library/plugins/databridge/class.networkinstance_cpp.md) для сервера и клиента.
### Возвращаемое значение

Указатель на интерфейс [network instance](../../../../api/library/plugins/databridge/class.networkinstance_cpp.md). Это базовый класс для сервера и клиента.
## Server * getServer ( ) const

Возвращает [Server interface](../../../../api/library/plugins/databridge/class.server_cpp.md).
### Возвращаемое значение

Указатель на [Server interface](../../../../api/library/plugins/databridge/class.server_cpp.md).
## Client * getClient ( ) const

Возвращает [Client interface](../../../../api/library/plugins/databridge/class.client_cpp.md).
### Возвращаемое значение

Указатель на [Client interface](../../../../api/library/plugins/databridge/class.client_cpp.md).
## void destroyInstance ( )

Завершает работу и уничтожает сетевой экземпляр.
> **Notice:** Вызывается автоматически при выгрузке плагина DataBridge.


## bool initHttpServer ( unsigned short port )

### Аргументы

- *unsigned short* **port**

## bool stopHttpServer ( )
