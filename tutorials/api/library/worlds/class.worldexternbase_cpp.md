# Unigine.WorldExternBase Class (CPP)

**Header:** #include <UnigineWorld.h>

**Inherits from:** Base


Базовый класс UNIGINE WorldExtern.


## WorldExternBase Class

### Методы класса

---

## template < class Type >

## static addClassID ( int class_id )

Регистрирует пользовательский класс мира с уникальным ID класса.
```cpp
// регистрируем класс MyWorld
WorldExternBase::addClassID<MyWorld>(1);

```


### Аргументы

- *int* **class_id** - Уникальный ID класса.

## int getClassID ( )

Возвращает уникальный ID класса.
### Возвращаемое значение

Уникальный ID класса.
## Ptr < Node > getNode ( ) const

Возвращает умный указатель на Node.
### Возвращаемое значение

Умный указатель на Node.
## Ptr < WorldExtern > getWorldExtern ( ) const

Возвращает умный указатель на WorldExtern.
### Возвращаемое значение

Умный указатель на WorldExtern.
## int loadWorld ( const Ptr < Xml > & xml )

Загружает состояние мира из Xml.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../api/library/common/class.xml_cpp.md)> &* **xml** - Умный указатель на Xml.

### Возвращаемое значение

1, если состояние мира успешно загружено; иначе 0.
## void preRender ( float ifps )

Функция pre-render, то есть выполняемая после *update()* и перед *render()*.
### Аргументы

- *float* **ifps** - Значение, обратное FPS.

## void renderHandler ( )

Рендерит обработчик для внешнего мира.
## void renderVisualizer ( )

Рендерит визуализатор.
> **Notice:** Необходимо включить визуализатор движка консольной командой **show_visualizer 1**.


## bool saveState ( const Ptr < Stream > & stream )

Сохраняет состояние мира в поток.
Для сохранения в поток требуется создать blob для сохранения. Для восстановления сохранённого состояния используется метод [restoreState()](#restoreState_Stream_int):


```cpp
// инициализируем узел и задаём его состояние
//...//

// сохраняем состояние
BlobPtr blob_state = Blob::create();
worldExtern1->saveState(blob_state);

// изменяем состояние
//...//

// восстанавливаем состояние
blob_state->seekSet(0);				// возвращаем каретку в начало blob
worldExtern1->restoreState(blob_state);

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Умный указатель на поток.

### Возвращаемое значение

true при успехе; иначе false.
## bool restoreState ( const Ptr < Stream > & stream )

Восстанавливает состояние мира из потока.
Для восстановления из потока требуется создать blob для сохранения и сохранить состояние методом [saveState()](#saveState_Stream_int):


```cpp
// инициализируем узел и задаём его состояние
//...//

// сохраняем состояние
BlobPtr blob_state = Blob::create();
worldExtern1->saveState(blob_state);

// изменяем состояние
//...//

// восстанавливаем состояние
blob_state->seekSet(0);				// возвращаем каретку в начало blob
worldExtern1->restoreState(blob_state);

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Умный указатель на поток.

### Возвращаемое значение

true при успехе; иначе false.
## int saveWorld ( const Ptr < Xml > & xml )

Сохраняет состояние мира в Xml.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../api/library/common/class.xml_cpp.md)> &* **xml** - Умный указатель на Xml.

### Возвращаемое значение

1, если состояние мира успешно сохранено; иначе 0.
## void update ( float ifps )

Функция обновления. Вызывается, когда узел видим.
### Аргументы

- *float* **ifps** - Значение, обратное FPS.

## void updateEnabled ( )

Обновляет флаг включения.
## void updateTransform ( )

Обновляет матрицу трансформации внешнего мира.
## void setUpdateDistanceLimit ( float distance )

Задаёт расстояние от камеры, в пределах которого внешний мир должен обновляться.
### Аргументы

- *float* **distance** - Расстояние от камеры, в пределах которого внешний мир должен обновляться (в единицах).

## float getUpdateDistanceLimit ( )

Возвращает расстояние от камеры, в пределах которого внешний мир должен обновляться.
### Возвращаемое значение

Расстояние от камеры, в пределах которого внешний мир должен обновляться (в единицах).
## void setUpdate ( bool enabled )

Задаёт значение, указывающее, должен ли внешний мир постоянно обновляться каждый кадр, независимо от [update distance](#setUpdateDistanceLimit_float_void).
### Аргументы

- *bool* **enabled** - true, чтобы включить принудительное обновление для внешнего мира; false - чтобы отключить принудительное обновление и учитывать [update distance](#setUpdateDistanceLimit_float_void).

## bool isUpdate ( )

Возвращает значение, указывающее, должен ли внешний мир постоянно обновляться каждый кадр, независимо от [update distance](#setUpdateDistanceLimit_float_void).
### Возвращаемое значение

true, если внешний мир постоянно обновляется каждый кадр; иначе false
