// Демонстрирует точки монтирования FileSystem для доступа к внешним папкам и пакетам.
// Точки монтирования предоставляют внешние директории или пакеты .zip/.ung как виртуальные пути,
// позволяя загружать ресурсы во время выполнения из мест вне папки данных проекта.

#include "MountPointsSample.h"
#include "UnigineConsole.h"
#include "UnigineGui.h"
#include "UnigineImage.h"
#include "UnigineMathLibVec4.h"
#include "UniginePtr.h"
#include "UnigineWidgets.h"
#include "UnigineFileSystem.h"

REGISTER_COMPONENT(MountPointsSample)

using namespace Unigine;
using namespace Math;

// Создаёт точку монтирования для внешней папки или пакета (.zip, .ung) с использованием указанного абсолютного пути
bool MountPointsSample::add_mount(const char *absolute_path_external, const char *mount_path)
{
	// Проверяет, существует ли внешняя папка или пакет.
	if (!Dir::isDir(absolute_path_external) && !FileSystem::isFileExist(String(absolute_path_external) + ".zip"))
	{
		Log::error("External folder/package doesn't exist\n");
		return false;
	}

	// Монтирует внешнюю папку или пакет в файловую систему.
	// Сохраняет файл .umount с именем, производным от mount_path, и указанным режимом доступа (чтение и запись).
	FileSystemMountPtr mount = FileSystem::createMount(absolute_path_external, mount_path, FileSystemMount::ACCESS_READWRITE);

	if (!mount)
		return false;

	return true;
}

// Размонтирует точку монтирования, связанную с указанным абсолютным путём к смонтированной папке или пакету.
bool MountPointsSample::remove_mount(const char *absolute_path_external)
{
	// Проверяет, смонтирована ли указанная папка или пакет в данный момент.
	if (!FileSystem::getMount(absolute_path_external))
		return false;

	FileSystem::removeMount(absolute_path_external);
	return true;
}

// Виртуальные пути настраиваются, UI инициализируется.
void MountPointsSample::init()
{
	virtual_path_umount = String::pathname(World::getPath()) + mounts_folder_name + "/";
	package_image_path = virtual_path_umount + package_name + "/" + image_name;
	folder_image_path = virtual_path_umount + folder_name + "/" + image_name;
	init_gui();

	update_images();
}

// Подключения событий очищаются, окно UI освобождается.
void MountPointsSample::shutdown()
{
	disconnectAll();
	window.shutdown();
}

// Создаётся UI примера с элементами управления монтированием и отображением статуса.
void MountPointsSample::init_gui()
{
	window.createWindow();

	auto parameters = window.getParameterGroupBox();

	WidgetHBoxPtr create_hbox = WidgetHBox::create();
	create_hbox->setSpace(10, 10);

	status_label = WidgetLabel::create("Status: ");
	status_label->setFontWrap(1);
	status_label->setWidth(300);

	create_hbox->addChild(status_label, Gui::ALIGN_LEFT);
	parameters->addChild(create_hbox, Gui::ALIGN_EXPAND);
	parameters->addChild(WidgetSpacer::create());

	// Виджет монтирования папки
	create_mount_widget(sprite_folder, folder_name, "Folder");
	parameters->addChild(WidgetSpacer::create());

	// Виджет монтирования пакета
	create_mount_widget(sprite_package, package_name, "Package");
	parameters->addChild(WidgetSpacer::create());

	image_folder = Image::create();
	image_package = Image::create();
	// sprite_folder->setImage(image_folder);
	// sprite_package->setImage(image_package);

	current_mounts = WidgetVBox::create();
	current_mounts->setSpace(0, 10);
	auto mounts_title = WidgetLabel::create("<b>Current mount points</b>");
	mounts_title->setFontRich(1);
	auto folder_label = WidgetLabel::create();
	folder_label->setFontWrap(1);
	auto package_label = WidgetLabel::create();
	package_label->setFontWrap(1);
	current_mounts->addChild(mounts_title, Gui::ALIGN_LEFT);
	current_mounts->addChild(folder_label, Gui::ALIGN_LEFT);
	current_mounts->addChild(package_label, Gui::ALIGN_LEFT);
	parameters->addChild(current_mounts, Gui::ALIGN_LEFT);

	show_sample_mounts();
}


// Кнопки монтирования/размонтирования и спрайт предпросмотра изображения создаются для одного внешнего ресурса.
void MountPointsSample::create_mount_widget(WidgetSpritePtr &sprite, const char *external_name, const char *type)
{
	// Определяются абсолютный исходный путь и целевой виртуальный путь монтирования
	String absolute_path_external = FileSystem::getAbsolutePath(String("../external_resources/") + external_name);
	String mount_path = virtual_path_umount + external_name;
	String image_path = mount_path + "/" + image_name;

	auto vbox = WidgetVBox::create();
	vbox->setSpace(0, 10);

	auto hbox_buttons = WidgetHBox::create();

	auto create_btn = WidgetButton::create(String::format("Create Mount %s", type));
	create_btn->getEventClicked().connect(*this, [this, mount_path, absolute_path_external]() {
		if (add_mount(absolute_path_external.get(), mount_path))
		{
			status_message("Mount Point Created", vec4_green);
			show_sample_mounts();
			update_images();
		} else
		{
			status_message(Console::getLastError(), vec4_red);
		}
	});

	auto remove_btn = WidgetButton::create(String::format("Unmount %s", type));
	remove_btn->getEventClicked().connect(*this, [this, absolute_path_external]() {
		if (remove_mount(absolute_path_external))
		{
			status_message("The Mount Point unmounted", vec4_green);
			show_sample_mounts();
			update_images();
		} else
		{
			status_message("The Mount Point is not mounted", vec4_red);
		}
	});

	hbox_buttons->addChild(create_btn);
	hbox_buttons->addChild(remove_btn);
	hbox_buttons->setSpace(10, 0);

	sprite = WidgetSprite::create();
	sprite->setWidth(100);
	sprite->setHeight(100);

	vbox->addChild(hbox_buttons, Gui::ALIGN_TOP);
	vbox->addChild(sprite, Gui::ALIGN_BACKGROUND);

	window.getParameterGroupBox()->addChild(vbox, Gui::ALIGN_RIGHT);
}

// Обновляются текст и цвет метки статуса.
void MountPointsSample::status_message(const char *msg, vec4 color)
{
	status_label->setFontColor(color);
	status_label->setText(String("Status: ") + msg);
}

// Информация о точке монтирования отображается в метке по указанному индексу.
void MountPointsSample::show_mount(const char *absolute_path, int index)
{
	auto mount = FileSystem::getMount(absolute_path);
	auto label = static_ptr_cast<WidgetLabel>(current_mounts->getChild(index));
	if (mount)
	{
		label->setText(mount->getUMountPath());
		label->setToolTip(
			String::format("<b>Virtual Mount Path:</b> %s<br><b>Absolute Path:</b> %s", mount->getVirtualPath(), mount->getDataPath())
				.get());
	} else
		label->setText("");
}

// Статусы монтирования папки и пакета обновляются в UI.
void MountPointsSample::show_sample_mounts()
{
	show_mount(FileSystem::getAbsolutePath(String("../external_resources/") + folder_name), 1);
	show_mount(FileSystem::getAbsolutePath(String("../external_resources/") + package_name), 2);
}

// Изображения предпросмотра загружаются из смонтированных путей, либо используются резервные текстуры.
void MountPointsSample::update_images()
{
	// Изображение папки загружается, если монтирование существует, иначе используется резервный вариант
	image_folder->clearData();
	if (!FileSystem::isFileExist(folder_image_path) ||
		!image_folder->load(folder_image_path))
	{
		image_folder->load("core/textures/common/red.texture");
	}
	sprite_folder->setImage(image_folder);

	// Изображение пакета загружается, если монтирование существует, иначе используется резервный вариант
	image_package->clearData();
	if (!FileSystem::isFileExist(package_image_path) ||
			!image_package->load(package_image_path))
	{
		image_package->load("core/textures/common/red.texture");
	}
	sprite_package->setImage(image_package);
}
