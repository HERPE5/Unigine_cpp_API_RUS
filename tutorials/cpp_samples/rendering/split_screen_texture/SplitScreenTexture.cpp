// Рендеринг мультиплеера с разделённым экраном. Две камеры рендерят в отдельные текстуры,
// которые отображаются стопкой по вертикали с помощью виджетов-спрайтов. Также текстуры
// назначаются игровым объектам-дисплеям (TV) для эффекта "картинка в картинке".

#include "SplitScreenTexture.h"

#include <UnigineGame.h>
#include <UnigineGui.h>
#include <UniginePlayers.h>
#include <UnigineTextures.h>
#include <UnigineWindowManager.h>

REGISTER_COMPONENT(SplitScreenTexture);

using namespace Unigine;
using namespace Math;

// Камеры извлекаются из узлов игроков; для каждого вида создаются текстуры и viewport'ы.
void SplitScreenTexture::init()
{
	init_gui();
	// Извлекаем объекты камер из назначенных узлов игроков для рендеринга
	cached_camera_top = checked_ptr_cast<Player>(camera_top.get())->getCamera();
	cached_camera_bottom = checked_ptr_cast<Player>(camera_bottom.get())->getCamera();

	// Создаём текстуры рендер-таргета с размером в половину высоты экрана (раскладка стопкой)
	texture_top = Texture::create();
	create_texture_2D(*texture_top);
	texture_bottom = Texture::create();
	create_texture_2D(*texture_bottom);

	// Каждой камере нужен свой viewport для независимого состояния рендеринга
	viewport_top = Viewport::create();
	viewport_bottom = Viewport::create();

	// Подключаем текстуры к игровым объектам-дисплеям (TV) для эффекта "картинка в картинке"
	bind_texture(display_player1.get(), texture_top);
	bind_texture(display_player2.get(), texture_bottom);
}

// Создаются спрайты GUI и подписи с подсказками управления; рендеринг по умолчанию отключается.
void SplitScreenTexture::init_gui()
{
	// Кэшируем размеры окна для определения изменения размера
	ivec2 window_size = WindowManager::getMainWindow()->getSize();
	current_width = window_size.x;
	current_height = window_size.y;
	auto gui = Gui::getCurrent();

	// Отключаем стандартный рендеринг сцены, поскольку мы обрабатываем его вручную через viewport'ы
	Render::setEnabled(false);

	// Создаём виджеты-спрайты, которые будут отображать отрендеренные текстуры
	widget_top = WidgetSprite::create(gui);
	widget_bottom = WidgetSprite::create(gui);

	// Вертикальная раскладка размещает два вида стопкой (игрок сверху над игроком снизу)
	lay = WidgetVBox::create();
	gui->addChild(lay, Gui::ALIGN_OVERLAP | Gui::ALIGN_BACKGROUND);
	lay->addChild(widget_top);
	lay->addChild(widget_bottom);

	// Подсказки управления для схемы ввода каждого игрока
	wasd_label = setup_label(gui, "Use WASD to move");
	arrows_label = setup_label(gui, "Use arrows to move");
	update_labels_pos();
}

// Создаётся виджет подписи с белым текстом и добавляется в GUI-оверлей.
WidgetLabelPtr SplitScreenTexture::setup_label(Unigine::GuiPtr gui, const char *text)
{
	auto label = WidgetLabel::create(gui, text);
	label->setFontColor(vec4(1.f, 1.f, 1.f, 1.f));
	label->setFontSize(24);
	// Выравнивание ALIGN_OVERLAP позволяет вручную позиционировать поверх других виджетов
	gui->addChild(label, Gui::ALIGN_OVERLAP);
	// Вычисляем размеры подписи для правильного позиционирования
	label->arrange();
	return label;
}

// Подписи позиционируются в верхнем правом углу viewport'а каждого игрока.
void SplitScreenTexture::update_labels_pos()
{
	// Подпись WASD размещается в верхнем viewport'е (игрок 1)
	wasd_label->setPosition(current_width - 30 - wasd_label->getWidth(), 10);
	// Подпись со стрелками размещается в нижнем viewport'е (игрок 2), со смещением на половину высоты экрана
	arrows_label->setPosition(current_width - 30 - arrows_label->getWidth(),
	 	current_height / 2 + 10);
}

// Материал наследуется, чтобы изменения были локальными; UV-трансформация переворачивает текстуру для правильной ориентации.
void SplitScreenTexture::bind_texture(const NodePtr &tv_display, const TexturePtr &texture)
{
	auto obj = checked_ptr_cast<ObjectMeshStatic>(tv_display);
	auto mat = obj->getMaterial(0);
	// Наследуем материал, чтобы назначение текстуры не влияло на другие объекты, использующие тот же материал
	mat = mat->inherit();
	mat->setTexture(mat->findTexture("albedo"), texture);
	// UV-трансформация переворачивает и зеркалирует текстуру для правильной ориентации на TV-дисплее
	mat->setParameterFloat4("uv_transform", vec4(-1.f, Render::isFlipped() ? 1.f : -1.f, 0.f, 0.f));
	obj->setMaterial(mat, 0);
}

// Текстура создаётся с половиной высоты окна для раскладки разделённого экрана стопкой.
void SplitScreenTexture::create_texture_2D(Texture &texture)
{
	// Формат RG11B10F обеспечивает HDR-диапазон цвета; высота уменьшена вдвое для разделения на двух игроков
	texture.create2D(current_width, current_height / 2, Texture::FORMAT_RG11B10F,
		Texture::SAMPLER_FILTER_LINEAR | Texture::SAMPLER_ANISOTROPY_16
			| Texture::FORMAT_USAGE_RENDER);
}

// Каждый viewport рендерит свой вид камеры в текстуру; спрайты отображают результаты.
void SplitScreenTexture::update()
{
	// Пересоздаём текстуры, если размер окна изменился
	update_screen_size();

	// Рендерим вид камеры каждого игрока в соответствующую текстуру
	viewport_top->renderTexture2D(cached_camera_top, texture_top);
	viewport_bottom->renderTexture2D(cached_camera_bottom, texture_bottom);

	// Обновляем виджеты-спрайты отрендеренными текстурами; флаг переворота обрабатывает различия платформ
	widget_top->setRender(texture_top, !Render::isFlipped());
	widget_bottom->setRender(texture_bottom, !Render::isFlipped());
}

// Изменения размера окна запускают пересоздание текстур для соответствия новым размерам.
void SplitScreenTexture::update_screen_size()
{
	ivec2 window_size = WindowManager::getMainWindow()->getSize();
	int app_width = window_size.x;
	bool need_update = false;

	// Проверяем изменение ширины
	if (app_width != current_width)
	{
		current_width = app_width;
		need_update = true;
	}

	// Проверяем изменение высоты
	int app_height = window_size.y;
	if (app_height != current_height)
	{
		need_update = true;
		current_height = app_height;
	}

	// Пересоздаём текстуры с новыми размерами и перепозиционируем подписи
	if (need_update)
	{
		create_texture_2D(*texture_top);
		create_texture_2D(*texture_bottom);
		update_labels_pos();
	}
}

// Рендеринг по умолчанию восстанавливается; все виджеты GUI планируются к удалению.
void SplitScreenTexture::shutdown()
{
	// Повторно включаем стандартный рендеринг, отключённый в init_gui()
	Render::setEnabled(true);
	// Планируем удаление виджетов, чтобы избежать уничтожения во время обработки событий
	lay.deleteLater();
	widget_top.deleteLater();
	widget_bottom.deleteLater();
	wasd_label.deleteLater();
	arrows_label.deleteLater();
}
