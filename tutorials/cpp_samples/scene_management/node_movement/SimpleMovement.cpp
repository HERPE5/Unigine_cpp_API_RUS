// Три эквивалентных подхода к перемещению узла: с помощью translate/rotate,
// setPosition/setRotation и setTransform. Все дают одинаковый результат,
// но демонстрируют разные паттерны API для управления трансформациями узлов.

#include "SimpleMovement.h"

#include "UnigineConsole.h"
#include "UnigineGame.h"

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(SimpleMovement);
REGISTER_COMPONENT(SimpleMovement2);
REGISTER_COMPONENT(SimpleMovement3);

/*=============== Simple Movement, вариант 1 ===============*/

// Ввод WASD обрабатывается; узел перемещается с помощью методов translate/rotate.
void SimpleMovement::update()
{
	// Пропускаем ввод, когда активна консоль
	if (Console::isActive())
		return;

	// Вычитание даёт -1, 0 или +1: только W = 1, только S = -1, оба или ни одного = 0
	int move_sign = int(Input::isKeyPressed(Input::KEY_W)) - int(Input::isKeyPressed(Input::KEY_S));
	if (move_sign)
	{
		// Ось Y — направление вперёд в локальном пространстве; знак определяет направление
		move(Vec3(0.0f, float(move_sign), 0.0f));
	}

	// Тот же паттерн для поворота: A = +1 (влево), D = -1 (вправо), оба/ни одного = 0
	int rotate_sign = int(Input::isKeyPressed(Input::KEY_A)) - int(Input::isKeyPressed(Input::KEY_D));
	if (rotate_sign)
	{
		// Поворот вокруг оси Z (рыскание); знак определяет направление поворота
		turn(vec3(0.0f, 0.0f, float(rotate_sign)));
	}
}

// translate() перемещает узел в его локальном пространстве координат.
void SimpleMovement::move(const Unigine::Math::Vec3& dir)
{
	Vec3 delta_movement = dir * velocity * Game::getIFps();
	// Простейший подход: translate сам выполняет преобразование из локального пространства в мировое
	node->translate(delta_movement);
}

// rotate() применяет инкрементальный поворот к текущей ориентации.
void SimpleMovement::turn(const Unigine::Math::vec3& dir)
{
	vec3 delta_rotation = dir * angular_velocity * Game::getIFps();
	node->rotate(delta_rotation);
}


/*=============== Simple Movement, вариант 2 ===============*/

// Ввод WASD обрабатывается; узел перемещается с помощью setPosition/setRotation.
void SimpleMovement2::update()
{
	if (Console::isActive())
		return;

	// Вычитание даёт -1, 0 или +1: только W = 1, только S = -1, оба или ни одного = 0
	int move_sign = int(Input::isKeyPressed(Input::KEY_W)) - int(Input::isKeyPressed(Input::KEY_S));
	if (move_sign)
	{
		move(Vec3(0.0f, float(move_sign), 0.0f));
	}

	// Тот же паттерн для поворота: A = +1 (влево), D = -1 (вправо), оба/ни одного = 0
	int rotate_sign = int(Input::isKeyPressed(Input::KEY_A)) - int(Input::isKeyPressed(Input::KEY_D));
	if (rotate_sign)
	{
		turn(vec3(0.0f, 0.0f, float(rotate_sign)));
	}
}

// setPosition() требует ручного преобразования направления из локального пространства в мировое.
void SimpleMovement2::move(const Unigine::Math::Vec3& dir)
{
	// Направление нужно повернуть на ориентацию узла, чтобы двигаться в локальном пространстве
	Vec3 deltaMovement = node->getRotation() * (dir * velocity * Game::getIFps());
	Vec3 oldPosition = node->getPosition();
	node->setPosition(oldPosition + deltaMovement);
}

// setRotation() перемножает кватернионы для объединения поворотов.
void SimpleMovement2::turn(const Unigine::Math::vec3& dir)
{
	float deltaRotation = angular_velocity * Game::getIFps();
	quat oldRotation = node->getRotation();
	// Перемножение кватернионов применяет дельту поворота к текущей ориентации
	node->setRotation(oldRotation * quat(dir, deltaRotation));
}


/*=============== Simple Movement, вариант 3 ===============*/

// Ввод WASD обрабатывается; узел перемещается с помощью setTransform с матрицами.
void SimpleMovement3::update()
{
	if (Console::isActive())
		return;

	// Вычитание даёт -1, 0 или +1: только W = 1, только S = -1, оба или ни одного = 0
	int move_sign = int(Input::isKeyPressed(Input::KEY_W)) - int(Input::isKeyPressed(Input::KEY_S));
	if (move_sign)
	{
		move(Vec3(0.0f, float(move_sign), 0.0f));
	}

	// Тот же паттерн для поворота: A = +1 (влево), D = -1 (вправо), оба/ни одного = 0
	int rotate_sign = int(Input::isKeyPressed(Input::KEY_A)) - int(Input::isKeyPressed(Input::KEY_D));
	if (rotate_sign)
	{
		turn(vec3(0.0f, 0.0f, float(rotate_sign)));
	}
}

// setTransform() применяет матрицу переноса к текущей трансформации.
void SimpleMovement3::move(const Unigine::Math::Vec3& dir)
{
	Mat4 transform = node->getTransform();
	Vec3 delta_movement = dir * velocity * Game::getIFps();
	// Создаём матрицу переноса из дельты позиции
	Mat4 delta_transform = translate(delta_movement);
	// Перемножение матриц применяет перемещение в локальном пространстве
	node->setTransform(transform * delta_transform);
}

// setTransform() применяет матрицу поворота к текущей трансформации.
void SimpleMovement3::turn(const Unigine::Math::vec3& dir)
{
	Mat4 transform = node->getTransform();
	float deltaRotation = angular_velocity * Game::getIFps();
	// Создаём матрицу поворота из оси и угла
	Mat4 delta_transform = Unigine::Math::rotate(Vec3(dir), deltaRotation);
	node->setTransform(transform * delta_transform);
}
