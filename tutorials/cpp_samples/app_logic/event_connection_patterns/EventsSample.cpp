// Демонстрирует четыре паттерна подключения к событиям Unigine:
// 1) EventConnection - одиночный коллбэк с управлением включением/отключением
// 2) EventConnections - несколько коллбэков, управляемых как группа
// 3) Наследуемый EventConnections - класс наследует управление подключением
// 4) Callback ID - ручное управление через connectUnsafe() и disconnect(id)

#include "EventsSample.h"

#include <UnigineConsole.h>

using namespace Unigine;

void EventsSample::EventHolder::run(int value)
{
	event.run(value);
}

void EventsSample::InheritedEventConnectionExample::subscribe(Unigine::Event<int> &event)
{
	// Поскольку этот класс наследуется от Unigine::EventConnections,
	// мы можем передать *this в connect(). Объект будет управлять подключением,
	// автоматически отсоединяя коллбэки при уничтожении.
	// Это похоже на EventConnectionsExample.
	event.connect(*this,
		[](int value) { Log::message("InheritedEventConnectionExample event called\n", value); });
}

void EventsSample::InheritedEventConnectionExample::unsubscribe()
{
	// Отсоединяем все события, связанные с этим объектом
	disconnectAll();
}

void EventsSample::EventConnectionExample::subscribe(Unigine::Event<int> &event)
{
	// Передаём объект подключения для хранения коллбэка.
	// Полезно, когда нужен точный контроль над конкретным коллбэком.
	event.connect(connection,
		[](int value) { Log::message("EventConnectionExample event called\n", value); });

	// Включаем или отключаем коллбэк через подключение
	connection.setEnabled(true);
}

void EventsSample::EventConnectionExample::unsubscribe()
{
	// Отсоединяем коллбэк
	connection.disconnect();
}

void EventsSample::EventConnectionsExample::subscribe(Unigine::Event<int> &event)
{
	// Передаём объект Unigine::EventConnections для хранения нескольких коллбэков.
	// Удобно для управления множеством коллбэков сразу, но нельзя включать/отключать по отдельности.
	// Полезно, когда несколько коллбэков имеют общее время жизни.
	event.connect(connections,
		[](int value) { Log::message("EventConnectionsExample event called\n", value); });
}

void EventsSample::EventConnectionsExample::unsubscribe()
{
	// Явное отсоединение не требуется; подключения автоматически очищаются при уничтожении объекта
}

void EventsSample::CallbackIDConnection::subscribe(Unigine::Event<int> &event)
{
	// connectUnsafe возвращает ID, представляющий коллбэк,
	// позволяя вручную управлять (отсоединять или отслеживать) этот конкретный коллбэк
	callback_id = event.connectUnsafe(
		[](int value) { Log::message("CallbackIDConnection event called\n", value); });
}

void EventsSample::CallbackIDConnection::unsubscribe(Unigine::Event<int> &event)
{
	// Сохраняем событие, чтобы позже отсоединить коллбэк по его ID
	// В этом подходе временем жизни коллбэка управляете вы сами
	event.disconnect(callback_id);
}


REGISTER_COMPONENT(EventsSample)

// Подписываются все четыре паттерна подключения, событие вызывается один раз.
void EventsSample::init()
{
	event_connection_example.subscribe(holder.getEvent());
	event_connections_example.subscribe(holder.getEvent());
	inherited_event_connection_example.subscribe(holder.getEvent());
	callback_id_connection.subscribe(holder.getEvent());

	holder.run(42);
	Console::setOnscreen(true);
}

// Все паттерны подключения отписываются, чтобы продемонстрировать очистку.
void EventsSample::shutdown()
{
	event_connection_example.unsubscribe();
	event_connections_example.unsubscribe();
	inherited_event_connection_example.unsubscribe();
	callback_id_connection.unsubscribe(holder.getEvent());

	Console::setOnscreen(false);
}
