# Unigine::Property Class (CPP)

**Header:** #include <UnigineProperties.h>


Этот класс предоставляет интерфейс для работы со свойствами: он используется для изменения [properties](../../../principles/world_structure/index.md#properties), которые позволяют управлять значениями параметров, связанных с логикой. Когда свойство назначается узлу, создаётся экземпляр [internal property](../../../principles/properties/index.md#internal), который сохраняется в файл `.world` или `.node`. Однако вместо всего списка параметров он содержит только изменённые.


Следует различать понятия [path](#setFilePath_cstr_void) и [name](#setName_cstr_void) свойства:

- **Путь (path)** указывает, где свойство хранится на диске. Путь включает имя файла свойства.
- **Имя (name)** указывает, как свойство будет отображаться в UnigineEditor (окно Property Hierarchy, раздел поверхностей узлов окна Parameters). Имя также можно использовать для обращения к свойству из [code](../../../api/library/engine/class.properties_cpp.md#findProperty_cstr_Property).

По умолчанию имя свойства и имя файла `*.prop` совпадают.
Используя функции этого класса, можно, например, реализовать *редактор свойств*.


**Свойства (Properties)** определяют, как объект будет вести себя и взаимодействовать с другими объектами и окружением сцены.


Свойство — это "материал" для логики приложения, представленный набором **[parameters](../../../code/formats/property_format.md#element_parameter)**, связанных с логикой. Свойства можно использовать для построения [**компонентов**](../../../principles/component_system/index.md), расширяющих функциональность узлов.


Все свойства в проекте организованы в [hierarchy](../../../principles/properties/inheritance.md). Чтобы изменить свойства, их следует получать из иерархии через функции [*API*](../../../api/library/engine/class.properties_cpp.md).


Параметрами свойств управляют по отдельности через [PropertyParameter class](../../../api/library/common/class.propertyparameter_cpp.md); чтобы получить любой параметр по его имени или идентификатору, следует использовать метод **[getParameterPtr()](../../...md#getParameterPtr_cstr_PropertyParameter)**.


```cpp
PropertyParameterPtr pPropertyParameter = pProperty->getParameterPtr(); // get "root" parameter
NodePtr pTargetNode = pPropertyParameter->getChild(k)->getValueNode(); // get child with index "k", then its value

// ...

float positionFactor = pPropertyParameter->getChild(k)->getValueFloat();
// и т.д.

// Если известны имена, можно использовать:
pTargetNode = pProperty->getParameterPtr("target")->getValueNode();
positionFactor = pProperty->getParameterPtr("position_factor")->getValueFloat();


```


Автоматическое преобразование типов параметров свойств делает их подобными неким универсальным переменным, т.е. можно задать новое значение для целочисленного параметра int_param и указать его тип следующим образом:


```cpp
PropertyParameterPtr int_param;

/* ... */

// задаём новое значение целочисленного параметра с использованием строки
int_param->setValue("15");

// задаём новое значение целочисленного параметра с использованием float
int_param->setValue(5.0f);

// получаем значение целочисленного параметра как строку
Log::message("Integer parameter value : %s", int_param->getValueString());


```


> **Notice:** Изменять можно только существующие параметры свойства. Чтобы добавить или удалить параметры, следует вручную отредактировать файл `.prop` или использовать API для редактирования XML-файла через код.


### Добавление и удаление свойств


> **Notice:** Класс *Property* не позволяет добавлять новое свойство в иерархию свойств.

Новое свойство можно добавить в иерархию одним из следующих способов:
- Путём создания и ручного редактирования соответствующего файла `.prop`. Например, создадим в папке `data` следующий файл, описывающий свойство для GameObjectUnit: ```xml <?xml version="1.0" encoding="utf-8"?> <property version="2.16.0.2" manual="1" editable="0" name="GameObjectsUnit"> <parameter name="weapon_type" type="switch" items="air,land,all_types">0</parameter> <parameter name="attack" type="toggle">1</parameter> <parameter name="damage" type="int" max="1000">1</parameter> <parameter name="velocity" type="float" max="100">30</parameter> <parameter name="material" type="string"/> </property> ```
- Путём наследования от существующего свойства через функцию [*Properties::inheritProperty()*](../../../api/library/engine/class.properties_cpp.md#inheritProperty_UGUID_cstr_cstr_Property) или функцию [*inherit()*](#inherit_cstr_Property) класса Property. Например: ```cpp // наследуем свойство GameObjectsUnit_0 от свойства GameObjectsUnit PropertyPtr inherited_prop = Properties::findManualProperty("GameObjectsUnit")->inherit("GameObjectsUnit_0", "game_object_unit_0.prop"); // наследуем свойство GameObjectsUnit_1 от свойства GameObjectsUnit_0 через Manager Properties::inheritProperty(inherited_prop->getGUID(), "GameObjectsUnit_1", "game_object_unit_1.prop"); ``` Чтобы сохранить все свойства в иерархии, которые можно сохранить (т.е. редактируемые, с указанным путём, не внутренние и не ручные), используйте функцию [*Properties::saveProperties()*](../../../api/library/engine/class.properties_cpp.md#saveProperties_int). > **Notice:** По умолчанию все параметры и состояния наследуемого свойства совпадают с указанными в родительском свойстве. Дочернее свойство может [override some parameters of its parent or add new ones](../../../principles/world_structure/index.md#properties_hierarchy).
- Путём редактирования соответствующего файла `.prop` [via API](../../../api/library/common/class.xml_cpp.md): можно открыть XML-файл, записать в него данные и сохранить его.


Чтобы удалить свойство, можно просто вызвать функцию *[removeProperty()](../../../api/library/engine/class.properties_cpp.md#removeProperty_UGUID_int_int_int)*:

```cpp
// удаляем свойство с указанным именем со всеми его дочерними элементами и удаляем файл *.prop
Properties::removeProperty(Properties::findProperty("GameObjectsUnit_0")->getGUID(), 1, 1);


```


### Обработка событий


Вы можете подписаться на события, чтобы отслеживать любые изменения, вносимые в свойство и его параметры, и выполнять определённые действия. Сигнатура функции-обработчика может быть одной из следующих:

```cpp
// для типа ParameterChanged
void handler_function_name(const PropertyPtr &property, int parameter_num);

// для всех остальных типов
void handler_function_name(const PropertyPtr &property);


```

 Пример ниже показывает, как подписаться на события для отслеживания изменений параметров свойства и вывести имя свойства и изменённого параметра (предположим, у нас есть ручное свойство с именем *my_prop* и целочисленным параметром с именем *my_int_param*).
```cpp
// экземпляр класса EventConnections для управления подписками на события
EventConnections econn;

void parameter_changed(const PropertyPtr &property, int num)
{
	Log::message("Parameter \"%s\" of the property \"%s\" has changed its value.\n", property->getParameterPtr(num)->getName(), property->getName());
	// ...
}

	// где-то в коде

	// получаем ручное свойство с именем "my_prop" через Property Manager
	PropertyPtr property = Properties::findManualProperty("my_prop.prop");

	// подписываемся на событие изменения параметра
	property->getEventParameterChanged().connect(econn, parameter_changed);

	// изменяем значение параметра "my_int_param"
	property->getParameterPtr("my_int_param")->setValueInt(3);

	// ...

	// удаляем все подписки на события где-то при завершении работы
	econn.disconnectAll();


```


### Пример использования


Чтобы проиллюстрировать управление свойствами и их параметрами, сделаем простой просмотрщик всех свойств проекта, а также их параметров. Наш просмотрщик будет иметь следующие возможности:

- Просмотр списка всех свойств, используемых в проекте.
- Просмотр списка параметров текущего выбранного свойства. Унаследованные, переопределённые и уникальные параметры отображаются разными цветами.
- Изменение значения выбранного параметра свойства.
- Сброс значения выбранного параметра свойства.
- Наследование нового свойства от выбранного.
- Клонирование выбранного свойства.
- Сохранение текущего выбранного свойства в файл.
- Перезагрузка всех свойств.


![](property_viewer.png)


Мы можем добавить следующие файлы `*.prop` в папку `data` нашего проекта, чтобы проверить наш просмотрщик:

- `my_property.prop` <details> <summary>my_property.prop | Close</summary> **my_property.prop** ```xml <?xml version="1.0" encoding="utf-8"?> <property version="2.16.0.2" name="my_property" parent="node_base" manual="1"> <parameter name="damage" type="int" max="1000">1</parameter> <parameter name="mass" type="float" tooltip="Aircraft mass">1345</parameter> <parameter name="attack" type="toggle">1</parameter> <parameter name="weapon_type" type="switch" items="air,land,all_types">0</parameter> <parameter name="Mask" type="mask"/> <parameter name="Base Material" type="material"/> <parameter name="Model Node" type="node"/> <struct name="member"> <parameter name="name" type="string"></parameter> <parameter name="rank" type="switch" items="2LT,1LT,CPT,MAJ,LTC,COL,BG,MG">0</parameter> <parameter name="year" type="int"></parameter> <parameter name="status" type="toggle">1</parameter> </struct> <parameter name="Members" type="array" array_type="member" group="Crew Information"> <value> <parameter name="name">Mike Watts</parameter> <parameter name="rank" type="switch" items="2LT,1LT,CPT,MAJ,LTC,COL,BG,MG">3</parameter> <parameter name="year">1990</parameter> </value> <value> <parameter name="name">John Doe</parameter> <parameter name="rank" type="switch" items="2LT,1LT,CPT,MAJ,LTC,COL,BG,MG">2</parameter> <parameter name="year">1995</parameter> </value> <value> <parameter name="name">Vincent Preston</parameter> <parameter name="rank" type="switch" items="2LT,1LT,CPT,MAJ,LTC,COL,BG,MG">1</parameter> <parameter name="year">1997</parameter> </value> </parameter> <parameter name="Service Flags" type="array" array_type="toggle" group="Auxiliary"> <value>1</value> <value>0</value> <value>1</value> <value>0</value> </parameter> </property> ``` </details>
- `custom_prop.prop` <details> <summary>custom_prop.prop | Close</summary> **custom_prop.prop** ```xml <?xml version="1.0" encoding="utf-8"?> <property version="2.16.0.2" name="custom_prop" manual="1"> <!-- First structure declaration --> <struct name="struct1"> <parameter name="param_a" type="int">1</parameter> <parameter name="param_b" type="toggle">0</parameter> <parameter name="param_c" type="int">1</parameter> </struct> <!-- Inherited structure declaration--> <struct name="struct2" parent_name="struct1"> <parameter name="param2_a" type="toggle">0</parameter> <parameter name="param2_b" type="float">1.0</parameter> </struct> <!-- Struct parameter of struct2 type --> <parameter name="my_struct_param" type="struct2"></parameter> <!-- Nested structure declaration --> <struct name="struct3"> <parameter name="param3_a" type="struct2">0</parameter> <parameter name="param3_b" type="int">15</parameter> </struct> <!-- Declaration of a one-dimensional array of struct3 elements--> <parameter name="my_struct_array" array_type="struct3"></parameter> </property> ``` </details>
- `custom_prop_0.prop` inherited from the **custom_prop** property. <details> <summary>custom_prop_0.prop | Close</summary> **custom_prop_0.prop** ```xml <?xml version="1.0" encoding="utf-8"?> <property version="2.16.0.2" name="custom_prop_0" manual="1" parent_name="custom_prop"> <!-- Declaration of a 2-dimensional array (matrix) of integer elements--> <parameter name="my_int_array" array_type="int" array_dim="2"></parameter> </property> ``` </details>


Ниже приведён исходный код на C++, реализующий наш Property Viewer. Вы можете скопировать и вставить его в соответствующие файлы вашего проекта.


<details>
<summary>AppSystemLogic.h | Close</summary>

**AppSystemLogic.h**


```cpp
#ifndef __APP_SYSTEM_LOGIC_H__
#define __APP_SYSTEM_LOGIC_H__

#include <UnigineLogic.h>
#include <UnigineWidgets.h>
#include <UnigineGui.h>
#include <UnigineMap.h>

using namespace Unigine;
using namespace Math;

class AppSystemLogic : public Unigine::SystemLogic
{

private:
	// объявляем используемые виджеты UI
	WidgetWindowPtr window;
	WidgetHBoxPtr hbox;

	WidgetGroupBoxPtr properties_gb;
	WidgetTreeBoxPtr properties;
	WidgetGroupBoxPtr parameters_gb;
	WidgetTreeBoxPtr parameters;
	WidgetGroupBoxPtr value_gb;
	WidgetGroupBoxPtr menu_gb;

	WidgetVBoxPtr vbox2, vbox3;
	WidgetHBoxPtr hbox2;
	WidgetButtonPtr reload;
	WidgetButtonPtr clone;
	WidgetButtonPtr inherit;
	WidgetButtonPtr save_prop;

	// значения
	Vector<WidgetLabelPtr> label;
	WidgetEditLinePtr value;
	WidgetButtonPtr change;
	WidgetButtonPtr reset;

	WidgetLabelPtr info;
	WidgetLabelPtr prop_info;
	// списки свойств и параметров
	Map<int, PropertyPtr> item_prop;
	Map<int, PropertyParameterPtr> item_param;

	void refresh_properties();
	void properties_changed();
	void parameters_changed();

	void change_clicked(const Unigine::WidgetPtr &button, int mbuttons);
	void reset_clicked(const Unigine::WidgetPtr &button, int mbuttons);
	void reload_clicked(const Unigine::WidgetPtr &button, int mbuttons);
	void refresh_info();
	void clone_clicked(const Unigine::WidgetPtr &button, int mbuttons);
	void inherit_clicked(const Unigine::WidgetPtr &button, int mbuttons);
	void save_prop_clicked(const Unigine::WidgetPtr &button, int mbuttons);
public:
	AppSystemLogic();
	~AppSystemLogic() override;

	int init() override;

	int update() override;
	int postUpdate() override;

	int shutdown() override;
};

#endif // __APP_SYSTEM_LOGIC_H__

```

</details>


<details>
<summary>AppSystemLogic.cpp | Close</summary>

**AppSystemLogic.cpp**


```cpp
#include "AppSystemLogic.h"
#include <UnigineProperties.h>
#include <UnigineFileSystem.h>
#include <functional>

using namespace Unigine;

// экземпляр класса EventConnections для управления подписками на события
EventConnections econnections;

// Системная логика, существует в течение жизненного цикла приложения.
// Эти методы вызываются сразу после соответствующих методов системного скрипта (UnigineScript).

AppSystemLogic::AppSystemLogic()
{
}

AppSystemLogic::~AppSystemLogic()
{
}

int AppSystemLogic::init()
{
	Engine::get()->setBackgroundUpdate(Engine::BACKGROUND_UPDATE_RENDER_NON_MINIMIZED);

	// создаём пользовательский интерфейс
	GuiPtr gui = Gui::getCurrent();
	window = WidgetWindow::create(gui, "Properties Viewer");
	window->setSizeable(1);
	window->setWidth(WindowManager::getMainWindow()->getSize().x);
	window->setHeight(WindowManager::getMainWindow()->getSize().y);
	gui->addChild(window, Gui::ALIGN_OVERLAP);

	vbox2 = WidgetVBox::create(gui);
	window->addChild(vbox2, Gui::ALIGN_EXPAND);

	hbox = WidgetHBox::create(gui);
	vbox2->addChild(hbox, Gui::ALIGN_EXPAND);

	properties_gb = WidgetGroupBox::create(gui, "Properties");
	parameters_gb = WidgetGroupBox::create(gui, "Parameters");
	hbox->addChild(properties_gb, Gui::ALIGN_EXPAND);
	hbox->addChild(parameters_gb, Gui::ALIGN_EXPAND);

	properties = WidgetTreeBox::create(gui);
	parameters = WidgetTreeBox::create(gui);
	properties_gb->addChild(properties, Gui::ALIGN_EXPAND);
	parameters_gb->addChild(parameters, Gui::ALIGN_EXPAND);

	vbox3 = WidgetVBox::create(gui);
	hbox->addChild(vbox3, Gui::ALIGN_EXPAND);
	value_gb = WidgetGroupBox::create(gui, "Value");
	value_gb->setWidth(300);
	value_gb->setHeight(300);
	value_gb->arrange();
	menu_gb = WidgetGroupBox::create(gui, "Menu");
	vbox3->addChild(value_gb, Gui::ALIGN_LEFT);
	vbox3->addChild(menu_gb, Gui::ALIGN_EXPAND);

	label.append() = WidgetLabel::create(gui, "");
	label.last()->setFontRich(1);
	value_gb->addChild(label.last(), Gui::ALIGN_LEFT);
	value = WidgetEditLine::create(gui);
	value_gb->addChild(value, Gui::ALIGN_EXPAND);
	for (int i = 0; i < 12; i++)
	{
		label.append() = WidgetLabel::create(gui, "");
		label.last()->setFontRich(1);
		value_gb->addChild(label.last(), Gui::ALIGN_LEFT);
	}
	change = WidgetButton::create(gui, "Change Value");
	value_gb->addChild(change, Gui::ALIGN_LEFT);
	reset = WidgetButton::create(gui, "Reset Value");
	value_gb->addChild(reset, Gui::ALIGN_LEFT);

	reload = WidgetButton::create(gui, "Reload Property Files");
	clone = WidgetButton::create(gui, "Clone Property");
	inherit = WidgetButton::create(gui, "Inherit Property");
	save_prop = WidgetButton::create(gui, "Save Property");

	menu_gb->addChild(reload, Gui::ALIGN_EXPAND);
	menu_gb->addChild(clone, Gui::ALIGN_EXPAND);
	menu_gb->addChild(inherit, Gui::ALIGN_EXPAND);
	menu_gb->addChild(save_prop, Gui::ALIGN_EXPAND);

	info = WidgetLabel::create(gui);
	info->setFontRich(1);
	info->setText(
		"<font color=00ffff>Unique value</font><br>"
		"<font color=ffffff>Inherited value</font><br>"
		"<font color=ffff00>Overridden value</font><br>");
	menu_gb->addChild(info, Gui::ALIGN_LEFT);
	prop_info = WidgetLabel::create(gui);
	menu_gb->addChild(prop_info, Gui::ALIGN_LEFT);

	// подписываемся на события элементов UI
	properties->getEventChanged().connect(econnections, this, &AppSystemLogic::properties_changed);
	parameters->getEventChanged().connect(econnections, this, &AppSystemLogic::parameters_changed);

	change->getEventClicked().connect(econnections, this, &AppSystemLogic::change_clicked);
	reset->getEventClicked().connect(econnections, this, &AppSystemLogic::reset_clicked);
	reload->getEventClicked().connect(econnections, this, &AppSystemLogic::reload_clicked);
	clone->getEventClicked().connect(econnections, this, &AppSystemLogic::clone_clicked);
	inherit->getEventClicked().connect(econnections, this, &AppSystemLogic::inherit_clicked);
	save_prop->getEventClicked().connect(econnections, this, &AppSystemLogic::save_prop_clicked);

	refresh_properties();
	return 1;
}

/// метод обновления свойств
void AppSystemLogic::refresh_properties()
{
	properties->getEventChanged().setEnabled(false);
	properties->clear();
	item_prop.clear();

	// рекурсивная функция, проходящая по всем дочерним свойствам и строящая иерархию свойств
	std::function<void(int, const PropertyPtr &)> attach_children = [&, this](int parent, const PropertyPtr &prop_parent)
	{
		for (int k = 0; k < prop_parent->getNumChildren(); k++)
		{
			PropertyPtr prop = prop_parent->getChild(k);
			if (prop != prop_parent && prop->getParent() && prop->getParent() == prop_parent)
			{
				int child = properties->addItem(prop->getName());
				properties->addItemChild(parent, child);
				item_prop.append(child, prop);
				attach_children(child, prop);
			}
		}
	};
	// строим иерархию свойств
	for (int i = 0; i < Properties::getNumProperties(); i++)
	{
		PropertyPtr prop_base = Properties::getProperty(i);
		if (prop_base->isBase())
		{
			int parent = properties->addItem(prop_base->getName());
			item_prop.append(parent, prop_base);
			attach_children(parent, prop_base);
		}
	}
	properties->getEventChanged().setEnabled(true);
}

/// метод обновления параметров свойства
void AppSystemLogic::properties_changed()
{
	parameters->getEventChanged().setEnabled(false);
	// очищаем список параметров свойства и обновляем отображаемые значения
	parameters->clear();
	value_gb->setEnabled(0);
	for (int i = 0; i <= 12; i++)
		label[i]->setText("");

	item_param.clear();

	int item = properties->getCurrentItem();
	if (item == -1)
	{
		parameters->getEventChanged().setEnabled(true);
		return;
	}
	// получаем свойство из списка в соответствии с текущим выбором
	PropertyPtr prop = item_prop[item];

	// получаем корневой параметр выбранного свойства
	PropertyParameterPtr pp = prop->getParameterPtr();

	// рекурсивная функция, проходящая по всем параметрам свойства
	std::function<void(int, const PropertyParameterPtr &)> add_parameters = [&, this](int parent, const PropertyParameterPtr &p)
	{
		for (int i = 0; i < p->getNumChildren(); i++)
		{
			PropertyParameterPtr child = p->getChild(i);
			int child_index = parameters->addItem(child->getName());
			parameters->setItemColor(child_index,
				vec4(
					itof(child->isInherited()),
					1,
					itof(!child->isOverridden()),
					child->isHidden() ? 0.5f : 1.0f));
			item_param.append(child_index, child);

			if (parent != -1)
				parameters->addItemChild(parent, child_index);

			add_parameters(child_index, child);
		}
	};

	// строим иерархию параметров для выбранного свойства
	add_parameters(-1, pp);

	// подготавливаем информацию о свойстве
	String pi = String::format("\nName: %s\nPath: %s\nInternal: %d\nStructs: %d\n", prop->getName(), prop->getFilePath(), prop->isInternal(), prop->getNumStructs());
	// добавляем все структуры, определённые в свойстве (если есть)
	for (int i = 0; i < prop->getNumStructs(); i++)
		pi += String::format("%d) %s\n", i, prop->getStructName(i));
	// отображаем информацию о свойстве
	prop_info->setText(pi.get());

	parameters->getEventChanged().setEnabled(true);
	parameters->setCurrentItem(-1);
}
/// метод обновления информации о текущем выбранном параметре свойства
void AppSystemLogic::parameters_changed()
{
	// проверяем, выбран ли какой-либо параметр свойства
	int item = parameters->getCurrentItem();
	if (item == -1)
		return;

	value_gb->setEnabled(1);
	// получаем параметр из списка в соответствии с текущим выбором
	PropertyParameterPtr p = item_param[item];
	int i = 0;
	label[i++]->setText(String::format("<font color=ffff00>ID:</font> %d", p->getID()));
	label[i++]->setText(String::format("<font color=ffff00>Name:</font> %s", p->getName()));
	label[i++]->setText(String::format("<font color=ffff00>Title:</font> %s", p->getTitle()));
	label[i++]->setText(String::format("<font color=ffff00>Tooltip:</font> %s", p->getTooltip()));
	label[i++]->setText(String::format("<font color=ffff00>Group:</font> %s", p->getGroup()));
	label[i++]->setText(String::format("<font color=ffff00>Filter:</font> %s", p->getFilter()));

	String s;
	// отображаем тип параметра
	if (p->getType() == Property::PARAMETER_ARRAY)
		s = String::format("<font color=ffff00>Type:</font> array "
			"[<font color=ffff00>Size:</font> %d, <font color=ffff00>Type:</font> %s]", p->getArraySize(), p->getArrayTypeName());
	else if (p->getType() == Property::PARAMETER_STRUCT)
		s = String::format("<font color=ffff00>Type:</font> struct [<font color=ffff00>Struct Name:</font> %s]", p->getStructName());
	else
		s = String::format("<font color=ffff00>Type:</font> %s", p->getProperty()->parameterNameByType(p->getType()));
	label[i++]->setText(s.get());
	label[i++]->setText(String::format("<font color=ffff00>Hidden:</font> %d", p->isHidden()));
	label[i++]->setText(String::format("<font color=ffff00>Inherited:</font> %d", p->isInherited()));
	label[i++]->setText(String::format("<font color=ffff00>Overridden:</font> %d", p->isOverridden()));
	label[i++]->setText(String::format("<font color=ffff00>Has Min:</font> %d", p->hasSliderMinValue()));
	label[i++]->setText(String::format("<font color=ffff00>Has Max:</font> %d", p->hasSliderMaxValue()));
	s = "";
	if (p->getType() == Property::PARAMETER_INT)
		s = String::format("<font color=ffff00>Min:</font> %d <font color=ffff00>Max:</font> %d", p->getIntMinValue(), p->getIntMaxValue());
	else if (p->getType() == Property::PARAMETER_FLOAT)
		s = String::format("<font color=ffff00>Min:</font> %f <font color=ffff00>Max:</font> %f", p->getFloatMinValue(), p->getFloatMaxValue());
	else if (p->getType() == Property::PARAMETER_DOUBLE)
		s = String::format("<font color=ffff00>Min:</font> %f <font color=ffff00>Max:</font> %f", p->getDoubleMinValue(), p->getDoubleMaxValue());
	else if (p->getType() == Property::PARAMETER_SWITCH)
		s = String::format("<font color=ffff00>Switch Num Items:</font> %d", p->getSwitchNumItems());
	label[i++]->setText(s.get());
	value->setText(p->getValueString());
	reset->setEnabled(p->isOverridden());
}

/// обработчик события on_click кнопки change
void AppSystemLogic::change_clicked(const WidgetPtr &button, int mbuttons)
{
	// проверяем, выбран ли в данный момент какой-либо параметр свойства
	int item = parameters->getCurrentItem();
	if (item == -1)
		return;
	// задаём значение текущего выбранного параметра свойства и обновляем информацию
	PropertyParameterPtr pp = item_param[item];
	pp->setValue(value->getText());

	refresh_info();
}

/// обработчик события on_click кнопки reset
void AppSystemLogic::reset_clicked(const WidgetPtr &button, int mbuttons)
{
	// проверяем, выбран ли в данный момент какой-либо параметр свойства
	int item = parameters->getCurrentItem();
	if (item == -1)
		return;

	// сбрасываем значение текущего выбранного параметра свойства и обновляем информацию
	PropertyParameterPtr pp = item_param[item];
	pp->resetValue();

	refresh_info();
}

/// обработчик события on_click кнопки reload
void AppSystemLogic::reload_clicked(const WidgetPtr &button, int mbuttons)
{
	// перезагружаем все свойства и обновляем информацию
	Properties::reloadProperties();
	refresh_info();
}

/// метод обновления информации о свойстве и параметре
void AppSystemLogic::refresh_info()
{
	// получаем текущие индексы выбора свойства и параметра
	int item_pr = properties->getCurrentItem();
	int item_pa = parameters->getCurrentItem();
	refresh_properties();

	// задаём текущие элементы и обновляем отображаемую информацию
	properties->setCurrentItem(clamp(item_pr, -1, properties->getNumItems() - 1));
	properties_changed();
	parameters->setCurrentItem(clamp(item_pa, -1, parameters->getNumItems() - 1));
	parameters_changed();
}

void AppSystemLogic::clone_clicked(const WidgetPtr &button, int mbuttons)
{
	// проверяем, выбрано ли какое-либо свойство в иерархии
	int item = properties->getCurrentItem();
	if (item == -1)
		return;
	// клонируем выбранное свойство
	PropertyPtr p = item_prop[item];
	PropertyPtr p_clone = p->clone();
	p_clone->setName(String::format("%s_cloned", p->getName()));

	// обновляем отображаемую информацию
	refresh_info();
}

/// обработчик события on_click кнопки inherit
void AppSystemLogic::inherit_clicked(const WidgetPtr &button, int mbuttons)
{
	// проверяем, выбрано ли какое-либо свойство в иерархии
	int item = properties->getCurrentItem();
	if (item == -1)
		return;
	// наследуем новое свойство от выбранного
	PropertyPtr p = item_prop[item];
	p->inherit()->setName(String::format("%s_inherited", p->getName()));

	// обновляем отображаемую информацию
	refresh_info();
}

/// метод сохранения текущего выбранного свойства в файл "my_test_prop.prop"
void AppSystemLogic::save_prop_clicked(const WidgetPtr &button, int mbuttons)
{
	// проверяем, выбрано ли какое-либо свойство в иерархии
	int item = properties->getCurrentItem();
	if (item == -1)
		return;
	// сохраняем свойство в указанный файл
	PropertyPtr p = item_prop[item];
	p->save("my_test_prop.prop");
}
////////////////////////////////////////////////////////////////////////////////
// начало основного цикла
////////////////////////////////////////////////////////////////////////////////

int AppSystemLogic::update()
{
	// Здесь пишите код, вызываемый перед обновлением каждого кадра рендеринга.
	return 1;
}

int AppSystemLogic::postUpdate()
{
	// Здесь пишите код, вызываемый после обновления каждого кадра рендеринга.
	return 1;
}

////////////////////////////////////////////////////////////////////////////////
// конец основного цикла
////////////////////////////////////////////////////////////////////////////////

int AppSystemLogic::shutdown()
{
	// удаляем все подписки на события где-то при завершении работы
	econnections.disconnectAll();
	return 1;
}

```

</details>


## Property Class

### Методы класса

## Ptr < Node > getNode () const

Returns the current node to which the property is assigned.
### Возвращаемое значение

Current node to which the property is assigned.
## int getNumStructs () const

Returns the current number of structures of the property.
### Возвращаемое значение

Current number of structures of the property.
## Ptr < PropertyParameter > getParameterPtr () const

Returns the current root [property parameter](../../../api/library/common/class.propertyparameter_cpp.md).
You can't iterate through all parameters of the property in a single loop, a recursive function should be used instead:


```cpp
#include <functional>
std::function<void(const PropertyParameterPtr &)> recursive_func = [&, this](const PropertyParameterPtr &p)
{
	for (int i = 0; i < p->getNumChildren(); i++)
	{
		PropertyParameterPtr child = p->getChild(i);

		// сделать что-то... например, вывести имена и значения параметров
		Log::message("- %s: %s \n", child->getName(), child->getValueString().get());

		recursive_func(child);
	}
};

/* ... */
int AppWorldLogic::init() {
	/* ... */

	// получаем корневой параметр свойства
	PropertyParameterPtr root_parameter = property->getParameterPtr();

	// проходим по всем параметрам свойства
	recursive_func(root_parameter);

	return 1;
}

```


### Возвращаемое значение

Current root property parameter smart pointer.
## int getNumChildren () const

Returns the current number of children of the current property.
### Возвращаемое значение

Current number of child properties.
## bool isHierarchyValid () const

Returns the current value indicating if there are no missing parents in the hierarchy of the property.
### Возвращаемое значение

**true** if there are no missing parents in the hierarchy of the property; otherwise **false**.
## void setFileGUID ( const UGUID & guid )

Sets a new GUID of the property file.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - The new [GUID](../../../api/library/filesystem/class.uguid_cpp.md) for the property file.

## const UGUID & getFileGUID () const

Returns the current GUID of the property file.
### Возвращаемое значение

Current new [GUID](../../../api/library/filesystem/class.uguid_cpp.md) for the property file.
## void setFilePath ( const char * path )

Sets a new [path](#name_path) to the property file.
### Аргументы

- *const char ** **path** - The [path](#name_path) to the property file.

## const char * getFilePath () const

Returns the current [path](#name_path) to the property file.
### Возвращаемое значение

Current [path](#name_path) to the property file.
## UGUID getGUID () const

Returns the current GUID of the property.
### Возвращаемое значение

Current GUID of the property.
## void setName ( const char * name )

Sets a new new [name](../../../code/formats/property_format.md#property_name) for the property.
> **Notice:** This method is not available for [manual](#isManual_int) and [non-editable](#isEditable_int) properties.


### Аргументы

- *const char ** **name** - The property [name](../../../code/formats/property_format.md#property_name).

## const char * getName () const

Returns the current new [name](../../../code/formats/property_format.md#property_name) for the property.
> **Notice:** This method is not available for [manual](#isManual_int) and [non-editable](#isEditable_int) properties.


### Возвращаемое значение

Current property [name](../../../code/formats/property_format.md#property_name).
## bool isEngine () const

Returns the current value indicating if the property is engine-related (i.e. required for engine operation). Such properties are stored in the `core`, `editor` and `editor2` folders.
### Возвращаемое значение

**true** if the property is engine-related; otherwise **false**.
## bool isManual () const

Returns the current value indicating if the property is a [manual](../../../principles/properties/index.md#manual) one.
### Возвращаемое значение

**true** if the property is manual; otherwise **false**.
## bool isInternal () const

Returns the current value indicating if the property is an [internal](../../../principles/properties/index.md#internal) one.
### Возвращаемое значение

**true** if the property is internal; otherwise **false**.
## bool isEditable () const

Returns the current value indicating if the property can be [edited](../../../code/formats/property_format.md#property_editable).
### Возвращаемое значение

**true** if the property is editable; otherwise **false**.
## bool isHidden () const

Returns the current value indicating if the property is [hidden](../../../code/formats/property_format.md#property_hidden).
### Возвращаемое значение

**true** if the property is hidden; otherwise **false**.
## bool isBase () const

Returns the current value indicating if the property is a base property.
### Возвращаемое значение

**true** if the property is a base property; otherwise **false**.
## int getID () const

Returns the current identifier of the property.
### Возвращаемое значение

Current property ID.
## Ptr < Property > getParent () const

Returns the current [parent](../../../code/formats/property_format.md#property_parent) property.
### Возвращаемое значение

Current parent property if it exists; if the current property has no parent, nullptr will be returned.
## const char * getTooltip () const

Returns the current tooltip for the property.
### Возвращаемое значение

Current tooltip for the property.
## int getNumInterfaces () const

Returns the current total number of interfaces.
> **Notice:** You can use interfaces only within the C# Component System. For more information, see the article [C# Interfaces and Abstract Classes.](../../../code/csharp/interfaces_and_abstract_classes.md).

### Возвращаемое значение

Current total number of interfaces.
## Event<const Ptr < Property > &> getEventDestroy () const

Событие, вызываемое при уничтожении свойства. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Property> & **property**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Destroy
void destroy_event_handler(const Ptr<Property> & property)
{
	Log::message("\Обработка события Destroy\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections destroy_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventDestroy().connect(destroy_event_connections, destroy_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventDestroy().connect(destroy_event_connections, [](const Ptr<Property> & property) {
		Log::message("\Обработка события Destroy (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
destroy_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection destroy_event_connection;

// подписываемся на событие Destroy с функцией-обработчиком, сохраняя соединение
publisher->getEventDestroy().connect(destroy_event_connection, destroy_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
destroy_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
destroy_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Destroy через соединение
destroy_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события Destroy, реализованный как член класса
	void event_handler(const Ptr<Property> & property)
	{
		Log::message("\Обработка события Destroy\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventDestroy().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId destroy_handler_id;

// подписываемся на событие Destroy с лямбда-обработчиком, сохраняя идентификатор соединения
destroy_handler_id = publisher->getEventDestroy().connect(e_connections, [](const Ptr<Property> & property) {
		Log::message("\Обработка события Destroy (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventDestroy().disconnect(destroy_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Destroy при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventDestroy().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventDestroy().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < Property > &, int> getEventParameterChanged () const

Событие, вызываемое при изменении или сбросе к значению по умолчанию любого параметра свойства. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Property> & **property**, int **param_index**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события ParameterChanged
void parameterchanged_event_handler(const Ptr<Property> & property,  int param_index)
{
	Log::message("\Обработка события ParameterChanged\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections parameterchanged_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventParameterChanged().connect(parameterchanged_event_connections, parameterchanged_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventParameterChanged().connect(parameterchanged_event_connections, [](const Ptr<Property> & property,  int param_index) {
		Log::message("\Обработка события ParameterChanged (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
parameterchanged_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection parameterchanged_event_connection;

// подписываемся на событие ParameterChanged с функцией-обработчиком, сохраняя соединение
publisher->getEventParameterChanged().connect(parameterchanged_event_connection, parameterchanged_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
parameterchanged_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
parameterchanged_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие ParameterChanged через соединение
parameterchanged_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события ParameterChanged, реализованный как член класса
	void event_handler(const Ptr<Property> & property,  int param_index)
	{
		Log::message("\Обработка события ParameterChanged\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventParameterChanged().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId parameterchanged_handler_id;

// подписываемся на событие ParameterChanged с лямбда-обработчиком, сохраняя идентификатор соединения
parameterchanged_handler_id = publisher->getEventParameterChanged().connect(e_connections, [](const Ptr<Property> & property,  int param_index) {
		Log::message("\Обработка события ParameterChanged (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventParameterChanged().disconnect(parameterchanged_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий ParameterChanged при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventParameterChanged().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventParameterChanged().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < Property > &> getEventReparented () const

Событие, вызываемое при изменении родителя свойства. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Property> & **property**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Reparented
void reparented_event_handler(const Ptr<Property> & property)
{
	Log::message("\Обработка события Reparented\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections reparented_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventReparented().connect(reparented_event_connections, reparented_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventReparented().connect(reparented_event_connections, [](const Ptr<Property> & property) {
		Log::message("\Обработка события Reparented (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
reparented_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection reparented_event_connection;

// подписываемся на событие Reparented с функцией-обработчиком, сохраняя соединение
publisher->getEventReparented().connect(reparented_event_connection, reparented_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
reparented_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
reparented_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Reparented через соединение
reparented_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события Reparented, реализованный как член класса
	void event_handler(const Ptr<Property> & property)
	{
		Log::message("\Обработка события Reparented\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventReparented().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId reparented_handler_id;

// подписываемся на событие Reparented с лямбда-обработчиком, сохраняя идентификатор соединения
reparented_handler_id = publisher->getEventReparented().connect(e_connections, [](const Ptr<Property> & property) {
		Log::message("\Обработка события Reparented (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventReparented().disconnect(reparented_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Reparented при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventReparented().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventReparented().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < Property > &> getEventRenamed () const

Событие, вызываемое при изменении [name](#name_path) свойства. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Property> & **property**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Renamed
void renamed_event_handler(const Ptr<Property> & property)
{
	Log::message("\Обработка события Renamed\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections renamed_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventRenamed().connect(renamed_event_connections, renamed_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventRenamed().connect(renamed_event_connections, [](const Ptr<Property> & property) {
		Log::message("\Обработка события Renamed (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
renamed_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection renamed_event_connection;

// подписываемся на событие Renamed с функцией-обработчиком, сохраняя соединение
publisher->getEventRenamed().connect(renamed_event_connection, renamed_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
renamed_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
renamed_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Renamed через соединение
renamed_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события Renamed, реализованный как член класса
	void event_handler(const Ptr<Property> & property)
	{
		Log::message("\Обработка события Renamed\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventRenamed().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId renamed_handler_id;

// подписываемся на событие Renamed с лямбда-обработчиком, сохраняя идентификатор соединения
renamed_handler_id = publisher->getEventRenamed().connect(e_connections, [](const Ptr<Property> & property) {
		Log::message("\Обработка события Renamed (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventRenamed().disconnect(renamed_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Renamed при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventRenamed().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventRenamed().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < Property > &> getEventMoved () const

Событие, вызываемое при изменении [path](#name_path) свойства. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Property> & **property**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Moved
void moved_event_handler(const Ptr<Property> & property)
{
	Log::message("\Обработка события Moved\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections moved_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventMoved().connect(moved_event_connections, moved_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventMoved().connect(moved_event_connections, [](const Ptr<Property> & property) {
		Log::message("\Обработка события Moved (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
moved_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection moved_event_connection;

// подписываемся на событие Moved с функцией-обработчиком, сохраняя соединение
publisher->getEventMoved().connect(moved_event_connection, moved_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
moved_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
moved_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Moved через соединение
moved_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события Moved, реализованный как член класса
	void event_handler(const Ptr<Property> & property)
	{
		Log::message("\Обработка события Moved\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventMoved().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId moved_handler_id;

// подписываемся на событие Moved с лямбда-обработчиком, сохраняя идентификатор соединения
moved_handler_id = publisher->getEventMoved().connect(e_connections, [](const Ptr<Property> & property) {
		Log::message("\Обработка события Moved (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventMoved().disconnect(moved_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Moved при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventMoved().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventMoved().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < Property > &> getEventReloaded () const

Событие, вызываемое при перезагрузке свойства. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Property> & **property**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Reloaded
void reloaded_event_handler(const Ptr<Property> & property)
{
	Log::message("\Обработка события Reloaded\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections reloaded_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventReloaded().connect(reloaded_event_connections, reloaded_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventReloaded().connect(reloaded_event_connections, [](const Ptr<Property> & property) {
		Log::message("\Обработка события Reloaded (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
reloaded_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection reloaded_event_connection;

// подписываемся на событие Reloaded с функцией-обработчиком, сохраняя соединение
publisher->getEventReloaded().connect(reloaded_event_connection, reloaded_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
reloaded_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
reloaded_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Reloaded через соединение
reloaded_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события Reloaded, реализованный как член класса
	void event_handler(const Ptr<Property> & property)
	{
		Log::message("\Обработка события Reloaded\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventReloaded().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId reloaded_handler_id;

// подписываемся на событие Reloaded с лямбда-обработчиком, сохраняя идентификатор соединения
reloaded_handler_id = publisher->getEventReloaded().connect(e_connections, [](const Ptr<Property> & property) {
		Log::message("\Обработка события Reloaded (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventReloaded().disconnect(reloaded_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Reloaded при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventReloaded().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventReloaded().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
---

## static PropertyPtr create ( )

Конструктор. Создаёт новый экземпляр свойства.
## Ptr < Property > getChild ( int num ) const

Возвращает дочернее свойство текущего свойства.
### Аргументы

- *int* **num** - Номер целевого дочернего свойства.

### Возвращаемое значение

Дочернее свойство.
## void setEditable ( int editable )

Задаёт значение, указывающее, можно ли [edited](../../../code/formats/property_format.md#property_editable) свойство.
### Аргументы

- *int* **editable** - 1, чтобы сделать свойство редактируемым; 0, чтобы сделать его только для чтения.

## bool hasOverrides ( ) const

Возвращает значение, указывающее, имеет ли свойство хотя бы один переопределённый параметр.
### Возвращаемое значение

true, если свойство имеет хотя бы один переопределённый параметр; иначе false.
## bool isParent ( const char * name ) const

Возвращает значение, указывающее, является ли свойство с указанным именем [parent](../../../code/formats/property_format.md#property_parent) данного свойства.
Предположим, у нас в проекте есть следующие два ручных свойства:


- ```xml <?xml version="1.0" encoding="utf-8"?> <property version="2.7.3" name="my_prop" parent_name="surface_base" manual="1"> <parameter name="my_parameter">100</parameter> </property> ```
- ```xml <?xml version="1.0" encoding="utf-8"?> <property version="2.7.3" name="my_prop_0" parent_name="my_prop" manual="1"> <parameter name="my_parameter1">101</parameter> <parameter name="my_parameter2">101</parameter> </property> ```


Следующий код вернёт 1, поскольку свойство *my_prop* является родителем свойства *my_prop_0*:


```cpp
// получаем свойство с именем my_prop_0
PropertyPtr property = Properties::findManualProperty("my_prop_0");
// выполняем проверку родителя
Log::message("%d\n",property->isParent("my_prop"));

```


### Аргументы

- *const char ** **name** - Имя родительского свойства.

### Возвращаемое значение

true, если свойство с указанным именем является родителем данного свойства; иначе false.
## bool isParent ( const UGUID & guid ) const

Возвращает значение, указывающее, является ли свойство с указанным GUID [parent](../../../code/formats/property_format.md#property_parent) данного свойства.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - GUID родительского свойства.

### Возвращаемое значение

true, если свойство с указанным GUID является родителем данного свойства; иначе false.
## int setParent ( const Ptr < Property > & property , bool save_all_values = 0 )

Задаёт указанное свойство как родителя для данного свойства и сохраняет значения параметров свойства (если установлен соответствующий флаг).
> **Notice:** Метод недоступен для [manual](#isManual_int) и [non-editable](#isEditable_int) свойств.


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Property](../../../api/library/common/class.property_cpp.md)> &* **property** - Свойство, задаваемое как родитель для данного свойства.
- *bool* **save_all_values** - Флаг, указывающий, будут ли сохранены значения параметров свойства после смены родителя.

### Возвращаемое значение

1, если указанное свойство успешно задано как родитель для данного свойства; иначе 0.
## Ptr < Property > clone ( )

Клонирует свойство. Клонированное свойство не будет иметь имени, пути и не будет отображаться в иерархии свойств.
### Возвращаемое значение

Умный указатель на клонированное свойство.
## Ptr < Property > clone ( const char * name , const char * path )

Клонирует свойство и присваивает клону указанные имя и путь. Клонированное свойство будет сохранено по указанному пути при вызове *[saveProperties()](../../../api/library/engine/class.properties_cpp.md#saveProperties_int)*. Этот метод можно использовать, например, для создания свойства, пропущенного во время миграции проекта.
### Аргументы

- *const char ** **name** - Имя клонированного свойства.
- *const char ** **path** - Путь для сохранения клонированного свойства.

### Возвращаемое значение

Умный указатель на клонированное свойство.
## Ptr < Property > clone ( const char * name , const char * path , const UGUID & guid )

Клонирует свойство и присваивает клону указанные имя, GUID и путь. Клонированное свойство будет сохранено по указанному пути при вызове *[saveProperties()](../../../api/library/engine/class.properties_cpp.md#saveProperties_int)*. Этот метод можно использовать, например, для создания свойства, пропущенного во время миграции проекта.
### Аргументы

- *const char ** **name** - Имя клонированного свойства.
- *const char ** **path** - Путь для сохранения клонированного свойства.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) клонированного свойства.

### Возвращаемое значение

Умный указатель на клонированное свойство.
## Ptr < Property > clone ( const char * name )

Клонирует свойство.
```cpp
// получаем свойство для клонирования
PropertyPtr property = Properties::findProperty("surface_base_0");
// клонируем свойство
PropertyPtr cloned = property->clone("cloned_surface_base_0");
// выполняем что-то с клонированным указателем
// ...
// удаляем указатель
cloned.grab();
cloned.destroy();

```


### Аргументы

- *const char ** **name** - Имя клонированного свойства.

### Возвращаемое значение

Умный указатель на клонированное свойство.
## Ptr < Property > inherit ( )

Наследует новое свойство от данного. Наследуемое свойство будет пустым: у него не будет имени, пути, и оно не будет отображаться в иерархии свойств.
### Возвращаемое значение

Умный указатель на наследуемое свойство.
## Ptr < Property > inherit ( const char * name )

Наследует новое свойство от данного и присваивает ему указанное имя.
### Аргументы

- *const char ** **name** - Имя наследуемого свойства.

### Возвращаемое значение

Умный указатель на наследуемое свойство.
## Ptr < Property > inherit ( const char * name , const char * path )

Наследует новое свойство от данного и присваивает ему указанные имя и путь. Наследуемое свойство будет сохранено по указанному пути при вызове *[saveProperties()](../../../api/library/engine/class.properties_cpp.md#saveProperties_int)*.
### Аргументы

- *const char ** **name** - Имя наследуемого свойства.
- *const char ** **path** - Путь для сохранения наследуемого свойства.

### Возвращаемое значение

Умный указатель на наследуемое свойство.
## Ptr < Property > inherit ( const char * name , const char * path , const UGUID & guid )

Наследует новое свойство от данного и присваивает ему указанные имя, GUID и путь. Наследуемое свойство будет сохранено по указанному пути при вызове *[saveProperties()](../../../api/library/engine/class.properties_cpp.md#saveProperties_int)*.
### Аргументы

- *const char ** **name** - Имя наследуемого свойства.
- *const char ** **path** - Путь для сохранения наследуемого свойства.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) наследуемого свойства.

### Возвращаемое значение

Умный указатель на наследуемое свойство.
## bool load ( )

Загружает свойство из файла, указанного функцией *[setFilePath()](#setFilePath_cstr_void)*.
> **Notice:** Эту функцию можно использовать для загрузки свойств, созданных во время выполнения приложения или хранящихся вне директории `data`.


### Возвращаемое значение

true, если данные свойства успешно загружены; иначе false.
## bool load ( const char * path )

Загружает свойство из указанного [`*.prop` file](../../../code/formats/property_format.md).
### Аргументы

- *const char ** **path** - Путь к файлу `*.prop`, из которого загружаются данные свойства.

### Возвращаемое значение

true, если данные свойства успешно загружены; иначе false.
## bool loadXml ( const Ptr < Xml > & xml )

Загружает данные свойства (все его параметры) из указанного экземпляра класса Xml.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../api/library/common/class.xml_cpp.md)> &* **xml** - Экземпляр [Xml class](../../../api/library/common/class.xml_cpp.md), в котором хранятся данные свойства.

### Возвращаемое значение

true, если данные свойства успешно загружены; иначе false.
## bool loadWorld ( const Ptr < Xml > & xml )

Загружает данные текущего свойства (все его опции, состояния и параметры) из указанного экземпляра класса Xml.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../api/library/common/class.xml_cpp.md)> &* **xml** - Экземпляр [Xml class](../../../api/library/common/class.xml_cpp.md), в котором хранятся данные свойства.

### Возвращаемое значение

true, если данные свойства успешно загружены; иначе false.
## bool reload ( )

Перезагружает свойство и все его дочерние элементы.
### Возвращаемое значение

true, если свойство успешно перезагружено; иначе false.
## bool canSaveInFile ( ) const

Возвращает значение, указывающее, можно ли сохранить свойство в файл. Например, эта функция вернёт 0 для [internal](#isInternal_int) или [manual](#isManual_int) свойства.
### Возвращаемое значение

true, если свойство можно сохранить в файл; иначе false.
## bool saveState ( const Ptr < Stream > & stream ) const

Сохраняет данные текущего свойства (все его параметры) в бинарный поток.
**Пример** использования методов saveState() и [restoreState()](#restoreState_Stream_int_int):


```cpp
// где-то в коде

// получаем ручное свойство с именем "my_prop" через Property Manager
PropertyPtr property = Properties::findManualProperty("my_prop");
property->setParameterInt(property->findParameter("my_int_param"), 3);

// сохраняем состояние
Blob blob_state = new Blob();
property.SaveState(blob_state);

// изменяем состояние
property->setParameterInt(property->findParameter("my_int_param"), 4);

// восстанавливаем состояние
blob_state.SeekSet(0);	// возвращаем каретку в начало blob
propertyparam1.RestoreState(blob_state, 0);

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, в который будут сохранены данные свойства.

### Возвращаемое значение

true, если данные свойства успешно сохранены; иначе false.
## bool restoreState ( const Ptr < Stream > & stream , int restore_mode = 0 )

Восстанавливает данные свойства (все его параметры) из бинарного потока в указанном режиме.
**Пример** использования методов [saveState()](#saveState_Stream_int) и restoreState():


```cpp
// где-то в коде

// получаем ручное свойство с именем "my_prop" через Property Manager
PropertyPtr property = Properties::findManualProperty("my_prop");
property->setParameterInt(property->findParameter("my_int_param"), 3);

// сохраняем состояние
Blob blob_state = new Blob();
property.SaveState(blob_state);

// изменяем состояние
property->setParameterInt(property->findParameter("my_int_param"), 4);

// восстанавливаем состояние
blob_state.SeekSet(0);	// возвращаем каретку в начало blob
propertyparam1.RestoreState(blob_state, 0);

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, в котором хранятся сохранённые данные параметров свойства.
- *int* **restore_mode** - Режим восстановления. Одно из значений [Property::RESTORE_MODE_*](#RESTORE_MODE_MERGE). Значение по умолчанию — [Property::RESTORE_MODE_REPLACE](#RESTORE_MODE_REPLACE).

### Возвращаемое значение

true при успехе; иначе false.
## bool save ( )

Сохраняет данные свойства в файл, указанный функцией *[setFilePath()](#setFilePath_cstr_void)*.
> **Notice:** Этот метод недоступен для [manual](#isManual_int) и [internal](#isInternal_int) свойств.


### Возвращаемое значение

true, если данные свойства успешно сохранены; иначе false.
## bool save ( const char * path )

Сохраняет данные свойства в указанный [`*.prop` file](../../../code/formats/property_format.md).
> **Notice:** Этот метод недоступен для [manual](#isManual_int) свойств.


### Аргументы

- *const char ** **path** - Путь к файлу `*.prop`, в который сохраняются данные свойства.

### Возвращаемое значение

true, если данные свойства успешно сохранены; иначе false.
## bool saveXml ( const Ptr < Xml > & xml ) const

Сохраняет данные свойства (все его параметры) в указанный экземпляр класса Xml.
> **Notice:** Этот метод недоступен для [manual](#isManual_int) свойств.


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../api/library/common/class.xml_cpp.md)> &* **xml** - Экземпляр [Xml class](../../../api/library/common/class.xml_cpp.md), в который будут сохранены данные свойства.

### Возвращаемое значение

true, если данные свойства успешно сохранены; иначе false.
## bool saveWorld ( const Ptr < Xml > & xml , int force = 0 ) const

Сохраняет данные текущего свойства (все его параметры) в указанный экземпляр класса Xml.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../api/library/common/class.xml_cpp.md)> &* **xml** - Экземпляр [Xml class](../../../api/library/common/class.xml_cpp.md), в который будут сохранены данные свойства.
- *int* **force** - Значение, указывающее, используется ли принудительное сохранение данных свойства: 1, чтобы включить принудительное сохранение, 0, чтобы отключить его.

### Возвращаемое значение

true, если данные свойства успешно сохранены; иначе false.
## int parameterTypeByName ( const char * param_type ) const

Возвращает идентификатор типа параметра по указанному имени типа.
### Аргументы

- *const char ** **param_type** - Имя типа параметра.

### Возвращаемое значение

Идентификатор типа параметра, одно из значений [PARAMETER_*](#PARAMETER_COLOR).
## const char * parameterNameByType ( int param_type ) const

Возвращает имя типа параметра по указанному идентификатору типа.
### Аргументы

- *int* **param_type** - Идентификатор типа параметра, одно из значений [PARAMETER_*](#PARAMETER_COLOR).

### Возвращаемое значение

Имя типа параметра.
## Ptr < PropertyParameter > getParameterPtr ( const char * name )

Возвращает [property parameter](../../../api/library/common/class.propertyparameter_cpp.md) по его имени.
### Аргументы

- *const char ** **name** - Имя параметра свойства.

### Возвращаемое значение

Умный указатель на параметр свойства.
> **Notice:** Этот метод никогда не возвращает nullptr, независимо от того, существует ли параметр с указанным именем. Он лишь выводит сообщение об ошибке в консоль в случае несуществующего параметра. Чтобы проверить, действительно ли такой параметр существует, используйте метод [*PropertyParameter.isExist()*](../../../api/library/common/class.propertyparameter_cpp.md#isExist_int). Например:
> ```cpp
> // получаем некоторое свойство с именем "my_property"
> PropertyPtr pProperty = Properties::findManualProperty("my_property");
>
> // пытаемся получить параметр свойства с именем "some_parameter"
> PropertyParameterPtr param = pProperty->getParameterPtr("some_parameter");
>
> // проверяем, существует ли такой параметр, и выводим сообщение
> if (param->isExist())
> 	Log::message("Specified property parameter exists!\n");
> else
> 	Log::message("No such parameter!\n");
>
> ```


## Ptr < PropertyParameter > getParameterPtr ( int id )

Возвращает [property parameter](../../../api/library/common/class.propertyparameter_cpp.md) по его идентификатору.
### Аргументы

- *int* **id** - Идентификатор параметра свойства.

### Возвращаемое значение

Умный указатель на параметр свойства.
> **Notice:** Этот метод никогда не возвращает nullptr, независимо от того, существует ли параметр с указанным идентификатором. Он лишь выводит сообщение об ошибке в консоль в случае несуществующего параметра. Чтобы проверить, действительно ли такой параметр существует, используйте метод [*PropertyParameter.isExist()*](../../../api/library/common/class.propertyparameter_cpp.md#isExist_int). Например:
> ```cpp
> // получаем некоторое свойство с именем "my_property"
> PropertyPtr pProperty = Properties::findManualProperty("my_property");
>
> // пытаемся получить параметр свойства с идентификатором ID=30
> PropertyParameterPtr param = pProperty->getParameterPtr(30);
>
> // проверяем, существует ли такой параметр, и выводим сообщение
> if (param->isExist())
> 	Log::message("Property parameter with the specified ID exists!\n");
> else
> 	Log::message("No such parameter!\n");
>
> ```


## int findStruct ( const char * name ) const

Возвращает номер структуры с указанным именем.
### Аргументы

- *const char ** **name** - Имя искомой структуры.

### Возвращаемое значение

Номер структуры с указанным именем, если она существует; иначе -1.
## const char * getStructName ( int num ) const

Возвращает имя структуры с указанным номером.
### Аргументы

- *int* **num** - Номер структуры.

### Возвращаемое значение

Имя структуры, если такая структура существует, иначе nullptr.
## const char * getInterfaceName ( int num ) const

Возвращает имя интерфейса с указанным номером.
> **Notice:** Интерфейсы можно использовать только в компонентной системе на C#. Подробнее см. статью [C# Interfaces and Abstract Classes.](../../../code/csharp/interfaces_and_abstract_classes.md).

### Аргументы

- *int* **num** - Номер интерфейса.

### Возвращаемое значение

Имя интерфейса, если такой интерфейс существует, иначе nullptr.
