#pragma once

#include <UnigineComponentSystem.h>
#include "../../menu_ui/SampleDescriptionWindow.h"

// Демонстрирует все четыре паттерна подключения событий в UNIGINE:
// 1. EventConnection - одиночный коллбэк с управлением включением/отключением
// 2. EventConnections - несколько коллбэков с общим временем жизни
// 3. Наследование от EventConnections - автоматическая очистка при уничтожении
// 4. connectUnsafe() с EventConnectionId - ручное управление временем жизни
class EventsSample : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(EventsSample, ComponentBase)
	COMPONENT_DESCRIPTION("This component demonstrates different ways to connect and manage UNIGINE events.")

	COMPONENT_INIT(init)
	COMPONENT_SHUTDOWN(shutdown)


private:
	// Вспомогательный класс, владеющий событием и запускающий его для демонстрации
	class EventHolder
	{
	public:
		Unigine::Event<int> &getEvent() { return event; } // возвращает событие для подписки
		void run(int value); // запускает событие с заданным значением

	private:
		Unigine::EventInvoker<int> event; // событие, которое можно вызывать и на которое можно подписываться
	};

	// Пример наследования от EventConnections для автоматического управления коллбэками.
	// Все подключённые коллбэки отсоединяются при уничтожении этого объекта.
	class InheritedEventConnectionExample final : public EventConnections
	{
	public:
		void subscribe(Unigine::Event<int> &event);
		void unsubscribe();

	private:
		Unigine::EventInvoker<int> event;
	};

	// Пример одиночного EventConnection,
	// позволяющего вручную включать/отключать коллбэк.
	class EventConnectionExample
	{
	public:
		void subscribe(Unigine::Event<int> &event);
		void unsubscribe();

	private:
		Unigine::EventConnection connection;
	};


	// Пример управления несколькими коллбэками с помощью EventConnections.
	// Коллбэки автоматически отсоединяются при уничтожении объекта или вызове disconnectAll().
	class EventConnectionsExample
	{
	public:
		void subscribe(Unigine::Event<int> &event);
		void unsubscribe();

	private:
		Unigine::EventConnections connections;
	};


	// Пример небезопасного подключения, где время жизни коллбэка нужно управлять самостоятельно.
	// Используйте только если точно понимаете, что делаете.
	class CallbackIDConnection
	{
	public:
		void subscribe(Unigine::Event<int> &event);
		void unsubscribe(Unigine::Event<int> &event);

	private:
		Unigine::EventConnectionId callback_id{};
	};

private:
	void init();
	void shutdown();

private:
	EventHolder holder; // источник событий, на который подписываются все примеры

	// По одному экземпляру каждого паттерна подключения для демонстрации
	InheritedEventConnectionExample inherited_event_connection_example;
	EventConnectionExample event_connection_example;
	EventConnectionsExample event_connections_example;
	CallbackIDConnection callback_id_connection;
};
