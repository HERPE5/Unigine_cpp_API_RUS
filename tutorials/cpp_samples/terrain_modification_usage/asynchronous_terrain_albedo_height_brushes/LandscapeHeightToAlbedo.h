// Преобразует значения высоты terrain в цвета albedo с помощью текстуры градиента.
// Диапазон высоты отображается на координаты градиента для колоризации.
// Работает со всей landscape layer map, используя асинхронное рисование текстуры.

#pragma once
#include <UnigineComponentSystem.h>

// Применяет колоризацию на основе градиента к terrain в зависимости от значений высоты.
class LandscapeHeightToAlbedo : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(LandscapeHeightToAlbedo, Unigine::ComponentBase);
	COMPONENT_INIT(init);

	void enable();		// Подключает callback асинхронного рисования текстуры
	void disable();		// Отключает callback асинхронного рисования текстуры

	void setTarget(const Unigine::LandscapeLayerMapPtr &in_landscape_layer_map) { landscape_layer_map = in_landscape_layer_map; }	// Задаёт целевой landscape

	void setGradient(const Unigine::TexturePtr &in_gradient) { gradient = in_gradient; }	// Задаёт текстуру цветового градиента
	void setMinHeight(float in_min_height) { min_height = in_min_height; }					// Задаёт минимальную высоту для отображения
	void setMaxHeight(float in_max_height) { max_height = in_max_height; }					// Задаёт максимальную высоту для отображения

	void run();		// Запускает асинхронное преобразование высоты в albedo

private:
	void init();
	// Callback, вызываемый, когда буфер асинхронного рисования текстуры готов
	void texture_draw_callback(const Unigine::UGUID &guid, int id, const Unigine::LandscapeTexturesPtr &buffer, const Unigine::Math::ivec2 &coord, int data_mask);

	Unigine::LandscapeLayerMapPtr landscape_layer_map;		// Целевой landscape для преобразования
	Unigine::MaterialPtr material;							// Шейдерный материал для преобразования высоты в albedo

	Unigine::TexturePtr gradient;		// Текстура цветового градиента
	float min_height{ 0.0f };			// Высота, отображаемая на начало градиента
	float max_height{ 1.0f };			// Высота, отображаемая на конец градиента

	// Параметры, захваченные для каждой операции асинхронного рисования.
	struct DrawData
	{
		Unigine::TexturePtr gradient;	// Текстура градиента для этой операции
		float min_height;				// Минимальная высота для этой операции
		float max_height;				// Максимальная высота для этой операции

		DrawData(
			const Unigine::TexturePtr &gradient,
			float min_height,
			float max_height)
			: gradient{ gradient }
			, min_height{ min_height }
			, max_height{ max_height }
		{ }
	};
	Unigine::HashMap<int, DrawData> per_operation_draw_data;	// Ожидающие операции по ID

	Unigine::EventConnection callback_handle;	// Хэндл для события рисования текстуры
};
