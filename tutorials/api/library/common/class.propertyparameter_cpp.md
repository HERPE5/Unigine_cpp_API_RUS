# Unigine::PropertyParameter Class (CPP)

**Header:** #include <UnigineProperties.h>


Этот класс используется для представления [property parameter](../../../code/formats/property_format.md#element_parameter).


## PropertyParameter Class

### Методы класса

## const char * getStructName () const

Возвращает текущее имя структуры, определяющей тип параметра-структуры.
### Возвращаемое значение

Текущее имя структуры, определяющей тип параметра-структуры.
## int getArrayDim () const

Возвращает текущую размерность параметра-массива.
> **Notice:** Многомерные массивы представлены как массивы массивов, поэтому возвращаемое значение этого метода будет уменьшаться с каждым уровнем вниз по иерархии.


### Возвращаемое значение

Текущая размерность параметра-массива.
## const char * getArrayTypeName () const

Возвращает текущее имя типа элементов параметра-массива.
### Возвращаемое значение

Текущее имя типа элементов параметра-массива (Float, Node, Material и т.д.).
## int getArrayType () const

Возвращает текущий тип элементов параметра-массива.
### Возвращаемое значение

Текущий тип элементов массива, одно из значений [*PARAMETER_**](../../../api/library/common/class.property_cpp.md#PARAMETER_COLOR).
> **Notice:** Этот метод не возвращает [*PARAMETER_ARRAY*](../../../api/library/common/class.property_cpp.md#PARAMETER_ARRAY) для параметра-массива, вместо этого он возвращает тип элементов массива (например, [*PARAMETER_FLOAT*](../../../api/library/common/class.property_cpp.md#PARAMETER_FLOAT), [*PARAMETER_STRUCT*](../../../api/library/common/class.property_cpp.md#PARAMETER_STRUCT) и т.д.)

## void setArraySize ( int size )

Задаёт новый размер параметра-массива.
### Аргументы

- *int* **size** - Размер массива (количество элементов).

## int getArraySize () const

Возвращает текущий размер параметра-массива.
### Возвращаемое значение

Текущий размер массива (количество элементов).
## void setValueFile ( const char * file )

Задаёт новое
значение [file parameter](../../../code/formats/property_format.md#parameter_type). Если свойство не [editable](../../../api/library/common/class.property_cpp.md#isEditable_int), значение не будет обновлено.


Значение, хранящееся в параметре файла, зависит от [flags](../../../code/formats/property_format.md#parameter_flags), заданных для параметра.


```cpp
// flags = "asset"
setValueFile("guid://asset_guid"); 		// getValueFile() -> asset_path
setValueFile("guid://runtime_guid");	// getValueFile() -> asset_path
setValueFile("asset_path");				// getValueFile() -> asset_path
setValueFile("runtime_path");			// getValueFile() -> asset_path

// flags = "runtime" - default
setValueFile("guid://asset_guid"); 		// getValueFile() -> runtime_path
setValueFile("guid://runtime_guid");	// getValueFile() -> runtime_path
setValueFile("asset_path");				// getValueFile() -> runtime_path
setValueFile("runtime_path");			// getValueFile() -> runtime_path

// flags = "abspath"
setValueFile(file_path);				// getValueFile() -> file_path

```


### Аргументы

- *const char ** **file** - Значение параметра файла.

## const char * getValueFile () const

Возвращает текущее
значение [file parameter](../../../code/formats/property_format.md#parameter_type). Если свойство не [editable](../../../api/library/common/class.property_cpp.md#isEditable_int), значение не будет обновлено.


Значение, хранящееся в параметре файла, зависит от [flags](../../../code/formats/property_format.md#parameter_flags), заданных для параметра.


```cpp
// flags = "asset"
setValueFile("guid://asset_guid"); 		// getValueFile() -> asset_path
setValueFile("guid://runtime_guid");	// getValueFile() -> asset_path
setValueFile("asset_path");				// getValueFile() -> asset_path
setValueFile("runtime_path");			// getValueFile() -> asset_path

// flags = "runtime" - default
setValueFile("guid://asset_guid"); 		// getValueFile() -> runtime_path
setValueFile("guid://runtime_guid");	// getValueFile() -> runtime_path
setValueFile("asset_path");				// getValueFile() -> runtime_path
setValueFile("runtime_path");			// getValueFile() -> runtime_path

// flags = "abspath"
setValueFile(file_path);				// getValueFile() -> file_path

```


### Возвращаемое значение

Текущее значение параметра файла.
## int getMaskType () const

Возвращает текущий тип элементов параметра-маски.
### Возвращаемое значение

Текущий тип параметра-маски, одно из значений [*PARAMETER_MASK_**](../../../api/library/common/class.property_cpp.md#PARAMETER_MASK_FIELD).
## int getSwitchNumItems () const

Возвращает текущее количество [items](../../../code/formats/property_format.md#parameter_items) [switch parameter](../../../code/formats/property_format.md#parameter_type). Если для параметра не задана переменная [*PARAMETER_SWITCH*](../../../api/library/common/class.property_cpp.md#PARAMETER_SWITCH), функция вернёт 0.
### Возвращаемое значение

Текущее количество элементов параметра-переключателя.
## int getSliderMaxExpand () const

Возвращает текущее значение, указывающее, может ли быть [decreased](../../../code/formats/property_format.md#parameter_flags) максимальное значение параметра-слайдера. Параметр-слайдер — это параметр одного из следующих типов: [PARAMETER_INT](../../../api/library/common/class.property_cpp.md#PARAMETER_INT), [PARAMETER_FLOAT](../../../api/library/common/class.property_cpp.md#PARAMETER_FLOAT), [PARAMETER_DOUBLE](../../../api/library/common/class.property_cpp.md#PARAMETER_INT).
### Возвращаемое значение

Текущее значение 1, если максимальное значение можно изменить; иначе 0.
## int getSliderMinExpand () const

Возвращает текущее значение, указывающее, может ли быть [decreased](../../../code/formats/property_format.md#parameter_flags) минимальное значение параметра-слайдера. Параметр-слайдер — это параметр одного из следующих типов: [PARAMETER_INT](../../../api/library/common/class.property_cpp.md#PARAMETER_INT), [PARAMETER_FLOAT](../../../api/library/common/class.property_cpp.md#PARAMETER_FLOAT), [PARAMETER_DOUBLE](../../../api/library/common/class.property_cpp.md#PARAMETER_INT).
### Возвращаемое значение

Текущее значение 1, если минимальное значение можно изменить; иначе 0.
## int getSliderLog10 () const

Возвращает текущее значение, указывающее, использует ли параметр-слайдер [logarithmic scale](../../../code/formats/property_format.md#parameter_flags) (с основанием десять). Параметр-слайдер — это параметр одного из следующих типов: [PARAMETER_INT](../../../api/library/common/class.property_cpp.md#PARAMETER_INT), [PARAMETER_FLOAT](../../../api/library/common/class.property_cpp.md#PARAMETER_FLOAT), [PARAMETER_DOUBLE](../../../api/library/common/class.property_cpp.md#PARAMETER_DOUBLE).
### Возвращаемое значение

Текущее значение 1, если параметр свойства использует логарифмическую шкалу; иначе 0.
## double getDoubleMaxValue () const

Возвращает текущее максимальное значение типа double параметра свойства.
### Возвращаемое значение

Текущее максимальное значение типа double параметра свойства.
## double getDoubleMinValue () const

Возвращает текущее минимальное значение типа double параметра свойства.
### Возвращаемое значение

Текущее минимальное значение типа double параметра свойства.
## float getFloatMaxValue () const

Возвращает текущее максимальное значение типа float параметра свойства.
### Возвращаемое значение

Текущее максимальное значение типа float параметра свойства.
## float getFloatMinValue () const

Возвращает текущее минимальное значение типа float параметра свойства.
### Возвращаемое значение

Текущее минимальное значение типа float параметра свойства.
## int getIntMaxValue () const

Возвращает текущее максимальное целочисленное значение параметра свойства.
### Возвращаемое значение

Текущее максимальное целочисленное значение параметра свойства.
## int getIntMinValue () const

Возвращает текущее минимальное целочисленное значение параметра свойства.
### Возвращаемое значение

Текущее минимальное целочисленное значение параметра свойства.
## void setValueGUID ( const UGUID & guid )

Задаёт новое значение параметра свойства типа [UGUID](../../../api/library/filesystem/class.uguid_cpp.md).
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - Значение параметра свойства типа [UGUID](../../../api/library/filesystem/class.uguid_cpp.md).

## const UGUID & getValueGUID () const

Возвращает текущее значение параметра свойства типа [UGUID](../../../api/library/filesystem/class.uguid_cpp.md).
### Возвращаемое значение

Текущее значение параметра свойства типа [UGUID](../../../api/library/filesystem/class.uguid_cpp.md).
## void setValueMask ( int mask )

Задаёт новое значение [mask parameter](../../../code/formats/property_format.md#parameter_type). Если для параметра не задана переменная [*PARAMETER_MASK*](../../../api/library/common/class.property_cpp.md#PARAMETER_MASK), или свойство не [editable](../../../api/library/common/class.property_cpp.md#isEditable_int), значение не будет обновлено.
### Аргументы

- *int* **mask** - Значение целочисленного параметра-маски свойства.

## int getValueMask () const

Возвращает текущее значение [mask parameter](../../../code/formats/property_format.md#parameter_type). Если для параметра не задана переменная [*PARAMETER_MASK*](../../../api/library/common/class.property_cpp.md#PARAMETER_MASK), или свойство не [editable](../../../api/library/common/class.property_cpp.md#isEditable_int), значение не будет обновлено.
### Возвращаемое значение

Текущее значение целочисленного параметра-маски свойства.
## void setValueSwitch ( int switch )

Задаёт новое значение [switch parameter](../../../code/formats/property_format.md#parameter_type). Если для параметра не задана переменная [*PARAMETER_SWITCH*](../../../api/library/common/class.property_cpp.md#PARAMETER_SWITCH), функция вернёт 0.
### Аргументы

- *int* **switch** - Значение параметра-переключателя.

## int getValueSwitch () const

Возвращает текущее значение [switch parameter](../../../code/formats/property_format.md#parameter_type). Если для параметра не задана переменная [*PARAMETER_SWITCH*](../../../api/library/common/class.property_cpp.md#PARAMETER_SWITCH), функция вернёт 0.
### Возвращаемое значение

Текущее значение параметра-переключателя.
## void setValueToggle ( bool toggle )

Задаёт новое значение [toggle parameter](../../../code/formats/property_format.md#parameter_type). Если для параметра не задана переменная [*PARAMETER_TOGGLE*](../../../api/library/common/class.property_cpp.md#PARAMETER_TOGGLE), функция вернёт 0.
### Аргументы

- *bool* **toggle** - true — установить значение параметра-флажка как включённое, false — как выключенное.

## bool getValueToggle () const

Возвращает текущее значение [toggle parameter](../../../code/formats/property_format.md#parameter_type). Если для параметра не задана переменная [*PARAMETER_TOGGLE*](../../../api/library/common/class.property_cpp.md#PARAMETER_TOGGLE), функция вернёт 0.
### Возвращаемое значение

true, если значение параметра-флажка установлено как включённое, и false — как выключенное.
## void setValueNodeID ( int id )

Задаёт новое значение параметра свойства - идентификатора узла.
### Аргументы

- *int* **id** - Значение параметра свойства - идентификатора узла.

## int getValueNodeID () const

Возвращает текущее значение параметра свойства - идентификатора узла.
### Возвращаемое значение

Текущее значение параметра свойства - идентификатора узла.
## void setValueNode ( const Ptr < Node >& node )

Задаёт новое значение параметра свойства типа [Node](../../../api/library/nodes/class.node_cpp.md).
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>&* **node** - Значение параметра свойства типа [Node](../../../api/library/nodes/class.node_cpp.md).

## Ptr < Node > getValueNode () const

Возвращает текущее значение параметра свойства типа [Node](../../../api/library/nodes/class.node_cpp.md).
### Возвращаемое значение

Текущее значение параметра свойства типа [Node](../../../api/library/nodes/class.node_cpp.md).
## void setValueMaterial ( const Ptr < Material >& material )

Задаёт новое значение параметра свойства типа [Material](../../../api/library/rendering/class.material_cpp.md).
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)>&* **material** - Значение параметра свойства типа [Material](../../../api/library/rendering/class.material_cpp.md).

## Ptr < Material > getValueMaterial () const

Возвращает текущее значение параметра свойства типа [Material](../../../api/library/rendering/class.material_cpp.md).
### Возвращаемое значение

Текущее значение параметра свойства типа [Material](../../../api/library/rendering/class.material_cpp.md).
## void setValueProperty ( const Ptr < Property >& property )

Задаёт новое значение параметра свойства типа [Property](../../../api/library/common/class.property_cpp.md).
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Property](../../../api/library/common/class.property_cpp.md)>&* **property** - Значение параметра свойства типа [Property](../../../api/library/common/class.property_cpp.md).

## Ptr < Property > getValueProperty () const

Возвращает текущее значение параметра свойства типа [Property](../../../api/library/common/class.property_cpp.md).
### Возвращаемое значение

Текущее значение параметра свойства типа [Property](../../../api/library/common/class.property_cpp.md).
## void setValueVec4 ( const Math:: vec4 & vec4 )

Задаёт новое значение параметра свойства - четырёхкомпонентного вектора [vec4](../../../api/library/math/class.vec4_cpp.md)
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md)&* **vec4** - Значение параметра свойства - четырёхкомпонентного вектора [vec4](../../../api/library/math/class.vec4_cpp.md)

## Math:: vec4 getValueVec4 () const

Возвращает текущее значение параметра свойства - четырёхкомпонентного вектора [vec4](../../../api/library/math/class.vec4_cpp.md)
### Возвращаемое значение

Текущее значение параметра свойства - четырёхкомпонентного вектора [vec4](../../../api/library/math/class.vec4_cpp.md)
## void setValueVec3 ( const Math:: vec3 & vec3 )

Задаёт новое значение параметра свойства - трёхкомпонентного вектора [vec3](../../../api/library/math/class.vec3_cpp.md)
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md)&* **vec3** - Значение параметра свойства - трёхкомпонентного вектора [vec3](../../../api/library/math/class.vec3_cpp.md)

## Math:: vec3 getValueVec3 () const

Возвращает текущее значение параметра свойства - трёхкомпонентного вектора [vec3](../../../api/library/math/class.vec3_cpp.md)
### Возвращаемое значение

Текущее значение параметра свойства - трёхкомпонентного вектора [vec3](../../../api/library/math/class.vec3_cpp.md)
## void setValueString ( const char * string )

Задаёт новое значение строкового параметра свойства.
### Аргументы

- *const char ** **string** - Значение строкового параметра свойства.

## const char * getValueString () const

Возвращает текущее значение строкового параметра свойства.
### Возвращаемое значение

Текущее значение строкового параметра свойства.
## void setValueColor ( const Math:: vec4 & color )

Задаёт новое значение параметра свойства - четырёхкомпонентного вектора цвета [vec4](../../../api/library/math/class.vec4_cpp.md) (R, G, B, A).
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md)&* **color** - Значение параметра свойства - четырёхкомпонентного вектора цвета [vec4](../../../api/library/math/class.vec4_cpp.md) (R, G, B, A).

## Math:: vec4 getValueColor () const

Возвращает текущее значение параметра свойства - четырёхкомпонентного вектора цвета [vec4](../../../api/library/math/class.vec4_cpp.md) (R, G, B, A).
### Возвращаемое значение

Текущее значение параметра свойства - четырёхкомпонентного вектора цвета [vec4](../../../api/library/math/class.vec4_cpp.md) (R, G, B, A).
## void setValueDouble ( double double )

Задаёт новое значение параметра свойства типа double.
### Аргументы

- *double* **double** - Значение параметра свойства типа double.

## double getValueDouble () const

Возвращает текущее значение параметра свойства типа double.
### Возвращаемое значение

Текущее значение параметра свойства типа double.
## void setValueFloat ( float float )

Задаёт новое значение параметра свойства типа float.
### Аргументы

- *float* **float** - Значение параметра свойства типа float.

## float getValueFloat () const

Возвращает текущее значение параметра свойства типа float.
### Возвращаемое значение

Текущее значение параметра свойства типа float.
## void setValueInt ( int int )

Задаёт новое значение целочисленного параметра свойства.
### Аргументы

- *int* **int** - Значение целочисленного параметра свойства.

## int getValueInt () const

Возвращает текущее значение целочисленного параметра свойства.
### Возвращаемое значение

Текущее значение целочисленного параметра свойства.
## Ptr < Curve2d > getValueCurve2dOverride () const

Возвращает текущий экземпляр [Curve2d](../../../api/library/common/class.curve2d_cpp.md) для данных, хранящихся в указанном параметре свойства, переопределяющий значение по умолчанию. Этот метод позволяет задавать индивидуальные кривые, корректируя значение итогового свойства.
> **Notice:** Изменения, внесённые в кривую, не распространяются на родительские и одноуровневые свойства.


### Возвращаемое значение

Текущее
## void setValueCurve2d ( const Ptr < Curve2d >& curve2d )

Задаёт новое значение параметра свойства типа [Curve2d](../../../api/library/common/class.curve2d_cpp.md).
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Curve2d](../../../api/library/common/class.curve2d_cpp.md)>&* **curve2d** - Значение параметра свойства типа [Curve2d](../../../api/library/common/class.curve2d_cpp.md).

## Ptr < Curve2d > getValueCurve2d () const

Возвращает текущее значение параметра свойства типа [Curve2d](../../../api/library/common/class.curve2d_cpp.md).
### Возвращаемое значение

Текущее значение параметра свойства типа [Curve2d](../../../api/library/common/class.curve2d_cpp.md).
## bool isCurve2d () const

Возвращает значение, указывающее, является ли параметр свойства 2D-кривой.
### Возвращаемое значение

**true**, если параметр свойства является 2D-кривой; иначе **false**.
## bool isStruct () const

Возвращает значение, указывающее, является ли параметр свойства структурой.
### Возвращаемое значение

**true**, если параметр свойства является структурой; иначе **false**.
## bool isArray () const

Возвращает значение, указывающее, является ли параметр свойства массивом.
### Возвращаемое значение

**true**, если параметр свойства является массивом; иначе **false**.
## bool isNode () const

Возвращает значение, указывающее, является ли параметр свойства узлом.
### Возвращаемое значение

**true**, если параметр свойства является узлом; иначе **false**.
## bool isMaterial () const

Возвращает значение, указывающее, является ли параметр свойства материалом.
### Возвращаемое значение

**true**, если параметр свойства является материалом; иначе **false**.
## bool isProperty () const

Возвращает значение, указывающее, является ли параметр свойства свойством (Property).
### Возвращаемое значение

**true**, если параметр свойства является свойством (Property); иначе **false**.
## bool isFile () const

Возвращает значение, указывающее, является ли параметр свойства файлом.
### Возвращаемое значение

**true**, если параметр свойства является файлом; иначе **false**.
## bool isMask () const

Возвращает значение, указывающее, является ли параметр свойства маской.
### Возвращаемое значение

**true**, если параметр свойства является маской; иначе **false**.
## bool isIVec4 () const

Возвращает значение, указывающее, является ли параметр свойства вектором из 4 целочисленных компонентов.
### Возвращаемое значение

**true**, если параметр свойства является вектором из 4 целочисленных компонентов; иначе **false**.
## bool isIVec3 () const

Возвращает значение, указывающее, является ли параметр свойства вектором из 3 целочисленных компонентов.
### Возвращаемое значение

**true**, если параметр свойства является вектором из 3 целочисленных компонентов; иначе **false**.
## bool isIVec2 () const

Возвращает значение, указывающее, является ли параметр свойства вектором из 2 целочисленных компонентов.
### Возвращаемое значение

**true**, если параметр свойства является вектором из 2 целочисленных компонентов; иначе **false**.
## bool isDVec4 () const

Возвращает значение, указывающее, является ли параметр свойства вектором из 4 компонентов типа double.
### Возвращаемое значение

**true**, если параметр свойства является вектором из 4 компонентов типа double; иначе **false**.
## bool isDVec3 () const

Возвращает значение, указывающее, является ли параметр свойства вектором из 3 компонентов типа double.
### Возвращаемое значение

**true**, если параметр свойства является вектором из 3 компонентов типа double; иначе **false**.
## bool isDVec2 () const

Возвращает значение, указывающее, является ли параметр свойства вектором из 2 компонентов типа double.
### Возвращаемое значение

**true**, если параметр свойства является вектором из 2 компонентов типа double; иначе **false**.
## bool isVec4 () const

Возвращает значение, указывающее, является ли параметр свойства вектором из 4 компонентов типа float.
### Возвращаемое значение

**true**, если параметр свойства является вектором из 4 компонентов типа float; иначе **false**.
## bool isVec3 () const

Возвращает значение, указывающее, является ли параметр свойства вектором из 3 компонентов типа float.
### Возвращаемое значение

**true**, если параметр свойства является вектором из 3 компонентов типа float; иначе **false**.
## bool isVec2 () const

Возвращает значение, указывающее, является ли параметр свойства вектором из 2 компонентов типа float.
### Возвращаемое значение

**true**, если параметр свойства является вектором из 2 компонентов типа float; иначе **false**.
## bool isColor () const

Возвращает значение, указывающее, является ли параметр свойства цветом.
### Возвращаемое значение

**true**, если параметр свойства является цветом; иначе **false**.
## bool isString () const

Возвращает значение, указывающее, является ли параметр свойства строкой.
### Возвращаемое значение

**true**, если параметр свойства является строкой; иначе **false**.
## bool isSwitch () const

Возвращает значение, указывающее, является ли параметр свойства переключателем (switch).
### Возвращаемое значение

**true**, если параметр свойства является переключателем (switch); иначе **false**.
## bool isToggle () const

Возвращает значение, указывающее, является ли параметр свойства флажком (toggle).
### Возвращаемое значение

**true**, если параметр свойства является флажком (toggle); иначе **false**.
## bool isDouble () const

Возвращает значение, указывающее, является ли параметр свойства значением типа double.
### Возвращаемое значение

**true**, если параметр свойства является значением типа double; иначе **false**.
## bool isFloat () const

Возвращает значение, указывающее, является ли параметр свойства значением типа float.
### Возвращаемое значение

**true**, если параметр свойства является значением типа float; иначе **false**.
## bool isInt () const

Возвращает значение, указывающее, является ли параметр свойства целым числом.
### Возвращаемое значение

**true**, если параметр свойства является целым числом; иначе **false**.
## const char * getFilter () const

Возвращает текущую строку фильтра, связанную с параметром свойства. Эта строка задаёт фильтр для значений параметров типа file, material или property, который будет использоваться в unigineeditor. Например, можно указать ".xml|.node|.txt" для фильтрации определённых типов ассетов, или указать базовый материал для отсеивания материалов, которые нельзя использовать в конкретном случае (например, чтобы избежать попытки назначить post-материал мешу).
> **Notice:** Этот атрибут доступен только для параметров типов [file](../../../api/library/common/class.property_cpp.md#PARAMETER_FILE), [material](../../../api/library/common/class.property_cpp.md#PARAMETER_MATERIAL) и [property](../../../api/library/common/class.property_cpp.md#PARAMETER_PROPERTY).


### Возвращаемое значение

Текущая строка, задающая фильтр для значений параметров типа file, material или property.
## const char * getGroup () const

Возвращает текущее имя группы, к которой относится параметр свойства.
### Возвращаемое значение

Текущее имя группы, к которой относится параметр свойства.
## const char * getTooltip () const

Возвращает текущую всплывающую подсказку для параметра свойства. Этот заголовок отображается в UI UNIGINE Editor.
### Возвращаемое значение

Текущая всплывающая подсказка для параметра свойства.
## const char * getTitle () const

Возвращает текущий заголовок параметра свойства. Этот заголовок отображается в UI UNIGINE Editor.
### Возвращаемое значение

Текущий заголовок параметра свойства.
## const char * getName () const

Возвращает текущее имя параметра свойства.
### Возвращаемое значение

Текущее имя параметра свойства.
## int getType () const

Возвращает текущий идентификатор [type](../../../code/formats/property_format.md#parameter_type) параметра свойства. Получить имя типа параметра можно с помощью метода *[Property::parameterNameByType()](../../../api/library/common/class.property_cpp.md#parameterNameByType_int_cstr)*:
```cpp
Log::message("Parameter type: %s\n", prop_param->parameterNameByType(prop_param->getType()));
```


### Возвращаемое значение

Текущее одно из предопределённых значений **[PARAMETER_*](../../../api/library/common/class.property_cpp.md#PARAMETER_COLOR)**; при ошибке будет возвращено -1.
## const char * getTypeName () const

Возвращает текущее имя типа параметра свойства.
### Возвращаемое значение

Текущее имя типа параметра свойства.
## bool isOverridden () const

Возвращает текущее значение, указывающее, переопределён ли параметр свойства. Для всех типов параметров, кроме *int* и *string*, **значение считается переопределённым даже в случае присвоения ему исходного (значения по умолчанию)**. Чтобы проверить, действительно ли изменилось значение по умолчанию для параметра, рекомендуется использовать операторы и методы сравнения, поскольку в этом отношении *isOverridden()* поможет только с *int* и *string*.
### Возвращаемое значение

**true**, если параметр свойства переопределён; иначе **false**.
## bool isInherited () const

Возвращает текущее значение, указывающее, унаследован ли параметр свойства от родителя.
### Возвращаемое значение

**true**, если параметр свойства унаследован от родителя; иначе **false**.
## bool isHidden () const

Возвращает текущее значение, указывающее, является ли параметр свойства [hidden](../../../code/formats/property_format.md#parameter_hidden).
### Возвращаемое значение

**true**, если параметр свойства скрыт; иначе **false**.
## bool isExist () const

Возвращает текущее значение, указывающее, существует ли данный параметр свойства.
### Возвращаемое значение

**true**, если такой параметр свойства существует; иначе **false**.
## int getNumChildren () const

Возвращает текущее общее количество дочерних элементов параметра свойства.
### Возвращаемое значение

Текущее общее количество дочерних элементов параметра свойства.
## Ptr < PropertyParameter > getParent () const

Возвращает текущий родительский параметр свойства, если он существует.
### Возвращаемое значение

Текущий родительский параметр свойства, если он существует; иначе nullptr.
## UGUID getPropertyGUID () const

Возвращает текущий [GUID](../../../api/library/filesystem/class.uguid_cpp.md) свойства, которому принадлежит параметр.
### Возвращаемое значение

Текущий [GUID](../../../api/library/filesystem/class.uguid_cpp.md) свойства, которому принадлежит параметр.
## Ptr < Property > getProperty () const

Возвращает текущее свойство, которому принадлежит параметр.
### Возвращаемое значение

Текущее свойство, которому принадлежит параметр.
## int getID () const

Возвращает текущий идентификатор параметра свойства.
### Возвращаемое значение

Текущий идентификатор параметра свойства.
## void setSwitchItem ( int item )

Задаёт новый номер [item](../../../code/formats/property_format.md#parameter_items) [switch parameter](../../../code/formats/property_format.md#parameter_type).
Предположим, у нас объявлен параметр-переключатель свойства следующим образом:


```xml
<parameter items="red=-1,green,blue=5,yellow"/>
```


> **Notice:** Пробелы в объявлении атрибута *items* учитываются. Таким образом, **items="red=-1, green"** создаст 2 элемента: **"red"** и **" green"**


После загрузки у нас будут элементы переключателя со следующими значениями: red = -1, green = 0, blue = 5, yellow = 6.


```cpp
PropertyParameter::setValue(5); // "blue" будет выбран в соответствующем выпадающем списке в UnigineEditor
PropertyParameter::setSwitchItem(3); // "yellow" будет выбран в соответствующем выпадающем списке в UnigineEditor (поскольку это 3-й элемент, начиная с 0).

// Если в UnigineEditor выбран элемент "green":
PropertyParameter::getValueInt(); // возвращает 0, поскольку "green" соответствует значению 0.
PropertyParameter::getSwitchItem() // возвращает 1, поскольку "green" - это 1-й элемент в выпадающем списке (начиная с 0).

```


### Аргументы

- *int* **item** - Номер элемента параметра-переключателя.

## int getSwitchItem () const

Возвращает текущий номер [item](../../../code/formats/property_format.md#parameter_items) [switch parameter](../../../code/formats/property_format.md#parameter_type).
Предположим, у нас объявлен параметр-переключатель свойства следующим образом:


```xml
<parameter items="red=-1,green,blue=5,yellow"/>
```


> **Notice:** Пробелы в объявлении атрибута *items* учитываются. Таким образом, **items="red=-1, green"** создаст 2 элемента: **"red"** и **" green"**


После загрузки у нас будут элементы переключателя со следующими значениями: red = -1, green = 0, blue = 5, yellow = 6.


```cpp
PropertyParameter::setValue(5); // "blue" будет выбран в соответствующем выпадающем списке в UnigineEditor
PropertyParameter::setSwitchItem(3); // "yellow" будет выбран в соответствующем выпадающем списке в UnigineEditor (поскольку это 3-й элемент, начиная с 0).

// Если в UnigineEditor выбран элемент "green":
PropertyParameter::getValueInt(); // возвращает 0, поскольку "green" соответствует значению 0.
PropertyParameter::getSwitchItem() // возвращает 1, поскольку "green" - это 1-й элемент в выпадающем списке (начиная с 0).

```


### Возвращаемое значение

Текущий номер элемента параметра-переключателя.
## void setValueIVec4 ( const Math:: ivec4 & ivec4 )

Задаёт новое значение параметра свойства - четырёхкомпонентного вектора [ivec4](../../../api/library/math/class.ivec4_cpp.md).
### Аргументы

- *const  Math::[ivec4](../../../api/library/math/class.ivec4_cpp.md)&* **ivec4** - Значение параметра свойства.

## Math:: ivec4 getValueIVec4 () const

Возвращает текущее значение параметра свойства - четырёхкомпонентного вектора [ivec4](../../../api/library/math/class.ivec4_cpp.md).
### Возвращаемое значение

Текущее значение параметра свойства.
## void setValueIVec3 ( const Math:: ivec3 & ivec3 )

Задаёт новое значение параметра свойства - трёхкомпонентного вектора [ivec3](../../../api/library/math/class.ivec3_cpp.md).
### Аргументы

- *const  Math::[ivec3](../../../api/library/math/class.ivec3_cpp.md)&* **ivec3** - Значение параметра свойства.

## Math:: ivec3 getValueIVec3 () const

Возвращает текущее значение параметра свойства - трёхкомпонентного вектора [ivec3](../../../api/library/math/class.ivec3_cpp.md).
### Возвращаемое значение

Текущее значение параметра свойства.
## void setValueIVec2 ( const Math:: ivec2 & ivec2 )

Задаёт новое значение параметра свойства - двухкомпонентного вектора [ivec2](../../../api/library/math/class.ivec2_cpp.md).
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md)&* **ivec2** - Значение параметра свойства.

## Math:: ivec2 getValueIVec2 () const

Возвращает текущее значение параметра свойства - двухкомпонентного вектора [ivec2](../../../api/library/math/class.ivec2_cpp.md).
### Возвращаемое значение

Текущее значение параметра свойства.
## void setValueDVec4 ( const Math:: dvec4 & dvec4 )

Задаёт новое значение параметра свойства - четырёхкомпонентного вектора [dvec4](../../../api/library/math/class.dvec4_cpp.md).
### Аргументы

- *const  Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md)&* **dvec4** - Значение параметра свойства.

## Math:: dvec4 getValueDVec4 () const

Возвращает текущее значение параметра свойства - четырёхкомпонентного вектора [dvec4](../../../api/library/math/class.dvec4_cpp.md).
### Возвращаемое значение

Текущее значение параметра свойства.
## void setValueDVec3 ( const Math:: dvec3 & dvec3 )

Задаёт новое значение параметра свойства - трёхкомпонентного вектора [dvec3](../../../api/library/math/class.dvec3_cpp.md).
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md)&* **dvec3** - Значение параметра свойства.

## Math:: dvec3 getValueDVec3 () const

Возвращает текущее значение параметра свойства - трёхкомпонентного вектора [dvec3](../../../api/library/math/class.dvec3_cpp.md).
### Возвращаемое значение

Текущее значение параметра свойства.
## void setValueDVec2 ( const Math:: dvec2 & dvec2 )

Задаёт новое значение параметра свойства - двухкомпонентного вектора [dvec2](../../../api/library/math/class.dvec2_cpp.md).
### Аргументы

- *const  Math::[dvec2](../../../api/library/math/class.dvec2_cpp.md)&* **dvec2** - Значение параметра свойства.

## Math:: dvec2 getValueDVec2 () const

Возвращает текущее значение параметра свойства - двухкомпонентного вектора [dvec2](../../../api/library/math/class.dvec2_cpp.md).
### Возвращаемое значение

Текущее значение параметра свойства.
## void setValueVec2 ( const Math:: vec2 & vec2 )

Задаёт новое значение параметра свойства - двухкомпонентного вектора [vec2](../../../api/library/math/class.vec2_cpp.md).
### Аргументы

- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md)&* **vec2** - Значение параметра свойства.

## Math:: vec2 getValueVec2 () const

Возвращает текущее значение параметра свойства - двухкомпонентного вектора [vec2](../../../api/library/math/class.vec2_cpp.md).
### Возвращаемое значение

Текущее значение параметра свойства.
---

## bool isChild ( const Ptr < PropertyParameter > & parameter ) const

Возвращает значение, указывающее, является ли указанный параметр свойства дочерним для данного параметра свойства.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[PropertyParameter](../../../api/library/common/class.propertyparameter_cpp.md)> &* **parameter** - Параметр свойства для проверки.

### Возвращаемое значение

true, если указанный параметр свойства является дочерним для данного параметра свойства; иначе false.
## int findChild ( const char * name ) const

Возвращает номер дочернего параметра свойства с указанным именем.
### Аргументы

- *const char ** **name** - Имя искомого дочернего параметра свойства.

### Возвращаемое значение

Номер дочернего параметра свойства с указанным именем, если он существует; иначе -1.
## Ptr < PropertyParameter > getChild ( int num ) const

Возвращает дочерний параметр свойства по его номеру.
### Аргументы

- *int* **num** - Номер дочернего параметра свойства в диапазоне от 0 до [total number of children](#getNumChildren_int) данного параметра свойства.

### Возвращаемое значение

Умный указатель на дочерний параметр свойства, если он существует; иначе nullptr.
## Ptr < PropertyParameter > getChild ( const char * name ) const

Возвращает дочерний параметр свойства по его имени.
### Аргументы

- *const char ** **name** - Имя дочернего параметра свойства.

### Возвращаемое значение

Умный указатель на дочерний параметр свойства, если он существует; иначе nullptr.
## int getChildIndex ( const Ptr < PropertyParameter > & parameter ) const

Возвращает индекс указанного дочернего параметра свойства.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[PropertyParameter](../../../api/library/common/class.propertyparameter_cpp.md)> &* **parameter** - Дочерний параметр свойства, для которого требуется найти индекс.

### Возвращаемое значение

Индекс дочернего параметра свойства в диапазоне от 0 до [total number of children](#getNumChildren_int) данного параметра свойства, если такой дочерний элемент существует; иначе -1.
## void setValue ( int value )

Задаёт значение параметра свойства с использованием указанного целочисленного значения.
### Аргументы

- *int* **value** - Целочисленное значение для установки в качестве значения параметра свойства.

## void setValue ( float value )

Задаёт значение параметра свойства с использованием указанного значения float.
### Аргументы

- *float* **value** - Значение float для установки в качестве значения параметра свойства.

## void setValue ( double value )

Задаёт значение параметра свойства с использованием указанного значения double.
### Аргументы

- *double* **value** - Значение double для установки в качестве значения параметра свойства.

## void setValue ( const char * value )

Задаёт значение параметра свойства с использованием указанной строки.
### Аргументы

- *const char ** **value** - Строка для установки в качестве значения параметра свойства.

## void setValue ( const Math:: vec2 & value )

Задаёт значение параметра свойства с использованием указанного двухкомпонентного вектора [vec2](../../../api/library/math/class.vec2_cpp.md).
### Аргументы

- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **value** - Двухкомпонентный вектор float для установки в качестве значения параметра свойства.

## void setValue ( const Math:: vec3 & value )

Задаёт значение параметра свойства с использованием указанного трёхкомпонентного вектора [vec3](../../../api/library/math/class.vec3_cpp.md).
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **value** - Трёхкомпонентный вектор float для установки в качестве значения параметра свойства.

## void setValue ( const Math:: vec4 & value )

Задаёт значение параметра свойства с использованием указанного четырёхкомпонентного вектора [vec4](../../../api/library/math/class.vec4_cpp.md).
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **value** - Четырёхкомпонентный вектор float для установки в качестве значения параметра свойства.

## void setValue ( const Math:: dvec2 & value )

Задаёт значение параметра свойства с использованием указанного двухкомпонентного вектора [dvec2](../../../api/library/math/class.dvec2_cpp.md).
### Аргументы

- *const  Math::[dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **value** - Двухкомпонентный вектор double для установки в качестве значения параметра свойства.

## void setValue ( const Math:: dvec3 & value )

Задаёт значение параметра свойства с использованием указанного трёхкомпонентного вектора [dvec3](../../../api/library/math/class.dvec3_cpp.md).
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **value** - Трёхкомпонентный вектор double для установки в качестве значения параметра свойства.

## void setValue ( const Math:: dvec4 & value )

Задаёт значение параметра свойства с использованием указанного четырёхкомпонентного вектора [dvec4](../../../api/library/math/class.dvec4_cpp.md).
### Аргументы

- *const  Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **value** - Четырёхкомпонентный вектор double для установки в качестве значения параметра свойства.

## void setValue ( const Math:: ivec2 & value )

Задаёт значение параметра свойства с использованием указанного двухкомпонентного вектора [ivec2](../../../api/library/math/class.ivec2_cpp.md).
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **value** - Двухкомпонентный целочисленный вектор для установки в качестве значения параметра свойства.

## void setValue ( const Math:: ivec3 & value )

Задаёт значение параметра свойства с использованием указанного трёхкомпонентного вектора [ivec3](../../../api/library/math/class.ivec3_cpp.md).
### Аргументы

- *const  Math::[ivec3](../../../api/library/math/class.ivec3_cpp.md) &* **value** - Трёхкомпонентный целочисленный вектор для установки в качестве значения параметра свойства.

## void setValue ( const Math:: ivec4 & value )

Задаёт значение параметра свойства с использованием указанного четырёхкомпонентного вектора [ivec4](../../../api/library/math/class.ivec4_cpp.md).
### Аргументы

- *const  Math::[ivec4](../../../api/library/math/class.ivec4_cpp.md) &* **value** - Четырёхкомпонентный целочисленный вектор для установки в качестве значения параметра свойства.

## void setValue ( const UGUID & value )

Задаёт значение параметра свойства с использованием указанного значения [UGUID](../../../api/library/filesystem/class.uguid_cpp.md).
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **value** - Значение [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) для установки в качестве значения параметра свойства.

## void setValue ( const Ptr < Node > & value )

Задаёт значение параметра свойства с использованием указанного [Node](../../../api/library/nodes/class.node_cpp.md).
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **value** - [Node](../../../api/library/nodes/class.node_cpp.md) для установки в качестве значения параметра свойства.

## void setValue ( const Ptr < Material > & value )

Задаёт значение параметра свойства с использованием указанного [Material](../../../api/library/rendering/class.material_cpp.md).
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **value** - [Material](../../../api/library/rendering/class.material_cpp.md) для установки в качестве значения параметра свойства.

## void setValue ( const Ptr < Property > & value )

Задаёт значение параметра свойства с использованием указанного [Property](../../../api/library/common/class.property_cpp.md).
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Property](../../../api/library/common/class.property_cpp.md)> &* **value** - [Property](../../../api/library/common/class.property_cpp.md) для установки в качестве значения параметра свойства.

## bool setValue ( const Variable & value )

Задаёт значение параметра свойства с использованием указанного [Variable](../../../api/library/common/class.variable_cpp.md).
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **value** - [Variable](../../../api/library/common/class.variable_cpp.md) для установки в качестве значения параметра свойства.

### Возвращаемое значение

true, если значение свойства успешно установлено; иначе false.
## void setValue ( const Ptr < Curve2d > & value )

Задаёт значение параметра свойства с использованием указанного значения [Curve2d](../../../api/library/common/class.curve2d_cpp.md).
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Curve2d](../../../api/library/common/class.curve2d_cpp.md)> &* **value** - Значение [Curve2d](../../../api/library/common/class.curve2d_cpp.md) для установки в качестве значения параметра свойства.

## void resetValue ( )

Сбрасывает переопределённое значение параметра свойства.
> **Notice:** Сброс значения параметра свойства затрагивает все его дочерние элементы.


## Variable getValue ( ) const

Возвращает текущее значение параметра свойства как [Variable](../../../api/library/common/class.variable_cpp.md).
### Возвращаемое значение

Значение параметра свойства.
## bool hasSliderMinValue ( ) const

Возвращает значение, указывающее, задано ли минимальное значение для параметра-слайдера. Параметр-слайдер — это параметр одного из следующих типов: [PARAMETER_INT](../../../api/library/common/class.property_cpp.md#PARAMETER_INT), [PARAMETER_FLOAT](../../../api/library/common/class.property_cpp.md#PARAMETER_FLOAT), [PARAMETER_DOUBLE](../../../api/library/common/class.property_cpp.md#PARAMETER_DOUBLE).
### Возвращаемое значение

true, если для параметра-слайдера задано минимальное значение; иначе false.
## bool hasSliderMaxValue ( ) const

Возвращает значение, указывающее, задано ли максимальное значение для параметра-слайдера. Параметр-слайдер — это параметр одного из следующих типов: [PARAMETER_INT](../../../api/library/common/class.property_cpp.md#PARAMETER_INT), [PARAMETER_FLOAT](../../../api/library/common/class.property_cpp.md#PARAMETER_FLOAT), [PARAMETER_DOUBLE](../../../api/library/common/class.property_cpp.md#PARAMETER_DOUBLE).
### Возвращаемое значение

true, если для параметра-слайдера задано максимальное значение; иначе false.
## const char * getSwitchItemName ( int item ) const

Возвращает имя [item](../../../code/formats/property_format.md#parameter_items) [switch parameter](../../../code/formats/property_format.md#parameter_type).
### Аргументы

- *int* **item** - Номер элемента параметра-переключателя.

### Возвращаемое значение

Имя элемента параметра-переключателя с указанным номером.
## int getSwitchItemValue ( int item ) const

Возвращает значение [item](../../../code/formats/property_format.md#parameter_items) [switch parameter](../../../code/formats/property_format.md#parameter_type) с указанным номером.
### Аргументы

- *int* **item** - Номер элемента параметра-переключателя.

### Возвращаемое значение

Значение элемента параметра-переключателя с указанным номером.
## const char * getValueFile ( bool fast = 0 ) const

Возвращает текущее значение [file parameter](../../../code/formats/property_format.md#parameter_type).
### Аргументы

- *bool* **fast** - true, чтобы использовать указанное число как индекс в пользовательском вспомогательном кэше параметров; иначе false.

### Возвращаемое значение

Текущее значение параметра файла в зависимости от [flags](../../../code/formats/property_format.md#parameter_flags), заданных для параметра:
```cpp
// flags = "asset"
setValueFile("guid://asset_guid"); 		// getValueFile() -> asset_path
setValueFile("guid://runtime_guid");	// getValueFile() -> asset_path
setValueFile("asset_path");				// getValueFile() -> asset_path
setValueFile("runtime_path");			// getValueFile() -> asset_path

// flags = "runtime" - default
setValueFile("guid://asset_guid"); 		// getValueFile() -> runtime_path
setValueFile("guid://runtime_guid");	// getValueFile() -> runtime_path
setValueFile("asset_path");				// getValueFile() -> runtime_path
setValueFile("runtime_path");			// getValueFile() -> runtime_path

// flags = "abspath"
setValueFile(file_path);				// getValueFile() -> file_path

```


> **Notice:** Чтобы получить GUID файла, используйте метод [getValueGUID()](#getValueGUID_UGUID).


## const char * getValueFile ( ) const

Возвращает текущее значение [file parameter](../../../code/formats/property_format.md#parameter_type).
### Возвращаемое значение

Текущее значение параметра файла
## bool getFileIsAsset ( ) const

Возвращает значение, указывающее, хранит ли параметр файла ссылку на файл ассета.
### Возвращаемое значение

true, если параметр файла хранит ссылку на файл ассета; иначе false.
## bool getFileIsRuntime ( ) const

Возвращает значение, указывающее, хранит ли параметр файла ссылку на runtime-файл.
### Возвращаемое значение

true, если параметр файла хранит ссылку на runtime-файл; иначе false.
## bool getFileIsAbsPath ( ) const

Возвращает значение, указывающее, хранит ли параметр файла абсолютный путь к файлу.
### Возвращаемое значение

true, если параметр файла хранит абсолютный путь к файлу; иначе false.
## bool isFileExist ( ) const

Возвращает значение, указывающее, существует ли файл, соответствующий параметру свойства.
### Возвращаемое значение

true, если файл, соответствующий параметру свойства, существует; иначе false.
## bool saveState ( const Ptr < Stream > & stream ) const

Сохраняет данные параметра свойства в бинарный поток.
**Пример** использования методов saveState() и [restoreState()](#restoreState_Stream_int_int):


```cpp
// создаём параметр свойства и задаём его состояние
propertyparam1->setValueInt(7);

// сохраняем состояние
BlobPtr blob_state = Blob::create();
propertyparam1->saveState(blob_state);

// изменяем состояние
propertyparam1->setValueInt(4);

// восстанавливаем состояние
blob_state->seekSet(0);				// возвращаем каретку в начало blob
propertyparam1->restoreState(blob_state, 0);

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, в который будут сохранены данные параметра свойства.

### Возвращаемое значение

true, если данные параметра свойства успешно сохранены; иначе false.
## bool restoreState ( const Ptr < Stream > & stream , int restore_mode = 0 )

Восстанавливает данные параметра свойства из бинарного потока в указанном режиме.
**Пример** использования методов [saveState()](#saveState_Stream_int) и restoreState():


```cpp
// создаём параметр свойства и задаём его состояние
propertyparam1->setValueInt(7);

// сохраняем состояние
BlobPtr blob_state = Blob::create();
propertyparam1->saveState(blob_state);

// изменяем состояние
propertyparam1->setValueInt(4);

// восстанавливаем состояние
blob_state->seekSet(0);				// возвращаем каретку в начало blob
propertyparam1->restoreState(blob_state, 0);

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, в котором хранятся сохранённые данные параметра свойства.
- *int* **restore_mode** - Режим восстановления. Одно из значений [Property::RESTORE_MODE_*](../../../api/library/common/class.property_cpp.md#RESTORE_MODE_MERGE). Значение по умолчанию — [Property::RESTORE_MODE_REPLACE](../../../api/library/common/class.property_cpp.md#RESTORE_MODE_REPLACE).

### Возвращаемое значение

true, если данные параметра свойства успешно восстановлены; иначе false.
## bool isValuePropertyInternal ( ) const

Проверяет, установлен ли [flag](../../../code/formats/property_format.md#parameter_flags) параметра свойства как internal (flags="internal"). Если параметр внутренний, ему можно назначить только свойство, уже назначенное какому-либо узлу. Если параметр свойства не внутренний, ему можно назначить свойство из Asset Browser.
### Возвращаемое значение

true, если флаг параметра свойства установлен как "Internal"; иначе false.
## bool isValueFitFilter ( const Ptr < Node > & value ) const

Проверяет, соответствует ли тип указанного узла текущему [filter](../../../code/formats/property_format.md#parameter_filter) параметра свойства.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **value** - Значение для проверки.

### Возвращаемое значение

true, если узел соответствует фильтру; иначе false.
## bool isValueFitFilter ( const Ptr < Property > & value ) const

Проверяет, соответствует ли указанное свойство текущему [filter](../../../code/formats/property_format.md#parameter_filter) параметра свойства.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Property](../../../api/library/common/class.property_cpp.md)> &* **value** - Значение для проверки.

### Возвращаемое значение

true, если свойство соответствует фильтру; иначе false.
## bool isValueFitFilter ( const Ptr < Material > & value ) const

Проверяет, соответствует ли указанный материал текущему [filter](../../../code/formats/property_format.md#parameter_filter) параметра свойства.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **value** - Значение для проверки.

### Возвращаемое значение

true, если материал соответствует фильтру; иначе false.
## bool isValueFitFilter ( const UGUID & value ) const

Проверяет, соответствует ли указанный GUID текущему [filter](../../../code/formats/property_format.md#parameter_filter) параметра свойства.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **value** - Значение для проверки.

### Возвращаемое значение

true, если GUID соответствует фильтру; иначе false.
## bool isValuePropertyInterface ( ) const

Проверяет, определён ли [flag](../../../code/formats/property_format.md#parameter_flags) параметра свойства как тип interface (flags="interface"), позволяющий назначать ему любой компонент, реализующий требуемый интерфейс.
> **Notice:** Интерфейсы можно использовать только в компонентной системе на C#. Подробнее см. статью [C# Interfaces and Abstract Classes.](../../../code/csharp/interfaces_and_abstract_classes.md).

### Возвращаемое значение

true, если флаг параметра свойства установлен как "interface"; иначе false.
