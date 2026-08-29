# Unigine::BodyCloth Class (CPP)

**Header:** #include <UniginePhysics.h>

**Inherits from:** BodyParticles


Этот класс используется для симуляции плоских деформируемых [cloth bodies](../../../principles/physics/bodies/cloth/index.md). Они используют [mass-spring simulation model](../../../principles/physics/bodies/cloth/index.md#model): ткань формируется из [particles](../../../api/library/physics/class.bodyparticles_cpp.md) (сферической формы), расположенных в вершинах меша ткани и соединённых внутренними joints.


### См. также


- Пример использования [Creating and Attaching a Cloth](../../../code/usage/cloth_particle_joint/index_cpp.md), демонстрирующий создание объекта, назначение ему тела ткани и настройку его параметров

  -
  -
  -
  -
  -
  -
  -
  -
  -


## BodyCloth Class

### Методы класса

---

## static BodyClothPtr create ( )

Конструктор. Создаёт тело ткани со свойствами по умолчанию.
## static BodyClothPtr create ( const Ptr < Object > & object )

Конструктор. Создаёт тело ткани со свойствами по умолчанию для указанного объекта.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)> &* **object** - Объект, представленный новым телом ткани.

## int getNumIndices ( )

Возвращает количество индексов частиц.
### Возвращаемое значение

Количество индексов частиц.
## int getParticleIndex ( int num )

Возвращает индекс частицы по его номеру.
### Аргументы

- *int* **num** - Номер индекса частицы.

### Возвращаемое значение

Индекс частицы.
## void setTwoSided ( int sided )

Задаёт значение, указывающее, является ли ткань односторонней или двусторонней. (Если ткань двусторонняя, её материал не должен одновременно быть [two-sided](../../../api/library/rendering/class.material_cpp.md#setTwoSided_int_void)).
### Аргументы

- *int* **sided** - Положительное значение, если ткань должна быть двусторонней; **0**, если односторонней.

## int getTwoSided ( )

Возвращает значение, указывающее, является ли ткань односторонней или двусторонней. (Если ткань двусторонняя, её материал не должен одновременно быть [two-sided](../../../api/library/rendering/class.material_cpp.md#setTwoSided_int_void)).
### Возвращаемое значение

**1**, если ткань отрисовывается односторонней; **0**, если односторонняя.
