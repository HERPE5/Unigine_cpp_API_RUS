// Рисует значения высоты на terrain с помощью настраиваемых мазков кисти.
// Поддерживает альфа- и аддитивный режимы смешивания для скульптинга terrain.
// Мазки кисти применяются через асинхронное рисование текстуры с GPU-шейдером.

#pragma once
#include <UnigineComponentSystem.h>

// Выбор режима смешивания рисования высоты.
enum class BlendMode
{
	Alpha = 0,		// Заменяет значения высоты высотой кисти
	Additive = 1	// Добавляет высоту кисти к существующей высоте terrain
};

// Применяет рисование высоты кистью к landscape layer map.
class LandscapeHeightPainter : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(LandscapeHeightPainter, Unigine::ComponentBase);
	COMPONENT_INIT(init);

	void enable();		// Подключает callback асинхронного рисования текстуры
	void disable();		// Отключает callback асинхронного рисования текстуры

	void setTarget(const Unigine::LandscapeLayerMapPtr &in_landscape_layer_map) { landscape_layer_map = in_landscape_layer_map; }	// Задаёт целевой landscape

	void setBlendMode(BlendMode in_blend_mode) { blend_mode = in_blend_mode; }							// Задаёт режим смешивания высоты
	void setBrushTexture(const Unigine::TexturePtr &in_brush_texture) { brush_texture = in_brush_texture; }		// Задаёт текстуру-паттерн кисти
	void setBrushMask(const Unigine::TexturePtr &in_brush_mask) { brush_mask = in_brush_mask; }					// Задаёт маску непрозрачности кисти
	void setBrushSize(float in_brush_size) { brush_size = in_brush_size; }										// Задаёт диаметр кисти в мировых единицах
	void setBrushSpacing(float in_brush_spacing) { brush_spacing = in_brush_spacing; }							// Задаёт интервал мазков как долю размера
	void setBrushAngle(float in_brush_angle) { brush_angle = in_brush_angle; }									// Задаёт угол поворота кисти в градусах
	void setBrushOpacity(float in_brush_opacity) { brush_opacity = in_brush_opacity; }							// Задаёт множитель непрозрачности кисти
	void setBrushHeight(float in_brush_height) { brush_height = in_brush_height; }								// Задаёт целевое значение высоты
	void setBrushHeightScale(float in_brush_height_scale) { brush_height_scale = in_brush_height_scale; }		// Задаёт коэффициент масштаба текстуры высоты

	void paintAt(const Unigine::Math::Vec3 &world_position);	// Применяет мазок кисти в мировой позиции

private:
	void init();
	// Callback, вызываемый, когда буфер асинхронного рисования текстуры готов
	void texture_draw_callback(const Unigine::UGUID &guid, int id, const Unigine::LandscapeTexturesPtr &buffer, const Unigine::Math::ivec2 &coord, int data_mask);

	Unigine::MaterialPtr brush_material;			// Шейдерный материал для рендеринга кисти
	Unigine::Math::Vec3 last_paint_position;		// Предыдущая позиция мазка для интервала

	Unigine::LandscapeLayerMapPtr landscape_layer_map;	// Целевой landscape для рисования

	// Параметры кисти
	BlendMode blend_mode{ BlendMode::Alpha };			// Альфа- или аддитивное смешивание высоты
	Unigine::TexturePtr brush_texture;					// Текстура-паттерн для формы кисти
	Unigine::TexturePtr brush_mask;						// Маска непрозрачности для затухания кисти
	float brush_size{ 1.0f };							// Диаметр кисти в мировых единицах
	float brush_spacing{ 0.2f };						// Интервал мазков как доля размера
	float brush_angle{ 0.0f };							// Поворот кисти в градусах
	float brush_opacity{ 1.0f };						// Общий множитель непрозрачности
	float brush_height{ 0.0f };							// Целевое значение высоты terrain
	float brush_height_scale{ 1.0f };					// Множитель для высоты текстуры кисти

	// Параметры, захваченные для каждой операции асинхронного рисования.
	struct DrawData
	{
		BlendMode blend_mode;					// Режим смешивания для этой операции
		Unigine::TexturePtr brush_texture;		// Паттерн кисти для этой операции
		Unigine::TexturePtr brush_mask;			// Маска кисти для этой операции
		float brush_angle;						// Угол поворота для этой операции
		float brush_opacity;					// Непрозрачность для этой операции
		float brush_height;						// Значение высоты для этой операции
		float brush_height_scale;				// Масштаб высоты для этой операции

		DrawData(
			BlendMode blend_mode,
			const Unigine::TexturePtr &brush_texture,
			const Unigine::TexturePtr &brush_mask,
			float brush_angle,
			float brush_opacity,
			float brush_height,
			float brush_height_scale)
			: blend_mode{ blend_mode }
			, brush_texture{ brush_texture }
			, brush_mask{ brush_mask }
			, brush_angle{ brush_angle }
			, brush_opacity{ brush_opacity }
			, brush_height{ brush_height }
			, brush_height_scale{ brush_height_scale }
		{ }
	};
	Unigine::HashMap<int, DrawData> per_operation_draw_data;	// Ожидающие операции по ID

	Unigine::EventConnection callback_handle;	// Хэндл для события рисования текстуры
};
