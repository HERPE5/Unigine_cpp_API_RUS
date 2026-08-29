# Unigine::Plugins::Kinect Class (CPP)

**Header:** #include <plugins/Unigine/Kinect/UnigineKinect.h>

> **Notice:** Этот класс является синглтоном.


Этот набор функций доступен, если загружен [Kinect2 plugin](../../../code/plugins/kinect2/index_cpp.md). Этот плагин используется для получения уже распознанных данных от сенсора Kinect2.

> **Notice:** На компьютере должен быть установлен Kinect SDK 2.0+.


Если плагин загружен вместе с движком, устанавливается определение `HAS_KINECT`. Это определение можно использовать, например, чтобы избежать ошибок, если плагин не загружен: код, в котором выполняются функции плагина, можно обернуть следующим образом:


```cpp
#ifdef HAS_KINECT
	// функции kinect
#endif

```


Плагин Unigine Kinect работает следующим образом: когда [kinect::isBodyTracked(body)](#isBodyTracked_int_bool) возвращает **0**, [kinect::getBonePosition(body, bone)](#getBonePosition_int_int_vec3) вернёт **vec3_zero**. Kinect имеет собственную частоту кадров, поэтому информация об отслеживании тела доступна не в каждом кадре движка. Отслеживание запястья можно реализовать следующим образом:


```cpp
vec3 wrist;

int update() {
    if(kinect::isBodyTracked(0)) {
        wrist = kinect::getBonePosition(0,KINECT::BONE_WRIST_LEFT);
    }
    visualizer->renderSphere(0.05f,translate(wrist),vec4_one);
    return 1;
}

```


### См. также


- Статья о [Kinect2 Plugin](../../../code/plugins/kinect2/index_cpp.md)

  -
  -
  -


## Kinect Class

### Перечисления

## FACE_PROPERTY

| Name | Description |
|---|---|
| **FACE_PROPERTY_HAPPY** = 0 | Лицо пользователя счастливое (например, пользователь улыбается). |
| **FACE_PROPERTY_ENGAGED** = 1 | Лицо пользователя вовлечено. |
| **FACE_PROPERTY_GLASSES** = 2 | На лице есть очки. |
| **FACE_PROPERTY_EYE_LEFT_CLOSED** = 3 | Левый глаз пользователя закрыт. |
| **FACE_PROPERTY_EYE_RIGHT_CLOSED** = 4 | Правый глаз пользователя закрыт. |
| **FACE_PROPERTY_MOUTH_OPEN** = 5 | Рот пользователя открыт. |
| **FACE_PROPERTY_MOUTH_MOVED** = 6 | Рот пользователя двигался. |
| **FACE_PROPERTY_LOOKING_AWAY** = 7 | Пользователь смотрит в сторону. |

## FACE_POINT

| Name | Description |
|---|---|
| **FACE_POINT_EYE_LEFT** = 0 | Левый глаз. |
| **FACE_POINT_EYE_RIGHT** = 1 | Правый глаз. |
| **FACE_POINT_NOSE** = 2 | Нос. |
| **FACE_POINT_MOUTH_CORNER_LEFT** = 3 | Левый уголок рта. |
| **FACE_POINT_MOUTH_CORNER_RIGHT** = 4 | Правый уголок рта. |

## FACE_DETECTION_RESULT

| Name | Description |
|---|---|
| **FACE_DETECTION_RESULT_UNKNOWN** = 0 | Флаг, указывающий, что лицо находится в неизвестном состоянии. |
| **FACE_DETECTION_RESULT_NO** = 1 | Флаг, указывающий, что свойство (состояние) лица не отслеживается. |
| **FACE_DETECTION_RESULT_MAYBE** = 2 | Флаг, указывающий, что свойство (состояние) лица отслеживается частично. |
| **FACE_DETECTION_RESULT_YES** = 3 | Флаг, указывающий, что свойство (состояние) лица отслеживается. |

## BONE

| Name | Description |
|---|---|
| **BONE_HEAD** = 3 | Голова. |
| **BONE_NECK** = 2 | Шея. |
| **BONE_SPINE_SHOULDER** = 20 | Позвоночник на уровне плеча. |
| **BONE_SPINE_MID** = 1 | Середина позвоночника. |
| **BONE_SPINE_BASE** = 0 | Основание позвоночника. |
| **BONE_SHOULDER_LEFT** = 4 | Левое плечо. |
| **BONE_ELBOW_LEFT** = 5 | Левый локоть. |
| **BONE_WRIST_LEFT** = 6 | Левое запястье. |
| **BONE_HAND_LEFT** = 7 | Левая кисть. |
| **BONE_HAND_TIP_LEFT** = 21 | Кончик левой кисти. |
| **BONE_THUMB_LEFT** = 22 | Левый большой палец. |
| **BONE_SHOULDER_RIGHT** = 8 | Правое плечо. |
| **BONE_ELBOW_RIGHT** = 9 | Правый локоть. |
| **BONE_WRIST_RIGHT** = 10 | Правое запястье. |
| **BONE_HAND_RIGHT** = 11 | Правая кисть. |
| **BONE_HAND_TIP_RIGHT** = 23 | Кончик правой кисти. |
| **BONE_THUMB_RIGHT** = 24 | Правый большой палец. |
| **BONE_HIP_LEFT** = 12 | Левое бедро (кроме большого пальца). |
| **BONE_KNEE_LEFT** = 13 | Левое колено. |
| **BONE_ANKLE_LEFT** = 14 | Левая лодыжка. |
| **BONE_FOOT_LEFT** = 15 | Левая стопа. |
| **BONE_HIP_RIGHT** = 16 | Правое бедро (кроме большого пальца). |
| **BONE_KNEE_RIGHT** = 17 | Правое колено. |
| **BONE_ANKLE_RIGHT** = 18 | Правая лодыжка. |
| **BONE_FOOT_RIGHT** = 19 | Правая стопа. |

## HAND_STATE

| Name | Description |
|---|---|
| **HAND_STATE_UNKNOWN** = 0 | Флаг, указывающий, что состояние кисти неизвестно. |
| **HAND_STATE_NOT_TRACKED** = 1 | Флаг, указывающий, что состояние кисти не отслеживается. |
| **HAND_STATE_OPEN** = 2 | Флаг, указывающий, что кисть открыта. |
| **HAND_STATE_CLOSED** = 3 | Флаг, указывающий, что кисть закрыта (сжата в кулак). |
| **HAND_STATE_LASSO** = 4 | Флаг, указывающий, что кисть находится в состоянии lasso (закрытая кисть с поднятыми средним и указательным пальцами). |

## TRACKING_CONFIDENCE

| Name | Description |
|---|---|
| **TRACKING_CONFIDENCE_LOW** = 0 | Флаг, указывающий, что кисть отслеживается с низким уровнем достоверности (возможно, кисть отслеживается корректно). |
| **TRACKING_CONFIDENCE_HIGH** = 1 | Флаг, указывающий, что кисть отслеживается с высоким уровнем достоверности (кисть отслеживается полностью). |

## TRACKING_STATE

| Name | Description |
|---|---|
| **TRACKING_STATE_NOT_TRACKED** = 0 | Флаг, указывающий, что тело и кости не отслеживаются. |
| **TRACKING_STATE_INFERRED** = 1 | Флаг, указывающий, что тело и кости вычисляются приближённо (Kinect предполагает их положение). |
| **TRACKING_STATE_TRACKED** = 2 | Флаг, указывающий, что тело и кости отслеживаются. |

## NUM

| Name | Description |
|---|---|
| **NUM_BODIES** = 6 | Количество отслеживаемых тел. Максимальное значение — **6**. |
| **NUM_BONES** = 25 | Количество отслеживаемых костей. Максимальное значение — **25**. |
| **NUM_FACE_POINTS** = 5 | Количество отслеживаемых точек лица (левый и правый глаза, нос, левый и правый уголки рта). Максимальное значение — **5**. |
| **NUM_FACE_PROPERTIES** = 8 | Количество отслеживаемых состояний лица (например, счастливое, вовлечённое, в очках и т.д.). Максимальное значение — **8**. |

## STREAM

| Name | Description |
|---|---|
| **STREAM_COLOR** = 1 | Цветной поток. Если эта константа не указана при [sensor initialization](#init_uint_int), доступа к цветному потоку не будет. |
| **STREAM_INFRARED** = 2 | Инфракрасный поток. Если эта константа не указана при [sensor initialization](#init_uint_int), доступа к инфракрасному потоку не будет. |
| **STREAM_DEPTH** = 8 | Поток глубины. Если эта константа не указана при [sensor initialization](#init_uint_int), доступа к потоку глубины не будет. |
| **STREAM_BODY** = 32 | Тело. Если эта константа не указана при [sensor initialization](#init_uint_int), тела не будут отслеживаться. |
| **STREAM_ALL** = 43 | Константы [*STREAM_COLOR*](#STREAM_COLOR), [*STREAM_INFRARED*](#STREAM_INFRARED), [*STREAM_DEPTH*](#STREAM_DEPTH), [*STREAM_BODY*](#STREAM_BODY), объединённые с помощью **логического ИЛИ**. |

### Методы класса

---

## Kinect::TRACKING_STATE getBodyLeanState ( int body ) const

Возвращает значение, указывающее, отслеживалось ли тело с указанным номером как lean или нет.
### Аргументы

- *int* **body** - Индекс тела в диапазоне [0;[NUM_BODIES](#NUM_BODIES) - 1 ].

### Возвращаемое значение

Одна из констант [TRACKING_STATE_*](#TRACKING_STATE_NOT_TRACKED), задающая состояние отслеживания. Если [*STREAM_BODY*](#STREAM_BODY) не указана при [initialization](#init_uint_int) сенсора, будет возвращено значение [*TRACKING_STATE_NOT_TRACKED*](#TRACKING_STATE_NOT_TRACKED).
## Math:: quat getBoneOrientation ( int body , Kinect::BONE bone ) const

Возвращает ориентацию указанной кости указанного тела относительно родительской кости.
### Аргументы

- *int* **body** - Номер тела в диапазоне [0;[NUM_BODIES](#NUM_BODIES) - 1 ].
- *[Kinect::BONE](../../../api/library/plugins/engine.kinect_cpp.md#BONE)* **bone** - Номер кости в диапазоне [0;[NUM_BONES](#NUM_BONES) - 1 ].

### Возвращаемое значение

Ориентация кости относительно родительской кости. Если [*STREAM_BODY*](#STREAM_BODY) не указана при [initialization](#init_uint_int) сенсора, будет возвращён нулевой кватернион.
## Math:: vec3 getBonePosition ( int body , Kinect::BONE bone ) const

Возвращает положение указанной кости указанного тела относительно сенсора.
### Аргументы

- *int* **body** - Номер тела в диапазоне [0;[NUM_BODIES](#NUM_BODIES) - 1 ].
- *[Kinect::BONE](../../../api/library/plugins/engine.kinect_cpp.md#BONE)* **bone** - Номер кости в диапазоне [0;[NUM_BONES](#NUM_BONES) - 1 ].

### Возвращаемое значение

Положение кости относительно сенсора. Если [*STREAM_BODY*](#STREAM_BODY) не указана при [initialization](#init_uint_int) сенсора, будет возвращён нулевой вектор.
## Kinect::TRACKING_STATE getBoneState ( int body , Kinect::BONE bone ) const

Возвращает текущее состояние отслеживания указанной кости указанного тела.
### Аргументы

- *int* **body** - Номер тела в диапазоне [0;[NUM_BODIES](#NUM_BODIES) - 1 ].
- *[Kinect::BONE](../../../api/library/plugins/engine.kinect_cpp.md#BONE)* **bone** - Номер кости в диапазоне [0;[NUM_BONES](#NUM_BONES) - 1 ].

### Возвращаемое значение

Одна из констант [TRACKING_STATE_*](#TRACKING_STATE_NOT_TRACKED), задающая состояние отслеживания. Если [*STREAM_BODY*](#STREAM_BODY) не указана при [initialization](#init_uint_int) сенсора, будет возвращено значение [*TRACKING_STATE_NOT_TRACKED*](#TRACKING_STATE_NOT_TRACKED).
## Ptr < Image > getColorBuffer ( ) const

Возвращает изображение, представляющее текущий цветной буфер в формате RGBA8.
> **Notice:** Изображение в цветном буфере удаляется каждый кадр. Однако данные отправляются в буфер не каждый кадр, поэтому функция может вернуть **NULL**.


### Возвращаемое значение

Изображение, представляющее текущий цветной буфер. Если [*STREAM_COLOR*](#STREAM_COLOR) не указана при [initialization](#init_uint_int) сенсора, будет возвращён **NULL**.
## Ptr < Image > getDepthBuffer ( ) const

Возвращает изображение, представляющее текущий буфер глубины в формате R16.
> **Notice:** Изображение в буфере глубины удаляется каждый кадр. Однако данные отправляются в буфер не каждый кадр, поэтому функция может вернуть **NULL**.


### Возвращаемое значение

Изображение, представляющее текущий буфер глубины. Если [*STREAM_DEPTH*](#STREAM_DEPTH) не указана при [initialization](#init_uint_int) сенсора, будет возвращён **NULL**.
## Math:: ivec4 getFaceBoundsInColorSpace ( int face ) const

Возвращает границы указанного лица относительно размера цветного буфера.
### Аргументы

- *int* **face** - Номер лица в диапазоне [0;[NUM_BODIES](#NUM_BODIES) - 1 ].

### Возвращаемое значение

Границы лица в формате *(Left,Top,Right,Bottom)*. Если [*STREAM_BODY*](#STREAM_BODY) не указана при [initialization](#init_uint_int) сенсора, будет возвращён нулевой вектор.
## Math:: ivec4 getFaceBoundsInInfraredSpace ( int face ) const

Возвращает границы указанного лица относительно размера инфракрасного буфера.
### Аргументы

- *int* **face** - Номер лица в диапазоне [0;[NUM_BODIES](#NUM_BODIES) - 1 ].

### Возвращаемое значение

Границы лица в формате *(Left,Top,Right,Bottom)*. Если [*STREAM_BODY*](#STREAM_BODY) не указана при [initialization](#init_uint_int) сенсора, будет возвращён нулевой вектор.
## Math:: quat getFaceOrientation ( int face ) const

Возвращает ориентацию указанного лица относительно сенсора.
### Аргументы

- *int* **face** - Номер лица в диапазоне [0;[NUM_BODIES](#NUM_BODIES) - 1 ].

### Возвращаемое значение

Ориентация лица. Если [*STREAM_BODY*](#STREAM_BODY) не указана при [initialization](#init_uint_int) сенсора, будет возвращён нулевой кватернион.
## Math:: vec3 getFacePointInColorSpace ( int face , Kinect::FACE_POINT point ) const

Возвращает координаты указанной точки указанного лица относительно размера цветного буфера.
> **Notice:** Используются только компоненты *X* и *Y* возвращаемого вектора, компонент *Z* следует игнорировать.


### Аргументы

- *int* **face** - Номер лица в диапазоне [0;[NUM_BODIES](#NUM_BODIES) - 1 ].
- *[Kinect::FACE_POINT](../../../api/library/plugins/engine.kinect_cpp.md#FACE_POINT)* **point** - Номер точки лица в диапазоне [0;[NUM_FACE_POINTS](#NUM_FACE_POINTS) - 1 ].

### Возвращаемое значение

Координаты точки лица. Если [*STREAM_BODY*](#STREAM_BODY) не указана при [initialization](#init_uint_int) сенсора, будет возвращён нулевой вектор.
## Math:: vec3 getFacePointInInfraredSpace ( int face , Kinect::FACE_POINT point ) const

Возвращает координаты указанной точки указанного лица относительно размера инфракрасного буфера.
> **Notice:** Используются только компоненты *X* и *Y* возвращаемого вектора, компонент *Z* следует игнорировать.


### Аргументы

- *int* **face** - Номер лица в диапазоне [0;[NUM_BODIES](#NUM_BODIES) - 1 ].
- *[Kinect::FACE_POINT](../../../api/library/plugins/engine.kinect_cpp.md#FACE_POINT)* **point** - Номер точки лица в диапазоне [0;[NUM_FACE_POINTS](#NUM_FACE_POINTS) - 1 ].

### Возвращаемое значение

Координаты точки лица. Если [*STREAM_BODY*](#STREAM_BODY) не указана при [initialization](#init_uint_int) сенсора, будет возвращён нулевой вектор.
## Kinect::FACE_DETECTION_RESULT getFaceProperty ( int face , Kinect::FACE_PROPERTY property ) const

Возвращает значение, указывающее, насколько точно отслеживалось указанное свойство лица.
### Аргументы

- *int* **face** - Номер лица в диапазоне [0;[NUM_BODIES](#NUM_BODIES) - 1 ].
- *[Kinect::FACE_PROPERTY](../../../api/library/plugins/engine.kinect_cpp.md#FACE_PROPERTY)* **property** - Номер свойства лица в диапазоне [0;[NUM_FACE_PROPERTIES](#NUM_FACE_PROPERTIES) - 1 ].

### Возвращаемое значение

Одна из констант [*KINECT_FACE_DETECTION_RESULT_**](#FACE_DETECTION_RESULT_UNKNOWN). Если [*STREAM_BODY*](#STREAM_BODY) не указана при [initialization](#init_uint_int) сенсора, будет возвращено значение [*KINECT_FACE_DETECTION_RESULT_UNKNOWN*](#FACE_DETECTION_RESULT_UNKNOWN).
## Ptr < Image > getInfraredBuffer ( ) const

Возвращает изображение, представляющее текущий инфракрасный буфер в формате R16.
> **Notice:** Изображение в инфракрасном буфере удаляется каждый кадр. Однако данные отправляются в буфер не каждый кадр, поэтому функция может вернуть **NULL**.


### Возвращаемое значение

Изображение, представляющее текущий инфракрасный буфер. Если [*STREAM_INFRARED*](#STREAM_INFRARED) не указана при [initialization](#init_uint_int) сенсора, будет возвращён **NULL**.
## Kinect::TRACKING_CONFIDENCE getLeftHandConfidence ( int body ) const

Возвращает уровень достоверности отслеживания левой кисти указанного тела.
### Аргументы

- *int* **body** - Номер тела в диапазоне [0;[NUM_BODIES](#NUM_BODIES) - 1 ].

### Возвращаемое значение

Одна из констант [*TRACKING_CONFIDENCE_**](#TRACKING_CONFIDENCE_LOW). Если [*STREAM_BODY*](#STREAM_BODY) не указана при [initialization](#init_uint_int) сенсора, будет возвращено значение [*TRACKING_CONFIDENCE_LOW*](#TRACKING_CONFIDENCE_LOW).
## Kinect::HAND_STATE getLeftHandState ( int body ) const

Возвращает текущее состояние левой кисти указанного тела.
### Аргументы

- *int* **body** - Номер тела в диапазоне [0;[NUM_BODIES](#NUM_BODIES) - 1 ].

### Возвращаемое значение

Одна из констант [*HAND_STATE_**](#HAND_STATE_UNKNOWN). Если [*STREAM_BODY*](#STREAM_BODY) не указана при [initialization](#init_uint_int) сенсора, будет возвращено значение [*HAND_STATE_UNKNOWN*](#HAND_STATE_UNKNOWN).
## Kinect::TRACKING_CONFIDENCE getRightHandConfidence ( int body ) const

Возвращает уровень достоверности отслеживания правой кисти указанного тела.
### Аргументы

- *int* **body** - Номер тела в диапазоне [0;[NUM_BODIES](#NUM_BODIES) - 1 ].

### Возвращаемое значение

Одна из констант [*TRACKING_CONFIDENCE_**](#TRACKING_CONFIDENCE_LOW). Если [*STREAM_BODY*](#STREAM_BODY) не указана при [initialization](#init_uint_int) сенсора, будет возвращено значение [*TRACKING_CONFIDENCE_LOW*](#TRACKING_CONFIDENCE_LOW).
## Kinect::HAND_STATE getRightHandState ( int body ) const

Возвращает текущее состояние правой кисти указанного тела.
### Аргументы

- *int* **body** - Номер тела в диапазоне [0;[NUM_BODIES](#NUM_BODIES) - 1 ].

### Возвращаемое значение

Одна из констант [*HAND_STATE_**](#HAND_STATE_UNKNOWN). Если [*STREAM_BODY*](#STREAM_BODY) не указана при [initialization](#init_uint_int) сенсора, будет возвращено значение [*HAND_STATE_UNKNOWN*](#HAND_STATE_UNKNOWN).
## int init ( unsigned int stream_flags )

Инициализация сенсора Kinect2. Константы [*STREAM_**](#STREAM_COLOR) задают, какие потоки данных следует инициализировать.
### Аргументы

- *unsigned int* **stream_flags** - Битовая маска, представленная одной из констант [*STREAM_**](#STREAM_COLOR) или их комбинацией.

### Возвращаемое значение

1, если сенсор успешно инициализирован; иначе 0.
### Примеры


Например, доступ к цветному буферу и буферу глубины будет открыт, если инициализировать сенсор следующим образом:

```cpp
engine.kinect.init(KINECT_STREAM_COLOR | KINECT_STREAM_DEPTH);
```


## bool isBodyTracked ( int body ) const

Возвращает значение, указывающее, отслеживалось ли сенсором тело с указанным номером.
### Аргументы

- *int* **body** - Номер тела в диапазоне [0;[NUM_BODIES](#NUM_BODIES) - 1 ].

### Возвращаемое значение

true, если тело отслеживалось; иначе false. Если [*STREAM_BODY*](#STREAM_BODY) не указана при [initialization](#init_uint_int) сенсора, будет возвращено false.
## bool isFaceTracked ( int face ) const

Возвращает значение, указывающее, отслеживалось ли лицо с указанным номером.
### Аргументы

- *int* **face** - Номер лица в диапазоне [0;[NUM_BODIES](#NUM_BODIES) - 1 ].

### Возвращаемое значение

true, если указанное лицо отслеживается; иначе false. Если [*STREAM_BODY*](#STREAM_BODY) не указана при [initialization](#init_uint_int) сенсора, будет возвращено false.
## void shutdown ( )

Завершение работы сенсора Kinect2.
