# SkeletonPoseMatrix Class (CPP)

**Header:** #include <UnigineSkeleton.h>


Этот класс представляет позу скелета, хранимую как матрицы 4x4 (mat4) для каждого сустава. В отличие от [SkeletonPoseDecomposed](../../../../api/library/animations/skeletal/class.skeletonposedecomposed_cpp.md), который хранит положение, поворот и масштаб отдельно, этот класс хранит трансформацию каждого сустава в виде единой матрицы — что может быть более эффективно для некоторых операций, таких как скининг.


Трансформация каждого сустава может храниться либо в локальном пространстве (относительно родительского сустава), либо в пространстве объекта (относительно корня скелета). Используйте [convertToObjectSpace()](#convertToObjectSpace_void) и [convertToLocalSpace()](#convertToLocalSpace_void) для переключения между представлениями.


## SkeletonPoseMatrix Class

### Перечисления

## SPACE_TYPE

Тип координатного пространства для трансформаций позы.
| Имя | Описание |
|---|---|
| **SPACE_TYPE_LOCAL** = 0 | Трансформации заданы относительно родительского сустава. |
| **SPACE_TYPE_OBJECT** = 1 | Трансформации заданы в локальном пространстве объекта (относительно корня скелета). |

### Методы класса

## void setSkeleton ( )

Устанавливает новый скелет, связанный с этой позой. Определяет иерархию суставов и количество трансформаций.
### Аргументы

- **skeleton** - Скелет для этой позы.

## getSkeleton () const

Возвращает текущий скелет, связанный с этой позой. Определяет иерархию суставов и количество трансформаций.
### Возвращаемое значение

Текущий скелет для этой позы.
## getNumTransforms () const

Возвращает текущее общее количество трансформаций суставов в позе, соответствующее количеству суставов в назначенном скелете.
### Возвращаемое значение

Текущее количество трансформаций суставов.
## getSpaceType () const

Возвращает текущее координатное пространство трансформаций позы.
### Возвращаемое значение

Текущий тип координатного пространства.
---

## static SkeletonPoseMatrixPtr create ( )

Создаёт пустую матричную позу без назначенного скелета.
## static SkeletonPoseMatrixPtr create ( const Ptr <ConstSkeleton> & skeleton )

Создаёт матричную позу, инициализированную для указанного скелета, с трансформациями, выделенными для всех суставов.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<ConstSkeleton> &* **skeleton** - Скелет, для которого инициализируется поза.

## void clear ( )

Очищает все трансформации суставов и сбрасывает позу в пустое состояние.
## void setTransform ( int index , const Math:: mat4 & transform )

Устанавливает матричную трансформацию для сустава с указанным индексом.
### Аргументы

- *int* **index** - Индекс сустава.
- *const  Math::[mat4](../../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матричная трансформация, устанавливаемая для сустава.

## Math:: mat4 getTransform ( int index ) const

Возвращает матричную трансформацию для сустава с указанным индексом.
### Аргументы

- *int* **index** - Индекс сустава.

### Возвращаемое значение

Матричная трансформация сустава.
## void convertToObjectSpace ( )

Преобразует все трансформации суставов из локального пространства в пространство объекта. После этого вызова трансформация каждого сустава задаётся относительно корня скелета, а не относительно его родительского сустава.
## void convertToLocalSpace ( )

Преобразует все трансформации суставов из пространства объекта в локальное пространство. После этого вызова трансформация каждого сустава задаётся относительно его родительского сустава.
## void inverse ( )

Инвертирует все трансформации суставов в позе.
## void renderJoints ( const Math:: Mat4 & world_offset , float basis_length = 0.03f , bool depth_test = false ) const

Отображает отладочную визуализацию координатных осей всех суставов в вьюпорте.
### Аргументы

- *const  Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **world_offset** - Мировая матрица трансформации для позиционирования отладочной визуализации.
- *float* **basis_length** - Длина линий координатных осей для каждого сустава, в единицах.
- *bool* **depth_test** - Следует ли включить тест глубины для отладочной визуализации.

## void renderSelectedJoints ( const Vector <int> & joints , const Math:: Mat4 & world_offset , float basis_length = 0.03f , bool depth_test = false ) const

Отображает отладочную визуализацию координатных осей выбранных суставов в вьюпорте.
### Аргументы

- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **joints** - Список индексов суставов для отображения.
- *const  Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **world_offset** - Мировая матрица трансформации для позиционирования отладочной визуализации.
- *float* **basis_length** - Длина линий координатных осей для каждого сустава, в единицах.
- *bool* **depth_test** - Следует ли включить тест глубины для отладочной визуализации.

## void renderJointNames ( const Math:: Mat4 & world_offset , const Math:: vec4 & color , int outline = 0 , int font_size = -1 ) const

Отображает отладочные текстовые метки с именами суставов в их положениях в вьюпорте.
### Аргументы

- *const  Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **world_offset** - Мировая матрица трансформации для позиционирования отладочной визуализации.
- *const  Math::[vec4](../../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет текста для меток имён суставов.
- *int* **outline** - Толщина контура текстовых меток, в пикселях. Используйте 0, чтобы отключить контур.
- *int* **font_size** - Размер шрифта текстовых меток, в пикселях. Используйте -1 для размера по умолчанию.

## void renderSelectedJointNames ( const Vector <int> & joints , const Math:: Mat4 & world_offset , const Math:: vec4 & color , int outline = 0 , int font_size = -1 ) const

Отображает отладочные текстовые метки с именами выбранных суставов в их положениях в вьюпорте.
### Аргументы

- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **joints** - Список индексов суставов, для которых требуется отобразить имена.
- *const  Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **world_offset** - Мировая матрица трансформации для позиционирования отладочной визуализации.
- *const  Math::[vec4](../../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет текста для меток имён суставов.
- *int* **outline** - Толщина контура текстовых меток, в пикселях. Используйте 0, чтобы отключить контур.
- *int* **font_size** - Размер шрифта текстовых меток, в пикселях. Используйте -1 для размера по умолчанию.

## void renderBones ( const Math:: Mat4 & world_offset , const Math:: vec4 & color , float radius = 0.01f , bool depth_test = false ) const

Отображает отладочную визуализацию всех костей в виде фигур, соединяющих родительские и дочерние суставы, в вьюпорте.
### Аргументы

- *const  Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **world_offset** - Мировая матрица трансформации для позиционирования отладочной визуализации.
- *const  Math::[vec4](../../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет фигур костей.
- *float* **radius** - Радиус фигур костей, в единицах.
- *bool* **depth_test** - Следует ли включить тест глубины для отладочной визуализации.

## void renderSelectedBones ( const Vector <int> & end_joints , const Math:: Mat4 & world_offset , const Math:: vec4 & color , float radius = 0.01f , bool depth_test = false ) const

Отображает отладочную визуализацию выбранных костей в виде фигур, соединяющих родительские и дочерние суставы, в вьюпорте.
### Аргументы

- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **end_joints** - Список индексов конечных суставов, определяющих, какие кости отображать. Каждая кость рисуется от родителя сустава до самого сустава.
- *const  Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **world_offset** - Мировая матрица трансформации для позиционирования отладочной визуализации.
- *const  Math::[vec4](../../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет фигур костей.
- *float* **radius** - Радиус фигур костей, в единицах.
- *bool* **depth_test** - Следует ли включить тест глубины для отладочной визуализации.

## void assignFrom ( const Ptr < SkeletonPoseMatrix > & other )

Копирует все данные из другой матричной позы, включая ссылку на скелет, трансформации и тип пространства.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[SkeletonPoseMatrix](../../../../api/library/animations/skeletal/class.skeletonposematrix_cpp.md)> &* **other** - Исходная матричная поза, из которой копируются данные.

## void assignFromPoseDecomposed ( const Ptr < SkeletonPoseDecomposed > & other )

Копирует данные из декомпозированной позы, преобразуя декомпозированные трансформации (положение, поворот, масштаб) в матричное представление.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[SkeletonPoseDecomposed](../../../../api/library/animations/skeletal/class.skeletonposedecomposed_cpp.md)> &* **other** - Исходная декомпозированная поза, из которой выполняется преобразование и копирование.

## bool copyFromCompatible ( const Ptr < SkeletonPoseMatrix > & other )

Копирует трансформации суставов из матричной позы, использующей другой, но совместимый скелет (с совпадающими именами суставов).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[SkeletonPoseMatrix](../../../../api/library/animations/skeletal/class.skeletonposematrix_cpp.md)> &* **other** - Исходная матричная поза с совместимым скелетом.

### Возвращаемое значение

true, если копирование прошло успешно (скелеты совместимы); иначе false.
## bool copyFromCompatible ( const Ptr < SkeletonPoseDecomposed > & other )

Копирует трансформации суставов из декомпозированной позы, использующей другой, но совместимый скелет (с совпадающими именами суставов), преобразуя их в матричное представление.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[SkeletonPoseDecomposed](../../../../api/library/animations/skeletal/class.skeletonposedecomposed_cpp.md)> &* **other** - Исходная декомпозированная поза с совместимым скелетом.

### Возвращаемое значение

true, если копирование прошло успешно (скелеты совместимы); иначе false.
## bool blend ( const Ptr < SkeletonPoseMatrix > & pose , float weight )

Смешивает эту позу с другой матричной позой, используя указанный вес. Обе позы должны использовать один и тот же скелет.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[SkeletonPoseMatrix](../../../../api/library/animations/skeletal/class.skeletonposematrix_cpp.md)> &* **pose** - Поза, с которой требуется выполнить блендинг.
- *float* **weight** - Вес блендинга в диапазоне [0.0, 1.0]. Значение 0.0 оставляет текущую позу без изменений, 1.0 полностью заменяет её целевой позой.

### Возвращаемое значение

true, если блендинг прошёл успешно; иначе false.
## bool blendByMask ( const Ptr < SkeletonPoseMatrix > & pose , float weight , const char * mask_name )

Смешивает эту позу с другой матричной позой, используя указанный вес и именованную маску блендинга из скелета. Маска блендинга управляет влиянием для каждого сустава, позволяя выполнять частичный блендинг тела (например, смешивание только суставов верхней части тела).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[SkeletonPoseMatrix](../../../../api/library/animations/skeletal/class.skeletonposematrix_cpp.md)> &* **pose** - Поза, с которой требуется выполнить блендинг.
- *float* **weight** - Вес блендинга в диапазоне [0.0, 1.0], дополнительно модулируемый значениями маски для каждого сустава.
- *const char ** **mask_name** - Имя маски блендинга, определённой в скелете. Маска управляет влиянием блендинга для каждого сустава.

### Возвращаемое значение

true, если блендинг прошёл успешно; иначе false.
