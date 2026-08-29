# Unigine::Plugins::SpiderVision::EasyBlendData Class (CPP)

**Header:** #include <plugins/Unigine/SpiderVision/UnigineSpiderVision.h>


Этот класс управляет данными, созданными в *EasyBlend* для настройки проекций. Экземпляр этого класса хранит меш, созданный на основе файла `*.ol`, для соответствующего изменения изображения viewport.


Этот объект доступен через соответствующий метод класса [ViewportData](../../../../api/library/plugins/spidervision/class.viewportdata_cpp.md#getEasyblendData_EasyBlendData).


Поддерживаемая версия *EasyBlend SDK* — *Scalable 7.0*.


Данные цветокоррекции хранятся в [configuration file](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#config_file).


## EasyBlendData Class

### Методы класса

---

## bool loadFile ( const char * filepath )

Загружает настройки EasyBlend из файла.
### Аргументы

- *const char ** **filepath** - Путь к файлу настроек EasyBlend.

### Возвращаемое значение

true, если настройки EasyBlend успешно загружены; иначе false.
## void clear ( )

Очищает настройки EasyBlend.
## bool isLoaded ( ) const

Возвращает значение, указывающее, загружены ли настройки EasyBlend.
### Возвращаемое значение

true, если настройки EasyBlend загружены; иначе false.
## String getFilePath ( ) const

Возвращает путь к файлу настроек EasyBlend.
### Возвращаемое значение

Путь к файлу настроек EasyBlend.
## Ptr < MeshDynamic > getMesh ( ) const

Возвращает динамический меш, представляющий настройки EasyBlend.
### Возвращаемое значение

Динамический меш, представляющий настройки EasyBlend.
## void saveXml ( const Ptr < Xml > & xml )

Сохраняет данные EasyBlend в указанный экземпляр класса Xml.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../../api/library/common/class.xml_cpp.md)> &* **xml** - Экземпляр [Xml class](../../../../api/library/common/class.xml_cpp.md), в который будут сохранены данные.

## bool restoreXml ( const Ptr < Xml > & xml )

Загружает данные EasyBlend из указанного экземпляра класса Xml.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../../api/library/common/class.xml_cpp.md)> &* **xml** - Экземпляр [Xml class](../../../../api/library/common/class.xml_cpp.md), из которого загружаются данные.

### Возвращаемое значение

true, если данные успешно загружены; иначе false.
## void save ( const Ptr < Stream > & stream )

Сохраняет данные EasyBlend в указанный поток.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, в который записываются данные.

## void restore ( const Ptr < Stream > & stream )

Загружает данные EasyBlend из указанного потока.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, из которого загружаются данные.

## void applyData ( ViewportData * OUT_data )

Применяет настройки EasyBlend к данным viewport.
### Аргументы

- *[ViewportData](../../../../api/library/plugins/spidervision/class.viewportdata_cpp.md) ** **OUT_data** - Экземпляр [ViewportData class](../../../../api/library/plugins/spidervision/class.viewportdata_cpp.md), хранящий данные viewport. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.
