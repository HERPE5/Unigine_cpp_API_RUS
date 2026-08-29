// Демонстрирует передачу объектов UNIGINE (Image) между C++ и UnigineScript. Показаны
// три подхода: прямой ImagePtr, Variable с setImage/getImage и система шаблонов
// TypeToVariable/VariableToType для автоматического преобразования типов.

#include "ScriptTransfer.h"

#include "../../utils/UnigineScriptsInterpreter.h"

#include <UnigineInterface.h>
#include <UnigineWorld.h>
#include <UnigineConsole.h>

REGISTER_COMPONENT(ScriptTransfer)

using namespace Unigine;


// ============================================================================
// Приём объектов - три способа принять объекты UNIGINE из скрипта
// ============================================================================

// Способ 0: прямой параметр ImagePtr (автоматическое преобразование)
void my_image_info_0(ImagePtr image)
{
	Log::message("%s my_image_info_0(): %s %d %d (%p)\n", sourse_str, image->getFormatName(),
		image->getWidth(), image->getHeight(), image.get());
}

// Способ 1: параметр Variable с явным извлечением через getImage
void my_image_info_1(const Variable &v)
{
	ImagePtr image = v.getImage(Interpreter::get());

	Log::message("%s my_image_info_1(): %s %d %d (%p)\n", sourse_str, image->getFormatName(),
		image->getWidth(), image->getHeight(), image.get());
}

// Способ 2: параметр Variable с преобразованием через шаблон VariableToType
void my_image_info_2(const Variable &v)
{
	ImagePtr image = VariableToType<ImagePtr>(Interpreter::get(), v).value;

	Log::message("%s my_image_info_2(): %s %d %d (%p)\n", sourse_str, image->getFormatName(),
		image->getWidth(), image->getHeight(), image.get());
}

// ============================================================================
// Возврат объектов - три способа вернуть объекты UNIGINE в скрипт
// ============================================================================

// Постоянные ссылки, чтобы изображения оставались живыми после возврата из функции
ImagePtr image_0;
ImagePtr image_1;
ImagePtr image_2;

// Способ 0: возврат ImagePtr напрямую (автоматическое преобразование)
ImagePtr my_image_create_0()
{
	image_0 = Image::create();
	image_0->create2D(128, 128, Image::FORMAT_RG8);

	return image_0;
}

// Способ 1: возврат Variable с явным оборачиванием через setImage
Variable my_image_create_1()
{
	image_1 = Image::create();
	image_1->create2D(128, 128, Image::FORMAT_RG8);

	Variable v;
	v.setImage(Interpreter::get(), image_1);
	return v;
}

// Способ 2: возврат Variable через преобразование шаблоном TypeToVariable
Variable my_image_create_2()
{
	image_2 = Image::create();
	image_2->create2D(128, 128, Image::FORMAT_RG8);

	return TypeToVariable<ImagePtr>(Interpreter::get(), image_2).value;
}

// ============================================================================
// Регистрация функций
// ============================================================================

// Отложенная регистрация: экспортирует все функции получения информации и создания изображений
USCInterpreter transfer_interpreter([]() {
	Interpreter::addExternFunction("my_image_info_0", MakeExternFunction(&my_image_info_0));
	Interpreter::addExternFunction("my_image_info_1", MakeExternFunction(&my_image_info_1));
	Interpreter::addExternFunction("my_image_info_2", MakeExternFunction(&my_image_info_2));
	Interpreter::addExternFunction("my_image_create_0", MakeExternFunction(&my_image_create_0));
	Interpreter::addExternFunction("my_image_create_1", MakeExternFunction(&my_image_create_1));
	Interpreter::addExternFunction("my_image_create_2", MakeExternFunction(&my_image_create_2));
});


// Настраивает экранную консоль для отображения результатов передачи
void ScriptTransfer::init()
{
	Console::setOnscreen(true);
	Console::setOnscreenFontSize(15);
	Console::setOnscreenTime(1000);
	Console::setOnscreenHeight(100);
}

// Восстанавливает настройки консоли по умолчанию
void ScriptTransfer::shutdown()
{
	Console::setOnscreen(false);
	Console::setOnscreenHeight(30);
}
