# Unigine::PhysicsIntersectionNormal Class (CPP)

**Header:** #include <UniginePhysics.h>

**Inherits from:** PhysicsIntersection


Этот класс хранит всю информацию о точке пересечения физики (координаты пересечения, форму объекта, индекс поверхности) плюс координаты нормали в этой точке.


#### Пример использования


Следующий пример показывает, как можно получить нормаль точки пересечения с помощью класса *PhysicsIntersectionNormal*. В этом примере линия — это невидимая трассируемая линия от точки камеры (vec3 p0) до точки указателя мыши (vec3 p1). Последовательность выполнения следующая:


- Определить и инициализировать две точки (p0 и p1) с помощью функции *[Player::getDirectionFromScreen()](../../../api/library/players/class.player_cpp.md#getDirectionFromScreen_Vec3_Vec3_int_int_int_int_int_int_void)*.
- Создать экземпляр класса *PhysicsIntersectionNormal* для получения нормали точки пересечения.
- Проверить, есть ли пересечение с объектом.
- Когда объект пересекается с трассируемой линией, все поверхности пересечённого объекта изменяют параметры своего материала. Экземпляр класса *PhysicsIntersectionNormal* получает нормаль точки пересечения. Её можно получить с помощью функции *[getNormal()](#getNormal_vec3)*.


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

	// создаём экземпляр объекта PhysicsIntersectionNormal для сохранения информации о пересечении
	PhysicsIntersectionNormalPtr intersection = PhysicsIntersectionNormal::create();
	// получаем пересечение
	ObjectPtr object = Physics::getIntersection(p0, p1, 1, intersection);

	// если пересечение произошло, изменяем параметр материала объекта
	if (object)
	{
		for (int i = 0; i < object->getNumSurfaces(); i++)
		{
			object->setMaterialParameterFloat4("albedo_color", vec4(1.0f, 1.0f, 0.0f, 1.0f), i);
		}

		// если у пересечённого объекта есть форма, выводим информацию о нормали пересечения
		ShapePtr shape = intersection->getShape();
		if (shape)
		{
			Log::message("Normal coordinates: (%f %f %f)\n",

			intersection->getNormal().x,
			intersection->getNormal().y,
			intersection->getNormal().z);
		}
	}

	return 1;
}


```


## PhysicsIntersectionNormal Class

### Методы класса

---

## static PhysicsIntersectionNormalPtr create ( )

Конструктор PhysicsIntersectionNormal.
## void setNormal ( const Math:: vec3 & normal )

Задаёт новую нормаль точки пересечения.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **normal** - Нормаль точки пересечения.

## Math:: vec3 getNormal ( )

Возвращает нормаль точки пересечения.
### Возвращаемое значение

Нормаль точки пересечения.
