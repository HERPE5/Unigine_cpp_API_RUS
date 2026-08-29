# Unigine::SHA1 Class (CPP)

**Header:** #include <UnigineChecksum.h>


## SHA1 Class

### Методы класса

---

## static SHA1Ptr create ( )

Конструктор по умолчанию, создающий пустой экземпляр.
## void begin ( )

Инициализирует 160-битную контрольную сумму SHA1 начальным значением.
## void update ( const void* data , int size )

Обновляет 160-битную контрольную сумму SHA1.
### Аргументы

- *const void** **data** - Указатель на входные данные.
- *int* **size** - Размер входных данных, в байтах.

## void end ( unsigned int* value , bool big_endian )

Финализирует значение контрольной суммы путём инвертирования всех битов.
### Аргументы

- *unsigned int** **value** - 160-битная контрольная сумма SHA1 (массив из 5 элементов unsigned int).
- *bool* **big_endian** - Флаг порядка байтов. **true** — использовать порядок big-endian; **false** — использовать порядок little-endian.

## int calculate ( const void* data , int size , bool big_endian )

Вычисляет 160-битную контрольную сумму SHA1.
### Аргументы

- *const void** **data** - Указатель на входные данные.
- *int* **size** - Размер входных данных, в байтах.
- *bool* **big_endian** - Флаг порядка байтов. **true** — использовать порядок big-endian; **false** — использовать порядок little-endian.

### Возвращаемое значение

160-битная контрольная сумма SHA1.
## void calculate ( unsigned int* value , const void* data , int size , bool big_endian )

Вычисляет 160-битную контрольную сумму SHA1.
### Аргументы

- *unsigned int** **value** - 160-битная контрольная сумма SHA1 (массив из 5 элементов unsigned int).
- *const void** **data** - Указатель на входные данные.
- *int* **size** - Размер входных данных, в байтах.
- *bool* **big_endian** - Флаг порядка байтов. **true** — использовать порядок big-endian; **false** — использовать порядок little-endian.
