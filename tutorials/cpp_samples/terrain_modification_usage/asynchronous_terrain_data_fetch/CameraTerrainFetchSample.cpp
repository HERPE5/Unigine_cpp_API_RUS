// Демонстрирует асинхронный запрос данных terrain с помощью LandscapeFetch.
// Пускает луч от камеры через курсор мыши к поверхности terrain.
// Отображает высоту terrain, нормаль и значения масок в точке пересечения.

#include "CameraTerrainFetchSample.h"

#include <UnigineVisualizer.h>
#include <UnigineGame.h>

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(CameraTerrainFetchSample)

// Включается визуализатор; ссылка на игрока получается из прикреплённого узла.
void CameraTerrainFetchSample::init()
{
	// Состояние визуализатора сохраняется для восстановления при завершении работы
	visualizer_enabled = Visualizer::isEnabled();
	Visualizer::setEnabled(true);

	// Компонент должен быть прикреплён к узлу Player
	main_player = checked_ptr_cast<Player>(node);
	if (!main_player)
		Log::error("CameraTerrainFetchSample::init(): CameraTerrainFetchSample must be assigned to a player node!\n");
}

// Асинхронный запрос terrain инициируется или результаты отображаются каждый кадр.
void CameraTerrainFetchSample::update()
{
	if (!main_player)
		return;

	// Конечные точки луча вычисляются из позиции курсора мыши
	Vec3 a, b;
	auto main_window = WindowManager::getMainWindow();
	auto mouse = Input::getMousePosition();

	main_player->getDirectionFromMainWindow(a, b, mouse.x, mouse.y);

	// Объект запроса создаётся на первом кадре
	if (!fetch)
	{
		fetch = LandscapeFetch::create();

		// Настраиваются типы данных для запроса из terrain
		fetch->setUsesHeight(true);
		fetch->setUsesNormal(true);
		fetch->setUsesAlbedo(true);

		// Включаются все каналы масок для запроса
		for (int i = 0; i < num_masks; i += 1)
			fetch->setUsesMask(i, true);

		// Ставится в очередь начальное асинхронное пересечение
		fetch->intersectionAsync(a, a + ((b - a) * Game::getPlayer()->getZFar()));
	}

	else
	{
		// Результаты обрабатываются по завершении асинхронной операции
		if (fetch->isAsyncCompleted())
		{
			if (fetch->isIntersection())
			{
				// Данные terrain извлекаются из результата запроса
				auto terrain = Landscape::getActiveTerrain();
				auto point = fetch->getPosition();
				auto height = fetch->getHeight();
				auto vector_length = 10.f;
				StringStack<> info;

				// Информационная строка строится со значениями высоты и масок
				info += String::format("height : %.3f\n", height);
				info += "masks: \n";

				for (int i = 0; i < num_masks; i++)
					info += String::format("    %s: %.2f\n", terrain->getDetailMask(i)->getName(), fetch->getMask(i));

				// Вектор нормали, сфера и текст рендерятся в точке пересечения
				Visualizer::renderVector(point, point + Vec3(fetch->getNormal() * vector_length), vec4_white, .25f);
				Visualizer::renderSolidSphere(1.f, translate(point), vec4_white);
				Visualizer::renderMessage3D(point, vec3(1.f, 1.f, 0.f), info.get(), vec4_green, 1);
			}

			else
				// Сообщение об ошибке показывается, когда луч не попадает в terrain
				Visualizer::renderMessage3D(b, vec3(1.f, 1.f, 0), "Out of terrain.", vec4_red, 1);

			// Ставится в очередь следующее асинхронное пересечение
			fetch->intersectionAsync(a, a + ((b - a) * Game::getPlayer()->getZFar()));
		}
	}
}

void CameraTerrainFetchSample::shutdown()
{
	Visualizer::setEnabled(visualizer_enabled);
	fetch = nullptr;
}
