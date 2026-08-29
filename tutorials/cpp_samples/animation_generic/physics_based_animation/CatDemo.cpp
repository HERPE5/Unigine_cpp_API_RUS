// Контроллер демо, управляющий несколькими алгоритмами сглаживания для движения кота.
// Каждый дочерний узел содержит отдельный компонент MotionMode (варианты Linear, EaseIn,
// EaseOut, Spring). Пользователь может переключаться между режимами через выпадающий список.

#include "CatDemo.h"

#include "MotionMode.h"
#include "SpringRegular.h"

#include <UnigineWidgets.h>

REGISTER_COMPONENT(CatDemo);

using namespace Unigine;
using namespace Math;

// Создаются элементы GUI демо-режима и добавляются в окно примера.
void CatDemo::initGUI(const WidgetWindowPtr &window)
{
	demo_box = WidgetGroupBox::create("Demo", 8, 4);
	auto demo_label = WidgetLabel::create("Choose animation type for the cat:");
	demo_box->addChild(demo_label, Gui::ALIGN_LEFT);

	// Режимы движения кота добавляются в демо-комбобокс
	for (const auto &c : cat_components)
		demo_combo->addItem(c->getNode()->getName());
	demo_combo->setCurrentItem(mode);
	demo_combo->getEventChanged().connect(this, &CatDemo::update_cat_mode);
	demo_combo->setEnabled(0);
	demo_combo->arrange();
	demo_box->addChild(demo_combo, Gui::ALIGN_LEFT);

	window->addChild(demo_box, Gui::ALIGN_LEFT);
}

// Компоненты MotionMode собираются из дочерних узлов и связываются с целевыми ссылками.
void CatDemo::init()
{
	if (!laserNode)
		Log::error("CatGame::init(): cannot find laserNode!\n");
	if (!catNode)
		Log::error("CatGame::init(): cannot find catNode!\n");

	if (!demo_combo)
		demo_combo = WidgetComboBox::create();

	// Собираем все компоненты MotionMode из дочерних узлов.
	// Каждый дочерний узел представляет отдельный алгоритм сглаживания
	// (варианты Linear, EaseIn, EaseOut, Spring и т.д.)
	int num_demo_modes = node->getNumChildren();
	cat_components.allocate(num_demo_modes);

	for (int i = 0; i < num_demo_modes; i++)
	{
		NodePtr mode = node->getChild(i);
		auto comp = ComponentSystem::get()->getComponent<MotionMode>(mode);
		if (!comp)
			continue;
		// Связываем ссылки на цель и преследователя для каждого режима движения
		comp->targetNode = laserNode;
		comp->persecutorNode = catNode;
		comp->setEnabled(false);
		cat_components.emplace_back(comp);
	}
}

// Вызывается при активации демо-режима. GUI включается, применяется текущий режим движения.
void CatDemo::on_enable()
{
	demo_combo->setEnabled(1);
	update_cat_mode();
	demo_box->setHidden(false);
}

// Вызывается при деактивации демо-режима. Текущий режим движения и GUI отключаются.
void CatDemo::on_disable()
{
	cat_components[mode]->setEnabled(0);
	demo_combo->setEnabled(0);
	demo_box->setHidden(true);
}

// Считывает выбранный режим из комбобокса и переключается на него.
void CatDemo::update_cat_mode()
{
	auto new_mode = demo_combo->getCurrentItem();
	switch_cat_mode(new_mode);
}

// Отключает текущий режим движения и включает новый.
void CatDemo::switch_cat_mode(int new_mode)
{
	cat_components[mode]->setEnabled(false);
	mode = new_mode;
	cat_components[mode]->setEnabled(true);
}

void CatDemo::shutdown()
{
	shutdown_gui();
}

// Виджеты GUI освобождаются через deleteLater для безопасного отложенного уничтожения.
void CatDemo::shutdown_gui()
{
	demo_box.deleteLater();
	demo_combo.deleteLater();
}
