# Unigine::StringArray class (CPP)

**Header:** #include <UnigineString.h>


Массив строк.


## StringArray Class

### Методы класса

---

## static StringArrayPtr create ( int size )

Конструктор. Создаёт пустой массив строк указанного размера.
### Аргументы

- *int* **size** - Размер массива.

## static StringArrayPtr create ( const StringArray <Capacity> & s )

Конструктор копирования.
### Аргументы

- *const [StringArray](../../../api/library/common/class.stringarray_cpp.md)<Capacity> &* **s** - Массив строк.

## int empty ( )

Возвращает значение, указывающее, пуст ли массив строк.
### Возвращаемое значение

1, если массив пуст, иначе 0.
## const char * operator[] ( int index )

Доступ к массиву.
### Аргументы

- *int* **index** - Индекс элемента массива.

### Возвращаемое значение

Элемент массива.
## int size ( )

Возвращает размер массива строк.
### Возвращаемое значение

Размер массива.
