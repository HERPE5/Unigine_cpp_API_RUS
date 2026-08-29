# Variable Export

> **Warning:** Область применения UnigineScript ограничена реализацией логики, связанной с материалами (material expressions, scriptable materials, brush materials). Не используйте UnigineScript как язык логики приложения, вместо этого рассмотрите C#/C++, поскольку именно эти API являются предпочтительными. Доступность новых функций движка в UnigineScript (за пределами области его применения) не гарантируется, поскольку текущий уровень поддержки подразумевает только исправление критических проблем.


Чтобы использовать переменные из вашего кода C++ в UnigineScript, их необходимо экспортировать. После этого они будут доступны на стороне скрипта.


- Внешние переменные доступны **только для чтения**.
- Если значение зарегистрированной переменной изменяется в коде C++, оно мгновенно **изменяется** и в скрипте (в отличие от [constants](../../../../code/cpp/usage/script/constants.md)).


### См. также


Пример можно найти в директории `<UnigineSDK>/source/samples/Api/Scripts/Variable/`.


## Пример экспорта переменной


Предположим, вы объявили ряд переменных на стороне C++. Чтобы их экспортировать, необходимо сделать следующее:

1. Создайте указатель на внешнюю переменную с помощью *MakeExternVariable()*.
2. Зарегистрируйте переменную с помощью *[Unigine::Interpreter::addExternVariable()](../../../../api/library/common/class.interpreter_cpp.md#addExternVariable_const_char_ptr_ExternVariableBase_ptr_int_void)*.
3. Все переменные экспортируются в глобальное пространство имён. Чтобы ограничить область видимости переменной, используйте [library namespace](../../../../code/cpp/usage/script/namespace.md).


```cpp
#include <UnigineInterpreter.h>
#include <UnigineInterface.h>
using namespace Unigine;

int main(int argc,char **argv) {

	int i = 2;
	float f = 1.5f;
	vec3 v3 = vec3(1.0f,2.0f,3.0f);
	vec4 v4 = vec4(0.1f,0.2f,0.3f,0.4f);
	float m[16] = { 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,\
					8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f };
	mat4 mat = mat4(m);
	quat q = quat(0.0f,0.0f,1.0f,0.0f);

	// экспортируем переменную и указываем имя для доступа к ней из скриптов Unigine
	Interpreter::addExternVariable("integer",MakeExternVariable(&i));
	Interpreter::addExternVariable("float_point",MakeExternVariable(&f));
	Interpreter::addExternVariable("vector3",MakeExternVariable(&v3));
	Interpreter::addExternVariable("vector4",MakeExternVariable(&v4));
	Interpreter::addExternVariable("matrix4",MakeExternVariable(&mat));
	Interpreter::addExternVariable("quaternion",MakeExternVariable(&q));

	Engine *engine = Engine::init(argc,argv);

	// входим в главный цикл
	while(engine->isDone() == 0) {
		engine->update();
		engine->render();
		engine->swap();
		// если значение переменной изменяется после её регистрации, в скриптах значение также изменится
		i = 42;
	}

	// завершаем работу движка
	Engine::shutdown();

}

```


### Доступ из скриптов


После регистрации вы можете обращаться к переменным из скрипта по их зарегистрированным именам:


```cpp
// my_world.usc
int init() {

	log.message("Integer is %d\nFloat is %f\n",integer,float_point);
	log.message("Vector3 x is %f\nVector3 y is %f\n",vector3.x,vector3.y);
	log.message("Vector4 w is %f\n",vector4.w);
	log.message("Matrix4 m10 is %f\nMatrix4 m11 is %f\n",matrix4.m10,matrix4.m11);

	return 1;
}

```


### Вывод


После запуска приложения в консоль будут выведены следующие результаты:

```text
Integer is 2
Float is 1.500000
Vector3 x is 1.000000
Vector3 y is 2.000000
Vector4 w is 0.400000
Matrix4 m10 is 1.000000
Matrix4 m11 is 5.000000

```


При перезагрузке мира в консоли появится целочисленное значение, изменённое на стороне C++:

```text
Integer is 42
Float is 1.500000
Vector3 x is 1.000000
Vector3 y is 2.000000
Vector4 w is 0.400000
Matrix4 m10 is 1.000000
Matrix4 m11 is 5.000000

```
