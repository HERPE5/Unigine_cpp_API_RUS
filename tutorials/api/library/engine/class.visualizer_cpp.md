# Класс Unigine::Visualizer (CPP)

**Заголовочный файл:** #include <UnigineVisualizer.h>

> **Notice:** Этот класс является одиночкой (singleton).


Управляет настройками, связанными с визуализатором. Визуализатор используется для отображения каркасной сетки меша, ограничивающих боксов объектов и всевозможных визуальных вспомогательных элементов (таких как формы физических коллизий, шарниры и т.д.).


### Пример использования


Чтобы отобразить начало координат мира, выполните следующее:


```cpp
#include "AppWorldLogic.h"
#include "UnigineVisualizer.h"

using namespace Unigine;
using namespace Math;

AppWorldLogic::AppWorldLogic()
{}

AppWorldLogic::~AppWorldLogic()
{}

int AppWorldLogic::init()
{
	// включаем визуализатор
	Visualizer::setEnabled(true);

	return 1;
}

int AppWorldLogic::update()
{

	// отображаем начало координат мира
	Visualizer::renderVector(Vec3(0.0f, 0.0f, 0.1f), Vec3(1.0f, 0.0f, 0.1f), vec4_red);
	Visualizer::renderVector(Vec3(0.0f, 0.0f, 0.1f), Vec3(0.0f, 1.0f, 0.1f), vec4_green);
	Visualizer::renderVector(Vec3(0.0f, 0.0f, 0.1f), Vec3(0.0f, 0.0f, 1.1f), vec4_blue);

	return 1;
}


```


Чтобы отобразить след от перемещения камеры, используйте следующее:


```cpp
#include "AppWorldLogic.h"
#include "UnigineVisualizer.h"
#include "UnigineGame.h"

using namespace Unigine;
using namespace Math;

AppWorldLogic::AppWorldLogic()
{}

AppWorldLogic::~AppWorldLogic()
{}

int AppWorldLogic::init()
{
	// включаем визуализатор
	Visualizer::setEnabled(true);

	return 1;
}

int AppWorldLogic::update()
{

	static auto last_pos = Game::getPlayer()->getWorldPosition();

	// отслеживание движения камеры
	const auto current_pos = Game::getPlayer()->getWorldPosition();
	if (length2(current_pos - last_pos) >= 0.1f)
	{
		Visualizer::renderPoint3D(last_pos, 0.05f, vec4_green, false, 2.0f);
		last_pos = current_pos;
	}

	return 1;
}


```


Вы сможете увидеть зелёные квадраты, если будете двигаться назад или развернётесь, чтобы посмотреть на свой след.


## Класс Visualizer

### Перечисления

## MODE

Режим визуализатора. Управляет способом отображения всех визуальных вспомогательных элементов.
| Имя | Описание |
|---|---|
| **MODE_DISABLED** = 0 | Не отображать визуализатор вообще. |
| **MODE_ENABLED_DEPTH_TEST_ENABLED** = 1 | Отображать визуализатор с включённым тестом глубины. |
| **MODE_ENABLED_DEPTH_TEST_DISABLED** = 2 | Отображать визуализатор без теста глубины. |

### Методы класса

## void setTextureName ( const char * name )

Устанавливает новый путь к вспомогательной текстуре визуализатора. Эта текстура применяется к **[billboards](#renderBillboard3D_Vec3_float_vec4_int_float_int_void)** и **[handlers](#renderNodeHandler_Node_float_void)** (отображаемым с помощью *[renderBillboard3D()](../../...md#renderBillboard3D_Vec3_float_vec4_int_float_int_void)* и *[renderNodeHandler()](../../...md#renderNodeHandler_Node_float_void)*). Чтобы восстановить текстуру по умолчанию, передайте пустую строку **("")**.
### Аргументы

- *const char ** **name** - Путь к текстуре.

## const char * getTextureName () const

Возвращает текущий путь к вспомогательной текстуре визуализатора. Эта текстура применяется к **[billboards](#renderBillboard3D_Vec3_float_vec4_int_float_int_void)** и **[handlers](#renderNodeHandler_Node_float_void)** (отображаемым с помощью *[renderBillboard3D()](../../...md#renderBillboard3D_Vec3_float_vec4_int_float_int_void)* и *[renderNodeHandler()](../../...md#renderNodeHandler_Node_float_void)*). Чтобы восстановить текстуру по умолчанию, передайте пустую строку **("")**.
### Возвращаемое значение

Текущий путь к текстуре.
## void setSize ( )

Устанавливает новый размер хендлера. Все хендлеры имеют одинаковый размер.
### Аргументы

- **size** - Размер хендлера, в пикселях.

## getSize () const

Возвращает текущий размер хендлера. Все хендлеры имеют одинаковый размер.
### Возвращаемое значение

Текущий размер хендлера, в пикселях.
## void setEnabled ( bool enabled )

Устанавливает новое значение, указывающее, включён ли визуализатор (отображение вспомогательных объектов, таких как хендлеры и ограничивающие боксы).
### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить визуализатор; **false** - чтобы отключить его.

## bool isEnabled () const

Возвращает текущее значение, указывающее, включён ли визуализатор (отображение вспомогательных объектов, таких как хендлеры и ограничивающие боксы).
### Возвращаемое значение

**true**, если визуализатор включён; иначе **false**.
## void setMode ( Visualizer::MODE mode )

Устанавливает новый [visualizer mode](#MODE), управляющий способом отображения всех визуальных вспомогательных элементов. Вы можете выбрать отображение визуализатора с тестом глубины или без него, либо полностью отключить его.
### Аргументы

- *[Visualizer::MODE](../../../api/library/engine/class.visualizer_cpp.md#MODE)* **mode** - Режим визуализатора.

## Visualizer::MODE getMode () const

Возвращает текущий [visualizer mode](#MODE), управляющий способом отображения всех визуальных вспомогательных элементов. Вы можете выбрать отображение визуализатора с тестом глубины или без него, либо полностью отключить его.
### Возвращаемое значение

Текущий режим визуализатора.
## int getNumHandlers () const

Возвращает текущее общее количество хендлеров.
> **Notice:** Общее количество хендлеров может изменяться каждый кадр в зависимости от трансформаций камеры (т.е. от того, сколько хендлеров видно в текущем кадре), поэтому не рекомендуется сохранять и повторно использовать это значение.


### Возвращаемое значение

Текущее общее количество хендлеров.
---

## void clear ( )

Очищает все внутренние примитивы, созданные вызовами функций *renderSmth*. Эти примитивы накапливаются во внутреннем буфере, а затем отображаются вместе.
> **Notice:** Этот метод можно использовать для отображения нескольких вьюпортов с визуализатором.


## void renderPoint2D ( const Math:: vec2 & v , float size , const Math:: vec4 & color , float order = 0.0f , float duration = 0.0f ) const

Отображает 2D-точку заданного размера и цвета. 2D-точки отображаются в плоскости экрана; координаты верхнего левого угла — (0; 0), нижнего правого угла — (1; 1).
### Аргументы

- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **v** - Координаты точки.
- *float* **size** - Размер точки в диапазоне [0;1]. Размер точки задаётся пропорционально разрешению экрана.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет точки.
- *float* **order** - Значение z-порядка для отображаемого элемента. Элемент с *более низким* порядком отображается *поверх* элемента с *более высоким*.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.

## void renderPoint3D ( const Math:: Vec3 & v , float size , const Math:: vec4 & color , bool screen_space = false , float duration = 0.0f , bool depth_test = true ) const

Отображает 3D-точку заданного размера и цвета. 3D-точки отображаются в мировом пространстве.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **v** - Координаты точки.
- *float* **size** - Размер точки в диапазоне [0;1]. Размер точки задаётся пропорционально разрешению экрана.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет точки.
- *bool* **screen_space** - Флаг, указывающий тип используемых измерений:

  - **false** - использовать измерения мирового пространства
  - **true** - использовать измерения пространства экрана
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderLine2D ( const Math:: vec2 & v0 , const Math:: vec2 & v1 , const Math:: vec4 & color , float order = 0.0f , float duration = 0.0f )

Отображает 2D-линию заданного цвета. 2D-линии отображаются в плоскости экрана; координаты верхнего левого угла — **(0; 0)**, нижнего правого угла — **(1; 1)**.
### Аргументы

- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **v0** - Начальная точка линии.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **v1** - Конечная точка линии.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет линии.
- *float* **order** - Значение z-порядка для отображаемого элемента. Элемент с *более низким* порядком отображается *поверх* элемента с *более высоким*.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.

## void renderLine3D ( const Math:: Vec3 & v0 , const Math:: Vec3 & v1 , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true )

Отображает 3D-линию заданного цвета. 3D-линии отображаются в мировом пространстве.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **v0** - Начальная точка линии.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **v1** - Конечная точка линии.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет линии.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderLine2D ( const Math:: vec2 & v0 , const Math:: vec2 & v1 , const Math:: vec2 & v2 , const Math:: vec4 & color , float order = 0.0f , float duration = 0.0f )

Отображает 2D-линию заданного цвета с использованием 3 точек. 2D-линии отображаются в плоскости экрана; координаты верхнего левого угла — **(0; 0)**, нижнего правого угла — **(1; 1)**.
### Аргументы

- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **v0** - Координаты начальной точки линии.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **v1** - Координаты промежуточной точки линии.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **v2** - Координаты конечной точки линии.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет линии.
- *float* **order** - Значение z-порядка для отображаемого элемента. Элемент с *более низким* порядком отображается *поверх* элемента с *более высоким*.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.

## void renderLine3D ( const Math:: Vec3 & v0 , const Math:: Vec3 & v1 , const Math:: Vec3 & v2 , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true )

Отображает 3D-линию заданного цвета. 3D-линии отображаются в мировом пространстве.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **v0** - Координаты начальной точки линии.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **v1** - Координаты промежуточной точки линии.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **v2** - Координаты конечной точки линии.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет линии.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderLine2D ( const Math:: vec2 & v0 , const Math:: vec2 & v1 , const Math:: vec2 & v2 , const Math:: vec2 & v3 , const Math:: vec4 & color , float order = 0.0f , float duration = 0.0f )

Отображает 2D-линию заданного цвета. 2D-линии отображаются в плоскости экрана; координаты верхнего левого угла — **(0; 0)**, нижнего правого угла — **(1; 1)**.
### Аргументы

- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **v0** - Координаты начальной точки линии.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **v1** - Координаты первой промежуточной точки линии.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **v2** - Координаты второй промежуточной точки линии.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **v3** - Координаты конечной точки линии.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будет отображена линия.
- *float* **order** - Значение z-порядка для отображаемого элемента. Элемент с *более низким* порядком отображается *поверх* элемента с *более высоким*.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.

## void renderLine3D ( const Math:: Vec3 & v0 , const Math:: Vec3 & v1 , const Math:: Vec3 & v2 , const Math:: Vec3 & v3 , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true )

Отображает 3D-линию заданного цвета. 3D-линии отображаются в мировом пространстве.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **v0** - Координаты начальной точки линии.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **v1** - Координаты первой промежуточной точки линии.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **v2** - Координаты второй промежуточной точки линии.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **v3** - Координаты конечной точки линии.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будет отображена линия.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderTriangle2D ( const Math:: vec2 & v0 , const Math:: vec2 & v1 , const Math:: vec2 & v2 , const Math:: vec4 & color , float order = 0.0f , float duration = 0.0f ) const

Отображает 2D-треугольник заданного цвета. 2D-треугольники отображаются в плоскости экрана; координаты верхнего левого угла — **(0; 0)**, нижнего правого угла — **(1; 1)**.
### Аргументы

- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **v0** - Координаты первой вершины.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **v1** - Координаты второй вершины.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **v2** - Координаты третьей вершины.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет треугольника.
- *float* **order** - Значение z-порядка для отображаемого элемента. Элемент с *более низким* порядком отображается *поверх* элемента с *более высоким*.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.

## void renderTriangle3D ( const Math:: Vec3 & v0 , const Math:: Vec3 & v1 , const Math:: Vec3 & v2 , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true ) const

Отображает 3D-треугольник заданного цвета. 3D-треугольники отображаются в мировом пространстве.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **v0** - Координаты первой вершины.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **v1** - Координаты второй вершины.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **v2** - Координаты третьей вершины.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет треугольника.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderQuad2D ( const Math:: vec2 & v0 , const Math:: vec2 & v1 , const Math:: vec2 & v2 , const Math:: vec2 & v3 , const Math:: vec4 & color , float order = 0.0f , float duration = 0.0f ) const

Отображает 2D-четырёхугольник заданного цвета. 2D-четырёхугольники отображаются в плоскости экрана; координаты верхнего левого угла — **(0; 0)**, нижнего правого угла — **(1; 1)**.
### Аргументы

- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **v0** - Координаты первой вершины.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **v1** - Координаты второй вершины.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **v2** - Координаты третьей вершины.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **v3** - Координаты четвёртой вершины.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будет отображён четырёхугольник.
- *float* **order** - Значение z-порядка для отображаемого элемента. Элемент с *более низким* порядком отображается *поверх* элемента с *более высоким*.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.

## void renderQuad3D ( const Math:: Vec3 & v0 , const Math:: Vec3 & v1 , const Math:: Vec3 & v2 , const Math:: Vec3 & v3 , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true ) const

Отображает 3D-четырёхугольник заданного цвета. 3D-четырёхугольники отображаются в мировом пространстве.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **v0** - Координаты первой вершины.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **v1** - Координаты второй вершины.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **v2** - Координаты третьей вершины.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **v3** - Координаты четвёртой вершины.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будет отображён четырёхугольник.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderBillboard3D ( const Math:: Vec3 & v , float size , const Math:: vec4 & texcoord , bool screen_space = false , float duration = 0.0f , bool depth_test = true ) const

Отображает 3D-билборд указанного размера. Изображение билборда можно настроить с помощью **[setTextureName()](../../...md#setTextureName_cstr_void)**.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **v** - Координаты билборда.
- *float* **size** - Размер билборда в единицах (метрах).
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **texcoord** - Координаты текстуры билборда, состоящие из двух пар элементов вектора (x, y, z, w):

  - x - размер текстуры по оси X в диапазоне [0.0f; 1.0f]
  - y - размер текстуры по оси Y в диапазоне [0.0f; 1.0f]
  - z - смещение начальной позиции текстуры по оси X в диапазоне [0.0f; 1.0f]
  - w - смещение начальной позиции текстуры по оси Y [0.0f; 1.0f]
- *bool* **screen_space** - Флаг, указывающий тип используемых измерений:

  - **false** - использовать измерения мирового пространства
  - **true** - использовать измерения пространства экрана
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderVector ( const Math:: Vec3 & position_start , const Math:: Vec3 & position_end , const Math:: vec4 & color , float arrow_size = 0.25f , bool screen_space = false , float duration = 0.0f , bool depth_test = true ) const

Отображает вектор заданного цвета.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **position_start** - Координаты начала вектора.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **position_end** - Координаты конца вектора.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет вектора.
- *float* **arrow_size** - Относительная длина наконечника стрелки (конуса) по отношению к общей длине вектора. Например, значение по умолчанию 0.25f означает, что наконечник стрелки занимает 25% от общей длины стрелки.
- *bool* **screen_space** - Флаг, указывающий тип используемых измерений:

  - **false** - использовать измерения мирового пространства
  - **true** - использовать измерения пространства экрана
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderDirection ( const Math:: Vec3 & position , const Math:: vec3 & direction , const Math:: vec4 & color , float arrow_size = 0.25f , bool screen_space = true , float duration = 0.0f , bool depth_test = true ) const

Отображает вектор направления заданного цвета.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **position** - Координаты начала вектора.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **direction** - Целевое направление вектора.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет вектора.
- *float* **arrow_size** - Относительная длина наконечника стрелки (конуса) по отношению к общей длине вектора. Например, значение по умолчанию 0.25f означает, что наконечник стрелки занимает 25% от общей длины стрелки.
- *bool* **screen_space** - Флаг, указывающий тип используемых измерений:

  - **false** - использовать измерения мирового пространства
  - **true** - использовать измерения пространства экрана
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderBox ( const Math:: vec3 & size , const Math:: Mat4 & transform , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true ) const

Отображает бокс заданного цвета.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **size** - Размеры бокса.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации, используемая для позиционирования бокса.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будет отображён бокс.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderFrustum ( const Math:: mat4 & projection , const Math:: Mat4 & transform , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true ) const

Отображает каркасный (wireframe) фрустум заданного цвета.
### Аргументы

- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **projection** - Матрица проекции, используемая для преобразования координат.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации, используемая для позиционирования фрустума.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будет отображён фрустум.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderCircle ( float radius , const Math:: Mat4 & transform , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true ) const

Отображает каркасную окружность заданного цвета.
### Аргументы

- *float* **radius** - Радиус окружности.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации, используемая для позиционирования окружности.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет окружности.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderSector ( float radius , float angle , const Math:: Mat4 & transform , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true ) const

Отображает каркасный сектор заданного цвета.
### Аргументы

- *float* **radius** - Радиус окружности, из которой вырезан сектор.
- *float* **angle** - Угол сектора.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации, используемая для позиционирования сектора.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет сектора.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderCone ( float radius , float angle , const Math:: Mat4 & transform , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true ) const

Отображает каркасный конус заданного цвета.
### Аргументы

- *float* **radius** - Радиус конуса.
- *float* **angle** - Угол конуса.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации, используемая для позиционирования конуса.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будет отображён конус.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderSphere ( float radius , const Math:: Mat4 & transform , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true ) const

Отображает каркасную сферу заданного цвета.
### Аргументы

- *float* **radius** - Радиус сферы.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации, используемая для позиционирования сферы.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет сферы.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderCapsule ( float radius , float height , const Math:: Mat4 & transform , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true ) const

Отображает каркасную капсулу (цилиндр с закруглёнными концами) заданного цвета.
### Аргументы

- *float* **radius** - Радиус капсулы.
- *float* **height** - Высота капсулы.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации, используемая для позиционирования капсулы.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет капсулы.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderCylinder ( float radius , float height , const Math:: Mat4 & transform , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true ) const

Отображает каркасный цилиндр заданного цвета.
### Аргументы

- *float* **radius** - Радиус цилиндра.
- *float* **height** - Высота цилиндра.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации, используемая для позиционирования цилиндра.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет цилиндра.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderEllipse ( const Math:: vec3 & radius , const Math:: Mat4 & transform , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true ) const

Отображает каркасный эллипс заданного цвета.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **radius** - Значения радиуса эллипса вдоль трёх осей.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации для эллипса.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет эллипса.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderSolidBox ( const Math:: vec3 & size , const Math:: Mat4 & transform , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true ) const

Отображает сплошной (закрашенный) бокс заданного цвета.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **size** - Размер сплошного бокса.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации, используемая для позиционирования сплошного бокса.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет бокса.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderSolidSphere ( float radius , const Math:: Mat4 & transform , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true ) const

Отображает сплошную (закрашенную) сферу заданного цвета.
### Аргументы

- *float* **radius** - Радиус сплошной сферы.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации, используемая для позиционирования сплошной сферы.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет сферы.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderSolidCapsule ( float radius , float height , const Math:: Mat4 & transform , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true ) const

Отображает сплошную (закрашенную) капсулу заданного цвета.
### Аргументы

- *float* **radius** - Радиус капсулы.
- *float* **height** - Высота капсулы.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации, используемая для позиционирования капсулы.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет капсулы.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderSolidCylinder ( float radius , float height , const Math:: Mat4 & transform , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true ) const

Отображает сплошной (закрашенный) цилиндр заданного цвета.
### Аргументы

- *float* **radius** - Радиус цилиндра.
- *float* **height** - Высота цилиндра.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации, используемая для позиционирования цилиндра.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет цилиндра.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderSolidEllipse ( const Math:: vec3 & radius , const Math:: Mat4 & transform , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true ) const

Отображает сплошной (закрашенный) эллипс заданного цвета.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **radius** - Значения радиуса эллипса вдоль трёх осей.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации, используемая для позиционирования эллипса.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет эллипса.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderRectangle ( const Math:: vec4 & rectangle , const Math:: vec4 & color , float duration = 0.0f )

Отображает 2D каркасный прямоугольник заданного цвета.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **rectangle** - Четырёхкомпонентный вектор, содержащий координаты верхнего левого угла (первые два компонента) и нижнего правого угла (вторые два компонента) прямоугольника.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет прямоугольника.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.

## void renderBoundBox ( const Math:: BoundBox & bb , const Math:: Mat4 & transform , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true )

Отображает ограничивающий бокс заданного цвета.
### Аргументы

- *const  Math::[BoundBox](../../../api/library/math/bounds/class.boundbox_cpp.md) &* **bb** - Ограничивающий бокс.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации для ограничивающего бокса.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будет отображён бокс.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderBoundSphere ( const Math:: BoundSphere & bs , const Math:: Mat4 & transform , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true )

Отображает ограничивающую сферу заданного цвета.
### Аргументы

- *const  Math::[BoundSphere](../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Ограничивающая сфера.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации для ограничивающей сферы.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будет отображена сфера.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderNodeBoundBox ( const Ptr < Node > & node , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true )

Отображает ограничивающий бокс, выровненный по осям, для указанного узла.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **node** - Узел, для которого отображается ограничивающий бокс.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будет отображён бокс.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderNodeBoundSphere ( const Ptr < Node > & node , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true )

Отображает ограничивающую сферу указанного узла.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **node** - Узел, для которого отображается ограничивающая сфера.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будет отображена сфера.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderObjectSurfaceBoundBox ( const Ptr < Object > & object , int surface , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true )

Отображает ограничивающий бокс указанной поверхности объекта.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)> &* **object** - Объект, содержащий целевую поверхность.
- *int* **surface** - Номер целевой поверхности в объекте.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будет отображён бокс.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderObjectSurfaceBoundSphere ( const Ptr < Object > & object , int surface , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true )

Отображает ограничивающую сферу указанной поверхности объекта.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)> &* **object** - Объект, содержащий целевую поверхность.
- *int* **surface** - Номер целевой поверхности в объекте.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будет отображена сфера.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false — чтобы отключить его.

## void renderNodeHandler ( const Ptr < Node > & node , float duration = 0.0f ) const

Отображает хендлер для указанного узла. Изображение хендлера можно настроить с помощью **[setTextureName()](../../...md#setTextureName_cstr_void)**.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **node** - Узел, для которого будет отображён хендлер.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.

## void renderObject ( const Ptr < Object > & object , const Math:: vec4 & color , float duration = 0.0f ) const

Отображает каркас объекта.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)> &* **object** - Объект, каркас которого будет отображён.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будет отображён каркас.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.

## void renderObjectSurface ( const Ptr < Object > & object , int surface , const Math:: vec4 & color , float duration = 0.0f ) const

Отображает границы указанной поверхности объекта.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)> &* **object** - Объект, содержащий целевую поверхность.
- *int* **surface** - Номер целевой поверхности в объекте.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будут отображены границы.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.

## void renderSolidObject ( const Ptr < Object > & object , const Math:: vec4 & color , float duration = 0.0f ) const

Отображает объект, закрашенный сплошным цветом.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)> &* **object** - Умный указатель объекта.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будет отображён объект.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.

## void renderSolidObjectSurface ( const Ptr < Object > & object , int surface , const Math:: vec4 & color , float duration = 0.0f ) const

Отображает поверхность объекта, закрашенную сплошным цветом.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)> &* **object** - Умный указатель объекта.
- *int* **surface** - Номер поверхности объекта.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будет отображена поверхность объекта.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.

## void renderMessage2D ( const Math:: vec3 & position , const Math:: vec3 & center , const char * str , const Math:: vec4 & color , int outline , int font_size = -1 , float duration = 0.0f )

Отображает сообщение заданного цвета. Позиция сообщения указывается в экранных координатах.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **position** - Координаты опорной точки сообщения, каждая в диапазоне **[0;1]**.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **center** - Выравнивание сообщения. Первые два значения в векторе задают смещение, третье игнорируется. Например, vec3(-1,-1,0) задаёт смещение центра сообщения к его верхнему левому краю. vec3(1,1,0) - к нижнему правому углу.
- *const char ** **str** - Текст сообщения для отображения.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будет отображено сообщение.
- *int* **outline** - **1**, чтобы использовать контур шрифта, **0**, чтобы не использовать.
- *int* **font_size** - Размер шрифта.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.

## void renderMessage3D ( const Math:: Vec3 & position , const Math:: vec3 & center , const char * str , const Math:: vec4 & color , int outline , int font_size = -1 , float duration = 0.0f )

Отображает сообщение заданного цвета. Позиция сообщения указывается в мировых координатах.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **position** - Координаты опорной точки сообщения (в мировых координатах).
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **center** - Выравнивание сообщения. Первые два значения в векторе задают смещение, третье игнорируется. Например, vec3(-1,-1,0) задаёт смещение центра сообщения к его верхнему левому краю. vec3(1,1,0) - к нижнему правому углу.
- *const char ** **str** - Текст сообщения для отображения.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будет отображено сообщение.
- *int* **outline** - **1**, чтобы использовать контур шрифта, **0**, чтобы не использовать.
- *int* **font_size** - Размер шрифта.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.

## Ptr < Node > getHandlerNode ( int num ) const

Возвращает узел хендлера по его индексу.
> **Notice:** Индекс хендлера может изменяться каждый кадр в зависимости от трансформаций камеры (т.е. от того, сколько хендлеров видно в текущем кадре), поэтому не рекомендуется сохранять и повторно использовать это значение.


### Аргументы

- *int* **num** - Индекс узла хендлера в диапазоне от 0 до [total number of handlers](#getNumHandlers_int).

### Возвращаемое значение

Узел, для которого отображается хендлер.
## float getHandlerSize ( int num ) const

Возвращает размер иконки хендлера в единицах по его индексу. На это значение может влиять размер иконки (задаваемый методом [setSize()](#setSize_int_void)) и опция 3D (консольная команда [world_handler_3d](../../../code/console/index.md#world_handler_3d)).
### Аргументы

- *int* **num** - Индекс узла хендлера в диапазоне от 0 до [total number of handlers](#getNumHandlers_int).

### Возвращаемое значение

Размер иконки хендлера, в единицах.
## void renderMesh ( const Ptr < MeshRender > & mesh , const Math:: Mat4 & transform , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true )

Отображает каркас указанного меша заданного цвета.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[MeshRender](../../../api/library/rendering/class.meshrender_cpp.md)> &* **mesh** - Отображаемый меш.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации для меша.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будет отображён каркас меша.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false - чтобы отключить его.

## void renderMesh ( const UGUID & mesh_guid , const Math:: Mat4 & transform , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true )

Отображает каркас меша, загруженного по указанному GUID ассета, заданного цвета.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **mesh_guid** - GUID ассета меша для отображения.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации для меша.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будет отображён каркас меша.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false - чтобы отключить его.

## void renderMesh ( const char * path , const Math:: Mat4 & transform , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true )

Отображает каркас меша, загруженного из указанного пути к файлу, заданного цвета.
### Аргументы

- *const char ** **path** - Путь к файлу меша для отображения.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации для меша.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будет отображён каркас меша.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false - чтобы отключить его.

## void renderSolidMesh ( const Ptr < MeshRender > & mesh , const Math:: Mat4 & transform , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true )

Отображает сплошную (закрашенную) версию указанного меша заданного цвета.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[MeshRender](../../../api/library/rendering/class.meshrender_cpp.md)> &* **mesh** - Отображаемый меш.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации для меша.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будет отображён меш.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false - чтобы отключить его.

## void renderSolidMesh ( const UGUID & mesh_guid , const Math:: Mat4 & transform , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true )

Отображает сплошную (закрашенную) версию меша, загруженного по указанному GUID ассета, заданного цвета.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **mesh_guid** - GUID ассета меша для отображения.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации для меша.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будет отображён меш.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false - чтобы отключить его.

## void renderSolidMesh ( const char * path , const Math:: Mat4 & transform , const Math:: vec4 & color , float duration = 0.0f , bool depth_test = true )

Отображает сплошную (закрашенную) версию меша, загруженного из указанного пути к файлу, заданного цвета.
### Аргументы

- *const char ** **path** - Путь к файлу меша для отображения.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации для меша.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, которым будет отображён каркас меша.
- *float* **duration** - Период времени (в секундах), в течение которого отображаемый элемент должен быть виден. Значение по умолчанию 0 означает, что визуализатор отображается только в течение 1 кадра.
- *bool* **depth_test** - true, чтобы включить тест глубины для элемента (если он должен быть перекрыт элементами, расположенными ближе к камере); false - чтобы отключить его.
