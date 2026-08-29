# SkeletonRetargeterNamesMatching Class (CPP)

**Header:** #include <UnigineSkeleton.h>

**Inherits from:** SkeletonRetargeter


Этот класс реализует ретаргетинг между двумя скелетами путём сопоставления суставов по их именам. Он полезен, когда два скелета имеют разные иерархии, но используют одинаковые или похожие соглашения об именовании суставов. Суставы сопоставляются путём поиска совпадающих пар имён между двумя скелетами.


Сопоставление можно настроить вручную через [setNamesMatching()](#setNamesMatching_VECString_VECString_int) или определить автоматически через [setAutoMatching()](#setAutoMatching_int).


## SkeletonRetargeterNamesMatching Class

---

## static SkeletonRetargeterNamesMatchingPtr create ( const UGUID & first_file_guid , const UGUID & second_file_guid )

Создаёт ретаргетер с сопоставлением по именам для двух скелетов, идентифицированных их файловыми GUID.
### Аргументы

- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **first_file_guid** - GUID файла первого скелета.
- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **second_file_guid** - GUID файла второго скелета.

## static SkeletonRetargeterNamesMatchingPtr create ( const char * first_file , const char * second_file )

Создаёт ретаргетер с сопоставлением по именам для двух скелетов, идентифицированных их путями к файлам.
### Аргументы

- *const char ** **first_file** - Путь к файлу первого скелета.
- *const char ** **second_file** - Путь к файлу второго скелета.

## bool setNamesMatching ( const Vector < String > & first_names , const Vector < String > & second_names )

Вручную устанавливает сопоставление имён суставов между двумя скелетами. Каждая пара элементов с одинаковым индексом в обоих списках определяет сопоставляемую пару.
### Аргументы

- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../../api/library/common/class.string_cpp.md)> &* **first_names** - Список имён суставов первого скелета.
- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../../api/library/common/class.string_cpp.md)> &* **second_names** - Список соответствующих имён суставов второго скелета. Должен иметь ту же длину, что и first_names.

### Возвращаемое значение

true, если сопоставление было успешно установлено; иначе false.
## bool setAutoMatching ( )

Автоматически определяет совпадения имён суставов между двумя скелетами, используя файлы скелетов, указанные при создании.
### Возвращаемое значение

true, если автоматическое сопоставление прошло успешно; иначе false.
## bool setAutoMatching ( const Ptr <ConstSkeleton> & first_skeleton , const Ptr <ConstSkeleton> & second_skeleton )

Автоматически определяет совпадения имён суставов между двумя явно предоставленными экземплярами скелетов.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<ConstSkeleton> &* **first_skeleton** - Первый экземпляр скелета для сопоставления.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<ConstSkeleton> &* **second_skeleton** - Второй экземпляр скелета для сопоставления.

### Возвращаемое значение

true, если автоматическое сопоставление прошло успешно; иначе false.
