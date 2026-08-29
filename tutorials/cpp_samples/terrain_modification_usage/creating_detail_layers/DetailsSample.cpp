// Демонстрирует создание слоёв деталей terrain во время выполнения на ObjectLandscapeTerrain.
// Материалы деталей для травы, камня и снега создаются и применяются к каналам маски.
// Порядок рендеринга настраивается для правильного наслоения деталей (камень, трава, затем снежные шапки).

#include "DetailsSample.h"

REGISTER_COMPONENT(DetailsSample);

using namespace Unigine;
using namespace Math;

// Инициализируется GUI; ссылка на terrain получается из свойства.
void DetailsSample::init()
{
	init_gui();

	// Узел terrain приводится к ObjectLandscapeTerrain для доступа к маскам деталей
	terrain = static_ptr_cast<ObjectLandscapeTerrain>(terrain_param.get());
}

// Ресурсы GUI освобождаются.
void DetailsSample::shutdown()
{
	shutdown_gui();
}

// Деталь травы создаётся с трипланарным отображением на канале маски 1.
void DetailsSample::create_detail_grass()
{
	// Текстура загружается из свойства пути файла
	grass_texture = Texture::create();
	grass_texture->load(grass_texture_param.get());

	// Материал наследуется от базового материала деталей terrain
	grass_material
		= Materials::findManualMaterial("Unigine::landscape_terrain_detail_base")->inherit();
	grass_material->setState("triplanar", 1);	// Трипланарная проекция избегает растяжения UV на склонах
	grass_material->setParameterFloat("size", 5.0f);
	grass_material->setParameterFloat("albedo_opacity", 0.8f);
	grass_material->setParameterFloat4("albedo", {0.8f, 0.8f, 0.6f, 1.0f});
	grass_material->setTexture("albedo", grass_texture);
	grass_material->setParameterFloat("height_opacity", 0.0f);	// Без смещения по высоте

	// Деталь добавляется на канал маски 1
	auto grass_mask = terrain->getDetailMask(1);
	grass_mask->setName("Grass Mask");

	auto grass_detail = grass_mask->addDetail();
	grass_detail->setName("Grass Detail");
	grass_detail->setMaterial(grass_material);
}

// Деталь камня создаётся с трипланарным отображением на канале маски 2.
void DetailsSample::create_detail_stone()
{
	stone_texture = Texture::create();
	stone_texture->load(stone_texture_param.get());

	// Настройки материала похожи на траву, но с другим оттенком и масштабом
	stone_material
		= Materials::findManualMaterial("Unigine::landscape_terrain_detail_base")->inherit();
	stone_material->setState("triplanar", 1);
	stone_material->setParameterFloat("size", 4.0f);
	stone_material->setParameterFloat("albedo_opacity", 0.9f);
	stone_material->setParameterFloat4("albedo", {0.6f, 0.6f, 0.5f, 1.0f});
	stone_material->setTexture("albedo", stone_texture);
	stone_material->setParameterFloat("height_opacity", 0.0f);

	// Деталь добавляется на канал маски 2
	auto stone_mask = terrain->getDetailMask(2);
	stone_mask->setName("Stone Mask");

	auto stone_detail = stone_mask->addDetail();
	stone_detail->setName("Stone Detail");
	stone_detail->setMaterial(stone_material);
}

// Деталь снежной шапки появляется только выше определённой высоты terrain на канале маски 0.
void DetailsSample::create_detail_snow_cap()
{
	// Белый материал использует цвет albedo по умолчанию (без текстуры)
	snow_material
		= Materials::findManualMaterial("Unigine::landscape_terrain_detail_base")->inherit();
	snow_material->setParameterFloat("height_opacity", 0.0f);

	// Деталь добавляется на канал маски 0 (белая/базовая маска)
	auto white_mask = terrain->getDetailMask(0);
	white_mask->setName("White Mask");

	auto stone_detail = white_mask->addDetail();
	stone_detail->setName("Snow Cap Detail");
	stone_detail->setMaterial(snow_material);
	// Снег появляется только выше 100м с плавным переходом 30м
	stone_detail->setMinVisibleHeight(100.0f);
	stone_detail->setMinFadeHeight(30.0f);
}

// Порядок рендеринга меняется, чтобы снег рендерился последним (поверх других деталей).
void DetailsSample::set_detail_render_order()
{
	// Желаемый порядок рендеринга:
	// 1. камень (рендерится первым, может быть перекрыт)
	// 2. трава
	// 3. снежные шапки (рендерятся последними, перекрывают остальное на большой высоте)

	auto white_mask = terrain->getDetailMask(0);
	auto stone_mask = terrain->getDetailMask(2);
	// Обмен перемещает белую маску (снег) для рендеринга после маски камня
	white_mask->swapRenderOrder(stone_mask);
}

// Создаётся окно примера с кнопкой Create и превью текстур.
void DetailsSample::init_gui()
{
	sample_description_window.createWindow();

	auto window = sample_description_window.getWindow();
	auto create_details_button = WidgetButton::create("Create details");
	window->addChild(create_details_button);

	create_details_button->getEventClicked().connect(this, &DetailsSample::add_details_button_callback);

	// Превью текстур добавляются для травы и камня
	add_detail_properties(window, "Grass", grass_texture_param);
	add_detail_properties(window, "Stone", stone_texture_param);
}

// Групповой бокс с миниатюрой текстуры добавляется для указанного типа детали.
void DetailsSample::add_detail_properties(const Unigine::WidgetPtr &parent, const char *title,
	decltype(grass_texture_param) &texture)
{
	auto group_box = WidgetGroupBox::create(title, 4, 0);
	parent->addChild(group_box, Gui::ALIGN_LEFT);

	auto hbox = WidgetHBox::create();
	group_box->addChild(hbox, Gui::ALIGN_LEFT);
	auto label = WidgetLabel::create("Texture");
	label->setWidth(100);
	hbox->addChild(label, Gui::ALIGN_LEFT);

	// Изображение загружается и изменяется в размере для отображения миниатюры
	auto image = Image::create(texture.get());
	image->resize(64, 64);
	auto sprite = WidgetSprite::create();
	sprite->setImage(image);
	hbox->addChild(sprite, Gui::ALIGN_LEFT);
}

// Окно примера уничтожается.
void DetailsSample::shutdown_gui()
{
	sample_description_window.shutdown();
}

// Все слои деталей создаются при клике по кнопке; дублирующее создание предотвращается.
void DetailsSample::add_details_button_callback()
{
	if (created)
		return;

	create_detail_grass();
	create_detail_stone();
	create_detail_snow_cap();
	set_detail_render_order();
	created = true;
}
