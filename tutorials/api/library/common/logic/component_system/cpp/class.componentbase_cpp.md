# ComponentBase Class (CPP)

**Header:** #include <UnigineComponentSystem.h>


Это базовый класс, реализующий базовую функциональность C++ логических [components](../../../../../../principles/component_system/index.md).


> **Notice:** Все ваши компоненты должны быть унаследованы от этого класса.


Для объявления компонента используйте макрос ***COMPONENT_DEFINE***, в этом случае имя свойства, связанного с компонентом, будет совпадать с именем класса.


```cpp
#include <UnigineComponentSystem.h>

using namespace Unigine;

class MyComponent : public ComponentBase
{
public:
	// объявление конструктора и деструктора класса MyComponent
	COMPONENT_DEFINE(MyComponent, ComponentBase);

	//...
};

```


Чтобы указать пользовательское имя свойства, вместо этого используйте макросы ***COMPONENT*** и ***PROP_NAME***:


```cpp
// конструктор и деструктор компонента
COMPONENT(MyComponent, Unigine::ComponentBase);

// пользовательское имя свойства, связанного с компонентом
PROP_NAME("my_component");

```


### Параметры компонента


Параметр компонента создаётся с использованием любого из следующих макросов. Каждый макрос имеет [format](../../../../../../code/formats/property_format.md), указанный в скобках, с **обязательными** аргументами, выделенными жирным шрифтом:


- [PROP_PARAM](#param_basic)(**type, name**, mask_type [только для параметров Mask], default_value, items [только для параметров switch], title, tooltip, group, args)
- [PROP_STRUCT](#param_structures)(**type, name**, title, tooltip, group, args)
- [PROP_ARRAY](#param_arrays)(**type, name**, title, tooltip, group, args)
- [PROP_ARRAY_STRUCT](#param_arrays)(**struct_type, name**, title, tooltip, group, args)


Общие необязательные аргументы:


- *title, tooltip, group* - для отображения соответствующей информации о параметре свойства в UnigineEditor.
- *args* - для передачи аргументов (например, значений min/max, условий, фильтров файлов) в XML-элемент параметра в свойстве компонента. В следующем примере *Setting 1* и *Setting 2* отображаются только если *Auto Adjustment* отключён: ```cpp PROP_PARAM(Toggle, auto_adjustment, false); PROP_PARAM(Float, setting_1, 2.0f / 1.0f, "Setting 1", "", "", "auto_adjustment=0"); PROP_PARAM(Float, setting_2, 1.0f, "Setting 2", "", "", "auto_adjustment=0"); ```


Подробнее об *args* см. [here](../../../../../../code/formats/property_format.md#element_parameter).


При создании компонента следует объявить все используемые параметры. Список [available parameter types](../../../../../../code/formats/property_format.md#parameter_type) такой же, как и для [properties](../../../../../../principles/properties/index.md), поскольку они используются как основа для компонентов.


#### Базовые параметры


Параметры базовых типов (Int, Float, Node, Material и т. д.) объявляются с использованием макроса **PROP_PARAM**, имеющего следующий формат:


```cpp
				PROP_PARAM(type, name, mask_type, default_value, items, title, tooltip, group, args)

```


Аргументы, кроме *type, name*, являются необязательными:


- *mask_type* - только для параметров Mask; доступные типы масок перечислены [here](../../../../../../code/formats/property_format.md#mask_flags).
- *default_value* - доступен для всех типов параметров, но может быть опущен для Vec*, Color, Property, Material, Node и Curve2d. Например: ```cpp // для значения int его следует задавать следующим образом PROP_PARAM(Int, name, 0, "title", "tooltip") // для Vec*, Color, Property, Material, Node и Curve2d это может выглядеть так PROP_PARAM(Color, name, vec4_black, "title", ...) // или даже так PROP_PARAM(Color, name, "title", ...) ```
- *items* - только для параметра типа [*switch*](../../../../../../code/formats/property_format.md#parameter_type).


#### Структуры


Каждая структура, которую вы хотите использовать в своём компоненте, должна быть унаследована от класса **ComponentStruct**. Это необходимо для обеспечения корректной генерации соответствующего [property file](../../../../../../code/formats/property_format.md).


Для объявления структурированного параметра используйте следующий макрос (последние три аргумента необязательны, см. [above](#parameters)):

```cpp
PROP_STRUCT(type, name, title, tooltip, group, args);
```


> **Notice:** Если компонент имеет структурированный параметр (**struct**), определение структуры должно появиться перед объявлением параметра. То же самое верно, когда структура наследуется от другой структуры: родитель должен быть определён перед своим потомком.


Ниже приведён пример компонента с именем **SomeComponent**, имеющего несколько параметров различных типов, включая структуры (вложенные и наследуемые):


```cpp
class SomeComponent: public Unigine::ComponentBase
{
public:
	// конструктор и деструктор нашего компонента
	COMPONENT(SomeComponent, Unigine::ComponentBase);

	// имя свойства, связанного с компонентом
	PROP_NAME("my_component");

	// методы, выполняемые на определённых этапах последовательности выполнения
	COMPONENT_INIT(init);

	// параметры
	PROP_PARAM(Float, speed, 30.0f);
	PROP_PARAM(Node, some_node);

	// объявление структуры (свойства внутри свойства) с именем "ParentStruct"
	struct ParentStruct : public Unigine::ComponentStruct
	{
		// параметры, которые будут отображаться в UnigineEditor
		PROP_PARAM(Int, var1, 1);
		PROP_PARAM(Float, var2, 2.0f);
		PROP_PARAM(Double, var3, 3.0f);

		// вспомогательные переменные, которые не будут видны в UnigineEditor
		float my_var1 = 2.0f;
		int my_var2 = 10;
	};

	// объявление структурированного параметра с именем "my_struct" типа ParentStruct, объявленного выше
	PROP_STRUCT(ParentStruct, my_struct);

	// объявление дочерней структуры с именем "ChildStruct", унаследованной от ParentStruct
	struct ChildStruct : public ParentStruct
	{
		// параметры, которые будут отображаться в UnigineEditor
		PROP_PARAM(Int, child_param1, 1);
		PROP_PARAM(Double, child_param2, 2.0f);

		// объявление вложенной структуры
		struct NestedStruct : public Unigine::ComponentStruct
		{
			// параметры, которые будут отображаться в UnigineEditor
			PROP_PARAM(String, string_param1, "This is my string!");
		};

		// объявление структурированного параметра с именем "my_nested_struct" типа NestedStruct, объявленного выше
		PROP_STRUCT(NestedStruct, my_nested_struct);
	};

	// объявление структурированного параметра с именем "my_struct2" типа ChildStruct, объявленного выше
	PROP_STRUCT(ChildStruct, my_struct2, "Child Struct", "Example of an inherited structure with a nested one");

	// ...
};

```


#### Массивы


Параметры типа массив объявляются с использованием следующих макросов (последние три аргумента необязательны, см. [above](#parameters)):


```cpp
PROP_ARRAY_STRUCT(struct_type, name, title, tooltip, group, args);	// для массивов структур
PROP_ARRAY(type, name, title, tooltip, group, args);				// для массивов всех остальных типов

```


Например, чтобы объявить простой массив элементов типа integer и массив элементов **ParentStruct** для описанного выше компонента **SomeComponent**, можно использовать:


```cpp
// ...

// объявление простого массива элементов типа integer с именем int_array
PROP_ARRAY(Int, int_array, "Integer Array", "This is an array of integer elements");

// объявление массива элементов ParentStruct с именем struct_array (ParentStruct должна быть объявлена ранее)
PROP_ARRAY_STRUCT(ParentStruct, struct_array);

// ...

```


> **Notice:** Вы можете [edit arrays](../../../../../../editor2/properties_settings/index.md#edit_arrays) в UnigineEditor с помощью контекстного меню.


#### Доступ к параметрам


Доступ к параметрам, включая параметры типа массив и структурированные, внутри компонента прост (во многом так же, как вы обычно работаете с переменными-членами). Ниже приведён пример доступа к параметрам описанного выше компонента **SomeComponent** внутри его метода *init()*:


```cpp
// ...

SomeComponent::init()
{
	// ...

	// изменение значения параметра speed
	speed = 120.0f;

	// изменение размера массива и установка значений нескольких его элементов
	int_array.resize(5);
	int_array[0] = 1;
	int_array[4] = 10;

	// установка значения параметра var3 первого элемента ParentStruct массива с именем struct_array
	struct_array[0]->var3 = struct_array[0]->var3 + 20.0f;

	// изменение значения параметра var1 структурированного параметра my_struct
	my_struct->var1 = 5;

	// вывод значения параметра string_param1 вложенного структурированного параметра (my_nested_struct) внутри my_struct2 типа ChildStruct, унаследованного от ParentStruct
	Log::message("String parameter value: %s",my_struct2->my_nested_struct->string_param1.get());

	// ...
}

```


### Методы компонента


Каждый компонент может иметь произвольный набор методов, реализующих его логику. Эти методы выполняются на соответствующих этапах [execution sequence](../../../../../../code/fundamentals/execution_sequence/index.md). Вы можете задать несколько методов для каждого этапа — они будут выполняться в соответствии со значением **[order](#methods_order)** (необязательно) или в том порядке, в котором они указаны в объявлении.


```cpp
COMPONENT_INIT(function_name, order, invoke_disabled);
COMPONENT_UPDATE_ASYNC_THREAD(function_name, order, invoke_disabled);
COMPONENT_UPDATE_SYNC_THREAD(function_name, order, invoke_disabled);
COMPONENT_UPDATE(function_name, order, invoke_disabled);
COMPONENT_POST_UPDATE(function_name, order, invoke_disabled);
COMPONENT_UPDATE_PHYSICS(function_name, order), invoke_disabled;
COMPONENT_SWAP(function_name, order, invoke_disabled);
COMPONENT_SHUTDOWN(function_name, order, invoke_disabled);

```


Компоненты также могут переопределять несколько обратных вызовов жизненного цикла. Они вызываются системой компонентов при создании компонента и при изменении его состояния включённости:


```cpp
void on_ready() override {}		// вызывается один раз при создании компонента
void on_enable() override {} 	// вызывается один раз при включении свойства/узла
void on_disable() override {}	// ... при отключении

```


#### Порядок выполнения методов


Если к узлу присоединено несколько компонентов, значение **order** определяет порядок, в котором будут вызываться их методы на соответствующем этапе последовательности выполнения. Например, предположим, что у нас есть два компонента (*Component1* и *Component2*), присоединённые к узлу, и у обоих объявлены функции *init()* следующим образом:


```cpp
	// Component1
	COMPONENT_INIT(init, 2);

	// ...

	// Component2
	COMPONENT_INIT(init, 3);

	// ...

```


Эти функции будут вызваны в следующем порядке:


1. Component1::init()
2. Component2::init()


Значение *invoke_disabled* (необязательно) указывает, должен ли метод выполняться, даже если компонент или узел отключён. Например:


```cpp
//...
COMPONENT_INIT(init, 2, true);  // инициализация данных даже при отключённом состоянии

void init()
{
    // логика инициализации
}

COMPONENT_UPDATE(update, 0);    // выполняется только при включённом состоянии

void update()
{
    // логика обновления кадра
}

```


#### Порядок выполнения классов


Вы можете использовать наследование на основе макросов для управления порядком выполнения базовых и производных классов.


Чтобы **переопределить** метод базового класса:


```cpp
class A
{
	COMPONENT_UPDATE(update);
	void update();
};

class B: public class A
{
	COMPONENT_UPDATE(update);
	void update();
};

// В этом случае будет выполнен только B::update(). Не имеет значения, что A::update() не является виртуальным.

```


Чтобы выполнить метод базового класса перед производным:


```cpp
class A
{
	COMPONENT_UPDATE(update, -1);
	void update();
};

class B: public class A
{
	COMPONENT_UPDATE(update);
	void update();
};

// В этом случае сначала выполняется A::update(), а затем B::update().

```


Чтобы выполнить метод производного класса перед базовым:


```cpp
class A
{
	COMPONENT_UPDATE(update);
	void update();
};

class B: public class A
{
	COMPONENT_UPDATE(update, -1);
	void update();
};

// В этом случае сначала выполняется B::update(), а затем A::update().

```


### Пример использования


Ниже вы найдёте пример объявления логического компонента (**MyComponent.h**) вместе с реализацией логики (**MyComponent.cpp**).


Файл реализации компонента (`*.cpp`) должен содержать следующий макрос для обеспечения его автоматической регистрации системой C++ Component System при её [initialized](../../../../../../api/library/common/logic/component_system/cpp/class.componentsystem_cpp.md#initialize_void):

```cpp
REGISTER_COMPONENT ( your_component_name );
```


> **Warning:** Не помещайте этот макрос в заголовочные файлы (`*.h`), иначе ваш проект не соберётся!


<details>
<summary>MyComponent.h | Close</summary>

**MyComponent.h**


```cpp
class MyComponent: public Unigine::ComponentBase
{
public:

	// конструктор и деструктор нашего компонента
	COMPONENT(MyComponent, Unigine::ComponentBase);

	// имя свойства, связанного с компонентом
	PROP_NAME("my_component");

	// методы, выполняемые на определённых этапах последовательности выполнения (см. раздел "protected")
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update1, 3);
	COMPONENT_UPDATE(update2, 5);

	// параметры
	PROP_PARAM(Float, speed, 30.0f);
	PROP_PARAM(Node, some_node);

	// объявление структуры (свойства внутри свойства) с именем "ParentStruct"
	struct ParentStruct : public Unigine::ComponentStruct
	{
		// параметры, которые будут отображаться в UnigineEditor
		PROP_PARAM(Int, var1, 1);
		PROP_PARAM(Float, var2, 2.0f);
		PROP_PARAM(Double, var3, 3.0f);

		// вспомогательные переменные, которые не будут видны в UnigineEditor
		float my_var1 = 2.0f;
		int my_var2 = 10;
	};

	// объявление структурированного параметра с именем "my_struct" типа ParentStruct, объявленного выше
	PROP_STRUCT(ParentStruct, my_struct);

	// объявление дочерней структуры с именем "ChildStruct", унаследованной от ParentStruct
	struct ChildStruct : public ParentStruct
	{
		// параметры, которые будут отображаться в UnigineEditor
		PROP_PARAM(Int, child_param1, 1);
		PROP_PARAM(Double, child_param2, 2.0f);

		// объявление вложенной структуры
		struct NestedStruct : public Unigine::ComponentStruct
		{
			// параметры, которые будут отображаться в UnigineEditor
			PROP_PARAM(String, string_param1, "This is my string!");
		};

		// объявление структурированного параметра с именем "my_nested_struct" типа NestedStruct, объявленного выше
		PROP_STRUCT(NestedStruct, my_nested_struct);
	};

	// объявление структурированного параметра с именем "my_struct2" типа ChildStruct, объявленного выше
	PROP_STRUCT(ChildStruct, my_struct2, "Child Struct", "Example of an inherited structure with a nested one");

	// объявление простого массива элементов типа integer с именем int_array
	PROP_ARRAY(Int, int_array, "Integer Array", "This is an array of integer elements");

	// объявление массива элементов ParentStruct с именем struct_array (ParentStruct должна быть объявлена ранее)
	PROP_ARRAY_STRUCT(ParentStruct, struct_array);

protected:
	// главный цикл мира
	void init();
	void update1();
	void update2();

};

```

</details>


<details>
<summary>MyComponent.cpp | Close</summary>

**MyComponent.cpp**


```cpp
#include "MyComponent.h"

REGISTER_COMPONENT( MyComponent );		// макрос для регистрации компонента системой C++ Component System

using namespace Unigine;
using namespace Math;

// метод, вызываемый при инициализации компонента
void MyComponent::init()
{
	// изменение значения параметра speed
	speed = 120.0f;

	// изменение размера массива и установка значений нескольких его элементов
	int_array.resize(5);
	int_array[0] = 1;
	int_array[4] = 10;

	// установка значения параметра var3 первого элемента ParentStruct массива с именем struct_array
	struct_array[0]->var3 = struct_array[0]->var3 + 20.0f;

	// изменение значения параметра var1 структурированного параметра my_struct
	my_struct->var1 = 5;

	// вывод значения параметра string_param1 вложенного структурированного параметра (my_nested_struct) внутри my_struct2 типа ChildStruct, унаследованного от ParentStruct
	Log::message("\nString parameter value: %s",my_struct2->my_nested_struct->string_param1.get());
}

// первый метод, вызываемый при обновлении мира
void MyComponent::update1()
{
	Log::message("\nMyComponent::update1() method!");
}

// второй метод, вызываемый при обновлении мира
void MyComponent::update2()
{
	Log::message("\nMyComponent::update2() method!");
}

```

</details>


### См. также


- [C++ Component System usage example](../../../../../../code/usage/using_component_system/index.md) с более подробной информацией об использовании C++ Component System.
- Статья *[Property File Format](../../../../../../code/formats/property_format.md)*, чтобы узнать больше о формате файла свойств (`*.prop`).
- Пример C++


## ComponentBase Class

### Методы класса

---

## virtual void on_ready ( )

Этот метод вызывается **немедленно** после того, как компонент был создан и присоединён к узлу. Вы можете переопределить этот метод и использовать его вместо конструктора для инициализации, так как компонент находится в "неопределённом" состоянии на момент конструирования.
> **Notice:** Метод *init()* вызывается только при [initializing a world](../../../../../../code/fundamentals/execution_sequence/main_loop.md#world_init). Реализация инициализации компонента в *on_ready()* позволяет выполнить всю необходимую подготовку заранее, если к вашему компоненту будут обращаться другие компоненты при инициализации мира.

## virtual void on_enable ( )

Этот метод вызывается системой компонентов, когда компонент становится включённым и активным (и узел, и свойство включены). Вы можете переопределить этот метод, чтобы реализовать определённые действия, выполняемые каждый раз, когда компонент становится включённым и активным.
## virtual void on_disable ( )

Этот метод вызывается системой компонентов, когда компонент становится отключённым (и узел, и свойство отключены). Вы можете переопределить этот метод, чтобы реализовать определённые действия, выполняемые каждый раз, когда компонент становится отключённым и неактивным.
## const char * getClassName ( )

Возвращает имя класса, связанного с компонентом. Имя генерируется автоматически в макросе *COMPONENT*.
### Возвращаемое значение

Имя класса компонента.
## const char * getComponentDescription ( )

Возвращает описание компонента. Описание можно указать в макросе *COMPONENT_DESCRIPTION*.
### Возвращаемое значение

Описание компонента.
## const char * getPropertyName ( )

Возвращает имя свойства, связанного с компонентом.
> **Notice:** Имя генерируется автоматически, если вы используете макрос *COMPONENT_DEFINE*: в этом случае имя свойства будет совпадать с именем класса. Чтобы указать пользовательское имя, используйте вместо этого макросы *COMPONENT* и *PROP_NAME*.


### Возвращаемое значение

Имя свойства.
## const char * getParentPropertyName ( )

Возвращает имя родительского свойства, от которого унаследовано текущее свойство, связанное с компонентом.
> **Notice:** Имя генерируется автоматически, если вы используете макрос *COMPONENT_DEFINE*: в этом случае имя свойства будет совпадать с именем класса. Чтобы указать пользовательское имя, используйте вместо этого макросы *COMPONENT* и *PROP_NAME*.

### Возвращаемое значение

Имя родительского свойства.
## void setEnabled ( int enable )

Включает или отключает компонент.
### Аргументы

- *int* **enable** - Используйте **1**, чтобы включить компонент, **0** — чтобы отключить его.

## int isEnabled ( )

Возвращает значение, указывающее, включён ли компонент.
### Возвращаемое значение

**1**, если компонент включён; иначе **0**.
## int isInitialized ( )

Возвращает значение, указывающее, инициализирован ли компонент (его метод *init()* уже был вызван).
### Возвращаемое значение

**1**, если компонент инициализирован; иначе **0**.
## int isAutoSaveProperty ( )

Возвращает значение, указывающее, должен ли файл свойства, связанного с компонентом, автоматически генерироваться каждый раз при [initialized](../../../../../../api/library/common/logic/component_system/cpp/class.componentsystem_cpp.md#initialize_void) C++ Component System или вызове метода [createPropertyFiles()](../../../../../../api/library/common/logic/component_system/cpp/class.componentsystem_cpp.md#createPropertyFiles_void).
> **Notice:** По умолчанию файлы свойств всех компонентов перегенерируются автоматически; такое поведение может быть нежелательным, если вы вручную изменяете свойства после создания. В этом случае можно добавить следующий макрос в заголовочный файл, содержащий объявление вашего компонента:
> ```cpp
> PROP_AUTOSAVE(0);
> ```


### Возвращаемое значение

**1**, если файл свойства, связанного с компонентом, должен автоматически генерироваться каждый раз при [initialized](../../../../../../api/library/common/logic/component_system/cpp/class.componentsystem_cpp.md#initialize_void) C++ Component System или вызове метода [createPropertyFiles()](../../../../../../api/library/common/logic/component_system/cpp/class.componentsystem_cpp.md#createPropertyFiles_void); иначе **0**.
## const Node Ptr & getNode ( )

Возвращает узел, к которому присоединён компонент.
### Возвращаемое значение

Узел, к которому присоединён компонент.
## const Property Ptr & getProperty ( )

Возвращает свойство, связанное с компонентом.
### Возвращаемое значение

Свойство, связанное с компонентом.
## int getPropertyNum ( )

Возвращает номер свойства, связанного с компонентом.
### Возвращаемое значение

Номер свойства в списке свойств, назначенных узлу.
## template < C class >

## C * addComponent ( const Node Ptr & node )

Добавляет компонент к указанному узлу. Этот метод эквивалентен методу [ComponentSystem::addComponent()](../../../../../../api/library/common/logic/component_system/cpp/class.componentsystem_cpp.md#addComponent_const_NodePtr_ref_C_ptr).
### Аргументы

- *const [Node](../../../../../../api/library/nodes/class.node_cpp.md)Ptr &* **node** - Узел, к которому добавляется компонент.

### Возвращаемое значение

Указатель на новый добавленный компонент, если он был успешно добавлен к указанному узлу; иначе nullptr.
## template < C class >

## int removeComponent ( const Node Ptr & node )

Удаляет компонент с указанного узла. Этот метод эквивалентен методу [ComponentSystem::removeComponent()](../../../../../../api/library/common/logic/component_system/cpp/class.componentsystem_cpp.md#removeComponent_const_NodePtr_ref_int).
### Аргументы

- *const [Node](../../../../../../api/library/nodes/class.node_cpp.md)Ptr &* **node** - Узел, с которого удаляется компонент.

### Возвращаемое значение

**1**, если компонент был успешно удалён с указанного узла; иначе **0**.
## template < C class >

## C * getComponent ( const Node Ptr & node , bool enabled_only = false )

Возвращает первый компонент указанного типа, связанный с указанным узлом. Этот метод эквивалентен методу [ComponentSystem::getComponent()](../../../../../../api/library/common/logic/component_system/cpp/class.componentsystem_cpp.md#getComponent_const_NodePtr_ref_C_ptr).
### Аргументы

- *const [Node](../../../../../../api/library/nodes/class.node_cpp.md)Ptr &* **node** - Узел, для которого требуется найти компонент этого типа.
- *bool* **enabled_only** - Флаг включённости: true — получить только включённый компонент, false — получить компонент в любом случае.

### Возвращаемое значение

Указатель на компонент, если он существует; иначе nullptr.
## template < C class >

## void getComponents ( const Node Ptr & node , Vector <C *> & components )

Возвращает все компоненты этого типа, назначенные указанному узлу, и помещает их в указанный буферный вектор. Этот метод эквивалентен методу [ComponentSystem::getComponents()](../../../../../../api/library/common/logic/component_system/cpp/class.componentsystem_cpp.md#getComponents_const_NodePtr_ref_Vectortmplargs_ref_int_void).
### Аргументы

- *const [Node](../../../../../../api/library/nodes/class.node_cpp.md)Ptr &* **node** - Узел, компоненты которого требуется получить.
- *[Vector](../../../../../../api/library/containers/vector/class.vector_cpp.md)<C *> &* **components** - Буферный вектор, в который будут помещены все найденные компоненты этого типа.

## template < C class >

## C * getComponentInChildren ( const Node Ptr & node , bool enabled_only = false )

Возвращает первый компонент этого типа, найденный среди всех дочерних узлов указанного узла (включая сам узел). Этот метод выполняет поиск компонента в следующем порядке:
- сам узел
- ссылка на узел
- дочерние узлы
- дочерние узлы дочерних узлов

Этот метод эквивалентен методу [ComponentSystem::getComponentInChildren()](../../../../../../api/library/common/logic/component_system/cpp/class.componentsystem_cpp.md#getComponentInChildren_const_NodePtr_ref_C_ptr).
### Аргументы

- *const [Node](../../../../../../api/library/nodes/class.node_cpp.md)Ptr &* **node** - Узел, иерархию которого требуется проверить на наличие компонентов этого типа.
- *bool* **enabled_only** - Флаг включённости: true — получить только включённый компонент, false — получить компонент в любом случае.

### Возвращаемое значение

Указатель на компонент, если он существует; иначе nullptr.
## template < C class >

## void getComponentsInChildren ( const Node Ptr & node , Vector <C *> & components )

Выполняет поиск всех компонентов этого типа вниз по иерархии указанного узла и помещает их в заданный буферный вектор. Этот метод эквивалентен методу [ComponentSystem::getComponentsInChildren()](../../../../../../api/library/common/logic/component_system/cpp/class.componentsystem_cpp.md#getComponentsInChildren_const_NodePtr_ref_Vectortmplargs_ref_int_void).
### Аргументы

- *const [Node](../../../../../../api/library/nodes/class.node_cpp.md)Ptr &* **node** - Узел, иерархию которого требуется проверить на наличие компонентов этого типа.
- *[Vector](../../../../../../api/library/containers/vector/class.vector_cpp.md)<C *> &* **components** - Буферный вектор, в который будут помещены все найденные компоненты этого типа.

## template < C class >

## C * getComponentInParent ( const Node Ptr & node , bool enabled_only = false )

Возвращает первый компонент этого типа, найденный среди всех предков и [posessors](../../../../../../api/library/nodes/class.node_cpp.md#getPossessor_Node) указанного узла. Этот метод эквивалентен методу [ComponentSystem::getComponentInParent()](../../../../../../api/library/common/logic/component_system/cpp/class.componentsystem_cpp.md#getComponentInParent_const_NodePtr_ref_C_ptr).
### Аргументы

- *const [Node](../../../../../../api/library/nodes/class.node_cpp.md)Ptr &* **node** - Узел, иерархию которого требуется проверить на наличие компонентов этого типа.
- *bool* **enabled_only** - Флаг включённости: true — получить только включённый компонент, false — получить компонент в любом случае.

### Возвращаемое значение

Указатель на компонент, если он существует; иначе nullptr.
## template < C class >

## void getComponentsInParent ( const Node Ptr & node , Vector <C *> & components )

Выполняет поиск всех компонентов этого типа вверх по иерархии указанного узла и помещает их в заданный буферный вектор. Этот метод эквивалентен методу [ComponentSystem::getComponentsInParent()](../../../../../../api/library/common/logic/component_system/cpp/class.componentsystem_cpp.md#getComponentsInParent_const_NodePtr_ref_Vectortmplargs_ref_int_void).
### Аргументы

- *const [Node](../../../../../../api/library/nodes/class.node_cpp.md)Ptr &* **node** - Узел, иерархию которого требуется проверить на наличие компонентов этого типа.
- *[Vector](../../../../../../api/library/containers/vector/class.vector_cpp.md)<C *> &* **components** - Буферный вектор, в который будут помещены все найденные компоненты этого типа.

## void setDestroyCallback ( Unigine:: CallbackBase * func )

Задаёт функцию обратного вызова, вызываемую перед уничтожением компонента. Эта функция может использоваться для реализации определённых действий, выполняемых при уничтожении компонента.
### Аргументы

- *Unigine::[CallbackBase](../../../../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **func** - Функция обратного вызова.

## void clearDestroyCallback ( )

Удаляет функцию обратного вызова при уничтожении, ранее заданную методом [setDestroyCallback()](#setDestroyCallback_CallbackBase_ptr_void). Эта функция обратного вызова может использоваться для реализации определённых действий, выполняемых при уничтожении компонента.
## void save_property ( const char * name )

Сохраняет все параметры свойства, связанного с компонентом, в указанный `prop`-файл.
### Аргументы

- *const char ** **name** - Имя целевого `.prop`-файла.

## void init ( )

Движок вызывает эту функцию при инициализации мира. Разместите здесь код для инициализации ресурсов во время запуска мира.
## void update ( )

Движок вызывает эту функцию перед обновлением каждого кадра рендеринга. Здесь можно указать все функции, связанные с логикой, которые должны вызываться каждый кадр во время выполнения приложения.
## void postUpdate ( )

Движок вызывает эту функцию после обновления каждого кадра рендеринга. Здесь можно скорректировать поведение после обновления состояния узла.
## void updatePhysics ( )

Движок вызывает эту функцию перед обновлением каждого кадра физики. Здесь можно управлять физикой, выполнять непрерывные операции, связанные с физикой (толкать машину вперёд в зависимости от текущих оборотов двигателя, постоянно моделировать дуновение ветра, выполнять немедленную обработку столкновений и т. д.). Движок вызывает *updatePhysics()* с фиксированной частотой (по умолчанию 60 раз в секунду) независимо от количества кадров в секунду. Аналогична функции updatePhysics() скрипта мира.
## void shutdown ( )

Движок вызывает эту функцию при завершении работы мира. Здесь можно очистить ресурсы, созданные во время выполнения скрипта мира, чтобы избежать утечек памяти.
## int is_equals ( const Ptr < Xml > & xml1 , const Ptr < Xml > & xml2 )

Возвращает значение, указывающее, действительно ли равны два узла xml (имеют одинаковый набор параметров с одинаковыми значениями и одинаковую иерархию).
### Аргументы

- *const [Ptr](../../../../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../../../../api/library/common/class.xml_cpp.md)> &* **xml1** - Первый узел xml.
- *const [Ptr](../../../../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../../../../api/library/common/class.xml_cpp.md)> &* **xml2** - Второй узел xml.

### Возвращаемое значение

1, если два указанных узла xml равны; иначе 0.
