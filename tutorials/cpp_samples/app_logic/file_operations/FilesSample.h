#pragma once

#include <UnigineComponentSystem.h>

// Демонстрирует файловый ввод-вывод с использованием класса File.
// Предоставляет простой UI в стиле блокнота с отдельными окнами чтения/записи.
// Файлы хранятся в директории данных проекта.
class FilesSample : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(FilesSample, Unigine::ComponentBase)
	COMPONENT_DESCRIPTION("This component demonstrates basic file I/O by providing a GUI with two windows: "
							"a writer to save text into a file and a reader to display the file contents.")

	COMPONENT_INIT(init)
	COMPONENT_SHUTDOWN(shutdown)

	// путь к файлу, используемый для чтения и записи
	PROP_PARAM(String, filepath, "cpp_samples/app_logic/files/generated_file")

private:
	void init();
	void shutdown();

	void create_writer(); // создаёт редактируемое текстовое окно с кнопкой сохранения
	void create_reader(); // создаёт окно отображения только для чтения с кнопкой обновления

private:
	Unigine::WidgetWindowPtr reader; // окно, отображающее содержимое файла
	Unigine::WidgetWindowPtr writer; // окно для редактирования и сохранения текста

	int widget_padding = 30; // отступ от краёв экрана
};
