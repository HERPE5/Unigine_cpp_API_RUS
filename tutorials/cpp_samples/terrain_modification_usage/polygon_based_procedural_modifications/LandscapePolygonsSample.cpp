// Демонстрирует изменение terrain на основе полигонов и генерацию мешей.
// Поддерживает создание мешей, размещение декалей, рисование масок и редактирование высоты.
// Фигуры определяются позициями дочерних узлов и триангулируются для операций.

#include "LandscapePolygonsSample.h"
#include <UnigineVisualizer.h>
#include <UnigineGame.h>
#include <UnigineDecals.h>
#include <UnigineConsole.h>
#include "../../utils/Utils.h"

REGISTER_COMPONENT(LandscapePolygonsSample);

using namespace Unigine;
using namespace Math;

// Параметры компонента проверяются, исходные позиции сохраняются.
void LandscapePolygonsSample::init()
{
	// Проверяется назначение узла редактора layer map
	if (!layer_map_editor_node.get())
	{
		Log::warning("LandscapePolygonsSample::init 'Layer Map Editor' node is not assigned.\n");
		return;
	}

	// Узлы фигур проверяются, захватываются исходные позиции
	for (int i = 0; i < figures.size(); i++)
	{
		if (!figures[i].get())
		{
			Log::warning("LandscapePolygonsSample::init invalid figures array value.\n");
			return;
		} else
		{
			// Позиция фигуры сохраняется для последующего сброса
			figures_initial_positions.append(figures[i]->getWorldPosition());
			int child_number = figures[i]->getNumChildren();
			points_initial_positions.append();

			// Позиции дочерних точек сохраняются для последующего сброса
			for (int j = 0; j < child_number; j++)
			{
				points_initial_positions.last().append(figures[i]->getChild(j)->getWorldPosition());
			}
		}
	}

	// Компонент манипулятора получается из узла
	manipulators = ComponentSystem::get()->getComponent<Manipulators>(manipulators_node.get());
	if (!manipulators)
	{
		Log::warning("LandscapePolygonsSample::init can't find manipulators component on 'Manipulators' node.\n");
		return;
	}

	// Оси поворота и масштаба отключаются для манипуляции только переносом
	manipulators->setAxesRotation(false);
	manipulators->setAxesScale(false);

	// Узел clutter приводится к типу для инвалидации растительности
	clutter = checked_ptr_cast<ObjectMeshClutter>(clutter_node.get());
	if (!clutter_node.get())
	{
		Log::warning("LayerMapEditor::init clutter node in unspecified \n");
		return;
	}

	// Layer map приводится к типу из ссылки на узел
	layer_map = checked_ptr_cast<LandscapeLayerMap>(layer_map_node.get());

	if (!layer_map)
	{
		Log::warning("LandscapePolygonsSample::init layer map is unspecified \n");
		return;
	}

	// Редактор полигонов создаётся с layer map и материалом рендеринга
	layer_map_editor = new LayerMapPolygonEditor(layer_map, mesh_material.get());
	layer_map_editor->setClutter(clutter);

	// Ortho-материал проверяется для генерации декалей
	if (!ortho_material.get())
	{
		Log::warning("LandscapePolygonsSample::init ortho_material is unspecified \n");
		return;
	}

	// Инициализируются элементы управления GUI
	init_gui();

	// Визуализатор включается для отладочного рендеринга триангуляции
	Visualizer::setEnabled(true);
}

// Визуализация триангуляции рендерится каждый кадр.
void LandscapePolygonsSample::update()
{
	// Линии триангуляции рисуются для всех полигональных фигур
	draw_triangulation_all_figures();
}

// Изменения landscape отменяются, ресурсы очищаются.
void LandscapePolygonsSample::shutdown()
{
	// Все изменения и созданные узлы сбрасываются
	reset();

	// UI окна описания уничтожается
	description_window.shutdown();

	// Визуализация маски landscape отключается
	Render::setShowLandscapeMask(0);
}

// Триангуляция полигонов вычисляется и визуализируется для всех узлов фигур.
void LandscapePolygonsSample::draw_triangulation_all_figures()
{
	// Каждая фигура обрабатывается независимо
	for (int i = 0; i < figures.size(); i++)
	{
		auto figure = figures[i];

		// Массивы точек выделяются на основе количества дочерних узлов
		Vector<Vec3> points(figure->getNumChildren());
		Vector<vec2> mesh_points(figure->getNumChildren());
		Vector<unsigned short> indices = Vector<unsigned short>();
		double avgZ = 0.0;

		// Позиции дочерних узлов извлекаются как вершины полигона
		for (int j = 0; j < figure->getNumChildren(); j++)
		{
			points[j] = figure->getChild(j)->getWorldPosition();
			mesh_points[j] = vec2(points[j].x, points[j].y);
			avgZ += points[j].z;
		}
		avgZ /= figure->getNumChildren();

		// Полигон триангулируется с помощью 2D-проекции
		triangulatePolygon(mesh_points, indices);

		// Рёбра треугольников рендерятся через визуализатор
		draw_triangulation(points, indices);
	}
}

// Создаётся окно панели управления с опциями манипуляции и генерации.
void LandscapePolygonsSample::init_gui()
{
	// Создаётся основное окно примера
	description_window.createWindow();
	auto params = description_window.getParameterGroupBox();

	// Создаётся строка выбора режима манипулятора
	auto figureHBox = WidgetHBox::create();
	params->addChild(figureHBox, Gui::ALIGN_LEFT);

	auto selectedFigureLabel = WidgetLabel::create("Manipulator transform mode:   ");
	figureHBox->addChild(selectedFigureLabel, Gui::ALIGN_LEFT);

	// Создаётся выпадающий список для режима трансформации фигуры или точки
	WidgetComboBoxPtr manipulatorComboBox = WidgetComboBox::create();
	figureHBox->addChild(manipulatorComboBox);

	manipulatorComboBox->addItem("Figure");
	manipulatorComboBox->addItem("Point");

	// Подключается callback изменения режима
	manipulatorComboBox->getEventChanged().connect(*this, [this, manipulatorComboBox]()
		{
			int item = manipulatorComboBox->getCurrentItem();
			switch (item)
			{
				case 0://Фигура
				{
					// Включается режим трансформации родителя
					manipulators->transform_parent = true;
					manipulators->updateManipulatorTransform();
					break;
				}
				case 1://Точка
				{
					// Включается режим трансформации отдельной точки
					manipulators->transform_parent = false;
					manipulators->updateManipulatorTransform();
					break;
				}
				default:
					break;
			}
		});

	// По умолчанию выбран режим Figure
	manipulatorComboBox->setCurrentItem(0);

	// Создаётся строка переключения видимости маски
	auto renderMaskHBox = WidgetHBox::create();
	params->addChild(renderMaskHBox, Gui::ALIGN_LEFT);

	auto showClutterMaskLabel = WidgetLabel::create("Show layer map's clutter mask:   ");
	renderMaskHBox->addChild(showClutterMaskLabel, Gui::ALIGN_LEFT);

	// Создаётся чекбокс для визуализации маски landscape
	WidgetCheckBoxPtr renderMaskCheckBox = WidgetCheckBox::create();
	renderMaskHBox->addChild(renderMaskCheckBox);

	// Подключается callback переключения маски
	renderMaskCheckBox->getEventChanged().connect(*this, [this, renderMaskCheckBox]()
		{
			if (renderMaskCheckBox->isChecked())
			{
				// Созданные узлы скрываются для визуализации маски
				for (auto& node : created_nodes)
				{
					node->setEnabled(false);
				}
				Render::setShowLandscapeMask(1);

			} else
			{
				// Созданные узлы отображаются снова
				for (auto& node : created_nodes)
				{
					node->setEnabled(true);
				}
				Render::setShowLandscapeMask(0);
			}
		});

	// Создаётся раздел кнопок функций
	auto featuresLabel = WidgetLabel::create("Generation features:");
	params->addChild(featuresLabel, Gui::ALIGN_LEFT);
	auto window = description_window.getWindow();

	// Создаётся сетка кнопок из 3 столбцов
	auto buttons_grid_box = WidgetGridBox::create(3, 2, 2);
	params->addChild(buttons_grid_box);

	// Добавляется кнопка генерации ObjectMeshStatic
	auto button = WidgetButton::create("ObjectMeshStatic");
	button->getEventClicked().connect(this, &LandscapePolygonsSample::generate_mesh_button);
	buttons_grid_box->addChild(button, Gui::ALIGN_EXPAND);

	// Добавляется кнопка генерации DecalMesh
	button = WidgetButton::create("DecalMesh");
	button->getEventClicked().connect(this, &LandscapePolygonsSample::generate_decal_mesh_button);
	buttons_grid_box->addChild(button, Gui::ALIGN_EXPAND);

	// Добавляется кнопка генерации DecalOrtho
	button = WidgetButton::create("DecalOrtho");
	button->getEventClicked().connect(this, &LandscapePolygonsSample::generate_decal_ortho_button);
	buttons_grid_box->addChild(button, Gui::ALIGN_EXPAND);

	// Добавляется кнопка рисования маски terrain
	button = WidgetButton::create("Terrain mask");
	button->getEventClicked().connect(this, &LandscapePolygonsSample::draw_terrain_mask_button);
	buttons_grid_box->addChild(button, Gui::ALIGN_EXPAND);

	// Добавляется кнопка выравнивания terrain
	button = WidgetButton::create("Level terrain");
	button->getEventClicked().connect(this, &LandscapePolygonsSample::level_terrain_button);
	buttons_grid_box->addChild(button, Gui::ALIGN_EXPAND);

	// Добавляется кнопка понижения terrain
	button = WidgetButton::create("Lower terrain");
	button->getEventClicked().connect(this, &LandscapePolygonsSample::lower_terrain_button);
	buttons_grid_box->addChild(button, Gui::ALIGN_EXPAND);

	// Кнопка Reset добавляется внизу
	button = WidgetButton::create("Reset");
	button->getEventClicked().connect(this, &LandscapePolygonsSample::reset);
	params->addChild(button, Gui::ALIGN_BOTTOM);
}



// Изменения landscape отменяются, созданные узлы удаляются.
void LandscapePolygonsSample::reset()
{
	// Запускается асинхронный сброс изменений landscape
	Landscape::asyncResetModifications(layer_map->getGUID());

	// Созданные узлы планируются к удалению
	for (auto& n : created_nodes)
	{
		n.deleteLater();
	}
	created_nodes.clear();

	// Растительность clutter инвалидируется для обновления
	clutter->invalidate();

	// Позиции фигур и точек восстанавливаются
	revert_points_positions();
}

// Меш рендерится в текстуру с помощью ортографической проекции для генерации декалей.
void LandscapePolygonsSample::render_mesh_to_texture(Unigine::MeshPtr mesh, Unigine::TexturePtr texture, Unigine::MaterialPtr render_material, Unigine::Math::vec4 color)
{
	// Входные параметры проверяются
	if (!texture)
	{
		Log::error("MeshToMaskTextureSample::renderMesh: texture in nullptr \n");
		return;
	}
	if (!mesh)
	{
		Log::error("MeshToMaskTextureSample::renderMesh: mesh in nullptr \n");
		return;
	}
	if (!render_material)
	{
		Log::error("MeshToMaskTextureSample::renderMesh: material is nullptr\n");
		return;
	}

	// Создаётся и загружается объект рендеринга меша
	MeshRenderPtr meshRender = MeshRender::create();
	meshRender->load(mesh);

	// Ортографическая проекция вычисляется из границ меша
	Mat4 mesh_transform = Mat4_identity;
	double half_width = mesh->getBoundBox().getSize().x * 0.5f;
	double half_height = mesh->getBoundBox().getSize().y * 0.5f;
	mat4 projection = Math::ortho(
		-half_width, half_width,
		-half_height, half_height,
		0.01, 1000
	);

	// Вычисляется трансформация камеры вида сверху
	Mat4 camera_transform = Math::setTo(mesh_transform.getTranslate() + Vec3_up * 10, mesh_transform.getTranslate(), vec3_forward, Math::AXIS_NZ);

	// Получается временный рендер-таргет
	auto renderTarget = Render::getTemporaryRenderTarget();

	// Состояние рендеринга сохраняется и очищается
	RenderState::saveState();
	RenderState::clearStates();
	RenderState::setBlendFunc(RenderState::BLEND_NONE, RenderState::BLEND_NONE);
	RenderState::clearBuffer(RenderState::BUFFER_COLOR, vec4_black);

	// Текстура привязывается как цветовой вывод
	renderTarget->bindColorTexture(0, texture);
	renderTarget->enable();

	// Настраиваются матрицы камеры
	Renderer::setModelview(inverse((Mat4)camera_transform));
	Renderer::setOldModelview(inverse((Mat4)camera_transform));
	Renderer::setProjection(projection);
	Renderer::setOldProjection(projection);

	// Вычисляются матрицы трансформации для шейдера
	vec4 transforms[3];
	Mat4 local_transform = Mat4(mesh_transform);
	Mat4* transform_array = &local_transform;
	Simd::mulMat4Mat4(transforms, inverse(camera_transform), (const Mat4**)&transform_array, 1);

	// Настраиваются параметры шейдера
	ShaderPtr shader = render_material->getShaderForce("render_mesh");
	shader->setParameterArrayFloat4("s_transform", transforms, 3);
	render_material->setParameterFloat4("mesh_color", color);

	// Выполняется проход рендеринга
	auto pass = render_material->getRenderPass("render_mesh");
	Renderer::setMaterial(pass, render_material);
	Renderer::setShaderParameters(pass, render_material, 0);

	// Меш рендерится как треугольники
	meshRender->render(MeshRender::MODE_TRIANGLES);

	// Рендер-таргет отключается и отвязывается
	renderTarget->disable();
	renderTarget->unbindAll();

	// Состояние рендеринга восстанавливается, таргет освобождается
	RenderState::restoreState();
	Render::releaseTemporaryRenderTarget(renderTarget);
}

// Объекты ObjectMeshStatic создаются из полигональных фигур.
void LandscapePolygonsSample::generate_mesh_button()
{
	// Каждая фигура преобразуется в объект меша
	for (int i = 0; i < figures.size(); i++)
	{
		auto figure = figures[i];
		Vector<Vec3> points;

		// Позиции дочерних узлов собираются как вершины
		for (int j = 0; j < figure->getNumChildren(); j++)
		{
			points.append(figure->getChild(j)->getWorldPosition());
		}

		// Ограничивающий бокс вычисляется из позиций вершин
		WorldBoundBox bb = WorldBoundBox(points.get(), points.size());

		// Триангулированный меш генерируется из вершин полигона
		auto mesh = GeometryGenerator::CreatePolygonMesh(points);
		if (!mesh)
			continue;

		// Объект меша создаётся с динамическим процедурным режимом
		auto meshObj = ObjectMeshStatic::create();
		meshObj->setMeshProceduralMode(ObjectMeshStatic::PROCEDURAL_MODE_DYNAMIC, 0);
		meshObj->applyMoveMeshProceduralForce(mesh, 0);
		meshObj->setWorldPosition(bb.getCenter());

		// Пересечение включается для трассировки лучей
		meshObj->setIntersection(true, 0);
		meshObj->setIntersectionMask(1 << 0, 0);
		meshObj->setImmovable(false);

		// Созданный узел отслеживается для очистки
		created_nodes.append(meshObj);
	}
}

// Объекты DecalMesh создаются из полигональных фигур.
void LandscapePolygonsSample::generate_decal_mesh_button()
{
	// Каждая фигура преобразуется в декаль меша
	for (int i = 0; i < figures.size(); i++)
	{
		auto figure = figures[i];
		Vector<Vec3> points;

		// Позиции дочерних узлов собираются как вершины
		for (int j = 0; j < figure->getNumChildren(); j++)
		{
			points.append(figure->getChild(j)->getWorldPosition());
		}

		// Ограничивающий бокс вычисляется из позиций вершин
		WorldBoundBox bb = WorldBoundBox(points.get(), points.size());

		// Триангулированный меш генерируется из вершин полигона
		auto mesh = GeometryGenerator::CreatePolygonMesh(points);
		if (!mesh)
			continue;

		// Декаль меша создаётся с динамическим процедурным режимом
		auto decal = Unigine::DecalMesh::create();
		decal->setMeshProceduralMode(ObjectMeshStatic::PROCEDURAL_MODE_DYNAMIC, 0);
		decal->applyMoveMeshProceduralForce(mesh, 0);

		// Декаль позиционируется над центром полигона
		decal->setWorldPosition(Vec3(bb.getCenter().x, bb.getCenter().y, bb.getCenter().z + 10));
		decal->setRadius(200);

		// Назначается базовый материал декали
		auto mat = Materials::findManualMaterial("Unigine::decal_base");
		decal->setMaterial(mat);
		decal->setViewportMask(~0);
		decal->setSaveToWorldEnabled(true);

		// Созданный узел отслеживается для очистки
		created_nodes.append(decal);
	}
}

// Объекты DecalOrtho создаются с отрендеренными текстурами полигонов.
void LandscapePolygonsSample::generate_decal_ortho_button()
{
	// Каждая фигура преобразуется в ортогональную декаль с отрендеренной текстурой
	for (int i = 0; i < figures.size(); i++)
	{
		auto figure = figures[i];
		Vector<Vec3> points;

		// Позиции дочерних узлов собираются как вершины
		for (int j = 0; j < figure->getNumChildren(); j++)
		{
			points.append(figure->getChild(j)->getWorldPosition());
		}

		// Ограничивающий бокс вычисляется из позиций вершин
		WorldBoundBox bb = WorldBoundBox(points.get(), points.size());

		// Триангулированный меш генерируется из вершин полигона
		auto mesh = GeometryGenerator::CreatePolygonMesh(points);
		if (!mesh)
			continue;

		// Текстура рендеринга создаётся для albedo декали
		auto tex = Texture::create();
		tex->create2D(512, 512, Texture::FORMAT_RGBA8, Texture::FORMAT_USAGE_UNORDERED_ACCESS | Texture::FORMAT_USAGE_RENDER);
		tex->clearBuffer(vec4_zero);

		// Меш рендерится в текстуру с помощью ортографической проекции
		render_mesh_to_texture(mesh, tex, mesh_material);
		ortho_decal_textures.append(tex);

		// Создаётся экземпляр материала с отрендеренной текстурой
		auto mat = ortho_material->inherit();
		mat->setTexture("albedo", tex);

		// Ортогональная декаль создаётся и позиционируется над полигоном
		auto decal = Unigine::DecalOrtho::create();
		decal->setWorldPosition(Vec3(bb.getCenter().x, bb.getCenter().y, bb.maximum.z + 10));
		decal->setRadius(200);
		decal->setMaterial(mat);

		// Размеры декали задаются из ограничивающего бокса
		decal->setWidth(bb.getSize().x);
		decal->setHeight(bb.getSize().y);
		decal->setSaveToWorldEnabled(true);

		// Созданный узел отслеживается для очистки
		created_nodes.append(decal);
	}
}

// Маска terrain рисуется с помощью форм полигонов.
void LandscapePolygonsSample::draw_terrain_mask_button()
{
	// Каждая фигура рисуется на маске terrain
	for (int i = 0; i < figures.size(); i++)
	{
		auto figure = figures[i];
		Vector<Vec3> points;

		// Позиции дочерних узлов собираются как вершины
		for (int j = 0; j < figure->getNumChildren(); j++)
		{
			points.append(figure->getChild(j)->getWorldPosition());
		}

		// Полигон рендерится в слой маски landscape
		layer_map_editor->generateMeshOnMask(points, Landscape::FLAGS_DATA_MASK_0);

		// Планируется обновление clutter
		is_clutter_mask_valid = false;
		invalidation_frame = Game::getFrame();
	}
}

// Высота terrain выравнивается в границах полигона.
void LandscapePolygonsSample::level_terrain_button()
{
	// Область каждой фигуры выравнивается до минимальной высоты
	for (int i = 0; i < figures.size(); i++)
	{
		auto figure = figures[i];
		Vector<Vec3> points;

		// Позиции дочерних узлов собираются как вершины
		for (int j = 0; j < figure->getNumChildren(); j++)
		{
			points.append(figure->getChild(j)->getWorldPosition());
		}

		// Ограничивающий бокс вычисляется для ссылки на высоту
		WorldBoundBox bb = WorldBoundBox(points.get(), points.size());

		// Terrain выравнивается до самой низкой точки в полигоне
		layer_map_editor->levelHeightForMesh(points, bb.minimum.z);
	}
}

// Высота terrain понижается в границах полигона.
void LandscapePolygonsSample::lower_terrain_button()
{
	// Область каждой фигуры понижается на фиксированную величину
	for (int i = 0; i < figures.size(); i++)
	{
		auto figure = figures[i];
		Vector<Vec3> points;

		// Позиции дочерних узлов собираются как вершины
		for (int j = 0; j < figure->getNumChildren(); j++)
		{
			points.append(figure->getChild(j)->getWorldPosition());
		}

		// Terrain понижается на 20 единиц в пределах полигона
		layer_map_editor->lowerTerrain(points, 20.0f);
	}

}

// Узлы фигур и точек восстанавливаются в исходные позиции.
void LandscapePolygonsSample::revert_points_positions()
{
	// Каждая фигура восстанавливается в исходную позицию
	for (int figure = 0; figure < figures.size(); figure++)
	{
		// Позиция родителя фигуры восстанавливается
		figures[figure]->setWorldPosition(figures_initial_positions[figure]);
		int child_number = figures.get(figure)->getNumChildren();

		// Позиции дочерних точек восстанавливаются
		for (int point = 0; point < child_number; point++)
		{
			figures[figure]->getChild(point)->setWorldPosition(points_initial_positions[figure][point]);
		}
	}

	// Трансформация манипулятора обновляется
	manipulators->updateManipulatorTransform();
}


// Рёбра треугольников рендерятся с помощью визуализатора для отладочного отображения.
void LandscapePolygonsSample::draw_triangulation(
	const Unigine::Vector<Unigine::Math::Vec3>& points,
	const Unigine::Vector<unsigned short>& indices)
{
	// Каждый треугольник рендерится как три ребра
	for (int i = 0; i + 2 < indices.size(); i += 3)
	{
		// Индексы вершин извлекаются для текущего треугольника
		const unsigned ia = indices[i + 0];
		const unsigned ib = indices[i + 1];
		const unsigned ic = indices[i + 2];

		// Извлекаются позиции вершин
		const Vec3& A = points[ia];
		const Vec3& B = points[ib];
		const Vec3& C = points[ic];

		// Рёбра треугольника рисуются красным
		Visualizer::renderLine3D(A, B, vec4_red);
		Visualizer::renderLine3D(B, C, vec4_red);
		Visualizer::renderLine3D(C, A, vec4_red);
	}
}
