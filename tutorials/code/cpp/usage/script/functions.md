# Function Export

> **Warning:** Область применения UnigineScript ограничена реализацией логики, связанной с материалами (material expressions, scriptable materials, brush materials). Не используйте UnigineScript как язык логики приложения, вместо этого рассмотрите C#/C++, поскольку именно эти API являются предпочтительными. Доступность новых функций движка в UnigineScript (за пределами области его применения) не гарантируется, поскольку текущий уровень поддержки подразумевает только исправление критических проблем.


Unigine API поддерживает экспорт:

- Чистых функций
- Методов конкретных объектов в качестве чистых функций


### См. также


Пример можно найти в директории `<UnigineSDK>/source/samples/Api/Scripts/Functions/`.


## Пример экспорта функции


Экспортируемые чистые функции и методы объектов могут принимать до 9 аргументов.

> **Notice:** Объект, методы которого экспортированы, не должен уничтожаться, пока он используется движком в скрипте.


Ниже приведён пример экспорта функции и метода.

1. Создайте указатель на внешнюю функцию с помощью *MakeExternFunction()*. Для методов объектов используйте *MakeExternObjectFunction()*.
2. Зарегистрируйте функцию или метод с помощью *[Unigine::Interpreter::addExternFunction()](../../../../api/library/common/class.interpreter_cpp.md#addExternFunction_const_char_ptr_ExternFunctionBase_ptr_int_void)*.
3. Все функции экспортируются в глобальное пространство имён. Чтобы ограничить область видимости экспортируемой функции или метода, используйте [library namespace](../../../../code/cpp/usage/script/namespace.md).


```cpp
#include <UnigineApp.h>
#include <UnigineConsole.h>
#include <UnigineEngine.h>
#include <UnigineInterface.h>
#include <UnigineLogic.h>
#include <UnigineString.h>
#include <UnigineWorld.h>

using namespace Unigine;
using namespace Unigine::Math;

//////////////////////////////////////////////////////////////////////////
// User defined functions
//////////////////////////////////////////////////////////////////////////

/*
 */
Variable my_sum(const Variable &v0, const Variable &v1)
{
	if (v0.getType() == Variable::INT && v1.getType() == Variable::INT)
	{
		Log::message("my_sum(%d,%d): called\n", v0.getInt(), v1.getInt());
		return Variable(v0.getInt() + v1.getInt());
	}

	if (v0.getType() == Variable::STRING && v1.getType() == Variable::STRING)
	{
		Log::message("my_sum(%s,%s): called\n", v0.getString(), v1.getString());
		return Variable((String(v0.getString()) + "+" + String(v1.getString())).get());
	}

	Log::message("my_sum(%s,%s): called\n", v0.getTypeName().get(), v1.getTypeName().get());

	return Variable("unknown");
}

/*
 */
float my_mul(float a, float b)
{
	Log::message("my_mul(%g,%g): called\n", a, b);

	return a * b;
}

/*
 */
float my_dot(const vec3 &v0, const vec3 &v1)
{
	Log::message("my_dot((%g,%g,%g),(%g,%g,%g)): called\n", v0.x, v0.y, v0.z, v1.x, v1.y, v1.z);

	return dot(v0, v1);
}

//////////////////////////////////////////////////////////////////////////
// User defined class member functions
//////////////////////////////////////////////////////////////////////////

/*
 */
class MyApplication
{
public:
	MyApplication()
		: seed(1)
	{
	}

	void init(int s = 1)
	{
		Log::message("MyApplication::init(%d) called\n", s);
		seed = s;
	}

	void shutdown()
	{
		Log::message("MyApplication::shutdown() called\n");
		seed = 1;
	}

	int update()
	{
		seed = (seed * 3877 + 29573) % 139968;
		return seed;
	}

	int get() const
	{
		return seed;
	}

private:
	int seed;
};

//////////////////////////////////////////////////////////////////////////
// System logic class
//////////////////////////////////////////////////////////////////////////

class AppSystemLogic : public SystemLogic
{
public:
	AppSystemLogic() {}
	virtual ~AppSystemLogic() {}

	int init() override
	{
		App::setUpdate(1);
		// загружаем мир с файлом скрипта на UnigineScript, использующим наши функции
		World::loadWorld("functions");

		return 1;
	}
};
//////////////////////////////////////////////////////////////////////////
// Main
//////////////////////////////////////////////////////////////////////////
 int main(int argc, char **argv)
{
	// синглтон
	MyApplication my_application;

	// экспортируем функции
	Interpreter::addExternFunction("my_sum", MakeExternFunction(&my_sum, ",1"));
	Interpreter::addExternFunction("my_mul", MakeExternFunction(&my_mul));
	Interpreter::addExternFunction("my_dot", MakeExternFunction(&my_dot));

	// экспортируем функции-члены класса
	Interpreter::addExternLibrary("my_application");
	Interpreter::addExternFunction("my_application.init", MakeExternObjectFunction(&my_application, &MyApplication::init, "1"));
	Interpreter::addExternFunction("my_application.shutdown", MakeExternObjectFunction(&my_application, &MyApplication::shutdown));
	Interpreter::addExternFunction("my_application.update", MakeExternObjectFunction(&my_application, &MyApplication::update));
	Interpreter::addExternFunction("my_application.get", MakeExternObjectFunction(&my_application, &MyApplication::get));

	// инициализируем движок
	EnginePtr engine(argc, argv);

	// входим в главный цикл
	AppSystemLogic system_logic;
	engine->main(&system_logic, NULL, NULL);

	return 0;
}

```


### Доступ из скриптов


После регистрации экспортированные функции и методы можно использовать в скрипте, написанном на UnigineScript (загруженном в *AppSystemLogic::init()* выше):


```cpp
/*
 */
int init()
{
	/////////////////////////////////

	log.message("\nFunctions:\n\n");

	// my_sum(1) со значением второго аргумента по умолчанию
	log.message("result is: %s\n\n", typeinfo(my_sum(1)));

	// my_sum(1,2)
	log.message("result is: %s\n\n", typeinfo(my_sum(1, 2)));

	// my_sum("begin","end")
	log.message("result is: %s\n\n", typeinfo(my_sum("begin", "end")));

	// my_sum(1,"end")
	log.message("result is: %s\n\n", typeinfo(my_sum(1, "end")));

	// my_mul(16,64)
	log.message("result is: %s\n\n", typeinfo(my_mul(16, 64)));

	// my_dot(vec3(1.0f,2.0f,3.0f),vec3(4.0f,5.0f,6.0f))
	log.message("result is: %s\n\n", typeinfo(my_dot(vec3(1.0f, 2.0f, 3.0f), vec3(4.0f, 5.0f, 6.0f))));

	/////////////////////////////////

	log.message("Member functions:\n\n");

	// аргумент по умолчанию
	my_application.init();

	// заданный вручную аргумент
	my_application.init(100);

	// обновляем приложение
	for (int i = 0; i < 4; i++)
		log.message("%d: %d\n", i, my_application.update());

	// завершаем работу
	my_application.shutdown();

	/////////////////////////////////

	// показываем консоль
	engine.console.setActivity(1);

	return 1;
}

```


### Вывод


В консоль будет выведен следующий результат:


```text
Functions:

my_sum(1,1): called
result is: int: 2

my_sum(1,2): called
result is: int: 3

my_sum(begin,end): called
result is: string: "begin+end"

my_sum(int,string): called
result is: string: "unknown"

my_mul(16,64): called
result is: float: 1024

my_dot((1,2,3),(4,5,6)): called
result is: float: 32

Member functions:

MyApplication::init(1) called
MyApplication::init(100) called
0: 137337
1: 46850
2: 128527
3: 42672
MyApplication::shutdown() called

```


## Значения аргументов по умолчанию


Если вы хотите экспортировать функции со значениями аргументов по умолчанию, вы можете указать их в качестве последнего аргумента *MakeExternFunction()*. Порядок значений должен совпадать с порядком аргументов в объявлении функции, а значения должны быть разделены запятыми. Например:


```cpp
void foo(const char *a,float b) { }

// указываем значения по умолчанию:
Interpreter::addExternFunction("foo",MakeExternFunction(&foo,"\"Unigine\",0.4"));

```


Если вы хотите указать значения по умолчанию не для всех аргументов, просто пропустите те, у которых значений по умолчанию нет, но не забывайте про запятые:


```cpp
// указываем только требуемое значение по умолчанию:
Interpreter::addExternFunction("foo",MakeExternFunction(&foo,",0.4"));

```


### Выражение в качестве аргумента по умолчанию


Помимо констант, в качестве значений по умолчанию можно также указывать выражения.

- Выражения вычисляются до регистрации функции.
- Выражение, указанное в качестве аргумента по умолчанию, должно возвращать значение того же типа, что и соответствующий аргумент. Преобразования типов не поддерживаются, единственное исключение - двустороннее преобразование между *float* и *int*.


## Особенности перегрузки


В отличие от C++, UnigineScript не является строго типизированным языком. В коде C++ у вас может быть две или более функций с одинаковым именем, возвращающих значение одного типа, но принимающих разные типы аргументов (или отличающихся количеством аргументов). Если вы попытаетесь экспортировать их в скрипты, просто зарегистрировав имена функций, *MakeExternFunction()* завершится с ошибкой.


Чтобы регистрация сработала, необходимо явно указать:

1. Тип возвращаемого значения
2. Типы аргументов


```cpp
void foo(int a) { }
void foo(float a) { }

/* Interpreter::addExternFunction("foo",MakeExternFunction(&foo));
 * Это выражение не сработает, поскольку интерпретатор не может выбрать между функциями.
 */

// чтобы зарегистрировать void foo(int a), используйте:
Interpreter::addExternFunction("foo",MakeExternFunction<void,int>(&foo));

// чтобы зарегистрировать void foo(float a), используйте:
Interpreter::addExternFunction("foo",MakeExternFunction<void,float>(&foo));

```


Предположим, у нас более сложная ситуация: первые аргументы функций имеют одинаковый тип. В этом случае для регистрации используется следующий синтаксис:


```cpp
void foo(int a) { }
void foo(int a,int b) { }

/* Interpreter::addExternFunction("foo",MakeExternFunction<void,int>(&foo));
 * Это выражение не сработает, поскольку обе функции принимают целое число в качестве первого аргумента.
 */

// чтобы зарегистрировать void foo(int a), используйте:
Interpreter::addExternFunction("foo",MakeExternFunction((void (*)(int))&foo));

// чтобы зарегистрировать void foo(int a,int b), используйте:
Interpreter::addExternFunction("foo",MakeExternFunction((void (*)(int,int))&foo));

/* Interpreter::addExternFunction("foo",MakeExternFunction<void,int,int>(&foo));
 * Это выражение также позволит зарегистрировать void foo(int a,int b).
 */

```


### Перегрузка экспортированных методов


Если для имён статических методов класса существует неоднозначность, она разрешается так же, как и для функций.


```cpp
class Class {

	public:

		static int foo(float a) { return 1; }
        static int foo(int a) { return 1; }
		static void foo(int a,int b) { return 1; }
};

/*
*/

// чтобы зарегистрировать foo(float a):
Interpreter::addExternFunction("foo",MakeExternFunction((int (*)(float))&Class::foo));
// чтобы зарегистрировать foo(int a):
Interpreter::addExternFunction("foo",MakeExternFunction((int (*)(int))&Class::foo));
// чтобы зарегистрировать foo(int a,int b):
Interpreter::addExternFunction("foo",MakeExternFunction((void (*)(int,int))&Class::foo));

```
