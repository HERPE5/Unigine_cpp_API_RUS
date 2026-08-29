#pragma once
#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>
#include <UnigineWidgets.h>

// Этот компонент демонстрирует ретаргетинг анимации между скелетами с разными пропорциями.
// Ретаргетинг теперь работает автоматически через общие скелеты, назначенные на MeshSkinned
// и MeshSkinnedAnimation. Чтобы избежать растяжения при различии пропорций скелетов,
// к большинству костей применяются маски кадров "только вращение". Кости бёдер и контакта с землёй
// получают полные трансформации для сохранения корректной высоты тела и позиции относительно земли.
class AnimationBonesRetargetingSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(AnimationBonesRetargetingSample, ComponentBase);
	COMPONENT_INIT(init);

private:
	void init();
};
