# Unigine::WidgetDialogFile Class (CPP)

**Header:** #include <UnigineWidgets.h>

**Inherits from:** WidgetDialog


Этот класс создаёт диалоговое окно, в котором выбирается файл. С левой стороны отображается информация о файле или предпросмотр изображения.


### Пример


Следующий код демонстрирует, как создать виджет диалога выбора файла и использовать его для выбора файлов. Добавьте приведённый ниже код в соответствующие файлы вашего проекта (`AppWorldLogic.h` и `AppWorldLogic.cpp`).


<details>
<summary>AppWorldLogic.h | Close</summary>

`AppWorldLogic.h`


```cpp
class AppWorldLogic : public Unigine::WorldLogic
{

	// ... //

private:
	// объявляем используемые виджеты и функции обратного вызова для них
	Unigine::WidgetLabelPtr file_name;
	Unigine::WidgetButtonPtr open_button;
	Unigine::WidgetDialogFilePtr file_dialog;
	void on_button_clicked(const Unigine::WidgetPtr & widget,  int mouse_buttons);
	void dialog_ok_clicked();
	void dialog_cancel_clicked();

	Unigine::EventConnections connection;
};


```

</details>


<details>
<summary>AppWorldLogic.cpp | Close</summary>

`AppWorldLogic.cpp`


```cpp
#include "AppWorldLogic.h"
#include <UnigineFileSystem.h>

using namespace Unigine;

// обратный вызов, срабатывающий при нажатии кнопки, отображающей диалог выбора файла
void AppWorldLogic::on_button_clicked(const WidgetPtr & widget, int mouse_buttons)
{
	// сбрасываем выбор файла, показываем диалог и устанавливаем на него постоянный фокус
	file_dialog->setFile("");
	file_dialog->setHidden(0);
	file_dialog->setPermanentFocus();
}

// обратный вызов, срабатывающий при нажатии кнопки Ok диалога выбора файла
void AppWorldLogic::dialog_ok_clicked()
{
	// получаем текущий выбранный путь из диалога и проверяем, существует ли файл
	String path = file_dialog->getFile();
	if (!FileSystem::isFileExist(path))
		return;

	// если файл существует, скрываем диалог, отображаем выбранный файл в метке "file_name" и снимаем фокус
	file_dialog->setHidden(1);
	file_name->setText(path);
	file_dialog->removeFocus();
}

// обратный вызов, срабатывающий при нажатии кнопки Cancel диалога выбора файла
void AppWorldLogic::dialog_cancel_clicked()
{
	file_dialog->setHidden(1);
	file_dialog->removeFocus();
}

int AppWorldLogic::init()
{
	// получаем указатель на системный GUI
	GuiPtr gui = Gui::getCurrent();

	// создаём виджет метки для отображения файла, выбранного через диалог
	file_name = WidgetLabel::create(gui, "No file selected yet");
	gui->addChild(file_name, Gui::ALIGN_TOP | Gui::ALIGN_BACKGROUND);

	// создаём виджет кнопки для отображения диалога выбора файла
	open_button = WidgetButton::create(gui, "Select an image file on disk");
	gui->addChild(open_button, Gui::ALIGN_TOP | Gui::ALIGN_BACKGROUND);


	// задаём функцию "on_button_clicked" для обработки события CLICKED для кнопки
	open_button->getEventClicked().connect(connection, this, &AppWorldLogic::on_button_clicked);

	// создаём виджет диалога выбора файла и задаём его подпись, путь по умолчанию и фильтр расширений файлов для отображения только *.png и *.jpeg файлов
	file_dialog = WidgetDialogFile::create(gui, "File open dialog");
	file_dialog->setPath("./");
	file_dialog->setFilter(".png.jpeg");

	// задаём функцию "dialog_ok_clicked" для обработки события CLICKED кнопки Ok диалога
	file_dialog->getOkButton()->getEventClicked().connect(connection, this, &AppWorldLogic::dialog_ok_clicked);

	// задаём функцию "dialog_cancel_clicked" для обработки события CLICKED кнопки Cancel диалога
	file_dialog->getCancelButton()->getEventClicked().connect(connection, this, &AppWorldLogic::dialog_cancel_clicked);

	// добавляем созданный виджет диалога выбора файла в системный GUI и скрываем его
	file_dialog->setHidden(1);
	gui->addChild(file_dialog, Gui::ALIGN_OVERLAP | Gui::ALIGN_CENTER);

	return 1;
}


```

</details>


## WidgetDialogFile Class

### Методы класса

---

## static WidgetDialogFilePtr create ( const Ptr < Gui > & gui , const char * str = 0 )

Конструктор. Создаёт диалог выбора файла с указанными параметрами и добавляет его в указанный GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - [GUI](../../../api/library/gui/class.gui_cpp.md), которому будет принадлежать диалог.
- *const char ** **str** - Заголовок диалога. Это опциональный параметр.

## static WidgetDialogFilePtr create ( const char * str = 0 )

Конструктор. Создаёт диалог выбора файла с указанными параметрами и добавляет его в GUI движка.
### Аргументы

- *const char ** **str** - Заголовок диалога. Это опциональный параметр.

## void setFile ( const char * file )

Выбирает указанный файл в диалоге выбора файла.
### Аргументы

- *const char ** **file** - Абсолютный или относительный (к папке data) путь.

## const char * getFile ( ) const

Возвращает текущий выбранный файл.
### Возвращаемое значение

Путь к файлу.
## void setFilter ( const char * filter )

Устанавливает фильтр имён файлов, используемый для отображения файлов только нужных типов.
### Аргументы

- *const char ** **filter** - Список расширений файлов с ведущими точками и без дополнительных разделителей, например: .mesh.smesh.

## const char * getFilter ( ) const

Возвращает текущий используемый фильтр имён файлов.
### Возвращаемое значение

Список расширений файлов с ведущими точками и без дополнительных разделителей, например: .mesh.smesh.
## void setPath ( const char * path )

Устанавливает путь к папке, содержимое которой должно отображаться в диалоге выбора файла.
### Аргументы

- *const char ** **path** - Абсолютный или относительный (к папке data) путь.

## const char * getPath ( ) const

Возвращает текущий путь к папке, содержимое которой отображается в диалоге выбора файла.
### Возвращаемое значение

Текущий путь к папке.
## void setTabs ( const char * tabs )

Добавляет набор вкладок в диалог выбора файла. Вкладки позволяют пользователю взаимодействовать с несколькими папками одновременно.
### Аргументы

- *const char ** **tabs** - Список путей, разделённых точкой с запятой. Каждый путь соответствует вкладке.

## const char * getTabs ( ) const

Возвращает список вкладок в диалоге выбора файла. Вкладки позволяют пользователю взаимодействовать с несколькими папками одновременно.
### Возвращаемое значение

Список путей, разделённых точкой с запятой. Каждый путь соответствует вкладке.
