#pragma once

#include "../../menu_ui/SampleDescriptionWindow.h"
#include "../../utils/intersection/Intersections.h"

#include <UnigineComponentSystem.h>
#include <UnigineWidgets.h>

// Демонстрирует большой объём асинхронных запросов пересечения с двойной буферизацией.
// Эмиттер испускает лучи по сферическому паттерну; каждый луч использует асинхронное пересечение.
// Статистика задержки отслеживает, сколько кадров проходит между запросом и завершением.
class MultipleAsyncRequestsSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(MultipleAsyncRequestsSample, Unigine::ComponentBase);
	COMPONENT_DESCRIPTION("This component demonstrates running many asynchronous intersection ray casts, "
		"using double buffering to manage completed requests, visualizing hits, and reporting frame-latency statistics.")

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// длина луча для тестов пересечения (задаётся в редакторе)
	PROP_PARAM(Float, intersection_distance, 10000.0f);

private:
	void init();     // создаёт пул запросов и инициализирует двойной буфер
	void update();   // анимирует эмиттер и обрабатывает результаты пересечения
	void shutdown(); // ожидает завершения незавершённых запросов и очищает ресурсы

	void on_intersection_end(IntersectionRequest *r); // коллбэк для асинхронного завершения

private:
	// разрешение сетки лучей (азимут и возвышение)
	const int num_slices{30};
	const int num_stacks{30};

	// пределы высоты эмиттера для простого движения вверх/вниз
	const float min_height{35.0f};
	const float max_height{200.0f};

	// исходная позиция и вращение эмиттера
	Unigine::Math::Vec3 emitter_pos{500.0f, 500.0f, 100.0f};
	float emitter_rotation{0.0f};

	// один асинхронный запрос на каждый луч в сетке
	Unigine::Vector<IntersectionRequest *> requests;

	// двойная буферизация во избежание конфликтов с асинхронной работой
	Unigine::Vector<IntersectionRequest *> *buffer{nullptr};
	Unigine::Vector<IntersectionRequest *> first_buffer;
	Unigine::Vector<IntersectionRequest *> second_buffer;
	Unigine::Mutex mutex;

	// кешированные данные попадания для каждого луча
	struct Result
	{
		bool is_intersected{false};
		Unigine::Math::Vec3 point;
		Unigine::Math::vec3 normal;
	};

	Unigine::Vector<Result> results;

	// UI примера с описанием и элементами управления
	void init_gui();
	SampleDescriptionWindow sample_description_window;

	// счётчики задержки по кадрам для статистики асинхронного завершения
	long long immediate_latency_count{0};
	long long low_latency_count{0};
	long long middle_latency_count{0};
	long long high_latency_count{0};
};
