// Демонстрирует базовый файловый ввод-вывод с использованием Unigine::File. Окно Writer сохраняет редактируемый
// текст в файл, окно Reader отображает содержимое файла. Используются режимы "wb"/"rb" для
// бинарно-безопасных операций со строками через writeString/readString.

#include "FilesSample.h"

using namespace Unigine;
using namespace Math;


// Текстовое содержимое записывается в файл в бинарном режиме для хранения строки с префиксом длины.
void writeTextToFile(const String &content, const String &filepath)
{
	const FilePtr file = File::create();

	// Открываем файл в бинарном режиме записи
	if (!file->open(filepath, "wb"))
	{
		Log::error("writeTextToFile: Failed to open file %s\n", filepath.get());
		return;
	}

	// Записываем строку с префиксом длины (формат writeString)
	file->writeString(content.get());

	if (!file->close())
	{
		Log::error("writeTextToFile: Failed to close file %s\n", filepath.get());
	}
}

// Текстовое содержимое считывается из файла в бинарном режиме для чтения строки с префиксом длины.
String readTextFromFile(const String &filepath)
{
	const FilePtr file = File::create();
	// Открываем файл в бинарном режиме чтения
	if (!file->open(filepath, "rb"))
	{
		Log::error("readTextFromFile: Failed to open file %s\n", filepath.get());
		return "";
	}
	// Считываем строку с префиксом длины (формат readString)
	String content = file->readString();

	if (!file->close())
	{
		Log::error("readTextFromFile: Failed to close file %s\n", filepath.get());
	}
	return content;
}


REGISTER_COMPONENT(FilesSample)

// Создаются окна Reader и Writer для демонстрации файлового ввода-вывода.
void FilesSample::init()
{
	create_reader();
	create_writer();
}

// Окна UI освобождаются.
void FilesSample::shutdown()
{
	writer.deleteLater();
	reader.deleteLater();
}

// Создаётся окно Writer с редактируемым текстовым полем и кнопкой сохранения.
void FilesSample::create_writer()
{
	EngineWindowViewportPtr main_window = WindowManager::getMainWindow();
	GuiPtr gui = main_window->getGui();

	// Создаём окно writer
	writer = WidgetWindow::create(gui, "Writer");
	writer->setWidth(300);
	writer->setHeight(150);
	gui->addChild(writer, Gui::ALIGN_OVERLAP);
	writer->setPosition(widget_padding, main_window->getSize().y / 2);

	// Редактируемое текстовое поле предзаполняется текущим содержимым файла
	WidgetEditLinePtr edit_line = WidgetEditLine::create(gui, readTextFromFile(filepath.get()));
	edit_line->setCapacity(1000);
	writer->addChild(edit_line, Gui::ALIGN_TOP | Gui::ALIGN_EXPAND);
	edit_line->setText(readTextFromFile(filepath.get()));

	// Кнопка "Write" сохраняет текущий текст в файл при нажатии
	WidgetButtonPtr write_button = WidgetButton::create(gui, "Write");
	write_button->getEventClicked().connect(*this, [edit_line, this] {
		const char *content = edit_line->getText();
		writeTextToFile(content, filepath.get());
	});
	writer->addChild(write_button, Gui::ALIGN_CENTER | Gui::ALIGN_BOTTOM);
}

// Создаётся окно Reader с меткой только для чтения и кнопкой обновления.
void FilesSample::create_reader()
{
	EngineWindowViewportPtr main_window = WindowManager::getMainWindow();
	GuiPtr gui = main_window->getGui();

	// Создаём окно reader
	reader = WidgetWindow::create(gui, "Reader");
	reader->setWidth(300);
	reader->setHeight(150);
	gui->addChild(reader, Gui::ALIGN_OVERLAP);
	reader->setPosition(main_window->getSize().x - reader->getWidth() - widget_padding,
		main_window->getSize().y / 2);

	// Метка отображает содержимое файла (отображение только для чтения)
	WidgetLabelPtr label = WidgetLabel::create(gui, "");
	label->setEnabled(false);
	reader->addChild(label, Gui::ALIGN_TOP | Gui::ALIGN_EXPAND);

	// Кнопка "Read" перезагружает текст из файла при нажатии
	WidgetButtonPtr read_button = WidgetButton::create(gui, "Read");

	// Лямбда захватывает метку и перезагружает содержимое файла
	const auto read_file = [label, this] {
		label->setText(readTextFromFile(filepath.get()));
	};

	read_button->getEventClicked().connect(*this, read_file);
	// Первоначальная загрузка содержимого файла
	read_file();
	reader->addChild(read_button, Gui::ALIGN_CENTER | Gui::ALIGN_BOTTOM);
}
