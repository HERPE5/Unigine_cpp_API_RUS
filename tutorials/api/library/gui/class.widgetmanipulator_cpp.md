# Unigine::WidgetManipulator Class (CPP)

**Header:** #include <UnigineWidgets.h>

**Inherits from:** Widget


Этот базовый класс создаёт перетаскиваемый 3D-манипулятор.


### См. также


- Пример использования: [Using Manipulators to Transform Objects](../../../code/usage/manipulator_component/index_cpp.md)
- Пример C++


## WidgetManipulator Class

### Методы класса

---

## static WidgetManipulatorPtr create ( const Ptr < Gui > & gui )

Конструктор WidgetManipulator. Создаёт виджет манипулятора и добавляет его в указанный GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - Указатель на GUI.

## static WidgetManipulatorPtr create ( )

Конструктор WidgetManipulator. Создаёт виджет манипулятора и добавляет его в GUI движка.
## void setBasis ( const Math:: Mat4 & basis )

Устанавливает базис системы координат для манипулятора. Это могут быть мировые координаты (единичная матрица) или координаты родительского узла, если управляемый узел является дочерним.
### Аргументы

- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **basis** - Матрица, столбцы которой задают базисные векторы.

## Math:: Mat4 getBasis ( ) const

Возвращает текущий базис системы координат для манипулятора. Это могут быть мировые координаты (единичная матрица) или координаты родительского узла, если управляемый узел является дочерним.
### Возвращаемое значение

Матрица, столбцы которой задают базисные векторы.
## void setColor ( const Math:: vec4 & color )

Устанавливает цвет манипулятора.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет манипулятора. Указанное значение ограничивается диапазоном **[0;1]**.

## Math:: vec4 getColor ( ) const

Возвращает текущий цвет манипулятора.
### Возвращаемое значение

Цвет манипулятора.
## void setMask ( int mask )

Скрывает стрелки осей (вдоль *X*, *Y* или *Z*) манипулятора.
### Аргументы

- *int* **mask** - 3-битная маска для осей.

## int getMask ( ) const

Возвращает маску, скрывающую стрелки осей (вдоль *X*, *Y* или *Z*) манипулятора.
### Возвращаемое значение

3-битная маска для осей.
## void setModelview ( const Math:: Mat4 & modelview )

Устанавливает матрицу model-view для манипулятора.
### Аргументы

- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **modelview** - Матрица model-view.

## Math:: Mat4 getModelview ( ) const

Возвращает текущую матрицу проекции манипулятора.
### Возвращаемое значение

Матрица model-view.
## void setProjection ( const Math:: mat4 & projection )

Устанавливает матрицу проекции для манипулятора.
### Аргументы

- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **projection** - Матрица проекции.

## Math:: mat4 getProjection ( ) const

Возвращает текущую матрицу model-view манипулятора.
### Возвращаемое значение

Матрица проекции.
## void setRenderGui ( const Ptr < Gui > & gui )

Устанавливает GUI отрисовки.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - Умный указатель [GUI](../../../api/library/gui/class.gui_cpp.md).

## Ptr < Gui > getRenderGui ( ) const

Возвращает текущий GUI отрисовки.
### Возвращаемое значение

Умный указатель [GUI](../../../api/library/gui/class.gui_cpp.md).
## void setSize ( int size )

Устанавливает размер рукоятки манипулятора. В зависимости от формы рукоятки это может быть радиус или высота.
### Аргументы

- *int* **size** - Размер в пикселях.

## int getSize ( ) const

Возвращает текущий размер рукоятки манипулятора. В зависимости от формы рукоятки это может быть радиус или высота.
### Возвращаемое значение

Размер в пикселях.
## void setStep ( float step )

Устанавливает шаг, используемый для выравнивания объектов.
### Аргументы

- *float* **step** - Шаг в единицах.

## float getStep ( ) const

Возвращает шаг, используемый для выравнивания объектов.
### Возвращаемое значение

Шаг в единицах.
## void setTransform ( const Math:: Mat4 & transform )

Устанавливает матрицу трансформации для манипулятора.
### Аргументы

- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации.

## Math:: Mat4 getTransform ( ) const

Возвращает текущую матрицу трансформации манипулятора.
### Возвращаемое значение

Матрица трансформации.
## int getFocusedAxis ( ) const

Возвращает номер оси манипулятора, находящейся в данный момент в фокусе.
### Возвращаемое значение

Номер оси манипулятора, находящейся в данный момент в фокусе. Значения зависят от типа манипулятора:
- [WidgetManipulatorRotator](../../../api/library/gui/class.widgetmanipulatorrotator_cpp.md): одна из переменных [AXIS_*](../../../api/library/gui/class.widgetmanipulatorrotator_cpp.md#AXIS_UNKNOWN).
- [WidgetManipulatorScaler](../../../api/library/gui/class.widgetmanipulatorscaler_cpp.md): одна из переменных [AXIS_*](../../../api/library/gui/class.widgetmanipulatorscaler_cpp.md#AXIS_UNKNOWN).
- [WidgetManipulatorTranslator](../../../api/library/gui/class.widgetmanipulatortranslator_cpp.md): одна из переменных [AXIS_*](../../../api/library/gui/class.widgetmanipulatortranslator_cpp.md#AXIS_UNKNOWN).


## bool isFocusAxis ( ) const

Возвращает значение, указывающее, находится ли какая-либо ось манипулятора в данный момент в фокусе.
### Возвращаемое значение

true, если какая-либо ось манипулятора находится в данный момент в фокусе; иначе false.
## bool isHoverAxis ( ) const

Возвращает значение, указывающее, находится ли курсор в данный момент над какой-либо осью манипулятора.
### Возвращаемое значение

true, если курсор в данный момент находится над какой-либо осью манипулятора; иначе false.
