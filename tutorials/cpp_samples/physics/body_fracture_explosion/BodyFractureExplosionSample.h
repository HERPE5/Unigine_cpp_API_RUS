// UI примера для запуска эффекта взрыва. Предоставляет кнопку, которая
// получает компонент BodyFractureExplosion из целевого узла и
// запускает взрыв при нажатии.

#pragma once
#include "../../menu_ui/SampleDescriptionWindow.h"
#include <UnigineComponentSystem.h>

class BodyFractureExplosionSample
	: public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(BodyFractureExplosionSample, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Узел, содержащий компонент BodyFractureExplosion для запуска
	PROP_PARAM(Node, target);

private:
	void init();
	void shutdown();

private:
	SampleDescriptionWindow sample_description_window;
};
