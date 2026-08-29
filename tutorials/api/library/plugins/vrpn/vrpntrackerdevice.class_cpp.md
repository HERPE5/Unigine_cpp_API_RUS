# Unigine::Plugins::VrpnTrackerDevice Class (CPP)

**Header:** #include <plugins/Unigine/VrpnClient/UnigineVrpnClient.h>


Класс для [VRPN Plugin](../../../../code/plugins/vrpn/index_cpp.md), позволяющий получать данные о позиции, ориентации, скорости и ускорении отслеживаемых объектов от 3D-сенсоров трекинга.


### См. также


- Статья о [VRPN Plugin](../../../../code/plugins/vrpn/index_cpp.md)
- Примеры UnigineScript:

  -
  -


## VrpnTrackerDevice Class

### Методы класса

---

## VrpnTrackerDevice ( const char * name )

Конструктор.
### Аргументы

- *const char ** **name** - Путь к устройству в формате *device_name@server_address*.

## void setAccelerationCallback ( const char * name )

Задаёт функцию callback скрипта мира, получающую данные об ускорении отслеживаемых объектов.
### Аргументы

- *const char ** **name** - Имя функции callback.

### Примеры


```cpp
VrpnTrackerDevice vrpn_tracker;

int init() {
	vrpn_tracker = new VrpnTrackerDevice("device_name@server_addr");
	vrpn_tracker.setAccelerationCallback("acceleration_callback");

	return 1;
}

int shutdown() {
	delete vrpn_tracker;
	return 1;
}

int update() {
	vrpn_tracker.update();
	return 1;
}
// функция callback
void acceleration_callback(int sensor,vec3 acceleration,quat orientation,float ifps) {
	log.message("Device sensor %d: acceleration %s, orientation %s, ifps %f\n",sensor,acceleration,orientation,ifps);
}

```


## const char * getAccelerationCallback ( )

Возвращает имя функции callback скрипта мира, получающей данные об ускорении отслеживаемых объектов. Функция callback должна быть определена в скрипте мира и принимать **4** аргумента:
1. Номер сенсора (*int*)
2. Линейное ускорение (*vec3* для версии с одинарной точностью, или *dvec3* для версии с двойной точностью)
3. Ускорение изменения ориентации (аналог углового ускорения; *quat*)
4. Время измерения ускорения (*float* для версии с одинарной точностью, или *double* для версии с двойной точностью)


```cpp
// одинарная точность
void callback_func(int sensor,vec3 acceleration,quat acceleration_orientation,float ifps) {
	// логика функции
}
// двойная точность
void callback_func(int sensor,dvec3 acceleration,quat acceleration_orientation,double ifps) {
	// логика функции
}

```


### Возвращаемое значение

Имя функции callback.
## void setTransformCallback ( const char * name )

Задаёт функцию callback скрипта мира, получающую данные о позиции и ориентации отслеживаемых объектов.
### Аргументы

- *const char ** **name** - Имя функции callback.

### Примеры


```cpp
VrpnTrackerDevice vrpn_tracker;

int init() {
	vrpn_tracker = new VrpnTrackerDevice("device_name@server_addr");
	vrpn_tracker.setTransformCallback("transform_callback");

	return 1;
}

int shutdown() {
	delete vrpn_tracker;
	return 1;
}

int update() {
	vrpn_tracker.update();
	return 1;
}
// функция callback
void transform_callback(int sensor,vec3 position,quat orientation) {
	log.message("Device sensor %d: position %s, orientation %s\n",sensor,position,orientation);
}

```


## const char * getTransformCallback ( )

Возвращает имя функции callback скрипта мира, получающей данные о позиции и ориентации отслеживаемых объектов. Функция callback должна быть определена в скрипте мира и принимать **3** аргумента:
1. Номер сенсора (*int*)
2. Позиция (*vec3* для версии с одинарной точностью, или *dvec3* для версии с двойной точностью)
3. Ориентация (*quat*)


```cpp
// float precision
void callback_func(int sensor,vec3 acceleration,quat acceleration_orientation,float ifps) {
	// function logic
}
// double precision
void callback_func(int sensor,dvec3 acceleration,quat acceleration_orientation,double ifps) {
	// function logic
}

```


### Возвращаемое значение

Имя функции callback.
## void setVelocityCallback ( const char * name )

Задаёт функцию callback скрипта мира, получающую данные о скорости отслеживаемых объектов.
### Аргументы

- *const char ** **name** - Имя функции callback.

### Примеры


```cpp
VrpnTrackerDevice vrpn_tracker;

int init() {
	vrpn_tracker = new VrpnTrackerDevice("device_name@server_addr");
	vrpn_tracker.setVelocityCallback("velocity_callback");

	return 1;
}

int shutdown() {
	delete vrpn_tracker;
	return 1;
}

int update() {
	vrpn_tracker.update();
	return 1;
}

// функция callback
void velocity_callback(int sensor,vec3 velocity,quat orientation,float velocity_ifps) {
	log.message("Device sensor %d: velocity %s, orientation %s, ifps %f\n",sensor,velocity,orientation,ifps);
}

```


## const char * getVelocityCallback ( )

Возвращает имя функции callback скрипта мира, получающей данные о скорости отслеживаемых объектов. Функция callback должна быть определена в скрипте мира и принимать **4** аргумента:
1. Номер сенсора (*int*)
2. Линейная скорость (*vec3* для версии с одинарной точностью, или *dvec3* для версии с двойной точностью)
3. Скорость изменения ориентации (аналог угловой скорости; *quat*)
4. Время измерения скорости (*float* для версии с одинарной точностью, или *double* для версии с двойной точностью)


```cpp
// одинарная точность
void callback_func(int sensor,vec3 velocity,quat velocity_orientation,float ifps) {
	// логика функции
}
// двойная точность
void callback_func(int sensor,dvec3 velocity,quat velocity_orientation,double ifps) {
	// логика функции
}

```


### Возвращаемое значение

Имя функции callback.
## void update ( )

Обновляет внутреннее состояние устройства и получает данные ввода.
> **Notice:** Эта функция должна вызываться каждый кадр.


## int getNumSensors ( ) const

Возвращает общее количество сенсоров.
### Возвращаемое значение

Общее количество сенсоров.
## Math:: Vec3 getSensorPosition ( int num ) const

Возвращает позицию указанного сенсора.
### Аргументы

- *int* **num** - Индекс сенсора в диапазоне [0; [NUM_SENSORS](#getNumSensors_int) - 1 ].

### Возвращаемое значение

Позиция сенсора.
## Math:: quat getSensorRotation ( int num ) const

Возвращает поворот указанного сенсора.
### Аргументы

- *int* **num** - Индекс сенсора в диапазоне [0; [NUM_SENSORS](#getNumSensors_int) - 1 ].

### Возвращаемое значение

Поворот сенсора.
## Math:: Vec3 getSensorVelocity ( int num ) const

Возвращает текущую скорость сенсора (м/с2).
### Аргументы

- *int* **num** - Индекс сенсора в диапазоне [0; [NUM_SENSORS](#getNumSensors_int) - 1 ].

### Возвращаемое значение

Скорость сенсора, в единицах в секунду.
## Math:: quat getSensorVelocityOrientation ( int num ) const

Возвращает ориентацию указанного сенсора после [delta time](#getSensorVelocityIFps_int_scalar).
### Аргументы

- *int* **num** - Индекс сенсора в диапазоне [0; [NUM_SENSORS](#getNumSensors_int) - 1 ].

### Возвращаемое значение

Ориентация скорости сенсора.
## Math::Scalar getSensorVelocityIFps ( int num ) const

Возвращает дельту времени (в секундах) для скорости сенсора.
### Аргументы

- *int* **num** - Индекс сенсора в диапазоне [0; [NUM_SENSORS](#getNumSensors_int) - 1 ].

### Возвращаемое значение

Дельта времени (в секундах).
## Math:: Vec3 getSensorAcceleration ( int num ) const

Возвращает текущее ускорение сенсора (м/с2).
### Аргументы

- *int* **num** - Индекс сенсора в диапазоне [0; [NUM_SENSORS](#getNumSensors_int) - 1 ].

### Возвращаемое значение

Ускорение сенсора.
## Math:: quat getSensorAccelerationOrientation ( int num ) const

Возвращает ориентацию указанного сенсора после [delta time](#getSensorAccelerationIFps_int_scalar).
### Аргументы

- *int* **num** - Индекс сенсора в диапазоне [0; [NUM_SENSORS](#getNumSensors_int) - 1 ].

### Возвращаемое значение

Ориентация ускорения сенсора.
## Math::Scalar getSensorAccelerationIFps ( int num ) const

Возвращает дельту времени (в секундах) для ускорения сенсора.
### Аргументы

- *int* **num** - Индекс сенсора в диапазоне [0; [NUM_SENSORS](#getNumSensors_int) - 1 ].

### Возвращаемое значение

Дельта времени (в секундах).
