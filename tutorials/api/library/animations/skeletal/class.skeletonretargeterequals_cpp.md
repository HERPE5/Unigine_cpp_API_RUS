# SkeletonRetargeterEquals Class (CPP)

**Header:** #include <UnigineSkeleton.h>

**Inherits from:** SkeletonRetargeter


Этот класс реализует ретаргетинг между двумя скелетами, имеющими идентичные иерархии суставов (одинаковое количество суставов, одинаковые отношения родитель-потомок). Это простейшая и наиболее эффективная стратегия ретаргетинга — трансформации суставов передаются напрямую по индексу без какого-либо переотображения.


## SkeletonRetargeterEquals Class

---

## static SkeletonRetargeterEqualsPtr create ( const UGUID & first_file_guid , const UGUID & second_file_guid )

Создаёт ретаргетер для двух скелетов с идентичными иерархиями, идентифицированных их файловыми GUID.
### Аргументы

- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **first_file_guid** - GUID файла первого скелета.
- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **second_file_guid** - GUID файла второго скелета.

## static SkeletonRetargeterEqualsPtr create ( const char * first_file , const char * second_file )

Создаёт ретаргетер для двух скелетов с идентичными иерархиями, идентифицированных их путями к файлам.
### Аргументы

- *const char ** **first_file** - Путь к файлу первого скелета.
- *const char ** **second_file** - Путь к файлу второго скелета.
