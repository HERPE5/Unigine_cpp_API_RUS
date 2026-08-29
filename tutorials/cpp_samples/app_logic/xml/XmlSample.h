#pragma once

#include <UnigineComponentSystem.h>

// Демонстрирует XML API для работы с иерархическими данными.
// Показывает создание узлов XML с атрибутами, дочерними элементами и текстовыми данными.
// Включает рекурсивный обход дерева для форматированного вывода в консоль.
class XmlSample : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(XmlSample, ComponentBase)
	COMPONENT_DESCRIPTION("This component demonstrates creating a hierarchical XML structure with attributes and data, "
							"and recursively printing its contents to the console.")

	COMPONENT_INIT(init)
	COMPONENT_SHUTDOWN(shutdown)

private:
	void init();
	void shutdown();

	// Создаёт и заполняет структуру XML
	Unigine::XmlPtr xml_create();

	// Выводит содержимое XML с форматированием
	void xml_print(Unigine::XmlPtr xml, int offset = 0);
};
