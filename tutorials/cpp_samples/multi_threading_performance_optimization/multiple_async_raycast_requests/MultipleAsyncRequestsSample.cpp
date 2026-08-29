// Стресс-тестирует систему асинхронного пересечения множеством одновременных запросов лучей.
// Использует двойную буферизацию для потокобезопасного управления запросами и отслеживает гистограмму
// задержки, показывающую, сколько кадров занимает завершение каждого запроса.

#include "MultipleAsyncRequestsSample.h"

#include <UniginePlayers.h>
#include <UnigineGame.h>
#include <UnigineInput.h>
#include <UnigineVisualizer.h>

REGISTER_COMPONENT(MultipleAsyncRequestsSample);

using namespace Unigine;
using namespace Math;

// Выделяется пул запросов, инициализируется система двойного буфера.
void MultipleAsyncRequestsSample::init()
{
	init_gui();

	// Храним результаты для каждого луча в плотном массиве параллельно с 'requests' для дружественного к кешу доступа при рендеринге
	requests.resize(num_slices * num_stacks);
	for (int i = 0; i < requests.size(); i++)
	{
		requests[i] = new IntersectionRequest();
		requests[i]->addAsyncEndCallback(MakeCallback(this, &MultipleAsyncRequestsSample::on_intersection_end));
	}
	results.resize(num_slices * num_stacks);

	// Система с двумя буферами: пока один буфер обрабатывается асинхронной системой, другой перестраивается из завершённых коллбэков
	second_buffer = requests;
	buffer = &second_buffer;

	Visualizer::setEnabled(true);
}

// Эмиттер анимируется, завершённые лучи визуализируются, отправляются новые запросы.
void MultipleAsyncRequestsSample::update()
{
	// Анимируем эмиттер (движение вверх/вниз и вращение)
	// Эмиттер задаёт исходную точку и направления для всех лучей пересечения в этом кадре
	float k = (Math::sin(0.3f * Game::getTime()) + 1.0f) / 2.0f;
	emitter_pos.z = min_height + k * (max_height - min_height);

	emitter_rotation += 10.0f * Game::getIFps();
	if (emitter_rotation > 360.0f)
		emitter_rotation -= 360.0f;

	Visualizer::renderPoint3D(emitter_pos, 2.0f, vec4_red);

	// Обновляем лучи: проверяем результаты и перезапускаем запросы
	float slice_step = 360.0f / num_slices;
	float stack_step = 85.0f / num_stacks;

	for (int i = 0; i < num_slices; i++)
	{
		for (int j = 0; j < num_stacks; j++)
		{
			IntersectionRequest *fetch = requests[i * num_stacks + j];
			Result &res = results[i * num_stacks + j];

			if (fetch->isAsyncCompleted())
			{
				if (fetch->isIntersection())
				{
					res.point = fetch->getPoint();
					res.normal = fetch->getNormal();
				}
				res.is_intersected = fetch->isIntersection();

				// Задаём новое направление для следующего испускания
				Vec3 dir = rotateZ(slice_step * i + emitter_rotation) * Vec3_forward;
				dir = quat(cross(vec3(dir), vec3_up), -stack_step * j) * dir;

				fetch->setPositionBegin(emitter_pos);
				fetch->setPositionEnd(emitter_pos + dir * intersection_distance);
			}

			// Отрисовываем нормали попаданий для немедленной визуальной обратной связи
			if (res.is_intersected)
				Visualizer::renderVector(res.point, res.point + Vec3(res.normal) * 5.0f, vec4_red);
		}
	}

	// Меняем буфер, который будет собирать новые завершённые запросы в этом кадре
	// Двойная буферизация гарантирует, что мы не изменяем контейнер, пока его использует асинхронная система
	{
		ScopedLock lock(mutex);

		if (buffer == &first_buffer)
			buffer = &second_buffer;
		else
			buffer = &first_buffer;

		buffer->clear();
	}

	// Запускаем асинхронные пересечения на неактивном буфере
	if (buffer == &first_buffer)
		Intersections::getAsync(second_buffer);
	else
		Intersections::getAsync(first_buffer);

	// Показываем статистику задержки в UI
	long long total_count = immediate_latency_count + low_latency_count + middle_latency_count + high_latency_count;
	if (total_count != 0)
	{
		float immediate = static_cast<float>(immediate_latency_count) / total_count * 100.0f;
		float low = static_cast<float>(low_latency_count) / total_count * 100.0f;
		float middle = static_cast<float>(middle_latency_count) / total_count * 100.0f;
		float high = static_cast<float>(high_latency_count) / total_count * 100.0f;

		String text = "Latency (number of frames per result): \n";
		text += String::format("0-2 (Immediate): %.1f", immediate) + "%\n";
		text += String::format("3-5 (Low): %.1f", low) + "%\n";
		text += String::format("5-7 (Middle): %.1f", middle) + "%\n";
		text += String::format(">7 (High): %.1f", high) + "%\n";

		sample_description_window.setStatus(text.get());
	}
}

// Ожидаются все незавершённые запросы, освобождаются ресурсы.
void MultipleAsyncRequestsSample::shutdown()
{
	// Закрываем UI и останавливаем отрисовку
	sample_description_window.shutdown();
	Visualizer::setEnabled(false);

	// Ожидаем все запросы и очищаем ресурсы
	Intersections::wait(requests);

	for (int i = 0; i < requests.size(); i++)
		delete requests[i];
	requests.clear();

	buffer = nullptr;
	first_buffer.clear();
	second_buffer.clear();

	results.clear();
}

// Задержка записывается, запрос добавляется в буфер завершения.
void MultipleAsyncRequestsSample::on_intersection_end(IntersectionRequest *r)
{
	// Считаем, сколько кадров заняло завершение запроса
	long long d = r->getAsyncFrameLatency();
	if (d <= 2)
		immediate_latency_count++;
	else if (d <= 5)
		low_latency_count++;
	else if (d <= 7)
		middle_latency_count++;
	else
		high_latency_count++;

	ScopedLock lock(mutex);
	buffer->append(r);
}

// Создаётся окно UI для отображения статистики задержки.
void MultipleAsyncRequestsSample::init_gui()
{
	sample_description_window.createWindow();
}
