// Интерактивный GUI для рисования по landscape с режимами albedo, высоты и градиента.
// Координирует несколько компонентов-художников и предоставляет визуализацию превью кисти.
// Поддерживает редактирование параметров в реальном времени с клавиатурными и мышиными сокращениями.

#pragma once

#include "LandscapeAlbedoPainter.h"
#include "LandscapeHeightPainter.h"
#include "LandscapeHeightToAlbedo.h"
#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>
#include <UniginePlayers.h>
#include <UnigineWidgets.h>
#include <UnigineDecals.h>

// Основной контроллер примера рисования по terrain с интерфейсом GUI с вкладками.
class PaintSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(PaintSample, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);


	// Ссылки на узлы компонентов-художников
	PROP_PARAM(Node, albedo_painter_param, "Albedo Painter");		// Узел с LandscapeAlbedoPainter
	PROP_PARAM(Node, height_painter_param, "Height Painter");		// Узел с LandscapeHeightPainter
	PROP_PARAM(Node, height_to_albedo_param, "Height To Albedo");	// Узел с LandscapeHeightToAlbedo

	PROP_PARAM(Node, landscape_layer_map_param, "Landscape Layer Map");	// Целевой слой terrain
	PROP_PARAM(Node, player_param, "Player");							// Камера для трассировки лучей

	// Массивы ресурсов для выбора кисти
	PROP_ARRAY(File, brush_textures_param, "Brush Textures");	// Доступные паттерны кисти
	PROP_ARRAY(File, brush_masks_param, "Brush Masks");			// Доступные маски кисти
	PROP_ARRAY(File, gradients_param, "Gradients");				// Доступные градиенты высоты-в-albedo

private:
	void init();
	void init_resources();		// Загружает текстуры кисти, маски и градиенты
	void update();
	void shutdown();

	Unigine::LandscapeLayerMapPtr landscape_layer_map;		// Целевой terrain для рисования
	Unigine::PlayerSpectatorPtr player;						// Камера для трассировки луча мыши
	Unigine::LandscapeFetchPtr landscape_fetch;				// Запрос пересечения с terrain
	Unigine::DecalOrthoPtr brush_decal;						// Визуальное превью кисти на terrain
	Unigine::MaterialPtr brush_decal_material;				// Материал для превью кисти
	Unigine::Input::MOUSE_HANDLE saved_mouse_handle{ Unigine::Input::MOUSE_HANDLE_GRAB };	// Исходный режим мыши

	// Выбор режима рисования.
	enum class Mode
	{
		AlbedoPainter,		// Рисование albedo кистью
		HeightPainter,		// Скульптинг высоты кистью
		HeightToAlbedo		// Колоризация на основе градиента
	};
	Mode mode{ Mode::AlbedoPainter };	// Текущий активный режим рисования
	void set_mode(Mode mode);			// Переключает между режимами рисования

	// Ссылки на компоненты-художники
	LandscapeAlbedoPainter *albedo_painter{ nullptr };		// Компонент рисования albedo
	LandscapeHeightPainter *height_painter{ nullptr };		// Компонент рисования высоты
	LandscapeHeightToAlbedo *height_to_albedo{ nullptr };	// Компонент высоты-в-albedo

	// Загруженные ресурсы текстур
	Unigine::Vector<Unigine::TexturePtr> brush_textures;	// Паттерны кисти в полном разрешении
	Unigine::Vector<Unigine::TexturePtr> brush_masks;		// Маски кисти в полном разрешении
	Unigine::Vector<Unigine::TexturePtr> gradients;			// Градиенты в полном разрешении

	// Изображения-иконки GUI (уменьшенные из текстур)
	Unigine::Vector<Unigine::ImagePtr> brush_textures_icons;	// Миниатюры текстур кисти
	Unigine::Vector<Unigine::ImagePtr> brush_masks_icons;		// Миниатюры масок кисти
	Unigine::Vector<Unigine::ImagePtr> gradiends_icons;			// Миниатюры градиентов

	// Сеттеры параметров с опциональной синхронизацией GUI
	void set_brush_texture(const Unigine::TexturePtr &brush_texture);		// Задаёт текущий паттерн кисти
	void set_brush_mask(const Unigine::TexturePtr &brush_mask);				// Задаёт текущую маску кисти
	void set_gradient(const Unigine::TexturePtr &gradient);					// Задаёт градиент высоты-в-albedo
	void set_brush_size(float brush_size, bool update_ui = true);			// Задаёт диаметр кисти
	void set_brush_spacing(float brush_spacing, bool update_ui = true);		// Задаёт интервал мазков
	void set_brush_angle(float brush_angle, bool update_ui = true);			// Задаёт поворот кисти
	void set_brush_height(float brush_height, bool update_ui = true);		// Задаёт целевое значение высоты
	void set_brush_height_scale(float brush_height_scale, bool update_ui = true);	// Задаёт масштаб высоты
	void set_brush_opacity(float brush_opacity, bool update_ui = true);		// Задаёт непрозрачность кисти
	void set_brush_color(const Unigine::Math::vec3 &brush_color, bool update_ui = true);	// Задаёт цвет кисти
	void set_height_blend_mode(BlendMode blend_mode, bool update_ui = true);	// Задаёт режим альфа/аддитив
	void set_min_height(float min_height, bool update_ui = true);			// Задаёт минимальную высоту градиента
	void set_max_height(float max_height, bool update_ui = true);			// Задаёт максимальную высоту градиента

	// Текущие значения параметров кисти
	Unigine::TexturePtr brush_texture;					// Активная текстура-паттерн кисти
	Unigine::TexturePtr brush_mask;						// Активная текстура маски кисти
	Unigine::TexturePtr gradient;						// Активная текстура градиента
	float brush_size{ 100.0f };							// Диаметр кисти в мировых единицах
	float brush_spacing{ 0.2f };						// Интервал мазков как доля размера
	float brush_angle{ 0.0f };							// Поворот кисти в градусах
	float brush_height{ 0.0f };							// Целевая высота terrain
	float brush_height_scale{ 0.5f };					// Множитель текстуры высоты
	float brush_opacity{ 1.0f };						// Общий множитель непрозрачности
	Unigine::Math::vec3 brush_color{ 1.0f, 1.0f, 1.0f };	// RGB-цвет кисти
	BlendMode blend_mode{ BlendMode::Alpha };			// Режим смешивания высоты
	float min_height{ 0.0f };							// Минимум отображения градиента
	float max_height{ 1.0f };							// Максимум отображения градиента


	// Инициализация и очистка GUI
	void init_gui();		// Создаёт интерфейс с вкладками и элементами управления параметрами
	void shutdown_gui();	// Освобождает ресурсы GUI

	Unigine::WidgetWindowPtr window;		// Главное окно примера
	Unigine::WidgetTabBoxPtr tab_box;		// Вкладки выбора режима

	// Виджеты вкладки Albedo Painter
	Unigine::WidgetEditLinePtr albedo_brush_size_edit_line;			// Ввод размера кисти
	Unigine::WidgetEditLinePtr albedo_brush_spacing_edit_line;		// Ввод интервала кисти
	Unigine::WidgetEditLinePtr albedo_brush_angle_edit_line;		// Ввод угла кисти
	Unigine::WidgetEditLinePtr albedo_brush_opacity_edit_line;		// Ввод непрозрачности кисти
	Unigine::WidgetEditLinePtr albedo_brush_color_r_edit_line;		// Красный канал цвета
	Unigine::WidgetEditLinePtr albedo_brush_color_g_edit_line;		// Зелёный канал цвета
	Unigine::WidgetEditLinePtr albedo_brush_color_b_edit_line;		// Синий канал цвета

	// Виджеты вкладки Height Painter
	Unigine::WidgetEditLinePtr height_brush_size_edit_line;			// Ввод размера кисти
	Unigine::WidgetEditLinePtr height_brush_spacing_edit_line;		// Ввод интервала кисти
	Unigine::WidgetEditLinePtr height_brush_angle_edit_line;		// Ввод угла кисти
	Unigine::WidgetEditLinePtr height_brush_opacity_edit_line;		// Ввод непрозрачности кисти
	Unigine::WidgetEditLinePtr height_brush_height_edit_line;		// Ввод целевой высоты
	Unigine::WidgetEditLinePtr height_brush_height_scale_edit_line;	// Ввод масштаба высоты
	Unigine::WidgetComboBoxPtr height_blend_mode_combo_box;			// Селектор альфа/аддитив

	// Виджеты вкладки Height-To-Albedo
	Unigine::WidgetEditLinePtr min_height_edit_line;	// Минимальная высота градиента
	Unigine::WidgetEditLinePtr max_height_edit_line;	// Максимальная высота градиента

	SampleDescriptionWindow sample_description_window;	// Переиспользуемый компонент окна

	// Callback'и событий GUI
	void tab_box_callback();											// Обрабатывает выбор вкладки
	void brush_texture_button_callback(int index);						// Обрабатывает выбор текстуры
	void brush_mask_button_callback(int index);							// Обрабатывает выбор маски
	void gradient_button_callback(int index);							// Обрабатывает выбор градиента
	void brush_size_edit_line_callback(const Unigine::WidgetPtr &widget);		// Обрабатывает изменение размера
	void brush_spacing_edit_line_callback(const Unigine::WidgetPtr &widget);	// Обрабатывает изменение интервала
	void brush_angle_edit_line_callback(const Unigine::WidgetPtr &widget);		// Обрабатывает изменение угла
	void brush_height_edit_line_callback(const Unigine::WidgetPtr &widget);		// Обрабатывает изменение высоты
	void brush_height_scale_edit_line_callback(const Unigine::WidgetPtr &widget);	// Обрабатывает изменение масштаба
	void brush_opacity_edit_line_callback(const Unigine::WidgetPtr &widget);	// Обрабатывает изменение непрозрачности
	void brush_color_r_edit_line_callback(const Unigine::WidgetPtr &widget);	// Обрабатывает красный канал
	void brush_color_g_edit_line_callback(const Unigine::WidgetPtr &widget);	// Обрабатывает зелёный канал
	void brush_color_b_edit_line_callback(const Unigine::WidgetPtr &widget);	// Обрабатывает синий канал
	void blend_mode_combo_box_callback(const Unigine::WidgetPtr &widget);		// Обрабатывает режим смешивания
	void min_height_edit_line_callback(const Unigine::WidgetPtr &widget);		// Обрабатывает минимальную высоту
	void max_height_edit_line_callback(const Unigine::WidgetPtr &widget);		// Обрабатывает максимальную высоту
	void height_to_albedo_run_button_callback();								// Запускает преобразование

	// Хэндлы соединений событий для управления callback'ами
	Unigine::EventConnection albedo_brush_size_edit_line_callback;
	Unigine::EventConnection height_brush_size_edit_line_callback;
	Unigine::EventConnection albedo_brush_spacing_edit_line_callback;
	Unigine::EventConnection height_brush_spacing_edit_line_callback;
	Unigine::EventConnection albedo_brush_angle_edit_line_callback;
	Unigine::EventConnection height_brush_angle_edit_line_callback;
	Unigine::EventConnection height_brush_height_edit_line_callback;
	Unigine::EventConnection height_brush_height_scale_edit_line_callback;
	Unigine::EventConnection albedo_brush_opacity_edit_line_callback;
	Unigine::EventConnection height_brush_opacity_edit_line_callback;
	Unigine::EventConnection albedo_brush_color_r_edit_line_callback;
	Unigine::EventConnection albedo_brush_color_g_edit_line_callback;
	Unigine::EventConnection albedo_brush_color_b_edit_line_callback;
	Unigine::EventConnection height_blend_mode_combo_box_callback;
	Unigine::EventConnection min_height_edit_line_callback_;
	Unigine::EventConnection max_height_edit_line_callback_;

};
