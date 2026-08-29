// Генерирует динамическую текстуру поля высот с помощью процедурных синусоидальных волн. Узлы FieldHeight
// изменяют террейн или поверхности воды в пределах своего ограничивающего объёма. Этот компонент
// создаёт анимированные паттерны волн, обновляя текстуру R8 каждый кадр.

#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineFields.h>
#include <UnigineGame.h>


class DynamicTextureFieldHeight : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(DynamicTextureFieldHeight, ComponentBase);

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

public:
	// Изменяет размер текстуры карты высот (должен быть степенью 2)
	void setImageSize(int size);
	// Более высокая частота = больше пиков волн по текстуре
	void setFrequency(float frequency);
	// Множитель скорости анимации для движения волн
	void setSpeed(float speed);
	// Высота волны как нормализованное значение 0-1
	void setAmplitude(float power);
	// Опциональный UI-спрайт для визуального отображения карты высот
	void setWidgetSprite(Unigine::WidgetSpritePtr sprite);

private:
	void init();
	void update();

	// Разрешение текстуры (ширина и высота равны)
	int size_map{ 1024 };
	float speed{ 1.0f };
	float frequency{ 1.0f };
	// Формат R8 использует диапазон 0-255; 127 = половина интенсивности
	int amplitude{ 127 };

	// Данные изображения на стороне CPU для манипуляции пикселями
	Unigine::ImagePtr image;
	// UI-превью карты высот (опционально)
	Unigine::WidgetSpritePtr sprite;
	// Узел FieldHeight, который изменяет этот компонент
	Unigine::FieldHeightPtr instance;
	// GPU-текстура, загружаемая каждый кадр с новыми данными
	Unigine::TexturePtr texture;
	Unigine::ObjectGuiPtr gui;
};