#pragma once

#include <UnigineComponentSystem.h>

// Подписчик событий, демонстрирующий различные паттерны подключения.
// Показывает привязку метода экземпляра, лямбду с захваченной ссылкой на узел,
// EventConnection для управления включением/отключением и EventConnectionId для ручного управления.
class EventsAdvancedUnit
	: public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(EventsAdvancedUnit, Unigine::ComponentBase);
	COMPONENT_DESCRIPTION("This component demonstrates advanced event subscriptions "
						"using methods, lambdas, and connection IDs.");

	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	PROP_PARAM(Node, input_manager); // узел с EventsAdvancedSample, на который подписываемся

private:
	void init();
	void shutdown();

	// обработчики событий для разных осей вращения
	void rotate(float x, float y, float z);                                   // обработчик - метод экземпляра
	static void rotateNode(float x, float y, float z, Unigine::NodePtr node); // статический обработчик для XYZ
	static void rotateNodeY(float angle, Unigine::NodePtr node);              // статический обработчик для оси Y

private:
	// объекты подключения для разных паттернов подписки
	Unigine::EventConnection rotate_y_connection;     // для управления включением/отключением
	Unigine::EventConnectionId rotate_z_connection_id; // для ручного отключения по ID
	Unigine::EventConnectionId rotate_connection_id;   // для ручного отключения по ID
};
