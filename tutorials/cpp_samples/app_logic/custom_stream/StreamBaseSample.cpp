// Демонстрирует реализацию пользовательского потока путём оборачивания функций C stdio
// интерфейсом StreamBase. Пользовательские потоки позволяют интегрировать внешние источники I/O
// (сеть, сжатие, шифрование) с системой сериализации Unigine.

#include "StreamBaseSample.h"
#include <UnigineConsole.h>

// Файловый поток открывается по указанному пути с заданным режимом.
MyFile::MyFile(const char *path, const char *mode)
{
	const Unigine::String absolute_path = Unigine::FileSystem::getAbsolutePath(path);
	file = fopen(absolute_path, mode);
}

// Дескриптор файла закрывается при уничтожении потока.
MyFile::~MyFile()
{
	if (file)
		fclose(file);
}

// Возвращается ненулевое значение, если файл был успешно открыт.
int MyFile::isOpened()
{
	return file != nullptr;
}

// Возвращается ненулевое значение, если данные доступны для чтения (не достигнут EOF).
int MyFile::isAvailable()
{
	return file && feof(file) == 0;
}

// Данные считываются из файла в буфер; возвращается количество считанных элементов.
size_t MyFile::read(void *ptr, size_t size, size_t nmemb)
{
	return fread(ptr, size, nmemb, file);
}

// Данные записываются из буфера в файл; возвращается количество записанных элементов.
size_t MyFile::write(const void *ptr, size_t size, size_t nmemb)
{
	return fwrite(ptr, size, nmemb, file);
}

// Пользовательский поток демонстрируется путём записи и чтения типизированных данных.
void StreamBaseSample::sample()
{
	Unigine::String file_str = filepath.get();
	if (file_str.size() <= 0)
	{
		Unigine::Log::error("StreamBaseSample::sample(): Filepath param is empty!");
		return;
	}

	Unigine::Console::setOnscreen(true);

	// Данные записываются в файл с помощью пользовательского потока
	{
		MyFile file(file_str, "wb");
		Unigine::StreamPtr stream = file.getStream();
		stream->writeString("Some string");
		stream->writeInt(42);
		stream->writeFloat(3.14f);
	}

	// Данные считываются обратно из файла с помощью пользовательского потока
	{
		MyFile file(file_str, "rb");
		Unigine::StreamPtr stream = file.getStream();
		Unigine::Log::message("%s\n", stream->readString().get());
		Unigine::Log::message("%d\n", stream->readInt());
		Unigine::Log::message("%f\n", stream->readFloat());
	}
}

// Консоль на экране отключается.
void StreamBaseSample::shutdown()
{
	Unigine::Console::setOnscreen(false);
}

REGISTER_COMPONENT(StreamBaseSample)
