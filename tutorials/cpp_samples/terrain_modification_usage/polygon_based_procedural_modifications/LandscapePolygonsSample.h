// Демонстрирует изменение terrain на основе полигонов и генерацию мешей.
// Поддерживает создание мешей, размещение декалей, рисование масок и редактирование высоты.
// Фигуры определяются позициями дочерних узлов и триангулируются для операций.

#pragma once
#include "../../menu_ui/SampleDescriptionWindow.h"
#include "../../utils/GeometryGenerator.h"
#include "../../utils/LayerMapPolygonEditor.h"
#include "../../user_interface/widget_manipulators/Manipulators.h"

#include <UnigineComponentSystem.h>
#include <UnigineObjects.h>
#include <UnigineWidgets.h>

// Контроллер для функций изменения landscape на основе полигонов.
class LandscapePolygonsSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(LandscapePolygonsSample, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	PROP_PARAM(Node, terrain_param, "Terrain");				// Ссылка на узел terrain
	PROP_ARRAY(Node, figures, "Figures");						// Массив родительских узлов фигур (дочерние узлы определяют вершины полигона)

	PROP_PARAM(Node, layer_map_node, "Layer Map");				// Целевая landscape layer map для изменений
	PROP_PARAM(Node, layer_map_editor_node, "Layer Map Editor");// Ссылка на узел утилиты редактора
	PROP_PARAM(Node, manipulators_node, "");					// Узел, содержащий элементы управления манипулятором
	PROP_PARAM(Material, ortho_material, "DecalOrtho material");// Материал, применяемый к ортогональным декалям
	PROP_PARAM(Material, mesh_material, "Mesh render material");// Материал, используемый для рендеринга меша в текстуру
	PROP_PARAM(Node, clutter_node, "Clutter node");				// Объект растительности clutter для инвалидации

private:
	void init();
	void update();
	void shutdown();

	void draw_triangulation_all_figures();		// Визуализирует триангулированные полигоны для всех фигур
	void init_gui();							// Создаёт панель управления с выбором режима и кнопками функций
	void reset();								// Отменяет изменения landscape и удаляет созданные узлы
	void render_mesh_to_texture(Unigine::MeshPtr mesh, Unigine::TexturePtr texture, Unigine::MaterialPtr render_material, Unigine::Math::vec4 color = Unigine::Math::vec4_white);	// Рендерит меш в текстуру с помощью ортографической проекции
	void generate_mesh_button();				// Создаёт ObjectMeshStatic из полигональных фигур
	void generate_decal_mesh_button();			// Создаёт DecalMesh из полигональных фигур
	void generate_decal_ortho_button();			// Создаёт DecalOrtho с отрендеренной текстурой из полигонов
	void draw_terrain_mask_button();			// Рисует данные маски на landscape с помощью форм полигонов
	void level_terrain_button();				// Выравнивает высоту terrain в границах полигона
	void lower_terrain_button();				// Понижает высоту terrain в границах полигона
	void revert_points_positions();				// Восстанавливает узлы фигур и точек в исходные позиции

	// Рендерит рёбра треугольников с помощью визуализатора для отладки.
	static void draw_triangulation(
		const Unigine::Vector<Unigine::Math::Vec3>& mesh_points,
		const Unigine::Vector<unsigned short>& indices);

private:
	Unigine::LandscapeLayerMapPtr layer_map;		// Целевая landscape layer map

	Unigine::ObjectMeshClutterPtr clutter;			// Объект clutter для инвалидации растительности
	bool is_clutter_mask_valid = true;				// Отслеживает, нужно ли обновление clutter после изменений маски
	const int clutter_invalidation_delay_frames = 10;	// Задержка перед инвалидацией clutter
	int invalidation_frame = 0;						// Кадр, в котором была запущена инвалидация

	Unigine::WidgetListBoxPtr feature_list;			// Виджет списка для выбора функции

	Unigine::Vector<Unigine::TexturePtr> ortho_decal_textures;	// Отрендеренные текстуры для ортогональных декалей
	Unigine::Vector<Unigine::NodePtr> created_nodes;			// Узлы, созданные во время генерации
	Unigine::Vector<Unigine::Math::Vec3> figures_initial_positions;			// Сохранённые исходные позиции фигур для сброса
	Unigine::Vector<Unigine::Vector<Unigine::Math::Vec3>> points_initial_positions;	// Сохранённые исходные позиции точек для сброса

	SampleDescriptionWindow description_window;		// Окно UI для элементов управления примера
	LayerMapPolygonEditor* layer_map_editor = nullptr;	// Экземпляр утилиты редактора полигонов
	Manipulators* manipulators = nullptr;			// Элементы управления манипулятором трансформации
};
