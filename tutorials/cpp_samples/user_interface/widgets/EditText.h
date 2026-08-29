// Демонстрирует многострочный текстовый ввод с использованием WidgetEditText. Изменения текста
// отслеживаются через callback EventChanged и отображаются в оверлее консоли.
// Размеры виджета и размер шрифта настраиваются через свойства компонента.

#pragma once
#include <UnigineComponentSystem.h>

// Создаёт многострочное поле ввода текста с уведомлением об изменении.
class EditText : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(EditText, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Позиция на экране в пикселях
	PROP_PARAM(Vec2, position, Unigine::Math::vec2(250, 150));
	// Размеры виджета в пикселях
	PROP_PARAM(Vec2, size, Unigine::Math::vec2(150, 100));
	// Начальный текст-заполнитель
	PROP_PARAM(String, text, "Enter text...");
	// Размер шрифта для вводимого текста
	PROP_PARAM(Int, font_size, 16)

private:
	void init();
	void shutdown();

	// Контекст GUI для создания виджета
	Unigine::GuiPtr gui;
	// Экземпляр виджета многострочного текстового ввода
	Unigine::WidgetEditTextPtr widget_edittext;
};
