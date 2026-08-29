// Демонстрирует систему типов класса Variable для взаимодействия C++/UnigineScript.
// Проверяет все поддерживаемые примитивные и векторные типы, передавая их в функцию
// скрипта и логируя информацию о возвращённом типе.

#include "ScriptVariables.h"

#include "../../utils/UnigineScriptsInterpreter.h"

#include <UnigineInterface.h>
#include <UnigineWorld.h>
#include <UnigineConsole.h>

REGISTER_COMPONENT(ScriptVariables)

using namespace Unigine;
using namespace Unigine::Math;

// ============================================================================
// Функция информации о типе - логирует тип и значение Variable
// ============================================================================

// Проверяет тип Variable и логирует его значение в подходящем формате
void my_typeinfo(const Variable &v)
{
	switch (v.getType())
	{
	case Variable::INT: Log::message("%s my_typeinfo(): int: %d\n", sourse_str, v.getInt()); break;
	case Variable::LONG:
		Log::message("%s my_typeinfo(): long: %lld\n", sourse_str, v.getLong());
		break;
	case Variable::FLOAT:
		Log::message("%s my_typeinfo(): float: %g\n", sourse_str, v.getFloat());
		break;
	case Variable::DOUBLE:
		Log::message("%s my_typeinfo(): double: %g\n", sourse_str, v.getDouble());
		break;
	case Variable::VEC3:
		Log::message("%s my_typeinfo(): vec3: %g %g %g\n", sourse_str, v.getVec3().x, v.getVec3().y,
			v.getVec3().z);
		break;
	case Variable::VEC4:
		Log::message("%s my_typeinfo(): vec4: %g %g %g %g\n", sourse_str, v.getVec4().x,
			v.getVec4().y, v.getVec4().z, v.getVec4().w);
		break;
	case Variable::DVEC3:
		Log::message("%s my_typeinfo(): dvec3: %g %g %g\n", sourse_str, v.getDVec3().x,
			v.getDVec3().y, v.getDVec3().z);
		break;
	case Variable::DVEC4:
		Log::message("%s my_typeinfo(): dvec4: %g %g %g %g\n", sourse_str, v.getDVec4().x,
			v.getDVec4().y, v.getDVec4().z, v.getDVec4().w);
		break;
	case Variable::IVEC3:
		Log::message("%s my_typeinfo(): ivec3: %d %d %d\n", sourse_str, v.getIVec3().x,
			v.getIVec3().y, v.getIVec3().z);
		break;
	case Variable::IVEC4:
		Log::message("%s my_typeinfo(): ivec4: %d %d %d %d\n", sourse_str, v.getIVec4().x,
			v.getIVec4().y, v.getIVec4().z, v.getIVec4().w);
		break;
	}
}

// ============================================================================
// Жизненный цикл компонента - проверяет все типы Variable
// ============================================================================

// Создаёт Variable каждого типа и передаёт в скрипт для сквозного теста
void ScriptVariables::init()
{
	Console::setOnscreen(true);
	Console::setOnscreenFontSize(15);
	Console::setOnscreenTime(1000);
	Console::setOnscreenHeight(100);

	Engine *engine = Engine::get();
	Variable value, ret;

	// Получаем ID функции скрипта для повторных вызовов
	Variable my_typeinfo_id = Variable(engine->getWorldFunction("my_typeinfo", 1));

	// Проверяем тип int
	value.setInt(13);
	ret = engine->runWorldFunction(my_typeinfo_id, value);
	my_typeinfo(ret);

	// Проверяем тип long long
	value.setLong(13LL);
	ret = engine->runWorldFunction(my_typeinfo_id, value);
	my_typeinfo(ret);

	// Проверяем тип float
	value.setFloat(13.0f);
	ret = engine->runWorldFunction(my_typeinfo_id, value);
	my_typeinfo(ret);

	// Проверяем тип double
	value.setDouble(13.0);
	ret = engine->runWorldFunction(my_typeinfo_id, value);
	my_typeinfo(ret);

	// Проверяем тип vec3 (3-компонентный вектор float)
	value.setVec3(vec3(1.0f, 2.0f, 3.0f));
	ret = engine->runWorldFunction(my_typeinfo_id, value);
	my_typeinfo(ret);

	// Проверяем тип vec4 (4-компонентный вектор float)
	value.setVec4(vec4(1.0f, 2.0f, 3.0f, 4.0f));
	ret = engine->runWorldFunction(my_typeinfo_id, value);
	my_typeinfo(ret);

	// Проверяем тип dvec3 (3-компонентный вектор double)
	value.setDVec3(dvec3(1.0, 2.0, 3.0));
	ret = engine->runWorldFunction(my_typeinfo_id, value);
	my_typeinfo(ret);

	// Проверяем тип dvec4 (4-компонентный вектор double)
	value.setDVec4(dvec4(1.0, 2.0, 3.0, 4.0));
	ret = engine->runWorldFunction(my_typeinfo_id, value);
	my_typeinfo(ret);

	// Проверяем тип ivec3 (3-компонентный вектор int)
	value.setIVec3(ivec3(1, 2, 3));
	ret = engine->runWorldFunction(my_typeinfo_id, value);
	my_typeinfo(ret);

	// Проверяем тип ivec4 (4-компонентный вектор int)
	value.setIVec4(ivec4(1, 2, 3, 4));
	ret = engine->runWorldFunction(my_typeinfo_id, value);
	my_typeinfo(ret);
}

// Восстанавливает настройки консоли по умолчанию
void ScriptVariables::shutdown()
{
	Console::setOnscreen(false);
	Console::setOnscreenHeight(30);
}
