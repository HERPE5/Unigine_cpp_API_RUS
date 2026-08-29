// Демонстрирует callback-функции событий физического тела: frozen, position и contact.
// Создаётся башня из твёрдых тел; каждое тело меняет материал в зависимости от состояния.
// Замороженные тела становятся серыми, движущиеся подсвечиваются, контакты визуализируются.

#pragma once

#include <UnigineComponentSystem.h>

class BodyCallbacks : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(BodyCallbacks, Unigine::ComponentBase);

	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Параметры построения башни
	PROP_PARAM(Float, space, 1.2);
	PROP_PARAM(Int, tower_level, 10);
	// Материал, применяемый при переходе тела в замороженное (спящее) состояние
	PROP_PARAM(Material, frozen_materal);
	// Материал, применяемый когда тело движется (бодрствует)
	PROP_PARAM(Material, position_materal);
	// Ресурс меша для блоков башни
	PROP_PARAM(File, mesh_file);

private:
	void init();
	void shutdown();

	// Вызывается, когда скорость тела падает ниже порога заморозки
	void frozen_callback(const Unigine::BodyPtr &body);
	// Вызывается каждый кадр, пока тело движется
	void position_callback(const Unigine::BodyPtr &body);
	// Вызывается при обнаружении новой точки контакта
	void contact_callback(const Unigine::BodyPtr &body);

private:
	Unigine::MaterialPtr frozen_mat;
	Unigine::MaterialPtr position_mat;

	// Хранит все созданные объекты башни для очистки
	Unigine::Vector<Unigine::NodePtr> objects;
	// Управляет всеми соединениями событий для пакетного отключения
	Unigine::EventConnections body_connections;
};
