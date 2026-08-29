# Unigine::WidgetCheckBox Class (CPP)

**Header:** #include <UnigineWidgets.h>

**Inherits from:** Widget


Этот класс создаёт [checkboxes](../../../code/gui/ui/ui_widgets.md#checkbox). Набор чекбоксов можно преобразовать в группу радиокнопок (действующую как единый взаимоисключающий элемент управления), если все чекбоксы [attached](../../../api/library/gui/class.widget_cpp.md#addAttach_Widget_cstr_int_int_void) к одному из них (например, к первому).


Объект этого класса может выглядеть следующим образом:


![Checkbox widget](../../../code/gui/ui/widgets/checkbox.png)


![Radio button widget](../../../code/gui/ui/widgets/radiobutton.png)


### См. также


- Пример C++


## Пример


Следующий код демонстрирует, как создать виджет чекбокса и задать его параметры.


```cpp
#include "AppWorldLogic.h"
#include <UnigineWidgets.h>

using namespace Unigine;

/* .. */

// функция-обработчик события
int onCheckBoxEventChanged()
{
	/* .. */

	return 1;
}
// создаём экземпляр класса EventConnection
EventConnection connection;

/* .. */

int AppWorldLogic::init()
{
	GuiPtr gui = Gui::getCurrent();

	// создаём виджет чекбокса и задаём его подпись
	WidgetCheckBoxPtr widget_checkbox = WidgetCheckBox::create(gui, "Automatic mode");

	// задаём подсказку
	widget_checkbox->setToolTip("Toggle automatic mode");

	// перестраиваем размер чекбокса
	widget_checkbox->arrange();

	// задаём позицию чекбокса
	widget_checkbox->setPosition(10, 10);

	// устанавливаем состояние чекбокса как отмеченное
	widget_checkbox->setChecked(1);

	// задаём функцию onCheckBoxChanged для обработки события CHANGED
	widget_checkbox->getEventChanged().connect(connection, onCheckBoxEventChanged);

	// добавляем созданный виджет чекбокса в системный GUI
	gui->addChild(widget_checkbox, Gui::ALIGN_OVERLAP | Gui::ALIGN_FIXED);

	return 1;
}

// ...

int AppWorldLogic::shutdown()
{
	// удаляем подписку на событие
	connection.disconnect();
	return 1;
}


```


## WidgetCheckBox Class

### Методы класса

---

## static WidgetCheckBoxPtr create ( const Ptr < Gui > & gui , const char * str = 0 )

Конструктор. Создаёт чекбокс с указанной текстовой подписью и добавляет его в указанный GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - [GUI](../../../api/library/gui/class.gui_cpp.md), которому будет принадлежать новый чекбокс.
- *const char ** **str** - Подпись чекбокса. Это опциональный параметр.

## static WidgetCheckBoxPtr create ( const char * str = 0 )

Конструктор. Создаёт чекбокс с указанной текстовой подписью и добавляет его в GUI движка.
### Аргументы

- *const char ** **str** - Подпись чекбокса. Это опциональный параметр.

## void setChecked ( bool checked )

Устанавливает значение, указывающее, выбран ли чекбокс.
### Аргументы

- *bool* **checked** - 1, чтобы отметить (выбрать) чекбокс, 0 — чтобы снять отметку.

## bool isChecked ( ) const

Возвращает значение, указывающее, выбран ли чекбокс.
### Возвращаемое значение

1, если чекбокс отмечен (выбран); иначе 0.
## void setText ( const char * text )

Устанавливает текстовую подпись чекбокса.
### Аргументы

- *const char ** **text** - Подпись чекбокса.

## const char * getText ( ) const

Возвращает текстовую подпись чекбокса.
### Возвращаемое значение

Подпись чекбокса.
## void setCheckedColor ( const Math:: vec4 & color )

Устанавливает цвет, используемый для отмеченного состояния виджета.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Четырёхкомпонентный вектор, задающий цвет в формате RGBA.

## Math:: vec4 getCheckedColor ( ) const

Возвращает текущий цвет, используемый для отмеченного состояния виджета.
### Возвращаемое значение

Четырёхкомпонентный вектор, задающий цвет в формате RGBA.
## void setUncheckedColor ( const Math:: vec4 & color )

Устанавливает цвет, используемый для неотмеченного состояния виджета.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Четырёхкомпонентный вектор, задающий цвет в формате RGBA.

## Math:: vec4 getUncheckedColor ( ) const

Возвращает текущий цвет, используемый для неотмеченного состояния виджета.
### Возвращаемое значение

Четырёхкомпонентный вектор, задающий цвет в формате RGBA.
