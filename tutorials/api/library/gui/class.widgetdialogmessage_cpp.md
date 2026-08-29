# Unigine::WidgetDialogMessage Class (CPP)

**Header:** #include <UnigineWidgets.h>

**Inherits from:** WidgetDialog


Этот класс создаёт диалоговое окно, содержащее текстовую строку сообщения.


## WidgetDialogMessage Class

### Методы класса

---

## static WidgetDialogMessagePtr create ( const Ptr < Gui > & gui , const char * str = 0 )

Конструктор. Создаёт диалог сообщения с указанными параметрами и добавляет его в указанный GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - [GUI](../../../api/library/gui/class.gui_cpp.md), которому будет принадлежать диалог.
- *const char ** **str** - Заголовок диалога. Это опциональный параметр.

## static WidgetDialogMessagePtr create ( const char * str = 0 )

Конструктор. Создаёт диалог сообщения с указанными параметрами и добавляет его в GUI движка.
### Аргументы

- *const char ** **str** - Заголовок диалога. Это опциональный параметр.

## void setMessageFont ( const char * name )

Устанавливает шрифт, используемый для отображения текстового сообщения в виджете.
### Аргументы

- *const char ** **name** - Имя шрифта.

## void setMessageFontColor ( const Math:: vec4 & color )

Устанавливает цвет шрифта, используемого для отображения текстового сообщения в виджете.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет шрифта.

## void setMessageFontRich ( int rich )

Устанавливает значение, указывающее, должно ли использоваться форматирование rich text для текстового сообщения в виджете.
### Аргументы

- *int* **rich** - Положительное число для использования форматирования rich text, 0 для использования обычного текстового форматирования.

## void setMessageFontSize ( int size )

Устанавливает размер шрифта, используемого для отображения текстового сообщения в виджете.
### Аргументы

- *int* **size** - Размер шрифта.

## void setMessageHidden ( bool hidden )

Скрывает или показывает текстовое сообщение в виджете.
### Аргументы

- *bool* **hidden** - true, чтобы скрыть текстовое сообщение, false — чтобы показать его.

## bool isMessageHidden ( ) const

Возвращает значение, указывающее, скрыто ли текстовое сообщение в виджете или показано.
### Возвращаемое значение

Возвращает 1, если текстовое сообщение скрыто; иначе 0.
## void setMessageText ( const char * text )

Устанавливает текстовое сообщение диалога.
### Аргументы

- *const char ** **text** - Сообщение.

## const char * getMessageText ( ) const

Возвращает текстовое сообщение диалога. Значение по умолчанию совпадает с заголовком диалога.
### Возвращаемое значение

Текстовое сообщение.
