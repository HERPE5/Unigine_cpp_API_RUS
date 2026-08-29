// Интерактивный GUI для рисования по landscape с режимами albedo, высоты и градиента.
// Координирует несколько компонентов-художников и предоставляет визуализацию превью кисти.
// Поддерживает редактирование параметров в реальном времени с клавиатурными и мышиными сокращениями.

#include "PaintSample.h"

REGISTER_COMPONENT(PaintSample);

using namespace Unigine;
using namespace Math;

// Получаются компоненты; создаётся декаль превью кисти; инициализируется GUI.
void PaintSample::init()
{
	// Режим обработки мыши сохраняется и переключается в пользовательский режим
	saved_mouse_handle = ControlsApp::getMouseHandle();
	ControlsApp::setMouseHandle(Input::MOUSE_HANDLE_USER);

	// Компоненты-художники получаются из ссылочных узлов
	albedo_painter = getComponent<LandscapeAlbedoPainter>(albedo_painter_param);
	height_painter = getComponent<LandscapeHeightPainter>(height_painter_param);
	height_to_albedo = getComponent<LandscapeHeightToAlbedo>(height_to_albedo_param);

	// Инициализируются камера игрока и запрос landscape
	player = static_ptr_cast<PlayerSpectator>(player_param.get());
	landscape_fetch = LandscapeFetch::create();

	// Загружается материал декали превью кисти
	auto guid = FileSystem::getGUID(
		FileSystem::resolvePartialVirtualPath("decal_brush_base.basemat"));
	if (!guid.isValid())
	{
		Log::warning("PaintSample::init(): can not find \"decal_brush_base.basemat\" material\n");
		return;
	}

	// Декаль превью кисти создаётся с унаследованным материалом
	brush_decal_material = Materials::findMaterialByFileGUID(guid)->inherit();
	brush_decal = DecalOrtho::create();
	brush_decal->setRadius(100.0f);
	brush_decal->setWidth(1.0f);
	brush_decal->setHeight(1.0f);
	brush_decal->setMaterial(brush_decal_material);

	// Инициализируются ресурсы и GUI
	init_resources();
	init_gui();

	// Landscape layer map назначается всем художникам
	landscape_layer_map = static_ptr_cast<LandscapeLayerMap>(landscape_layer_map_param.get());
	albedo_painter->setTarget(landscape_layer_map);
	height_painter->setTarget(landscape_layer_map);
	height_to_albedo->setTarget(landscape_layer_map);

	// Начальные значения параметров применяются ко всем художникам
	set_mode(mode);
	set_brush_texture(brush_textures[0]);
	set_brush_mask(brush_masks[0]);
	set_gradient(gradients[0]);
	set_brush_size(brush_size);
	set_brush_spacing(brush_spacing);
	set_brush_angle(brush_angle);
	set_brush_height(brush_height);
	set_brush_height_scale(brush_height_scale);
	set_brush_opacity(brush_opacity);
	set_brush_color(brush_color);
	set_height_blend_mode(blend_mode);
	set_min_height(min_height);
	set_max_height(max_height);
}

// Загружаются текстуры кисти, маски и градиенты с миниатюрами для GUI.
void PaintSample::init_resources()
{
	// Загружаются текстуры-паттерны кисти, создаются миниатюры
	for (int i = 0; i < brush_textures_param.size(); ++i)
	{
		auto image = Image::create();
		image->load(brush_textures_param[i]);

		auto texture = Texture::create();
		texture->create(image);
		brush_textures.push_back(texture);

		// Миниатюра создаётся изменением размера изображения
		image->resize(32, 32);
		brush_textures_icons.push_back(image);
	}

	// Загружаются текстуры масок кисти, создаются миниатюры
	for (int i = 0; i < brush_masks_param.size(); ++i)
	{
		auto image = Image::create();
		image->load(brush_masks_param[i]);

		auto texture = Texture::create();
		texture->create(image);
		brush_masks.push_back(texture);

		// Миниатюра создаётся изменением размера изображения
		image->resize(32, 32);
		brush_masks_icons.push_back(image);
	}

	// Загружаются текстуры градиентов, создаются миниатюры
	for (int i = 0; i < gradients_param.size(); ++i)
	{
		auto image = Image::create();
		image->load(gradients_param[i]);

		auto texture = Texture::create();
		texture->create(image);
		gradients.push_back(texture);

		// Миниатюра градиента сохраняет соотношение сторон
		image->resize(32, 128);
		gradiends_icons.push_back(image);
	}
}

// Обрабатывается ввод; обновляется превью кисти; рисование запускается по клику.
void PaintSample::update()
{
	// Ввод игнорируется, когда мышь находится над окном
	if (window->getMouseX() >= 0 && window->getMouseX() < window->getWidth() && window->getMouseY() >= 0 && window->getMouseY() < window->getHeight())
	{
		return;
	}

	// Вращение камеры управляется правой кнопкой мыши
	if (Input::isMouseButtonPressed(Input::MOUSE_BUTTON::MOUSE_BUTTON_RIGHT))
	{
		vec2 delta = vec2(Input::getMouseDeltaPosition()) * 0.2f;
		player->setPhiAngle(player->getPhiAngle() + delta.x);
		player->setThetaAngle(player->getThetaAngle() + delta.y);
	}

	// Угол кисти настраивается Shift + колесо мыши
	if (Input::isKeyPressed(Input::KEY_LEFT_SHIFT) || Input::isKeyPressed(Input::KEY_RIGHT_SHIFT))
		set_brush_angle(brush_angle + Input::getMouseWheel() * 5);
	// Размер кисти настраивается Ctrl + колесо мыши
	else if (Input::isKeyPressed(Input::KEY_LEFT_CTRL) || Input::isKeyPressed(Input::KEY_RIGHT_CTRL))
		set_brush_size(brush_size + Input::getMouseWheel() * 0.5f);

	// Режимы рисования кистью требуют пересечения с terrain
	if (mode == Mode::AlbedoPainter || mode == Mode::HeightPainter)
	{
		// Луч пускается от камеры через позицию мыши
		const auto mouse_coord = Input::getMousePosition();
		bool fetched = landscape_fetch->intersectionForce(player->getPosition(),
			player->getPosition() + Vec3(player->getDirectionFromMainWindow(mouse_coord.x, mouse_coord.y)) * 10000.0);

		if (fetched)
		{
			// Декаль превью кисти позиционируется над terrain
			brush_decal->setPosition(landscape_fetch->getPosition() + Vec3(0.0, 0.0, 50.0));

			// Мазок рисования применяется по левой кнопке мыши
			if (Input::isMouseButtonPressed(Input::MOUSE_BUTTON::MOUSE_BUTTON_LEFT))
			{
				switch (mode)
				{
					case Mode::AlbedoPainter:
						albedo_painter->paintAt(landscape_fetch->getPosition());
						break;
					case Mode::HeightPainter:
						height_painter->paintAt(landscape_fetch->getPosition());
						break;
					default: break;
				}
			}
		}
	}
}

// Все художники отключаются; обработка мыши восстанавливается; GUI освобождается.
void PaintSample::shutdown()
{
	// Отключаются все callback'и художников
	albedo_painter->disable();
	height_painter->disable();
	height_to_albedo->disable();

	// Восстанавливается исходный режим обработки мыши
	ControlsApp::setMouseHandle(saved_mouse_handle);

	shutdown_gui();
}

// Переключается активный режим рисования; включается соответствующий художник.
void PaintSample::set_mode(Mode in_mode)
{
	mode = in_mode;

	// Включается только выбранный художник; остальные отключаются
	switch (mode)
	{
		case PaintSample::Mode::AlbedoPainter:
			albedo_painter->enable();
			height_painter->disable();
			height_to_albedo->disable();
			brush_decal->setEnabled(true);
			tab_box->setCurrentTab(0);
			break;
		case PaintSample::Mode::HeightPainter:
			albedo_painter->disable();
			height_painter->enable();
			height_to_albedo->disable();
			brush_decal->setEnabled(true);
			tab_box->setCurrentTab(1);
			break;
		case PaintSample::Mode::HeightToAlbedo:
			albedo_painter->disable();
			height_painter->disable();
			height_to_albedo->enable();
			brush_decal->setEnabled(false);		// Превью кисти не нужно
			tab_box->setCurrentTab(2);
			break;
		default:
			albedo_painter->disable();
			height_painter->disable();
			height_to_albedo->disable();
			brush_decal->setEnabled(false);
			break;
	}
}

// Текстура-паттерн кисти применяется к обоим художникам и превью-декали.
void PaintSample::set_brush_texture(const Unigine::TexturePtr &in_brush_texture)
{
	brush_texture = in_brush_texture;

	// Оба художника на основе кисти получают текстуру
	albedo_painter->setBrushTexture(in_brush_texture);
	height_painter->setBrushTexture(in_brush_texture);

	// Декаль превью кисти обновляется
	brush_decal_material->setTexture("albedo", brush_texture);
}

// Текстура маски кисти применяется к обоим художникам и превью-декали.
void PaintSample::set_brush_mask(const Unigine::TexturePtr &in_brush_mask)
{
	brush_mask = in_brush_mask;

	// Оба художника на основе кисти получают маску
	albedo_painter->setBrushMask(in_brush_mask);
	height_painter->setBrushMask(in_brush_mask);

	// Декаль превью кисти обновляется
	brush_decal_material->setTexture("mask", brush_mask);
}

// Текстура градиента применяется к конвертеру высоты-в-albedo.
void PaintSample::set_gradient(const Unigine::TexturePtr &in_gradient)
{
	gradient = in_gradient;

	height_to_albedo->setGradient(gradient);
}

// Размер кисти применяется к художникам и превью-декали с опциональной синхронизацией GUI.
void PaintSample::set_brush_size(float in_brush_size, bool update_ui)
{
	// Обеспечивается минимальный размер
	brush_size = max(in_brush_size, 1.0f);

	// Оба художника на основе кисти получают размер
	albedo_painter->setBrushSize(brush_size);
	height_painter->setBrushSize(brush_size);

	// Размер декали превью кисти изменяется
	brush_decal->setWidth(brush_size);
	brush_decal->setHeight(brush_size);

	// Поля ввода GUI синхронизируются при запросе
	if (update_ui)
	{
		// Callback временно отключается во избежание рекурсии
		albedo_brush_size_edit_line_callback.disconnect();
		albedo_brush_size_edit_line->setText(String::ftoa(brush_size));
		albedo_brush_size_edit_line->getEventChanged().connect(
			albedo_brush_size_edit_line_callback, this, &PaintSample::brush_size_edit_line_callback);

		height_brush_size_edit_line_callback.disconnect();
		height_brush_size_edit_line->setText(String::ftoa(brush_size));
		height_brush_size_edit_line->getEventChanged().connect(
			height_brush_size_edit_line_callback, this, &PaintSample::brush_size_edit_line_callback);
	}
}

// Интервал кисти применяется к обоим художникам с опциональной синхронизацией GUI.
void PaintSample::set_brush_spacing(float in_brush_spacing, bool update_ui)
{
	// Обеспечивается минимальный интервал
	brush_spacing = max(in_brush_spacing, 0.0f);

	// Оба художника на основе кисти получают интервал
	albedo_painter->setBrushSpacing(brush_spacing);
	height_painter->setBrushSpacing(brush_spacing);

	// Поля ввода GUI синхронизируются при запросе
	if (update_ui)
	{
		albedo_brush_spacing_edit_line_callback.disconnect();
		albedo_brush_spacing_edit_line->setText(String::ftoa(brush_spacing));
		albedo_brush_spacing_edit_line->getEventChanged().connect(
			albedo_brush_spacing_edit_line_callback, this, &PaintSample::brush_spacing_edit_line_callback);

		height_brush_spacing_edit_line_callback.disconnect();
		height_brush_spacing_edit_line->setText(String::ftoa(brush_spacing));
		height_brush_spacing_edit_line->getEventChanged().connect(
			height_brush_spacing_edit_line_callback, this, &PaintSample::brush_spacing_edit_line_callback);
	}
}

// Угол кисти применяется к художникам и превью-декали с опциональной синхронизацией GUI.
void PaintSample::set_brush_angle(float in_brush_angle, bool update_ui)
{
	brush_angle = in_brush_angle;

	// Оба художника на основе кисти получают угол
	albedo_painter->setBrushAngle(brush_angle);
	height_painter->setBrushAngle(brush_angle);

	// Поворот декали превью кисти обновляется (инвертирован для визуального соответствия)
	brush_decal->setRotation(quat(0.0f, 0.0f, -brush_angle), true);

	// Поля ввода GUI синхронизируются при запросе
	if (update_ui)
	{
		albedo_brush_angle_edit_line_callback.disconnect();
		albedo_brush_angle_edit_line->setText(String::ftoa(brush_angle));
		albedo_brush_angle_edit_line->getEventChanged().connect(
			albedo_brush_angle_edit_line_callback, this, &PaintSample::brush_angle_edit_line_callback);

		height_brush_angle_edit_line_callback.disconnect();
		height_brush_angle_edit_line->setText(String::ftoa(brush_angle));
		height_brush_angle_edit_line->getEventChanged().connect(
			height_brush_angle_edit_line_callback, this, &PaintSample::brush_angle_edit_line_callback);
	}
}

// Значение высоты кисти применяется к художнику высоты с опциональной синхронизацией GUI.
void PaintSample::set_brush_height(float in_brush_height, bool update_ui)
{
	brush_height = in_brush_height;

	// Только художник высоты использует этот параметр
	height_painter->setBrushHeight(in_brush_height);

	// Поле ввода GUI синхронизируется при запросе
	if (update_ui)
	{
		height_brush_height_edit_line_callback.disconnect();
		height_brush_height_edit_line->setText(String::ftoa(brush_height));
		height_brush_height_edit_line->getEventChanged().connect(
			height_brush_height_edit_line_callback, this, &PaintSample::brush_height_edit_line_callback);
	}
}

// Масштаб высоты кисти применяется к художнику высоты с опциональной синхронизацией GUI.
void PaintSample::set_brush_height_scale(float in_brush_height_scale, bool update_ui)
{
	brush_height_scale = in_brush_height_scale;

	// Только художник высоты использует этот параметр
	height_painter->setBrushHeightScale(in_brush_height_scale);

	// Поле ввода GUI синхронизируется при запросе
	if (update_ui)
	{
		height_brush_height_scale_edit_line_callback.disconnect();
		height_brush_height_scale_edit_line->setText(String::ftoa(brush_height_scale));
		height_brush_height_scale_edit_line->getEventChanged().connect(
			height_brush_height_scale_edit_line_callback, this, &PaintSample::brush_height_scale_edit_line_callback);
	}
}

// Непрозрачность кисти применяется к обоим художникам с опциональной синхронизацией GUI.
void PaintSample::set_brush_opacity(float in_brush_opacity, bool update_ui)
{
	// Непрозрачность ограничивается допустимым диапазоном
	brush_opacity = clamp(in_brush_opacity, 0.0f, 1.0f);

	// Оба художника на основе кисти получают непрозрачность
	albedo_painter->setBrushOpacity(brush_opacity);
	height_painter->setBrushOpacity(brush_opacity);

	// Поля ввода GUI синхронизируются при запросе
	if (update_ui)
	{
		albedo_brush_opacity_edit_line_callback.disconnect();
		albedo_brush_opacity_edit_line->setText(String::ftoa(brush_opacity));
		albedo_brush_opacity_edit_line->getEventChanged().connect(
			albedo_brush_opacity_edit_line_callback, this, &PaintSample::brush_opacity_edit_line_callback);

		height_brush_opacity_edit_line_callback.disconnect();
		height_brush_opacity_edit_line->setText(String::ftoa(brush_opacity));
		height_brush_opacity_edit_line->getEventChanged().connect(
			height_brush_opacity_edit_line_callback, this, &PaintSample::brush_opacity_edit_line_callback);
	}
}

// Цвет кисти применяется к художнику albedo и превью-декали с опциональной синхронизацией GUI.
void PaintSample::set_brush_color(const Unigine::Math::vec3 &in_brush_color, bool update_ui)
{
	// Каналы цвета ограничиваются допустимым диапазоном
	brush_color = clamp(in_brush_color, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f});

	// Только художник albedo использует цвет кисти
	albedo_painter->setBrushColor(brush_color);

	// Цвет декали превью кисти обновляется
	brush_decal_material->setParameterFloat4("albedo", {brush_color, 1.0f});

	// Поля ввода GUI синхронизируются при запросе (отображаются как 0-255)
	if (update_ui)
	{
		albedo_brush_color_r_edit_line_callback.disconnect();
		albedo_brush_color_r_edit_line->setText(String::itoa(ftoi(brush_color.x * 255.0f)));
		albedo_brush_color_r_edit_line->getEventChanged().connect(
			albedo_brush_color_r_edit_line_callback, this, &PaintSample::brush_color_r_edit_line_callback);

		albedo_brush_color_g_edit_line_callback.disconnect();
		albedo_brush_color_g_edit_line->setText(String::itoa(ftoi(brush_color.y * 255.0f)));
		albedo_brush_color_g_edit_line->getEventChanged().connect(
			albedo_brush_color_g_edit_line_callback, this, &PaintSample::brush_color_g_edit_line_callback);

		albedo_brush_color_b_edit_line_callback.disconnect();
		albedo_brush_color_b_edit_line->setText(String::itoa(ftoi(brush_color.z * 255.0f)));
		albedo_brush_color_b_edit_line->getEventChanged().connect(
			albedo_brush_color_b_edit_line_callback, this, &PaintSample::brush_color_b_edit_line_callback);
	}
}

// Режим смешивания высоты применяется к художнику высоты с опциональной синхронизацией GUI.
void PaintSample::set_height_blend_mode(BlendMode in_blend_mode, bool update_ui)
{
	blend_mode = in_blend_mode;

	// Только художник высоты использует режим смешивания
	height_painter->setBlendMode(in_blend_mode);

	// Выпадающий список GUI синхронизируется при запросе
	if (update_ui)
	{
		height_blend_mode_combo_box_callback.disconnect();
		switch (blend_mode)
		{
			case BlendMode::Alpha: height_blend_mode_combo_box->setCurrentItem(0); break;
			case BlendMode::Additive: height_blend_mode_combo_box->setCurrentItem(1); break;
		}
		height_blend_mode_combo_box->getEventChanged().connect(
			height_blend_mode_combo_box_callback, this, &PaintSample::blend_mode_combo_box_callback);
	}
}

// Минимальная высота для отображения градиента применяется с опциональной синхронизацией GUI.
void PaintSample::set_min_height(float in_min_height, bool update_ui)
{
	min_height = in_min_height;

	// Только height-to-albedo использует этот параметр
	height_to_albedo->setMinHeight(min_height);

	// Поле ввода GUI синхронизируется при запросе
	if (update_ui)
	{
		min_height_edit_line_callback_.disconnect();
		min_height_edit_line->setText(String::ftoa(min_height));
		min_height_edit_line->getEventChanged().connect(
			min_height_edit_line_callback_, this, &PaintSample::min_height_edit_line_callback);
	}
}

// Максимальная высота для отображения градиента применяется с опциональной синхронизацией GUI.
void PaintSample::set_max_height(float in_max_height, bool update_ui)
{
	max_height = in_max_height;

	// Только height-to-albedo использует этот параметр
	height_to_albedo->setMaxHeight(max_height);

	// Поле ввода GUI синхронизируется при запросе
	if (update_ui)
	{
		max_height_edit_line_callback_.disconnect();
		max_height_edit_line->setText(String::ftoa(max_height));
		max_height_edit_line->getEventChanged().connect(
			max_height_edit_line_callback_, this, &PaintSample::max_height_edit_line_callback);
	}
}

// Создаётся GUI с вкладками и элементами управления параметрами для всех режимов рисования.
void PaintSample::init_gui()
{
	// Окно примера создаётся из переиспользуемого компонента
	sample_description_window.createWindow();

	auto parameters = sample_description_window.getParameterGroupBox();

	window = sample_description_window.getWindow();

	// Создаётся блок вкладок для выбора режима
	tab_box = WidgetTabBox::create();
	tab_box->getEventChanged().connect(this, &PaintSample::tab_box_callback);
	tab_box->addTab("Albedo Painter");

	auto hbox = WidgetHBox::create(5);
	tab_box->addChild(hbox, Gui::ALIGN_LEFT);
	auto label = WidgetLabel::create("Texture");
	hbox->addChild(label, Gui::ALIGN_LEFT);
	auto gridbox = WidgetGridBox::create(6);
	tab_box->addChild(gridbox, Gui::ALIGN_LEFT);
	for (int i = 0; i < brush_textures.size(); ++i)
	{
		auto button = WidgetButton::create();
		button->setImage(brush_textures_icons[i]);
		button->getEventClicked().connect(this, &PaintSample::brush_texture_button_callback, i);
		gridbox->addChild(button, Gui::ALIGN_LEFT);
	}

	hbox = WidgetHBox::create(5);
	tab_box->addChild(hbox, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Mask");
	hbox->addChild(label, Gui::ALIGN_LEFT);
	gridbox = WidgetGridBox::create(6);
	tab_box->addChild(gridbox, Gui::ALIGN_LEFT);
	for (int i = 0; i < brush_masks.size(); ++i)
	{
		auto button = WidgetButton::create();
		button->setImage(brush_masks_icons[i]);
		button->getEventClicked().connect(this, &PaintSample::brush_mask_button_callback, i);
		gridbox->addChild(button, Gui::ALIGN_LEFT);
	}

	hbox = WidgetHBox::create(5);
	tab_box->addChild(hbox, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Size");
	label->setWidth(100);
	hbox->addChild(label, Gui::ALIGN_LEFT);
	albedo_brush_size_edit_line = WidgetEditLine::create();
	albedo_brush_size_edit_line->setValidator(Gui::VALIDATOR_FLOAT);
	hbox->addChild(albedo_brush_size_edit_line, Gui::ALIGN_LEFT);

	hbox = WidgetHBox::create(5);
	tab_box->addChild(hbox, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Spacing");
	label->setWidth(100);
	hbox->addChild(label, Gui::ALIGN_LEFT);
	albedo_brush_spacing_edit_line = WidgetEditLine::create();
	albedo_brush_spacing_edit_line->setValidator(Gui::VALIDATOR_FLOAT);
	hbox->addChild(albedo_brush_spacing_edit_line, Gui::ALIGN_LEFT);

	hbox = WidgetHBox::create(5);
	tab_box->addChild(hbox, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Angle");
	label->setWidth(100);
	hbox->addChild(label, Gui::ALIGN_LEFT);
	albedo_brush_angle_edit_line = WidgetEditLine::create();
	albedo_brush_angle_edit_line->setValidator(Gui::VALIDATOR_FLOAT);
	hbox->addChild(albedo_brush_angle_edit_line, Gui::ALIGN_LEFT);

	hbox = WidgetHBox::create(5);
	tab_box->addChild(hbox, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Opacity");
	label->setWidth(100);
	hbox->addChild(label, Gui::ALIGN_LEFT);
	albedo_brush_opacity_edit_line = WidgetEditLine::create();
	albedo_brush_opacity_edit_line->setValidator(Gui::VALIDATOR_FLOAT);
	hbox->addChild(albedo_brush_opacity_edit_line, Gui::ALIGN_LEFT);

	hbox = WidgetHBox::create(5);
	tab_box->addChild(hbox, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Color");
	label->setWidth(100);
	hbox->addChild(label, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("R");
	hbox->addChild(label, Gui::ALIGN_LEFT);
	albedo_brush_color_r_edit_line = WidgetEditLine::create();
	albedo_brush_color_r_edit_line->setValidator(Gui::VALIDATOR_UINT);
	hbox->addChild(albedo_brush_color_r_edit_line, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("G");
	hbox->addChild(label, Gui::ALIGN_LEFT);
	albedo_brush_color_g_edit_line = WidgetEditLine::create();
	albedo_brush_color_g_edit_line->setValidator(Gui::VALIDATOR_UINT);
	hbox->addChild(albedo_brush_color_g_edit_line, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("B");
	hbox->addChild(label, Gui::ALIGN_LEFT);
	albedo_brush_color_b_edit_line = WidgetEditLine::create();
	albedo_brush_color_b_edit_line->setValidator(Gui::VALIDATOR_UINT);
	hbox->addChild(albedo_brush_color_b_edit_line, Gui::ALIGN_LEFT);


	tab_box->addTab("Height Painter");

	hbox = WidgetHBox::create(5);
	tab_box->addChild(hbox, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Texture");
	hbox->addChild(label, Gui::ALIGN_LEFT);
	gridbox = WidgetGridBox::create(6);
	tab_box->addChild(gridbox, Gui::ALIGN_LEFT);
	for (int i = 0; i < brush_textures.size(); ++i)
	{
		auto button = WidgetButton::create();
		button->setImage(brush_textures_icons[i]);
		button->getEventClicked().connect(this, &PaintSample::brush_texture_button_callback, i);
		gridbox->addChild(button, Gui::ALIGN_LEFT);
	}

	hbox = WidgetHBox::create(5);
	tab_box->addChild(hbox, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Mask");
	hbox->addChild(label, Gui::ALIGN_LEFT);
	gridbox = WidgetGridBox::create(6);
	tab_box->addChild(gridbox, Gui::ALIGN_LEFT);
	for (int i = 0; i < brush_masks.size(); ++i)
	{
		auto button = WidgetButton::create();
		button->setImage(brush_masks_icons[i]);
		button->getEventClicked().connect(this, &PaintSample::brush_mask_button_callback, i);
		gridbox->addChild(button, Gui::ALIGN_LEFT);
	}

	hbox = WidgetHBox::create(5);
	tab_box->addChild(hbox, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Size");
	label->setWidth(100);
	hbox->addChild(label, Gui::ALIGN_LEFT);
	height_brush_size_edit_line = WidgetEditLine::create();
	height_brush_size_edit_line->setValidator(Gui::VALIDATOR_FLOAT);
	hbox->addChild(height_brush_size_edit_line, Gui::ALIGN_LEFT);

	hbox = WidgetHBox::create(5);
	tab_box->addChild(hbox, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Spacing");
	label->setWidth(100);
	hbox->addChild(label, Gui::ALIGN_LEFT);
	height_brush_spacing_edit_line = WidgetEditLine::create();
	height_brush_spacing_edit_line->setValidator(Gui::VALIDATOR_FLOAT);
	hbox->addChild(height_brush_spacing_edit_line, Gui::ALIGN_LEFT);

	hbox = WidgetHBox::create(5);
	tab_box->addChild(hbox, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Angle");
	label->setWidth(100);
	hbox->addChild(label, Gui::ALIGN_LEFT);
	height_brush_angle_edit_line = WidgetEditLine::create();
	height_brush_angle_edit_line->setValidator(Gui::VALIDATOR_FLOAT);
	hbox->addChild(height_brush_angle_edit_line, Gui::ALIGN_LEFT);

	hbox = WidgetHBox::create(5);
	tab_box->addChild(hbox, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Opacity");
	label->setWidth(100);
	hbox->addChild(label, Gui::ALIGN_LEFT);
	height_brush_opacity_edit_line = WidgetEditLine::create();
	height_brush_opacity_edit_line->setValidator(Gui::VALIDATOR_FLOAT);
	hbox->addChild(height_brush_opacity_edit_line, Gui::ALIGN_LEFT);

	hbox = WidgetHBox::create(5);
	tab_box->addChild(hbox, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Height");
	label->setWidth(100);
	hbox->addChild(label, Gui::ALIGN_LEFT);
	height_brush_height_edit_line = WidgetEditLine::create();
	height_brush_height_edit_line->setValidator(Gui::VALIDATOR_FLOAT);
	hbox->addChild(height_brush_height_edit_line, Gui::ALIGN_LEFT);

	hbox = WidgetHBox::create(5);
	tab_box->addChild(hbox, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Height Scale");
	label->setWidth(100);
	hbox->addChild(label, Gui::ALIGN_LEFT);
	height_brush_height_scale_edit_line = WidgetEditLine::create();
	height_brush_height_scale_edit_line->setValidator(Gui::VALIDATOR_FLOAT);
	hbox->addChild(height_brush_height_scale_edit_line, Gui::ALIGN_LEFT);

	hbox = WidgetHBox::create(5);
	tab_box->addChild(hbox, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Blend Mode");
	label->setWidth(100);
	hbox->addChild(label, Gui::ALIGN_LEFT);
	height_blend_mode_combo_box = WidgetComboBox::create();
	height_blend_mode_combo_box->addItem("Alpha");
	height_blend_mode_combo_box->addItem("Additive");
	hbox->addChild(height_blend_mode_combo_box);


	tab_box->addTab("Height To Albedo");

	hbox = WidgetHBox::create(5);
	tab_box->addChild(hbox, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Min Height");
	label->setWidth(100);
	hbox->addChild(label, Gui::ALIGN_LEFT);
	min_height_edit_line = WidgetEditLine::create();
	min_height_edit_line->setValidator(Gui::VALIDATOR_FLOAT);
	hbox->addChild(min_height_edit_line, Gui::ALIGN_LEFT);

	hbox = WidgetHBox::create(5);
	tab_box->addChild(hbox, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Max Height");
	label->setWidth(100);
	hbox->addChild(label, Gui::ALIGN_LEFT);
	max_height_edit_line = WidgetEditLine::create();
	max_height_edit_line->setValidator(Gui::VALIDATOR_FLOAT);
	hbox->addChild(max_height_edit_line, Gui::ALIGN_LEFT);

	hbox = WidgetHBox::create(5);
	tab_box->addChild(hbox, Gui::ALIGN_LEFT);
	label = WidgetLabel::create("Gradient");
	hbox->addChild(label, Gui::ALIGN_LEFT);
	gridbox = WidgetGridBox::create(6);
	tab_box->addChild(gridbox, Gui::ALIGN_LEFT);
	for (int i = 0; i < gradients.size(); ++i)
	{
		auto button = WidgetButton::create();
		button->setImage(gradiends_icons[i]);
		button->getEventClicked().connect(this, &PaintSample::gradient_button_callback, i);
		gridbox->addChild(button, Gui::ALIGN_LEFT);
	}

	parameters->addChild(tab_box);
}

// Окно примера освобождается.
void PaintSample::shutdown_gui()
{
	sample_description_window.shutdown();
}

// =====================================================================
// CALLBACK'И GUI - обрабатывают взаимодействие пользователя с элементами управления
// =====================================================================

// Активный режим рисования переключается на основе выбранной вкладки.
void PaintSample::tab_box_callback()
{
	switch (tab_box->getCurrentTab())
	{
		case 0: set_mode(Mode::AlbedoPainter); break;
		case 1: set_mode(Mode::HeightPainter); break;
		case 2: set_mode(Mode::HeightToAlbedo); break;
	}
}

// Текстура кисти меняется на выбранный индекс.
void PaintSample::brush_texture_button_callback(int index)
{
	set_brush_texture(brush_textures[index]);
}

// Маска кисти меняется на выбранный индекс.
void PaintSample::brush_mask_button_callback(int index)
{
	set_brush_mask(brush_masks[index]);
}

// Градиент меняется, запускается преобразование высоты в albedo.
void PaintSample::gradient_button_callback(int index)
{
	set_gradient(gradients[index]);
	height_to_albedo->run();
}

// Размер кисти обновляется из текста поля ввода.
void PaintSample::brush_size_edit_line_callback(const Unigine::WidgetPtr &widget)
{
	float value = String::atof(static_ptr_cast<WidgetEditLine>(widget)->getText());
	set_brush_size(value, true);
}

// Интервал кисти обновляется из текста поля ввода.
void PaintSample::brush_spacing_edit_line_callback(const Unigine::WidgetPtr &widget)
{
	float value = String::atof(static_ptr_cast<WidgetEditLine>(widget)->getText());
	set_brush_spacing(value, false);
}

// Угол кисти обновляется из текста поля ввода.
void PaintSample::brush_angle_edit_line_callback(const Unigine::WidgetPtr &widget)
{
	float value = String::atof(static_ptr_cast<WidgetEditLine>(widget)->getText());
	set_brush_angle(value, false);
}

// Высота кисти обновляется из текста поля ввода.
void PaintSample::brush_height_edit_line_callback(const Unigine::WidgetPtr &widget)
{
	float value = String::atof(static_ptr_cast<WidgetEditLine>(widget)->getText());
	set_brush_height(value, false);
}

// Масштаб высоты кисти обновляется из текста поля ввода.
void PaintSample::brush_height_scale_edit_line_callback(const Unigine::WidgetPtr &widget)
{
	float value = String::atof(static_ptr_cast<WidgetEditLine>(widget)->getText());
	set_brush_height_scale(value, false);
}

// Непрозрачность кисти обновляется из текста поля ввода.
void PaintSample::brush_opacity_edit_line_callback(const Unigine::WidgetPtr &widget)
{
	float value = String::atof(static_ptr_cast<WidgetEditLine>(widget)->getText());
	set_brush_opacity(value, false);
}

// Красный канал цвета обновляется из текста поля ввода (из 0-255 в 0-1).
void PaintSample::brush_color_r_edit_line_callback(const Unigine::WidgetPtr &widget)
{
	float value = String::atof(static_ptr_cast<WidgetEditLine>(widget)->getText()) / 255.0f;
	set_brush_color({value, brush_color.y, brush_color.z}, false);
}

// Зелёный канал цвета обновляется из текста поля ввода (из 0-255 в 0-1).
void PaintSample::brush_color_g_edit_line_callback(const Unigine::WidgetPtr &widget)
{
	float value = String::atof(static_ptr_cast<WidgetEditLine>(widget)->getText()) / 255.0f;
	set_brush_color({brush_color.x, value, brush_color.z}, false);
}

// Синий канал цвета обновляется из текста поля ввода (из 0-255 в 0-1).
void PaintSample::brush_color_b_edit_line_callback(const Unigine::WidgetPtr &widget)
{
	float value = String::atof(static_ptr_cast<WidgetEditLine>(widget)->getText()) / 255.0f;
	set_brush_color({brush_color.x, brush_color.y, value}, false);
}

// Минимальная высота градиента обновляется из текста поля ввода.
void PaintSample::min_height_edit_line_callback(const Unigine::WidgetPtr &widget)
{
	float value = String::atof(static_ptr_cast<WidgetEditLine>(widget)->getText());
	set_min_height(value, false);
}

// Максимальная высота градиента обновляется из текста поля ввода.
void PaintSample::max_height_edit_line_callback(const Unigine::WidgetPtr &widget)
{
	float value = String::atof(static_ptr_cast<WidgetEditLine>(widget)->getText());
	set_max_height(value, false);
}

// Режим смешивания высоты обновляется из выбора в выпадающем списке.
void PaintSample::blend_mode_combo_box_callback(const Unigine::WidgetPtr &widget)
{
	switch (static_ptr_cast<WidgetComboBox>(widget)->getCurrentItem())
	{
		case 0: set_height_blend_mode(BlendMode::Alpha); break;
		case 1: set_height_blend_mode(BlendMode::Additive); break;
	}
}

// Преобразование высоты в albedo запускается вручную.
void PaintSample::height_to_albedo_run_button_callback()
{
	height_to_albedo->run();
}
