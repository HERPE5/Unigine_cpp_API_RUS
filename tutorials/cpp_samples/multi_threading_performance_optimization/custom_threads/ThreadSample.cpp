// Показывает пользовательские подклассы Thread с паттернами бесконечных и подсчитанных итераций.
// Потоки логируют сообщения для демонстрации выполнения; показана корректная обработка завершения.

#include "ThreadSample.h"

#include <UnigineConsole.h>

#include <memory>

using namespace Unigine;
using namespace Unigine::Math;

ThreadSample::InfiniteThread::InfiniteThread() {}
ThreadSample::InfiniteThread::~InfiniteThread() {}

void ThreadSample::InfiniteThread::process()
{
	while (isRunning())
	{
		Log::message("Hello from infinite thread\n");

		sleep(1000);
	}
	Log::message("Infinite thread finished\n");
}


ThreadSample::CountedThread::CountedThread(uint32_t iterations) : iterations(iterations) {}
ThreadSample::CountedThread::~CountedThread() {}

void ThreadSample::CountedThread::process()
{
	for (uint32_t i = 0; i < iterations; ++i)
	{
		Log::message("Hello from counted thread: %u\n", i);

		if (!isRunning())
			break;

		sleep(1000);
	}

	Log::message("Counted thread finished\n");
}

// Sample Logic

REGISTER_COMPONENT(ThreadSample)

// Создаются и запускаются оба типа потоков.
void ThreadSample::init()
{
	// Создаём и запускаем потоки
	// run() внутри вызывает переопределённый process()
	Console::setOnscreen(true);

	infinite_thread = std::make_unique<InfiniteThread>();
	infinite_thread->run();

	counted_thread = std::make_unique<CountedThread>(10);
	counted_thread->run();
}

// Поток со счётчиком останавливается после завершения его итераций.
void ThreadSample::update()
{
	// Останавливаем поток со счётчиком, если он завершил свои итерации
	if (!counted_thread->isRunning())
		counted_thread->stop();
}

// Оба потока останавливаются, консоль скрывается.
void ThreadSample::shutdown()
{
	// Гарантируем корректную остановку обоих потоков при завершении
	Console::setOnscreen(false);
	if (infinite_thread->isRunning())
		infinite_thread->stop();
	if (counted_thread->isRunning())
		counted_thread->stop();
}
