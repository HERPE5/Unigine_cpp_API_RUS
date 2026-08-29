# ObjectMeshCluster Class (CPP)

**Header:** #include <UnigineObjects.h>

**Inherits from:** Object


Класс [MeshCluster](../../../objects/objects/mesh_cluster/index.md) позволяет запекать идентичные меши (с одним и тем же материалом, применённым к их поверхностям) в один объект, что уменьшает загруженность пространственного дерева, сокращает количество выборок текстур и ускоряет рендеринг.


Меши отрисовываются в пределах заданной [visible distance](#setVisibleDistance_float_void) от камеры. При удалении за эту дистанцию меши [fade out](#setFadeDistance_float_void), а затем полностью исчезают.


### See Also


- C# Component samples:

  -
  -
- C++ samples:

  -
  -

  -
  -


## ObjectMeshCluster Class

### Методы класса

---

## static ObjectMeshClusterPtr create ( const char * path )

Конструктор ObjectMeshCluster. Создаёт кластер мешей с исходным мешем, загруженным из указанного файла.
### Аргументы

- *const char ** **path** - Путь к файлу исходного меша.

## static ObjectMeshClusterPtr create ( )

Конструктор ObjectMeshCluster. Создаёт пустой кластер мешей
## void setFadeDistance ( float distance )

Задаёт дистанцию, в пределах которой меши, обрабатываемые кластером мешей, будут затухать (то есть будет отрисовываться меньше мешей, а не все). Дистанция отсчитывается начиная с [visible distance](#setVisibleDistance_float_void). Значение по умолчанию: 0. Использование дистанции затухания позволяет объектам исчезать по одному, пока к концу этой дистанции не останется лишь несколько. Это делает исчезновение плавным и намного менее заметным.
### Аргументы

- *float* **distance** - Дистанция затухания для мешей, в единицах. Если указано отрицательное значение, вместо него будет использовано 0.

## float getFadeDistance ( ) const

Возвращает дистанцию, в пределах которой меши, обрабатываемые кластером мешей, будут затухать. Значение по умолчанию: 0.
### Возвращаемое значение

Дистанция затухания для мешей, в единицах.
## void setMeshPath ( const char * path )

Задаёт путь к мешу, обрабатываемому *Mesh Cluster*. Не обновляет меш немедленно с использованием нового пути. Если меш находится в процедурном режиме, он будет сброшен.
### Аргументы

- *const char ** **path** - Новый путь к исходному *.mesh*-файлу для установки.

## const char * getMeshPath ( ) const

Возвращает путь к исходному *.mesh*-файлу меша, обрабатываемого *Mesh Cluster*.
### Возвращаемое значение

Путь к исходному *.mesh*-файлу.
## int addMeshTransform ( )

Добавляет новую трансформацию экземпляра меша в *Mesh Cluster*. Чтобы задать новую добавленную трансформацию, передайте возвращаемое значение этого метода в метод [*setMeshTransform()*](#setMeshTransform_int_mat4_void).
### Возвращаемое значение

Номер последнего добавленного экземпляра меша.
## void setMeshTransform ( int num , const Math:: mat4 & transform )

Задаёт трансформацию для указанного экземпляра меша.
### Аргументы

- *int* **num** - Номер экземпляра меша.
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации меша.

## Math:: mat4 getMeshTransform ( int num ) const

Возвращает трансформацию указанного экземпляра меша.
### Аргументы

- *int* **num** - Номер экземпляра меша.

### Возвращаемое значение

Матрица трансформации меша.
## void removeMeshTransform ( int num )

Удаляет трансформацию указанного экземпляра меша из кластера.
### Аргументы

- *int* **num** - Номер экземпляра меша.

## void removeMeshTransformFast ( int num )

Удаляет трансформацию указанного экземпляра меша из кластера.
### Аргументы

- *int* **num** - Номер экземпляра меша.

## int getNumMeshes ( ) const

Возвращает общее количество мешей, обрабатываемых кластером мешей.
### Возвращаемое значение

Количество мешей.
## void setVisibleDistance ( float distance )

Задаёт дистанцию, в пределах которой будут отрисовываться меши, обрабатываемые кластером мешей. Значение по умолчанию: бесконечность (в этом случае [fade distance](#setFadeDistance_float_void) будет игнорироваться).
### Аргументы

- *float* **distance** - Дистанция видимости для мешей, в единицах. Если указано отрицательное значение, вместо него будет использовано 0.

## float getVisibleDistance ( ) const

Возвращает дистанцию, в пределах которой отрисовываются меши, обрабатываемые кластером мешей. Значение по умолчанию: бесконечность (в этом случае [fade distance](#setFadeDistance_float_void) игнорируется).
### Возвращаемое значение

Дистанция видимости для мешей, в единицах.
## void clearMeshes ( )

Удаляет все меши, в данный момент запечённые в кластер мешей.
## void createMeshes ( const Vector < Math:: Mat4 > & world_transforms )

Создаёт меши в соответствии с вектором трансформаций (в мировых координатах) и запекает их в кластер. Все запечённые меши идентичны исходному [mesh](#getMeshPath_cstr) и имеют один и тот же материал, применённый к их поверхностям.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[Mat4](../../../api/library/math/class.mat4_cpp.md)> &* **world_transforms** - Вектор трансформаций в мировых координатах.

## void appendMeshes ( const Vector < Math:: Mat4 > & world_transforms )

Добавляет новые меши с трансформациями, хранящимися в указанном векторе (в мировых координатах), и запекает их в кластер. Все запечённые меши идентичны исходному [mesh](#getMeshPath_cstr) и имеют один и тот же материал, применённый к их поверхностям.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[Mat4](../../../api/library/math/class.mat4_cpp.md)> &* **world_transforms** - Вектор трансформаций в мировых координатах.

## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [Node](../../../api/library/nodes/class.node_cpp.md).
## bool removeClusterTransforms ( const Math:: WorldBoundBox & bb )

Удаляет меши кластера, найденные в пределах указанного ограничивающего объёма, из кластера.
### Аргументы

- *const  Math::[WorldBoundBox](../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb** - Ограничивающий объём, определяющий область, в пределах которой меши кластера должны быть удалены из кластера.

### Возвращаемое значение

true, если меши кластера, найденные в пределах указанного ограничивающего объёма, успешно удалены; иначе false.
## bool removeClusterTransformsFromSphere ( const Math:: WorldBoundSphere & bb )

Удаляет меши кластера, найденные в пределах указанной ограничивающей сферы, из кластера.
### Аргументы

- *const  Math::[WorldBoundSphere](../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bb** - Ограничивающая сфера, определяющая область, для которой должны быть собраны трансформации мешей кластера.

### Возвращаемое значение

**true**, если меши кластера, найденные в пределах указанной ограничивающей сферы, успешно удалены; иначе **false**.
## bool detachClusterTransforms ( const Math:: WorldBoundBox & bb , Vector < Math:: mat4 > & OUT_transforms )

Открепляет меши кластера, найденные в области, заданной указанным ограничивающим объёмом, от кластера и записывает их трансформации (в локальных координатах) в указанный буфер.
### Аргументы

- *const  Math::[WorldBoundBox](../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb** - Ограничивающий объём, определяющий область, в пределах которой меши кластера должны быть откреплены от кластера.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[mat4](../../../api/library/math/class.mat4_cpp.md)> &* **OUT_transforms** - Буфер для хранения трансформаций открепляемых мешей кластера. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

### Возвращаемое значение

true, если меши кластера были откреплены от кластера; иначе false.
## bool detachClusterWorldTransforms ( const Math:: WorldBoundBox & bb , Vector < Math:: Mat4 > & OUT_transforms )

Открепляет меши кластера, найденные в области, заданной указанным ограничивающим объёмом, от кластера и записывает их трансформации (в мировых координатах) в указанный буфер.
### Аргументы

- *const  Math::[WorldBoundBox](../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb** - Ограничивающий объём, определяющий область, в пределах которой меши кластера должны быть откреплены от кластера.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[Mat4](../../../api/library/math/class.mat4_cpp.md)> &* **OUT_transforms** - Буфер для хранения трансформаций открепляемых мешей кластера. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

### Возвращаемое значение

true, если меши кластера были откреплены от кластера; иначе false.
## bool detachClusterWorldTransformsFromSphere ( const Math:: WorldBoundSphere & bb , Vector < Math:: Mat4 > & OUT_transforms )

Открепляет меши кластера, найденные в области, заданной указанным ограничивающим объёмом, от кластера и записывает их трансформации (в мировых координатах) в указанный буфер.
### Аргументы

- *const  Math::[WorldBoundSphere](../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bb** - Ограничивающая сфера, определяющая область, для которой должны быть собраны трансформации мешей кластера.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[Mat4](../../../api/library/math/class.mat4_cpp.md)> &* **OUT_transforms** - Буфер для хранения трансформаций мешей кластера в мировых координатах. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

### Возвращаемое значение

true, если меши кластера были откреплены от кластера; иначе false.
## bool getClusterTransforms ( const Math:: WorldBoundBox & bounds , Vector < Math:: mat4 > & OUT_transforms )

Собирает трансформации (в локальных координатах) для всех мешей кластера в пределах области, заданной указанным ограничивающим объёмом, и записывает их в указанный буфер.
### Аргументы

- *const  Math::[WorldBoundBox](../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bounds** - Ограничивающий объём, определяющий область, для которой должны быть собраны трансформации мешей кластера.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[mat4](../../../api/library/math/class.mat4_cpp.md)> &* **OUT_transforms** - Буфер для хранения трансформаций мешей кластера. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

### Возвращаемое значение

true, если найдены трансформации мешей кластера; или false, если трансформации мешей кластера не найдены.
## bool getClusterWorldTransforms ( const Math:: WorldBoundBox & bounds , Vector < Math:: Mat4 > & OUT_transforms )

Собирает трансформации (в мировых координатах) для всех мешей кластера в пределах области, заданной указанным ограничивающим объёмом, и записывает их в указанный буфер.
### Аргументы

- *const  Math::[WorldBoundBox](../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bounds** - Ограничивающий объём, определяющий область, для которой должны быть собраны трансформации мешей кластера.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[Mat4](../../../api/library/math/class.mat4_cpp.md)> &* **OUT_transforms** - Буфер для хранения трансформаций мешей кластера в мировых координатах. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

### Возвращаемое значение

true, если найдены трансформации мешей кластера; или false, если трансформации мешей кластера в пределах указанной области не найдены.
## bool getClusterWorldTransformsFromSphere ( const Math:: WorldBoundSphere & bounds , Vector < Math:: Mat4 > & OUT_transforms )

Собирает трансформации (в мировых координатах) для всех мешей кластера в пределах области, заданной указанной ограничивающей сферой, и записывает их в указанный буфер.
### Аргументы

- *const  Math::[WorldBoundSphere](../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bounds** - Ограничивающая сфера, определяющая область, для которой должны быть собраны трансформации мешей кластера.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[Mat4](../../../api/library/math/class.mat4_cpp.md)> &* **OUT_transforms** - Буфер для хранения трансформаций мешей кластера в мировых координатах. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

### Возвращаемое значение

true, если найдены трансформации мешей кластера; или false, если трансформации мешей кластера в пределах указанной области не найдены.
## bool getInstancesFromSphere ( const Math:: WorldBoundSphere & bb , Vector <int> & OUT_instances )

Возвращает индексы экземпляров внутри ограничивающей сферы.
> **Notice:** Возвращаемый список индексов экземпляров **не отсортирован**.


### Аргументы

- *const  Math::[WorldBoundSphere](../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bb** - Ограничивающая сфера, определяющая область, в пределах которой должны быть собраны экземпляры.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **OUT_instances** - Вектор, содержащий индексы экземпляров. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

### Возвращаемое значение

true, если внутри ограничивающей сферы есть хотя бы один экземпляр; или false.
## Ptr<ConstMesh> getMeshCurrentRAM ( ) const

 Возвращает текущий исходный меш, используемый объектом и загруженный в память (RAM).
### Возвращаемое значение

Текущий исходный меш, используемый объектом.
## Ptr < MeshRender > getMeshCurrentVRAM ( )

Возвращает текущий render-меш, используемый объектом и загруженный в видеопамять (VRAM).
### Возвращаемое значение

Текущий render-меш, используемый объектом.
## Ptr<ConstMesh> getMeshForceRAM ( )

Возвращает исходный меш, используемый объектом, и немедленно загружает его в память (RAM).
### Возвращаемое значение

Исходный меш, используемый объектом.
## Ptr < MeshRender > getMeshForceVRAM ( )

Возвращает render-меш, используемый объектом, и немедленно загружает его в видеопамять (VRAM). При этом статический меш также будет загружен в память (RAM).
> **Notice:** Загрузка в VRAM должна выполняться только в главном потоке.


### Возвращаемое значение

Render-меш, используемый объектом.
## Ptr<ConstMesh> getMeshAsyncRAM ( )

Возвращает исходный меш, используемый объектом, и загружает его в память (RAM) асинхронно.
### Возвращаемое значение

Исходный меш, используемый объектом.
## Ptr < MeshRender > getMeshAsyncVRAM ( )

**[ Main Thread ]**Возвращает render-меш, используемый объектом, и загружает его в видеопамять (VRAM) асинхронно. При этом статический меш также будет загружен в память (RAM).
> **Notice:** Загрузка в VRAM должна выполняться только в главном потоке.


### Возвращаемое значение

Render-меш, используемый объектом.
## Ptr < Mesh > getMeshDynamicRAM ( )

Возвращает процедурный исходный меш, связанный с объектом, и гарантирует его загрузку в системную память (RAM). Этот метод доступен только когда меш находится в **динамическом** режиме (*[PROCEDURAL_MODE_DYNAMIC](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_DYNAMIC)*). *Процедурный меш* — это меш, созданный с помощью кода, использующий определённый режим потоковой передачи (streaming). В режиме *[PROCEDURAL_MODE_DYNAMIC](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_DYNAMIC)* объект остаётся в памяти после создания и выгружается только вручную с помощью *[deleteDynamicMesh()](../../../api/library/objects/class.objectmeshstatic_cpp.md#deleteDynamicMesh_int)* или при изменении процедурного режима.
> **Notice:** Обратите внимание, что модификация процедурного меша **напрямую влияет на потоковую передачу и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Возвращаемое значение

Процедурный исходный меш, используемый объектом.
## Ptr < MeshRender > getMeshDynamicVRAM ( )

Возвращает процедурный render-меш, связанный с объектом, и гарантирует его загрузку в видеопамять (VRAM). Этот метод доступен только когда меш находится в **динамическом** режиме (*[PROCEDURAL_MODE_DYNAMIC](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_DYNAMIC)*). *Процедурный меш* — это меш, созданный с помощью кода, использующий определённый режим потоковой передачи (streaming). В режиме *[PROCEDURAL_MODE_DYNAMIC](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_DYNAMIC)* объект остаётся в памяти после создания и выгружается только вручную с помощью *[deleteDynamicMesh()](../../../api/library/objects/class.objectmeshstatic_cpp.md#deleteDynamicMesh_int)* или при изменении процедурного режима.
> **Notice:** Обратите внимание, что модификация процедурного меша **напрямую влияет на потоковую передачу и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Возвращаемое значение

Процедурный render-меш, используемый объектом.
## bool loadAsyncVRAM ( )

**[ Main Thread ]**Асинхронно загружает меш в видеопамять (VRAM), если включён [async streaming mode for meshes](../../../api/library/rendering/class.render_cpp.md#STREAMING_MODE). В противном случае выполняется [forced](#loadForceVRAM_bool) загрузка. Этот метод рекомендуется использовать для реализации собственной системы предзагрузки (т.е. асинхронной предварительной загрузки мешей в видеопамять перед их использованием).
> **Notice:** Загрузка в VRAM должна выполняться только в главном потоке.


### Возвращаемое значение

true, если меш загружен успешно, иначе false. Если меш уже загружен в VRAM, будет возвращено true.
## bool loadAsyncRAM ( )

Асинхронно загружает меш в память (RAM), если включён [async streaming mode for meshes](../../../api/library/rendering/class.render_cpp.md#STREAMING_MODE). В противном случае выполняется [forced](#loadForceRAM_bool) загрузка. Этот метод рекомендуется использовать для реализации собственной системы предзагрузки (т.е. асинхронной предварительной загрузки мешей в память перед их использованием).
### Возвращаемое значение

true, если меш загружен успешно, иначе false. Если меш уже загружен в RAM, будет возвращено true.
## bool loadForceVRAM ( )

Выполняет принудительную загрузку меша в видеопамять (VRAM) немедленно. Принудительная загрузка в VRAM выполняется в главном потоке.
> **Notice:** Загрузка в VRAM должна выполняться только в главном потоке.


### Возвращаемое значение

true, если меш загружен успешно, иначе false. Если меш уже загружен в VRAM, будет возвращено true.
## bool loadForceRAM ( )

Выполняет принудительную загрузку меша в память (RAM) немедленно.
### Возвращаемое значение

true, если меш загружен успешно, иначе false. Если меш уже загружен в RAM, будет возвращено true.
## bool isMeshNull ( ) const

Возвращает значение, указывающее, является ли исходный меш, используемый объектом, null (не существует, не назначен, не загружен и т.д.).
### Возвращаемое значение

true, если исходный меш, используемый объектом, равен null; иначе false.
## bool isMeshLoadedRAM ( ) const

Возвращает значение, указывающее, загружен ли исходный меш, используемый объектом, в память (RAM).
### Возвращаемое значение

true, если исходный меш, используемый объектом, загружен в RAM; иначе false.
## bool isMeshLoadedVRAM ( ) const

Возвращает значение, указывающее, загружен ли исходный меш, используемый объектом, в видеопамять (VRAM).
### Возвращаемое значение

true, если исходный меш, используемый объектом, загружен в VRAM; иначе false.
## Ptr < Mesh > createCopyMeshRAM ( ) const

Создаёт и возвращает копию исходного меша, используемого объектом, загружая его напрямую с диска, если он отсутствует в кэше. Этот метод не выполняет потоковую загрузку скопированного меша в кэш памяти, что приводит к меньшему использованию RAM.
### Возвращаемое значение

Копия исходного меша или nullptr, если исходный меш отсутствует в RAM или его путь к файлу недействителен.
## bool getCopyMeshRAM ( Ptr < Mesh > & result ) const

Получает копию исходного меша, используемого объектом, и записывает её в предоставленный объект меша. Если меш отсутствует в кэше, он загружается напрямую с диска. Этот метод не выполняет потоковую загрузку скопированного меша в кэш памяти, что приводит к меньшему использованию RAM.
### Аргументы

- *[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **result** - Объект, который получит копию исходного меша.

### Возвращаемое значение

true, если меш был успешно скопирован, false, если исходный меш отсутствует в RAM или его путь к файлу недействителен.
## bool isMeshProceduralDone ( ) const

Возвращает значение, указывающее, завершены ли все асинхронные операции над процедурным мешем.
> **Notice:** Обратите внимание, что модификация процедурного меша **напрямую влияет на потоковую передачу и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Возвращаемое значение

true, если ни одна асинхронная операция с геометрией не активна, иначе false.
## bool isMeshProceduralActive ( ) const

Возвращает значение, указывающее, выполняется ли в данный момент асинхронная операция над процедурным мешем.
> **Notice:** Обратите внимание, что модификация процедурного меша **напрямую влияет на потоковую передачу и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Возвращаемое значение

true, если асинхронная операция с геометрией активна, иначе false.
## bool isMeshProceduralDynamic ( ) const

Возвращает значение, указывающее, является ли текущий процедурный режим *[PROCEDURAL_MODE_DYNAMIC](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_DYNAMIC)*.
> **Notice:** Обратите внимание, что модификация процедурного меша **напрямую влияет на потоковую передачу и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Возвращаемое значение

true, если активен *[PROCEDURAL_MODE_DYNAMIC](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_DYNAMIC)*, иначе false.
## void setMeshProceduralMode ( ObjectMeshStatic::PROCEDURAL_MODE mode , int mesh_render_flags = 0 )

Задаёт процедурный режим для меша. Указанный режим определяет, как процедурные данные хранятся, обновляются и выгружаются.
> **Notice:** Обратите внимание, что модификация процедурного меша **напрямую влияет на потоковую передачу и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Аргументы

- *[ObjectMeshStatic::PROCEDURAL_MODE](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE)* **mode** - Один из *[PROCEDURAL_MODE](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE)*, применяемый к мешу.
- *int* **mesh_render_flags** - Необязательные [usage flags](../../../api/library/rendering/class.meshrender_cpp.md#USAGE_DYNAMIC_VERTEX), управляющие тем, как данные вершин и индексов хранятся для render-меша.

## ObjectMeshStatic::PROCEDURAL_MODE getMeshProceduralMode ( ) const

Возвращает значение, указывающее, какой процедурный режим назначен мешу. Значение соответствует одному из доступных типов *[PROCEDURAL_MODE](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE)*, определяющих, как процедурные данные хранятся, обновляются и выгружаются.
> **Notice:** Обратите внимание, что модификация процедурного меша **напрямую влияет на потоковую передачу и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Возвращаемое значение

Текущий процедурный режим меша.
## bool applyCopyMeshProceduralForce ( const Ptr<ConstMesh> & mesh , int mesh_render_flags = 0 )

**[ Main Thread ]**
Принудительно копирует все данные вершин из заданного меша в процедурный меш объекта, выполняя операцию немедленно. Работает только когда **процедурный режим включён**.


> **Notice:** Обратите внимание, что модификация процедурного меша **напрямую влияет на потоковую передачу и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Аргументы

- *[const Ptr<ConstMesh> &](#ConstMeshPtr)* **mesh** - Исходный меш, из которого копируются данные вершин.
- *int* **mesh_render_flags** - Необязательные [usage flags](../../../api/library/rendering/class.meshrender_cpp.md#USAGE_DYNAMIC_VERTEX) для *[MeshRender](../../../api/library/rendering/class.meshrender_cpp.md)*.

### Возвращаемое значение

true, если меш был успешно скопирован, иначе false.
## bool applyMoveMeshProceduralForce ( const Ptr < Mesh > & mesh , int mesh_render_flags = 0 )

**[ Main Thread ]**
Принудительно перемещает все данные вершин из заданного меша в процедурный меш объекта, выполняя операцию немедленно без выделения памяти и копирования данных (семантика перемещения). Работает только когда **процедурный режим включён**.


В режиме *[PROCEDURAL_MODE_DYNAMIC](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_DYNAMIC)* этот метод ведёт себя идентично своему асинхронному варианту.


Эта операция **обменивает данные меша объекта с заданным мешем**. При повторном использовании того же объекта меша для дальнейшей генерации данных убедитесь, что его внутреннее состояние (например, количество поверхностей) корректно.


> **Notice:** Обратите внимание, что модификация процедурного меша **напрямую влияет на потоковую передачу и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh** - Исходный меш, из которого перемещаются данные вершин.
- *int* **mesh_render_flags** - Необязательные [usage flags](../../../api/library/rendering/class.meshrender_cpp.md#USAGE_DYNAMIC_VERTEX) для *[MeshRender](../../../api/library/rendering/class.meshrender_cpp.md)*.

### Возвращаемое значение

true, если меш был успешно перемещён (передан без копирования), иначе false.
## bool applyMoveMeshProceduralForce ( const Ptr < Mesh > & mesh_ram , const Ptr < MeshRender > & mesh_vram )

**[ Main Thread ]**
Принудительно перемещает все данные вершин и рендеринга из заданных *mesh_ram* и *mesh_vram* в процедурный меш объекта, выполняя операцию немедленно с использованием семантики перемещения, без копирования данных или выделения VRAM. Работает только когда **процедурный режим включён**.


Эта операция **обменивает данные меша объекта с заданным мешем**. При повторном использовании того же объекта меша для дальнейшей генерации данных убедитесь, что его внутреннее состояние (например, количество поверхностей) корректно.


> **Notice:** Обратите внимание, что модификация процедурного меша **напрямую влияет на потоковую передачу и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh_ram** - Исходный меш, содержащий данные вершин.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[MeshRender](../../../api/library/rendering/class.meshrender_cpp.md)> &* **mesh_vram** - Исходный меш, содержащий данные рендеринга.

### Возвращаемое значение

true, если данные были успешно перемещены (переданы без копирования), иначе false.
## bool applyCopyMeshProceduralAsync ( const Ptr<ConstMesh> & mesh , int mesh_render_flags = 0 )

**[ Main Thread ]**
Асинхронно копирует все данные вершин из заданного меша в процедурный меш объекта. Операция не является принудительной и выполняется в фоновом режиме без заметной задержки. Работает только когда **процедурный режим включён**.


В режимах *[PROCEDURAL_MODE_FILE](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_FILE)* и *[PROCEDURAL_MODE_BLOB](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_BLOB)* этот метод работает быстрее по сравнению с принудительным вариантом, так как записи файлов и операции с памятью выполняются в фоновых потоках.


> **Notice:** Обратите внимание, что модификация процедурного меша **напрямую влияет на потоковую передачу и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Аргументы

- *[const Ptr<ConstMesh> &](#ConstMeshPtr)* **mesh** - Исходный меш, из которого копируются данные вершин.
- *int* **mesh_render_flags** - Необязательные [usage flags](../../../api/library/rendering/class.meshrender_cpp.md#USAGE_DYNAMIC_VERTEX) для *[MeshRender](../../../api/library/rendering/class.meshrender_cpp.md)*.

### Возвращаемое значение

true, если меш был успешно скопирован, иначе false.
## bool applyMoveMeshProceduralAsync ( const Ptr < Mesh > & mesh , int mesh_render_flags = 0 )

**[ Main Thread ]**
Асинхронно перемещает все данные вершин из заданного меша в процедурный меш объекта. Операция не является принудительной и выполняется в фоновом режиме без заметной задержки, без выделения памяти и копирования данных (семантика перемещения). Работает только когда **процедурный режим включён**.


В режимах *[PROCEDURAL_MODE_FILE](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_FILE)* и *[PROCEDURAL_MODE_BLOB](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_BLOB)* этот метод работает быстрее по сравнению с принудительным вариантом, так как записи файлов и операции с памятью выполняются в фоновых потоках.


Эта операция **обменивает данные меша объекта с заданным мешем**. При повторном использовании того же объекта меша для дальнейшей генерации данных убедитесь, что его внутреннее состояние (например, количество поверхностей) корректно.


> **Notice:** Обратите внимание, что модификация процедурного меша **напрямую влияет на потоковую передачу и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh** - Исходный меш, из которого копируются данные вершин.
- *int* **mesh_render_flags** - Необязательные [usage flags](../../../api/library/rendering/class.meshrender_cpp.md#USAGE_DYNAMIC_VERTEX) для *[MeshRender](../../../api/library/rendering/class.meshrender_cpp.md)*.

## bool applyMoveMeshProceduralAsync ( const Ptr < Mesh > & mesh_ram , const Ptr < MeshRender > & mesh_vram )

**[ Main Thread ]**
Асинхронно перемещает все данные вершин и рендеринга из заданных mesh_ram и mesh_vram в процедурный меш объекта, без копирования или выделения VRAM. Операция не является принудительной и выполняется в фоновом режиме без заметной задержки. Работает только когда **процедурный режим включён**.


В режимах *[PROCEDURAL_MODE_FILE](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_FILE)* и *[PROCEDURAL_MODE_BLOB](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_BLOB)* этот метод работает быстрее, так как записи файлов и операции с памятью выполняются в фоновых потоках.


В режиме *[PROCEDURAL_MODE_DYNAMIC](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_DYNAMIC)* этот метод ведёт себя идентично своему принудительному варианту.


Эта операция **обменивает данные меша объекта с заданным мешем**. При повторном использовании того же объекта меша для дальнейшей генерации данных убедитесь, что его внутреннее состояние (например, количество поверхностей) корректно.


> **Notice:** Обратите внимание, что модификация процедурного меша **напрямую влияет на потоковую передачу и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh_ram** - Исходный меш, содержащий данные вершин.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[MeshRender](../../../api/library/rendering/class.meshrender_cpp.md)> &* **mesh_vram** - Исходный меш, содержащий данные рендеринга.

### Возвращаемое значение

true, если данные были успешно перемещены, иначе false.
## bool deleteDynamicMesh ( )

**[ Main Thread ]**
Освобождает всю память, используемую процедурным мешем, включая VRAM и RAM. Работает только когда процедурный режим установлен в *[PROCEDURAL_MODE_DYNAMIC](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_DYNAMIC)*.


> **Notice:** Обратите внимание, что модификация процедурного меша **напрямую влияет на потоковую передачу и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Возвращаемое значение

true, если память была успешно освобождена, иначе false.
## bool runGenerateMeshProceduralAsync ( CallbackBase1 < Ptr < Mesh >> * callback_generate , int mesh_render_flags = 0 )

**[ Main Thread ]**
Запускает асинхронную генерацию данных процедурного меша. Функция *callback_generate* выполняется в фоновом потоке и должна создать и заполнить объект меша новыми данными. Сгенерированный меш будет передан объекту после завершения, без блокировки главного потока. Работает только когда **процедурный режим включён**.


Обратите внимание, что callback выполняется в единственном выделенном потоке, управляемом движком, он не распараллеливается и не должен порождать дополнительные потоки.


> **Notice:** Обратите внимание, что модификация процедурного меша **напрямую влияет на потоковую передачу и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Аргументы

- *[CallbackBase1](../../../api/library/common/callbacks/class.callbackbase1_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)>> ** **callback_generate** -  Callback-функция, ответственная за создание и заполнение исходного меша. Выполняется в главном потоке. Функция должна быть обёрнута с помощью *[MakeCallback()](../../../api/library/common/class.unigine.namespace_cpp.md#MakeCallback_Classm_RetClassm)* и иметь следующую сигнатуру: ```cpp void callback_generate(Ptr<Mesh> mesh) ```
- *int* **mesh_render_flags** - Необязательные [usage flags](../../../api/library/rendering/class.meshrender_cpp.md#USAGE_DYNAMIC_VERTEX) для *[MeshRender](../../../api/library/rendering/class.meshrender_cpp.md)*.

### Возвращаемое значение

true, если модификация была успешно завершена и применена, иначе false
## bool runGenerateMeshProceduralAsync ( CallbackBase1 < Ptr < Mesh >> * callback_generate , CallbackBase * callback_done , int mesh_render_flags = 0 )

**[ Main Thread ]**
Запускает асинхронную генерацию данных процедурного меша. Функция *callback_generate* выполняется в фоновом потоке и должна создать и заполнить объект меша новыми данными. Сгенерированный меш будет передан объекту после завершения, без блокировки главного потока. После применения меша к объекту будет вызван необязательный callback_done. Работает только когда **процедурный режим включён**.


Обратите внимание, что callback выполняется в единственном выделенном потоке, управляемом движком, он не распараллеливается и не должен порождать дополнительные потоки.


> **Notice:** Обратите внимание, что модификация процедурного меша **напрямую влияет на потоковую передачу и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Аргументы

- *[CallbackBase1](../../../api/library/common/callbacks/class.callbackbase1_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)>> ** **callback_generate** -  Callback-функция, ответственная за создание и заполнение исходного меша. Выполняется в главном потоке. Функция должна быть обёрнута с помощью *[MakeCallback()](../../../api/library/common/class.unigine.namespace_cpp.md#MakeCallback_Classm_RetClassm)* и иметь следующую сигнатуру: ```cpp void callback_generate(Ptr<Mesh> mesh) ```
- *[CallbackBase](../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **callback_done** -  Необязательный callback, выполняемый после того, как геометрия полностью применена. Функция должна быть обёрнута с помощью *[MakeCallback()](../../../api/library/common/class.unigine.namespace_cpp.md#MakeCallback_Classm_RetClassm)* и иметь следующую сигнатуру: ```cpp void callback_done() ```
- *int* **mesh_render_flags** - Необязательные [usage flags](../../../api/library/rendering/class.meshrender_cpp.md#USAGE_DYNAMIC_VERTEX) для *[MeshRender](../../../api/library/rendering/class.meshrender_cpp.md)*.

### Возвращаемое значение

true, если генерация была успешно завершена и применена, иначе false
## bool runGenerateMeshProceduralForce ( CallbackBase1 < Ptr < Mesh >> * callback_generate , int mesh_render_flags = 0 )

**[ Main Thread ]**
Запускает немедленную (принудительную) генерацию данных процедурного меша. Функция *callback_generate* выполняется в главном потоке и должна создать и заполнить объект меша новыми данными. Сгенерированный меш применяется к объекту сразу после завершения генерации. Работает только когда **процедурный режим включён**.


> **Notice:** Обратите внимание, что модификация процедурного меша **напрямую влияет на потоковую передачу и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Аргументы

- *[CallbackBase1](../../../api/library/common/callbacks/class.callbackbase1_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)>> ** **callback_generate** -  Callback-функция, ответственная за создание и заполнение исходного меша. Выполняется в главном потоке. Функция должна быть обёрнута с помощью *[MakeCallback()](../../../api/library/common/class.unigine.namespace_cpp.md#MakeCallback_Classm_RetClassm)* и иметь следующую сигнатуру: ```cpp void callback_generate(Ptr<Mesh> mesh) ```
- *int* **mesh_render_flags** - Необязательные [usage flags](../../../api/library/rendering/class.meshrender_cpp.md#USAGE_DYNAMIC_VERTEX) для *[MeshRender](../../../api/library/rendering/class.meshrender_cpp.md)*.

### Возвращаемое значение

true, если генерация была успешно завершена и применена, иначе false
## bool runGenerateMeshProceduralForce ( CallbackBase1 < Ptr < Mesh >> * callback_generate , CallbackBase * callback_done , int mesh_render_flags = 0 )

**[ Main Thread ]**
Запускает немедленную (принудительную) генерацию данных процедурного меша. Функция *callback_generate* выполняется в главном потоке и должна создать и заполнить объект Mesh данными вершин. После применения меша к объекту в главном потоке вызывается необязательный *callback_done*. Работает только когда **процедурный режим включён**.


> **Notice:** Обратите внимание, что модификация процедурного меша **напрямую влияет на потоковую передачу и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Аргументы

- *[CallbackBase1](../../../api/library/common/callbacks/class.callbackbase1_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)>> ** **callback_generate** -  Callback-функция, ответственная за создание и заполнение исходного меша. Выполняется в главном потоке. Функция должна быть обёрнута с помощью *[MakeCallback()](../../../api/library/common/class.unigine.namespace_cpp.md#MakeCallback_Classm_RetClassm)* и иметь следующую сигнатуру: ```cpp void callback_generate(Ptr<Mesh> mesh) ```
- *[CallbackBase](../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **callback_done** -  Необязательный callback, выполняемый после того, как геометрия полностью применена. Функция должна быть обёрнута с помощью *[MakeCallback()](../../../api/library/common/class.unigine.namespace_cpp.md#MakeCallback_Classm_RetClassm)* и иметь следующую сигнатуру: ```cpp void callback_done() ```
- *int* **mesh_render_flags** - Необязательные [usage flags](../../../api/library/rendering/class.meshrender_cpp.md#USAGE_DYNAMIC_VERTEX) для *[MeshRender](../../../api/library/rendering/class.meshrender_cpp.md)*.

### Возвращаемое значение

true if the generation was completed and applied successfully, otherwise false
