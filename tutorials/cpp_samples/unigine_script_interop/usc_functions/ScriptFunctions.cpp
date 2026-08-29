// Демонстрирует экспорт функций C++ в UnigineScript. Показывает экспорт автономных
// функций (my_sum, my_mul, my_dot) и функций-членов класса через addExternLibrary.
// my_sum демонстрирует полиморфизм на основе Variable (обрабатывает типы int и string).

#include "ScriptFunctions.h"

#include "../../utils/UnigineScriptsInterpreter.h"

#include <UnigineInterface.h>
#include <UnigineWorld.h>
#include <UnigineConsole.h>

REGISTER_COMPONENT(ScriptFunctions)

using namespace Unigine;
using namespace Math;

// ============================================================================
// Автономные функции - экспортированы напрямую в UnigineScript
// ============================================================================

// Полиморфная сумма: складывает целые числа или конкатенирует строки, иначе возвращает "unknown"
Variable my_sum(const Variable &v0, const Variable &v1)
{
	if (v0.getType() == Variable::INT && v1.getType() == Variable::INT)
	{
		Log::message("%s my_sum(%d,%d): called\n", sourse_str, v0.getInt(), v1.getInt());
		return Variable(v0.getInt() + v1.getInt());
	}

	if (v0.getType() == Variable::STRING && v1.getType() == Variable::STRING)
	{
		Log::message("%s my_sum(%s,%s): called\n", sourse_str, v0.getString(), v1.getString());
		return Variable((String(v0.getString()) + "+" + String(v1.getString())).get());
	}

	Log::message("%s my_sum(%s,%s): called\n", sourse_str, v0.getTypeName().get(),
		v1.getTypeName().get());
	return Variable("unknown");
}

// Перемножает два float
float my_mul(float a, float b)
{
	Log::message("%s my_mul(%g,%g): called\n", sourse_str, a, b);
	return a * b;
}

// Вычисляет скалярное произведение двух векторов vec3
float my_dot(const vec3 &v0, const vec3 &v1)
{
	Log::message("%s my_dot((%g,%g,%g),(%g,%g,%g)): called\n", sourse_str, v0.x, v0.y, v0.z, v1.x,
		v1.y, v1.z);
	return dot(v0, v1);
}

// ============================================================================
// Класс-синглтон - функции-члены, экспортированные как библиотека
// ============================================================================

// Простой генератор псевдослучайных чисел, предоставленный скрипту как библиотека my_application
class MyApplication
{
public:
	MyApplication()
		: seed(1)
	{}

	void init(int s = 1)
	{
		Log::message("%s MyApplication::init(%d) called\n", sourse_str, s);
		seed = s;
	}

	void shutdown()
	{
		Log::message("%s MyApplication::shutdown() called\n", sourse_str);
		seed = 1;
	}

	int update()
	{
		seed = (seed * 3877 + 29573) % 139968;
		return seed;
	}

	int get() const { return seed; }

private:
	int seed;
} my_application;

// ============================================================================
// Регистрация функций
// ============================================================================

// Отложенная регистрация: экспортирует автономные функции и библиотеку my_application
USCInterpreter functions_interpreter([]() {
	// Экспортируем автономные функции
	Interpreter::addExternFunction("my_sum", MakeExternFunction(&my_sum, ",1"));
	Interpreter::addExternFunction("my_mul", MakeExternFunction(&my_mul));
	Interpreter::addExternFunction("my_dot", MakeExternFunction(&my_dot));

	// Экспортируем методы синглтона как библиотеку my_application.*
	Interpreter::addExternLibrary("my_application");
	Interpreter::addExternFunction("my_application.init",
		MakeExternObjectFunction(&my_application, &MyApplication::init, "1"));
	Interpreter::addExternFunction("my_application.shutdown",
		MakeExternObjectFunction(&my_application, &MyApplication::shutdown));
	Interpreter::addExternFunction("my_application.update",
		MakeExternObjectFunction(&my_application, &MyApplication::update));
	Interpreter::addExternFunction("my_application.get",
		MakeExternObjectFunction(&my_application, &MyApplication::get));
});


// Настраивает экранную консоль для отображения результатов вызовов функций
void ScriptFunctions::init()
{
	Console::setOnscreen(true);
	Console::setOnscreenFontSize(15);
	Console::setOnscreenTime(1000);
	Console::setOnscreenHeight(100);
}

// Восстанавливает настройки консоли по умолчанию
void ScriptFunctions::shutdown()
{
	Console::setOnscreen(false);
	Console::setOnscreenHeight(30);
}
