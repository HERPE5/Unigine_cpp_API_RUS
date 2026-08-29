# Unigine::Plugins::IG::Entity Class (CPP)

**Header:** #include <plugins/Unigine/IG/UnigineIG.h>


Этот класс представляет интерфейс Entity IG.

> **Notice:** Плагин IG должен быть загружен.


## Entity Class

### Перечисления

## STATE

| Name | Description |
|---|---|
| **STATE_INACTIVE** = 0 | Сущность неактивна. |
| **STATE_ACTIVE** = 1 | Сущность активна. |
| **STATE_DESTROYED** = 2 | Сущность уничтожена. |

## CLAMP

| Name | Description |
|---|---|
| **CLAMP_NO_CLAMP** = 0 | Привязка высоты для сущности отключена. |
| **CLAMP_NON_CONFORMAL** = 1 | Параметр высоты задаёт смещение сущности над уровнем земли. |
| **CLAMP_CONFORMAL** = 2 | Параметр высоты задаёт смещение сущности над уровнем моря. |

## CLAMP_HEIGHT_MODE

| Name | Description |
|---|---|
| **CLAMP_HEIGHT_MODE_RELATIVE** = 0 | Режим привязки высоты, при котором сущность привязывается к земле, а высота вычисляется от земли. |
| **CLAMP_HEIGHT_MODE_IGNORE** = 1 | Режим привязки высоты, при котором сущность привязывается к земле, а высота игнорируется. |

## ANIMATION_DIRECTION

| Name | Description |
|---|---|
| **ANIMATION_DIRECTION_FORWARD** = 0 | Прямое направление воспроизведения анимации сущности. |
| **ANIMATION_DIRECTION_BACKWARD** = 1 | Обратное направление воспроизведения анимации сущности. |

## ANIMATION_LOOP

| Name | Description |
|---|---|
| **ANIMATION_LOOP_ONESHOT** = 0 | Однократный режим воспроизведения анимации сущности. |
| **ANIMATION_LOOP_CONTINUOUS** = 1 | Непрерывный режим воспроизведения анимации сущности. |

## ANIMATION_STATE

| Name | Description |
|---|---|
| **ANIMATION_STATE_STOP** = 0 | Остановить воспроизведение анимации сущности. |
| **ANIMATION_STATE_PAUSE** = 1 | Приостановить воспроизведение анимации сущности. |
| **ANIMATION_STATE_PLAY** = 2 | Запустить воспроизведение анимации сущности. |
| **ANIMATION_STATE_CONTINUE** = 3 | Возобновить воспроизведение анимации сущности. |

## COORDINATE_SYSTEM

| Name | Description |
|---|---|
| **COORDINATE_SYSTEM_WORLD** = 0 | Если опорная система координат установлена в это значение, а сущность является сущностью верхнего уровня (не дочерней), скорость и ускорение задаются относительно базы данных. Линейная скорость и ускорение описывают путь вдоль поверхности геоида и над ней. Угловая скорость и ускорение описывают поворот относительно опорной плоскости. Если сущность является дочерней, скорость и ускорение задаются относительно локальной системы координат родителя. |
| **COORDINATE_SYSTEM_LOCAL** = 1 | Если опорная система координат установлена в это значение, скорость и ускорение задаются относительно локальной системы координат сущности. |

### Методы класса

---

## long long getID ( ) const

Возвращает уникальный ID экземпляра сущности.
### Возвращаемое значение

ID сущности.
## Ptr < Node > getNode ( ) const

Возвращает узел, назначенный сущности.
### Возвращаемое значение

Узел, назначенный сущности.
## Ptr < NodeReference > getNodeReference ( ) const

Возвращает ссылку на узел, назначенную сущности.
### Возвращаемое значение

NodeReference, назначенная сущности.
## void setGeoPosition ( const Math::dvec3& position , double timestamp )

Задаёт положение сущности в геокоординатах (широта, долгота, высота).
### Аргументы

- *const  Math::dvec3&* **position** - Новые задаваемые геокоординаты положения сущности.
- *double* **timestamp** - Временная метка, указывающая момент времени, для которого задаётся положение сущности в геокоординатах.

## Math:: dvec3 getGeoPosition ( ) const

Возвращает текущее положение сущности в геокоординатах (широта, долгота, высота).
### Возвращаемое значение

Координаты положения сущности.
> **Notice:** Геокоординаты будут возвращены, если родительская сущность не назначена, иначе будут возвращены локальные координаты.


## void setRotationEuler ( const Math::vec3& euler , double timestamp )

Задаёт поворот сущности в указанный момент времени.
### Аргументы

- *const  Math::vec3&* **euler** - Задаваемые углы Эйлера поворота сущности.
- *double* **timestamp** - Временная метка, указывающая момент времени, для которого задаётся поворот.

## Math:: vec3 getRotationEuler ( ) const

Возвращает текущие углы Эйлера поворота сущности.
### Возвращаемое значение

Углы Эйлера поворота сущности.
## void setPositionOffset ( const Math::dvec3& offset , double timestamp )

Задаёт смещение положения сущности в указанный момент времени.
### Аргументы

- *const  Math::dvec3&* **offset** - Задаваемое смещение положения сущности.
- *double* **timestamp** - Временная метка, указывающая момент времени, для которого задаётся смещение положения.

## Math:: dvec3 getPositionOffset ( ) const

Возвращает текущее смещение положения сущности.
### Возвращаемое значение

Текущее смещение положения сущности.
## void setType ( long long id )

Задаёт тип сущности. ID типа сущности определяется в [entity definition section](../../../../../ig/config.md#config_entities) конфигурационного файла IG следующим образом:
```xml
<entity_types>
	<entity id="111" name="b52">
	</entity>
</entity_types>

```

 Установка типа в 0 удаляет сущность со сцены.
### Аргументы

- *long long* **id** - Задаваемый тип сущности. 0 удаляет сущность со сцены.

## long long getType ( ) const

Возвращает тип сущности. ID типа сущности определяется в [entity definition section](../../../../../ig/config.md#config_entities) конфигурационного файла IG следующим образом:
```xml
<entity_types>
	<entity id="111" name="b52">
	</entity>
</entity_types>

```


### Возвращаемое значение

Тип сущности.
## long long getInternalType ( ) const

Возвращает внутренний тип сущности.
### Возвращаемое значение

Внутренний тип сущности.
## void setAutoTypeMatchEnabled ( bool enabled )

Задаёт значение, указывающее, следует ли включить автоматическое сопоставление типов для сущности. Если включено, предотвращает установку несуществующего типа для сущности.
### Аргументы

- *bool* **enabled** - true, чтобы включить автоматическое сопоставление типов для сущности; false — чтобы отключить.

## bool isAutoTypeMatchEnabled ( ) const

Возвращает значение, указывающее, включено ли автоматическое сопоставление типов для сущности. Если включено, предотвращает установку несуществующего типа для сущности.
### Возвращаемое значение

true, если автоматическое сопоставление типов для сущности включено; иначе false.
## void setState ( Entity::STATE id )

Задаёт состояние сущности.
### Аргументы

- *[Entity::STATE](../../../../../api/library/plugins/ig/api/class.entity_cpp.md#STATE)* **id** - Задаваемое состояние сущности.

## Entity::STATE getState ( ) const

Возвращает текущее состояние сущности.
### Возвращаемое значение

Текущее состояние сущности.
## void setCollision ( bool enabled )

Задаёт значение, указывающее, следует ли включить обнаружение столкновений для сущности.
### Аргументы

- *bool* **enabled** - true, чтобы включить обнаружение столкновений для сущности; false — чтобы отключить.

## bool isCollision ( ) const

Возвращает значение, указывающее, включено ли обнаружение столкновений для сущности.
### Возвращаемое значение

Значение параметра **Collision Detection Enable**. true — обнаружение столкновений для сущности должно быть включено; false — обнаружение столкновений для сущности должно быть отключено.
## void setParent ( Entity * entity )

Присоединяет сущность как дочернюю к указанной родительской сущности.
### Аргументы

- *[Entity](../../../../../api/library/plugins/ig/api/class.entity_cpp.md) ** **entity** - Родительская сущность.

## void unparent ( )

Отсоединяет сущность от её родителя.
## long long getParentID ( ) const

Возвращает ID родителя сущности.
### Возвращаемое значение

ID родителя сущности.
## int getAttachState ( ) const

Возвращает значение параметра **Attach State**. Оно указывает, присоединена ли сущность как дочерняя к [parent](#getParentID_llong).
### Возвращаемое значение

Значение параметра **Attach State**. 1 — сущность должна быть или остаться присоединённой к сущности, указанной [Parent ID parameter](#getParentID_llong); 0 — сущность должна быть отсоединена от родителя.
## void setAlpha ( int byte_value )

Задаёт значение alpha, определяющее прозрачность геометрии сущности.
### Аргументы

- *int* **byte_value** - Задаваемое значение alpha.

## int getAlpha ( ) const

Возвращает текущее значение alpha, определяющее прозрачность геометрии сущности.
### Возвращаемое значение

Значение alpha.
## void setInheritAlpha ( bool enabled )

Задаёт значение, указывающее, использует ли сущность значение alpha своего [parent](#getParentID_llong).
### Аргументы

- *bool* **enabled** - true — сущность должна использовать значение alpha своего [parent](#getParentID_llong); false — сущность должна использовать собственное значение alpha.

## bool isInheritAlpha ( ) const

Возвращает значение, указывающее, использует ли сущность значение alpha своего [parent](#getParentID_llong).
### Возвращаемое значение

true, если сущность использует значение alpha своего [parent](#getParentID_llong); иначе false.
## void setGroundClamp ( Entity::CLAMP clamp )

Задаёт значение параметра **Ground/Ocean Clamp**.
### Аргументы

- *[Entity::CLAMP](../../../../../api/library/plugins/ig/api/class.entity_cpp.md#CLAMP)* **clamp** - Значение параметра **Ground/Ocean Clamp**.

## Entity::CLAMP getGroundClamp ( ) const

Возвращает значение параметра **Ground/Ocean Clamp**.
### Возвращаемое значение

Значение параметра **Ground/Ocean Clamp**.
## void setGroundClampHeightMode ( Entity::CLAMP_HEIGHT_MODE height_mode )

Задаёт значение параметра **clamp height mode**, используемого для [clamping](#setGroundClamp_int_void). По умолчанию Ground Clamp Height Mode установлен в RELATIVE — сущность привязывается к земле, а высота вычисляется от земли. При установке режима в IGNORE сущность привязывается к земле, а высота игнорируется.
### Аргументы

- *[Entity::CLAMP_HEIGHT_MODE](../../../../../api/library/plugins/ig/api/class.entity_cpp.md#CLAMP_HEIGHT_MODE)* **height_mode** - Значение параметра **Clamp height mode**.

## Entity::CLAMP_HEIGHT_MODE getGroundClampHeightMode ( ) const

Возвращает значение параметра **clamp height mode**, используемого для [clamping](#setGroundClamp_int_void). По умолчанию Ground Clamp Height Mode установлен в RELATIVE — сущность привязывается к земле, а высота вычисляется от земли. При установке режима в IGNORE сущность привязывается к земле, а высота игнорируется.
### Возвращаемое значение

Значение параметра **Clamp height mode**.
## Math:: dvec3 getGroundClampPoint ( ) const

Возвращает текущие координаты точки привязки к земле для сущности. Привязка выполняется относительно земли и уровня моря.
## void setAnimationDirection ( Entity::ANIMATION_DIRECTION animation_direction )

Задаёт направление воспроизведения анимации сущности.
### Аргументы

- *[Entity::ANIMATION_DIRECTION](../../../../../api/library/plugins/ig/api/class.entity_cpp.md#ANIMATION_DIRECTION)* **animation_direction** - Направление воспроизведения анимации сущности.

## Entity::ANIMATION_DIRECTION getAnimationDirection ( ) const

Возвращает текущее направление воспроизведения анимации сущности.
### Возвращаемое значение

Направление воспроизведения анимации сущности.
## void setAnimationLoop ( Entity::ANIMATION_LOOP animation_loop )

Задаёт режим воспроизведения анимации сущности.
### Аргументы

- *[Entity::ANIMATION_LOOP](../../../../../api/library/plugins/ig/api/class.entity_cpp.md#ANIMATION_LOOP)* **animation_loop** - Режим воспроизведения анимации сущности.

## Entity::ANIMATION_LOOP getAnimationLoop ( ) const

Возвращает текущий режим воспроизведения анимации сущности.
### Возвращаемое значение

Режим воспроизведения анимации сущности.
## void setAnimationState ( Entity::ANIMATION_STATE animation_state )

Задаёт состояние воспроизведения анимации сущности.
### Аргументы

- *[Entity::ANIMATION_STATE](../../../../../api/library/plugins/ig/api/class.entity_cpp.md#ANIMATION_STATE)* **animation_state** - Состояние воспроизведения анимации сущности.

## Entity::ANIMATION_STATE getAnimationState ( ) const

Возвращает текущее состояние воспроизведения анимации сущности.
### Возвращаемое значение

Состояние воспроизведения анимации сущности.
## void setInterpolation ( bool id )

Задаёт значение, указывающее, включены ли интерполяция и экстраполяция.
### Аргументы

- *bool* **id** - true, чтобы включить интерполяцию и экстраполяцию; false — чтобы отключить.

## bool isInterpolation ( ) const

Возвращает значение, указывающее, включены ли интерполяция и экстраполяция.
### Возвращаемое значение

true, если интерполяция и экстраполяция включены; иначе false.
## void clearInterpolationData ( )

Очищает все данные интерполяции для сущности.
## void setExtrapolationCoordSystem ( Entity::COORDINATE_SYSTEM animation_state )

Задаёт опорную систему координат, к которой применяются линейная и угловая скорость и ускорение. Если опорная система координат установлена в [WORLD](#COORDINATE_SYSTEM_WORLD), а сущность является сущностью верхнего уровня (не дочерней), скорость и ускорение задаются относительно базы данных. Линейная скорость и ускорение описывают путь вдоль поверхности геоида и над ней. Угловая скорость и ускорение описывают поворот относительно опорной плоскости. Если сущность является дочерней, скорость и ускорение задаются относительно локальной системы координат родителя. Если опорная система координат установлена в [LOCAL](#COORDINATE_SYSTEM_LOCAL), скорость и ускорение задаются относительно локальной системы координат сущности.
### Аргументы

- *[Entity::COORDINATE_SYSTEM](../../../../../api/library/plugins/ig/api/class.entity_cpp.md#COORDINATE_SYSTEM)* **animation_state** - Система координат, используемая для экстраполяции.

## Entity::COORDINATE_SYSTEM getExtrapolationCoordSystem ( ) const

Возвращает текущую опорную систему координат, к которой применяются линейная и угловая скорость и ускорение. Если опорная система координат установлена в [WORLD](#COORDINATE_SYSTEM_WORLD), а сущность является сущностью верхнего уровня (не дочерней), скорость и ускорение задаются относительно базы данных. Линейная скорость и ускорение описывают путь вдоль поверхности геоида и над ней. Угловая скорость и ускорение описывают поворот относительно опорной плоскости. Если сущность является дочерней, скорость и ускорение задаются относительно локальной системы координат родителя. Если опорная система координат установлена в [LOCAL](#COORDINATE_SYSTEM_LOCAL), скорость и ускорение задаются относительно локальной системы координат сущности.
### Возвращаемое значение

Система координат экстраполяции.
## void setVelocity ( const Math::dvec3& linear , const Math::vec3& angular_deg )

Задаёт линейную и угловую скорость сущности.
### Аргументы

- *const  Math::dvec3&* **linear** - Задаваемый вектор линейной скорости.
- *const  Math::vec3&* **angular_deg** - Вектор угловой скорости (roll, pitch, yaw), в градусах в секунду.

## Math:: dvec3 getLinearVelocity ( ) const

Возвращает линейную скорость сущности.
### Возвращаемое значение

Вектор линейной скорости.
## Math:: vec3 getAngularVelocity ( ) const

Возвращает угловую скорость сущности.
### Возвращаемое значение

Вектор угловой скорости (roll, pitch, yaw), в градусах в секунду.
## void setAcceleration ( const Math::dvec3& linear , const Math::vec3& angular_deg )

Задаёт линейное и угловое ускорение сущности.
### Аргументы

- *const  Math::dvec3&* **linear** - Задаваемый вектор линейного ускорения.
- *const  Math::vec3&* **angular_deg** - Вектор углового ускорения (roll, pitch, yaw), в градусах в секунду.

## Math:: dvec3 getLinearAcceleration ( ) const

Возвращает линейное ускорение сущности.
### Возвращаемое значение

Вектор линейного ускорения.
## Math:: vec3 getAngularAcceleration ( ) const

Возвращает угловое ускорение сущности.
### Возвращаемое значение

Вектор углового ускорения (roll, pitch, yaw), в градусах в секунду.
## void setTerminalVelocity ( float terminal_velocity )

Задаёт максимальную скорость, которую может поддерживать сущность.
### Аргументы

- *float* **terminal_velocity** - Максимальная скорость, которую может поддерживать сущность.

## float getTerminalVelocity ( ) const

Возвращает текущую максимальную скорость, которую может поддерживать сущность.
### Возвращаемое значение

Максимальная скорость, которую может поддерживать сущность.
## void setRetardationRate ( float retardation_rate )

Задаёт скорость замедления — параметр, определяющий величину ускорения, приложенного против вектора мгновенной линейной скорости сущности. Используется для симуляции сопротивления и других сил трения, действующих на сущность.
### Аргументы

- *float* **retardation_rate** - Скорость замедления — параметр, определяющий величину ускорения, приложенного против вектора мгновенной линейной скорости сущности.

## float getRetardationRate ( ) const

Возвращает текущую скорость замедления — параметр, определяющий величину ускорения, приложенного против вектора мгновенной линейной скорости сущности. Используется для симуляции сопротивления и других сил трения, действующих на сущность.
### Возвращаемое значение

Скорость замедления — параметр, определяющий величину ускорения, приложенного против вектора мгновенной линейной скорости сущности.
## void restoreGeoPosition ( )

Сбрасывает текущую трансформацию сущности к последним известным геокоординатам. Рекомендуется в таких случаях, как изменение параметров проекции на лету.
## Component * getComponent ( int id , bool auto_create )

Возвращает [interface](../../../../../api/library/plugins/ig/api/class.component_cpp.md) указанного компонента.
### Аргументы

- *int* **id** - ID компонента.
- *bool* **auto_create** - true, чтобы автоматически создать компонент с указанным ID, если он ещё не существует; false - чтобы вернуть nullptr, если компонент не существует.

### Возвращаемое значение

Интерфейс компонента, если он существует, иначе nullptr.
## Vector < IG::Component * > getComponents ( ) const

Возвращает список всех [components](../../../../../api/library/plugins/ig/api/class.component_cpp.md), связанных с сущностью.
## ArticulatedPart * getArticulatedPart ( int id , bool auto_create )

Возвращает [interface](../../../../../api/library/plugins/ig/api/class.articulatedpart_cpp.md) указанной сочленённой части.
### Аргументы

- *int* **id** - ID сочленённой части.
- *bool* **auto_create** - true, чтобы автоматически создать сочленённую часть с указанным ID, если она ещё не существует; false - чтобы вернуть nullptr, если сочленённая часть не существует.

### Возвращаемое значение

Интерфейс сочленённой части, если он существует, иначе nullptr.
## Vector < IG::ArticulatedPart * > getArticulatedParts ( ) const

Возвращает список всех [articulated parts](../../../../../api/library/plugins/ig/api/class.articulatedpart_cpp.md), связанных с сущностью.
## CollisionSegment * getCollisionSegment ( int id , bool auto_create )

Возвращает интерфейс указанного сегмента столкновения.
### Аргументы

- *int* **id** - ID сегмента столкновения.
- *bool* **auto_create** - true, чтобы автоматически создать сегмент столкновения с указанным ID, если он ещё не существует; false - чтобы вернуть nullptr, если сегмент столкновения не существует.

### Возвращаемое значение

Интерфейс сегмента столкновения, если он существует, иначе nullptr.
## Vector < IG::CollisionSegment * > getCollisionSegments ( ) const

Возвращает список всех [collision segments](../../../../../api/library/plugins/ig/api/class.collisionsegment_cpp.md), связанных с сущностью.
## CollisionVolume * getCollisionVolume ( int id , bool auto_create )

Возвращает интерфейс указанного объёма столкновения.
### Аргументы

- *int* **id** - ID объёма столкновения.
- *bool* **auto_create** - true, чтобы автоматически создать объём столкновения с указанным ID, если он ещё не существует; false - чтобы вернуть nullptr, если объём столкновения не существует.

### Возвращаемое значение

Интерфейс объёма столкновения, если он существует, иначе nullptr.
## Vector < IG::CollisionVolume * > getCollisionVolumes ( ) const

Возвращает список всех [collision volumes](../../../../../api/library/plugins/ig/api/class.collisionvolume_cpp.md), связанных с сущностью.
## Vector < Ptr < Node > > getObjects ( ) const

Возвращает вектор всех узлов, составляющих сущность.
### Возвращаемое значение

Вектор узлов, составляющих сущность.
## int64_t getEntityTypeFromDIS ( uint8_t kind , uint8_t domain , uint16_t country , uint8_t cat , uint8_t subcat , uint8_t spec , uint8_t extra )

Возвращает идентификатор типа сущности (определённый в [entity definition section](../../../../../ig/config.md#config_entities)) на основе заданных аргументов. Этот метод используется для преобразования ID сущности из типа DIS в тип IG.
Тип также можно задать с помощью ID в стиле DIS:
```xml
<entity_types>
	<entity id="1.2.222.4.14.0.0" name="vehicle">
	</entity>
</entity_types>

```


### Аргументы

- *uint8_t* **kind** - Вид сущности
- *uint8_t* **domain** - Домен
- *uint16_t* **country** - Страна
- *uint8_t* **cat** - Категория
- *uint8_t* **subcat** - Подкатегория
- *uint8_t* **spec** - Уточнение
- *uint8_t* **extra** - Дополнительно

### Возвращаемое значение

Идентификатор типа сущности
## bool getDISTypeFromEntityType ( int64_t entity_type , uint8_t & kind , uint8_t & domain , uint16_t & country , uint8_t & cat , uint8_t & subcat , uint8_t & spec , uint8_t & extra )

Возвращает идентификатор типа сущности в стиле DIS (устанавливая значения для указанных аргументов: kind, domain и т.д.) на основе указанного ID типа сущности, используемого в IG (см. [entity definition section](../../../../../ig/config.md#config_entities)). Этот метод используется для преобразования ID сущности из типа IG в тип DIS.
Тип сущности можно задать с помощью ID в стиле DIS:
```xml
<entity_types>
	<entity id="1.2.222.4.14.0.0" name="vehicle">
	</entity>
</entity_types>

```


### Аргументы

- *int64_t* **entity_type** - Идентификатор типа сущности.
- *uint8_t &* **kind** - Вид
- *uint8_t &* **domain** - Домен
- *uint16_t &* **country** - Страна
- *uint8_t &* **cat** - Категория
- *uint8_t &* **subcat** - Подкатегория
- *uint8_t &* **spec** - Уточнение
- *uint8_t &* **extra** - Дополнительно

### Возвращаемое значение

true, если преобразование ID типа сущности из IG в DIS выполнено успешно, иначе false.
## int64_t getEntityIDFromDISID ( uint16_t app , uint16_t id )

Возвращает результат преобразования ID сущности из DIS в IG. В случае DIS сущность идентифицируется парой: Application ID + Entity ID (Site ID игнорируется IG).
### Аргументы

- *uint16_t* **app** - Application ID.
- *uint16_t* **id** - Entity ID, используемый в приложении DIS.

### Возвращаемое значение

Entity ID, используемый в IG.
## void getDISIDFromEntityID ( int64_t entity_id , uint16_t & app , uint16_t & id )

Преобразует ID сущности из IG в DIS и помещает результат в переменные, указанные через аргументы **app** и **id**. В случае DIS сущность идентифицируется парой: Application ID + Entity ID (Site ID игнорируется IG).
### Аргументы

- *int64_t* **entity_id** - Entity ID, используемый в IG.
- *uint16_t &* **app** - Application ID, используемый в DIS.
- *uint16_t &* **id** - Entity ID, используемый в DIS.

## const char * getTypeName ( ) const

Возвращает имя типа сущности (определённого в [entity definition section](../../../../../ig/config.md#config_entities)).
### Возвращаемое значение

Имя типа сущности.
## bool isPrespawned ( ) const

Возвращает значение, указывающее, является ли сущность предварительно созданной (т.е. созданной через UnigineEditor и уже существующей в мире).
### Возвращаемое значение

true, если сущность предварительно создана, иначе false.
## void * addOnBeforeChangeTypeCallback ( CallbackBase2 < int64_t, int64_t > * func )

Добавляет колбэк, вызываемый перед изменением типа сущности.
### Аргументы

- *[CallbackBase2](../../../../../api/library/common/callbacks/class.callbackbase2_cpp.md) < int64_t, int64_t > ** **func** - Указатель на колбэк. Функция колбэка должна иметь следующую сигнатуру: *void (int64_t **old_type**, int64_t **old_type**)*.

### Возвращаемое значение

ID последнего добавленного колбэка Before Change Type, если колбэк был успешно добавлен; иначе **nullptr**. Этот ID можно использовать для [remove](#removeOnBeforeChangeTypeCallback_void_ptr_bool) этого колбэка при необходимости.
## bool removeOnBeforeChangeTypeCallback ( void * id )

Удаляет указанный колбэк из списка колбэков Before Change Type.
### Аргументы

- *void ** **id** - ID колбэка, полученный при [adding a Before Change Type callback](#addOnBeforeChangeTypeCallback_CallbackBase2_ptr_void_ptr).

### Возвращаемое значение

true, если колбэк Before Change Type с указанным ID был успешно удалён; иначе false.
## void clearOnBeforeChangeTypeCallback ( )

Очищает все [added](#addOnBeforeChangeTypeCallback_CallbackBase2_ptr_void_ptr) колбэки Before Change Type.
## void * addOnAfterChangeTypeCallback ( CallbackBase2 < int64_t, int64_t > * func )

Добавляет колбэк, вызываемый после изменения типа сущности.
### Аргументы

- *[CallbackBase2](../../../../../api/library/common/callbacks/class.callbackbase2_cpp.md) < int64_t, int64_t > ** **func** - Указатель на колбэк. Функция колбэка должна иметь следующую сигнатуру: *void (int64_t **old_type**, int64_t **old_type**)*.

### Возвращаемое значение

ID последнего добавленного колбэка After Change Type, если колбэк был успешно добавлен; иначе **nullptr**. Этот ID можно использовать для [remove](#removeOnAfterChangeTypeCallback_void_ptr_bool) этого колбэка при необходимости.
## bool removeOnAfterChangeTypeCallback ( void * id )

Удаляет указанный колбэк из списка колбэков After Change Type.
### Аргументы

- *void ** **id** - ID колбэка, полученный при [adding a After Change Type callback](#addOnAfterChangeTypeCallback_CallbackBase2_ptr_void_ptr).

### Возвращаемое значение

true, если колбэк After Change Type с указанным ID был успешно удалён; иначе false.
## void clearOnAfterChangeTypeCallback ( )

Очищает все [added](#addOnAfterChangeTypeCallback_CallbackBase2_ptr_void_ptr) колбэки After Change Type.
## void setOwnerID ( int id )

Задаёт ID владельца сущности.
### Аргументы

- *int* **id** - Задаваемый ID владельца.

## int getOwnerID ( ) const

Возвращает ID владельца сущности.
### Возвращаемое значение

ID владельца сущности.
## void setDebugDescription ( String description )

Задаёт отладочное описание сущности.
### Аргументы

- *[String](../../../../../api/library/common/class.string_cpp.md)* **description** - Задаваемое отладочное описание.

## String getDebugDescription ( ) const

Возвращает отладочное описание сущности.
### Возвращаемое значение

Отладочное описание сущности.
## void setEntityName ( const char * name )

Задаёт имя сущности.
### Аргументы

- *const char ** **name** - Задаваемое имя сущности.

## const char * getEntityName ( ) const

Возвращает имя сущности.
### Возвращаемое значение

Имя сущности.
