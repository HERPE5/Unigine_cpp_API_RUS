# ComponentVariable Class (CPP)

**Header:** #include <UnigineComponentSystem.h>


Этот класс используется для обращения к [component parameters](../../../../../../api/library/common/logic/component_system/cpp/class.componentbase_cpp.md#parameters).


## ComponentVariable Class

### Методы класса

---

## const PropertyParameter Ptr & getParameter ( ) const

Возвращает указатель на соответствующий параметр свойства.
### Возвращаемое значение

Указатель на параметр свойства.
## int size ( )

Возвращает количество элементов в массиве.
> **Notice:** Этот метод предназначен для параметров компонента типа массив и массив структур.


### Возвращаемое значение

Количество элементов в массиве.
## C & operator[] ( int index )

Возвращает ссылку на запрашиваемый элемент.
> **Notice:** Этот метод предназначен для параметров компонента типа массив и массив структур.


### Аргументы

- *int* **index** - Позиция возвращаемого элемента.

### Возвращаемое значение

Ссылка на запрашиваемый элемент.
