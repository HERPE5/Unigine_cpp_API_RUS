// UI примера для спауна узлов по таймеру с визуальной обратной связью таймера.
// Отрисовывает сферу с интерполяцией цвета, меняющую цвет от красного
// к зелёному по мере прогресса таймера спауна к следующему спауну.

#pragma once
#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>

class NodeSpawnerTimer;

// Предоставляет слайдер частоты спауна и отрисовывает сферу визуализации таймера.
class NodeSpawnerTimerSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(NodeSpawnerTimerSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	PROP_PARAM(Node, timed_spawner);

private:
	void init();
	void update();
	void shutdown();

private:
	// Ссылка на компонент спаунера для доступа к состоянию таймера
	NodeSpawnerTimer *spawner = nullptr;
	SampleDescriptionWindow sample_description_window;
};
