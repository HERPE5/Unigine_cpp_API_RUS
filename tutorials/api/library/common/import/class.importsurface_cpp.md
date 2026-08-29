# Unigine::ImportSurface Class (CPP)

**Header:** #include <UnigineImport.h>


Этот класс представляет отдельную поверхность в составе [ImportGeometry](../../../../api/library/common/import/class.importgeometry_cpp.md) — отрисовываемую часть геометрии со своим [material](../../../../api/library/common/import/class.importmaterial_cpp.md), настройками видимости и дистанции затухания, а также ограничивающим прямоугольником.


## ImportSurface Class

### Методы класса

## void setBoundBox ( const Math:: WorldBoundBox & box )

Задаёт новый ограничивающий прямоугольник элемента геометрии.
### Аргументы

- *const  Math::[WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md)&* **box** - Ограничивающий прямоугольник элемента геометрии.

## Math:: WorldBoundBox getBoundBox () const

Возвращает текущий ограничивающий прямоугольник элемента геометрии.
### Возвращаемое значение

Текущий ограничивающий прямоугольник элемента геометрии.
## void setData ( void * data )

Задаёт новые метаданные импортированной поверхности.
### Аргументы

- *void ** **data** - Метаданные поверхности.

## void * getData () const

Возвращает текущие метаданные импортированной поверхности.
### Возвращаемое значение

Текущие метаданные поверхности.
## void setName ( const char * name )

Задаёт новое имя импортированной поверхности.
### Аргументы

- *const char ** **name** - Имя поверхности.

## const char * getName () const

Возвращает текущее имя импортированной поверхности.
### Возвращаемое значение

Текущее имя поверхности.
## void setMaterial ( const Ptr < ImportMaterial >& material )

Задаёт новый материал, назначенный импортированной поверхности.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMaterial](../../../../api/library/common/import/class.importmaterial_cpp.md)>&* **material** - Материал поверхности: экземпляр класса *[ImportMaterial](../../../../api/library/common/import/class.importmaterial_cpp.md)*, если материал назначен импортированной поверхности; иначе **nullptr**

## Ptr < ImportMaterial > getMaterial () const

Возвращает текущий материал, назначенный импортированной поверхности.
### Возвращаемое значение

Текущий материал поверхности: экземпляр класса *[ImportMaterial](../../../../api/library/common/import/class.importmaterial_cpp.md)*, если материал назначен импортированной поверхности; иначе **nullptr**
## void setMaxFadeDistance ( float distance )

Задаёт новое [Maximum Fade Distance](../../../../principles/world_management/index.md#max_fade) для импортированной поверхности.
### Аргументы

- *float* **distance** - Максимальное расстояние затухания, в единицах.

## float getMaxFadeDistance () const

Возвращает текущее [Maximum Fade Distance](../../../../principles/world_management/index.md#max_fade) для импортированной поверхности.
### Возвращаемое значение

Текущее максимальное расстояние затухания, в единицах.
## void setMinFadeDistance ( float distance )

Задаёт новое [Minimum Fade Distance](../../../../principles/world_management/index.md#min_fade) для импортированной поверхности.
### Аргументы

- *float* **distance** - Минимальное расстояние затухания, в единицах.

## float getMinFadeDistance () const

Возвращает текущее [Minimum Fade Distance](../../../../principles/world_management/index.md#min_fade) для импортированной поверхности.
### Возвращаемое значение

Текущее минимальное расстояние затухания, в единицах.
## void setMaxVisibleDistance ( float distance )

Задаёт новое [Maximum Visibility Distance](../../../../principles/world_management/index.md#min_visible) для импортированной поверхности.
### Аргументы

- *float* **distance** - Максимальное расстояние видимости, в единицах.

## float getMaxVisibleDistance () const

Возвращает текущее [Maximum Visibility Distance](../../../../principles/world_management/index.md#min_visible) для импортированной поверхности.
### Возвращаемое значение

Текущее максимальное расстояние видимости, в единицах.
## void setMinVisibleDistance ( float distance )

Задаёт новое [Minimum Visibility Distance](../../../../principles/world_management/index.md#min_visible) для импортированной поверхности.
### Аргументы

- *float* **distance** - Минимальное расстояние видимости, в единицах.

## float getMinVisibleDistance () const

Возвращает текущее [Minimum Visibility Distance](../../../../principles/world_management/index.md#min_visible) для импортированной поверхности.
### Возвращаемое значение

Текущее минимальное расстояние видимости, в единицах.
## void setSourceIndex ( int index )

Задаёт новый индекс поверхности в исходном файле (FBX, glTF).
### Аргументы

- *int* **index** - Индекс поверхности в исходном файле (FBX, glTF).

## int getSourceIndex () const

Возвращает текущий индекс поверхности в исходном файле (FBX, glTF).
### Возвращаемое значение

Текущий индекс поверхности в исходном файле (FBX, glTF).
## void setTargetSurface ( int surface )

Задаёт новый номер целевой поверхности морфинга для импортированной поверхности.
### Аргументы

- *int* **surface** - Номер целевой поверхности морфинга, если есть; иначе -1.

## int getTargetSurface () const

Возвращает текущий номер целевой поверхности морфинга для импортированной поверхности.
### Возвращаемое значение

Текущий номер целевой поверхности морфинга, если есть; иначе -1.
---

## void copyFrom ( const Ptr < ImportSurface > & o )

Копирует данные из указанной исходной поверхности.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportSurface](../../../../api/library/common/import/class.importsurface_cpp.md)> &* **o** - Исходная поверхность.
