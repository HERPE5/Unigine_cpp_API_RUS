// Базовый класс для алгоритмов движения. Хранит ссылки на цель (лазерную указку)
// и преследователя (персонаж кота). Производные классы реализуют разное поведение
// сглаживания: linear, ease-in, ease-out, spring, bounce.

#include "MotionMode.h"

#include <UnigineObjects.h>

using namespace Unigine;
using namespace Math;

// Ссылки на узлы цели и преследователя проверяются и сохраняются.
void MotionMode::init()
{
	// Проверяем ссылки на узлы цели (лазер) и преследователя (кот).
	// Они задаются компонентом CatDemo во время выполнения.
	if (!targetNode.get())
		Log::error("MotionMode::init(): cannot get targetNode property\n");

	// Получаем интерфейс PersecutorBase из узла преследователя.
	// Это позволяет использовать разные реализации преследователя (скелетный меш, простой меш и т.д.)
	persecutor = ComponentSystem::get()->getComponent<PersecutorBase>(persecutorNode.get());
	if (!persecutor)
		Log::error("MotionMode::init(): cannot get Persecutor component from persecutorNode\n");
}
