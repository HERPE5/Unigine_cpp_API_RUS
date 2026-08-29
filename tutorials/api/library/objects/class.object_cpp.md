# Класс Object (CPP)

**Header:** #include <UnigineObjects.h>

**Inherits from:** Node


[Object](../../../objects/index.md) with a set of [surfaces](../../../principles/world_structure/index.md#surfaces) to represent geometry. Rendering materials are [assigned](#setMaterial_Material_int_void) to each surface of the object. A [physical body](#setBody_Body_int_int) can be assigned to the object.


## Класс Object

### Перечисления

## SURFACE_SHADOW_MODE

| Название | Описание |
|---|---|
| **SURFACE_SHADOW_MODE_MIXED** = 0 | Режим отбрасывания теней как от статичных, так и от динамических источников света. |
| **SURFACE_SHADOW_MODE_DYNAMIC** = 1 | Режим отбрасывания теней только если поверхность освещена динамическим источником света. |

## SURFACE_LIGHTING_MODE

| Название | Описание |
|---|---|
| **SURFACE_LIGHTING_MODE_STATIC** = 0 | Оптимизировано для использования в статичном GI, статичных отражениях и кэшированных тенях. |
| **SURFACE_LIGHTING_MODE_DYNAMIC** = 1 | Исключает поверхность из использования в статичном GI и статичных отражениях и подходит для динамических теней. |
| **SURFACE_LIGHTING_MODE_ADVANCED** = 2 | Позволяет вручную настраивать все параметры, связанные с освещением. |

### Методы класса

---

## bool setBody ( const Ptr < Body > & body , bool update = 1 )

Назначает физическое тело объекту.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body** - Физическое тело для назначения объекту.
- *bool* **update** - Флаг обновления. Установите этот флаг, чтобы обновить объект после назначения ему указанного тела.

### Возвращаемое значение

true, если указанное тело успешно задано; иначе false.
## void setBody ( const Ptr < Body > & body )

Назначает физическое тело объекту.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body** - Физическое тело для назначения объекту.

## Ptr < Body > getBody ( ) const

Возвращает физическое тело, назначенное объекту.
### Возвращаемое значение

Тело, назначенное объекту, или **NULL** (**0**), если тело не назначено.
## Ptr < BodyRigid > getBodyRigid ( ) const

Возвращает твёрдое тело, назначенное объекту.
### Возвращаемое значение

Твёрдое тело, назначенное объекту, или **NULL** (**0**), если тело не назначено или не является твёрдым.
## Math:: BoundBox getBoundBox ( int surface ) const

Возвращает ограничивающий параллелепипед указанной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Ограничивающий параллелепипед.
## Math:: BoundSphere getBoundSphere ( int surface ) const

Возвращает ограничивающую сферу указанной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Ограничивающая сфера.
## void setBakeToEnvProbe ( bool enabled , int surface )

Задаёт значение, указывающее, будет ли указанная поверхность запекаться в пробники окружения.
### Аргументы

- *bool* **enabled** - **1**, чтобы включить запекание указанной поверхности в пробники окружения, **0** - чтобы отключить.
- *int* **surface** - Номер поверхности.

## bool getBakeToEnvProbe ( int surface ) const

Возвращает значение, указывающее, будет ли указанная поверхность запекаться в пробники окружения.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

true, если указанная поверхность будет запекаться в пробники окружения; иначе false.
## void setBakeToGI ( bool enabled , int surface )

Задаёт значение, указывающее, будет ли указанная поверхность запекаться в GI (воксельные пробники и lightmap).
### Аргументы

- *bool* **enabled** - **1**, чтобы включить запекание указанной поверхности в GI, **0** - чтобы отключить.
- *int* **surface** - Номер поверхности.

## bool getBakeToGI ( int surface ) const

Возвращает значение, указывающее, будет ли указанная поверхность запекаться в GI (воксельные пробники и lightmap).
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

**1**, если указанная поверхность будет запекаться в GI; иначе **0**.
## void setCastEnvProbeShadow ( bool enabled , int surface )

Включает или отключает отбрасывание теней от пробников окружения указанной поверхностью.
### Аргументы

- *bool* **enabled** - **1**, чтобы включить отбрасывание теней от пробников окружения указанной поверхностью, **0**, чтобы отключить.
- *int* **surface** - Номер поверхности.

## bool getCastEnvProbeShadow ( int surface ) const

Возвращает значение, указывающее, включено ли отбрасывание теней от пробников окружения указанной поверхностью.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

**1**, если отбрасывание теней от пробников окружения указанной поверхностью включено; иначе **0**.
## void setCastShadow ( bool enabled , int surface )

Включает или отключает отбрасывание теней от источников света, отличных от World, для указанной поверхности.
### Аргументы

- *bool* **enabled** - **1**, если указанная поверхность должна отбрасывать тени; иначе **0**.
- *int* **surface** - Номер поверхности.

## bool getCastShadow ( int surface ) const

Возвращает флаг отбрасывания тени поверхностью, указывающий, должна ли указанная поверхность отбрасывать тени от источников света, отличных от World.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Положительное число, если указанная поверхность отбрасывает тени; иначе **0**.
## void setCastWorldShadow ( bool enabled , int surface )

Включает или отключает отбрасывание теней от мировых источников света для указанной поверхности.
### Аргументы

- *bool* **enabled** - true, если указанная поверхность должна отбрасывать мировые тени; иначе false.
- *int* **surface** - Номер поверхности.

## bool getCastWorldShadow ( int surface ) const

Возвращает флаг отбрасывания мировой тени поверхностью, указывающий, должна ли указанная поверхность отбрасывать тени от мировых источников света.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Положительное число, если указанная поверхность отбрасывает мировые тени; иначе **0**.
## void setCollision ( bool enabled , int surface )

Включает или отключает [collision detection](../../../principles/physics/collision/index.md) для указанной поверхности.
### Аргументы

- *bool* **enabled** - **1**, если обнаружение столкновений включено для указанной поверхности; иначе **0**.
- *int* **surface** - Номер поверхности.

## bool getCollision ( int surface ) const

Возвращает флаг столкновений поверхности, указывающий, включено ли [collision detection](../../../principles/physics/collision/index.md) для указанной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Положительное число, если обнаружение столкновений включено для указанной поверхности; иначе **0**.
## void setCollisionMask ( int mask , int surface )

Задаёт маску столкновений для указанной поверхности. Два объекта сталкиваются, если у обоих совпадающие маски.
### Аргументы

- *int* **mask** - Маска столкновений поверхности.
- *int* **surface** - Номер поверхности.

## int getCollisionMask ( int surface ) const

Возвращает маску столкновений для указанной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Маска столкновений поверхности.
## void setEnabled ( bool enabled )

Включает или отключает узел.
### Аргументы

- *bool* **enabled** - true, чтобы включить узел, false, чтобы отключить.

## void setEnabled ( bool enabled , int surface )

Включает или отключает поверхность с указанным номером. Отключённая поверхность не рендерится, не участвует в обнаружении столкновений и не отбрасывает тени.
```cpp
// временно отключаем первую поверхность объекта (индекс 0)
obj->setEnabled(false, 0);	// (включить/отключить, индекс поверхности)

//...

// снова включаем первую поверхность, если она отключена
if(!obj->isEnabled(0))
	obj->setEnabled(true, 0);

```


### Аргументы

- *bool* **enabled** - true, чтобы включить поверхность, false, чтобы отключить.
- *int* **surface** - Номер поверхности.

## bool isEnabled ( int surface ) const

Возвращает значение, указывающее, включена ли указанная поверхность.
```cpp
// временно отключаем первую поверхность объекта (индекс 0)
obj->setEnabled(false, 0);	// (включить/отключить, индекс поверхности)

//...

// снова включаем первую поверхность, если она отключена
if(!obj->isEnabled(0))
	obj->setEnabled(true, 0);

```


### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

true, если поверхность включена; иначе false.
## bool isEnabled ( ) const

Возвращает значение, указывающее, включены ли узел и его родительские узлы.
### Возвращаемое значение

Положительное число, если узел и его родительские узлы включены; иначе **0**.
## void setIntersection ( bool enabled , int surface )

Включает или отключает пересечения с указанной поверхностью.
### Аргументы

- *bool* **enabled** - true, чтобы включить пересечения с указанной поверхностью, false, чтобы отключить.
- *int* **surface** - Номер поверхности.

## bool getIntersection ( const Math::Vec3& p0 , const Math::Vec3& p1 , const Ptr < ObjectIntersectionTexCoord > & v , int surface ) const

Проверяет, есть ли пересечение линии с указанной поверхностью. Если функция возвращает true, данные о текстурных координатах точки пересечения будут помещены в объект [ObjectIntersectionTexCoord](../../../api/library/objects/class.objectintersectiontexcoord_cpp.md).
> **Notice:** Следующие объекты имеют индивидуальные параметры, управляющие точностью обнаружения пересечений для них:
> - *[ObjectLandscapeTerrain](../../../api/library/objects/landscape_terrain/class.objectlandscapeterrain_cpp.md#setIntersectionPrecision_float_void)*
> - *[ObjectWaterGlobal](../../../api/library/objects/class.objectwaterglobal_cpp.md#intersections)*


### Аргументы

- *const  Math::Vec3&* **p0** - Координаты начальной точки линии (локальные).
- *const  Math::Vec3&* **p1** - Координаты конечной точки линии (локальные).
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[ObjectIntersectionTexCoord](../../../api/library/objects/class.objectintersectiontexcoord_cpp.md)> &* **v** - Экземпляр класса [ObjectIntersectionTexCoord](../../../api/library/objects/class.objectintersectiontexcoord_cpp.md) для хранения соответствующих данных пересечения.
- *int* **surface** - Номер поверхности.

### Возвращаемое значение

true, если есть пересечение с указанной поверхностью; иначе false.
## bool getIntersection ( int surface ) const

Возвращает флаг пересечений поверхности. Этот флаг указывает, включены ли пересечения с указанной поверхностью.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

true, если пересечения с указанной поверхностью включены; иначе false.
## bool getIntersection ( const Math::Vec3& p0 , const Math::Vec3& p1 , const Ptr < ObjectIntersectionNormal > & v , int surface ) const

Проверяет, есть ли пересечение линии с указанной поверхностью. Если функция возвращает true, данные о нормали в точке пересечения будут помещены в объект [ObjectIntersectionNormal](../../../api/library/objects/class.objectintersectionnormal_cpp.md).
> **Notice:** Следующие объекты имеют индивидуальные параметры, управляющие точностью обнаружения пересечений для них:
> - *[ObjectLandscapeTerrain](../../../api/library/objects/landscape_terrain/class.objectlandscapeterrain_cpp.md#setIntersectionPrecision_float_void)*
> - *[ObjectWaterGlobal](../../../api/library/objects/class.objectwaterglobal_cpp.md#intersections)*

### Аргументы

- *const  Math::Vec3&* **p0** - Координаты начальной точки линии (локальные).
- *const  Math::Vec3&* **p1** - Координаты конечной точки линии (локальные).
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[ObjectIntersectionNormal](../../../api/library/objects/class.objectintersectionnormal_cpp.md)> &* **v** - Экземпляр класса [ObjectIntersectionNormal](../../../api/library/objects/class.objectintersectionnormal_cpp.md) для хранения соответствующих данных пересечения.
- *int* **surface** - Номер поверхности.

### Возвращаемое значение

true, если есть пересечение с указанной поверхностью; иначе false.
## bool getIntersection ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , int mask , const Ptr < ObjectIntersection > & v , int * ret_surface ) const

Проверяет, есть ли пересечение линии с поверхностью с указанной маской пересечений. Если функция возвращает true, данные о точке пересечения будут помещены в объект [ObjectIntersection](../../../api/library/objects/class.objectintersection_cpp.md), а номер первой пересечённой поверхности - в возвращаемую переменную.
> **Notice:** Следующие объекты имеют индивидуальные параметры, управляющие точностью обнаружения пересечений для них:
> - *[ObjectLandscapeTerrain](../../../api/library/objects/landscape_terrain/class.objectlandscapeterrain_cpp.md#setIntersectionPrecision_float_void)*
> - *[ObjectWaterGlobal](../../../api/library/objects/class.objectwaterglobal_cpp.md#intersections)*

### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Координаты начальной точки линии (локальные).
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Координаты конечной точки линии (локальные).
- *int* **mask** - Маска пересечений.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[ObjectIntersection](../../../api/library/objects/class.objectintersection_cpp.md)> &* **v** - Экземпляр класса [ObjectIntersection](../../../api/library/objects/class.objectintersection_cpp.md) для хранения соответствующих данных пересечения.
- *int ** **ret_surface** - Индекс пересечённой поверхности.

### Возвращаемое значение

true, если пересечение есть; иначе false.
## bool getIntersection ( const Math::Vec3& p0 , const Math:: Vec3 & p1 , const Ptr < ObjectIntersection > & v , int surface ) const

Проверяет, есть ли пересечение линии с указанной поверхностью. Если функция возвращает true, данные о точке пересечения будут помещены в объект [ObjectIntersection](../../../api/library/objects/class.objectintersection_cpp.md).
> **Notice:** Следующие объекты имеют индивидуальные параметры, управляющие точностью обнаружения пересечений для них:
> - *[ObjectLandscapeTerrain](../../../api/library/objects/landscape_terrain/class.objectlandscapeterrain_cpp.md#setIntersectionPrecision_float_void)*
> - *[ObjectWaterGlobal](../../../api/library/objects/class.objectwaterglobal_cpp.md#intersections)*

### Аргументы

- *const  Math::Vec3&* **p0** - Координаты начальной точки линии (локальные).
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Координаты конечной точки линии (локальные).
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[ObjectIntersection](../../../api/library/objects/class.objectintersection_cpp.md)> &* **v** - Экземпляр класса [ObjectIntersection](../../../api/library/objects/class.objectintersection_cpp.md) для хранения соответствующих данных пересечения.
- *int* **surface** - Номер поверхности.

### Возвращаемое значение

true, если есть пересечение с указанной поверхностью; иначе false.
## bool getIntersection ( const Math::Vec3& p0 , const Math::Vec3& p1 , int mask , const Ptr < ObjectIntersectionNormal > & v , int * ret_surface ) const

Проверяет, есть ли пересечение линии с поверхностью с указанной маской пересечений. Если функция возвращает true, данные о нормали в точке пересечения будут помещены в объект [ObjectIntersectionNormal](../../../api/library/objects/class.objectintersectionnormal_cpp.md), а номер первой пересечённой поверхности - в возвращаемую переменную.
> **Notice:** Следующие объекты имеют индивидуальные параметры, управляющие точностью обнаружения пересечений для них:
> - *[ObjectLandscapeTerrain](../../../api/library/objects/landscape_terrain/class.objectlandscapeterrain_cpp.md#setIntersectionPrecision_float_void)*
> - *[ObjectWaterGlobal](../../../api/library/objects/class.objectwaterglobal_cpp.md#intersections)*

### Аргументы

- *const  Math::Vec3&* **p0** - Координаты начальной точки линии (локальные).
- *const  Math::Vec3&* **p1** - Координаты конечной точки линии (локальные).
- *int* **mask** - Маска пересечений.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[ObjectIntersectionNormal](../../../api/library/objects/class.objectintersectionnormal_cpp.md)> &* **v** - Экземпляр класса [ObjectIntersectionNormal](../../../api/library/objects/class.objectintersectionnormal_cpp.md) для хранения соответствующих данных пересечения.
- *int ** **ret_surface** - Индекс пересечённой поверхности.

### Возвращаемое значение

true, если пересечение есть; иначе false.
## bool getIntersection ( const Math::Vec3& p0 , const Math::Vec3& p1 , int mask , const Ptr < ObjectIntersectionTexCoord > & v , int * ret_surface ) const

Проверяет, есть ли пересечение линии с поверхностью с указанной маской пересечений. Если функция возвращает true, данные о текстурных координатах точки пересечения будут помещены в объект [ObjectIntersectionNormal](../../../api/library/objects/class.objectintersectionnormal_cpp.md), а номер первой пересечённой поверхности - в возвращаемую переменную.
> **Notice:** Следующие объекты имеют индивидуальные параметры, управляющие точностью обнаружения пересечений для них:
> - *[ObjectLandscapeTerrain](../../../api/library/objects/landscape_terrain/class.objectlandscapeterrain_cpp.md#setIntersectionPrecision_float_void)*
> - *[ObjectWaterGlobal](../../../api/library/objects/class.objectwaterglobal_cpp.md#intersections)*

### Аргументы

- *const  Math::Vec3&* **p0** - Координаты начальной точки линии (локальные).
- *const  Math::Vec3&* **p1** - Координаты конечной точки линии (локальные).
- *int* **mask** - Маска пересечений.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[ObjectIntersectionTexCoord](../../../api/library/objects/class.objectintersectiontexcoord_cpp.md)> &* **v** - Экземпляр класса [ObjectIntersectionTexCoord](../../../api/library/objects/class.objectintersectiontexcoord_cpp.md) для хранения соответствующих данных пересечения.
- *int ** **ret_surface** - Индекс пересечённой поверхности.

### Возвращаемое значение

true, если пересечение есть; иначе false.
## bool getIntersection ( const Math::Vec3& p0 , const Math::Vec3& p1 , int mask , Math:: Vec3 * ret_point , Math:: vec3 * OUT_ret_normal , Math:: vec4 * OUT_ret_texcoord , int * ret_index , int * OUT_ret_instance , int * ret_surface ) const

Проверяет, есть ли пересечение линии с поверхностью с указанной маской пересечений. Если функция возвращает true, данные о пересечении (точка, нормаль и текстурные координаты) и номер первой пересечённой поверхности будут помещены в соответствующие возвращаемые переменные.
> **Notice:** Следующие объекты имеют индивидуальные параметры, управляющие точностью обнаружения пересечений для них:
> - *[ObjectLandscapeTerrain](../../../api/library/objects/landscape_terrain/class.objectlandscapeterrain_cpp.md#setIntersectionPrecision_float_void)*
> - *[ObjectWaterGlobal](../../../api/library/objects/class.objectwaterglobal_cpp.md#intersections)*

### Аргументы

- *const  Math::Vec3&* **p0** - Координаты начальной точки линии (локальные).
- *const  Math::Vec3&* **p1** - Координаты конечной точки линии (локальные).
- *int* **mask** - Маска пересечений.
- *Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) ** **ret_point** - Координаты точки пересечения (локальная система координат объекта). Передайте NULL, если этот параметр не требуется.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) ** **OUT_ret_normal** - Координаты вектора нормали в точке пересечения. Передайте NULL, если этот параметр не требуется. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.
- *Math::[vec4](../../../api/library/math/class.vec4_cpp.md) ** **OUT_ret_texcoord** - Текстурные координаты точки пересечения (vec4, где vec4.xy - для первого (0) UV-канала, vec4.zw - для второго (1) UV-канала). Передайте NULL, если этот параметр не требуется. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.
- *int ** **ret_index** - Номер пересечённого треугольника. Передайте NULL, если этот параметр не требуется.
- *int ** **OUT_ret_instance** - Номер пересечённого экземпляра. Передайте NULL, если этот параметр не требуется. > **Notice:** Номер пересечённого экземпляра можно получить для следующих классов: > - *[ObjectMeshSkinned](../../../api/library/objects/class.objectmeshskinned_cpp.md)* > - *[ObjectMeshCluster](../../../api/library/objects/class.objectmeshcluster_cpp.md)* > - *[ObjectMeshSplineCluster](../../../api/library/objects/class.objectmeshsplinecluster_cpp.md)* > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.
- *int ** **ret_surface** - Номер пересечённой поверхности. Передайте NULL, если этот параметр не требуется.

### Возвращаемое значение

true, если найдено хотя бы одно пересечение; иначе false.
## bool getIntersection ( const Math:: Vec3 & p0 , const Math::Vec3& p1 , Math:: Vec3 * ret_point , Math:: vec3 * OUT_ret_normal , Math:: vec4 * OUT_ret_texcoord , int * ret_index , int * OUT_ret_instance , int surface ) const

Проверяет, есть ли пересечение линии с указанной поверхностью. Если функция возвращает true, данные о пересечении (точка, нормаль и текстурные координаты) будут помещены в соответствующие возвращаемые переменные.
> **Notice:** Следующие объекты имеют индивидуальные параметры, управляющие точностью обнаружения пересечений для них:
> - *[ObjectLandscapeTerrain](../../../api/library/objects/landscape_terrain/class.objectlandscapeterrain_cpp.md#setIntersectionPrecision_float_void)*
> - *[ObjectWaterGlobal](../../../api/library/objects/class.objectwaterglobal_cpp.md#intersections)*

### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Координаты начальной точки линии (локальные).
- *const  Math::Vec3&* **p1** - Координаты конечной точки линии (локальные).
- *Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) ** **ret_point** - Координаты точки пересечения (локальная система координат объекта). Передайте NULL, если этот параметр не требуется.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) ** **OUT_ret_normal** - Координаты вектора нормали в точке пересечения. Передайте NULL, если этот параметр не требуется. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.
- *Math::[vec4](../../../api/library/math/class.vec4_cpp.md) ** **OUT_ret_texcoord** - Текстурные координаты точки пересечения (vec4, где vec4.xy - для первого (0) UV-канала, vec4.zw - для второго (1) UV-канала). Передайте NULL, если этот параметр не требуется. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.
- *int ** **ret_index** - Номер пересечённого треугольника. Передайте NULL, если этот параметр не требуется.
- *int ** **OUT_ret_instance** - Номер пересечённого экземпляра. Передайте NULL, если этот параметр не требуется. > **Notice:** Номер пересечённого экземпляра можно получить для следующих классов: > - *[ObjectMeshSkinned](../../../api/library/objects/class.objectmeshskinned_cpp.md)* > - *[ObjectMeshCluster](../../../api/library/objects/class.objectmeshcluster_cpp.md)* > - *[ObjectMeshSplineCluster](../../../api/library/objects/class.objectmeshsplinecluster_cpp.md)* > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.
- *int* **surface** - Номер поверхности.

### Возвращаемое значение

true, если есть пересечение с указанной поверхностью; иначе false.
## void setIntersectionMask ( int mask , int surface )

Задаёт маску пересечений для указанной поверхности.
### Аргументы

- *int* **mask** - Маска пересечений поверхности.
- *int* **surface** - Номер поверхности.

## int getIntersectionMask ( int surface ) const

Возвращает маску пересечений для указанной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Маска пересечений поверхности.
## void setPhysicsIntersection ( bool enabled , int surface )

Включает или отключает физические пересечения (между физическими объектами с телами и формами коллайдеров, или пересечения луча с геометрией коллайдера) для указанной поверхности.
### Аргументы

- *bool* **enabled** - true, чтобы включить физические пересечения с указанной поверхностью, false, чтобы отключить.
- *int* **surface** - Номер поверхности.

## bool getPhysicsIntersection ( int surface ) const

Возвращает флаг физических пересечений поверхности. Этот флаг указывает, включены ли физические пересечения (между физическими объектами с телами и формами коллайдеров, или пересечения луча с геометрией коллайдера) с указанной поверхностью.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

true, если пересечения с указанной поверхностью включены; иначе false.
## void setPhysicsIntersectionMask ( int mask , int surface )

Задаёт [physics intersection mask](../../../principles/bit_masking/index.md#physics_intersection_mask) для поверхности с указанным номером.
### Аргументы

- *int* **mask** - Маска физических пересечений поверхности.
- *int* **surface** - Номер поверхности.

## int getPhysicsIntersectionMask ( int surface ) const

Возвращает [physics intersection mask](../../../principles/bit_masking/index.md#physics_intersection_mask) для поверхности с указанным номером.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Маска физических пересечений, заданная для указанной поверхности.
## void setShadowMask ( int mask , int surface )

Задаёт маску теней для указанной поверхности.
Чтобы тень от поверхности объекта отображалась для источника света, эта маска должна совпадать (хотя бы одним битом) со следующими:

- [Light source shadow mask](../../../api/library/lights/class.light_cpp.md#setShadowMask_int_void)
- [Material shadow mask](../../../api/library/rendering/class.material_cpp.md#setShadowMask_int_void), назначенного этой поверхности


### Аргументы

- *int* **mask** - Маска теней поверхности.
- *int* **surface** - Номер поверхности.

## int getShadowMask ( int surface ) const

Возвращает маску теней для указанной поверхности.
Чтобы тень от поверхности объекта отображалась для источника света, эта маска должна совпадать (хотя бы одним битом) со следующими:

- [Light source shadow mask](../../../api/library/lights/class.light_cpp.md#setShadowMask_int_void)
- [Material shadow mask](../../../api/library/rendering/class.material_cpp.md#setShadowMask_int_void), назначенного этой поверхности


### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Маска теней поверхности.
## Ptr < Material > getMaterial ( int surface ) const

Возвращает материал, используемый для указанной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Умный указатель на материал.
## Ptr < Material > getMaterialInherit ( int surface )

Наследует материал поверхности (то есть создаёт экземпляр материала). Изменения, внесённые в новый экземпляр материала, не влияют на исходный материал.
> **Notice:** Дочерний материал будет создан только один раз, все последующие вызовы этого метода будут возвращать первый созданный дочерний материал.


### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Умный указатель на унаследованный материал.
## bool isMaterialInherited ( int surface ) const

Возвращает значение, указывающее, унаследован ли материал указанной поверхности. Изменения, внесённые в экземпляр материала, не влияют на исходный материал.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Положительное число, если материал унаследован; иначе **0**.
## void clearMaterialInherit ( int surface )

Удаляет унаследованный материал и восстанавливает исходный (родительский) материал для указанной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности.

## void setMaterialParameterInt ( const char * name , int parameter , int surface )

Задаёт значение указанного целочисленного параметра материала поверхности.
> **Notice:** При первом вызове этот метод создаёт копию исходного материала (что эквивалентно методу [getMaterialInherit](#getMaterialInherit_int_Material)).


### Аргументы

- *const char ** **name** - Имя параметра.
- *int* **parameter** - Значение параметра.
- *int* **surface** - Номер поверхности.

## int getMaterialParameterInt ( const char * name , int surface ) const

Возвращает значение указанного целочисленного параметра материала поверхности.
### Аргументы

- *const char ** **name** - Имя параметра.
- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Значение параметра.
## void setMaterialParameterInt2 ( const char * name , const Math:: ivec2 & parameter , int surface )

Задаёт значение указанного параметра [*ivec2*](../../../api/library/math/class.ivec2_cpp.md) материала поверхности.
> **Notice:** При первом вызове этот метод создаёт копию исходного материала (что эквивалентно методу [getMaterialInherit](#getMaterialInherit_int_Material)).


### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **parameter** - Значение параметра.
- *int* **surface** - Номер поверхности.

## Math:: ivec2 getMaterialParameterInt2 ( const char * name , int surface ) const

Возвращает значение указанного параметра [*ivec2*](../../../api/library/math/class.ivec2_cpp.md) материала поверхности.
### Аргументы

- *const char ** **name** - Имя параметра.
- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Значение параметра.
## void setMaterialParameterInt3 ( const char * name , const Math:: ivec3 & parameter , int surface )

Задаёт значение указанного параметра [*ivec3*](../../../api/library/math/class.ivec3_cpp.md) материала поверхности.
> **Notice:** При первом вызове этот метод создаёт копию исходного материала (что эквивалентно методу [getMaterialInherit](#getMaterialInherit_int_Material)).


### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[ivec3](../../../api/library/math/class.ivec3_cpp.md) &* **parameter** - Значение параметра.
- *int* **surface** - Номер поверхности.

## Math:: ivec3 getMaterialParameterInt3 ( const char * name , int surface ) const

Возвращает значение указанного параметра [*ivec3*](../../../api/library/math/class.ivec3_cpp.md) материала поверхности.
### Аргументы

- *const char ** **name** - Имя параметра.
- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Значение параметра.
## void setMaterialParameterInt4 ( const char * name , const Math:: ivec4 & parameter , int surface )

Задаёт значение указанного параметра [*ivec4*](../../../api/library/math/class.ivec4_cpp.md) материала поверхности.
> **Notice:** При первом вызове этот метод создаёт копию исходного материала (что эквивалентно методу [getMaterialInherit](#getMaterialInherit_int_Material)).


### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[ivec4](../../../api/library/math/class.ivec4_cpp.md) &* **parameter** - Значение параметра.
- *int* **surface** - Номер поверхности.

## Math:: ivec4 getMaterialParameterInt4 ( const char * name , int surface ) const

Возвращает значение указанного параметра [*ivec4*](../../../api/library/math/class.ivec4_cpp.md) материала поверхности.
### Аргументы

- *const char ** **name** - Имя параметра.
- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Значение параметра.
## void setMaterialParameterFloat ( const char * name , float parameter , int surface )

Задаёт значение указанного параметра типа float материала поверхности.
> **Notice:** При первом вызове этот метод создаёт копию исходного материала (что эквивалентно методу [getMaterialInherit](#getMaterialInherit_int_Material)).


### Аргументы

- *const char ** **name** - Имя параметра.
- *float* **parameter** - Значение параметра.
- *int* **surface** - Номер поверхности.

## float getMaterialParameterFloat ( const char * name , int surface ) const

Возвращает значение указанного параметра типа float материала поверхности.
### Аргументы

- *const char ** **name** - Имя параметра.
- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Значение параметра.
## void setMaterialParameterFloat2 ( const char * name , const Math:: vec2 & parameter , int surface )

Задаёт значение указанного параметра [*vec2*](../../../api/library/math/class.vec2_cpp.md) материала поверхности.
> **Notice:** При первом вызове этот метод создаёт копию исходного материала (что эквивалентно методу [getMaterialInherit](#getMaterialInherit_int_Material)).


### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **parameter** - Значение параметра.
- *int* **surface** - Номер поверхности.

## Math:: vec2 getMaterialParameterFloat2 ( const char * name , int surface ) const

Возвращает значение указанного параметра [*vec2*](../../../api/library/math/class.vec2_cpp.md) материала поверхности.
### Аргументы

- *const char ** **name** - Имя параметра.
- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Значение параметра.
## void setMaterialParameterFloat3 ( const char * name , const Math:: vec3 & parameter , int surface )

Задаёт значение указанного параметра [*vec3*](../../../api/library/math/class.vec3_cpp.md) материала поверхности.
> **Notice:** При первом вызове этот метод создаёт копию исходного материала (что эквивалентно методу [getMaterialInherit](#getMaterialInherit_int_Material)).


### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **parameter** - Значение параметра.
- *int* **surface** - Номер поверхности.

## Math:: vec3 getMaterialParameterFloat3 ( const char * name , int surface ) const

Возвращает значение указанного параметра [*vec3*](../../../api/library/math/class.vec3_cpp.md) материала поверхности.
### Аргументы

- *const char ** **name** - Имя параметра.
- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Значение параметра.
## void setMaterialParameterFloat4 ( const char * name , const Math:: vec4 & parameter , int surface )

Задаёт значение указанного параметра [*vec4*](../../../api/library/math/class.vec4_cpp.md) материала поверхности.
> **Notice:** При первом вызове этот метод создаёт копию исходного материала (что эквивалентно методу [getMaterialInherit](#getMaterialInherit_int_Material)).


### Аргументы

- *const char ** **name** - Имя параметра.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **parameter** - Значение параметра.
- *int* **surface** - Номер поверхности.

## Math:: vec4 getMaterialParameterFloat4 ( const char * name , int surface ) const

Возвращает значение указанного параметра [*vec4*](../../../api/library/math/class.vec4_cpp.md) материала поверхности.
### Аргументы

- *const char ** **name** - Имя параметра.
- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Значение параметра.
## void setMaterialState ( const char * name , int state , int surface )

Задаёт значение состояния (state) для материала указанной поверхности.
> **Notice:** При первом вызове этот метод создаёт копию исходного материала (что эквивалентно методу [getMaterialInherit](#getMaterialInherit_int_Material)).


### Аргументы

- *const char ** **name** - Имя состояния материала.
- *int* **state** - Значение состояния.
- *int* **surface** - Номер поверхности.

## int getMaterialState ( const char * name , int surface ) const

Возвращает значение состояния (state) материала указанной поверхности.
### Аргументы

- *const char ** **name** - Имя состояния материала.
- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Значение состояния.
## void setMaterialTexture ( const char * name , const char * texture , int surface )

Задаёт путь к указанной текстуре материала указанной поверхности.
> **Notice:** При первом вызове этот метод создаёт копию исходного материала (что эквивалентно методу [getMaterialInherit](#getMaterialInherit_int_Material)).


### Аргументы

- *const char ** **name** - Имя текстуры материала.
- *const char ** **texture** - Путь к файлу текстуры.
- *int* **surface** - Номер поверхности.

## const char * getMaterialTexture ( const char * name , int surface ) const

Возвращает путь к указанной текстуре материала указанной поверхности.
### Аргументы

- *const char ** **name** - Имя текстуры материала.
- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Путь к файлу текстуры.
## void setMinVisibleDistance ( float distance , int surface )

Обновляет минимальную дистанцию видимости указанной поверхности. Это расстояние, начиная с которого поверхность начинает [fade in](#setMinFadeDistance_float_int_void), пока не станет полностью видимой.
### Аргументы

- *float* **distance** - Минимальная дистанция видимости, в единицах. Если задано отрицательное значение, вместо него будет использовано **0**. Значение по умолчанию: -inf.
- *int* **surface** - Номер поверхности.

## float getMinVisibleDistance ( int surface ) const

Возвращает минимальную дистанцию видимости указанной поверхности. Это расстояние, начиная с которого поверхность начинает [fade in](#setMinFadeDistance_float_int_void), пока не станет полностью видимой.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Минимальная дистанция видимости, в единицах.
## void setMaxVisibleDistance ( float distance , int surface )

Обновляет максимальную дистанцию видимости указанной поверхности. Это расстояние, начиная с которого поверхность начинает [fade out](#setMaxFadeDistance_float_int_void), пока не станет полностью невидимой.
### Аргументы

- *float* **distance** - Максимальная дистанция видимости, в единицах. Если задано отрицательное значение, вместо него будет использовано **0**. Значение по умолчанию: inf.
- *int* **surface** - Номер поверхности.

## float getMaxVisibleDistance ( int surface ) const

Возвращает максимальную дистанцию видимости указанной поверхности. Это расстояние, начиная с которого поверхность начинает [fade out](#getMaxFadeDistance_int_float), пока не станет полностью невидимой.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Максимальная дистанция видимости, в единицах.
## void setMinFadeDistance ( float distance , int surface )

Обновляет минимальную дистанцию проявления (fade-in) указанной поверхности. На протяжении этой дистанции поверхность плавно становится видимой за счёт [alpha fade](../../../code/console/index.md#render_alpha_fade). Отсчитывается начиная с [minimum visible distance](#getMinVisibleDistance_int_float).
### Аргументы

- *float* **distance** - Минимальная дистанция проявления, в единицах. Если задано отрицательное значение, вместо него будет использовано **0**. Значение по умолчанию: 0.
- *int* **surface** - Номер поверхности.

## float getMinFadeDistance ( int surface ) const

Возвращает минимальную дистанцию проявления (fade-in) указанной поверхности. На протяжении этой дистанции поверхность плавно становится видимой за счёт [alpha fade](../../../code/console/index.md#render_alpha_fade). Отсчитывается начиная с [minimum visible distance](#getMinVisibleDistance_int_float).
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Минимальная дистанция проявления, в единицах.
## void setMaxFadeDistance ( float distance , int surface )

Обновляет максимальную дистанцию исчезновения (fade-out) указанной поверхности. На протяжении этой дистанции поверхность плавно становится невидимой за счёт [alpha fade](../../../code/console/index.md#render_alpha_fade). Отсчитывается начиная с [maximum visible distance](#getMaxVisibleDistance_int_float).
### Аргументы

- *float* **distance** - Максимальная дистанция исчезновения, в единицах. Если задано отрицательное значение, вместо него будет использовано **0**. Значение по умолчанию: 0.
- *int* **surface** - Номер поверхности.

## float getMaxFadeDistance ( int surface ) const

Возвращает максимальную дистанцию исчезновения (fade-out) указанной поверхности. На протяжении этой дистанции поверхность плавно становится невидимой за счёт [alpha fade](../../../code/console/index.md#render_alpha_fade). Отсчитывается начиная с [maximum visible distance](#getMaxVisibleDistance_int_float).
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Максимальная дистанция исчезновения, в единицах.
## void setMinParent ( int parent , int surface )

Задаёт номер родительской поверхности минимального LOD.
### Аргументы

- *int* **parent** - Номер родительской поверхности минимального LOD.
- *int* **surface** - Номер поверхности.

## int getMinParent ( int surface ) const

Возвращает номер родительской поверхности минимального LOD.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Номер родительской поверхности минимального LOD.
## void setMaxParent ( int parent , int surface )

Задаёт номер родительской поверхности максимального LOD.
### Аргументы

- *int* **parent** - Номер родительской поверхности максимального LOD.
- *int* **surface** - Номер поверхности.

## int getMaxParent ( int surface ) const

Возвращает номер родительской поверхности максимального LOD.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Номер родительской поверхности максимального LOD.
## int getNumSurfaces ( ) const

Возвращает количество поверхностей объекта.
> **Notice:** Для удобства *[ObjectMeshDynamic::create()](../../../api/library/objects/class.objectmeshdynamic_cpp.md#ObjectMeshDynamic_constPtrMesh_int)* инициализирует объект одной внутренней поверхностью с именем "`dynamic`". Первый вызов *[addSurface()](../../../api/library/objects/class.objectmeshdynamic_cpp.md#addSurface_cstr_void)* просто присваивает этой поверхности пользовательское имя, не изменяя общее количество поверхностей. Чтобы создать дополнительные поверхности, вызовите *[addSurface()](../../../api/library/objects/class.objectmeshdynamic_cpp.md#addSurface_cstr_void)* снова.


### Возвращаемое значение

## int getNumTriangles ( int surface ) const

Возвращает количество треугольников, составляющих указанную поверхность.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Количество треугольников.
## void setParent ( int parent , int surface )

Задаёт или очищает родительскую поверхность для указанной поверхности.
### Аргументы

- *int* **parent** - Номер родительской поверхности или **-1**, чтобы очистить родителя.
- *int* **surface** - Номер поверхности.

## int getParent ( int surface ) const

Возвращает номер родительской поверхности для указанной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Номер родительской поверхности. Если возвращается -1, родительская поверхность для указанной поверхности не задана.
## int setSurfaceProperty ( const char * name , const char * pattern )

Задаёт новое свойство для указанной поверхности.
### Аргументы

- *const char ** **name** - Имя нового свойства.
- *const char ** **pattern** - Шаблон (строка с [regular expression](../../../api/library/common/class.regexp_cpp.md#intro)), с которым будут сопоставляться имена поверхностей.

### Возвращаемое значение

1, если свойство успешно задано; иначе 0.
## int setSurfaceProperty ( const char * name , int surface )

Задаёт новое свойство для указанной поверхности.
### Аргументы

- *const char ** **name** - Имя нового свойства.
- *int* **surface** - Номер поверхности.

### Возвращаемое значение

1, если свойство успешно задано; иначе 0.
## int setSurfaceProperty ( const UGUID & guid , int surface )

Задаёт новое свойство для указанной поверхности.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) свойства.
- *int* **surface** - Номер поверхности.

### Возвращаемое значение

1, если свойство успешно задано; иначе 0.
## int setSurfaceProperty ( const UGUID & guid , const char * pattern )

Задаёт новое свойство для указанной поверхности (поверхностей).
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) свойства.
- *const char ** **pattern** - Шаблон (строка с [regular expression](../../../api/library/common/class.regexp_cpp.md#intro)), с которым будут сопоставляться имена поверхностей.

### Возвращаемое значение

1, если свойство успешно задано; иначе 0.
## int setSurfaceProperty ( const Ptr < Property > & property , int surface )

Задаёт новое свойство для указанной поверхности.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Property](../../../api/library/common/class.property_cpp.md)> &* **property** - Умный указатель на свойство.
- *int* **surface** - Номер поверхности.

### Возвращаемое значение

1, если свойство успешно задано; иначе 0.
## int setSurfaceProperty ( const Ptr < Property > & property , const char * pattern )

Задаёт новое свойство для указанной поверхности (поверхностей).
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Property](../../../api/library/common/class.property_cpp.md)> &* **property** - Умный указатель на свойство.
- *const char ** **pattern** - Шаблон (строка с [regular expression](../../../api/library/common/class.regexp_cpp.md#intro)), с которым будут сопоставляться имена поверхностей.

### Возвращаемое значение

1, если свойство успешно задано; иначе 0.
## Ptr < Property > getSurfaceProperty ( int surface ) const

Возвращает умный указатель на свойство.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Умный указатель на свойство.
## Ptr < Property > getSurfacePropertyInherit ( int surface )

Наследует свойство для конкретного объекта. Все изменения унаследованного свойства не влияют на исходное.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Умный указатель на унаследованное свойство.
## void clearSurfaceProperty ( int surface )

Удаляет назначенное свойство с указанной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности.

## void clearSurfacePropertyInherit ( int surface )

Удаляет унаследованное свойство и восстанавливает исходное (родительское) свойство для указанной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности.

## bool isSurfacePropertyInherited ( int surface ) const

Возвращает значение, указывающее, унаследовано ли указанное свойство.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Положительное число, если свойство поверхности унаследовано; иначе **0**.
## const char * getSurfacePropertyName ( int surface ) const

Возвращает имя свойства указанной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Имя свойства.
## const char * getSurfaceName ( int surface ) const

Возвращает имя указанной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Имя поверхности.
## void setViewportMask ( int mask , int surface )

Задаёт [viewport mask](../../../principles/bit_masking/index.md#viewport) для указанной поверхности. Поверхность объекта отображается, если её маска совпадает с масками игрока (камеры) и материала.
```cpp
// скрываем первую поверхность от камеры, отключая все биты маски
obj->setViewportMask(0, 0);

// восстанавливаем видимость поверхности (у камеры должен быть включён первый бит маски Viewport)
obj->setViewportMask(1, 0);

// включаем все биты с использованием побитового NOT
obj->setViewportMask(~0, 0);

// включаем ТОЛЬКО пятый бит маски
obj->setViewportMask(1 << 4, 0);


```


### Аргументы

- *int* **mask** - Маска viewport поверхности.
- *int* **surface** - Номер поверхности.

## int getViewportMask ( int surface ) const

Возвращает маску viewport для указанной поверхности. Поверхность объекта отображается, если её маска совпадает с масками игрока (камеры) и материала.
```cpp
// получаем маску viewport первой поверхности
int mask = obj->getViewportMask(0);

// проверяем, установлен ли пятый бит
bool isBitSet = (mask >> 4 & 1) != 0;

// проверяем, совпадают ли маски
bool doMasksMatch = (mask & mask2) != 0;


```


### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Маска viewport поверхности.
## Math:: WorldBoundBox getWorldBoundBox ( int surface ) const

Возвращает мировой ограничивающий параллелепипед указанной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Ограничивающий параллелепипед (в мировых координатах).
## Math:: WorldBoundSphere getWorldBoundSphere ( int surface ) const

Возвращает мировую ограничивающую сферу указанной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Ограничивающая сфера (в мировых координатах).
## int findSurface ( const char * name ) const

Ищет поверхность с указанным именем.
### Аргументы

- *const char ** **name** - Имя поверхности.

### Возвращаемое значение

Номер поверхности, если она существует; иначе -1.
## void flushBodyTransform ( )

Принудительно задаёт трансформации тела для узла.
## void render ( Render::PASS pass , int surface )


Отображает необработанную поверхность объекта в текстуру в указанном проходе.


> **Notice:** Все [camera parameters](../../../code/uusl/parameters.md#camera_parameters) должны быть заданы вручную.


**Пример использования**


```cpp
texture_render->bindColorTexture(0, texture);
texture_render->enable();
object->render(Render::PASS_AMBIENT, 0);
texture_render->disable();
texture_render->unbindColorTexture(0);


```


### Аргументы

- *[Render::PASS](../../../api/library/rendering/class.render_cpp.md#PASS)* **pass** - [Render pass](../../../api/library/rendering/class.render_cpp.md#PASS_WIREFRAME).
- *int* **surface** - Номер поверхности.

## void setSoundOcclusion ( float occlusion , int surface )

Задаёт новое значение окклюзии звука для указанной поверхности объекта, определяющее степень её влияния на звуки в случае окклюзии. Чтобы источник звука был перекрыт (occluded) указанной поверхностью, хотя бы один бит его [occlusion mask](#setSoundOcclusionMask_int_int_void) должен совпадать с [occlusion mask of the sound source](../../../api/library/sounds/class.soundsource_cpp.md#setOcclusionMask_int_void).
> **Notice:** [Sound occlusion](../../../api/library/engine/class.sound_cpp.md#setSourceOcclusion_int_void) должна быть включена.


### Аргументы

- *float* **occlusion** - Значение окклюзии в диапазоне **[0.0f, 1.0f]**, задаваемое для указанной поверхности. Значение по умолчанию: 0.0f.

  - 0.0f - без окклюзии, громкость звука остаётся неизменной при окклюзии этой поверхностью.
  - 1.0f - максимальная окклюзия, звук вообще не будет слышен при окклюзии этой поверхностью.
- *int* **surface** - Номер поверхности.

## float getSoundOcclusion ( int surface ) const

Возвращает текущее значение окклюзии звука для указанной поверхности объекта, определяющее степень её влияния на звуки в случае окклюзии. Чтобы источник звука был перекрыт (occluded) указанной поверхностью, хотя бы один бит его [occlusion mask](#setSoundOcclusionMask_int_int_void) должен совпадать с [occlusion mask of the sound source](../../../api/library/sounds/class.soundsource_cpp.md#setOcclusionMask_int_void).
> **Notice:** [Sound occlusion](../../../api/library/engine/class.sound_cpp.md#setSourceOcclusion_int_void) должна быть включена.


### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Текущее значение окклюзии в диапазоне **[0.0f, 1.0f]**, заданное для указанной поверхности.
- 0.0f - без окклюзии, громкость звука остаётся неизменной при окклюзии этой поверхностью.
- 1.0f - максимальная окклюзия, звук вообще не будет слышен при окклюзии этой поверхностью.

Значение по умолчанию: 0.0f.
## void setSoundOcclusionMask ( int mask , int surface )

Задаёт новую маску окклюзии звука для указанной поверхности объекта. Чтобы источник звука был перекрыт (occluded) указанной поверхностью, хотя бы один бит этой маски должен совпадать с [occlusion mask of the sound source](../../../api/library/sounds/class.soundsource_cpp.md#setOcclusionMask_int_void). Каждая поверхность имеет собственное [occlusion value](#setSoundOcclusion_float_int_void), определяющее степень её влияния на звуки в случае окклюзии.
> **Notice:** [Sound occlusion](../../../api/library/engine/class.sound_cpp.md#setSourceOcclusion_int_void) должна быть включена.


### Аргументы

- *int* **mask** - Целое число, каждый бит которого является маской окклюзии источника звука.
- *int* **surface** - Номер поверхности.

## int getSoundOcclusionMask ( int surface ) const

Возвращает маску окклюзии звука для указанной поверхности объекта. Чтобы источник звука был перекрыт (occluded) указанной поверхностью, хотя бы один бит этой маски должен совпадать с [occlusion mask of the sound source](../../../api/library/sounds/class.soundsource_cpp.md#setOcclusionMask_int_void). Каждая поверхность имеет собственное [occlusion value](#setSoundOcclusion_float_int_void), определяющее степень её влияния на звуки в случае окклюзии.
> **Notice:** [Sound occlusion](../../../api/library/engine/class.sound_cpp.md#setSourceOcclusion_int_void) должна быть включена.


### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Целое число, каждый бит которого является маской окклюзии источника звука.
## void setPhysicsFriction ( float value , int surface )

Задаёт коэффициент трения для указанной поверхности. Этот коэффициент позволяет моделировать более грубое трение поверхностей и направлен противоположно направлению движения тела. Учитываются значения параметра трения обеих контактирующих поверхностей. Итоговое вычисленное трение зависит от масс объектов и гравитации, а также от угла между контактирующими поверхностями.
- Чем *выше* значение, тем меньше склонность тела к скольжению.

Трение вычисляется по контакту между физическими телами.
### Аргументы

- *float* **value** - Значение коэффициента трения в диапазоне **[0.0f, 1.0f]**, задаваемое для указанной поверхности.
- *int* **surface** - Номер поверхности.

## float getPhysicsFriction ( int surface ) const

Возвращает текущий коэффициент трения для указанной поверхности. Этот коэффициент позволяет моделировать более грубое трение поверхностей и направлен противоположно направлению движения тела. Учитываются значения параметра трения обеих контактирующих поверхностей. Итоговое вычисленное трение зависит от масс объектов и гравитации, а также от угла между контактирующими поверхностями.
- Чем *выше* значение, тем меньше склонность тела к скольжению.

Трение вычисляется по контакту между физическими телами.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Текущее значение коэффициента трения в диапазоне **[0.0f, 1.0f]**, заданное для указанной поверхности.
## void setPhysicsRestitution ( float value , int surface )

Задаёт коэффициент упругости (restitution) для указанной поверхности. Этот коэффициент определяет степень относительной кинетической энергии, сохраняемой после столкновения. Он определяет, насколько упругим является объект при контакте с другим объектом. Зависит от упругости материалов сталкивающихся тел. Симулируемая упругость, как и [friction](#setPhysicsFriction_float_int_void), учитывает суммарное значение для обоих контактирующих объектов.
- Максимальное значение 1.0f моделирует упругое столкновение. Объекты отскакивают в соответствии с полученным при контакте импульсом.
- Минимальное значение 0.0f моделирует неупругое столкновение. Объекты вообще не отскакивают.

Упругость вычисляется по контакту между физическими телами.
### Аргументы

- *float* **value** - Значение коэффициента упругости в диапазоне **[0.0f, 1.0f]**, задаваемое для указанной поверхности.
- *int* **surface** - Номер поверхности.

## float getPhysicsRestitution ( int surface ) const

Возвращает текущий коэффициент упругости (restitution) для указанной поверхности. Этот коэффициент определяет степень относительной кинетической энергии, сохраняемой после столкновения. Он определяет, насколько упругим является объект при контакте с другим объектом. Зависит от упругости материалов сталкивающихся тел. Симулируемая упругость, как и [friction](#setPhysicsFriction_float_int_void), учитывает суммарное значение для обоих контактирующих объектов.
- Максимальное значение 1.0f моделирует упругое столкновение. Объекты отскакивают в соответствии с полученным при контакте импульсом.
- Минимальное значение 0.0f моделирует неупругое столкновение. Объекты вообще не отскакивают.

Упругость вычисляется по контакту между физическими телами.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Текущее значение коэффициента упругости в диапазоне **[0.0f, 1.0f]**, заданное для указанной поверхности.
## void setShadowMode ( Object::SURFACE_SHADOW_MODE mode , int surface )

Задаёт режим отбрасывания теней для указанной поверхности. Чтобы поверхность отбрасывала тень от источника света (Omni, Proj или World), её режим теней должен быть [adjusted](../../../content/optimization/lights/index.md#static_light) с [shadow mode of the light source](../../../api/library/lights/class.light_cpp.md#setShadowMode_int_void).
### Аргументы

- *[Object::SURFACE_SHADOW_MODE](../../../api/library/objects/class.object_cpp.md#SURFACE_SHADOW_MODE)* **mode** - Режим теней поверхности, который нужно задать, один из следующих:

  - [SURFACE_SHADOW_MODE_DYNAMIC](#SURFACE_SHADOW_MODE_DYNAMIC)
  - [SURFACE_SHADOW_MODE_MIXED](#SURFACE_SHADOW_MODE_MIXED)
- *int* **surface** - Номер целевой поверхности.

## Object::SURFACE_SHADOW_MODE getShadowMode ( int surface ) const

Возвращает режим теней, заданный для указанной поверхности. Чтобы поверхность отбрасывала тень от источника света (Omni, Proj или World), её режим теней должен быть [adjusted](../../../content/optimization/lights/index.md#static_light) с [shadow mode of the light source](../../../api/library/lights/class.light_cpp.md#setShadowMode_int_void).
### Аргументы

- *int* **surface** - Номер целевой поверхности.

### Возвращаемое значение

Режим теней поверхности, один из следующих:
- [SURFACE_SHADOW_MODE_DYNAMIC](#SURFACE_SHADOW_MODE_DYNAMIC)
- [SURFACE_SHADOW_MODE_MIXED](#SURFACE_SHADOW_MODE_MIXED)


## UGUID getLostMaterialGUID ( int surface ) const

Возвращает [GUID](../../../api/library/filesystem/class.uguid_cpp.md) потерянного материала. Если по какой-то причине материал, назначенный указанной поверхности, отсутствует, этот метод можно использовать для получения его GUID.
### Аргументы

- *int* **surface** - Номер целевой поверхности.

### Возвращаемое значение

[GUID](../../../api/library/filesystem/class.uguid_cpp.md) потерянного материала.
## UGUID getLostSurfacePropertyGUID ( int surface ) const

Возвращает [GUID](../../../api/library/filesystem/class.uguid_cpp.md) потерянного свойства поверхности. Если по какой-то причине свойство, назначенное указанной поверхности, отсутствует, этот метод можно использовать для получения его GUID.
### Аргументы

- *int* **surface** - Номер целевой поверхности.

### Возвращаемое значение

[GUID](../../../api/library/filesystem/class.uguid_cpp.md) потерянного свойства.
## bool isVisibleCamera ( ) const

Проверяет, отрисовывается ли объект.
### Возвращаемое значение

**1**, если объект отрисовывается; иначе **0**.
## bool isVisibleShadow ( ) const

Проверяет, отрисовывается ли только тень объекта.
### Возвращаемое значение

**1**, если тень объекта отрисовывается; иначе **0**.
## void setLightingMode ( Object::SURFACE_LIGHTING_MODE mode , int surface )

Задаёт режим освещения для указанной поверхности.
### Аргументы

- *[Object::SURFACE_LIGHTING_MODE](../../../api/library/objects/class.object_cpp.md#SURFACE_LIGHTING_MODE)* **mode** - Режим освещения поверхности, который нужно задать, один из следующих:

  - [SURFACE_LIGHTING_MODE_STATIC](#SURFACE_LIGHTING_MODE_STATIC)
  - [SURFACE_LIGHTING_MODE_DYNAMIC](#SURFACE_LIGHTING_MODE_DYNAMIC)
  - [SURFACE_LIGHTING_MODE_ADVANCED](#SURFACE_LIGHTING_MODE_ADVANCED)
- *int* **surface** - Номер целевой поверхности.

## Object::SURFACE_LIGHTING_MODE getLightingMode ( int surface ) const

Возвращает режим освещения указанной поверхности.
### Аргументы

- *int* **surface** - Номер целевой поверхности.

### Возвращаемое значение

Режим освещения поверхности, один из следующих:
- [SURFACE_LIGHTING_MODE_STATIC](#SURFACE_LIGHTING_MODE_STATIC)
- [SURFACE_LIGHTING_MODE_DYNAMIC](#SURFACE_LIGHTING_MODE_DYNAMIC)
- [SURFACE_LIGHTING_MODE_ADVANCED](#SURFACE_LIGHTING_MODE_ADVANCED)


## void setMaterialFilePath ( const char * path , int surface )

Задаёт материал по пути к файлу для указанной поверхности.
### Аргументы

- *const char ** **path** - Путь к файлу материала.
- *int* **surface** - Номер целевой поверхности.

## void setMaterialFilePath ( const char * path , const char * pattern )

Задаёт материал по пути к файлу для указанных поверхностей.
### Аргументы

- *const char ** **path** - Путь к файлу материала.
- *const char ** **pattern** - Шаблон (строка с [regular expression](../../../api/library/common/class.regexp_cpp.md#intro)), с которым будут сопоставляться имена поверхностей.

## String getMaterialFilePath ( int surface ) const

Возвращает путь к файлу материала, назначенного указанной поверхности.
### Аргументы

- *int* **surface** - Номер целевой поверхности.

### Возвращаемое значение

Путь к файлу материала.
## void setMaterialGUID ( const UGUID & guid , int surface )

Задаёт новый материал с указанным [GUID](../../../api/library/filesystem/class.uguid_cpp.md) для указанной поверхности.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) материала.
- *int* **surface** - Номер целевой поверхности.

## void setMaterialGUID ( const UGUID & guid , const char * pattern )

Задаёт новый материал с указанным [GUID](../../../api/library/filesystem/class.uguid_cpp.md) для указанной поверхности.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) материала.
- *const char ** **pattern** - Шаблон (строка с [regular expression](../../../api/library/common/class.regexp_cpp.md#intro)), с которым будут сопоставляться имена поверхностей.

## UGUID getMaterialGUID ( int surface ) const

Возвращает [GUID](../../../api/library/filesystem/class.uguid_cpp.md) материала указанной поверхности.
### Аргументы

- *int* **surface** - Номер целевой поверхности.

### Возвращаемое значение

[GUID](../../../api/library/filesystem/class.uguid_cpp.md) материала.
## void setMaterial ( const Ptr < Material > & mat , int surface )

Задаёт новый материал для указанной поверхности.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **mat** - Умный указатель на материал.
- *int* **surface** - Номер поверхности.

## void setMaterial ( const Ptr < Material > & mat , const char * pattern )

Задаёт новый материал для указанной поверхности.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **mat** - Умный указатель на материал.
- *const char ** **pattern** - Шаблон (строка с [regular expression](../../../api/library/common/class.regexp_cpp.md#intro)), с которым будут сопоставляться имена поверхностей.

## int getSurfaceStatDrawCalls ( int surface ) const

Возвращает количество вызовов отрисовки (DIP) для поверхности с указанным номером за последний кадр.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Количество вызовов отрисовки (DIP) для указанной поверхности за последний кадр.
## int getSurfaceStatDrawCountViewport ( int surface ) const

Возвращает количество раз, которое поверхность с указанным номером была отрисована в области просмотра за последний кадр.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Количество раз, которое указанная поверхность была отрисована в области просмотра за последний кадр.
## int getSurfaceStatDrawCountReflection ( int surface ) const

Возвращает количество раз, которое поверхность с указанным индексом была отрисована при рендеринге отражений за последний кадр.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Количество раз, которое указанная поверхность была отрисована при рендеринге отражений за последний кадр.
## int getSurfaceStatDrawCountShadow ( int surface ) const

Возвращает количество раз, которое поверхность с указанным индексом была отрисована при рендеринге теней за последний кадр.
```cpp
ObjectMeshStaticPtr mesh;
int total_draw_count_shadows = 0;

// функция-обработчик события, вычисляющая общее количество отрисовок поверхностей Static Mesh

void endscreen_event_handler()
{
	total_draw_count_shadows = 0;

	for (int surf = 0; surf < mesh->getNumSurfaces(); surf++)
	{
		if (mesh->getSurfaceStatFrame(surf) == Engine::get()->getFrame())
		{
				// Эта поверхность была отрисована в текущем кадре, поэтому информация актуальна
			total_draw_count_shadows += mesh->getSurfaceStatDrawCountShadow(surf);
		}
	}
}

// создаём экземпляр класса EventConnection
EventConnection endscreen_event_connection;

int AppWorldLogic::init()
{

	// подписываемся на событие EndScreen с функцией-обработчиком, сохраняя соединение
	Render::getEventEndScreen().connect(endscreen_event_connection, endscreen_event_handler);

	return 1;
}


```


### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Количество раз, которое указанная поверхность была отрисована при рендеринге теней за последний кадр.
## long long getSurfaceStatFrame ( int surface ) const

Возвращает номер [Engine frame](../../../api/library/engine/class.engine_cpp.md#getFrame_int64_t), в котором указанная поверхность отрисовывалась последний раз.
### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Номер кадра, в котором указанная поверхность отрисовывалась последний раз.
