// Демонстрирует процедурное создание LandscapeTerrain из исходных изображений.
// Текстуры albedo, высоты и маски объединяются в файл карты landscape (.lmap).
// Карта затем применяется к ObjectLandscapeTerrain через LandscapeLayerMap.

#include "CreateSample.h"

REGISTER_COMPONENT(CreateSample);

using namespace Unigine;
using namespace Math;

// Инициализируется GUI; массивы исходных изображений проверяются на соответствие размерам сетки.
void CreateSample::init()
{
	init_gui();

	// Ожидаемое количество тайлов вычисляется из размеров сетки
	int image_count = grid_size_param.get().x * grid_size_param.get().y;
	if (albedo_images_param.size() != image_count
		|| height_images_param.size() != image_count
		|| grass_mask_images_param.size() != image_count
		|| stone_mask_images_param.size() != image_count)
	{
		Log::error("Expected %i terrain images\n", image_count);
		return;
	}
}

// Ресурсы GUI освобождаются.
void CreateSample::shutdown()
{
	shutdown_gui();
}

// Файл карты landscape создаётся из исходных изображений; настраиваются параметры слоёв.
void CreateSample::create_landscape_map()
{
	// Создатель файла карты настраивается разрешением и раскладкой сетки
	auto map_file_creator = LandscapeMapFileCreator::create();
	map_file_creator->setResolution(resolution_param.get());
	map_file_creator->setGrid(grid_size_param.get());
	map_file_creator->getEventCreate().connect(this, &CreateSample::create_callback);
	map_file_creator->setPath("landscape_map.gen.lmap");
	map_file_creator->run();

	// Настройки файла карты загружаются для настройки режимов смешивания слоёв
	auto map_file_settings = LandscapeMapFileSettings::create();
	map_file_settings->load(FileSystem::getGUID("landscape_map.gen.lmap"));

	// Слой albedo включается с альфа-смешиванием
	map_file_settings->setEnabledAlbedo(true);
	map_file_settings->setAlbedoBlending(Unigine::Landscape::BLENDING_MODE::ALPHA_BLEND);
	map_file_settings->setEnabledOpacityAlbedo(false);

	// Слой высоты включается с альфа-смешиванием
	map_file_settings->setEnabledHeight(true);
	map_file_settings->setHeightBlending(Unigine::Landscape::BLENDING_MODE::ALPHA_BLEND);
	map_file_settings->setEnabledOpacityHeight(false);

	// Канал маски 0 (базовый) включается
	map_file_settings->setEnabledMask(0, true);
	map_file_settings->setMaskBlending(0, Unigine::Landscape::BLENDING_MODE::ALPHA_BLEND);
	map_file_settings->setEnabledOpacityMask(0, false);

	// Канал маски 1 (трава) включается
	map_file_settings->setEnabledMask(1, true);
	map_file_settings->setMaskBlending(1, Unigine::Landscape::BLENDING_MODE::ALPHA_BLEND);
	map_file_settings->setEnabledOpacityMask(1, false);

	// Канал маски 2 (камень) включается
	map_file_settings->setEnabledMask(2, true);
	map_file_settings->setMaskBlending(2, Unigine::Landscape::BLENDING_MODE::ALPHA_BLEND);
	map_file_settings->setEnabledOpacityMask(2, false);

	map_file_settings->apply();
}

// Объект terrain создаётся, карта слоя присоединяется с настроенными параметрами.
void CreateSample::create_landscape_objects()
{
	// Объект terrain создаётся и устанавливается активным
	auto terrain = ObjectLandscapeTerrain::create();
	terrain->setActiveTerrain(true);

	// Карта слоя создаётся как дочерний элемент terrain
	auto layer_map = LandscapeLayerMap::create();
	layer_map->setParent(terrain);
	layer_map->setPath("landscape_map.gen.lmap");
	layer_map->setHeightScale(terrain_height_scale);
	layer_map->setSize(Unigine::Math::Vec2(terrain_size));
	layer_map->setPosition(Vec3_zero);
}

// Данные тайла загружаются из исходных изображений и копируются в буферы изображений landscape.
void CreateSample::create_callback(const LandscapeMapFileCreatorPtr &creator, const LandscapeImagesPtr &images, int x, int y)
{
	// Линейный индекс тайла вычисляется из координат сетки
	int index = y * grid_size_param.get().x + x;
	ivec2 tile_resolution = resolution_param.get() / grid_size_param.get();

	// Исходные изображения загружаются для текущего тайла
	auto source_albedo = Image::create(albedo_images_param.get(index).get());
	auto source_height = Image::create(height_images_param.get(index).get());
	auto source_grass_mask = Image::create(grass_mask_images_param.get(index).get());
	auto source_stone_mask = Image::create(stone_mask_images_param.get(index).get());

	// Изображение albedo проверяется и копируется в буфер landscape
	if (source_albedo->getWidth() == tile_resolution.x && source_albedo->getHeight() == tile_resolution.y)
	{
		auto albedo = images->getAlbedo();
		albedo->create2D(source_albedo->getWidth(), source_albedo->getHeight(), source_albedo->getFormat());
		albedo->copy(source_albedo, 0, 0, 0, 0, source_albedo->getWidth(), source_albedo->getHeight());
	}
	else
		Log::error("Incorrect albedo tile image size\n");

	// Изображение высоты проверяется и копируется в буфер landscape
	if (source_height->getWidth() == tile_resolution.x && source_height->getHeight() == tile_resolution.y)
	{
		auto height = images->getHeight();
		height->create2D(source_height->getWidth(), source_height->getHeight(), source_height->getFormat());
		height->copy(source_height, 0, 0, 0, 0, source_height->getWidth(), source_height->getHeight());
	}
	else
		Log::error("Incorrect height tile image size\n");

	// Изображение маски создаётся с каналами RGBA для нескольких слоёв деталей
	auto masks = images->getMask(0);
	masks->create2D(source_albedo->getWidth(), source_albedo->getHeight(), Image::FORMAT_RGBA8);
	masks->setChannelInt(0, 255);	// Канал 0 устанавливается в полную непрозрачность (базовый слой)

	// Маска травы копируется в канал 1
	if (source_grass_mask->getWidth() == tile_resolution.x && source_grass_mask->getHeight() == tile_resolution.y)
		masks->copy(source_grass_mask, 1, 0);
	else
		Log::error("Incorrect grass mask tile image size\n");

	// Маска камня копируется в канал 2
	if (source_stone_mask->getWidth() == tile_resolution.x && source_stone_mask->getHeight() == tile_resolution.y)
		masks->copy(source_stone_mask, 2, 0);
	else
		Log::error("Incorrect stone mask tile image size\n");
}

// Окно примера создаётся с кнопкой Create и сетками превью изображений.
void CreateSample::init_gui()
{
	sample_description_window.createWindow();

	auto window = sample_description_window.getWindow();

	// Кнопка Create запускает генерацию terrain
	auto button = WidgetButton::create("Create");
	button->setWidth(200);
	button->setHeight(20);
	button->getEventClicked().connect(this, &CreateSample::create_button_callback);
	window->addChild(button, Gui::ALIGN_LEFT);

	// Сетки изображений отображают миниатюры исходных текстур
	add_image_grid(window, "Albedo", albedo_images_param);
	add_image_grid(window, "Height", height_images_param);
	add_image_grid(window, "Grass mask", grass_mask_images_param);
	add_image_grid(window, "Stone mask", stone_mask_images_param);


	window->arrange();
}

// Сетка миниатюр создаётся из исходных изображений для визуального превью.
void CreateSample::add_image_grid(const Unigine::WidgetPtr &parent, const char *title, decltype(albedo_images_param) &images)
{
	auto hbox = WidgetHBox::create(4, 4);
	parent->addChild(hbox, Gui::ALIGN_LEFT);
	auto label = WidgetLabel::create(title);
	hbox->addChild(label, Gui::ALIGN_LEFT);

	// Виджет сетки располагает миниатюры в рядах и столбцах, соответствующих раскладке тайлов
	auto grid = WidgetGridBox::create(grid_size_param.get().x, 4, 4);
	for (int i = 0; i < grid_size_param.get().y; ++i)
	{
		for (int j = 0; j < grid_size_param.get().x; ++j)
		{
			// Изображение загружается и изменяется в размере до миниатюры
			auto image = Image::create(images.get(grid_size_param.get().x * (grid_size_param.get().y - i - 1) + j).get());
			image->resize(64, 64);
			image->convertToFormat(Image::FORMAT_RGB8);
			image->flipY();
			auto sprite = WidgetSprite::create();
			sprite->setImage(image);
			grid->addChild(sprite);
		}
	}
	parent->addChild(grid, Gui::ALIGN_LEFT);
}


// Окно примера уничтожается.
void CreateSample::shutdown_gui()
{
	sample_description_window.shutdown();
}

// Terrain генерируется при клике по кнопке; дублирующее создание предотвращается.
void CreateSample::create_button_callback()
{
	if (created)
		return;

	create_landscape_map();
	create_landscape_objects();
	created = true;
}
