# Unigine::WidgetButton Class (CPP)

**Header:** #include <UnigineWidgets.h>

**Inherits from:** Widget


Интерфейс для работы с виджетом кнопки.


Объект этого класса выглядит следующим образом:


![](../../../code/gui/ui/widgets/button.png)


Ниже приведён пример двух кнопок. Button1 имеет фон и изображение, Button2 — без них:


![](../../../code/gui/ui/examples/button.png)


> **Notice:** Кнопка автоматически растягивается или сжимается, чтобы соответствовать размеру текущей текстуры/изображения. При изменении размера кнопки размер изображения не меняется. Если вам нужно создать тип виджета кнопки с автоматически подстраиваемым размером изображения или поворотом изображения, рассмотрите вместо этого *[Widget Sprite](../../../api/library/gui/class.widgetsprite_cpp.md)*.


#### См. также


- Пример C++
- Пример UnigineScript


### Пример


Следующий код демонстрирует, как создать виджет кнопки и задать его параметры.


```cpp
#include <UnigineWidgets.h>
#include <UnigineUserInterface.h>
using namespace Unigine;

/* .. */

// функция-обработчик события
int onButtonClicked()
{
	/* .. */

	return 1;
}

/* .. */

// получаем указатель на системный GUI
GuiPtr gui = Gui::getCurrent();

// создаём виджет кнопки и задаём её подпись
WidgetButtonPtr widget_button = WidgetButton::create(gui, "Delete");

// задаём подсказку
widget_button->setToolTip("Delete object(s)");

// перестраиваем размер кнопки
widget_button->arrange();

// задаём позицию кнопки
widget_button->setPosition(10, 10);

// задаём функцию onButtonClicked для обработки события CLICKED
widget_button->getEventClicked().connect(onButtonClicked);

// добавляем созданный виджет кнопки в системный GUI
gui->addChild(widget_button, Gui::ALIGN_OVERLAP | Gui::ALIGN_FIXED);

```


## WidgetButton Class

### Методы класса

---

## static WidgetButtonPtr create ( const Ptr < Gui > & gui , const char * str = 0 )

Конструктор. Создаёт кнопку с указанной подписью и добавляет её в указанный GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - [GUI](../../../api/library/gui/class.gui_cpp.md), которому будет принадлежать новая кнопка.
- *const char ** **str** - Подпись кнопки. Это опциональный параметр.

## static WidgetButtonPtr create ( const char * str = 0 )

Конструктор. Создаёт кнопку с указанной подписью и добавляет её в GUI движка.
### Аргументы

- *const char ** **str** - Подпись кнопки. Это опциональный параметр.

## void setBackground ( int background )

Устанавливает значение, указывающее, должна ли отрисовываться фоновая текстура для кнопки. По умолчанию фоновая текстура всегда отрисовывается. Значение по умолчанию — 1.
### Аргументы

- *int* **background** - 1, чтобы отрисовывать фоновую текстуру, 0 — не отрисовывать. Значение по умолчанию — 1.

## int getBackground ( ) const

Возвращает значение, указывающее, отрисовывается ли фоновая текстура для кнопки. Значение по умолчанию — 1.
### Возвращаемое значение

1, если фоновая текстура отрисовывается; иначе 0.
## void setImage ( const Ptr < Image > & image )

Устанавливает новое изображение для кнопки.
> **Notice:** The button is automatically stretched or shrinked to match the size of the current image. When you resize the button the size of the image does not change. In case you need to create a type of button widget with an auto-adjusted image size, or image rotation, please consider *[Widget Sprite](../../../api/library/gui/class.widgetsprite_cpp.md)* instead.

### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)> &* **image** - Устанавливаемое изображение.

## Ptr < Image > getImage ( ) const

Возвращает текущее изображение кнопки.
> **Notice:** The button is automatically stretched or shrinked to match the size of the current image. When you resize the button the size of the image does not change. In case you need to create a type of button widget with an auto-adjusted image size, or image rotation, please consider *[Widget Sprite](../../../api/library/gui/class.widgetsprite_cpp.md)* instead.

### Возвращаемое значение

Изображение кнопки.
## void setText ( const char * text )

Устанавливает текстовую подпись кнопки.
### Аргументы

- *const char ** **text** - Подпись кнопки.

## const char * getText ( ) const

Возвращает текстовую подпись кнопки.
### Возвращаемое значение

Подпись кнопки.
## void setTextAlign ( int align )

Устанавливает выравнивание подписи кнопки.
### Аргументы

- *int* **align** - Одно из значений перечисления Gui:: с префиксом ALIGN_*.

## int getTextAlign ( ) const

Возвращает выравнивание подписи кнопки.
### Возвращаемое значение

Выравнивание подписи кнопки: одно из значений перечисления Gui:: с префиксом ALIGN_*.
## void setTexture ( const char * texture )

Устанавливает новую текстуру, используемую как изображение кнопки.
> **Notice:** The button is automatically stretched or shrinked to match the size of the current image. When you resize the button the size of the image does not change. In case you need to create a type of button widget with an auto-adjusted image size, or image rotation, please consider *[Widget Sprite](../../../api/library/gui/class.widgetsprite_cpp.md)* instead.

### Аргументы

- *const char ** **texture** - Путь к файлу текстуры.

## const char * getTexture ( ) const

Возвращает путь к текущей текстуре изображения кнопки.
> **Notice:** The button is automatically stretched or shrinked to match the size of the current image. When you resize the button the size of the image does not change. In case you need to create a type of button widget with an auto-adjusted image size, or image rotation, please consider *[Widget Sprite](../../../api/library/gui/class.widgetsprite_cpp.md)* instead.

### Возвращаемое значение

Путь к текстуре изображения кнопки.
## void setToggleable ( bool toggleable )

Устанавливает значение, указывающее, является ли кнопка переключателем или простой кнопкой.
### Аргументы

- *bool* **toggleable** - 1, чтобы сделать кнопку переключателем, 0 — простой кнопкой. Значение по умолчанию — 0.

## bool isToggleable ( ) const

Возвращает значение, указывающее, является ли кнопка переключателем или простой кнопкой. Значение по умолчанию — 0.
### Возвращаемое значение

1, если кнопка является переключателем; иначе 0.
## void setToggled ( bool toggled )

Устанавливает состояние кнопки-переключателя.
### Аргументы

- *bool* **toggled** - 1, чтобы нажать кнопку, 0 — чтобы отпустить.

## bool isToggled ( ) const

Возвращает значение, указывающее, нажата ли кнопка-переключатель.
### Возвращаемое значение

true, если кнопка нажата; иначе false.
## void setButtonColor ( const Math:: vec4 & color )

Устанавливает цвет, используемый для кнопки.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Четырёхкомпонентный вектор, задающий цвет в формате RGBA.

## Math:: vec4 getButtonColor ( ) const

Возвращает текущий цвет кнопки.
### Возвращаемое значение

Четырёхкомпонентный вектор, задающий цвет в формате RGBA.
## void setStyleImage ( const Ptr < Image > & image )

Устанавливает изображение скина кнопки.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)> &* **image** - Устанавливаемое изображение.

## Ptr < Image > getStyleImage ( ) const

Возвращает изображение скина кнопки.
### Возвращаемое значение

Изображение скина кнопки.
## void setStyleTexture ( const char * texture )

Устанавливает текстуру скина кнопки.
### Аргументы

- *const char ** **texture** - Путь к файлу текстуры.

## const char * getStyleTexture ( ) const

Возвращает путь к текстуре скина кнопки.
### Возвращаемое значение

Путь к файлу текстуры.
