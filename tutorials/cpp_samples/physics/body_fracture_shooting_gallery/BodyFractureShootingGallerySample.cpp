// Настраивает обработку мыши для примера тира. MOUSE_HANDLE_GRAB
// блокирует и скрывает курсор для прицеливания; восстанавливается в пользовательский режим при завершении работы.

#include "BodyFractureShootingGallerySample.h"

REGISTER_COMPONENT(BodyFractureShootingGallerySample);

using namespace Unigine;

void BodyFractureShootingGallerySample::init()
{
	// Блокируем и скрываем курсор для прицеливания от первого лица
	Input::setMouseHandle(Input::MOUSE_HANDLE_GRAB);
}

void BodyFractureShootingGallerySample::shutdown()
{
	// Восстанавливаем обычное поведение курсора
	Input::setMouseHandle(Input::MOUSE_HANDLE_USER);
}
