# Unigine::WorldIntersection Class (CPP)

**Заголовочный файл:** #include <UnigineWorld.h>


Этот класс хранит результат пересечения мира (координаты пересечения, индекс пересечённого треугольника и индекс пересечённой поверхности).


#### Пример использования


Следующий пример показывает, как получить информацию о пересечении с помощью класса WorldIntersection. В этом примере линия — это невидимая трассируемая линия от точки камеры (vec3 p0) до точки указателя мыши (vec3 p1). Последовательность выполнения следующая:

- Определить и инициализировать две точки (p0 и p1) с помощью функции *[Player::getDirectionFromScreen()](../../../api/library/players/class.player_cpp.md#getDirectionFromScreen_Vec3_Vec3_int_int_int_int_int_int_void)*.
- Создать экземпляр класса WorldIntersection для получения информации о пересечении.
- Проверить, есть ли пересечение с объектом. Функция [*World::getIntersection()*](../../../api/library/engine/class.world_cpp.md#getIntersection_vec3_vec3_int_Variable_Object) возвращает пересечённый объект, если объект пересекается с трассируемой линией.
- В этом примере, когда объект пересекается с трассируемой линией, все поверхности пересечённого объекта меняют параметры своего материала. Экземпляр класса WorldIntersection получает координаты точки пересечения и индекс пересечённого треугольника. Получить все эти поля можно с помощью функций [*getIndex()*](#getIndex_int) и [*getPoint()*](#getPoint_Vec3)


```cpp
/* ... */
// инициализируем точки направления мыши
Vec3 p0, p1;

// получаем текущего игрока (камеру)
PlayerPtr player = Game::getPlayer();
if (player.get() == NULL)
	return 0;

// получаем размер (ширину и высоту) текущего окна приложения
ivec2 main_size = ivec2_one;

EngineWindowPtr main_window = WindowManager::getMainWindow();
if (!main_window)
	Engine::get()->quit();

main_size = main_window->getSize();

// получаем текущие координаты X и Y указателя мыши
int mouse_x = Input::getMousePosition().x - main_window->getPosition().x;
int mouse_y = Input::getMousePosition().y - main_window->getPosition().y;

// получаем направление мыши от позиции игрока (p0) до указателя курсора мыши (p1)
player->getDirectionFromScreen(p0, p1, mouse_x, mouse_y, 0, 0, main_size.x, main_size.y);

// создаём экземпляр класса WorldIntersection для получения результата
WorldIntersectionPtr intersection = WorldIntersection::create();

// создаём экземпляр для пересечённого объекта и проверяем пересечение
ObjectPtr object = World::getIntersection(p0, p1, 1, intersection);

// если пересечение произошло, меняем параметр материала объекта
if (object)
{
	for (int i = 0; i < object->getNumSurfaces(); i++)
	{
		object->setMaterialParameterFloat4("albedo_color", vec4(1.0f, 0.0f, 0.0f, 1.0f), i);

		// выводим детали пересечения в консоль
		Log::message("point: (%f %f %f) index: %i \n", intersection->getPoint().x, intersection->getPoint().y, intersection->getPoint().z, intersection->getIndex());
	}
}
/* ... */


```


## WorldIntersection Class

### Перечисления

## TYPE

| Name | Описание |
|---|---|
| **WORLD_INTERSECTION** = 0 | Точка пересечения (координаты), индекс пересечённого треугольника объекта и индекс пересечённой поверхности. |
| **WORLD_INTERSECTION_NORMAL** = 1 | Нормаль точки пересечения. |
| **WORLD_INTERSECTION_TEX_COORD** = 2 | Текстурные координаты точки пересечения. |
| **NUM_WORLD_INTERSECTIONS** = 3 | Общее количество мировых пересечений. |

### Методы класса

---

## static WorldIntersectionPtr create ( )

Конструктор WorldIntersection.
## void setIndex ( int index )

Задаёт новый номер треугольника пересечения.
### Аргументы

- *int* **index** — номер треугольника пересечения.

## int getIndex ( ) const

Возвращает номер пересечённого треугольника.
### Возвращаемое значение

Номер пересечённого треугольника.
## void setInstance ( int instance )

Задаёт новый номер пересечённого экземпляра.
> **Примечание:** Номер пересечённого экземпляра можно получить для следующих классов:
> - *[ObjectMeshSkinned](../../../api/library/objects/class.objectmeshskinned_cpp.md)*
> - *[ObjectMeshCluster](../../../api/library/objects/class.objectmeshcluster_cpp.md)*
> - *[ObjectMeshSplineCluster](../../../api/library/objects/class.objectmeshsplinecluster_cpp.md)*


### Аргументы

- *int* **instance** — номер пересечённого экземпляра.

## int getInstance ( ) const

Возвращает номер пересечённого экземпляра.
> **Примечание:** Номер пересечённого экземпляра можно получить для следующих классов:
> - *[ObjectMeshSkinned](../../../api/library/objects/class.objectmeshskinned_cpp.md)*
> - *[ObjectMeshCluster](../../../api/library/objects/class.objectmeshcluster_cpp.md)*
> - *[ObjectMeshSplineCluster](../../../api/library/objects/class.objectmeshsplinecluster_cpp.md)*


### Возвращаемое значение

Номер пересечённого экземпляра.
## void setPoint ( const Math:: Vec3 & point )

Задаёт новые координаты точки пересечения.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** — координаты точки пересечения.

## Math:: Vec3 getPoint ( ) const

Возвращает координаты точки пересечения.
### Возвращаемое значение

Координаты точки пересечения.
## void setSurface ( int surface )

Задаёт новый номер поверхности пересечения.
### Аргументы

- *int* **surface** — номер поверхности пересечения.

## int getSurface ( ) const

Возвращает номер пересечённой поверхности.
### Возвращаемое значение

Номер пересечённой поверхности.
## WorldIntersection::TYPE getType ( ) const

Возвращает идентификатор типа мирового пересечения.
### Возвращаемое значение

[TYPE](#WORLD_INTERSECTION).
## const char * getTypeName ( ) const

Возвращает имя типа мирового пересечения.
### Возвращаемое значение

Имя типа мирового пересечения.
