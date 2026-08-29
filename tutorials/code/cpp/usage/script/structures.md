# Data Structure Export

> **Warning:** Область применения UnigineScript ограничена реализацией логики, связанной с материалами (material expressions, scriptable materials, brush materials). Не используйте UnigineScript как язык логики приложения, вместо этого рассмотрите C#/C++, поскольку именно эти API являются предпочтительными. Доступность новых функций движка в UnigineScript (за пределами области его применения) не гарантируется, поскольку текущий уровень поддержки подразумевает только исправление критических проблем.


Структуры данных (вместе с их конструкторами и акцессорами, если это необходимо) можно экспортировать в UnigineScript.


### См. также


Пример находится в папке `<UnigineSDK>/source/samples/Api/Scripts/Structures/`.


## Пример экспорта структуры данных


Структуры данных экспортируются так же, как и [classes](../../../../code/cpp/usage/script/classes.md) C++:

1. Создайте внешний класс на основе вашей структуры данных C++ с помощью *MakeExternClass()*.
2. Добавьте конструкторы во внешний класс.
3. Добавьте методы во внешний класс.
4. Зарегистрируйте внешний класс с помощью *[Unigine::Interpreter::addExternClass()](../../../../api/library/common/class.interpreter_cpp.md#addExternClass_const_char_ptr_ExternClassBase_ptr_int_void)*.


Вот как различные структуры данных можно экспортировать из C++ в UnigineScript:


```cpp
#include <string>
#include <map>

#include <UnigineEngine.h>
#include <UnigineInterpreter.h>
#include <UnigineInterface.h>

/*
*/
using namespace Unigine;

/******************************************************************************\
*
* Data structure
*
\******************************************************************************/

/*
 */
typedef struct mydata{
	std::string name;
	Unigine::Math::ivec3 vec;
	const char *getName() const { return name.c_str(); }
} mydata;

std::map<std::string, mydata> mymap;

/*
 */
void get_data(const Variable &id) {

	void *interpreter = Interpreter::get();
	ArrayMap map = ArrayMap::get(interpreter,id);
	for(std::map<std::string,mydata>::iterator it = mymap.begin(); it != mymap.end(); ++it) {
		map.append(Variable(it->first.c_str()),Variable(interpreter,TypeInfo(TypeID<mydata*>()),&it->second));
	}
}

/*
 */
struct MyVector {

	MyVector() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {

	}

	float x;
	float y;
	float z;
	float w;
};

/******************************************************************************\
*
* Main
*
\******************************************************************************/

/*
*/
int main(int argc,char **argv) {

	// экспортируем структуру данных как внешний класс
	ExternClass<mydata> *mydata_export = MakeExternClass<mydata>();
	// добавляем конструктор по умолчанию
	mydata_export->addConstructor();
	// экспортируем акцессор структуры
	mydata_export->addFunction("getName",&mydata::getName);
	// регистрируем экспортированный класс
	Interpreter::addExternClass("mydata",mydata_export);
	// регистрируем внешнюю функцию
	Interpreter::addExternFunction("get_data2",MakeExternFunction(&get_data,"[]"));

	// заполняем карту
	mydata data;

	data.name = std::string("map_data_0");
	mymap[std::string("key_0")] = data;

	data.name = std::string("map_data_1");
	mymap[std::string("key_1")] = data;

	// экспортируем структуру данных как внешний класс
	ExternClass<MyVector> *my_vector = MakeExternClass<MyVector>();
	// добавляем конструктор
	my_vector->addConstructor();
	// регистрируем акцессоры структуры
	my_vector->addSetFunction("setX",&MyVector::x);
	my_vector->addGetFunction("getX",&MyVector::x);
	my_vector->addSetFunction("setY",&MyVector::y);
	my_vector->addGetFunction("getY",&MyVector::y);
	my_vector->addSetFunction("setZ",&MyVector::z);
	my_vector->addGetFunction("getZ",&MyVector::z);
	my_vector->addSetFunction("setW",&MyVector::w);
	my_vector->addGetFunction("getW",&MyVector::w);
	// регистрируем внешний класс
	Interpreter::addExternClass("MyVector",my_vector);

	// инициализируем движок
	Engine *engine = Engine::init(0,argc,argv);

	// входим в главный цикл и вызываем функцию update() в загруженном скрипте мира
	engine->main();

	// завершаем работу движка и вызываем функцию shutdown() в загруженном скрипте мира
	Engine::shutdown();

	return 0;
}

```


### Доступ из скриптов


После регистрации экспортированную структуру данных можно использовать в UnigineScript точно так же, как и обычный класс.


```cpp
// my_world.usc

int init() {

	// получаем данные из карты
	mydata data2[];
	get_data2(data2);
	foreachkey(string key; data2) {
		log.message("%s: %s\n",key,data2[key].getName());
	}

	log.message("\n");

	// создаём внешнюю структуру
	MyVector vector = new MyVector();

	// задаём члены
	vector.setX(1.0f);
	vector.setY(2.0f);
	vector.setZ(4.0f);
	vector.setW(8.0f);

	// получаем члены
	log.warning("MyVector: (%g,%g,%g,%g)\n",vector.getX(),vector.getY(),vector.getZ(),vector.getW());

	// удаляем внешнюю структуру
	delete vector;

	// показываем консоль
	engine.console.setActivity(1);

	return 1;
}

```


### Вывод


В консоль будет выведен следующий результат:


```text
key_0: map_data_0
key_1: map_data_1

MyVector: (1,2,3,4,8)

```
