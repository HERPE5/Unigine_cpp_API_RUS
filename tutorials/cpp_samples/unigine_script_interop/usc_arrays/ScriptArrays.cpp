// Демонстрирует взаимодействие C++ с массивами UnigineScript. Экспортирует функции для манипуляции
// контейнерами ArrayVector (индексированный) и ArrayMap (ключ-значение) из скрипта. Показывает
// паттерны итерации с прямыми/обратными итераторами для карт.

#include "ScriptArrays.h"

#include "../../utils/UnigineScriptsInterpreter.h"

#include <UnigineConsole.h>
#include <UnigineInterface.h>
#include <UnigineWorld.h>

REGISTER_COMPONENT(ScriptArrays)

using namespace Unigine;


// ============================================================================
// Функции ArrayVector - доступ к индексированному контейнеру из скрипта
// ============================================================================

// Устанавливает элемент по указанному индексу в переданном из скрипта ArrayVector
void my_array_vector_set(const Variable &id, int index, const Variable &v)
{
	ArrayVector vector = ArrayVector::get(Interpreter::get(), id);
	vector.set(index, v);
}

// Возвращает элемент по указанному индексу из переданного из скрипта ArrayVector
Variable my_array_vector_get(const Variable &id, int index)
{
	ArrayVector vector = ArrayVector::get(Interpreter::get(), id);
	return vector.get(index);
}

// ============================================================================
// Функции ArrayMap - доступ к контейнеру ключ-значение из скрипта
// ============================================================================

// Устанавливает значение для заданного ключа в переданном из скрипта ArrayMap
void my_array_map_set(const Variable &id, const Variable &key, const Variable &v)
{
	ArrayMap map = ArrayMap::get(Interpreter::get(), id);
	map.set(key, v);
}

// Возвращает значение для заданного ключа из переданного из скрипта ArrayMap
Variable my_array_map_get(const Variable &id, const Variable &key)
{
	ArrayMap map = ArrayMap::get(Interpreter::get(), id);
	return map.get(key);
}

// ============================================================================
// Функции-генераторы - демонстрируют манипуляцию контейнерами из C++
// ============================================================================

// Заполняет ArrayVector значениями квадратов и строковым элементом
void my_array_vector_generate(const Variable &id)
{
	ArrayVector vector = ArrayVector::get(Interpreter::get(), id);
	vector.clear();
	for (int i = 0; i < 4; i++)
		vector.append(Variable(i * i));
	vector.remove(0);
	vector.append(Variable("128"));
}

// Заполняет ArrayMap парами ключ-значение из квадратов и строковой записью
void my_array_map_generate(const Variable &id)
{
	ArrayMap map = ArrayMap::get(Interpreter::get(), id);
	map.clear();
	for (int i = 0; i < 4; i++)
		map.append(Variable(i * i), Variable(i * i));
	map.remove(Variable(0));
	map.append(Variable(128), Variable("128"));
}

// ============================================================================
// Функции перечисления - демонстрируют паттерны итерации
// ============================================================================

// Перебирает ArrayVector по индексу и логирует информацию о типе каждого элемента
void my_array_vector_enumerate(const Variable &id)
{
	ArrayVector vector = ArrayVector::get(Interpreter::get(), id);
	for (int i = 0; i < vector.size(); i++)
		Log::message("%s %d: %s\n", sourse_str, i, vector.get(i).getTypeInfo().get());
}

// Перебирает ArrayMap от первой до последней записи с помощью прямого итератора
void my_array_map_enumerate_forward(const Variable &id)
{
	ArrayMap map = ArrayMap::get(Interpreter::get(), id);
	ArrayMap::Iterator end = map.end();
	for (ArrayMap::Iterator it = map.begin(); it != end; ++it)
		Log::message("%s %d: %s\n", sourse_str, it.key().getInt(), it.get().getTypeInfo().get());
}

// Перебирает ArrayMap от последней до первой записи с помощью обратного итератора
void my_array_map_enumerate_backward(const Variable &id)
{
	ArrayMap map = ArrayMap::get(Interpreter::get(), id);
	ArrayMap::Iterator end = map.end();
	for (ArrayMap::Iterator it = map.back(); it != end; --it)
		Log::message("%s %d: %s\n", sourse_str, it.key().getInt(), it.get().getTypeInfo().get());
}

// ============================================================================
// Регистрация функций - экспортирует функции C++, вызываемые из UnigineScript
// ============================================================================

// Отложенная регистрация: лямбда выполняется после инициализации движка, перед инициализацией мира
USCInterpreter arrays_interpreter([]() {
	Interpreter::addExternFunction("my_array_vector_set",
		MakeExternFunction(&my_array_vector_set, "[]"));
	Interpreter::addExternFunction("my_array_vector_get",
		MakeExternFunction(&my_array_vector_get, "[]"));
	Interpreter::addExternFunction("my_array_map_set", MakeExternFunction(&my_array_map_set, "[]"));
	Interpreter::addExternFunction("my_array_map_get", MakeExternFunction(&my_array_map_get, "[]"));
	Interpreter::addExternFunction("my_array_vector_generate",
		MakeExternFunction(&my_array_vector_generate, "[]"));
	Interpreter::addExternFunction("my_array_map_generate",
		MakeExternFunction(&my_array_map_generate, "[]"));
	Interpreter::addExternFunction("my_array_vector_enumerate",
		MakeExternFunction(&my_array_vector_enumerate, "[]"));
	Interpreter::addExternFunction("my_array_map_enumerate_forward",
		MakeExternFunction(&my_array_map_enumerate_forward, "[]"));
	Interpreter::addExternFunction("my_array_map_enumerate_backward",
		MakeExternFunction(&my_array_map_enumerate_backward, "[]"));
});


// ============================================================================
// Жизненный цикл компонента
// ============================================================================

// Настраивает экранную консоль для отображения результатов операций с массивами
void ScriptArrays::init()
{
	Console::setOnscreen(true);
	Console::setOnscreenFontSize(15);
	Console::setOnscreenHeight(100);
	Console::setOnscreenTime(1000);
}

// Восстанавливает настройки консоли по умолчанию
void ScriptArrays::shutdown()
{
	Console::setOnscreen(false);
	Console::setOnscreenHeight(30);
}
