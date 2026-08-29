#pragma once
#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>
#include <UnigineObjects.h>
#include <UnigineWidgets.h>

class PhysicsMover;

// Предоставляет элементы управления UI для настройки параметров физического движения в реальном времени.
// Слайдеры позволяют настраивать силу, крутящий момент, ограничения скорости и силу торможения.
class PhysicsMovementSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(PhysicsMovementSample, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	PROP_PARAM(Node, car); // Узел транспортного средства с компонентом PhysicsMover

private:
	void init();         // Получает компонент движения и создаёт UI
	void shutdown();     // Закрывает окно UI

	void init_gui();     // Создаёт слайдеры параметров
	void shutdown_gui(); // Освобождает ресурсы UI

private:
	Unigine::NodePtr car_node;             // Закэшированная ссылка на узел автомобиля

	PhysicsMover* physics_mover = nullptr; // Настраиваемый контроллер движения

	SampleDescriptionWindow sample_description_window; // Окно UI параметров
};
