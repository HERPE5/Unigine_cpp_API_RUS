#pragma once
#include <UnigineComponentSystem.h>

// Демонстрирует реализацию пользовательского потока путём расширения StreamBase.
// StreamBase предоставляет абстрактный интерфейс для бинарного I/O, который может обернуть
// любой базовый источник данных. Здесь стандартные операции C FILE оборачиваются
// для интеграции с потоковым API UNIGINE (readString, writeInt и т.д.).

// Пользовательская реализация потока для бинарного I/O файлов с использованием stdio FILE.
// Оборачивает fopen/fread/fwrite для обеспечения совместимости со StreamBase.
class MyFile final : public Unigine::StreamBase
{
public:
	MyFile(const char *path, const char *mode);
	~MyFile() override;
	int isOpened() override;
	int isAvailable() override;
	size_t read(void *ptr, size_t size, size_t nmemb) override;
	size_t write(const void *ptr, size_t size, size_t nmemb) override;

private:
	FILE *file;
};

class StreamBaseSample final : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(StreamBaseSample, ComponentBase)
	COMPONENT_DESCRIPTION("This component demonstrates custom file streaming by implementing a wrapper "
							"around standard file I/O.")

	COMPONENT_INIT(sample)
	COMPONENT_SHUTDOWN(shutdown)

	// параметр пути к файлу (задаётся в редакторе)
	PROP_PARAM(File, filepath)

private:
	void sample();
	void shutdown();
};
