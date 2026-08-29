// Реализует раскопку terrain с помощью проекции глубины объекта. Форма роющего объекта
// проецируется на поверхность terrain, изменяя данные высоты и маски
// в базовом LandscapeLayerMap с помощью операций асинхронного рисования текстуры.

#pragma once
#include "../../menu_ui/SampleDescriptionWindow.h"
#include <UnigineComponentSystem.h>
#include <UnigineObjects.h>
#include <UnigineWidgets.h>
#include <UnigineViewport.h>
#include "ObjectDepth.h"
#include <UniginePhysics.h>

class DiggingTool : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(DiggingTool, Unigine::ComponentBase);

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// Слой terrain для изменения раскопкой
	PROP_PARAM(Node, lmap_node, "Landscape Terrain Layer Map");
	// Объект, форма которого определяет объём раскопки
	PROP_PARAM(Node, digging_object_node, "Digging Object");

private:
	void init();
	void update();
	void shutdown();

	// Плавная интерполяция позиции/поворота роющего объекта
	void update_digging_object();
	// Проверяет, достаточно ли переместился объект, чтобы требовалось обновление terrain
	bool should_update_terrain();
	// Ставит в очередь асинхронное изменение текстуры landscape
	void enqueue_terrain_update();
	// Очищает все изменения terrain, сделанные этим инструментом
	void reset_modifications();

	// Callback, вызываемый по завершении асинхронного рисования текстуры
	void on_texture_draw(const Unigine::UGUID &guid, int operation_id, const Unigine::LandscapeTexturesPtr &buffer, const Unigine::Math::ivec2 &coords, int data_mask);

private:
	// Данные, хранимые для каждой ожидающей асинхронной операции
	struct DrawData
	{
		Unigine::Math::ivec2 resolution;
		// Текстура глубины, отрендеренная сверху роющего объекта
		Unigine::TexturePtr object_depth_texture;
	};

	using LandscapeOperationID = int;

	Unigine::LandscapeLayerMapPtr layer_map;
	// Материал, содержащий шейдерные проходы раскопки
	Unigine::MaterialPtr digging_tool_mat;
	Unigine::ObjectPtr digging_object;
	// Вспомогательный класс для рендеринга глубины сверху
	ObjectDepth object_depth;

	// Текущий ограничивающий бокс роющего объекта в мировом пространстве
	Unigine::Math::WorldBoundBox digging_object_wbb;

	// Минимальное перемещение перед запуском обновления terrain (мировые единицы)
	float position_spacing = .025f;
	// Минимальный поворот перед запуском обновления terrain (градусы)
	float rotation_spacing = 1.f;

	// Целевая трансформация для плавной интерполяции
	Unigine::Math::Mat4 target_transform;
	// Значения предыдущего кадра для обнаружения изменений
	Unigine::Math::Vec3 prev_position;
	Unigine::Math::vec3 prev_rotation;

	// Операции, ожидающие завершения callback
	Unigine::HashMap<LandscapeOperationID, DrawData> per_operation_draw_data;
	Unigine::EventConnection texture_draw_connection;

private:
	// UI для управления роющим объектом в сцене
	struct Gui
	{
		void init(DiggingTool *sample);
		void update();
		void shutdown();

		void set_manipulator(Unigine::WidgetManipulatorPtr manipulator);

		// Виджеты манипуляторов переноса и поворота
		Unigine::WidgetManipulatorTranslatorPtr translator;
		Unigine::WidgetManipulatorRotatorPtr rotator;
		Unigine::WidgetManipulatorPtr active;
		// Система координат для ориентации манипулятора
		enum { LOCAL, WORLD } basis = LOCAL;
		SampleDescriptionWindow window;
		DiggingTool *sample = nullptr;
	};

	Gui gui;
};
