// Демонстрирует процедурное создание LandscapeTerrain из исходных изображений.
// Текстуры albedo, высоты и маски объединяются в файл карты landscape (.lmap).
// Карта затем применяется к ObjectLandscapeTerrain через LandscapeLayerMap.

#pragma once

#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>
#include <UnigineObjects.h>
#include <UnigineWidgets.h>

// Создаёт landscape terrain из сетки исходных изображений во время выполнения.
class CreateSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(CreateSample, Unigine::ComponentBase);
	COMPONENT_INIT(init, 2);
	COMPONENT_SHUTDOWN(shutdown);

	PROP_PARAM(IVec2, resolution_param, "Resolution");	// Общее разрешение карты landscape в пикселях
	PROP_PARAM(IVec2, grid_size_param, "Grid Size");	// Количество тайлов по X и Y

	PROP_ARRAY(File, albedo_images_param, "Albedo Images");			// Текстуры цвета/диффузии для каждого тайла
	PROP_ARRAY(File, height_images_param, "Height Images");			// Изображения карты высот для каждого тайла
	PROP_ARRAY(File, grass_mask_images_param, "Grass Mask Images");	// Маска детали травы для каждого тайла
	PROP_ARRAY(File, stone_mask_images_param, "Stone Mask Images");	// Маска детали камня для каждого тайла

	PROP_PARAM(Vec2, terrain_size, Unigine::Math::vec2(1000.0f, 1000.0f));	// Мировой размер terrain в единицах
	PROP_PARAM(Float, terrain_height_scale, 150.0f);						// Множитель вертикального масштаба карты высот

private:
	void init();
	void shutdown();

	void create_landscape_map();		// Генерирует файл .lmap из исходных изображений
	void create_landscape_objects();	// Создаёт узел terrain и присоединяет карту слоя

	// Callback, вызываемый для каждого тайла во время создания карты
	void create_callback(const Unigine::LandscapeMapFileCreatorPtr &creator,
		const Unigine::LandscapeImagesPtr &images, int x, int y);


	bool created{false};	// Предотвращает дублирующее создание terrain

	void init_gui();
	// Отображает миниатюры изображений в виде сетки
	void add_image_grid(const Unigine::WidgetPtr &parent, const char *title,
		decltype(albedo_images_param) &images);
	void shutdown_gui();
	void create_button_callback();	// Обрабатывает клик по кнопке Create

private:
	SampleDescriptionWindow sample_description_window;
};
