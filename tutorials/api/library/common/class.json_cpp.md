# Unigine::Json Class (CPP)

**Header:** #include <UnigineJson.h>


Этот класс используется для разбора и создания строк в формате JSON.


Каждый Json-узел имеет тип, имя и значение. Доступны следующие типы:


- null
- bool
- number
- string
- array
- object


Json-узел имеет иерархическую структуру: он может иметь дочерние Json-узлы и родительский узел.


#### Создание Json-узла


Приведённый ниже код создаёт Json-узел, добавляет дочерние узлы с разными типами значений и сохраняет результат в файл `*.json`:

> **Notice:** При добавлении дочерних узлов типа *array*/*object* необходимо вызвать функции *[setArray()](#setArray_void)*/*[setObject()](#setObject_void)* после *addChild()*.


```cpp
#include <UnigineJson.h>

using namespace Unigine;
using namespace Math;

int AppWorldLogic::init()
{

	JsonPtr json = Json::create();

	json->addChild("child_0", 0);    // int
	json->addChild("child_1", 1.1);   // float
	json->addChild("child_2", "two");  // string

	// array
	JsonPtr array_0 = json->addChild("array_0");
	array_0->setArray();
	array_0->addChild(NULL, 1);
	array_0->addChild(NULL, 1);
	array_0->addChild(NULL, 0);

	// object
	JsonPtr object_0 = json->addChild("object_0");
	object_0->setObject();
	object_0->addChild("one", 5);
	object_0->addChild("two", 6);
	object_0->addChild("three", 7);

	// save the Json node to the file
	json->save("json/my.json");

	return 1;
}


```


`my.json`:


```text
{
	"child_0": 0,
	"child_1": 1.1000000000000001,
	"child_2": "two",
	"array_0": [
		1,
		1,
		0
	],
	"object_0": {
		"one": 5,
		"two": 6,
		"three": 7
	}
}

```


Дочерние узлы имеют имена *child_0*, *child_1*, *child_2* и значения: целое 0, double 1.1 и строку two. Также есть дочерние узлы *array_0* и *object_0* типов array и object соответственно. Имя дочернего узла всегда имеет строковый тип.


#### Редактирование Json-узла


Json-узел можно редактировать средствами класса Json: можно добавлять или удалять дочерние узлы, изменять его значения. Например, чтобы добавить новый узел типа array, можно сделать следующее:


`my_array.json`


```text
{
"array_0": [ 0, 0, 1 ]
}

```


```cpp
#include <UnigineJson.h>

using namespace Unigine;
using namespace Math;

int AppWorldLogic::init()
{

	JsonPtr json = Json::create();

	// load the Json node from my.json
	json->load("json/my_array.json");

	// add the array node as a child
	JsonPtr array_1 = json->addChild("array_1");
	array_1->setArray();
	// add object nodes to the array
	for (int i = 0; i < 5; i++)
	{
		JsonPtr object = array_1->addChild(NULL);
		object->addChild("name", String::format("value_%d", i));
		object->addChild("value", i + 1);
	}

	// save the updated Json node to a new file
	json->save("json/my_array.json");

	return 1;
}


```


Результат:


```text
{
"array_0": [ 0, 0, 1 ],
"array_1": [
	{
		"name": "value_0",
		"value": 1
	},
	{
		"name": "value_1",
		"value": 2
	},
	{
		"name": "value_2",
		"value": 3
	},
	{
		"name": "value_3",
		"value": 4
	},
	{
		"name": "value_4",
		"value": 5
	}
]
}

```


Также можно изменить тип узла. Однако в некоторых случаях это может привести к потере данных. Например, если изменить тип с *object* на *array*, имена дочерних узлов будут потеряны.


```cpp
#include <UnigineJson.h>

using namespace Unigine;
using namespace Math;

int AppWorldLogic::init()
{

	JsonPtr json = Json::create();

	// create an object node
	JsonPtr object_0 = json->addChild("array_or_object?");
	object_0->setObject();
	object_0->addChild("name1", 1);
	object_0->addChild("name2", 2);
	object_0->addChild("name3", 3);
	// save to a file
	json->save("json/object.json");
	// change the type to "array"
	object_0->setArray();
	// save to another file
	json->save("json/array.json");

	return 1;
}


```


В результате файлы будут содержать следующее:


`object.json`


```text
{
	"array_or_object?": {
		"name1": 1,
		"name2": 2,
		"name3": 3
	}
}

```


`array.json`


```text
{
	"array_or_object?": [
		1,
		2,
		3
	]
}

```


##### Доступ к данным


Класс Json предоставляет несколько методов для доступа к данным Json-узла в зависимости от его типа. Например, методы *[read()](#read_cstr_bool_void)* можно использовать для доступа к данным Json-узла типа *object* следующим образом:


`cubes.json`


```text
{
	"cubes": {
		"first": {
			"name": "cube_red",
			"coefficient": 1.0
			"color": [255, 0, 0, 255]
		},
		"second": {
			"name": "cube_green",
			"coefficient": 2.0
			"color": [0, 255, 0, 255]
		},
		"third": {
			"name": "cube_blue",
			"coefficient": 3.0
			"color": [0, 0, 255, 255]
		},
		"fourth": {
			"name": "cube_magenta",
			"coefficient": 4.0
			"color": [255, 0, 255, 255]
		},
		"fifth": {
			"name": "cube_white",
			"coefficient": 5.0
			"color": [255, 255, 255, 255]
		}
	}
}

```


```cpp
#include <UnigineJson.h>

using namespace Unigine;
using namespace Math;

int AppWorldLogic::init()
{

	float coefficient;
	String name;
	vec4 color;

	JsonPtr json = Json::create();

	// load the Json node from the file
	json->load("json/cubes.json");
	// get its child node
	JsonPtr cubes = json->getChild("cubes");

	for (int i = 0; i < cubes->getNumChildren(); i++)
	{
		// get a child node of the "cubes" node
		JsonPtr child = cubes->getChild(i);

		// read the node name
		name = child->read("name");
		// read the coefficient to a variable
		child->read("coefficient", coefficient);
		// read the color to a variable
		child->read("color", color);

		// create a dynamic mesh using read values
		ObjectMeshDynamicPtr box = Primitives::createBox(Math::vec3_one * coefficient);
		box->setName(name);
		box->setWorldPosition(Math::Vec3(0.0f, 0.0f, 1.0f * coefficient));
		box->setMaterialParameterFloat4("albedo_color", color, 0);
		Log::message("The %s box: %s\n", child->getName(), box->getName());

	}

	return 1;
}


```


В результате будет создано пять цветных кубов с использованием данных из предоставленного файла `cubes.json`.


Если у вас есть *array* из двух, трёх или четырёх элементов, можно использовать соответственно методы *[getVec2()](#getVec2_vec2)*, *[getVec3()](#getVec3_vec3)* и *[getVec4()](#getVec4_vec4)*. Например:


`my_array.json`


```text
{
	"array_0": [ 0, 0, 1 ]
}

```


```cpp
#include <UnigineJson.h>

using namespace Unigine;
using namespace Math;

int AppWorldLogic::init()
{

	// get the "array_0" child
	JsonPtr a = json->getChild("array_0");
	// get its value
	vec3 v = a->getVec3();
	// print the result to the console
	Log::message("%f %f %f\n", v.x, v.y, v.z);

	return 1;
}


```


Используя методы *write()* класса, можно также добавлять новые дочерние узлы и редактировать значения существующих. Например:


```cpp
#include <UnigineJson.h>

using namespace Unigine;
using namespace Math;

int AppWorldLogic::init()
{

	json->load("json/cubes.json");

	// add a new child node of the object type
	JsonPtr cube = json->getChild("cubes")->addChild("sixth");
	cube->setObject();
	// write new child nodes with the specified values
	cube->write("name", "cube_black");
	cube->write("coefficient", 6.0);
	cube->write("color", vec4(0, 0, 0, 0));

	// write new values for the existing Json node
	cube = json->getChild("cubes")->getChild("first");
	cube->write("name", "cube_black");
	cube->write("coefficient", 3.0);
	cube->write("color", vec4(0, 0, 0, 0));

	// save changes to the .json file
	json->save("json/cubes.json");

	return 1;
}


```


## Json Class

### Методы класса

---

## static JsonPtr create ( )

Конструктор по умолчанию, создающий пустой экземпляр.
## static JsonPtr create ( const char * name )

Конструктор, создающий JSON-узел с заданным именем.
### Аргументы

- *const char ** **name** - Имя Json-узла.

## void setArray ( )

Задаёт тип array текущему Json-узлу.
> **Notice:** Этот метод можно вызвать для вновь добавленного узла или для существующего узла, чтобы изменить его тип. Однако в некоторых случаях это может привести к потере данных. Например, если изменить тип с *object* на *array*, имена дочерних узлов будут потеряны.


## int isArray ( ) const

Возвращает значение, указывающее, имеет ли Json-узел тип array.
### Возвращаемое значение

1, если Json имеет тип array; иначе 0.
## void setBool ( int arg1 )

Задаёт логическое значение и тип текущему Json-узлу.
### Аргументы

- *int* **arg1** - Целочисленное значение.

## int getBool ( ) const

Считывает логическое значение текущего Json-узла.
### Возвращаемое значение

1, если Json-узел имеет тип bool; иначе 0.
## int isBool ( ) const

Возвращает значение, указывающее, имеет ли Json-узел тип bool.
### Возвращаемое значение

1, если Json имеет тип bool; иначе 0.
## Ptr < Json > getChild ( int num ) const

Возвращает дочерний узел текущего Json-узла по номеру дочернего узла.
### Аргументы

- *int* **num** - Номер дочернего узла Json-узла.

### Возвращаемое значение

Дочерний Json-узел.
## Ptr < Json > getChild ( const char * name ) const

Возвращает дочерний узел текущего Json-узла по имени дочернего узла.
### Аргументы

- *const char ** **name** - Имя Json-узла.

### Возвращаемое значение

Дочерний Json-узел.
## int isChild ( const char * name ) const

Проверяет, существует ли дочерний узел с заданным именем.
### Аргументы

- *const char ** **name** - Имя дочернего узла.

### Возвращаемое значение

1, если дочерний узел с указанным именем существует; иначе 0.
## Ptr < Json > addChild ( const char * name , double value )

Добавляет новую пару имя-значение как дочерний узел текущего Json-узла.
### Аргументы

- *const char ** **name** - Имя узла.
- *double* **value** - Значение текущего Json-узла как целое число.

### Возвращаемое значение

Дочерний Json-узел.
## Ptr < Json > addChild ( const char * name , int value )

Добавляет новую пару имя-значение как дочерний узел текущего Json-узла.
### Аргументы

- *const char ** **name** - Имя узла.
- *int* **value** - Значение текущего Json-узла как целое число.

### Возвращаемое значение

Дочерний Json-узел.
## Ptr < Json > addChild ( const char * name , const char * value )

Добавляет новую пару имя-значение как дочерний узел текущего Json-узла.
### Аргументы

- *const char ** **name** - Имя узла.
- *const char ** **value** - Значение текущего Json-узла как целое число.

### Возвращаемое значение

Дочерний Json-узел.
## Ptr < Json > addChild ( const char * name )

Добавляет новую пару имя-значение как дочерний узел текущего Json-узла.
### Аргументы

- *const char ** **name** - Имя узла.

### Возвращаемое значение

Дочерний Json-узел.
## Ptr < Json > addChild ( const Ptr < Json > & json )

Добавляет новую пару имя-значение как дочерний узел текущего Json-узла.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Json](../../../api/library/common/class.json_cpp.md)> &* **json** - Имя узла.

### Возвращаемое значение

Дочерний Json-узел.
## Ptr < Json > addChild ( )

Добавляет дочерний узел к текущему Json-узлу.
### Возвращаемое значение

Дочерний Json-узел.
## String getSubTree ( const char * name = 0 )

Возвращает поддерево Json-узла в виде неформатированной строки.
### Аргументы

- *const char ** **name** - Имя дочернего узла. Если имя указано, функция возвращает форматированное поддерево для этого дочернего Json-узла.

### Возвращаемое значение

Неформатированное поддерево.
## String getFormattedSubTree ( const char * name = 0 )

Возвращает поддерево Json-узла в виде форматированной строки.
### Аргументы

- *const char ** **name** - Имя дочернего узла. Если имя указано, функция возвращает форматированное поддерево для этого дочернего Json-узла.

### Возвращаемое значение

Форматированное поддерево.
## void setName ( const char * name )

Задаёт заданное имя Json-узлу.
### Аргументы

- *const char ** **name** - Имя Json-узла.

## const char * getName ( ) const

Возвращает имя текущего Json-узла.
### Возвращаемое значение

Имя Json-узла.
## void setNull ( )

Задаёт тип null текущему Json-узлу.
## int isNull ( ) const

Возвращает значение, указывающее, имеет ли Json-узел тип null.
### Возвращаемое значение

1, если Json имеет тип null; иначе 0.
## void setNumber ( double arg1 )

Задаёт числовое значение и тип текущему Json-узлу.
### Аргументы

- *double* **arg1** - Значение double.

## double getNumber ( ) const

Возвращает числовое значение текущего Json-узла.
### Возвращаемое значение

Числовое значение текущего Json-узла.
## int isNumber ( ) const

Возвращает значение, указывающее, имеет ли Json-узел числовой тип.
### Возвращаемое значение

1, если Json имеет числовой тип; иначе 0.
## int getNumChildren ( ) const

Возвращает количество дочерних узлов текущего Json-узла.
### Возвращаемое значение

Количество дочерних узлов.
## void reserveChildren ( int num )

Задаёт зарезервированную ёмкость Json-узла для хранения указанного количества дочерних узлов.
### Аргументы

- *int* **num** - Количество дочерних узлов.

## void setObject ( )

Задаёт тип object текущему Json-узлу.
## int isObject ( ) const

Возвращает значение, указывающее, имеет ли Json-узел тип object.
### Возвращаемое значение

1, если Json имеет тип object; иначе 0.
## Ptr < Json > getParent ( )

Возвращает родительский узел текущего Json-узла.
### Возвращаемое значение

Родительский Json-узел.
## void setString ( const char * arg1 )

Задаёт строковое значение и тип текущему Json-узлу. Функция автоматически преобразует числовые значения в строковый тип.
### Аргументы

- *const char ** **arg1** - Строковое значение.

## String getString ( )

Возвращает значение текущего Json-узла в виде строки.
### Возвращаемое значение

Значение текущего Json-узла.
## int isString ( ) const

Возвращает значение, указывающее, имеет ли Json-узел строковый тип.
### Возвращаемое значение

1, если Json имеет строковый тип; иначе 0.
## void clear ( )

Очищает все данные текущего Json-узла, включая тип, значение, имя и все дочерние узлы. Если у текущего Json-узла есть родитель, он также удаляется из родительского Json-узла.
## Ptr < Json > removeChild ( const Ptr < Json > & json )

Удаляет дочерний Json-узел.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Json](../../../api/library/common/class.json_cpp.md)> &* **json** - Json-узел для удаления.

### Возвращаемое значение

Удалённый дочерний Json-узел.
## Ptr < Json > removeChild ( const char * name )

Удаляет дочерний Json-узел.
### Аргументы

- *const char ** **name** - Имя удаляемого Json-узла.

### Возвращаемое значение

Удалённый дочерний Json-узел.
## void clearChildren ( )

Очищает все дочерние узлы текущего Json-узла.
## void copy ( const Ptr < Json > & source )

Копирует тип, имя и значение из исходного Json-узла в текущий Json-узел и добавляет дочерние узлы исходного Json в качестве дочерних узлов текущего Json-узла.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Json](../../../api/library/common/class.json_cpp.md)> &* **source** - Исходный Json-узел.

## Ptr < Json > find ( const char * name )

Находит Json-узел по его имени в дереве текущего Json-узла.
### Аргументы

- *const char ** **name** - Имя Json-узла.

### Возвращаемое значение

Найденный Json-узел.
## int load ( const char * path )

Загружает данные в текущий Json-узел из файла по заданному пути.
### Аргументы

- *const char ** **path** - Путь к файлу.

### Возвращаемое значение

1, если Json-узел успешно загружен; иначе 0.
## int parse ( const char * source )

Разбирает заданную строку в Json-узел.
**Пример использования**


```cpp
#include <UnigineJson.h>

/* ... */

JsonPtr json = Json::create();
json->addChild("child_0", 1);

JsonPtr json_2 = Json::create();
json_2->parse(json->getSubTree().get());

```


Теперь узел json_2 содержит:


```text
{
	"child_0": 1
}

```


### Аргументы

- *const char ** **source** - Строка для разбора.

### Возвращаемое значение

1, если строка успешно разобрана; иначе 0.
## int save ( const char * path ) const

Сохраняет Json-узел в файл по заданному пути. Создаёт заданный путь к файлу, если он ещё не существует (включая поддиректории).
### Аргументы

- *const char ** **path** - Путь к файлу.

### Возвращаемое значение

1, если файл успешно сохранён; иначе 0.
## void read ( const char * name , bool & value ) const

Считывает логическое значение Json-узла с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *bool &* **value** - Целевая логическая переменная, в которую сохраняется значение Json-узла с указанным именем.

## void read ( const char * name , int & value ) const

Считывает целочисленное значение Json-узла с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *int &* **value** - Целевая целочисленная переменная, в которую сохраняется значение Json-узла с указанным именем.

## void read ( const char * name , unsigned int & value ) const

Считывает беззнаковое целочисленное значение Json-узла с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *unsigned int &* **value** - Целевая беззнаковая целочисленная переменная, в которую сохраняется значение Json-узла с указанным именем.

## void read ( const char * name , char & value ) const

Считывает символьное значение Json-узла с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *char &* **value** - Целевая символьная переменная, в которую сохраняется значение Json-узла с указанным именем.

## void read ( const char * name , double & value ) const

Считывает значение double Json-узла с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *double &* **value** - Целевая переменная double, в которую сохраняется значение Json-узла с указанным именем.

## void read ( const char * name , float & value ) const

Считывает значение float Json-узла с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *float &* **value** - Целевая переменная float, в которую сохраняется значение Json-узла с указанным именем.

## void read ( const char * name , UGUID & value ) const

Считывает значение Json-узла с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *[UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **value** - UGUID переменной, в которую сохраняется значение Json-узла с указанным именем.

## void read ( const char * name , Math:: vec2 & value ) const

Считывает двухкомпонентное значение Json-узла типа массив с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **value** - Целевая векторная переменная, в которую сохраняется значение Json-узла с указанным именем.

## void read ( const char * name , Math:: vec3 & value ) const

Считывает трёхкомпонентное значение Json-узла типа массив с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **value** - Целевая векторная переменная, в которую сохраняется значение Json-узла с указанным именем.

## void read ( const char * name , Math:: vec4 & value ) const

Считывает четырёхкомпонентное значение Json-узла типа массив с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **value** - Целевая векторная переменная, в которую сохраняется значение Json-узла с указанным именем.

## void read ( const char * name , Math:: dvec2 & value ) const

Считывает двухкомпонентное значение Json-узла типа массив с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *Math::[dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **value** - Целевая векторная переменная, в которую сохраняется значение Json-узла с указанным именем.

## void read ( const char * name , Math:: dvec3 & value ) const

Считывает трёхкомпонентное значение Json-узла типа массив с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **value** - Целевая векторная переменная, в которую сохраняется значение Json-узла с указанным именем.

## void read ( const char * name , Math:: dvec4 & value ) const

Считывает четырёхкомпонентное значение Json-узла типа массив с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **value** - Целевая векторная переменная, в которую сохраняется значение Json-узла с указанным именем.

## void read ( const char * name , Math:: ivec2 & value ) const

Считывает двухкомпонентное значение Json-узла типа массив с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **value** - Целевая векторная переменная, в которую сохраняется значение Json-узла с указанным именем.

## void read ( const char * name , Math:: ivec3 & value ) const

Считывает трёхкомпонентное значение Json-узла типа массив с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *Math::[ivec3](../../../api/library/math/class.ivec3_cpp.md) &* **value** - Целевая векторная переменная, в которую сохраняется значение Json-узла с указанным именем.

## void read ( const char * name , Math:: ivec4 & value ) const

Считывает четырёхкомпонентное значение Json-узла типа массив с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *Math::[ivec4](../../../api/library/math/class.ivec4_cpp.md) &* **value** - Целевая векторная переменная, в которую сохраняется значение Json-узла с указанным именем.

## void read ( const char * name , Vector < int > & OUT_value ) const

Считывает значения Json-узла типа массив с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< int > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( const char * name , Vector < char > & OUT_value ) const

Считывает значения Json-узла типа массив с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< char > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( const char * name , Vector < double > & OUT_value ) const

Считывает значения Json-узла типа массив с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< double > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( const char * name , Vector < float > & OUT_value ) const

Считывает значения Json-узла типа массив с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< float > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( const char * name , Vector < String > & OUT_value ) const

Считывает значения Json-узла типа массив с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< [String](../../../api/library/common/class.string_cpp.md) > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( const char * name , Vector < Math:: vec2 > & OUT_value ) const

Считывает значения Json-узла типа массив с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( const char * name , Vector < Math:: vec3 > & OUT_value ) const

Считывает значения Json-узла типа массив с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( const char * name , Vector < Math:: vec4 > & OUT_value ) const

Считывает значения Json-узла типа массив с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( const char * name , Vector < Math:: dvec2 > & OUT_value ) const

Считывает значения Json-узла типа массив с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[dvec2](../../../api/library/math/class.dvec2_cpp.md) > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( const char * name , Vector < Math:: dvec3 > & OUT_value ) const

Считывает значения Json-узла типа массив с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( const char * name , Vector < Math:: dvec4 > & OUT_value ) const

Считывает значения Json-узла типа массив с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( const char * name , Vector < Math:: ivec2 > & OUT_value ) const

Считывает значения Json-узла типа массив с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( const char * name , Vector < Math:: ivec3 > & OUT_value ) const

Считывает значения Json-узла типа массив с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[ivec3](../../../api/library/math/class.ivec3_cpp.md) > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( const char * name , Vector < Math:: ivec4 > & OUT_value ) const

Считывает значения Json-узла типа массив с указанным именем в указанную целевую переменную.
### Аргументы

- *const char ** **name** - Имя Json-узла.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[ivec4](../../../api/library/math/class.ivec4_cpp.md) > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( bool & value ) const

Считывает логическое значение Json-узла в указанную целевую переменную.
### Аргументы

- *bool &* **value** - Целевая логическая переменная, в которую сохраняется значение Json-узла.

## void read ( int & value ) const

Считывает целочисленное значение Json-узла в указанную целевую переменную.
### Аргументы

- *int &* **value** - Целевая целочисленная переменная, в которую сохраняется значение Json-узла.

## void read ( char & value ) const

Считывает символьное значение Json-узла в указанную целевую переменную.
### Аргументы

- *char &* **value** - Целевая символьная переменная, в которую сохраняется значение Json-узла.

## void read ( double & value ) const

Считывает значение double Json-узла в указанную целевую переменную.
### Аргументы

- *double &* **value** - Целевая переменная double, в которую сохраняется значение Json-узла.

## void read ( float & value ) const

Считывает значение float Json-узла в указанную целевую переменную.
### Аргументы

- *float &* **value** - Целевая переменная float, в которую сохраняется значение Json-узла.

## void read ( Math:: vec2 & value ) const

Считывает двухкомпонентное значение Json-узла типа массив в указанную целевую переменную.
### Аргументы

- *Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **value** - Целевая векторная переменная, в которую сохраняются два компонента Json-узла типа массив.

## void read ( Math:: vec3 & value ) const

Считывает трёхкомпонентное значение Json-узла типа массив в указанную целевую переменную.
### Аргументы

- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **value** - Целевая векторная переменная, в которую сохраняются три компонента Json-узла типа массив.

## void read ( Math:: vec4 & value ) const

Считывает четырёхкомпонентное значение Json-узла типа массив в указанную целевую переменную.
### Аргументы

- *Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **value** - Целевая векторная переменная, в которую сохраняются четыре компонента Json-узла типа массив.

## void read ( Math:: dvec2 & value ) const

Считывает двухкомпонентное значение Json-узла типа массив в указанную целевую переменную.
### Аргументы

- *Math::[dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **value** - Целевая векторная переменная, в которую сохраняются два компонента Json-узла типа массив.

## void read ( Math:: dvec3 & value ) const

Считывает трёхкомпонентное значение Json-узла типа массив в указанную целевую переменную.
### Аргументы

- *Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **value** - Целевая векторная переменная, в которую сохраняются три компонента Json-узла типа массив.

## void read ( Math:: dvec4 & value ) const

Считывает четырёхкомпонентное значение Json-узла типа массив в указанную целевую переменную.
### Аргументы

- *Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **value** - Целевая векторная переменная, в которую сохраняются четыре компонента Json-узла типа массив.

## void read ( Math:: ivec2 & value ) const

Считывает двухкомпонентное значение Json-узла типа массив в указанную целевую переменную.
### Аргументы

- *Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **value** - Целевая векторная переменная, в которую сохраняются два компонента Json-узла типа массив.

## void read ( Math:: ivec3 & value ) const

Считывает трёхкомпонентное значение Json-узла типа массив в указанную целевую переменную.
### Аргументы

- *Math::[ivec3](../../../api/library/math/class.ivec3_cpp.md) &* **value** - Целевая векторная переменная, в которую сохраняются три компонента Json-узла типа массив.

## void read ( Math:: ivec4 & value ) const

Считывает четырёхкомпонентное значение Json-узла типа массив в указанную целевую переменную.
### Аргументы

- *Math::[ivec4](../../../api/library/math/class.ivec4_cpp.md) &* **value** - Целевая векторная переменная, в которую сохраняются четыре компонента Json-узла типа массив.

## void read ( Vector < bool > & OUT_value ) const

Считывает значения Json-узла типа массив в указанную целевую переменную.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< bool > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( Vector < int > & OUT_value ) const

Считывает значения Json-узла типа массив в указанную целевую переменную.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< int > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( Vector < char > & OUT_value ) const

Считывает значения Json-узла типа массив в указанную целевую переменную.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< char > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( Vector < double > & OUT_value ) const

Считывает значения Json-узла типа массив в указанную целевую переменную.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< double > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( Vector < float > & OUT_value ) const

Считывает значения Json-узла типа массив в указанную целевую переменную.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< float > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( Vector < String > & OUT_value ) const

Считывает значения Json-узла типа массив в указанную целевую переменную.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< [String](../../../api/library/common/class.string_cpp.md) > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( Vector < Math:: vec2 > & OUT_value ) const

Считывает значения Json-узла типа массив в указанную целевую переменную.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( Vector < Math:: vec3 > & OUT_value ) const

Считывает значения Json-узла типа массив в указанную целевую переменную.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( Vector < Math:: vec4 > & OUT_value ) const

Считывает значения Json-узла типа массив в указанную целевую переменную.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( Vector < Math:: dvec2 > & OUT_value ) const

Считывает значения Json-узла типа массив в указанную целевую переменную.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[dvec2](../../../api/library/math/class.dvec2_cpp.md) > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( Vector < Math:: dvec3 > & OUT_value ) const

Считывает значения Json-узла типа массив в указанную целевую переменную.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( Vector < Math:: dvec4 > & OUT_value ) const

Считывает значения Json-узла типа массив в указанную целевую переменную.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( Vector < Math:: ivec2 > & OUT_value ) const

Считывает значения Json-узла типа массив в указанную целевую переменную.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( Vector < Math:: ivec3 > & OUT_value ) const

Считывает значения Json-узла типа массив в указанную целевую переменную.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[ivec3](../../../api/library/math/class.ivec3_cpp.md) > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void read ( Vector < Math:: ivec4 > & OUT_value ) const

Считывает значения Json-узла типа массив в указанную целевую переменную.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[ivec4](../../../api/library/math/class.ivec4_cpp.md) > &* **OUT_value** - Вектор, в который сохраняются компоненты Json-узла типа массив. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## String read ( const char * name ) const

Возвращает значение Json-узла с указанным именем в виде строки.
### Аргументы

- *const char ** **name** - Имя Json-узла.

### Возвращаемое значение

Значение текущего Json-узла как целое число.
## void write ( const char * name , bool value )

Записывает указанное логическое значение в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *bool* **value** - Логическое значение, записываемое в Json-узел с указанным именем.

## void write ( const char * name , int value )

Записывает указанное целочисленное значение в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *int* **value** - Целочисленное значение, записываемое в Json-узел с указанным именем.

## void write ( const char * name , unsigned int value )

Записывает указанное беззнаковое целочисленное значение в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *unsigned int* **value** - Беззнаковое целочисленное значение, записываемое в Json-узел с указанным именем.

## void write ( const char * name , char value )

Записывает указанное символьное значение в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *char* **value** - Символьное значение, записываемое в Json-узел с указанным именем.

## void write ( const char * name , const char * value )

Записывает указанное значение в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const char ** **value** - Значение, записываемое в Json-узел с указанным именем.

## void write ( const char * name , double value )

Записывает указанное значение double в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *double* **value** - Значение double, записываемое в Json-узел с указанным именем.

## void write ( const char * name , float value )

Записывает указанное значение float в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *float* **value** - Значение float, записываемое в Json-узел с указанным именем.

## void write ( const char * name , const Math:: vec2 & value )

Записывает указанное двухкомпонентное значение в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **value** - Двухкомпонентное значение, записываемое в Json-узел с указанным именем.

## void write ( const char * name , const Math:: vec3 & value )

Записывает указанное трёхкомпонентное значение в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **value** - Трёхкомпонентное значение, записываемое в Json-узел с указанным именем.

## void write ( const char * name , const Math:: vec4 & value )

Записывает указанное четырёхкомпонентное значение в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **value** - Четырёхкомпонентное значение, записываемое в Json-узел с указанным именем.

## void write ( const char * name , const Math:: dvec2 & value )

Записывает указанное двухкомпонентное значение в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const  Math::[dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **value** - Двухкомпонентное значение, записываемое в Json-узел с указанным именем.

## void write ( const char * name , const Math:: dvec3 & value )

Записывает указанное трёхкомпонентное значение в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **value** - Трёхкомпонентное значение, записываемое в Json-узел с указанным именем.

## void write ( const char * name , const Math:: dvec4 & value )

Записывает указанное четырёхкомпонентное значение в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const  Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **value** - Четырёхкомпонентное значение, записываемое в Json-узел с указанным именем.

## void write ( const char * name , const Math:: ivec2 & value )

Записывает указанное двухкомпонентное значение в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **value** - Двухкомпонентное значение, записываемое в Json-узел с указанным именем.

## void write ( const char * name , const Math:: ivec3 & value )

Записывает указанное трёхкомпонентное значение в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const  Math::[ivec3](../../../api/library/math/class.ivec3_cpp.md) &* **value** - Трёхкомпонентное значение, записываемое в Json-узел с указанным именем.

## void write ( const char * name , const Math:: ivec4 & value )

Записывает указанное четырёхкомпонентное значение в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const  Math::[ivec4](../../../api/library/math/class.ivec4_cpp.md) &* **value** - Четырёхкомпонентное значение, записываемое в Json-узел с указанным именем.

## void write ( const char * name , const Vector < int > & value )

Записывает указанные значения в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< int > &* **value** - Вектор значений, записываемых в Json-узел с указанным именем.

## void write ( const char * name , const Vector < char > & value )

Записывает указанные значения в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< char > &* **value** - Вектор значений, записываемых в Json-узел с указанным именем.

## void write ( const char * name , const Vector < double > & value )

Записывает указанные значения в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< double > &* **value** - Вектор значений, записываемых в Json-узел с указанным именем.

## void write ( const char * name , const Vector < float > & value )

Записывает указанные значения в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< float > &* **value** - Вектор значений, записываемых в Json-узел с указанным именем.

## void write ( const char * name , const Vector < String > & value )

Записывает указанные значения в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< [String](../../../api/library/common/class.string_cpp.md) > &* **value** - Вектор значений, записываемых в Json-узел с указанным именем.

## void write ( const char * name , const Vector < Math:: vec2 > & value )

Записывает указанные значения в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) > &* **value** - Вектор значений, записываемых в Json-узел с указанным именем.

## void write ( const char * name , const Vector < Math:: vec3 > & value )

Записывает указанные значения в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) > &* **value** - Вектор значений, записываемых в Json-узел с указанным именем.

## void write ( const char * name , const Vector < Math:: vec4 > & value )

Записывает указанные значения в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) > &* **value** - Вектор значений, записываемых в Json-узел с указанным именем.

## void write ( const char * name , const Vector < Math:: dvec2 > & value )

Записывает указанные значения в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[dvec2](../../../api/library/math/class.dvec2_cpp.md) > &* **value** - Вектор значений, записываемых в Json-узел с указанным именем.

## void write ( const char * name , const Vector < Math:: dvec3 > & value )

Записывает указанные значения в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) > &* **value** - Вектор значений, записываемых в Json-узел с указанным именем.

## void write ( const char * name , const Vector < Math:: dvec4 > & value )

Записывает указанные значения в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) > &* **value** - Вектор значений, записываемых в Json-узел с указанным именем.

## void write ( const char * name , const Vector < Math:: ivec2 > & value )

Записывает указанные значения в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) > &* **value** - Вектор значений, записываемых в Json-узел с указанным именем.

## void write ( const char * name , const Vector < Math:: ivec3 > & value )

Записывает указанные значения в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[ivec3](../../../api/library/math/class.ivec3_cpp.md) > &* **value** - Вектор значений, записываемых в Json-узел с указанным именем.

## void write ( const char * name , const Vector < Math:: ivec4 > & value )

Записывает указанные значения в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[ivec4](../../../api/library/math/class.ivec4_cpp.md) > &* **value** - Вектор значений, записываемых в Json-узел с указанным именем.

## void write ( const char * name , const UGUID& value )

Записывает указанное значение в целевой Json-узел с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *const UGUID&* **value** - UGUID значения, записываемого в Json-узел с указанным именем.

## void write ( const UGUID& value )

Записывает указанное значение в текущий Json-узел.
### Аргументы

- *const UGUID&* **value** - UGUID значения, записываемого в Json-узел.

## void write ( bool value )

Записывает указанное логическое значение в текущий Json-узел.
### Аргументы

- *bool* **value** - Логическое значение, записываемое в текущий Json-узел.

## void write ( int value )

Записывает указанное целочисленное значение в текущий Json-узел.
### Аргументы

- *int* **value** - Целочисленное значение, записываемое в текущий Json-узел.

## void write ( char value )

Записывает указанное символьное значение в текущий Json-узел.
### Аргументы

- *char* **value** - Символьное значение, записываемое в текущий Json-узел.

## void write ( const char * value )

Записывает указанное значение в текущий Json-узел.
### Аргументы

- *const char ** **value** - Значение, записываемое в текущий Json-узел.

## void write ( double value )

Записывает указанное значение double в текущий Json-узел.
### Аргументы

- *double* **value** - Значение double, записываемое в текущий Json-узел.

## void write ( float value )

Записывает указанное значение float в текущий Json-узел.
### Аргументы

- *float* **value** - Значение float, записываемое в текущий Json-узел.

## void write ( const Math:: vec2 & value )

Записывает указанное двухкомпонентное значение в текущий Json-узел.
### Аргументы

- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **value** - Двухкомпонентное значение, записываемое в текущий Json-узел.

## void write ( const Math:: vec3 & value )

Записывает указанное трёхкомпонентное значение в текущий Json-узел.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **value** - Трёхкомпонентное значение, записываемое в текущий Json-узел.

## void write ( const Math:: vec4 & value )

Записывает указанное четырёхкомпонентное значение в текущий Json-узел.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **value** - Четырёхкомпонентное значение, записываемое в текущий Json-узел.

## void write ( const Math:: dvec2 & value )

Записывает указанное двухкомпонентное значение в текущий Json-узел.
### Аргументы

- *const  Math::[dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **value** - Двухкомпонентное значение, записываемое в текущий Json-узел.

## void write ( const Math:: dvec3 & value )

Записывает указанное трёхкомпонентное значение в текущий Json-узел.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **value** - Трёхкомпонентное значение, записываемое в текущий Json-узел.

## void write ( const Math:: dvec4 & value )

Записывает указанное четырёхкомпонентное значение в текущий Json-узел.
### Аргументы

- *const  Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **value** - Четырёхкомпонентное значение, записываемое в текущий Json-узел.

## void write ( const Math:: ivec2 & value )

Записывает указанное двухкомпонентное значение в текущий Json-узел.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **value** - Двухкомпонентное значение, записываемое в текущий Json-узел.

## void write ( const Math:: ivec3 & value )

Записывает указанное трёхкомпонентное значение в текущий Json-узел.
### Аргументы

- *const  Math::[ivec3](../../../api/library/math/class.ivec3_cpp.md) &* **value** - Трёхкомпонентное значение, записываемое в текущий Json-узел.

## void write ( const Math:: ivec4 & value )

Записывает указанное четырёхкомпонентное значение в текущий Json-узел.
### Аргументы

- *const  Math::[ivec4](../../../api/library/math/class.ivec4_cpp.md) &* **value** - Четырёхкомпонентное значение, записываемое в текущий Json-узел.

## void write ( const Vector < bool > & value )

Записывает указанные значения в текущий Json-узел.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< bool > &* **value** - Вектор значений, записываемых в текущий Json-узел.

## void write ( const Vector < int > & value )

Записывает указанные значения в текущий Json-узел.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< int > &* **value** - Вектор значений, записываемых в текущий Json-узел.

## void write ( const Vector < char > & value )

Записывает указанные значения в текущий Json-узел.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< char > &* **value** - Вектор значений, записываемых в текущий Json-узел.

## void write ( const Vector < double > & value )

Записывает указанные значения в текущий Json-узел.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< double > &* **value** - Вектор значений, записываемых в текущий Json-узел.

## void write ( const Vector < float > & value )

Записывает указанные значения в текущий Json-узел.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< float > &* **value** - Вектор значений, записываемых в текущий Json-узел.

## void write ( const Vector < String > & value )

Записывает указанные значения в текущий Json-узел.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< [String](../../../api/library/common/class.string_cpp.md) > &* **value** - Вектор значений, записываемых в текущий Json-узел.

## void write ( const Vector < Math:: vec2 > & value )

Записывает указанные значения в текущий Json-узел.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) > &* **value** - Вектор значений, записываемых в текущий Json-узел.

## void write ( const Vector < Math:: vec3 > & value )

Записывает указанные значения в текущий Json-узел.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) > &* **value** - Вектор значений, записываемых в текущий Json-узел.

## void write ( const Vector < Math:: vec4 > & value )

Записывает указанные значения в текущий Json-узел.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) > &* **value** - Вектор значений, записываемых в текущий Json-узел.

## void write ( const Vector < Math:: dvec2 > & value )

Записывает указанные значения в текущий Json-узел.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[dvec2](../../../api/library/math/class.dvec2_cpp.md) > &* **value** - Вектор значений, записываемых в текущий Json-узел.

## void write ( const Vector < Math:: dvec3 > & value )

Записывает указанные значения в текущий Json-узел.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) > &* **value** - Вектор значений, записываемых в текущий Json-узел.

## void write ( const Vector < Math:: dvec4 > & value )

Записывает указанные значения в текущий Json-узел.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) > &* **value** - Вектор значений, записываемых в текущий Json-узел.

## void write ( const Vector < Math:: ivec2 > & value )

Записывает указанные значения в текущий Json-узел.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) > &* **value** - Вектор значений, записываемых в текущий Json-узел.

## void write ( const Vector < Math:: ivec3 > & value )

Записывает указанные значения в текущий Json-узел.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[ivec3](../../../api/library/math/class.ivec3_cpp.md) > &* **value** - Вектор значений, записываемых в текущий Json-узел.

## void write ( const Vector < Math:: ivec4 > & value )

Записывает указанные значения в текущий Json-узел.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[ivec4](../../../api/library/math/class.ivec4_cpp.md) > &* **value** - Вектор значений, записываемых в текущий Json-узел.

## const char * getTypeName ( ) const

Возвращает имя [type](#node_type) Json-узла.
### Возвращаемое значение

Имя типа Json-узла.
## void setInt ( int value )

Задаёт указанное целочисленное значение текущему Json-узлу.
### Аргументы

- *int* **value** - Значение, задаваемое текущему Json-узлу.

## void setInt ( const char * name , int value )

Задаёт указанное целочисленное значение целевому Json-узлу с указанным именем. Если такой узел не найден, добавляется новый узел с указанным именем.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.
- *int* **value** - Значение, задаваемое целевому Json-узлу.

## int getInt ( ) const

Возвращает значение текущего Json-узла как целочисленное значение, если это возможно.
### Возвращаемое значение

Значение текущего Json-узла как целое число.
## int getInt ( const char * name ) const

Возвращает значение целевого Json-узла с указанным именем как целочисленное значение, если это возможно.
### Аргументы

- *const char ** **name** - Имя целевого Json-узла.

## void setVec2 ( const Math:: vec2 & value )

Задаёт первые два элемента Json-узла типа массив.
### Аргументы

- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **value** - Вектор, задающий первые два элемента Json-узла типа массив.

## Math:: vec2 getVec2 ( ) const

Возвращает двухкомпонентный вектор, составленный из первых двух элементов Json-узла типа массив. Если узел не является массивом, будет возвращён нулевой вектор (0.0f, 0.0f).
### Возвращаемое значение

Вектор, составленный из первых двух элементов Json-узла типа массив.
## void setVec3 ( const Math:: vec3 & value )

Задаёт первые три элемента Json-узла типа массив.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **value** - Вектор, задающий первые три элемента Json-узла типа массив.

## Math:: vec3 getVec3 ( ) const

Возвращает трёхкомпонентный вектор, составленный из первых трёх элементов Json-узла типа массив. Если узел не является массивом, будет возвращён нулевой вектор (0.0f, 0.0f, 0.0f).
### Возвращаемое значение

Вектор, составленный из первых трёх элементов Json-узла типа массив.
## void setVec4 ( const Math:: vec4 & value )

Задаёт первые четыре элемента Json-узла типа массив.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **value** - Вектор, задающий первые четыре элемента Json-узла типа массив.

## Math:: vec4 getVec4 ( ) const

Возвращает четырёхкомпонентный вектор, составленный из первых четырёх элементов Json-узла типа массив. Если узел не является массивом, будет возвращён нулевой вектор (0.0f, 0.0f, 0.0f, 0.0f).
### Возвращаемое значение

Вектор, составленный из первых четырёх элементов Json-узла типа массив.
## void setDVec2 ( const Math:: dvec2 & value )

Задаёт первые два элемента Json-узла типа массив.
### Аргументы

- *const  Math::[dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **value** - Вектор, задающий первые два элемента Json-узла типа массив.

## Math:: dvec2 getDVec2 ( ) const

Возвращает двухкомпонентный вектор, составленный из первых двух элементов Json-узла типа массив. Если узел не является массивом, будет возвращён нулевой вектор (0.0, 0.0).
### Возвращаемое значение

Вектор, составленный из первых двух элементов Json-узла типа массив.
## void setDVec3 ( const Math:: dvec3 & value )

Задаёт первые три элемента Json-узла типа массив.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **value** - Вектор, задающий первые три элемента Json-узла типа массив.

## Math:: dvec3 getDVec3 ( ) const

Возвращает трёхкомпонентный вектор, составленный из первых трёх элементов Json-узла типа массив. Если узел не является массивом, будет возвращён нулевой вектор (0.0, 0.0, 0.0).
### Возвращаемое значение

Вектор, составленный из первых трёх элементов Json-узла типа массив.
## void setDVec4 ( const Math:: dvec4 & value )

Задаёт первые четыре элемента Json-узла типа массив.
### Аргументы

- *const  Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **value** - Вектор, задающий первые четыре элемента Json-узла типа массив.

## Math:: dvec4 getDVec4 ( ) const

Возвращает четырёхкомпонентный вектор, составленный из первых четырёх элементов Json-узла типа массив. Если узел не является массивом, будет возвращён нулевой вектор (0.0, 0.0, 0.0, 0.0).
### Возвращаемое значение

Вектор, составленный из первых четырёх элементов Json-узла типа массив.
## void setIVec2 ( const Math:: ivec2 & value )

Задаёт первые два элемента Json-узла типа массив.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **value** - Вектор, задающий первые два элемента Json-узла типа массив.

## Math:: ivec2 getIVec2 ( ) const

Возвращает двухкомпонентный вектор, составленный из первых двух элементов Json-узла типа массив. Если узел не является массивом, будет возвращён нулевой вектор (0, 0).
### Возвращаемое значение

Вектор, составленный из первых двух элементов Json-узла типа массив.
## void setIVec3 ( const Math:: ivec3 & value )

Задаёт первые три элемента Json-узла типа массив.
### Аргументы

- *const  Math::[ivec3](../../../api/library/math/class.ivec3_cpp.md) &* **value** - Вектор, задающий первые три элемента Json-узла типа массив.

## Math:: ivec3 getIVec3 ( ) const

Возвращает трёхкомпонентный вектор, составленный из первых трёх элементов Json-узла типа массив. Если узел не является массивом, будет возвращён нулевой вектор (0, 0, 0).
### Возвращаемое значение

Вектор, составленный из первых трёх элементов Json-узла типа массив.
## void setIVec4 ( const Math:: ivec4 & value )

Задаёт первые четыре элемента Json-узла типа массив.
### Аргументы

- *const  Math::[ivec4](../../../api/library/math/class.ivec4_cpp.md) &* **value** - Вектор, задающий первые четыре элемента Json-узла типа массив.

## Math:: ivec4 getIVec4 ( ) const

Возвращает четырёхкомпонентный вектор, составленный из первых четырёх элементов Json-узла типа массив. Если узел не является массивом, будет возвращён нулевой вектор (0, 0, 0, 0).
### Возвращаемое значение

Вектор, составленный из первых четырёх элементов Json-узла типа массив.
