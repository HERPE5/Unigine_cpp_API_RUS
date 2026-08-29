# MeshSkinned Class (CPP)

**Header:** #include <UnigineMesh.h>


Этот класс - контейнер для данных геометрии skinned-меша - вершин, нормалей, тангенсов, текстурных координат, цветов, индексов и весов скининга суставов. Он предоставляет интерфейс для загрузки, изменения и сохранения skinned-мешей.


Геометрия организована в поверхности, каждая из которых может иметь несколько morph target. Каждая вершина хранит до 4 влияний суставов (индексы и веса) для скелетной анимации.


Ключевые понятия:


- Source joints - иерархия суставов (имена, отношения родитель-потомок, bind poses), на которую ссылается этот меш.
- Surfaces (поверхности) - подмножества геометрии, каждое со своими данными вершин/индексов и ограничивающими объёмами.
- Morph targets - варианты позиций вершин, нормалей и тангенсов для каждой поверхности, используемые для анимации blend shape.
- Координатные индексы (CIndices) - индексы в буфер позиций вершин.
- Треугольные индексы (TIndices) - индексы в буфер уникальных атрибутов вершин (нормали, тангенсы, UV).


## MeshSkinned Class

### Методы класса

## getSharedSkeleton () const

Возвращает текущий экземпляр скелета, связанный с этим мешем, загруженный из общего пути или GUID скелета.
### Возвращаемое значение

Текущий экземпляр общего скелета.
## void setSharedSkeletonFileGUID ( )

Задаёт новый GUID файла скелета, связанного с этим мешем.
### Аргументы

- **guid** - GUID файла общего скелета.

## getSharedSkeletonFileGUID () const

Возвращает текущий GUID файла скелета, связанного с этим мешем.
### Возвращаемое значение

Текущий GUID файла общего скелета.
## void setSharedSkeletonPath ( )

Задаёт новый путь к файлу скелета, связанного с этим мешем.
### Аргументы

- **path** - Путь к файлу общего скелета.

## const char * getSharedSkeletonPath () const

Возвращает текущий путь к файлу скелета, связанного с этим мешем.
### Возвращаемое значение

Текущий путь к файлу общего скелета.
## getNumSrcJoints () const

Возвращает текущее общее количество source joints в этом меше.
### Возвращаемое значение

Текущее количество source joints.
## getNumSurfaces () const

Возвращает текущее общее количество поверхностей в этом меше.
### Возвращаемое значение

Текущее количество поверхностей.
## getBoundBox () const

Возвращает текущий выровненный по осям ограничивающий параллелепипед, охватывающий всю геометрию меша.
### Возвращаемое значение

Текущий ограничивающий параллелепипед меша.
## getBoundSphere () const

Возвращает текущую ограничивающую сферу, охватывающую всю геометрию меша.
### Возвращаемое значение

Текущая ограничивающая сфера меша.
## getSystemMemoryUsage () const

Возвращает текущий общий объём системной памяти, используемой этим мешем, в байтах.
### Возвращаемое значение

Текущее использование системной памяти в байтах.
---

## static MeshSkinnedPtr create ( )

Создаёт пустой skinned-меш.
## static MeshSkinnedPtr create ( const char * path )

Создаёт skinned-меш и загружает данные из заданного файла.
### Аргументы

- *const char ** **path** - Путь к файлу меша.

## void initSourceSkeleton ( const Ptr <ConstSkeleton> & skeleton )

Инициализирует иерархию source joints из заданного экземпляра скелета.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<ConstSkeleton> &* **skeleton** - Экземпляр скелета, из которого инициализируются source joints.

## void initSourceSkeleton ( const char * path )

Инициализирует иерархию source joints из скелета, загруженного из заданного пути к файлу.
### Аргументы

- *const char ** **path** - Путь к файлу скелета.

## void assignFrom ( const Ptr < MeshSkinned > & mesh )

Копирует все данные из исходного меша: геометрию, суставы и поверхности.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[MeshSkinned](../../../api/library/rendering/class.meshskinned_cpp.md)> &* **mesh** - Экземпляр исходного меша.

## int info ( const char * path ) const

Считывает метаданные из заданного файла меша без загрузки полных данных геометрии.
### Аргументы

- *const char ** **path** - Путь к файлу меша.

### Возвращаемое значение

1, если метаданные файла успешно считаны; иначе 0.
## int load ( const char * path )

Загружает полные данные меша из заданного файла.
### Аргументы

- *const char ** **path** - Путь к файлу меша.

### Возвращаемое значение

1, если меш успешно загружен; иначе 0.
## int save ( const char * path ) const

Сохраняет данные меша в заданный файл. Создаёт файл и все необходимые подкаталоги, если они не существуют.
### Аргументы

- *const char ** **path** - Путь к выходному файлу.

### Возвращаемое значение

1, если меш успешно сохранён; иначе 0.
## void clear ( )

Очищает все данные меша: геометрию, суставы и поверхности.
## bool flipYZ ( int surface = -1 )

Меняет местами оси Y и Z для заданной поверхности (или всех поверхностей).
### Аргументы

- *int* **surface** - Индекс поверхности. Используйте -1 для всех поверхностей.

### Возвращаемое значение

true, если операция выполнена успешно; иначе false.
## bool flipTangent ( int surface = -1 )

Меняет направление тангенса для заданной поверхности (или всех поверхностей).
### Аргументы

- *int* **surface** - Индекс поверхности. Используйте -1 для всех поверхностей.

### Возвращаемое значение

true, если операция выполнена успешно; иначе false.
## bool createBounds ( int surface = -1 )

Пересчитывает ограничивающие параллелепипеды и ограничивающие сферы для заданной поверхности (или всех поверхностей).
### Аргументы

- *int* **surface** - Индекс поверхности. Используйте -1 для всех поверхностей.

### Возвращаемое значение

true, если границы успешно созданы; иначе false.
## bool removeIndices ( int surface = -1 )

Удаляет все индексы из заданной поверхности (или всех поверхностей).
### Аргументы

- *int* **surface** - Индекс поверхности. Используйте -1 для всех поверхностей.

### Возвращаемое значение

true, если индексы успешно удалены; иначе false.
## bool createIndices ( int surface = -1 )

Создаёт треугольные и координатные индексы для заданной поверхности (или всех поверхностей).
### Аргументы

- *int* **surface** - Индекс поверхности. Используйте -1 для всех поверхностей.

### Возвращаемое значение

true, если индексы успешно созданы; иначе false.
## bool optimizeIndices ( int flags , int surface = -1 )

Оптимизирует буфер индексов для заданной поверхности (или всех поверхностей), используя заданные флаги.
### Аргументы

- *int* **flags** - Флаги оптимизации.
- *int* **surface** - Индекс поверхности. Используйте -1 для всех поверхностей.

### Возвращаемое значение

true, если оптимизация выполнена успешно; иначе false.
## bool createNormals ( int surface = -1 , int target = -1 )

Создаёт нормали для заданной поверхности и morph target путём усреднения нормалей граней.
### Аргументы

- *int* **surface** - Индекс поверхности. Используйте -1 для всех поверхностей.
- *int* **target** - Индекс morph target. Используйте -1 для всех целей.

### Возвращаемое значение

true, если нормали успешно созданы; иначе false.
## bool createNormals ( float angle , int surface = -1 , int target = -1 )

Создаёт нормали с заданным пороговым углом для определения сглаженных/жёстких рёбер.
### Аргументы

- *float* **angle** - Пороговый угол в градусах для определения сглаженных/жёстких рёбер.
- *int* **surface** - Индекс поверхности. Используйте -1 для всех поверхностей.
- *int* **target** - Индекс morph target. Используйте -1 для всех целей.

### Возвращаемое значение

true, если нормали успешно созданы; иначе false.
## bool createTangents ( int surface = -1 , int target = -1 )

Создаёт векторы тангенциального базиса для заданной поверхности и morph target.
### Аргументы

- *int* **surface** - Индекс поверхности. Используйте -1 для всех поверхностей.
- *int* **target** - Индекс morph target. Используйте -1 для всех целей.

### Возвращаемое значение

true, если тангенсы успешно созданы; иначе false.
## bool createTangents ( float angle , const Vector <int> & surfaces )

Создаёт векторы тангенциального базиса для заданных поверхностей с заданным пороговым углом.
### Аргументы

- *float* **angle** - Пороговый угол в градусах.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **surfaces** - Список индексов обрабатываемых поверхностей.

### Возвращаемое значение

true, если тангенсы успешно созданы; иначе false.
## int findSrcJoint ( const char * name ) const

Ищет source joint с заданным именем и возвращает его индекс.
### Аргументы

- *const char ** **name** - Искомое имя сустава.

### Возвращаемое значение

Индекс source joint, или -1, если не найден.
## const char * getSrcJointName ( int bone ) const

Возвращает имя source joint по заданному индексу.
### Аргументы

- *int* **bone** - Индекс source joint.

### Возвращаемое значение

Имя сустава.
## int getSrcJointParent ( int bone ) const

Возвращает индекс родительского сустава для заданного source joint.
### Аргументы

- *int* **bone** - Индекс source joint.

### Возвращаемое значение

Индекс родительского сустава, или -1, если у сустава нет родителя.
## Math:: mat4 getSrcJointObjectITransform ( int joint ) const

Возвращает инвертированную матрицу трансформации bind pose в пространстве объекта для заданного source joint. Используется для вычислений скининга.
### Аргументы

- *int* **joint** - Индекс source joint.

### Возвращаемое значение

Инвертированная матрица bind pose в пространстве объекта.
## Math::Transform getSrcJointBindLocalTransform ( int joint ) const

Возвращает трансформацию bind pose в локальном пространстве (относительно родительского сустава) для заданного source joint.
### Аргументы

- *int* **joint** - Индекс source joint.

### Возвращаемое значение

Трансформация bind pose в локальном пространстве.
## void setSrcJointRestLocalTransform ( int index , Math::Transform & transform )

Задаёт трансформацию rest pose в локальном пространстве для заданного source joint.
### Аргументы

- *int* **index** - Индекс source joint.
- *Math::Transform &* **transform** - Трансформация rest pose в локальном пространстве.

## Math::Transform getSrcJointRestLocalTransform ( int index ) const

Возвращает трансформацию rest pose в локальном пространстве для заданного source joint.
### Аргументы

- *int* **index** - Индекс source joint.

### Возвращаемое значение

Трансформация rest pose в локальном пространстве.
## int findSurface ( const char * name ) const

Ищет поверхность с заданным именем и возвращает её индекс.
### Аргументы

- *const char ** **name** - Искомое имя поверхности.

### Возвращаемое значение

Индекс поверхности, или -1, если не найдена.
## void sortSurfaces ( )

Сортирует поверхности по алфавиту по имени.
## void clearSurface ( int surface = -1 , int target = -1 )

Очищает данные геометрии для заданной поверхности и morph target.
### Аргументы

- *int* **surface** - Индекс поверхности. Используйте -1 для всех поверхностей.
- *int* **target** - Индекс morph target. Используйте -1 для всех целей.

## int addSurface ( const char * name = 0 )

Добавляет новую пустую поверхность с заданным именем.
### Аргументы

- *const char ** **name** - Имя поверхности. Может быть пустым.

### Возвращаемое значение

Индекс новой добавленной поверхности.
## void setSurfaceName ( int surface , const char * name )

Задаёт имя заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.
- *const char ** **name** - Имя поверхности.

## const char * getSurfaceName ( int surface ) const

Возвращает имя заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Имя поверхности.
## void setNumSurfaceTargets ( int surface , int num )

Задаёт количество morph target для заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.
- *int* **num** - Количество morph target.

## int getNumSurfaceTargets ( int surface ) const

Возвращает количество morph target для заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Количество morph target.
## void setSurfaceTargetName ( int surface , int target , const char * name )

Задаёт имя заданного morph target.
### Аргументы

- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.
- *const char ** **name** - Имя target.

## const char * getSurfaceTargetName ( int surface , int target ) const

Возвращает имя заданного morph target.
### Аргументы

- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

### Возвращаемое значение

Имя target.
## int findSurfaceTarget ( int surface , const char * name ) const

Ищет morph target по имени в заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.
- *const char ** **name** - Искомое имя target.

### Возвращаемое значение

Индекс morph target, или -1, если не найден.
## int setSurfaceTransform ( const Math:: mat4 & transform , int surface = -1 , int target = -1 )

Применяет матрицу трансформации к вершинам, нормалям и тангенсам заданной поверхности и morph target.
### Аргументы

- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Применяемая матрица трансформации.
- *int* **surface** - Индекс поверхности. Используйте -1 для всех поверхностей.
- *int* **target** - Индекс morph target. Используйте -1 для всех целей.

### Возвращаемое значение

1, если трансформация успешно применена; иначе 0.
## int addMeshSurface ( const char * v , const Ptr <ConstMeshSkinned> & mesh , int surface , int target = -1 )

Добавляет поверхность из заданного исходного меша как новую поверхность с заданным именем.
### Аргументы

- *const char ** **v** - Имя новой поверхности.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<ConstMeshSkinned> &* **mesh** - Исходный меш, из которого копируется поверхность.
- *int* **surface** - Индекс поверхности в исходном меше.
- *int* **target** - Индекс morph target в исходной поверхности. Используйте -1 для всех целей.

### Возвращаемое значение

Индекс новой добавленной поверхности.
## int addMeshSurface ( int v , const Ptr <ConstMeshSkinned> & mesh , int surface , int target = -1 )

Добавляет геометрию из заданной поверхности исходного меша к существующей поверхности этого меша.
### Аргументы

- *int* **v** - Индекс целевой поверхности, к которой добавляется геометрия.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<ConstMeshSkinned> &* **mesh** - Исходный меш, из которого копируется поверхность.
- *int* **surface** - Индекс поверхности в исходном меше.
- *int* **target** - Индекс morph target в исходной поверхности. Используйте -1 для всех целей.

### Возвращаемое значение

Индекс целевой поверхности.
## int addEmptySurface ( const char * name , int num_vertex , int num_indices )

Добавляет новую поверхность с предварительно выделенными буферами вершин и индексов.
### Аргументы

- *const char ** **name** - Имя поверхности.
- *int* **num_vertex** - Количество выделяемых вершин.
- *int* **num_indices** - Количество выделяемых индексов.

### Возвращаемое значение

Индекс новой добавленной поверхности.
## int addSurfaceTarget ( int surface , const char * name = 0 )

Добавляет новый morph target к заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.
- *const char ** **name** - Имя target. Может быть пустым.

### Возвращаемое значение

Индекс нового добавленного morph target.
## int addBoxSurface ( const char * name , const Math:: vec3 & size )

Добавляет примитивную поверхность box с заданными размерами.
### Аргументы

- *const char ** **name** - Имя поверхности.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **size** - Размеры box (ширина, высота, глубина).

### Возвращаемое значение

Индекс новой добавленной поверхности.
## int addPlaneSurface ( const char * name , float width , float height , float step )

Добавляет примитивную поверхность plane с заданными размерами и шагом тесселяции.
### Аргументы

- *const char ** **name** - Имя поверхности.
- *float* **width** - Ширина plane.
- *float* **height** - Высота plane.
- *float* **step** - Шаг тесселяции.

### Возвращаемое значение

Индекс новой добавленной поверхности.
## int addSphereSurface ( const char * name , float radius , int stacks , int slices )

Добавляет примитивную поверхность sphere с заданным радиусом и подразделением.
### Аргументы

- *const char ** **name** - Имя поверхности.
- *float* **radius** - Радиус sphere.
- *int* **stacks** - Количество горизонтальных подразделений.
- *int* **slices** - Количество вертикальных подразделений.

### Возвращаемое значение

Индекс новой добавленной поверхности.
## int addCapsuleSurface ( const char * name , float radius , float height , int stacks , int slices )

Добавляет примитивную поверхность capsule с заданными размерами и подразделением.
### Аргументы

- *const char ** **name** - Имя поверхности.
- *float* **radius** - Радиус capsule.
- *float* **height** - Высота capsule (цилиндрическая часть).
- *int* **stacks** - Количество горизонтальных подразделений.
- *int* **slices** - Количество вертикальных подразделений.

### Возвращаемое значение

Индекс новой добавленной поверхности.
## int addCylinderSurface ( const char * name , float radius , float height , int stacks , int slices )

Добавляет примитивную поверхность cylinder с заданными размерами и подразделением.
### Аргументы

- *const char ** **name** - Имя поверхности.
- *float* **radius** - Радиус cylinder.
- *float* **height** - Высота cylinder.
- *int* **stacks** - Количество горизонтальных подразделений.
- *int* **slices** - Количество вертикальных подразделений.

### Возвращаемое значение

Индекс новой добавленной поверхности.
## int addPrismSurface ( const char * name , float size_0 , float size_1 , float height , int sides )

Добавляет примитивную поверхность prism с заданными размерами.
### Аргументы

- *const char ** **name** - Имя поверхности.
- *float* **size_0** - Размер нижней грани.
- *float* **size_1** - Размер верхней грани.
- *float* **height** - Высота prism.
- *int* **sides** - Количество сторон.

### Возвращаемое значение

Индекс новой добавленной поверхности.
## int addIcosahedronSurface ( const char * name , float radius )

Добавляет примитивную поверхность icosahedron с заданным радиусом.
### Аргументы

- *const char ** **name** - Имя поверхности.
- *float* **radius** - Радиус icosahedron.

### Возвращаемое значение

Индекс новой добавленной поверхности.
## int addDodecahedronSurface ( const char * name , float radius )

Добавляет примитивную поверхность dodecahedron с заданным радиусом.
### Аргументы

- *const char ** **name** - Имя поверхности.
- *float* **radius** - Радиус dodecahedron.

### Возвращаемое значение

Индекс новой добавленной поверхности.
## int getNumCVertex ( int surface = 0 ) const

Возвращает количество уникальных координатных вершин (позиций) для заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Количество уникальных координатных вершин.
## int getNumTVertex ( int surface = 0 ) const

Возвращает количество уникальных треугольных вершин (комбинаций атрибутов) для заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Количество уникальных треугольных вершин.
## int remapCVertex ( int surface = 0 )

Переназначает индексы координатных вершин для заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

1, если переназначение выполнено успешно; иначе 0.
## void setNumWeights ( int size , int surface = 0 )

Задаёт количество записей весов скининга для заданной поверхности.
### Аргументы

- *int* **size** - Количество записей весов.
- *int* **surface** - Индекс поверхности.

## int getNumWeights ( int surface = 0 ) const

Возвращает количество записей весов скининга для заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Количество записей весов.
## void setWeightCount ( int num , int count , int surface = 0 )

Задаёт количество влияний суставов для заданной записи веса.
### Аргументы

- *int* **num** - Индекс записи веса.
- *int* **count** - Количество влияний суставов (от 1 до 4).
- *int* **surface** - Индекс поверхности.

## int getWeightCount ( int num , int surface = 0 ) const

Возвращает количество влияний суставов для заданной записи веса.
### Аргументы

- *int* **num** - Индекс записи веса.
- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Количество влияний суставов.
## void setWeightJoints ( int num , const Math:: ivec4 & joints , int surface = 0 )

Задаёт индексы суставов для заданной записи веса. Каждый компонент ivec4 - это индекс source joint.
### Аргументы

- *int* **num** - Индекс записи веса.
- *const  Math::[ivec4](../../../api/library/math/class.ivec4_cpp.md) &* **joints** - Четыре индекса суставов, упакованных в ivec4.
- *int* **surface** - Индекс поверхности.

## Math:: ivec4 getWeightJoints ( int num , int surface = 0 ) const

Возвращает индексы суставов для заданной записи веса.
### Аргументы

- *int* **num** - Индекс записи веса.
- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Четыре индекса суставов, упакованных в ivec4.
## void setWeightWeights ( int num , const Math:: vec4 & weights , int surface = 0 )

Задаёт веса суставов для заданной записи веса.
### Аргументы

- *int* **num** - Индекс записи веса.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **weights** - Четыре веса суставов, упакованных в vec4. Сумма компонентов должна равняться 1.0.
- *int* **surface** - Индекс поверхности.

## Math:: vec4 getWeightWeights ( int num , int surface = 0 ) const

Возвращает веса суставов для заданной записи веса.
### Аргументы

- *int* **num** - Индекс записи веса.
- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Четыре веса суставов, упакованных в vec4.
## void setNumVertex ( int size , int surface = 0 , int target = 0 )

Задаёт количество вершин для заданной поверхности и morph target.
### Аргументы

- *int* **size** - Количество вершин.
- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

## int getNumVertex ( int surface , int target = 0 ) const

Возвращает количество вершин для заданной поверхности и morph target.
### Аргументы

- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

### Возвращаемое значение

Количество вершин.
## void addVertex ( const Vector < Math:: vec3 > & vertices , int surface = 0 , int target = 0 )

Добавляет несколько вершин к заданной поверхности и morph target.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[vec3](../../../api/library/math/class.vec3_cpp.md)> &* **vertices** - Массив добавляемых позиций вершин.
- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

## void addVertex ( const Math:: vec3 & vertex , int surface = 0 , int target = 0 )

Добавляет одну вершину к заданной поверхности и morph target.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **vertex** - Позиция вершины.
- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

## void setVertex ( int num , const Math:: vec3 & vertex , int surface = 0 , int target = 0 )

Задаёт позицию вершины по заданному индексу.
### Аргументы

- *int* **num** - Индекс вершины.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **vertex** - Позиция вершины.
- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

## Math:: vec3 getVertex ( int num , int surface = 0 , int target = 0 ) const

Возвращает позицию вершины по заданному индексу.
### Аргументы

- *int* **num** - Индекс вершины.
- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

### Возвращаемое значение

Позиция вершины.
## void setNumTexCoords0 ( int size , int surface = 0 )

Задаёт количество текстурных координат первого канала UV для заданной поверхности.
### Аргументы

- *int* **size** - Количество текстурных координат.
- *int* **surface** - Индекс поверхности.

## int getNumTexCoords0 ( int surface = 0 ) const

Возвращает количество текстурных координат первого канала UV для заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Количество текстурных координат.
## void addTexCoords0 ( const Vector < Math:: vec2 > & texcoords , int surface = 0 )

Добавляет несколько текстурных координат первого канала UV к заданной поверхности.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[vec2](../../../api/library/math/class.vec2_cpp.md)> &* **texcoords** - Массив добавляемых текстурных координат.
- *int* **surface** - Индекс поверхности.

## void addTexCoord0 ( const Math:: vec2 & texcoord , int surface = 0 )

Добавляет одну текстурную координату первого канала UV к заданной поверхности.
### Аргументы

- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **texcoord** - Текстурная координата.
- *int* **surface** - Индекс поверхности.

## void setTexCoord0 ( int num , const Math:: vec2 & texcoord , int surface = 0 )

Задаёт текстурную координату первого канала UV по заданному индексу.
### Аргументы

- *int* **num** - Индекс текстурной координаты.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **texcoord** - Текстурная координата.
- *int* **surface** - Индекс поверхности.

## Math:: vec2 getTexCoord0 ( int num , int surface = 0 ) const

Возвращает текстурную координату первого канала UV по заданному индексу.
### Аргументы

- *int* **num** - Индекс текстурной координаты.
- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Текстурная координата.
## void setNumTexCoords1 ( int size , int surface = 0 )

Задаёт количество текстурных координат второго канала UV для заданной поверхности.
### Аргументы

- *int* **size** - Количество текстурных координат.
- *int* **surface** - Индекс поверхности.

## int getNumTexCoords1 ( int surface = 0 ) const

Возвращает количество текстурных координат второго канала UV для заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Количество текстурных координат.
## void addTexCoords1 ( const Vector < Math:: vec2 > & texcoords , int surface = 0 )

Добавляет несколько текстурных координат второго канала UV к заданной поверхности.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[vec2](../../../api/library/math/class.vec2_cpp.md)> &* **texcoords** - Массив добавляемых текстурных координат.
- *int* **surface** - Индекс поверхности.

## void addTexCoord1 ( const Math:: vec2 & texcoord , int surface = 0 )

Добавляет одну текстурную координату второго канала UV к заданной поверхности.
### Аргументы

- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **texcoord** - Текстурная координата.
- *int* **surface** - Индекс поверхности.

## void setTexCoord1 ( int num , const Math:: vec2 & texcoord , int surface = 0 )

Задаёт текстурную координату второго канала UV по заданному индексу.
### Аргументы

- *int* **num** - Индекс текстурной координаты.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **texcoord** - Текстурная координата.
- *int* **surface** - Индекс поверхности.

## Math:: vec2 getTexCoord1 ( int num , int surface = 0 ) const

Возвращает текстурную координату второго канала UV по заданному индексу.
### Аргументы

- *int* **num** - Индекс текстурной координаты.
- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Текстурная координата.
## void setNumNormals ( int size , int surface = 0 , int target = 0 )

Задаёт количество нормалей для заданной поверхности и morph target.
### Аргументы

- *int* **size** - Количество нормалей.
- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

## int getNumNormals ( int surface = 0 , int target = 0 ) const

Возвращает количество нормалей для заданной поверхности и morph target.
### Аргументы

- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

### Возвращаемое значение

Количество нормалей.
## void addNormals ( const Vector < Math:: vec3 > & normals , int surface = 0 , int target = 0 )

Добавляет несколько нормалей к заданной поверхности и morph target.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[vec3](../../../api/library/math/class.vec3_cpp.md)> &* **normals** - Массив добавляемых нормалей.
- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

## void addNormal ( const Math:: vec3 & normal , int surface = 0 , int target = 0 )

Добавляет одну нормаль к заданной поверхности и morph target.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **normal** - Вектор нормали.
- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

## void setNormal ( int num , const Math:: vec3 & normal , int surface = 0 , int target = 0 )

Задаёт нормаль по заданному индексу.
### Аргументы

- *int* **num** - Индекс нормали.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **normal** - Вектор нормали.
- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

## Math:: vec3 getNormal ( int num , int surface = 0 , int target = 0 ) const

Возвращает нормаль по заданному индексу.
### Аргументы

- *int* **num** - Индекс нормали.
- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

### Возвращаемое значение

Вектор нормали.
## void setNumTangents ( int size , int surface = 0 , int target = 0 )

Задаёт количество тангенсов для заданной поверхности и morph target.
### Аргументы

- *int* **size** - Количество тангенсов.
- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

## int getNumTangents ( int surface , int target = 0 ) const

Возвращает количество тангенсов для заданной поверхности и morph target.
### Аргументы

- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

### Возвращаемое значение

Количество тангенсов.
## void addTangents ( const Vector < Math:: quat > & tangents , int surface = 0 , int target = 0 )

Добавляет несколько тангенсов к заданной поверхности и morph target.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[quat](../../../api/library/math/class.quat_cpp.md)> &* **tangents** - Массив добавляемых кватернионов тангенсов.
- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

## void addTangent ( const Math:: quat & tangent , int surface = 0 , int target = 0 )

Добавляет один тангенс к заданной поверхности и morph target.
### Аргументы

- *const  Math::[quat](../../../api/library/math/class.quat_cpp.md) &* **tangent** - Кватернион тангенса, кодирующий тангенциальный базис.
- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

## void setTangent ( int num , const Math:: quat & tangent , int surface = 0 , int target = 0 )

Задаёт тангенс по заданному индексу.
### Аргументы

- *int* **num** - Индекс тангенса.
- *const  Math::[quat](../../../api/library/math/class.quat_cpp.md) &* **tangent** - Кватернион тангенса.
- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

## Math:: quat getTangent ( int num , int surface = 0 , int target = 0 ) const

Возвращает тангенс по заданному индексу.
### Аргументы

- *int* **num** - Индекс тангенса.
- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

### Возвращаемое значение

Кватернион тангенса.
## void setNumColors ( int size , int surface = 0 )

Задаёт количество цветов вершин для заданной поверхности.
### Аргументы

- *int* **size** - Количество цветов вершин.
- *int* **surface** - Индекс поверхности.

## int getNumColors ( int surface = 0 ) const

Возвращает количество цветов вершин для заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Количество цветов вершин.
## void addColors ( const Vector < Math:: vec4 > & colors , int surface = 0 )

Добавляет несколько цветов вершин к заданной поверхности.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[vec4](../../../api/library/math/class.vec4_cpp.md)> &* **colors** - Массив добавляемых цветов вершин.
- *int* **surface** - Индекс поверхности.

## void addColor ( const Math:: vec4 & color , int surface = 0 )

Добавляет один цвет вершины к заданной поверхности.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет вершины (RGBA, диапазон от 0.0 до 1.0).
- *int* **surface** - Индекс поверхности.

## void setColor ( int num , const Math:: vec4 & color , int surface = 0 )

Задаёт цвет вершины по заданному индексу.
### Аргументы

- *int* **num** - Индекс цвета.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет вершины (RGBA, диапазон от 0.0 до 1.0).
- *int* **surface** - Индекс поверхности.

## Math:: vec4 getColor ( int num , int surface = 0 ) const

Возвращает цвет вершины по заданному индексу.
### Аргументы

- *int* **num** - Индекс цвета.
- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Цвет вершины (RGBA, диапазон от 0.0 до 1.0).
## void setNumCIndices ( int size , int surface = 0 )

Задаёт количество координатных индексов для заданной поверхности.
### Аргументы

- *int* **size** - Количество координатных индексов.
- *int* **surface** - Индекс поверхности.

## int getNumCIndices ( int surface = 0 ) const

Возвращает количество координатных индексов для заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Количество координатных индексов.
## void addCIndices ( const Vector <int> & indices , int surface = 0 )

Добавляет несколько координатных индексов к заданной поверхности.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **indices** - Массив добавляемых координатных индексов.
- *int* **surface** - Индекс поверхности.

## void addCIndex ( int index , int surface = 0 )

Добавляет один координатный индекс к заданной поверхности.
### Аргументы

- *int* **index** - Добавляемый координатный индекс.
- *int* **surface** - Индекс поверхности.

## void setCIndex ( int num , int index , int surface = 0 )

Задаёт координатный индекс в заданной позиции.
### Аргументы

- *int* **num** - Позиция в буфере координатных индексов.
- *int* **index** - Значение координатного индекса.
- *int* **surface** - Индекс поверхности.

## int getCIndex ( int num , int surface = 0 ) const

Возвращает координатный индекс в заданной позиции.
### Аргументы

- *int* **num** - Позиция в буфере координатных индексов.
- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Значение координатного индекса.
## void setNumTIndices ( int size , int surface = 0 )

Задаёт количество треугольных индексов для заданной поверхности.
### Аргументы

- *int* **size** - Количество треугольных индексов.
- *int* **surface** - Индекс поверхности.

## int getNumTIndices ( int surface = 0 ) const

Возвращает количество треугольных индексов для заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Количество треугольных индексов.
## void addTIndices ( const Vector <int> & indices , int surface = 0 )

Добавляет несколько треугольных индексов к заданной поверхности.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **indices** - Массив добавляемых треугольных индексов.
- *int* **surface** - Индекс поверхности.

## void addTIndex ( int index , int surface = 0 )

Добавляет один треугольный индекс к заданной поверхности.
### Аргументы

- *int* **index** - Добавляемый треугольный индекс.
- *int* **surface** - Индекс поверхности.

## void setTIndex ( int num , int index , int surface = 0 )

Задаёт треугольный индекс в заданной позиции.
### Аргументы

- *int* **num** - Позиция в буфере треугольных индексов.
- *int* **index** - Значение треугольного индекса.
- *int* **surface** - Индекс поверхности.

## int getTIndex ( int num , int surface = 0 ) const

Возвращает треугольный индекс в заданной позиции.
### Аргументы

- *int* **num** - Позиция в буфере треугольных индексов.
- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Значение треугольного индекса.
## void setNumIndices ( int size , int surface = 0 )

Задаёт количество индексов рендеринга для заданной поверхности.
### Аргументы

- *int* **size** - Количество индексов рендеринга.
- *int* **surface** - Индекс поверхности.

## int getNumIndices ( int surface = 0 ) const

Возвращает количество индексов рендеринга для заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Количество индексов рендеринга.
## void addIndices ( const Vector <int> & indices , int surface = 0 )

Добавляет несколько индексов рендеринга к заданной поверхности.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **indices** - Массив добавляемых индексов рендеринга.
- *int* **surface** - Индекс поверхности.

## void addIndex ( int index , int surface = 0 )

Добавляет один индекс рендеринга к заданной поверхности.
### Аргументы

- *int* **index** - Добавляемый индекс рендеринга.
- *int* **surface** - Индекс поверхности.

## void setIndex ( int num , int index , int surface = 0 )

Задаёт индекс рендеринга в заданной позиции.
### Аргументы

- *int* **num** - Позиция в буфере индексов рендеринга.
- *int* **index** - Значение индекса рендеринга.
- *int* **surface** - Индекс поверхности.

## int getIndex ( int num , int surface = 0 ) const

Возвращает индекс рендеринга в заданной позиции.
### Аргументы

- *int* **num** - Позиция в буфере индексов рендеринга.
- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Значение индекса рендеринга.
## Vector < Math:: vec3 > & getVertices ( int surface = 0 , int target = 0 )

Возвращает прямой доступ к массиву позиций вершин для заданной поверхности и morph target.
### Аргументы

- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

### Возвращаемое значение

Ссылка на массив позиций вершин.
## Vector < Math:: vec3 > & getNormals ( int surface = 0 , int target = 0 )

Возвращает прямой доступ к массиву нормалей для заданной поверхности и morph target.
### Аргументы

- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

### Возвращаемое значение

Ссылка на массив нормалей.
## Vector < Math:: quat > & getTangents ( int surface = 0 , int target = 0 )

Возвращает прямой доступ к массиву кватернионов тангенсов для заданной поверхности и morph target.
### Аргументы

- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

### Возвращаемое значение

Ссылка на массив кватернионов тангенсов.
## Vector < Math:: vec2 > & getTexCoords0 ( int surface = 0 )

Возвращает прямой доступ к массиву текстурных координат первого канала UV для заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Ссылка на массив первого канала UV.
## Vector < Math:: vec2 > & getTexCoords1 ( int surface = 0 )

Возвращает прямой доступ к массиву текстурных координат второго канала UV для заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Ссылка на массив второго канала UV.
## Vector < Math:: bvec4 > & getColors ( int surface = 0 )

Возвращает прямой доступ к массиву цветов вершин для заданной поверхности. Цвета хранятся с точностью 8 бит на канал (bvec4).
### Аргументы

- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Ссылка на массив цветов вершин (8 бит на канал).
## Vector <int> & getCIndices ( int surface = 0 )

Возвращает прямой доступ к массиву координатных индексов для заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Ссылка на массив координатных индексов.
## Vector <int> & getTIndices ( int surface = 0 )

Возвращает прямой доступ к массиву треугольных индексов для заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Ссылка на массив треугольных индексов.
## const Vector < Math:: vec3 > & getVertices ( int surface = 0 , int target = 0 ) const

Возвращает доступ только для чтения к массиву позиций вершин для заданной поверхности и morph target.
### Аргументы

- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

### Возвращаемое значение

Константная ссылка на массив позиций вершин.
## const Vector < Math:: vec3 > & getNormals ( int surface = 0 , int target = 0 ) const

Возвращает доступ только для чтения к массиву нормалей для заданной поверхности и morph target.
### Аргументы

- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

### Возвращаемое значение

Константная ссылка на массив нормалей.
## const Vector < Math:: quat > & getTangents ( int surface = 0 , int target = 0 ) const

Возвращает доступ только для чтения к массиву кватернионов тангенсов для заданной поверхности и morph target.
### Аргументы

- *int* **surface** - Индекс поверхности.
- *int* **target** - Индекс morph target.

### Возвращаемое значение

Константная ссылка на массив кватернионов тангенсов.
## const Vector < Math:: vec2 > & getTexCoords0 ( int surface = 0 ) const

Возвращает доступ только для чтения к массиву текстурных координат первого канала UV для заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Константная ссылка на массив первого канала UV.
## const Vector < Math:: vec2 > & getTexCoords1 ( int surface = 0 ) const

Возвращает доступ только для чтения к массиву текстурных координат второго канала UV для заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Константная ссылка на массив второго канала UV.
## const Vector < Math:: bvec4 > & getColors ( int surface = 0 ) const

Возвращает доступ только для чтения к массиву цветов вершин для заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Константная ссылка на массив цветов вершин (8 бит на канал).
## const Vector <int> & getCIndices ( int surface = 0 ) const

Возвращает доступ только для чтения к массиву координатных индексов для заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Константная ссылка на массив координатных индексов.
## const Vector <int> & getTIndices ( int surface = 0 ) const

Возвращает доступ только для чтения к массиву треугольных индексов для заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Константная ссылка на массив треугольных индексов.
## Math:: BoundBox getBoundBox ( int surface ) const

Возвращает выровненный по осям ограничивающий параллелепипед для заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Ограничивающий параллелепипед для заданной поверхности.
## Math:: BoundSphere getBoundSphere ( int surface ) const

Возвращает ограничивающую сферу для заданной поверхности.
### Аргументы

- *int* **surface** - Индекс поверхности.

### Возвращаемое значение

Ограничивающая сфера для заданной поверхности.
## void setBoundBox ( const Math:: BoundBox & bb , int surface )

Задаёт ограничивающий параллелепипед для заданной поверхности.
### Аргументы

- *const  Math::[BoundBox](../../../api/library/math/bounds/class.boundbox_cpp.md) &* **bb** - Задаваемый ограничивающий параллелепипед.
- *int* **surface** - Индекс поверхности.

## void setBoundBox ( const Math:: BoundBox & bb )

Задаёт ограничивающий параллелепипед для всего меша.
### Аргументы

- *const  Math::[BoundBox](../../../api/library/math/bounds/class.boundbox_cpp.md) &* **bb** - Задаваемый ограничивающий параллелепипед.

## void setBoundSphere ( const Math:: BoundSphere & bs , int surface )

Задаёт ограничивающую сферу для заданной поверхности.
### Аргументы

- *const  Math::[BoundSphere](../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Задаваемая ограничивающая сфера.
- *int* **surface** - Индекс поверхности.

## void setBoundSphere ( const Math:: BoundSphere & bs )

Задаёт ограничивающую сферу для всего меша.
### Аргументы

- *const  Math::[BoundSphere](../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Задаваемая ограничивающая сфера.
