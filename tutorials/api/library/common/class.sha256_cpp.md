# Unigine::SHA256 Class (CPP)

**Header:** #include <UnigineChecksum.h>


## SHA256 Class

### Методы класса

---

## static SHA256Ptr create ( )

Конструктор по умолчанию, создающий пустой экземпляр.
## void update ( const void* data , int size )

Обновляет 256-битную контрольную сумму SHA256.
### Аргументы

- *const void** **data** - Указатель на входные данные.
- *int* **size** - Размер входных данных, в байтах.

## void end ( unsigned int* value , bool big_endian )

Финализирует значение контрольной суммы путём инвертирования всех битов.
### Аргументы

- *unsigned int** **value** - 256-битная контрольная сумма SHA256 (массив из 8 элементов unsigned int).
- *bool* **big_endian** - Флаг порядка байтов. **true** — использовать порядок big-endian; **false** — использовать порядок little-endian.

## int calculate ( const void* data , int size , bool big_endian )

Вычисляет 256-битную контрольную сумму SHA256.
### Аргументы

- *const void** **data** - Указатель на входные данные.
- *int* **size** - Размер входных данных, в байтах.
- *bool* **big_endian** - Флаг порядка байтов. **true** — использовать порядок big-endian; **false** — использовать порядок little-endian.

### Возвращаемое значение

256-битная контрольная сумма SHA256.
## void calculate ( unsigned int* value , const void* data , int size , bool big_endian )

Вычисляет 256-битную контрольную сумму SHA256.
### Аргументы

- *unsigned int** **value** - 256-битная контрольная сумма SHA256 (массив из 8 элементов unsigned int).
- *const void** **data** - Указатель на входные данные.
- *int* **size** - Размер входных данных, в байтах.
- *bool* **big_endian** - Флаг порядка байтов. **true** — использовать порядок big-endian; **false** — использовать порядок little-endian.
