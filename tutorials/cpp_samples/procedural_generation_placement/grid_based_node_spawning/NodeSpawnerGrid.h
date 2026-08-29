// Вспомогательная функция для создания узлов по паттерну 2D-сетки.
// Узлы загружаются из файла .node и позиционируются на основе
// размера ячейки и размеров сетки. Поддерживает центрированную или угловую точку опоры.

#pragma once
#include <UnigineVector.h>
#include <UnigineNode.h>

namespace Utils
{
	// Создаёт grid_size.x * grid_size.y узлов из node_path.
	// pivot_at_center: true центрирует сетку в начале координат world_transform.
	// output: опциональный вектор для сбора ссылок на созданные узлы.
	void spawnGrid(const char* node_path, const Unigine::Math::vec2 &cell_size, const Unigine::Math::ivec2 &grid_size,
		const Unigine::Math::Mat4 &world_transform,
		bool pivot_at_center = false,
		Unigine::Vector<Unigine::NodePtr>* output = nullptr);
}