// Демонстрирует события разрушения соединений с использованием разрушаемой структуры моста.
// Секции моста соединяются шарнирными соединениями с ограничениями силы/крутящего момента.
// Когда нагрузка превышает пределы, соединения разрушаются и запускают визуальную обратную связь.

#pragma once

#include <UnigineComponentSystem.h>

class JointCallbacks : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(JointCallbacks, Unigine::ComponentBase);

	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Количество сегментов в цепи моста
	PROP_PARAM(Int, bridge_sections, 14);
	// Материал, применяемый к сегментам после разрушения их соединения
	PROP_PARAM(Material, broken_materal);
	// Материал, применяемый к целым сегментам, всё ещё соединённым
	PROP_PARAM(Material, joint_materal);
	// Ресурс меша для блоков секций моста
	PROP_PARAM(File, mesh_file);

private:
	void init();
	void shutdown();

	// Callback, вызываемый когда сила/крутящий момент соединения превышает пределы
	void broken_callback(const Unigine::JointPtr &joint);

private:
	Unigine::MaterialPtr broken_mat;
	Unigine::MaterialPtr joint_mat;

	// Все созданные объекты для очистки
	Unigine::Vector<Unigine::NodePtr> objects;
	// Управляет всеми соединениями событий соединений
	Unigine::EventConnections joint_connections;

	// Расстояние между соседними секциями моста
	float space = 1.1f;
};
