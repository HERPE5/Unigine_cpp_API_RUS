# CigiHatHotResponse Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>


## CigiHatHotResponse Class

### Методы класса

---

## void setHatHotID ( int id )

Задаёт значение параметра **HAT/HOT ID**, указываемое в пакете.
### Аргументы

- *int* **id** - Значение параметра **HAT/HOT ID**.

## void setResponseType ( int type )

Задаёт значение параметра **Response Type**, указываемое в пакете.
### Аргументы

- *int* **type** - Значение параметра **Response Type**. Поддерживаются следующие значения:

  - 0 - HAT
  - 1 - HOT

## void setResponseValid ( int valid )

Задаёт значение параметра **Response Valid**, указываемое в пакете.
### Аргументы

- *int* **valid** - Значение параметра **Response Valid**. Поддерживаются следующие значения:

  - 0 - недействительно (превышен лимит периода обновления)
  - 1 - действительно (лимит периода обновления не превышен)

## void setHeight ( double height )

Задаёт значение параметра **Height**, указываемое в пакете.
### Аргументы

- *double* **height** - Значение параметра **Height**.
