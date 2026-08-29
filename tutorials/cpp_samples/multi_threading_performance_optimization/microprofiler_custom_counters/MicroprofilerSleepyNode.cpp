#include "MicroprofilerSleepyNode.h"
#include <UnigineProfiler.h>

REGISTER_COMPONENT(MicroprofilerSleepyNode);

using namespace Unigine;

void MicroprofilerSleepyNode::init()
{
	// Макрос, автоматически создающий область профилирования для текущей функции
	// Начало и конец области генерируются автоматически
	UNIGINE_PROFILER_FUNCTION;
	sleepFor(1);
}

void MicroprofilerSleepyNode::updateAsyncThread()
{
	// beginMicro начинает область профилирования и возвращает её ID
	// endMicro закрывает область профилирования
	// Этот подход даёт полный контроль над временем жизни области
	int id = Profiler::beginMicro(__FUNCTION__);
	sleepFor(2);
	Profiler::endMicro(id);
}

void MicroprofilerSleepyNode::updateSyncThread()
{
	// Похоже на UNIGINE_PROFILER_FUNCTION, но позволяет задавать произвольные имена областей
	// Здесь используется __FUNCTION__, поэтому имя области совпадает с именем функции
	UNIGINE_PROFILER_SCOPED(__FUNCTION__);
	sleepFor(0.2);
}

void MicroprofilerSleepyNode::update()
{
	// Профилирование запускается в конструкторе
	// структуры ScopedProfiler и завершается автоматически
	// при выходе из области видимости (вызов деструктора).
	ScopedProfiler profiler(__FUNCTION__);
	node->rotate(0.0f, 0.0f, 3.0f);
	sleepFor(0.2);
}

void MicroprofilerSleepyNode::postUpdate()
{
	UNIGINE_PROFILER_FUNCTION;
	sleepFor(0.05);
}

void MicroprofilerSleepyNode::updatePhysics()
{
	UNIGINE_PROFILER_FUNCTION;
	sleepFor(0.02);
}

void MicroprofilerSleepyNode::swap()
{
	UNIGINE_PROFILER_FUNCTION;
	sleepFor(0.01);
}

void MicroprofilerSleepyNode::shutdown()
{
	UNIGINE_PROFILER_FUNCTION;
	sleepFor(1);
}

void MicroprofilerSleepyNode::sleepFor(double ms)
{
	auto ct = Time::getMilliseconds();
	while (true)
	{
		auto t = Time::getMilliseconds();
		if (t - ct >= ms)
			return;
	}
}
