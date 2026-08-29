# Unigine::Random Class (CPP)

**Header:** #include <UnigineMathLibRandom.h>


Этот класс реализует функции генерации псевдослучайных чисел для различных целей. Используется 32-битное значение seed (начальное значение); при создании экземпляр инициализируется значением seed, равным текущему времени. В случае, если два экземпляра *Random* созданы с одинаковым значением seed, и для каждого из них выполняется одна и та же последовательность вызовов методов, они будут генерировать и возвращать идентичные последовательности чисел. Поэтому, если у вас есть компонент, использующий собственный внутренний член *Random* (например, для перемещения узла в случайном направлении, см. код ниже), последовательность чисел, генерируемая для разных узлов с этим назначенным компонентом, скорее всего будет одинаковой, что приведёт к тому, что все узлы будут двигаться вместе в одном направлении.


![](balls_sync.gif)


<details>
<summary>Компонент, использующий класс Math::Random (одинаковые значения) | Закрыть</summary>

```cpp
#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineMathLibRandom.h>
class RandomMovement : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(RandomMovement, Unigine::ComponentBase);
	COMPONENT_UPDATE(update);

	PROP_PARAM(Float, speed, 2.0f, "Speed");	// скорость перемещения
private:
	Unigine::Math::Random rnd;	// внутренний генератор случайных чисел
	void update();
};

```


```cpp
#include "RandomMovement.h"
#include <UnigineGame.h>
using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(RandomMovement);

void RandomMovement::update()
{
	// формируем вектор направления с использованием случайных значений (различается для разных узлов с назначенным компонентом)
	vec3 dir = vec3(rnd.getInt(-1, 2), rnd.getInt(-1, 2), 0);
	vec3 p0 = node->getWorldPosition();
	vec3 p1 = p0 + dir * speed * Game::getIFps();

	// перемещаем узел вдоль полученного вектора направления с заданной скоростью
	node->setWorldPosition(p1);
}

```

</details>


Чтобы избежать такого поведения, вы можете использовать аналогичные методы класса *[Game](../../../api/library/engine/class.game_cpp.md)*, так как в этом случае используется единый генератор *Random* (внутренний член класса *Game*), и каждый вызов метода *[Game::getRandom*()](../../../api/library/engine/class.game_cpp.md#getRandom_uint)* возвращает следующий элемент последовательности псевдослучайных чисел.


![](balls_async.gif)


<details>
<summary>Компонент, использующий генератор случайных чисел класса Game (разные значения) | Закрыть</summary>

```cpp
#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineGame.h>
class RandomMovement : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(RandomMovement, Unigine::ComponentBase);
	COMPONENT_UPDATE(update);

	PROP_PARAM(Float, speed, 2.0f, "Speed");	// скорость перемещения
private:
	void update();
};

```


```cpp
#include "RandomMovement.h"
#include <UnigineGame.h>

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(RandomMovement);

void RandomMovement::update()
{
	// формируем вектор направления с использованием случайных значений (различается для разных узлов с назначенным компонентом)
	vec3 dir = vec3(Game::getRandomInt(-1, 2), Game::getRandomInt(-1, 2), 0);
	vec3 p0 = node->getWorldPosition();
	vec3 p1 = p0 + dir * speed * Game::getIFps();

	// перемещаем узел вдоль полученного вектора направления с заданной скоростью
	node->setWorldPosition(p1);
}

```

</details>


## Random Class

### Методы класса

---

## static RandomPtr create ( )

Конструктор. Инициализирует генератор случайных чисел.
## static RandomPtr create ( unsigned int seed_ )

Конструктор. Инициализирует генератор случайных чисел с заданным значением seed.
### Аргументы

- *unsigned int* **seed_** - Значение seed.

## Random & getRandom ( )

Возвращает статический потокобезопасный объект случайных чисел.
### Возвращаемое значение

Потокобезопасный объект случайных чисел.
## void setSeed ( unsigned int seed_ ) const

Задаёт новое значение seed.
### Аргументы

- *unsigned int* **seed_** - Новое значение seed.

## unsigned int getSeed ( ) const

Возвращает активное значение seed.
### Возвращаемое значение

Активное значение seed.
## unsigned int get ( ) const

Возвращает случайное беззнаковое целое число.
### Возвращаемое значение

Случайное беззнаковое целое число.
## int getInt ( )

Возвращает случайное целое число.
### Возвращаемое значение

Случайное целое число.
## unsigned long long getULong ( )

Возвращает случайное беззнаковое длинное целое число (64 бита).
### Возвращаемое значение

Случайное беззнаковое длинное целое число (64 бита).
## long long getLong ( )

Возвращает случайное длинное целое число (64 бита).
### Возвращаемое значение

Случайное длинное целое число (64 бита).
## float getFloat ( )

Возвращает случайное число типа float.
### Возвращаемое значение

Случайное число типа float.
## double getDouble ( )

Возвращает случайное число типа double.
### Возвращаемое значение

Случайное число типа double.
## int getInt ( int from , int to ) const

Возвращает случайное целое число в заданном диапазоне **[from,to)**.
### Аргументы

- *int* **from** - Начало диапазона.
- *int* **to** - Конец диапазона.

### Возвращаемое значение

Случайное целое число.
## float getFloat ( float from , float to ) const

Возвращает случайное число типа float в заданном диапазоне **[from,to)**.
### Аргументы

- *float* **from** - Начало диапазона.
- *float* **to** - Конец диапазона.

### Возвращаемое значение

Случайное число типа float.
## double getDouble ( double from , double to ) const

Возвращает случайное число типа double в заданном диапазоне **[from,to)**.
### Аргументы

- *double* **from** - Начало диапазона.
- *double* **to** - Конец диапазона.

### Возвращаемое значение

Случайное число типа double.
## vec4 getColor ( ) const

Возвращает случайный цвет.
### Возвращаемое значение

Случайный цвет.
## vec3 getDirection ( ) const

Возвращает случайный вектор направления (нормализованный).
### Возвращаемое значение

Случайный вектор направления.
