# CigiHatHotExtResponse Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>


## CigiHatHotExtResponse Class

### Методы класса

---

## void setHatHotID ( int id )

Задаёт значение параметра **HAT/HOT ID**, указываемое в пакете.
### Аргументы

- *int* **id** - Значение параметра **HAT/HOT ID**.

## void setResponseValid ( int valid )

Задаёт значение параметра **Response Valid**, указываемое в пакете.
### Аргументы

- *int* **valid** - Значение параметра **Response Valid**. Поддерживаются следующие значения:

  - 0 - недействительно (превышен лимит периода обновления)
  - 1 - действительно (лимит периода обновления не превышен)

## void setHeightAbove ( double height )

Задаёт значение параметра **HAT**, указываемое в пакете.
### Аргументы

- *double* **height** - Значение параметра **HAT**.

## void setHeightOf ( double height )

Задаёт значение параметра **HOT**, указываемое в пакете.
### Аргументы

- *double* **height** - Значение параметра **HOT**.

## void setAzimuth ( float a )

Задаёт значение параметра **Normal Vector Azimuth**, указываемое в пакете.
### Аргументы

- *float* **a** - Значение параметра **Normal Vector Azimuth**.

## void setElevation ( float e )

Задаёт значение параметра **Normal Vector Elevation**, указываемое в пакете.
### Аргументы

- *float* **e** - Значение параметра **Normal Vector Elevation**.

## void setMaterialCode ( unsigned int valid )

Задаёт значение параметра **Material Code**, указываемое в пакете.
### Аргументы

- *unsigned int* **valid** - Значение параметра **Material Code**.
