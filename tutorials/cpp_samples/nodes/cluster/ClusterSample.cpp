// Интерактивная демонстрация ObjectMeshCluster. Клик по земле добавляет
// экземпляры в точке клика; клик по существующим экземплярам удаляет их.
// Демонстрирует обновление пространственного дерева, необходимое после изменения содержимого кластера.

#include "ClusterSample.h"

#include <UnigineConsole.h>
#include <UnigineGame.h>
#include <UnigineWidgets.h>
#include <UnigineWorld.h>

REGISTER_COMPONENT(ClusterSample);

using namespace Unigine;
using namespace Math;

// Фиксированное смещение по высоте для размещённых экземпляров (над плоскостью земли)
const float OFFSET_Z = 0.5f;

void ClusterSample::init()
{
	// Приводим общую ссылку Node к ObjectMeshCluster для типобезопасного доступа к API
	cluster = checked_ptr_cast<ObjectMeshCluster>(clusterNode.get());
	if (!cluster)
		Log::error("ClusterSample::init(): can not get clusterNode property\n");

	sample_description_window.createWindow();
	update_gui();
}

void ClusterSample::update()
{
	// Пропускаем обработку ввода, когда открыта консоль, чтобы избежать конфликтов
	if (Console::isActive())
		return;

	// Обрабатываем клик левой кнопкой мыши для операций добавления/удаления
	if (Input::isMouseButtonDown(Input::MOUSE_BUTTON::MOUSE_BUTTON_LEFT))
	{
		// Выпускаем луч от камеры через позицию курсора мыши
		ivec2 mouse = Input::getMousePosition();
		Vec3 p0 = Game::getPlayer()->getWorldPosition();
		// Луч простирается на 100 единиц от камеры в направлении обзора
		Vec3 p1 = p0 + Vec3(Game::getPlayer()->getDirectionFromMainWindow(mouse.x, mouse.y)) * 100;

		// Выполняем проверку пересечения с миром для объектов, соответствующих маске
		ObjectPtr obj = World::getIntersection(p0, p1, intersection_mask.get(), intersection);
		if (obj)
		{
			// Проверяем, является ли объект попадания нашим кластером (удаляем экземпляр)
			if (obj == cluster)
			{
				// getInstance() возвращает, какой экземпляр кластера был затронут
				int num = intersection->getInstance();
				cluster->removeMeshTransform(num);
			}
			else
			{
				// Попадание в землю или другой объект - добавляем новый экземпляр в точке клика
				Vec3 point = intersection->getPoint();
				// Переопределяем Z, чтобы разместить экземпляр на фиксированной высоте
				point.z = OFFSET_Z;

				// Добавляем экземпляр, используя трансформацию в локальном пространстве относительно кластера
				int new_index = cluster->addMeshTransform();
				// Преобразуем мировую позицию в локальное пространство кластера
				cluster->setMeshTransform(new_index,
					mat4(cluster->getIWorldTransform() * translate(point)));

				// Альтернатива: добавить несколько экземпляров в мировом пространстве за раз
				// Vector<Mat4> transforms = Vector<Mat4>(translate(point), 1);
				// cluster->appendMeshes(transforms);
			}

			// Пространственное дерево должно обновляться после любого изменения кластера.
			// Это перестраивает внутреннюю ускоряющую структуру, используемую для:
			// - Отсечения по фрустуму (определение видимости)
			// - Запросов пересечений (трассировка лучей относительно экземпляров)
			// - Расчётов LOD на основе расстояния до камеры
			cluster->updateSpatialTree();
		}

		// Обновляем UI, чтобы отобразить актуальное количество экземпляров
		update_gui();
	}
}

void ClusterSample::shutdown()
{
	shutdown_gui();
}

void ClusterSample::init_gui() {}

void ClusterSample::update_gui()
{
	// Отображаем текущее количество экземпляров мешей в кластере
	sample_description_window.setStatus(
		String::format("Number of meshes in the cluster: %d", cluster->getNumMeshes()).get());
}

void ClusterSample::shutdown_gui()
{
	sample_description_window.shutdown();
}
