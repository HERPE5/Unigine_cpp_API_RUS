// UI примера для спауна узлов по таймеру. Отображает сферу, меняющую цвет от красного
// к зелёному по мере прогресса таймера спауна. Цвет сферы предоставляет визуальную обратную связь
// о времени, оставшемся до следующего спауна.

#include "NodeSpawnerTimerSample.h"

#include "NodeSpawnerTimer.h"

#include <UnigineGui.h>
#include <UnigineVisualizer.h>

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(NodeSpawnerTimerSample);

// Визуализатор включается, создаётся слайдер частоты спауна.
void NodeSpawnerTimerSample::init()
{
	Visualizer::setEnabled(true);
	sample_description_window.createWindow();

	spawner = getComponent<NodeSpawnerTimer>(timed_spawner);
	spawner->spawn_rate = 5.0f;
	auto gui = Gui::getCurrent();
	// Слайдер позволяет настраивать интервал спауна во время выполнения
	sample_description_window.addFloatParameter("Spawn Frequency", "spawn frequency", 2, 0.1, 20,
		[this](float v) { spawner->spawn_rate = v; });
}

// Сфера визуализации таймера отрисовывается каждый кадр с интерполированным цветом.
void NodeSpawnerTimerSample::update()
{
	// Цвет интерполируется от красного (таймер на 0) до зелёного (таймер на spawn_rate)
	vec4 color = lerp(vec4_red, vec4_green,
		inverseLerp(0, spawner->spawn_rate, spawner->getTimer()));
	color.w = 0.5f; // прозрачность
	Visualizer::renderSolidSphere(1.0f, timed_spawner->getWorldTransform(), color);
}

// Визуализатор отключается, окно UI очищается.
void NodeSpawnerTimerSample::shutdown()
{
	Visualizer::setEnabled(false);
	sample_description_window.shutdown();
}
