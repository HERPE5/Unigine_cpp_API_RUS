#pragma once

#include <UnigineComponentSystem.h>

// Демонстрирует применение процедурных мешей к ObjectMeshCluster.
// Меш сферы пересоздаётся каждый кадр с меняющейся тесселяцией (stacks/slices),
// затем применяется асинхронно ко всем экземплярам кластера. Использует PROCEDURAL_MODE_DYNAMIC
// для оптимальной производительности, когда данные меша часто меняются.
class ProceduralMeshApply : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(ProceduralMeshApply, Unigine::ComponentBase);
	COMPONENT_DESCRIPTION("This component demonstrates applying a procedural sphere mesh to a cluster with dynamic tessellation");

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();                              // Создаёт кластер и сетку экземпляров
	void update();                            // Перестраивает меш и применяет к кластеру
	void shutdown();                          // Освобождает ресурсы меша и кластера

	void update_mesh(Unigine::MeshPtr mesh);  // Пересоздаёт сферу с текущей тесселяцией

private:
	Unigine::MeshPtr mesh;                    // Данные процедурного меша
	Unigine::ObjectMeshClusterPtr cluster;    // Кластер, отображающий экземпляры меша

	// Базовый радиус сферы
	float radius = 0.5f;

	// Пределы для вертикальных подразбиений (stacks)
	const int max_num_stacks = 30;
	const int min_num_stacks = 2;

	// Текущая тесселяция сферы
	int num_stacks = 2;
	int num_slices = 3;

	// Сигнализирует, увеличиваем или уменьшаем количество slices и stacks
	bool is_increasing = true;

	// Параметры для периодического изменения тесселяции сферы
	float change_rate = 0.1f;
	float current_time = 0.f;

	// Раскладка кластера
	const int size = 20;		// Количество ячеек по X и Y
	float offset = 1.f;			// Расстояние между мешами
};
