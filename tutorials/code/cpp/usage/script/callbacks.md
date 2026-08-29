# Callbacks

> **Warning:** Область применения UnigineScript ограничена реализацией логики, связанной с материалами (material expressions, scriptable materials, brush materials). Не используйте UnigineScript как язык логики приложения, вместо этого рассмотрите C#/C++, поскольку именно эти API являются предпочтительными. Доступность новых функций движка в UnigineScript (за пределами области его применения) не гарантируется, поскольку текущий уровень поддержки подразумевает только исправление критических проблем.


Любая функция из системного, мирового или редакторского скрипта может быть вызвана в коде C++. Функции UnigineScript, вызываемые из внешнего кода, называются коллбэками (callbacks). С помощью коллбэков скрипты могут взаимодействовать друг с другом, а также с внешним приложением.

- Коллбэки поддерживают до **4** аргументов и могут возвращать значение произвольного типа.


### См. также


Пример можно найти в директории `<UnigineSDK>/source/samples/Api/Scripts/Callbacks/`.


## Пример использования коллбэков


### Сторона C++


Чтобы продемонстрировать использование коллбэков, сначала напишем часть кода на C++. Вот код из файла `your_project_name.cpp`:


```cpp
#include <UnigineEngine.h>
#include <UnigineInterpreter.h>
#include <UnigineInterface.h>

#include "AppSystemLogic.h"
#include "AppWorldLogic.h"

using namespace Unigine;

/*
	Функция мира
*/
const Variable &runWorldFunction(const Variable &name,const Variable &v) {

	Log::warning("runWorldFunction(%s,%s) is called\n",name.getTypeName().get(),v.getTypeName().get());

	Engine *engine = Engine::get();
	return engine->runWorldFunction(name,v);
}

/*
*/
#ifdef _WIN32
	int wmain(int argc,wchar_t *argv[]) {
#else
	int main(int argc,char *argv[]) {
#endif

	// экспортируем функцию runWorldFunction(), определённую выше
	Unigine::Interpreter::addExternFunction("runWorldFunction", MakeExternFunction(&runWorldFunction));

	AppSystemLogic system_logic;
	AppWorldLogic world_logic;

	Unigine::EnginePtr engine(argc,argv);

	engine->main(&system_logic,&world_logic);

	return 0;
}

```


The following code should be in `AppWorldLogic.cpp`


```cpp
#include "AppWorldLogic.h"
#include "UnigineEditor.h"
#include "UnigineGame.h"

#include <UnigineInterpreter.h>

using namespace Unigine;
/*
 */
AppWorldLogic::AppWorldLogic() {

}

AppWorldLogic::~AppWorldLogic() {

}

/*
 */
int AppWorldLogic::init() {
	return 1;
}

int AppWorldLogic::shutdown() {
	return 1;
}

/*
 */
int AppWorldLogic::update() {
	/*
		Пример использования коллбэков
	*/

	// вызываем функцию counter() скрипта
	Variable ret = Engine::get()->runWorldFunction(Variable("counter"));
	// выводим сообщение в зависимости от значения, возвращённого функцией counter() скрипта:
	// выводим текущее значение счётчика
	if (ret.getInt() != -1) Log::message("counter is: %d\n", ret.getInt());
	// выводим путь к файлу мира
	if (ret.getInt() == 3) Log::message("\nworld-file path is: \"%s\"\n", Engine::get()->runWorldFunction(Variable("engine.world.getPath")).getString());

	return 1;
}

int AppWorldLogic::postUpdate() {
	return 1;
}

int AppWorldLogic::updatePhysics() {
	return 1;
}

```


### Сторона Unigine Script


> **Notice:** Требуемый мир должен быть загружен, а скрипт, назначенный этому `*.world`, не должен содержать ошибок компиляции.


Файл скрипта мира, в котором определены коллбэки:


```cpp
// unigine_project.usc

/*
*/
int callback(int value) {

	log.warning("callback(%s) is called\n",typeinfo(value));

	return value;
}

/*
*/
void counter() {

	for(int i = 0; i < 4; i++) {
		log.warning("counter(): called\n");
		yield i;
	}

	return -1;
}

/*
*/
int init() {

	log.message("\n");

	// вызываем функцию callback() скрипта через функцию API runWorldFunction()
	log.message("result is: %s\n\n",typeinfo(runWorldFunction("callback",10)));
	log.message("result is: %s\n\n",typeinfo(runWorldFunction("callback",vec3(1,2,3))));
	log.message("result is: %s\n\n",typeinfo(runWorldFunction("callback","a string")));

	/////////////////////////////////

	// показываем консоль
	engine.console.setActivity(1);

	return 1;
}

```


### Последовательность вызовов


Последовательность вызова функций будет следующей:


1. Интерпретатор экспортирует функцию *runWorldFunction()*, делая её доступной из скрипта.
2. Движок инициализируется, и вызывается функция *init()* скрипта. Эта функция вызывает экспортированную функцию *runWorldFunction()*.
3. Экспортированная функция *runWorldFunction()* вызывает функцию *callback()* из скрипта.
4. Движок входит в главный цикл, где вызывает функцию *counter()* из скрипта с помощью функции [*Unigine::Engine::runWorldFunction()*](../../../../api/library/engine/class.engine_cpp.md#runWorldFunction_const_Variable_ref_const_Variable_ref).


### Вывод


В консоль будет выведен следующий результат:


```text
runWorldFunction(string,int): called
callback(int: 10): called
result is: int: 10

runWorldFunction(string,vec3): called
callback(vec3: 1 2 3): called
result is: vec3: 1 2 3

runWorldFunction(string,string): called
callback(string: "a string") is called
result is: string: "a string"

counter(): called
counter is: 0
counter(): called
counter is: 1
counter(): called
counter is: 2
counter(): called
counter is: 3

world world-file path is: "unigine_project/unigine_project"

```
