# ObjectExternBase Class (CPP)

**Header:** #include <UnigineObjects.h>

**Inherits from:** Base


Базовый класс, от которого наследуются [custom user-defined objects](../../../api/library/objects/class.objectextern_cpp.md).


## ObjectExternBase Class

### Методы класса

---

## template < class Type >

## static addClassID ( int class_id )

Регистрирует пользовательский класс объекта с уникальным идентификатором класса.
```cpp
// регистрируем класс MyObject
ObjectExternBase::addClassID<MyObject>(1);

```


### Аргументы

- *int* **class_id** - Уникальный идентификатор класса.

## int getClassID ( )

Возвращает уникальный идентификатор класса.
### Возвращаемое значение

Уникальный идентификатор класса.
## int getCollision ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , Vector < int > & OUT_surfaces )

Пространственное столкновение с ограничивающим объёмом (bounding box).
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Координаты начальной точки линии.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Координаты конечной точки линии.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< int > &* **OUT_surfaces** - Возвращаемый массив с номерами поверхностей. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

### Возвращаемое значение

Возвращает **1**, если массив поверхностей не пуст.
## int getCollision ( const BoundBox & bb , Vector < int > & OUT_surfaces )

Пространственное столкновение с ограничивающим объёмом (bounding box).
### Аргументы

- *const [BoundBox](../../../api/library/math/bounds/class.boundbox_cpp.md) &* **bb** - Ограничивающий объём.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< int > &* **OUT_surfaces** - Возвращаемый массив с номерами поверхностей. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

### Возвращаемое значение

Возвращает **1**, если массив поверхностей не пуст.
## int getIntersection ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , Math:: Vec3 * OUT_ret_point , Math:: vec3 * OUT_ret_normal , Math:: vec4 * OUT_ret_texcoord , int * OUT_ret_index , int * OUT_ret_instance , int surface )

Возвращает значение, указывающее, что линия пересекает поверхность объекта.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Координаты начальной точки линии.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Координаты конечной точки линии.
- *Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) ** **OUT_ret_point** - Координаты точки пересечения. Передайте NULL, если этот параметр не требуется. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) ** **OUT_ret_normal** - Вектор нормали в точке пересечения. Передайте NULL, если этот параметр не требуется. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *Math::[vec4](../../../api/library/math/class.vec4_cpp.md) ** **OUT_ret_texcoord** - Текстурные координаты точки пересечения. Передайте NULL, если этот параметр не требуется. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *int ** **OUT_ret_index** - Номер пересечённого треугольника. Передайте NULL, если этот параметр не требуется. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *int ** **OUT_ret_instance** - Номер пересечённого экземпляра. Передайте NULL, если этот параметр не требуется. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Возвращает **1**, если пересечение произошло.
## Ptr < Node > getNode ( ) const

Возвращает умный указатель на Node.
### Возвращаемое значение

Умный указатель на Node.
## int getNumSurfaces ( )

Возвращает количество поверхностей объекта.
### Возвращаемое значение

Количество поверхностей объекта.
## int getNumTriangles ( int surface )

Возвращает количество треугольников.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Возвращает количество треугольников.
## Ptr < Object > getObject ( ) const

Возвращает умный указатель на Object.
### Возвращаемое значение

Умный указатель на Object.
## Ptr < ObjectExtern > getObjectExtern ( ) const

Возвращает умный указатель на ObjectExtern.
### Возвращаемое значение

Умный указатель на ObjectExtern.
## int getOrder ( const Math:: Vec3 & camera , int surface )

Возвращает порядок рендеринга относительно положения камеры.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **camera** - Положение камеры в мировых координатах.
- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Порядок рендеринга поверхности.
## int getRandomPoint ( Math:: vec3 & ret_point , Math:: vec3 & ret_normal , Math:: vec3 & ret_velocity , int surface )

Возвращает случайную точку на поверхности.
### Аргументы

- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret_point** - Координаты случайной точки.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret_normal** - Случайный вектор нормали.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret_velocity** - Случайный вектор скорости.
- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Возвращает **1**, если случайная точка допустима.
## int getResource ( int surface )

Возвращает уникальный идентификатор ресурса рендеринга.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Идентификатор ресурса поверхности.
## int getSequence ( const Math:: Vec3 & camera , int surface )

Возвращает последовательность рендеринга относительно положения камеры.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **camera** - Положение камеры в мировых координатах.
- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Последовательность рендеринга поверхности.
## const char * getSurfaceName ( int surface )

Возвращает имя поверхности объекта.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Имя поверхности.
## float getTransparentDistance ( const Math:: Vec3 & camera , int surface )

Возвращает дистанцию рендеринга прозрачности.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **camera** - Положение камеры в мировых координатах.
- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Дистанция рендеринга поверхности.
## void create ( int surface )

Выполняет функцию create.
### Аргументы

- *int* **surface** - Номер поверхности.

## int findSurface ( const char * name )

Возвращает номер поверхности объекта по её имени.
### Аргументы

- *const char ** **name** - Имя поверхности.

### Возвращаемое значение

Номер поверхности.
## int hasCreate ( )

Возвращает значение, указывающее, что у объекта есть функция create.
### Возвращаемое значение

Возвращает **1**, если у объекта есть функция create.
## int hasLods ( )

Возвращает значение, указывающее, есть ли у объекта LOD-уровни.
### Возвращаемое значение

Возвращает **1**, если у объекта есть LOD-уровни поверхностей.
## int hasRender ( )

Возвращает значение, указывающее, что у объекта есть функция render.
### Возвращаемое значение

Возвращает **1**, если у объекта есть функция render.
## int hasShadow ( )

Возвращает значение, указывающее, что у объекта есть функция shadow.
### Возвращаемое значение

Возвращает **1**, если у объекта есть функция shadow.
## int loadWorld ( const Ptr < Xml > & xml )

Загружает состояние объекта из Xml.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../api/library/common/class.xml_cpp.md)> &* **xml** - Умный указатель на Xml.

### Возвращаемое значение

Возвращает **1**, если состояние объекта было успешно загружено; иначе возвращается **0**.
## void preRender ( float ifps )

Функция предварительного рендеринга, т.е. вызывается после *update()* и перед *render()*. Этот метод можно использовать для выполнения необходимых подготовительных действий перед рендерингом (например, подготовки текстуры) после *update()*.
### Аргументы

- *float* **ifps** - Значение, обратное FPS.

## void render ( Render::PASS pass , int surface )

Выполняет функцию render.
### Аргументы

- *[Render::PASS](../../../api/library/rendering/class.render_cpp.md#PASS)* **pass** - Проход рендеринга.
- *int* **surface** - Номер поверхности.

## void renderHandler ( )

Выполняет рендеринг обработчика.
## void renderShadow ( Render::PASS pass , int surface )

Выполняет функцию render.
### Аргументы

- *[Render::PASS](../../../api/library/rendering/class.render_cpp.md#PASS)* **pass** - Проход рендеринга.
- *int* **surface** - Номер поверхности.

## void renderVisualizer ( )

Выполняет рендеринг визуализатора.
> **Notice:** Необходимо включить визуализатор движка с помощью консольной команды **show_visualizer 1**.


## void resizeSurfaces ( ) const

Изменяет размер всех поверхностей объекта.
## bool saveState ( const Ptr < Stream > & stream )

Сохраняет состояние объекта в поток.
Для сохранения в поток необходимо создать blob для сохранения. Для восстановления сохранённого состояния используется метод [restoreState()](#restoreState_Stream_int):


```cpp
// инициализируем узел и устанавливаем его состояние
//...//

// сохраняем состояние
BlobPtr blob_state = Blob::create();
object->saveState(blob_state);

// изменяем состояние
//...//

// восстанавливаем состояние
blob_state->seekSet(0);				// возвращаем каретку в начало блоба
object->restoreState(blob_state);

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Умный указатель на Stream.

### Возвращаемое значение

true в случае успеха; иначе false.
## bool restoreState ( const Ptr < Stream > & stream )

Восстанавливает состояние объекта из потока.
Для восстановления из потока необходимо создать blob для сохранения и сохранить состояние с помощью метода [saveState()](#saveState_Stream_int):


```cpp
// инициализируем узел и устанавливаем его состояние
//...//

// сохраняем состояние
BlobPtr blob_state = Blob::create();
object->saveState(blob_state);

// изменяем состояние
//...//

// восстанавливаем состояние
blob_state->seekSet(0);				// возвращаем каретку в начало блоба
object->restoreState(blob_state);

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Умный указатель на Stream.

### Возвращаемое значение

true в случае успеха; иначе false.
## int saveWorld ( const Ptr < Xml > & xml )

Сохраняет состояние объекта в Xml.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../api/library/common/class.xml_cpp.md)> &* **xml** - Умный указатель на Xml.

### Возвращаемое значение

Возвращает **1**, если состояние объекта было успешно сохранено; иначе возвращается **0**.
## void update ( float ifps )

Функция обновления.
### Аргументы

- *float* **ifps** - Значение, обратное FPS.

## void updateEnabled ( )

Обновляет состояние включённости.
## void updateEnabled ( int surface )

Обновляет состояние включённости.
### Аргументы

- *int* **surface** - Номер поверхности.

## void updateSurfaces ( ) const

Обновляет все поверхности объекта.
## void updateTransform ( )

Обновляет трансформацию.
## void setUpdateDistanceLimit ( float distance )

Задаёт дистанцию от камеры, в пределах которой объект должен обновляться.
### Аргументы

- *float* **distance** - Дистанция от камеры, в пределах которой объект должен обновляться (в единицах).

## float getUpdateDistanceLimit ( )

Возвращает дистанцию от камеры, в пределах которой объект должен обновляться.
### Возвращаемое значение

Дистанция от камеры, в пределах которой объект должен обновляться (в единицах).
## void setForceUpdate ( bool enabled )

Задаёт значение, указывающее, должен ли объект принудительно обновляться каждый кадр, независимо от [update distance](#setUpdateDistanceLimit_float_void).
### Аргументы

- *bool* **enabled** - true, чтобы включить принудительное обновление объекта; false — чтобы отключить принудительное обновление и учитывать [update distance](#setUpdateDistanceLimit_float_void).

## bool isForceUpdate ( )

Возвращает значение, указывающее, должен ли объект принудительно обновляться каждый кадр, независимо от [update distance](#setUpdateDistanceLimit_float_void).
### Возвращаемое значение

true, если объект принудительно обновляется каждый кадр; иначе false
