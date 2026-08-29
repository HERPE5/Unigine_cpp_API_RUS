# Event Handling Callbacks (CPP)


Callback (callback-функция) — это обёртка функции, представляющая указатель на статические и на функции-члены, которые должны быть выполнены с указанными параметрами в определённый момент. Callback может быть передан в функцию в качестве аргумента.


> **Примечание:** Callback-функции гарантированно реентерабельны и обеспечивают безопасное выполнение в многопоточной среде.


В C++ API UNIGINE класс *[**CallbackBase**](../../../api/library/common/callbacks/class.callbackbase_cpp.md)* является базовым классом для представления callback-функций с переменным числом аргументов от **0** до **5**. Для создания callback-функции используется функция *[*MakeCallback()*](../../../api/library/common/class.unigine.namespace_cpp.md#MakeCallback_Retm)*:


```cpp
void callback_function() {
	/* .. */
}
CallbackBase *callback = MakeCallback(callback_function);

```


Callback к функции-члену как текущего класса, так и другого, создаётся следующим образом:


```cpp
void ThisClass::callback_function() {
	/* .. */
}
/* .. */
// первый аргумент - это экземпляр класса, второй - указатель на функцию-член
CallbackBase *callback = MakeCallback(this, &ThisClass::callback_function);

```


Классы *[**CallbackBase**](../../../api/library/common/callbacks/index.md)* используются для создания callback-функции с фиксированным числом аргументов. В зависимости от количества аргументов следует использовать соответствующий класс. В этом случае необходимо указать шаблонные аргументы:


```cpp
void ThisClass::callback_function(NodePtr, int) {
	/* .. */
}
// создаём callback без предопределённых параметров
CallbackBase2<NodePtr, int> *callback = MakeCallback(this, &ThisClass::callback_function);

// создаём callback с предопределёнными параметрами
CallbackBase2<NodePtr, int> *callback2 = MakeCallback(this, &ThisClass::callback_function, NodeDummy::create()->getNode(), 1);

// создаём callback с параметрами из лямбды
CallbackBase2<NodePtr, int> *callback = MakeCallback([](NodePtr node, int value) { /* .. */ });

// создаём callback с параметрами из обобщённой (generic) лямбды
CallbackBase2<NodePtr, int> *callback = MakeCallback([](auto node, auto value) { /* .. */ });

```


Чтобы использовать перегруженные функции и методы как callback-функции, укажите шаблонные параметры:
*MakeCallback< Class, ReturnType, Callback Parameters Types >*


```cpp
void ThisClass::callback_method()
{
	/* .. */
}

void ThisClass::callback_method(WidgetPtr w, WidgetPtr w2, int i)
{
	/* .. */
}

CallbackBase *callback = MakeCallback<ThisClass, void, WidgetPtr, WidgetPtr, int>(this, &ThisClass::callback_method);

```


Чтобы вызвать пользовательский callback, используется функция *[*run()*](../../../api/library/common/callbacks/class.callbackbase_cpp.md#run_void)* одного из классов *CallbackBase*.


```cpp
// запускаем callback без параметров или с параметрами по умолчанию
callback->run();

// запускаем callback с указанными параметрами
callback->run(node, 2);

```


Вы также можете использовать лямбда-выражения для callback-функций:


```cpp
// создаём callback из лямбды
int value = 5;
CallbackBase* callback = MakeCallback([value](){ /* .. */ });

// или std function
std::function<void()> callable_obj = [value]() { /* .. */ };
CallbackBase* callback = MakeCallback(callable_obj);

// или любой другой вызываемый объект
struct Callable
{
void operator()() const { /* .. */ }
int value;
} callable_obj = { /* .. */ };

CallbackBase* callback = MakeCallback(callable_obj);

```


### Пример использования


В следующем разделе приведён полный исходный код простого примера использования callback-функций.


<details>
<summary>AppWorldLogic.h | Close</summary>

```cpp
#ifndef __APP_WORLD_LOGIC_H__
#define __APP_WORLD_LOGIC_H__

#include <UnigineLogic.h>
#include <UnigineStreams.h>
#include <UnigineCallback.h>

using namespace Unigine;
using namespace Math;

class AppWorldLogic: public Unigine::WorldLogic
{

public:

	int init() override;

	int update() override;
	int postUpdate() override;
	int updatePhysics() override;

	int shutdown() override;
};

#endif // __APP_WORLD_LOGIC_H__

```

</details>


<details>
<summary>AppWorldLogic.cpp | Close</summary>

```cpp
#include "AppWorldLogic.h"

class SomeClass
{
public:
	// функция-член, которая будет вызвана при выполнении действия
	void callback_method(int a, int b)
	{
		Log::message("\tcallback_method has been called %d %d\n", a, b);
	}

	void create_callbacks()
	{
		Log::message("Create a callback with no predefined parameters\n");
		CallbackBase * callback = MakeCallback(this, &SomeClass::callback_method);

		// запускаем callback с двумя параметрами
		callback->run(73, 37);
		// запускаем callback без параметров.
		// если callback-функция имеет аргументы, это приведёт к небезопасному поведению
		callback->run();

		Log::message("Create a callback with predefined parameters\n");
		CallbackBase * callback2 = MakeCallback(this, &SomeClass::callback_method, 1, 2);

		// запускаем callback без параметров. В этом случае будут использованы предопределённые параметры
		callback2->run();
		// запускаем callback с параметрами. Предопределённые параметры будут проигнорированы
		callback2->run(351, 153);
		// запускаем callback только с 1 параметром.
		// второй предопределённый параметр будет использован как второй аргумент
		callback2->run(118);
	}
};

// callback-функция, которая будет вызвана при выполнении действия
void callback_function(int a, int b)
{
	Log::message("\tcallback_function has been called %d %d\n", a, b);
}

int AppWorldLogic::init()
{
	SomeClass *some = new SomeClass();
	// вызываем функцию-член SomeClass
	some->create_callbacks();

	Log::message("Create a callback in the other instance\n");
	// используем callback-функцию SomeClass для создания callback
	CallbackBase * callback3 = MakeCallback(some, &SomeClass::callback_method, 5, 25);
	callback3->run();

	Log::message("Create callback functions\n");
	CallbackBase * callback4 = MakeCallback(&callback_function);
	callback4->run(20, 70);
	CallbackBase * callback5 = MakeCallback(&callback_function, 50, 25);
	callback5->run();

	return 1;
}

int AppWorldLogic::update()
{

	return 1;
}

int AppWorldLogic::postUpdate()
{
	return 1;
}

int AppWorldLogic::updatePhysics()
{
	return 1;
}

int AppWorldLogic::shutdown()
{
	return 1;
}

```

</details>
