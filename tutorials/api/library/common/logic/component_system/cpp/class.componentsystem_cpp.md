# ComponentSystem Class (CPP)

**Header:** #include <UnigineComponentSystem.h>

**Inherits from:** Unigine::WorldLogic

> **Notice:** Этот класс является одиночкой (singleton).


Этот класс реализует функциональность [C++ Component System](../../../../../../principles/component_system/index.md) и используется для создания, удаления компонентов и управления ими.

> **Notice:** Этот класс является одиночкой (singleton).


### См. также


- [C++ Component System usage example](../../../../../../code/usage/using_component_system/index.md) с более подробной информацией об использовании C++ Component System.
- Пример C++


## ComponentSystem Class

### Методы класса

---

## ComponentSystem * get ( )

Возвращает указатель на C++ Component System. Этот указатель необходимо получить для доступа к функциям C++ Component System:
```cpp
ComponentSystem *cs = ComponentSystem::get();
// доступ к функциям C++ Component System
...

```


## void initialize ( )

Выполняет инициализацию C++ Component System, регистрацию всех компонентов и создание всех необходимых [property files](../../../../../../code/formats/property_format.md).
> **Notice:** - Этот метод следует вызывать в методе [AppSystemLogic::init()](../../../../../../code/fundamentals/execution_sequence/app_logic_system.md#systemlogic_init).
> - Если файл свойства для какого-либо компонента не существует, он будет создан автоматически.


```cpp
virtual int AppSystemLogic::init()
{
	// инициализация ComponentSystem и регистрация всех компонентов
	ComponentSystem::get()->initialize();

	/*...*/

	return 1;
}

```


## void addInitCallback ( Unigine:: CallbackBase * callback )

Добавляет обратный вызов, вызываемый во время инициализации ComponentSystem.
### Аргументы

- *Unigine::[CallbackBase](../../../../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **callback** - Указатель на обратный вызов.

## void setEnabled ( bool enabled )

Включает или отключает C++ Component System. Это можно использовать для отладки производительности: включать или отключать *update()*, *postUpdate()*, *updatePhysics()*, *swap()*, *updateSync()*, *updateAsync()* для всех компонентов.
### Аргументы

- *bool* **enabled** - true — включить C++ Component System, false — отключить её.

## bool isEnabled ( )

Возвращает значение, указывающее, включена ли C++ Component System. Это можно использовать для отладки производительности: проверить, включены/отключены ли *update()*, *postUpdate()*, *updatePhysics()*, *swap()*, *updateSync()*, *updateAsync()* для всех компонентов.
### Возвращаемое значение

true, если C++ Component System включена, false, если отключена.
## int getNumComponents ( )

Возвращает общее количество компонентов, зарегистрированных в C++ Component System.
> **Notice:** Этот метод очень медленный, и его не следует использовать часто.


### Возвращаемое значение

Общее количество зарегистрированных компонентов.
## int getNumNodesWithComponents ( )

Возвращает общее количество узлов с назначенными компонентами.
### Возвращаемое значение

Общее количество узлов с назначенными компонентами.
## template < C class >

## void createPropertyFile ( )

Создаёт файл свойства для зарегистрированного компонента, связанного со свойством с указанным именем. Параметры каждого компонента хранятся в отдельном файле `*.prop`. Если этот файл свойства не существует, он будет создан в папке `data/ComponentSystem` с именем, полученным методом компонента [getPropertyName()](../../../../../../api/library/common/logic/component_system/cpp/class.componentbase_cpp.md#getPropertyName_const_char_ptr).
## void initializeComponents ( constNodePtr & node )

Принудительно инициализирует компоненты, связанные с указанным узлом, в текущем кадре (не дожидаясь выполнения обратного вызова *WorldLogic::update()*).
### Аргументы

- *constNodePtr &* **node** - Узел, для которого требуется инициализировать компоненты.

## void createPropertyFile ( const char * name )

Создаёт файл свойства для зарегистрированного компонента, связанного со свойством с указанным именем. Параметры каждого компонента хранятся в отдельном файле `*.prop`. Если этот файл свойства не существует, он будет создан в папке `data/ComponentSystem`.
### Аргументы

- *const char ** **name** - Имя свойства, связанного с компонентом.

## void createPropertyFiles ( )

Создаёт файлы свойств для всех зарегистрированных компонентов. Параметры каждого компонента хранятся в отдельном файле `*.prop`. Если эти файлы свойств не существуют, они будут созданы в папке `data/ComponentSystem`.
## void refreshProperty ( const char * name )

Перезаписывает файл `*.prop` для указанного свойства и перезагружает его в [Property Manager](../../../../../../api/library/engine/class.properties_cpp.md).
### Аргументы

- *const char ** **name** - Имя свойства.

## template < C class >

## void refreshProperty ( )

Перезаписывает файл свойства для указанного компонента и перезагружает его в [Property Manager](../../../../../../api/library/engine/class.properties_cpp.md).
## template < C class >

## void registerComponent ( )

Регистрирует пользовательский компонент, унаследованный от класса [ComponentBase](../../../../../../api/library/common/logic/component_system/cpp/class.componentbase_cpp.md).
> **Notice:** - Компоненты должны регистрироваться в методе [AppSystemLogic::init()](../../../../../../code/fundamentals/execution_sequence/app_logic_system.md#systemlogic_init).
> - Если файл свойства для компонента не существует, он будет создан автоматически.
> - Вместо этого рекомендуется использовать макрос *[REGISTER_COMPONENT](../../../../../../code/usage/using_component_system/index.md#REGISTER_COMPONENT)*.


```cpp
virtual int AppSystemLogic::init()
{
	// регистрация нового пользовательского компонента
	ComponentSystem::get()->registerComponent<MyComponent>();

	/*...*/

	return 1;
}

```


## template < C class >

## void unregisterComponent ( )

Удаляет пользовательский компонент, унаследованный от класса [ComponentBase](../../../../../../api/library/common/logic/component_system/cpp/class.componentbase_cpp.md).
## template < C class >

## C * addComponent ( const Node Ptr & node )

Добавляет компонент к указанному узлу.
```cpp
NodeDummyPtr node = NodeDummy::create();
node->setName("node_dummy");

ComponentSystem::get()->addComponent<MyComponent>(node->getNode());
// теперь узел с именем node_dummy появится в редакторе

```


### Аргументы

- *const [Node](../../../../../../api/library/nodes/class.node_cpp.md)Ptr &* **node** - Узел, к которому добавляется компонент.

### Возвращаемое значение

Указатель на новый добавленный компонент, если он был успешно добавлен к указанному узлу; иначе **nullptr**.
## template < C class >

## C * getComponent ( const Node Ptr & node , bool enabled_only = false )

Возвращает первый компонент указанного типа, связанный с указанным узлом.
### Аргументы

- *const [Node](../../../../../../api/library/nodes/class.node_cpp.md)Ptr &* **node** - Узел, для которого требуется найти компонент указанного типа.
- *bool* **enabled_only** - Флаг включённости: true — получить только включённый компонент, false — получить компонент в любом случае.

### Возвращаемое значение

Указатель на компонент, если он есть; иначе nullptr.
## template < C class >

## void getComponents ( const Node Ptr & node , Vector <C *> & out_components , int clear_vector )

Выполняет поиск всех компонентов указанного типа, назначенных указанному узлу, и помещает их в заданный буферный вектор.
### Аргументы

- *const [Node](../../../../../../api/library/nodes/class.node_cpp.md)Ptr &* **node** - Узел, для которого требуется найти компоненты указанного типа.
- *[Vector](../../../../../../api/library/containers/vector/class.vector_cpp.md)<C *> &* **out_components** - Буферный вектор, в который будут добавлены все найденные компоненты указанного типа.
- *int* **clear_vector** - Флаг, указывающий, следует ли очищать буферный вектор перед добавлением найденных компонентов. Используйте **1**, чтобы очистить вектор, **0** — чтобы добавлять новые найденные компоненты в конец вектора. Значение по умолчанию — 1.

## template < C class >

## C * getComponentInChildren ( const Node Ptr & node , bool enabled_only = false )

Возвращает первый компонент указанного типа, найденный среди всех дочерних узлов указанного узла (включая сам узел). Этот метод выполняет поиск компонента в следующем порядке:
- сам узел
- ссылка на узел
- дочерние узлы
- дочерние узлы дочерних узлов


### Аргументы

- *const [Node](../../../../../../api/library/nodes/class.node_cpp.md)Ptr &* **node** - Узел, иерархию которого требуется проверить на наличие компонента указанного типа.
- *bool* **enabled_only** - Флаг включённости: true — получить только включённый компонент, false — получить компонент в любом случае.

### Возвращаемое значение

Указатель на компонент, если он есть; иначе nullptr.
## template < C class >

## void getComponentsInChildren ( const Node Ptr & node , Vector <C *> & out_components , int clear_vector )

Выполняет поиск всех компонентов указанного типа вниз по иерархии указанного узла и помещает их в заданный буферный вектор.
### Аргументы

- *const [Node](../../../../../../api/library/nodes/class.node_cpp.md)Ptr &* **node** - Узел, иерархию которого требуется проверить.
- *[Vector](../../../../../../api/library/containers/vector/class.vector_cpp.md)<C *> &* **out_components** - Буферный вектор, в который будут добавлены все найденные компоненты указанного типа.
- *int* **clear_vector** - Флаг, указывающий, следует ли очищать буферный вектор перед добавлением найденных компонентов. Используйте **1**, чтобы очистить вектор, **0** — чтобы добавлять новые найденные компоненты в конец вектора. Значение по умолчанию — 1.

## template < C class >

## C * getComponentInParent ( const Node Ptr & node , bool enabled_only = false )

Возвращает первый компонент указанного типа, найденный среди всех предков и [posessors](../../../../../../api/library/nodes/class.node_cpp.md#getPossessor_Node) указанного узла.
### Аргументы

- *const [Node](../../../../../../api/library/nodes/class.node_cpp.md)Ptr &* **node** - Узел, иерархию которого требуется проверить.
- *bool* **enabled_only** - Флаг включённости: true — получить только включённый компонент, false — получить компонент в любом случае.

### Возвращаемое значение

Указатель на компонент, если он есть; иначе nullptr.
## template < C class >

## void getComponentsInParent ( const Node Ptr & node , Vector <C *> & out_components , int clear_vector )

Выполняет поиск всех компонентов указанного типа вверх по иерархии указанного узла и помещает их в заданный буферный вектор.
### Аргументы

- *const [Node](../../../../../../api/library/nodes/class.node_cpp.md)Ptr &* **node** - Узел, иерархию которого требуется проверить.
- *[Vector](../../../../../../api/library/containers/vector/class.vector_cpp.md)<C *> &* **out_components** - Буферный вектор, в который будут добавлены все найденные компоненты указанного типа.
- *int* **clear_vector** - Флаг, указывающий, следует ли очищать буферный вектор перед добавлением найденных компонентов. Используйте **1**, чтобы очистить вектор, **0** — чтобы добавлять новые найденные компоненты в конец вектора. Значение по умолчанию — 1.

## template < C class >

## C * getComponentInWorld ( bool enabled_only = false )

Возвращает первый компонент этого типа, найденный в текущем мире.
### Аргументы

- *bool* **enabled_only** - Флаг включённости: true — получить только включённый компонент, false — получить компонент в любом случае.

### Возвращаемое значение

Указатель на компонент, если он есть; иначе nullptr.
## template < C class >

## void getComponentsInWorld ( Vector <C *> & out_components , bool enabled_only = false )

Выполняет поиск всех компонентов указанного типа в текущем мире и помещает их в заданный буферный вектор.
### Аргументы

- *[Vector](../../../../../../api/library/containers/vector/class.vector_cpp.md)<C *> &* **out_components** - Буферный вектор, в который будут добавлены все найденные компоненты указанного типа.
- *bool* **enabled_only** - Флаг включённости: true — получить только включённые компоненты, false — получить все компоненты.

## template < C class >

## int removeComponent ( const Node Ptr & node )

Удаляет компонент с указанного узла.
```cpp
// удаляет пользовательский компонент MyComponent с узла
ComponentSystem::get()->removeComponent<MyComponent>(some_node);

```


### Аргументы

- *const [Node](../../../../../../api/library/nodes/class.node_cpp.md)Ptr &* **node** - Узел, с которого удаляется компонент.

### Возвращаемое значение

**1**, если компонент был успешно удалён с указанного узла; иначе **0**.
## void setWarningLevel ( int level )

Задаёт уровень предупреждений для C++ Component System. Предупреждения могут быть очень полезны при отладке приложения, например, для исследования случаев Null Reference Exception.
### Аргументы

- *int* **level** - Новый устанавливаемый уровень предупреждений. Одно из следующих значений:

  - WARNING_LEVEL::NONE - сообщения о предупреждениях отключены.
  - WARNING_LEVEL::LOW - сообщения о предупреждениях генерируются только для серьёзных случаев.
  - WARNING_LEVEL::HIGH - сообщения о предупреждениях генерируются для всех случаев, включая потенциальные. На этом уровне, например, будет сообщаться обо всех параметрах Node/Property/Material, которые пусты при запуске.

## int getWarningLevel ( )

Возвращает текущий уровень предупреждений для C++ Component System. Предупреждения могут быть очень полезны при отладке приложения, например, для исследования случаев Null Reference Exception.
### Возвращаемое значение

Текущий уровень предупреждений. Одно из следующих значений:
- WARNING_LEVEL::NONE - сообщения о предупреждениях отключены.
- WARNING_LEVEL::LOW - сообщения о предупреждениях генерируются только для серьёзных случаев.
- WARNING_LEVEL::HIGH - сообщения о предупреждениях генерируются для всех случаев, включая потенциальные. На этом уровне, например, будет сообщаться обо всех параметрах Node/Property/Material, которые пусты при запуске.
