# Unigine::TypeInfo Class (CPP)

**Header:** #include <UnigineType.h>


Класс RTTI TypeInfo.


## TypeInfo Class

### Методы класса

---

## TypeInfo ( )

Конструктор по умолчанию, создающий пустой класс.
## TypeInfo ( int id , const char * name )

Конструктор.
### Аргументы

- *int* **id** - Идентификатор типа.
- *const char ** **name** - Имя типа.

## TypeInfo ( const TypeInfo & type )

Конструктор копирования.
### Аргументы

- *const [TypeInfo](../../../api/library/common/class.typeinfo_cpp.md) &* **type** - Класс TypeInfo.

## int getID ( ) const

Доступ к идентификатору типа.
### Возвращаемое значение

Идентификатор типа.
## const char * getName ( ) const

Доступ к имени типа.
### Возвращаемое значение

Имя типа.
## explicit TypeInfo ( Type type )

Конструктор.
### Аргументы

- *Type* **type** - Класс TypeID.
