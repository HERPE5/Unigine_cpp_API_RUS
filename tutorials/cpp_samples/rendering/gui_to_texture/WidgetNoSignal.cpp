// Анимированная метка "No Signal", отскакивающая по канве GUI-в-текстуру.
// Демонстрирует сочетание GuiToTexture с пользовательской анимацией виджета и
// физикой отражения от краёв для классического эффекта заставки.

#include "WidgetNoSignal.h"

#include "GuiToTexture.h"

#include <UnigineGame.h>

REGISTER_COMPONENT(WidgetNoSignal);

using namespace Unigine;
using namespace Math;

// Виджет метки создаётся с синим фоном и добавляется на канву GUI.
void WidgetNoSignal::init()
{
	const auto *gui_to_texture = ComponentSystem::get()->getComponent<GuiToTexture>(node);
	const GuiPtr gui = gui_to_texture->getGui();

	label = WidgetLabel::create(gui);
	label->setFontSize(150);
	label->setText("No Signal");

	container = WidgetVBox::create();
	container->setBackground(1);
	container->setBackgroundColor(vec4_blue);

	container->addChild(label, Gui::ALIGN_EXPAND | Gui::ALIGN_BACKGROUND);

	gui->addChild(container, Gui::ALIGN_OVERLAP | Gui::ALIGN_CENTER);
	gui_to_texture->renderToTexture();
}

// Позиция виджета обновляется на основе скорости и направления; движение накапливается для субпиксельной точности.
void WidgetNoSignal::update()
{
	const float frame_speed = label_speed * Game::getIFps();
	const vec2 delta = direction * frame_speed;
	const int pos_x = container->getPositionX();
	const int pos_y = container->getPositionY();

	if (ivec2(pos_x, pos_y) + ivec2(accumulated_delta) == ivec2(pos_x, pos_y))
	{
		accumulated_delta += delta;
		return;
	}
	container->setPositionX(pos_x + ftoi(accumulated_delta.x));
	container->setPositionY(pos_y + ftoi(accumulated_delta.y));
	accumulated_delta = vec2(0.f, 0.f);

	reflect_direction();
}

// Все четыре угла проверяются относительно границ канвы; направление отражается при столкновении.
void WidgetNoSignal::reflect_direction()
{
	const ivec2 size = container->getParentGui()->getSize();

	const int label_pos_x = container->getPositionX();
	const int label_pos_y = container->getPositionY();

	const int x_right_corner_delta = label->getTextRenderSize(label->getText()).x;
	const int y_bottom_corner_delta = label->getTextRenderSize(label->getText()).y;

	const auto left_top_corner_pos = ivec2(label_pos_x, label_pos_y);
	const auto right_top_corner_pos = ivec2(label_pos_x + x_right_corner_delta, label_pos_y);
	const auto left_bottom_corner_pos = ivec2(label_pos_x, label_pos_y + y_bottom_corner_delta);
	const auto right_bottom_corner_pos = ivec2(label_pos_x + x_right_corner_delta,
		label_pos_y + y_bottom_corner_delta);

	// Проверяем верхний левый угол
	{
		// Пересечение с верхом
		if (left_top_corner_pos.x > 0 && left_top_corner_pos.y < 0)
		{
			container->setPositionY(0);
			direction = reflect_vector(direction, vec2(0, 1));
			return;
		}

		if (left_top_corner_pos.x < 0 && left_top_corner_pos.y > 0)
		{
			container->setPositionX(0);
			direction = reflect_vector(direction, vec2(1, 0));
			return;
		}

		// Пересечение с углом
		if (left_top_corner_pos.x < 0 && left_top_corner_pos.y < 0)
		{
			direction = vec2(1, 1).normalize();
			container->setPositionX(0);
			container->setPositionY(0);
			return;
		}
	}

	// Проверяем верхний правый угол
	{
		// Правый угол
		if (right_top_corner_pos.x > size.x && right_top_corner_pos.y > 0)
		{
			container->setPositionX(size.x - x_right_corner_delta);
			direction = reflect_vector(direction, vec2(-1, 0));
			return;
		}

		if (right_top_corner_pos.x > size.x && right_top_corner_pos.y < 0)
		{
			container->setPositionX(size.x - x_right_corner_delta);
			container->setPositionY(0);
			direction = vec2(-1, 1);
			return;
		}
	}

	// Проверяем нижний левый угол
	{
		if (left_bottom_corner_pos.x < 0 && left_bottom_corner_pos.y < size.y)
		{
			container->setPositionX(0);
			direction = reflect_vector(direction, vec2(1, 0));
			return;
		}

		if (left_bottom_corner_pos.x > 0 && left_bottom_corner_pos.y > size.y)
		{
			container->setPositionY(size.y - y_bottom_corner_delta);
			direction = reflect_vector(direction, vec2(0, -1));
			return;
		}

		if (left_bottom_corner_pos.x < 0 && left_bottom_corner_pos.y > size.y)
		{
			container->setPositionX(0);
			container->setPositionY(y_bottom_corner_delta);
			direction = vec2(1, -1);
			return;
		}
	}

	// Проверяем нижний правый угол
	{
		if (right_bottom_corner_pos.x > size.x && right_bottom_corner_pos.y < size.y)
		{
			container->setPositionX(size.x - x_right_corner_delta);
			direction = reflect_vector(direction, vec2(-1, 0));
			return;
		}

		if (right_bottom_corner_pos.x > size.x && right_bottom_corner_pos.y > size.y)
		{
			container->setPositionX(size.x - x_right_corner_delta);
			container->setPositionY(size.y - y_bottom_corner_delta);
			direction = vec2(-1, -1);
			return;
		}
	}
}

// Стандартная формула отражения: v' = v - 2(v·n)n
vec2 WidgetNoSignal::reflect_vector(const vec2 &vector, const vec2 &normal)
{
	return (vector - normal * dot(vector, normal) * 2).normalize();
}