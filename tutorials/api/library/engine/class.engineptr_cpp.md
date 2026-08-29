# EnginePtr Class (CPP)

**Header:** #include <UnigineEngine.h>


This class is an analogue of the C++ [std::auto_ptr](http://www.cplusplus.com/reference/memory/auto_ptr/) class template. It automatically destroys the engine instance when the function is destroyed.

```cpp
Unigine::EnginePtr engine(...);
engine->main();

```


## EnginePtr Class

### Методы класса

---

## EnginePtr ( )

An EnginePtr constructor.
## EnginePtr ( const Engine Ptr & ptr )

An EnginePtr copy-constructor.
### Аргументы

- *const [Engine](../../../api/library/engine/class.engine_cpp.md)Ptr &* **ptr** - Pointer to the EnginePtr instance.

## EnginePtr ( int argc , char ** argv )

An EnginePtr constructor.
### Аргументы

- *int* **argc** - Number of [command line arguments](../../../code/command_line.md).
- *char *** **argv** - Array of [command line arguments](../../../code/command_line.md) values.

## EnginePtr ( int argc , wchar_t ** argv )

An EnginePtr constructor.
### Аргументы

- *int* **argc** - Number of [command line arguments](../../../code/command_line.md).
- *wchar_t *** **argv** - Array of [command line arguments](../../../code/command_line.md) values.

## EnginePtr ( const InitParameters& init_parameters , int argc , char ** argv )

An EnginePtr constructor (uses the specified [initialization parameters](../../../api/library/engine/class.engine_cpp.md#init_parameters)).
### Аргументы

- *const InitParameters&* **init_parameters** - Structure of initializing parameters.
- *int* **argc** - Number of [command line arguments](../../../code/command_line.md).
- *char *** **argv** - Array of [command line arguments](../../../code/command_line.md) values.

## EnginePtr ( const InitParameters& init_parameters , int argc , wchar_t ** argv )

An EnginePtr constructor (uses the specified [initialization parameters](../../../api/library/engine/class.engine_cpp.md#init_parameters)).
### Аргументы

- *const InitParameters&* **init_parameters** - Structure of initializing parameters.
- *int* **argc** - Number of [command line arguments](../../../code/command_line.md).
- *wchar_t *** **argv** - Array of [command line arguments](../../../code/command_line.md) values.

## Engine * get ( )

Returns a pointer to the existing [Engine](../../../api/library/engine/class.engine_cpp.md) instance.
### Возвращаемое значение

Pointer to [Engine](../../../api/library/engine/class.engine_cpp.md).
## int isOwner ( )

Returns the *owner* flag of the pointer. If the pointer is the owner, on its deletion the object also will be deleted.
### Возвращаемое значение

*Owner* flag.
## void grab ( )

Sets the *[owner](#owner)* flag to **1** for the Engine pointer.
## Engine * operator-> ( )

Pointer dereferencing and member access operator.
### Возвращаемое значение

[Engine](../../../api/library/engine/class.engine_cpp.md) instance.
## Engine Ptr & operator= ( const Engine Ptr & ptr )

Assign operator.
### Аргументы

- *const [Engine](../../../api/library/engine/class.engine_cpp.md)Ptr &* **ptr** - EnginePtr instance.

### Возвращаемое значение

EnginePtr instance.
## void release ( )

Releases the owner flag for the pointer. Engine instance will stay alive upon the pointer destruction.
## void shutdown ( )

Destroys the existing engine instance. The pointer must be an owner of the engine instance.
