// Генерирует процедурную геометрию меша вдоль пути сплайна с использованием GeometryGenerator.
// Контрольные точки интерактивны через Manipulators; перемещение любой точки пересоздаёт
// меш. Поддерживает типы геометрии ribbon, square pipe и round pipe.

#include "SplineGenerationSample.h"

#include <UnigineVisualizer.h>
#include <UnigineConsole.h>


REGISTER_COMPONENT(SplineGenerationSample);

using namespace Unigine;
using namespace Math;

// Процедурный объект меша и манипуляторы инициализируются; создаётся UI.
void SplineGenerationSample::init()
{
	// Создаётся пустой объект меша для получения процедурной геометрии
	spline_mesh_object = ObjectMeshStatic::create();

	// PROCEDURAL_MODE_DYNAMIC хранит меш в RAM для частых обновлений.
	// Второй параметр (0) использует рендеринг на основе RAM по умолчанию.
	spline_mesh_object->setMeshProceduralMode(ObjectMeshStatic::PROCEDURAL_MODE_DYNAMIC, 0);

	// Объекту разрешено перемещаться/трансформироваться в сцене
	spline_mesh_object->setImmovable(false);

	if (!spline_obejct_material.get())
	{
		Log::warning("SplineGenerationSample::init spline object material is unspecified.\n");
		return;
	}

	// Компонент Manipulators извлекается из указанного узла для обработки перетаскивания контрольных точек
	manipulators = ComponentSystem::get()->getComponent<Manipulators>(manipulators_node);
	if (!manipulators)
	{
		Log::warning("SplineGenerationSample::init manipulators_node is unspecified.\n");
		return;
	}

	// Подписываемся на изменения трансформации для пересоздания меша сплайна при перемещении любой контрольной точки
	manipulators->getEventTransformChanged().connect(event_connections, [this](ObjectPtr obj) {regenerate(); });

	Visualizer::setEnabled(true);
	init_gui();
}

// Точки сплайна и каркас меша визуализируются каждый кадр.
void SplineGenerationSample::update()
{
	// Каждая интерполированная точка сплайна визуализируется как маленькая красная сфера
	for (auto& point : current_spline_points)
	{
		Visualizer::renderPoint3D(point, 0.1f, vec4_red);
	}

	// Наложение каркаса отрисовывается на поверхности сгенерированного меша
	if (spline_mesh_object)
	{
		Visualizer::renderObjectSurface(spline_mesh_object, 0, vec4_white);
	}
}

// Окно UI освобождается, визуализатор отключается.
void SplineGenerationSample::shutdown()
{
	description_window.shutdown();
	Visualizer::setEnabled(false);
}

// Плоский лентообразный меш генерируется вдоль пути сплайна.
void SplineGenerationSample::generate_spline_mesh()
{
	// Позиции контрольных точек извлекаются из узлов сцены
	Vector<Vec3> points = get_points();

	// Контрольные точки интерполируются в гладкий сплайн с равномерной длиной сегментов
	if (!GeometryGenerator::computeSplinePoints(points, current_spline_points, segments_length_param))
	{
		Log::message("SplineGenerationSample::generateSplineMesh Invalid spline points");
	}

	// Плоский лентообразный меш генерируется вдоль пути сплайна
	MeshPtr mesh = GeometryGenerator::generateSplineMesh(current_spline_points, mesh_width_param, width_subdivision_param, segments_length_param, get_uv_settings());

	// Сгенерированный меш применяется немедленно (режим Force блокирует до завершения)
	spline_mesh_object->applyMoveMeshProceduralForce(mesh, 0);
	spline_mesh_object->setMaterial(spline_obejct_material, 0);
	last_generation_type = RIBBON;
}

// Меш квадратной трубы генерируется вдоль пути сплайна.
void SplineGenerationSample::generate_spline_square_pipe()
{
	Vector<Vec3> points = get_points();
	if (!GeometryGenerator::computeSplinePoints(points, current_spline_points, segments_length_param))
	{
		Log::message("SplineGenerationSample::generateSplineMesh Invalid spline points");
	}
	MeshPtr mesh = GeometryGenerator::generateSplineMeshSquare(current_spline_points, mesh_width_param, width_subdivision_param, segments_length_param, get_uv_settings());

	spline_mesh_object->applyMoveMeshProceduralForce(mesh, 0);
	spline_mesh_object->setMaterial(spline_obejct_material, 0);
	last_generation_type = SQUARE_PIPE;
}

// Меш круглой трубы генерируется вдоль пути сплайна.
void SplineGenerationSample::generate_spline_round_pipe()
{
	Vector<Vec3> points = get_points();
	if (!GeometryGenerator::computeSplinePoints(points, current_spline_points, segments_length_param))
	{
		Log::message("SplineGenerationSample::generateSplineMesh Invalid spline points");
	}

	// Генерируется меш круглой трубы; параметр ширины становится радиусом (делится на 2)
	MeshPtr mesh = GeometryGenerator::generateSplineMeshRound(current_spline_points, mesh_width_param / 2, width_subdivision_param, segments_length_param, get_uv_settings());
	spline_mesh_object->applyMoveMeshProceduralForce(mesh, 0);
	spline_mesh_object->setMaterial(spline_obejct_material, 0);
	last_generation_type = ROUND_PIPE;
}

// Меш пересоздаётся с использованием последнего выбранного типа геометрии.
void SplineGenerationSample::regenerate()
{
	switch (last_generation_type)
	{
	case SplineGenerationSample::RIBBON:
		generate_spline_mesh();
		break;
	case SplineGenerationSample::SQUARE_PIPE:
		generate_spline_square_pipe();
		break;
	case SplineGenerationSample::ROUND_PIPE:
		generate_spline_round_pipe();
		break;
	default:
		generate_spline_mesh();
		break;
	}
}

// Точки сплайна очищаются, геометрия меша удаляется.
void SplineGenerationSample::clear()
{
	current_spline_points.clear();
	// Текущая геометрия заменяется пустым мешем для очистки визуализации
	spline_mesh_object->applyMoveMeshProceduralForce(Mesh::create(), 0);
}

// Мировые позиции извлекаются из массива узлов контрольных точек.
Unigine::Vector<Unigine::Math::Vec3> SplineGenerationSample::get_points()
{
	int pointsNum = spline_nodes.size();
	Vector<Vec3> points = Vector<Vec3>(pointsNum);

	for (int i = 0; i < pointsNum; i++)
	{
		points[i] = spline_nodes[i]->getWorldPosition();
	}
	return points;
}


// Создаётся окно UI с элементами управления параметрами и кнопками генерации.
void SplineGenerationSample::init_gui()
{
	description_window.createWindow();
	auto params = description_window.getParameterGroupBox();

	auto featuresLabel = WidgetLabel::create("Generation features:");
	params->addChild(featuresLabel, Gui::ALIGN_LEFT);
	auto window = description_window.getWindow();
	auto buttons_grid_box = WidgetGridBox::create(3, 2, 2);
	params->addChild(buttons_grid_box);

	description_window.addFloatParameter("Mesh Width", "Mesh Width", mesh_width_param, 0.1f, 10.0f, [this](float v) {
		mesh_width_param = v;
		regenerate();
		});

	auto sliderParam = description_window.addIntParameter("Mesh Width Subdivision Number", "Mesh Width Subdivision Number", width_subdivision_param, 1, 20, [this](int v) {
		width_subdivision_param = v;
		regenerate();
		});

	description_window.addFloatParameter("Segment Length", "Segment Length", segments_length_param, 0.1f, 5.0f, [this](float v) {
		segments_length_param = v;
		regenerate();
		});

	description_window.addFloatParameter("UV Length Tiling", "Length Tiling", length_tiling, 0.05, 1.5, [this](float v) {
		length_tiling = v;
		regenerate();
		});
	description_window.addFloatParameter("UV Width Tiling", "Width Tiling", width_tiling, 0.5, 5, [this](float v) {
		width_tiling = v;
		regenerate();
		});
	description_window.addBoolParameter("Stretch UV Along Length", "Stretch UV Along Length", stretch_uv_along_length_param, [this](bool v) {
		stretch_uv_along_length_param = v;
		regenerate();
		});

	description_window.addBoolParameter("Stretch UV Along Width", "Stretch UV Along Width", stretch_uv_along_width_param, [this](bool v) {
		stretch_uv_along_width_param = v;
		regenerate();
		});

	description_window.addBoolParameter("Show Wireframe", "Show Wireframe", show_wireframe_param, [this](bool v) {
		show_wireframe_param = v;
		Visualizer::setEnabled(v);
		});

	auto button = WidgetButton::create("Ribbon");
	button->getEventClicked().connect(this, &SplineGenerationSample::generate_spline_mesh);
	buttons_grid_box->addChild(button, Gui::ALIGN_EXPAND);

	button = WidgetButton::create("Square Pipe");
	button->getEventClicked().connect(this, &SplineGenerationSample::generate_spline_square_pipe);
	buttons_grid_box->addChild(button, Gui::ALIGN_EXPAND);

	button = WidgetButton::create("Round Pipe");
	button->getEventClicked().connect(this, &SplineGenerationSample::generate_spline_round_pipe);
	buttons_grid_box->addChild(button, Gui::ALIGN_EXPAND);


	button = WidgetButton::create("Clear");
	button->getEventClicked().connect(this, &SplineGenerationSample::clear);
	params->addChild(button, Gui::ALIGN_BOTTOM);
}

// Структура настроек UV заполняется из текущих значений параметров.
GeometryGenerator::SplineMeshUVSettings SplineGenerationSample::get_uv_settings()
{
	auto settings = GeometryGenerator::SplineMeshUVSettings{};
	settings.length_tiling_amount = length_tiling;
	settings.width_tiling_amount = width_tiling;
	settings.stretch_along_length = (bool)stretch_uv_along_length_param.get();
	settings.stretch_along_width = (bool)stretch_uv_along_width_param.get();
	return settings;
}
