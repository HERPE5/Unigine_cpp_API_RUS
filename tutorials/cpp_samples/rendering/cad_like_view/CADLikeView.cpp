// Раскладка вьюпортов 2x2 в стиле CAD: ортографические обзоры сверху/сбоку/спереди плюс
// один перспективный обзор. У каждого обзора есть куб ориентации для управления камерой.
// Поддерживает перетаскивание-панорамирование в ортографических обзорах и свободную камеру в перспективе.

#include "CADLikeView.h"

#include "ViewportCube.h"

#include <UnigineConsole.h>
#include <UniginePlayers.h>
#include <UnigineViewport.h>
#include <UnigineWindowManager.h>

REGISTER_COMPONENT(CADLikeView);

using namespace Unigine;
using namespace Math;

// Инициализирует камеры, создаёт виджеты вьюпортов и кубы обзора,
// настраивает ортографическую проекцию для технических видов.
void CADLikeView::init()
{
	// Отключаем рендеринг движка на время настройки вьюпортов и камер
	Render::setEnabled(false);

	// Получаем камеры от игроков
	camera_top = checked_ptr_cast<Player>(player_top.get())->getCamera();
	camera_perspective = checked_ptr_cast<Player>(player_perspective.get())->getCamera();
	camera_side = checked_ptr_cast<Player>(player_side.get())->getCamera();
	camera_front = checked_ptr_cast<Player>(player_front.get())->getCamera();

	// Задаём ортографическую проекцию для обзоров сверху/сбоку/спереди
	set_ortho_projection(ortho_width.get(), ortho_height.get());
	last_handle = Input::getMouseHandle();
	Input::setMouseHandle(Input::MOUSE_HANDLE_USER);

	// Создаём виджеты вьюпортов и кубы ориентации
	create_viewports();
	create_viewcubes();
	update_viewcubes_position();
}

// Создаёт четыре виджета WidgetSpriteViewport, расположенных в сетке GridBox 2x2.
void CADLikeView::create_viewports()
{
	// Делим главное окно на сетку 2x2 и создаём вьюпорты для каждого обзора
	const ivec2 window_size = WindowManager::getMainWindow()->getSize();

	current_width = window_size.x;
	current_height = window_size.y;

	const int viewport_width = current_width / 2;
	const int viewport_height = current_height / 2;

	const auto gui = Gui::getCurrent();

	viewport_top = WidgetSpriteViewport::create(gui, viewport_width, viewport_height);
	viewport_perspective = WidgetSpriteViewport::create(gui, viewport_width, viewport_height);
	viewport_side = WidgetSpriteViewport::create(gui, viewport_width, viewport_height);
	viewport_front = WidgetSpriteViewport::create(gui, viewport_width, viewport_height);

	lay = WidgetGridBox::create(gui, 2);
	gui->addChild(lay, Gui::ALIGN_OVERLAP | Gui::ALIGN_BACKGROUND | Gui::ALIGN_EXPAND);

	lay->addChild(viewport_top);
	lay->addChild(viewport_perspective);
	lay->addChild(viewport_side);
	lay->addChild(viewport_front);
}

// Применяет матрицу ортографической проекции к камерам сверху, сбоку и спереди.
void CADLikeView::set_ortho_projection(const float width, const float height)
{
	// Применяем ортографическую проекцию к камерам сверху/сбоку/спереди
	constexpr float z_near = 0.001f;
	constexpr float z_far = 1000.f;
	const mat4 ortho_projection = ortho(-width / 2, width / 2, -height / 2, height / 2, z_near,
		z_far);
	camera_top->setProjection(ortho_projection);
	camera_side->setProjection(ortho_projection);
	camera_front->setProjection(ortho_projection);
}

// Создаёт экземпляры ViewportCube для каждого вьюпорта, задаёт позицию центрирования
// и минимальную дистанцию на основе ограничивающей сферы целевой фигуры.
void CADLikeView::create_viewcubes()
{
	// Создаём кубы ориентации для каждого вьюпорта
	viewcube_top = std::make_unique<ViewportCube>(checked_ptr_cast<Player>(player_top.get()),
		ortho_width, ortho_height);
	viewcube_perspective = std::make_unique<ViewportCube>(
		checked_ptr_cast<Player>(player_perspective.get()), ortho_width, ortho_height);
	viewcube_side = std::make_unique<ViewportCube>(checked_ptr_cast<Player>(player_side.get()),
		ortho_width, ortho_height);
	viewcube_front = std::make_unique<ViewportCube>(checked_ptr_cast<Player>(player_front.get()),
		ortho_width, ortho_height);

	// Блокируем изменение проекции куба обзора для ортографических видов
	viewcube_top->setChangeProjectionEnabled(false);
	viewcube_side->setChangeProjectionEnabled(false);
	viewcube_front->setChangeProjectionEnabled(false);

	// Центрируем кубы обзора на целевой фигуре
	const Vec3 centering_position = figure.get()->getHierarchyWorldBoundSphere().center;
	viewcube_top->setCenteringPosition(centering_position);
	viewcube_perspective->setCenteringPosition(centering_position);
	viewcube_side->setCenteringPosition(centering_position);
	viewcube_front->setCenteringPosition(centering_position);

	// Задаём минимальную дистанцию до фигуры для правильной видимости
	const Scalar min_distance_multiplier = 2.0f;
	const Scalar min_distance = figure.get()->getHierarchyWorldBoundSphere().radius
		* min_distance_multiplier;
	viewcube_top->setMinimalDistance(min_distance);
	viewcube_perspective->setMinimalDistance(min_distance);
	viewcube_side->setMinimalDistance(min_distance);
	viewcube_front->setMinimalDistance(min_distance);
}

// Позиционирует виджеты кубов обзора в правом верхнем углу каждого вьюпорта.
void CADLikeView::update_viewcubes_position()
{
	// Позиционируем кубы обзора в углу каждого вьюпорта
	const ivec2 cube_offset(-130, 10);
	viewcube_top->setViewcubePosition(ivec2(current_width / 2, 0) + cube_offset);
	viewcube_perspective->setViewcubePosition(ivec2(current_width, 0) + cube_offset);
	viewcube_side->setViewcubePosition(ivec2(current_width / 2, current_height / 2) + cube_offset);
	viewcube_front->setViewcubePosition(ivec2(current_width, current_height / 2) + cube_offset);
}

// Обновление каждого кадра: обрабатывает изменение размера окна, ввод,
// назначение камер вьюпортам и обновление кубов обзора.
void CADLikeView::update()
{
	if (!WindowManager::getMainWindow())
		return;

	// Обновляем размеры вьюпортов при изменении размера окна
	update_screen_size();
	update_input();

	// Назначаем камеры вьюпортам
	viewport_top->setCamera(camera_top);
	viewport_perspective->setCamera(camera_perspective);
	viewport_side->setCamera(camera_side);
	viewport_front->setCamera(camera_front);

	// Обновляем кубы ориентации
	viewcube_top->update();
	viewcube_perspective->update();
	viewcube_side->update();
	viewcube_front->update();
}

// Обнаруживает изменение размера окна и соответственно обновляет размеры текстур вьюпортов.
void CADLikeView::update_screen_size()
{
	// Корректируем текстуры вьюпортов и перепозиционируем кубы обзора при изменении размера окна
	const ivec2 window_size = WindowManager::getMainWindow()->getSize();
	bool need_update_viewcubes = false;

	const int window_width = window_size.x;
	if (window_width != current_width)
	{
		need_update_viewcubes = true;
		current_width = window_width;
		const int viewport_width = current_width / 2;
		viewport_top->setTextureWidth(viewport_width);
		viewport_perspective->setTextureWidth(viewport_width);
		viewport_side->setTextureWidth(viewport_width);
		viewport_front->setTextureWidth(viewport_width);
	}

	const int window_height = window_size.y;
	if (window_height != current_height)
	{
		need_update_viewcubes = true;
		current_height = window_height;
		const int viewport_height = window_height / 2;
		viewport_top->setTextureHeight(viewport_height);
		viewport_perspective->setTextureHeight(viewport_height);
		viewport_side->setTextureHeight(viewport_height);
		viewport_front->setTextureHeight(viewport_height);
	}

	if (need_update_viewcubes)
	{
		update_viewcubes_position();
	}
}

// Обрабатывает ввод мыши для перетаскивания вьюпорта и управления перспективной камерой.
void CADLikeView::update_input()
{
	// Игнорируем ввод, когда активна консоль
	if (Console::isActive())
		return;

	// Начинаем перетаскивание игрока (камеры) при нажатии левой кнопки мыши
	if (Input::isMouseButtonDown(Input::MOUSE_BUTTON_LEFT))
	{
		set_dragged_player();
	}

	// Останавливаем перетаскивание при отпускании левой кнопки мыши
	if (Input::isMouseButtonUp(Input::MOUSE_BUTTON_LEFT))
	{
		checked_ptr_cast<Player>(player_perspective.get())->setControlled(false);
		Input::setMouseHandle(Input::MOUSE_HANDLE_USER);
		dragged_player = PlayerPtr();
	}

	// Продолжаем перетаскивание при удержании левой кнопки мыши
	if (Input::isMouseButtonPressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (dragged_player)
		{
			const int viewport_width = current_width / 2;
			const int viewport_height = current_height / 2;

			// Нормализуем дельту мыши относительно текущего вьюпорта
			const Vec2 normalized_delta = Vec2(Input::getMouseDeltaPosition())
				/ Vec2((float)viewport_width, (float)viewport_height);

			// Масштабируем дельту в мировые координаты согласно ортографической проекции
			Vec2 delta_pos = normalized_delta
				* Vec2((itof(current_width) / current_height) * ortho_width, ortho_height);
			delta_pos.x *= -1;

			// Перемещаем игрока (камеру) в сцене
			dragged_player->translate({delta_pos, 0});
		}
	}
}

// Определяет, над каким вьюпортом находится мышь, и настраивает перетаскивание.
// Перспективный вьюпорт включает свободное управление камерой; остальные используют перетаскивание-панорамирование.
void CADLikeView::set_dragged_player()
{
	// Не выбираем игрока, если мышь находится над каким-либо кубом обзора
	if (viewcube_top->isHovered() || viewcube_perspective->isHovered() || viewcube_side->isHovered()
		|| viewcube_front->isHovered())
	{
		return;
	}

	const int viewport_width = current_width / 2;
	const int viewport_height = current_height / 2;

	// Получаем позицию мыши относительно клиентской области окна
	const ivec2 mouse_pos = Input::getMousePosition()
		- WindowManager::getMainWindow()->getClientPosition();

	// Определяем, какого игрока/камеру пользователь намерен перетащить,
	// на основе позиции мыши в сетке вьюпортов 2x2
	if (checkRange(mouse_pos.x, 0, viewport_width))
	{
		if (checkRange(mouse_pos.y, 0, viewport_height))
		{
			dragged_player = checked_ptr_cast<Player>(player_top.get());
		}
		else if (checkRange(mouse_pos.y, viewport_height, current_height))
		{
			dragged_player = checked_ptr_cast<Player>(player_side.get());
		}
	}
	else if (checkRange(mouse_pos.x, viewport_width, current_width))
	{
		if (checkRange(mouse_pos.y, 0, viewport_height))
		{
			// Для перспективного обзора включаем управление мышью
			Input::setMouseHandle(Input::MOUSE_HANDLE_SOFT);
			checked_ptr_cast<Player>(player_perspective.get())->setControlled(true);
		}
		else if (checkRange(mouse_pos.y, viewport_height, current_height))
		{
			dragged_player = checked_ptr_cast<Player>(player_front.get());
		}
	}
}

// Очищает вьюпорты, кубы обзора и восстанавливает настройки рендеринга/ввода.
void CADLikeView::shutdown()
{
	// Восстанавливаем рендеринг движка и обработку ввода, очищаем кубы обзора и раскладку
	Render::setEnabled(true);
	Input::setMouseHandle(last_handle);

	viewcube_top.reset();
	viewcube_perspective.reset();
	viewcube_side.reset();
	viewcube_front.reset();

	lay.deleteLater();
	viewport_top.deleteLater();
	viewport_perspective.deleteLater();
	viewport_side.deleteLater();
	viewport_front.deleteLater();
}
