// UI примера для создания сетки. Предоставляет слайдеры для размеров сетки и размера ячейки,
// а также чекбокс для переключения между режимами угловой и центральной точки опоры. Сетка перестраивается
// при каждом изменении параметра путём удаления и пересоздания всех узлов.

#include "NodeSpawnerGridSample.h"


#include "NodeSpawnerGrid.h"

REGISTER_COMPONENT(NodeSpawnerGridSample);

using namespace Unigine;
using namespace Math;

// Создаются слайдеры UI и чекбокс; создаётся начальная сетка.
void NodeSpawnerGridSample::init()
{
	sample_description_window.createWindow();

	// Слайдер ширины сетки - запускает перестроение при изменении
	sample_description_window.addIntParameter("Grid Size X", "Grid Size X", 5, 1, 100, [this](int v) {
		grid_size_x = v;
		redraw();
	});

	// Слайдер высоты сетки - запускает перестроение при изменении
	sample_description_window.addIntParameter("Grid Size Y", "Grid Size Y", 5, 1, 100, [this](int v) {
		grid_size_y = v;
		redraw();
	});

	// Слайдер расстояния между ячейками - запускает перестроение при изменении
	sample_description_window.addFloatParameter("Cell Size", "Cell Size", 2.f, 0.5f, 100.f, [this](float v) {
		cell_size = v;
		redraw();
	});

	// Чекбокс режима точки опоры - переключает между угловым и центральным началом координат
	auto parameters = sample_description_window.getParameterGroupBox();
	auto hbox = WidgetHBox::create();
	auto checkbox = WidgetCheckBox::create();
	checkbox->getEventClicked().connect(*this, [this, checkbox]() {
		is_pivot_center = checkbox->isChecked();
		redraw();
	});
	auto label = WidgetLabel::create("Spawn from center");

	hbox->addChild(label);
	hbox->addChild(checkbox);

	parameters->addChild(hbox, Gui::ALIGN_LEFT);

	redraw();
}


// Существующие узлы удаляются, создаётся новая сетка с текущими настройками.
void NodeSpawnerGridSample::redraw()
{
	// Очищаем предыдущую сетку перед созданием новой
	if (!spawned_nodes.empty())
	{
		for (const auto &it : spawned_nodes)
		{
			it.deleteLater();
		}
		spawned_nodes.clear();
	}
	// Создаём сетку в начале координат мира с текущими параметрами
	Utils::spawnGrid(node_to_spawn, vec2(cell_size), ivec2(grid_size_x, grid_size_y),
		Mat4_identity, is_pivot_center, &spawned_nodes);
}

// Окно UI очищается при уничтожении компонента.
void NodeSpawnerGridSample::shutdown()
{
	//checkbox_connection.disconnect();
	sample_description_window.shutdown();
}
