# Serialization

> **Warning:** Область применения UnigineScript ограничена реализацией логики, связанной с материалами (material expressions, scriptable materials, brush materials). Не используйте UnigineScript как язык логики приложения, вместо этого рассмотрите C#/C++, поскольку именно эти API являются предпочтительными. Доступность новых функций движка в UnigineScript (за пределами области его применения) не гарантируется, поскольку текущий уровень поддержки подразумевает только исправление критических проблем.


Unigine API позволяет создавать объекты, состояния которых можно сохранять в бинарный файл и позже восстанавливать из него.


### См. также


Пример можно найти в директории `<UnigineSDK>/source/samples/Api/Scripts/Serialization/`.


## Рекомендации по сериализации


Сохранение и восстановление состояния объекта выполняется с помощью механизма бинарной сериализации Unigine. Чтобы быть совместимым с этим механизмом, класс должен реализовать методы, позволяющие сохранять состояния объектов класса в *[Unigine::Stream](../../../../api/library/common/class.stream_cpp.md)* и восстанавливать их оттуда.


Эти методы можно сгруппировать следующим образом:

- Методы для сохранения/восстановления **состояний**. Состояния используются для объектов, создаваемых и обрабатываемых исключительно в UnigineScript. Это означает, что такой объект, реализованный на стороне C++, создаётся в скрипте через оператор *new* и удаляется через *delete*. Он не передаётся между UnigineScript и какой-либо другой системой.

  - *saveState()* - сохраняет состояние объекта, созданного на стороне UnigineScript.
  - *restoreState()* — восстанавливает состояние объекта, созданного на стороне UnigineScript. Эта функция подразумевает, что у класса есть конструктор по умолчанию, создающий пустой объект.
- Методы для сохранения/восстановления **указателей**. Указатели используются для объектов, которые создаются в части приложения на C++ и там же будут удалены. Скрипт получает объект, но не отвечает за управление им. Например, так происходит, когда функция C++, создающая объект, вызывается из скрипта.

  - *savePointer()* — статический метод, используемый для сохранения состояния объекта, созданного на стороне C++ и обрабатываемого скриптом.
  - *restorePointer()* — статический метод, используемый для восстановления состояния объекта, созданного на стороне C++ и обрабатываемого скриптом.


Если объект должен создаваться как в скрипте, так и на стороне C++, необходимо реализовать все четыре функции.


> **Notice:** Если указанные выше методы реализованы неправильно, объекты не будут сохраняться, и будут возникать ошибки, связанные с памятью.


### Шаг 1. Реализация сохранения и восстановления объекта


По умолчанию используется следующая реализация (см. файл заголовка `include/UnigineInterpreter.h`):


```cpp
// функтор для сохранения состояния объекта, созданного в скриптах
template <class Class>
void ExternClassSaveState(const StreamPtr &stream,Class *object) {
	object->saveState(stream);
}

// функтор для восстановления состояния объекта, созданного в скриптах
template <class Class>
Class *ExternClassRestoreState(const StreamPtr &stream) {
	Class *object = new Class();
	object->restoreState(stream);
	return object;
}

// функтор для сохранения состояния объекта, созданного на стороне C++ и обрабатываемого скриптом
template <class Class>
	void ExternClassSavePointer(const StreamPtr &stream,Class *object) {
	Class::savePointer(stream,object);
}

// функтор для восстановления состояния объекта, созданного на стороне C++ и обрабатываемого скриптом
template <class Class>
Class *ExternClassRestorePointer(const StreamPtr &stream) {
	return Class::restorePointer(stream);
}

```


### Шаг 2. Экспорт класса


Необходимо экспортировать классы, экземпляры которых будут сериализованы. Для этого можно использовать одну из следующих функций:

- Функцию *MakeExternClass()*. Экземпляры классов, [exported](../../../../code/cpp/usage/script/classes.md) с помощью этой функции, не подлежат восстановлению, то есть их необходимо создавать заново вручную. Если вы попытаетесь восстановить экземпляр такого класса, он будет восстановлен как **null**.
- Функцию *MakeExternClassSaveRestoreState()*, которая позволяет сохранять и восстанавливать экземпляры, созданные внутри UnigineScript.
- Функцию *MakeExternClassSaveRestorePointer()*, которая позволяет сохранять и восстанавливать объекты, созданные в коде C++ и экспортированные в UnigineScript.
- Функцию *MakeExternClassSaveRestoreStatePointer()*, которая объединяет две предыдущие возможности, то есть можно сохранять и восстанавливать объекты, созданные как на стороне UnigineScript, так и на стороне C++.


#### Изменение поведения сериализации


После экспорта по-прежнему можно изменить поведение сериализации во время выполнения. Для этого можно использовать две функции UnigineScript.

> **Notice:** Это полностью безопасно только в том случае, если реализовано и сохранение/восстановление состояния, и сохранение/восстановление указателя.


- [*class_append()*](../../../../api/library/common/class.system_cpp.md#class_append_Variable) присоединяет объект к скрипту, который будет им управлять (сохранять, восстанавливать и удалять его).
- [*class_remove()*](../../../../api/library/common/class.system_cpp.md#class_remove_Variable) удаляет объект из скрипта.


> **Notice:** UnigineScript не уничтожает объекты, которые были созданы на стороне C++ и не были присоединены к скрипту.


## Пример сериализации


Ниже приведён пример экспорта класса C++, полностью поддерживающего сериализацию в UnigineScript.


### Сторона C++


```cpp
#include <UnigineEngine.h>
#include <UnigineInterpreter.h>
#include <UnigineInterface.h>

#include "AppSystemLogic.h"
#include "AppWorldLogic.h"

using namespace Unigine;
using namespace Math;

/******************************************************************************\
*
* User defined class
*
\******************************************************************************/

class MyObject : public Base {

	public:

		MyObject() : mass(0.0f) {
			Log::warning("MyObject::MyObject(): called\n");
		}
		MyObject(const vec3 &size,float mass) : size(size), mass(mass) {
			Log::warning("MyObject::MyObject((%g,%g,%g),%g): called\n",size.x,size.y,size.z,mass);
		}
		~MyObject() {
			Log::warning("MyObject::~MyObject(): called\n");
		}

		// размер
		void setSize(const vec3 &s) {
			Log::warning("MyObject::setSize((%g,%g,%g)): called\n",s.x,s.y,s.z);
			size = s;
		}
		const vec3 &getSize() const {
			return size;
		}

		// масса
		void setMass(float m) {
			Log::warning("MyObject::setMass(%g): called\n",m);
			mass = m;
		}
		float getMass() const {
			return mass;
		}

		// сохранение состояния
		void saveState(StreamPtr &stream) const {
			Log::warning("MyObject::saveState(): called\n");
			stream->writeVec3(size);
			stream->writeFloat(mass);
		}

		// восстановление состояния
		void restoreState(StreamPtr &stream) {
			Log::warning("MyObject::restoreState(): called\n");
			size = stream->readVec3();
			mass = stream->readFloat();
		}

		// сохранение указателя
		static void savePointer(StreamPtr &stream,MyObject *object) {
			Log::warning("MyObject::savePointer(): called\n");
			stream->writeVec3(object->size);
			stream->writeFloat(object->mass);
		}

		// восстановление указателя
		static MyObject *restorePointer(StreamPtr &stream) {
			MyObject *object = new MyObject();
			Log::warning("MyObject::restorePointer(): called\n");
			object->size = stream->readVec3();
			object->mass = stream->readFloat();
			return object;
		}

	private:

		vec3 size;
		float mass;
};

MyObject *MakeMyObject(const vec3 &size,float mass) {
	return new MyObject(size,mass);
}

void DeleteMyObject(MyObject *object) {
	delete object;
}

/******************************************************************************\
*
* Main
*
\******************************************************************************/

#ifdef _WIN32
	int wmain(int argc,wchar_t *argv[]) {
#else
	int main(int argc,char *argv[]) {
#endif

	// экспортируем класс с сериализацией
	ExternClass<MyObject> *my_object = MakeExternClassSaveRestoreStatePointer<MyObject>();
	my_object->addConstructor<const vec3&,float>();
	my_object->addFunction("setSize",&MyObject::setSize);
	my_object->addFunction("getSize",&MyObject::getSize);
	my_object->addFunction("setMass",&MyObject::setMass);
	my_object->addFunction("getMass",&MyObject::getMass);
	Interpreter::addExternClass("MyObject",my_object);

	// экспортируем функции
	Interpreter::addExternFunction("MakeMyObject",MakeExternFunction(&MakeMyObject));
	Interpreter::addExternFunction("DeleteMyObject",MakeExternFunction(&DeleteMyObject));

	AppSystemLogic system_logic;
	AppWorldLogic world_logic;

	Unigine::EnginePtr engine(argc,argv);

	engine->main(&system_logic,&world_logic);

	return 0;
}

```


### Сторона Unigine Script


А вот как экспортированный класс можно использовать в UnigineScript (см. описание управляющей конструкции [*yield*](../../../../code/uniginescript/language/control_statements/other_statements/yield.md) для лучшего понимания примера):


```cpp
/*
 */
MyObject object_0;
MyObject object_1;

/*
 */
void object_info(MyObject object) {

	// параметры объекта
	vec3 size = object.getSize();
	float mass = object.getMass();

	log.message("size is: (%g,%g,%g), mass is: %g\n",size.x,size.y,size.z,mass);
}

/*
 */
int init() {

	/////////////////////////////////

	log.message("\n");

	// создаём объект, сконструированный скриптом
	object_0 = new MyObject(vec3(1.0f,2.0f,3.0f),10.0f);

	// создаём объект, сконструированный извне
	object_1 = MakeMyObject(vec3(4.0f,5.0f,6.0f),100.0f);

	/////////////////////////////////

	// показываем консоль
	engine.console.setActivity(1);

	return 1;
}

/*
 */
int shutdown() {

	// удаляем объект, сконструированный извне
	DeleteMyObject(object_1);

	return 1;
}

/*
 */
int update() {

	/////////////////////////////////
	// первое обновление
	/////////////////////////////////

	log.message("\n");

	// параметры
	object_info(object_0);
	object_info(object_1);

	yield 1;

	/////////////////////////////////
	// второе обновление
	/////////////////////////////////

	log.message("\n");



	yield 1;

	/////////////////////////////////
	// третье обновление
	/////////////////////////////////

	log.message("\n");

	// параметры
	object_info(object_0);
	object_info(object_1);

	yield 1;

	/////////////////////////////////

	return 1;
}

```


### Вывод


В консоль будет выведен следующий результат:


```text
MyObject::MyObject((1,2,3),10): called
MyObject::MyObject((4,5,6),100): called

size is: (1,2,3), mass is: 10
size is: (4,5,6), mass is: 100

Saving "data/serialization" world state to "save/quicksave.save" file

MyObject::saveState(): called
MyObject::savePointer(): called
MyObject::~MyObject(): called
MyObject::~MyObject(): called

Restoring "data/serialization" world state from "save/quicksave.save" file

MyObject::MyObject(): called
MyObject::restoreState(): called
MyObject::MyObject(): called
MyObject::restorePointer(): called

size is: (1,2,3), mass is: 10
size is: (4,5,6), mass is: 100

Unigine~# quit

MyObject::~MyObject(): called
MyObject::~MyObject(): called

```
