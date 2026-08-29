// Вариант пружины с использованием интуитивных параметров (duration, damping_ratio) вместо
// сырых физических значений. Преобразуется в жёсткость/демпфирование с помощью формул времени
// затухания демпфированного гармонического осциллятора для предсказуемого таймлайна анимации.

#include "SpringEasy.h"

#include <UnigineGame.h>

REGISTER_COMPONENT(SpringEasy);

using namespace Unigine;
using namespace Math;

// Жёсткость и демпфирование вычисляются из интуитивных параметров с использованием формул гармонического осциллятора.
void SpringEasy::refresh_spring_settings()
{
	// Преобразуем интуитивные параметры (duration, damping_ratio) в физические параметры.
	// Выведено из формулы времени затухания демпфированного гармонического осциллятора.
	float frac_log = Math::log(fraction_of_amplitude);
	stiffness = Math::pow(frac_log, 2) / (Math::pow(duration, 2) * Math::pow(damping_ratio, 2));
	// Коэффициент критического демпфирования: 2 * sqrt(k) * zeta
	damping = 2.0f * sqrtf(stiffness) * damping_ratio;
}