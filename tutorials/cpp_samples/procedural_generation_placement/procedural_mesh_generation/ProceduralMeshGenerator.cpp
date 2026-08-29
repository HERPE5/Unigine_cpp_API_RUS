// Генерирует сетки процедурных объектов мешей с использованием асинхронных callback-функций. Сравнивает три
// процедурных режима: Dynamic (постоянная память), File (на основе диска) и Blob (кэшируется в RAM).
// Статистика памяти показывает различия в использовании RAM/VRAM между режимами во время выполнения.

#include "ProceduralMeshGenerator.h"

#include <UnigineConsole.h>

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(ProceduralMeshGenerator);

// Константа для преобразования байтов в МБ
constexpr float B2MB = 1.f / (1024 * 1024);

void ProceduralMeshGenerator::init()
{
	// Вычисляем количество объектов для текущего размера сетки
	num_objects = size * size;
	new_size = size;

	// UI примера с описанием и элементами управления
	init_gui();
}

void ProceduralMeshGenerator::update()
{
	// Проверяем, завершилась ли генерация всех объектов
	if (is_creating_objects && num_created_objects == num_objects)
	{
		set_gui_enabled(true);
		is_creating_objects = false;
	}

	// Проверяем, завершилось ли удаление всех объектов
	if (is_deleting_done)
	{
		is_deleting_done = false;
		if (is_creating_objects)
			create_objects();
		else
			set_gui_enabled(true);
	}

	// Применяем новый размер поля, когда генерация не выполняется
	if (!is_creating_objects && new_size != size)
	{
		size = new_size;
		num_objects = size * size;
	}

	// Обновляем статистику использования памяти
	update_stats();
}

void ProceduralMeshGenerator::shutdown()
{
	clear_objects();
	shutdown_gui();
}

void ProceduralMeshGenerator::create_objects()
{
	is_creating_objects = true;

	// Если объекты уже существуют, сначала очищаем их; создание возобновится после завершения удаления
	if (box_objects.size() > 0)
	{
		clear_objects();
		return;
	}

	// Заранее размещаем объекты в сетке с расстоянием
	float field_offset = (1.f + offset) * size / 2.f;
	box_objects.reserve(num_objects);

	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			auto obj = ObjectMeshStatic::create();
			obj->setWorldPosition(
				Vec3(x + x * offset - field_offset, y + y * offset - field_offset, 1.5));

			obj->setMeshProceduralMode(current_mode);

			// Этот вызов:
			// 1) Строит меш через callback create_mesh,
			// 2) Создаёт/загружает MeshRender на основе current_mesh_render_flag,
			// 3) Применяет меш к объекту,
			// 4) Вызывает create_done по завершении.
			obj->runGenerateMeshProceduralAsync(
				MakeCallback(this, &ProceduralMeshGenerator::create_mesh),
				MakeCallback(this, &ProceduralMeshGenerator::create_done, obj), current_mesh_render_flag);

			box_objects.append(obj);
		}
	}
}

void ProceduralMeshGenerator::create_mesh(MeshPtr mesh)
{
	// Создаём простую поверхность коробки
	mesh->addBoxSurface("box", vec3(1));

	// Динамические процедурные меши постоянно хранятся в памяти,
	// поэтому мы можем вычислить их использование памяти сразу после создания
	if (current_mode != ObjectMeshStatic::PROCEDURAL_MODE_DYNAMIC)
		return;
	dynamic_ram += mesh->getMemoryUsage();
}

void ProceduralMeshGenerator::create_done(ObjectMeshStaticPtr obj)
{
	// Проверяем, что объект всё ещё действителен, так как этот callback
	// может быть вызван после того, как мир уже выгружен.
	if (!obj)
		return;

	num_created_objects++;

	// Динамические процедурные меши постоянно хранятся в памяти,
	// поэтому мы можем вычислить их использование памяти сразу после создания.
	// Процедурные меши File и Blob не занимают VRAM, пока не активны.
	if (current_mode != ObjectMeshStatic::PROCEDURAL_MODE_DYNAMIC)
		return;

	MeshRenderPtr m_vram = obj->getMeshCurrentVRAM();
	if (m_vram)
	{
		dynamic_ram += m_vram->getSystemMemoryUsage();
		dynamic_vram += m_vram->getVideoMemoryUsage();
	}
}

void ProceduralMeshGenerator::clear_objects()
{
	// Сбрасываем счётчики и статистику памяти
	num_created_objects = 0;
	dynamic_ram = 0;
	dynamic_vram = 0;

	// Удаляем все сгенерированные объекты
	for (auto &obj : box_objects)
	{
		obj.deleteLater();
	}
	box_objects.clear();
	is_deleting_done = true;
}

void ProceduralMeshGenerator::update_stats()
{
	int ram = 0, active_vram = 0;
	auto &stat = Render::getStreamingStatistics();

	switch (last_mode)
	{
	// Для режима Dynamic использование памяти накапливается при создании и остаётся постоянным
	case Unigine::ObjectMeshStatic::PROCEDURAL_MODE_DYNAMIC:
		ram = int(dynamic_ram * B2MB);
		active_vram = int(dynamic_vram * B2MB);
		break;

	// Режимы File и Blob используют память только когда объекты активны; иначе они кэшируются
	case Unigine::ObjectMeshStatic::PROCEDURAL_MODE_BLOB:
	case Unigine::ObjectMeshStatic::PROCEDURAL_MODE_FILE:
		ram = int(stat.static_meshes.ram.active * B2MB);
		active_vram = int(stat.static_meshes.vram.active * B2MB);
		break;

	default:
		break;
	}

	String status = String::format(
		"Num ready objects: %d\nRAM: %d MB\nVRAM Active: %d MB",
		num_created_objects.fetch(), ram, active_vram);

	sample_description_window.setStatus(status);
}

void ProceduralMeshGenerator::init_gui()
{
	// UI примера с описанием и элементами управления
	sample_description_window.createWindow(Gui::ALIGN_RIGHT);
	auto params = sample_description_window.getParameterGroupBox();

	auto gridbox = WidgetGridBox::create(2, 10);
	params->addChild(gridbox);

	//	--------Селектор процедурного режима--------
	modes_map["Dynamic"] = ObjectMeshStatic::PROCEDURAL_MODE_DYNAMIC;
	modes_map["File"] = ObjectMeshStatic::PROCEDURAL_MODE_FILE;
	modes_map["Blob"] = ObjectMeshStatic::PROCEDURAL_MODE_BLOB;

	auto label = WidgetLabel::create("Procedural Mode");
	gridbox->addChild(label, Gui::ALIGN_LEFT);

	mode_combo = WidgetComboBox::create();
	mode_combo->addItem("Dynamic");
	mode_combo->addItem("File");
	mode_combo->addItem("Blob");
	gridbox->addChild(mode_combo, Gui::ALIGN_EXPAND);

	current_mode = ObjectMeshStatic::PROCEDURAL_MODE_DYNAMIC;
	mode_combo->setCurrentItem(0);
	mode_combo->getEventChanged().connect(*this, [this]() {
		auto item = mode_combo->getCurrentItemText();
		current_mode = modes_map[item];
	});

	//	--------Селектор динамического использования MeshRender--------
	flags_map["None"] = 0;
	flags_map["DYNAMIC_VERTEX"] = MeshRender::USAGE_DYNAMIC_VERTEX;
	flags_map["DYNAMIC_INDICES"] = MeshRender::USAGE_DYNAMIC_INDICES;
	flags_map["DYNAMIC_ALL"] = MeshRender::USAGE_DYNAMIC_ALL;

	label = WidgetLabel::create("MeshRender Flag");
	gridbox->addChild(label, Gui::ALIGN_LEFT);

	flags_combo = WidgetComboBox::create();
	flags_combo->addItem("None");
	flags_combo->addItem("DYNAMIC_VERTEX");
	flags_combo->addItem("DYNAMIC_INDICES");
	flags_combo->addItem("DYNAMIC_ALL");
	gridbox->addChild(flags_combo, Gui::ALIGN_EXPAND);

	current_mesh_render_flag = 0;
	flags_combo->setCurrentItem(0);
	flags_combo->getEventChanged().connect(*this, [this]() {
		auto item = flags_combo->getCurrentItemText();
		current_mesh_render_flag = flags_map[item];
	});

	//	--------Ввод размера поля--------
	label = WidgetLabel::create("Field Size");
	gridbox->addChild(label, Gui::ALIGN_LEFT);

	auto spinbox_hbox = WidgetHBox::create();
	gridbox->addChild(spinbox_hbox, Gui::ALIGN_EXPAND);

	spinbox = WidgetSpinBox::create(1, 1000);
	spinbox->setValue(size);
	spinbox->getEventChanged().connect(*this, [this]() { new_size = spinbox->getValue(); });

	editline = WidgetEditLine::create();
	editline->setValidator(Gui::VALIDATOR_UINT);
	editline->getEventFocusOut().connect(*this, [this]() {
		int text = atoi(editline->getText());
		new_size = clamp(text, spinbox->getMinValue(), spinbox->getMaxValue());
		if (text != new_size)
			editline->setText(String::itoa(new_size));
	});
	editline->setText(String::itoa(size));
	editline->addAttach(spinbox);

	spinbox_hbox->addChild(editline);
	spinbox_hbox->addChild(spinbox, Gui::ALIGN_EXPAND);

	//	--------Разделитель--------
	auto spacer = WidgetSpacer::create();
	spacer->setOrientation(1);
	params->addChild(spacer, Gui::ALIGN_EXPAND);

	//	--------Кнопки создания--------
	auto hbox = WidgetHBox::create(10);
	params->addChild(hbox, Gui::ALIGN_EXPAND);
	generate_button = WidgetButton::create("Generate");
	generate_button->getEventClicked().connect(this, &ProceduralMeshGenerator::on_generate_button);
	hbox->addChild(generate_button, Gui::ALIGN_EXPAND);
	clear_button = WidgetButton::create("Clear");
	clear_button->getEventClicked().connect(this, &ProceduralMeshGenerator::on_clear_button);
	hbox->addChild(clear_button, Gui::ALIGN_EXPAND);
}

void ProceduralMeshGenerator::shutdown_gui()
{
	sample_description_window.shutdown();
	modes_map.clear();
	flags_map.clear();
}

void ProceduralMeshGenerator::set_gui_enabled(bool enabled)
{
	generate_button->setEnabled(enabled);
	clear_button->setEnabled(enabled);
}

void ProceduralMeshGenerator::on_generate_button()
{
	set_gui_enabled(false);

	last_mode = current_mode;

	create_objects();
}

void ProceduralMeshGenerator::on_clear_button()
{
	set_gui_enabled(false);
	clear_objects();
}
