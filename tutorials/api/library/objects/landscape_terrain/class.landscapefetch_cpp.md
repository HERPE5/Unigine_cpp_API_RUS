# Unigine.LandscapeFetch Class (CPP)

**Header:** #include <UnigineObjects.h>


Этот класс используется для [fetching](#fetchForce_int) данных объекта [Landscape Terrain](../../../../api/library/objects/landscape_terrain/class.objectlandscapeterrain_cpp.md) в заданной точке (например, запрос высоты) или проверки [intersection](#intersectionForce_int) с трассируемой линией. Доступны следующие оптимизации производительности:


- Для каждого запроса можно включать или отключать определённые типы данных (альбедо, высоты, маски и т.д.). При включённом типе данных информацию можно получить через соответствующий *метод get()*. Отключение ненужных данных при выполнении запросов немного экономит производительность (например, можно включить только данные альбедо, если в заданной точке нужна только информация о цвете).
- Как запросы получения данных (fetch), так и запросы пересечения can be performed [asynchronously](#example_async), когда мгновенный результат не требуется.


Рабочий процесс следующий:


1. Создайте новый экземпляр объекта *LandscapeFetch*.
2. Задайте необходимые параметры (например, какие слои данных использовать, включать ли отверстия и т.д.).
3. Чтобы получить данные террейна для заданной точки, вызовите метод **[fetchForce()](../../../...md#fetchForce_int)**, указав координаты нужной точки. > **Notice:** Данные террейна также можно получать асинхронно с помощью метода **[fetchAsync()](../../../...md#fetchAsync_int_void)**.
4. Чтобы найти пересечение трассируемой линии с террейном, вызовите либо метод **[intersectionForce()](../../../...md#intersectionForce_int)**, либо метод **[intersectionAsync()](../../../...md#intersectionAsync_int_void)**, если требуется выполнить асинхронный запрос.


### Usage Example


```cpp
// создаём объект fetch и задаём необходимые параметры
LandscapeFetchPtr landscape_fetch = LandscapeFetch::create();

// отключаем все типы данных террейна, чтобы включить только необходимые
landscape_fetch->setUses(0);

// включаем проверку данных высот в запросах fetch/intersection, если необходимо
landscape_fetch->setUsesHeight(true);
// включаем проверку данных нормалей в запросах fetch/intersection, если необходимо
landscape_fetch->setUsesNormal(true);

// включаем проверку отверстий террейна в запросах fetch/intersection, если необходимо
landscape_fetch->setHolesEnabled(true);

// включаем проверку необходимых масок (например, первой и второй) в запросах fetch/intersection, если необходимо
landscape_fetch->setUsesMask(0, true);
landscape_fetch->setUsesMask(1, true);

// ...

// получаем данные террейна для точки (100, 100) и выводим значение высоты
landscape_fetch->setFetchPosition(Vec2(100, 100));
if (landscape_fetch->fetchForce())
	Log::message("Высота террейна в указанной точке: %f", Scalar(landscape_fetch->getHeight()));

```


### Пример асинхронных операций


```cpp
// создаём объект fetch и задаём необходимые параметры
LandscapeFetchPtr landscape_fetch = LandscapeFetch::create();
// отключаем все типы данных террейна, чтобы включить только необходимые
landscape_fetch->setUses(0);
// включаем проверку данных высот в запросах fetch/intersection, если необходимо
landscape_fetch->setUsesHeight(true);
// включаем проверку отверстий террейна в запросах fetch, если необходимо
landscape_fetch->setHolesEnabled(true);

// ...

// выполняем асинхронный запрос fetch для точки (2.05, 2.05)
landscape_fetch->setFetchPosition(Vec2(2.05f, 2.05f));
landscape_fetch->fetchAsync();

// ...

// проверяем, завершён ли наш асинхронный запрос fetch, и выводим значение высоты
if (landscape_fetch->isAsyncCompleted())
		Log::message("Высота террейна в указанной точке: %f", Scalar(landscape_fetch->getHeight()));

```


### Пример компонента


<details>
<summary>TerrainFetchSample.h | Закрыть</summary>

```cpp
#pragma once
#include <UnigineVector.h>
#include <UniginePlayers.h>
#include <UnigineComponentSystem.h>

class TerrainFetchSample : public Unigine::ComponentBase
{
public:
	COMPONENT(TerrainFetchSample, ComponentBase)
	COMPONENT_INIT(init)
	COMPONENT_UPDATE(update)
	COMPONENT_SHUTDOWN(shutdown)

	PROP_NAME("TerrainFetchSample")

private:
	void init();
	void update();
	void shutdown();

	// объявляем главного игрока и экземпляр класса LandscapeFetch, используемый для получения данных террейна
	Unigine::PlayerPtr main_player;
	Unigine::LandscapeFetchPtr fetch;
};

```

</details>


<details>
<summary>TerrainFetchSample.cpp | Закрыть</summary>

```cpp
#include "TerrainFetchSample.h"
#include <UnigineVisualizer.h>

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(TerrainFetchSample)

void TerrainFetchSample::init()
{
	// проверяем, является ли узел, которому назначен компонент, игроком
	main_player = checked_ptr_cast<Player>(node);
	if (!main_player)
		Log::error("TerrainFetchSample::init(): TerrainFetchSample должен быть назначен узлу игрока!\n");

	// включаем визуализатор
	Visualizer::setEnabled(1);
}

void TerrainFetchSample::update()
{
	if (!main_player)
		return;

	Vec3 p0, p1;
	// получаем главное окно приложения и позицию мыши
	const auto main_window = WindowManager::getMainWindow();
	const auto mouse_coord = Input::getMousePosition();

	// получаем вектор направления, на который указывает курсор мыши
	main_player->getDirectionFromMainWindow(p0, p1, mouse_coord.x, mouse_coord.y);

	if (!fetch)
	{
		// создаём fetch
		fetch = LandscapeFetch::create();

		// указываем, что мы будем использовать данные высот, альбедо и нормалей
		fetch->setUsesHeight(true);
		fetch->setUsesNormal(true);
		fetch->setUsesAlbedo(true);

		// указываем, что мы будем использовать слои масок от 0 до 3
		fetch->setUsesMask(0, true);
		fetch->setUsesMask(1, true);
		fetch->setUsesMask(2, true);
		fetch->setUsesMask(3, true);

		// асинхронно получаем точку пересечения между вектором направления и поверхностью террейна (точка под курсором мыши)
		fetch->intersectionAsync(p0, p0 + ((p1 - p0) * 1000.0));
	}
	else
	{
		// проверяем, завершена ли асинхронная задача
		if (fetch->isAsyncCompleted())
		{
			// если пересечение найдено
			if (fetch->isIntersection())
			{
				// получаем полученные данные и текущий активный landscape terrain
				Vec3 point = fetch->getPosition();
				auto terrain = Landscape::getActiveTerrain();

				// отрисовываем нормаль и вектор 'Up' в точке пересечения
				Visualizer::renderVector(point, point + Vec3_up * 10, vec4_blue);
				Visualizer::renderVector(point, point + Vec3(fetch->getNormal() * 10), vec4_red);
				Visualizer::renderSolidSphere(1, translate(point), vec4_black);

				// выводим значение высоты террейна в точке
				String string;
				string += String::format("Высота : %f\n", fetch->getHeight());

				// добавляем имена и индексы масок под курсором
				string += "Маски: \n";
				for (int i = 0; i < 4; i++)
				{
					string += String::format(" - \"%s\": %.2f\n", terrain->getDetailMask(i)->getName(), fetch->getMask(i));
				}
				// выводим текст в точке пересечения
				Visualizer::renderMessage3D(point, vec3(1, 1, 0), string.get(), vec4_green, 1);
			}
			else
			{
				// выводим сообщение, указывающее, что мы указываем куда-то за пределы террейна
				Visualizer::renderMessage3D(p1, vec3(1, 1, 0), "Out of terrain", vec4_red, 1);
			}
			// асинхронно получаем точку пересечения между вектором направления и поверхностью террейна (точка под курсором мыши)
			fetch->intersectionAsync(p0, p0 + ((p1 - p0) * 1000.0));
		}
	}
}

void TerrainFetchSample::shutdown()
{
	// выполняем очистку
	fetch = nullptr;
}


```

</details>


### См. также


- C++ sample
- C++ sample


## LandscapeFetch Class

### Методы класса

## Math:: Vec3 getPosition () const

Возвращает текущие координаты точки fetch/intersection.
### Возвращаемое значение

Текущие координаты точки fetch/intersection в виде трёхкомпонентного вектора.
## float getHeight () const

Возвращает текущее значение высоты в точке.
### Возвращаемое значение

Текущее значение высоты в точке.
## Math:: vec3 getNormal () const

Возвращает текущие координаты вектора нормали в точке.
> **Notice:** Чтобы получить корректную информацию о нормали через этот метод, [engage normal data](#setUsesNormal_int_void) для запроса fetch/intersection.


### Возвращаемое значение

Текущие координаты вектора нормали в точке.
## Math:: vec4 getAlbedo () const

Возвращает текущую информацию о цвете альбедо в точке.
> **Notice:** Чтобы получить корректную информацию о цвете альбедо через этот метод, [engage albedo data](#setUsesAlbedo_int_void) для запроса fetch/intersection.


### Возвращаемое значение

Текущий цвет альбедо в точке в виде 4-компонентного вектора (R, G, B, A).
## bool isIntersection () const

Возвращает текущее значение, указывающее, было ли обнаружено пересечение.
### Возвращаемое значение

**true**, если пересечение обнаружено; иначе **false**.
## void setUses ( int uses )

Задаёт новые флаги, включающие/отключающие определённые типы данных для запроса fetch/intersection.
### Аргументы

- *int* **uses** - Комбинация флагов включения данных.

## int getUses () const

Возвращает текущие флаги, включающие/отключающие определённые типы данных для запроса fetch/intersection.
### Возвращаемое значение

Текущая комбинация флагов включения данных.
## void setUsesHeight ( bool height )

Задаёт новое значение, указывающее, включены ли данные высот в запросе fetch/intersection. При включённом типе данных его можно получить через соответствующий метод *get()*. Отключение ненужных данных при выполнении запросов немного экономит производительность (например, можно включить только данные альбедо, если в заданной точке нужна только информация о цвете). Эта опция включена по умолчанию.
### Аргументы

- *bool* **height** - Установите **true**, чтобы включить данные высот в запросе fetch/intersection; **false** — чтобы отключить.

## bool isUsesHeight () const

Возвращает текущее значение, указывающее, включены ли данные высот в запросе fetch/intersection. При включённом типе данных его можно получить через соответствующий метод *get()*. Отключение ненужных данных при выполнении запросов немного экономит производительность (например, можно включить только данные альбедо, если в заданной точке нужна только информация о цвете). Эта опция включена по умолчанию.
### Возвращаемое значение

**true**, если данные высот включены в запросе fetch/intersection; иначе **false**.
## void setUsesNormal ( bool normal )

Задаёт новое значение, указывающее, включены ли данные нормалей в запросе fetch/intersection. При включённом типе данных его можно получить через соответствующий метод *get()*. Отключение ненужных данных при выполнении запросов немного экономит производительность (например, можно включить только данные альбедо, если в заданной точке нужна только информация о цвете).
> **Notice:** Включите эту опцию, чтобы получить information about [normal](#getNormal_vec3) for the point.


### Аргументы

- *bool* **normal** - Установите **true**, чтобы включить данные нормалей в запросе fetch/intersection; **false** — чтобы отключить.

## bool isUsesNormal () const

Возвращает текущее значение, указывающее, включены ли данные нормалей в запросе fetch/intersection. При включённом типе данных его можно получить через соответствующий метод *get()*. Отключение ненужных данных при выполнении запросов немного экономит производительность (например, можно включить только данные альбедо, если в заданной точке нужна только информация о цвете).
> **Notice:** Включите эту опцию, чтобы получить information about [normal](#getNormal_vec3) for the point.


### Возвращаемое значение

**true**, если данные нормалей включены в запросе fetch/intersection; иначе **false**.
## void setUsesAlbedo ( bool albedo )

Задаёт новое значение, указывающее, включены ли данные альбедо в запросе fetch/intersection. При включённом типе данных его можно получить через соответствующий метод *get()*. Отключение ненужных данных при выполнении запросов немного экономит производительность (например, можно включить только данные альбедо, если в заданной точке нужна только информация о цвете).
> **Notice:** Включите эту опцию, чтобы получить information about [albedo](#getAlbedo_vec4) for the point.


### Аргументы

- *bool* **albedo** - Установите **true**, чтобы включить данные альбедо в запросе fetch/intersection; **false** — чтобы отключить.

## bool isUsesAlbedo () const

Возвращает текущее значение, указывающее, включены ли данные альбедо в запросе fetch/intersection. При включённом типе данных его можно получить через соответствующий метод *get()*. Отключение ненужных данных при выполнении запросов немного экономит производительность (например, можно включить только данные альбедо, если в заданной точке нужна только информация о цвете).
> **Notice:** Включите эту опцию, чтобы получить information about [albedo](#getAlbedo_vec4) for the point.


### Возвращаемое значение

**true**, если данные альбедо включены в запросе fetch/intersection; иначе **false**.
## void setIntersectionPrecision ( float precision )

Задаёт новое значение точности, используемое для определения пересечений, запрашиваемых методами [*intersectionForce()*](#intersectionForce_int) и [*intersectionAsync()*](#intersectionAsync_int_void).
### Аргументы

- *float* **precision** - Точность определения пересечений как доля от максимальной точности, в диапазоне [0; 1]. Значение по умолчанию: 0.5f. Максимальная точность определяется движком на основе данных вашего Landscape Terrain.

## float getIntersectionPrecision () const

Возвращает текущее значение точности, используемое для определения пересечений, запрашиваемых методами [*intersectionForce()*](#intersectionForce_int) и [*intersectionAsync()*](#intersectionAsync_int_void).
### Возвращаемое значение

Текущая точность определения пересечений как доля от максимальной точности, в диапазоне [0; 1]. Значение по умолчанию: 0.5f. Максимальная точность определяется движком на основе данных вашего Landscape Terrain.
## void setIntersectionPositionBegin ( const Math:: Vec3 & begin )

Задаёт новые координаты начальной точки для определения пересечений.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md)&* **begin** - Трёхкомпонентный вектор, задающий координаты начальной точки по осям X, Y и Z.

## Math:: Vec3 getIntersectionPositionBegin () const

Возвращает текущие координаты начальной точки для определения пересечений.
### Возвращаемое значение

Текущий трёхкомпонентный вектор, задающий координаты начальной точки по осям X, Y и Z.
## void setIntersectionPositionEnd ( const Math:: Vec3 & end )

Задаёт новые координаты конечной точки для определения пересечений.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md)&* **end** - Трёхкомпонентный вектор, задающий координаты конечной точки по осям X, Y и Z.

## Math:: Vec3 getIntersectionPositionEnd () const

Возвращает текущие координаты конечной точки для определения пересечений.
### Возвращаемое значение

Текущий трёхкомпонентный вектор, задающий координаты конечной точки по осям X, Y и Z.
## void setFetchPosition ( const Math:: Vec2 & position )

Задаёт новую точку, для которой нужно получить данные террейна.
### Аргументы

- *const  Math::[Vec2](../../../../api/library/math/class.vec2_cpp.md)&* **position** - Двухкомпонентный вектор, задающий координаты точки по осям X и Y.

## Math:: Vec2 getFetchPosition () const

Возвращает текущую точку, для которой нужно получить данные террейна.
### Возвращаемое значение

Текущий двухкомпонентный вектор, задающий координаты точки по осям X и Y.
## bool isAsyncCompleted () const

Возвращает текущее значение, указывающее, завершена ли асинхронная операция. По завершении операции можно получить необходимые данные с помощью методов *get()*.
### Возвращаемое значение

**true**, если асинхронная операция завершена; иначе **false**.
## void setHolesEnabled ( bool enabled )

Задаёт новое значение, указывающее, включена ли проверка отверстий террейна в запросе fetch/intersection. Эта опция включена по умолчанию. При отключении отверстия террейна, созданные с помощью декалей, игнорируются.
### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить проверку отверстий террейна в запросе fetch/intersection; **false** — чтобы отключить.

## bool isHolesEnabled () const

Возвращает текущее значение, указывающее, включена ли проверка отверстий террейна в запросе fetch/intersection. Эта опция включена по умолчанию. При отключении отверстия террейна, созданные с помощью декалей, игнорируются.
### Возвращаемое значение

**true**, если проверка отверстий террейна в запросе fetch/intersection включена; иначе **false**.
## Event<> getEventEnd () const

Событие, вызываемое по завершении получения данных (fetch). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** For more details see the [Event Handling](../../../../code/fundamentals/events/index_cpp.md) article.

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события End
void end_event_handler()
{
	Log::message("\Обработка события End\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections end_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEnd().connect(end_event_connections, end_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEnd().connect(end_event_connections, []() {
		Log::message("\Обработка события End (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
end_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection end_event_connection;

// подписываемся на событие End с функцией-обработчиком, сохраняя соединение
publisher->getEventEnd().connect(end_event_connection, end_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
end_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
end_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие End через соединение
end_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события End, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события End\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEnd().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId end_handler_id;

// подписываемся на событие End с лямбда-обработчиком, сохраняя идентификатор соединения
end_handler_id = publisher->getEventEnd().connect(e_connections, []() {
		Log::message("\Обработка события End (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEnd().disconnect(end_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий End при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEnd().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEnd().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventStart () const

Событие, вызываемое в начале процесса получения данных (fetch). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** For more details see the [Event Handling](../../../../code/fundamentals/events/index_cpp.md) article.

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Start
void start_event_handler()
{
	Log::message("\Обработка события Start\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections start_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventStart().connect(start_event_connections, start_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventStart().connect(start_event_connections, []() {
		Log::message("\Обработка события Start (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
start_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection start_event_connection;

// подписываемся на событие Start с функцией-обработчиком, сохраняя соединение
publisher->getEventStart().connect(start_event_connection, start_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
start_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
start_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Start через соединение
start_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события Start, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события Start\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventStart().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId start_handler_id;

// подписываемся на событие Start с лямбда-обработчиком, сохраняя идентификатор соединения
start_handler_id = publisher->getEventStart().connect(e_connections, []() {
		Log::message("\Обработка события Start (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventStart().disconnect(start_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Start при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventStart().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventStart().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
---

## static LandscapeFetchPtr create ( )

Конструктор LandscapeFetch.
## float getMask ( int num ) const

Возвращает информацию, сохранённую для точки в детализирующей маске с указанным номером.
> **Notice:** Чтобы получить корректную информацию о детализирующей маске через этот метод, [engage mask data](#setUsesMask_int_int_void) для запроса fetch/intersection.


### Аргументы

- *int* **num** - Номер детализирующей маски в диапазоне **[0; 19]**.

### Возвращаемое значение

Значение для точки, сохранённое в детализирующей маске с указанным номером.
## void setUsesMask ( int num , bool value )

Задаёт значение, указывающее, включены ли данные указанной детализирующей маски в запросе fetch/intersection. При включённом типе данных его можно получить через соответствующий метод *get()*. Отключение ненужных данных при выполнении запросов немного экономит производительность (например, можно включить только данные альбедо, если в заданной точке нужна только информация о цвете).
> **Notice:** Включите эту опцию, чтобы получить data of the [detail mask](#getMask_int_float) for the point.


### Аргументы

- *int* **num** - Номер детализирующей маски в диапазоне **[0; 19]**.
- *bool* **value** - true, чтобы включить данные указанной детализирующей маски в запросе fetch/intersection, false — чтобы отключить.

## bool isUsesMask ( int num ) const

Возвращает значение, указывающее, включены ли данные указанной детализирующей маски в запросе fetch/intersection. При включённом типе данных его можно получить через соответствующий метод *get()*. Отключение ненужных данных при выполнении запросов немного экономит производительность (например, можно включить только данные альбедо, если в заданной точке нужна только информация о цвете).
> **Notice:** Включите эту опцию, чтобы получить данные [detail mask](#getMask_int_float) для точки.


### Аргументы

- *int* **num** - Номер детализирующей маски в диапазоне **[0; 19]**.

### Возвращаемое значение

true, если данные указанной детализирующей маски включены в запросе fetch/intersection; иначе false.
## bool fetchForce ( )

Получает данные террейна в принудительном режиме для точки, заданной методом [*setFetchPosition()*](#setFetchPosition_Vec2_void). Чтобы снизить нагрузку, когда мгновенный результат не требуется, можно использовать метод [*fetchAsync()*](#fetchAsync_int_void).
### Возвращаемое значение

true, если данные террейна успешно получены для указанной точки; иначе false.
## bool fetchForce ( const Math:: Vec2 & position )

Получает данные террейна в принудительном режиме для указанной точки. Чтобы снизить нагрузку, когда мгновенный результат не требуется, можно использовать метод [*fetchAsync()*](#fetchAsync_int_void).
### Аргументы

- *const  Math::[Vec2](../../../../api/library/math/class.vec2_cpp.md) &* **position** - Координаты точки.

### Возвращаемое значение

true, если данные террейна успешно получены для указанной точки; иначе false.
## bool intersectionForce ( )

Выполняет трассировку вдоль линии от точки **p0**, заданной методом [*setIntersectionPositionBegin()*](#setIntersectionPositionBegin_Vec3_void), до точки **p1**, заданной методом [*setIntersectionPositionEnd()*](#setIntersectionPositionEnd_Vec3_void), для поиска пересечения с террейном в принудительном режиме. Чтобы снизить нагрузку, когда мгновенный результат не требуется, можно использовать метод [*intersectionAsync()*](#intersectionAsync_int_void).
### Возвращаемое значение

true, если пересечение с террейном найдено; иначе false.
## bool intersectionForce ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 )

Выполняет трассировку вдоль линии от точки **p0** до точки **p1** для поиска пересечения с террейном в принудительном режиме. Чтобы снизить нагрузку, когда мгновенный результат не требуется, можно использовать метод [*intersectionAsync()*](#intersectionAsync_int_void).
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **p0** - Координаты точки **p0**.
- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **p1** - Координаты точки **p1**.

### Возвращаемое значение

true, если пересечение с террейном найдено; иначе false.
## void fetchAsync ( bool critical = false )

Получает данные террейна для точки, заданной методом [*setFetchPosition()*](#setFetchPosition_Vec2_void), в [asynchronous mode](#example_async) (соответствующая задача будет помещена в очередь, для ожидания результата используйте метод [*wait()*](#wait_void)). Для мгновенного результата используйте метод [*fetchForce()*](#fetchForce_int).
### Аргументы

- *bool* **critical** - true, чтобы задать высокий приоритет для задачи получения данных, false — чтобы задать обычный приоритет.

## void fetchAsync ( const Math:: Vec2 & position , bool critical = false )

Получает данные террейна для указанной точки в [asynchronous mode](#example_async) (соответствующая задача будет помещена в очередь, для ожидания результата используйте метод [*wait()*](#wait_void)). Для мгновенного результата используйте метод [*fetchForce()*](#fetchForce_int).
### Аргументы

- *const  Math::[Vec2](../../../../api/library/math/class.vec2_cpp.md) &* **position** - Координаты точки.
- *bool* **critical** - true, чтобы задать высокий приоритет для задачи получения данных, false — чтобы задать обычный приоритет.

## void intersectionAsync ( bool critical = false )

Выполняет трассировку вдоль линии от точки **p0**, заданной методом [*setIntersectionPositionBegin()*](#setIntersectionPositionBegin_Vec3_void), до точки **p1**, заданной методом [*setIntersectionPositionEnd()*](#setIntersectionPositionEnd_Vec3_void), для поиска пересечения с террейном в [asynchronous mode](#example_async) (соответствующая задача будет помещена в очередь, для ожидания результата используйте метод [*wait()*](#wait_void)). Для мгновенного результата используйте метод [*intersectionForce()*](#intersectionForce_int).
### Аргументы

- *bool* **critical** - true, чтобы задать высокий приоритет для задачи пересечения, false — чтобы задать обычный приоритет.

## void intersectionAsync ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , bool critical = false )

Выполняет трассировку вдоль линии от точки **p0** до точки **p1** для поиска пересечения с террейном в [asynchronous mode](#example_async) (соответствующая задача будет помещена в очередь, для ожидания результата используйте метод [*wait()*](#wait_void)). Для мгновенного результата используйте метод [*intersectionForce()*](#intersectionForce_int).
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **p0** - Координаты точки **p0**.
- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **p1** - Координаты точки **p1**.
- *bool* **critical** - true, чтобы задать высокий приоритет для задачи пересечения, false — чтобы задать обычный приоритет.

## void fetchForce ( const Vector < Ptr < LandscapeFetch >> & fetches )

Получает данные террейна (пакетно) в принудительном режиме для точки, заданной методом [*setFetchPosition()*](#setFetchPosition_Vec2_void). Чтобы снизить нагрузку, когда мгновенный результат не требуется, можно использовать метод [*fetchAsync()*](#fetchAsync_VECLandscapeFetch_int_void).
### Аргументы

- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../../api/library/common/class.ptr_cpp.md)<[LandscapeFetch](../../../../api/library/objects/landscape_terrain/class.landscapefetch_cpp.md)>> &* **fetches** - Список запросов fetch, которые нужно выполнить.

## void intersectionForce ( const Vector < Ptr < LandscapeFetch >> & fetches )

Выполняет трассировку (пакетно) вдоль линии от точки **p0**, заданной методом [*setIntersectionPositionBegin()*](#setIntersectionPositionBegin_Vec3_void), до точки **p1**, заданной методом [*setIntersectionPositionEnd()*](#setIntersectionPositionEnd_Vec3_void), для поиска пересечения с террейном в принудительном режиме. Чтобы снизить нагрузку, когда мгновенный результат не требуется, можно использовать метод [*intersectionAsync()*](#intersectionAsync_VECLandscapeFetch_int_void).
### Аргументы

- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../../api/library/common/class.ptr_cpp.md)<[LandscapeFetch](../../../../api/library/objects/landscape_terrain/class.landscapefetch_cpp.md)>> &* **fetches** - Список запросов fetch, которые нужно выполнить.

## void fetchAsync ( const Vector < Ptr < LandscapeFetch >> & fetches , bool critical = false )

Получает данные террейна (пакетно) для точки, заданной методом [*setFetchPosition()*](#setFetchPosition_Vec2_void), в [asynchronous mode](#example_async) (соответствующая задача будет помещена в очередь, для ожидания результата используйте метод [*wait()*](#wait_VECLandscapeFetch_void)). Для мгновенного результата используйте метод [*fetchForce()*](#fetchForce_VECLandscapeFetch_void).
### Аргументы

- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../../api/library/common/class.ptr_cpp.md)<[LandscapeFetch](../../../../api/library/objects/landscape_terrain/class.landscapefetch_cpp.md)>> &* **fetches** - Список запросов fetch, которые нужно выполнить.
- *bool* **critical** - true, чтобы задать высокий приоритет для задачи получения данных, false — чтобы задать обычный приоритет.

## void intersectionAsync ( const Vector < Ptr < LandscapeFetch >> & fetches , bool critical = false )

Выполняет трассировку (пакетно) вдоль линии от точки **p0**, заданной методом [*setIntersectionPositionBegin()*](#setIntersectionPositionBegin_Vec3_void), до точки **p1**, заданной методом [*setIntersectionPositionEnd()*](#setIntersectionPositionEnd_Vec3_void), для поиска пересечения с террейном в [asynchronous mode](#example_async) (соответствующая задача будет помещена в очередь, для ожидания результата используйте метод [*wait()*](#wait_VECLandscapeFetch_void)). Для мгновенного результата используйте метод [*intersectionForce()*](#intersectionForce_VECLandscapeFetch_void).
### Аргументы

- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../../api/library/common/class.ptr_cpp.md)<[LandscapeFetch](../../../../api/library/objects/landscape_terrain/class.landscapefetch_cpp.md)>> &* **fetches** - Список запросов fetch, которые нужно выполнить.
- *bool* **critical** - true, чтобы задать высокий приоритет для задачи пересечения, false — чтобы задать обычный приоритет.

## void wait ( )

Ожидает завершения операции получения данных (fetch). По завершении операции можно получить необходимые данные с помощью методов *get()*.
## void wait ( const Vector < Ptr < LandscapeFetch >> & fetches )

Ожидает завершения указанных операций получения данных (fetch). По завершении операций можно получить необходимые данные с помощью методов *get()*.
### Аргументы

- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../../api/library/common/class.ptr_cpp.md)<[LandscapeFetch](../../../../api/library/objects/landscape_terrain/class.landscapefetch_cpp.md)>> &* **fetches** - Список запросов fetch, которые нужно выполнить.
