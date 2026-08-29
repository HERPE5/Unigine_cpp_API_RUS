# Unigine::WidgetDialogColor Class (CPP)

**Header:** #include <UnigineWidgets.h>

**Inherits from:** WidgetDialog


Этот класс создаёт диалог с кликабельным полем цвета, слайдерами значений RGB, параметрами цвета и предопределённой палитрой. Доступны два формата цвета:

- Стандартный формат, представляющий цвета как четырёхкомпонентные векторы.
- Веб-формат, допускающий следующие варианты: *RRGGBB*, *RRGGBBAA*, *#RRGGBB*, *#RRGGBBAA*.


## WidgetDialogColor Class

### Методы класса

---

## static WidgetDialogColorPtr create ( const Ptr < Gui > & gui , const char * str = 0 )

Конструктор. Создаёт диалог выбора цвета с указанными параметрами и добавляет его в указанный GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - [GUI](../../../api/library/gui/class.gui_cpp.md), которому будет принадлежать диалог.
- *const char ** **str** - Заголовок диалога. Это опциональный параметр.

## static WidgetDialogColorPtr create ( const char * str = 0 )

Конструктор. Создаёт диалог выбора цвета с указанными параметрами и добавляет его в GUI движка.
### Аргументы

- *const char ** **str** - Заголовок диалога. Это опциональный параметр.

## void setColor ( const Math:: vec4 & color )

Выбирает указанный цвет.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет.

## Math:: vec4 getColor ( ) const

Возвращает текущий выбранный цвет.
### Возвращаемое значение

Текущий цвет.
## void setPaletteColors ( const char * colors )

Заполняет палитру указанными цветами.
### Аргументы

- *const char ** **colors** - Список цветов в веб-формате, разделённых точкой с запятой.

## const char * getPaletteColors ( ) const

Возвращает текущие цвета палитры.
### Возвращаемое значение

Список цветов в веб-формате, разделённых точкой с запятой.
## void setWebColor ( const char * color )

Выбирает цвет в веб-формате.
### Аргументы

- *const char ** **color** - Цвет в веб-формате.

## const char * getWebColor ( ) const

Возвращает текущий выбранный цвет в веб-формате.
### Возвращаемое значение

Текущий цвет.
