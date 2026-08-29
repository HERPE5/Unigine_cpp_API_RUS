// Перечисляет все зарегистрированные свойства и материалы в проекте. Демонстрирует
// статический доступ Properties:: и Materials:: для обхода базы данных ресурсов.
// Полезно для отладки иерархий наследования материалов/свойств.

#include "MaterialsAndPropertiesSample.h"

#include <UnigineConsole.h>

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(MaterialsAndPropertiesSample)

// Консоль включается, все свойства/материалы перечисляются.
void MaterialsAndPropertiesSample::sample()
{
	Console::setOnscreen(true);
	Console::setOnscreenHeight(100);

	// Свойства
	{
		Log::message("Properties:\n");

		// Проходим по всем доступным свойствам
		for (int j = 0; j < Properties::getNumProperties(); j++)
		{
			PropertyPtr property = Properties::getProperty(j);

			// Выводим имя свойства и количество дочерних свойств
			Log::message("Property: %s (%d children)\n", 
				property->getName(),
				property->getNumChildren());
		}
	}

	Log::message("\n");

	// Материалы
	{
		// Выводим количество материалов
		Log::message("Materials: %d\n", Materials::getNumMaterials());

		// Проходим по всем материалам
		for (int i = 0; i < Materials::getNumMaterials(); i++)
		{
			MaterialPtr material = Materials::getMaterial(i);

			// Выводим путь к файлу материала и количество дочерних материалов
			Log::message("\t%asset: materials: %d\n", 
				material->getFilePath().get(),
				material->getNumChildren());
		}
	}
}


// Консоль скрывается, высота сбрасывается.
void MaterialsAndPropertiesSample::shutdown()
{
	Console::setOnscreen(false);
	Console::setOnscreenHeight(30);
}
