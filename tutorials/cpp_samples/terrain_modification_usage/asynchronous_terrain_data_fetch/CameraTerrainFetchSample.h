// Демонстрирует асинхронный запрос данных terrain с помощью LandscapeFetch.
// Пускает луч от камеры через курсор мыши к поверхности terrain.
// Отображает высоту terrain, нормаль и значения масок в точке пересечения.

#pragma once
#include <UnigineVector.h>
#include <UniginePlayers.h>
#include <UnigineComponentSystem.h>

// Запрашивает и отображает данные terrain в позиции курсора мыши.
class CameraTerrainFetchSample : public Unigine::ComponentBase
{
public:
	COMPONENT(CameraTerrainFetchSample, ComponentBase)
	COMPONENT_INIT(init)
	COMPONENT_UPDATE(update)
	COMPONENT_SHUTDOWN(shutdown)

	PROP_NAME("CameraTerrainFetchSample")
	PROP_AUTOSAVE(0)

private:
	void init();
	void update();
	void shutdown();

	Unigine::PlayerPtr main_player;				// Узел камеры игрока, к которому прикреплён этот компонент
	Unigine::LandscapeFetchPtr fetch;			// Асинхронный запрос данных terrain
	bool visualizer_enabled = false;			// Исходное состояние визуализатора для восстановления
	int num_masks = 4;							// Количество масок terrain для запроса
};
