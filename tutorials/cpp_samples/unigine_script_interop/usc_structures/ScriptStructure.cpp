// Демонстрирует экспорт структур C++ в UnigineScript с помощью ExternClass. Структура MyVector
// предоставляется с автоматически сгенерированными функциями получения/установки через addSetFunction и
// addGetFunction, которые создают аксессоры свойств из указателей на переменные-члены.

#include "ScriptStructure.h"

#include "../../utils/UnigineScriptsInterpreter.h"

#include <UnigineInterface.h>
#include <UnigineWorld.h>
#include <UnigineConsole.h>

REGISTER_COMPONENT(ScriptStructure)

using namespace Unigine;

// ============================================================================
// Extern-структура - простой контейнер данных, экспортированный в скрипт
// ============================================================================

// Структура 4-компонентного вектора с публичными полями
struct MyVector
{
	MyVector()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
		, w(0.0f)
	{}

	float x;
	float y;
	float z;
	float w;
};

// ============================================================================
// Регистрация структуры
// ============================================================================

// Отложенная регистрация: предоставляет MyVector с автоматически сгенерированными аксессорами свойств
USCInterpreter structure_interpreter([]() {
	ExternClass<MyVector> *my_vector = MakeExternClass<MyVector>();
	my_vector->addConstructor();
	my_vector->addSetFunction("setX", &MyVector::x);
	my_vector->addGetFunction("getX", &MyVector::x);
	my_vector->addSetFunction("setY", &MyVector::y);
	my_vector->addGetFunction("getY", &MyVector::y);
	my_vector->addSetFunction("setZ", &MyVector::z);
	my_vector->addGetFunction("getZ", &MyVector::z);
	my_vector->addSetFunction("setW", &MyVector::w);
	my_vector->addGetFunction("getW", &MyVector::w);
	Interpreter::addExternClass("MyVector", my_vector);
});


// Настраивает экранную консоль для отображения результатов операций со структурой
void ScriptStructure::init()
{
	Console::setOnscreen(true);
	Console::setOnscreenFontSize(15);
	Console::setOnscreenTime(1000);
	Console::setOnscreenHeight(100);
}

// Восстанавливает настройки консоли по умолчанию
void ScriptStructure::shutdown()
{
	Console::setOnscreen(false);
	Console::setOnscreenHeight(30);
}
