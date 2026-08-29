#pragma once

#include <UnigineComponentSystem.h>

#include <atomic>
#include <memory>

// Демонстрирует реализацию пользовательского потока с использованием базового класса Unigine::Thread.
// Показывает два паттерна: поток с бесконечным циклом и поток со счётчиком итераций.
class ThreadSample : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(ThreadSample, ComponentBase)
	COMPONENT_DESCRIPTION("This component demonstrates threaded execution by running one infinite thread "
			"and one counted thread with messages logging.")

	COMPONENT_INIT(init)
	COMPONENT_UPDATE(update)
	COMPONENT_SHUTDOWN(shutdown)

private:
	// Чтобы реализовать собственный поток, унаследуйтесь от класса Unigine::Thread
	// Переопределите метод process() - он будет вызван после запуска потока
	// Запустите ваш поток через метод run()

	// Поток, работающий непрерывно до остановки
	class InfiniteThread final : public Unigine::Thread
	{
	public:
		InfiniteThread();
		~InfiniteThread();

	private:
		void process() override;
	};

	// Поток, работающий заданное количество итераций
	class CountedThread final : public Unigine::Thread
	{
	public:
		CountedThread(uint32_t iterations);
		~CountedThread();

	protected:
		void process() override;

	private:
		uint32_t iterations{0};
	};

private:
	void init();     // создаёт и запускает оба потока
	void update();   // отслеживает завершение потока со счётчиком
	void shutdown(); // останавливает оба потока

private:
	// управляемый экземпляр потока со счётчиком
	std::unique_ptr<CountedThread> counted_thread;

	// управляемый экземпляр бесконечного потока
	std::unique_ptr<InfiniteThread> infinite_thread;
};
