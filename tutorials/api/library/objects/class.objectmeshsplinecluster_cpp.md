# ObjectMeshSplineCluster Class (CPP)

**Header:** #include <UnigineObjects.h>

**Inherits from:** Object


## ObjectMeshSplineCluster Class

### Методы класса

---

## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [Node](../../../api/library/nodes/class.node_cpp.md).
## const char * getMeshPath ( ) const

Возвращает путь к текущему исходному файлу меша для объекта.
### Возвращаемое значение

Путь к исходному файлу меша.
## int getNumMeshes ( ) const

Возвращает общее количество мешей, обрабатываемых кластером мешей по сплайну.
### Возвращаемое значение

Количество мешей.
## Math:: mat4 getMeshTransform ( int num ) const

Возвращает трансформацию заданного экземпляра меша.
### Аргументы

- *int* **num** - Номер экземпляра меша.

### Возвращаемое значение

Матрица трансформации меша.
## bool getClusterTransforms ( const Math:: WorldBoundBox & bounds , Vector < Math:: mat4 > & OUT_transforms )

Собирает трансформации (локальные координаты) для всех мешей кластера по сплайну в пределах области, заданной указанным ограничивающим боксом, и помещает их в указанный буфер.
### Аргументы

- *const  Math::[WorldBoundBox](../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bounds** - Ограничивающий бокс, определяющий область, для которой должны быть собраны трансформации мешей кластера по сплайну.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[mat4](../../../api/library/math/class.mat4_cpp.md)> &* **OUT_transforms** - Буфер для хранения трансформаций мешей кластера по сплайну. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

### Возвращаемое значение

true, если трансформации мешей кластера по сплайну найдены; либо false, если трансформации мешей кластера по сплайну не найдены.
## bool getClusterWorldTransforms ( const Math:: WorldBoundBox & bounds , Vector < Math:: Mat4 > & OUT_transforms )

Собирает трансформации (мировые координаты) для всех мешей кластера по сплайну в пределах области, заданной указанным ограничивающим боксом, и помещает их в указанный буфер.
### Аргументы

- *const  Math::[WorldBoundBox](../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bounds** - Ограничивающий бокс, определяющий область, для которой должны быть собраны трансформации мешей кластера по сплайну.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[Mat4](../../../api/library/math/class.mat4_cpp.md)> &* **OUT_transforms** - Буфер для хранения трансформаций мешей кластера по сплайну. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

### Возвращаемое значение

true, если трансформации мешей кластера по сплайну найдены; либо false, если трансформации мешей кластера по сплайну не найдены.
