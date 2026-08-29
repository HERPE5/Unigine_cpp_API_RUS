# Класс Unigine::Config (CPP)

**Заголовочный файл:** #include <UnigineConfig.h>

> **Примечание:** Этот класс является одиночкой (singleton).


Класс **Config** используется для чтения значений (настроек) из [application configuration file](../../../code/configuration_file_cpp.md#config) (по умолчанию `configs/default.config`) и записи их обратно.


Используйте соответствующие методы в зависимости от типа целевого элемента. Например, чтобы получить значения следующих элементов, следует использовать методы *getInt()* и *getString()* соответственно:

```xml
...
<item name="show_fps" type="int">1</item>
<item name="system_script" type="string">unigine_project/unigine.usc</item>
...

```


### Пример использования


С помощью класса Config вы можете сохранять пользовательские настройки в файл конфигурации и затем восстанавливать их при необходимости. Например:


<details>
<summary>AppSystemLogic.h | Close</summary>

`AppSystemLogic.h`


```cpp
#ifndef __APP_SYSTEM_LOGIC_H__
#define __APP_SYSTEM_LOGIC_H__

#include <UnigineLogic.h>

class AppSystemLogic : public Unigine::SystemLogic
{
public:
	AppSystemLogic();
	~AppSystemLogic() override;

	int init() override;

	int update() override;
	int postUpdate() override;

	int shutdown() override;

private:
	Unigine::String player_avatar;
	bool skip_cutscenes;
	bool blood_enabled;
	int bulletshell_lifetime;
};

#endif // __APP_SYSTEM_LOGIC_H__

```

</details>


<details>
<summary>AppSystemLogic.cpp | Close</summary>

`AppSystemLogic.cpp`


```cpp
#include "AppSystemLogic.h"
#include <UnigineConfig.h>

using namespace Unigine;

/*...*/

int AppSystemLogic::init() {

	// читаем пользовательские настройки из файла конфигурации
	player_avatar = Config::getString("player_avatar", "soldier1");
	skip_cutscenes = Config::getBool("skip_cutscenes", false);
	blood_enabled = Config::getBool("blood_enabled", false);
	bulletshell_lifetime = Config::getInt("bulletshell_lifetime", 100);

	return 1;
}

int AppSystemLogic::shutdown() {

	// автоматически сохраняем файл конфигурации при завершении работы
	Config::setAutosave(true);

	// записываем пользовательские настройки в файл конфигурации
	Config::setString("player_avatar", player_avatar.get());
	Config::setBool("skip_cutscenes", skip_cutscenes);
	Config::setBool("blood_enabled", blood_enabled);
	Config::setInt("bulletshell_lifetime", bulletshell_lifetime);
	// сохраняем данные в пользовательский файл конфигурации, отличный от файла по умолчанию
	Config::setPath("configs/my.config");
	Config::save();

	return 1;
}

```

</details>


### См. также


- Статья [Configuration Files](../../../code/configuration_file_cpp.md).


## Класс Config

### Методы класса

---

## static void setBool ( const char * name , int value )

Устанавливает значение заданной булевой настройки. Если настройка с этим именем уже существует, её значение перезаписывается.
### Аргументы

- *const char ** **name** - Имя настройки.
- *int* **value** - Булево значение (**0** или **1**). **0** означает *false*, **1** означает *true*.

## static int getBool ( const char * name )

Читает значение заданной булевой настройки.
### Аргументы

- *const char ** **name** - Имя настройки.

### Возвращаемое значение

Булево значение (**0** или **1**) настройки. **0** означает *false*, **1** означает *true*.
## static int getBool ( const char * name , int value )

Читает значение заданной булевой настройки. Возвращает значение, указанное вторым аргументом, если настройка не найдена.
### Аргументы

- *const char ** **name** - Имя настройки.
- *int* **value** - Пользовательское значение, возвращаемое, если настройка не найдена.

### Возвращаемое значение

Булево значение (**0** или **1**) настройки. **0** означает *false*, **1** означает *true*.
## static int isExist ( const char * name )

Проверяет, существует ли настройка с заданным именем.
### Аргументы

- *const char ** **name** - Имя настройки.

### Возвращаемое значение

**1**, если настройка существует; иначе **0**.
## static void setFloat ( const char * name , float value )

Устанавливает значение заданной настройки с плавающей точкой. Если настройка с этим именем уже существует, её значение перезаписывается.
### Аргументы

- *const char ** **name** - Имя настройки.
- *float* **value** - Значение настройки с плавающей точкой.

## static float getFloat ( const char * name , float value )

Читает значение заданной настройки с плавающей точкой. Возвращает значение, указанное вторым аргументом, если настройка не найдена.
### Аргументы

- *const char ** **name** - Имя настройки.
- *float* **value** - Пользовательское значение, возвращаемое, если настройка не найдена.

### Возвращаемое значение

Значение настройки с плавающей точкой.
## static float getFloat ( const char * name )

Читает значение заданной настройки с плавающей точкой.
### Аргументы

- *const char ** **name** - Имя настройки.

### Возвращаемое значение

Значение настройки с плавающей точкой.
## static void setInt ( const char * name , int value )

Устанавливает значение заданной целочисленной настройки. Если настройка с этим именем уже существует, её значение перезаписывается.
### Аргументы

- *const char ** **name** - Имя настройки.
- *int* **value** - Целочисленное значение настройки.

## static int getInt ( const char * name )

Читает значение заданной целочисленной настройки.
### Аргументы

- *const char ** **name** - Имя настройки.

### Возвращаемое значение

Целочисленное значение настройки.
## static int getInt ( const char * name , int value )

Читает значение заданной целочисленной настройки. Возвращает значение, указанное вторым аргументом, если настройка не найдена.
### Аргументы

- *const char ** **name** - Имя настройки.
- *int* **value** - Пользовательское значение, возвращаемое, если настройка не найдена.

### Возвращаемое значение

Целочисленное значение настройки.
## static void setString ( const char * name , const char * value )

Устанавливает значение заданной строковой настройки. Если настройка с этим именем уже существует, её значение перезаписывается.
### Аргументы

- *const char ** **name** - Имя настройки.
- *const char ** **value** - Строковое значение настройки.

## static const char * getString ( const char * name , const char * value )

Читает значение заданной строковой настройки. Возвращает значение, указанное вторым аргументом, если настройка не найдена.
### Аргументы

- *const char ** **name** - Имя настройки.
- *const char ** **value** - Пользовательское значение, возвращаемое, если настройка найдена.

### Возвращаемое значение

Строковое значение настройки.
## static const char * getString ( const char * name )

Читает значение заданной строковой настройки.
### Аргументы

- *const char ** **name** - Имя настройки.

### Возвращаемое значение

Строковое значение настройки.
## static int load ( )

***Console*:**`config_load`Загружает конфигурацию из файла. Чтобы изменить путь к файлу конфигурации, используйте метод [*setPath()*](#setPath_cstr_void).
### Возвращаемое значение

**true**, если конфигурация успешно загружена из файла; иначе **false**.
## static void remove ( const char * name )

Удаляет настройку с заданным именем из файла конфигурации.
### Аргументы

- *const char ** **name** - Имя настройки.

## static int save ( )

***Console*:**`config_save`Сохраняет текущую конфигурацию в файл. Чтобы изменить путь к файлу конфигурации, используйте метод [*setPath()*](#setPath_cstr_void).
### Возвращаемое значение

**true**, если текущая конфигурация успешно сохранена в файл; иначе **false**.
## static void setPath ( const char * path )

***Console*:**`config`Устанавливает новый путь к файлу конфигурации движка (по умолчанию: `configs/default.config`). Путь может быть указан как абсолютный или относительно папки *[*-data_path*](../../../code/command_line.md#data_path)* или *<project_name>*, если задан *[*-project_name*](../../../code/command_line.md#project_name)*. Этот параметр хранится в следующем файле конфигурации: **[*.boot](../../../code/configuration_file_cpp.md#boot)**.
### Аргументы

- *const char ** **path** - Новый путь к файлу конфигурации движка, который нужно установить.

## static const char * getPath ( ) const

***Console*:**`config`Возвращает текущий путь к файлу конфигурации движка (по умолчанию: `configs/default.config`). Этот параметр хранится в следующем файле конфигурации: **[*.boot](../../../code/configuration_file_cpp.md#boot)**.
### Возвращаемое значение

Текущий путь к файлу конфигурации движка.
## static void setAutosave ( bool autosave )

***Console*:**`config_autosave`Устанавливает значение, указывающее, сохраняются ли текущие настройки конфигурации движка автоматически в соответствующий файл конфигурации при загрузке, закрытии и сохранении мира, а также при завершении работы движка.
### Аргументы

- *bool* **autosave** - true — включить автоматическое сохранение текущих настроек конфигурации движка; false — отключить.

## static bool isAutosave ( ) const

***Console*:**`config_autosave`Возвращает значение, указывающее, сохраняются ли текущие настройки конфигурации движка автоматически в соответствующий файл конфигурации при загрузке, закрытии и сохранении мира, а также при завершении работы движка.
### Возвращаемое значение

true, если автоматическое сохранение текущих настроек конфигурации движка включено; иначе 0.
