#pragma once

#include <UnigineComponentSystem.h>

class VisualizerUsage : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(VisualizerUsage, Unigine::ComponentBase);
	COMPONENT_DESCRIPTION("This component demonstrates how to use the Visualizer API to render various 2D and 3D "
		"debug primitives, such as points, lines, shapes, bounding volumes, and object surfaces.");


	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

	// Переключатели для элементов 2D-визуализации
	bool renderPoint2D = false;
	bool renderLine2D = false;
	bool renderTriangle2D = false;
	bool renderQuad2D = false;
	bool renderRectangle = false;
	bool renderMessage2D = false;

private:
	// Узлы для примеров визуализации (задаются в редакторе)
	PROP_PARAM(Node, node_boundBox_example);
	PROP_PARAM(Node, node_boundSphere_example);

	PROP_PARAM(Node, node_object_example);
	PROP_PARAM(Node, node_object_solid_example);

	PROP_PARAM(Node, node_surface_example);
	PROP_PARAM(Node, node_surface_solid_example);

	PROP_PARAM(Node, node_object_surface_boundBox_example);
	PROP_PARAM(Node, node_object_surface_boundSphere_example);

	// Массив узлов-постаментов для позиционирования
	PROP_ARRAY(Node, postament_nodes);

	// Указатели на объекты — цели визуализации
	Unigine::ObjectPtr object_example;
	Unigine::ObjectPtr object_solid_example;

	Unigine::ObjectPtr surface_example;
	Unigine::ObjectPtr surface_solid_example;

	Unigine::ObjectPtr object_surface_boundBox_example;
	Unigine::ObjectPtr object_surface_boundSphere_example;

	
	void init();
	void update();		// Основной цикл обновления
	void update3D();	// Обновление элементов 3D-визуализации
	void update2D();	// Обновление элементов 2D-визуализации

	// Получить позицию из массива постаментов
	Unigine::Math::Vec3 getPostamentPoint(int index);
};