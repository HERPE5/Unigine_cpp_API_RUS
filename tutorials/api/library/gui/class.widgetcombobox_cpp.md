# Unigine::WidgetComboBox Class (CPP)

**Header:** #include <UnigineWidgets.h>

**Inherits from:** Widget


Этот класс создаёт [combo box](../../../code/gui/ui/ui_widgets.md#combobox).


Объект этого класса выглядит следующим образом:


![Combo box widget](../../../code/gui/ui/widgets/combobox.png)


#### См. также


- Пример C++


### Пример


Следующий код демонстрирует, как создать виджет комбобокса и задать его параметры.


```cpp
#include "AppWorldLogic.h"
#include <UnigineGui.h>

using namespace Unigine;

// экземпляр класса EventConnections для управления подписками на события
EventConnections econnections;

/* .. */

// функция-обработчик события
int onComboBoxChanged()
{
	/* .. */

	return 1;
}

/* .. */

int AppWorldLogic::init()
{
	// получаем указатель на системный GUI
	GuiPtr gui = Gui::getCurrent();

	// создаём виджет комбобокса
	WidgetComboBoxPtr widget_combo = WidgetComboBox::create(gui);

	// добавляем элементы в комбобокс
	widget_combo->addItem("----ALL-----");
	widget_combo->addItem("Item 1");
	widget_combo->addItem("Item 2");
	widget_combo->addItem("Item 3");

	// задаём подсказку
	widget_combo->setToolTip("This is a combo box");

	// перестраиваем размер комбобокса
	widget_combo->arrange();

	// задаём позицию комбобокса
	widget_combo->setPosition(10, 10);

	// устанавливаем первый элемент как выбранный
	widget_combo->setCurrentItem(0);

	// задаём функцию onComboBoxChanged для обработки события CHANGED
	widget_combo->getEventChanged().connect(econnections, onComboBoxChanged);

	// добавляем созданный виджет комбобокса в системный GUI
	gui->addChild(widget_combo, Gui::ALIGN_OVERLAP | Gui::ALIGN_FIXED);

	return 1;
}

int AppWorldLogic::shutdown()
{
	// удаляем все подписки на события
	econnections.disconnectAll();

	return 1;
}


```


## WidgetComboBox Class

### Методы класса

---

## static WidgetComboBoxPtr create ( const Ptr < Gui > & gui )

Конструктор. Создаёт пустой комбобокс и добавляет его в указанный GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - [GUI](../../../api/library/gui/class.gui_cpp.md), которому будет принадлежать новый комбобокс.

## static WidgetComboBoxPtr create ( )

Конструктор. Создаёт пустой комбобокс и добавляет его в GUI движка.
## void setCurrentItem ( int item )

Устанавливает указанный элемент как выбранный.
### Аргументы

- *int* **item** - Номер элемента.

## int getCurrentItem ( ) const

Возвращает текущий выбранный элемент.
### Возвращаемое значение

Номер элемента.
## const char * getCurrentItemData ( ) const

Возвращает [text data](#setItemData_int_cstr_void) текущего выбранного элемента. Эти данные можно использовать как текстовый идентификатор элемента (вместо использования номера элемента).
### Возвращаемое значение

Текстовые данные элемента.
## const char * getCurrentItemText ( ) const

Возвращает текстовое значение текущего выбранного элемента.
### Возвращаемое значение

Текст элемента.
## void setImage ( const Ptr < Image > & image )

Устанавливает изображение с мини-иконками, используемыми для элементов. Изображение представляет собой вертикальную полосу квадратных иконок.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)> &* **image** - Устанавливаемое изображение.

## Ptr < Image > getImage ( ) const

Возвращает изображение с мини-иконками, используемыми для элементов комбобокса.
### Возвращаемое значение

Изображение с мини-иконками.
## void setItemData ( int item , const char * str )

Устанавливает текстовые данные для элемента с указанным номером. Эти данные можно использовать как текстовый идентификатор элемента (вместо использования номера элемента).
### Аргументы

- *int* **item** - Номер элемента в диапазоне от 0 до общего количества элементов.
- *const char ** **str** - Устанавливаемые текстовые данные элемента.

## const char * getItemData ( int item ) const

Возвращает [text data](#setItemData_int_cstr_void) элемента с указанным номером. Эти данные можно использовать как текстовый идентификатор элемента (вместо использования номера элемента).
### Аргументы

- *int* **item** - Номер элемента в диапазоне от 0 до общего количества элементов.

### Возвращаемое значение

Текстовые данные элемента.
## void setItemText ( int item , const char * str )

Устанавливает текст для указанного элемента.
### Аргументы

- *int* **item** - Номер элемента в диапазоне от 0 до общего количества элементов.
- *const char ** **str** - Текст элемента.

## const char * getItemText ( int item ) const

Возвращает текст указанного элемента.
### Аргументы

- *int* **item** - Номер элемента в диапазоне от 0 до общего количества элементов.

### Возвращаемое значение

Текст элемента.
## void setItemTexture ( int item , int texture )

Устанавливает иконку для указанного элемента.
### Аргументы

- *int* **item** - Номер элемента в диапазоне от 0 до общего количества элементов.
- *int* **texture** - ID иконки, начиная с 0.

## int getItemTexture ( int item ) const

Возвращает иконку указанного элемента.
### Аргументы

- *int* **item** - Номер элемента в диапазоне от 0 до общего количества элементов.

### Возвращаемое значение

ID иконки, начиная с 0.
## int getNumItems ( ) const

Возвращает количество элементов в комбобоксе.
### Возвращаемое значение

Количество элементов.
## void setTexture ( const char * texture )

Устанавливает текстуру с мини-иконками, используемыми для элементов. Текстура представляет собой вертикальную полосу квадратных иконок.
### Аргументы

- *const char ** **texture** - Путь к файлу текстуры.

## const char * getTexture ( ) const

Возвращает путь к изображению с мини-иконками, используемыми для элементов комбобокса.
### Возвращаемое значение

Путь к файлу текстуры.
## int addItem ( const char * str , int texture = -1 )

Добавляет новый элемент с указанным текстом и иконкой.
### Аргументы

- *const char ** **str** - Текст элемента.
- *int* **texture** - ID иконки, начиная с 0.

### Возвращаемое значение

Номер добавленного элемента.
## void clear ( )

Удаляет все элементы из комбобокса.
## void removeItem ( int num )

Удаляет указанный элемент из комбобокса.
### Аргументы

- *int* **num** - Номер элемента в диапазоне от 0 до общего количества элементов.

## void setMainBackgroundColor ( const Math:: vec4 & color )

Устанавливает фоновый цвет, используемый для текстового поля виджета.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Четырёхкомпонентный вектор, задающий цвет в формате RGBA.

## Math:: vec4 getMainBackgroundColor ( ) const

Возвращает текущий фоновый цвет, используемый для текстового поля виджета.
### Возвращаемое значение

Четырёхкомпонентный вектор, задающий цвет в формате RGBA.
## void setListBackgroundColor ( const Math:: vec4 & color )

Устанавливает фоновый цвет, используемый для элементов списка виджета.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Четырёхкомпонентный вектор, задающий цвет в формате RGBA.

## Math:: vec4 getListBackgroundColor ( ) const

Возвращает текущий фоновый цвет, используемый для элементов списка виджета.
### Возвращаемое значение

Четырёхкомпонентный вектор, задающий цвет в формате RGBA.
## void setSelectionColor ( const Math:: vec4 & color )

Устанавливает цвет, используемый для выделения текущего выбора виджета.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Четырёхкомпонентный вектор, задающий цвет в формате RGBA.

## Math:: vec4 getSelectionColor ( ) const

Возвращает текущий цвет, используемый для выделения текущего выбора виджета.
### Возвращаемое значение

Четырёхкомпонентный вектор, задающий цвет в формате RGBA.
## void setBorderColor ( const Math:: vec4 & color )

Устанавливает цвет границы виджета.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Четырёхкомпонентный вектор, задающий цвет в формате RGBA.

## Math:: vec4 getBorderColor ( ) const

Возвращает текущий цвет границы виджета.
### Возвращаемое значение

Четырёхкомпонентный вектор, задающий цвет в формате RGBA.
## void setButtonColor ( const Math:: vec4 & color )

Устанавливает цвет кнопки виджета.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Четырёхкомпонентный вектор, задающий цвет в формате RGBA.

## Math:: vec4 getButtonColor ( ) const

Возвращает текущий цвет кнопки виджета.
### Возвращаемое значение

Четырёхкомпонентный вектор, задающий цвет в формате RGBA.
## int findItemByText ( const char * str ) const

Возвращает номер элемента, текст которого совпадает с указанным в аргументе.
### Аргументы

- *const char ** **str** - Текст элемента.

### Возвращаемое значение

Номер элемента с совпадающим текстом.
## void setStyleTextureIcon ( const char * icon )

Устанавливает скин, используемый для иконок.
### Аргументы

- *const char ** **icon** - Путь к файлу текстуры.

## const char * getStyleTextureIcon ( ) const

Возвращает путь к скину, используемому для иконок.
### Возвращаемое значение

Путь к файлу текстуры.
## void setStyleTextureButton ( const char * button )

Устанавливает скин, используемый для кнопок.
### Аргументы

- *const char ** **button** - Путь к файлу текстуры.

## const char * getStyleTextureButton ( ) const

Возвращает путь к скину, используемому для кнопок.
### Возвращаемое значение

Path to a texture file.
## void setStyleTextureSelection ( const char * selection )

Устанавливает скин, используемый для выделения текущего выбора виджета.
### Аргументы

- *const char ** **selection** - Путь к файлу текстуры.

## const char * getStyleTextureSelection ( ) const

Возвращает скин, используемый для выделения текущего выбора виджета.
### Возвращаемое значение

Path to a texture file.
## void setStyleTextureBackground ( const char * background )

Устанавливает скин, используемый для фона виджета.
### Аргументы

- *const char ** **background** - Путь к файлу текстуры.

## const char * getStyleTextureBackground ( ) const

Возвращает скин, используемый для фона виджета.
### Возвращаемое значение

Path to a texture file.
## void setStyleTextureBorder ( const char * border )

Устанавливает скин, используемый для границы виджета.
### Аргументы

- *const char ** **border** - Путь к файлу текстуры.

## const char * getStyleTextureBorder ( ) const

Возвращает скин, используемый для границы виджета.
### Возвращаемое значение

Path to a texture file.
