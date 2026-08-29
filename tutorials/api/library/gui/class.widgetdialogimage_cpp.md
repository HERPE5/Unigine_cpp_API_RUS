# Unigine::WidgetDialogImage Class (CPP)

**Header:** #include <UnigineWidgets.h>

**Inherits from:** WidgetDialog


Этот класс создаёт диалоговое окно с предпросмотром изображения с регулируемым масштабом.


## WidgetDialogImage Class

### Методы класса

---

## static WidgetDialogImagePtr create ( const Ptr < Gui > & gui , const char * str = 0 )

Конструктор. Создаёт диалог изображения с указанными параметрами и добавляет его в указанный GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - [GUI](../../../api/library/gui/class.gui_cpp.md), которому будет принадлежать диалог.
- *const char ** **str** - Заголовок диалога. Это опциональный параметр.

## static WidgetDialogImagePtr create ( const char * str = 0 )

Конструктор. Создаёт диалог изображения с указанными параметрами и добавляет его в GUI движка.
### Аргументы

- *const char ** **str** - Заголовок диалога. Это опциональный параметр.

## void setImage ( const Ptr < Image > & image )

Устанавливает изображение, предпросмотр и свойства которого должны отображаться в диалоге.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)> &* **image** - Устанавливаемое изображение.

## Ptr < Image > getImage ( ) const

Возвращает изображение, предпросмотр и свойства которого отображаются в диалоге.
### Возвращаемое значение

Изображение, предпросмотр и свойства которого отображаются в диалоге.
## void setTexture ( const char * texture )

Устанавливает имя изображения, предпросмотр и свойства которого должны отображаться в диалоге.
### Аргументы

- *const char ** **texture** - Путь к файлу изображения.

## const char * getTexture ( ) const

Возвращает имя изображения, предпросмотр и свойства которого отображаются в диалоге.
### Возвращаемое значение

Путь к файлу изображения.
