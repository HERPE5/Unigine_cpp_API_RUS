# Класс Unigine.BootConfig (CPP)

**Заголовочный файл:** #include <UnigineConfig.h>

> **Примечание:** Этот класс является одиночкой (singleton).


Одиночка, управляющий [startup configuration](../../../code/configuration_file_cpp.md#boot) движка и позволяющий настраивать [boot screen](../../../code/gui/screens/index.md#boot).


> **Примечание:** Шрифты, текстуры или любые другие ресурсы, используемые на экране загрузки, **не могут быть упакованы в архив UNG**.


### Пример использования


С помощью класса BootConfig вы можете настроить экран загрузки и изменить стартовые настройки, а затем сохранить их в файл конфигурации для следующего запуска движка. Например:


<details>
<summary>AppSystemLogic.cpp | Close</summary>

`AppSystemLogic.cpp`


```cpp
#include "AppSystemLogic.h"
#include <UnigineConfig.h>
#include <UnigineConsole.h>

using namespace Unigine;

/* .. */

int AppSystemLogic::shutdown()
{
	// задаём заголовок окна
	BootConfig::setWindowTitle("Project Name");
	Console::setString("starting_world", "my_world");

	// настраиваем экран загрузки
	BootConfig::setScreenWidth(960);
	BootConfig::setScreenHeight(540);

	BootConfig::setScreenBackgroundColor(Math::vec4_black);
	BootConfig::setScreenTransform(Math::vec4(1.0f, 1.0f, 0.5f, 0.5f));

	BootConfig::setScreenThreshold(16);
	BootConfig::setScreenTexture("textures/boot_screen.png");

	BootConfig::setScreenText("								\
			<p align=\"center\">							\
				<font color=\"#ffffff\" size=\"64\">		\
					<xy x=\"%10\" y=\"%50\"/>Helicopter	\
				</font>										\
			</p>");
	BootConfig::setScreenMessageEngineInit(R"(					\
			<p><font size=\"24\" color=\"#777777\">			\
				Engine initialization.						\
			</font></p>)");
	BootConfig::setScreenMessageFileSystemInit("Custom message for file system initialization.");
	BootConfig::setScreenMessageMaterialsInit("Custom message for materials initialization.");
	BootConfig::setScreenMessagePropertiesInit("Custom message for properties initialization.");
	BootConfig::setScreenMessageShadersCompilation("Custom message for shaders compilation.");

	BootConfig::save();

	return 1;
}

```

</details>


### См. также


- Статья [Configuration Files](../../../code/configuration_file_cpp.md).


## Класс BootConfig

### Методы класса

## void setScreenEnabled ( bool enabled )

Устанавливает новое значение, указывающее, включён ли экран загрузки.
### Аргументы

- *bool* **enabled** - **true** — включить экран загрузки; **false** — отключить.

## bool isScreenEnabled () const

Возвращает текущее значение, указывающее, включён ли экран загрузки.
### Возвращаемое значение

**true**, если экран загрузки включён; иначе **false**.
## void setScreenMessageShadersCompilation ( const char * compilation )

Устанавливает новое сообщение, отображаемое во время компиляции шейдеров. Сообщение задаётся так же, как и [screen text](#setScreenText_cstr_void).
### Аргументы

- *const char ** **compilation** - Сообщение для компиляции шейдеров.

## const char * getScreenMessageShadersCompilation () const

Возвращает текущее сообщение, отображаемое во время компиляции шейдеров. Сообщение задаётся так же, как и [screen text](#setScreenText_cstr_void).
### Возвращаемое значение

Текущее сообщение для компиляции шейдеров.
## void setScreenMessageEngineInit ( const char * init )

Устанавливает новое сообщение, отображаемое при инициализации движка. Сообщение задаётся так же, как и [screen text](#setScreenText_cstr_void).
### Аргументы

- *const char ** **init** - Сообщение для инициализации движка.

## const char * getScreenMessageEngineInit () const

Возвращает текущее сообщение, отображаемое при инициализации движка. Сообщение задаётся так же, как и [screen text](#setScreenText_cstr_void).
### Возвращаемое значение

Текущее сообщение для инициализации движка.
## void setScreenMessageFileSystemInit ( const char * init )

Устанавливает новое сообщение, отображаемое при инициализации файловой системы. Сообщение задаётся так же, как и [screen text](#setScreenText_cstr_void).
### Аргументы

- *const char ** **init** - Сообщение для инициализации файловой системы.

## const char * getScreenMessageFileSystemInit () const

Возвращает текущее сообщение, отображаемое при инициализации файловой системы. Сообщение задаётся так же, как и [screen text](#setScreenText_cstr_void).
### Возвращаемое значение

Текущее сообщение для инициализации файловой системы.
## void setScreenMessagePropertiesInit ( const char * init )

Устанавливает новое сообщение, отображаемое при инициализации свойств. Сообщение задаётся так же, как и [screen text](#setScreenText_cstr_void).
### Аргументы

- *const char ** **init** - Сообщение для инициализации свойств.

## const char * getScreenMessagePropertiesInit () const

Возвращает текущее сообщение, отображаемое при инициализации свойств. Сообщение задаётся так же, как и [screen text](#setScreenText_cstr_void).
### Возвращаемое значение

Текущее сообщение для инициализации свойств.
## void setScreenMessageStaticMeshesInit ( const char * init )

Устанавливает новое сообщение, отображаемое при инициализации статических мэшей. Сообщение задаётся так же, как и [screen text](#setScreenText_cstr_void).
### Аргументы

- *const char ** **init** - Сообщение для инициализации статических мэшей.

## const char * getScreenMessageStaticMeshesInit () const

Возвращает текущее сообщение, отображаемое при инициализации статических мэшей. Сообщение задаётся так же, как и [screen text](#setScreenText_cstr_void).
### Возвращаемое значение

Текущее сообщение для инициализации статических мэшей.
## void setScreenMessageMaterialsInit ( const char * init )

Устанавливает новое сообщение, отображаемое при инициализации материалов. Сообщение задаётся так же, как и [screen text](#setScreenText_cstr_void).
### Аргументы

- *const char ** **init** - Сообщение для инициализации материалов.

## const char * getScreenMessageMaterialsInit () const

Возвращает текущее сообщение, отображаемое при инициализации материалов. Сообщение задаётся так же, как и [screen text](#setScreenText_cstr_void).
### Возвращаемое значение

Текущее сообщение для инициализации материалов.
## void setScreenMessageMaterialsPreloading ( const char * preloading )

Устанавливает новое сообщение, отображаемое при предзагрузке материалов.
### Аргументы

- *const char ** **preloading** - Сообщение для предзагрузки материалов.

## const char * getScreenMessageMaterialsPreloading () const

Возвращает текущее сообщение, отображаемое при предзагрузке материалов.
### Возвращаемое значение

Текущее сообщение для предзагрузки материалов.
## void setScreenText ( const char * text )

Устанавливает новый текст экрана загрузки.
### Аргументы

- *const char ** **text** - Текст экрана загрузки. Может быть либо обычным текстом, либо [rich text](../../../code/gui/ui/index.md#rich_text). Предоставляется ряд псевдонимов:

  - UNIGINE_COPYRIGHT — текст авторских прав UNIGINE.
  - UNIGINE_VERSION — текущая версия UNIGINE.
  - LOADING_PROGRESS — прогресс загрузки от 0 до 100.

## const char * getScreenText () const

Возвращает текущий текст экрана загрузки.
### Возвращаемое значение

Текущий текст экрана загрузки. Может быть либо обычным текстом, либо [rich text](../../../code/gui/ui/index.md#rich_text). Предоставляется ряд псевдонимов:
- UNIGINE_COPYRIGHT — текст авторских прав UNIGINE.
- UNIGINE_VERSION — текущая версия UNIGINE.
- LOADING_PROGRESS — прогресс загрузки от 0 до 100.


## void setScreenFont ( const char * font )

Устанавливает новый путь к шрифту для рендеринга текста.
> **Примечание:** Шрифты или любые другие ресурсы, используемые на экране загрузки, **не могут быть упакованы в архив UNG**.


### Аргументы

- *const char ** **font** - Путь к шрифту для рендеринга текста.

## const char * getScreenFont () const

Возвращает текущий путь к шрифту для рендеринга текста.
> **Примечание:** Шрифты или любые другие ресурсы, используемые на экране загрузки, **не могут быть упакованы в архив UNG**.


### Возвращаемое значение

Текущий путь к шрифту для рендеринга текста.
## void setScreenTexture ( const char * texture )

Устанавливает новый путь к текстуре экрана загрузки.
> **Примечание:** Текстуры или любые другие ресурсы, используемые на экране загрузки, **не могут быть упакованы в архив UNG**.


### Аргументы

- *const char ** **texture** - Путь к текстуре экрана загрузки.

## const char * getScreenTexture () const

Возвращает текущий путь к текстуре экрана загрузки.
> **Примечание:** Текстуры или любые другие ресурсы, используемые на экране загрузки, **не могут быть упакованы в архив UNG**.


### Возвращаемое значение

Текущий путь к текстуре экрана загрузки.
## void setScreenThreshold ( int threshold )

Устанавливает новый порог для смешивания на основе альфа-канала.
### Аргументы

- *int* **threshold** - Порог для смешивания на основе альфа-канала.

## int getScreenThreshold () const

Возвращает текущий порог для смешивания на основе альфа-канала.
### Возвращаемое значение

Текущий порог для смешивания на основе альфа-канала.
## void setScreenTransform ( const Math:: vec4 & transform )

Устанавливает новую трансформацию текстуры экрана загрузки. Значение по умолчанию — vec4(1.0f, 1.0f, 0.5f, 0.5f).
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md)&* **transform** - Трансформация экрана, заданная вектором из четырёх чисел в диапазоне [0; 1]:

  1. Множитель размера текстуры
  2. Множитель размера окна
  3. Горизонтальная позиция
  4. Вертикальная позиция

## Math:: vec4 getScreenTransform () const

Возвращает текущую трансформацию текстуры экрана загрузки. Значение по умолчанию — vec4(1.0f, 1.0f, 0.5f, 0.5f).
### Возвращаемое значение

Текущая трансформация экрана, заданная вектором из четырёх чисел в диапазоне [0; 1]:
1. Множитель размера текстуры
2. Множитель размера окна
3. Горизонтальная позиция
4. Вертикальная позиция


## void setScreenBackgroundColor ( const Math:: vec4 & color )

Устанавливает новый цвет фона экрана.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md)&* **color** - Цвет фона, заданный вектором из четырёх чисел в диапазоне [0; 1].

## Math:: vec4 getScreenBackgroundColor () const

Возвращает текущий цвет фона экрана.
### Возвращаемое значение

Текущий цвет фона, заданный вектором из четырёх чисел в диапазоне [0; 1].
## void setScreenHeight ( int height )

Устанавливает новую высоту окна экрана загрузки, в пикселях.
### Аргументы

- *int* **height** - Высота окна экрана загрузки, в пикселях.

## int getScreenHeight () const

Возвращает текущую высоту окна экрана загрузки, в пикселях.
### Возвращаемое значение

Текущая высота окна экрана загрузки, в пикселях.
## void setScreenWidth ( int width )

Устанавливает новую ширину окна экрана загрузки.
### Аргументы

- *int* **width** - Ширина окна экрана загрузки, в пикселях.

## int getScreenWidth () const

Возвращает текущую ширину окна экрана загрузки.
### Возвращаемое значение

Текущая ширина окна экрана загрузки, в пикселях.
## int getNumExternPlugins () const

Возвращает текущее количество библиотек плагинов, автоматически загружаемых при старте движка. Эти плагины указаны в файле конфигурации `.boot` через элемент [`extern_plugin`](../../../code/configuration_file_cpp.md#boot). Список этих путей плагинов можно получить через методы *getNumExternPlugins()* и [*getExternPlugin(int num)*](#getExternPlugin_int_cstr). Порядок загрузки плагинов важен, вы можете переставить их через [*swapPluginPath()*](#swapPluginPath_int_int_void).
### Возвращаемое значение

Текущее количество библиотек плагинов, загружаемых при старте движка.
## int getNumPluginPaths () const

Возвращает текущее количество директорий, содержащих плагины, автоматически загружаемые при старте движка. Эти директории указаны в файле конфигурации `.boot` через элемент [`plugin_path`](../../../code/configuration_file_cpp.md#boot). Список этих путей плагинов можно получить через методы *getNumPluginPaths()* и [*getPluginPath(int num)*](../../../api/library/engine/class.engine_cpp.md#getPluginPath_int_const_char_ptr). Порядок загрузки плагинов важен, вы можете переставить пути через [*swapPluginPath()*](#swapPluginPath_int_int_void)
### Возвращаемое значение

Текущее количество директорий плагинов.
## void setConsoleCommand ( const char * command )

Устанавливает новую консольную команду(ы), используемую при старте движка (соответствует элементу [`console_command`](../../../code/configuration_file_cpp.md#boot) файла конфигурации `.boot`).
### Аргументы

- *const char ** **command** - Консольная команда(ы), используемая при старте движка. Несколько команд можно разделять последовательностью &&.

## const char * getConsoleCommand () const

Возвращает текущую консольную команду(ы), используемую при старте движка (соответствует элементу [`console_command`](../../../code/configuration_file_cpp.md#boot) файла конфигурации `.boot`).
### Возвращаемое значение

Текущая консольная команда(ы), используемая при старте движка. Несколько команд можно разделять последовательностью &&.
## void setExternDefine ( const char * define )

Устанавливает новое внешнее определение(я), используемое при старте движка (соответствует элементу [`extern_define`](../../../code/configuration_file_cpp.md#boot) файла конфигурации `.boot`).
### Аргументы

- *const char ** **define** - Внешнее определение(я), используемое при старте движка. Несколько определений разделяются запятыми (без пробелов). Определения могут быть заданы следующим образом:

  - DEFINITION_NAME
  - DEFINITION_NAME=VALUE
  - DEFINITION_NAME_1,DEFINITION_NAME_2, DEFINITION_NAME_3=VALUE,...,DEFINITION_NAME_N

## const char * getExternDefine () const

Возвращает текущее внешнее определение(я), используемое при старте движка (соответствует элементу [`extern_define`](../../../code/configuration_file_cpp.md#boot) файла конфигурации `.boot`).
### Возвращаемое значение

Текущее внешнее определение(я), используемое при старте движка. Несколько определений разделяются запятыми (без пробелов). Определения могут быть заданы следующим образом:
- DEFINITION_NAME
- DEFINITION_NAME=VALUE
- DEFINITION_NAME_1,DEFINITION_NAME_2, DEFINITION_NAME_3=VALUE,...,DEFINITION_NAME_N


## void setSoundApp ( const char * app )

Устанавливает новый используемый звуковой API (соответствует элементу [`sound_app`](../../../code/configuration_file_cpp.md#boot) файла конфигурации `.boot`).
### Аргументы

- *const char ** **app** - Звуковой API, используемый для рендеринга: *nosound, auto* или *openal*.

## const char * getSoundApp () const

Возвращает текущий используемый звуковой API (соответствует элементу [`sound_app`](../../../code/configuration_file_cpp.md#boot) файла конфигурации `.boot`).
### Возвращаемое значение

Текущий звуковой API, используемый для рендеринга: *nosound, auto* или *openal*.
## void setVideoApp ( const char * app )

Устанавливает новый используемый графический API для рендеринга (соответствует элементу [`video_app`](../../../code/configuration_file_cpp.md#boot) файла конфигурации `.boot`).
### Аргументы

- *const char ** **app** - Графический API, используемый для рендеринга: *null, auto, dx, dx12, direct3d12, vk, vulkan*.

## const char * getVideoApp () const

Возвращает текущий используемый графический API для рендеринга (соответствует элементу [`video_app`](../../../code/configuration_file_cpp.md#boot) файла конфигурации `.boot`).
### Возвращаемое значение

Текущий графический API, используемый для рендеринга: *null, auto, dx, dx12, direct3d12, vk, vulkan*.
## void setSystemCache ( const char * cache )

Устанавливает новый путь к файлу кэша, используемому движком (соответствует элементу [`system_cache`](../../../code/configuration_file_cpp.md#boot) файла конфигурации `.boot`).
### Аргументы

- *const char ** **cache** - Путь к файлу кэша, используемому движком. Может быть абсолютным путём или путём относительно [`data path`](../../../api/library/engine/class.engine_cpp.md#getDataPath_const_char_ptr), либо [`cache path`](#setCachePath_cstr_void) (если задан).

## const char * getSystemCache () const

Возвращает текущий путь к файлу кэша, используемому движком (соответствует элементу [`system_cache`](../../../code/configuration_file_cpp.md#boot) файла конфигурации `.boot`).
### Возвращаемое значение

Текущий путь к файлу кэша, используемому движком. Может быть абсолютным путём или путём относительно [`data path`](../../../api/library/engine/class.engine_cpp.md#getDataPath_const_char_ptr), либо [`cache path`](#setCachePath_cstr_void) (если задан).
## void setEditorCache ( const char * cache )

Устанавливает новый путь к файлу кэша, используемому UnigineEditor (соответствует элементу [`editor_cache`](../../../code/configuration_file_cpp.md#boot) файла конфигурации `.boot`).
### Аргументы

- *const char ** **cache** - Путь к файлу кэша, используемому UnigineEditor. Может быть абсолютным путём или путём относительно [`data path`](../../../api/library/engine/class.engine_cpp.md#getDataPath_const_char_ptr), либо [`cache path`](#setCachePath_cstr_void) (если задан).

## const char * getEditorCache () const

Возвращает текущий путь к файлу кэша, используемому UnigineEditor (соответствует элементу [`editor_cache`](../../../code/configuration_file_cpp.md#boot) файла конфигурации `.boot`).
### Возвращаемое значение

Текущий путь к файлу кэша, используемому UnigineEditor. Может быть абсолютным путём или путём относительно [`data path`](../../../api/library/engine/class.engine_cpp.md#getDataPath_const_char_ptr), либо [`cache path`](#setCachePath_cstr_void) (если задан).
## void setCachePath ( const char * path )

Устанавливает новый путь для хранения файлов кэша системы и Editor (соответствует элементу [`cache_path`](../../../code/configuration_file_cpp.md#boot) файла конфигурации `.boot`).
### Аргументы

- *const char ** **path** - Путь для хранения файлов кэша системы и Editor. Может быть абсолютным путём или путём относительно [`data path`](../../../api/library/engine/class.engine_cpp.md#getDataPath_const_char_ptr).

## const char * getCachePath () const

Возвращает текущий путь для хранения файлов кэша системы и Editor (соответствует элементу [`cache_path`](../../../code/configuration_file_cpp.md#boot) файла конфигурации `.boot`).
### Возвращаемое значение

Текущий путь для хранения файлов кэша системы и Editor. Может быть абсолютным путём или путём относительно [`data path`](../../../api/library/engine/class.engine_cpp.md#getDataPath_const_char_ptr).
## void setEditorScript ( const char * script )

Устанавливает новый путь к [editor script](../../../code/fundamentals/execution_sequence/app_logic_system.md#editor_logic) (соответствует элементу [`system_script`](../../../code/configuration_file_cpp.md#boot) файла конфигурации `.boot`).
### Аргументы

- *const char ** **script** - Путь к [editor script](../../../code/fundamentals/execution_sequence/app_logic_system.md#editor_logic) (указывается относительно папки `data`).

## const char * getEditorScript () const

Возвращает текущий путь к [editor script](../../../code/fundamentals/execution_sequence/app_logic_system.md#editor_logic) (соответствует элементу [`system_script`](../../../code/configuration_file_cpp.md#boot) файла конфигурации `.boot`).
### Возвращаемое значение

Текущий путь к [editor script](../../../code/fundamentals/execution_sequence/app_logic_system.md#editor_logic) (указывается относительно папки `data`).
## void setSystemScript ( const char * script )

Устанавливает новый путь к [system script](../../../code/fundamentals/execution_sequence/app_logic_system.md#system_logic) (соответствует элементу [`system_script`](../../../code/configuration_file_cpp.md#boot) файла конфигурации `.boot`).
### Аргументы

- *const char ** **script** - Путь к [system script](../../../code/fundamentals/execution_sequence/app_logic_system.md#system_logic) (указывается относительно папки `data`).

## const char * getSystemScript () const

Возвращает текущий путь к [system script](../../../code/fundamentals/execution_sequence/app_logic_system.md#system_logic) (соответствует элементу [`system_script`](../../../code/configuration_file_cpp.md#boot) файла конфигурации `.boot`).
### Возвращаемое значение

Текущий путь к [system script](../../../code/fundamentals/execution_sequence/app_logic_system.md#system_logic) (указывается относительно папки `data`).
## void setEngineLog ( const char * log )

Устанавливает новый файл журнала (в формате TXT), используемый движком. Путь может быть абсолютным или относительным к бинарному исполняемому файлу. Для относительных путей, если задан стартовый параметр **Project Name**, файл журнала с указанным именем будет создан в соответствующей директории профиля пользователя (будет использовано только имя, оставшаяся часть относительного пути будет отброшена).
### Аргументы

- *const char ** **log** - Файл журнала (в формате TXT), используемый движком.

## const char * getEngineLog () const

Возвращает текущий файл журнала (в формате TXT), используемый движком. Путь может быть абсолютным или относительным к бинарному исполняемому файлу. Для относительных путей, если задан стартовый параметр **Project Name**, файл журнала с указанным именем будет создан в соответствующей директории профиля пользователя (будет использовано только имя, оставшаяся часть относительного пути будет отброшена).
### Возвращаемое значение

Текущий файл журнала (в формате TXT), используемый движком.
## void setGuiPath ( const char * path )

Устанавливает новый путь к скину GUI, используемому для интерфейса движка. Путь может быть указан как абсолютный или относительно папки `data`.
### Аргументы

- *const char ** **path** - Путь к скину GUI, используемому для интерфейса движка (абсолютный путь или путь относительно папки `data`).

## const char * getGuiPath () const

Возвращает текущий путь к скину GUI, используемому для интерфейса движка. Путь может быть указан как абсолютный или относительно папки `data`.
### Возвращаемое значение

Текущий путь к скину GUI, используемому для интерфейса движка (абсолютный путь или путь относительно папки `data`).
## void setAutosave ( bool autosave )

Устанавливает новое значение, указывающее, сохраняются ли автоматически настройки стартовой конфигурации в соответствующий файл конфигурации при загрузке, закрытии и сохранении мира, а также при завершении работы движка.
### Аргументы

- *bool* **autosave** - **true** — включить автоматическое сохранение текущих настроек стартовой конфигурации; **false** — отключить.

## bool isAutosave () const

Возвращает текущее значение, указывающее, сохраняются ли автоматически настройки стартовой конфигурации в соответствующий файл конфигурации при загрузке, закрытии и сохранении мира, а также при завершении работы движка.
### Возвращаемое значение

**true**, если автоматическое сохранение текущих настроек стартовой конфигурации включено; иначе **false**.
## void setPath ( const char * path )

Устанавливает новый путь к файлу стартовой конфигурации (по умолчанию: `configs/default.boot`). Путь может быть указан как абсолютный или относительно папки *[-data_path](../../../code/command_line.md#data_path)* или *<project_name>*, если задан *[-project_name](../../../code/command_line.md#project_name)*. Чтобы запустить приложение с другим файлом стартовой конфигурации, укажите путь к нему с помощью опции командной строки [`-boot_config`](../../../code/command_line.md#boot_config).
### Аргументы

- *const char ** **path** - Путь к файлу стартовой конфигурации.

## const char * getPath () const

Возвращает текущий путь к файлу стартовой конфигурации (по умолчанию: `configs/default.boot`). Путь может быть указан как абсолютный или относительно папки *[-data_path](../../../code/command_line.md#data_path)* или *<project_name>*, если задан *[-project_name](../../../code/command_line.md#project_name)*. Чтобы запустить приложение с другим файлом стартовой конфигурации, укажите путь к нему с помощью опции командной строки [`-boot_config`](../../../code/command_line.md#boot_config).
### Возвращаемое значение

Текущий путь к файлу стартовой конфигурации.
## void setWindowTitle ( const char * title )

Устанавливает новый заголовок окна приложения.
### Аргументы

- *const char ** **title** - Заголовок окна приложения.

## const char * getWindowTitle () const

Возвращает текущий заголовок окна приложения.
### Возвращаемое значение

Текущий заголовок окна приложения.
## void setWindowIconPath ( const char * path )

Устанавливает новый путь к пользовательской иконке для окна финального приложения.
### Аргументы

- *const char ** **path** - Путь к пользовательской иконке для окна финального приложения.

## const char * getWindowIconPath () const

Возвращает текущий путь к пользовательской иконке для окна финального приложения.
### Возвращаемое значение

Текущий путь к пользовательской иконке для окна финального приложения.
## void setVideoQuadroSync ( bool sync )

***Console*:**`video_quadro_sync`Устанавливает новое значение, указывающее, включена ли функция NVIDIA Quadro Sync, обеспечивающая поддержку синхронизации рендеринга кадров на нескольких дисплеях. Включение этой опции автоматически переключает вид в полноэкранный режим, включает [VSYNC](../../../api/library/rendering/class.render_cpp.md#VSync) и устанавливает значение [MaxFPS](../../../api/library/rendering/class.render_cpp.md#MaxFPS) равным 0.
### Аргументы

- *bool* **sync** - **true** — включить функцию NVIDIA Quadro Sync; **false** — отключить. Значение по умолчанию — **false**.

## bool isVideoQuadroSync () const

***Console*:**`video_quadro_sync`Возвращает текущее значение, указывающее, включена ли функция NVIDIA Quadro Sync, обеспечивающая поддержку синхронизации рендеринга кадров на нескольких дисплеях. Включение этой опции автоматически переключает вид в полноэкранный режим, включает [VSYNC](../../../api/library/rendering/class.render_cpp.md#VSync) и устанавливает значение [MaxFPS](../../../api/library/rendering/class.render_cpp.md#MaxFPS) равным 0.
### Возвращаемое значение

**true**, если функция NVIDIA Quadro Sync включена; иначе **false**. Значение по умолчанию — **false**.
## void setVideoOffscreen ( bool offscreen )

***Console*:**`video_offscreen`Устанавливает новое значение, указывающее, включён ли для приложения оффскрин-режим. Оффскрин-режим позволяет запускать движок UNIGINE в облаке и использовать мощные серверы (например, для генерации фотореалистичных наборов данных для глубокого обучения и верификации алгоритмов ИИ).
> **Примечание:** Доступно только во время инициализации (старта) движка, не имеет эффекта во время выполнения.


### Аргументы

- *bool* **offscreen** - **true** — включить использование оффскрин-режима для приложения; **false** — отключить. Значение по умолчанию — **false**.

## bool isVideoOffscreen () const

***Console*:**`video_offscreen`Возвращает текущее значение, указывающее, включён ли для приложения оффскрин-режим. Оффскрин-режим позволяет запускать движок UNIGINE в облаке и использовать мощные серверы (например, для генерации фотореалистичных наборов данных для глубокого обучения и верификации алгоритмов ИИ).
> **Примечание:** Доступно только во время инициализации (старта) движка, не имеет эффекта во время выполнения.


### Возвращаемое значение

**true**, если использование оффскрин-режима для приложения включено; иначе **false**. Значение по умолчанию — **false**.
## void setVideoAdapter ( int adapter )

***Console*:**`video_adapter`Устанавливает новый [ID](../../../api/library/engine/class.systeminfo_cpp.md#getGPUID_int_int) аппаратного видеоадаптера, используемого для рендеринга.
> **Примечание:** Доступно только во время инициализации (старта) движка, не имеет эффекта во время выполнения.


### Аргументы

- *int* **adapter** - [ID](../../../api/library/engine/class.systeminfo_cpp.md#getGPUID_int_int) аппаратного видеоадаптера, значение от 0 до [the number of available video adapters](../../../api/library/engine/class.systeminfo_cpp.md#getGPUCount_int). Диапазон значений: **[0, 32]**. Значение по умолчанию: **0**.

## int getVideoAdapter () const

***Console*:**`video_adapter`Возвращает текущий [ID](../../../api/library/engine/class.systeminfo_cpp.md#getGPUID_int_int) аппаратного видеоадаптера, используемого для рендеринга.
> **Примечание:** Доступно только во время инициализации (старта) движка, не имеет эффекта во время выполнения.


### Возвращаемое значение

Текущий [ID](../../../api/library/engine/class.systeminfo_cpp.md#getGPUID_int_int) аппаратного видеоадаптера, значение от 0 до [the number of available video adapters](../../../api/library/engine/class.systeminfo_cpp.md#getGPUCount_int).
Диапазон значений: **[0, 32]**. Значение по умолчанию: **0**.
## void setVideoDebugShader ( bool shader )

***Console*:**`video_debug_shaders`Устанавливает новое значение, указывающее, должен ли использоваться отладочный шейдер для приложения независимо от типа его сборки (debug или release). Эту опцию следует включать, если вы используете инструменты отладки графики (например, отладчик [RenderDoc](https://renderdoc.org/)).
### Аргументы

- *bool* **shader** - **true** — включить отладочный шейдер для приложения; **false** — отключить.

## bool isVideoDebugShader () const

***Console*:**`video_debug_shaders`Возвращает текущее значение, указывающее, должен ли использоваться отладочный шейдер для приложения независимо от типа его сборки (debug или release). Эту опцию следует включать, если вы используете инструменты отладки графики (например, отладчик [RenderDoc](https://renderdoc.org/)).
### Возвращаемое значение

**true**, если отладочный шейдер для приложения включён; иначе **false**.
## void setVideoDebug ( int debug )

***Console*:**`video_debug`Устанавливает новый режим отладки видео для графического API.
> **Примечание:** Остерегайтесь серьёзного замедления при включении. Доступно только во время инициализации (старта) движка, не имеет эффекта во время выполнения.


### Аргументы

- *int* **debug** - Режим отладки видео для графического API. Одно из следующих значений:

  - **0** - релизный контекст рендеринга (без отладки) (по умолчанию)
  - **1** - отладочный контекст рендеринга
  - **2** - отладочный контекст рендеринга с остановкой при ошибке (только для отладочных сборок)
  - **3** - проверка на стороне GPU (только dx12, только для отладочных сборок)

## int getVideoDebug () const

***Console*:**`video_debug`Возвращает текущий режим отладки видео для графического API.
> **Примечание:** Остерегайтесь серьёзного замедления при включении. Доступно только во время инициализации (старта) движка, не имеет эффекта во время выполнения.


### Возвращаемое значение

Текущий режим отладки видео для графического API. Одно из следующих значений:
- **0** - релизный контекст рендеринга (без отладки) (по умолчанию)
- **1** - отладочный контекст рендеринга
- **2** - отладочный контекст рендеринга с остановкой при ошибке (только для отладочных сборок)
- **3** - проверка на стороне GPU (только dx12, только для отладочных сборок)

---

## bool load ( )

***Console*:**`boot_config_load`Загружает стартовую конфигурацию движка из файла. Чтобы изменить путь к файлу конфигурации, используйте метод [*setPath()*](#setPath_cstr_void).
### Возвращаемое значение

**true**, если конфигурация успешно загружена из файла; иначе **false**.
## bool save ( ) const

***Console*:**`boot_config_save`Сохраняет текущую стартовую конфигурацию движка в файл. Чтобы изменить путь к файлу конфигурации, используйте метод [*setPath()*](#setPath_cstr_void).
### Возвращаемое значение

**true**, если текущая конфигурация успешно сохранена в файл; иначе **false**.
## void reset ( )

Сбрасывает настройки в файле стартовой конфигурации движка к значениям по умолчанию.
## void removePluginPath ( int num )

 Удаляет путь плагина с указанным номером из списка путей плагинов, заданных в файле конфигурации `.boot` через элемент [`plugin_path`](../../../code/configuration_file_cpp.md#boot). Путь плагина — это директория, содержащая плагины, автоматически загружаемые при старте движка.
### Аргументы

- *int* **num** - Номер пути плагина, удаляемого из списка заданных путей плагинов, в диапазоне от 0 до [total number of plugin paths specified](#getNumPluginPaths_int).

## void swapPluginPath ( int num0 , int num1 )

 Меняет местами два пути плагинов с заданными номерами, указанные в файле конфигурации `.boot`. Путь плагина — это директория, содержащая плагины, автоматически загружаемые при старте движка. Список этих путей плагинов можно получить через методы [*getNumPluginPaths()*](../../../api/library/engine/class.engine_cpp.md#getNumPluginPaths_int) и [*getPluginPath(int num)*](../../../api/library/engine/class.engine_cpp.md#getPluginPath_int_const_char_ptr). Порядок загрузки плагинов важен, вы можете переставить пути через [*swapPluginPath()*](#swapPluginPath_int_int_void)
### Аргументы

- *int* **num0** - Номер первого пути плагина в списке заданных путей плагинов, который нужно поменять местами, в диапазоне от 0 до [total number of plugin paths specified](#getNumPluginPaths_int).
- *int* **num1** - Номер второго пути плагина в списке заданных путей плагинов, который нужно поменять местами, в диапазоне от 0 до [total number of plugin paths specified](#getNumPluginPaths_int).

## const char * getPluginPath ( int num )

 Возвращает путь плагина с заданным номером, указанный в файле конфигурации `.boot` через элемент [`plugin_path`](../../../code/configuration_file_cpp.md#boot). Путь плагина — это директория, содержащая плагины, автоматически загружаемые при старте движка. Порядок загрузки плагинов важен, вы можете переставить пути через [*swapPluginPath()*](#swapPluginPath_int_int_void).
### Аргументы

- *int* **num** - Номер пути плагина в списке заданных путей плагинов, в диапазоне от 0 до [total number of plugin paths specified](#getNumPluginPaths_int).

### Возвращаемое значение

Путь к директории плагинов с заданным номером в списке путей плагинов. Может быть абсолютным или указанным относительно бинарного исполняемого файла.
## void setPluginPath ( int num , const char * value )

 Устанавливает новый путь для элемента списка путей плагинов с заданным номером, указанного в файле конфигурации `.boot` через элемент [`plugin_path`](../../../code/configuration_file_cpp.md#boot). Путь плагина — это директория, содержащая плагины, автоматически загружаемые при старте движка. Порядок загрузки плагинов важен, вы можете переставить пути через [*swapPluginPath()*](#swapPluginPath_int_int_void).
### Аргументы

- *int* **num** - Номер пути плагина в списке заданных путей плагинов.
- *const char ** **value** - Новый путь, устанавливаемый для указанного элемента списка путей плагинов. Может быть указан относительно бинарного исполняемого файла или как абсолютный путь.

## void removeExternPlugin ( int num )

 Удаляет плагин с указанным номером из списка плагинов, заданных в файле конфигурации `.boot` через элемент [`extern_plugin`](../../../code/configuration_file_cpp.md#boot).
### Аргументы

- *int* **num** - Номер плагина, удаляемого из списка заданных плагинов, в диапазоне от 0 до [total number of plugins specified](#getNumExternPlugins_int).

## void swapExternPlugin ( int num0 , int num1 )

 Меняет местами два плагина с заданными номерами, указанные в файле конфигурации `.boot`. Список этих плагинов можно получить через методы [*getNumExternPlugins()*](#getNumExternPlugins_int) и [*getExternPlugin(int num)*](#getExternPlugin_int_cstr). Порядок загрузки плагинов важен, этот метод позволяет переставлять плагины для изменения порядка загрузки.
### Аргументы

- *int* **num0** - Номер первого плагина в списке заданных плагинов, который нужно поменять местами, в диапазоне от 0 до [total number of plugins specified](#getNumExternPlugins_int).
- *int* **num1** - Номер второго плагина в списке заданных плагинов, который нужно поменять местами, в диапазоне от 0 до [total number of plugins specified](#getNumExternPlugins_int).

## const char * getExternPlugin ( int num )

 Возвращает имя плагина с заданным номером, указанное в файле конфигурации `.boot` через элемент [`extern_plugin`](../../../code/configuration_file_cpp.md#boot). Порядок загрузки плагинов важен, вы можете переставить пути через [*swapExternPlugin()*](#swapExternPlugin_int_int_void).
### Аргументы

- *int* **num** - Номер плагина в списке заданных плагинов, в диапазоне от 0 до [total number of plugins specified](#getNumExternPlugins_int).

### Возвращаемое значение

Имя плагина с заданным номером, указанное в файле конфигурации `.boot`. Имя библиотеки плагина указывается без каких-либо префиксов и постфиксов (например, `libNetwork_x64d.so` указывается как "**Network**").
## void setExternPlugin ( int num , const char * value )

Устанавливает новое имя плагина с заданным номером, указанное в файле конфигурации `.boot` через элемент [`extern_plugin`](../../../code/configuration_file_cpp.md#boot). Порядок загрузки плагинов важен, вы можете переставить пути через [*swapExternPlugin()*](#swapExternPlugin_int_int_void).
### Аргументы

- *int* **num** - Номер плагина, устанавливаемого в списке заданных плагинов, в диапазоне от 0 до [total number of plugins specified](#getNumExternPlugins_int).
- *const char ** **value** - Имя плагина с заданным номером, указанное в файле конфигурации `.boot`. Имя библиотеки плагина указывается без каких-либо префиксов и постфиксов (например, `libNetwork_x64d.so` указывается как "**Network**").
