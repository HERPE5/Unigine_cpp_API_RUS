// Спаунер узлов на основе таймера, периодически загружающий и создающий экземпляр файла .node.
// Частота спауна настраивается. Таймер вычитает интервал, а не сбрасывается
// в ноль, обеспечивая согласованную частоту спауна независимо от колебаний времени кадра.

#include "NodeSpawnerTimer.h"
#include <UnigineGame.h>

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(NodeSpawnerTimer);

// Время накапливается каждый кадр; узел создаётся при достижении интервала.
void NodeSpawnerTimer::update()
{
	// Накапливаем время кадра до достижения интервала спауна
	time_buffer_sec += Game::getIFps();
	if (time_buffer_sec >= spawn_rate)
	{
		// Вычитаем интервал (не сбрасываем), чтобы поддерживать точность времени между кадрами
		time_buffer_sec -= spawn_rate;
		NodePtr spawned_node = World::loadNode(node_to_spawn);
		// Создаём в позиции трансформации этого компонента
		spawned_node->setTransform(node->getTransform());
	}
}