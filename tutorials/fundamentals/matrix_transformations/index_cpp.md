# Matrix Transformations (CPP)


Множество расчётов в UNIGINE выполняется с использованием матриц. По сути, матричные преобразования являются одной из основных концепций 3D-движков. Эта статья содержит объяснение матричных преобразований с примерами использования.


### См. также


- Статья о типах данных UNIGINE [mat4](../../../code/uniginescript/language/data_types.md#mat4) и [dmat4](../../../code/uniginescript/language/data_types.md#dmat4).
- Описание [Math Matrix Functions](../../../api/library/math/math.matrix_cpp.md).


## Преобразования


Проще говоря, матрица в 3D-графике - это массив чисел, расположенных в строках и столбцах:


![](matrix_2.png)


Обычно используются матрицы 4x4. Такой размер (4x4) матриц обусловлен состоянием перемещения в 3D-пространстве. Когда вы помещаете новый узел в мир, у него есть матрица мировой трансформации 4x4, определяющая позицию узла в мире.


В UNIGINE матрицы столбцовые (column-oriented). Следовательно, первый столбец матрицы трансформации представляет вектор **X** локальной системы координат (v1), второй представляет вектор **Y** (v2), третий представляет вектор **Z** (v3), а четвёртый представляет вектор перемещения t. Первые три столбца показывают направления локальных осей координат ([rotation](#rotation_matrix)) и [scale](#scaling_matrix) начала координат. Последний столбец содержит перемещение локального начала координат относительно мирового начала координат.


![](opengl_matrix_2.png)


### Единичная матрица


Мировое начало координат имеет следующую матрицу:


![](identity_matrix.png)


Эта матрица называется *единичной матрицей (identity matrix)* - матрицей с единицами на главной диагонали и нулями во всех остальных местах. Если матрицу умножить на единичную матрицу, ничего не изменится: результирующая матрица будет такой же, какой была до умножения.


Если локальное начало координат имеет единичную матрицу, это означает, что локальное и мировое начала координат *совпадают*.


![](same_origin.png)


### Поворот


Чтобы изменить ориентацию локального начала координат, следует изменить первые три столбца матрицы.


Чтобы повернуть начало координат вдоль разных осей, следует использовать соответствующие матрицы:


![](rot_matrices.png)


В приведённых выше матрицах α - угол поворота вдоль оси.


Следующая матрица показывает поворот локального начала координат вдоль оси **Y** на 45 градусов:


| ![](rotation_origin.png) | ![](rotation_45.png) |
|---|---|


### Перемещение


Последний столбец матрицы трансформации показывает позицию локального начала координат в мире относительно мирового начала координат. Следующая матрица показывает перемещение начала координат. Вектор перемещения t равен (3, 0, 2).


| ![](translation_origin.png) | ![](translate_302.png) |
|---|---|


### Масштабирование


Длина вектора показывает коэффициент масштаба вдоль оси.


Чтобы вычислить длину вектора (также известную как величина), нужно найти квадратный корень из суммы квадратов компонентов вектора. Формула следующая:


```text
|vector length| = √(x² + y² + z²)
```


Следующая матрица масштабирует локальное начало координат до 2 единиц вдоль всех осей.


| ![](scale_origin.png) | ![](scale_2.png) |
|---|---|


## Накопление преобразований


Порядок матричных преобразований в коде очень важен.


Если вы хотите реализовать последовательность накапливающихся преобразований, порядок преобразований в коде должен быть следующим:


```text
TransformedVector = TransformationMatrixN * ... * TransformationMatrix2 * TransformationMatrix1 * Vector
```


Преобразования применяются одно за другим, начиная с TransformationMatrix1 и заканчивая TransformationMatrixN.


### Пример


Этот пример показывает разницу между двумя порядками матричных преобразований.


Пример кода ниже получает объект material ball. В первом случае за поворотом следует перемещение, а во втором случае за перемещением следует поворот.


В файле `AppWorldLogic.h` определите умный указатель узла material_ball.


```cpp
// AppWorldLogic.h

/* ... */

class AppWorldLogic : public Unigine::WorldLogic {

public:
	/* .. */
private:
	Unigine::NodePtr material_ball;
};

```


В файле `AppWorldLogic.cpp` выполните следующее:


- Подключите заголовочные файлы `UnigineEditor.h, UnigineVisualizer.h, UnigineConsole.h`.
- Используйте директивы **using namespace Unigine** и **using namespace Unigine::Math**: имена пространств имён Unigine и *Unigine::Math* будут внедрены в глобальное пространство имён.
- Включите визуализатор, передав команду *[`show_visualizer 1`](../../../code/console/index.md#visualizer)* функции *[run()](../../../api/library/engine/class.console_cpp.md#run_cstr_void)* класса *Console*.
- Получите *material ball* из редактора.
- Создайте новые матрицы поворота и перемещения.
- Вычислите новую матрицу трансформации и примените её к *material ball*.
- Отрендерите мировое начало координат с помощью метода *[renderVector()](../../../api/library/engine/class.visualizer_cpp.md#renderVector_Vec3_Vec3_vec4_float_int_float_int_void)* класса *Visualizer*.


```cpp
// AppWorldLogic.cpp file
#include "AppWorldLogic.h"
#include "UnigineWorld.h"
#include "UnigineVisualizer.h"
#include "UnigineConsole.h"

// inject Unigine and Unigine::Math namespaces names to global namespace
using namespace Unigine;
using namespace Unigine::Math;

/* ... */

int AppWorldLogic::init() {

	// включаем визуализатор для рендеринга мирового начала координат
	Console::run("show_visualizer 1");

	// получаем material ball
	material_ball = World::getNodeByName("material_ball");

	// создаём матрицы поворота и перемещения
	Mat4 rotation_matrix = (Mat4)rotateZ(-90.0f);
	Mat4 translation_matrix = (Mat4)translate(vec3(0.0f, 3.0f, 0.0f));

	// создаём новую матрицу трансформации для material ball,
	// умножая текущую матрицу на матрицы поворота и перемещения
	Mat4 transform = translation_matrix * rotation_matrix * material_ball->getTransform();

	// устанавливаем матрицу трансформации для material ball
	material_ball->setTransform(transform);

	return 1;
}

int AppWorldLogic::update() {
	// рендерим мировое начало координат
	Visualizer::renderVector(Vec3(0.0f,0.0f,0.1f), Vec3(1.0f,0.0f,0.1f), vec4_red);
	Visualizer::renderVector(Vec3(0.0f,0.0f,0.1f), Vec3(0.0f,1.0f,0.1f), vec4_green);
	Visualizer::renderVector(Vec3(0.0f,0.0f,0.1f), Vec3(0.0f,0.0f,1.1f), vec4_blue);

	return 1;
}

```


Чтобы изменить порядок, просто измените строку накопления преобразований:


```cpp
Mat4 transform = rotation_matrix * translation_matrix * material_ball->getTransform();
```


Результат будет разным. Изображения ниже показывают разницу (камера расположена в одном и том же месте).


| ![](mb_order_tr.png) | ![](mb_order_rt.png) |
|---|---|
| *Порядок: поворот и перемещение* | *Порядок: перемещение и поворот* |


Изображения выше показывают позицию мешей относительно мирового начала координат.


## Иерархия матриц


Ещё одна важная концепция - иерархия матриц. Когда узел добавляется в мир как дочерний узел другого узла, у него есть матрица трансформации, связанная с родительским узлом. Именно поэтому класс *[*Node*](../../../api/library/nodes/class.node_cpp.md)* различает функции *[*getTransform()*](../../../api/library/nodes/class.node_cpp.md#getTransform_Mat4), [*setTransform()*](../../../api/library/nodes/class.node_cpp.md#setTransform_Mat4_void)* и *[*getWorldTransform()*](../../../api/library/nodes/class.node_cpp.md#getWorldTransform_Mat4), [*setWorldTransform()*](../../../api/library/nodes/class.node_cpp.md#setWorldTransform_Mat4_void)*, которые возвращают локальную и мировую матрицы трансформации соответственно.


> **Примечание:** Если у добавленного узла нет родителя, этот узел использует *матрицу мировой трансформации*.


В чём причина использования иерархии матриц? Чтобы перемещать узел относительно другого узла. И когда вы перемещаете родительский узел, дочерние узлы тоже переместятся.


| ![](hierarchy1.png) | ![](hierarchy2.png) |
|---|---|
| *Начало координат родителя совпадает с мировым началом координат* | *Начало координат родителя было перемещено, и начало координат потомка тоже было перемещено* |


Изображения выше показывают главную суть иерархии матриц. Когда начало координат родителя (узла) перемещается, начало координат потомка тоже переместится, а локальная матрица трансформации потомка не изменится. Но мировая матрица трансформации потомка изменится. Если вам нужна мировая матрица трансформации потомка относительно мирового начала координат, следует использовать функции *[*getWorldTransform()*](../../../api/library/nodes/class.node_cpp.md#getWorldTransform_Mat4), [*setWorldTransform()*](../../../api/library/nodes/class.node_cpp.md#setWorldTransform_Mat4_void)*; в случае, если вам нужна локальная матрица трансформации потомка относительно родителя, следует использовать функции *[*getTransform()*](../../../api/library/nodes/class.node_cpp.md#getTransform_Mat4), [*setTransform()*](../../../api/library/nodes/class.node_cpp.md#setTransform_Mat4_void)*.


### Пример


Следующий пример показывает, насколько важна иерархия матриц.


В этом примере мы получаем узел и клонируем его. Затем мы изменяем матрицы трансформации этих узлов. Мы рассмотрим два случая:


1. Два узла независимы.
2. Один узел является дочерним по отношению к другому.


В файле `AppWorldLogic.h` определите умные указатели дочернего и родительского узлов material_ball.


```cpp
// AppWorldLogic.h

/* ... */

class AppWorldLogic : public Unigine::WorldLogic {

public:
	/* .. */
private:
	Unigine::NodePtr material_ball_child;
	Unigine::NodePtr material_ball_parent;
};

```


В `AppWorldLogic.cpp` реализуйте следующий код:


```cpp
// AppWorldLogic.cpp
#include "AppWorldLogic.h"
#include "UnigineEditor.h"
#include "UnigineVisualizer.h"
#include "UnigineConsole.h"
#include "UnigineLog.h"

using namespace Unigine;
using namespace Unigine::Math;

int AppWorldLogic::init() {

	// включаем визуализатор для рендеринга мирового начала координат
	Console::run("show_visualizer 1");

	// получаем material ball и клонируем его
	material_ball_child = World::getNodeByName("material_ball");
	material_ball_parent = material_ball_child->clone();

	// делаем один узел дочерним по отношению к другому
	material_ball_parent->addChild(material_ball_child);

	// создаём матрицы поворота и перемещения для первого material_ball
	Mat4 rotation_matrix = (Mat4)rotateZ(-90.0f);
	Mat4 translation_matrix = (Mat4)translate(vec3(3.0f, 0.0f, 0.0f));

	// создаём матрицу перемещения для второго (родительского) material ball
	Mat4 translation_matrix_clone = (Mat4)translate(vec3(0.5f, 0.0f, 1.0f));

	// создаём новые матрицы трансформации для material ball
	Mat4 transform = translation_matrix * rotation_matrix * material_ball_child->getTransform();
	Mat4 transform_clone = translation_matrix_clone * material_ball_parent->getTransform();

	// устанавливаем матрицы трансформации для material ball
	material_ball_child->setTransform(transform);
	material_ball_parent->setTransform(transform_clone);

	return 1;
}

int AppWorldLogic::update() {
	// рендерим мировое начало координат
	Visualizer::renderVector(Vec3(0.0f,0.0f,0.1f), Vec3(1.0f,0.0f,0.1f), vec4_red);
	Visualizer::renderVector(Vec3(0.0f,0.0f,0.1f), Vec3(0.0f,1.0f,0.1f), vec4_green);
	Visualizer::renderVector(Vec3(0.0f,0.0f,0.1f), Vec3(0.0f,0.0f,1.1f), vec4_blue);

	return 1;
}

int AppWorldLogic::shutdown() {
	// очищаем умные указатели
	material_ball_child.clear();
	material_ball_parent.clear();

	return 1;
}

```


Если закомментировать следующую строку:


```cpp
// делаем один узел дочерним по отношению к другому
material_ball_parent->addChild(material_ball_child);

```


вы получите другой результат:


| ![](hierarchy_parent.png) | ![](hierarchy_indie.png) |
|---|---|
| *Узлы родитель-потомок* | *Узлы независимы* |


Когда узлы независимы, у них разные локальные и мировые матрицы трансформации. В случае узлов родитель-потомок локальная матрица трансформации потомка остаётся той же после перемещения, но мировая матрица трансформации меняется (это можно проверить с помощью отладочного профилировщика).
