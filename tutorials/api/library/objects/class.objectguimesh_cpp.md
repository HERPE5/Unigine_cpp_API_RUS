# ObjectGuiMesh Class (CPP)

**Header:** #include <UnigineObjects.h>

**Inherits from:** Object


Этот класс позволяет рендерить [GUI](../../../objects/objects/gui/gui_mesh.md) на произвольный меш. В отличие от [ObjectGui](../../../api/library/objects/class.objectgui_cpp.md), его можно использовать для создания неплоских дисплеев, размещённых в мире. Если меш содержит несколько поверхностей, один и тот же GUI будет отрендерен на каждой из них. Обратите внимание, что GUI рендерится в соответствии с UV-разметкой поверхностей.


### See Also


UnigineScript sample


## ObjectGuiMesh Class

### Методы класса

---

## static ObjectGuiMeshPtr create ( const char * mesh_path , const char * name = 0 )

Конструктор ObjectGuiMesh. *Gui Mesh* будет создан на основе меша, загруженного из указанного пути.
### Аргументы

- *const char ** **mesh_path** - Путь к исходному *.mesh*-файлу, используемому для объекта
- *const char ** **name**

## static ObjectGuiMeshPtr create ( )

Конструктор. Создаёт новый объект *Gui Mesh*.
## void setControlDistance ( float distance )

Задаёт расстояние, на котором GUI становится управляемым.
### Аргументы

- *float* **distance** - Новое расстояние в единицах.

## float getControlDistance ( ) const

Возвращает расстояние, на котором GUI становится управляемым.
### Возвращаемое значение

Расстояние в единицах.
## Ptr < Gui > getGui ( ) const

Возвращает экземпляр Gui, связанный с объектом.
### Возвращаемое значение

Умный указатель на Gui.
## void setMeshPath ( const char * path )

Задаёт новый путь к исходному мешу для объекта *Gui Mesh*. Если меш находится в процедурном режиме, он будет сброшен.
> **Notice:** Меш должен содержать одну поверхность. Если меш содержит несколько поверхностей, будет использована только поверхность с индексом 0.


### Аргументы

- *const char ** **path** - Новый путь к исходному *.mesh*-файлу для установки.

## const char * getMeshPath ( ) const

Возвращает путь к исходному *.mesh*-файлу, используемому в данный момент для объекта *Gui Mesh*.
### Возвращаемое значение

Путь к исходному *.mesh*-файлу.
## void setMouse ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , int mouse_buttons , bool mouse_show )

Задаёт позицию курсора мыши в [virtual control mode](#MOUSE_VIRTUAL).
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальная точка. Отрезок между начальной и конечной точками должен пересекать ObjectGui. Точка пересечения определяет координаты x и y на ObjectGui.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечная точка. Отрезок между начальной и конечной точками должен пересекать ObjectGui. Точка пересечения определяет координаты x и y на ObjectGui.
- *int* **mouse_buttons** - Статус кнопки мыши. Установите 1, чтобы указать, что кнопка нажата; иначе 0.
- *bool* **mouse_show** - Статус курсора мыши. Установите 1, чтобы показать курсор мыши; иначе 0.

## void setMouseMode ( int mode )

Задаёт режим мыши. Этот метод можно использовать для установки [virtual control mode](#MOUSE_VIRTUAL) для мыши.
### Аргументы

- *int* **mode** - Режим мыши. Одна из переменных [MOUSE_*](#MOUSE_VIRTUAL).

## int getMouseMode ( ) const

Возвращает текущий режим мыши.
### Возвращаемое значение

Режим мыши. Одна из переменных [MOUSE_*](#MOUSE_VIRTUAL).
## void setMouseShow ( bool show )

Задаёт значение, указывающее, должен ли курсор мыши отображаться в объекте mesh GUI.
### Аргументы

- *bool* **show** - true для отображения курсора мыши; иначе false.

## bool isMouseShow ( ) const

Возвращает значение, указывающее, отображается ли курсор мыши в объекте mesh GUI.
### Возвращаемое значение

true, если курсор отображается; иначе false.
## void setBackground ( bool background )

Задаёт значение, указывающее, должен ли рендериться фон GUI (чёрный экран).
### Аргументы

- *bool* **background** - true для рендеринга фона GUI, false, чтобы оставить его прозрачным.

## bool isBackground ( ) const

Возвращает значение, указывающее, рендерится ли фон GUI (чёрный экран).
### Возвращаемое значение

true, если фон рендерится; иначе false.
## int getScreenHeight ( ) const

Возвращает высоту экрана объекта mesh GUI.
### Возвращаемое значение

Высота в пикселях.
## void setScreenSize ( int width , int height )

Задаёт размеры экрана объекта mesh GUI.
### Аргументы

- *int* **width** - Новая ширина в пикселях. Если указано отрицательное значение, вместо него будет использовано 0.
- *int* **height** - Новая высота в пикселях. Если указано отрицательное значение, вместо него будет использовано 0.

## int getScreenWidth ( ) const

Возвращает ширину экрана объекта mesh GUI.
### Возвращаемое значение

Ширина в пикселях.
## static int type ( )

Возвращает идентификатор типа *ObjectMeshStatic*.
### Возвращаемое значение

 Идентификатор типа *ObjectMeshStatic*.
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

**[ Main Thread ]**Асинхронно загружает меш в видеопамять (VRAM), если включён [asynchronous mesh streaming mode](../../../api/library/rendering/class.render_cpp.md#STREAMING_MODE). В противном случае выполняется [forced](#loadForceVRAM_bool) загрузка. Этот метод рекомендуется использовать для реализации собственной системы предзагрузки (т.е. асинхронной предварительной загрузки мешей в видеопамять перед их использованием).
> **Notice:** Загрузка в VRAM должна выполняться только в главном потоке.


### Возвращаемое значение

true, если меш загружен успешно, иначе false. Если меш уже загружен в VRAM, будет возвращено true.
## bool loadAsyncRAM ( )

Асинхронно загружает меш в память (RAM), если включён [asynchronous mesh streaming mode](../../../api/library/rendering/class.render_cpp.md#STREAMING_MODE). В противном случае выполняется [forced](#loadForceRAM_bool) загрузка. Этот метод рекомендуется использовать для реализации собственной системы предзагрузки (т.е. асинхронной предварительной загрузки мешей в память перед их использованием).
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
Принудительно перемещает все данные вершин из заданного меша в процедурный меш объекта, выполняя операцию немедленно без выделения памяти и копирования данных (семантика перемещения).


В режиме *[PROCEDURAL_MODE_DYNAMIC](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_DYNAMIC)* этот метод ведёт себя идентично своему асинхронному варианту. Работает только когда **процедурный режим включён**.


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
Запускает немедленную (принудительную) генерацию данных процедурного меша. Функция *callback_generate* выполняется в главном потоке и должна создать и заполнить объект Mesh данными вершин. После применения меша к объекту в главном потоке вызывается необязательный *callback_done*. Работает только когда **процедурный режим включён**


> **Notice:** Обратите внимание, что модификация процедурного меша **напрямую влияет на потоковую передачу и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Аргументы

- *[CallbackBase1](../../../api/library/common/callbacks/class.callbackbase1_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)>> ** **callback_generate** -  Callback-функция, ответственная за создание и заполнение исходного меша. Выполняется в главном потоке. Функция должна быть обёрнута с помощью *[MakeCallback()](../../../api/library/common/class.unigine.namespace_cpp.md#MakeCallback_Classm_RetClassm)* и иметь следующую сигнатуру: ```cpp void callback_generate(Ptr<Mesh> mesh) ```
- *[CallbackBase](../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **callback_done** -  Необязательный callback, выполняемый после того, как геометрия полностью применена. Функция должна быть обёрнута с помощью *[MakeCallback()](../../../api/library/common/class.unigine.namespace_cpp.md#MakeCallback_Classm_RetClassm)* и иметь следующую сигнатуру: ```cpp void callback_done() ```
- *int* **mesh_render_flags** - Необязательные [usage flags](../../../api/library/rendering/class.meshrender_cpp.md#USAGE_DYNAMIC_VERTEX) для *[MeshRender](../../../api/library/rendering/class.meshrender_cpp.md)*.

### Возвращаемое значение

true, если генерация была успешно завершена и применена, иначе false
