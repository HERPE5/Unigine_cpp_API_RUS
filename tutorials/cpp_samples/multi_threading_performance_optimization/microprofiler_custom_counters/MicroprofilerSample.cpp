// Показывает URL микропрофилировщика для анализа производительности в браузере. Включает фоновый
// рендеринг, чтобы профилирование было возможно, даже когда окно не в фокусе.

#include "MicroprofilerSample.h"
#include "UnigineEngine.h"
#include "UnigineWindowManager.h"
#include <UnigineProfiler.h>

REGISTER_COMPONENT(MicroprofilerSample);

using namespace Unigine;

// Отображается URL микропрофилировщика, если доступен; включаются фоновые обновления.
void MicroprofilerSample::init()
{
	// UI примера с описанием и элементами управления
	StringStack<> description = "";
	if (String(Profiler::getMicroprofileUrl()) == "")
	{
		WindowManager::dialogError("Warning", "Microprofiler is not available!");
		description = "<font color=\"#de4a14\"><p>Microprofiler is not compiled.</p>"
					  "<p>Use development-release binaries.</p></font>";
	}
	else
	{
		description = String::format("<p>Microprofiler url - <font color=\"#de4a14\">%s</font></p>",
			Profiler::getMicroprofileUrl());
	}

	sample_description_window.createWindow();
	
	const auto& parameterGB = sample_description_window.getParameterGroupBox();
	auto label = WidgetLabel::create(description);
	label->setFontRich(1);
	parameterGB->addChild(label);

	previous_bg_update = Engine::get()->getBackgroundUpdate();
	Engine::get()->setBackgroundUpdate(Unigine::Engine::BACKGROUND_UPDATE_RENDER_NON_MINIMIZED);
}

// Восстанавливается режим фоновых обновлений, закрывается UI.
void MicroprofilerSample::shutdown()
{
	Engine::get()->setBackgroundUpdate(previous_bg_update);
	sample_description_window.shutdown();
}
