// Демонстрирует загрузку раскладок UI из внешних файлов .ui через класс UserInterface.
// Виджеты получаются по имени и подключаются к callback'ам. Menubox включает
// опцию выхода, которая выполняет консольную команду для завершения приложения.

#include "UserInterface.h"

#include <UnigineConsole.h>

REGISTER_COMPONENT(UserInterface);

// Раскладка UI загружается из файла, виджеты подключаются к обработчикам событий.
void UserInterface::init()
{
	if (Unigine::String::isEmpty(ui_file.get()))
	{
		Unigine::Log::warning("UserInterface::init(): ui_file is not assigned.\n");
		return;
	}

	Unigine::GuiPtr gui = Unigine::WindowManager::getMainWindow()->getGui();

	// Разбираем XML-файл .ui и создаём иерархию виджетов
	user_interface = Unigine::UserInterface::create(gui, ui_file.get());
	if (user_interface == nullptr)
	{
		Unigine::Log::warning("UserInterface::init(): can't created UserInterface.\n");
	}

	// получаем виджеты по имени из загруженной раскладки UI и подключаем обработчики событий
	Unigine::WidgetPtr edittext = user_interface->getWidgetByName("edittext");
	if (edittext != nullptr)
	{
		edittext->getEventChanged().connect(this, &UserInterface::edittext_changed);
	}

	Unigine::WidgetPtr menubox_0 = user_interface->getWidgetByName("menubox_0");
	if (menubox_0 != nullptr)
	{
		menubox_0->getEventClicked().connect(this, &UserInterface::menubox_0_clicked);
	}

	// findWidget возвращает индекс, который можно использовать с getWidget
	int index = user_interface->findWidget("window");
	if (index != -1)
	{
		window = user_interface->getWidget(index);
		// arrange() пересчитывает позиции дочерних виджетов перед добавлением в GUI
		window->arrange();
		Unigine::WindowManager::getMainWindow()->addChild(window, Unigine::Gui::ALIGN_OVERLAP | Unigine::Gui::ALIGN_CENTER);
	}

	Unigine::Console::setOnscreen(true);
}

// Виджет окна и раскладка UI освобождаются.
void UserInterface::shutdown()
{
	if (window)
		window.deleteLater();

	if(user_interface)
		user_interface.deleteLater();

	Unigine::Console::setOnscreen(false);
}

// Событие изменения текста логируется для демонстрации привязки callback'ов.
void UserInterface::edittext_changed(const Unigine::WidgetPtr &widget)
{
	Unigine::WidgetEditTextPtr edittext = Unigine::checked_ptr_cast<Unigine::WidgetEditText>(widget);
	Unigine::Log::message("EditText changed: %s\n", edittext->getText());
}

// Выбор меню логируется, для элемента с индексом 2 выполняется команда выхода.
void UserInterface::menubox_0_clicked(const Unigine::WidgetPtr &widget)
{
	Unigine::WidgetMenuBoxPtr menubox = Unigine::checked_ptr_cast<Unigine::WidgetMenuBox>(widget);
	Unigine::Log::message("MenuBox clicked: %s\n", menubox->getCurrentItemText());
	// Индекс элемента 2 соответствует опции "Quit" в раскладке меню
	if (menubox->getCurrentItem() == 2)
		Unigine::Console::run("quit");
}
