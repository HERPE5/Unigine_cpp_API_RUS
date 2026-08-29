#pragma once

#include <UnigineComponentSystem.h>
#include "../../menu_ui/SampleDescriptionWindow.h"
#include "UnigineCallback.h"
#include "UnigineFileSystem.h"
#include "UnigineWidgets.h"

// Демонстрирует API точек монтирования FileSystem для доступа к внешним ресурсам.
// Внешние папки и пакеты (.zip, .ung) можно монтировать в виртуальную
// файловую систему во время выполнения, делая их содержимое доступным через виртуальные пути.
// Точки монтирования сохраняются как файлы .umount и могут создаваться/удаляться динамически.
class MountPointsSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(MountPointsSample, Unigine::ComponentBase)
	COMPONENT_INIT(init)
	COMPONENT_SHUTDOWN(shutdown)

private:
	SampleDescriptionWindow window;                       // главное окно UI
	Unigine::WidgetVBoxPtr mount_points_labels = nullptr; // контейнер для меток состояния монтирования

	// имена ресурсов для демонстрации
	Unigine::String folder_name = "external_folder";
	Unigine::String package_name = "external_package";
	Unigine::String image_name = "image.jpg";
	Unigine::String mounts_folder_name = "mounts";

	// виртуальный путь к папке, содержащей файлы .umounts
	Unigine::String virtual_path_umount;

	// виртуальный путь к внешнему изображению, доступному через точки монтирования
	Unigine::String folder_image_path;
	Unigine::String package_image_path;

	Unigine::ImagePtr image_folder = nullptr;  // изображение предпросмотра из смонтированной папки
	Unigine::ImagePtr image_package = nullptr; // изображение предпросмотра из смонтированного пакета

	// элементы UI
	Unigine::WidgetLabelPtr status_label = nullptr;   // отображает сообщения о статусе операций
	Unigine::WidgetSpritePtr sprite_folder = nullptr;  // показывает предпросмотр монтирования папки
	Unigine::WidgetSpritePtr sprite_package = nullptr; // показывает предпросмотр монтирования пакета

	Unigine::WidgetVBoxPtr current_mounts; // контейнер для меток активных точек монтирования

	// управление монтированием внешних ресурсов
	bool add_mount(const char *absolute_path_external, const char *mount_path);
	bool remove_mount(const char *absolute_path_external);

	// вспомогательные методы UI
	void create_mount_widget(Unigine::WidgetSpritePtr &sprite, const char *external_name, const char *type);
	void status_message(const char *msg, Unigine::Math::vec4 color = Unigine::Math::vec4_white);
	void show_mount(const char *absolute_path, int index);

	void show_sample_mounts(); // обновляет отображение статуса монтирования
	void update_images();      // перезагружает изображения предпросмотра из монтирований
	void init_gui();           // создаёт элементы управления UI

	void init();     // настраивает пути и инициализирует UI
	void shutdown(); // освобождает UI и отключает события
};