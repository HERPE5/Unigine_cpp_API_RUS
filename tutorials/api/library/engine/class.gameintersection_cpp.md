# Класс Unigine::GameIntersection (CPP)

**Заголовочный файл:** #include <UnigineGame.h>


Хранит результат функции [*Game::getIntersection()*](../../../api/library/engine/class.game_cpp.md#getIntersection_Vec3_Vec3_float_int_GameIntersection_Obstacle) — точку, в которой произошло пересечение с [obstacle](../../../api/library/pathfinding/class.obstacle_cpp.md).


![](cylinder01.png)


### Пример использования


Следующий пример показывает, как можно получить точку пересечения (vec3) цилиндра между двумя точками с препятствием. В этом примере мы задаём цилиндр от точки камеры (vec3 p0) до точки указателя мыши (vec3 p1) с заданным радиусом. Последовательность выполнения следующая:


1. Определите и инициализируйте две точки (p0 и p1) с помощью *[Player::getDirectionFromScreen()](../../../api/library/players/class.player_cpp.md#getDirectionFromScreen_Vec3_Vec3_int_int_int_int_int_int_void)*.
2. Создайте экземпляр класса GameIntersection, чтобы получить координаты точки пересечения.
3. Проверьте, есть ли пересечение с препятствием. Функция *Game::getIntersection()* возвращает пересекаемое препятствие, когда препятствие оказывается в области цилиндра.
4. После этого экземпляр GameIntersection получает точку ближайшего пересечения, и вы можете получить её с помощью функции *getPoint()*.


```cpp
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
player->getDirectionFromScreen(p0, p1, mouse_x, mouse_y, 0, 0, main_size.x, main_size.y);

// создаём экземпляр класса GameIntersection
GameIntersectionPtr intersection = GameIntersection::create();

// пытаемся получить пересечение с препятствием
// цилиндр имеет радиус 1.5f, маска пересечения равна 1
ObstaclePtr obstacle = Game::getIntersection(p0, p1, 1.5f, 1, intersection);

// проверяем, произошло ли пересечение направления мыши с каким-либо препятствием;
if (obstacle)
{
	// выводим координаты пересечения в консоль
	Log::message("The intersection with the obstacle was here: (%f %f %f)\n", intersection->getPoint().x, intersection->getPoint().y, intersection->getPoint().z);
}
/* ... */


```


## Класс GameIntersection

### Методы класса

---

## static GameIntersectionPtr create ( )

Конструктор GameIntersection.
## void setPoint ( const Math:: Vec3 & point )

Устанавливает новые координаты точки пересечения.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Координаты точки пересечения.

## Math:: Vec3 getPoint ( )

Возвращает координаты точки пересечения.
### Возвращаемое значение

Координаты точки пересечения.
