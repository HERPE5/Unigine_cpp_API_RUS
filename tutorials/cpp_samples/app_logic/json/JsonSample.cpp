// Демонстрирует Unigine::Json API для создания и обхода структур JSON.
// Показывает построение дерева с объектами, массивами, строками, числами, булевыми значениями и null.
// Рекурсивная функция вывода форматирует результат с правильными отступами и запятыми.

#include "JsonSample.h"

#include <UnigineConsole.h>

using namespace Unigine;
using namespace Math;


// Пример создания объекта JSON
JsonPtr JsonSample::json_create()
{
	// Корневой узел JSON
	JsonPtr json = Json::create("node");

	// Добавляем объект с дочерней строкой
	JsonPtr json_1 = json->addChild();
	json_1->setObject();
	json_1->setName("object");
	json_1->addChild("child", "hello from json");

	// Создаём массив и добавляем в него несколько дочерних элементов
	JsonPtr array = json->addChild("array");
	array->setArray();

	// Первый элемент массива: объект с числом
	JsonPtr array_1 = array->addChild("array_child_0");
	array_1->setObject();
	array_1->addChild("object_child_number", 12);

	// Второй элемент массива: строка
	JsonPtr array_2 = array->addChild("array_child_1");
	array_2->addChild("object_child_string", "some string");

	// Третий элемент массива: булево значение
	JsonPtr array_3 = array->addChild("array_child_2");
	JsonPtr bool_child = array_3->addChild("object_child_bool");
	bool_child->setBool(true);

	// Четвёртый элемент массива: значение null
	JsonPtr array_4 = array->addChild("array_child_3");
	JsonPtr null_child = array_4->addChild("object_child_null", false);
	null_child->setNull();

	return json;
}

// Выводит всё дерево JSON в консоль с форматированием.
void JsonSample::json_print(const JsonPtr &json)
{
	// Выводим дерево JSON, начиная с корня
	json_print_node(json, 0);
}


// Рекурсивная функция вывода JSON
// Проходит по объектам, массивам и значениям, затем красиво их форматирует
void JsonSample::json_print_node(const JsonPtr &json, int offset, int index, bool print_name)
{
	bool is_comma_needed = false;
	JsonPtr parent = json->getParent();
	if (parent)
	{
		is_comma_needed = parent->getNumChildren() != index;
	}

	// Обрабатываем тип object
	if (json->isObject())
	{
		if (print_name)
		{
			print_string_offset(String::format("%s: {", json->getName()).get(), offset);
		}
		else
		{
			print_string_offset("{", offset);
		}
		const int num_children = json->getNumChildren();
		for (int i = 0; i < num_children; i++)
		{
			json_print_node(json->getChild(i), offset + 1, i + 1);
		}
		print_string_offset("}", offset, is_comma_needed);
	}

	// Обрабатываем тип array
	if (json->isArray())
	{
		if (print_name)
		{
			print_string_offset(String::format("%s: [", json->getName()).get(), offset);
		}
		else
		{
			print_string_offset("[", offset);
		}
		const int num_children = json->getNumChildren();
		for (int i = 0; i < num_children; i++)
		{
			JsonPtr child = json->getChild(i);
			json_print_node(child, offset + 1, i + 1, false);
		}
		print_string_offset("]", offset, is_comma_needed);
	}

	// Обрабатываем тип number
	if (json->isNumber())
	{
		if (print_name)
		{
			print_string_offset(
				String::format("%s: %.2f", json->getName(), json->getNumber()).get(), offset,
				is_comma_needed);
		}
		else
		{
			print_string_offset(String::format("%.2f", json->getNumber()).get(), is_comma_needed);
		}
	}

	// Обрабатываем тип string
	if (json->isString())
	{
		if (print_name)
		{
			print_string_offset(
				String::format("%s: \"%s\"", json->getName(), json->getString().get()).get(),
				offset, is_comma_needed);
		}
		else
		{
			print_string_offset(String::format("\"%s\"", json->getString().get()).get(), offset,
				is_comma_needed);
		}
	}

	// Обрабатываем тип boolean
	if (json->isBool())
	{
		String value = json->getBool() ? "true" : "false";
		if (print_name)
		{
			print_string_offset(String::format("%s: %s", json->getName(), value.get()).get(),
				offset, is_comma_needed);
		}
		else
		{
			print_string_offset(String::format("%s", value.get()).get(), offset, is_comma_needed);
		}
	}

	// Обрабатываем тип null
	if (json->isNull())
	{
		if (print_name)
		{
			print_string_offset(String::format("%s: null", json->getName()).get(), offset,
				is_comma_needed);
		}
		else
		{
			print_string_offset("null", offset, is_comma_needed);
		}
	}
}

// Утилита для вывода строк с отступом и опциональной запятой
void JsonSample::print_string_offset(const Unigine::String &value, int offset, bool print_comma)
{
	for (int i = 0; i < offset; ++i)
	{
		Log::message("\t");
	}
	Log::message("%s", value.get());
	if (print_comma)
	{
		Log::message(",");
	}
	Log::message("\n");
}

// Sample Logic
REGISTER_COMPONENT(JsonSample)

// Консоль включается, дерево JSON создаётся и выводится.
void JsonSample::init()
{
	is_console_onscreen = Console::isOnscreen();
	Console::setOnscreen(true);

	{
		// Создаём дерево JSON
		const JsonPtr json = json_create();

		// Выводим его в консоль
		json_print(json);
	}
}

// Состояние консоли восстанавливается к исходному значению.
void JsonSample::shutdown()
{
	Console::setOnscreen(is_console_onscreen);
}
