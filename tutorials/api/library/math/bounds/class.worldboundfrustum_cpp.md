# Unigine::WorldBoundFrustum Struct (CPP)

**Header:** #include <UnigineMathLibBounds.h>


Эта структура служит для построения ограничивающего усечённого объёма (frustum) в координатах двойной точности.


*WorldBoundFrustum* позволяет проверить:


- находится ли заданный ограничивающий объём (параллелепипед, сфера или другой усечённый объём) внутри данного усечённого объёма (даже частично) - для этого используйте методы *[inside( bound )](#inside_WorldBoundSphere_int)*.
- находится ли заданный ограничивающий объём (параллелепипед, сфера или другой усечённый объём) внутри данного усечённого объёма полностью - для этого используйте методы *[insideAll( bound )](#insideAll_WorldBoundSphere_int)*.
- находятся ли определённые точки вашего объекта внутри усечённого объёма (может потребоваться, если нужны **более точные результаты**, чем получаемые двумя описанными выше методами) - здесь следует использовать методы *[inside( point )](#inside_dvec3_int)* и проверять все интересующие точки. ![](../check_points.jpg)


> **Notice:** При необходимости убедитесь, что для усечённого объёма используется корректная **проекция с учётом соотношения сторон (aspect-corrected)**. См. изображение в спойлере ниже: *красный* - стандартная матрица проекции, *зелёный* - матрица проекции с учётом соотношения сторон.


<details>
<summary>Коррекция соотношения сторон для проекции усечённого объёма | Закрыть</summary>

![](../boundfrustum1.jpg)
![](../boundfrustum2.jpg)

</details>


### Пример использования


Например, можно использовать *WorldBoundFrustum*, чтобы проверить, находится ли узел внутри видового усечённого объёма камеры. Ознакомьтесь с компонентом ниже.


<details>
<summary>FrustumChecker.h | Закрыть</summary>

```cpp
#pragma once
#include <UnigineComponentSystem.h>
class FrustumChecker :
	public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(FrustumChecker, Unigine::ComponentBase);
	COMPONENT_UPDATE(update);

private:
	void update();
};

```

</details>


<details>
<summary>FrustumChecker.cpp | Закрыть</summary>

```cpp
#include "FrustumChecker.h"
#include "UnigineGame.h"
#include "UnigineMathLibBounds.h"
#include "UnigineVisualizer.h"
REGISTER_COMPONENT(FrustumChecker);

using namespace Unigine;

void FrustumChecker::update()
{
	// получение текущей камеры
	Unigine::CameraPtr camera = Game::getPlayer()->getCamera();

	// получение главного окна приложения
	Unigine::EngineWindowPtr main_window = WindowManager::getMainWindow();
	if (!main_window) {
		Engine::get()->quit();
		return;
	}

	// вычисление текущего соотношения сторон для получения корректной матрицы проекции с учётом соотношения сторон
	// стандартная матрица проекции не учитывает соотношение сторон
	Unigine::Math::ivec2 main_size = WindowManager::getMainWindow()->getSize();
	float aspect = float(main_size.y) / main_size.x;
	Unigine::Math::mat4 proj = camera->getAspectCorrectedProjection(aspect);

	// получение матрицы model-view камеры
	Unigine::Math::Mat4 model_view = camera->getModelview();
	Unigine::Math::WorldBoundFrustum bfrustum(proj, model_view);

	// проверка, находится ли ограничивающий объём узла внутри видового усечённого объёма камеры
	if (bfrustum.inside(node->getWorldBoundBox())) {
		Log::message("Node's bound is visible inside the frustum.");

		// проверка, находится ли ограничивающий объём полностью или частично внутри усечённого объёма
		Log::message(bfrustum.insideAll(node->getWorldBoundBox()) ? " COMPLETELY!\n": " PARTIALLY!\n");

		// проверка, находится ли определённая точка объекта (здесь WorldPosition) внутри усечённого объёма
		Log::message(bfrustum.inside(node->getWorldPosition()) ? "(The point is INSIDE)\n" : "(The point is OUTSIDE)\n");
	}
	else
		Log::message("Node's bound is outside the frustum.\n");

	// отображение BoundBox узла, ограничивающего усечённого объёма и точки с использованием Visualizer
	Visualizer::renderFrustum(proj, Math::inverse(model_view), Math::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	Visualizer::renderBoundBox(node->getBoundBox(), node->getTransform(), Math::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	Visualizer::renderSphere(0.01f, Math::translate(node->getWorldPosition()), Math::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}

```

</details>


## Класс WorldBoundFrustum

### Методы класса

---

## static WorldBoundFrustumPtr create ( )

Конструктор по умолчанию.
## WorldBoundFrustum ( const Math:: mat4 & projection , const Math:: Mat4 & modelview )

Конструктор. Инициализирует ограничивающий усечённый объём заданными матрицами.
### Аргументы

- *const  Math::[mat4](../../../../api/library/math/class.mat4_cpp.md) &* **projection** - Матрица проекции.
- *const  Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **modelview** - Матрица model-view.

## WorldBoundFrustum ( const WorldBoundFrustum & bf )

Конструктор. Инициализирует заданным ограничивающим усечённым объёмом.
### Аргументы

- *const [WorldBoundFrustum](../../../../api/library/math/bounds/class.worldboundfrustum_cpp.md) &* **bf** - Ограничивающий усечённый объём.

## WorldBoundFrustum ( const BoundFrustum & bf )

Конструктор. Инициализирует заданным ограничивающим усечённым объёмом.
### Аргументы

- *const [BoundFrustum](../../../../api/library/math/bounds/class.boundfrustum_cpp.md) &* **bf** - Ограничивающий усечённый объём.

## WorldBoundFrustum ( const WorldBoundFrustum & bf , const Math:: Mat4 & itransform )

Конструктор. Инициализирует заданным ограничивающим усечённым объёмом и матрицей трансформации.
### Аргументы

- *const [WorldBoundFrustum](../../../../api/library/math/bounds/class.worldboundfrustum_cpp.md) &* **bf** - Ограничивающий усечённый объём.
- *const  Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **itransform** - Обратная матрица трансформации.

## WorldBoundFrustum ( const BoundFrustum & bf , const Math:: Mat4 & itransform )

Конструктор. Инициализирует заданным ограничивающим усечённым объёмом и матрицей трансформации.
### Аргументы

- *const [BoundFrustum](../../../../api/library/math/bounds/class.boundfrustum_cpp.md) &* **bf** - Ограничивающий усечённый объём.
- *const  Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **itransform** - Обратная матрица трансформации.

## WorldBoundFrustum & operator= ( const WorldBoundFrustum & bf )

Оператор присваивания.
### Аргументы

- *const [WorldBoundFrustum](../../../../api/library/math/bounds/class.worldboundfrustum_cpp.md) &* **bf** - Ограничивающий усечённый объём.

### Возвращаемое значение

Ограничивающий усечённый объём.
## void clear ( )

Очищает ограничивающий усечённый объём.
## void set ( const Math:: mat4 & projection , const Math:: Mat4 & modelview )

Задаёт ограничивающий усечённый объём заданными матрицами.
### Аргументы

- *const  Math::[mat4](../../../../api/library/math/class.mat4_cpp.md) &* **projection** - Матрица проекции.
- *const  Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **modelview** - Матрица model-view.

## void set ( const WorldBoundFrustum & bf )

Задаёт ограничивающий усечённый объём заданным ограничивающим усечённым объёмом.
### Аргументы

- *const [WorldBoundFrustum](../../../../api/library/math/bounds/class.worldboundfrustum_cpp.md) &* **bf** - Ограничивающий усечённый объём.

## void set ( const WorldBoundFrustum & bf , const Math:: Mat4 & itransform )

Задаёт ограничивающий усечённый объём заданным ограничивающим усечённым объёмом и матрицей трансформации.
### Аргументы

- *const [WorldBoundFrustum](../../../../api/library/math/bounds/class.worldboundfrustum_cpp.md) &* **bf** - Ограничивающий усечённый объём.
- *const  Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **itransform** - Обратная матрица трансформации.

## void set ( const BoundFrustum & bf )

Задаёт ограничивающий усечённый объём заданным ограничивающим усечённым объёмом.
### Аргументы

- *const [BoundFrustum](../../../../api/library/math/bounds/class.boundfrustum_cpp.md) &* **bf** - Ограничивающий усечённый объём.

## void set ( const BoundFrustum & bf , const Math:: Mat4 & itransform )

Задаёт ограничивающий усечённый объём заданным ограничивающим усечённым объёмом и матрицей трансформации.
### Аргументы

- *const [BoundFrustum](../../../../api/library/math/bounds/class.boundfrustum_cpp.md) &* **bf** - Ограничивающий усечённый объём.
- *const  Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **itransform** - Обратная матрица трансформации.

## bool isValid ( ) const

Проверяет статус ограничивающего усечённого объёма.
### Возвращаемое значение

true, если ограничивающий усечённый объём допустим; иначе false.
## void setITransform ( const Math:: dmat4 & itransform )

Задаёт текущую матрицу трансформации обратной матрицей трансформации.
### Аргументы

- *const  Math::[dmat4](../../../../api/library/math/class.dmat4_cpp.md) &* **itransform** - Обратная матрица трансформации.

## void setTransform ( const Math:: dmat4& transform )

Задаёт текущую матрицу трансформации указанной исходной матрицей трансформации.
### Аргументы

- *const  Math:: dmat4&* **transform** - Исходная матрица трансформации.

## int compare ( const WorldBoundFrustum & bf ) const

Сравнивает текущий ограничивающий усечённый объём с заданным.
### Аргументы

- *const [WorldBoundFrustum](../../../../api/library/math/bounds/class.worldboundfrustum_cpp.md) &* **bf** - Ограничивающий усечённый объём.

### Возвращаемое значение

**true**, если текущий ограничивающий усечённый объём равен заданному; иначе **false**.
## int operator== ( const WorldBoundFrustum & bf ) const

Оператор сравнения ограничивающих усечённых объёмов на равенство.
### Аргументы

- *const [WorldBoundFrustum](../../../../api/library/math/bounds/class.worldboundfrustum_cpp.md) &* **bf** - Ограничивающий усечённый объём для сравнения.

### Возвращаемое значение

**true**, если текущий ограничивающий усечённый объём равен заданному; иначе **false**.
## int operator!= ( const WorldBoundFrustum & bf ) const

Оператор сравнения ограничивающих усечённых объёмов на неравенство.
### Аргументы

- *const [WorldBoundFrustum](../../../../api/library/math/bounds/class.worldboundfrustum_cpp.md) &* **bf** - Ограничивающий усечённый объём для сравнения.

### Возвращаемое значение

**true**, если текущий ограничивающий усечённый объём не равен заданному; иначе **false**.
## int inside ( const Math:: Vec3 & point ) const

Проверяет, находится ли точка внутри ограничивающего усечённого объёма.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **point** - Координаты точки.

### Возвращаемое значение

**1**, если точка находится внутри ограничивающего усечённого объёма; иначе **0**.
## int inside ( const Math:: Vec3 & point , Math::Scalar radius ) const

Проверяет, находится ли сфера внутри ограничивающего усечённого объёма.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **point** - Координаты центра сферы.
- *Math::Scalar* **radius** - Радиус сферы.

### Возвращаемое значение

**1**, если сфера находится внутри ограничивающего усечённого объёма; иначе **0**.
## int inside ( const Math:: Vec3 & min , const Math:: Vec3 & max ) const

Проверяет, находится ли параллелепипед внутри ограничивающего усечённого объёма.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **min** - Минимальная координата параллелепипеда.
- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **max** - Максимальная координата параллелепипеда.

### Возвращаемое значение

**1**, если параллелепипед находится внутри ограничивающего усечённого объёма; иначе **0**.
## int inside ( const Math:: Vec3 * points , int num ) const

Проверяет, находится ли набор точек внутри ограничивающего усечённого объёма.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) ** **points** - Вектор точек.
- *int* **num** - Количество точек.

### Возвращаемое значение

**1**, если точки находятся внутри ограничивающего усечённого объёма; иначе **0**.
## int inside ( const WorldBoundSphere & bs ) const

Проверяет, находится ли ограничивающая сфера внутри ограничивающего усечённого объёма.
### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

### Возвращаемое значение

**1**, если ограничивающая сфера находится внутри ограничивающего усечённого объёма; иначе **0**.
## int inside ( const WorldBoundBox & bb ) const

Проверяет, находится ли ограничивающий параллелепипед внутри ограничивающего усечённого объёма.
### Аргументы

- *const [WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед.

### Возвращаемое значение

**1**, если ограничивающий параллелепипед находится внутри ограничивающего усечённого объёма; иначе **0**.
## int inside ( const WorldBoundFrustum & bb ) const

Проверяет, находится ли ограничивающий усечённый объём, указанный в аргументе, внутри ограничивающего усечённого объёма.
### Аргументы

- *const [WorldBoundFrustum](../../../../api/library/math/bounds/class.worldboundfrustum_cpp.md) &* **bb** - Ограничивающий усечённый объём.

### Возвращаемое значение

**1**, если заданный ограничивающий усечённый объём находится внутри ограничивающего усечённого объёма; иначе **0**.
## int insideFast ( const Math:: Vec3 & point ) const

Выполняет быструю проверку, находится ли точка внутри ограничивающего усечённого объёма.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **point** - Точка.

### Возвращаемое значение

**1**, если точка находится внутри ограничивающего усечённого объёма; иначе **0**.
## int insideFast ( const Math:: Vec3 & point , Math::Scalar radius ) const

Выполняет быструю проверку, находится ли сфера внутри ограничивающего усечённого объёма.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **point** - Центральная точка.
- *Math::Scalar* **radius** - Радиус.

### Возвращаемое значение

**1**, если сфера находится внутри ограничивающего усечённого объёма; иначе **0**.
## int insideFast ( const Math:: Vec3 & min , const Math:: Vec3 & max ) const

Выполняет быструю проверку, находится ли параллелепипед внутри ограничивающего усечённого объёма.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **min** - Минимальная точка.
- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **max** - Максимальная точка.

### Возвращаемое значение

**1**, если параллелепипед находится внутри ограничивающего усечённого объёма; иначе **0**.
## int insideFast ( const Math:: Vec3 * points , int num_points ) const

Выполняет быструю проверку, находится ли набор точек внутри ограничивающего усечённого объёма.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) ** **points** - Вектор точек.
- *int* **num_points** - Количество точек.

### Возвращаемое значение

**1**, если точка находится внутри ограничивающего усечённого объёма; иначе **0**.
## int insideValid ( const WorldBoundSphere & bs ) const

Проверяет, находится ли заданная ограничивающая сфера внутри ограничивающего усечённого объёма (предполагая, что текущие координаты ограничивающего объёма допустимы).
> **Notice:** Метод не проверяет [status](#isValid_bool) текущего ограничивающего усечённого объёма.


### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

### Возвращаемое значение

**1**, если заданная ограничивающая сфера находится внутри ограничивающего усечённого объёма; иначе **0**.
## int insideValid ( const WorldBoundBox & bb ) const

Проверяет, находится ли заданный ограничивающий параллелепипед внутри ограничивающего усечённого объёма (предполагая, что текущие координаты ограничивающего объёма допустимы).
> **Notice:** Метод не проверяет [status](#isValid_bool) текущего ограничивающего усечённого объёма.


### Аргументы

- *const [WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед.

### Возвращаемое значение

**1**, если заданный ограничивающий параллелепипед находится внутри ограничивающего усечённого объёма; иначе **0**.
## int insideValid ( const WorldBoundFrustum & bb ) const

Проверяет, находится ли заданный ограничивающий усечённый объём внутри ограничивающего усечённого объёма (предполагая, что текущие координаты ограничивающего объёма допустимы).
> **Notice:** Метод не проверяет [status](#isValid_bool) текущего ограничивающего усечённого объёма.


### Аргументы

- *const [WorldBoundFrustum](../../../../api/library/math/bounds/class.worldboundfrustum_cpp.md) &* **bb** - Ограничивающий усечённый объём.

### Возвращаемое значение

**1**, если заданный ограничивающий усечённый объём находится внутри ограничивающего усечённого объёма; иначе **0**.
## int insideValidFast ( const WorldBoundSphere & bs ) const

Выполняет быструю проверку, находится ли заданная ограничивающая сфера внутри текущего ограничивающего усечённого объёма (предполагая, что текущие координаты ограничивающего объёма допустимы).
> **Notice:** Метод не проверяет [status](#isValid_bool) текущего ограничивающего усечённого объёма.


### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

### Возвращаемое значение

**1**, если заданная ограничивающая сфера находится внутри ограничивающего усечённого объёма; иначе **0**.
## int insideValidFast ( const WorldBoundBox & bb ) const

Выполняет быструю проверку, находится ли заданный ограничивающий параллелепипед внутри текущего ограничивающего усечённого объёма (предполагая, что текущие координаты ограничивающего объёма допустимы).
> **Notice:** Метод не проверяет [status](#isValid_bool) текущего ограничивающего усечённого объёма.


### Аргументы

- *const [WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед.

### Возвращаемое значение

**1**, если заданный ограничивающий параллелепипед находится внутри ограничивающего усечённого объёма; иначе **0**.
## int insideValidFast ( const WorldBoundFrustum & bb ) const

Выполняет быструю проверку, находится ли заданный ограничивающий усечённый объём внутри текущего ограничивающего усечённого объёма (предполагая, что текущие координаты ограничивающего объёма допустимы).
> **Notice:** Метод не проверяет [status](#isValid_bool) текущего ограничивающего усечённого объёма.


### Аргументы

- *const [WorldBoundFrustum](../../../../api/library/math/bounds/class.worldboundfrustum_cpp.md) &* **bb** - Ограничивающий усечённый объём.

### Возвращаемое значение

**1**, если заданный ограничивающий усечённый объём находится внутри ограничивающего усечённого объёма; иначе **0**.
## int insideAll ( const WorldBoundBox & bb ) const

Проверяет, находится ли целиком заданный ограничивающий параллелепипед внутри текущего ограничивающего усечённого объёма.
### Аргументы

- *const [WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед.

### Возвращаемое значение

**1**, если весь параллелепипед находится внутри ограничивающего усечённого объёма; иначе **0**.
## int insideAll ( const WorldBoundSphere & bs ) const

Проверяет, находится ли целиком заданная ограничивающая сфера внутри текущего ограничивающего усечённого объёма.
### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

### Возвращаемое значение

**1**, если вся сфера находится внутри ограничивающего усечённого объёма; иначе **0**.
## int insideAll ( const WorldBoundFrustum & bs ) const

Проверяет, находится ли целиком заданный ограничивающий усечённый объём внутри текущего ограничивающего усечённого объёма.
### Аргументы

- *const [WorldBoundFrustum](../../../../api/library/math/bounds/class.worldboundfrustum_cpp.md) &* **bs** - Ограничивающий усечённый объём.

### Возвращаемое значение

**1**, если заданный усечённый объём находится внутри ограничивающего усечённого объёма; иначе **0**.
## int insideAllValid ( const WorldBoundSphere & bs ) const

Проверяет, находится ли целиком заданная ограничивающая сфера внутри текущего ограничивающего усечённого объёма (предполагая, что текущие координаты ограничивающего объёма допустимы).
> **Notice:** Метод не проверяет [status](#isValid_bool) текущего ограничивающего усечённого объёма.


### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

### Возвращаемое значение

**1**, если заданная ограничивающая сфера находится внутри ограничивающего усечённого объёма; иначе **0**.
## int insideAllValid ( const WorldBoundBox & bb ) const

Проверяет, находится ли целиком заданный ограничивающий параллелепипед внутри текущего ограничивающего усечённого объёма (предполагая, что текущие координаты ограничивающего объёма допустимы).
> **Notice:** Метод не проверяет [status](#isValid_bool) текущего ограничивающего усечённого объёма.


### Аргументы

- *const [WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед.

### Возвращаемое значение

**1**, если заданный ограничивающий параллелепипед находится внутри ограничивающего усечённого объёма; иначе **0**.
## int insideAllValid ( const WorldBoundFrustum & bb ) const

Проверяет, находится ли целиком заданный ограничивающий усечённый объём внутри текущего ограничивающего усечённого объёма (предполагая, что текущие координаты ограничивающего объёма допустимы).
> **Notice:** Метод не проверяет [status](#isValid_bool) текущего ограничивающего усечённого объёма.


### Аргументы

- *const [WorldBoundFrustum](../../../../api/library/math/bounds/class.worldboundfrustum_cpp.md) &* **bb** - Ограничивающий усечённый объём.

### Возвращаемое значение

**1**, если заданный ограничивающий усечённый объём находится внутри ограничивающего усечённого объёма; иначе **0**.
## int insideAllValidFast ( const WorldBoundSphere & bs ) const

Выполняет быструю проверку, находится ли целиком заданная ограничивающая сфера внутри текущего ограничивающего усечённого объёма (предполагая, что текущие координаты ограничивающего объёма допустимы).
> **Notice:** Метод не проверяет [status](#isValid_bool) текущего ограничивающего усечённого объёма.


### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

### Возвращаемое значение

**1**, если заданная ограничивающая сфера находится внутри ограничивающего усечённого объёма; иначе **0**.
## int insideAllValidFast ( const WorldBoundBox & bb ) const

Выполняет быструю проверку, находится ли целиком заданный ограничивающий параллелепипед внутри текущего ограничивающего усечённого объёма (предполагая, что текущие координаты ограничивающего объёма допустимы).
> **Notice:** Метод не проверяет [status](#isValid_bool) текущего ограничивающего усечённого объёма.


### Аргументы

- *const [WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед.

### Возвращаемое значение

**1**, если заданный ограничивающий параллелепипед находится внутри ограничивающего усечённого объёма; иначе **0**.
## int insideAllValidFast ( const WorldBoundFrustum & bb ) const

Выполняет быструю проверку, находится ли целиком заданный ограничивающий усечённый объём внутри текущего ограничивающего усечённого объёма (предполагая, что текущие координаты ограничивающего объёма допустимы).
> **Notice:** Метод не проверяет [status](#isValid_bool) текущего ограничивающего усечённого объёма.


### Аргументы

- *const [WorldBoundFrustum](../../../../api/library/math/bounds/class.worldboundfrustum_cpp.md) &* **bb** - Ограничивающий усечённый объём.

### Возвращаемое значение

**1**, если заданный ограничивающий усечённый объём находится внутри ограничивающего усечённого объёма; иначе **0**.
## bool insidePlanes ( const WorldBoundSphere & bs ) const

Проверяет, находится ли заданная ограничивающая сфера внутри объёма, определяемого плоскостями текущего ограничивающего усечённого объёма.
### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

### Возвращаемое значение

**true**, если заданная ограничивающая сфера находится внутри объёма; иначе **false**.
## bool insidePlanes ( const WorldBoundBox & bb ) const

Проверяет, находится ли заданный ограничивающий параллелепипед внутри объёма, определяемого плоскостями текущего ограничивающего усечённого объёма.
### Аргументы

- *const [WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед.

### Возвращаемое значение

**true**, если заданный ограничивающий параллелепипед находится внутри объёма; иначе **false**.
## bool insidePlanes ( const WorldBoundFrustum & bf ) const

Проверяет, находится ли заданный ограничивающий усечённый объём внутри объёма, определяемого плоскостями текущего ограничивающего усечённого объёма.
### Аргументы

- *const [WorldBoundFrustum](../../../../api/library/math/bounds/class.worldboundfrustum_cpp.md) &* **bf** - Ограничивающий усечённый объём.

### Возвращаемое значение

**true**, если заданный ограничивающий усечённый объём находится внутри объёма; иначе **false**.
## bool insidePlanesValid ( const WorldBoundSphere & bs ) const

Проверяет, находится ли заданная ограничивающая сфера внутри объёма, определяемого плоскостями текущего ограничивающего усечённого объёма (предполагая, что текущие координаты ограничивающего объёма допустимы).
> **Notice:** Метод не проверяет [status](#isValid_bool) текущего ограничивающего усечённого объёма.


### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

### Возвращаемое значение

**true**, если заданная ограничивающая сфера находится внутри объёма; иначе **false**.
## bool insidePlanesValid ( const WorldBoundBox & bb ) const

Проверяет, находится ли заданный ограничивающий параллелепипед внутри объёма, определяемого плоскостями текущего ограничивающего усечённого объёма (предполагая, что текущие координаты ограничивающего объёма допустимы).
> **Notice:** Метод не проверяет [status](#isValid_bool) текущего ограничивающего усечённого объёма.


### Аргументы

- *const [WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед.

### Возвращаемое значение

**true**, если заданный ограничивающий параллелепипед находится внутри объёма; иначе **false**.
## bool insidePlanesValid ( const WorldBoundFrustum & bf ) const

Проверяет, находится ли заданный ограничивающий усечённый объём внутри объёма, определяемого плоскостями текущего ограничивающего усечённого объёма (предполагая, что текущие координаты ограничивающего объёма допустимы).
> **Notice:** Метод не проверяет [status](#isValid_bool) текущего ограничивающего усечённого объёма.


### Аргументы

- *const [WorldBoundFrustum](../../../../api/library/math/bounds/class.worldboundfrustum_cpp.md) &* **bf** - Ограничивающий усечённый объём.

### Возвращаемое значение

**true**, если заданный ограничивающий усечённый объём находится внутри объёма; иначе **false**.
## bool insidePlanesValidFast ( const WorldBoundSphere & bs ) const

Выполняет быструю проверку, находится ли заданная ограничивающая сфера внутри объёма, определяемого плоскостями текущего ограничивающего усечённого объёма (предполагая, что текущие координаты ограничивающего объёма допустимы).
> **Notice:** Метод не проверяет [status](#isValid_bool) текущего ограничивающего усечённого объёма.


### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

### Возвращаемое значение

**true**, если заданная ограничивающая сфера находится внутри объёма; иначе **false**.
## bool insidePlanesValidFast ( const WorldBoundBox & bb ) const

Выполняет быструю проверку, находится ли заданный ограничивающий параллелепипед внутри объёма, определяемого плоскостями текущего ограничивающего усечённого объёма (предполагая, что текущие координаты ограничивающего объёма допустимы).
> **Notice:** Метод не проверяет [status](#isValid_bool) текущего ограничивающего усечённого объёма.


### Аргументы

- *const [WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед.

### Возвращаемое значение

**true**, если заданный ограничивающий параллелепипед находится внутри объёма; иначе **false**.
## bool insidePlanesValidFast ( const WorldBoundFrustum & bf ) const

Выполняет быструю проверку, находится ли заданный ограничивающий усечённый объём внутри объёма, определяемого плоскостями текущего ограничивающего усечённого объёма (предполагая, что текущие координаты ограничивающего объёма допустимы).
> **Notice:** Метод не проверяет [status](#isValid_bool) текущего ограничивающего усечённого объёма.


### Аргументы

- *const [WorldBoundFrustum](../../../../api/library/math/bounds/class.worldboundfrustum_cpp.md) &* **bf** - Ограничивающий усечённый объём.

### Возвращаемое значение

**true**, если заданный ограничивающий усечённый объём находится внутри объёма; иначе **false**.
## int insideShadowValid ( const WorldBoundSphere & object , const Math:: Vec3 & direction ) const

Проверяет, находится ли заданная ограничивающая сфера внутри тени текущего ограничивающего усечённого объёма (предполагая, что текущие координаты ограничивающего объёма допустимы).
> **Notice:** Метод не проверяет [status](#isValid_bool) текущего ограничивающего усечённого объёма.


### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **object** - Ограничивающая сфера.
- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **direction** - Вектор направления.

### Возвращаемое значение

**1**, если заданная ограничивающая сфера находится внутри тени; иначе **0**.
## bool insideShadowValid ( const WorldBoundSphere & object , const WorldBoundSphere & light , const Math:: Vec3 & offset ) const

Проверяет, находится ли заданная ограничивающая сфера внутри тени текущего ограничивающего усечённого объёма и вне ограничивающей сферы источника света.
> **Notice:** Метод не проверяет [status](#isValid_bool) текущего ограничивающего усечённого объёма.


### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **object** - Ограничивающая сфера.
- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **light** - Ограничивающая сфера источника света.
- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **offset** - Вектор смещения.

### Возвращаемое значение

**true**, если заданная ограничивающая сфера находится внутри тени и вне заданной ограничивающей сферы источника света; иначе **false**.
