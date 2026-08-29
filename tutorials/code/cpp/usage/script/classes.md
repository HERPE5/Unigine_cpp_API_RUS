# Class Export

> **Warning:** Область применения UnigineScript ограничена реализацией логики, связанной с материалами (material expressions, scriptable materials, brush materials). Не используйте UnigineScript как язык логики приложения, вместо этого рассмотрите C#/C++, поскольку именно эти API являются предпочтительными. Доступность новых функций движка в UnigineScript (за пределами области его применения) не гарантируется, поскольку текущий уровень поддержки подразумевает только исправление критических проблем.


Unigine API поддерживает экспорт классов из C++ в UnigineScript вместе с их:

- Конструкторами
- Функциями-членами (поддерживается до восьми аргументов)


> **Notice:** Переменные-члены не могут быть экспортированы. Поскольку прямой доступ к ним невозможен, для них необходимо создать методы-акцессоры.


### См. также


Простое приложение с реализацией и экспортом класса C++ можно найти в директории `<UnigineSDK>/source/samples/Api/Scripts/Classes/`.


## Экспорт класса


Чтобы экспортировать класс C++ в UnigineScript, необходимо реализовать *статический* метод, который:

1. Создаёт внешний класс C++ с помощью функции *MakeExternClass()*.
2. Добавляет конструкторы во внешний класс с помощью функции [*Unigine::ExternClass<Class>::addConstructor()*](../../../../api/library/common/class.externclass_cpp.md#addConstructor_const_char_ptr_void).
3. Добавляет методы во внешний класс с помощью функции [*Unigine::ExternClass<Class>::addFunction()*](../../../../api/library/common/class.externclass_cpp.md#addFunction_const_char_ptr_methodptr_const_char_ptr_void). Если метод принимает массив в качестве аргумента, необходимо указать объявление массива в качестве последнего аргумента *addFunction()* следующим образом: ```cpp my_object->addFunction("my_array",&MyExternObject::my_array,"[]"); ``` Если целевой метод имеет более одного аргумента, укажите объявление массива в соответствующей позиции: ```cpp // метод my_array() принимает массив в качестве второго аргумента my_object->addFunction("my_array",&MyExternObject::my_array,",[],"); ``` Подробнее см. также раздел [Default Argument Values](../../../../code/cpp/usage/script/functions.md#args) статьи Function Export и статью [UnigineScript Containers](../../../../code/cpp/usage/script/arrays.md).
4. Регистрирует внешний класс с помощью *[Unigine::Interpreter::addExternClass()](../../../../api/library/common/class.interpreter_cpp.md#addExternClass_const_char_ptr_ExternClassBase_ptr_int_void)*.
5. Экспортирует функции внешнего класса с помощью функции [*Interpreter::addExternFunction()*](../../../../api/library/common/class.interpreter_cpp.md#addExternFunction_const_char_ptr_ExternFunctionBase_ptr_int_void).


> **Notice:** Обратите внимание, что статические методы классов экспортируются как [pure functions](../../../../code/cpp/usage/script/functions.md).


Например:

```cpp
class MyExternObject {

	public:

		// конструкторы
		MyExternObject() : mass(0.0f) {
		Log::warning("MyExternObject::MyExternObject(): called\n");
		}

		MyExternObject(const vec3 &size, float mass) : size(size), mass(mass) {
			Log::warning("MyExternObject::MyExternObject((%g,%g,%g),%g): called\n", size.x, size.y, size.z, mass);
		}

		// деструктор
		~MyExternObject() {
			Log::warning("MyExternObject::~MyExternObject(): called\n");
		}

		// экспорт класса в скрипт
		static void registerClass();

		// размер
		void setSize(const vec3 &s) {
			Log::warning("MyExternObject::setSize((%g,%g,%g)): called\n",s.x,s.y,s.z);
			size = s;
		}
		const vec3 &getSize() const {
			return size;
		}

		// масса
		void setMass(float m) {
			Log::warning("MyExternObject::setMass(%g): called\n",m);
			mass = m;
		}
		float getMass() const {
			return mass;
		}

	private:

		vec3 size;
		float mass;
};

/*
*/
MyExternObject *MakeMyExternObject(const vec3 &size,float mass) {
	return new MyExternObject(size,mass);
}

void DeleteMyExternObject(MyExternObject *object) {
	delete object;
}

/*
 */
void MyExternObjectSetSize(MyExternObject *object,const vec3 &size) {
	object->setSize(size);
}

const vec3 &MyExternObjectGetSize(MyExternObject *object) {
	return object->getSize();
}

// экспортируем внешний класс
void registerClass() {

	ExternClass<MyExternObject> *my_object = MakeExternClass<MyExternObject>();
	my_object->addConstructor();
	my_object->addConstructor<const vec3&, float>();
	my_object->addFunction("setSize",&MyExternObject::setSize);
	my_object->addFunction("getSize",&MyExternObject::getSize);
	my_object->addFunction("setMass",&MyExternObject::setMass);
	my_object->addFunction("getMass",&MyExternObject::getMass);
	Interpreter::addExternClass("MyExternObject",my_object);

	// экспортируем функции внешнего класса
	Interpreter::addExternFunction("DeleteMyExternObject",MakeExternFunction(&DeleteMyExternObject));
	Interpreter::addExternFunction("MakeMyExternObject",MakeExternFunction(&MakeMyExternObject));
	Interpreter::addExternFunction("MyExternObjectSetSize",MakeExternFunction(&MyExternObjectSetSize));
	Interpreter::addExternFunction("MyExternObjectGetSize",MakeExternFunction(&MyExternObjectGetSize));

}

```


Затем реализованный метод *registerClass()* можно вызвать одним из следующих способов:

- В функции *main()* перед инициализацией движка: ```cpp #ifdef _WIN32 int wmain(int argc,wchar_t *argv[]) { #else int main(int argc,char *argv[]) { #endif // экспортируем класс MyExternObject::registerClass(); AppSystemLogic system_logic; AppWorldLogic world_logic; AppEditorLogic editor_logic; Unigine::EnginePtr engine(argc,argv); // входим в главный цикл engine->main(&system_logic,&world_logic,&editor_logic); return 0; } ``` Если класс использует ресурсы движка и/или графические ресурсы, их следует корректно обрабатывать в главном цикле: Если, например, класс создаёт ресурс движка в конструкторе, а вы экспортируете этот класс в функции *main()*, ресурс движка может быть создан до инициализации движка, что приведёт к его сбою.

  - Если используются ресурсы движка (например, Texture, Image, Mesh, Node и т.д.), класс должен как минимум реализовывать методы *init()* и *shutdown()*. Именно в них должны выполняться создание и удаление ресурсов.
- В конструкторе [WorldLogic](../../../../code/fundamentals/execution_sequence/app_logic_system.md#worldlogic)/[SystemLogic](../../../../code/fundamentals/execution_sequence/app_logic_system.md#systemlogic). Например: ```cpp class MyWorldLogic : public WorldLogic { // экспортируем класс MyExternObject::registerClass(); public: virtual int init(); virtual int shutdown(); }; int MyWorldLogic::init() { Log::message("MyWorldLogic::init(): called\n"); return 1; } int MyWorldLogic::shutdown() { Log::message("MyWorldLogic::shutdown(): called\n"); return 1; } ``` > **Notice:** Если вы вызываете метод *registerClass()* в функции *init()* WorldLogic, класс не будет доступен в функции *init()* скрипта мира, поскольку она вызывается до инициализации WorldLogic согласно последовательности выполнения. То же самое верно для SystemLogic.


### Доступ из скриптов


После регистрации экспортированный класс можно использовать в UnigineScript точно так же, как и любые другие классы.


```cpp
// my_world.usc

/*
*/
void extern_object_info(MyExternObject object) {

	// вызываем методы объекта для получения его параметров
	vec3 size = object.getSize();
	float mass = object.getMass();

	log.message("size is: (%g,%g,%g), mass is: %g\n",size.x,size.y,size.z,mass);
}

/*
*/
int init() {

	/* ... code ... */
	/////////////////////////////////

	log.message("\n");

	// создаём внешний объект с помощью конструктора по умолчанию
	MyExternObject extern_object = new MyExternObject();
	extern_object_info(extern_object);

	// задаём параметры внешнего объекта
	extern_object.setSize(vec3(10.0f,20.0f,30.0f));
	extern_object_info(extern_object);

	// удаляем объект
	delete extern_object;

	/////////////////////////////////

	log.message("\n");

	// создаём объект с помощью другого конструктора
	extern_object = new MyExternObject(vec3(1.0f,2.0f,3.0f),10.0f);
	extern_object_info(extern_object);

	// задаём параметры объекта
	MyExternObjectSetSize(extern_object,vec3(10.0f,20.0f,30.0f));
	vec3 size = MyExternObjectGetSize(extern_object);
	log.message("size is: (%g,%g,%g)\n",size.x,size.y,size.z);

	// удаляем объект
	delete extern_object;

	/////////////////////////////////

	log.message("\n");

	// создаём объект с помощью функции внешнего класса
	extern_object = MakeMyExternObject(vec3(4.0f,5.0f,6.0f),10.0f);
	extern_object_info(extern_object);

	// задаём параметры объекта
	extern_object.setMass(100.0f);
	extern_object_info(extern_object);

	// удаляем объект с помощью функции внешнего класса
	DeleteMyExternObject(extern_object);

	/////////////////////////////////

	return 1;
}

```


### Вывод


В консоль будут выведены следующие результаты:


```text
MyExternObject::MyExternObject(): called
size is: (0,0,0), mass is: 0
MyExternObject::setSize((10,20,30)): called
size is: (10,20,30), mass is: 0
MyExternObject::~MyExternObject(): called

MyExternObject::MyExternObject((1,2,3),10): called
size is: (1,2,3), mass is: 10
MyExternObject::setSize((10,20,30)): called
size is: (10,20,30)
MyExternObject::~MyExternObject(): called

MyExternObject::MyExternObject((4,5,6),10): called
size is: (4,5,6), mass is: 10
MyExternObject::setMass(100): called
size is: (4,5,6), mass is: 100
MyExternObject::~MyExternObject(): called

```


## Экспорт класса-синглтона


Общий подход к экспорту классов C++, описанный выше, применим ко всем типам классов. Однако экспорт *классов-синглтонов* имеет несколько особенностей.


Класс-синглтон можно экспортировать в скрипт:

- Как *библиотеку*. ```cpp class Singleton { public: // получаем экземпляр синглтона static Singleton *get(); // экспортируем класс static void registerClass(); // создаём и удаляем ресурсы движка и GPU (если таковые есть) int init(); int shutdown(); // методы класса void setData(float data) { Log::message("singleton.setData() called\n"); }; float getData() const { Log::message("singleton.getData() called\n"); return 1.0f; } private: float data; static Singleton *instance; TexturePtr texture; }; // инициализируем экземпляр синглтона Singleton *Singleton::instance = nullptr; // получаем экземпляр синглтона Singleton *Singleton::get() { if (instance == nullptr) return new Singleton(); return instance; } // экспортируем класс-синглтон как библиотеку с именем "singleton" void Singleton::registerClass() { Singleton *instance = Singleton::get(); // добавляем библиотеку Interpreter::addExternLibrary("singleton"); // добавляем методы в библиотеку Interpreter::addExternFunction("singleton.getData", MakeExternObjectFunction(instance, &Singleton::getData)); Interpreter::addExternFunction("singleton.setData", MakeExternObjectFunction(instance, &Singleton::setData)); } int Singleton::init() { // инициализируем Texture return 1; } int Singleton::shutdown() { // удаляем Texture return 1; } ```
- Как класс с методом *get()*, возвращающим экземпляр синглтона. ```cpp class Singleton { public: // получаем экземпляр синглтона static Singleton *get(); // экспортируем класс static void registerClass(); // создаём и удаляем ресурсы движка и GPU (если таковые есть) int init(); int shutdown(); // методы класса void setData(float data) { Log::message("singleton.setData() called\n"); }; float getData() const { Log::message("singleton.getData() called\n"); return 1.0f; } private: float data; static Singleton *instance; TexturePtr texture; }; // инициализируем экземпляр синглтона Singleton *Singleton::instance = nullptr; // получаем экземпляр синглтона Singleton *Singleton::get() { if (instance == nullptr) return new Singleton(); return instance; } // экспортируем класс-синглтон как внешний класс с геттером void Singleton::registerClass() { // создаём внешний класс ExternClass<Singleton> *singleton_bindings = MakeExternClass<Singleton>(); singleton_bindings->addFunction("setData", &Singleton::setData); singleton_bindings->addFunction("getData", &Singleton::getData); Interpreter::addExternClass("Singleton", singleton_bindings); // добавляем геттер, возвращающий экземпляр синглтона Interpreter::addExternFunction("get_singleton", MakeExternFunction(&Singleton::get)); } int Singleton::init() { // инициализируем Texture return 1; } int Singleton::shutdown() { // удаляем Texture return 1; } ```

 Затем класс можно экспортировать в скрипт одним из способов, описанных [above](#export_classes). Например:
```cpp
#ifdef _WIN32
	int wmain(int argc,wchar_t *argv[]) {
#else
	int main(int argc,char *argv[]) {
#endif

	// экспортируем класс
	Singleton::registerClass();

	AppSystemLogic system_logic;
	AppWorldLogic world_logic;

	Unigine::EnginePtr engine(argc,argv);

	// входим в главный цикл
	engine->main(&system_logic,&world_logic);

	return 0;
}

```


### Доступ из скрипта


- Если класс был экспортирован как библиотека: ```cpp int init() { float data = singleton.getData(); return 1; } ```
- Если класс был экспортирован с геттером, возвращающим экземпляр синглтона: ```cpp int init() { Singleton singleton = get_singleton(); float data = singleton.getData(); return 1; } ```


## Экспорт класса с защищённым конструктором


При необходимости вы можете сделать защищённый конструктор класса C++ доступным из скриптов. Чтобы экспортировать его, необходимо объявить шаблон *Unigine::ExternClassConstructor<Class,List,Type>* дружественным (friend) классу.

> **Notice:** Поддерживается до 9 аргументов.

Объявление шаблона можно найти в файле заголовка `<UnigineSDK>/include/UnigineInterpreter.h`.
> **Notice:** Защищённые члены класса не могут быть экспортированы.


```cpp
#include <UnigineEngine.h>
#include <UnigineInterpreter.h>

using namespace Unigine;

/******************************************************************************\
*
* User defined class
*
\******************************************************************************/

/*
*/
class MyClass {

	protected:

		 // объявляем шаблон дружественным (friend) классу MyClass
		template <class,typename,typename> friend class Unigine::ExternClassConstructor;

		// определяем первый конструктор (без аргументов)
		MyClass() {
			Log::warning("MyClass::MyClass() is called\n");
		}

		// определяем второй конструктор с одним аргументом
		MyClass(int v) {
			Log::warning("MyClass::MyClass(%d) is called\n",v);
		}
};

/******************************************************************************\
*
* Main
*
\******************************************************************************/

/*
 */
int main(int argc,char **argv) {

	// экспортируем класс
	ExternClass<MyClass> *my_object = MakeExternClass<MyClass>();
	// добавляем конструктор по умолчанию без аргументов
	my_object->addConstructor();
	// добавляем конструктор с одним аргументом
	my_object->addConstructor<int>();
	// регистрируем экспортированный класс
	Interpreter::addExternClass("MyExternObject",my_object);

	// инициализируем движок
	Engine *engine = Engine::init(argc,argv);

	// входим в главный цикл
	engine->main();

	// завершаем работу движка
	Engine::shutdown();

	return 0;
}

```


Также можно объявить соответствующий шаблон дружественным классу для каждого из защищённых конструкторов следующим образом:

```cpp
class MyClass {

	protected:

		// объявляем шаблоны дружественными классу MyClass
		// один - для добавления конструктора без аргументов
		friend class Unigine::ExternClassConstructor<MyClass,MakeTypeList<>::Type>;
		// и другой - для добавления конструктора с одним аргументом
		friend class Unigine::ExternClassConstructor<MyClass,MakeTypeList<int>::Type>;

		// определяем первый конструктор (без аргументов)
		MyClass() {
			Log::warning("MyClass::MyClass() is called\n");
		}

		// определяем второй конструктор с одним аргументом
		MyClass(int v) {
			Log::warning("MyClass::MyClass(%d) is called\n",v);
		}
};

```


### Доступ из скриптов


После этого экспортированный класс можно использовать в UnigineScript.


```cpp
// my_world.usc

int init() {

	// создаём экземпляр экспортированного класса
	MyExternObject object_0 = new MyExternObject();
	MyExternObject object_1 = new MyExternObject(1);

	return 1;
}

```


### Вывод


```text
MyClass::MyClass() is called
MyClass::MyClass(1) is called

```


## Экспорт наследуемых классов


Вы можете экспортировать классы C++, унаследованные от других классов C++, в UnigineScript и использовать их так же, как и другие классы. Как базовый, так и производный классы экспортируются, как описано [above](#export_classes). Для каждого производного класса необходимо добавить базовый класс с помощью функции [*Unigine::ExternClass<Class>::addBaseClass()*](../../../../api/library/common/class.externclass_cpp.md#addBaseClass_ExternClassBase_ptr_void).

```cpp
my_derived_class->addBaseClass(my_base_class);
```

 В этом примере мы объявляем и экспортируем следующие классы:
- **MyBase** - базовый класс
- **MyNode** - класс, унаследованный от класса MyBase
- **MyObject** - класс, унаследованный от класса MyNode


```cpp
#include <UnigineEngine.h>
#include <UnigineInterpreter.h>
#include <UnigineInterface.h>

#include "AppSystemLogic.h"
#include "AppWorldLogic.h"

using namespace Unigine;

//////////////////////////////////////////////////////////////////////////
// User defined class
//////////////////////////////////////////////////////////////////////////

class MyBase
{
public:
	MyBase()
	{
		Log::warning("MyBase::MyBase(): called\n");
	}
	virtual ~MyBase()
	{
		Log::warning("MyBase::~MyBase(): called\n");
	}

	void function()
	{
		Log::warning("MyBase::function(): called\n");
	}

	virtual const char *getName() = 0;

	static void registerClasses();
};

class MyNode : public MyBase
{
public:
	MyNode()
	{
		Log::warning("MyNode::MyNode(): called\n");
	}
	virtual ~MyNode()
	{
		Log::warning("MyNode::~MyNode(): called\n");
	}

	void function()
	{
		Log::warning("MyNode::function(): called\n");
	}

	virtual const char *getName()
	{
		return "MyNode";
	}

	static void registerNode(ExternClass<MyBase> *my_base);

};

class MyObject : public MyNode
{
public:
	MyObject()
	{
		Log::warning("MyObject::MyObject(): called\n");
	}
	virtual ~MyObject()
	{
		Log::warning("MyObject::~MyObject(): called\n");
	}

	void function()
	{
		Log::warning("MyObject::function(): called\n");
	}

	virtual const char *getName()
	{
		return "MyObject";
	}

	static void registerObject(ExternClass<MyNode> *my_node);
};

void MyBase::registerClasses() {

	// создаём базовый класс
	ExternClass<MyBase> *my_base = MakeExternClass<MyBase>();

	// добавляем функции
	my_base->addFunction("function", &MyBase::function);
	my_base->addFunction("getName", &MyBase::getName);

	// регистрируем класс MyBase
	Interpreter::addExternClass("MyBase", my_base);

	MyNode::registerNode(my_base);

}

void MyNode::registerNode(ExternClass<MyBase> *my_base) {

	// создаём класс, унаследованный от MyBase
	ExternClass<MyNode> *my_node = MakeExternClass<MyNode>();

	// добавляем конструктор по умолчанию без аргументов
	my_node->addConstructor();
	my_node->addFunction("function", &MyNode::function);

	// добавляем базовый класс для класса MyNode
	my_node->addBaseClass(my_base);

	// регистрируем класс MyNode
	Interpreter::addExternClass("MyNode", my_node);

	MyObject::registerObject(my_node);
}

void MyObject::registerObject(ExternClass<MyNode> *my_node) {

	// создаём класс, унаследованный от MyNode
	ExternClass<MyObject> *my_object = MakeExternClass<MyObject>();

	// добавляем конструктор по умолчанию без аргументов
	my_object->addConstructor();

	// добавляем функцию
	my_object->addFunction("function", &MyObject::function);

	// добавляем базовый класс для класса MyObject
	my_object->addBaseClass(my_node);

	// регистрируем класс MyObject
	Interpreter::addExternClass("MyObject", my_object);
}

#ifdef _WIN32
int wmain(int argc, wchar_t *argv[])
#else
int main(int argc, char *argv[])
#endif
{

	MyBase::registerClasses();

	// инициализируем движок
	Unigine::EnginePtr engine(argc, argv);

	// UnigineLogic
	AppSystemLogic system_logic;
	AppWorldLogic world_logic;

	// входим в главный цикл
	engine->main(&system_logic, &world_logic);

	return 0;
}

```


### Доступ из скриптов


После регистрации экспортированные классы можно использовать в UnigineScript точно так же, как и любые другие классы.


```cpp
// my_world.usc

/*
*/

int init() {
	/////////////////////////////////

	log.message("\n");

	// класс объекта
	MyObject object = new MyObject();
	object.function();
	log.message("%s\n", object.getName());

	// класс узла
	MyNode node = object;
	node.function();
	log.message("%s\n", node.getName());

	// базовый класс
	MyBase base = node;
	base.function();
	log.message("%s\n", base.getName());

	// удаляем объект
	delete object;

	/////////////////////////////////

	// показываем консоль
	engine.console.setActivity(1);

}

```


### Вывод


В консоль будут выведены следующие результаты:


```text
MyBase::MyBase(): called
MyNode::MyNode(): called
MyObject::MyObject(): called
MyObject::function(): called
MyObject
MyNode::function(): called
MyObject
MyBase::function(): called
MyObject
MyObject::~MyObject(): called
MyNode::~MyNode(): called
MyBase::~MyBase(): called

```


## Управление памятью для внешних классов


При создании и удалении переменных, ссылающихся на внешние классы, необходимо задавать соответствующую область видимости (world / system / editor). Для установки требуемой области видимости следует использовать указатели на соответствующий интерпретатор, получаемые с помощью следующих функций:

- [*Unigine::Engine::getWorldInterpreter()*](../../../../api/library/engine/class.engine_cpp.md#getWorldInterpreter_void_ptr)
- [*Unigine::Engine::getSystemInterpreter()*](../../../../api/library/engine/class.engine_cpp.md#getSystemInterpreter_void_ptr)
- [*Unigine::Engine::getEditorInterpreter()*](../../../../api/library/engine/class.engine_cpp.md#getEditorInterpreter_void_ptr)


Также можно использовать указатель на текущий интерпретатор, получаемый с помощью функции [*Unigine::Interpreter::get()*](../../../../api/library/common/class.interpreter_cpp.md#get_void_ptr). Если эта функция вызывается интерпретатором мира, текущим интерпретатором будет интерпретатор мира.

```cpp
Interpreter *interpreter = Unigine::Interpreter::get();
```


> **Notice:** Если функция C++ вызывается из скрипта (мира, системы или редактора), это означает, что текущая область видимости уже установлена, и вызывать перечисленные выше функции не требуется.


Если соответствующая область видимости не установлена, при создании или удалении переменной могут возникать утечки памяти.


Например, если у вас есть функция, определённая на стороне скрипта, и вы хотите вызвать её из кода C++ с переменной внешнего класса в качестве аргумента, необходимо установить среду выполнения скрипта:


```cpp
#include <UnigineEngine.h>
#include <UnigineInterpreter.h>
#include <UnigineInterface.h>

#include <string>

using namespace Unigine;

class MyExternClass {

    public:

        MyExternClass() {}
        MyExternClass(const std::string &m) { my_member = m; }
        MyExternClass(const MyExternClass &other) { my_member = other.my_member; }
        ~MyExternClass() {}

    private:

        std::string my_member;

};

void my_update() {

    MyExternClass mec("hello!!!\n");
    Engine *engine = Engine::get();
	// получаем указатель на интерпретатор мира
	Interpreter *world = (Interpreter*)engine->getWorldInterpreter();
	// создаём переменную внешнего класса
	Unigine::Variable v(world,TypeInfo(TypeID<MyExternClass*>()),new MyExternClass(mec),1,1);
	// указываем имя вызываемой функции
	Unigine::Variable name("onMyUpdate");
	// вызываем функцию скрипта мира с переменной MyExternClass в качестве аргумента
   	engine->runWorldFunction(name,v);

}

int main(int argc,char **argv) {

    ExternClass<MyExternClass> *mec = MakeExternClass<MyExternClass>();
    Interpreter::addExternClass("MyExternClass",mec);

    Engine *engine = Engine::init(argc,argv);
    while(engine->isDone() == 0) {
		engine->update();
		engine->postUpdate();
		engine->swap();

        my_update();
    }

    Engine::shutdown();
    return 0;
}

```


> **Notice:** В примере выше *Variable v* является статической переменной, поэтому при выходе из области её видимости необходимо сбросить контекст.


```cpp
// функция скрипта мира, принимающая переменную, ссылающуюся на внешний класс
void onMyUpdate(MyExternClass v) {
	// какой-то код
}

int init() {
	// какой-то код
	return 1;
}

int shutdown() {
	// какой-то код
	return 1;
}

int update() {
	// какой-то код
	return 1;
}

```
