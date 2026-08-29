# Класс Unigine::VectorStack (CPP)

**Заголовочный файл:** #include <UnigineVector.h>

**Наследуется от:** Vector


## Класс VectorStack

### Методы класса

---

## VectorStack ( )

## VectorStack ( std::initializer_list<Type> list )

### Аргументы

- *std::initializer_list<Type>* **list**

## VectorStack ( const VectorStack& o )

### Аргументы

- *const VectorStack&* **o**

## VectorStack ( VectorStack&& o )

### Аргументы

- *VectorStack&&* **o**

## VectorStack ( size_t size )

### Аргументы

- *size_t* **size**

## VectorStack ( const Type& t , size_t size )

### Аргументы

- *const Type&* **t**
- *size_t* **size**

## VectorStack ( const Type* v , size_t size )

### Аргументы

- *const Type** **v**
- *size_t* **size**

## void VectorStack<Type, Capacity, Counter> ( const VectorStack <Type,OtherCapacity,OtherCounter>& o )

### Аргументы

- *const [VectorStack](../../../../api/library/containers/vector/class.vectorstack_cpp.md)<Type,OtherCapacity,OtherCounter>&* **o**

## void VectorStack<Type, Capacity, Counter> ( VectorStack <Type,OtherCapacity,OtherCounter>& o )

### Аргументы

- *[VectorStack](../../../../api/library/containers/vector/class.vectorstack_cpp.md)<Type,OtherCapacity,OtherCounter>&* **o**

## void VectorStack<Type, Capacity, Counter> ( const Vector <Type,OtherCounter>& o )

### Аргументы

- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<Type,OtherCounter>&* **o**

## void VectorStack<Type, Capacity, Counter> ( Vector <Type,OtherCounter>& o )

### Аргументы

- *[Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<Type,OtherCounter>&* **o**

## VectorStack <Type, Capacity, Counter> & operator= ( const VectorStack& v )

### Аргументы

- *const VectorStack&* **v**

## VectorStack <Type, Capacity, Counter> & operator= ( VectorStack&& v )

### Аргументы

- *VectorStack&&* **v**

## VectorStack <Type, Capacity, Counter> & operator= ( const VectorStack <Type,OtherCapacity,OtherCounter>& v )

### Аргументы

- *const [VectorStack](../../../../api/library/containers/vector/class.vectorstack_cpp.md)<Type,OtherCapacity,OtherCounter>&* **v**

## VectorStack <Type, Capacity, Counter> & operator= ( VectorStack <Type,OtherCapacity,OtherCounter>& v )

### Аргументы

- *[VectorStack](../../../../api/library/containers/vector/class.vectorstack_cpp.md)<Type,OtherCapacity,OtherCounter>&* **v**

## VectorStack <Type, Capacity, Counter> & operator= ( const Vector <Type,OtherCounter>& v )

### Аргументы

- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<Type,OtherCounter>&* **v**

## VectorStack <Type, Capacity, Counter> & operator= ( Vector <Type,OtherCounter>& v )

### Аргументы

- *[Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<Type,OtherCounter>&* **v**

## size_t getMemoryUsage ( ) const

## void destroy ( )
