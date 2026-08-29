// Вариант пружины с использованием прямых физических параметров (жёсткость, демпфирование) из свойств
// компонента. Предоставляет RefreshSpring() для сброса значений, полезно, когда игровая логика
// динамически изменяет параметры пружины (например, при нарастании сложности).

#include "SpringRegular.h"

#include <UnigineGame.h>

REGISTER_COMPONENT(SpringRegular);

using namespace Unigine;
using namespace Math;

// Настройки пружины сбрасываются к значениям по умолчанию, заданным в свойствах.
void SpringRegular::RefreshSpring()
{
	refresh_spring_settings();
}

// Вызывается при деактивации компонента. Параметры пружины сбрасываются к значениям по умолчанию.
void SpringRegular::on_disable()
{
	// Сбрасываем к значениям по умолчанию при отключении компонента
	refresh_spring_settings();
}

// Жёсткость и демпфирование задаются из значений по умолчанию, заданных в свойствах.
void SpringRegular::refresh_spring_settings()
{
	// Используем значения по умолчанию из свойств (позволяет сбросить после нарастания сложности в игровом режиме)
	stiffness = defaultStiffness;
	damping = defaultDamping;
}