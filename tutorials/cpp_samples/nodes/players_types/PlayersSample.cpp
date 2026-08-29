// Демонстрирует четыре типа игроков и их уникальное поведение:
// - Dummy: статическая камера без управления, полезна для катсцен
// - Persecutor: камера от третьего лица, следующая за целевым узлом
// - Spectator: свободнолетающая камера noclip с инерцией
// - Actor: контроллер персонажа с физическим движением и прыжками

#include <UnigineComponentSystem.h>
#include <UnigineVisualizer.h>
#include <UniginePlayers.h>
#include <UnigineGame.h>

#include "../../menu_ui/SampleDescriptionWindow.h"
#include "../../utils/Utils.h"

using namespace Unigine;
using namespace Math;

class PlayersSample : public ComponentBase
{
public:
	COMPONENT_DEFINE(PlayersSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init()
	{
		// Ищем объект сцены для использования в качестве цели камеры для Persecutor
		NodePtr target = World::getNodeByName("material_ball");

		// Создаём резервную цель, если ничего не найдено в сцене
		if (!target)
			target = NodeDummy::create();

		// Создаём PlayerDummy: фиксированная камера без встроенного управления
		{
			dummy = PlayerDummy::create();

			float z_near = .25f;
			float z_far = 1000.f;
			float fov = 60.f;

			// Перспективная проекция стандартна для 3D-сцен
			dummy->setProjectionMode(Camera::PROJECTION_MODE_PERSPECTIVE);

			if (true) // Настраиваем проекцию через отдельные параметры
			{
				dummy->setZNear(z_near);
				dummy->setZFar(z_far);
				dummy->setFov(fov);
			}

			else // Альтернатива: задать матрицу проекции напрямую
			{
				// perspective() строит стандартную матрицу фрустума
				mat4 projection_matrix = perspective(fov, 1.f, z_near, z_far);
				dummy->setProjection(projection_matrix);
			}

			// Позиционируем камеру, смотрящую на цель, на расстоянии 3.5м
			dummy->setWorldTransform(setTo(rotate(Vec3_up, 0.f * 360.f) * Vec3(3.5f, 0.f, 1.5f), target->getWorldPosition(), vec3_up));
		}

		// Создаём PlayerPersecutor: камера от третьего лица, вращающаяся вокруг цели
		{
			persecutor = PlayerPersecutor::create();

			// Режим вертикального FOV более распространён в играх
			persecutor->setFovMode(Camera::FOV_MODE_VERTICAL);
			persecutor->setFov(60.f);

			// Включаем столкновения, чтобы камера не проходила сквозь геометрию
			persecutor->setCollision(true);
			persecutor->setCollisionMask(~0);
			persecutor->setCollisionRadius(.5f);

			// Fixed=false позволяет дистанции камеры динамически изменяться
			persecutor->setFixed(false);
			persecutor->setMaxDistance(8.f);
			persecutor->setMinDistance(3.f);
			// Anchor смещает точку взгляда от начала координат цели (например, высота головы)
			persecutor->setAnchor(vec3(0.f, 0.f, 0.5f));

			// Задаём узел, за которым будет следовать эта камера
			persecutor->setTarget(target);

			// Отключаем управление, пока этот игрок не станет активным
			persecutor->setControlled(false);

			// Позиционируем на 90 градусов вокруг цели
			persecutor->setWorldTransform(setTo(rotate(Vec3_up, .25f * 360.f) * Vec3(3.5f, 0.f, 1.5f), target->getWorldPosition(), vec3_up));
		}

		// Создаём PlayerSpectator: свободнолетающая камера с инерцией (режим noclip)
		{
			spectator = PlayerSpectator::create();

			spectator->setFovMode(Camera::FOV_MODE_VERTICAL);
			spectator->setFov(80.f);

			// Физика движения: ускорение создаёт постепенный набор скорости
			spectator->setAcceleration(5.f);
			spectator->setMaxVelocity(10.f);
			// Затухание вызывает постепенное замедление при отсутствии ввода
			spectator->setDamping(.9f);

			// Столкновения предотвращают пролёт сквозь стены
			spectator->setCollision(true);
			spectator->setCollisionMask(~0);
			spectator->setCollisionRadius(0.5f);

			spectator->setControlled(false);

			// Позиционируем на 180 градусов вокруг цели
			spectator->setWorldTransform(setTo(rotate(Vec3_up, .5f * 360.f) * Vec3(3.5f, 0.f, 1.5f), target->getWorldPosition(), vec3_up));
		}

		// Создаём PlayerActor: контроллер персонажа с физическим движением по земле
		{
			actor = PlayerActor::create();

			// Капсульная форма столкновений для тела персонажа
			actor->setCollision(true);
			actor->setCollisionMask(~0);
			actor->setCollisionRadius(0.5f);
			actor->setCollisionHeight(1.f);

			// Включаем физические взаимодействия с миром
			actor->setPhysical(true);
			actor->setPhysicalMask(~0);
			actor->setPhysicalMass(1.f);

			actor->setMaxVelocity(5.f);

			// Высота прыжка в метрах
			actor->setJumping(1.5f);

			actor->setControlled(false);

			// Позиционируем на 270 градусов вокруг цели
			actor->setWorldTransform(setTo(rotate(Vec3_up, .75f * 360.f) * Vec3(3.5f, 0.f, 1.5f), target->getWorldPosition(), vec3_up));
		}

		// Начинаем с Actor в качестве активного игрока
		actor->setMainPlayer(true);

		visualizer_enabled = Visualizer::isEnabled();
		Visualizer::setEnabled(true);
		gui.init(this);

		// Захватываем мышь для управления камерой
		mouse_handle = Input::getMouseHandle();
		Input::setMouseHandle(Input::MOUSE_HANDLE::MOUSE_HANDLE_GRAB);
	}

	void update()
	{
		// Отрисовываем отладочную визуализацию для всех неактивных игроков
		visualize_player(dummy);
		visualize_player(persecutor);
		visualize_player(spectator);
		visualize_player(actor);

		gui.update();
	}

	void shutdown()
	{
		gui.shutdown();
		Visualizer::setEnabled(visualizer_enabled);
		// Восстанавливаем исходный режим обработки мыши
		Input::setMouseHandle(mouse_handle);
	}

	void visualize_player(PlayerPtr player)
	{
		// Пропускаем визуализацию для текущего игрока (загораживала бы обзор)
		if (!player || Game::getPlayer() == player)
			return;

		vec4 label_color = vec4_white;
		vec4 frustum_color = vec4_white;
		vec4 collision_shape_color = visualize_collision_shapes ? vec4(.97f, .9f, .356f, 1.f) : vec4_zero;
		vec4 persecutor_target_color = visualize_persecutor_target ? vec4(vec3(91, 221, 247) / 255.f, 1.f) : vec4_zero;

		// Обратная матрица modelview = мировая трансформация камеры
		Mat4 imodelview = player->getCamera()->getIModelview();
		Vec3 camera_position = imodelview.getTranslate();

		// getAspectCorrectedProjection() применяет соотношение сторон viewport
		// (исходная матрица проекции имеет aspect=1.0)
		Visualizer::renderFrustum(player->getAspectCorrectedProjection(), imodelview, frustum_color);

		{
			// Рисуем локальные оси координат в позиции камеры
			float arrow_size = .6f;
			float arrow_end_size = .15f;
			float arrow_opacity = .8f;

			// Извлекаем базисные векторы из матрицы трансформации
			Vec3 forward = imodelview.getAxisY();
			Vec3 right = imodelview.getAxisX();
			Vec3 up = imodelview.getAxisZ();

			Visualizer::renderVector(camera_position, camera_position + forward * arrow_size, vec4_green * vec4(vec3(1.f), arrow_opacity), arrow_end_size);
			Visualizer::renderVector(camera_position, camera_position + right * arrow_size, vec4_red * vec4(vec3(1.f), arrow_opacity), arrow_end_size);
			Visualizer::renderVector(camera_position, camera_position + up * arrow_size, vec4_blue * vec4(vec3(1.f), arrow_opacity), arrow_end_size);
		}

		// Визуализация, специфичная для типа
		switch (player->getType())
		{
			case Node::PLAYER_DUMMY:
			{
				Visualizer::renderMessage3D(camera_position + Vec3_up * .3f, vec3_zero, "Dummy", label_color, 1, 16);

				break;
			}

			case Node::PLAYER_PERSECUTOR:
			{
				PlayerPersecutorPtr persecutor = static_ptr_cast<PlayerPersecutor>(player);

				Visualizer::renderMessage3D(camera_position + Vec3_up * .3f, vec3_zero, "Persecutor", label_color, 1, 16);

				// Визуализируем сферу столкновений вокруг камеры
				if (persecutor->getCollision())
				{
					Visualizer::renderSphere(
						persecutor->getCollisionRadius(),
						persecutor->getWorldTransform(),
						collision_shape_color
					);
				}

				// Подсвечиваем целевой узел, за которым следует камера
				NodePtr target = persecutor->getTarget();

				if (target)
				{
					WorldBoundBox bbox = target->getWorldBoundBox();

					Visualizer::renderMessage3D(bbox.getCenter() + Vec3_up * (bbox.getSize().y * .5f + .2f), vec3_zero, "Persecutor Target", persecutor_target_color, 1, 16);
					Visualizer::renderNodeBoundBox(target, persecutor_target_color);
				}

				break;
			}

			case Node::PLAYER_SPECTATOR:
			{
				PlayerSpectatorPtr spectator = static_ptr_cast<PlayerSpectator>(player);

				Visualizer::renderMessage3D(camera_position + Vec3_up * .3f, vec3_zero, "Spectator", label_color, 1, 16);

				if (spectator->getCollision())
				{
					Visualizer::renderSphere(
						spectator->getCollisionRadius(),
						spectator->getWorldTransform(),
						collision_shape_color
					);
				}

				break;
			}

			case Node::PLAYER_ACTOR:
			{
				PlayerActorPtr actor = static_ptr_cast<PlayerActor>(player);

				Visualizer::renderMessage3D(camera_position + Vec3_up * .3f, vec3_zero, "Actor", label_color, 1, 16);

				// Actor использует капсульные столкновения (цилиндр с полусферическими торцами)
				if (actor->getCollision())
				{
					Visualizer::renderCapsule(
						actor->getCollisionRadius(),
						actor->getCollisionHeight(),
						{
							// Позиционируем капсулу над землёй (центр тела капсулы)
							translate(
								actor->getWorldTransform().getAxisZ() * (
									actor->getCollisionRadius() +
									actor->getCollisionHeight() * .5f
								)
							) *
							actor->getWorldTransform(),
						},
						collision_shape_color
					);
				}

				break;
			}

			default: break;
		}
	}

	// ========================================================================================

	struct SampleGui : public EventConnections
	{
		void init(PlayersSample *sample)
		{
			this->sample = sample;

			sample_description_window.createWindow();

			auto parameters = sample_description_window.getParameterGroupBox();
			auto vbox = WidgetVBox::create();
			parameters->addChild(vbox);

			vbox->addChild(WidgetSpacer::create());

			{
				// Кнопки выбора игрока
				auto hbox = WidgetHBox::create();

				dummy_btn = WidgetButton::create("Dummy");
				dummy_btn->getEventClicked().connect(this, &SampleGui::on_player_button_clicked);
				dummy_btn->setToggleable(true);
				hbox->addChild(dummy_btn);

				persecutor_btn = WidgetButton::create("Persecutor");
				persecutor_btn->getEventClicked().connect(this, &SampleGui::on_player_button_clicked);
				persecutor_btn->setToggleable(true);
				hbox->addChild(persecutor_btn);

				spectator_btn = WidgetButton::create("Spectator");
				spectator_btn->getEventClicked().connect(this, &SampleGui::on_player_button_clicked);
				spectator_btn->setToggleable(true);
				hbox->addChild(spectator_btn);

				actor_btn = WidgetButton::create("Actor");
				actor_btn->getEventClicked().connect(this, &SampleGui::on_player_button_clicked);
				actor_btn->setToggleable(true);
				// Имитируем клик, чтобы выбрать Actor по умолчанию
				actor_btn->runEventClicked(0);
				hbox->addChild(actor_btn);

				vbox->addChild(hbox);
			}

			// Слайдеры параметров камеры (применяются к текущему активному игроку)
			fov_slider = sample_description_window.addFloatParameter("FOV", "", 60.f, 10.f, 120.f, [](float value) { auto player = Game::getPlayer(); if (player) player->setFov(value); });
			z_far_slider = sample_description_window.addFloatParameter("Far Z", "", 1000.f, 5.f, 1000.f, [](float value) { auto player = Game::getPlayer(); if (player) player->setZFar(value); });
			z_near_slider = sample_description_window.addFloatParameter("Near Z", "", 0.25f, 0.01f, 5.f, [](float value) { auto player = Game::getPlayer(); if (player) player->setZNear(value); });
		}

		void update()
		{
			// Синхронизируем значения слайдеров с настройками камеры текущего игрока
			auto player = Game::getPlayer();

			if (player)
			{
				fov_slider->setValue(int(player->getFov()) * 100);
				z_far_slider->setValue(int(player->getZFar()) * 100);
				z_near_slider->setValue(int(player->getZNear()) * 100);
			}
		}

		void shutdown() { sample_description_window.shutdown(); }

		void on_player_button_clicked(const WidgetPtr &widget, int mouse)
		{
			// Отключаем все события кнопок во время смены состояния, чтобы предотвратить рекурсию
			MUTE_EVENT(dummy_btn->getEventClicked());
			MUTE_EVENT(persecutor_btn->getEventClicked());
			MUTE_EVENT(spectator_btn->getEventClicked());
			MUTE_EVENT(actor_btn->getEventClicked());

			// Снимаем состояние нажатия со всех кнопок
			dummy_btn->setToggled(false);
			persecutor_btn->setToggled(false);
			spectator_btn->setToggled(false);
			actor_btn->setToggled(false);

			// Отключаем управление у всех игроков
			sample->persecutor->setControlled(false);
			sample->spectator->setControlled(false);
			sample->actor->setControlled(false);

			// Активируем выбранного игрока
			if (widget == dummy_btn)
			{
				// У Dummy нет управления - камера остаётся фиксированной
				Game::setPlayer(sample->dummy);
				dummy_btn->setToggled(true);
			}

			if (widget == persecutor_btn)
			{
				Game::setPlayer(sample->persecutor);
				sample->persecutor->setControlled(true);
				persecutor_btn->setToggled(true);
			}

			if (widget == spectator_btn)
			{
				Game::setPlayer(sample->spectator);
				sample->spectator->setControlled(true);
				spectator_btn->setToggled(true);
			}

			if (widget == actor_btn)
			{
				Game::setPlayer(sample->actor);
				sample->actor->setControlled(true);
				actor_btn->setToggled(true);
			}
		}

		PlayersSample *sample = nullptr;
		SampleDescriptionWindow sample_description_window;

		WidgetSliderPtr fov_slider;
		WidgetSliderPtr z_far_slider;
		WidgetSliderPtr z_near_slider;

		WidgetButtonPtr dummy_btn;
		WidgetButtonPtr persecutor_btn;
		WidgetButtonPtr spectator_btn;
		WidgetButtonPtr actor_btn;
	};

	// ========================================================================================

	// Неподвижная камера без управления
	PlayerDummyPtr dummy;
	// Камера от третьего лица, следующая за целью
	PlayerPersecutorPtr persecutor;
	// Свободно летающая камера с инерцией
	PlayerSpectatorPtr spectator;
	// Контроллер персонажа с физикой
	PlayerActorPtr actor;

	bool visualizer_enabled = false;
	bool visualize_collision_shapes = true;
	bool visualize_persecutor_target = true;

	SampleGui gui;
	// Сохранённый режим мыши для восстановления
	Input::MOUSE_HANDLE mouse_handle;
};

REGISTER_COMPONENT(PlayersSample);
