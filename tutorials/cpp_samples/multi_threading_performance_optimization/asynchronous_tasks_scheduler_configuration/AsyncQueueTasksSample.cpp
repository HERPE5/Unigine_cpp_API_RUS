// Предоставляет UI для тестирования различных режимов выполнения задач AsyncQueue. Поддерживает одиночные
// асинхронные задачи на различных типах потоков и многопоточные задачи в режимах sync/async.

#include "AsyncQueueTasksSample.h"

#include <UnigineAsyncQueue.h>
#include <UnigineConsole.h>

REGISTER_COMPONENT(AsyncQueueTasksSample);

using namespace Unigine;

// Создаются элементы управления UI для выбора типа потока и выполнения задачи.
void AsyncQueueTasksSample::init()
{
	Console::setOnscreen(true);

	// UI примера с описанием и элементами управления
	sample_description_window.createWindow(Gui::ALIGN_RIGHT);

	WidgetGroupBoxPtr parameters = sample_description_window.getParameterGroupBox();

	// Блок UI для выбора типа потока, в котором будет выполняться задача
	auto async_thread_type_hbox = WidgetHBox::create(5);
	parameters->addChild(async_thread_type_hbox, Gui::ALIGN_EXPAND);

	auto async_thread_type_label = WidgetLabel::create("Task Thread Type");
	async_thread_type_hbox->addChild(async_thread_type_label);

	auto async_thread_type_combobox = WidgetComboBox::create();
	async_thread_type_combobox->addItem("BACKGORUND");
	async_thread_type_combobox->addItem("ASYNC");
	async_thread_type_combobox->addItem("ASYNC FRAME POOL");
	async_thread_type_combobox->addItem("GPU STREAM");
	async_thread_type_combobox->addItem("FILE STREAM");
	async_thread_type_combobox->addItem("MAIN");
	async_thread_type_combobox->addItem("NEW");
	async_thread_type_hbox->addChild(async_thread_type_combobox, Gui::ALIGN_EXPAND);

	// Кнопка для запуска одиночной асинхронной задачи в выбранном типе потока
	auto run_async_button = WidgetButton::create("Run Async");
	run_async_button->getEventClicked().connect(*this, [instance = this, async_thread_type_combobox]()
		{
			// Запускаем задачу асинхронно в указанном потоке
			// Также можно указать приоритет задачи
			// CRITICAL (высокий), DEFAULT (средний) или BACKGROUND (низкий)
			AsyncQueue::runAsync(AsyncQueue::ASYNC_THREAD(async_thread_type_combobox->getCurrentItem()), MakeCallback(instance, &AsyncQueueTasksSample::async_task));
		});
	parameters->addChild(run_async_button, Gui::ALIGN_EXPAND);

	auto spacer = WidgetSpacer::create();
	parameters->addChild(spacer, Gui::ALIGN_EXPAND);

	// Блок UI для управления выполнением многопоточной задачи
	auto multithread_hbox = WidgetHBox::create(5);
	parameters->addChild(multithread_hbox, Gui::ALIGN_EXPAND);

	auto multithread_label = WidgetLabel::create("Num threads");
	multithread_hbox->addChild(multithread_label);

	auto spinbox_hbox = WidgetHBox::create();
	auto multithread_editline = WidgetEditLine::create();
	multithread_editline->setEditable(false);
	auto multithread_spinbox = WidgetSpinBox::create();
	multithread_editline->addAttach(multithread_spinbox);
	multithread_spinbox->setMinValue(1);
	multithread_spinbox->setMaxValue(20);
	multithread_spinbox->setValue(1);
	spinbox_hbox->addChild(multithread_editline);
	spinbox_hbox->addChild(multithread_spinbox);
	multithread_hbox->addChild(spinbox_hbox, Gui::ALIGN_RIGHT);

	// Чекбокс для выбора, должны ли многопоточные задачи завершаться в течение текущего кадра
	auto frame_checkbox = WidgetCheckBox::create("Wait for multithreaded task to complete in frame");
	parameters->addChild(frame_checkbox, Gui::ALIGN_LEFT);

	// Кнопка для запуска многопоточных задач асинхронно (не блокирует вызывающую сторону)
	auto run_async_multithread_button = WidgetButton::create("Run Async Multithread");
	run_async_multithread_button->getEventClicked().connect(*this, [instance = this, multithread_spinbox, frame_checkbox]()
		{
			// Запускаем задачу в многопоточном режиме. Текущий номер потока и общее количество потоков передаются в коллбэк
			// Не блокирует поток, из которого вызвана
			if(frame_checkbox->isChecked())
				AsyncQueue::runFrameAsyncMultiThread(MakeCallback(instance, &AsyncQueueTasksSample::multithread_task), multithread_spinbox->getValue());
			else
				AsyncQueue::runAsyncMultiThread(MakeCallback(instance, &AsyncQueueTasksSample::multithread_task), multithread_spinbox->getValue());
		});
	parameters->addChild(run_async_multithread_button, Gui::ALIGN_EXPAND);

	// Кнопка для запуска многопоточных задач синхронно (блокирует вызывающую сторону до завершения)
	auto run_sync_multithread_button = WidgetButton::create("Run Sync Multithread");
	run_sync_multithread_button->getEventClicked().connect(*this, [instance = this, multithread_spinbox, frame_checkbox]()
		{
			// Запускаем задачу в многопоточном режиме. Текущий номер потока и общее количество потоков передаются в коллбэк
			// Блокирует поток, из которого вызвана (вызывающий поток разблокируется после завершения задачи во всех потоках)
			if(frame_checkbox->isChecked())
				AsyncQueue::runFrameSyncMultiThread(MakeCallback(instance, &AsyncQueueTasksSample::multithread_task), multithread_spinbox->getValue());
			else	
				AsyncQueue::runSyncMultiThread(MakeCallback(instance, &AsyncQueueTasksSample::multithread_task), multithread_spinbox->getValue());
		});
	parameters->addChild(run_sync_multithread_button, Gui::ALIGN_EXPAND);
}

// Консоль скрывается, окно UI закрывается.
void AsyncQueueTasksSample::shutdown()
{
	// Скрываем консоль и очищаем UI примера
	Console::setOnscreen(false);
	sample_description_window.shutdown();
}

// Одиночная задача, выполняемая на рабочем потоке; логирует ID потока.
void AsyncQueueTasksSample::async_task()
{
	// Имитируем нагрузку
	Thread::sleep(200);
	Log::message("This is async task, thread id: %d\n", Thread::getID());
}

// Параллельная задача, выполняемая на нескольких потоках; логирует текущий индекс потока и общее число.
void AsyncQueueTasksSample::multithread_task(int current_thread, int total_thread)
{
	// Имитируем нагрузку
	Thread::sleep(200);
	Log::message("This is multithread task(current thread: %d, total number of threads: %d), thread id: %d\n", current_thread, total_thread, Thread::getID());
}
