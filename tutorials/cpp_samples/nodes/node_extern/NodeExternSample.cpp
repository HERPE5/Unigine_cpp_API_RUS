// Демонстрирует NodeExtern для создания пользовательских типов узлов с индивидуальным поведением.
// NodeExternBase предоставляет интерфейс для пользовательских узлов, интегрирующихся со
// сценовым графом движка. Пользовательские узлы могут определять собственные ограничивающие объёмы, визуализацию
// и методы, оставаясь при этом управляемыми через стандартный API Node.

#include <UnigineComponentSystem.h>
#include <UnigineMathLib.h>
#include <UnigineVisualizer.h>
#include <UnigineGame.h>

#include "../../menu_ui/SampleDescriptionWindow.h"

using namespace Unigine;
using namespace Math;

// Пользовательский класс узла, наследуемый от NodeExternBase
class MyNode : public NodeExternBase
{
public:
	// Уникальный идентификатор этого типа узла (используется при сериализации и создании через фабрику)
	static constexpr int id = 1;

	// Конструктор по умолчанию: вызывается при программном создании узла
	MyNode()
	{
		Log::message("MyNode::MyNode(): called\n");
	}

	// Конструктор фабрики: вызывается при загрузке узла из файла или создании через NodeExtern::create()
	// Параметр void* - это внутренний дескриптор узла
	MyNode(void *node): NodeExternBase(node)
	{
		Log::message("MyNode::MyNode(void*): called\n");
	}

	~MyNode() override
	{
		Log::message("MyNode::~MyNode(): called\n");
	}

	// Возвращает зарегистрированный ID класса для идентификации типа
	int getClassID() override { return id; }

	// Определяет ограничивающий объём в локальном пространстве для отсечения и выбора
	const BoundBox &getBoundBox() override { return bbox; }

	// Пользовательский рендеринг для отладочной визуализации
	void renderVisualizer() override
	{
		// Отрисовываем ограничивающий объём в мировом пространстве, используя трансформацию узла
		Visualizer::renderBoundBox(bbox, getNode()->getWorldTransform(), color);
	}

	// Пользовательский метод: демонстрирует расширение функциональности узла
	void setColor(const vec4 &color)
	{
		this->color = color;
	}

private:
	// Ограничивающий объём единичного куба с центром в начале координат
	BoundBox bbox = BoundBox(vec3(-.5f), vec3(.5f));
	// Цвет визуализации для ограничивающего объёма
	vec4 color = vec4_white;
};

class NodeExternSample : public ComponentBase
{
public:
	COMPONENT_DEFINE(NodeExternSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init()
	{
		// Регистрируем пользовательский класс узла в фабрике движка
		// Это позволяет NodeExtern::create() создавать экземпляры MyNode по ID
		NodeExternBase::addClassID<MyNode>(MyNode::id);

		if (true)
		{
			// Предпочтительный способ: создание через фабрику движка
			// Движок управляет временем жизни и интегрируется с сериализацией сцены
			NodeExternPtr node_extern = NodeExtern::create(MyNode::id);
			NodeExternBase *node_extern_base = node_extern->getNodeExtern();
			if (node_extern_base)
			{
				// Приводим к конкретному типу для доступа к пользовательским методам
				my_node = static_cast<MyNode *>(node_extern_base);
			}
		}

		else
		{
			// Альтернатива: прямое создание экземпляра (требует ручного управления памятью)
			my_node = new MyNode();
		}

		if (my_node)
		{
			// Доступ к стандартным методам Node через getNode() (позиция, вращение и т.д.)
			my_node->getNode()->setWorldPosition(Vec3(0.f, 0.f, 1.f));

			// Прямой доступ к пользовательским методам MyNode
			my_node->setColor(vec4_white);
		}

		visualizer_enabled = Visualizer::isEnabled();
		Visualizer::setEnabled(true);
	}

	void update()
	{
		// Отрисовываем визуализацию пользовательского узла каждый кадр
		my_node->renderVisualizer();
	}

	void shutdown()
	{
		Visualizer::setEnabled(visualizer_enabled);
	}

	// ========================================================================================

	bool visualizer_enabled = false;
	// Указатель на пользовательский узел (принадлежит NodeExtern, а не этому компоненту)
	MyNode *my_node = nullptr;
};

REGISTER_COMPONENT(NodeExternSample);
