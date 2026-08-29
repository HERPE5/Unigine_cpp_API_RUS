// UI примера для демонстрации перемещения узла.
// Предоставляет ползунки скорости/угловой скорости и кнопку сброса,
// применяющиеся ко всем трём компонентам вариантов движения.

#pragma once
#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>

class SimpleMovement;
class SimpleMovement2;
class SimpleMovement3;

// Контроллер UI для настройки параметров движения и сброса позиции.
class SimpleMovementInfo : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(SimpleMovementInfo, Unigine::ComponentBase);
	COMPONENT_DESCRIPTION("This component displays information about the sample and demonstrates "
						  "how to use a simple move and rotate of a node.");

	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Ссылки на узлы с каждым вариантом движения
	PROP_PARAM(Node, simple_movement_node);
	PROP_PARAM(Node, simple_movement2_node);
	PROP_PARAM(Node, simple_movement3_node);

private:
	void init();
	void shutdown();
	// Получает ссылки на компоненты и сохраняет начальные трансформации
	void init_components();

	SampleDescriptionWindow sample_description_window;

	// Начальные трансформации, сохранённые для функции сброса
	Unigine::Math::Mat4 simple_movement_start_transform;
	Unigine::Math::Mat4 simple_movement2_start_transform;
	Unigine::Math::Mat4 simple_movement3_start_transform;

	// Закэшированные ссылки на компоненты для изменения параметров
	SimpleMovement *simple_movement = nullptr;
	SimpleMovement2 *simple_movement2 = nullptr;
	SimpleMovement3 *simple_movement3 = nullptr;
};
