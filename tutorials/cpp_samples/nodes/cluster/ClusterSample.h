// Интерактивная демонстрация ObjectMeshCluster. Клик по земле добавляет
// экземпляры в точке клика; клик по существующим экземплярам удаляет их.
// Демонстрирует обновление пространственного дерева, необходимое после изменения содержимого кластера.

#pragma once

#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>

class ClusterSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(ClusterSample, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// Ссылка на узел ObjectMeshCluster для управления
	PROP_PARAM(Node, clusterNode);
	// Маска пересечений для трассировки лучей (определяет, какие объекты попадают под луч)
	PROP_PARAM(Mask, intersection_mask, 1)

private:
	// Закэшированный указатель на кластер для эффективного доступа при обновлениях
	Unigine::ObjectMeshClusterPtr cluster;
	// Переиспользуемый объект результата пересечения во избежание выделений памяти каждый кадр
	Unigine::WorldIntersectionPtr intersection = Unigine::WorldIntersection::create();
	// Окно примера, показывающее количество экземпляров
	SampleDescriptionWindow sample_description_window;

private:
	void init();
	void update();
	void shutdown();

	void init_gui();
	// Обновляет отображаемое количество мешей после операций добавления/удаления
	void update_gui();
	void shutdown_gui();
};
