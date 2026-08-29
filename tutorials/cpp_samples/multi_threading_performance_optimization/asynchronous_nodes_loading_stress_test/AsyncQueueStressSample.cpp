// Создаёт множество узлов в фоновом потоке с помощью AsyncQueue::runAsync(). Узлы
// создаются со случайными позициями вне главного потока, затем активируются через коллбэк главного потока.

#include "AsyncQueueStressSample.h"

#include <UnigineAsyncQueue.h>
#include <UnigineGame.h>
#include <UnigineProfiler.h>

REGISTER_COMPONENT(AsyncQueueStressSample);

using namespace Unigine;
using namespace Math;

// Профилировщик включается, создаётся UI с кнопкой загрузки.
void AsyncQueueStressSample::init()
{
	// Включаем профилировщик, чтобы наблюдать, как фоновая загрузка влияет на производительность
	Profiler::setEnabled(true);

	num_nodes_loaded = 0;

	// UI примера с описанием и элементами управления
	sample_description_window.createWindow(Gui::ALIGN_RIGHT);

	WidgetGroupBoxPtr parameters = sample_description_window.getParameterGroupBox();
	
	auto num_nodes_hbox = WidgetHBox::create(5);
	parameters->addChild(num_nodes_hbox, Gui::ALIGN_EXPAND);

	auto multithread_label = WidgetLabel::create("Num nodes");
	num_nodes_hbox->addChild(multithread_label);

	auto spinbox_hbox = WidgetHBox::create();
	auto editline = WidgetEditLine::create();
	editline->setValidator(Gui::VALIDATOR_INT);
	auto spinbox = WidgetSpinBox::create();
	editline->addAttach(spinbox);
	spinbox->setMinValue(1);
	spinbox->setMaxValue(10000);
	spinbox->setValue(100);
	spinbox_hbox->addChild(editline);
	spinbox_hbox->addChild(spinbox);
	num_nodes_hbox->addChild(spinbox_hbox, Gui::ALIGN_RIGHT);

	auto request_load_nodes_button = WidgetButton::create("Request Load Nodes Async");
	parameters->addChild(request_load_nodes_button, Gui::ALIGN_EXPAND);

	num_nodes_loaded_label = WidgetLabel::create();
	parameters->addChild(num_nodes_loaded_label, Gui::ALIGN_EXPAND);

	// По клику запрашиваем фоновую загрузку узлов через AsyncQueue::runAsync()
	request_load_nodes_button->getEventClicked().connect(*this, [this, spinbox]()
	{
		AsyncQueue::runAsync(AsyncQueue::ASYNC_THREAD_BACKGROUND, MakeCallback(this, &AsyncQueueStressSample::load_nodes, spinbox->getValue()));
	});
}

// Отображается количество загруженных узлов; метка становится красной при превышении порога.
void AsyncQueueStressSample::update()
{
	// Обновляем UI текущим количеством загруженных узлов, подсвечиваем при высокой нагрузке
	num_nodes_loaded_label->setText("Num nodes loaded " + String::ltoa(num_nodes_loaded));
	if (num_nodes_loaded > 2000)
		num_nodes_loaded_label->setFontColor(vec4_red);
}

// Профилировщик отключается, окно UI закрывается.
void AsyncQueueStressSample::shutdown()
{
	// Отключаем профилировщик и очищаем UI примера
	Profiler::setEnabled(false);
	sample_description_window.shutdown();
}

// Узлы загружаются в фоновом потоке; активация планируется в главном потоке.
void AsyncQueueStressSample::load_nodes(int num)
{
	// Этот метод выполняется в фоновом потоке.
	// Он создаёт узлы и назначает случайные позиции, не блокируя главный поток.
	// Поскольку узлы создаются вне главного потока, позже нужно вызвать updateEnabled()
	// в главном потоке, чтобы зарегистрировать их в движке (добавить в пространственное дерево).
	for (int i = 0; i < num; ++i)
	{
		NodePtr loaded_node = World::loadNode(node_to_spawn.get(), false);

		// Назначаем случайную позицию в мире
		Vec3 position;
		position.x = Game::getRandomFloat(-100.0f, 100.0f);
		position.y = Game::getRandomFloat(-100.0f, 100.0f);
		position.z = Game::getRandomFloat(0.0f, 50.0f);
		loaded_node->setWorldPosition(position);

		num_nodes_loaded++;

		// Планируем активацию в главном потоке для регистрации узла в пространственном дереве
		AsyncQueue::runAsync(AsyncQueue::ASYNC_THREAD_MAIN, MakeCallback([loaded_node]()
			{
				// Вызываем updateEnabled, которая рекурсивно пройдёт по всем дочерним элементам и добавит их в пространственное дерево
				loaded_node->updateEnabled();
			}));
	}
}
