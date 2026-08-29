// Отскакивающая метка "No Signal" для классического эффекта заставки.
// Использует GuiToTexture с включённым автообновлением, поэтому нужно обновлять
// только состояние виджета, а перерисовка текстуры происходит автоматически.

#pragma once

#include <UnigineComponentSystem.h>

class GuiToTexture;

// Анимирует отскакивающую метку, отражающуюся от краёв канвы.
class WidgetNoSignal final : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(WidgetNoSignal, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

	// Скорость движения в пикселях в секунду
	PROP_PARAM(Float, label_speed, 1000.f, nullptr, nullptr, nullptr, "min=0.1;max=3000");

private:
	void init();
	void update();

	void reflect_direction();

	static Unigine::Math::vec2 reflect_vector(const Unigine::Math::vec2 &vector,
		const Unigine::Math::vec2 &normal);

private:
	// Текущая позиция на канве
	Unigine::Math::ivec2 position{};

	// Контейнерный виджет с фоновым цветом
	Unigine::WidgetVBoxPtr container{};
	// Текстовая метка, отображающая "No Signal"
	Unigine::WidgetLabelPtr label;

	// Аккумулятор субпиксельного движения для плавной анимации
	Unigine::Math::vec2 accumulated_delta{};
	// Нормализованный вектор направления движения
	Unigine::Math::vec2 direction{1.f, 1.f};
	Unigine::Math::vec2 start_position;
};