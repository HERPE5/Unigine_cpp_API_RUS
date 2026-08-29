# Unigine::Plugins::DataBridge::Server Class (CPP)

**Header:** #include <plugins/Unigine/DataBridge/UnigineDataBridge.h>


Этот класс наследуется от класса [NetworkInstance](../../../../api/library/plugins/databridge/class.networkinstance_cpp.md).


## Server Class

### Методы класса

---

## bool init ( NetworkInstance::ADDRESSING_METHOD in_addressing_method , const char * broadcast_address , const char * multicast_address , unsigned short udp_port )

Инициализирует сервер с указанными аргументами.
### Аргументы

- *[NetworkInstance::ADDRESSING_METHOD](../../../../api/library/plugins/databridge/class.networkinstance_cpp.md#ADDRESSING_METHOD)* **in_addressing_method** - Используемый режим адресации.
- *const char ** **broadcast_address** - Используемый широковещательный адрес.
- *const char ** **multicast_address** - Используемый multicast-адрес.
- *unsigned short* **udp_port** - Используемый UDP-порт сервера.

### Возвращаемое значение

true, если сервер инициализирован; иначе false.
