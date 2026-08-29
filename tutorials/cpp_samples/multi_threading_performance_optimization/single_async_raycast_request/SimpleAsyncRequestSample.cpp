// Испускает один асинхронный луч пересечения от камеры через курсор мыши каждый кадр.
// Точка попадания и нормаль визуализируются; статистика задержки вычисляется и отображается.

#include "SimpleAsyncRequestSample.h"

#include <UniginePlayers.h>
#include <UnigineGame.h>
#include <UnigineInput.h>
#include <UnigineVisualizer.h>

REGISTER_COMPONENT(SimpleAsyncRequestSample);

using namespace Unigine;
using namespace Math;

// UI создаётся, визуализатор включается.
void SimpleAsyncRequestSample::init()
{
	init_gui();
	Visualizer::setEnabled(true);
}

// Луч испускается от игрока через мышь; результат визуализируется, задержка отслеживается.
void SimpleAsyncRequestSample::update()
{
	// Получаем главного игрока на сцене
	PlayerPtr main_player = Game::getPlayer();
	if (main_player)
	{
		// Если предыдущий запрос пересечения завершён, считываем результат и запускаем новый
		if (is_player_completed)
		{
			// Записываем задержку конвейера в миллисекундах (измеряется в update, где Game::getTime актуально)
			if (warmup_frames > 0)
			{
				warmup_frames--;
			}
			else if (player_request_time > 0.0)
			{
				double latency_ms = (Game::getTime() - player_request_time) * 1000.0;

				player_latency[player_latency_index] = latency_ms;
				player_latency_index++;
				if (player_latency_index == PLAYER_LATENCY_COUNT)
					player_latency_index = 0;
				if (player_latency_filled < PLAYER_LATENCY_COUNT)
					player_latency_filled++;

				// Обновляем максимум за всё время и вычисляем среднюю задержку по буферу
				if (latency_ms > max_player_latency)
					max_player_latency = latency_ms;

				avg_player_latency = 0.0;
				for (int i = 0; i < player_latency_filled; i++)
					avg_player_latency += player_latency[i];
				avg_player_latency /= player_latency_filled;
			}

			// Отмечаем запрос как выполняющийся
			is_player_completed = false;

			Vec3 p0 = main_player->getWorldPosition();
			const auto mouse_coord = Input::getMousePosition();
			Vec3 p1 = p0 + Vec3(main_player->getDirectionFromMainWindow(mouse_coord.x, mouse_coord.y)) * intersection_distance.get();

			// Захватываем умный указатель, чтобы лямбда не обращалась к удалённому узлу
			NodePtr check_deleted = node;

			// Записываем время отправки и выполняем асинхронный запрос пересечения
			player_request_time = Game::getTime();
			Intersections::getAsync(p0, p1, 1, [this, check_deleted](IntersectionRequest *r)
			{
				if (!check_deleted)
					return;

				is_player_completed = true;

				// Сохраняем результат пересечения
				if (r->isIntersection())
				{
					player_result.point = r->getPoint();
					player_result.normal = r->getNormal();
				}
				player_result.is_intersected = r->isIntersection();
			});
		}

		// Отрисовываем вектор в точке пересечения для визуализации результата
		if (player_result.is_intersected)
			Visualizer::renderVector(player_result.point, player_result.point + Vec3(player_result.normal) * 10.0f, vec4_green);
	}

	String text = String::format(
		"Latency (ms per result)\nPlayer: avg %.3f ms, max %.3f ms\n\n",
		avg_player_latency,
		max_player_latency
	);
	sample_description_window.setStatus(text.get());
}

// Визуализатор отключается, окно UI закрывается.
void SimpleAsyncRequestSample::shutdown()
{
	Visualizer::setEnabled(false);
	sample_description_window.shutdown();
}

// Создаётся окно UI.
void SimpleAsyncRequestSample::init_gui()
{
	sample_description_window.createWindow();
}
