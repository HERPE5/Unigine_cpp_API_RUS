# Unigine::NodeExtern Class (CPP)

**Header:** #include <UnigineNodes.h>

**Inherits from:** Node


NodeExtern — это пользовательский узел, создаваемый через API. Класс NodeExtern является обёрткой для реализации пользовательского класса узла, унаследованного от класса [NodeExternBase](../../../api/library/nodes/class.nodeexternbase_cpp.md).


Узел NodeExtern создаётся, когда движок загружает экземпляр пользовательского класса узла. Он также может быть создан напрямую с использованием конструктора класса с ID пользовательского класса узла в качестве аргумента. В обоих случаях узел NodeExtern оборачивает пользовательский класс узла, унаследованный от NodeExternBase.


Пользовательский узел создаётся следующим образом:

> **Notice:** Пользовательский узел может быть реализован только на стороне C++. Поэтому необходимо реализовать пользовательский класс узла на C++, а затем использовать его на стороне C++ или UnigineScript.


1. Унаследуйте пользовательский класс узла от NodeExternBase: ```cpp #include <UnigineNodes.h> using namespace Unigine; // наследование пользовательского класса от NodeExternBase class MyNode : public NodeExternBase { }; ```
2. Реализуйте логику пользовательского узла и зарегистрируйте класс через *[NodeExternBase::addClassID()](../../../api/library/nodes/class.nodeexternbase_cpp.md)*: > **Notice:** Пользовательский класс узла не является узлом, так как класс NodeExternBase не унаследован от класса [Node](../../../api/library/nodes/class.node_cpp.md). ```cpp #include <UnigineNodes.h> #include <UnigineEngine.h> #include "AppSystemLogic.h" #include "AppWorldLogic.h" using namespace Unigine; // наследование пользовательского класса от NodeExternBase class MyNode : public NodeExternBase { public: // конструкторы MyNode(){} MyNode(void *node) : NodeExternBase(node){} // деструктор virtual ~MyNode(){} // уникальный ID класса virtual int getClassID() {return 1;} // задание мировой трансформации узла void setWorldTransform(const Math::Mat4 &transform) {getNode()->setWorldTransform(transform);} // другие методы // ... }; int main(int argc,char *argv[]) { // регистрация класса MyNode NodeExternBase::addClassID<MyNode>(1); Unigine::EnginePtr engine(argc,argv); AppSystemLogic system_logic; AppWorldLogic world_logic; engine->main(&system_logic,&world_logic); return 0; } ``` При необходимости пользовательский класс узла можно [exported to UnigineScript](../../../api/library/nodes/class.nodeexternbase_cpp.md#export_class).
3. Создайте пользовательский узел одним из следующих способов: ```cpp // создание указателя MyNode напрямую: узел NodeExtern также будет создан MyNode *my_node_0 = new MyNode(); // получение узла NodeExtern my_node_0->getNodeExtern(); // создание экземпляра NodeExtern по ID класса MyNode NodeExternPtr my_node_1 = NodeExtern::create(1); // получение указателя MyNode при необходимости MyNode *my_node_2 = (MyNode*)my_node_1->getNodeExtern(); ``` Если класс был [exported to UnigineScript](../../../api/library/nodes/class.nodeexternbase_cpp.md#export_class), можно выполнить то же самое на стороне UnigineScript: ```cpp // создание указателя MyNode напрямую: узел NodeExtern также будет создан MyNode my_node_0 = new MyNode(); // получение узла NodeExtern my_node_0.getNodeExtern(); // создание экземпляра NodeExtern по ID класса MyNode NodeExtern my_node_1 = new NodeExtern(1); // получение MyNode при необходимости MyNode my_node_2 = class_cast("MyNode", node.getNodeExtern()); ```


### См. также


- Класс [NodeExternBase](../../../api/library/nodes/class.nodeexternbase_cpp.md) для полного примера использования классов NodeExtern и NodeExternBase.
- Пример на C++


## Класс NodeExtern

### Методы класса

---

## static NodeExternPtr create ( int class_id )

Конструктор. Создаёт пользовательский узел. Также будет создан экземпляр пользовательского класса узла.
### Аргументы

- *int* **class_id** - Уникальный ID класса.

## int getClassID ( )

Возвращает [class ID](../../../api/library/nodes/class.nodeexternbase_cpp.md#addClassID_int_void) узла.
### Возвращаемое значение

ID класса, если узел существует; иначе 0.
## NodeExternBase * getNodeExtern ( )

Возвращает указатель на пользовательский класс узла.
```cpp
// создание экземпляра NodeExtern по ID класса MyNode
NodeExternPtr my_node_1 = NodeExtern::create(1);
// получение указателя MyNode
MyNode *my_node_2 = (MyNode*)my_node_1->getNodeExtern();

```


### Возвращаемое значение

Указатель на пользовательский класс узла.
## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [NodeExtern](../../../api/library/nodes/class.node_cpp.md#NODE_EXTERN).
