# Unigine::Plugins::DataBridge::NetworkInstance Class (CPP)

**Header:** #include <plugins/Unigine/DataBridge/UnigineDataBridge.h>


Этот класс предоставляет доступ к сетевому экземпляру, которым может быть либо [Server](../../../../api/library/plugins/databridge/class.server_cpp.md), либо [Client](../../../../api/library/plugins/databridge/class.client_cpp.md).


## NetworkInstance Class

### Перечисления

## ADDRESSING_METHOD

| Name | Description |
|---|---|
| **BROADCAST** = 0 | [Broadcast addressing mode](../../../../code/plugins/syncker/index.md#addressing_broadcast) (один-ко-всем): хосты имеют разные IP-адреса, но единый порт. |
| **UNICAST** = 1 | [Unicast addressing mode](../../../../code/plugins/syncker/index.md#addressing_unicast) (один-к-одному): хосты имеют разные IP-адреса (некоторые могут совпадать) и разные порты. |
| **MULTICAST** = 2 | [Multicast addressing mode](../../../../code/plugins/syncker/index.md#addressing_multicast) (один-ко-многим): хосты имеют разные IP-адреса, но единый порт. |

### Методы класса

## double getTime () const

Возвращает текущее время кадра сервера, в секундах (даже при вызове с компьютера клиента). Это время последней операции смены буферов (т.е. начало следующего кадра). Это значение точнее, чем аналогичное значение класса [Game](../../../../api/library/engine/class.game_cpp.md#Time).
### Возвращаемое значение

Текущее время кадра сервера, в секундах
## double getIFps () const

Возвращает текущую длительность последнего кадра. Этот метод точнее, чем аналогичный метод класса [Game](../../../../api/library/engine/class.game_cpp.md#getIFps_float), и возвращает значение двойной точности.
### Возвращаемое значение

Текущая длительность предыдущего кадра, в секундах.
---

## void update ( )

Обновляет сетевой экземпляр.
## void shutdown ( )

Завершает работу сетевого экземпляра.
## void setDisconnectTimeout ( float seconds )

Задаёт период таймаута, после которого клиент считается отключённым.
### Аргументы

- *float* **seconds** - Длительность периода таймаута, в секундах.

## float getDisconnectTimeout ( ) const

Возвращает текущий период таймаута, после которого клиент считается отключённым.
### Возвращаемое значение

Длительность периода таймаута, в секундах.
