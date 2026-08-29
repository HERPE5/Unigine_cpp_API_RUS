// Демонстрирует MakeCallback() для создания типобезопасных обёрток функций. Показывает связывание
// свободных функций и методов экземпляра, предварительное связывание аргументов на момент создания и
// переопределение связанных аргументов во время выполнения через run() с разным количеством аргументов.

#include "Callbacks.h"

#include <UnigineConsole.h>

REGISTER_COMPONENT(Callbacks)

using namespace Unigine;
using namespace Unigine::Math;


// Свободные функции в анонимном пространстве имён - демонстрируют оборачивание коллбэков
// для отдельных функций (в отличие от методов экземпляра)
namespace
{
static void function_0()
{
	Log::message("function_0(): called\n");
}

static void function_1(int a)
{
	Log::message("function_1(%d): called\n", a);
}

static void function_2(int a, int b)
{
	Log::message("function_2(%d,%d): called\n", a, b);
}

static void function_3(int a, int b, int c)
{
	Log::message("function_3(%d,%d,%d): called\n", a, b, c);
}

static void function_4(int a, int b, int c, int d)
{
	Log::message("function_4(%d,%d,%d,%d): called\n", a, b, c, d);
}
} 

void Callbacks::init()
{
	Console::setOnscreen(true);

	// MakeCallback() связывает аргументы на момент создания.
	// Для методов экземпляра первым аргументом является экземпляр объекта.
	// Аргументы можно переопределить при вызове run() - аргументы времени выполнения имеют приоритет.
	CallbackBase *callback_func_0 = MakeCallback(function_0);
	CallbackBase *callback_method_0 = MakeCallback(this, &Callbacks::method_0);
	CallbackBase *callback_func_1 = MakeCallback(function_1, 1);
	CallbackBase *callback_method_1 = MakeCallback(this, &Callbacks::method_1, 1);
	CallbackBase *callback_func_2 = MakeCallback(function_2, 1, 2);
	CallbackBase *callback_method_2 = MakeCallback(this, &Callbacks::method_2, 1, 2);
	CallbackBase *callback_func_3 = MakeCallback(function_3, 1, 2, 3);
	CallbackBase *callback_method_3 = MakeCallback(this, &Callbacks::method_3, 1, 2, 3);
	CallbackBase *callback_func_4 = MakeCallback(function_4, 1, 2, 3, 4);
	CallbackBase *callback_method_4 = MakeCallback(this, &Callbacks::method_4, 1, 2, 3, 4);

	// Демонстрируем переопределение аргументов: run() с аргументами заменяет связанные аргументы слева
	Log::message("\n");
	callback_func_0->run();
	callback_method_0->run();

	Log::message("\n");
	callback_func_1->run();
	callback_func_1->run(-1);
	callback_method_1->run();
	callback_method_1->run(-1);

	Log::message("\n");
	callback_func_2->run();
	callback_func_2->run(-1);
	callback_func_2->run(-1, -2);
	callback_method_2->run();
	callback_method_2->run(-1);
	callback_method_2->run(-1, -2);

	Log::message("\n");
	callback_func_3->run();
	callback_func_3->run(-1);
	callback_func_3->run(-1, -2);
	callback_func_3->run(-1, -2, -3);
	callback_method_3->run();
	callback_method_3->run(-1);
	callback_method_3->run(-1, -2);
	callback_method_3->run(-1, -2, -3);

	Log::message("\n");
	callback_func_4->run();
	callback_func_4->run(-1);
	callback_func_4->run(-1, -2);
	callback_func_4->run(-1, -2, -3);
	callback_func_4->run(-1, -2, -3, -4);
	callback_method_4->run();
	callback_method_4->run(-1);
	callback_method_4->run(-1, -2);
	callback_method_4->run(-1, -2, -3);
	callback_method_4->run(-1, -2, -3, -4);

	Log::message("\n");
}

void Callbacks::shutdown()
{
	Console::setOnscreen(false);
}

// Реализация методов экземпляра
void Callbacks::method_0()
{
	Log::message("Callbacks::method_0(): called\n");
}

void Callbacks::method_1(int a)
{
	Log::message("Callbacks::method_1(%d): called\n", a);
}

void Callbacks::method_2(int a, int b)
{
	Log::message("Callbacks::method_2(%d,%d): called\n", a, b);
}

void Callbacks::method_3(int a, int b, int c)
{
	Log::message("Callbacks::method_3(%d,%d,%d): called\n", a, b, c);
}

void Callbacks::method_4(int a, int b, int c, int d)
{
	Log::message("Callbacks::method_4(%d,%d,%d,%d): called\n", a, b, c, d);
}
