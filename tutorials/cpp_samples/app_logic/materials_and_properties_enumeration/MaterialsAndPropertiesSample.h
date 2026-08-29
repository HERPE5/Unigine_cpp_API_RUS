#pragma once

#include <UnigineComponentSystem.h>

// Демонстрирует интроспекцию систем Materials и Properties.
// Показывает запрос зарегистрированных материалов и свойств из движка,
// обход их иерархий и доступ к метаданным (имена, пути, дочерние элементы).
class MaterialsAndPropertiesSample : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(MaterialsAndPropertiesSample, ComponentBase)
	COMPONENT_DESCRIPTION("This component demonstrates querying and printing engine properties and materials, "
							"including their names, file paths, and child counts, to the console.")

	COMPONENT_INIT(sample)
	COMPONENT_SHUTDOWN(shutdown)

private:
	void sample();   // запрашивает и выводит все свойства и материалы
	void shutdown(); // восстанавливает настройки консоли

private:
	bool is_console_onscreen{false}; // сохранённое состояние консоли для восстановления при завершении
};
