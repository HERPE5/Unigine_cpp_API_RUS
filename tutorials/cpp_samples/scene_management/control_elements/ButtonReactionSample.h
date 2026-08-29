// Компонент-реактор, трансформирующий узел на основе состояния интерактивного элемента.
// Интерполирует между исходной и целевой трансформациями, используя значение интерактивного элемента.
// Демонстрирует паттерн разделённых элемента управления и реактора для систем симуляции.

#pragma once
#include <UnigineComponentSystem.h>
#include "Interactable.h"

// Трансформирует узел на основе нормализованного значения связанного интерактивного элемента.
class ButtonReactionSample : public Unigine::ComponentBase
{
	public:
	COMPONENT_DEFINE(ButtonReactionSample, ComponentBase);

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

	// Смещение позиции, когда значение интерактивного элемента равно 1.0
	PROP_PARAM(Vec3, position);
	// Смещение поворота по углам Эйлера, когда значение интерактивного элемента равно 1.0
	PROP_PARAM(Vec3, rotation);
	// Ссылка на интерактивный элемент, управляющий этим реактором
	PROP_PARAM(Node, interatable_node);

private:

	void init();
	void update();

	// Начальная позиция для интерполяции
	Unigine::Math::Vec3 initial_position;
	// Начальный поворот для интерполяции
	Unigine::Math::quat initial_rotation;
	// Целевой поворот, когда значение равно 1.0
	Unigine::Math::quat final_rotation;
	// Закэшированный указатель на интерактивный компонент
	Interactable* interactable_comp = nullptr;
};

