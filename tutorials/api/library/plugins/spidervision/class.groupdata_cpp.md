# Unigine::Plugins::SpiderVision::GroupData Class (CPP)

**Header:** #include <plugins/Unigine/SpiderVision/UnigineSpiderVision.h>


Этот класс хранит настройки группы viewport, расположенных согласно заданному шаблону.


Данные цветокоррекции хранятся в [configuration file](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#config_file).


Этот объект доступен через соответствующий метод класса [DisplaysConfig](../../../../api/library/plugins/spidervision/class.displaysconfig_cpp.md#getGroupByIndex_int_GroupData).


## GroupData Class

### Перечисления

## GROUP_TYPE

| Name | Description |
|---|---|
| **WALL** = 0 | Настенная многоканальная конфигурация визуализации. |

### Методы класса

## int getID () const

Возвращает текущий ID группы viewport.
### Возвращаемое значение

Текущий ID группы viewport.
## GroupData::GROUP_TYPE getType () const

Возвращает текущий тип группы viewport.
### Возвращаемое значение

Текущий тип группы viewport.
## void setName ( const char * name )

Задаёт новое имя группы viewport.
### Аргументы

- *const char ** **name** - Имя группы viewport.

## String getName () const

Возвращает текущее имя группы viewport.
### Возвращаемое значение

Текущее имя группы viewport.
---

## void saveXml ( const Ptr < Xml > & xml )

Сохраняет данные группы viewport в указанный экземпляр класса Xml.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../../api/library/common/class.xml_cpp.md)> &* **xml** - Экземпляр [Xml class](../../../../api/library/common/class.xml_cpp.md), в который будут сохранены данные.

## bool restoreXml ( const Ptr < Xml > & xml )

Загружает данные группы viewport из указанного экземпляра класса Xml.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../../api/library/common/class.xml_cpp.md)> &* **xml** - Экземпляр [Xml class](../../../../api/library/common/class.xml_cpp.md), из которого загружаются данные.

### Возвращаемое значение

true, если данные успешно загружены; иначе false.
## void save ( const Ptr < Stream > & stream )

Сохраняет данные группы viewport в указанный поток.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, в который записываются данные.

## void restore ( const Ptr < Stream > & stream )

Загружает данные группы viewport из указанного потока.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, из которого загружаются данные.
