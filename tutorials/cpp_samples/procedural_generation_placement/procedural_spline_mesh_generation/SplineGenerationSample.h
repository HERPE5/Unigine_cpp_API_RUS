#pragma once
#include <UnigineComponentSystem.h>

#include "../../menu_ui/SampleDescriptionWindow.h"
#include "../../utils/GeometryGenerator.h"
#include "../../user_interface/widget_manipulators/Manipulators.h"

// Демонстрирует процедурную генерацию меша вдоль пути сплайна.
// Контрольные точки из узлов сцены интерполируются в гладкий сплайн,
// затем выдавливаются в геометрию (профили ribbon, square pipe или round pipe).
// Меш обновляется в реальном времени через процедурный режим при перемещении точек манипуляторами.
// UV-развёртка поддерживает режимы повторения и растяжения по осям длины/ширины.
class SplineGenerationSample final : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(SplineGenerationSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	PROP_ARRAY(Node, spline_nodes, "Spline nodes"); // Контрольные точки, определяющие путь сплайна

	// Параметры генерации меша
	PROP_PARAM(Float, mesh_width_param, 5.0f);              // Ширина сгенерированной геометрии
	PROP_PARAM(Int, width_subdivision_param, 5);            // Подразбиения по ширине
	PROP_PARAM(Float, segments_length_param, 3.0f);         // Длина каждого сегмента сплайна

	// Параметры UV-развёртки
	PROP_PARAM(Float, length_tiling, 1.0f);                 // Повторение текстуры вдоль длины сплайна
	PROP_PARAM(Float, width_tiling, 1.0f);                  // Повторение текстуры по ширине
	PROP_PARAM(Toggle, stretch_uv_along_length_param, false); // Растянуть UV по всей длине
	PROP_PARAM(Toggle, stretch_uv_along_width_param, false);  // Растянуть UV по всей ширине

	PROP_PARAM(Toggle, show_wireframe_param, false);        // Отображать наложение каркаса
	PROP_PARAM(Material, spline_obejct_material, "Spline Object Material"); // Материал для меша

	PROP_PARAM(Node, manipulators_node, "Manipulators node"); // Узел, содержащий компонент Manipulators

private:
	// Доступные профили геометрии для выдавливания сплайна
	enum GENERATION_TYPE
	{
		RIBBON,      // Плоская лентообразная поверхность
		SQUARE_PIPE, // Четырёхгранная труба
		ROUND_PIPE   // Круглая труба
	};

	void init();     // Инициализирует объект меша и манипуляторы
	void update();   // Визуализирует точки сплайна и каркас
	void shutdown(); // Освобождает ресурсы UI

	void init_gui();                  // Создаёт окно элементов управления параметрами
	void generate_spline_mesh();      // Генерирует плоскую лентообразную геометрию
	void generate_spline_square_pipe(); // Генерирует геометрию четырёхгранной трубы
	void generate_spline_round_pipe();  // Генерирует геометрию круглой трубы
	void regenerate();                // Пересоздаёт с текущим типом
	void clear();                     // Очищает меш и данные сплайна

	Unigine::Vector<Unigine::Math::Vec3> get_points();     // Извлекает позиции из контрольных узлов
	GeometryGenerator::SplineMeshUVSettings get_uv_settings(); // Строит настройки UV из параметров

private:
	Unigine::ObjectMeshStaticPtr spline_mesh_object;             // Процедурный объект меша
	Unigine::Vector<Unigine::Math::Vec3> current_spline_points;  // Интерполированные точки сплайна
	GENERATION_TYPE last_generation_type = RIBBON;               // Текущий выбранный тип геометрии

	SampleDescriptionWindow description_window; // Окно UI для параметров
	Manipulators *manipulators = nullptr;       // Обработчик манипуляции контрольными точками
	EventConnections event_connections;         // Хранит подписки на события
};
