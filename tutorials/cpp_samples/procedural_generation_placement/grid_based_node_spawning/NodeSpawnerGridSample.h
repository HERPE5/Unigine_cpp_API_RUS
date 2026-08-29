// UI примера для настройки создания узлов по сетке.
// Предоставляет элементы управления для размеров сетки, размера ячейки и режима точки опоры.
// Сетка перестраивается интерактивно по мере настройки параметров.

#pragma once
#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>

// Управляет элементами UI и запускает перестроение сетки при изменении параметров.
class NodeSpawnerGridSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(NodeSpawnerGridSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);
	PROP_PARAM(File, node_to_spawn)

private:
	void init();
	void shutdown();
	// Очищает существующие узлы и создаёт новую сетку с текущими настройками
	void redraw();

private:
	// Расстояние между соседними узлами в сетке
	float cell_size = 5.0f;
	// Количество узлов по каждой оси
	int grid_size_x = 5;
	int grid_size_y = 5;
	SampleDescriptionWindow sample_description_window;
	// Ссылки на все созданные узлы; используются для очистки перед пересозданием
	Unigine::Vector<Unigine::NodePtr> spawned_nodes;
	// Если true, сетка центрируется в начале координат; иначе растёт от угла
	bool is_pivot_center = false;
};
