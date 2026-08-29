// Контроллер GUI для компонента TerrainMesh с интерактивным редактированием параметров.
// Предоставляет элементы управления для позиции, размера, поворота, разрешения и количества параллельных запросов.
// Отображает прогресс запросов в реальном времени и запускает генерацию меша.

#pragma once

#include "../../menu_ui/SampleDescriptionWindow.h"
#include "TerrainMesh.h"

#include <UnigineComponentSystem.h>
#include <UnigineWidgets.h>

// Интерактивный GUI для настройки и запуска операций TerrainMesh.
class TerrainMeshSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(TerrainMeshSample, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	PROP_PARAM(Node, terrain_mesh_prop, "Controlled Terrain Mesh");	// Ссылка на управляемый узел TerrainMesh

private:
	void init();
	void update();
	void shutdown();

	void update_terrain_mesh_parameters();	// Применяет текущие значения GUI к TerrainMesh

	TerrainMesh *terrain_mesh;		// Управляемый компонент terrain mesh

	// Параметры генерации меша
	Unigine::Math::Vec2 position{500.0f, 500.0f};	// Мировая позиция XY
	Unigine::Math::vec2 scale{500.0f, 500.0f};		// Масштаб XY
	float rotation{45.0f};							// Поворот вокруг оси Z в градусах
	Unigine::Math::ivec2 resolution{256, 256};		// Разрешение сетки
	int concurrent_fetches{10000};					// Максимум параллельных асинхронных запросов

	// Виджеты GUI
	void init_gui();
	void shutdown_gui();

	Unigine::WidgetWindowPtr window;
	Unigine::WidgetEditLinePtr position_x_edit_line;
	Unigine::WidgetEditLinePtr position_y_edit_line;
	Unigine::WidgetEditLinePtr size_x_edit_line;
	Unigine::WidgetEditLinePtr size_y_edit_line;;
	Unigine::WidgetEditLinePtr rotation_edit_line;
	Unigine::WidgetEditLinePtr resolution_x_edit_line;
	Unigine::WidgetEditLinePtr resolution_y_edit_line;
	Unigine::WidgetEditLinePtr concurrent_fetches_edit_line;
	Unigine::WidgetCheckBoxPtr draw_bounding_box_check_box;
	Unigine::WidgetCheckBoxPtr draw_wireframe_check_box;

	Unigine::WidgetLabelPtr status_label;		// Подпись отображения прогресса

	SampleDescriptionWindow sample_description_window;

	// Callback'и событий GUI
	void position_x_edit_line_callback();
	void position_y_edit_line_callback();
	void size_x_edit_line_callback();
	void size_y_edit_line_callback();
	void rotation_edit_line_callback();
	void resolution_x_edit_line_callback();
	void resolution_y_edit_line_callback();
	void concurrent_fetches_edit_line_callback();
	void draw_bounding_box_check_box_callback();
	void draw_wireframe_check_box_callback();
	void generate_button_callback();	// Запускает генерацию меша
};