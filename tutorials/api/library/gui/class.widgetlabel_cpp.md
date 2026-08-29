# Unigine::WidgetLabel Class (CPP)

**Header:** #include <UnigineWidgets.h>

**Inherits from:** Widget


Этот класс создаёт [text label](../../../code/gui/ui/ui_widgets.md#label).


Объект этого класса выглядит следующим образом:


![](../../../code/gui/ui/widgets/label.png)


#### См. также


- Пример C++
- Примеры UnigineScript:

  -
  -
  -
  -
  -
  -
  -


### Пример


Следующий код демонстрирует, как создать виджет метки и задать его параметры.


```cpp
#include <UnigineWidgets.h>
using namespace Unigine;

/* .. */

// получаем указатель на системный GUI
GuiPtr gui = Gui::get();

// создаём виджет метки и задаём её подпись
WidgetLabelPtr widget_label = WidgetLabel::create(gui, "Label text");

// задаём подсказку
widget_label->setToolTip("This is a label");

// перестраиваем размер метки
widget_label->arrange();

// задаём позицию метки
widget_label->setPosition(10, 10);

// добавляем созданный виджет метки в системный GUI
gui->addChild(widget_label, Gui::ALIGN_OVERLAP | Gui::ALIGN_FIXED);

```


## WidgetLabel Class

### Методы класса

---

## static WidgetLabelPtr create ( const Ptr < Gui > & gui , const char * str = 0 )

Конструктор. Создаёт новую текстовую метку и добавляет её в указанный GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - [GUI](../../../api/library/gui/class.gui_cpp.md), которому будет принадлежать новая метка.
- *const char ** **str** - Текст метки. Это опциональный параметр.

## static WidgetLabelPtr create ( const char * str = 0 )

Конструктор. Создаёт новую текстовую метку и добавляет её в GUI движка.
### Аргументы

- *const char ** **str** - Текст метки. Это опциональный параметр.

## void setText ( const char * text )

Устанавливает текст для метки.
### Аргументы

- *const char ** **text** - Текст метки.

## const char * getText ( ) const

Возвращает текст метки.
### Возвращаемое значение

Текст метки.
## void setTextAlign ( int align )

Устанавливает выравнивание метки.
### Аргументы

- *int* **align** - Одно из значений перечисления Gui:: с префиксом ALIGN_*.

## int getTextAlign ( ) const

Возвращает выравнивание метки.
### Возвращаемое значение

Выравнивание метки: одно из значений перечисления Gui:: с префиксом ALIGN_*.
