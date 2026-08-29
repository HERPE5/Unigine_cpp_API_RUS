// Демонстрирует Unigine::Xml API для создания и обхода структур XML.
// Показывает построение иерархического дерева с вложенными узлами, атрибутами и данными.
// Рекурсивная функция вывода отображает структуру с отступами на основе глубины.

#include "XmlSample.h"

#include <UnigineConsole.h>

using namespace Unigine;
using namespace Math;

// Создаёт иерархическую структуру XML с вложенными узлами и атрибутами
XmlPtr XmlSample::xml_create()
{
	XmlPtr xml = Xml::create("node");
	XmlPtr xml_0 = XmlPtr(xml->addChild("child", "arg=\"0\""));
	XmlPtr xml_1 = XmlPtr(xml_0->addChild("child", "arg=\"1\""));
	XmlPtr xml_2 = XmlPtr(xml_1->addChild("child", "arg=\"2\""));
	xml_2->setData("some data");
	return xml;
}

// Рекурсивно выводит структуру XML с отступами для визуализации иерархии
void XmlSample::xml_print(Unigine::XmlPtr xml, int offset)
{
	// Создаём отступ на основе глубины узла
	for (int i = 0; i < offset; i++)
	{
		Log::message(" ");
	}

	// Выводим имя узла, атрибуты и данные
	Log::message("%s: ", xml->getName());
	for (int i = 0; i < xml->getNumArgs(); ++i)
	{
		Log::message("%s=%s ", xml->getArgName(i), xml->getArgValue(i));
	}
	Log::message(": %s\n", xml->getData());

	// Рекурсивно выводим все дочерние узлы
	for (int i = 0; i < xml->getNumChildren(); i++)
	{
		xml_print(XmlPtr(xml->getChild(i)), offset + 1);
	}
}


// Sample Logic

REGISTER_COMPONENT(XmlSample)

void XmlSample::init()
{
	Console::setOnscreen(true);

	{
		Log::message("\n");
		// Создаём структуру XML и выводим её иерархическое содержимое
		XmlPtr xml = xml_create();
		xml_print(xml, 0);
	}
}

void XmlSample::shutdown()
{
	Console::setOnscreen(false);
}
