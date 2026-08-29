#pragma once
#include "SunController.h"

using namespace Unigine;
using namespace Math;

// Управляет вращением солнца для симуляции цикла день/ночь. Время (в секундах) отображается на
// угол поворота: 0 сек = -180°, max_time = +180°. Вызывает time_changed_event для синхронизации UI.
REGISTER_COMPONENT(SunController);

// Начальный поворот солнца сохраняется для вычисления смещений на основе времени.
void SunController::init()
{
	sun_init_tilt = node->getWorldRotation();
}

// Время продвигается, позиция солнца обновляется в непрерывном режиме.
void SunController::update()
{
	if (is_continuous)
	{
		current_time += Game::getIFps() * timescale;
		if (current_time > max_time_sec)
		{
			// Оборачиваем без потери лишнего дельта-времени
			current_time -= max_time_sec;
		}
		refreshSunPosition();
		// Уведомляем слушателей об изменении времени
		time_changed_event.run(current_time);
	}
}

// Режим непрерывного вращения включается или отключается.
void SunController::setContinuousEnabled(bool value)
{
	is_continuous = value;
}

// Устанавливается множитель времени для скорости непрерывного вращения.
void SunController::setTimescale(float timescale)
{
	this->timescale = timescale;
}

// Поворот солнца вычисляется из текущего времени и применяется к узлу.
void SunController::refreshSunPosition()
{
	// Преобразование времени в поворот
	float time = fmodf(current_time, max_time_sec);
	float k = Math::inverseLerp(0.0f, max_time_sec, time);
	// Смещение +180 градусов, чтобы 12:00 соответствовало полудню
	float angle = Math::lerp(-180.0f, 180.0f, k);
	node->setWorldRotation(sun_init_tilt * quat(angle, 0.0f, 0.0f), true);
}

// Время устанавливается вручную, позиция солнца обновляется немедленно.
void SunController::setTime(int t)
{
	current_time = t;
	refreshSunPosition();

	time_changed_event.run(current_time);
}
