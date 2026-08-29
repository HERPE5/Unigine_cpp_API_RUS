# Класс Unigine::Game (CPP)

**Заголовочный файл:** #include <UnigineGame.h>

> **Примечание:** Этот класс является одиночкой (singleton).


Этот класс содержит функции для управления игровой логикой приложения. Он предоставляет функциональность для:


- Назначения игрока вьюпорту *[Engine Camera](../../../editor2/camera_settings/index.md)*.
- Приостановки, ускорения и замедления рендеринга, физики или игровой логики.


### Пример использования


Следующий пример создаёт PlayerSpectator и устанавливает его как активную камеру движка. Игрок вращается вокруг оси Y с заданной скоростью, которая устанавливается через *[setScale()](#setScale_float_void)*:


- Нажатие F замедляет игровую логику, из-за чего вращение игрока также замедляется.
- Нажатие G ускоряет игровую логику и, соответственно, вращение игрока.


```cpp
#include "AppWorldLogic.h"
#include <UniginePlayers.h>
#include <UnigineGame.h>

using namespace Unigine;
using namespace Math;

	// объявляем указатель на PlayerSpectator
	PlayerSpectatorPtr player;

int AppWorldLogic::init()
{

	// создаём новый экземпляр PlayerSpectator
	player = PlayerSpectator::create();

	// задаём необходимые параметры: FOV, ZNear, ZFar, вектор направления взгляда и позицию
	player->setFov(90.0f);
	player->setZNear(0.1f);
	player->setZFar(10000.0f);
	player->setViewDirection(vec3(0.0f, 1.0f, 0.0f));
	player->setWorldPosition(Vec3(-1.6f, -1.7f, 1.7f));

	// устанавливаем игрока для экземпляра-одиночки Game
	Game::setPlayer(player);

	return 1;
}

int AppWorldLogic::update()
{

	// замедляем игровую логику
	if (Input::isKeyDown(Input::KEY_F)) {
		Game::setScale(Game::getScale() / 2);
		Log::message("Game logic speed has been decreased. Frame duration is %f seconds\n", Game::getIFps());
	}

	// ускоряем игровую логику
	if (Input::isKeyDown(Input::KEY_G)) {
		Game::setScale(Game::getScale() * 2);
		Log::message("Game logic speed has been increased. Frame duration is %f seconds\n", Game::getIFps());
	}

	// вращаем игрока на 45 градусов в секунду вокруг оси Y
	player->setWorldRotation(player->getWorldRotation() * quat(0.0f, 1.0f, 0.0f, 45.0f * Game::getIFps()));

	return 1;
}

int AppWorldLogic::shutdown()
{

	// очищаем указатель
	player.clear();

	return 1;
}


```


### См. также


- Статья о классе *[GameIntersection](../../../api/library/engine/class.gameintersection_cpp.md)* как пример использования игровых пересечений
- Пример на UnigineScript
- Пример на UnigineScript


## Класс Game

### Методы класса

---

## void setData ( const char * data )

Устанавливает пользовательские данные, связанные с игровой логикой. Эта строка записывается непосредственно в файл `*.world`, а именно в дочерний тег *data* тега *game*, например:
```xml
<?xml version="1.0" encoding="utf-8"?>
<world version="2.16.0.2">

	<game>
		<data>User data</data>
	</game>

</world>


```


### Аргументы

- *const char ** **data** - Пользовательские данные. Данные могут содержать строку в формате XML.

## const char * getData ( ) const

Возвращает пользовательские данные, связанные с игровой логикой. Эта строка записывается непосредственно в файл `*.world`, а именно в дочерний тег *data* тега *game*, например:
```xml
<?xml version="1.0" encoding="utf-8"?>
<world version="2.16.0.2">

	<game>
		<data>User data</data>
	</game>

</world>


```


### Возвращаемое значение

Пользовательские данные. Данные могут содержать строку в формате XML.
## void setEnabled ( bool enabled )

Приостанавливает или возобновляет игровую логику.
### Аргументы

- *bool* **enabled** - **1** — возобновить игровую логику, **0** — приостановить.

## bool isEnabled ( ) const

Возвращает значение, указывающее, приостановлена ли игра.
### Возвращаемое значение

true, если игровая логика не приостановлена; иначе false.
## void setFrame ( int frame )

Устанавливает игровой кадр с заданным номером как текущий.
### Аргументы

- *int* **frame** - Номер кадра.

## int getFrame ( ) const

Возвращает номер текущего игрового кадра.
```cpp
// получаем текущий игровой кадр
int loading_frames = Game::getFrame();
// выполняем асинхронную загрузку узлов
// ...
// вычисляем количество игровых кадров, потребовавшихся для загрузки узлов
loading_frames = Game::getFrame() - loading_frames;


```


### Возвращаемое значение

Номер кадра.
## void setIFps ( float ifps )

Устанавливает [scaled](#setScale_float_void) значение обратного FPS (время в секундах, потребовавшееся для завершения последнего кадра). Эта функция устанавливает фиксированный FPS, не зависящий от реального FPS, на который способно оборудование. То есть она принудительно задаёт постоянные приращения времени кадра между рендерящимися кадрами, используемые для обновления анимации/выражений и т.д. Чтобы снять ограничение FPS, используйте -1.
Эта функция полезна при захвате видеоряда с фиксированным значением FPS (например, 25 кадров в секунду).


### Аргументы

- *float* **ifps** - Значение обратного FPS (1/FPS) в секундах. **-1** снимает ограничение FPS.

## float getIFps ( ) const

Возвращает [scaled](#setScale_float_void) значение обратного FPS (время в секундах, потребовавшееся для завершения последнего кадра). Это значение не зависит от реального FPS, на который способно оборудование. -1 означает, что значение обратного FPS не задано.
```cpp
NodePtr node;
// ...
// получаем значение обратного FPS
float ifps = Game::getIFps();

// перемещаем узел вверх на 0.1 единицы каждую секунду, а не каждый кадр
node->worldTranslate(Math::Vec3(0.0f, 0.0f, 0.1f * ifps));


```


### Возвращаемое значение

Масштабированное значение обратного FPS (1/FPS) в секундах. Если игра приостановлена, возвращается **0**.
## Ptr < Obstacle > getIntersection ( Vec3 p0 , Vec3 p1 , float radius , int mask , const Vector < Ptr < Node >> & exclude , Math:: Vec3 * OUT_intersection )

Выполняет проверку пересечения, чтобы определить, находится ли препятствие для поиска пути внутри цилиндра между двумя точками. Указанные препятствия будут проигнорированы.
> **Примечание:** Для этой функции используются координаты мирового пространства.


![](cylinder01.png)


### Аргументы

- *[Vec3](../../../api/library/math/class.vec3_cpp.md)* **p0** - Начальная точка.
- *[Vec3](../../../api/library/math/class.vec3_cpp.md)* **p1** - Конечная точка.
- *float* **radius** - Радиус цилиндра пересечения.
- *int* **mask** - Маска пересечения препятствия. Препятствие игнорируется, если его маска не совпадает.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **exclude** - Массив исключаемых препятствий. Эти узлы препятствий игнорируются при выполнении проверки пересечения.
- *Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) ** **OUT_intersection** - Точка пересечения. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

### Возвращаемое значение

Пересекаемое препятствие.
## Ptr < Obstacle > getIntersection ( Vec3 p0 , Vec3 p1 , float radius , int mask , const Ptr < GameIntersection > & intersection )


Выполняет проверку пересечения, чтобы определить, находится ли препятствие для поиска пути внутри цилиндра между двумя точками.


> **Примечание:** Для этой функции используются координаты мирового пространства.


![](cylinder01.png)


Следующий пример показывает, как можно получить точку пересечения (vec3) цилиндра между двумя точками с препятствием. В этом примере мы задаём цилиндр от точки камеры (vec3 p0) до точки указателя мыши (vec3 p1) с заданным радиусом. Последовательность выполнения следующая:

1. Определите и инициализируйте две точки (p0 и p1) с помощью *[Player::getDirectionFromScreen()](../../../api/library/players/class.player_cpp.md#getDirectionFromScreen_Vec3_Vec3_int_int_int_int_int_int_void)*.
2. Создайте экземпляр класса GameIntersection, чтобы получить координаты точки пересечения.
3. Проверьте, есть ли пересечение с препятствием. Функция *Game::getIntersection()* возвращает пересекаемое препятствие, когда препятствие оказывается в области цилиндра.
4. После этого экземпляр GameIntersection получает точку ближайшего пересечения, и вы можете получить её с помощью функции *getPoint()*.


```cpp
/* ... */
// инициализируем точки направления мыши
Vec3 p0, p1;

// получаем текущего игрока (камеру)
PlayerPtr player = Game::getPlayer();
if (player.get() == NULL)
	return 0;

// получаем ширину и высоту текущего окна приложения
ivec2 main_size = ivec2_one;

EngineWindowPtr main_window = WindowManager::getMainWindow();
if (!main_window)
	Engine::get()->quit();

main_size = main_window->getSize();

// получаем текущие координаты X и Y указателя мыши
int mouse_x = Input::getMousePosition().x - main_window->getPosition().x;
int mouse_y = Input::getMousePosition().y - main_window->getPosition().y;

// получаем направление мыши от позиции игрока (p0) до указателя мыши (p1)
player->getDirectionFromScreen(p0, p1, 0, 0, mouse_x, mouse_y, main_size.x, main_size.y);

// создаём экземпляр класса GameIntersection
GameIntersectionPtr intersection = GameIntersection::create();

// пытаемся получить пересечение с препятствием
// цилиндр имеет радиус 1.5f, маска пересечения равна 1
ObstaclePtr obstacle = Game::getIntersection(p0, p1, 1.5f, 1, intersection);

// проверяем, произошло ли пересечение направления мыши с каким-либо препятствием
if (obstacle)
{
	// выводим координаты пересечения в консоль
	Log::message("The intersection with the obstacle was here: (%f %f %f)\n", intersection->getPoint().x, intersection->getPoint().y, intersection->getPoint().z);
}
/* ... */


```


### Аргументы

- *[Vec3](../../../api/library/math/class.vec3_cpp.md)* **p0** - Начальная точка.
- *[Vec3](../../../api/library/math/class.vec3_cpp.md)* **p1** - Конечная точка.
- *float* **radius** - Радиус цилиндра пересечения.
- *int* **mask** - Маска пересечения препятствия. Препятствие игнорируется, если его маска не совпадает.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[GameIntersection](../../../api/library/engine/class.gameintersection_cpp.md)> &* **intersection** - Экземпляр класса [GameIntersection](../../../api/library/engine/class.gameintersection_cpp.md), в который помещается результат.

### Возвращаемое значение

Пересекаемое препятствие.
## float getNoise1 ( float pos , float size , int frequency ) const

Возвращает значение шума, вычисленное с помощью функции шума Перлина.
### Аргументы

- *float* **pos** - Позиция с плавающей точкой.
- *float* **size** - Размер шума.
- *int* **frequency** - Частота шума.

### Возвращаемое значение

Значение шума.
## float getNoise2 ( const Math:: vec2 & pos , const Math:: vec2 & size , int frequency ) const

Возвращает 2D-значение шума, вычисленное с помощью функции шума Перлина.
### Аргументы

- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **pos** - Позиция точки vec2.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **size** - Размер шума vec2.
- *int* **frequency** - Частота шума.

### Возвращаемое значение

2D-значение шума.
## float getNoise3 ( const Math:: vec3 & pos , const Math:: vec3 & size , int frequency ) const

Возвращает 3D-значение шума, вычисленное с помощью функции шума Перлина.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **pos** - vec3 point position.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **size** - vec3 size of the noise.
- *int* **frequency** - Noise frequency.

### Возвращаемое значение

3D-значение шума.
## void setPlayer ( const Ptr < Player > & player )

Назначает нового игрока вьюпорту *Engine Camera*.
```cpp
// создаём нового игрока
PlayerDummyPtr player = PlayerDummy::create();
// задаём необходимые параметры
player->setFov(60.0f);
player->setWorldPosition(Math::Vec3(-1.0f, -1.0f, 1.0f));
// устанавливаем игрока для экземпляра-одиночки Game
Game::setPlayer(player);


```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Player](../../../api/library/players/class.player_cpp.md)> &* **player** - Игрок, устанавливаемый как текущий.

## Ptr < Player > getPlayer ( ) const

Возвращает текущего игрока, назначенного вьюпорту *Engine Camera*.
```cpp
Vec3 p0, p1;

// получаем текущего игрока (камеру)
PlayerPtr player = Game::getPlayer();

if (player.get() == NULL)
	return 0;

// получаем ширину и высоту клиентской области текущего окна приложения
Math::ivec2 winsize = WindowManager::getMainWindow()->getClientSize();
int width = winsize.x;
int height = winsize.y;

// получаем текущие координаты X и Y указателя мыши
int mouse_x = Gui::getCurrent()->getMouseX();
int mouse_y = Gui::getCurrent()->getMouseY();

// получаем направление мыши от позиции игрока (p0) до указателя мыши (p1)
player->getDirectionFromScreen(p0, p1, mouse_x, mouse_y, 0, 0, width, height);


```


### Возвращаемое значение

Текущий игрок.
## unsigned int getRandom ( ) const

Возвращает псевдослучайное беззнаковое целое число.
### Возвращаемое значение

Случайное беззнаковое целое число.
## double getRandomDouble ( double from , double to )

Возвращает псевдослучайное число типа double в заданном диапазоне (конечная точка не включается).
### Аргументы

- *double* **from** - Начальная точка диапазона.
- *double* **to** - Конечная точка диапазона.

### Возвращаемое значение

Случайное число типа double.
## float getRandomFloat ( float from , float to )

Возвращает псевдослучайное число с плавающей точкой в заданном диапазоне (конечная точка не включается).
### Аргументы

- *float* **from** - Начальная точка диапазона.
- *float* **to** - Конечная точка диапазона.

### Возвращаемое значение

Случайное число с плавающей точкой.
## int getRandomInt ( int from , int to )

Возвращает псевдослучайное целое число в заданном диапазоне (конечная точка не включается).
### Аргументы

- *int* **from** - Начальная точка диапазона.
- *int* **to** - Конечная точка диапазона.

### Возвращаемое значение

Случайное целое число.
## void setScale ( float scale )


Устанавливает значение, используемое для масштабирования продолжительности кадра. Оно увеличивает или уменьшает скорость рендеринга, физики и игровой логики. Эту функцию можно использовать для создания эффектов замедленного/ускоренного движения.


Например, если масштаб равен **2**, скорость симуляции всех эффектов (например, частиц) увеличивается вдвое. Что касается физики, на самом деле она будет симулироваться с тем же фиксированным физическим FPS, но количество итераций будет вдвое больше. Физический FPS можно масштабировать отдельно с помощью функции [*engine.physics.setScale()*](../../../api/library/physics/class.physics_cpp.md#setScale_float_void).


Эта функция масштабирует значение, заданное с помощью [*setIFps()*](#setIFps_float_void).


### Аргументы

- *float* **scale** - Коэффициент масштабирования. Указанное значение ограничивается диапазоном **[0;32]**.

## float getScale ( ) const

Возвращает значение, используемое для масштабирования продолжительности кадра.
### Возвращаемое значение

Значение для масштабирования продолжительности кадра.
## void setSeed ( int seed )

Устанавливает начальное значение (seed) для генератора псевдослучайных чисел.
### Аргументы

- *int* **seed** - Число, используемое для инициализации псевдослучайной последовательности чисел.

## int getSeed ( ) const

Возвращает начальное значение (seed) для генератора псевдослучайных чисел.
### Возвращаемое значение

Число, используемое для инициализации псевдослучайной последовательности чисел.
## void setTime ( float time )

Устанавливает значение времени для игры. Время отсчитывается с момента загрузки мира и не учитывает паузы игры.
### Аргументы

- *float* **time** - Время в секундах.

## float getTime ( ) const

Возвращает текущее время, проведённое в игре. Оно отсчитывается с момента загрузки мира и не учитывает паузы игры.
### Возвращаемое значение

Время в секундах.
## void getMainPlayers ( const Vector < Ptr < Player > > & players )

Возвращает массив указателей на игроков, установленных как [main players](../../../api/library/players/class.player_cpp.md#setMainPlayer_int_void).
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Player](../../../api/library/players/class.player_cpp.md)> > &* **players** - Массив указателей на главных игроков.

## Math:: vec4 getRandomColor ( ) const

Возвращает случайно сгенерированный вектор цвета: (R, G, B, A).
### Возвращаемое значение

Четырёхкомпонентный вектор [vec4](../../../api/library/math/class.vec4_cpp.md), представляющий цвет: (R, G, B, A).
## void setPlayerListener ( const Ptr < Player > & listener )

Устанавливает игрока в качестве слушателя.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Player](../../../api/library/players/class.player_cpp.md)> &* **listener** - Игрок, устанавливаемый как слушатель.

## Ptr < Player > getPlayerListener ( ) const

Возвращает игрока, который в данный момент является слушателем.
### Возвращаемое значение

Игрок, установленный как слушатель.
## void getListeners ( Vector < Ptr < Player > > & OUT_players )

Добавляет всех потенциальных слушателей в указанный массив.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Player](../../../api/library/players/class.player_cpp.md)> > &* **OUT_players** - Список для хранения потенциальных слушателей. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.
