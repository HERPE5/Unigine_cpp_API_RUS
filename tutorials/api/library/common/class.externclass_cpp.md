# Unigine::ExternClass Template (CPP)

**Header:** #include <UnigineInterface.h>


Unigine ExternClass.


## ExternClass Class

### Методы класса

---

## SaveFuncType Definition

### Описание

Полное объявление:
 *typedef void(* Unigine::ExternClass< Class >::SaveFunc)(const StreamPtr &stream, Class *object)*

Функтор для сохранения состояния объекта.
### Аргументы

*stream* -  Поток записи для сериализации объекта. *object* -  Указатель на объект класса.
### Возвращаемое значение

 void(*
## RestoreFuncType Definition

### Описание

Полное объявление:
 *typedef Class*(* Unigine::ExternClass< Class >::RestoreFunc)(const StreamPtr &stream)*

Функтор для восстановления состояния объекта.
### Аргументы

*stream* -  Поток чтения для сериализации объекта.
### Возвращаемое значение

 Class *(* Указатель на объект класса.
## DestructorFuncType Definition

### Описание

Полное объявление:
 *typedef void(* Unigine::ExternClass< Class >::DestructorFunc)(Class *object)*

Функтор для удаления объекта.
### Аргументы

*object* -  Указатель на объект класса.
### Возвращаемое значение

 void(*
---

## ExternClass ( SaveFunc save_state , RestoreFunc restore_state , SaveFunc save_pointer , RestoreFunc restore_pointer , DestructorFunc destructor )

Конструктор по умолчанию.
### Аргументы

- *SaveFunc* **save_state** - Функтор для сохранения состояния сконструированного объекта.
- *RestoreFunc* **restore_state** - Функтор для восстановления состояния сконструированного объекта.
- *SaveFunc* **save_pointer** - Функтор для сохранения состояния внешнего сконструированного объекта.
- *RestoreFunc* **restore_pointer** - Функтор для восстановления состояния внешнего сконструированного объекта.
- *DestructorFunc* **destructor** - Функтор для удаления сконструированного объекта.

## void setDestructor ( DestructorFunc destructor )

Задаёт функтор для удаления сконструированных объектов.
### Аргументы

- *DestructorFunc* **destructor** - Функтор для удаления сконструированного объекта.

## void setSaveRestorePointer ( SaveFunc save , RestoreFunc restore )

Задаёт функторы для сохранения/восстановления указателей.
### Аргументы

- *SaveFunc* **save** - Функтор для сохранения состояния внешнего сконструированного объекта.
- *RestoreFunc* **restore** - Функтор для восстановления состояния внешнего сконструированного объекта.

## void setSaveRestoreState ( SaveFunc save , RestoreFunc restore )

Задаёт функторы для сохранения/восстановления состояния.
### Аргументы

- *SaveFunc* **save** - Функтор для сохранения состояния сконструированного объекта.
- *RestoreFunc* **restore** - Функтор для восстановления состояния сконструированного объекта.

## void addBaseClass ( ExternClassBase * base )

Добавляет базовый класс к внешнему классу.
### Аргументы

- *ExternClassBase ** **base** - Указатель на базовый класс.

## void addConstructor ( const char * args )

Добавляет конструктор к внешнему классу. Конструктор может принимать до 9 аргументов.
### Аргументы

- *const char ** **args** - Аргументы по умолчанию.

## void addConstructor ( Class *(*)() func , const char * args )

Добавляет конструктор к внешнему классу. Конструктор может принимать до 9 аргументов.
### Аргументы

- *Class *(*)()* **func** - Функтор для создания объекта.
- *const char ** **args** - Аргументы по умолчанию.

## void addFunction ( const char * name , Ret (Type::*)() __attribute__((thiscall)) func , const char * args )

Добавляет функцию-член к внешнему классу. Функция может принимать до 9 аргументов и возвращать void или значение любого поддерживаемого типа. Также поддерживаются константные функции-члены.
### Аргументы

- *const char ** **name** - Имя функции-члена.
- *Ret (Type::*)() __attribute__((thiscall))* **func** - Указатель на функцию-член.
- *const char ** **args** - Аргументы по умолчанию.

## void addGetFunction ( const char * name , Type Class::* member )

Добавляет функцию-геттер для члена внешнего класса.
### Аргументы

- *const char ** **name** - Имя функции-геттера.
- *Type Class::** **member** - Член класса.

## void addSetFunction ( const char * name , Type Class::* member )

Добавляет функцию-сеттер для члена внешнего класса.
### Аргументы

- *const char ** **name** - Имя функции-сеттера.
- *Type Class::** **member** - Член класса.
