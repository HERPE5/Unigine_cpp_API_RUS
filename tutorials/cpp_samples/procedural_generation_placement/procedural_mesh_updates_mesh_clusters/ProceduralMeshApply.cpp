// Применяет процедурно сгенерированные меши к ObjectMeshCluster с использованием асинхронных обновлений.
// Демонстрирует динамическую тесселяцию сферы с PROCEDURAL_MODE_DYNAMIC для мешей,
// которые часто меняются. Экземпляры кластера используют общую геометрию процедурного меша.

#include "ProceduralMeshApply.h"

#include <UnigineGame.h>
#include <UnigineVisualizer.h>

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(ProceduralMeshApply);

// Кластер создаётся с динамическим процедурным режимом, заполняется сетка экземпляров.
void ProceduralMeshApply::init()
{
	mesh = Mesh::create();
	cluster = ObjectMeshCluster::create();

	// Выбираем процедурный режим для кластера:
	//		Disable - процедурный режим отключён
	//		Dynamic - самая высокая производительность; хранится в RAM и VRAM; не выгружается автоматически
	//		Blob    - средняя производительность; хранится в RAM/VRAM; автоматически выгружается при неактивности
	//		File    - самая низкая производительность; хранится на диске; автоматически выгружается при неактивности
	cluster->setMeshProceduralMode(ObjectMeshStatic::PROCEDURAL_MODE_DYNAMIC);
	cluster->setWorldPosition(Vec3(0.f, 0.f, 3.f));

	// Создаём трансформации для сетки экземпляров
	Vector<Mat4> transforms;
	float field_offset = (1.f + offset) * size / 2.f;

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			transforms.append(
				translate(Vec3(x + x * offset - field_offset, y + y * offset - field_offset, 1.5)));
		}
	}
	cluster->appendMeshes(transforms);

	Visualizer::setEnabled(true);
}

// Меш пересоздаётся и применяется асинхронно каждый кадр.
void ProceduralMeshApply::update()
{
	// Перестраиваем меш сферы перед применением его к кластеру
	update_mesh(mesh);

	// Применяем новый меш. Можно сделать это через Force или Async.
	// Флаги хранения MeshRender (второй аргумент) управляют тем, где хранятся данные меша:
	//		0						- по умолчанию, хранить данные в VRAM
	//		USAGE_DYNAMIC_VERTEX	- хранить вершины в RAM
	//		USAGE_DYNAMIC_INDICES	- хранить индексы в RAM
	//		USAGE_DYNAMIC_ALL		- хранить и вершины, и индексы в RAM

	cluster->applyMoveMeshProceduralAsync(mesh, 0);
	Visualizer::renderObject(cluster, vec4_green);
}

// Ресурсы меша и кластера освобождаются.
void ProceduralMeshApply::shutdown()
{
	mesh.clear();
	cluster.deleteLater();

	Visualizer::setEnabled(false);
}

// Меш сферы пересоздаётся с колеблющимися значениями тесселяции.
void ProceduralMeshApply::update_mesh(MeshPtr mesh)
{
	// Периодически изменяем тесселяцию сферы (stacks/slices)
	current_time += Game::getIFps();

	if (current_time > change_rate)
	{
		current_time = 0.f;

		num_slices = is_increasing ? num_slices + 1 : num_slices - 1;
		num_stacks = is_increasing ? num_stacks + 1 : num_stacks - 1;

		if (num_stacks == max_num_stacks)
			is_increasing = false;

		if (num_stacks <= min_num_stacks)
		{
			is_increasing = true;
			num_stacks = min_num_stacks;
			num_slices = num_stacks + 1;
		}
	}

	// Создаём поверхность сферы с текущими параметрами
	mesh->clear();
	mesh->addSphereSurface("sphere", radius, num_stacks, num_slices);
}
