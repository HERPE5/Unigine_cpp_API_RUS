// Демонстрирует встроенные диалоговые виджеты для распространённых взаимодействий UI.
// Включает WidgetDialogMessage, WidgetDialogFile, WidgetDialogColor и WidgetDialogImage.
// Каждый диалог обрабатывает события OK/Cancel с соответствующим логированием результата.

#pragma once

#include <UnigineComponentSystem.h>

// Показывает различные типы диалогов с отображением по нажатию кнопки и обработкой событий.
class Dialogs : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Dialogs, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Файл изображения для демонстрации WidgetDialogImage
	PROP_PARAM(File, image);

private:
	void init();
	void shutdown();

	// Обрабатывает клик по кнопке OK с типом диалога для извлечения результата
	void dialog_ok_clicked(const Unigine::WidgetPtr &widget, int mouse_buttons, Unigine::WidgetDialogPtr dialog, int type);
	// Обрабатывает клик по кнопке Cancel для закрытия диалога
	void dialog_cancel_clicked(const Unigine::WidgetPtr &widget, int mouse_buttons, Unigine::WidgetDialogPtr dialog);
	// Отображает диалог и подключает обработчики событий OK/Cancel
	void dialog_show(const Unigine::WidgetDialogPtr &widget, int type);
	// Создаёт и показывает диалог сообщения
	void button_message_clicked(const Unigine::WidgetPtr &widget, int mouse_buttons, const char *title, const char *message);
	// Создаёт и показывает диалог выбора файла
	void button_file_clicked(const Unigine::WidgetPtr &widget, int mouse_buttons, const char *title, const char *path);
	// Создаёт и показывает диалог выбора цвета
	void button_color_clicked(const Unigine::WidgetPtr &widget, int mouse_buttons, const char *title, Unigine::Math::vec4 color);
	// Создаёт и показывает диалог предпросмотра изображения
	void button_image_clicked(const Unigine::WidgetPtr &widget, int mouse_buttons, const char *title, const char *texture);

	// Окно-контейнер, содержащее кнопки вызова диалогов
	Unigine::WidgetWindowPtr window;
	// Текущий активный экземпляр диалога
	Unigine::WidgetDialogPtr dialog;
};
