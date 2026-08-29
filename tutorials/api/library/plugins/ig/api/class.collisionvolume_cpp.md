# Unigine::Plugins::IG::CollisionVolume Class (CPP)

**Header:** #include <plugins/Unigine/IG/UnigineIG.h>


Этот класс используется для управления объёмами столкновений, назначаемыми [entities](../../../../../api/library/plugins/ig/api/class.entity_cpp.md) и используемыми для обнаружения столкновений.

> **Notice:** Плагин IG должен быть загружен.


Объём обнаружения столкновений — это сфера или прямоугольный параллелепипед, посредством которого IG выполняет проверку столкновений. Когда объём обнаружения столкновений проходит через другой объём столкновения, IG регистрирует столкновение, отправляя соответствующее уведомление.

> **Notice:** Проверка обнаружения столкновений выполняется IG каждый кадр.


Объём задаётся указанием его положения, размера и ориентации относительно системы координат тела связанной сущности. Размер сферы задаётся радиусом; размер параллелепипеда задаётся его шириной, высотой и глубиной.


В отличие от сегментов обнаружения столкновений, которые проверяются по схеме сегмент-полигон, объёмы обнаружения столкновений проверяются по схеме объём-объём. Объёмы, связанные с одной и той же сущностью, не проверяются друг относительно друга.


## CollisionVolume Class

### Методы класса

---

## int getID ( ) const

Возвращает ID объёма столкновения.
### Возвращаемое значение

ID объёма столкновения.
## Entity * getEntity ( ) const

Возвращает [entity](../../../../../api/library/plugins/ig/api/class.entity_cpp.md), которой назначен объём столкновения.
### Возвращаемое значение

Сущность, которой назначен объём столкновения.
## void setEnabled ( bool value )

Включает или отключает объём столкновения.
### Аргументы

- *bool* **value** - true, чтобы включить объём столкновения; false - чтобы отключить его.

## bool isEnabled ( ) const

Возвращает значение, указывающее, включён ли объём столкновения.
### Возвращаемое значение

true, если объём столкновения включён; иначе false
## void setPosition ( const Math::vec3& value )

Задаёт координаты центра объёма столкновения.
### Аргументы

- *const  Math::vec3&* **value** - Координаты центра объёма столкновения, в системе координат [entity](#getEntity_Entity).

## Math:: vec3 getPosition ( ) const

Возвращает текущие координаты центра объёма столкновения.
### Возвращаемое значение

Текущие координаты центра объёма столкновения, в системе координат [entity](#getEntity_Entity).
## void setRotation ( const Math::quat& value )

Задаёт поворот объёма столкновения в форме параллелепипеда. Кватернион поворота получается путём преобразования углов Эйлера NED (*roll, pitch, yaw*) в кватернион с помощью метода *[NEDConverter::eulerNEDToRotation()](../../../../../api/library/plugins/ig/api/class.nedconverter_cpp.md#eulerNEDToRotation_vec3_quat)*.
### Аргументы

- *const  Math::quat&* **value** - Кватернион, задающий поворот объёма столкновения в форме параллелепипеда.

## Math:: quat getRotation ( ) const

Возвращает текущий поворот объёма столкновения в форме параллелепипеда. Полученный кватернион поворота можно преобразовать в углы Эйлера NED (*roll, pitch, yaw*) с помощью метода *[NEDConverter::rotationToEulerNED()](../../../../../api/library/plugins/ig/api/class.nedconverter_cpp.md#rotationToEulerNED_quat_vec3)*.
### Возвращаемое значение

Кватернион, задающий поворот объёма столкновения в форме параллелепипеда.
## void setSize ( const Math::vec3& size )

Задаёт размер объёма столкновения в форме параллелепипеда.
### Аргументы

- *const  Math::vec3&* **size** - Вектор, задающий размер объёма столкновения в форме параллелепипеда (*depth, width, height*). Каждый компонент задаётся в метрах.

## void setRadius ( float radius )

Задаёт радиус сферического объёма столкновения.
### Аргументы

- *float* **radius** - Радиус сферического объёма столкновения, в метрах.

## void * addOnCollisionDetectedCallback ( Unigine:: CallbackBase4 < CollisionVolume *, Ptr < ShapeContact >, long long, int > * func )

Добавляет функцию колбэка, вызываемую при обнаружении столкновения с объёмом столкновения. Эта функция может использоваться для определения конкретных действий, выполняемых при обнаружении столкновения с объёмом. Сигнатура функции колбэка должна быть следующей:
```cpp
void(CollisionVolume *v, ContactPtr cnt, long long contacted_entity, int contacted_segment);
```


Функцию колбэка можно задать следующим образом:


```cpp
addOnCollisionDetectedCallback(MakeCallback(collision_callback_function_name));
```


**Пример:** Задание колбэка обнаружения столкновения для объёма столкновения сущности


```cpp
/// функция колбэка, вызываемая при обнаружении столкновения с объёмом столкновения
void my_callback(CollisionVolume *v, ShapeContactPtr cnt, long long contacted_entity, int contacted_segment)
{
	// ваш код
}

// ...
// где-то в коде
void SomeClass::init()
{
	// добавление "my_callback" для вызова при обнаружении столкновения с объёмом
	ig_manager->getEntity(entity_id)->getCollisionVolume(volume_id)->addOnCollisionDetectedCallback(Unigine::MakeCallback( my_callback );
}

```


### Аргументы

- *Unigine::[CallbackBase4](../../../../../api/library/common/callbacks/class.callbackbase4_cpp.md)< [CollisionVolume](../../../../../api/library/plugins/ig/api/class.collisionvolume_cpp.md) *, [Ptr](../../../../../api/library/common/class.ptr_cpp.md)<[ShapeContact](../../../../../api/library/physics/class.shapecontact_cpp.md)>, long long, int > ** **func** - Функция колбэка.

### Возвращаемое значение

ID последнего добавленного колбэка обнаружения столкновения, если колбэк был успешно добавлен; иначе **nullptr**. Этот ID можно использовать для [remove](#removeOnCollisionDetectedCallback_void_ptr_bool) этого колбэка при необходимости.
## bool removeOnCollisionDetectedCallback ( void * id )

Удаляет указанный колбэк из списка колбэков обнаружения столкновения.
### Аргументы

- *void ** **id** - ID колбэка обнаружения столкновения, полученный при его [adding](#addOnCollisionDetectedCallback_CallbackBase_ptr_void).

### Возвращаемое значение

True, если колбэк обнаружения столкновения с указанным ID был успешно удалён; иначе false.
## void clearOnCollisionDetectedCallbacks ( )

Очищает все [added](#addOnCollisionDetectedCallback_CallbackBase_ptr_void) колбэки обнаружения столкновения.
## void setName ( const char * value )

Задаёт новое имя объёма столкновения.
### Аргументы

- *const char ** **value** - Задаваемое имя объёма столкновения.

## const char * getName ( ) const

Возвращает имя объёма столкновения.
### Возвращаемое значение

Имя объёма столкновения.
