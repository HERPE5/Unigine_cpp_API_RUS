#pragma once

#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>

// Демонстрирует систему коллбэков Unigine для отложенного вызова функций.
// MakeCallback() оборачивает свободные функции и методы экземпляра в объекты CallbackBase,
// которые можно выполнить позже со значениями по умолчанию или аргументами, заданными во время выполнения.
// Поддерживает функции с 0-4 аргументами со связыванием аргументов на момент создания.
class Callbacks final : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(Callbacks, ComponentBase)
	COMPONENT_DESCRIPTION("This component demonstrates the Unigine callback system by wrapping free functions "
			"and member methods into Callback objects and executing them with different arguments.")

	COMPONENT_INIT(init)
	COMPONENT_SHUTDOWN(shutdown)


private:
	void init();
	void shutdown();

	// Примеры методов экземпляра для вызова через коллбэки
	void method_0();
	void method_1(int a);
	void method_2(int a, int b);
	void method_3(int a, int b, int c);
	void method_4(int a, int b, int c, int d);
};
