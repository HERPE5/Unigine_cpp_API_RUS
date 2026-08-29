# Unigine::File Class (CPP)

**Header:** #include <UnigineStreams.h>

**Inherits from:** Stream


Этот класс позволяет записывать и читать данные из файлов.


***File*** — это высокоуровневая абстракция над любым файлом или фрагментом данных, таким как:


- Файл, хранящийся на диске ([FileSystem::isDiskFile()](../../../api/library/filesystem/class.filesystem_cpp.md#isDiskFile_cstr_bool))
- Файл, загруженный в кэш ([FileSystem::isCacheFile()](../../../api/library/filesystem/class.filesystem_cpp.md#isCacheFile_cstr_bool))
- Blob ([FileSystem::isBlobFile()](../../../api/library/filesystem/class.filesystem_cpp.md#isBlobFile_cstr_bool))
- Файл пакета ([FileSystem::isPackageFile()](../../../api/library/filesystem/class.filesystem_cpp.md#isPackageFile_cstr_bool))


### Пример


Пример ниже создаёт Xml и выводит все добавленные данные в консоль.


```cpp
#include "AppWorldLogic.h"
#include <UnigineConsole.h>

using namespace Unigine;

String my_file_read(FilePtr file)
{
	Log::message("\nFile name is %s\n", file->getName());
	Log::message("File size is %d bytes\n", file->getSize());
	return file->readString();
}

void my_file_write(FilePtr file, const char *str)
{
	file->writeString(str);
}

int AppWorldLogic::init()
{

	FilePtr file = File::create();

	// записываем файл
	file->open("api_file.txt", "wb");
	if (file->isOpened())
	{
		my_file_write(file, "Message from the file");
		file->close();
	}

	// читаем файл
	file->open("api_file.txt", "rb");
	if (file->isOpened())
	{
		String data = my_file_read(file);
		Log::message("\n%s\n", data.get());
		file->close();
	}

	// показываем консоль
	Console::setActive(1);

	return 1;
}


```


### См. также


- Пример C++ API находится в папке **<UnigineSDK>/source/samples/Api/Systems/FileSample**


## File Class

### Методы класса

---

## static FilePtr create ( )

Конструктор по умолчанию.
## static FilePtr create ( const char * name , const char * mode , bool use_cache = true )

Конструктор.
### Аргументы

- *const char ** **name** - Имя файла.
- *const char ** **mode** - Режим доступа (см. [open()](#open_cstr_cstr_bool_int)).
- *bool* **use_cache**

## int getc ( ) const

Читает следующий символ из файла.
### Возвращаемое значение

Одиночный символ, прочитанный из открытого файла.
## const char * getName ( ) const

Возвращает имя открытого файла.
### Возвращаемое значение

Имя файла.
## size_t getSize ( ) const

Возвращает размер открытого файла в байтах.
### Возвращаемое значение

Размер файла в байтах.
## bool close ( ) const

Закрывает файл для любой операции.
### Возвращаемое значение

Возвращает 1, если файл успешно закрыт; иначе 0.
## int eof ( ) const

Проверяет достижение конца файла для дескриптора файла.
### Возвращаемое значение

**1**, если достигнут конец файла; иначе **0**.
## int flush ( ) const

Принудительно записывает все буферизованные данные в файл.
### Возвращаемое значение

1, если данные успешно записаны; иначе 0.
## int open ( const char * name , const char * mode , bool use_cache = true ) const

Открывает файл с заданным режимом доступа: rb — для открытия файла на чтение; wb — для создания нового файла.
- r - Открытие только для чтения. Поток позиционируется на начало файла.
- r+ - Открытие для чтения и записи. Поток позиционируется на начало файла.
- w - Усекает файл до нулевой длины или создаёт файл для записи. Поток позиционируется на начало файла.
- w+ - Открытие для чтения и записи. Файл создаётся, если он не существует, иначе усекается до нулевой длины. Поток позиционируется на начало файла.
- a - Открытие для добавления (запись в конец файла). Файл создаётся, если он не существует. Поток позиционируется на конец файла.
- a+ - Открытие для чтения и добавления (запись в конец файла). Файл создаётся, если он не существует. Начальная позиция для чтения — начало файла, но вывод всегда добавляется в конец файла.
- b - Для бинарных файлов. В противном случае файл считается текстовым, и Windows заменяет **\n** на **\n\r** в текстовых файлах.


### Аргументы

- *const char ** **name** - Имя открываемого файла.
- *const char ** **mode** - Режим доступа.
- *bool* **use_cache**

### Возвращаемое значение

true, если файл успешно открыт (или создан, если указан режим доступа wb); иначе false.
## int seekCur ( size_t offset ) const

Устанавливает смещение индикатора позиции файла относительно его текущей позиции.
### Аргументы

- *size_t* **offset** - Смещение индикатора позиции файла от текущей позиции, в байтах.

### Возвращаемое значение

Возвращает 1, если смещение индикатора позиции файла успешно установлено; иначе 0.
## int seekEnd ( size_t offset ) const

Устанавливает смещение индикатора позиции файла относительно конца файла.
### Аргументы

- *size_t* **offset** - Смещение индикатора позиции файла от конца файла, в байтах.

### Возвращаемое значение

Возвращает 1, если смещение индикатора позиции файла успешно установлено; иначе 0.
## int seekSet ( size_t offset ) const

Устанавливает смещение индикатора позиции файла относительно начала файла.
### Аргументы

- *size_t* **offset** - Смещение индикатора позиции файла от начала файла, в байтах.

### Возвращаемое значение

1, если смещение успешно установлено; иначе 0.
## size_t tell ( ) const

Возвращает текущее смещение индикатора позиции файла.
### Возвращаемое значение

Смещение в байтах от начала файла.
## int truncate ( )
