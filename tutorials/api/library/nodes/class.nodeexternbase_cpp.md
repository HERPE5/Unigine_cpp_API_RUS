# Unigine::NodeExternBase Class (CPP)

**Header:** #include <UnigineNodes.h>

**Inherits from:** Base


Базовый класс, используемый для реализации логики [custom user-defined nodes](../../../api/library/nodes/class.nodeextern_cpp.md). Пользовательский класс узла должен быть унаследован от NodeExternBase.


> **Notice:** NodeExternBase не является узлом (он не унаследован от класса [Node](../../../api/library/nodes/class.node_cpp.md)). Поэтому когда движок загружает экземпляр пользовательского класса узла, создаётся узел [NodeExtern](../../../api/library/nodes/class.nodeextern_cpp.md). Он оборачивает реализацию пользовательского класса узла, унаследованного от класса NodeExternBase.


### Пример использования


Чтобы реализовать логику пользовательского узла, выполните следующее:

> **Notice:** Пользовательский узел может быть реализован только на стороне C++. Поэтому пример ниже показывает, как реализовать такой узел на C++, а затем использовать его как на C++, так и на UnigineScript.


1. Унаследуйте ваш пользовательский класс узла от *NodeExternBase*.
2. Реализуйте конструкторы, деструктор и все необходимые методы.
3. Зарегистрируйте класс через *addClassID()*.
4. (Опционально) При необходимости экспортируйте класс и его функции в UnigineScript.


`MyNode.h` содержит реализацию пользовательского класса *MyNode*, унаследованного от класса NodeExternBase.


```cpp
#include <UnigineNodes.h>

using namespace Unigine;

// наследование пользовательского класса от NodeExternBase
class MyNode : public NodeExternBase
{
public:

	// конструкторы
	MyNode();
	MyNode(void *node);
	// деструктор
	virtual ~MyNode();

	// уникальный ID класса
	virtual int getClassID();

	// сохранение и восстановление состояния узла
	virtual int saveState(const StreamPtr &stream);
	virtual int restoreState(const StreamPtr &stream);

	// сохранение и восстановление указателя на узел
	static void savePointer(const StreamPtr &stream, MyNode *node);
	static NodeExternBase *restorePointer(const StreamPtr &stream);

	// задание мировой трансформации узла
	void setWorldTransform(const Math::Mat4 &transform);
};

```


`MyNode.cpp` содержит реализацию методов MyNode.


```cpp
#include "MyNode.h"

// конструктор без аргументов
MyNode::MyNode()
{
	Log::warning("MyNode::MyNode(): called\n");
}
// конструктор с 1 аргументом
MyNode::MyNode(void *node)
	: NodeExternBase(node)
{
	Log::warning("MyNode::MyNode(void*): called\n");
}
// деструктор
MyNode::~MyNode()
{
	Log::warning("MyNode::~MyNode(): called\n");
}
// возвращает ID класса MyNode
int MyNode::getClassID()
{
	return 1;
}
// сохранение состояния узла
int MyNode::saveState(const StreamPtr &stream)
{
	Log::warning("MyNode::saveState(): called\n");
	return NodeExternBase::saveState(stream);
}
// восстановление состояния узла
int MyNode::restoreState(const StreamPtr &stream)
{
	Log::warning("MyNode::restoreState(): called\n");
	return NodeExternBase::restoreState(stream);
}
// сохранение указателя на узел
void MyNode::savePointer(const StreamPtr &stream, MyNode *node)
{
	Log::warning("MyNode::savePointer(): called\n");
	return NodeExternBase::savePointer(stream, node);
}
// восстановление указателя на узел
NodeExternBase *MyNode::restorePointer(const StreamPtr &stream)
{
	Log::warning("MyNode::restorePointer(): called\n");
	return NodeExternBase::restorePointer(stream);
}

// задание мировой трансформации узла
void MyNode::setWorldTransform(const Math::Mat4 &transform)
{
	getNode()->setWorldTransform(transform);
	Log::message("MyNode::setWorldTransform(): called\n");
}

```


В `unigine_project.cpp` регистрируется класс MyNode.


```cpp
#include <UnigineEngine.h>
#include "AppSystemLogic.h"
#include "AppWorldLogic.h"
#include "MyNode.h"

int main(int argc,char *argv[]) {

	// регистрация класса MyNode
	NodeExternBase::addClassID<MyNode>(1);

	Unigine::EnginePtr engine(argc,argv);

	AppSystemLogic system_logic;
	AppWorldLogic world_logic;

	engine->main(&system_logic,&world_logic);

	return 0;
}

```


В `AppWorldLogic.cpp` показаны подходы к работе с классом MyNode: можно напрямую создать экземпляр класса MyNode или создать экземпляр класса NodeExtern, используя ID класса MyNode. В обоих случаях создаётся экземпляр класса MyNode.


```cpp
#include "AppWorldLogic.h"
#include "MyNode.h"

int AppWorldLogic::init() {

	// создание указателя MyNode напрямую
	MyNode *my_node_0 = new MyNode();
	// вызов функции-члена
	my_node_0->setWorldTransform(Math::translate(Math::Vec3(0.5)));

	// создание экземпляра NodeExtern по ID класса MyNode
	NodeExternPtr my_node_1 = NodeExtern::create(1);
	// получение указателя MyNode
	MyNode *my_node_2 = (MyNode*)my_node_1->getNodeExtern();
	// вызов функции-члена MyNode
	my_node_2->setWorldTransform(Math::translate(Math::Vec3(1.0)));

	return 1;
}

```


```text
MyNode::MyNode(): called
MyNode::setWorldTransform(): called
MyNode::MyNode(void*): called
MyNode::setWorldTransform(): called
MyNode::~MyNode(): called

```


#### Экспорт в UnigineScript


Чтобы использовать пользовательский узел на стороне UnigineScript, экспортируйте класс и его функции в UnigineScript.


`unigine_project.cpp`:


```cpp
#include <UnigineEngine.h>
#include <UnigineInterface.h>
#include "AppSystemLogic.h"
#include "AppWorldLogic.h"
#include "MyNode.h"

int main(int argc,char *argv[]) {

	// регистрация класса MyNode
	NodeExternBase::addClassID<MyNode>(1);

	// экспорт класса MyNode
	ExternClass<MyNode> *my_node = MakeExternClassSaveRestoreStatePointer<MyNode>();
	my_node->addConstructor();
	my_node->addFunction("grab", &MyNode::grab);
	my_node->addFunction("release", &MyNode::release);
	my_node->addFunction("getNode", &MyNode::getNode);
	my_node->addFunction("setWorldTransform", &MyNode::setWorldTransform);
	Interpreter::addExternClass("MyNode", my_node);

	Unigine::EnginePtr engine(argc,argv);

	AppSystemLogic system_logic;
	AppWorldLogic world_logic;

	engine->main(&system_logic,&world_logic);

	return 0;
}

```


А затем используйте класс MyNode на стороне UnigineScript:


```cpp
#include <core/unigine.h>

int init() {

	// создание MyNode
	MyNode my_node_0 = new MyNode();
	my_node_0.setWorldTransform(Mat4(translate(0.0f, 0.0f, 1.0f)));

	// создание NodeExtern по ID класса
	NodeExtern node = new NodeExtern(1);
	MyNode my_node_1 = class_cast("MyNode", node.getNodeExtern());
	my_node_1.setWorldTransform(Mat4(translate(0.0f, 0.0f, -1.0f)));

	return 1;
}

```


## Класс NodeExternBase

### Методы класса

---

## template < class Type >

## static addClassID ( int class_id )

Регистрирует пользовательский класс узла с уникальным ID класса.
```cpp
// регистрация класса MyNode
NodeExternBase::addClassID<MyNode>(1);

```


### Аргументы

- *int* **class_id** - Уникальный ID класса.

## void copy ( NodeExternBase * node , int is_root )

Копирует текущий пользовательский узел в заданный.
### Аргументы

- *[NodeExternBase](../../../api/library/nodes/class.nodeexternbase_cpp.md) ** **node** - Указатель на целевой узел.
- *int* **is_root** - Уникальный ID класса.

## BoundBox getBoundBox ( )

Возвращает ограничивающий параллелепипед пользовательского узла.
### Возвращаемое значение

Ограничивающий параллелепипед.
## BoundSphere getBoundSphere ( )

Возвращает ограничивающую сферу пользовательского узла.
### Возвращаемое значение

Ограничивающая сфера.
## int getClassID ( )

Возвращает уникальный ID класса.
### Возвращаемое значение

Уникальный ID класса.
## Ptr < Node > getNode ( )

Возвращает умный указатель на Node.
### Возвращаемое значение

Умный указатель на Node.
## Ptr < NodeExtern > getNodeExtern ( )

Возвращает экземпляр [NodeExtern](../../../api/library/nodes/class.nodeextern_cpp.md), созданный при загрузке пользовательского узла.
### Возвращаемое значение

Умный указатель на NodeExtern.
## int loadWorld ( const Ptr < Xml > & xml )

Загружает состояние узла из Xml.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../api/library/common/class.xml_cpp.md)> &* **xml** - Умный указатель на Xml.

### Возвращаемое значение

Возвращает 1, если состояние узла успешно загружено; иначе возвращается 0.
## void renderHandler ( )

Отображает манипулятор пользовательского узла.
## void renderVisualizer ( )

Отображает визуализатор для пользовательского узла.
> **Notice:** Необходимо включить визуализатор движка консольной командой **show_visualizer 1**.


## bool saveState ( const Ptr < Stream > & stream )

Сохраняет состояние узла в поток.
Для сохранения в поток требуется создать blob для сохранения. Для восстановления сохранённого состояния используется метод [restoreState()](#restoreState_Stream_int):


```cpp
// initialize a node and set its state
//...//

// save state
BlobPtr blob_state = Blob::create();
node->saveState(blob_state);

// change state
//...//

// restore state
blob_state->seekSet(0);				// returning the carriage to the start of the blob
node->restoreState(blob_state);

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Умный указатель на поток.

### Возвращаемое значение

true при успехе; иначе false.
## bool restoreState ( const Ptr < Stream > & stream )

Восстанавливает состояние узла из потока.
Для восстановления из потока требуется создать blob для сохранения и сохранить состояние, используя метод [saveState()](#saveState_Stream_int):


```cpp
// initialize a node and set its state
//...//

// save state
BlobPtr blob_state = Blob::create();
node->saveState(blob_state);

// change state
//...//

// restore state
blob_state->seekSet(0);				// returning the carriage to the start of the blob
node->restoreState(blob_state);

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Умный указатель на поток.

### Возвращаемое значение

true при успехе; иначе false.
## int saveWorld ( const Ptr < Xml > & xml )

Сохраняет состояние узла в Xml.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../api/library/common/class.xml_cpp.md)> &* **xml** - Умный указатель на Xml.

### Возвращаемое значение

1, если состояние узла успешно сохранено; иначе возвращается 0.
## void swap ( NodeExternBase * node )

Меняет местами два пользовательских узла.
### Аргументы

- *[NodeExternBase](../../../api/library/nodes/class.nodeexternbase_cpp.md) ** **node** - Указатель на пользовательский узел для обмена.

## void updateEnabled ( )

Обновляет состояние enabled.
## void updateTransform ( )

Обновляет матрицу трансформации пользовательского узла.
