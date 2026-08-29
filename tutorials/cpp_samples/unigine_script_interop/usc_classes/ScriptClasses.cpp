// Демонстрирует экспорт классов C++ в UnigineScript. Показывает два подхода:
// 1) Хранение пользовательских объектов скрипта в C++ с помощью Variable
// 2) Экспорт классов C++ (MyExternObject) с конструкторами и методами через ExternClass

#include "ScriptClasses.h"

#include "../../utils/UnigineScriptsInterpreter.h"

#include <UnigineInterface.h>
#include <UnigineWorld.h>
#include <UnigineConsole.h>

REGISTER_COMPONENT(ScriptClasses)

using namespace Unigine;
using namespace Math;


// ============================================================================
// Паттерн пользовательского класса - хранение объектов скрипта в C++
// ============================================================================

// Хранит ссылку на пользовательский объект, созданный скриптом
Variable user_object;

// Сохраняет ссылку на объект скрипта, переданную из UnigineScript
void SetMyUserObject(Variable &v)
{
	Log::message("%s SetMyUserObject(%s): called\n", sourse_str, v.getTypeName().get());
	user_object = v;
}

// Возвращает сохранённую ссылку на объект скрипта обратно в UnigineScript
const Variable &GetMyUserObject()
{
	Log::message("%s GetMyUserObject(): called\n", sourse_str);
	return user_object;
}

// ============================================================================
// Паттерн Extern Class - предоставление класса C++ скрипту
// ============================================================================

// Конструктор по умолчанию, инициализирует mass нулём
MyExternObject::MyExternObject()
	: mass(0.0f)
{
	Log::message("%s MyExternObject::MyExternObject(): called\n", sourse_str);
}

// Параметризованный конструктор с size и mass
MyExternObject::MyExternObject(const vec3 &size, float mass)
	: size(size)
	, mass(mass)
{
	Log::message("%s MyExternObject::MyExternObject((%g,%g,%g),%g): called\n", sourse_str, size.x,
		size.y, size.z, mass);
}

MyExternObject::~MyExternObject()
{
	Log::message("%s MyExternObject::~MyExternObject(): called\n", sourse_str);
}

void MyExternObject::setSize(const vec3 &s)
{
	Log::message("%s MyExternObject::setSize((%g,%g,%g)): called\n", sourse_str, s.x, s.y, s.z);
	size = s;
}

void MyExternObject::setMass(float m)
{
	Log::message("%s MyExternObject::setMass(%g): called\n", sourse_str, m);
	mass = m;
}

// ============================================================================
// Альтернативный API - свободные функции, оборачивающие методы класса
// ============================================================================

// Фабричная функция для создания MyExternObject из скрипта
MyExternObject *MakeMyExternObject(const vec3 &size, float mass)
{
	return new MyExternObject(size, mass);
}

// Обёртка деструктора для очистки на стороне скрипта
void DeleteMyExternObject(MyExternObject *object)
{
	delete object;
}

// Свободная функция-обёртка для метода setSize
void MyExternObjectSetSize(MyExternObject *object, const vec3 &size)
{
	object->setSize(size);
}

// Свободная функция-обёртка для метода getSize
const vec3 &MyExternObjectGetSize(MyExternObject *object)
{
	return object->getSize();
}

// ============================================================================
// Регистрация функций
// ============================================================================

// Отложенная регистрация: экспортирует функции пользовательского объекта и класс MyExternObject
USCInterpreter calsses_interpreter([]() {
	Interpreter::addExternFunction("SetMyUserObject", MakeExternFunction(&SetMyUserObject));
	Interpreter::addExternFunction("GetMyUserObject", MakeExternFunction(&GetMyUserObject));

	// Экспортируем класс MyExternObject с конструкторами и методами
	ExternClass<MyExternObject> *my_object = MakeExternClass<MyExternObject>();
	my_object->addConstructor();
	my_object->addConstructor<const vec3 &, float>();
	my_object->addFunction("setSize", &MyExternObject::setSize);
	my_object->addFunction("getSize", &MyExternObject::getSize);
	my_object->addFunction("setMass", &MyExternObject::setMass);
	my_object->addFunction("getMass", &MyExternObject::getMass);
	Interpreter::addExternClass("MyExternObject", my_object);

	// Экспортируем обёртки свободных функций как альтернативный API
	Interpreter::addExternFunction("DeleteMyExternObject",
		MakeExternFunction(&DeleteMyExternObject));
	Interpreter::addExternFunction("MakeMyExternObject", MakeExternFunction(&MakeMyExternObject));
	Interpreter::addExternFunction("MyExternObjectSetSize",
		MakeExternFunction(&MyExternObjectSetSize));
	Interpreter::addExternFunction("MyExternObjectGetSize",
		MakeExternFunction(&MyExternObjectGetSize));
});


// Настраивает экранную консоль для отображения результатов операций с классами
void ScriptClasses::init()
{
	Console::setOnscreen(true);
	Console::setOnscreenFontSize(15);
	Console::setOnscreenTime(1000);
	Console::setOnscreenHeight(100);
}

// Восстанавливает настройки консоли по умолчанию
void ScriptClasses::shutdown()
{
	Console::setOnscreen(false);
	Console::setOnscreenHeight(30);
}
