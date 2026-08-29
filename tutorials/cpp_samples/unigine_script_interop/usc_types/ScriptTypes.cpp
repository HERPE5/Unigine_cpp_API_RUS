// Демонстрирует пользовательскую маршализацию типов между C++ и UnigineScript. Класс MyVector3
// становится совместимым со скриптом через специализации шаблонов TypeToVariable и VariableToType,
// которые преобразуют между MyVector3 и встроенным типом vec3 для бесшовного взаимодействия.

#include "ScriptTypes.h"

#include "../../utils/UnigineScriptsInterpreter.h"

#include <UnigineInterface.h>
#include <UnigineWorld.h>
#include <UnigineConsole.h>

REGISTER_COMPONENT(ScriptTypes)

using namespace Unigine;
using namespace Unigine::Math;

// ============================================================================
// Пользовательский класс вектора - напрямую не совместим с UnigineScript
// ============================================================================

// Пользовательский 3D-вектор с приватными полями и методами доступа
class MyVector3
{
public:
	MyVector3()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
	{}
	MyVector3(float x, float y, float z)
		: x(x)
		, y(y)
		, z(z)
	{}

	float X() const { return x; }
	float Y() const { return y; }
	float Z() const { return z; }
	float &X() { return x; }
	float &Y() { return y; }
	float &Z() { return z; }

private:
	float x;
	float y;
	float z;
};

// Сложение векторов с использованием пользовательского типа
MyVector3 my_add(const MyVector3 &v0, const MyVector3 &v1)
{
	return MyVector3(v0.X() + v1.X(), v0.Y() + v1.Y(), v0.Z() + v1.Z());
}

// Вычитание векторов с использованием пользовательского типа
MyVector3 my_sub(MyVector3 v0, MyVector3 v1)
{
	return MyVector3(v0.X() - v1.X(), v0.Y() - v1.Y(), v0.Z() - v1.Z());
}

// Скалярное произведение с использованием пользовательского типа
float my_vec_dot(MyVector3 v0, MyVector3 v1)
{
	return v0.X() * v1.X() + v0.Y() * v1.Y() + v0.Z() * v1.Z();
}

// ============================================================================
// Шаблоны преобразования типов - обеспечивают маршализацию MyVector3 <-> vec3
// ============================================================================

namespace Unigine
{
// Преобразует MyVector3 в Variable (для возврата в скрипт)
template<>
struct TypeToVariable<MyVector3>
{
	TypeToVariable(void *i, const MyVector3 &v) { value.setVec3(vec3(v.X(), v.Y(), v.Z())); }
	Variable value;
};

// Преобразует Variable в MyVector3 (для получения из скрипта, по значению)
template<>
struct VariableToType<MyVector3>
{
	VariableToType(void *i, const Variable &variable)
	{
		vec3 v = variable.getVec3();
		value = MyVector3(v.x, v.y, v.z);
	}
	MyVector3 value;
};

// Преобразует Variable в MyVector3 (для получения из скрипта, по константной ссылке)
template<>
struct VariableToType<const MyVector3 &>
{
	VariableToType(void *i, const Variable &variable)
	{
		vec3 v = variable.getVec3();
		value = MyVector3(v.x, v.y, v.z);
	}
	MyVector3 value;
};
} // namespace Unigine

// ============================================================================
// Регистрация функций
// ============================================================================

// Отложенная регистрация: экспортирует функции векторной математики с использованием пользовательского типа
USCInterpreter types_interpreter([]() {
	Interpreter::addExternFunction("my_add", MakeExternFunction(my_add));
	Interpreter::addExternFunction("my_sub", MakeExternFunction(my_sub));
	Interpreter::addExternFunction("my_vec_dot", MakeExternFunction(my_vec_dot));
});


// Настраивает экранную консоль для отображения результатов преобразования типов
void ScriptTypes::init()
{
	Console::setOnscreen(true);
	Console::setOnscreenFontSize(15);
	Console::setOnscreenTime(1000);
	Console::setOnscreenHeight(100);
}

// Восстанавливает настройки консоли по умолчанию
void ScriptTypes::shutdown()
{
	Console::setOnscreen(false);
	Console::setOnscreenHeight(30);
}
