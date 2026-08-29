// Генерирует динамическую текстуру поля высот с помощью процедурных синусоидальных волн. Узлы FieldHeight
// изменяют террейн или поверхности воды в пределах своего ограничивающего объёма. Этот компонент
// создаёт анимированные паттерны волн, обновляя текстуру R8 каждый кадр.

#include "DynamicTextureFieldHeight.h"


REGISTER_COMPONENT(DynamicTextureFieldHeight);

using namespace Unigine;
using namespace Math;

void DynamicTextureFieldHeight::setImageSize(int size)
{
	size_map = size;
	// Формат 0 = IMAGE_FORMAT_R8 (один канал, 8 бит)
	// Пересоздание изображения отбрасывает старые данные и выделяет новый буфер
	image->create2D(size_map, size_map, 0);
}


void DynamicTextureFieldHeight::setFrequency(float f)
{
	frequency = f;
}

void DynamicTextureFieldHeight::setSpeed(float s)
{
	speed = s;
}

void DynamicTextureFieldHeight::setAmplitude(float power)
{
	// Преобразуем нормализованный диапазон 0-1 в значение пикселя R8 (0-255)
	// 127 - половина от 255, поэтому power=1.0 даёт максимальное смещение высоты
	amplitude = int(127.0f * power);
}

void DynamicTextureFieldHeight::setWidgetSprite(WidgetSpritePtr spr)
{
	sprite = spr;
}

void DynamicTextureFieldHeight::init()
{
	// checked_ptr_cast возвращает null, если узел не является FieldHeight
	instance = checked_ptr_cast<FieldHeight>(node);
	if (instance)
	{
		image = Image::create();
		// Создаём одноканальное 8-битное изображение для данных поля высот
		// Значение 128 = нейтральная высота, <128 = ниже, >128 = выше
		image->create2D(size_map, size_map, 0);

		// Создаём GPU-текстуру и привязываем её к узлу FieldHeight
		texture = Texture::create();
		texture->setImage(image);
		instance->setTexture(texture);
	}
	else
	{
		// Отключаем компонент, если он присоединён к узлу неверного типа
		node->setEnabled(false);
		Log::error("Component can only be added to the Field Height");
	}
}

void DynamicTextureFieldHeight::update()
{
	// Game::getTime() возвращает общее прошедшее время в секундах
	float time = Game::getTime() * speed;

	// Прямой доступ к пикселям для производительности (без вызовов функций для каждого пикселя)
	unsigned char* pixels_ = image->getPixels();
	for (int j = 0; j < size_map; j++)
	{
		// sinFast возвращает [-1, 1], добавление 1.0 сдвигает в [0, 2]
		// Результат ограничивается диапазоном 0-255 при присвоении unsigned char
		float value = amplitude * (sinFast(j * frequency / size_map + time) + 1.0f);
		// Горизонтальные полосы: одинаковое значение по всей строке
		for (int i = 0; i < size_map; i++)
		{
			pixels_[i + (size_map * j)] = value;
		}
	}

	// Загружаем изменённое CPU-изображение в GPU-текстуру
	texture->setImage(image);
	// Обновляем UI-превью, если подключено
	if (sprite)
		sprite->setImage(image);
}


