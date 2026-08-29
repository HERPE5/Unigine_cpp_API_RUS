# Unigine::Plugins::DataBridge::Client Class (CPP)

**Header:** #include <plugins/Unigine/DataBridge/UnigineDataBridge.h>


Этот класс наследуется от класса [NetworkInstance](../../../../api/library/plugins/databridge/class.networkinstance_cpp.md).


## Client Class

### Методы класса

## long long getID () const

Возвращает текущий ID клиента.
### Возвращаемое значение

Текущий ID клиента, составленный следующим образом: IP-адрес (32 бита) + номер порта (16 бит).
---

## bool init ( NetworkInstance::ADDRESSING_METHOD in_addressing_method , const char * server_address , const char * multicast_address , unsigned short server_udp_port , unsigned short client_udp_port )

Инициализирует клиент с указанными аргументами.
### Аргументы

- *[NetworkInstance::ADDRESSING_METHOD](../../../../api/library/plugins/databridge/class.networkinstance_cpp.md#ADDRESSING_METHOD)* **in_addressing_method** - Используемый режим адресации.
- *const char ** **server_address** - Используемый IP-адрес сервера.
- *const char ** **multicast_address** - Используемый multicast-адрес.
- *unsigned short* **server_udp_port** - Используемый UDP-порт сервера.
- *unsigned short* **client_udp_port** - Используемый UDP-порт клиента.

### Возвращаемое значение

true, если клиент инициализирован; иначе false.
## bool isConnected ( ) const

Возвращает значение, указывающее, подключён ли клиент.
### Возвращаемое значение

true, если клиент подключён; иначе false.
## bool isReady ( ) const

Возвращает значение, указывающее, готов ли клиент к работе: подключён и получил данные от сервера.
### Возвращаемое значение

true, если клиент готов к работе; иначе - false.
