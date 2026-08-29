#pragma once

#include "../../menu_ui/SampleDescriptionWindow.h"
#include "../../utils/intersection/Intersections.h"

#include <UnigineComponentSystem.h>
#include <UnigineWidgets.h>

// Демонстрирует одиночный асинхронный запрос пересечения от камеры через курсор мыши.
// Отслеживает статистику задержки по времени (среднюю и максимальную) для анализа производительности.
class SimpleAsyncRequestSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(SimpleAsyncRequestSample, Unigine::ComponentBase);
	COMPONENT_DESCRIPTION("This component performs an asynchronous intersection from the player toward the mouse cursor, "
				"visualizes the hit with a normal vector, and displays average and maximum time latency in the UI.")

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// максимальное расстояние для проверки пересечений от игрока (задаётся в редакторе)
	PROP_PARAM(Float, intersection_distance, 10000.0f);

private:
	void init();     // включает визуализатор и создаёт UI
	void update();   // испускает луч и отображает результат пересечения
	void shutdown(); // отключает визуализатор и закрывает UI

private:
	// структура для хранения результата запроса пересечения
	struct Result
	{
		bool is_intersected{false};
		Unigine::Math::Vec3 point;
		Unigine::Math::vec3 normal;
	};

	// состояние, связанное с игроком
	bool is_player_completed{true};					// предыдущее состояние запроса
	Result player_result;							// последний результат пересечения
	double player_request_time{0.0};				// время отправки последнего асинхронного запроса
	int warmup_frames{5};							// пропускаем начальные кадры во избежание всплесков нагрузки

	// UI примера с описанием и элементами управления
	void init_gui();
	SampleDescriptionWindow sample_description_window;

	// отслеживание задержки запросов (в миллисекундах)
	enum
	{
		PLAYER_LATENCY_COUNT = 600							// количество отсчётов для хранения истории задержки
	};
	double player_latency[PLAYER_LATENCY_COUNT]{0.0};		// кольцевой буфер (мс)
	double avg_player_latency{0.0};							// средняя задержка по буферу (мс)
	double max_player_latency{0.0};							// максимальная зафиксированная задержка (мс)
	int player_latency_index{0};							// текущий индекс в буфере
	int player_latency_filled{0};							// количество заполненных записей в буфере
};
