// Простой контроллер движения машины, поддерживающий две схемы клавиш (WASD или стрелки).
// Использует lerp для плавного ускорения/торможения и поворота.

#include "CarControl.h"
#include <UnigineConsole.h>
#include <UnigineGame.h>
#include <UnigineInput.h>

REGISTER_COMPONENT(CarControl);

using namespace Unigine;
using namespace Math;

// Привязки клавиш ввода настраиваются в зависимости от параметра use_arrows.
void CarControl::init()
{
	init_input_keys();
}


// Назначения клавиш выбираются в зависимости от предпочтений игрока (WASD или стрелки).
void CarControl::init_input_keys()
{
	// Клавиши WASD для игрока 1 (по умолчанию)
	if (!use_arrows.get())
	{
		key_forward = Input::KEY_W;
		key_back = Input::KEY_S;
		key_left = Input::KEY_A;
		key_right = Input::KEY_D;

	} else
	{
		// Клавиши стрелок для игрока 2
		key_forward = Input::KEY_UP;
		key_back = Input::KEY_DOWN;
		key_left = Input::KEY_LEFT;
		key_right = Input::KEY_RIGHT;
	}
}

// Ввод опрашивается; скорость и поворот плавно интерполируются к целевым значениям.
void CarControl::update()
{
	// Пропускаем обработку ввода, когда открыта консоль, чтобы не мешать вводу текста
	if (Console::isActive())
		return;

	// Получаем текущие направления ввода (-1, 0 или 1)
	int fb = get_movement_command();
	int rl = get_rotate_command();

	// Lerp обеспечивает плавное ускорение/торможение для естественного движения
	float ifps = Game::getIFps();
	forward = lerp(forward, Scalar(max_speed.get() * fb), Scalar(ifps * acceleration_factor.get()));
	rotation = lerp(rotation, float(max_rotation.get() * rl), ifps);

	// Применяем поворот вокруг оси Z (рыскание) и перемещение вдоль локальной оси Y (вперёд)
	node->rotate(0, 0, rotation * ifps);
	node->translate(0, forward * ifps, 0);
}

// Состояние клавиш вперёд/назад преобразуется в значение направления.
int CarControl::get_movement_command() const
{
	int fb = 0;
	if (Input::isKeyPressed(key_forward))
	{
		fb = 1;
	} else if (Input::isKeyPressed(key_back))
	{
		fb = -1;
	}
	return fb;
}

// Состояние клавиш влево/вправо преобразуется в значение направления поворота.
int CarControl::get_rotate_command() const
{
	int rl = 0;
	if (Input::isKeyPressed(key_left))
	{
		rl = 1;
	} else if (Input::isKeyPressed(key_right))
	{
		rl = -1;
	}
	return rl;
}

// Очистка не требуется; состояние компонента сбрасывается автоматически.
void CarControl::shutdown()
{
}