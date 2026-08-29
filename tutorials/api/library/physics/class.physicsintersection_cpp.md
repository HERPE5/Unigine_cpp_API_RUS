# Unigine::PhysicsIntersection Class (CPP)

**Header:** #include <UniginePhysics.h>


Этот класс хранит результат пересечения физики (координаты пересечения, форму объекта, индекс поверхности). Если требуется информация о нормали в точке пересечения, используйте класс *[PhysicsIntersectionNormal](../../../api/library/physics/class.physicsintersectionnormal_cpp.md)*.


#### Пример использования


Следующий пример показывает, как можно получить информацию о пересечении с помощью класса *PhysicsIntersection*. В этом примере задаётся линия от точки камеры *(vec3 p0)* до точки указателя мыши *(vec3 p1)*. Последовательность выполнения следующая:


1. Определить и инициализировать две точки (p0 и p1) с помощью функции *[Player::getDirectionFromScreen()](../../../api/library/players/class.player_cpp.md#getDirectionFromScreen_Vec3_Vec3_int_int_int_int_int_int_void)*.
2. Создать экземпляр класса *PhysicsIntersection* для получения информации о пересечении.
3. Проверить, есть ли пересечение с объектом с формой или коллизионным объектом. Функция *[getIntersection()](../../../api/library/physics/class.physics_cpp.md#getIntersection_Vec3_Vec3_int_Variable)* возвращает пересечённый объект, когда объект пересекается с трассируемой линией.
4. Когда объект пересекается с трассируемой линией, все поверхности пересечённого объекта изменяют параметры своего материала. Если у объекта есть форма, информация о ней будет выведена в консоль. Экземпляр класса *PhysicsIntersection* получает координаты точки пересечения и объект класса *Shape*. Все эти поля можно получить с помощью функций *[getShape()](../../../api/library/physics/class.physicsintersection_cpp.md#getShape_Shape), [getPoint()](../../../api/library/physics/class.physicsintersection_cpp.md#getPoint_Vec3)*.


```cpp
#include "AppWorldLogic.h"
#include <UnigineObjects.h>
#include <UnigineEditor.h>
#include <UnigineGame.h>
#include <UniginePhysics.h>

using namespace Unigine;
using namespace Math;

int AppWorldLogic::init()
{
	// создаём экземпляр Mesh с поверхностью-боксом
	MeshPtr mesh = Mesh::create();
	mesh->addBoxSurface("box", vec3(0.2f));

	// создаём новый динамический меш из экземпляра Mesh
	ObjectMeshDynamicPtr dynamic_mesh = ObjectMeshDynamic::create(mesh);

	dynamic_mesh->setWorldTransform(translate(Vec3(0.0f, 0.0f, 2.0f)));

	// назначаем тело и форму динамическому мешу
	BodyRigidPtr body = BodyRigid::create(dynamic_mesh);
	ShapeBoxPtr shape = ShapeBox::create(body, vec3(0.2f));

	return 1;
}

////////////////////////////////////////////////////////////////////////////////
// начало главного цикла
////////////////////////////////////////////////////////////////////////////////

int AppWorldLogic::update()
{
	// инициализируем точки направления мыши
	Vec3 p0, p1;

	// получаем текущего игрока (камеру)
	PlayerPtr player = Game::getPlayer();
	if (player.get() == NULL)
		return 0;
	// получаем ширину и высоту главного окна приложения
	Math::ivec2 winsize = WindowManager::getMainWindow()->getClientSize();
	int width = winsize.x;
	int height = winsize.y;
	// получаем текущие координаты X и Y указателя мыши
	int mouse_x = Gui::getCurrent()->getMouseX();
	int mouse_y = Gui::getCurrent()->getMouseY();
	// получаем направление мыши от позиции игрока (p0) до курсора мыши (p1)
	player->getDirectionFromScreen(p0, p1, mouse_x, mouse_y, 0, 0, width, height);

	// создаём экземпляр объекта PhysicsIntersection для сохранения информации о пересечении
	PhysicsIntersectionPtr intersection = PhysicsIntersection::create();
	// получаем пересечение
	ObjectPtr object = Physics::getIntersection(p0, p1, 1, intersection);

	// если пересечение произошло, изменяем параметр материала объекта
	if (object)
	{
		for (int i = 0; i < object->getNumSurfaces(); i++)
		{
			object->setMaterialParameterFloat4("albedo_color", vec4(1.0f, 1.0f, 0.0f, 1.0f), i);
		}

		// если у пересечённого объекта есть форма, выводим информацию о пересечении
		ShapePtr shape = intersection->getShape();
		if (shape)
		{
			Log::message("physics intersection info: point: (%f %f %f) shape: %s\n", intersection->getPoint().x, intersection->getPoint().y, intersection->getPoint().z, shape->getTypeName());
		}
	}

	return 1;
}


```


## PhysicsIntersection Class

### Перечисления

## TYPE

| Имя | Описание |
|---|---|
| **PHYSICS_INTERSECTION** = 0 | Объект PhysicsIntersection, хранящий базовую информацию о точке пересечения (координаты пересечения, форму объекта, индекс поверхности). |
| **PHYSICS_INTERSECTION_NORMAL** = 1 | Объект [PhysicsIntersectionNormal](../../../api/library/physics/class.physicsintersectionnormal_cpp.md), хранящий ту же информацию, что и объект PhysicsIntersection, плюс дополнительную информацию о нормали в точке пересечения. |
| **NUM_PHYSICS_INTERSECTIONS** = 2 |  |

### Методы класса

---

## static PhysicsIntersectionPtr create ( )

Конструктор PhysicsIntersection.
## void setPoint ( const Math:: Vec3 & point )

Задаёт новые координаты точки пересечения.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Координаты точки пересечения.

## Math:: Vec3 getPoint ( )

Возвращает координаты точки пересечения.
### Возвращаемое значение

Координаты точки пересечения.
## void setShape ( const Ptr < Shape > & shape )

Задаёт новую форму пересечения.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Shape](../../../api/library/physics/class.shape_cpp.md)> &* **shape** - Форма пересечения.

## Ptr < Shape > getShape ( )

Возвращает форму пересечения.
### Возвращаемое значение

Форма пересечения.
## void setSurface ( int surface )

Задаёт новый номер поверхности пересечения.
### Аргументы

- *int* **surface** - Номер поверхности пересечения.

## int getSurface ( )

Возвращает номер пересечённой поверхности.
### Возвращаемое значение

Номер пересечённой поверхности.
## PhysicsIntersection::TYPE getType ( )

Возвращает тип пересечения физики. Тип определяет информацию, хранимую объектом (включены ли данные о нормали в точке пересечения).
### Возвращаемое значение

Тип пересечения физики, одно из значений [TYPE](#PHYSICS_INTERSECTION).
## const char * getTypeName ( )

Возвращает имя типа пересечения физики. Тип определяет информацию, хранимую объектом (включены ли данные о нормали в точке пересечения).
### Возвращаемое значение

Имя типа пересечения физики. Одно из следующих значений:
- PhysicsIntersection
- PhysicsIntersectionNormal
