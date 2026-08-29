// Демонстрирует однострочный текстовый ввод с использованием WidgetEditLine. Изменения текста
// отслеживаются через callback EventChanged и отображаются в оверлее консоли.
// Размер виджета и шрифт настраиваются через свойства компонента.

#pragma once
#include <UnigineComponentSystem.h>

// Создаёт однострочное поле ввода текста с уведомлением об изменении.
class EditLine : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(EditLine, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Позиция на экране в пикселях
	PROP_PARAM(Vec2, position, Unigine::Math::vec2(750, 50));
	// Размеры виджета в пикселях
	PROP_PARAM(Vec2, size, Unigine::Math::vec2(150, 30));
	// Начальный текст-заполнитель
	PROP_PARAM(String, text, "Enter text...");
	// Размер шрифта для вводимого текста
	PROP_PARAM(Int, font_size, 16)

private:
	void init();
	void shutdown();

	// Контекст GUI для создания виджета
	Unigine::GuiPtr gui;
	// Экземпляр виджета строки ввода
	Unigine::WidgetEditLinePtr widget_editline;
};
