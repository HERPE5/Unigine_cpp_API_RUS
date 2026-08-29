// Изменяет геометрию процедурного меша каждый кадр с анимированной волновой деформацией.
// Демонстрирует многопоточные обновления меша с использованием AsyncQueue для фоновой обработки.
// Поддерживает режимы применения Copy/Move и ручное управление MeshRender для управления VRAM.

#include "ProceduralMeshModifier.h"

#include <UnigineAsyncQueue.h>
#include <UnigineGame.h>
#include <UnigineProfiler.h>
#include <UnigineThread.h>

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(ProceduralMeshModifier);


void ProceduralMeshModifier::init()
{
	// UI примера с описанием и элементами управления
	init_gui();

	is_deleted = false;
	updated_meshvram_manual = is_meshvram_manual;

	isize = 30.f / size;

	// Подготавливаем объекты меша RAM/VRAM и объект сцены
	mesh_ram = Mesh::create();
	mesh_vram = MeshRender::create();
	object = ObjectMeshStatic::create();
	object->setMeshProceduralMode(current_mode);
	object->setWorldPosition(Vec3_one);
}

void ProceduralMeshModifier::update()
{
	UNIGINE_PROFILER_FUNCTION;

	// Пропускаем, если обновление/применение уже выполняется
	if (is_running || object->isMeshProceduralActive())
		return;

	is_running = true;
	is_meshvram_manual = updated_meshvram_manual;

	// Пересоздаём объект, если процедурный режим изменился
	if (object->getMeshProceduralMode() != current_mode)
	{
		object.deleteLater();
		object = ObjectMeshStatic::create();
		object->setMeshProceduralMode(current_mode);
		object->setWorldPosition(Vec3_one);
	}

	// Выбираем, где строить меш: в фоновом потоке (асинхронно) или в основном потоке
	if (is_thread_async)
	{
		// Строит меш в фоновом потоке, не блокируя основной поток.
		// Изменения меша обрабатываются в отдельном потоке столько времени, сколько нужно,
		// не влияя на производительность.
		AsyncQueue::runAsync(AsyncQueue::ASYNC_THREAD_BACKGROUND,
			MakeCallback(this, &ProceduralMeshModifier::async_update_ram));
	}
	else
	{
		// Строим и применяем в этом кадре в основном потоке
		update_ram();
		if (is_meshvram_manual)
			update_vram();
		apply_data();
	}
}

void ProceduralMeshModifier::shutdown()
{
	// Сигнализируем другим потокам, что shutdown() был вызван в основном потоке
	is_deleted = true;

	shutdown_gui();

	// Ждём завершения любой активной работы с мешем перед очисткой ресурсов
	mesh_lock.wait();

	mesh_ram.clear();
	mesh_vram.clear();
	object.deleteLater();
}

void ProceduralMeshModifier::update_mesh(MeshPtr mesh)
{
	UNIGINE_PROFILER_FUNCTION;

	float time = Game::getTime();

	// Гарантируем ровно одну поверхность и очищаем предыдущие данные
	if (mesh->getNumSurfaces() != 1)
	{
		mesh->clear();
		mesh->addSurface("");
	}
	else
	{
		mesh->clearSurface();
	}

	// Генерируем сетку вершин с анимированной волной
	auto &vertices = mesh->getVertices();
	vertices.reserve(size * size);

	for (int y = 0; y < size; y++)
	{
		float Y = y * isize - 15.0f;
		float Z = cos(Y + time);

		for (int x = 0; x < size; x++)
		{
			float X = x * isize - 15.0f;
			vertices.append(vec3(X, Y, Z * sin(X + time)));
		}
	}

	// Резервируем достаточно памяти для индексов, чтобы вектор не перевыделялся
	// каждый раз при исчерпании ёмкости
	auto &cindices = mesh->getCIndices();
	cindices.reserve((size - 1) * (size - 1) * 6);
	auto &tindices = mesh->getTIndices();
	tindices.reserve((size - 1) * (size - 1) * 6);

	// Добавляем одинаковые индексы в буферы координатных и треугольных индексов
	auto addIndex = [&cindices, &tindices](int index) {
		cindices.append(index);
		tindices.append(index);
	};

	// Строим треугольники для каждого квада в сетке
	for (int y = 0; y < size - 1; y++)
	{
		int offset = size * y;
		for (int x = 0; x < size - 1; x++)
		{
			addIndex(offset);
			addIndex(offset + 1);
			addIndex(offset + size);
			addIndex(offset + size);
			addIndex(offset + 1);
			addIndex(offset + size + 1);
			offset++;
		}
	}

	mesh->createTangents();

	{
		UNIGINE_PROFILER_SCOPED("CreateCollisionData");

		// Если вы планируете использовать пересечения или столкновения с этим мешем,
		// рекомендуется создать CollisionData. Иначе проверки пересечений
		// и столкновений будут крайне неэффективными.

		if (is_collision_enabled)
		{
			// Создаёт как Spatial Tree, так и Edges
			// для эффективных пересечений и столкновений соответственно
			mesh->createCollisionData();

			// При необходимости можно создать только одно:

			// mesh->createSpatialTree();		// только пересечения
			// mesh->createEdges();				// только столкновения
		}
		else
			// Можно также создать меш без CollisionData или удалить существующие данные,
			// если они не нужны.
			// Чтобы проверить, есть ли у меша CollisionData, используйте:
			//		mesh->hasCollisionData();
			//		mesh->hasSpatialTree();
			//		mesh->hasEdges();
			mesh->clearCollisionData();
	}

	// Обновляем границы после изменений геометрии
	mesh->createBounds();
}

void ProceduralMeshModifier::update_ram()
{
	UNIGINE_PROFILER_FUNCTION;

	// Выходим, если сторона основного потока завершает работу
	if (is_deleted.fetch())
		return;

	// Блокируем mesh_ram, чтобы другие потоки не мешали обновлению меша
	ScopedLock sl(mesh_lock);
	update_mesh(mesh_ram);
}

void ProceduralMeshModifier::update_vram()
{
	UNIGINE_PROFILER_FUNCTION;

	// Выходим, если сторона основного потока завершает работу
	if (is_deleted.fetch())
		return;

	// Загружаем меш RAM в меш VRAM
	ScopedLock sl(mesh_lock);
	mesh_vram->load(mesh_ram);
}

void ProceduralMeshModifier::async_update_ram()
{
	// Строим меш RAM
	update_ram();

	if (is_meshvram_manual)
	{
		// Загружаем MeshRender в потоке GPU Stream при ручном режиме
		AsyncQueue::runAsync(AsyncQueue::ASYNC_THREAD_GPU_STREAM,
			MakeCallback(this, &ProceduralMeshModifier::async_update_vram));
	}
	else
	{
		// Если не нужно загружать MeshRender вручную и автоматической загрузки внутри
		// методов apllyMeshProcedural достаточно, возвращаемся в основной поток
		AsyncQueue::runAsync(AsyncQueue::ASYNC_THREAD_MAIN, MakeCallback([this, check = node]() {
			// Проверяем, что логика примера в основном потоке всё ещё жива. Если нет, останавливаем
			// изменение и выходим
			if (!check || check.isDeleted())
				return;
			apply_data();
		}));
	}
}

void ProceduralMeshModifier::async_update_vram()
{
	// Обновляем MeshRender
	update_vram();

	// Возвращаемся в основной поток для применения нового меша
	AsyncQueue::runAsync(AsyncQueue::ASYNC_THREAD_MAIN, MakeCallback([this, check = node]() {
		// Проверяем, что логика примера в основном потоке всё ещё жива. Если нет, останавливаем
		// изменение и выходим
		if (!check || check.isDeleted())
			return;
		apply_data();
	}));
}

// Применять процедурный меш только в основном потоке!
void ProceduralMeshModifier::apply_data()
{
	UNIGINE_PROFILER_FUNCTION;

	// В асинхронном режиме применение обрабатывается в отдельном потоке без блокировки основного потока.
	if (is_async_mode)
	{
		if (is_meshvram_manual)
		{
			// Ручной MeshRender поддерживается только в режиме "Move"
			object->applyMoveMeshProceduralAsync(mesh_ram, mesh_vram);
		}
		else
		{
			if (is_copy_mode)
				// В режиме "Copy" данные из mesh_ram дублируются для внутреннего использования,
				// в то время как сам mesh_ram остаётся неизменным.
				object->applyCopyMeshProceduralAsync(mesh_ram, current_mesh_render_flag);
			else
				// В режиме "Move" данные берутся из mesh_ram для внутреннего использования,
				// что изменяет mesh_ram в процессе.
				object->applyMoveMeshProceduralAsync(mesh_ram, current_mesh_render_flag);
		}
	}
	// В принудительном режиме основной поток остаётся заблокированным до завершения применения.
	else
	{
		if (is_meshvram_manual)
		{
			object->applyMoveMeshProceduralForce(mesh_ram, mesh_vram);
		}
		else
		{
			if (is_copy_mode)
				object->applyCopyMeshProceduralForce(mesh_ram, current_mesh_render_flag);
			else
				object->applyMoveMeshProceduralForce(mesh_ram, current_mesh_render_flag);
		}
	}

	// Полный цикл изменения меша завершён
	is_running = false;
}

void ProceduralMeshModifier::init_gui()
{
	// UI примера с описанием и элементами управления
	sample_description_window.createWindow(Gui::ALIGN_RIGHT);
	auto params = sample_description_window.getParameterGroupBox();

	auto gridbox = WidgetGridBox::create(2, 10);
	params->addChild(gridbox, Gui::ALIGN_EXPAND);

	//	--------Селектор потока--------
	auto label = WidgetLabel::create("Thread");
	gridbox->addChild(label, Gui::ALIGN_LEFT);

	thread_combo = WidgetComboBox::create();
	thread_combo->addItem("Main");
	thread_combo->addItem("Background");
	gridbox->addChild(thread_combo, Gui::ALIGN_EXPAND);

	thread_combo->setCurrentItem(1);
	thread_combo->getEventChanged().connect(*this, [this]() {
		int item = thread_combo->getCurrentItem();
		is_thread_async = item != 0;
	});

	//	--------Селектор процедурного режима--------
	modes_map["Dynamic"] = ObjectMeshStatic::PROCEDURAL_MODE_DYNAMIC;
	modes_map["File"] = ObjectMeshStatic::PROCEDURAL_MODE_FILE;
	modes_map["Blob"] = ObjectMeshStatic::PROCEDURAL_MODE_BLOB;

	label = WidgetLabel::create("Procedural Mode");
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

	//	--------Селектор флага MeshRender--------
	usage_map["None"] = 0;
	usage_map["DYNAMIC_VERTEX"] = MeshRender::USAGE_DYNAMIC_VERTEX;
	usage_map["DYNAMIC_INDICES"] = MeshRender::USAGE_DYNAMIC_INDICES;
	usage_map["DYNAMIC_ALL"] = MeshRender::USAGE_DYNAMIC_ALL;

	label = WidgetLabel::create("MeshRender Flag");
	gridbox->addChild(label, Gui::ALIGN_LEFT);

	usage_combo = WidgetComboBox::create();
	usage_combo->addItem("None");
	usage_combo->addItem("DYNAMIC_VERTEX");
	usage_combo->addItem("DYNAMIC_INDICES");
	usage_combo->addItem("DYNAMIC_ALL");
	gridbox->addChild(usage_combo, Gui::ALIGN_EXPAND);

	current_mesh_render_flag = 0;
	usage_combo->setCurrentItem(0);
	usage_combo->getEventChanged().connect(*this, [this]() {
		auto item = usage_combo->getCurrentItemText();
		current_mesh_render_flag = usage_map[item];
	});

	//	--------Селектор режима Async/Force--------
	label = WidgetLabel::create("Async Mode");
	gridbox->addChild(label, Gui::ALIGN_LEFT);

	async_combo = WidgetComboBox::create();
	async_combo->addItem("Async");
	async_combo->addItem("Force");
	gridbox->addChild(async_combo, Gui::ALIGN_EXPAND);

	async_combo->setCurrentItem(0);
	async_combo->getEventChanged().connect(*this, [this]() {
		int item = async_combo->getCurrentItem();
		is_async_mode = item == 0;
	});

	//	--------Селектор режима применения--------
	label = WidgetLabel::create("Apply mode");
	gridbox->addChild(label, Gui::ALIGN_LEFT);

	move_combo = WidgetComboBox::create();
	move_combo->addItem("Copy");
	move_combo->addItem("Move");
	gridbox->addChild(move_combo, Gui::ALIGN_EXPAND);

	is_copy_mode = true;
	move_combo->setCurrentItem(0);
	move_combo->getEventChanged().connect(*this, [this]() {
		auto item = move_combo->getCurrentItem();
		is_copy_mode = item == 0;
	});

	//	--------Создать Collision Data--------
	label = WidgetLabel::create("Create CollisionData");
	gridbox->addChild(label, Gui::ALIGN_LEFT);

	auto collison_checkbox = WidgetCheckBox::create();
	gridbox->addChild(collison_checkbox, Gui::ALIGN_EXPAND);
	collison_checkbox->getEventChanged().connect(*this,
		[this, collison_checkbox]() { is_collision_enabled = collison_checkbox->isChecked(); });

	//	--------Создать MeshRender вручную--------
	label = WidgetLabel::create("Manual MeshRender");
	gridbox->addChild(label, Gui::ALIGN_LEFT);

	meshvram_checkbox = WidgetCheckBox::create();
	gridbox->addChild(meshvram_checkbox, Gui::ALIGN_EXPAND);
	meshvram_checkbox->getEventChanged().connect(*this, [this]() {
		updated_meshvram_manual = meshvram_checkbox->isChecked();
		warning_label->setHidden(!updated_meshvram_manual);
	});

	//	--------Предупреждение о создании MeshRender--------
	warning_label = WidgetLabel::create("MeshRender can be used only with mode \"Move\". Apply mode "
										"\"Copy\" will be ignored ");
	warning_label->setFontWrap(1);
	warning_label->setHidden(true);
	warning_label->setFontColor(vec4_red);

	params->setFontWrap(1);
	params->addChild(warning_label, Gui::ALIGN_EXPAND);
}

void ProceduralMeshModifier::shutdown_gui()
{
	sample_description_window.shutdown();
}
