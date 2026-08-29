// Демонстрирует Node::saveState и Node::restoreState для сериализации состояния узла
// в Blob. Состояние можно сохранять и восстанавливать во время выполнения через кнопки UI. Призрачный
// бокс рендерится в сохранённой позиции, чтобы визуализировать разницу.

#include <UnigineComponentSystem.h>
#include <UnigineVisualizer.h>

#include "../../menu_ui/SampleDescriptionWindow.h"

using namespace Unigine;
using namespace Math;

// Демонстрирует сохранение и восстановление состояния узла через сериализацию в Blob.
class StateSample : public ComponentBase
{
public:
	COMPONENT_DEFINE(StateSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// Целевой узел, чьё состояние будет сохраняться/восстанавливаться
	PROP_PARAM(Node, node_param);

private:
	// Создаётся Blob для хранения состояния, захватывается начальное состояние.
	void init()
	{
		saved_state = Blob::create();
		save_state();

		visualizer_enabled = Visualizer::isEnabled();
		Visualizer::setEnabled(true);
		gui.init(this);
	}

	// Призрачный бокс рендерится в сохранённой позиции для визуального сравнения.
	void update()
	{
		// Внешний каркас показывает границы взаимодействия
		Visualizer::renderBox(vec3(2.f), translate(Vec3(0, 3, 1.3)), vec4_white);
		// Полупрозрачный бокс показывает сохранённую позицию
		Visualizer::renderSolidBox(vec3(.75f), last_transform, vec4(vec3(1), .25f));
	}

	// Состояние визуализатора восстанавливается, UI очищается.
	void shutdown()
	{
		gui.shutdown();
		Visualizer::setEnabled(visualizer_enabled);
	}

	// Состояние узла сериализуется в Blob, трансформация кэшируется для призрачного рендеринга.
	void save_state()
	{
		// Очищаем предыдущее состояние и сериализуем текущее состояние узла в Blob
		saved_state->clear();
		node_param->saveState(saved_state);
		// Кэшируем трансформацию для призрачной визуализации
		last_transform = node_param->getWorldTransform();
	}

	// Состояние узла десериализуется из Blob, восстанавливая позицию и свойства.
	void restore_state()
	{
		if (saved_state && saved_state->getSize())
		{
			// Сбрасываем позицию потока перед чтением
			saved_state->seekSet(0);
			node_param->restoreState(saved_state);
			// Сбрасываем для возможных будущих чтений
			saved_state->seekSet(0);
		}
	}

	// ========================================================================================

	// Вложенный класс GUI для управления кнопками сохранения/восстановления.
	struct SampleGui : public EventConnections
	{
		void init(StateSample *sample)
		{
			this->sample = sample;

			sample_description_window.createWindow();

			auto parameters = sample_description_window.getParameterGroupBox();
			auto vbox = WidgetVBox::create();
			parameters->addChild(vbox);

			{
				auto hbox = WidgetHBox::create();

				save_btn = WidgetButton::create("Save");
				save_btn->getEventClicked().connect(this, &SampleGui::on_save_state_btn_clicked);
				hbox->addChild(save_btn);

				restore_btn = WidgetButton::create("Restore");
				restore_btn->getEventClicked().connect(this, &SampleGui::on_restore_state_btn_clicked);
				hbox->addChild(restore_btn);

				vbox->addChild(hbox);
			}
		}

		void shutdown()
		{
			sample_description_window.shutdown();
		}

		void on_save_state_btn_clicked(const WidgetPtr &widget, int mouse)
		{
			sample->save_state();
		}

		void on_restore_state_btn_clicked(const WidgetPtr &widget, int mouse)
		{
			sample->restore_state();
		}

		WidgetButtonPtr save_btn;
		WidgetButtonPtr restore_btn;

		StateSample *sample = nullptr;
		SampleDescriptionWindow sample_description_window;
	};

	// ========================================================================================

	// Сохранённое состояние визуализатора для восстановления при завершении работы
	bool visualizer_enabled = false;
	// Закэшированная трансформация сохранённого состояния для призрачной визуализации
	Mat4 last_transform;
	// Бинарное хранилище для сериализованного состояния узла
	BlobPtr saved_state;
	SampleGui gui;
};

REGISTER_COMPONENT(StateSample);
