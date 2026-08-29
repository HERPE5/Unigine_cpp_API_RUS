#pragma once
#include <UnigineComponentSystem.h>

#include "../../menu_ui/SampleDescriptionWindow.h"

// Демонстрирует JSON API для сериализации данных.
// Показывает создание иерархических структур JSON, добавление типизированных значений
// и рекурсивный обход дерева для форматированного вывода.
class JsonSample : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(JsonSample, ComponentBase)
	COMPONENT_DESCRIPTION("This component demonstrates creating a JSON tree, recursively traversing it, "
							"and printing a formatted representation to the console.")

	COMPONENT_INIT(init)
	COMPONENT_SHUTDOWN(shutdown)

private:
	void init();
	void shutdown();

	// Создаёт пример объекта JSON (корневой узел + дочерние элементы)
	Unigine::JsonPtr json_create();

	// Выводит всё дерево JSON
	void json_print(const Unigine::JsonPtr &json);

	// Рекурсивная функция: выводит один узел (объект, массив, значение и т.д.)
	void json_print_node(const Unigine::JsonPtr &json, int offset = 0, int index = 0,
		bool print_name = true);

	// Вспомогательная функция: выводит строку с отступом + опциональной запятой
	void print_string_offset(const Unigine::String &value, int offset, bool print_comma = false);

private:
	bool is_console_onscreen{false}; // сохранённое состояние консоли для восстановления при завершении
};
