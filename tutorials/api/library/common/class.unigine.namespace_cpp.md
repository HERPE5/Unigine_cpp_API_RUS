# Unigine Namespace Items (CPP)


## CallbackBase * MakeCallback ( Ret(*)() func )

Создаёт обратный вызов функции. Функция может принимать до 4 аргументов.
### Аргументы

- *Ret(*)()* **func** - Указатель на функцию.

### Возвращаемое значение

Указатель на обратный вызов.
## CallbackBase * MakeCallback ( Class * func )

Создаёт обратный вызов функции-члена класса. Функция может принимать до 4 аргументов.
### Аргументы

- *Class ** **func** - Указатель на функцию-член класса.

### Возвращаемое значение

Указатель на обратный вызов.
## template < typename Type >

## SpinLockTemplate ( volatile Type * ptr , const Type old_value , const Type new_value )

Пытается атомарно обновить *ptr с old_value на new_value с помощью операции *[AtomicCAS](#AtomicCAS_voidvolatileptr_voidptr_voidptr_bool)*. Если CAS завершается неудачей, входит в [spin-wait loop](../../../api/library/common/mt/class.backoffspinner_cpp.md), пока значение по *ptr не станет равным old_value и обновление не сможет быть повторено.
### Аргументы

- *volatile Type ** **ptr** - Указатель на разделяемую переменную
- *const Type* **old_value** - Ожидаемое текущее значение *ptr
- *const Type* **new_value** - Значение для записи, если *ptr == old_value


## void SpinLock ( volatile char * ptr , char old_value , char new_value )

Специализированная версия **[SpinLockTemplate](#SpinLockTemplate_volatiletmplptr_consttmpl_consttmpl)** для 8-битных значений.
### Аргументы

- *volatile char ** **ptr** - Указатель на разделяемую переменную
- *char* **old_value** - Ожидаемое текущее значение *ptr
- *char* **new_value** - Значение для записи, если *ptr == old_value


## void SpinLock ( volatile short * ptr , short old_value , short new_value )

Специализированная версия **[SpinLockTemplate](#SpinLockTemplate_volatiletmplptr_consttmpl_consttmpl)** для 16-битных значений.
### Аргументы

- *volatile short ** **ptr** - Указатель на разделяемую переменную
- *short* **old_value** - Ожидаемое текущее значение *ptr
- *short* **new_value** - Значение для записи, если *ptr == old_value


## void SpinLock ( volatile int * ptr , int old_value , int new_value )

Специализированная версия **[SpinLockTemplate](#SpinLockTemplate_volatiletmplptr_consttmpl_consttmpl)** для 32-битных значений.
### Аргументы

- *volatile int ** **ptr** - Указатель на разделяемую переменную
- *int* **old_value** - Ожидаемое текущее значение *ptr
- *int* **new_value** - Значение для записи, если *ptr == old_value


## void SpinLock ( volatile long long * ptr , long long old_value , long long new_value )

Специализированная версия **[SpinLockTemplate](#SpinLockTemplate_volatiletmplptr_consttmpl_consttmpl)** для 64-битных значений.
### Аргументы

- *volatile long long ** **ptr** - Указатель на разделяемую переменную
- *long long* **old_value** - Ожидаемое текущее значение *ptr
- *long long* **new_value** - Значение для записи, если *ptr == old_value


## void WaitLock ( volatile char * ptr , char value )

Пытается получить блокировку на основе активного ожидания, ожидая, пока значение, на которое указывает ptr, не станет равным указанному значению. Внутренне вызывает [SpinLock](#SpinLock_volatilechar_char_char_void) с одинаковыми старым и новым значениями, ожидая в цикле, пока *ptr == value.
### Аргументы

- *volatile char ** **ptr** - Указатель на 8-битную разделяемую переменную
- *char* **value** - Целевое значение, которого следует дождаться.


## void WaitLock ( volatile short * ptr , short old_value )

Пытается получить блокировку на основе активного ожидания, ожидая, пока значение, на которое указывает ptr, не станет равным указанному значению. Внутренне вызывает [SpinLock](#SpinLock_volatileshort_short_short_void) с одинаковыми старым и новым значениями, ожидая в цикле, пока *ptr == value.
### Аргументы

- *volatile short ** **ptr** - Указатель на 16-битную разделяемую переменную
- *short* **old_value** - Целевое значение, которого следует дождаться.


## void WaitLock ( volatile int * ptr , int old_value )

Пытается получить блокировку на основе активного ожидания, ожидая, пока значение, на которое указывает ptr, не станет равным указанному значению. Внутренне вызывает [SpinLock](#SpinLock_volatileint_int_int_void) с одинаковыми старым и новым значениями, ожидая в цикле, пока *ptr == value.
### Аргументы

- *volatile int ** **ptr** - Указатель на 32-битную разделяемую переменную
- *int* **old_value** - Целевое значение, которого следует дождаться.


## void WaitLock ( volatile long long * ptr , long long old_value )

Пытается получить блокировку на основе активного ожидания, ожидая, пока значение, на которое указывает ptr, не станет равным указанному значению. Внутренне вызывает [SpinLock](#SpinLock_volatilellong_llong_llong_void) с одинаковыми старым и новым значениями, ожидая в цикле, пока *ptr == value.
### Аргументы

- *volatile long long ** **ptr** - Указатель на 64-битную разделяемую переменную
- *long long* **old_value** - Целевое значение, которого следует дождаться.


## template < typename Type >

## void MutexSpinLock ( volatile Type & mutex )

Атомарно устанавливает mutex с 0 на 1. Использует соответствующий метод *[SpinLock](#SpinLock_volatilechar_char_char_void)*.
### Аргументы

- *volatile Type &* **mutex** - Ссылка на разделяемую переменную, действующую как спин-мьютекс. Значение 0 означает разблокированное состояние, 1 — заблокированное.


## template < typename Type >

## bool MutexSpinTryLock ( volatile Type & mutex )

Пытается атомарно заблокировать mutex без ожидания. Использует *[AtomicCAS](#AtomicCAS_voidvolatileptr_voidptr_voidptr_bool)* с 0 и 1.
### Аргументы

- *volatile Type &* **mutex** - Ссылка на разделяемую переменную, действующую как спин-мьютекс. Значение 0 означает разблокированное состояние, 1 — заблокированное.

### Возвращаемое значение

Возвращает true, если *[AtomicCAS](#AtomicCAS_voidvolatileptr_voidptr_voidptr_bool)* успешно поменял значения местами; иначе false.
## template < typename Type >

## void MutexSpinUnlock ( volatile Type & mutex )

Атомарно устанавливает значение mutex в 0 (разблокировано). Использует *[AtomicCAS](#AtomicCAS_voidvolatileptr_voidptr_voidptr_bool)*.
### Аргументы

- *volatile Type &* **mutex** - Ссылка на разделяемую переменную, действующую как спин-мьютекс. Значение 0 означает разблокированное состояние, 1 — заблокированное.


## template < typename Type >

## bool MutexSpinIsLocked ( volatile Type & mutex )

Проверяет, заблокирован ли mutex в данный момент.
### Аргументы

- *volatile Type &* **mutex** - Ссылка на разделяемую переменную, действующую как спин-мьютекс. Значение 0 означает разблокированное состояние, 1 — заблокированное.

### Возвращаемое значение

Возвращает true, если mutex в данный момент заблокирован (ненулевое значение); иначе false.
## template < typename Type >

## void MutexSpinWaitLock ( volatile Type & mutex )

Ожидает в цикле, пока значение mutex не станет 0, не изменяя его. Использует *[SpinLock](#SpinLock_volatileint_int_int_void)* с двумя нулями.
### Аргументы

- *volatile Type &* **mutex** - Ссылка на разделяемую переменную, действующую как спин-мьютекс. Значение 0 означает разблокированное состояние, 1 — заблокированное.


## char AtomicAnd ( volatile char * ptr , char value )

Атомарная побитовая операция Unigine **И** (8-бит).
### Аргументы

- *volatile char ** **ptr** - Указатель на переменную.
- *char* **value** - Битовая маска для применения через побитовое **И**. Останутся установленными только биты, установленные и в *ptr, и в value.

### Возвращаемое значение

Предыдущее значение (непосредственно перед побитовым **И**).
## short AtomicAnd ( volatile short * ptr , short value )

Атомарная побитовая операция Unigine **И** (16-бит).
### Аргументы

- *volatile short ** **ptr** - Указатель на переменную.
- *short* **value** - Битовая маска для применения через побитовое **И**. Останутся установленными только биты, установленные и в *ptr, и в value.

### Возвращаемое значение

Предыдущее значение (непосредственно перед побитовым **И**).
## int AtomicAnd ( volatile int * ptr , int value )

Атомарная побитовая операция Unigine **И** (32-бит).
### Аргументы

- *volatile int ** **ptr** - Указатель на переменную.
- *int* **value** - Битовая маска для применения через побитовое **И**. Останутся установленными только биты, установленные и в *ptr, и в value.

### Возвращаемое значение

Предыдущее значение (непосредственно перед побитовым **И**).
## long long AtomicAnd ( volatile long long * ptr , long long value )

Атомарная побитовая операция Unigine **И** (64-бит).
### Аргументы

- *volatile long long ** **ptr** - Указатель на переменную.
- *long long* **value** - Битовая маска для применения через побитовое **И**. Останутся установленными только биты, установленные и в *ptr, и в value.

### Возвращаемое значение

Предыдущее значение (непосредственно перед побитовым **И**).
## char AtomicOr ( volatile char * ptr , char value )

Атомарная побитовая операция Unigine **ИЛИ** (8-бит).
### Аргументы

- *volatile char ** **ptr** - Указатель на переменную.
- *char* **value** - Битовая маска для применения через побитовое **ИЛИ**. Останутся установленными биты, установленные в *ptr или в value.

### Возвращаемое значение

Предыдущее значение (непосредственно перед побитовым **ИЛИ**).
## char AtomicOr ( volatile char * ptr , char value )

Атомарная побитовая операция Unigine **ИЛИ** (16-бит).
### Аргументы

- *volatile char ** **ptr** - Указатель на переменную.
- *char* **value** - Битовая маска для применения через побитовое **ИЛИ**. Останутся установленными биты, установленные в *ptr или в value.

### Возвращаемое значение

Предыдущее значение (непосредственно перед побитовым **ИЛИ**).
## char AtomicOr ( volatile char * ptr , char value )

Атомарная побитовая операция Unigine **ИЛИ** (32-бит).
### Аргументы

- *volatile char ** **ptr** - Указатель на переменную.
- *char* **value** - Битовая маска для применения через побитовое **ИЛИ**. Останутся установленными биты, установленные в *ptr или в value.

### Возвращаемое значение

Предыдущее значение (непосредственно перед побитовым **ИЛИ**).
## char AtomicOr ( volatile char * ptr , char value )

Атомарная побитовая операция Unigine **ИЛИ** (64-бит).
### Аргументы

- *volatile char ** **ptr** - Указатель на переменную.
- *char* **value** - Битовая маска для применения через побитовое **ИЛИ**. Останутся установленными биты, установленные в *ptr или в value.

### Возвращаемое значение

Предыдущее значение (непосредственно перед побитовым **ИЛИ**).
## char AtomicXor ( volatile char * ptr , char value )

Атомарная побитовая операция Unigine **исключающее ИЛИ** (8-бит).
### Аргументы

- *volatile char ** **ptr** - Указатель на переменную.
- *char* **value** - Битовая маска для применения через побитовое **исключающее ИЛИ**. Биты, установленные в *ptr или в value, но не в обоих, будут инвертированы после операции.

### Возвращаемое значение

Предыдущее значение (непосредственно перед побитовым **исключающим ИЛИ**).
## char AtomicXor ( volatile char * ptr , char value )

Атомарная побитовая операция Unigine **исключающее ИЛИ** (16-бит).
### Аргументы

- *volatile char ** **ptr** - Указатель на переменную.
- *char* **value** - Битовая маска для применения через побитовое **исключающее ИЛИ**. Биты, установленные в *ptr или в value, но не в обоих, будут инвертированы после операции.

### Возвращаемое значение

Предыдущее значение (непосредственно перед побитовым **исключающим ИЛИ**).
## char AtomicXor ( volatile char * ptr , char value )

Атомарная побитовая операция Unigine **исключающее ИЛИ** (32-бит).
### Аргументы

- *volatile char ** **ptr** - Указатель на переменную.
- *char* **value** - Битовая маска для применения через побитовое **исключающее ИЛИ**. Биты, установленные в *ptr или в value, но не в обоих, будут инвертированы после операции.

### Возвращаемое значение

Предыдущее значение (непосредственно перед побитовым **исключающим ИЛИ**).
## char AtomicXor ( volatile char * ptr , char value )

Атомарная побитовая операция Unigine **исключающее ИЛИ** (64-бит).
### Аргументы

- *volatile char ** **ptr** - Указатель на переменную.
- *char* **value** - Битовая маска для применения через побитовое **исключающее ИЛИ**. Биты, установленные в *ptr или в value, но не в обоих, будут инвертированы после операции.

### Возвращаемое значение

Предыдущее значение (непосредственно перед побитовым **исключающим ИЛИ**).
## char AtomicAdd ( volatile char * ptr , char value )

Unigine atomic add (8-bit).
### Аргументы

- *volatile char ** **ptr** - Указатель на переменную.
- *char* **value** - Значение для добавления.

### Возвращаемое значение

Предыдущее значение (непосредственно перед сложением).
## short AtomicAdd ( volatile short * ptr , short value )

Unigine atomic add (16-bit).
### Аргументы

- *volatile short ** **ptr** - Указатель на переменную.
- *short* **value** - Значение для добавления.

### Возвращаемое значение

Предыдущее значение (непосредственно перед сложением).
## int AtomicAdd ( volatile int * ptr , int value )

Unigine atomic add (32-bit).
### Аргументы

- *volatile int ** **ptr** - Указатель на переменную.
- *int* **value** - Значение для добавления.

### Возвращаемое значение

Предыдущее значение (непосредственно перед сложением).
## long long AtomicAdd ( volatile long long * ptr , long long value )

Unigine atomic add (64-bit).
### Аргументы

- *volatile long long ** **ptr** - Указатель на переменную.
- *long long* **value** - Значение для добавления.

### Возвращаемое значение

Предыдущее значение (непосредственно перед сложением).
## char AtomicInc ( volatile char * ptr )

Unigine atomic increment (8-bit).
### Аргументы

- *volatile char ** **ptr** - Указатель на переменную.

### Возвращаемое значение

Предыдущее значение (непосредственно перед сложением).
## short AtomicInc ( volatile short * ptr )

Unigine atomic increment (16-bit).
### Аргументы

- *volatile short ** **ptr** - Указатель на переменную.

### Возвращаемое значение

Предыдущее значение (непосредственно перед сложением).
## int AtomicInc ( volatile int * ptr )

Unigine atomic increment (32-bit).
### Аргументы

- *volatile int ** **ptr** - Указатель на переменную.

### Возвращаемое значение

Предыдущее значение (непосредственно перед сложением).
## long long AtomicInc ( volatile long long * ptr )

Unigine atomic increment (64-bit).
### Аргументы

- *volatile long long ** **ptr** - Указатель на переменную.

### Возвращаемое значение

Предыдущее значение (непосредственно перед сложением).
## char AtomicDec ( volatile char * ptr )

Unigine atomic decrement (8-bit).
### Аргументы

- *volatile char ** **ptr** - Указатель на переменную.

### Возвращаемое значение

Предыдущее значение (непосредственно перед вычитанием).
## short AtomicDec ( volatile short * ptr )

Unigine atomic decrement (16-bit).
### Аргументы

- *volatile short ** **ptr** - Указатель на переменную.

### Возвращаемое значение

Предыдущее значение (непосредственно перед вычитанием).
## int AtomicDec ( volatile int * ptr )

Атомарный декремент Unigine (32-бит).
### Аргументы

- *volatile int ** **ptr** - Указатель на переменную.

### Возвращаемое значение

Предыдущее значение (непосредственно перед вычитанием).
## long long AtomicDec ( volatile long long * ptr )

Атомарный декремент Unigine (64-бит).
### Аргументы

- *volatile long long ** **ptr** - Указатель на переменную.

### Возвращаемое значение

Предыдущее значение (непосредственно перед вычитанием).
## bool AtomicCAS ( volatile char * ptr , char old_value , char new_value )

Атомарное сравнение с обменом (compare and swap) Unigine (8-бит).
### Аргументы

- *volatile char ** **ptr** - Указатель на переменную.
- *char* **old_value** - Старое значение указателя.
- *char* **new_value** - Новое значение указателя.

### Возвращаемое значение

**true**, если значение переменной было успешно заменено; иначе **false**.
## bool AtomicCAS ( volatile short * ptr , short old_value , short new_value )

Атомарное сравнение с обменом (compare and swap) Unigine (16-бит).
### Аргументы

- *volatile short ** **ptr** - Указатель на переменную.
- *short* **old_value** - Старое значение указателя.
- *short* **new_value** - Новое значение указателя.

### Возвращаемое значение

**true**, если значение переменной было успешно заменено; иначе **false**.
## bool AtomicCAS ( volatile int * ptr , int old_value , int new_value )

Атомарное сравнение с обменом (compare and swap) Unigine (32-бит).
### Аргументы

- *volatile int ** **ptr** - Указатель на переменную.
- *int* **old_value** - Старое значение указателя.
- *int* **new_value** - Новое значение указателя.

### Возвращаемое значение

**true**, если значение переменной было успешно заменено; иначе **false**.
## bool AtomicCAS ( volatile long long * ptr , long long old_value , long long new_value )

Атомарное сравнение с обменом (compare and swap) Unigine (64-бит).
### Аргументы

- *volatile long long ** **ptr** - Указатель на переменную.
- *long long* **old_value** - Старое значение указателя.
- *long long* **new_value** - Новое значение указателя.

### Возвращаемое значение

**true**, если значение переменной было успешно заменено; иначе **false**.
## bool AtomicCAS ( void *volatile * ptr , void * old_value , void * new_value )

Атомарное сравнение с обменом (compare and swap) Unigine (указатель).
### Аргументы

- *void *volatile ** **ptr** - Указатель на переменную.
- *void ** **old_value** - Старое значение указателя.
- *void ** **new_value** - Новое значение указателя.

### Возвращаемое значение

**true**, если значение переменной было успешно заменено; иначе **false**.
## void AtomicSet ( volatile char * ptr , char value )

Атомарная установка значения Unigine (8-бит).
### Аргументы

- *volatile char ** **ptr** - Указатель на переменную.
- *char* **value** - Значение для установки.


## void AtomicSet ( volatile bool * ptr , bool value )

Атомарная установка значения Unigine (8-бит).
### Аргументы

- *volatile bool ** **ptr** - Указатель на переменную.
- *bool* **value** - Значение для установки.


## void AtomicSet ( volatile short * ptr , short value )

Атомарная установка значения Unigine (16-бит).
### Аргументы

- *volatile short ** **ptr** - Указатель на переменную.
- *short* **value** - Значение для установки.


## void AtomicSet ( volatile int * ptr , int value )

Атомарная установка значения Unigine (32-бит).
### Аргументы

- *volatile int ** **ptr** - Указатель на переменную.
- *int* **value** - Значение для установки.


## void AtomicSet ( volatile long long * ptr , long long value )

Атомарная установка значения Unigine (64-бит).
### Аргументы

- *volatile long long ** **ptr** - Указатель на переменную.
- *long long* **value** - Значение для установки.


## char AtomicGet ( volatile char * ptr )

Атомарное чтение Unigine (8-бит). Прямое обращение к переменной небезопасно!
### Аргументы

- *volatile char ** **ptr** - Указатель на переменную.

### Возвращаемое значение

Значение переменной.
## bool AtomicGet ( volatile bool * ptr )

Атомарное чтение Unigine (8-бит). Прямое обращение к переменной небезопасно!
### Аргументы

- *volatile bool ** **ptr** - Указатель на переменную.

### Возвращаемое значение

Значение переменной.
## short AtomicGet ( volatile short * ptr )

Атомарное чтение Unigine (16-бит). Прямое обращение к переменной небезопасно!
### Аргументы

- *volatile short ** **ptr** - Указатель на переменную.

### Возвращаемое значение

Значение переменной.
## int AtomicGet ( volatile int * ptr )

Атомарное чтение Unigine (32-бит). Прямое обращение к переменной небезопасно!
### Аргументы

- *volatile int ** **ptr** - Указатель на переменную.

### Возвращаемое значение

Значение переменной.
## long long AtomicGet ( volatile long long * ptr )

Атомарное чтение Unigine (64-бит). Прямое обращение к переменной небезопасно!
### Аргументы

- *volatile long long ** **ptr** - Указатель на переменную.

### Возвращаемое значение

Значение переменной.
## char AtomicSwap ( volatile char * ptr , char value )

Атомарный обмен значения Unigine (8-бит).
### Аргументы

- *volatile char ** **ptr** - Указатель на переменную.
- *char* **value** - Значение для установки.

### Возвращаемое значение

Предыдущее значение (непосредственно перед установкой).
## bool AtomicSwap ( volatile bool * ptr , bool value )

Атомарный обмен значения Unigine (8-бит).
### Аргументы

- *volatile bool ** **ptr** - Указатель на переменную.
- *bool* **value** - Значение для установки.

### Возвращаемое значение

Предыдущее значение (непосредственно перед установкой).
## short AtomicSwap ( volatile short * ptr , short value )

Атомарный обмен значения Unigine (16-бит).
### Аргументы

- *volatile short ** **ptr** - Указатель на переменную.
- *short* **value** - Значение для установки.

### Возвращаемое значение

Предыдущее значение (непосредственно перед установкой).
## int AtomicSwap ( volatile int * ptr , int value )

Атомарный обмен значения Unigine (32-бит).
### Аргументы

- *volatile int ** **ptr** - Указатель на переменную.
- *int* **value** - Значение для установки.

### Возвращаемое значение

Предыдущее значение (непосредственно перед установкой).
## long long AtomicSwap ( volatile long long * ptr , long long value )

Атомарный обмен значения Unigine (64-бит).
### Аргументы

- *volatile long long ** **ptr** - Указатель на переменную.
- *long long* **value** - Значение для установки.

### Возвращаемое значение

Предыдущее значение (непосредственно перед установкой).
## void quickSort ( Type * array , int size )

Сортирует входной массив с использованием алгоритма сравнения по умолчанию.
### Аргументы

- *Type ** **array** - Указатель на массив.
- *int* **size** - Размер массива.


## void quickSort ( Type * array , int size , Compare compare )

Сортирует входной массив с использованием указанного функтора сравнения.
### Аргументы

- *Type ** **array** - Указатель на массив.
- *int* **size** - Размер массива.
- *Compare* **compare** - Функтор сравнения.


## void quickSort ( Type * array , int size , int(*)(A0, A1) func )

Сортирует входной массив с использованием указанной функции сравнения.
### Аргументы

- *Type ** **array** - Указатель на массив.
- *int* **size** - Размер массива.
- *int(*)(A0, A1)* **func** - Функция сравнения.


## void quickDoubleSort ( Type * array , Data * data , int size )

Сортирует входной массив с использованием алгоритма сравнения по умолчанию.
### Аргументы

- *Type ** **array** - Указатель на массив.
- *Data ** **data** - Указатель на данные.
- *int* **size** - Размер массива.


## void quickDoubleSort ( Type * array , Data * data , int size , Compare compare )

Сортирует входной массив с использованием указанного функтора сравнения.
### Аргументы

- *Type ** **array** - Указатель на массив.
- *Data ** **data** - Указатель на данные.
- *int* **size** - Размер массива.
- *Compare* **compare** - Функтор сравнения.


## void quickDoubleSort ( Type * array , Data * data , int size , int(*)(A0, A1) func )

Сортирует входной массив с использованием указанной функции сравнения.
### Аргументы

- *Type ** **array** - Указатель на массив.
- *Data ** **data** - Указатель на данные.
- *int* **size** - Размер массива.
- *int(*)(A0, A1)* **func** - Функция сравнения.


## template < typename State , typename Process , typename Destroy >

## CPUShader * makeCPUShader ( Process func_process , Destroy func_destroy , CPUShader::PoolType pool_ = CPUShader::PoolType::Auto , CPUShader::Priority priority_ = CPUShader::Priority::Normal , CPUShader::FrameSyncMode frame_sync_ = CPUShader::FrameSyncMode::Swap , CPUShader::WaitMode wait_mode_ = CPUShader::WaitMode::Auto )

Создаёт **[CPUShaderCallable](../../../api/library/common/mt/class.cpushadercallable_cpp.md)** в куче с логикой обработки, логикой очистки и разделяемым состоянием типа **State**.
### Аргументы

- *Process* **func_process** - Функция, выполняемая в каждом потоке. Сигнатура: *void(CPUShader *shader, int thread_num, int num_threads)*.
- *Destroy* **func_destroy** - Функция очистки, вызываемая при уничтожении. Сигнатура: *void(State state)*.
- *[CPUShader::PoolType](#PoolType)* **pool_** - Целевой пул выполнения.
- *[CPUShader::Priority](#Priority)* **priority_** - Приоритет задачи в очереди пула.
- *[CPUShader::FrameSyncMode](#FrameSyncMode)* **frame_sync_** - Режим синхронизации кадра.
- *[CPUShader::WaitMode](#WaitMode)* **wait_mode_** - Стратегия ожидания для [wait()](../../../api/library/common/mt/class.cpushader_cpp.md#wait_void).

### Возвращаемое значение

Экземпляр шейдера, выделенный в куче. Ответственность за удаление лежит на вызывающей стороне.
## template < typename State , typename Process >

## CPUShader * makeCPUShader ( Process func_process , CPUShader::PoolType pool_ = CPUShader::PoolType::Auto , CPUShader::Priority priority_ = CPUShader::Priority::Normal , CPUShader::FrameSyncMode frame_sync_ = CPUShader::FrameSyncMode::Swap , CPUShader::WaitMode wait_mode_ = CPUShader::WaitMode::Auto )

Создаёт **[CPUShaderCallable](../../../api/library/common/mt/class.cpushadercallable_cpp.md)** в куче с логикой обработки и разделяемым состоянием типа **State**. Используется пустая функция очистки (no-op).
### Аргументы

- *Process* **func_process** - Функция, выполняемая в каждом потоке. Сигнатура: *void(CPUShader *shader, int thread_num, int num_threads)*.
- *[CPUShader::PoolType](#PoolType)* **pool_** - Целевой пул выполнения.
- *[CPUShader::Priority](#Priority)* **priority_** - Приоритет задачи в очереди пула.
- *[CPUShader::FrameSyncMode](#FrameSyncMode)* **frame_sync_** - Режим синхронизации кадра.
- *[CPUShader::WaitMode](#WaitMode)* **wait_mode_** - Стратегия ожидания для [wait()](../../../api/library/common/mt/class.cpushader_cpp.md#wait_void).

### Возвращаемое значение

Экземпляр шейдера, выделенный в куче. Ответственность за удаление лежит на вызывающей стороне.
## template < typename Process >

## CPUShader * makeCPUShaderStateless ( Process func_process , CPUShader::PoolType pool_ = CPUShader::PoolType::Auto , CPUShader::Priority priority_ = CPUShader::Priority::Normal , CPUShader::FrameSyncMode frame_sync_ = CPUShader::FrameSyncMode::Swap , CPUShader::WaitMode wait_mode_ = CPUShader::WaitMode::Auto )

Создаёт **[CPUShaderCallableStateless](../../../api/library/common/mt/class.cpushadercallablestateless_cpp.md)** в куче с логикой обработки и без разделяемого состояния.
### Аргументы

- *Process* **func_process** - Функция, выполняемая в каждом потоке. Сигнатура: *void(CPUShader *shader, int thread_num, int num_threads)*.
- *[CPUShader::PoolType](#PoolType)* **pool_** - Целевой пул выполнения.
- *[CPUShader::Priority](#Priority)* **priority_** - Приоритет задачи в очереди пула.
- *[CPUShader::FrameSyncMode](#FrameSyncMode)* **frame_sync_** - Режим синхронизации кадра.
- *[CPUShader::WaitMode](#WaitMode)* **wait_mode_** - Стратегия ожидания для [wait()](../../../api/library/common/mt/class.cpushader_cpp.md#wait_void).

### Возвращаемое значение

Экземпляр шейдера, выделенный в куче. Ответственность за удаление лежит на вызывающей стороне.
## template < typename Process >

## CPUShaderCallableStateless<Process> makeScopeCPUShaderStateless ( Process func_process , CPUShader::PoolType pool_ = CPUShader::PoolType::Auto , CPUShader::Priority priority_ = CPUShader::Priority::Normal , CPUShader::FrameSyncMode frame_sync_ = CPUShader::FrameSyncMode::Swap , CPUShader::WaitMode wait_mode_ = CPUShader::WaitMode::Auto )

Создаёт **[CPUShaderCallableStateless](../../../api/library/common/mt/class.cpushadercallablestateless_cpp.md)** на стеке (по значению). Шейдер уничтожается при выходе из области видимости.
### Аргументы

- *Process* **func_process** - Функция, выполняемая в каждом потоке. Сигнатура: *void(CPUShader *shader, int thread_num, int num_threads)*.
- *[CPUShader::PoolType](#PoolType)* **pool_** - Целевой пул выполнения.
- *[CPUShader::Priority](#Priority)* **priority_** - Приоритет задачи в очереди пула.
- *[CPUShader::FrameSyncMode](#FrameSyncMode)* **frame_sync_** - Режим синхронизации кадра.
- *[CPUShader::WaitMode](#WaitMode)* **wait_mode_** - Стратегия ожидания для [wait()](../../../api/library/common/mt/class.cpushader_cpp.md#wait_void).

### Возвращаемое значение

Экземпляр шейдера, выделенный на стеке.
## template < typename Process >

## void runSyncMultiThreadFunc ( Process func_process , int num_threads = -1 , CPUShader::PoolType pool_ = CPUShader::PoolType::Auto , CPUShader::Priority priority_ = CPUShader::Priority::Normal , CPUShader::FrameSyncMode frame_sync_ = CPUShader::FrameSyncMode::Swap , CPUShader::WaitMode wait_mode_ = CPUShader::WaitMode::Auto )

Удобная функция, которая создаёт **[CPUShaderCallableStateless](../../../api/library/common/mt/class.cpushadercallablestateless_cpp.md)** на стеке, запускает его синхронно через [runSync()](../../../api/library/common/mt/class.cpushader_cpp.md#runSync_int_void) и возвращает управление после завершения всех потоков.
### Аргументы

- *Process* **func_process** - Функция, выполняемая в каждом потоке. Сигнатура: *void(CPUShader *shader, int thread_num, int num_threads)*.
- *int* **num_threads** - Количество используемых потоков. Значение -1 означает использование количества потоков пула по умолчанию.
- *[CPUShader::PoolType](#PoolType)* **pool_** - Целевой пул выполнения.
- *[CPUShader::Priority](#Priority)* **priority_** - Приоритет задачи в очереди пула.
- *[CPUShader::FrameSyncMode](#FrameSyncMode)* **frame_sync_** - Режим синхронизации кадра.
- *[CPUShader::WaitMode](#WaitMode)* **wait_mode_** - Стратегия ожидания для [wait()](../../../api/library/common/mt/class.cpushader_cpp.md#wait_void).


## template < typename Callable >

## CPUTask * makeCPUTask ( Callable callable , CPUTask::Priority priority_ = CPUTask::Priority::Normal , CPUTask::FrameSyncMode frame_sync_ = CPUTask::FrameSyncMode::Disabled )

Создаёт **[AsyncTaskCallable](../../../api/library/common/mt/class.asynctaskcallable_cpp.md)** в куче с логикой обработки. Используется пустая функция очистки (no-op).
### Аргументы

- *Callable* **callable** - Функция, выполняемая при запуске задачи. Сигнатура: *void(CPUTask *task)*.
- *[CPUTask::Priority](#Priority)* **priority_** - Приоритет задачи в очереди пула.
- *[CPUTask::FrameSyncMode](#FrameSyncMode)* **frame_sync_** - Режим синхронизации кадра.

### Возвращаемое значение

Экземпляр задачи, выделенный в куче. Ответственность за удаление лежит на вызывающей стороне.
## template < typename Callable , typename Destroy >

## CPUTask * makeCPUTask ( Callable callable , Destroy destroy , CPUTask::Priority priority_ = CPUTask::Priority::Normal , CPUTask::FrameSyncMode frame_sync_ = CPUTask::FrameSyncMode::Disabled )

Создаёт **[AsyncTaskCallable](../../../api/library/common/mt/class.asynctaskcallable_cpp.md)** в куче с логикой обработки и пользовательской функцией очистки.
### Аргументы

- *Callable* **callable** - Функция, выполняемая при запуске задачи. Сигнатура: *void(CPUTask *task)*.
- *Destroy* **destroy** - Функция очистки, вызываемая при уничтожении. Сигнатура: *void()*.
- *[CPUTask::Priority](#Priority)* **priority_** - Приоритет задачи в очереди пула.
- *[CPUTask::FrameSyncMode](#FrameSyncMode)* **frame_sync_** - Режим синхронизации кадра.

### Возвращаемое значение

Экземпляр задачи, выделенный в куче. Ответственность за удаление лежит на вызывающей стороне.
