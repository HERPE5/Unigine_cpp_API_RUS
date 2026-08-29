#pragma once
#include <UnigineComponentSystem.h>
#include "../../menu_ui/SampleDescriptionWindow.h"

class Pawn;

// Демонстрирует архитектуру Component System и распространённые паттерны.
// Показывает создание компонентов во время выполнения, прикрепление компонентов на основе свойств
// и взаимодействие между компонентами.
// Реализует мини-игру: волчки создают снаряды, наносящие урон пешке.
class ComponentSystemSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(ComponentSystemSample, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void update();
	void shutdown();

	void my_pawn_destroyed() { my_pawn = nullptr; }
	Unigine::ObjectMeshDynamicPtr create_box(const Unigine::Math::Mat4 &transform,
		const Unigine::Math::vec3 &size);
	void init_gui();

private:
	Pawn *my_pawn;
	float time;

	Unigine::WidgetLabelPtr label;
};
