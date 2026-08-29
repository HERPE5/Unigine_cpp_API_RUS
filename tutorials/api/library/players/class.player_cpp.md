# Unigine.Player Class (CPP)

**Header:** #include <UniginePlayers.h>

**Inherits from:** Node


Этот класс используется для создания камер, отображающих мир. При создании нового player создаётся [camera](../../../api/library/rendering/class.camera_cpp.md) и задаются элементы управления, [masks](#player_masks), постпроцесс-материалы для этой камеры.


Область видимости (frustum) player определяется [near clipping plane](#setZNear_float_void), [far clipping plane](#setZFar_float_void) и [field of view](#setFov_float_void). Обратите внимание, что если задать пользовательскую матрицу [projection](#setProjection_mat4_void) и после этого вызвать любую из следующих функций:

- [*setFov()*](#setFov_float_void)
- [*setZFar()*](#setZFar_float_void)
- [*setZNear()*](#setZNear_float_void)

ваши пользовательские матрицы будут перезаписаны.
Player не может иметь родительский узел; для трансформаций всегда используются мировые координаты. Единственное исключение — [PlayerDummy](../../../api/library/players/class.playerdummy_cpp.md).


### Маски Player


Объекты, decals и источники света могут выборочно отображаться в viewport player. Чтобы отображаться, их маска viewport должна совпадать с [viewport mask](#setViewportMask_int_void) player (достаточно одного совпадающего бита):

- [surface viewport mask](../../../api/library/objects/class.object_cpp.md#setViewportMask_int_int_void) объекта или [decal viewport mask](../../../api/library/decals/class.decal_cpp.md#setViewportMask_int_void) decal
- [Light viewport mask](../../../api/library/lights/class.light_cpp.md#setViewportMask_int_void) для освещения объекта/decal
- [Material viewport mask](../../../api/library/rendering/class.material_cpp.md#setViewportMask_int_void) для рендеринга материала объекта/decal


Отражения также можно выборочно рендерить в viewport: объект может отрисовываться без отражения, либо отражение без объекта. Для этого [reflection viewport mask](#setReflectionViewportMask_int_void) player должна совпадать с:

- Маской отражения отражающего материала
- [Viewport mask](../../../api/library/rendering/class.material_cpp.md#setViewportMask_int_void) отражающего материала
- [surface viewport mask](../../../api/library/objects/class.object_cpp.md#setViewportMask_int_int_void) объекта
- [Material viewport mask](../../../api/library/rendering/class.material_cpp.md#setViewportMask_int_void) отражаемого материала
- [Light viewport mask](../../../api/library/lights/class.light_cpp.md#setViewportMask_int_void)

Этого достаточно, чтобы отрисовать отражение объекта без самого объекта. Если объект также должен присутствовать, все эти условия просто должны выполняться вместе с вышеупомянутыми.
Чтобы отрисовать объект без отражения, достаточно, чтобы либо [material viewport mask](../../../api/library/rendering/class.material_cpp.md#setViewportMask_int_void), либо [surface viewport mask](../../../api/library/objects/class.object_cpp.md#setViewportMask_int_int_void) объекта не совпадали с [reflection viewport mask](#setReflectionViewportMask_int_void) player.


Player также может иметь маски источника звука и реверберации звука. Как и для viewport, соответствующие маски объекта Player должны совпадать с масками [SoundReverb](../../../api/library/sounds/class.soundreverb_cpp.md#setReverbMask_int_void) и [SoundSource](../../../api/library/sounds/class.soundsource_cpp.md#setSourceMask_int_void).


### Перспективная и ортографическая проекции


В зависимости от требований вашего проекта вы можете настроить player на использование [perspective](../../../principles/world_management/index.md#camera_perspective) или [orthographic](../../../principles/world_management/index.md#camera_orthographic) проекции. Это можно сделать с помощью метода [*setProjection()*](#setProjection_mat4_void).


Например, следующий код можно использовать для настройки **ортографической проекции** или **перспективной проекции** для текущего игрового player в зависимости от значения флага:


```cpp
#include "AppWorldLogic.h"
#include <UnigineGame.h>
#include <UniginePlayers.h>

using namespace Unigine;
using namespace Math;

/* ... */

// вычисляет матрицу проекции для указанных параметров (углы для left, right, top и bottom в градусах)
Unigine::Math::mat4 calculateProjection(double left, double right, double bottom, double top, double zNear, double zFar, double zoom)
{
	left = zNear * Unigine::Math::tan(Unigine::Math::Consts::DEG2RAD*(left * zoom));
	right = zNear * Unigine::Math::tan(Unigine::Math::Consts::DEG2RAD*(right * zoom));
	top = zNear * Unigine::Math::tan(Unigine::Math::Consts::DEG2RAD*(top * zoom));
	bottom = zNear * Unigine::Math::tan(Unigine::Math::Consts::DEG2RAD*(bottom * zoom));

	return Unigine::Math::frustum(static_cast<float>(left), static_cast<float>(right), static_cast<float>(bottom), static_cast<float>(top), static_cast<float>(zNear), static_cast<float>(zFar));
}

	/* ... */

	// флаг ortho - измените это значение, чтобы переключить тип проекции
	int ortho_proj = 0;

int AppWorldLogic::init()
{
	// отключаем стандартную коррекцию соотношения сторон для главного окна,
	// чтобы пользовательская проекция применялась корректно
	Unigine::WindowManager::getMainWindow()->setAspectCorrection(false);

	// получаем текущий player
	PlayerPtr player = Game::getPlayer();

	// задаём ближнюю и дальнюю плоскости отсечения и соотношение сторон
	float znear = 0.001f;
	float zfar = 10000.0f;
	float aspect = 16.0f / 9.0f;

	float fov = 60.0f;
	float ortho_height = 2.0f;

	player->setZNear(znear);
	player->setZFar(zfar);
	player->setFov(fov);
	player->setOrthoHeight(ortho_height);

	if (ortho_proj)
	{
		// задаём ортографическую проекцию
		player->setProjectionMode(Camera::PROJECTION_MODE_ORTHOGRAPHIC);

		// или задаём ортографическую проекцию вручную
		player->setProjection(Math::ortho(-ortho_height / 2.0f, ortho_height / 2.0f, -ortho_height / 2.0f, ortho_height / 2.0f, znear, zfar));
	}
	else
	{
		// задаём перспективную проекцию
		player->setProjectionMode(Camera::PROJECTION_MODE_PERSPECTIVE);

		// или задаём матрицу проекции вручную
		player->setProjection(Math::perspective(fov, aspect, znear, zfar));

		// или вычисляем матрицу проекции для разрешения FullHD/4K
		auto projection = calculateProjection(-22.5f, 22.5f, -13.1f, 13.1f, 1.0f, 200000.0f, 1.0f);
		// и задаём вычисленную пользовательскую проекцию вручную
		player->setProjection(projection);
	}

	return 1;
}


```


### Получение углов Эйлера для активной камеры


Иногда может потребоваться получить текущий поворот активной камеры в виде набора углов Эйлера. Когда речь идёт об осях в UNIGINE, предполагается следующее:

|  |  |
|---|---|
| - Ось **X** направлена *вправо* и задаёт угол **pitch**. - Ось **Y** направлена *вперёд* и задаёт угол **roll**. - Ось **Z** направлена *вверх* и задаёт угол **yaw** (курс). | ![](../../../code/fundamentals/matrices/object_directions.png) *Векторы направления объекта* |


Чтобы получить углы Эйлера, следует использовать [*decomposeRotationZXY()*](../../../api/library/math/math.matrix_cpp.md#decomposeRotationZXY_const_mat3_ref_vec3), также известные как углы Кардана (**yaw** независим, затем получаем **pitch** и в конце **roll**). Однако есть один нюанс, который нужно учитывать — у камер другая система:

|  |  |
|---|---|
| - Ось **X** направлена *вправо* и задаёт угол **pitch**. - Ось **Y** направлена *вверх* и задаёт угол **yaw** (курс). - Ось **Z** направлена *назад* и задаёт угол **-roll**. | ![](../../../code/fundamentals/matrices/camera_directions.png) *Векторы направления камеры* |

Чтобы это компенсировать, нужно повернуть камеру на **-90** градусов вокруг оси **X**.
```cpp
#include "AppWorldLogic.h"
#include <UnigineGame.h>
#include <UniginePlayers.h>

using namespace Unigine;
using namespace Math;

/* ... */

	// получаем текущую матрицу вида текущей камеры
	Mat4 currentModelview = Game::getPlayer()->getCamera()->getIModelview();

	// разлагаем матрицу поворота камеры (с компенсацией)
	vec3 euler = decomposeRotationZXY(mat3(currentModelview * Mat4(rotateX(-90.0f))));
	euler.x += 90.0f;

	// выполняем коррекцию отрицательных значений углов
	if (euler.x < 0) euler.x += 360.0f;
	if (euler.y < 0) euler.y += 360.0f;
	if (euler.z < 0) euler.z += 360.0f;

	// углы Эйлера для камеры
	float pitch = euler.x;
	float roll = euler.y;
	float yaw = euler.z;


```


### Пример использования


В этом примере создаётся player [PlayerSpectator](../../../objects/players/spectator/index.md), задаются его параметры, и он устанавливается как текущий игровой player.


В заголовочном файле `AppWorldLogic.h` подключите заголовок `UniginePlayers.h` и объявите умный указатель [PlayerSpectator](../../../api/library/players/class.playerspectator_cpp.md).


```cpp
#include <UnigineLogic.h>
#include <UnigineStreams.h>
#include <UniginePlayers.h>

class AppWorldLogic : public Unigine::WorldLogic
{

public:

	/* публичные методы */

private:
	Unigine::PlayerSpectatorPtr playerSpectator;

};


```


В файле реализации `AppWorldLogic.cpp` выполните следующее:


- Подключите заголовок `UnigineGame.h`, чтобы задать нового player с помощью метода *[setPlayer()](../../../api/library/engine/class.game_cpp.md#setPlayer_Player_void)*.
- Используйте директиву **using namespace Unigine**: имена пространства имён Unigine будут внедрены в глобальное пространство имён.
- Задайте необходимые параметры созданного экземпляра Player.
- Установите недавно созданный Player как текущий игровой player.
- Очистите указатель на PlayerSpectator, чтобы избежать утечек памяти.


Необходимые части кода:


```cpp
#include "AppWorldLogic.h"
#include <UnigineGame.h>
#include <UniginePlayers.h>

using namespace Unigine;
using namespace Math;

/* ... */

int AppWorldLogic::init()
{

	// создаём новый экземпляр PlayerSpectator
	playerSpectator = PlayerSpectator::create();

	// задаём необходимые параметры: FOV, ZNear, ZFar, вектор направления взгляда и позицию PlayerSpectator.
	playerSpectator->setFov(90.0f);
	playerSpectator->setZNear(0.1f);
	playerSpectator->setZFar(10000.0f);
	playerSpectator->setViewDirection(Math::vec3(0.0f, 1.0f, 0.0f));
	playerSpectator->setWorldPosition(Math::Vec3(-1.6f, -1.7f, 1.7f));

	// задаём Player экземпляру-синглтону Game
	Game::setPlayer(playerSpectator);

	return 1;
}

int AppWorldLogic::shutdown()
{

	// очищаем указатель на Player
	playerSpectator.clear();

	return 1;
}


```


## Player Class

### Методы класса

---

## void setCamera ( const Ptr < Camera > & camera )

Задаёт указанный экземпляр Camera для Player.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera** - Умный указатель на задаваемую Camera.

## Ptr < Camera > getCamera ( ) const

Возвращает экземпляр Camera узла Player.
### Возвращаемое значение

Камера player.
## void setControlled ( bool controlled )

Отключает или включает элементы управления player.
### Аргументы

- *bool* **controlled** - true, чтобы включить элементы управления player, false — чтобы отключить (player перестаёт на них реагировать).

## bool isControlled ( ) const

Возвращает значение, указывающее, отключены ли элементы управления player (player не реагирует на них) или включены.
### Возвращаемое значение

true, если элементы управления player включены; иначе false.
## void setControls ( const Ptr < Controls > & controls )

Задаёт объект [Controls](../../../api/library/controls/class.controls_cpp.md), который будет хранить настройки элементов управления вводом для player.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Controls](../../../api/library/controls/class.controls_cpp.md)> &* **controls** - Объект [Controls](../../../api/library/controls/class.controls_cpp.md), используемый для обработки ввода.

## Ptr < Controls > getControls ( ) const

Возвращает объект [Controls](../../../api/library/controls/class.controls_cpp.md), хранящий настройки элементов управления вводом для player.
### Возвращаемое значение

Объект [Controls](../../../api/library/controls/class.controls_cpp.md), используемый для обработки ввода.
## void getDirectionFromScreen ( Math:: Vec3 & p0 , Math:: Vec3 & p1 , int mouse_x , int mouse_y , int screen_x , int screen_y , int screen_width , int screen_height ) const

Пускает луч в указанную позицию на экране и возвращает координаты начальной (p0) и конечной (p1) точек луча.
```cpp
Vec3 p0, p1;

// получаем текущего player (камеру)
PlayerPtr player = Game::getPlayer();

if (player.get() == NULL)
	return 0;

// получаем ширину и высоту клиентской области текущего окна приложения
Math::ivec2 winsize = WindowManager::getMainWindow()->getClientSize();
int width = winsize.x;
int height = winsize.y;

// получаем текущие координаты X и Y указателя мыши
int mouse_x = Gui::getCurrent()->getMouseX();
int mouse_y = Gui::getCurrent()->getMouseY();

// получаем направление мыши от позиции player (p0) до курсора мыши (p1)
player->getDirectionFromScreen(p0, p1, mouse_x, mouse_y, 0, 0, width, height);


```


### Аргументы

- *Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальные координаты луча.
- *Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечные координаты луча.
- *int* **mouse_x** - Координата X позиции мыши.
- *int* **mouse_y** - Координата Y позиции мыши.
- *int* **screen_x** - Координата X позиции экрана.
- *int* **screen_y** - Координата Y позиции экрана.
- *int* **screen_width** - Ширина экрана.
- *int* **screen_height** - Высота экрана.

## Math:: vec3 getDirectionFromScreen ( int mouse_x , int mouse_y , int screen_x , int screen_y , int screen_width , int screen_height ) const

Пускает луч в указанную позицию на экране и возвращает вектор направления этой позиции.
```cpp
// получаем ширину и высоту клиентской области текущего окна приложения
Math::ivec2 winsize = WindowManager::getMainWindow()->getClientSize();
int width = winsize.x;
int height = winsize.y;

// инициализируем точки луча от позиции player в направлении, указанном курсором мыши
Vec3 p0 = player->getWorldPosition();
Vec3 p1 = p0 + Vec3(player->getDirectionFromScreen(Gui::getCurrent()->getMouseX(), Gui::getCurrent()->getMouseY(), 0, 0, width, height)) * 100;


```


### Аргументы

- *int* **mouse_x** - Координата X позиции мыши.
- *int* **mouse_y** - Координата Y позиции мыши.
- *int* **screen_x** - Координата X позиции экрана.
- *int* **screen_y** - Координата Y позиции экрана.
- *int* **screen_width** - Ширина экрана.
- *int* **screen_height** - Высота экрана.

### Возвращаемое значение

Координаты вектора.
## void setFov ( float fov )


Задаёт вертикальное поле зрения player.


> **Notice:** Горизонтальное поле зрения (FOV) использовать нельзя, так как оно меняется в зависимости от соотношения сторон viewport. Задание FOV пересчитывает матрицу проекции с **соотношением сторон = 1**.


Для вычисления горизонтального FOV из вертикального при заданном соотношении сторон (width/height) можно использовать следующую формулу: **FOV_h = 2 × atan ( (width / height) × tan(FOV_v / 2))**.


### Аргументы

- *float* **fov** - Новое вертикальное поле зрения, в градусах. Указанное значение будет ограничено диапазоном **[0; 180]**. Значение по умолчанию: 60 градусов.

## float getFov ( ) const


Возвращает текущее вертикальное поле зрения player.


> **Notice:** Горизонтальное поле зрения (FOV) использовать нельзя, так как оно меняется в зависимости от соотношения сторон viewport.


Для вычисления горизонтального FOV из вертикального при заданном соотношении сторон (width/height) можно использовать следующую формулу: **FOV_h = 2 × atan ( (width / height) × tan(FOV_v / 2))**.


### Возвращаемое значение

Вертикальное поле зрения, в градусах. Значение по умолчанию: 60 градусов.
## void setObliqueFrustum ( bool frustum )

Включает или отключает скошенность (obliqueness) области видимости.
> **Notice:** Рекомендуется задавать скошенную область видимости с помощью этого метода, так как он не влияет на матрицу проекции. Чтобы указать ближнюю плоскость отсечения, используйте метод [setObliqueFrustumPlane()](#setObliqueFrustumPlane_Vec4_void).


### Аргументы

- *bool* **frustum** - true, чтобы включить скошенную область видимости; false — чтобы отключить.

## bool isObliqueFrustum ( ) const

Возвращает значение, указывающее, скошена ли область видимости.
### Возвращаемое значение

true, если область видимости скошена; иначе false.
## void setObliqueFrustumPlane ( const Math:: Vec4 & plane )

Задаёт скошенную ближнюю плоскость отсечения области видимости.
> **Notice:** Этот метод не влияет на матрицу проекции. Чтобы включить скошенную область видимости, используйте метод [setObliqueFrustum()](#setObliqueFrustum_int_void).


```cpp
#include "AppWorldLogic.h"
#include <UnigineGame.h>
#include <UniginePlayers.h>

using namespace Unigine;
using namespace Math;

/* ... */

int AppWorldLogic::update()
{

	float time = Game::getTime();

	// инициализируем плоскость, задаваемую как ближняя плоскость отсечения
	Math::Vec4 plane = Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f + Math::sin(time) * 4.0f);

	// получаем player
	PlayerPtr player = Game::getPlayer();
	if (player != nullptr)
	{
		// включаем скошенную область видимости
		player->setObliqueFrustum(1);

		// задаём нашу плоскость как скошенную ближнюю плоскость отсечения
		player->setObliqueFrustumPlane(plane);
	}

	return 1;
}


```


### Аргументы

- *const  Math::[Vec4](../../../api/library/math/class.vec4_cpp.md) &* **plane** - Мировые координаты задаваемой скошенной ближней плоскости отсечения (Nx, Ny, Nz, D), где Nx, Ny, Nz — координаты нормали плоскости, D — расстояние от начала координат до плоскости.

## Math:: Vec4 getObliqueFrustumPlane ( ) const

Возвращает скошенную ближнюю плоскость отсечения области видимости.
### Возвращаемое значение

Мировые координаты скошенной ближней плоскости отсечения (Nx, Ny, Nz, D), где Nx, Ny, Nz — координаты нормали плоскости, D — расстояние от начала координат до плоскости.
## void setProjection ( const Math:: mat4 & projection )

Обновляет текущую матрицу проекции.
> **Notice:** Не рекомендуется использовать этот метод для задания скошенности ближней плоскости отсечения области видимости, так как в этом случае ряд функций (например, облака, тени, TAA, ряд оптимизаций движка и т.д.) не будут функционировать корректно. Вместо этого используйте метод [setObliqueFrustum()](#setObliqueFrustum_int_void).


### Аргументы

- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **projection** - Новая матрица проекции.

## Math:: mat4 getProjection ( ) const

Возвращает текущую матрицу проекции с единичным (1.0) соотношением сторон.
### Возвращаемое значение

Текущая матрица проекции.
## Math:: mat4 getProjectionFromScreen ( int x0 , int y0 , int x1 , int y1 , int screen_width , int screen_height ) const

Создаёт матрицу проекции из 2 позиций на экране. Это требуется для выделения кадра (frame selection).
### Аргументы

- *int* **x0** - Координата X первой позиции на экране.
- *int* **y0** - Координата Y первой позиции на экране.
- *int* **x1** - Координата X второй позиции на экране.
- *int* **y1** - Координата Y второй позиции на экране.
- *int* **screen_width** - Ширина экрана.
- *int* **screen_height** - Высота экрана.

### Возвращаемое значение

Матрица проекции.
## void setReflectionViewportMask ( int mask )

Задаёт битовую маску для рендеринга отражений в viewport. Отражения отрисовываются в viewport, если маски отражающих материалов совпадают с этой маской (хотя бы один бит).
### Аргументы

- *int* **mask** - Маска viewport отражений (целое число, каждый бит которого является маской).

## int getReflectionViewportMask ( ) const

Возвращает текущую битовую маску для рендеринга отражений в viewport. Отражения отрисовываются в viewport, если маски отражающих материалов совпадают с этой маской (хотя бы один бит).
### Возвращаемое значение

Маска viewport отражений (целое число, каждый бит которого является маской).
## void setReverbMask ( int mask )

Задаёт маску реверберации, определяющую зоны реверберации, которые могут быть слышны. Чтобы звук реверберировал, хотя бы один бит этой маски должен совпадать с маской реверберации источника звука и маской реверберации зоны реверберации. Маски источника звука и зоны реверберации могут совпадать с маской player в разных битах, не обязательно в одном и том же.
### Аргументы

- *int* **mask** - Маска реверберации (целое число, каждый бит которого является маской для реверберирующих источников звука и зон реверберации).

## int getReverbMask ( ) const

Возвращает текущую битовую маску, определяющую, какие [reverberation zones](../../../api/library/sounds/class.soundreverb_cpp.md) могут быть слышны. Чтобы звук реверберировал, хотя бы один бит этой маски должен совпадать с [reverb mask of the sound source](../../../api/library/sounds/class.soundsource_cpp.md#setReverbMask_int_void) и [reverb mask of the reverberation zone](../../../api/library/sounds/class.soundreverb_cpp.md#setReverbMask_int_void). (Маски источника звука и зоны реверберации могут совпадать с маской player в разных битах, не обязательно в одном и том же).
### Возвращаемое значение

Маска реверберации (целое число, каждый бит которого является маской для реверберирующих источников звука и зон реверберации).
## int getScreenPosition ( int & x , int & y , const Math:: Vec3 & point , int screen_width , int screen_height ) const

Проецирует точку в мировых координатах на экран. Координаты экрана записываются в первые 2 переменные, переданные методу (в пикселях).
```cpp
// получаем относительную позицию на экране точки в мировом пространстве (world_point_position)
EngineWindowViewportPtr main_window = WindowManager::getMainWindow();
ivec2 client_render_size = main_window->getClientRenderSize();
int screen_x, screen_y;
Game::getPlayer()->getScreenPosition(screen_x, screen_y, world_point_position, client_render_size.x, client_render_size.y);
vec2 relative_pos = vec2(screen_x, screen_y) / client_render_size;

```


### Аргументы

- *int &* **x** - Координата X позиции на экране (в пикселях).
- *int &* **y** - Координата Y позиции на экране (в пикселях).
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Координаты точки.
- *int* **screen_width** - Ширина экрана.
- *int* **screen_height** - Высота экрана.

### Возвращаемое значение

1, если точка успешно спроецирована; иначе 0.
## void setSourceMask ( int mask )

Задаёт маску источника, определяющую источники звука, которые могут быть услышаны. Чтобы источник звука был услышан, его маска должна совпадать с этой хотя бы в одном бите. Кроме того, громкость звукового канала, в котором воспроизводится звук (его номер также зависит от этой маски), не должна быть равна 0.
### Аргументы

- *int* **mask** - Маска источника (целое число, каждый бит которого задаёт звуковой канал).

## int getSourceMask ( ) const

Возвращает маску источника, определяющую источники звука, которые могут быть услышаны. Чтобы источник звука был услышан, его маска должна совпадать с этой хотя бы в одном бите. Кроме того, громкость звукового канала, в котором воспроизводится звук (его номер также зависит от этой маски), не должна быть равна 0.
### Возвращаемое значение

Маска источника (целое число, каждый бит которого задаёт звуковой канал).
## void setUp ( const Math:: vec3 & up )

Задаёт направление "вверх" viewport player (т.е. наклон viewport player).
> **Notice:** В случае [PlayerActor](../../../api/library/players/class.playeractor_cpp.md) его трансформация заставляет пересчитывать внутреннее состояние (позицию, направление, углы и т.д.), поэтому направление "вверх" viewport player может стать "отрицательным вперёд". И тогда трансформация будет пересчитана с использованием этого направления, что вызовет переворот базиса player actor. Чтобы избежать такого переворота, углы theta и phi следует [recalculated](../../../api/library/players/class.playeractor_cpp.md#setViewDirection_vec3_void) с использованием [current viewing orientation](../../../api/library/players/class.playeractor_cpp.md#getViewDirection_vec3) player.


### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **up** - Новый вектор направления "вверх". Вектор нормализуется до 1.

## Math:: vec3 getUp ( ) const

Возвращает текущее направление "вверх" viewport player (т.е. наклон viewport player).
### Возвращаемое значение

Вектор направления "вверх".
## void setVelocity ( const Math:: vec3 & velocity )

Задаёт скорость player.
> **Notice:** В случае [PlayerActor](../../../api/library/players/class.playeractor_cpp.md) эта функция действительна только если player не симулируется физически ([*setPhysical()*](../../../api/library/players/class.playeractor_cpp.md#setPhysical_int_void) установлен в 0). Если это не так, перемещение PlayerActor выполняется через обращение к его телу.


### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **velocity** - Новая скорость, в единицах в секунду.

## Math:: vec3 getVelocity ( ) const

Возвращает текущую скорость player.
### Возвращаемое значение

Скорость, в единицах в секунду.
## void setViewDirection ( const Math:: vec3 & direction )

Задаёт указанный вектор направления взгляда экземпляру Player.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **direction** - Вектор направления взгляда.

## Math:: vec3 getViewDirection ( ) const

Возвращает вектор направления взгляда Player.
### Возвращаемое значение

Вектор направления взгляда.
## void setViewportMask ( int mask )

Задаёт маску viewport. Поверхности объектов, материалы, decals, источники света и объекты GUI будут отрисовываться в viewport только если их маска viewport совпадает с маской player (достаточно одного совпадающего бита).
### Аргументы

- *int* **mask** - Маска viewport (целое число, каждый бит которого является маской).

## int getViewportMask ( ) const

Возвращает текущую маску viewport. Поверхности объектов, материалы, decals, источники света и объекты GUI будут отрисовываться в viewport только если их маска viewport совпадает с маской player (достаточно одного совпадающего бита).
### Возвращаемое значение

Маска viewport (целое число, каждый бит которого является маской).
## void setZFar ( float zfar )

Задаёт расстояние до дальней плоскости отсечения области видимости player. Значение по умолчанию: 10000 единиц.
### Аргументы

- *float* **zfar** - Расстояние до дальней плоскости отсечения, в единицах. Минимальное значение — 0.

## float getZFar ( ) const

Возвращает текущее расстояние до дальней плоскости отсечения области видимости player. Значение по умолчанию: 10000 единиц.
### Возвращаемое значение

Расстояние до дальней плоскости отсечения, в единицах.
## void setZNear ( float znear )

Задаёт расстояние до ближней плоскости отсечения области видимости player. Значение по умолчанию: 0.1 единицы.
### Аргументы

- *float* **znear** - Расстояние до ближней плоскости отсечения, в единицах. Минимальное значение — 0.

## float getZNear ( ) const

Возвращает расстояние до ближней плоскости отсечения области видимости player. Значение по умолчанию: 0.1 единицы.
### Возвращаемое значение

Расстояние до ближней плоскости отсечения, в единицах.
## void flushTransform ( ) const

Принудительно немедленно устанавливает трансформации player. Эту функцию следует вызывать вручную после обновления пользовательского ввода через updateControls().
## void updateControls ( float ifps ) const

Получает текущие параметры player (импульс, направление, скорость и т.д.) в соответствии с пользовательским вводом. После обновления ввода следует вручную вызвать flushTransform(), чтобы применить его к player.
### Аргументы

- *float* **ifps** - Длительность кадра, в секундах.

## void setFovMode ( Camera::FOV_MODE mode )

Задаёт значение, указывающее тип FOV, используемый для player:
- Для стандартного player должен быть задан вертикальный FOV. В этом случае FOV задаётся напрямую в [degrees](#setFov_float_void).
- Для физически корректного (physically-based) player должен быть задан горизонтальный FOV. В этом случае FOV вычисляется в зависимости от [film gate](#setFilmGate_float_void) и [focal length](#setFocalLength_float_void) player.


### Аргументы

- *[Camera::FOV_MODE](../../../api/library/rendering/class.camera_cpp.md#FOV_MODE)* **mode** - *[FOV_MODE_VERTICAL](../../../api/library/rendering/class.camera_cpp.md#FOV_MODE_VERTICAL)* для player с вертикальным FOV; *[FOV_MODE_PHYSICALLY_BASED_CAMERA](../../../api/library/rendering/class.camera_cpp.md#FOV_MODE_PHYSICALLY_BASED_CAMERA)* для физически корректного player с горизонтальным FOV.

## Camera::FOV_MODE getFovMode ( ) const

Возвращает значение, указывающее тип FOV, используемый для player.
### Возвращаемое значение

0, если используется player с вертикальным FOV; 1, если используется физически корректный player с горизонтальным FOV.
## void setFilmGate ( float gate )

Задаёт film gate для физически корректной камеры с горизонтальным FOV.
### Аргументы

- *float* **gate** - Film gate.

## float getFilmGate ( ) const

Возвращает film gate физически корректной камеры с горизонтальным FOV.
### Возвращаемое значение

Film gate.
## void setFocalLength ( float length )

Задаёт фокусное расстояние объектива физически корректной камеры.
### Аргументы

- *float* **length** - Фокусное расстояние объектива камеры.

## float getFocalLength ( ) const

Возвращает фокусное расстояние объектива физически корректной камеры.
### Возвращаемое значение

Фокусное расстояние объектива камеры.
## Math:: mat4 getAspectCorrectedProjection ( int width = -1 , int height = -1 ) const

Возвращает матрицу проекции после коррекции для указанного соотношения сторон (**ширина экрана** / **высота экрана**). Учитывается [Currently fixed FOV component](#getFovFixed_int).
### Аргументы

- *int* **width** - Ширина экрана.
- *int* **height** - Высота экрана.

### Возвращаемое значение

Матрица проекции после коррекции для указанного соотношения сторон (**ширина экрана** / **высота экрана**).
## Camera::FOV_FIXED getFovFixed ( ) const

Возвращает значение, указывающее, какой компонент FOV (горизонтальный или вертикальный) в настоящее время фиксирован.
### Возвращаемое значение

Текущий фиксированный компонент FOV, одно из значений [Camera::FOV_FIXED_*](../../../api/library/rendering/class.camera_cpp.md#FOV_FIXED_HORIZONTAL).
## void addScriptableMaterial ( const Ptr < Material > & material )

Присоединяет новый [scriptable material](../../../content/materials/scriptable.md) к player. Чтобы применить scriptable material глобально, используйте метод **[addScriptableMaterial()](../../../api/library/rendering/class.render_cpp.md#addScriptableMaterial_Material_void)** класса Render. Порядок выполнения скриптов, назначенных scriptable materials, определяется номером материала в списке player.
> **Notice:** Выражения scriptable materials, [applied globally](../../../api/library/rendering/class.render_cpp.md#addScriptableMaterial_Material_void), выполняются раньше выражений тех, что применены для конкретного player.


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **material** - Scriptable material, присоединяемый к player.

## void insertScriptableMaterial ( int num , const Ptr < Material > & material )

Вставляет новый [scriptable material](../../../content/materials/scriptable.md) в список материалов, назначенных player. Чтобы применить scriptable material глобально, используйте метод [*insertScriptableMaterial()*](../../../api/library/rendering/class.render_cpp.md#insertScriptableMaterial_int_Material_void) класса Render. Порядок выполнения скриптов, назначенных scriptable materials, определяется номером материала в списке player.
> **Notice:** Выражения scriptable materials, [applied globally](../../../api/library/rendering/class.render_cpp.md#addScriptableMaterial_Material_void), выполняются раньше выражений тех, что применены для конкретного player.

### Аргументы

- *int* **num** - Позиция, в которую вставляется новый scriptable material.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **material** - Вставляемый scriptable material.

## void removeScriptableMaterial ( int num )

Удаляет [scriptable material](../../../content/materials/scriptable.md) с указанным номером из player.
### Аргументы

- *int* **num** - Номер scriptable material в диапазоне от 0 до [total number of scriptable materials](#getNumScriptableMaterials_int).

## int getNumScriptableMaterials ( ) const

Возвращает общее количество [scriptable materials](../../../content/materials/scriptable.md), присоединённых к player.
### Возвращаемое значение

Общее количество scriptable materials, присоединённых к player.
## int findScriptableMaterial ( const Ptr < Material > & material ) const

Возвращает номер указанного [scriptable material](../../../content/materials/scriptable.md) для player. Этот номер специфичен для player (действителен только для этого player) и определяет порядок выполнения назначенных выражений.
> **Notice:** Выражения scriptable materials, [applied globally](../../../api/library/rendering/class.render_cpp.md#addScriptableMaterial_Material_void), выполняются раньше выражений тех, что применены для конкретного player.


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **material** - Scriptable material, для которого нужно найти номер.

### Возвращаемое значение

Номер scriptable material в диапазоне от 0 до [total number of scriptable materials](#getNumScriptableMaterials_int), либо -1, если указанный материал не найден.
## void setScriptableMaterial ( int num , const Ptr < Material > & material )

Заменяет [scriptable material](../../../content/materials/scriptable.md) с указанным номером на новый указанный scriptable material. Номер материала определяет порядок выполнения назначенных ему выражений. Этот номер специфичен для player (действителен только для этого player).
> **Notice:** Выражения scriptable materials, [applied globally](../../../api/library/rendering/class.render_cpp.md#addScriptableMaterial_Material_void), выполняются раньше выражений тех, что применены для конкретного player.


### Аргументы

- *int* **num** - Номер scriptable material в диапазоне от 0 до [total number of scriptable materials](#getNumScriptableMaterials_int).
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **material** - Новый scriptable material, заменяющий материал с указанным номером.

## Ptr < Material > getScriptableMaterial ( int num ) const

Возвращает [scriptable material](../../../content/materials/scriptable.md), присоединённый к player, по его номеру.
### Аргументы

- *int* **num** - Номер scriptable material в диапазоне от 0 до [total number of scriptable materials](#getNumScriptableMaterials_int).

### Возвращаемое значение

Scriptable material, присоединённый к player, с указанным номером.
## void setScriptableMaterialEnabled ( int num , bool enabled )

Включает или отключает [scriptable material](../../../content/materials/scriptable.md) с указанным номером. Когда материал отключён (неактивен), присоединённые к нему скрипты не выполняются.
### Аргументы

- *int* **num** - Номер scriptable material в диапазоне от 0 до [total number of scriptable materials](#getNumScriptableMaterials_int).
- *bool* **enabled** - true, чтобы включить scriptable material с указанным номером, false — чтобы отключить.

## bool getScriptableMaterialEnabled ( int num ) const

Возвращает значение, указывающее, включён ли (активен) [scriptable material](../../../content/materials/scriptable.md) с указанным номером, присоединённый к player. Когда материал отключён (неактивен), присоединённые к нему скрипты не выполняются.
### Аргументы

- *int* **num** - Номер scriptable material в диапазоне от 0 до [total number of scriptable materials](#getNumScriptableMaterials_int).

### Возвращаемое значение

true, если scriptable material с указанным номером включён; иначе false.
## void swapScriptableMaterials ( int num_0 , int num_1 )

Меняет местами два [scriptable materials](../../../content/materials/scriptable.md) с указанными номерами. Номер материала определяет порядок выполнения назначенных ему выражений.
> **Notice:** Номер специфичен для player (действителен только для этого player).


### Аргументы

- *int* **num_0** - Номер первого scriptable material в диапазоне от 0 до [total number of scriptable materials](#getNumScriptableMaterials_int).
- *int* **num_1** - Номер второго scriptable material в диапазоне от 0 до [total number of scriptable materials](#getNumScriptableMaterials_int).

## void clearScriptableMaterials ( )

Очищает все [scriptable materials](../../../content/materials/scriptable.md), присоединённые к player.
## void setMainPlayer ( bool player )

Задаёт player как [main player](../../../objects/players/index.md#main_player).
### Аргументы

- *bool* **player** - true, чтобы задать player как главный, false — чтобы отменить.

## bool isMainPlayer ( ) const

Проверяет, является ли player [main player](../../../objects/players/index.md#main_player).
### Возвращаемое значение

true, если player является главным; иначе false.
## void setListener ( bool listener )

Задаёт player как слушателя (listener).
### Аргументы

- *bool* **listener** - true, чтобы задать player как слушателя, false — чтобы отменить.

## bool isListener ( ) const

Проверяет, является ли player [listener](../../../objects/players/index.md#listener).
### Возвращаемое значение

true, если player является слушателем; иначе false.
## void getDirectionFromMainWindow ( Math:: Vec3 & p0 , Math:: Vec3 & p1 , int mouse_x , int mouse_y ) const

Пускает луч в указанную позицию на экране и возвращает координаты начальной (p0) и конечной (p1) точек луча относительно текущего главного окна.
### Аргументы

- *Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальные координаты луча.
- *Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечные координаты луча.
- *int* **mouse_x** - Координата X позиции мыши в мировых координатах.
- *int* **mouse_y** - Координата Y позиции мыши в мировых координатах.

## Math:: vec3 getDirectionFromMainWindow ( int mouse_x , int mouse_y ) const

Пускает луч в указанную позицию на экране и возвращает вектор направления этой позиции относительно текущего главного окна.
### Аргументы

- *int* **mouse_x** - Координата X позиции мыши в мировых координатах.
- *int* **mouse_y** - Координата Y позиции мыши в мировых координатах.

### Возвращаемое значение

Координаты вектора.
## void getDirectionFromWindow ( Math:: Vec3 & p0 , Math:: Vec3 & p1 , int mouse_x , int mouse_y , const Ptr < EngineWindowViewport > & window ) const

Пускает луч в указанную позицию на экране и возвращает координаты начальной (p0) и конечной (p1) точек луча относительно указанного window viewport.
### Аргументы

- *Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальные координаты луча.
- *Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечные координаты луча.
- *int* **mouse_x** - Координата X позиции мыши в мировых координатах.
- *int* **mouse_y** - Координата Y позиции мыши в мировых координатах.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindowViewport](../../../api/library/gui/class.enginewindowviewport_cpp.md)> &* **window** - Window viewport, относительно которого возвращается направление.

## Math:: vec3 getDirectionFromWindow ( int mouse_x , int mouse_y , const Ptr < EngineWindowViewport > & window ) const

Пускает луч в указанную позицию на экране и возвращает вектор направления этой позиции относительно указанного window viewport.
### Аргументы

- *int* **mouse_x** - Координата X позиции мыши в мировых координатах.
- *int* **mouse_y** - Координата Y позиции мыши в мировых координатах.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindowViewport](../../../api/library/gui/class.enginewindowviewport_cpp.md)> &* **window** - Window viewport, относительно которого возвращается направление.

### Возвращаемое значение

Координаты вектора.
## Math:: mat4 getProjectionFromMainWindow ( int x0 , int y0 , int x1 , int y1 ) const

Создаёт матрицу проекции из 2 позиций на экране относительно текущего главного окна. Это требуется для выделения кадра (frame selection).
### Аргументы

- *int* **x0** - Координата X первой позиции на экране.
- *int* **y0** - Координата Y первой позиции на экране.
- *int* **x1** - Координата X второй позиции на экране.
- *int* **y1** - Координата Y второй позиции на экране.

### Возвращаемое значение

Матрица проекции.
## Math:: mat4 getProjectionFromWindow ( int x0 , int y0 , int x1 , int y1 , const Ptr < EngineWindowViewport > & window ) const

Создаёт матрицу проекции из 2 позиций на экране относительно указанного window viewport. Это требуется для выделения кадра (frame selection).
### Аргументы

- *int* **x0** - Координата X первой позиции на экране.
- *int* **y0** - Координата Y первой позиции на экране.
- *int* **x1** - Координата X второй позиции на экране.
- *int* **y1** - Координата Y второй позиции на экране.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindowViewport](../../../api/library/gui/class.enginewindowviewport_cpp.md)> &* **window** - Window viewport, относительно которого возвращается проекция.

### Возвращаемое значение

Матрица проекции.
## int getMainWindowPosition ( int & x , int & y , const Math:: Vec3 & point ) const

Проецирует точку в мировых координатах относительно главного окна. Координаты записываются в первые 2 переменные, переданные методу (в пикселях).
```cpp

// получаем относительную позицию на экране точки в мировом пространстве (world_point_position)
ivec2 client_render_size = WindowManager::getMainWindow()->getClientRenderSize();
int screen_x, screen_y;
Game::getPlayer()->getMainWindowPosition(screen_x, screen_y, world_point_position);
vec2 relative_pos = vec2(screen_x, screen_y) / client_render_size;

```


### Аргументы

- *int &* **x** - Координата X позиции на экране (в пикселях).
- *int &* **y** - Координата Y позиции на экране (в пикселях).
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Координаты точки.

### Возвращаемое значение

1, если точка успешно спроецирована; иначе 0.
## int getWindowPosition ( int & x , int & y , const Math:: Vec3 & point , const Ptr < EngineWindowViewport > & window ) const

Проецирует точку в мировых координатах относительно указанного window viewport. Координаты записываются в первые 2 переменные, переданные методу (в пикселях).
```cpp

// получаем относительную позицию на экране точки в мировом пространстве (world_point_position)
EngineWindowViewportPtr main_window = WindowManager::getMainWindow();
ivec2 client_render_size = main_window->getClientRenderSize();
int screen_x, screen_y;
Game::getPlayer()->getWindowPosition(screen_x, screen_y, world_point_position, main_window);
vec2 relative_pos = vec2(screen_x, screen_y) / client_render_size;

```


### Аргументы

- *int &* **x** - Координата X позиции на экране (в пикселях).
- *int &* **y** - Координата Y позиции на экране (в пикселях).
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Координаты точки.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindowViewport](../../../api/library/gui/class.enginewindowviewport_cpp.md)> &* **window** - Window viewport, относительно которого возвращается проекция.

### Возвращаемое значение

1, если точка успешно спроецирована; иначе 0.
## void setProjectionMode ( Camera::PROJECTION_MODE mode )

Задаёт режим проекции: ортографический или перспективный.
### Аргументы

- *[Camera::PROJECTION_MODE](../../../api/library/rendering/class.camera_cpp.md#PROJECTION_MODE)* **mode** - Режим проекции, *[PROJECTION_MODE_ORTHOGRAPHIC](../../../api/library/rendering/class.camera_cpp.md#PROJECTION_MODE_ORTHOGRAPHIC)* для ортографического режима; *[PROJECTION_MODE_PERSPECTIVE](../../../api/library/rendering/class.camera_cpp.md#PROJECTION_MODE_PERSPECTIVE)* для перспективного режима.

## Camera::PROJECTION_MODE getProjectionMode ( ) const

Возвращает текущий режим проекции: ортографический или перспективный.
### Возвращаемое значение

Режим проекции, *[PROJECTION_MODE_ORTHOGRAPHIC](../../../api/library/rendering/class.camera_cpp.md#PROJECTION_MODE_ORTHOGRAPHIC)* для ортографического режима; *[PROJECTION_MODE_PERSPECTIVE](../../../api/library/rendering/class.camera_cpp.md#PROJECTION_MODE_PERSPECTIVE)* для перспективного режима.
## void setOrthoHeight ( float height )

Задаёт высоту камеры с включённым ортографическим [projection mode](#getProjectionMode_int).
### Аргументы

- *float* **height** - Высота ортографической камеры.

## float getOrthoHeight ( ) const

Возвращает текущую высоту камеры с включённым ортографическим [projection mode](#getProjectionMode_int).
### Возвращаемое значение

Высота ортографической камеры.
