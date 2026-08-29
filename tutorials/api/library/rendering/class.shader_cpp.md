# Unigine.Shader Class (CPP)

**Header:** #include <UnigineShader.h>


Интерфейс для работы с шейдерами. Здесь *shader* - это шейдерная программа, которая может содержать несколько подшейдеров - vertex, fragment, geometry и т.д.


Этот класс позволяет компилировать эти шейдерные программы, задавать значения параметров и привязывать графический контекст.


Вы также можете задавать параметры (или массивы параметров) шейдерным программам.


### Пример использования


Этот пример демонстрирует, как использовать пользовательские подшейдеры (UUSL, HLSL) для рендеринга постэффекта.


Добавьте следующий код в файл `AppWorldLogic.cpp`.


```cpp
#include <UnigineFfp.h>

using namespace Unigine;

ShaderPtr shader;

// EventConnections class instance to manage event subscriptions
EventConnections econnections;

//// implementing the event handler to render the result
void endscreen_event_handler()
{
	// Getting a post RenderTarget to render to
	const auto rt = Renderer::getPostRenderTarget();
	rt->unbindAll();
	rt->bindColorTexture(0, Renderer::getTextureColor());
	rt->enable();

	// Binding our shader and rendering the screen via FFP
	shader->bind();
	// setting the fill color to magenta
	shader->setParameterFloat4("color", Math::vec4(1.0f, 0.0f, 1.0f, 1.0f));
	shader->flushParameters();
	Ffp::renderScreen();

	// Unbinding the shader and disabling the target
	shader->unbind();

	rt->disable();
}

int AppWorldLogic::init()
{

	// String containing the source code of the vertex shader (HLSL, UUSL)
	const auto vertex_shader = R"foo(
	float4 main(float2 pos : POSITION) : SV_POSITION
	{
		return float4(pos, 0.0f, 1.0f);
	}
	)foo";

	// String containing the source code of the fragment shader (HLSL, UUSL)
	const auto fragment_shader = R"foo(
	cbuffer vars : register(b0)
	{
		float4 color;
	};

	float4 main(float4 fragCoord : SV_POSITION) : SV_TARGET
	{
		return color;
	}
	)foo";

	shader = Shader::create();

	// Compiling a shader with the vertex and fragment subshaders
	shader->compileVertFrag(vertex_shader, fragment_shader, "");

	// Or you can call the "compile()" function as follows - the result will be the same
	// shader->compile(vertex_shader,nullptr,fragment_shader,nullptr,nullptr,nullptr,"");

	// Adding a render EndScreen event to render the result as a post-effect
	Render::getEventEndScreen().connect(econnections, endscreen_event_handler);

	return 1;
}

int AppWorldLogic::shutdown()
{
	// removing all event subscriptions somewhere on shutdown
	econnections.disconnectAll();

	return 1;
}


```


## Shader Class

### Перечисления

## WARNING_MODE

Режим предупреждений для компилятора шейдеров.
| Name | Description |
|---|---|
| **WARNING_MODE_DISABLE** = 0 | Все предупреждения компиляции шейдеров игнорируются. Использование этого режима не рекомендуется, так как это может привести к сбоям драйвера и ОС, поэтому используйте его на свой страх и риск. |
| **WARNING_MODE_SOFT** = 1 | Все предупреждения компиляции шейдеров выводятся в лог, но игнорируются. Этот режим можно использовать, если вы проверили и абсолютно уверены, что предупреждения не вызывают сбоев драйвера или ОС. |
| **WARNING_MODE_HARD** = 2 | Все предупреждения рассматриваются как ошибки. Этот уровень используется по умолчанию. |

## SUB_SHADER

| Name | Description |
|---|---|
| **SUB_SHADER_VERTEX** = 0 | Вершинный подшейдер. |
| **SUB_SHADER_CONTROL** = 1 | Управляющий подшейдер. |
| **SUB_SHADER_EVALUATE** = 2 | Оценочный подшейдер. |
| **SUB_SHADER_GEOMETRY** = 3 | Геометрический подшейдер. |
| **SUB_SHADER_FRAGMENT** = 4 | Фрагментный подшейдер. |
| **SUB_SHADER_COMPUTE** = 5 | Вычислительный подшейдер. |

### Методы класса

## void setIEEEStrictness ( bool ieeestrictness )

Задаёт новое значение, указывающее, принуждает ли компилятор шейдеров к строгой компиляции по стандарту IEEE.
> **Notice:** Доступно только для DirectX.

### Аргументы

- *bool* **ieeestrictness** - **true**, чтобы включить принудительную строгую компиляцию по стандарту IEEE компилятором шейдеров; **false** - чтобы отключить её.

## bool isIEEEStrictness () const

Возвращает текущее значение, указывающее, принуждает ли компилятор шейдеров к строгой компиляции по стандарту IEEE.
> **Notice:** Доступно только для DirectX.

### Возвращаемое значение

**true**, если принудительная строгая компиляция по стандарту IEEE компилятором шейдеров включена; иначе **false**.
## void setDisableExport ( bool export )

Задаёт новое значение, указывающее, отключён ли [export to a file](../../../code/uusl/index.md#uusl_debug). По умолчанию UNIGINE включает экспорт шейдерной программы в файл (например, для целей отладки). Файлы шейдеров создаются на нативном языке графического API (*Direct3D* - расширение `.hlsl`).
### Аргументы

- *bool* **export** - **true**, чтобы включить отключение экспорта шейдера в файл; **false** - чтобы отключить это.

## bool isDisableExport () const

Возвращает текущее значение, указывающее, отключён ли [export to a file](../../../code/uusl/index.md#uusl_debug). По умолчанию UNIGINE включает экспорт шейдерной программы в файл (например, для целей отладки). Файлы шейдеров создаются на нативном языке графического API (*Direct3D* - расширение `.hlsl`).
### Возвращаемое значение

**true**, если отключение экспорта шейдера в файл включено; иначе **false**.
## void setDisableCompileError ( bool error )

Задаёт новое значение, указывающее, отключён ли вывод ошибок компиляции шейдера.
### Аргументы

- *bool* **error** - **true**, чтобы включить отключение вывода ошибок компиляции шейдера; **false** - чтобы отключить это.

## bool isDisableCompileError () const

Возвращает текущее значение, указывающее, отключён ли вывод ошибок компиляции шейдера.
### Возвращаемое значение

**true**, если отключение вывода ошибок компиляции шейдера включено; иначе **false**.
## void setWarningMode ( Shader::WARNING_MODE mode )

Задаёт новый режим предупреждений для компилятора шейдеров. Можно выбрать режимы от самого низкого (все предупреждения компиляции шейдеров игнорируются) до самого высокого уровня, когда предупреждения рассматриваются как ошибки. По умолчанию используется *самый высокий* уровень, установка *более низких* уровней может привести к сбоям драйвера и ОС, поэтому используйте их на свой страх и риск. Уровень *[soft](#WARNING_MODE_SOFT)* можно использовать, если вы проверили и абсолютно уверены, что предупреждения не вызывают сбоев.
> **Notice:** Доступно только для DirectX.

### Аргументы

- *[Shader::WARNING_MODE](../../../api/library/rendering/class.shader_cpp.md#WARNING_MODE)* **mode** - Режим предупреждений.

## Shader::WARNING_MODE getWarningMode () const

Возвращает текущий режим предупреждений для компилятора шейдеров. Можно выбрать режимы от самого низкого (все предупреждения компиляции шейдеров игнорируются) до самого высокого уровня, когда предупреждения рассматриваются как ошибки. По умолчанию используется *самый высокий* уровень, установка *более низких* уровней может привести к сбоям драйвера и ОС, поэтому используйте их на свой страх и риск. Уровень *[soft](#WARNING_MODE_SOFT)* можно использовать, если вы проверили и абсолютно уверены, что предупреждения не вызывают сбоев.
> **Notice:** Доступно только для DirectX.

### Возвращаемое значение

Текущий режим предупреждений.
## void setOptimizationLevel ( int level )

Задаёт новый уровень оптимизации для компилятора шейдеров. Одно из следующих значений:
- 0 - Указывает компилятору пропускать шаги оптимизации при генерации кода.
- 1 - Указывает компилятору использовать самый низкий уровень оптимизации. На этом уровне компилятор может создавать более медленный код, но делает это быстрее.
- 2 - Указывает компилятору использовать второй по величине низкий уровень оптимизации.
- 3 - Указывает компилятору использовать второй по величине высокий уровень оптимизации.
- 4 - Указывает компилятору использовать самый высокий уровень оптимизации. На этом уровне компилятор создаёт наилучший возможный код, но это может занять значительно больше времени.


> **Notice:** Доступно только для DirectX.


### Аргументы

- *int* **level** - Уровень оптимизации.

## int getOptimizationLevel () const

Возвращает текущий уровень оптимизации для компилятора шейдеров. Одно из следующих значений:
- 0 - Указывает компилятору пропускать шаги оптимизации при генерации кода.
- 1 - Указывает компилятору использовать самый низкий уровень оптимизации. На этом уровне компилятор может создавать более медленный код, но делает это быстрее.
- 2 - Указывает компилятору использовать второй по величине низкий уровень оптимизации.
- 3 - Указывает компилятору использовать второй по величине высокий уровень оптимизации.
- 4 - Указывает компилятору использовать самый высокий уровень оптимизации. На этом уровне компилятор создаёт наилучший возможный код, но это может занять значительно больше времени.


> **Notice:** Доступно только для DirectX.


### Возвращаемое значение

Текущий уровень оптимизации.
## void setDisableCompileCache ( bool cache )

Задаёт новое значение, указывающее, отключён ли кэш компиляции для шейдера.
### Аргументы

- *bool* **cache** - **true**, чтобы включить отключение кэша компиляции для шейдера; **false** - чтобы отключить это.

## bool isDisableCompileCache () const

Возвращает текущее значение, указывающее, отключён ли кэш компиляции для шейдера.
### Возвращаемое значение

**true**, если отключение кэша компиляции для шейдера включено; иначе **false**.
---

## static ShaderPtr create ( )

Конструктор шейдера по умолчанию.
## static ShaderPtr create ( const char * name )

Конструктор шейдера. Загружает все существующие шейдеры с заданным именем.
### Аргументы

- *const char ** **name** - Имя шейдера.

## static ShaderPtr create ( const char * name , const char * defines )

Конструктор шейдера. Загружает все существующие шейдеры с заданным именем.
### Аргументы

- *const char ** **name** - Имя шейдера.
- *const char ** **defines** - Пользовательские определения.

## static ShaderPtr create ( const char * vertex , const char * fragment , const char * defines )

Конструктор шейдера. Загружает только вершинный и фрагментный подшейдеры с заданными именами.
### Аргументы

- *const char ** **vertex** - Имя или исходный код вершинного подшейдера.
- *const char ** **fragment** - Имя или исходный код фрагментного подшейдера.
- *const char ** **defines** - Пользовательские определения.

## void bind ( ) const

Привязывает шейдер.
## void clear ( ) const

Очищает шейдер.
## bool compile ( const char * vertex , const char * geometry , const char * fragment , const char * compute , const char * control , const char * evaluate , const char * defines = "" , unsigned long long key_cache = 0 )

Компилирует шейдер с указанными подшейдерами. Чтобы пропустить подшейдер, передайте nullptr вместо аргумента. В зависимости от типов подшейдеров, к аргументу *defines* автоматически добавляются дополнительные значения: *VERTEX, CONTROL, EVALUATE, GEOMETRY, FRAGMENT*.
### Аргументы

- *const char ** **vertex** - Путь к вершинному подшейдеру.
- *const char ** **geometry** - Путь к геометрическому подшейдеру.
- *const char ** **fragment** - Путь к фрагментному подшейдеру.
- *const char ** **compute** - Путь к вычислительному подшейдеру.
- *const char ** **control** - Путь к управляющему подшейдеру.
- *const char ** **evaluate** - Путь к оценочному подшейдеру.
- *const char ** **defines** - Пользовательские определения (например, "OPENGL", "DIRECT3D11" или любые другие).
- *unsigned long long* **key_cache** - Кэш ключа.

### Возвращаемое значение

**true**, если шейдер успешно скомпилирован; иначе **false**.
## void destroy ( ) const

Уничтожает шейдер.
## int findParameter ( const char * name )

Находит параметр шейдера.
### Аргументы

- *const char ** **name** - Быстрый идентификатор.

### Возвращаемое значение

Идентификатор параметра, если найден; иначе **-1**.
## void flushParameters ( ) const

Выполняет flush параметров шейдера.
## void unbind ( ) const

Отвязывает шейдер.
## void setParameterFloat ( int id , float value )

Задаёт значение float-параметра шейдера по указанному идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *float* **value** - Значение параметра.

## void setParameterFloat ( const char * name , float value )

Задаёт значение float-параметра шейдера по указанному имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *float* **value** - Значение параметра.

## void setParameterFloat2 ( int id , const Math:: vec2 & value )

Задаёт значение параметра шейдера для переменной float2.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **value** - Значение параметра.

## void setParameterFloat2 ( const char * name , const Math:: vec2 & value )

Задаёт значение параметра шейдера для переменной float2.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **value** - Значение параметра.

## void setParameterFloat3 ( int id , const Math:: vec3 & value )

Задаёт значение параметра шейдера для переменной float3.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **value** - Значение параметра.

## void setParameterFloat3 ( const char * name , const Math:: vec3 & value )

Задаёт значение параметра шейдера для переменной float3 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **value** - Значение параметра.

## void setParameterFloat4 ( int id , const Math:: vec4 & value )

Задаёт значение параметра шейдера для переменной float4.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **value** - Значение параметра.

## void setParameterFloat4 ( const char * name , const Math:: vec4 & value )

Задаёт значение параметра шейдера для переменной float4 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **value** - Значение параметра.

## void setParameterFloat3x3 ( int id , const Math:: mat3 & value )

Задаёт значение параметра шейдера для переменной float3x3.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const  Math::[mat3](../../../api/library/math/class.mat3_cpp.md) &* **value** - Значение параметра.

## void setParameterFloat3x3 ( const char * name , const Math:: mat3 & value )

Задаёт значение параметра шейдера для переменной float3x3 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[mat3](../../../api/library/math/class.mat3_cpp.md) &* **value** - Значение параметра.

## void setParameterFloat4x4 ( int id , const Math:: mat4 & value )

Задаёт значение параметра шейдера для переменной float4x4.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **value** - Значение параметра.

## void setParameterFloat4x4 ( const char * name , const Math:: mat4 & value )

Задаёт значение параметра шейдера для переменной float4x4 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **value** - Значение параметра.

## void setParameterInt ( int id , int value )

Задаёт значение параметра шейдера для переменной int.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *int* **value** - Значение параметра.

## void setParameterInt ( const char * name , int value )

Задаёт значение параметра шейдера для переменной int по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *int* **value** - Значение параметра.

## void setParameterInt2 ( int id , const Math:: ivec2 & value )

Задаёт значение параметра шейдера для переменной int2.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **value** - Значение параметра.

## void setParameterInt2 ( const char * name , const Math:: ivec2 & value )

Задаёт значение параметра шейдера для переменной int2 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **value** - Значение параметра.

## void setParameterInt3 ( int id , const Math:: ivec3 & value )

Задаёт значение параметра шейдера для переменной int3.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const  Math::[ivec3](../../../api/library/math/class.ivec3_cpp.md) &* **value** - Значение параметра.

## void setParameterInt3 ( const char * name , const Math:: ivec3 & value )

Задаёт значение параметра шейдера для переменной int3 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[ivec3](../../../api/library/math/class.ivec3_cpp.md) &* **value** - Значение параметра.

## void setParameterInt4 ( int id , const Math:: ivec4 & value )

Задаёт значение параметра шейдера для переменной int4.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const  Math::[ivec4](../../../api/library/math/class.ivec4_cpp.md) &* **value** - Значение параметра.

## void setParameterInt4 ( const char * name , const Math:: ivec4 & value )

Задаёт значение параметра шейдера для переменной int4 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[ivec4](../../../api/library/math/class.ivec4_cpp.md) &* **value** - Значение параметра.

## void setParameterDouble ( int id , double value )

Задаёт значение параметра шейдера для переменной double.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *double* **value** - Значение параметра.

## void setParameterDouble ( const char * name , double value )

Задаёт значение параметра шейдера для переменной double по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *double* **value** - Значение параметра.

## void setParameterDouble2 ( int id , const Math:: dvec2 & value )

Задаёт значение параметра шейдера для переменной double2.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const  Math::[dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **value** - Значение параметра.

## void setParameterDouble2 ( const char * name , const Math:: dvec2 & value )

Задаёт значение параметра шейдера для переменной double2 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **value** - Значение параметра.

## void setParameterDouble3 ( int id , const Math:: dvec3 & value )

Задаёт значение параметра шейдера для переменной double3.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **value** - Значение параметра.

## void setParameterDouble3 ( const char * name , const Math:: dvec3 & value )

Задаёт значение параметра шейдера для переменной double3 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **value** - Значение параметра.

## void setParameterDouble4 ( int id , const Math:: dvec4 & value )

Задаёт значение параметра шейдера для переменной double4.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const  Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **value** - Значение параметра.

## void setParameterDouble4 ( const char * name , const Math:: dvec4 & value )

Задаёт значение параметра шейдера для переменной double4 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **value** - Значение параметра.

## void setParameterDouble4x4 ( int id , const Math:: dmat4 & value )

Задаёт значение параметра шейдера для переменной double4x4.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const  Math::[dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **value** - Значение параметра.

## void setParameterDouble4x4 ( const char * name , const Math:: dmat4 & value )

Задаёт значение параметра шейдера для переменной double4x4 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **value** - Значение параметра.

## void setParameterScalar ( int id , Math::Scalar value )

Задаёт значение параметра шейдера для переменной scalar по идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *Math::Scalar* **value** - Значение параметра.

## void setParameterScalar ( const char * name , Math::Scalar value )

Задаёт значение параметра шейдера для переменной scalar по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *Math::Scalar* **value** - Значение параметра.

## void setParameterScalar2 ( int id , const Math:: Vec2 & value )

Задаёт значение параметра шейдера для переменной scalar2 по идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const  Math::[Vec2](../../../api/library/math/class.vec2_cpp.md) &* **value** - Значение параметра.

## void setParameterScalar2 ( const char * name , const Math:: Vec2 & value )

Задаёт значение параметра шейдера для переменной scalar2 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[Vec2](../../../api/library/math/class.vec2_cpp.md) &* **value** - Значение параметра.

## void setParameterScalar3 ( int id , const Math:: Vec3 & value )

Задаёт значение параметра шейдера для переменной scalar3 по идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **value** - Значение параметра.

## void setParameterScalar3 ( const char * name , const Math:: Vec3 & value )

Задаёт значение параметра шейдера для переменной scalar3 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **value** - Значение параметра.

## void setParameterScalar4 ( int id , const Math:: Vec4 & value )

Задаёт значение параметра шейдера для переменной scalar4 по идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const  Math::[Vec4](../../../api/library/math/class.vec4_cpp.md) &* **value** - Значение параметра.

## void setParameterScalar4 ( const char * name , const Math:: Vec4 & value )

Задаёт значение параметра шейдера для переменной scalar4 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[Vec4](../../../api/library/math/class.vec4_cpp.md) &* **value** - Значение параметра.

## void setParameterArrayFloat ( int id , const float * value , int num_elements )

Задаёт значения параметра-массива шейдера float по идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const float ** **value** - Значение параметра.
- *int* **num_elements** - Количество элементов массива.

## void setParameterArrayFloat ( const char * name , const float * value , int num_elements )

Задаёт значения параметра-массива шейдера float по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const float ** **value** - Значение параметра.
- *int* **num_elements** - Количество элементов массива.

## void setParameterArrayFloat ( int id , const Vector <float> & value )

Задаёт значения параметра-массива шейдера float по идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<float> &* **value** - Значение параметра.

## void setParameterArrayFloat ( const char * name , const Vector <float> & value )

Задаёт значения параметра-массива шейдера float по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<float> &* **value** - Значение параметра.

## void setParameterArrayFloat2 ( int id , const Math:: vec2 * value , int num_elements )

Задаёт значения параметра-массива шейдера float2 по идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) ** **value** - Значение параметра.
- *int* **num_elements** - Количество элементов массива.

## void setParameterArrayFloat2 ( const char * name , const Math:: vec2 * value , int num_elements )

Задаёт значения параметра-массива шейдера float2 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) ** **value** - Значение параметра.
- *int* **num_elements** - Количество элементов массива.

## void setParameterArrayFloat2 ( int id , const Vector < Math:: vec2 > & value )

Задаёт значения параметра-массива шейдера float2 по идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[vec2](../../../api/library/math/class.vec2_cpp.md)> &* **value** - Значение параметра.

## void setParameterArrayFloat2 ( const char * name , const Vector < Math:: vec2 > & value )

Задаёт значения параметра-массива шейдера float2 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[vec2](../../../api/library/math/class.vec2_cpp.md)> &* **value** - Значение параметра.

## void setParameterArrayFloat4 ( int id , const Math:: vec4 * value , int num_elements )

Задаёт значения параметра-массива шейдера float4 по идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) ** **value** - Значение параметра.
- *int* **num_elements** - Количество элементов массива.

## void setParameterArrayFloat4 ( const char * name , const Math:: vec4 * value , int num_elements )

Задаёт значения параметра-массива шейдера float4 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) ** **value** - Значение параметра.
- *int* **num_elements** - Количество элементов массива.

## void setParameterArrayFloat4 ( int id , const Vector < Math:: vec4 > & value )

Задаёт значения параметра-массива шейдера float4 по идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[vec4](../../../api/library/math/class.vec4_cpp.md)> &* **value** - Значение параметра.

## void setParameterArrayFloat4 ( const char * name , const Vector < Math:: vec4 > & value )

Задаёт значения параметра-массива шейдера float4 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[vec4](../../../api/library/math/class.vec4_cpp.md)> &* **value** - Значение параметра.

## void setParameterArrayFloat4x4 ( int id , const Math:: mat4 * value , int num_elements )

Задаёт значения параметра-массива шейдера float4x4 по идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) ** **value** - Значение параметра.
- *int* **num_elements** - Количество элементов массива.

## void setParameterArrayFloat4x4 ( const char * name , const Math:: mat4 * value , int num_elements )

Задаёт значения параметра-массива шейдера float4x4 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) ** **value** - Значение параметра.
- *int* **num_elements** - Количество элементов массива.

## void setParameterArrayFloat4x4 ( int id , const Vector < Math:: mat4 > & value )

Задаёт значения параметра-массива шейдера float4x4 по идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[mat4](../../../api/library/math/class.mat4_cpp.md)> &* **value** - Значение параметра.

## void setParameterArrayFloat4x4 ( const char * name , const Vector < Math:: mat4 > & value )

Задаёт значения параметра-массива шейдера float4x4 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[mat4](../../../api/library/math/class.mat4_cpp.md)> &* **value** - Значение параметра.

## void setParameterArrayInt ( int id , const int * value , int num_elements )

Задаёт значения параметра-массива шейдера integer по идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const int ** **value** - Значение параметра.
- *int* **num_elements** - Количество элементов массива.

## void setParameterArrayInt ( const char * name , const int * value , int num_elements )

Задаёт значения параметра-массива шейдера integer по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const int ** **value** - Значение параметра.
- *int* **num_elements** - Количество элементов массива.

## void setParameterArrayInt ( int id , const Vector <int> & value )

Задаёт значения параметра-массива шейдера integer по идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **value** - Значение параметра.

## void setParameterArrayInt ( const char * name , const Vector <int> & value )

Задаёт значения параметра-массива шейдера integer по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **value** - Значение параметра.

## void setParameterArrayInt2 ( int id , const Math:: ivec2 * value , int num_elements )

Задаёт значения параметра-массива шейдера int2 по идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) ** **value** - Значение параметра.
- *int* **num_elements** - Количество элементов массива.

## void setParameterArrayInt2 ( const char * name , const Math:: ivec2 * value , int num_elements )

Задаёт значения параметра-массива шейдера int2 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) ** **value** - Значение параметра.
- *int* **num_elements** - Количество элементов массива.

## void setParameterArrayInt2 ( int id , const Vector < Math:: ivec2 > & value )

Задаёт значения параметра-массива шейдера int2 по идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md)> &* **value** - Значение параметра.

## void setParameterArrayInt2 ( const char * name , const Vector < Math:: ivec2 > & value )

Задаёт значения параметра-массива шейдера int2 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md)> &* **value** - Значение параметра.

## void setParameterArrayInt4 ( int id , const Math:: ivec4 * value , int num_elements )

Задаёт значения параметра-массива шейдера int4 по идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const  Math::[ivec4](../../../api/library/math/class.ivec4_cpp.md) ** **value** - Значение параметра.
- *int* **num_elements** - Количество элементов массива.

## void setParameterArrayInt4 ( const char * name , const Math:: ivec4 * value , int num_elements )

Задаёт значения параметра-массива шейдера int4 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[ivec4](../../../api/library/math/class.ivec4_cpp.md) ** **value** - Значение параметра.
- *int* **num_elements** - Количество элементов массива.

## void setParameterArrayInt4 ( int id , const Vector < Math:: ivec4 > & value )

Задаёт значения параметра-массива шейдера int4 по идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[ivec4](../../../api/library/math/class.ivec4_cpp.md)> &* **value** - Значение параметра.

## void setParameterArrayInt4 ( const char * name , const Vector < Math:: ivec4 > & value )

Задаёт значения параметра-массива шейдера int4 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[ivec4](../../../api/library/math/class.ivec4_cpp.md)> &* **value** - Значение параметра.

## void setParameterArrayDouble ( int id , const double * value , int num_elements )

Задаёт значение параметра-массива шейдера double по идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const double ** **value** - Значение параметра.
- *int* **num_elements** - Количество элементов массива.

## void setParameterArrayDouble ( const char * name , const double * value , int num_elements )

Задаёт значение параметра-массива шейдера double по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const double ** **value** - Значение параметра.
- *int* **num_elements** - Количество элементов массива.

## void setParameterArrayDouble ( int id , const Vector <double> & value )

Задаёт значение параметра-массива шейдера double по идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<double> &* **value** - Значение параметра.

## void setParameterArrayDouble ( const char * name , const Vector <double> & value )

Задаёт значение параметра-массива шейдера double по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<double> &* **value** - Значение параметра.

## void setParameterArrayDouble2 ( int id , const Math:: dvec2 * value , int num_elements )

Задаёт значение параметра-массива шейдера double2 по идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const  Math::[dvec2](../../../api/library/math/class.dvec2_cpp.md) ** **value** - Значение параметра.
- *int* **num_elements** - Количество элементов массива.

## void setParameterArrayDouble2 ( const char * name , const Math:: dvec2 * value , int num_elements )

Задаёт значение параметра-массива шейдера double2 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[dvec2](../../../api/library/math/class.dvec2_cpp.md) ** **value** - Значение параметра.
- *int* **num_elements** - Количество элементов массива.

## void setParameterArrayDouble2 ( int id , const Vector < Math:: dvec2 > & value )

Задаёт значение параметра-массива шейдера double2 по идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[dvec2](../../../api/library/math/class.dvec2_cpp.md)> &* **value** - Значение параметра.

## void setParameterArrayDouble2 ( const char * name , const Vector < Math:: dvec2 > & value )

Задаёт значение параметра-массива шейдера double2 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[dvec2](../../../api/library/math/class.dvec2_cpp.md)> &* **value** - Значение параметра.

## void setParameterArrayDouble4 ( int id , const Math:: dvec4 * value , int num_elements )

Задаёт значение параметра-массива шейдера double4 по идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const  Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) ** **value** - Значение параметра.
- *int* **num_elements** - Количество элементов массива.

## void setParameterArrayDouble4 ( const char * name , const Math:: dvec4 * value , int num_elements )

Задаёт значение параметра-массива шейдера double4 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) ** **value** - Значение параметра.
- *int* **num_elements** - Количество элементов массива.

## void setParameterArrayDouble4 ( int id , const Vector < Math:: dvec4 > & value )

Задаёт значение параметра-массива шейдера double4 по идентификатору параметра.
### Аргументы

- *int* **id** - Идентификатор параметра.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md)> &* **value** - Значение параметра.

## void setParameterArrayDouble4 ( const char * name , const Vector < Math:: dvec4 > & value )

Задаёт значение параметра-массива шейдера double4 по имени параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md)> &* **value** - Значение параметра.

## bool compileCompute ( const char * compute , const char * defines = "" , unsigned long long key_cache = 0 )

Компилирует шейдер с указанным вычислительным подшейдером. Дополнительное значение *COMPUTE* автоматически добавляется к аргументу *defines*. Эта функция аналогична функции *[compile](#compile_cstr_cstr_cstr_cstr_cstr_cstr_cstr_ullong_int)()*, вызванной только с аргументом *compute*.
### Аргументы

- *const char ** **compute** - Путь к вычислительному подшейдеру.
- *const char ** **defines** - Пользовательские определения (например, "OPENGL", "DIRECT3D11" или любые другие).
- *unsigned long long* **key_cache** - Кэш ключа.

### Возвращаемое значение

true, если шейдер успешно скомпилирован; иначе false.
## bool compileVertFrag ( const char * vertex , const char * fragment , const char * defines = "" , unsigned long long key_cache = 0 )

Компилирует шейдер с указанными вершинным и фрагментным подшейдерами. Дополнительные значения *VERTEX* и *FRAGMENT* автоматически добавляются к аргументу *defines*. Эта функция аналогична функции *[compile](#compile_cstr_cstr_cstr_cstr_cstr_cstr_cstr_ullong_int)()*, вызванной только с аргументами *vertex* и *fragment*.
### Аргументы

- *const char ** **vertex** - Путь к вершинному подшейдеру.
- *const char ** **fragment** - Путь к фрагментному подшейдеру.
- *const char ** **defines** - Пользовательские определения (например, "OPENGL", "DIRECT3D11" или любые другие).
- *unsigned long long* **key_cache** - Кэш ключа.

### Возвращаемое значение

true, если шейдер успешно скомпилирован; иначе false.
## bool compileVertGeomFrag ( const char * vertex , const char * geometry , const char * fragment , const char * defines = "" , unsigned long long key_cache = 0 )

Компилирует шейдер с указанными вершинным, геометрическим и фрагментным подшейдерами. Дополнительные значения *VERTEX*, *GEOMETRY* и *FRAGMENT* автоматически добавляются к аргументу *defines*. Эта функция аналогична функции *[compile](#compile_cstr_cstr_cstr_cstr_cstr_cstr_cstr_ullong_int)()*, вызванной только с аргументами *vertex*, *fragment* и *geometry*.
### Аргументы

- *const char ** **vertex** - Путь к вершинному подшейдеру.
- *const char ** **geometry** - Путь к геометрическому подшейдеру.
- *const char ** **fragment** - Путь к фрагментному подшейдеру.
- *const char ** **defines** - Пользовательские определения (например, "OPENGL", "DIRECT3D11" или любые другие).
- *unsigned long long* **key_cache** - Кэш ключа.

### Возвращаемое значение

true, если шейдер успешно скомпилирован; иначе false.
## bool compileShader ( const char * shader , const char * defines = "" , unsigned long long key_cache = 0 )

Компилирует шейдер, включающий подшейдеры. В зависимости от типов подшейдеров, определённых в файле шейдера, к аргументу *defines* автоматически добавляются дополнительные значения: *VERTEX, CONTROL, EVALUATE, GEOMETRY, FRAGMENT*.
### Аргументы

- *const char ** **shader** - Путь к шейдеру.
- *const char ** **defines** - Пользовательские определения (например, "OPENGL", "DIRECT3D11" или любые другие).
- *unsigned long long* **key_cache** - Кэш ключа.

### Возвращаемое значение

true, если шейдер со всеми подшейдерами успешно скомпилирован; иначе false.
## bool validateShader ( Shader::SUB_SHADER type , const char * shader , const char * defines = "" )

Проверяет шейдер (может ли он быть скомпилирован).
### Аргументы

- *[Shader::SUB_SHADER](../../../api/library/rendering/class.shader_cpp.md#SUB_SHADER)* **type** - Тип подшейдера.
- *const char ** **shader** - Путь к шейдеру.
- *const char ** **defines** - Пользовательские определения (например, "OPENGL", "DIRECT3D11" или любые другие).

### Возвращаемое значение

true, если шейдер может быть скомпилирован; иначе false.
