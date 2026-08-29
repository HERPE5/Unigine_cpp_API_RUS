// Процедурная генерация объёмной 3D-текстуры. Анимирует поля плотности, отскакивающие
// внутри куба, записывая значения RGBA напрямую в 3D-изображение каждый
// кадр. Изображение применяется к материалу облака объёма для визуализации.

#include "ImagesSample.h"

#include <UnigineGame.h>

using namespace Unigine;
using namespace Math;

// Инициализирует случайные поля (позиции, скорости, радиусы), управляющие 3D-плотностью
void ImagesSample::image_init()
{
	positions.resize(num_fields);
	velocities.resize(num_fields);
	radiuses.resize(num_fields);

	for (int i = 0; i < num_fields; ++i)
	{
		positions[i].x = randFloat(0.f, size);
		positions[i].y = randFloat(0.f, size);
		positions[i].z = randFloat(0.f, size);

		velocities[i].x = randFloat(-velocity, velocity);
		velocities[i].y = randFloat(-velocity, velocity);
		velocities[i].z = randFloat(-velocity, velocity);

		radiuses[i] = randFloat(radius / 2, radius);
	}
}

// Перемещает поля, обновляет 3D-изображение и записывает необработанные данные пикселей
void ImagesSample::image_update()
{
	float ifps = Game::getIFps();

	// Обновляем позиции полей, отскок внутри куба
	for (int i = 0; i < num_fields; ++i)
	{
		vec3 p = positions[i] + velocities[i] * ifps;
		if (p.x < 0.f || p.x > size)
		{
			velocities[i].x = -velocities[i].x;
		}
		if (p.y < 0.f || p.y > size)
		{
			velocities[i].y = -velocities[i].y;
		}
		if (p.z < 0.f || p.z > size)
		{
			velocities[i].z = -velocities[i].z;
		}

		positions[i] += velocities[i] * ifps;
	}

	int width = image->getWidth();
	int height = image->getHeight();
	int depth = image->getDepth();

	// Получаем необработанный указатель на все пиксели 3D-текстуры.
	// Данные хранятся как массив байтов в порядке RGBA
	unsigned char *d = image->getPixels3D();

	vec3 position;
	float iwidth = size / width;
	float iheight = size / height;
	float idepth = size / depth;
	for (int z = 0; z < depth; ++z)
	{
		position.z = static_cast<float>(z) * idepth;
		for (int y = 0; y < height; ++y)
		{
			position.y = static_cast<float>(y) * iheight;
			for (int x = 0; x < width; x++)
			{
				position.x = static_cast<float>(x) * iwidth;
				float field = 0.f;
				for (int i = 0; i < num_fields; i++)
				{
					float distance = distance2(positions[i], position);
					if (distance < radiuses[i])
					{
						field += radiuses[i] - distance;
					}
				}

				if (field > 1.f) field = 1.f;

				// Преобразуем в 8-битное значение
				unsigned char density = static_cast<unsigned char>(field * 255.f);

				// "d" - это указатель на все пиксели изображения
				// Каждый элемент массива, на который указывает "d",
				// является значением цветового канала пикселя
				// вот представление того, как это выглядит
				// chars   d
				// ↓       ↓
				// RGBARGBARGBARGBARGBA
				*d++ = density; // R
				*d++ = density; // G
				*d++ = density; // B
				*d++ = density; // A

				// Теперь "d" указывает на канал R следующего пикселя
			}
		}
	}
}


// Sample Logic
REGISTER_COMPONENT(ImagesSample)

void ImagesSample::init()
{
	// Создаём небольшую 3D RGBA-текстуру и заполняем её начальными данными
	image = Image::create();
	image->create3D(32, 32, 32, Image::FORMAT_RGBA8);
	image_init();

	// Создаём объёмный бокс и применяем к нему ручной материал
	// подробнее см. статью "volume_cloud_base" в документации
	ObjectVolumeBoxPtr object = ObjectVolumeBox::create(vec3(20.f));
	object->setMaterial(Materials::findManualMaterial("Unigine::volume_cloud_base"), "*");
	object->setMaterialState("samples", 2, 0);
	object->setTransform(translate(Vec3(0.f, 0.f, 1.f)));
	material = object->getMaterialInherit(0);
}

void ImagesSample::update()
{
	// Обновляем 3D-текстуру каждый кадр новой плотностью,
	// записанной в наше изображение
	image_update();
	material->setTextureImage(material->findTexture("density_3d"), image);
}
