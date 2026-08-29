# Unigine::WidgetDialog Class (CPP)

**Header:** #include <UnigineWidgets.h>

**Inherits from:** WidgetWindow


Этот класс создаёт [dialog window](../../../code/gui/ui/ui_containers.md#dialog).

Объект этого класса выглядит следующим образом:


![](../../../code/gui/ui/widgets/dialog.png)


### См. также


- Пример C++


## WidgetDialog Class

### Методы класса

---

## static WidgetDialogPtr create ( const Ptr < Gui > & gui , const char * str = 0 , int x = 0 , int y = 0 )

Конструктор. Создаёт диалоговое окно с указанными параметрами и добавляет его в указанный GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - [GUI](../../../api/library/gui/class.gui_cpp.md), которому будет принадлежать диалог.
- *const char ** **str** - Заголовок окна. Это опциональный параметр.
- *int* **x** - Горизонтальное расстояние между виджетами в окне и между ними и границей окна. Это опциональный параметр.
- *int* **y** - Вертикальное расстояние между виджетами в окне и между ними и границей окна. Это опциональный параметр.

## static WidgetDialogPtr create ( const char * str = 0 , int x = 0 , int y = 0 )

Конструктор. Создаёт диалоговое окно с указанными параметрами и добавляет его в GUI движка.
### Аргументы

- *const char ** **str** - Заголовок окна. Это опциональный параметр.
- *int* **x** - Горизонтальное расстояние между виджетами в окне и между ними и границей окна. Это опциональный параметр.
- *int* **y** - Вертикальное расстояние между виджетами в окне и между ними и границей окна. Это опциональный параметр.

## Ptr < WidgetButton > getCancelButton ( ) const

Возвращает кнопку, отменяющую действие.
### Возвращаемое значение

Кнопка отмены.
## int isCancelClicked ( ) const

Возвращает значение, указывающее, нажата ли кнопка отмены.
### Возвращаемое значение

1, если кнопка отмены нажата; иначе 0.
## void setCancelText ( const char * text )

Sets a caption of the Кнопка отмены.
### Аргументы

- *const char ** **text** - Подпись кнопки отмены.

## const char * getCancelText ( ) const

Returns the caption of the Кнопка отмены. The default is Cancel.
### Возвращаемое значение

Подпись кнопки отмены.
## Ptr < WidgetButton > getCloseButton ( ) const

Возвращает кнопку, закрывающую действие.
### Возвращаемое значение

Кнопка закрытия.
## int isCloseClicked ( ) const

Возвращает значение, указывающее, нажата ли кнопка закрытия.
### Возвращаемое значение

1, если кнопка закрытия нажата; иначе 0.
## void setCloseText ( const char * text )

Sets a caption of the Кнопка закрытия.
### Аргументы

- *const char ** **text** - Подпись кнопки закрытия.

## const char * getCloseText ( ) const

Returns the caption of the Кнопка закрытия. The default is empty.
### Возвращаемое значение

Подпись кнопки закрытия.
## bool isDone ( ) const

Возвращает значение, указывающее, закрыто ли диалоговое окно.
### Возвращаемое значение

**1**, если диалоговое окно закрыто; иначе **0**.
## Ptr < WidgetButton > getOkButton ( ) const

Возвращает кнопку, подтверждающую действие.
### Возвращаемое значение

Кнопка OK.
## bool isOkClicked ( ) const

Возвращает значение, указывающее, нажата ли кнопка OK.
### Возвращаемое значение

true, если кнопка OK нажата; иначе false.
## void setOkText ( const char * text )

Sets a caption of the Кнопка OK.
### Аргументы

- *const char ** **text** - Подпись кнопки OK.

## const char * getOkText ( ) const

Returns the caption of the Кнопка OK. The default is OK.
### Возвращаемое значение

Подпись кнопки OK.
## int getResult ( ) const

Возвращает значение, указывающее, какая кнопка была нажата.
### Возвращаемое значение

1, если нажата кнопка OK; -1, если нажата кнопка отмены; 0, если нажата кнопка закрытия.
