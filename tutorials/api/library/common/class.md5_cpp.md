# Unigine::MD5 Class (CPP)

**Header:** #include <UnigineChecksum.h>


## MD5 Class

### Методы класса

---

## static MD5Ptr create ( )

Конструктор по умолчанию, создающий пустой экземпляр.
## void begin ( )

Инициализирует 128-битную контрольную сумму MD5 начальным значением.
## void update ( const void* data , int size )

Обновляет 128-битную контрольную сумму MD5.
### Аргументы

- *const void** **data** - Указатель на входные данные.
- *int* **size** - Размер входных данных, в байтах.

## void endMD5 ( unsigned int* value , bool big_endian )

Финализирует значение контрольной суммы путём инвертирования всех битов.
### Аргументы

- *unsigned int** **value** - 128-битная контрольная сумма MD5 (массив из 4 элементов unsigned int).
- *bool* **big_endian** - Флаг порядка байтов. **true** — использовать порядок big-endian; **false** — использовать порядок little-endian.

## void endD3D ( unsigned int* value )

Финализирует 128-битную контрольную сумму MD5 (версия DXBC).
### Аргументы

- *unsigned int** **value** - 128-битная контрольная сумма MD5 (массив из 4 элементов unsigned int).

## int calculate ( const void* data , int size , bool big_endian )

Вычисляет 128-битную контрольную сумму MD5.
### Аргументы

- *const void** **data** - Указатель на входные данные.
- *int* **size** - Размер входных данных, в байтах.
- *bool* **big_endian** - Флаг порядка байтов. **true** — использовать порядок big-endian; **false** — использовать порядок little-endian.

### Возвращаемое значение

128-битная контрольная сумма MD5.
## void calculate ( unsigned int* value , const void* data , int size , bool big_endian )

Вычисляет 128-битную контрольную сумму MD5.
### Аргументы

- *unsigned int** **value** - 128-битная контрольная сумма MD5 (массив из 4 элементов unsigned int).
- *const void** **data** - Указатель на входные данные.
- *int* **size** - Размер входных данных, в байтах.
- *bool* **big_endian** - Флаг порядка байтов. **true** — использовать порядок big-endian; **false** — использовать порядок little-endian.

## void calculateD3D ( unsigned int* value , const void* data , int size )

Вычисляет 128-битную контрольную сумму MD5 (версия DXBC).
### Аргументы

- *unsigned int** **value** - 128-битная контрольная сумма MD5 (массив из 4 элементов unsigned int).
- *const void** **data** - Указатель на входные данные.
- *int* **size** - Размер входных данных, в байтах.
