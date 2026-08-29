# Unigine::WorldIntersectionNormal Class (CPP)

**Header:** #include <UnigineWorld.h>

**Inherits from:** WorldIntersection


Этот класс хранит нормаль точки пересечения. Используйте этот класс, когда требуется дополнительная информация о нормали в точке пересечения (он также хранит координаты пересечения, индекс пересечённого треугольника и индекс пересечённой поверхности).


#### Пример использования


Следующий пример показывает, как получить информацию о пересечении с помощью класса WorldIntersection. В этом примере линия — это невидимая трассируемая линия от точки камеры (vec3 p0) до точки указателя мыши (vec3 p1). Последовательность выполнения следующая:

- Определить и инициализировать две точки (p0 и p1) с помощью функции *[Player::getDirectionFromScreen()](../../../api/library/players/class.player_cpp.md#getDirectionFromScreen_Vec3_Vec3_int_int_int_int_int_int_void)*.
- Создать экземпляр класса WorldIntersectionNormal для получения информации о пересечении.
- Проверить, есть ли пересечение с объектом. Функция [*World::getIntersection()*](../../../api/library/engine/class.world_cpp.md#getIntersection_vec3_vec3_int_Variable_Object) возвращает пересечённый объект, если объект пересекается с трассируемой линией.
- В этом примере, когда объект пересекается с трассируемой линией, все поверхности пересечённого объекта меняют параметры своего материала. Экземпляр класса WorldIntersectionNormal получает нормаль точки пересечения. Получить нормаль можно с помощью функции [*getNormal()*](#getNormal_vec3).


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

// создаём экземпляр класса WorldIntersectionNormal для получения результата
WorldIntersectionNormalPtr intersection = WorldIntersectionNormal::create();

// создаём экземпляр для пересечённого объекта и проверяем пересечение
ObjectPtr object = World::getIntersection(p0, p1, 1, intersection);

// если пересечение произошло, меняем параметр материала объекта
if (object)
{
	for (int i = 0; i < object->getNumSurfaces(); i++)
	{
		object->setMaterialParameterFloat4("albedo_color", vec4(1.0f, 0.0f, 0.0f, 1.0f), i);

		// выводим детали пересечения в консоль
		Log::message("Normal: type %s coordinates (%f %f %f)\n", typeid(intersection->getNormal()).name(),
			intersection->getNormal().x,
			intersection->getNormal().y,
			intersection->getNormal().z);
	}
}
/* ... */


```


## WorldIntersectionNormal Class

### Методы класса

---

## static WorldIntersectionNormalPtr create ( )

Конструктор WorldIntersectionNormal.
## void setNormal ( const Math:: vec3 & normal )

Задаёт новую нормаль точки пересечения.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **normal** - Нормаль точки пересечения.

## Math:: vec3 getNormal ( ) const

Возвращает нормаль точки пересечения.
### Возвращаемое значение

Нормаль точки пересечения.
