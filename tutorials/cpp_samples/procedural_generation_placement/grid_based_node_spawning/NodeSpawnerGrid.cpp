// Утилита для создания узлов по паттерну 2D-сетки. Поддерживает центрирование сетки
// в точке опоры или рост от угла. Узлы загружаются из файла .node
// и позиционируются на основе размера ячейки и размеров сетки.

#include "NodeSpawnerGrid.h"
#include <UnigineWorld.h>

using namespace Unigine;
using namespace Math;


// Создаёт сетку узлов из указанного файла .node. Если pivot_at_center равен true,
// сетка центрируется в начале координат мировой трансформации; иначе она растёт от угла.
void Utils::spawnGrid(const char* node_path, const Unigine::Math::vec2& cell_size, const Unigine::Math::ivec2& grid_size,
	const Unigine::Math::Mat4& world_transform,
	bool pivot_at_center,
	Unigine::Vector<Unigine::NodePtr>* output)
{
	for (int x = 0; x < grid_size.x; x++)
	{
		// Вычисляем позицию X - смещение на половину размера сетки при центрировании
		double x_pos = pivot_at_center ? x * cell_size.x - grid_size.x * cell_size.x/2 : x * cell_size.x;
		for (int y = 0; y < grid_size.y; y++)
		{
			// Вычисляем позицию Y - смещение на половину размера сетки при центрировании
			double y_pos = pivot_at_center ? y * cell_size.y - grid_size.y*cell_size.y/2 : y * cell_size.y;
			NodePtr spawned_node = World::loadNode(node_path);
			// Объединяем мировую трансформацию со смещением ячейки сетки (Z = 0 для плоской сетки)
			spawned_node->setTransform(world_transform * translate(Vec3(static_cast<Scalar>(x_pos), static_cast<Scalar>(y_pos), 0)));
			if (output)
				output->push_back(spawned_node);
		}
	}
}
