// Пускает луч от камеры через курсор мыши в 3D-сцену. Обнаруживает
// пересечения с объектами, чьи маски совпадают, и отображает имя поражённого объекта.
// Использует getDirectionFromMainWindow() для преобразования экранных координат в мировое направление.

#include "IntersectionMouseRay.h"

#include <UnigineGame.h>

REGISTER_COMPONENT(IntersectionMouseRay)

using namespace Unigine;
using namespace Math;

// Настраивается режим мыши, создаётся виджет подписи попадания.
void IntersectionMouseRay::init()
{
	// Курсор отображается, когда игрок не вращается
	init_handle = Input::getMouseHandle();
	Input::setMouseHandle(Input::MOUSE_HANDLE_SOFT);

	// Создаётся подпись для имени целевого объекта
	current_hit_label = WidgetLabel::create(Gui::getCurrent());
	current_hit_label->setFontSize(30);
	current_hit_label->setFontOutline(1);
	Gui::getCurrent()->addChild(current_hit_label, Gui::ALIGN_OVERLAP);
}

// Луч пускается от камеры через позицию мыши; отображается имя поражённого объекта.
void IntersectionMouseRay::update()
{
	PlayerPtr current_player = Game::getPlayer();

	// 2D-координаты экрана преобразуются в 3D-вектор направления в мировом пространстве.
	// Проекция камеры и отображение viewport обрабатываются функцией getDirectionFromMainWindow().
	ivec2 mouse_coord = Input::getMousePosition();
	Vec3 direction = Vec3(current_player->getDirectionFromMainWindow(mouse_coord.x, mouse_coord.y));

	// Определяется сегмент луча: начало в позиции камеры, продолжение вдоль направления
	Vec3 first_point = current_player->getWorldPosition();
	Vec3 second_point = first_point + (direction * distance);

	// Луч пускается, проверяется пересечение с объектами сцены.
	// Проверяются только объекты, чья маска пересечения перекрывается с 'mask'.
	Unigine::ObjectPtr hit_object = World::getIntersection(first_point, second_point, mask);
	if (hit_object)
	{
		current_hit_label->setText(hit_object->getName());
	}
	else
	{
		current_hit_label->setText("empty hit object");
	}

	// Подпись позиционируется рядом с курсором с небольшим смещением во избежание перекрытия
	GuiPtr window_gui = WindowManager::getMainWindow()->getGui();
	current_hit_label->setPosition(window_gui->getMouseX() + 25, window_gui->getMouseY() + 25);
}

// Режим мыши восстанавливается, виджет подписи удаляется.
void IntersectionMouseRay::shutdown()
{
	Input::setMouseHandle(init_handle);
	Gui::getCurrent()->removeChild(current_hit_label);
}
