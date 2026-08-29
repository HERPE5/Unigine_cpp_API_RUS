// UI примера для настройки частоты кадров с целью наблюдения разницы между
// приложением сил в update() и update_physics(). Более низкий FPS делает
// нестабильность физики на основе update() более заметной.

#include "UpdatePhysicsUsageSample.h"

REGISTER_COMPONENT(UpdatePhysicsUsageSample);

using namespace Unigine;
using namespace Math;


void UpdatePhysicsUsageSample::init()
{
	window_sample.createWindow();

	// Слайдер FPS демонстрирует стабильность физики при разных частотах рендеринга
	WidgetSliderPtr fpsSlider = window_sample.addIntParameter("Max fps", "Max fps", 60, 15, 150, [this](int v) {
		Render::setMaxFPS(v);
		});
	Render::setMaxFPS(60);

}

void UpdatePhysicsUsageSample::shutdown()
{
	window_sample.shutdown();
}
