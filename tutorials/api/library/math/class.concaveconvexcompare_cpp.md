# Unigine::ConcaveConvexCompare Class (CPP)

**Header:** #include <UnigineMathLibConcave.h>


Эта структура используется для сравнения объёмов выпуклых форм. Она может передаваться в функции сортировки в качестве метода сравнения.


## ConcaveConvexCompare Class

### Методы класса

---

## int operator() ( const Convex* c0 , const Convex* c1 )

Сравнивает объём двух выпуклых форм.
### Аргументы

- *const Convex** **c0** - Первая форма.
- *const Convex** **c1** - Вторая форма.

### Возвращаемое значение

1, если объём первой формы больше объёма второй формы; иначе 0.
