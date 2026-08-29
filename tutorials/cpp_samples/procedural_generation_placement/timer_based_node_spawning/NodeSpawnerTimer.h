// Спаунер узлов на основе таймера, периодически создающий экземпляры узлов.
// Частота спауна настраивается во время выполнения. Использует вычитание интервала,
// а не сброс, для поддержания согласованной частоты спауна.

#pragma once
#include <UnigineComponentSystem.h>

// Создаёт узлы через регулярные интервалы на основе настраиваемой частоты спауна.
class NodeSpawnerTimer :
	public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(NodeSpawnerTimer, ComponentBase);

	COMPONENT_UPDATE(update);

	// Интервал в секундах между спаунами
	PROP_PARAM(Float, spawn_rate, 5);
	// Путь к файлу .node, который будет создан
	PROP_PARAM(File, node_to_spawn);

	// Возвращает текущий прогресс таймера для визуализации UI
	float getTimer() const { return time_buffer_sec; }
private:
	void update();


private:
	// Накопленное время с последнего спауна
	float time_buffer_sec = 0.1f;
};

