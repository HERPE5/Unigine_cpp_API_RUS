// Демонстрирует создание слоёв деталей terrain во время выполнения на ObjectLandscapeTerrain.
// Материалы деталей для травы, камня и снега создаются и применяются к каналам маски.
// Порядок рендеринга настраивается для правильного наслоения деталей (камень, трава, затем снежные шапки).

#pragma once
#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>
#include <UnigineObjects.h>
#include <UnigineWidgets.h>

// Создаёт и настраивает слои деталей terrain во время выполнения.
class DetailsSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(DetailsSample, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	PROP_PARAM(Node, terrain_param, "Terrain");				// Ссылка на ObjectLandscapeTerrain
	PROP_PARAM(File, grass_texture_param, "Grass Texture");	// Текстура albedo для детали травы
	PROP_PARAM(File, stone_texture_param, "Stone Texture");	// Текстура albedo для детали камня

private:
	void init();
	void shutdown();

	void create_detail_grass();			// Создаёт деталь травы на канале маски 1
	void create_detail_stone();			// Создаёт деталь камня на канале маски 2
	void create_detail_snow_cap();		// Создаёт деталь снега на основе высоты на канале маски 0
	void set_detail_render_order();		// Настраивает правильный порядок наслоения

	Unigine::ObjectLandscapeTerrainPtr terrain;
	Unigine::TexturePtr grass_texture;
	Unigine::TexturePtr stone_texture;
	Unigine::MaterialPtr grass_material;
	Unigine::MaterialPtr stone_material;
	Unigine::MaterialPtr snow_material;
	bool created{false};	// Предотвращает дублирующее создание деталей

	void init_gui();
	// Отображает превью текстуры для типа детали
	void add_detail_properties(const Unigine::WidgetPtr &parent, const char *title,
		decltype(grass_texture_param) &texture);
	void shutdown_gui();

	SampleDescriptionWindow sample_description_window;

	void add_details_button_callback();	// Обрабатывает клик по кнопке Create
};