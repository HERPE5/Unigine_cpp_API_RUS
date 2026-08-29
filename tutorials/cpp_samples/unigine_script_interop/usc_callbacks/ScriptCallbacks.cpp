// Демонстрирует вызов функций UnigineScript из C++ с помощью Engine::runWorldFunction.
// Функция counter вызывается каждый кадр, а её возвращаемое значение используется для запуска
// дополнительных вызовов скрипта. Показывает двустороннее взаимодействие C++/скрипт.

#include "ScriptCallbacks.h"

#include "../../utils/UnigineScriptsInterpreter.h"

#include <UnigineInterface.h>
#include <UnigineConsole.h>

REGISTER_COMPONENT(ScriptCallbacks)

using namespace Unigine;


// Обёртка, логирующая информацию о вызове и вызывающая функцию скрипта по имени с одним аргументом
const Variable &runWorldFunction(const Variable &name, const Variable &v)
{
	Log::message("%s runWorldFunction(%s,%s): called\n", sourse_str, name.getTypeName().get(),
		v.getTypeName().get());

	return Engine::get()->runWorldFunction(name, v);
}

// Отложенная регистрация: предоставляет runWorldFunction в UnigineScript
USCInterpreter callbacks_interpreter([]() {
	Interpreter::addExternFunction("runWorldFunction", MakeExternFunction(&runWorldFunction));
});


// Настраивает экранную консоль для отображения результатов вызовов скрипта
void ScriptCallbacks::init()
{
	Console::setOnscreen(true);
	Console::setOnscreenFontSize(15);
	Console::setOnscreenTime(1000);
	Console::setOnscreenHeight(100);
}

// Вызывает функцию скрипта "counter"; при значении 3 также получает и логирует путь мира
void ScriptCallbacks::update()
{
	Variable ret = Engine::get()->runWorldFunction(Variable("counter"));
	if (ret.getInt() != -1)
		Log::message("%s counter is: %d\n", sourse_str, ret.getInt());
	if (ret.getInt() == 3)
	{
		Variable path = Engine::get()->runWorldFunction(Variable("engine.world.getPath"));
		Log::message("\n%s world path is: \"%s\"\n", sourse_str, path.getString());
	}
}

// Восстанавливает настройки консоли по умолчанию
void ScriptCallbacks::shutdown()
{
	Console::setOnscreen(false);
	Console::setOnscreenHeight(30);
}
