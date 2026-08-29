# CigiStartOfFrame Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>


## CigiStartOfFrame Class

### Методы класса

---

## void setDatabase ( int db )

Задаёт значение параметра **Database Number**, указываемое в пакете.
### Аргументы

- *int* **db** - Значение параметра **Database Number**.

## void setIGMode ( int mode )

Задаёт значение параметра **IG Mode**, указываемое в пакете.
### Аргументы

- *int* **mode** - Значение параметра **IG Mode**. Одно из значений [CIGI_MODE_*](../../../../../api/library/plugins/ig/cigi/class.cigi_connector_cpp.md#CIGI_MODE_STANDBY).

## void setIGStatus ( int mode )

Задаёт значение параметра **IG Status**, указываемое в пакете.
### Аргументы

- *int* **mode** - Значение параметра **IG Status**. Поддерживаются следующие значения:

  - 0 - нормальный
  - 1-255 - произошла ошибка

## void setTimeValid ( int valid )

Задаёт значение параметра **Timestamp Valid**, указываемое в пакете.
### Аргументы

- *int* **valid** - Значение параметра **Timestamp Valid**.

## void setEarthModel ( int model )

Задаёт значение параметра **Earth Reference Model**, указываемое в пакете.
### Аргументы

- *int* **model** - Значение параметра **Earth Reference Model**. Поддерживаются следующие значения:

  - 0 - WGS 84
  - 1 - Определяется Host

## void setIGFrame ( unsigned int frame )

Задаёт значение параметра **IG Frame Number**, указываемое в пакете.
### Аргументы

- *unsigned int* **frame** - Значение параметра **IG Frame Number**.

## void setTimeStamp ( unsigned int time )

Задаёт значение параметра **Timestamp**, указываемое в пакете.
### Аргументы

- *unsigned int* **time** - Значение параметра **Timestamp**.
