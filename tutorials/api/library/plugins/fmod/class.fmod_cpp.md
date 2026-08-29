# Unigine::Plugins::FMOD::FMOD Class (CPP)

**Header:** #include <plugins/Unigine/FMOD/UnigineFMOD.h>

> **Notice:** Этот класс является синглтоном.


> **Notice:** Этот набор функций доступен, если загружен плагин [FMOD](../../../../code/plugins/fmod/index.md).


Этот класс предназначен для работы с объектами FMODCore и FMODStudio.


## FMOD Class

### Методы класса

## FMODCore * getCore () const

Возвращает текущий объект FMOD Core System. Объект Core System можно получить до инициализации объекта Studio System для вызова дополнительных функций конфигурации ядра.
### Возвращаемое значение

Текущий объект FMOD Core System.
## FMODStudio * getStudio () const

Возвращает текущий объект FMOD Studio System.
### Возвращаемое значение

Текущий объект FMOD Studio System.
---

## void update ( )

Вызывает обновление FMOD Studio и Core.
## bool hasErrors ( int & error_type )

Проверяет наличие ошибок и возвращает код ошибки. Для интерпретации ошибки см. перечисление [ERROR_TYPE](../../../../api/library/plugins/fmod/class.fmodenums_cpp.md#ERROR_TYPE).
### Аргументы

- *int &* **error_type** - Переменная для хранения кода ошибки.

### Возвращаемое значение

true, если произошла ошибка, иначе false.
