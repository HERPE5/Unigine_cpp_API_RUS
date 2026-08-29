// Настраивает обработку мыши для примера тира. MOUSE_HANDLE_GRAB
// блокирует и скрывает курсор для управления в стиле прицеливания от первого лица.
// Обычное поведение курсора восстанавливается при завершении работы.

#pragma once
#include <UnigineComponentSystem.h>

class BodyFractureShootingGallerySample
	: public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(BodyFractureShootingGallerySample, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void shutdown();
};
