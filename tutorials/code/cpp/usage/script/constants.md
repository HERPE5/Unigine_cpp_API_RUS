# Constant Export

> **Warning:** Область применения UnigineScript ограничена реализацией логики, связанной с материалами (material expressions, scriptable materials, brush materials). Не используйте UnigineScript как язык логики приложения, вместо этого рассмотрите C#/C++, поскольку именно эти API являются предпочтительными. Доступность новых функций движка в UnigineScript (за пределами области его применения) не гарантируется, поскольку текущий уровень поддержки подразумевает только исправление критических проблем.


Константы - это переменные, значение которых не меняется независимо от того, что происходит в коде C++. Чтобы они были доступны в скриптах Unigine, их необходимо экспортировать со стороны C++.


- Внешние константы доступны **только для чтения**.
- Если значение зарегистрированной константы изменяется в коде C++, на стороне скрипта оно останется **прежним** (в отличие от [variables](../../../../code/cpp/usage/script/variables.md)).


## Пример экспорта константы


Константы экспортируются аналогично [variables](../../../../code/cpp/usage/script/variables.md):

1. Создайте указатель на внешнюю константу с помощью `MakeExternConstant()`.
2. Зарегистрируйте константу с помощью `Unigine::Interpreter::addExternVariable()`.
3. Все переменные экспортируются в глобальное пространство имён. Чтобы ограничить область видимости переменной, используйте [library namespace](../../../../code/cpp/usage/script/namespace.md).


```cpp
#include <UnigineEngine.h>
#include <UnigineInterpreter.h>

using namespace Unigine;

int main(int argc,char **argv) {

	int i = 0;
	float f = 0.0f;

	// экспортируем переменную и указываем имя для доступа к ней из скриптов Unigine
	Interpreter::addExternVariable("int_constant",MakeExternConstant(i));
	// также можно указать параметр шаблона, чтобы убедиться, что передаётся правильный тип
	Interpreter::addExternVariable("float_constant",MakeExternConstant<float>(f));

	Engine *engine = Engine::init(argc,argv);
	// входим в главный цикл
	while(engine->isDone() == 0) {
		engine->update();
		engine->render();
		engine->swap();
		// если значение переменной изменяется после её регистрации, значение в скриптах не изменится
		i = 42;
		f = 57.55f;
	}
	// завершаем работу движка
	Engine::shutdown();

}

```


### Доступ из скриптов


После регистрации вы можете обращаться к константам из скрипта по их зарегистрированным именам:


```cpp
// my_world.usc

log.message("Integer: %d\nFloat: %f\n",int_constant,float_constant);

```


### Вывод


В консоль будут выведены следующие результаты:

```text
Integer: 0
Float: 0.000000

```


> **Notice:** При перезагрузке мира значения констант, изменённые на стороне C++, останутся прежними.
