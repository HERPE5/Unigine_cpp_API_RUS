# Unigine.PhysicalNoise Class (CPP)

**Header:** #include <UniginePhysicals.h>

**Inherits from:** Physical


Класс *PhysicalNoise* используется для симуляции силового поля, воздействующего на физические тела и частицы на основе объёмной текстуры шума. Он создаёт дополнительный распределённый поток, задающий силу и направление смещения для тел и частиц в каждой точке силового поля.


> **Notice:** - Physical noise может воздействовать только на тело [*cloth*](../../../principles/physics/bodies/cloth/index.md), [*rope*](../../../api/library/physics/class.bodyrope_cpp.md) или [*rigid*](../../../principles/physics/bodies/rigid/index.md). Также следует помнить, что rigid body требует назначенной [shape](../../../principles/physics/shapes/index.md).
> - Physical noise будет воздействовать на частицы только если их физическая масса ненулевая.


### Пример использования


В этом примере создаются узел physical noise и 50 боксов, каждый со своим телом и формой. Созданные боксы падают под действием заданной гравитации и подвергаются воздействию physical noise, попадая в него.


Добавим следующий код в файл **AppWorldLogic.cpp**:


```cpp
// AppWorldLogic.cpp
/* .. */
#include <UnigineGame.h>
#include "AppWorldLogic.h"
#include <UniginePhysicals.h>
#include <UniginePrimitives.h>
#include <UnigineVisualizer.h>

using namespace Unigine;
using namespace Math;

// объявляем узел PhysicalNoise
PhysicalNoisePtr physical_noise;

/// функция, создающая именованный бокс заданного размера, цвета и трансформации с телом и формой
ObjectMeshDynamicPtr createBodyBox(const char* name, vec3 size, float mass, vec4 color, Mat4 transform)
{
	// создаём геометрию и задаём её параметры (имя, цвет и трансформацию)
	ObjectMeshDynamicPtr box = Primitives::createBox(size);
	box->setWorldTransform(transform);
	box->setMaterialParameterFloat4("albedo_color", color, 0);
	box->setName(name);

	// добавляем физику, т.е. rigid body и форму бокса с указанной массой
	BodyRigidPtr body = BodyRigid::create(box);
	body->addShape(ShapeBox::create(size), translate(vec3(0.0f)));
	box->getBody()->getShape(0)->setMass(mass);

	// задаём физическую маску для тела
	body->setPhysicalMask(1);

	return box;
}

/* .. */

int AppWorldLogic::init()
{
	// задаём параметры физики (гравитация, линейная и угловая скорости)
	Physics::setGravity(vec3(0.0f, 0.0f, -1.0f));
	Physics::setFrozenLinearVelocity(0.1f);
	Physics::setFrozenAngularVelocity(0.1f);

	// задаём параметры игрока
	Game::getPlayer()->setWorldPosition(Vec3(0.0f, 90.0f, 70.0f));
	Game::getPlayer()->setDirection(vec3(0.0f, -1.0f, -0.7f), vec3(0.0f, 0.0f, -1.0f));

	// создаём узел physical noise размером 60x60x60
	physical_noise = PhysicalNoise::create(vec3(60.0f));

	// задаём множитель силы равным 50
	physical_noise->setForce(50.0f);

	// задаём пороговое расстояние
	physical_noise->setThreshold(vec3(0.0f));

	// задаём физическую маску
	physical_noise->setPhysicalMask(1);

	//задаём параметры генерации текстуры шума (масштаб, частота, размер)
	physical_noise->setNoiseScale(0.2f);
	physical_noise->setFrequency(4);
	physical_noise->setImageSize(16);

	// задаём шаг сэмплирования равным 20
	physical_noise->setStep(vec3(20.0f));

	// включаем визуализатор, чтобы отобразить наш physical noise
	Visualizer::setEnabled(1);

	//генерируем 50 боксов с назначенными rigid bodies и формами
	for (int i = 0; i < 50; i++) {
		Vec3 position = Vec3(Game::getRandomDouble(-50.0f, 50.0f), Game::getRandomDouble(-50.0f, 50.0f), 40.0f);
		vec4 color = vec4(Game::getRandomFloat(0.0f, 1.0f), Game::getRandomFloat(0.0f, 1.0f), Game::getRandomFloat(0.0f, 1.0f), Game::getRandomFloat(0.0f, 1.0f));
		createBodyBox("box", vec3_one, 1.0f, color, translate(position));
	}

	return 1;
}

int AppWorldLogic::update()
{
	// отрисовываем визуализатор для узла physical noise
	physical_noise->renderVisualizer();

	return 1;
}


```


### См. также


- Статья [*Physical Noise*](../../../objects/effects/physicals/physical_noise/index.md), чтобы узнать больше о параметрах


## PhysicalNoise Class

### Методы класса

---

## static PhysicalNoisePtr create ( const Math:: vec3 & size )

Конструктор. Создаёт узел physical noise указанного размера.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **size** - Размер бокса physical noise в единицах.

## void setForce ( float force )

Задаёт значение множителя силы.
### Аргументы

- *float* **force** - Множитель силы. Чем выше значение, тем выше результирующая сила, воздействующая на объект внутри узла physical noise.

## float getForce ( )

Возвращает значение множителя силы.
### Возвращаемое значение

Множитель силы. Чем выше значение, тем выше результирующая сила, воздействующая на объект внутри узла physical noise.
## void setFrequency ( int frequency )

Задаёт количество октав для генерации текстуры шума Перлина.
> **Notice:** Не рекомендуется изменять этот параметр во время выполнения, так как текстура шума будет перегенерирована, что снизит производительность.


### Аргументы

- *int* **frequency** - Количество октав для генерации текстуры шума Перлина. Минимальное значение — **1**, максимальное — **16**. Чем выше значение, тем больше деталей в текстуре шума.

## int getFrequency ( )

Возвращает количество октав для генерации текстуры шума Перлина.
> **Notice:** Не рекомендуется изменять этот параметр во время выполнения, так как текстура шума будет перегенерирована, что снизит производительность.


### Возвращаемое значение

Количество октав для генерации текстуры шума Перлина. Минимальное значение — **1**, максимальное — **16**. Чем выше значение, тем больше деталей в текстуре шума.
## Ptr < Image > getImage ( )

Возвращает изображение текстуры шума.
### Возвращаемое значение

Изображение текстуры шума.
## void setImageSize ( int size )

Задаёт размер текстуры шума в пикселях.
### Аргументы

- *int* **size** - Размер текстуры шума в пикселях.

## int getImageSize ( )

Возвращает размер текстуры шума в пикселях.
### Возвращаемое значение

Размер текстуры шума в пикселях.
## void setNoiseScale ( float scale )

Задаёт масштаб текстуры шума.
> **Notice:** Не рекомендуется изменять этот параметр во время выполнения, так как текстура шума будет перегенерирована, что снизит производительность.


### Аргументы

- *float* **scale** - Масштаб текстуры шума. Минимальное значение — **0**, максимальное — **1**.

## float getNoiseScale ( )

Возвращает масштаб текстуры шума.
### Возвращаемое значение

Масштаб текстуры шума. Минимальное значение — 0, максимальное — 1.
## void setOffset ( const Math:: vec3 & offset )

Задаёт смещение сэмплирования, используемое для выборки пикселей из текстуры шума.
> **Notice:** Этот параметр можно использовать для анимации силового поля во время выполнения.


### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **offset** - Смещение сэмплирования по осям X, Y и Z.

## Math:: vec3 getOffset ( )

Возвращает смещение сэмплирования, используемое для выборки пикселей из текстуры шума.
> **Notice:** Этот параметр можно использовать для анимации силового поля во время выполнения.


### Возвращаемое значение

Смещение сэмплирования по осям X, Y и Z.
## void setSize ( const Math:: vec3 & size )

Задаёт размер узла physical noise.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **size** - Размер бокса physical noise в единицах. Если указано отрицательное значение, вместо него используется 0.

## Math:: vec3 getSize ( )

Возвращает текущий размер узла physical noise.
### Возвращаемое значение

Размер бокса physical noise в единицах.
## void setStep ( const Math:: vec3 & step )

Задаёт шаг сэмплирования, используемый для выборки пикселей из текстуры шума.
> **Notice:** Этот параметр можно использовать для анимации силового поля во время выполнения.


### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **step** - Размер шага сэмплирования по осям X, Y и Z.

## Math:: vec3 getStep ( )

Возвращает шаг сэмплирования, используемый для выборки пикселей из текстуры шума.
> **Notice:** Этот параметр можно использовать для анимации силового поля во время выполнения.


### Возвращаемое значение

Размер шага сэмплирования по осям X, Y и Z.
## void setThreshold ( const Math:: vec3 & threshold )

Задаёт пороговое расстояние для узла physical noise. Порог определяет расстояние постепенного изменения от нуля до полного значения силы. Эти значения задаются относительно размера бокса physical noise. Это означает, что пороговые значения должны быть меньше размера бокса physical noise.
![](../../../objects/effects/physicals/threshold.png)


### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **threshold** - Пороговое расстояние по осям X, Y и Z.

## Math:: vec3 getThreshold ( )

 Возвращает пороговое расстояние, заданное для узла physical noise. Порог определяет расстояние постепенного изменения от нуля до полного значения силы. Эти значения задаются относительно размера бокса physical noise. Это означает, что пороговые значения должны быть меньше размера бокса physical noise.
### Возвращаемое значение

## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [PhysicalNoise](../../../api/library/nodes/class.node_cpp.md#PHYSICAL_NOISE).
