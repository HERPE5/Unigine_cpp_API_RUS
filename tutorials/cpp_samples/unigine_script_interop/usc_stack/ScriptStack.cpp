// Демонстрирует доступ к стеку Interpreter для вариативных функций. Функция my_format
// реализует форматирование в стиле printf, извлекая аргументы Variable
// из стека скрипта на основе форматных спецификаторов (%d, %f, %s).

#include "ScriptStack.h"

#include "../../utils/UnigineScriptsInterpreter.h"

#include <UnigineInterface.h>
#include <UnigineWorld.h>
#include <UnigineConsole.h>

REGISTER_COMPONENT(ScriptStack)

using namespace Unigine;

// ============================================================================
// Вариативная функция форматирования - использует стек скрипта для переменных аргументов
// ============================================================================

// Форматтер в стиле printf, извлекающий аргументы из стека Interpreter
String my_format(const char *format)
{
	String ret;

	const char *s = format;

	while (*s)
	{
		// символ формата
		if (*s == '%')
		{
			s++;

			// символ формата
			if (*s == '%')
			{
				ret += *s++;
				continue;
			}

			// проверяем глубину стека
			if (Interpreter::getStack() < 1)
				Interpreter::error("my_format(): stack underflow\n");

			// извлекаем переменную из стека
			Variable v = Interpreter::popStack();

			// целое число
			if (*s == 'd' || *s == 'i')
			{
				ret += String::format("%d", v.getInt());
				s++;
			}

			// float
			else if (*s == 'f')
			{
				ret += String::format("%f", v.getFloat());
				s++;
			}

			// строка
			else if (*s == 's')
			{
				ret += String::format("%s", v.getString());
				s++;
			}

			// неизвестный формат
			else
				Interpreter::error("my_format(): unknown format %c\n", *s);
		}

		// копируем символ
		else
			ret += *s++;
	}

	return ret;
}

// ============================================================================
// Регистрация функций
// ============================================================================

// Отложенная регистрация: сигнатура ",..." указывает на вариативные аргументы на основе стека
USCInterpreter stack_interpreter([]() {
	Interpreter::addExternFunction("my_format", MakeExternFunction(&my_format, ",..."));
});


// Настраивает экранную консоль для отображения результатов форматирования
void ScriptStack::init()
{
	Console::setOnscreen(true);
	Console::setOnscreenFontSize(15);
	Console::setOnscreenTime(1000);
	Console::setOnscreenHeight(100);
}

// Восстанавливает настройки консоли по умолчанию
void ScriptStack::shutdown()
{
	Console::setOnscreen(false);
	Console::setOnscreenHeight(30);
}
