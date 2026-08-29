// Компонент-подписчик, подключающийся к событиям EventsAdvancedSample. Показывает
// различные паттерны подключения: метод экземпляра с дополнительными аргументами, статическую функцию с
// EventConnection, лямбду с connectUnsafe() и отбрасывание аргументов.

#include "EventsAdvancedUnit.h"
#include "EventsAdvancedSample.h"

REGISTER_COMPONENT(EventsAdvancedUnit);

using namespace Unigine;

// Демонстрируются четыре разных паттерна подключения: метод экземпляра, статическая функция
// с EventConnection, лямбда с connectUnsafe и отбрасывание аргументов.
void EventsAdvancedUnit::init()
{
	auto inputManager = getComponent<EventsAdvancedSample>(input_manager);

	if (!inputManager)
		return;

	// Подключаемся к методу класса с дополнительными параметрами.
	// Работает внутри компонента, так как Unigine::ComponentBase наследуется от EventConnection
	inputManager->getEventRotateX().connect(this, &EventsAdvancedUnit::rotate, 0.0f, 0.0f);

	// Подключаемся к функции и EventConnection с дополнительным параметром
	inputManager->getEventRotateY().connect(rotate_y_connection, rotateNodeY, node);

	// Подключаемся к лямбде и сохраняем EventConnectionId для последующего отключения
	rotate_z_connection_id = inputManager->getEventRotateZ().connectUnsafe([this](float angle) {
		Log::message("Rotate Z   (0.0 0.0 %.1f)!\n", angle);
		node->rotate(0, 0, angle);
	});

	// Подключаемся к функции с отбрасыванием аргумента и сохраняем EventConnectionId для последующего отключения
	rotate_connection_id = inputManager->getEventRotate().connectUnsafe(rotateNode, node);
}

// Все четыре паттерна подключения отключаются с помощью соответствующих методов.
void EventsAdvancedUnit::shutdown()
{
	auto inputManager = getComponent<EventsAdvancedSample>(input_manager);

	if (!inputManager)
		return;

	// Отключаем метод класса
	// Работает внутри компонента, так как Unigine::ComponentBase наследуется от EventConnection
	inputManager->getEventRotateX().disconnect(this, &EventsAdvancedUnit::rotate);

	// Отключаем EventConnection
	rotate_y_connection.disconnect();

	// Отключаем по EventConnectionId
	inputManager->getEventRotateZ().disconnect(rotate_z_connection_id);

	// Отключаем по EventConnectionId
	inputManager->getEventRotate().disconnect(rotate_connection_id);
}

// Обработчик - метод экземпляра: получает угол X из события, Y и Z - дополнительные аргументы (0.0).
void EventsAdvancedUnit::rotate(float x, float y, float z)
{
	Log::message("Rotate X   (%.1f %.1f %.1f)!\n", x, y, z);
	node->rotate(x, y, z);
}

// Статический обработчик для комбинированного события XYZ. Узел передаётся как дополнительный аргумент.
void EventsAdvancedUnit::rotateNode(float x, float y, float z, Unigine::NodePtr node)
{
	Log::message("Rotate XYZ (%.1f %.1f %.1f)!\n", x, y, z);
	if (node)
		node->rotate(x, y, z);
}

// Статический обработчик для вращения по оси Y. Узел передаётся как дополнительный аргумент.
void EventsAdvancedUnit::rotateNodeY(float angle, Unigine::NodePtr node)
{
	Log::message("Rotate Y   (0.0 %.1f 0.0)!\n", angle);
	if (node)
		node->rotate(0, angle, 0);
}
