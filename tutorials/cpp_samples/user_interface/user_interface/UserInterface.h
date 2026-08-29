// Загружает раскладки GUI из внешних XML-файлов .ui с помощью класса UserInterface.
// Виджеты получаются по имени для привязки событий. Демонстрирует динамическую
// загрузку UI без жёсткого задания создания виджетов в коде.

#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineUserInterface.h>

// Управляет раскладкой UI, загруженной из внешнего файла, с callback'ами событий виджетов.
class UserInterface : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(UserInterface, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Путь к XML-файлу .ui, содержащему определение раскладки виджетов
	PROP_PARAM(File, ui_file);

private:
	void init();
	void shutdown();

	// Callback, вызываемый при изменении содержимого текстового поля
	void edittext_changed(const Unigine::WidgetPtr &widget);
	// Callback, вызываемый при клике по элементу menubox
	void menubox_0_clicked(const Unigine::WidgetPtr &widget);

	// Загруженная раскладка UI, содержащая определения виджетов
	Unigine::UserInterfacePtr user_interface;
	// Виджет главного окна из загруженной раскладки
	Unigine::WidgetPtr window;
};