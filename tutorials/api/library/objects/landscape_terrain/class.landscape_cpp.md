# Unigine.Landscape Class (CPP)

**Header:** #include <UnigineObjects.h>

> **Notice:** Этот класс является синглтоном.


Этот класс используется для управления рендерингом и изменением ландшафтного террейна (landscape terrain).


Изменение террейна выполняется в асинхронном режиме на стороне GPU путём вызова соответствующего метода, который запускает операцию отрисовки. При вызове такого метода необходимо указать GUID файла `.lmap` [landscape layer map](../../../../api/library/objects/landscape_terrain/class.landscapelayermap_cpp.md), который нужно изменить, координаты левого верхнего угла и разрешение изменяемого сегмента данных, а также определить, какие слои данных будут затронуты (высоты, альбедо, маски), с помощью набора [flags](#FLAGS_FILE_DATA_HEIGHT). Сама операция должна быть реализована внутри обработчика callback.


### Изменение террейна на основе GPU


Рабочий процесс следующий:


1. Реализуйте логику изменения террейна на основе GPU в функции.
2. Задайте эту функцию-обработчик при подписке на событие *Texture Draw* (когда выполняется операция изменения террейна на основе GPU) через *[getEventTextureDraw()](#getEventTextureDraw_Event)*.
3. Запустите операцию отрисовки на GPU, вызвав метод [*asyncTextureDraw()*](#asyncTextureDraw_UGUID_ivec2_ivec2_int_void). Здесь необходимо указать GUID файла `.lmap` [landscape layer map](../../../../api/library/objects/landscape_terrain/class.landscapelayermap_cpp.md), который нужно изменить, координаты левого верхнего угла и разрешение изменяемого сегмента данных, а также определить, какие слои данных будут затронуты (высоты, альбедо, маски), с помощью набора [flags](#FLAGS_FILE_DATA_HEIGHT) > **Notice:** Если для вашего изменения требуются дополнительные данные за пределами указанной области, а также данные других landscape layer map (например, кисть копирования), можно включить принудительную загрузку необходимых данных — в этом случае следует использовать [this overload of the *asyncTextureDraw()* method](#asyncTextureDraw_UGUID_ivec2_ivec2_int_VECWorldBoundBox_void).


```cpp
// изменение на основе GPU
void my_texture_draw(const UGUID &guid, int id, const LandscapeTexturesPtr &buffer, const Math::ivec2 &coord, int data_mask)
{
	// получаем нужный материал кисти (встроенная в редактор кисть "circle_soft")
	// и наследуем от него дочерний материал
	auto file_guid = FileSystem::getGUID(FileSystem::resolvePartialVirtualPath("circle_soft.brush"));
	if (!file_guid.isValid())
	{
		Log::warning("LandscapePainter::init(): can not find \"circle_soft.brush\" material\n");
		return;
	}

	MaterialPtr brush_material = Materials::findMaterialByFileGUID(file_guid)->inherit();

	// задаём необходимые текстуры (например, альбедо и высоты)
	brush_material->setTexture("terrain_albedo", buffer->getAlbedo());
	brush_material->setTexture("terrain_height", buffer->getHeight());

	// настраиваем параметры материала кисти (размер, цвет и т.д., а также указываем маски, на которые влияет кисть)
	brush_material->setParameterFloat("size", 100.0f);
	brush_material->setParameterFloat("height", 10.0f);
	brush_material->setParameterFloat4("color", vec4_green);
	brush_material->setParameterInt("data_mask", data_mask);

	// запускаем выражение "brush" материала
	brush_material->runExpression("brush", buffer->getResolution().x, buffer->getResolution().y);

	// сбрасываем текстуры материала
	brush_material->setTexture("terrain_albedo", nullptr);
	brush_material->setTexture("terrain_height", nullptr);

}

// ...

int AppWorldLogic::init()
{
	// получаем существующий объект landscape terrain
	ObjectLandscapeTerrainPtr terrain = Landscape::getActiveTerrain();

	// получаем первую layermap, которую мы будем изменять
	LandscapeLayerMapPtr lmap = checked_ptr_cast<LandscapeLayerMap> (terrain->getChild(0));

	// подписываемся на операцию Texture Draw
	Landscape::getEventTextureDraw().connect(connections, my_texture_draw);

	// генерируем новый ID для операции отрисовки
	int id = Landscape::generateOperationID();

	// пользовательский код (привязка к ID)

	// запускаем операцию Texture Draw для выбранной карты ландшафта в точке (1, 1) с размером [32 x 32]
	Landscape::asyncTextureDraw(id, lmap->getGUID(), ivec2(1, 1), ivec2(32, 32), Landscape::FLAGS_DATA_HEIGHT | Landscape::FLAGS_DATA_ALBEDO);

	return 1;
}

// ...

 int AppWorldLogic::shutdown()
{
	// удаляем все подписки
	connections.disconnectAll();

	return 1;
}


```


И сам процесс:


1. После запуска операции изменения террейна со всеми необходимыми указанными параметрами движок копирует фрагмент данных террейна из указанного файла [landscape layer map](../../../../api/library/objects/landscape_terrain/class.landscapelayermap_cpp.md) по указанным координатам в буфер ([*LandscapeTextures*](../../../../api/library/objects/landscape_terrain/class.landscapetextures_cpp.md)) указанного разрешения.
2. По завершении процесса копирования выполняется функция-обработчик, которую вы использовали для подписки на событие *[TextureDraw](#getEventTextureDraw_Event)*. Эта функция изменяет буфер.
3. После этого выбранные слои данных изменённого буфера вставляются обратно в файл [landscape layer map](../../../../api/library/objects/landscape_terrain/class.landscapelayermap_cpp.md).


##### Пример использования: редактор кистей


Ниже приведён компонент C++, реализующий изменение *Landscape Terrain* на основе кистей.


<details>
<summary>LandscapeBrush.h | Закрыть</summary>

```cpp
#pragma once

#include <UnigineComponentSystem.h>
#include <UniginePlayers.h>
class LandscapeBrush :
	public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(LandscapeBrush, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	PROP_PARAM(Float, brush_size, 10.0f, "Brush Size");
	PROP_PARAM(Float, brush_height, 1.0f, "Brush Height");

private:
	void init();
	void update();
	void shutdown();
	void my_texture_draw(const Unigine::UGUID &guid, int id, const Unigine::LandscapeTexturesPtr &buffer, const Unigine::Math::ivec2 &coord, int data_mask);
	Unigine::LandscapeLayerMapPtr lmap;
	Unigine::PlayerPtr player;
	Unigine::LandscapeFetchPtr landscape_fetch;
	Unigine::MaterialPtr brush_material;
	Unigine::EventConnections connections;

```

</details>


<details>
<summary>LandscapeBrush.cpp | Закрыть</summary>

```cpp
#include "LandscapeBrush.h"
#include <UnigineGame.h>
REGISTER_COMPONENT(LandscapeBrush);

using namespace Unigine;
using namespace Math;

// изменение на основе GPU
void LandscapeBrush::my_texture_draw(const UGUID &guid, int id, const LandscapeTexturesPtr &buffer, const Math::ivec2 &coord, int data_mask)
{
	// задаём необходимые текстуры (например, альбедо и высоты)
	brush_material->setTexture("terrain_albedo", buffer->getAlbedo());
	brush_material->setTexture("terrain_height", buffer->getHeight());

	// настраиваем параметры материала кисти (размер, цвет и т.д., а также указываем маски, на которые влияет кисть)
	brush_material->setParameterFloat("size", brush_size);
	brush_material->setParameterFloat("height", brush_height);
	brush_material->setParameterFloat4("color", Math::vec4_green);
	brush_material->setParameterInt("data_mask", data_mask);

	// запускаем выражение "brush" материала
	brush_material->runExpression("brush", buffer->getResolution().x, buffer->getResolution().y);

	// сбрасываем текстуры материала
	brush_material->setTexture("terrain_albedo", nullptr);
	brush_material->setTexture("terrain_height", nullptr);
}

void LandscapeBrush::init()
{
	// получаем нужный материал кисти (встроенная в редактор кисть "circle_soft") и наследуем от него дочерний материал
	auto guid = FileSystem::getGUID(FileSystem::resolvePartialVirtualPath("circle_soft.brush"));
	if (!guid.isValid())
	{
		Log::warning("LandscapePainter::init(): can not find \"circle_soft.brush\" material\n");
		return;
	}

	brush_material = Materials::findMaterialByFileGUID(guid)->inherit();

	// получаем существующий объект landscape terrain
	ObjectLandscapeTerrainPtr terrain = Landscape::getActiveTerrain();

	// получаем первую layermap, которую мы будем изменять
	lmap = checked_ptr_cast<LandscapeLayerMap>(terrain->getChild(0));

	// подписываемся на операцию Texture Draw
	Landscape::getEventTextureDraw().connect(connections, this, &LandscapeBrush::my_texture_draw);

	// задаём режим обработки мыши USER, чтобы отобразить курсор на экране
	ControlsApp::setMouseHandle(Input::MOUSE_HANDLE_USER);

	// получаем текущего игрока
	player = Game::getPlayer();

	return;
}

void LandscapeBrush::update()
{
	// Здесь напишите код, который должен вызываться перед обновлением каждого кадра рендеринга: укажите все функции, связанные с графикой, которые должны вызываться каждый кадр во время работы приложения.
	// если нажата правая кнопка мыши
	if (Input::isMouseButtonDown(Input::MOUSE_BUTTON_RIGHT))
	{
		landscape_fetch = LandscapeFetch::create();

		// получаем направление от текущей позиции мыши
		Math::ivec2 mouse = Input::getMousePosition();
		Math::Vec3 dir = Math::Vec3(player->getDirectionFromMainWindow(mouse.x, mouse.y));
		// получаем координаты точки пересечения
		bool fetched = landscape_fetch->intersectionForce(player->getPosition(),
			player->getPosition() + Vec3(dir) * 10000.0);

		if (fetched)
		{
			// получаем локальную позицию кисти относительно карты слоя
			Vec3 brush_local_position = lmap->getIWorldTransform() * landscape_fetch->getPosition();

			// вычисляем границы области карты слоя, на которую воздействует кисть
			float half_size = brush_size / 2.0f;
			Vec3 brush_local_corners[4] = {
				brush_local_position + Vec3(-half_size, -half_size, 0.0),
				brush_local_position + Vec3(half_size, -half_size, 0.0),
				brush_local_position + Vec3(-half_size,  half_size, 0.0),
				brush_local_position + Vec3(half_size,  half_size, 0.0)
			};
			auto brush_local_bbox_min = Vec2{
				min(min(brush_local_corners[0].x, brush_local_corners[1].x), min(brush_local_corners[2].x, brush_local_corners[3].x)),
				min(min(brush_local_corners[0].y, brush_local_corners[1].y), min(brush_local_corners[2].y, brush_local_corners[3].y))
			};
			auto brush_local_bbox_max = Vec2{
				max(max(brush_local_corners[0].x, brush_local_corners[1].x), max(brush_local_corners[2].x, brush_local_corners[3].x)),
				max(max(brush_local_corners[0].y, brush_local_corners[1].y), max(brush_local_corners[2].y, brush_local_corners[3].y))
			};

			// вычисляем количество пикселей на единицу длины
			auto pixels_per_unit = Vec2{ lmap->getResolution() } / Vec2{ lmap->getSize() };

			// вычисляем координаты и размер области текстуры слоя ландшафта, которую нужно изменить
			auto drawing_region_coord = ivec2{ pixels_per_unit * brush_local_bbox_min };
			auto drawing_region_size = ivec2{ pixels_per_unit * (brush_local_bbox_max - brush_local_bbox_min) };

			// пользовательский код (привязка к ID)
			auto id = Landscape::generateOperationID();

			// запускаем операцию Texture Draw для выбранной карты ландшафта для области с указанными координатами и размером
			// затрагивая данные Height и Albedo
			Landscape::asyncTextureDraw(id, lmap->getGUID(), drawing_region_coord,
				drawing_region_size, Landscape::FLAGS_DATA_HEIGHT | Landscape::FLAGS_DATA_ALBEDO);
		}

	}
	return;
}

void LandscapeBrush::shutdown()
{
	// удаляем все подписки
	connections.disconnectAll();

	return;
}


```

</details>


### См. также


- C++ sample
- C++ sample
- C++ sample


## Landscape Class

### Перечисления

## TYPE_DATA

| Name | Description |
|---|---|
| **TYPE_DATA_HEIGHT** = 0 | Heights data type. |
| **TYPE_DATA_ALBEDO** = 1 | Albedo data type. |
| **TYPE_DATA_MASK_0** = 2 | Mask0 data type. |
| **TYPE_DATA_MASK_1** = 3 | Mask1 data type. |
| **TYPE_DATA_MASK_2** = 4 | Mask2 data type. |
| **TYPE_DATA_MASK_3** = 5 | Mask3 data type. |
| **TYPE_DATA_MASK_4** = 6 | Mask4 data type. |
| **TYPE_DATA_MASK_5** = 7 | Mask5 data type. |
| **TYPE_DATA_MASK_6** = 8 | Mask6 data type. |
| **TYPE_DATA_MASK_7** = 9 | Mask7 data type. |
| **TYPE_DATA_MASK_8** = 10 | Mask8 data type. |
| **TYPE_DATA_MASK_9** = 11 | Mask9 data type. |
| **TYPE_DATA_MASK_10** = 12 | Mask10 data type. |
| **TYPE_DATA_MASK_11** = 13 | Mask11 data type. |
| **TYPE_DATA_MASK_12** = 14 | Mask12 data type. |
| **TYPE_DATA_MASK_13** = 15 | Mask13 data type. |
| **TYPE_DATA_MASK_14** = 16 | Mask14 data type. |
| **TYPE_DATA_MASK_15** = 17 | Mask15 data type. |
| **TYPE_DATA_MASK_16** = 18 | Mask16 data type. |
| **TYPE_DATA_MASK_17** = 19 | Mask17 data type. |
| **TYPE_DATA_MASK_18** = 20 | Mask18 data type. |
| **TYPE_DATA_MASK_19** = 21 | Mask19 data type. |

## FLAGS_DATA

| Name | Description |
|---|---|
| **FLAGS_DATA_HEIGHT** = 1 << 0 | Heights data flag. |
| **FLAGS_DATA_ALBEDO** = 1 << 1 | Albedo data flag. |
| **FLAGS_DATA_MASK_0** = 1 << 2 | Mask0 data flag. |
| **FLAGS_DATA_MASK_1** = 1 << 3 | Mask1 data flag. |
| **FLAGS_DATA_MASK_2** = 1 << 4 | Mask2 data flag. |
| **FLAGS_DATA_MASK_3** = 1 << 5 | Mask3 data flag. |
| **FLAGS_DATA_MASK_4** = 1 << 6 | Mask4 data flag. |
| **FLAGS_DATA_MASK_5** = 1 << 7 | Mask5 data flag. |
| **FLAGS_DATA_MASK_6** = 1 << 8 | Mask6 data flag. |
| **FLAGS_DATA_MASK_7** = 1 << 9 | Mask7 data flag. |
| **FLAGS_DATA_MASK_8** = 1 << 10 | Mask8 data flag. |
| **FLAGS_DATA_MASK_9** = 1 << 11 | Mask9 data flag. |
| **FLAGS_DATA_MASK_10** = 1 << 12 | Mask10 data flag. |
| **FLAGS_DATA_MASK_11** = 1 << 13 | Mask11 data flag. |
| **FLAGS_DATA_MASK_12** = 1 << 14 | Mask12 data flag. |
| **FLAGS_DATA_MASK_13** = 1 << 15 | Mask13 data flag. |
| **FLAGS_DATA_MASK_14** = 1 << 16 | Mask14 data flag. |
| **FLAGS_DATA_MASK_15** = 1 << 17 | Mask15 data flag. |
| **FLAGS_DATA_MASK_16** = 1 << 18 | Mask16 data flag. |
| **FLAGS_DATA_MASK_17** = 1 << 19 | Mask17 data flag. |
| **FLAGS_DATA_MASK_18** = 1 << 20 | Mask18 data flag. |
| **FLAGS_DATA_MASK_19** = 1 << 21 | Mask19 data flag. |

## TYPE_FILE_DATA

Типы данных файлов.
| Name | Description |
|---|---|
| **TYPE_FILE_DATA_HEIGHT** = 0 | Данные высот файла карты ландшафта. |
| **TYPE_FILE_DATA_ALBEDO** = 1 | Данные альбедо файла карты ландшафта. |
| **TYPE_FILE_DATA_MASK_0** = 2 | Данные детализирующих масок файла карты ландшафта (маски с индексами 0, 1, 2, 3). |
| **TYPE_FILE_DATA_MASK_1** = 3 | Данные детализирующих масок файла карты ландшафта (маски с индексами 4, 5, 6, 7). |
| **TYPE_FILE_DATA_MASK_2** = 4 | Данные детализирующих масок файла карты ландшафта (маски 8, 9, 10, 11). |
| **TYPE_FILE_DATA_MASK_3** = 5 | Данные детализирующих масок файла карты ландшафта (маски с индексами 12, 13, 14, 15). |
| **TYPE_FILE_DATA_MASK_4** = 6 | Данные детализирующих масок файла карты ландшафта (маски с индексами 16, 17, 18, 19). |
| **TYPE_FILE_DATA_OPACITY_HEIGHT** = 7 | Данные непрозрачности высот файла карты ландшафта. |
| **TYPE_FILE_DATA_OPACITY_MASK_0** = 8 | Данные непрозрачности детализирующих масок файла карты ландшафта (маски с индексами 0, 1, 2, 3). |
| **TYPE_FILE_DATA_OPACITY_MASK_1** = 9 | Данные непрозрачности детализирующих масок файла карты ландшафта (маски с индексами 4, 5, 6, 7). |
| **TYPE_FILE_DATA_OPACITY_MASK_2** = 10 | Данные непрозрачности детализирующих масок файла карты ландшафта (маски с индексами 8, 9, 10, 11). |
| **TYPE_FILE_DATA_OPACITY_MASK_3** = 11 | Данные непрозрачности детализирующих масок файла карты ландшафта (маски с индексами 12, 13, 14, 15). |
| **TYPE_FILE_DATA_OPACITY_MASK_4** = 12 | Данные непрозрачности детализирующих масок файла карты ландшафта (маски с индексами 16, 17, 18, 19). |

## FLAGS_FILE_DATA

Флаги слоёв данных файла.
| Name | Description |
|---|---|
| **FLAGS_FILE_DATA_HEIGHT** = 1 << 0 | Данные высот файла карты ландшафта. |
| **FLAGS_FILE_DATA_ALBEDO** = 1 << 1 | Данные альбедо файла карты ландшафта. |
| **FLAGS_FILE_DATA_MASK_0** = 1 << 2 | Первый блок данных масок файла карты ландшафта (маски с индексами 0,1,2,3). |
| **FLAGS_FILE_DATA_MASK_1** = 1 << 3 | Второй блок данных масок файла карты ландшафта (маски с индексами 4,5,6,7). |
| **FLAGS_FILE_DATA_MASK_2** = 1 << 4 | Третий блок данных масок файла карты ландшафта (маски с индексами 8,9,10,11). |
| **FLAGS_FILE_DATA_MASK_3** = 1 << 5 | Четвёртый блок данных масок файла карты ландшафта (маски с индексами 12,13,14,15). |
| **FLAGS_FILE_DATA_MASK_4** = 1 << 6 | Пятый блок данных масок файла карты ландшафта (маски с индексами 16,17,18,19). |
| **FLAGS_FILE_DATA_OPACITY_HEIGHT** = 1 << 7 | Данные непрозрачности высот файла карты ландшафта. |
| **FLAGS_FILE_DATA_OPACITY_MASK_0** = 1 << 8 | Первый блок данных непрозрачности масок файла карты ландшафта (для масок с индексами 0,1,2,3). |
| **FLAGS_FILE_DATA_OPACITY_MASK_1** = 1 << 9 | Второй блок данных непрозрачности масок файла карты ландшафта (для масок с индексами 4,5,6,7). |
| **FLAGS_FILE_DATA_OPACITY_MASK_2** = 1 << 10 | Третий блок данных непрозрачности масок файла карты ландшафта (для масок с индексами 8,9,10,11). |
| **FLAGS_FILE_DATA_OPACITY_MASK_3** = 1 << 11 | Четвёртый блок данных непрозрачности масок файла карты ландшафта (для масок с индексами 12,13,14,15). |
| **FLAGS_FILE_DATA_OPACITY_MASK_4** = 1 << 12 | Пятый блок данных непрозрачности масок файла карты ландшафта (для масок с индексами 16,17,18,19). |

## COMPRESSOR_TYPE

Метод сжатия, используемый для карты слоя.
| Name | Description |
|---|---|
| **COMPRESSOR_TYPE_NONE** = 0 | Сжатие не используется. |
| **COMPRESSOR_TYPE_JACKALLESS** = 1 | Используется сжатие **Our Method**. Оно оптимизировано для сжатия 2D- и 3D-текстур и обеспечивает лучшие результаты, чем **LZ4** и **Zlib**, без снижения качества. |
| **COMPRESSOR_TYPE_LZ4** = 2 | Используется сжатие **LZ4** (временная опция, планируется к удалению в будущих релизах). |
| **COMPRESSOR_TYPE_ZLIB** = 3 | Сжатие **Zlib** (может обеспечить до 2 раз более высокий коэффициент сжатия, но занимает до 20 раз больше времени). |

## BLENDING_MODE

Режим смешивания, используемый для карты слоя.
| Name | Description |
|---|---|
| **ALPHA_BLEND** = 0 | Режим альфа-смешивания — цвета карты слоя и нижележащей карты смешиваются. |
| **ADDITIVE** = 1 | Аддитивный режим смешивания — данные карты слоя добавляются поверх данных нижележащих карт. |
| **OVERLAY** = 2 | Режим наложения (overlay) — данные карты слоя заменяют данные нижележащих карт. |
| **MULTIPLICATIVE** = 3 | Режим умножения — цвета альбедо нижележащей карты умножаются на цвета карты слоя. |

### Методы класса

## bool isFilesClosed () const

Возвращает текущее значение, указывающее, закрыты ли файлы `.lmap` для всех [landscape layer map](../../../../api/library/objects/landscape_terrain/class.landscapelayermap_cpp.md). Вызывайте этот метод перед внесением любых изменений (изменение, удаление, переименование) в файлы `.lmap` объекта landscape terrain, чтобы убедиться, что эти файлы в данный момент не используются движком, во избежание конфликтов. Если это не так, вы можете использовать метод [*filesClose()*](#filesClose_void), чтобы закрыть их.
### Возвращаемое значение

**true**, если файлы `.lmap` для всех landscape layer map закрыты; иначе **false**.
## static Event<const UGUID &, int, const char *, const char *> getEventSaveFile () const

Событие, вызываемое при применении изменений, внесённых в файл landscape layer map, и сохранении старого и нового состояний во временные файлы. Сигнатура обработчика события должна быть следующей:
```cpp
void savefile_event_handler(const UGUID & guid,  int operation_id,  const char * path_new_state,  const char * path_old_state)

```

 You can subscribe to events via *connect()* and unsubscribe via *disconnect()*. You can also use *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* and *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* classes for convenience (see examples below).

> **Notice:** For more details see the [Event Handling](../../../../code/fundamentals/events/index_cpp.md) article.

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const UGUID & **guid**, int **operation_id**, const char * **path_new_state**, const char * **path_old_state**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события SaveFile
void savefile_event_handler(const UGUID & guid,  int operation_id,  const char * path_new_state,  const char * path_old_state)
{
	Log::message("\Обработка события SaveFile\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections savefile_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Landscape::getEventSaveFile().connect(savefile_event_connections, savefile_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Landscape::getEventSaveFile().connect(savefile_event_connections, [](const UGUID & guid,  int operation_id,  const char * path_new_state,  const char * path_old_state) {
		Log::message("\Обработка события SaveFile (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
savefile_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection savefile_event_connection;

// подписываемся на событие SaveFile с функцией-обработчиком, сохраняя соединение
Landscape::getEventSaveFile().connect(savefile_event_connection, savefile_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
savefile_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
savefile_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие SaveFile через соединение
savefile_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события SaveFile, реализованный как член класса
	void event_handler(const UGUID & guid,  int operation_id,  const char * path_new_state,  const char * path_old_state)
	{
		Log::message("\Обработка события SaveFile\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Landscape::getEventSaveFile().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId savefile_handler_id;

// подписываемся на событие SaveFile с лямбда-обработчиком, сохраняя идентификатор соединения
savefile_handler_id = Landscape::getEventSaveFile().connect(e_connections, [](const UGUID & guid,  int operation_id,  const char * path_new_state,  const char * path_old_state) {
		Log::message("\Обработка события SaveFile (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Landscape::getEventSaveFile().disconnect(savefile_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий SaveFile при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Landscape::getEventSaveFile().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Landscape::getEventSaveFile().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const UGUID &, int, const char *> getEventApplyDiff () const

Событие, вызываемое при применении diff к файлу landscape layer map. Сигнатура обработчика события должна быть следующей:
```cpp
void applydiff_event_handler(const UGUID & guid,  int operation_id,  const char * lmap_file_path)

```

 You can subscribe to events via *connect()* and unsubscribe via *disconnect()*. You can also use *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* and *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* classes for convenience (see examples below).

> **Notice:** For more details see the [Event Handling](../../../../code/fundamentals/events/index_cpp.md) article.

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const UGUID & **guid**, int **operation_id**, const char * **lmap_file_path**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события ApplyDiff
void applydiff_event_handler(const UGUID & guid,  int operation_id,  const char * lmap_file_path)
{
	Log::message("\Обработка события ApplyDiff\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections applydiff_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Landscape::getEventApplyDiff().connect(applydiff_event_connections, applydiff_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Landscape::getEventApplyDiff().connect(applydiff_event_connections, [](const UGUID & guid,  int operation_id,  const char * lmap_file_path) {
		Log::message("\Обработка события ApplyDiff (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
applydiff_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection applydiff_event_connection;

// подписываемся на событие ApplyDiff с функцией-обработчиком, сохраняя соединение
Landscape::getEventApplyDiff().connect(applydiff_event_connection, applydiff_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
applydiff_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
applydiff_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие ApplyDiff через соединение
applydiff_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события ApplyDiff, реализованный как член класса
	void event_handler(const UGUID & guid,  int operation_id,  const char * lmap_file_path)
	{
		Log::message("\Обработка события ApplyDiff\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Landscape::getEventApplyDiff().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId applydiff_handler_id;

// подписываемся на событие ApplyDiff с лямбда-обработчиком, сохраняя идентификатор соединения
applydiff_handler_id = Landscape::getEventApplyDiff().connect(e_connections, [](const UGUID & guid,  int operation_id,  const char * lmap_file_path) {
		Log::message("\Обработка события ApplyDiff (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Landscape::getEventApplyDiff().disconnect(applydiff_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий ApplyDiff при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Landscape::getEventApplyDiff().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Landscape::getEventApplyDiff().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const UGUID &, int, const Ptr < LandscapeTextures > &, const Math:: ivec2 &, int> getEventTextureDraw () const

Событие, вызываемое при выполнении операции Texture Draw (изменение террейна на основе GPU). Сигнатура обработчика события должна быть следующей:
```cpp
void texturedraw_event_handler(const UGUID & guid,  int operation_id,  const Ptr<LandscapeTextures> & buffer,  const Math::ivec2 & coords,  int data_mask)

```

 You can subscribe to events via *connect()* and unsubscribe via *disconnect()*. You can also use *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* and *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* classes for convenience (see examples below).

> **Notice:** For more details see the [Event Handling](../../../../code/fundamentals/events/index_cpp.md) article.

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const UGUID & **guid**, int **operation_id**, const Ptr<LandscapeTextures> & **buffer**, const Math::ivec2 & **coords**, int **data_mask**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события TextureDraw
void texturedraw_event_handler(const UGUID & guid,  int operation_id,  const Ptr<LandscapeTextures> & buffer,  const Math::ivec2 & coords,  int data_mask)
{
	Log::message("\Обработка события TextureDraw\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections texturedraw_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Landscape::getEventTextureDraw().connect(texturedraw_event_connections, texturedraw_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Landscape::getEventTextureDraw().connect(texturedraw_event_connections, [](const UGUID & guid,  int operation_id,  const Ptr<LandscapeTextures> & buffer,  const Math::ivec2 & coords,  int data_mask) {
		Log::message("\Обработка события TextureDraw (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
texturedraw_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection texturedraw_event_connection;

// подписываемся на событие TextureDraw с функцией-обработчиком, сохраняя соединение
Landscape::getEventTextureDraw().connect(texturedraw_event_connection, texturedraw_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
texturedraw_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
texturedraw_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие TextureDraw через соединение
texturedraw_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события TextureDraw, реализованный как член класса
	void event_handler(const UGUID & guid,  int operation_id,  const Ptr<LandscapeTextures> & buffer,  const Math::ivec2 & coords,  int data_mask)
	{
		Log::message("\Обработка события TextureDraw\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Landscape::getEventTextureDraw().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId texturedraw_handler_id;

// подписываемся на событие TextureDraw с лямбда-обработчиком, сохраняя идентификатор соединения
texturedraw_handler_id = Landscape::getEventTextureDraw().connect(e_connections, [](const UGUID & guid,  int operation_id,  const Ptr<LandscapeTextures> & buffer,  const Math::ivec2 & coords,  int data_mask) {
		Log::message("\Обработка события TextureDraw (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Landscape::getEventTextureDraw().disconnect(texturedraw_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий TextureDraw при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Landscape::getEventTextureDraw().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Landscape::getEventTextureDraw().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
---

## bool terrainLoad ( const Math:: WorldBoundBox & bb )

Загружает данные террейна (тайлы) для всех landscape layer map в пределах указанного ограничивающего объёма в кэш.
### Аргументы

- *const  Math::[WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb** - Ограничивающий объём, определяющий landscape layer map, для которых нужно загрузить данные.

### Возвращаемое значение

true, если данные террейна успешно загружены для всех landscape layer map в пределах указанного ограничивающего объёма; иначе false.
## bool render ( const Ptr < LandscapeTextures > & buffers , const Math:: Mat4 & transform , Math::Scalar texel_size )

Отрисовывает область указанных landscape layer map, определённую заданной трансформацией и размером тексела, в указанные [buffers](../../../../api/library/objects/landscape_terrain/class.landscapetextures_cpp.md).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[LandscapeTextures](../../../../api/library/objects/landscape_terrain/class.landscapetextures_cpp.md)> &* **buffers** - Целевые [texture buffers](../../../../api/library/objects/landscape_terrain/class.landscapetextures_cpp.md), в которые отрисовываются указанные landscape layer map.
- *const  Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **transform** - Трансформация области landscape terrain, которую нужно отрисовать (координата Z игнорируется).
- *Math::Scalar* **texel_size** - Размер тексела, который нужно использовать. Определяет размер области в зависимости от разрешения *buffers*.

### Возвращаемое значение

true, если данные области landscape terrain (все landscape layer map), определённые указанной трансформацией и размером тексела, успешно отрисованы в указанные буферы; иначе false.
## bool render ( const Ptr < LandscapeTextures > & buffers , const Math:: Mat4 & transform , Math::Scalar texel_size , int padding )

Отрисовывает область указанных landscape layer map, определённую заданной трансформацией и размером тексела, в указанные [buffers](../../../../api/library/objects/landscape_terrain/class.landscapetextures_cpp.md). Используйте параметр *padding*, чтобы задать размер внутреннего отступа для области (при необходимости).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[LandscapeTextures](../../../../api/library/objects/landscape_terrain/class.landscapetextures_cpp.md)> &* **buffers** - Целевые [texture buffers](../../../../api/library/objects/landscape_terrain/class.landscapetextures_cpp.md), в которые отрисовываются указанные landscape layer map.
- *const  Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **transform** - Трансформация области landscape terrain, которую нужно отрисовать (координата Z игнорируется).
- *Math::Scalar* **texel_size** - Размер тексела, который нужно использовать. Определяет размер области в зависимости от разрешения *buffers*.
- *int* **padding** - Размер внутреннего отступа для отрисовываемой области (при необходимости).

### Возвращаемое значение

true, если данные области landscape terrain (все landscape layer map), определённые указанной трансформацией и размером тексела, успешно отрисованы в указанные буферы; иначе false.
## bool render ( const Vector < Ptr < LandscapeLayerMap >> & maps , const Ptr < LandscapeTextures > & buffers , const Math:: Mat4 & transform , Math::Scalar texel_size )

Отрисовывает область указанных landscape layer map, определённую заданной трансформацией и размером тексела, в указанные [buffers](../../../../api/library/objects/landscape_terrain/class.landscapetextures_cpp.md).
### Аргументы

- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../../api/library/common/class.ptr_cpp.md)<[LandscapeLayerMap](../../../../api/library/objects/landscape_terrain/class.landscapelayermap_cpp.md)>> &* **maps** - Список landscape layer map, которые нужно отрисовать.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[LandscapeTextures](../../../../api/library/objects/landscape_terrain/class.landscapetextures_cpp.md)> &* **buffers** - Целевые [texture buffers](../../../../api/library/objects/landscape_terrain/class.landscapetextures_cpp.md), в которые отрисовываются указанные landscape layer map.
- *const  Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **transform** - Трансформация области landscape terrain, которую нужно отрисовать (координата Z игнорируется).
- *Math::Scalar* **texel_size** - Размер тексела, который нужно использовать. Определяет размер области в зависимости от разрешения *buffers*.

### Возвращаемое значение

true, если данные области landscape terrain (указанные landscape layer map), определённые указанной трансформацией и размером тексела, успешно отрисованы в указанные буферы; иначе false.
## bool render ( const Vector < Ptr < LandscapeLayerMap >> & maps , const Ptr < LandscapeTextures > & buffers , const Math:: Mat4 & transform , Math::Scalar texel_size , int padding )

Отрисовывает область указанных landscape layer map, определённую заданной трансформацией и размером тексела, в указанные [buffers](../../../../api/library/objects/landscape_terrain/class.landscapetextures_cpp.md). Используйте параметр *padding*, чтобы задать размер внутреннего отступа для области (при необходимости).
### Аргументы

- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../../api/library/common/class.ptr_cpp.md)<[LandscapeLayerMap](../../../../api/library/objects/landscape_terrain/class.landscapelayermap_cpp.md)>> &* **maps** - Список landscape layer map, которые нужно отрисовать.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[LandscapeTextures](../../../../api/library/objects/landscape_terrain/class.landscapetextures_cpp.md)> &* **buffers** - Целевые [texture buffers](../../../../api/library/objects/landscape_terrain/class.landscapetextures_cpp.md), в которые отрисовываются указанные landscape layer map.
- *const  Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **transform** - Трансформация области landscape terrain, которую нужно отрисовать (координата Z игнорируется).
- *Math::Scalar* **texel_size** - Размер тексела, который нужно использовать. Определяет размер области в зависимости от разрешения *buffers*.
- *int* **padding** - Размер внутреннего отступа для отрисовываемой области.

### Возвращаемое значение

true, если данные области landscape terrain (указанные landscape layer map), определённые указанной трансформацией и размером тексела, успешно отрисованы в указанные буферы; иначе false.
## void asyncTextureDraw ( int operation_id , const UGUID & file_guid , const Math:: ivec2 & coord , const Math:: ivec2 & resolution , int flags_file_data , const Vector < Math:: WorldBoundBox > & bounds_preload_lmaps )

Запускает асинхронную операцию отрисовки на GPU с принудительной предзагрузкой данных террейна в пределах указанного ограничивающего объёма (все landscape layer map). Операция отрисовки представляет собой изменение текстурного буфера указанного размера, взятого в указанных координатах, и объединение слоёв данных, определённых указанными флагами. Сама операция должна быть реализована в обработчике события [TextureDraw](#getEventTextureDraw_Event). Этот метод можно использовать для реализации изменения террейна на основе GPU (например, кистей), которому требуются дополнительные данные за пределами области, заданной параметрами *coords* и *resolution*, а также данные других [landscape layer map](../../../../api/library/objects/landscape_terrain/class.landscapelayermap_cpp.md) (например, кисть копирования).
### Аргументы

- *int* **operation_id** - [operation ID](#generateOperationID_int) отрисовки.
- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **file_guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) файла landscape layer map, который нужно изменить.
- *const  Math::[ivec2](../../../../api/library/math/class.ivec2_cpp.md) &* **coord** - Координаты левого верхнего угла изменяемого сегмента данных landscape layer map по осям X и Y.
- *const  Math::[ivec2](../../../../api/library/math/class.ivec2_cpp.md) &* **resolution** - Разрешение изменяемого сегмента данных landscape layer map по осям X и Y, значение в диапазоне [0, 4096] по каждой оси.
- *int* **flags_file_data** - Маска слоёв данных. Комбинация флагов [FLAGS_FILE_DATA_*](#FLAGS_FILE_DATA_HEIGHT), указывающих затрагиваемые слои данных (высоты, альбедо, определённые маски).
- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)< Math::[WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md)> &* **bounds_preload_lmaps** - [Bounding box](../../../../api/library/math/bounds/class.worldboundbox_cpp.md) (мировой), определяющий область, содержащую тайлы террейна (все landscape layer map), которые нужно загрузить в память перед внесением изменений.

## void asyncTextureDraw ( int operation_id , const UGUID & file_guid , const Math:: ivec2 & coord , const Math:: ivec2 & resolution , int flags_file_data )

Запускает асинхронную операцию отрисовки на GPU. Операция отрисовки представляет собой изменение текстурного буфера указанного размера, взятого в указанных координатах, и объединение слоёв данных, определённых указанными флагами. Сама операция должна быть реализована в обработчике события [TextureDraw](#getEventTextureDraw_Event). Этот метод можно использовать для реализации изменения террейна на основе GPU (например, кистей).
### Аргументы

- *int* **operation_id** - [operation ID](#generateOperationID_int) отрисовки.
- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **file_guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) файла landscape layer map, который нужно изменить.
- *const  Math::[ivec2](../../../../api/library/math/class.ivec2_cpp.md) &* **coord** - Координаты левого верхнего угла изменяемого сегмента данных landscape layer map по осям X и Y.
- *const  Math::[ivec2](../../../../api/library/math/class.ivec2_cpp.md) &* **resolution** - Разрешение изменяемого сегмента данных landscape layer map по осям X и Y, значение в диапазоне [0, 4096] по каждой оси.
- *int* **flags_file_data** - Маска слоёв данных. Комбинация флагов [FLAGS_FILE_DATA_*](#FLAGS_FILE_DATA_HEIGHT), указывающих затрагиваемые слои данных (высоты, альбедо, определённые маски).

## void asyncTextureDraw ( int operation_id , const UGUID & file_guid , const Math:: ivec2 & coord , const Math:: ivec2 & resolution )

Запускает асинхронную операцию отрисовки на GPU. Операция отрисовки представляет собой изменение текстурного буфера указанного размера, взятого в указанных координатах, и объединение всех слоёв данных. Сама операция должна быть реализована в обработчике события [TextureDraw](#getEventTextureDraw_Event). Этот метод можно использовать для реализации изменения террейна на основе GPU (например, кистей).
### Аргументы

- *int* **operation_id** - [operation ID](#generateOperationID_int) отрисовки.
- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **file_guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) файла landscape layer map, который нужно изменить.
- *const  Math::[ivec2](../../../../api/library/math/class.ivec2_cpp.md) &* **coord** - Координаты левого верхнего угла изменяемого сегмента данных landscape layer map по осям X и Y.
- *const  Math::[ivec2](../../../../api/library/math/class.ivec2_cpp.md) &* **resolution** - Разрешение изменяемого сегмента данных landscape layer map по осям X и Y, значение в диапазоне [0, 4096] по каждой оси.

## void asyncTextureDraw ( const UGUID & file_guid , const Math:: ivec2 & coord , const Math:: ivec2 & resolution , int flags_file_data , const Vector < Math:: WorldBoundBox > & bounds_preload_lmaps )

Запускает асинхронную операцию отрисовки на GPU с принудительной предзагрузкой данных террейна в пределах указанного ограничивающего объёма (все landscape layer map). Операция отрисовки представляет собой изменение текстурного буфера указанного размера, взятого в указанных координатах, и объединение слоёв данных, определённых указанными флагами. Сама операция должна быть реализована в обработчике события [TextureDraw](#getEventTextureDraw_Event). Этот метод можно использовать для реализации изменения террейна на основе GPU (например, кистей), которому требуются дополнительные данные за пределами области, заданной параметрами *coords* и *resolution*, а также данные других [landscape layer map](../../../../api/library/objects/landscape_terrain/class.landscapelayermap_cpp.md) (например, кисть копирования).
### Аргументы

- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **file_guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) файла landscape layer map, который нужно изменить.
- *const  Math::[ivec2](../../../../api/library/math/class.ivec2_cpp.md) &* **coord** - Координаты левого верхнего угла изменяемого сегмента данных landscape layer map по осям X и Y.
- *const  Math::[ivec2](../../../../api/library/math/class.ivec2_cpp.md) &* **resolution** - Разрешение изменяемого сегмента данных landscape layer map по осям X и Y, значение в диапазоне [0, 4096] по каждой оси.
- *int* **flags_file_data** - Маска слоёв данных. Комбинация флагов [FLAGS_FILE_DATA_*](#FLAGS_FILE_DATA_HEIGHT), указывающих затрагиваемые слои данных (высоты, альбедо, определённые маски).
- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)< Math::[WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md)> &* **bounds_preload_lmaps** - [Bounding box](../../../../api/library/math/bounds/class.worldboundbox_cpp.md) (мировой), определяющий область, содержащую тайлы террейна (все landscape layer map), которые нужно загрузить в память перед внесением изменений.

## void asyncTextureDraw ( const UGUID & file_guid , const Math:: ivec2 & coord , const Math:: ivec2 & resolution , int flags_file_data )

Запускает асинхронную операцию отрисовки на GPU. Операция отрисовки представляет собой изменение текстурного буфера указанного размера, взятого в указанных координатах, и объединение слоёв данных, определённых указанными флагами. Сама операция должна быть реализована в обработчике события [TextureDraw](#getEventTextureDraw_Event). Этот метод можно использовать для реализации изменения террейна на основе GPU (например, кистей).
### Аргументы

- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **file_guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) файла landscape layer map, который нужно изменить.
- *const  Math::[ivec2](../../../../api/library/math/class.ivec2_cpp.md) &* **coord** - Координаты левого верхнего угла изменяемого сегмента данных landscape layer map по осям X и Y.
- *const  Math::[ivec2](../../../../api/library/math/class.ivec2_cpp.md) &* **resolution** - Разрешение изменяемого сегмента данных landscape layer map по осям X и Y, значение в диапазоне [0, 4096] по каждой оси.
- *int* **flags_file_data** - Маска слоёв данных. Комбинация флагов [FLAGS_FILE_DATA_*](#FLAGS_FILE_DATA_HEIGHT), указывающих затрагиваемые слои данных (высоты, альбедо, определённые маски).

## void asyncTextureDraw ( const UGUID & file_guid , const Math:: ivec2 & coord , const Math:: ivec2 & resolution )

Запускает асинхронную операцию отрисовки на GPU. Операция отрисовки представляет собой изменение текстурного буфера указанного размера, взятого в указанных координатах, и объединение всех слоёв данных. Сама операция должна быть реализована в обработчике события [TextureDraw](#getEventTextureDraw_Event). Этот метод можно использовать для реализации изменения террейна на основе GPU (например, кистей).
### Аргументы

- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **file_guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) файла landscape layer map, который нужно изменить.
- *const  Math::[ivec2](../../../../api/library/math/class.ivec2_cpp.md) &* **coord** - Координаты левого верхнего угла изменяемого сегмента данных landscape layer map по осям X и Y.
- *const  Math::[ivec2](../../../../api/library/math/class.ivec2_cpp.md) &* **resolution** - Разрешение изменяемого сегмента данных landscape layer map по осям X и Y, значение в диапазоне [0, 4096] по каждой оси.

## void asyncTextureDraw ( int operation_id , const UGUID & file_guid , const Math:: ivec2 & coord , const Math:: ivec2 & resolution , int flags_file_data , const Vector < Math:: WorldBoundBox > & bounds_preload_lmaps , const Vector < Math:: WorldBoundBox > & bounds_preload_vtextures )

Запускает асинхронную операцию отрисовки на GPU с принудительной предзагрузкой данных террейна в пределах указанных ограничивающих объёмов, включая как landscape layer map, так и виртуальные текстуры. Операция отрисовки представляет собой изменение текстурного буфера указанного размера, взятого в указанных координатах, и объединение слоёв данных, определённых указанными флагами. Предзагружаемые [virtual texture data](../../../../objects/objects/terrain/landscape_terrain/index.md#virtual_texture) включают цвет поверхности (альбедо), детали поверхности (нормали) и информацию о высоте геометрии (height), используемую для тесселяции террейна. Операция привязана к указанному ID операции и должна быть реализована в обработчике события [TextureDraw](#getEventTextureDraw_Event). Этот метод можно использовать для реализации изменений террейна на основе GPU (например, кистей), которым требуется полный доступ как к [landscape layer map](../../../../api/library/objects/landscape_terrain/class.landscapelayermap_cpp.md), так и к детальным [virtual texture data](../../../../objects/objects/terrain/landscape_terrain/index.md#virtual_texture) за пределами целевой области.
### Аргументы

- *int* **operation_id** - [operation ID](#generateOperationID_int) отрисовки.
- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **file_guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) файла landscape layer map, который нужно изменить.
- *const  Math::[ivec2](../../../../api/library/math/class.ivec2_cpp.md) &* **coord** - Координаты левого верхнего угла изменяемого сегмента данных landscape layer map по осям X и Y.
- *const  Math::[ivec2](../../../../api/library/math/class.ivec2_cpp.md) &* **resolution** - Разрешение изменяемого сегмента данных landscape layer map по осям X и Y, значение в диапазоне [0, 4096] по каждой оси.
- *int* **flags_file_data** - Маска слоёв данных. Комбинация флагов [FLAGS_FILE_DATA_*](#FLAGS_FILE_DATA_HEIGHT), указывающих затрагиваемые слои данных (высоты, альбедо, определённые маски).
- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)< Math::[WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md)> &* **bounds_preload_lmaps** - [Bounding box](../../../../api/library/math/bounds/class.worldboundbox_cpp.md) (мировой), определяющий область, содержащую тайлы террейна (все landscape layer map), которые нужно загрузить в память перед внесением изменений.
- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)< Math::[WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md)> &* **bounds_preload_vtextures** - [Bounding box](../../../../api/library/math/bounds/class.worldboundbox_cpp.md) (мировой), определяющий область, содержащую тайлы террейна (виртуальные текстуры, включая цвет поверхности, нормали и данные о высоте), которые нужно загрузить в память перед внесением изменений.

## void asyncTextureDraw ( const UGUID & file_guid , const Math:: ivec2 & coord , const Math:: ivec2 & resolution , int flags_file_data , const Vector < Math:: WorldBoundBox > & bounds_preload_lmaps , const Vector < Math:: WorldBoundBox > & bounds_preload_vtextures )

Запускает асинхронную операцию отрисовки на GPU с принудительной предзагрузкой данных террейна в пределах указанных ограничивающих объёмов, включая как landscape layer map, так и виртуальные текстуры. Операция отрисовки представляет собой изменение текстурного буфера указанного размера, взятого в указанных координатах, и объединение слоёв данных, определённых указанными флагами. Предзагружаемые [virtual texture data](../../../../objects/objects/terrain/landscape_terrain/index.md#virtual_texture) включают цвет поверхности (альбедо), детали поверхности (нормали) и информацию о высоте геометрии (height), используемую для тесселяции террейна. Операция должна быть реализована в обработчике события [TextureDraw](#getEventTextureDraw_Event). Этот метод можно использовать для реализации изменений террейна на основе GPU (например, кистей), которым требуется полный доступ как к [landscape layer map](../../../../api/library/objects/landscape_terrain/class.landscapelayermap_cpp.md), так и к детальным [virtual texture data](../../../../objects/objects/terrain/landscape_terrain/index.md#virtual_texture) за пределами целевой области.
### Аргументы

- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **file_guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) файла landscape layer map, который нужно изменить.
- *const  Math::[ivec2](../../../../api/library/math/class.ivec2_cpp.md) &* **coord** - Координаты левого верхнего угла изменяемого сегмента данных landscape layer map по осям X и Y.
- *const  Math::[ivec2](../../../../api/library/math/class.ivec2_cpp.md) &* **resolution** - Разрешение изменяемого сегмента данных landscape layer map по осям X и Y, значение в диапазоне [0, 4096] по каждой оси.
- *int* **flags_file_data** - Маска слоёв данных. Комбинация флагов [FLAGS_FILE_DATA_*](#FLAGS_FILE_DATA_HEIGHT), указывающих затрагиваемые слои данных (высоты, альбедо, определённые маски).
- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)< Math::[WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md)> &* **bounds_preload_lmaps** - [Bounding box](../../../../api/library/math/bounds/class.worldboundbox_cpp.md) (мировой), определяющий область, содержащую тайлы террейна (все landscape layer map), которые нужно загрузить в память перед внесением изменений.
- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)< Math::[WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md)> &* **bounds_preload_vtextures** - [Bounding box](../../../../api/library/math/bounds/class.worldboundbox_cpp.md) (мировой), определяющий область, содержащую тайлы террейна (виртуальные текстуры, включая цвет поверхности, нормали и данные о высоте), которые нужно загрузить в память перед внесением изменений.

## void asyncApplyDiff ( int operation_id , const UGUID & file_guid , const char * path )

Применяет состояние landscape layer map, сохранённое в указанном файле, к файлу landscape layer map с указанным GUID.
### Аргументы

- *int* **operation_id** - [operation ID](#generateOperationID_int).
- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **file_guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) файла landscape layer map, к которому нужно применить состояние, сохранённое по указанному пути.
- *const char ** **path** - Путь к файлу, в котором хранится текущее состояние изменений карты ландшафта.

## void asyncApplyDiff ( const UGUID & file_guid , const char * path )

Применяет состояние landscape layer map, сохранённое в указанном файле, к файлу landscape layer map с указанным GUID.
### Аргументы

- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **file_guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) файла landscape layer map, к которому нужно применить состояние, сохранённое по указанному пути.
- *const char ** **path** - Путь к файлу, в котором хранится текущее состояние изменений карты ландшафта.

## void asyncSaveFile ( int operation_id , const UGUID & file_guid )

Сохраняет файл landscape layer map с указанным GUID.
### Аргументы

- *int* **operation_id** - [operation ID](#generateOperationID_int).
- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **file_guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) файла landscape layer map.

## void asyncSaveFile ( const UGUID & file_guid )

Сохраняет файл landscape layer map с указанным GUID.
### Аргументы

- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **file_guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) файла landscape layer map.

## void asyncSaveFile ( int operation_id , const UGUID & file_guid , const char * path_new_diff , const char * path_old_diff )

Сохраняет указанный файл landscape layer map, применяя все изменения, а также сохраняя старое и новое состояния (diff) во временные файлы. Эти временные файлы можно использовать для выполнения операций отмены/повтора через метод [*applyDiff()*](#asyncApplyDiff_UGUID_cstr_void).
### Аргументы

- *int* **operation_id** - [operation ID](#generateOperationID_int).
- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **file_guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) файла landscape layer map.
- *const char ** **path_new_diff** - Путь к файлу для хранения нового состояния landscape layer map.
- *const char ** **path_old_diff** - Путь к файлу для хранения старого состояния landscape layer map.

## void asyncSaveFile ( const UGUID & file_guid , const char * path_new_diff , const char * path_old_diff )

Сохраняет указанный файл landscape layer map, применяя все изменения, а также сохраняя старое и новое состояния (diff) во временные файлы. Эти временные файлы можно использовать для выполнения операций отмены/повтора через метод [*applyDiff()*](#asyncApplyDiff_UGUID_cstr_void).
```cpp
UGUID lmap_file_guid;	// GUID файла .lmap
String cache_path;		// путь к директории кэша

String new_filepath;	// путь для хранения нового состояния
String old_filepath;	// путь для хранения старого состояния

// метод, реализующий операцию "apply"
void apply() override
{
	// генерируем необходимые пути для сохранения состояний (generate_filepath - некоторый абстрактный метод)
	new_filepath = generate_filepath(cache_path);
	old_filepath_ = generate_filepath(cache_path);

	// применяем изменения и сохраняем текущее и предыдущее состояния
	Landscape::asyncSaveFile(lmap_file_guid, new_filepath, old_filepath);
}

// метод, реализующий операцию "undo" путём применения предыдущего сохранённого состояния
void undo() override
{
	if (!old_filepath.empty())
		Landscape::asyncApplyDiff(lmap_file_guid, old_filepath);
}

// метод, реализующий операцию "redo" путём применения нового сохранённого состояния
void redo() override
{
	if (!new_filepath.empty())
		Landscape::asyncApplyDiff(lmap_file_guid, new_filepath);
}

```


### Аргументы

- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **file_guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) файла landscape layer map.
- *const char ** **path_new_diff** - Путь к файлу для хранения нового состояния landscape layer map.
- *const char ** **path_old_diff** - Путь к файлу для хранения старого состояния landscape layer map.

## void filesClose ( const Vector < UGUID > & reload_files )

Закрывает файлы `.lmap` для всех [landscape layer map](../../../../api/library/objects/landscape_terrain/class.landscapelayermap_cpp.md) и перезагружает те, у которых указаны GUID. Этот метод следует вызывать перед внесением любых изменений (изменение, удаление, переименование) в файлы `.lmap` объекта landscape terrain, чтобы избежать конфликтов, так как эти файлы непрерывно стримятся движком. Таким образом, вызывая этот метод, вы сообщаете движку, что он должен прекратить стриминг данных террейна. Список сообщает движку, какие файлы больше не действительны и должны быть перезагружены или удалены. После завершения изменений следует вызвать метод [*filesOpen()*](#filesOpen_void), чтобы возобновить операции стриминга.
### Аргументы

- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<[UGUID](../../../../api/library/filesystem/class.uguid_cpp.md)> &* **reload_files** - Список [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) файлов `.lmap`, которые нужно перезагрузить. Этот список должен содержать файлы `.lmap`, которые были удалены или у которых изменились данные (альбедо, высоты, маски). Если таких файлов нет, можно просто вызвать метод [*filesClose()*](#filesClose_void).

## void filesClose ( )

 Закрывает файлы `.lmap` для всех [landscape layer map](../../../../api/library/objects/landscape_terrain/class.landscapelayermap_cpp.md). Этот метод следует вызывать перед внесением любых изменений (изменение, удаление, переименование) в файлы `.lmap` объекта landscape terrain, чтобы избежать конфликтов, так как эти файлы непрерывно стримятся движком. Таким образом, вызывая этот метод, вы сообщаете движку, что он должен прекратить стриминг данных террейна. После завершения изменений следует вызвать метод [*filesOpen()*](#filesOpen_void), чтобы возобновить операции стриминга.
## void filesOpen ( )

 Открывает файлы `.lmap` для всех [landscape layer map](../../../../api/library/objects/landscape_terrain/class.landscapelayermap_cpp.md). Этот метод следует вызывать после внесения любых изменений (изменение, удаление, переименование) в файлы `.lmap` объекта landscape terrain. Перед такими изменениями следует вызывать метод [*filesClose()*](#filesClose_void).
## Ptr < ObjectLandscapeTerrain > getActiveTerrain ( )

Возвращает текущий активный объект [Landscape Terrain](../../../../api/library/objects/landscape_terrain/class.objectlandscapeterrain_cpp.md).
> **Notice:** Если сцена содержит несколько объектов Landscape Terrain, активным (отрисовываемым) может быть только один из них.


### Возвращаемое значение

Объект [Landscape Terrain](../../../../api/library/objects/landscape_terrain/class.objectlandscapeterrain_cpp.md), который в данный момент активен.
## int generateOperationID ( )

Генерирует новый ID для операции. Этот ID используется для управления операциями.
```cpp
int id = Landscape::generateOperationID();
// пользовательский код (привязка к ID)
Landscape::asyncTextureDraw(id, file_guid, coord, resolution, flags_file_data);

```


### Возвращаемое значение

Новый ID операции.
## void asyncResetModifications ( int operation_id , const UGUID & file_guid )

Асинхронно сбрасывает все несохранённые изменения, внесённые в landscape layer map, идентифицируемую GUID файла.
### Аргументы

- *int* **operation_id** - [operation ID](#generateOperationID_int) отрисовки.
- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **file_guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) файла landscape layer map, который нужно восстановить.

## void asyncResetModifications ( const UGUID & file_guid )

Асинхронно сбрасывает все несохранённые изменения, внесённые в landscape layer map, идентифицируемую GUID файла.
### Аргументы

- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **file_guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) of the landscape layer map file to be restored.
