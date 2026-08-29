// Контроллер GUI для компонента TerrainMesh с интерактивным редактированием параметров.
// Предоставляет элементы управления для позиции, размера, поворота, разрешения и количества параллельных запросов.
// Отображает прогресс запросов в реальном времени и запускает генерацию меша.

#include "TerrainMeshSample.h"

#include <UnigineVisualizer.h>

REGISTER_COMPONENT(TerrainMeshSample);


using namespace Unigine;
using namespace Math;

// Включается визуализатор; получается компонент terrain mesh; инициализируется GUI.
void TerrainMeshSample::init()
{
	Visualizer::setEnabled(true);
	terrain_mesh = getComponent<TerrainMesh>(terrain_mesh_prop.get());
	update_terrain_mesh_parameters();
	init_gui();
}

// Подпись статуса обновляется текущим прогрессом запросов.
void TerrainMeshSample::update()
{
	status_label->setText(String::format("Status: %i/%i",
		terrain_mesh->getCompletedFetchPositions(), terrain_mesh->getTotalFetchPositions()));
}

// Визуализатор отключается; ресурсы GUI освобождаются.
void TerrainMeshSample::shutdown()
{
	Visualizer::setEnabled(false);
	shutdown_gui();
}

// Трансформация составляется из значений GUI и применяется к узлу terrain mesh.
void TerrainMeshSample::update_terrain_mesh_parameters()
{
	// Трансформация строится из позиции, поворота и масштаба
	Mat4 transform;
	composeTransform(transform, Vec3(position.x, position.y, 0), quat(0.0f, 0.0f, rotation),
		vec3(scale.x, scale.y, 1.0f));
	terrain_mesh->getNode()->setTransform(transform);

	// Применяются настройки разрешения и параллелизма
	terrain_mesh->setResolution(resolution);
	terrain_mesh->setMaxFetchers(concurrent_fetches);
}

// Окно примера создаётся с полями редактирования параметров и элементами управления.
void TerrainMeshSample::init_gui()
{
	sample_description_window.createWindow();
	window = sample_description_window.getWindow();

	auto group_box = sample_description_window.getParameterGroupBox();

	// Создаются поля редактирования позиции X/Y
	auto hbox = WidgetHBox::create(5);
	group_box->addChild(hbox, Gui::ALIGN_LEFT);
	auto label = WidgetLabel::create("Position");
	label->setWidth(100);
	hbox->addChild(label, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("X");
	hbox->addChild(label, Gui::ALIGN_LEFT);
	position_x_edit_line = WidgetEditLine::create(
		String::ftoa(static_cast<float>(terrain_mesh->getNode()->getPosition().x)));
	position_x_edit_line->setValidator(Gui::VALIDATOR_FLOAT);
	position_x_edit_line->getEventChanged().connect(this, &TerrainMeshSample::position_x_edit_line_callback);
	hbox->addChild(position_x_edit_line, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Y");
	hbox->addChild(label, Gui::ALIGN_LEFT);
	position_y_edit_line = WidgetEditLine::create(
		String::ftoa(static_cast<float>(terrain_mesh->getNode()->getPosition().y)));
	position_y_edit_line->setValidator(Gui::VALIDATOR_FLOAT);
	position_y_edit_line->getEventChanged().connect(this, &TerrainMeshSample::position_y_edit_line_callback);
	hbox->addChild(position_y_edit_line, Gui::ALIGN_LEFT);

	// Создаются поля редактирования размера X/Y
	hbox = WidgetHBox::create(5);
	group_box->addChild(hbox, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Size");
	label->setWidth(100);
	hbox->addChild(label, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("X");
	hbox->addChild(label, Gui::ALIGN_LEFT);
	size_x_edit_line = WidgetEditLine::create(String::ftoa(terrain_mesh->getNode()->getScale().x));
	size_x_edit_line->setValidator(Gui::VALIDATOR_FLOAT);
	size_x_edit_line->getEventChanged().connect(this, &TerrainMeshSample::size_x_edit_line_callback);
	hbox->addChild(size_x_edit_line, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Y");
	hbox->addChild(label, Gui::ALIGN_LEFT);
	size_y_edit_line = WidgetEditLine::create(String::ftoa(terrain_mesh->getNode()->getScale().y));
	size_y_edit_line->setValidator(Gui::VALIDATOR_FLOAT);
	size_y_edit_line->getEventChanged().connect(this, &TerrainMeshSample::size_y_edit_line_callback);
	hbox->addChild(size_y_edit_line, Gui::ALIGN_LEFT);

	// Создаётся поле редактирования угла поворота
	hbox = WidgetHBox::create(5);
	group_box->addChild(hbox, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Angle");
	label->setWidth(100);
	hbox->addChild(label, Gui::ALIGN_LEFT);
	rotation_edit_line = WidgetEditLine::create(
		String::ftoa(terrain_mesh->getNode()->getRotation().getAngle(vec3_up)));
	rotation_edit_line->setValidator(Gui::VALIDATOR_FLOAT);
	rotation_edit_line->getEventChanged().connect(this, &TerrainMeshSample::rotation_edit_line_callback);
	hbox->addChild(rotation_edit_line, Gui::ALIGN_LEFT);

	// Создаются поля редактирования разрешения X/Y
	hbox = WidgetHBox::create(5);
	group_box->addChild(hbox, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Resolution");
	label->setWidth(100);
	hbox->addChild(label, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("X");
	hbox->addChild(label, Gui::ALIGN_LEFT);
	resolution_x_edit_line = WidgetEditLine::create(String::itoa(resolution.x));
	resolution_x_edit_line->setValidator(Gui::VALIDATOR_UINT);
	resolution_x_edit_line->getEventChanged().connect(this, &TerrainMeshSample::resolution_x_edit_line_callback);
	hbox->addChild(resolution_x_edit_line, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Y");
	hbox->addChild(label, Gui::ALIGN_LEFT);
	resolution_y_edit_line = WidgetEditLine::create(String::itoa(resolution.y));
	resolution_y_edit_line->setValidator(Gui::VALIDATOR_UINT);
	resolution_y_edit_line->getEventChanged().connect(this, &TerrainMeshSample::resolution_y_edit_line_callback);
	hbox->addChild(resolution_y_edit_line, Gui::ALIGN_LEFT);

	// Создаётся поле редактирования количества параллельных запросов
	hbox = WidgetHBox::create(5);
	group_box->addChild(hbox, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Concurrent fetches");
	label->setWidth(100);
	hbox->addChild(label, Gui::ALIGN_LEFT);
	concurrent_fetches_edit_line = WidgetEditLine::create(String::itoa(concurrent_fetches));
	concurrent_fetches_edit_line->setValidator(Gui::VALIDATOR_UINT);
	concurrent_fetches_edit_line->getEventChanged().connect(this, &TerrainMeshSample::concurrent_fetches_edit_line_callback);
	hbox->addChild(concurrent_fetches_edit_line, Gui::ALIGN_LEFT);

	// Создаются чекбоксы визуализации
	draw_bounding_box_check_box = WidgetCheckBox::create("Draw Bounding Box");
	draw_bounding_box_check_box->setChecked(true);
	draw_bounding_box_check_box->getEventChanged().connect(this, &TerrainMeshSample::draw_bounding_box_check_box_callback);
	group_box->addChild(draw_bounding_box_check_box, Gui::ALIGN_LEFT);

	draw_wireframe_check_box = WidgetCheckBox::create("Draw Wireframe");
	draw_wireframe_check_box->getEventChanged().connect(this, &TerrainMeshSample::draw_wireframe_check_box_callback);
	group_box->addChild(draw_wireframe_check_box, Gui::ALIGN_LEFT);

	// Создаётся кнопка Generate
	hbox = WidgetHBox::create(5);
	group_box->addChild(hbox, Gui::ALIGN_LEFT);
	auto button = WidgetButton::create("Generate");
	button->getEventClicked().connect(this, &TerrainMeshSample::generate_button_callback);
	hbox->addChild(button, Gui::ALIGN_LEFT);

	// Создаётся подпись статуса для отображения прогресса
	hbox = WidgetHBox::create(5);
	group_box->addChild(hbox, Gui::ALIGN_LEFT);
	status_label = WidgetLabel::create("Status: 0/0");
	hbox->addChild(status_label, Gui::ALIGN_LEFT);

	window->arrange();
}

// Виджет окна планируется к удалению.
void TerrainMeshSample::shutdown_gui()
{
	window.deleteLater();
}

// =====================================================================
// CALLBACK'И GUI - обновляют параметры при изменении полей ввода
// =====================================================================

void TerrainMeshSample::position_x_edit_line_callback()
{
	position.x = String::atof(position_x_edit_line->getText());
	update_terrain_mesh_parameters();
}

void TerrainMeshSample::position_y_edit_line_callback()
{
	position.y = String::atof(position_y_edit_line->getText());
	update_terrain_mesh_parameters();
}

void TerrainMeshSample::size_x_edit_line_callback()
{
	scale.x = String::atof(size_x_edit_line->getText());
	update_terrain_mesh_parameters();
}

void TerrainMeshSample::size_y_edit_line_callback()
{
	scale.y = String::atof(size_y_edit_line->getText());
	update_terrain_mesh_parameters();
}

void TerrainMeshSample::rotation_edit_line_callback()
{
	rotation = String::atof(rotation_edit_line->getText());
	update_terrain_mesh_parameters();
}

void TerrainMeshSample::resolution_x_edit_line_callback()
{
	resolution.x = String::atoi(resolution_x_edit_line->getText());
	update_terrain_mesh_parameters();
}

void TerrainMeshSample::resolution_y_edit_line_callback()
{
	resolution.y = String::atoi(resolution_y_edit_line->getText());
	update_terrain_mesh_parameters();
}

void TerrainMeshSample::concurrent_fetches_edit_line_callback()
{
	concurrent_fetches = String::atoi(concurrent_fetches_edit_line->getText());
	update_terrain_mesh_parameters();
}

// Переключается визуализация ограничивающего бокса.
void TerrainMeshSample::draw_bounding_box_check_box_callback()
{
	terrain_mesh->setDrawBoundingBox(draw_bounding_box_check_box->isChecked());
}

// Переключается визуализация каркаса.
void TerrainMeshSample::draw_wireframe_check_box_callback()
{
	terrain_mesh->setDrawWireframe(draw_wireframe_check_box->isChecked());
}

// Запускается генерация terrain mesh.
void TerrainMeshSample::generate_button_callback()
{
	terrain_mesh->run();
}
