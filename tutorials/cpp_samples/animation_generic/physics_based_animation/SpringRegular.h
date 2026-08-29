#pragma once

#include "SpringMotion.h"

#include <UnigineComponentSystem.h>

// Движение пружины с прямым управлением физическими параметрами.
// Предоставляет жёсткость и демпфирование как редактируемые свойства для точной настройки.
// Предоставляет сеттеры времени выполнения для динамической настройки сложности (используется в игровом режиме).
class SpringRegular : public SpringMotion

{
public:
	COMPONENT_DEFINE(SpringRegular, SpringMotion);

	PROP_PARAM(Float, defaultStiffness, 3.0f, "Stiffness");
	PROP_PARAM(Float, defaultDamping, 0.75f, "Damping");

	void setStiffness(float value) { stiffness = value; }
	float getStiffness() const { return stiffness; }
	void setDamping(float value) { damping = value; }
	float getDamping() const { return damping; }
	bool getFinished() const { return finished; }
	void RefreshSpring();

private:
	void on_disable() override;
	void refresh_spring_settings() override;
};
