# Unigine.EventConnections Class (CPP)

**Header:** #include <UnigineCallback.h>


Этот класс является контейнером для класса *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)*, используемым для хранения нескольких экземпляров *EventConnection*. Связи, хранящиеся в одном и том же контейнере *EventConnections*, могут относиться к разным событиям.


## EventConnections Class

### Методы класса

## bool empty () const

Возвращает текущее значение, указывающее, пуст ли контейнер.
### Возвращаемое значение

**true**, если контейнер пуст; иначе **false**.
---

## void disconnectAll ( )

Отменяет связь для всех экземпляров *EventConnection* в контейнере.
