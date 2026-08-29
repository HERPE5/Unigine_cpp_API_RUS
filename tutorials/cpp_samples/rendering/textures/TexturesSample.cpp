// Генерация процедурных текстур в реальном времени. Создаёт анимированные текстуры
// с XOR-паттерном, напрямую записывая данные пикселей в объекты Image каждый кадр.
// Изображения динамически применяются к слотам albedo объектов.

#include "TexturesSample.h"

#include <UnigineGame.h>

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(TexturesSample)

// Объекты мешей кэшируются; для каждой анимированной текстуры задаются базовые цвета.
void TexturesSample::init()
{
	UNIGINE_ASSERT(meshes_param.size() == 4);

	// Кэшируем ссылки на объекты мешей для эффективного доступа каждый кадр
	for (int i = 0; i < 4; ++i)
	{
		ObjectPtr object = checked_ptr_cast<Object>(meshes_param[i].get());
		if (object)
		{
			meshes.push_back(object);
		}
		else
		{
			Log::warning("TexturesSample::init(): object is null");
		}
	}

	// Задаём отдельные базовые цвета для каждой текстуры (жёлтый, голубой, пурпурный, белый)
	colors.push_back(ivec4(255, 255, 0, 255));
	colors.push_back(ivec4(0, 255, 255, 255));
	colors.push_back(ivec4(255, 0, 255, 255));
	colors.push_back(ivec4(255, 255, 255, 255));

	// Предварительно выделяем массив изображений (сами изображения создаются лениво в update)
	images.resize(4);
}

// XOR-паттерн перегенерируется каждый кадр со смещением анимации на основе времени.
void TexturesSample::update()
{
	float time = Game::getTime();

	for (int i = 0; i < 4; ++i)
	{
		// Вычисляем анимированное смещение с помощью синусоиды; каждая текстура анимируется с немного другой скоростью
		int offset = static_cast<int>(Math::sin(time * (0.9f + i * 0.1f)) * 127.0f + 127.0f);

		// Ленивая инициализация изображения на первом кадре
		ImagePtr &image = images[i];
		if (!image)
		{
			image = Image::create();
			image->create2D(128, 128, Image::FORMAT_RGBA8);
		}

		// Генерируем XOR-паттерн: классический demoscene-эффект с побитовым XOR координат
		ivec4 color = colors[i];
		for (int y = 0; y < image->getHeight(); y++)
		{
			for (int x = 0; x < image->getWidth(); x++)
			{
				// XOR создаёт узор, похожий на ромбы; смещение и остаток от деления добавляют вариацию анимации
				ivec4 c = color * ((x ^ y) * offset % 63) >> 6;
				image->set2D(x, y, Image::Pixel(c.x, c.y, c.z, c.w));
			}
		}

		// Применяем обновлённое изображение к слоту текстуры albedo меша
		ObjectPtr &mesh = meshes[i];
		MaterialPtr material = mesh->getMaterialInherit(0);
		int num = material->findTexture("albedo");
		if (num != -1)
		{
			// Загружаем данные изображения из CPU в GPU-текстуру
			material->setTextureImage(num, image);
		}
	}
}
