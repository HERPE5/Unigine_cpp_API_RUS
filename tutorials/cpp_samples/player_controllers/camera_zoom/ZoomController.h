// Реализует масштабирование камеры, синхронно регулируя FOV, масштаб дистанции рендеринга и
// чувствительность мыши. Более сильное увеличение сужает FOV, расширяя дистанции LOD
// и снижая чувствительность для стабильного прицеливания на большой дистанции.

#pragma once
#include "UnigineComponentSystem.h"

// Координирует FOV, дистанцию LOD и чувствительность ввода для плавного масштабирования.
class ZoomController : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(ZoomController, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	void focus_on_target(Unigine::NodePtr target);	// Ориентирует камеру на целевой узел
	void udpate_zoom_factor(float zoom_factor);		// Применяет масштаб: FOV, масштаб дистанции, чувствительность
	void reset();									// Сбрасывает масштаб к 1x

private:
	float default_FOV = 60.0f;				// Исходный FOV до масштабирования
	float default_distance_scale = 1.0f;	// Исходный множитель дистанции LOD
	float default_sensivity = 1.0f;			// Исходная чувствительность мыши
	float default_player_turning = 90.0f;	// Исходная скорость поворота (для Spectator/Actor)

	Unigine::PlayerPtr player;

	void init();
	void shutdown();
	void update_turning(float zoom_factor);	// Настраивает поворот игрока для типов Spectator/Actor
};