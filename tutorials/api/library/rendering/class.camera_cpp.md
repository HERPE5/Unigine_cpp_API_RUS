# Unigine.Camera Class (CPP)

**Header:** #include <UnigineCamera.h>


Класс **Camera** используется для создания новой камеры, её настройки (задания всех необходимых матриц, поля зрения, масок и т.д.), а затем передачи в экземпляр класса [Viewport](../../../api/library/rendering/class.viewport_cpp.md) для рендеринга изображения с этой камеры.

> **Notice:** Экземпляр этого класса **не является узлом (node)**.


Экземпляр камеры может иметь следующие маски:


- маска источника звука (Sound Source mask)
- маска реверберации звука (Sound Reverberation mask)
- маска viewport (Viewport mask)
- маска viewport отражений (Reflection Viewport mask)


Настройки камеры можно задать в разделе [Camera Settings in UnigineEditor](../../../editor2/camera_settings/index.md).


### Пример использования


В этом примере мы создаём экземпляр Camera и игрока [PlayerSpectator](../../../objects/players/spectator/index.md), задаём параметры камеры, назначаем камеру PlayerSpectator и делаем его текущим игроком игры.


В заголовочном файле `AppWorldLogic.h` подключите заголовок `UniginePlayers.h` и объявите умные указатели [PlayerSpectator](../../../api/library/players/class.playerspectator_cpp.md) и Camera.


```cpp
#include <UnigineLogic.h>
#include <UnigineStreams.h>
#include <UniginePlayers.h>

class AppWorldLogic : public Unigine::WorldLogic {

public:

	/* public methods */

private:
	Unigine::PlayerSpectatorPtr playerSpectator;
	Unigine::CameraPtr camera;
};

```


В файле реализации `AppWorldLogic.cpp` выполните следующее:


- Подключите заголовок `UnigineGame.h`, чтобы задать нового игрока с помощью метода *[setPlayer()](../../../api/library/engine/class.game_cpp.md#setPlayer_Player_void)*.
- Используйте директиву **using namespace Unigine**: имена пространства имён Unigine будут внедрены в глобальное пространство имён.
- Задайте необходимые параметры созданного экземпляра *Camera* и назначьте его *PlayerSpectator*.
- Сделайте PlayerSpectator текущим игроком игры.
- Обнулите указатель на PlayerSpectator, чтобы избежать утечек памяти.


Ниже приведены необходимые части кода:


```cpp
#include "AppWorldLogic.h"
#include "UnigineGame.h"

// внедряем имена пространства имён Unigine в глобальное пространство имён
using namespace Unigine;

/* ... */

int AppWorldLogic::init() {

	// создаём новый экземпляр PlayerSpectator и камеры
	playerSpectator = PlayerSpectator::create();
	camera = Camera::create();

	// задаём необходимые параметры камеры: FOV, ZNear, ZFar.
	// добавляем постэффект post_sensor_red к камере
	camera->setFov(110.0f);
	camera->setZNear(0.1f);
	camera->setZFar(10000.0f);

	// назначаем камеру игроку
	playerSpectator->setCamera(camera);

	// задаём позицию и направление взгляда playerSpectator
	playerSpectator->setViewDirection(Math::vec3(0.0f, 1.0f, 0.0f));
	playerSpectator->setWorldPosition(Math::dvec3(-1.6f, -1.7f, 1.7f));

	// назначаем Player синглтон-экземпляру Game
	Game::setPlayer(playerSpectator);

	return 1;
}

/* ... */

int AppWorldLogic::shutdown() {

	// обнуляем указатель на Player
	playerSpectator.clear();

	return 1;
}

```


## Camera Class

### Перечисления

## PROJECTION_MODE

| Name | Description |
|---|---|
| **PROJECTION_MODE_PERSPECTIVE** = 0 | Перспективная проекция. |
| **PROJECTION_MODE_ORTHOGRAPHIC** = 1 | Ортографическая проекция. |

## FOV_FIXED

| Name | Description |
|---|---|
| **FOV_FIXED_VERTICAL** = 0 | Зафиксирован вертикальный компонент FOV. |
| **FOV_FIXED_HORIZONTAL** = 1 | Зафиксирован горизонтальный компонент FOV. |

## FOV_MODE

| Name | Description |
|---|---|
| **FOV_MODE_VERTICAL** = 0 | Режим вертикального FOV. Вертикальное FOV камеры определяется значением [FOV](#setFov_float_void). |
| **FOV_MODE_PHYSICALLY_BASED_CAMERA** = 1 | Физически корректный режим. Горизонтальное FOV физически корректной камеры вычисляется с использованием значений [focal length](#setFocalLength_float_void) и [film gate](#setFilmGate_float_void) по следующей формуле: **FOV_h = 2 * atan(film_gate / (2 * focal_length)) * Consts::RAD2DEG** |

### Методы класса

## int getNumScriptableMaterials () const

Возвращает текущее общее количество [total number of scriptable materials](../../../content/materials/scriptable.md), присоединённых к камере.
### Возвращаемое значение

Текущее количество скриптовых материалов, присоединённых к камере.
## void setReverbMask ( int mask )

Задаёт новую битовую маску, определяющую, какие зоны реверберации могут быть услышаны. Для реверберации звука хотя бы один бит этой маски должен совпадать с маской реверберации источника звука и маской зоны реверберации. Маски источника звука и зоны реверберации могут совпадать с маской камеры по нескольким битам, не обязательно по одному.
### Аргументы

- *int* **mask** - Целое число, каждый бит которого используется для задания маски реверберирующих источников звука и зон реверберации.

## int getReverbMask () const

Возвращает текущую битовую маску, определяющую, какие зоны реверберации могут быть услышаны. Для реверберации звука хотя бы один бит этой маски должен совпадать с маской реверберации источника звука и маской зоны реверберации. Маски источника звука и зоны реверберации могут совпадать с маской камеры по нескольким битам, не обязательно по одному.
### Возвращаемое значение

Текущее целое число, каждый бит которого используется для задания маски реверберирующих источников звука и зон реверберации.
## void setSourceMask ( int mask )

Задаёт новую битовую маску, определяющую, какие звуковые каналы могут быть услышаны. Чтобы источник звука был слышен, его маска должна совпадать с этой хотя бы по одному биту. Кроме того, громкость звукового канала, в котором воспроизводится звук (его номер также зависит от этой маски), не должна быть равна **0**.
### Аргументы

- *int* **mask** - Целое число, каждый бит которого определяет звуковой канал.

## int getSourceMask () const

Возвращает текущую битовую маску, определяющую, какие звуковые каналы могут быть услышаны. Чтобы источник звука был слышен, его маска должна совпадать с этой хотя бы по одному биту. Кроме того, громкость звукового канала, в котором воспроизводится звук (его номер также зависит от этой маски), не должна быть равна **0**.
### Возвращаемое значение

Текущее целое число, каждый бит которого определяет звуковой канал.
## void setReflectionViewportMask ( int mask )

Задаёт новую битовую маску для рендеринга отражений в viewport камеры. Отражения рендерятся в viewport камеры, если маски отражающих материалов совпадают с этой (хотя бы по одному биту).
### Аргументы

- *int* **mask** - Целое число, каждый бит которого используется для задания маски.

## int getReflectionViewportMask () const

Возвращает текущую битовую маску для рендеринга отражений в viewport камеры. Отражения рендерятся в viewport камеры, если маски отражающих материалов совпадают с этой (хотя бы по одному биту).
### Возвращаемое значение

Текущее целое число, каждый бит которого используется для задания маски.
## void setViewportMask ( int mask )

Задаёт новую битовую маску для рендеринга в viewport. Поверхности объектов, материалы, декали, источники света и объекты GUI будут отрендерены в viewport только если их маска viewport совпадает с маской камеры (достаточно одного совпадающего бита).
### Аргументы

- *int* **mask** - Целое число, каждый бит которого используется для задания маски.

## int getViewportMask () const

Возвращает текущую битовую маску для рендеринга в viewport. Поверхности объектов, материалы, декали, источники света и объекты GUI будут отрендерены в viewport только если их маска viewport совпадает с маской камеры (достаточно одного совпадающего бита).
### Возвращаемое значение

Текущее целое число, каждый бит которого используется для задания маски.
## void setObliqueFrustum ( bool frustum )

Задаёт новое значение, указывающее, является ли frustum обзора наклонным (oblique).
> **Notice:** Рекомендуется задавать наклонный (oblique) frustum обзора именно этим методом, так как он не влияет на матрицу проекции. Чтобы задать ближнюю плоскость отсечения, используйте метод [setObliqueFrustumPlane()](#setObliqueFrustumPlane_Vec4_void).


### Аргументы

- *bool* **frustum** - Установите **true**, чтобы включить наклонный frustum обзора; **false** - чтобы отключить его.

## bool isObliqueFrustum () const

Возвращает текущее значение, указывающее, является ли frustum обзора наклонным (oblique).
> **Notice:** Рекомендуется задавать наклонный (oblique) frustum обзора именно этим методом, так как он не влияет на матрицу проекции. Чтобы задать ближнюю плоскость отсечения, используйте метод [setObliqueFrustumPlane()](#setObliqueFrustumPlane_Vec4_void).


### Возвращаемое значение

**true**, если наклонный frustum обзора включён; иначе **false**.
## void setObliqueFrustumPlane ( const Math:: Vec4 & plane )

Задаёт новую наклонную ближнюю плоскость отсечения frustum обзора.
> **Notice:** Этот метод не влияет на матрицу проекции. Чтобы включить наклонный frustum, используйте метод [setObliqueFrustum()](#setObliqueFrustum_int_void).


```cpp
// AppWorldLogic.cpp
#include <UnigineGame.h>
using namespace Unigine;

/* .. */

int AppWorldLogic::update() {
	// здесь пишем код, который должен вызываться перед обновлением каждого кадра рендеринга: указываем все функции, связанные с графикой, которые должны вызываться каждый кадр во время работы приложения
	float time = Game::getTime();

	// инициализация плоскости, которая будет задана как ближняя плоскость отсечения
	Math::Vec4 plane = Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f + Math::sin(time) * 4.0f);

	// получаем камеру
	CameraPtr camera = Game::getPlayer()->getCamera();
	if (camera)
	{
		// включаем наклонный (oblique) frustum
		camera->setObliqueFrustum(1);

		// задаём нашу плоскость как наклонную ближнюю плоскость отсечения
		camera->setObliqueFrustumPlane(plane);
	}

	return 1;
}

/* .. */

```


### Аргументы

- *const  Math::[Vec4](../../../api/library/math/class.vec4_cpp.md)&* **plane** - Мировые координаты наклонной ближней плоскости отсечения (Nx, Ny, Nz, D), где Nx, Ny, Nz - координаты нормали плоскости, D - расстояние от начала координат до плоскости.

## Math:: Vec4 getObliqueFrustumPlane () const

Возвращает текущую наклонную ближнюю плоскость отсечения frustum обзора.
> **Notice:** Этот метод не влияет на матрицу проекции. Чтобы включить наклонный frustum, используйте метод [setObliqueFrustum()](#setObliqueFrustum_int_void).


```cpp
// AppWorldLogic.cpp
#include <UnigineGame.h>
using namespace Unigine;

/* .. */

int AppWorldLogic::update() {
	// здесь пишем код, который должен вызываться перед обновлением каждого кадра рендеринга: указываем все функции, связанные с графикой, которые должны вызываться каждый кадр во время работы приложения
	float time = Game::getTime();

	// инициализация плоскости, которая будет задана как ближняя плоскость отсечения
	Math::Vec4 plane = Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f + Math::sin(time) * 4.0f);

	// получаем камеру
	CameraPtr camera = Game::getPlayer()->getCamera();
	if (camera)
	{
		// включаем наклонный (oblique) frustum
		camera->setObliqueFrustum(1);

		// задаём нашу плоскость как наклонную ближнюю плоскость отсечения
		camera->setObliqueFrustumPlane(plane);
	}

	return 1;
}

/* .. */

```


### Возвращаемое значение

Текущие мировые координаты наклонной ближней плоскости отсечения (Nx, Ny, Nz, D), где Nx, Ny, Nz - координаты нормали плоскости, D - расстояние от начала координат до плоскости.
## void setUp ( const Math:: vec3 & up )

Задаёт новое направление "вверх" для viewport камеры (т.е. наклон viewport камеры).
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md)&* **up** - Вектор направления "вверх". Вектор нормализован к 1.

## Math:: vec3 getUp () const

Возвращает текущее направление "вверх" для viewport камеры (т.е. наклон viewport камеры).
### Возвращаемое значение

Текущий вектор направления "вверх". Вектор нормализован к 1.
## void setZFar ( float zfar )

Задаёт новое расстояние до дальней плоскости отсечения frustum обзора камеры. Изменение значения обновляет матрицу проекции.
### Аргументы

- *float* **zfar** - Расстояние в единицах. Если задано отрицательное значение, вместо него будет использовано 0.

## float getZFar () const

Возвращает текущее расстояние до дальней плоскости отсечения frustum обзора камеры. Изменение значения обновляет матрицу проекции.
### Возвращаемое значение

Текущее расстояние в единицах. Если задано отрицательное значение, вместо него будет использовано 0.
## void setZNear ( float znear )

Задаёт новое расстояние до ближней плоскости отсечения frustum обзора камеры. Изменение значения обновляет матрицу проекции.
### Аргументы

- *float* **znear** - Расстояние в единицах. Если задано отрицательное значение, вместо него будет использовано 0.

## float getZNear () const

Возвращает текущее расстояние до ближней плоскости отсечения frustum обзора камеры. Изменение значения обновляет матрицу проекции.
### Возвращаемое значение

Текущее расстояние в единицах. Если задано отрицательное значение, вместо него будет использовано 0.
## void setFocalLength ( float length )

Задаёт новое фокусное расстояние объектива физически корректной камеры.
### Аргументы

- *float* **length** - Фокусное расстояние объектива камеры.

## float getFocalLength () const

Возвращает текущее фокусное расстояние объектива физически корректной камеры.
### Возвращаемое значение

Текущее фокусное расстояние объектива камеры.
## void setFilmGate ( float gate )

Задаёт новый film gate для физически корректной камеры с горизонтальным FOV.
### Аргументы

- *float* **gate** - Film gate.

## float getFilmGate () const

Возвращает текущий film gate для физически корректной камеры с горизонтальным FOV.
### Возвращаемое значение

Текущий film gate.
## void setFov ( float fov )

Задаёт новое вертикальное поле зрения (FOV) камеры.
> **Notice:** Горизонтальное FOV не может быть использовано, так как оно меняется в зависимости от соотношения сторон viewport. Задание FOV пересчитывает матрицу проекции с **соотношением сторон = 1**.


Вы можете использовать следующую формулу для вычисления горизонтального FOV из вертикального для заданного соотношения сторон (ширина/высота): **FOV_h = 2 × atan ( (width / height) × tan(FOV_v / 2))**.


### Аргументы

- *float* **fov** - Вертикальное поле зрения в градусах. Заданное значение будет ограничено диапазоном [0;180].

## float getFov () const

Возвращает текущее вертикальное поле зрения (FOV) камеры.
> **Notice:** Горизонтальное FOV не может быть использовано, так как оно меняется в зависимости от соотношения сторон viewport. Задание FOV пересчитывает матрицу проекции с **соотношением сторон = 1**.


Вы можете использовать следующую формулу для вычисления горизонтального FOV из вертикального для заданного соотношения сторон (ширина/высота): **FOV_h = 2 × atan ( (width / height) × tan(FOV_v / 2))**.


### Возвращаемое значение

Текущее вертикальное поле зрения в градусах. Заданное значение будет ограничено диапазоном [0;180].
## Camera::FOV_FIXED getFovFixed () const

Возвращает текущее значение, указывающее, какой компонент FOV (горизонтальный или вертикальный) в данный момент зафиксирован.
### Возвращаемое значение

Текущий зафиксированный компонент FOV, одно из значений [FOV_FIXED_*](#FOV_FIXED_HORIZONTAL).
## void setFovMode ( Camera::FOV_MODE mode )

Задаёт новое значение, указывающее тип FOV, используемый для камеры:
- Для классической камеры должно быть задано вертикальное FOV. В этом случае FOV задаётся напрямую в [degrees](#setFov_float_void).
- Для физически корректной камеры должно быть задано горизонтальное FOV. В этом случае FOV вычисляется в зависимости от [film gate](#setFilmGate_float_void) и [focal length](#setFocalLength_float_void) камеры.


### Аргументы

- *[Camera::FOV_MODE](../../../api/library/rendering/class.camera_cpp.md#FOV_MODE)* **mode** - Значение, указывающее тип FOV, используемый для камеры. 0, если используется камера с вертикальным FOV; 1, если используется физически корректная камера с горизонтальным FOV.

## Camera::FOV_MODE getFovMode () const

Возвращает текущее значение, указывающее тип FOV, используемый для камеры:
- Для классической камеры должно быть задано вертикальное FOV. В этом случае FOV задаётся напрямую в [degrees](#setFov_float_void).
- Для физически корректной камеры должно быть задано горизонтальное FOV. В этом случае FOV вычисляется в зависимости от [film gate](#setFilmGate_float_void) и [focal length](#setFocalLength_float_void) камеры.


### Возвращаемое значение

Текущее значение, указывающее тип FOV, используемый для камеры. 0, если используется камера с вертикальным FOV; 1, если используется физически корректная камера с горизонтальным FOV.
## void setProjection ( const Math:: mat4 & projection )

Задаёт новую матрицу проекции с единичным (1.0) соотношением сторон.
> **Notice:** Не рекомендуется использовать этот метод для задания наклона ближней плоскости отсечения frustum, так как в этом случае ряд функций (таких как облака, тени, TAA, ряд оптимизаций движка и т.д.) не будут работать корректно. Вместо этого используйте метод [setObliqueFrustum()](#setObliqueFrustum_int_void).


Этот метод позволяет настроить камеру на использование [perspective](../../../principles/world_management/index.md#camera_perspective) или [orthographic](../../../principles/world_management/index.md#camera_orthographic) проекции, в зависимости от требований вашего проекта.


Например, вы можете использовать следующий код для настройки **ортографической проекции** или **перспективной проекции** камеры в зависимости от значения флага:


```cpp
// AppWorldLogic.cpp

/* ... */
#include <UnigineCamera.h>
#include <UnigineGame.h>

// внедряем имена пространства имён Unigine в глобальное пространство имён
using namespace Unigine;

/* ... */

// ortho flag - change this value to switch projection type
int ortho = 0;

int AppWorldLogic::init() {

	// getting the camera of the current player
	CameraPtr camera = Game::getPlayer()->getCamera();

	// setting up near and far clipping planes and aspect ratio
	float znear = 0.001f;
	float zfar = 10000.0f;
	float aspect = 16.0f / 9.0f;

	if (ortho)
	{
		// setting up orthographic projection
		camera->setProjection(Math::ortho(-1.0f, 1.0f, -1.0f, 1.0f, znear, zfar));
	}
	else
	{
		// setting up perspective projection
		camera->setProjection(Math::perspective(60.0f, aspect, znear, zfar));
	}

	// setting player's camera
	Game::getPlayer()->setCamera(camera);

	return 1;
}

/* ... */

```


### Аргументы

- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md)&* **projection** - Матрица проекции.

## Math:: mat4 getProjection () const

Возвращает текущую матрицу проекции с единичным (1.0) соотношением сторон.
> **Notice:** Не рекомендуется использовать этот метод для задания наклона ближней плоскости отсечения frustum, так как в этом случае ряд функций (таких как облака, тени, TAA, ряд оптимизаций движка и т.д.) не будут работать корректно. Вместо этого используйте метод [setObliqueFrustum()](#setObliqueFrustum_int_void).


Этот метод позволяет настроить камеру на использование [perspective](../../../principles/world_management/index.md#camera_perspective) или [orthographic](../../../principles/world_management/index.md#camera_orthographic) проекции, в зависимости от требований вашего проекта.


Например, вы можете использовать следующий код для настройки **ортографической проекции** или **перспективной проекции** камеры в зависимости от значения флага:


```cpp
// AppWorldLogic.cpp

/* ... */
#include <UnigineCamera.h>
#include <UnigineGame.h>

// внедряем имена пространства имён Unigine в глобальное пространство имён
using namespace Unigine;

/* ... */

// флаг ortho - измените это значение, чтобы переключить тип проекции
int ortho = 0;

int AppWorldLogic::init() {

	// получаем камеру текущего игрока
	CameraPtr camera = Game::getPlayer()->getCamera();

	// настраиваем ближнюю и дальнюю плоскости отсечения и соотношение сторон
	float znear = 0.001f;
	float zfar = 10000.0f;
	float aspect = 16.0f / 9.0f;

	if (ortho)
	{
		// настраиваем ортографическую проекцию
		camera->setProjection(Math::ortho(-1.0f, 1.0f, -1.0f, 1.0f, znear, zfar));
	}
	else
	{
		// настраиваем перспективную проекцию
		camera->setProjection(Math::perspective(60.0f, aspect, znear, zfar));
	}

	// задаём камеру игрока
	Game::getPlayer()->setCamera(camera);

	return 1;
}

/* ... */

```


### Возвращаемое значение

Текущая матрица проекции.
## void setOffset ( const Math:: mat4 & offset )

Задаёт новую дополнительную трансформацию (матрицу смещения), заданную для камеры. Эта трансформация применяется после трансформации modelview. Матрица смещения не влияет на видовую матрицу или позицию камеры. Например, её можно использовать для симуляции тряски камеры от взрыва.
### Аргументы

- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md)&* **offset** - Матрица смещения.

## Math:: mat4 getOffset () const

Возвращает текущую дополнительную трансформацию (матрицу смещения), заданную для камеры. Эта трансформация применяется после трансформации modelview. Матрица смещения не влияет на видовую матрицу или позицию камеры. Например, её можно использовать для симуляции тряски камеры от взрыва.
### Возвращаемое значение

Текущая матрица смещения.
## void setPosition ( const Math:: Vec3 & position )

Задаёт новую позицию камеры. Вектор позиции хранится в 3-м столбце видовой матрицы (modelview и inverse modelview).
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md)&* **position** - Позиция камеры в мировом пространстве.

## Math:: Vec3 getPosition () const

Возвращает текущую позицию камеры. Вектор позиции хранится в 3-м столбце видовой матрицы (modelview и inverse modelview).
### Возвращаемое значение

Текущая позиция камеры в мировом пространстве.
## Math:: Mat4 getIModelview () const

инвертированная видовая матрица камеры.
### Возвращаемое значение

Инвертированная видовая матрица.
## void setModelview ( const Math:: Mat4 & modelview )

Задаёт новую видовую матрицу камеры.
### Аргументы

- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md)&* **modelview** - Видовая матрица.

## Math:: Mat4 getModelview () const

Возвращает текущую видовую матрицу камеры.
### Возвращаемое значение

Текущая видовая матрица.
## void setOrthoHeight ( float height )

Задаёт новую высоту камеры с включённым ортографическим [projection mode](#getProjectionMode_int).
### Аргументы

- *float* **height** - Высота ортографической камеры.

## float getOrthoHeight () const

Возвращает текущую высоту камеры с включённым ортографическим [projection mode](#getProjectionMode_int).
### Возвращаемое значение

Текущая высота ортографической камеры.
## void setProjectionMode ( Camera::PROJECTION_MODE mode )

Задаёт новый режим проекции: ортографический или перспективный.
### Аргументы

- *[Camera::PROJECTION_MODE](../../../api/library/rendering/class.camera_cpp.md#PROJECTION_MODE)* **mode** - Режим проекции, *[PROJECTION_MODE_ORTHOGRAPHIC](#PROJECTION_MODE_ORTHOGRAPHIC)* для ортографического режима; *[PROJECTION_MODE_PERSPECTIVE](#PROJECTION_MODE_PERSPECTIVE)* для перспективного режима.

## Camera::PROJECTION_MODE getProjectionMode () const

Возвращает текущий режим проекции: ортографический или перспективный.
### Возвращаемое значение

Текущий режим проекции, *[PROJECTION_MODE_ORTHOGRAPHIC](#PROJECTION_MODE_ORTHOGRAPHIC)* для ортографического режима; *[PROJECTION_MODE_PERSPECTIVE](#PROJECTION_MODE_PERSPECTIVE)* для перспективного режима.
---

## static CameraPtr create ( )

Конструктор. Создаёт новую камеру с настройками по умолчанию:
- [Modelview](#setModelview_Mat4_void), [inverse modelview](#getIModelview_Mat4) и [offset matrix](#setOffset_mat4_void) — единичные матрицы 4×4.
- FOV равно 60 градусам.
- [Distance to the near clipping plane](#setZNear_float_void) равно 0.1 единицы.
- [Distance to the far clipping plane](#setZFar_float_void) равно 10000 единиц.
- [Up direction vector](#setUp_vec3_void) равен (0,0,1).
- Маски viewport, отражения, источника звука и реверберации заданы равными 00000001.


## void getDirectionFromScreen ( Math:: Vec3 & p0 , Math:: Vec3 & p1 , float screen_x , float screen_y , float aspect ) const

Выпускает луч из определённой позиции на экране.
### Аргументы

- *Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальная координата луча.
- *Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечная координата луча.
- *float* **screen_x** - X-координата экрана в диапазоне [0;1], где 0 - левая верхняя точка, 1 - правая нижняя точка.
- *float* **screen_y** - Y-координата экрана в диапазоне [0;1], где 0 - левая верхняя точка, 1 - правая нижняя точка.
- *float* **aspect** - Соотношение сторон экрана (высота к ширине).

## Math:: vec3 getDirectionFromScreen ( float screen_x , float screen_y , float aspect ) const

Выпускает луч из определённой позиции на экране.
### Аргументы

- *float* **screen_x** - X-координата экрана в диапазоне [0;1], где 0 - левая верхняя точка, 1 - правая нижняя точка.
- *float* **screen_y** - Y-координата экрана в диапазоне [0;1], где 0 - левая верхняя точка, 1 - правая нижняя точка.
- *float* **aspect** - Соотношение сторон экрана (высота к ширине).

### Возвращаемое значение

Координата точки.
## Math:: mat4 getProjectionFromScreen ( float screen_x0 , float screen_y0 , float screen_x1 , float screen_y1 , float aspect ) const

Создаёт матрицу проекции из 2 позиций на экране. Это необходимо для выделения области кадра (frame selection).
### Аргументы

- *float* **screen_x0** - X-координата первой позиции на экране, в диапазоне [0;1], где 0 - левая верхняя точка, 1 - правая нижняя точка.
- *float* **screen_y0** - Y-координата первой позиции на экране, в диапазоне [0;1], где 0 - левая верхняя точка, 1 - правая нижняя точка.
- *float* **screen_x1** - X-координата второй позиции на экране, в диапазоне [0;1], где 0 - левая верхняя точка, 1 - правая нижняя точка.
- *float* **screen_y1** - Y-координата второй позиции на экране, в диапазоне [0;1], где 0 - левая верхняя точка, 1 - правая нижняя точка.
- *float* **aspect** - Соотношение сторон экрана (высота к ширине).

### Возвращаемое значение

Матрица проекции.
## int getScreenPosition ( float & screen_x , float & screen_y , const Math:: Vec3 & point , float aspect ) const

Проецирует точку в мировых координатах на экран. Координаты экрана записываются в первые 2 переменные, переданные методу.
### Аргументы

- *float &* **screen_x** - X-координата позиции на экране.
- *float &* **screen_y** - Y-координата позиции на экране.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Координаты точки.
- *float* **aspect** - Соотношение сторон (высота экрана к ширине).

### Возвращаемое значение

**1**, если точка была успешно спроецирована; иначе **0**.
## Ptr < Camera > clone ( ) const

Клонирует текущую камеру и сохраняет результат в заданный экземпляр камеры.
### Возвращаемое значение

Копия камеры.
## Math:: mat4 getAspectCorrectedProjection ( float aspect ) const

Возвращает матрицу проекции после коррекции для заданного соотношения сторон. Учитывается [Currently fixed FOV component](#getFovFixed_int).
### Аргументы

- *float* **aspect** - Соотношение сторон.

### Возвращаемое значение

Матрица проекции после коррекции для заданного соотношения сторон.
## void addScriptableMaterial ( const Ptr < Material > & material )

Присоединяет новый [scriptable material](../../../content/materials/scriptable.md) к камере. Чтобы применить скриптовый материал глобально, используйте метод *[addScriptableMaterial()](../../../api/library/rendering/class.render_cpp.md#addScriptableMaterial_Material_void)* класса Render. Порядок выполнения скриптов, назначенных скриптовым материалам, определяется номером материала в списке камеры.
> **Notice:** Выражения скриптовых материалов, [applied globally](../../../api/library/rendering/class.render_cpp.md#addScriptableMaterial_Material_void), выполняются раньше выражений материалов, применённых для конкретной камеры.


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **material** - Скриптовый материал, который присоединяется к камере.

## void insertScriptableMaterial ( int num , const Ptr < Material > & material )

Вставляет новый [scriptable material](../../../content/materials/scriptable.md) в список материалов, назначенных камере. Чтобы применить скриптовый материал глобально, используйте метод [*insertScriptableMaterial()*](../../../api/library/rendering/class.render_cpp.md#insertScriptableMaterial_int_Material_void) класса Render. Порядок выполнения скриптов, назначенных скриптовым материалам, определяется номером материала в списке камеры.
> **Notice:** Выражения скриптовых материалов, [applied globally](../../../api/library/rendering/class.render_cpp.md#addScriptableMaterial_Material_void), выполняются раньше выражений материалов, применённых для конкретной камеры.


### Аргументы

- *int* **num** - Позиция, на которую вставляется новый скриптовый материал.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **material** - Скриптовый материал, который вставляется.

## void removeScriptableMaterial ( int num )

Удаляет из камеры [scriptable material](../../../content/materials/scriptable.md) с заданным номером.
### Аргументы

- *int* **num** - Номер скриптового материала в диапазоне от 0 до [total number of scriptable materials](#getNumScriptableMaterials_int).

## int findScriptableMaterial ( const Ptr < Material > & material ) const

Возвращает номер заданного [scriptable material](../../../content/materials/scriptable.md) для камеры. Этот номер специфичен для камеры (действителен только для этой камеры) и определяет порядок выполнения назначенных выражений.
> **Notice:** Выражения скриптовых материалов, [applied globally](../../../api/library/rendering/class.render_cpp.md#addScriptableMaterial_Material_void), выполняются раньше выражений материалов, применённых для конкретной камеры.


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **material** - Скриптовый материал, для которого нужно найти номер.

### Возвращаемое значение

Номер скриптового материала в диапазоне от 0 до [total number of scriptable materials](#getNumScriptableMaterials_int), или -1, если заданный материал не найден.
## void setScriptableMaterial ( int num , const Ptr < Material > & material )

Заменяет [scriptable material](../../../content/materials/scriptable.md) с заданным номером на новый заданный скриптовый материал. Номер материала определяет порядок выполнения назначенных ему выражений. Этот номер специфичен для камеры (действителен только для этой камеры).
> **Notice:** Выражения скриптовых материалов, [applied globally](../../../api/library/rendering/class.render_cpp.md#addScriptableMaterial_Material_void), выполняются раньше выражений материалов, применённых для конкретной камеры.


### Аргументы

- *int* **num** - Номер скриптового материала в диапазоне от 0 до [total number of scriptable materials](#getNumScriptableMaterials_int).
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **material** - Новый скриптовый материал, заменяющий материал с заданным номером.

## Ptr < Material > getScriptableMaterial ( int num ) const

Возвращает [scriptable material](../../../content/materials/scriptable.md), присоединённый к камере, по его номеру.
### Аргументы

- *int* **num** - Номер скриптового материала в диапазоне от 0 до [total number of scriptable materials](#getNumScriptableMaterials_int).

### Возвращаемое значение

Скриптовый материал, присоединённый к камере, с заданным номером.
## void setScriptableMaterialEnabled ( int num , bool enabled )

Включает или отключает [scriptable material](../../../content/materials/scriptable.md) с заданным номером. Когда материал отключён (неактивен), присоединённые к нему скрипты не выполняются.
### Аргументы

- *int* **num** - Номер скриптового материала в диапазоне от 0 до [total number of scriptable materials](#getNumScriptableMaterials_int).
- *bool* **enabled** - true - чтобы включить скриптовый материал с заданным номером; false - чтобы отключить его.

## bool getScriptableMaterialEnabled ( int num ) const

Возвращает значение, указывающее, включён (активен) ли [scriptable material](../../../content/materials/scriptable.md) с заданным номером, присоединённый к камере. Когда материал отключён (неактивен), присоединённые к нему скрипты не выполняются.
### Аргументы

- *int* **num** - Номер скриптового материала в диапазоне от 0 до [total number of scriptable materials](#getNumScriptableMaterials_int).

### Возвращаемое значение

true, если скриптовый материал с заданным номером включён; иначе false.
## void swapScriptableMaterials ( int num_0 , int num_1 )

Меняет местами два [scriptable materials](../../../content/materials/scriptable.md) с заданными номерами. Номер материала определяет порядок выполнения назначенных ему выражений.
> **Notice:** Номер специфичен для камеры (действителен только для этой камеры).


### Аргументы

- *int* **num_0** - Номер первого скриптового материала в диапазоне от 0 до [total number of scriptable materials](#getNumScriptableMaterials_int).
- *int* **num_1** - Номер второго скриптового материала в диапазоне от 0 до [total number of scriptable materials](#getNumScriptableMaterials_int).

## void clearScriptableMaterials ( )

Удаляет все [scriptable materials](../../../content/materials/scriptable.md), присоединённые к камере.
## Ptr < Camera > copy ( const Ptr < Camera > & camera ) const

Копирует параметры из исходной камеры в этот экземпляр камеры.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera** - Умный указатель на исходную камеру.

### Возвращаемое значение

Умный указатель на эту камеру.
## void swap ( const Ptr < Camera > & camera )

Меняет местами параметры между заданной камерой и этим экземпляром камеры.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera** - Умный указатель на камеру.
