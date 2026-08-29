// Преобразует процедурный ObjectMeshClutter в статический ObjectMeshCluster. Clutter
// пересоздаёт экземпляры каждый кадр на основе зерна; Cluster хранит фиксированные трансформации
// для лучшей производительности во время выполнения, когда позиции экземпляров не должны меняться.

#pragma once

#include <UnigineComponentSystem.h>

class ClutterConverter : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(ClutterConverter, Unigine::ComponentBase);
	COMPONENT_INIT(init);

	// Исходный объект clutter, экземпляры которого будут преобразованы
	PROP_PARAM(Node, clutterMesh);
	// Родительский узел для создаваемого кластера (может отличаться от родителя clutter)
	PROP_PARAM(Node, clusterParent)

	// Создаёт статический кластер из текущих позиций экземпляров clutter
	void convertToCluster();
	// Рандомизирует размещение clutter, назначая новое значение зерна
	void generateClutter();

private:
	// Отслеживает, был ли создан кластер, чтобы предотвратить дубликаты
	bool is_converted = false;
	// Закэшированная ссылка на исходный объект clutter
	Unigine::ObjectMeshClutterPtr clutter_mesh;
	// Результирующий кластер после преобразования
	Unigine::ObjectMeshClusterPtr cluster_mesh;

private:
	void init();
	// Уничтожает существующий кластер перед созданием нового
	void remove_cluster();
	// Выполняет фактическое преобразование: копирует меш, поверхности и трансформации
	Unigine::ObjectMeshClusterPtr convert_mesh(const Unigine::ObjectMeshClutterPtr &clutter);
};
