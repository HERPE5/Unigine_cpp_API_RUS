# Library's Namespace

> **Warning:** Область применения UnigineScript ограничена реализацией логики, связанной с материалами (material expressions, scriptable materials, brush materials). Не используйте UnigineScript как язык логики приложения, вместо этого рассмотрите C#/C++, поскольку именно эти API являются предпочтительными. Доступность новых функций движка в UnigineScript (за пределами области его применения) не гарантируется, поскольку текущий уровень поддержки подразумевает только исправление критических проблем.


По умолчанию все переменные и функции экспортируются из C++ в глобальное пространство имён. Библиотеки предоставляют удобный способ организации предоставляемой функциональности путём добавления пространства имён библиотеки. Это пространство имён используется вместо синтаксиса `Foo::Bar`, который недопустим для экспорта.


## Пример экспорта в пространство имён


1. Чтобы использовать пространство имён библиотеки, сначала необходимо зарегистрировать библиотеку с помощью *[Unigine::Interpreter::addExternLibrary()](../../../../api/library/common/class.interpreter_cpp.md#addExternLibrary_const_char_ptr_int_void)*.
2. После этого вы можете использовать пространство имён библиотеки для регистрации своих переменных и функций.


```cpp
#include <UnigineEngine.h>
#include <UnigineInterpreter.h>
#include <UnigineInterface.h>

#include "AppSystemLogic.h"
#include "AppWorldLogic.h"

using namespace Unigine;

// Переменная в пространстве имён для экспорта.
namespace Foo {
	int i = 25;
}

#ifdef _WIN32
	int wmain(int argc,wchar_t *argv[]) {
#else
	int main(int argc,char *argv[]) {
#endif

	// Регистрируем библиотеку, чтобы использовать пространство имён библиотеки.
	Interpreter::addExternLibrary("Foo");

	// Экспортируем переменную с префиксом библиотеки.
	Interpreter::addExternVariable("Foo.integer",MakeExternVariable(&Foo::i));

	AppSystemLogic system_logic;
	AppWorldLogic world_logic;

	Unigine::EnginePtr engine(argc,argv);

	// Входим в главный цикл.
	engine->main(&system_logic,&world_logic);

	return 0;
}

```


### Доступ из скриптов


Вы можете просто вызывать зарегистрированные переменные, функции, классы из скриптов Unigine, используя зарегистрированное имя. (Если библиотека *Foo* не зарегистрирована, первая точка в имени объекта или функции будет трактоваться как оператор доступа к члену класса, что в нашем случае неверно).


В функцию init() файла скрипта мира `.usc` добавьте следующее:


```cpp
// my_world.usc

int init() {
	/* ... code ... */

	log.message("Foo.i is %d\n",Foo.integer);
	engine.console.setActivity(1);

	/* ... code ... */

}

```


### Вывод


В консоль будет выведено следующее сообщение:


```text
Foo.i is 25
```
