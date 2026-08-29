# Классы, связанные с границами


**Ограничивающий объект (bound object)** представляет собой сферический или кубический объём, охватывающий весь узел, используемый для описания размера и положения узла. В UNIGINE это может быть выровненный по осям ограничивающий параллелепипед (AABB) или сфера. Размер такого параллелепипеда или сферы определяется как минимальный, способный вместить объект.


Границы определяются только для узлов, имеющих визуальное представление или собственный размер. Следующие "абстрактные" объекты **вообще не имеют границ** и поэтому исключены из [spatial tree](../../../../principles/world_management/index.md#bsp):


- [Dummy Node](../../../../objects/nodes/dummy/index.md)
- [Node Reference](../../../../objects/nodes/reference/index.md)
- [Node Layer](../../../../objects/nodes/layer/index.md)
- [World Switcher](../../../../objects/worlds/world_switcher/index.md)
- [World Transform Path](../../../../objects/worlds/world_transforms/transform_path/index.md)
- [World Transform Bone](../../../../objects/worlds/world_transforms/transform_bone/index.md)
- [World Expression](../../../../objects/worlds/world_expression/index.md)
- *[Dummy Object](../../../../objects/objects/dummy/index.md)* (if it has no [body](../../../../principles/physics/bodies/index.md) assigned)


Такой подход значительно уменьшает размер дерева и повышает производительность за счёт экономии времени на пересчёт границ при трансформации таких узлов. Кроме того, AABB обеспечивают очень быстрые проверки благодаря упрощённым операциям, и для задания такого ограничивающего параллелепипеда требуются всего две точки — *(Xmin, Ymin, Zmin)* и *(Xmax, Ymax, Zmax)*.


Однако проверки границ могут быть неточными, поскольку граница не следует контурам объекта точно. Кроме того, ограничивающий параллелепипед выровнен по осям (то есть его рёбра параллельны координатным осям), и при вращении объекта граница изменяется. Поэтому границы используются только для быстрой проверки возможного столкновения объектов. Если проверка положительна, следует выполнить более точную проверку.


![](../../../../principles/world_management/bounds.gif)


Используются следующие типы границ:


- **Local Bounds** — ограничивающие объекты с локальными координатами, не учитывающие физику и дочерние узлы. Получаются с помощью следующих методов класса *Node*: *[getBoundBox()](../../../../api/library/nodes/class.node_cpp.md#getBoundBox_BoundBox)* и *[getBoundSphere()](../../../../api/library/nodes/class.node_cpp.md#getBoundSphere_BoundSphere)*.
- **World Bounds** — то же, что и локальные, но с мировыми координатами. Получаются с помощью следующих методов класса *Node*: *[getWorldBoundBox()](../../../../api/library/nodes/class.node_cpp.md#getWorldBoundBox_WorldBoundBox)* и *[getWorldBoundSphere()](../../../../api/library/nodes/class.node_cpp.md#getWorldBoundSphere_WorldBoundSphere)*.
- **Spatial Bounds** — ограничивающие объекты с мировыми координатами, используемые пространственным деревом и, следовательно, учитывающие физику (границы форм и т.д.). Получаются с помощью следующих методов класса *Node*: *[getSpatialBoundBox()](../../../../api/library/nodes/class.node_cpp.md#getSpatialBoundBox_WorldBoundBox)* и *[getSpatialBoundSphere()](../../../../api/library/nodes/class.node_cpp.md#getSpatialBoundSphere_WorldBoundSphere)*.


> **Notice:** *Spatial*-границы вычисляются быстрее, чем *World*-границы.


А также их иерархические аналоги (учитывающие всех потомков), используемые там, где требуются иерархические границы (они медленнее, но обеспечивают корректные вычисления):


- **Local Hierarchical Bounds** — ограничивающие объекты с локальными координатами, учитывающие границы всех дочерних узлов. Получаются с помощью следующих методов класса *Node*: *[getHierarchyBoundBox()](../../../../api/library/nodes/class.node_cpp.md#getHierarchyBoundBox_int_WorldBoundBox)* и *[getHierarchyBoundSphere()](../../../../api/library/nodes/class.node_cpp.md#getHierarchyBoundSphere_int_WorldBoundSphere)*.
- **World Hierarchical Bounds** — то же, что и локальные, но с мировыми координатами. Получаются с помощью следующих методов класса *Node*: *[getHierarchyWorldBoundBox()](../../../../api/library/nodes/class.node_cpp.md#getHierarchyWorldBoundBox_int_WorldBoundBox)* и *[getHierarchyWorldBoundSphere()](../../../../api/library/nodes/class.node_cpp.md#getHierarchyWorldBoundSphere_int_WorldBoundSphere)*.
- **Spatial Hierarchical Bounds** — иерархические ограничивающие объекты, используемые пространственным деревом и, следовательно, учитывающие физику (границы форм и т.д.). Получаются с помощью следующих методов класса *Node*: *[getHierarchySpatialBoundBox()](../../../../api/library/nodes/class.node_cpp.md#getHierarchySpatialBoundBox_int_WorldBoundBox)* и *[getHierarchySpatialBoundSphere()](../../../../api/library/nodes/class.node_cpp.md#getHierarchySpatialBoundSphere_int_WorldBoundSphere)*.


## Статьи в этом разделе

- [BoundBox Struct (CPP)](../../../../api/library/math/bounds/class.boundbox_cpp.md)

- [BoundFrustum Struct (CPP)](../../../../api/library/math/bounds/class.boundfrustum_cpp.md)

- [BoundSphere Struct (CPP)](../../../../api/library/math/bounds/class.boundsphere_cpp.md)

- [WorldBoundBox Struct (CPP)](../../../../api/library/math/bounds/class.worldboundbox_cpp.md)

- [WorldBoundFrustum Struct (CPP)](../../../../api/library/math/bounds/class.worldboundfrustum_cpp.md)

- [WorldBoundSphere Struct (CPP)](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md)
