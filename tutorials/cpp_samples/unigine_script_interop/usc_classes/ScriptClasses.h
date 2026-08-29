// Демонстрирует экспорт классов C++ в UnigineScript через ExternClass.
// Показывает два паттерна: хранение пользовательских объектов скрипта в C++ и предоставление классов C++
// с конструкторами, методами и свойствами, вызываемыми из скрипта.

#pragma once

#include <UnigineComponentSystem.h>

// Настраивает консоль для вывода на экран во время демонстрации взаимодействия с классами.
class ScriptClasses : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(ScriptClasses, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void shutdown();
};


// Пример класса C++, экспортированного в UnigineScript. Наследует Base для подсчёта ссылок.
class MyExternObject : public Unigine::Base
{
public:
	MyExternObject();
	MyExternObject(const Unigine::Math::vec3 &size, float mass);
	~MyExternObject();

	// Аксессоры свойства size
	void setSize(const Unigine::Math::vec3 &s);
	const Unigine::Math::vec3 &getSize() const { return size; }

	// Аксессоры свойства mass
	void setMass(float m);
	float getMass() const { return mass; }

private:
	Unigine::Math::vec3 size;
	float mass;
};
