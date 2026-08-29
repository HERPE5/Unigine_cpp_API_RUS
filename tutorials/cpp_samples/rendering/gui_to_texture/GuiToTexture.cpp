// Рендерит GUI в текстуру и применяет её к материалу объекта.
// Полезно для внутримировых дисплеев, экранов и интерактивных поверхностей. Цикл обновления
// GUI выполняется вручную вне основного рендеринга для захвата в текстуру.

#include "GuiToTexture.h"

#include <UnigineGame.h>

REGISTER_COMPONENT(GuiToTexture);

using namespace Unigine;

// Выполняет полный цикл рендеринга GUI и захватывает вывод в текстуру с мипмапами.
void GuiToTexture::renderToTexture() const
{

	// Сохраняем состояние рендеринга и помещаем его на вершину стека
	// Чтобы снять текущие настройки, нам нужно будет вызвать RenderState.RestoreState() в конце этого метода
	RenderState::saveState();

	// Теперь очищаем состояние, чтобы наша отрендеренная текстура не зависела от других операций рендеринга
	RenderState::clearStates();

	// Задаём размер вьюпорта, соответствующий разрешению текстуры
	RenderState::setViewport(0, 0, texture_resolution.get().x, texture_resolution.get().y);

	// Теперь привязываем текстуру GUI к слоту 0, так как GUI рендерится в слот 0
	render_target->bindColorTexture(0, gui_texture);
	// Включаем render target
	render_target->enable();
	// Очищаем текстуру и заполняем её чёрным цветом
	RenderState::clearBuffer(RenderState::BUFFER_COLOR, Math::vec4_black);

	// Теперь нам нужно выполнить весь цикл рендеринга gui

	// Включаем gui, чтобы он обновлялся и рендерился
	gui->enable();

	// Обновляем все виджеты
	gui->update();

	// Рендерим gui
	gui->preRender();
	gui->render();

	// Отключаем gui
	gui->disable();

	// Теперь нам нужно освободить render target и отвязать текстуру
	render_target->disable();
	render_target->unbindColorTexture(0);

	// Создаём мипмапы текстуры (набор текстур разного разрешения для обеспечения правильного рендеринга на больших дистанциях)
	gui_texture->createMipmaps();

	// Снимаем состояние рендеринга с вершины стека, чтобы конвейер рендеринга продолжил работу как обычно
	RenderState::restoreState();
}

// Создаются GUI и render target; текстура назначается в указанные слоты материала.
void GuiToTexture::init()
{
	const auto object = checked_ptr_cast<Object>(node);
	if (!object)
	{
		Log::error("GuiToTexture::init: component must be assigned to object");
	}

	// Находим нужную поверхность
	const int surface = object->findSurface(surface_name);
	if (surface == -1)
	{
		Log::error("GuiToTexture::init: surface with name %s not found", surface_name.get());
	}

	render_target = RenderTarget::create();

	// Нам нужно унаследовать материал, так как могут быть другие объекты, использующие этот материал,
	// и мы не хотим, чтобы все объекты в сцене получали gui от этого компонента
	const MaterialPtr material = object->getMaterialInherit(surface);

	gui = Gui::create();
	gui->setSize(texture_resolution.get());
	gui->setDefaultColor(Math::vec4_red);

	// Здесь нам нужно указать формат текстуры: RGBA8
	// и задать флаг FORMAT_USAGE_RENDER, чтобы иметь возможность рендерить в текстуру
	// также нужно указать сэмплер, задав ещё один флаг (билинейный сэмплер в нашем случае)
	gui_texture = Texture::create();
	gui_texture->create2D(texture_resolution.get().x, texture_resolution.get().y,
		Texture::FORMAT_RGBA8, Texture::FORMAT_USAGE_RENDER | Texture::SAMPLER_FILTER_BILINEAR);

	for (int texture_index = 0, num_textures = texture_slot_names.size(); texture_index < num_textures; ++texture_index)
	{
		const ComponentVariableString &texture_name = texture_slot_names[texture_index];
		material->setTexture(texture_name, gui_texture);
	}
}

// Текстура перерисовывается каждый кадр, когда включено автообновление.
void GuiToTexture::update() const
{
	if (auto_update_enabled)
	{
		renderToTexture();
	}
}
