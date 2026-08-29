// Выполняет нарезку высоты (height slicing) на GPU для данных landscape terrain. Читает высоту
// из исходного LandscapeLayerMap и записывает изменённую высоту/albedo в целевой слой.
// Использует callback'и асинхронного рисования текстуры и конечный автомат для многокадровой обработки.

#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineObjects.h>

class HeightSlicer : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(HeightSlicer, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

	// Подключает callback рисования текстуры к системе Landscape
	void enable();
	// Отключает все callback'и
	void disable();

	void setSourceLmap(const Unigine::LandscapeLayerMapPtr &in_source_lmap);
	void setTargetLmap(const Unigine::LandscapeLayerMapPtr &in_target_lmap) { target_lmap = in_target_lmap; }
	// Задаёт нормализованный порог высоты (от 0.0 до 1.0)
	void setSliceHeight(float in_slice_height) { slice_height = in_slice_height; }

	// Запускает операцию нарезки (неблокирующая, управляемая конечным автоматом)
	void run();

private:
	void init();
	void update();
	// Callback, вызываемый Landscape::asyncTextureDraw, когда рендер готов
	void texture_draw_callback(const Unigine::UGUID &guid,
			int id, const Unigine::LandscapeTexturesPtr &buffer,
			const Unigine::Math::ivec2 &coord, int data_mask);
	// Список карт landscape для рендеринга
	Unigine::Vector<Unigine::LandscapeLayerMapPtr> maps;
	// Закэшированная текстура высоты из исходного слоя
	Unigine::TexturePtr source_lmap_height;
	Unigine::LandscapeLayerMapPtr source_lmap;
	// Промежуточный буфер для операций с текстурами landscape
	Unigine::LandscapeTexturesPtr buffers;
	Unigine::LandscapeLayerMapPtr target_lmap;
	// Нормализованный порог нарезки (умножается на максимальную высоту во время выполнения)
	float slice_height{ 0.5f };
	// Флаг отслеживания, был ли отрендерен исходный слой высоты
	bool buffers_rendered = false;


	// Конечный автомат для многокадровой асинхронной обработки
	enum class State
	{
		IDLE,
		BEGIN_FETCH_HEIGHT,  // Начать запрос данных исходной высоты
		FETCHING_HEIGHT,     // Ожидание завершения рендеринга высоты
		BEGIN_DRAW,          // Начать асинхронное рисование в цель
		DRAWING              // Ожидание callback рисования
	};

	State state = State::IDLE;

	// Материал, содержащий шейдер нарезки
	Unigine::MaterialPtr slice_material;
};
