// Реализует рисование масок terrain с настраиваемыми параметрами кисти.
// Мазки кисти применяются к каналам маски LandscapeLayerMap через асинхронное рисование текстуры.
// Поддерживает настройку текстуры кисти, непрозрачности, поворота, интервала и цвета.

#include <UnigineComponentSystem.h>
#include <UnigineObjects.h>
#include <UnigineTextures.h>

#include <utility>

// Рисует данные маски на landscape terrain с помощью настраиваемых мазков кисти.
class LandscapeMaskPainter : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(LandscapeMaskPainter, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	PROP_PARAM(Node, clutter_param);	// Mesh clutter для инвалидации после рисования

	void enable();		// Подключает callback асинхронного рисования текстуры
	void disable();		// Отключает callback асинхронного рисования текстуры

	// Задаёт целевой landscape layer map для операций рисования.
	void setTarget(const Unigine::LandscapeLayerMapPtr &in_landscape_layer_map)
	{
		landscape_layer_map = in_landscape_layer_map;
	}

	// Задаёт паттерн текстуры кисти, используемый для мазков рисования.
	void setBrushTexture(const Unigine::TexturePtr &in_brush_texture)
	{
		brush_texture = in_brush_texture;
	}

	// Задаёт текстуру маски кисти для альфа-маскирования.
	void setBrushMask(const Unigine::TexturePtr &in_brush_texture)
	{
		brush_mask = in_brush_texture;
	}

	void setBrushSize(float in_brush_size) { brush_size = in_brush_size; }				// Диаметр кисти в мировых единицах
	void setBrushSpacing(float in_brush_spacing) { brush_spacing = in_brush_spacing; }	// Интервал между мазками как доля размера кисти
	void setBrushAngle(float in_brush_angle) { brush_angle = in_brush_angle; }			// Угол поворота кисти в градусах
	void setBrushOpacity(float in_brush_opacity) { brush_opacity = in_brush_opacity; }	// Непрозрачность кисти (от 0.0 до 1.0)
	void setBrushColor(const Unigine::Math::vec4 &in_brush_color) { brush_color = in_brush_color; }	// Множитель цвета кисти

	void paintAt(const Unigine::Math::Vec3 &world_position);	// Применяет мазок кисти в мировой позиции

private:
	void init();
	// Callback, вызываемый, когда асинхронное рисование текстуры готово к выполнению шейдера
	void texture_draw_callback(const Unigine::UGUID &guid, int id,
		const Unigine::LandscapeTexturesPtr &buffer, const Unigine::Math::ivec2 &coord,
		int data_mask);


private:
	Unigine::MaterialPtr brush_material = nullptr;		// Материал, используемый для прохода шейдера рендеринга кисти
	Unigine::Math::Vec3 last_paint_position{};			// Предыдущая позиция мазка для вычисления интервала

	Unigine::LandscapeLayerMapPtr landscape_layer_map = nullptr;	// Целевой landscape для рисования
	Unigine::TexturePtr brush_texture = nullptr;		// Текстура-паттерн кисти
	Unigine::TexturePtr brush_mask = nullptr;			// Текстура альфа-маски кисти

	float brush_size{1.0f};								// Диаметр кисти в мировых единицах
	float brush_spacing{0.2f};							// Интервал мазков как доля размера
	float brush_angle{0.0f};							// Поворот кисти в градусах
	Unigine::Math::vec4 brush_color{1.f, 1.f, 1.f, 1.f};	// Множитель цвета для кисти
	float brush_opacity{1.0f};							// Коэффициент непрозрачности кисти

	// Параметры, захваченные для каждой операции асинхронного рисования для отложенного выполнения шейдера.
	struct DrawData
	{
		Unigine::TexturePtr brush_texture = nullptr;	// Паттерн кисти для этого мазка
		Unigine::TexturePtr brush_mask = nullptr;		// Альфа-маска для этого мазка
		float brush_angle = 0.f;						// Угол поворота для этого мазка
		float brush_opacity = 0.f;						// Непрозрачность для этого мазка
		Unigine::Math::vec4 brush_color{};				// Цвет для этого мазка

		DrawData(Unigine::TexturePtr brush_texture, Unigine::TexturePtr brush_mask,
			float brush_angle, float brush_opacity, const Unigine::Math::vec4 &brush_color)
			: brush_texture{std::move(brush_texture)}
			, brush_mask{std::move(brush_mask)}
			, brush_angle{brush_angle}
			, brush_opacity{brush_opacity}
			, brush_color{brush_color}
		{}
	};

	Unigine::HashMap<int, DrawData> per_operation_draw_data;	// Ожидающие операции рисования по ID
	Unigine::EventConnection callback_handle{};					// Хэндл для события рисования текстуры

	Unigine::ObjectMeshClutterPtr clutter = nullptr;			// Clutter для обновления после рисования
};
