# Unigine::Math::DoubleTransform Struct (CPP)

**Header:** #include <UnigineMathLibTransforms.h>


Структура *DoubleTransform* представляет собой пространственное преобразование, хранимое в разложенной форме TRS (Translation-Rotation-Scale, перенос-поворот-масштаб) с двойной точностью переноса. Она хранит перенос, поворот и масштаб как отдельные компоненты: позицию [dvec3](../../../api/library/math/class.dvec3_cpp.md), поворот [quat](../../../api/library/math/class.quat_cpp.md) и масштаб [vec3](../../../api/library/math/class.vec3_cpp.md).


### Разложенная форма vs. матричная форма


Когда преобразования составляются с помощью умножения матриц (например, [mat4](../../../api/library/math/class.mat4_cpp.md)), неравномерный масштаб родительского преобразования может внести непреднамеренный сдвиг (shearing) в поворот дочернего объекта. Это происходит потому, что масштаб родителя встраивается в строки матрицы, искажая векторы ориентации дочернего объекта при перемножении матриц.


DoubleTransform избегает этого, составляя каждый компонент независимо:


- **Масштаб** - перемножается покомпонентно: *result.scale = parent.scale * child.scale*
- **Поворот** - составляется как кватернионы: *result.rotation = parent.rotation * child.rotation*
- **Позиция** - позиция дочернего объекта сначала масштабируется и поворачивается родителем, затем прибавляется к позиции родителя: *result.position = parent.position + parent.rotation * (parent.scale * child.position)*


В результате повороты дочерних объектов остаются корректными, даже если родительское преобразование имеет неравномерный масштаб.


### Transform и WorldTransform


Для использования в коде приложения предусмотрены два typedef:


- **Transform** - всегда разрешается в [FloatTransform](../../../api/library/math/class.floattransform_cpp.md).
- **WorldTransform** - разрешается в [FloatTransform](../../../api/library/math/class.floattransform_cpp.md) при сборке с одинарной точностью (float build) либо в *DoubleTransform* при сборке с двойной точностью (double build) (когда определён *USE_DOUBLE*).


В коде приложения рекомендуется использовать *WorldTransform* вместо непосредственного использования *DoubleTransform*, поскольку он автоматически выбирает подходящую точность для конфигурации сборки.


### Доступные операции


Следующие свободные функции работают с *DoubleTransform* и определены в том же заголовочном файле:


- [inverse()](../../../api/library/math/math.common_cpp.md#inverse_constDoubleTransformref_DoubleTransform) - возвращает обратное преобразование.
- [mul()](../../../api/library/math/math.common_cpp.md#mul_constDoubleTransformref_constDoubleTransformref_DoubleTransform) - составляет два преобразования или применяет преобразование к точке.
- [blendTransform()](../../../api/library/math/math.common_cpp.md#blendTransform_constDoubleTransformref_constDoubleTransformref_float_DoubleTransform) - интерполирует между двумя преобразованиями.


## DoubleTransform Struct

### Методы класса

---

## DoubleTransform ( )

Конструктор по умолчанию. Создаёт единичное преобразование: позиция в начале координат, отсутствие поворота и равномерный масштаб 1.
## DoubleTransform ( const DoubleTransform & transform )

Конструктор копирования.
### Аргументы

- *const DoubleTransform &* **transform** - Исходное преобразование для копирования.

## DoubleTransform ( const dvec3 & position , const quat & rotation , const vec3 & scale )

Конструктор. Инициализирует преобразование заданными значениями переноса, поворота и масштаба.
### Аргументы

- *const [dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **position** - Компонент переноса.
- *const [quat](../../../api/library/math/class.quat_cpp.md) &* **rotation** - Компонент поворота.
- *const [vec3](../../../api/library/math/class.vec3_cpp.md) &* **scale** - Компонент масштаба.

## void setMat ( const dmat4 & mat )

Задаёт преобразование, разлагая заданную матрицу [dmat4](../../../api/library/math/class.dmat4_cpp.md) на компоненты переноса, поворота и масштаба.
### Аргументы

- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **mat** - Матрица для разложения.

## dmat4 & getMat ( dmat4 & result )

Составляет матрицу [dmat4](../../../api/library/math/class.dmat4_cpp.md) из компонентов преобразования и сохраняет её в предоставленной матрице.
### Аргументы

- *[dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **result** - Выходная матрица для записи.

### Возвращаемое значение

Составленная матрица преобразования.
## dmat4 getMat ( )

Составляет и возвращает матрицу [dmat4](../../../api/library/math/class.dmat4_cpp.md) из компонентов преобразования.
### Возвращаемое значение

Составленная матрица преобразования.
## dmat4 & getIMat ( dmat4 & result )

Вычисляет обратное преобразование в виде матрицы [dmat4](../../../api/library/math/class.dmat4_cpp.md) и сохраняет его в предоставленной матрице.
### Аргументы

- *[dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **result** - Выходная матрица для записи.

### Возвращаемое значение

Матрица обратного преобразования.
## dmat4 getIMat ( )

Вычисляет и возвращает обратное преобразование в виде матрицы [dmat4](../../../api/library/math/class.dmat4_cpp.md).
### Возвращаемое значение

Матрица обратного преобразования.
