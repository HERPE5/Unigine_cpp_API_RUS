# Unigine::WorldIntersectionTexCoord Class (CPP)

**Header:** #include <UnigineWorld.h>

**Inherits from:** WorldIntersectionNormal


Этот класс хранит текстурные координаты точки пересечения. Используйте этот класс, когда требуется дополнительная информация о текстурных координатах в точке пересечения (он также хранит координаты пересечения, индекс пересечённого треугольника, индекс пересечённой поверхности и координаты нормали в точке пересечения).


#### Пример использования


Следующий пример показывает, как получить текстурные координаты в точке пересечения (vec4) с помощью класса WorldIntersectionTexCoord. В этом примере линия — это невидимая трассируемая линия от точки камеры (vec3 p0) до точки указателя мыши (vec3 p1). Последовательность выполнения следующая:

- Определить и инициализировать две точки (p0 и p1) с помощью функции *[Player::getDirectionFromScreen()](../../../api/library/players/class.player_cpp.md#getDirectionFromScreen_Vec3_Vec3_int_int_int_int_int_int_void)*.
- Создать экземпляр класса WorldIntersectionTexCoord для получения информации о пересечении.
- Проверить, есть ли пересечение с объектом. Функция [*World::getIntersection()*](../../../api/library/engine/class.world_cpp.md#getIntersection_vec3_vec3_int_Variable_Object) возвращает пересечённый объект, если объект пересекается с трассируемой линией.
- В этом примере, когда объект пересекается с трассируемой линией, все поверхности пересечённого объекта меняют параметры своего материала. Экземпляр класса WorldIntersectionTexCoord получает текстурные координаты точки пересечения. Получить текстурные координаты можно с помощью функции [*getTexCoord()*](#getTexCoord_vec4).


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

// создаём экземпляр класса WorldIntersectionTexCoord для получения результата
WorldIntersectionTexCoordPtr intersection = WorldIntersectionTexCoord::create();

// создаём экземпляр для пересечённого объекта и проверяем пересечение
ObjectPtr object = World::getIntersection(p0, p1, 1, intersection);

// если пересечение произошло, меняем параметр материала объекта
if (object)
{
	for (int i = 0; i < object->getNumSurfaces(); i++)
	{
		object->setMaterialParameterFloat4("albedo_color", vec4(1.0f, 0.0f, 0.0f, 1.0f), i);

		// выводим детали пересечения в консоль
		Log::message("Texture coordinates: (%f %f %f %f)\n",
			intersection->getTexCoord().x,
			intersection->getTexCoord().y,
			intersection->getTexCoord().z,
			intersection->getTexCoord().w);
	}
}
/* ... */


```


## WorldIntersectionTexCoord Class

### Методы класса

---

## static WorldIntersectionTexCoordPtr create ( )

Конструктор WorldIntersectionTexCoord.
## void setTexCoord ( const Math:: vec4 & coord )

Задаёт новые текстурные координаты точки пересечения.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **coord** - Текстурные координаты точки пересечения.

## Math:: vec4 getTexCoord ( ) const

Возвращает текстурные координаты точки пересечения.
### Возвращаемое значение

Текстурные координаты точки пересечения (где vec4.xy - для первого UV-канала, vec4.zw - для второго UV-канала).
