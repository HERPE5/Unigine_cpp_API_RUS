# Unigine::Hasher class (CPP)

**Header:** #include <UnigineHash.h>


Класс Hasher преобразует любые типы данных (строку, структуру и т. д.) в индексы, поддерживаемые хеш-таблицами.


## Hasher Class

### Методы класса

---

## HashType create ( const Type & v )

Преобразует заданное значение в тип, поддерживаемый хеш-таблицей. Например, хеш для типа String будет сгенерирован следующим образом:
```cpp
struct Hasher<String>
{
	using HashType = unsigned int;
	UNIGINE_INLINE static HashType create(const char *v) { return String::hash(v); }
	UNIGINE_INLINE static HashType create(const String &v) { return String::hash(v.get(), v.size()); }
};

```


### Аргументы

- *const Type &* **v** - Значение для преобразования.

### Возвращаемое значение

Преобразованное значение, поддерживаемое хеш-таблицей.
