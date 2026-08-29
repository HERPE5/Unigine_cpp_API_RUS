# Unigine::Plugins::IG::NEDConverter Class (CPP)

**Header:** #include <plugins/Unigine/IG/UnigineIG.h>


Этот служебный класс используется для преобразования между различными системами координат для IG (например, ENU <-> NED, поворот Эйлера <-> кватернион и т.д.).

> **Notice:** Плагин IG должен быть загружен.


## NEDConverter Class

### Перечисления

## TARGET_COORDINATE_SYSTEM

| Name | Description |
|---|---|
| **TARGET_COORDINATE_SYSTEM_NED** = 0 | Система координат NED (North-East-Down). X - вперёд, Y - вправо, Z - вниз, используется по умолчанию в Unigine. Порядок поворота: Z -> Y -> X (Yaw-Pitch-Roll) |
| **TARGET_COORDINATE_SYSTEM_ENU** = 1 | Система координат ENU (East-North-Up). X - вправо, Y - вперёд, Z - вверх, используется по умолчанию в Unigine. Порядок поворота: Z -> X -> Y (Yaw-Roll-Pitch) |

### Методы класса

## void setTargetCoordinateSystem ( NEDConverter::TARGET_COORDINATE_SYSTEM system )

Задаёт новую целевую систему координат.
### Аргументы

- *NEDConverter::TARGET_COORDINATE_SYSTEM* **system** - Целевая система координат.

## NEDConverter::TARGET_COORDINATE_SYSTEM getTargetCoordinateSystem () const

Возвращает текущую целевую систему координат.
### Возвращаемое значение

Текущая целевая система координат.
---

## Math:: dvec3 ENUtoNED ( const Math:: dvec3 & enu_pos ) const

Преобразует координаты точки, заданной в системе ENU (East-North-Up), в NED (North-East-Down).
### Аргументы

- *const  Math::[dvec3](../../../../../api/library/math/class.dvec3_cpp.md) &* **enu_pos** - Координаты точки в системе ENU (East-North-Up).

### Возвращаемое значение

Координаты точки в системе NED (North-East-Down).
## Math:: dvec3 NEDtoENU ( const Math:: dvec3 & ned_pos ) const

Преобразует координаты точки, заданной в системе NED (North-East-Down), в ENU (East-North-Up).
### Аргументы

- *const  Math::[dvec3](../../../../../api/library/math/class.dvec3_cpp.md) &* **ned_pos** - Координаты точки в системе NED (North-East-Down).

### Возвращаемое значение

Координаты точки в системе ENU (East-North-Up).
## Math:: dvec3 TARGETtoENU ( const Math:: dvec3 & ig_pos ) const

Преобразует координаты точки, заданной в целевой системе координат (см. *[setTargetCoordinateSystem()](../../../../...md#setTargetCoordinateSystem_int_void)*), в ENU (East-North-Up).
### Аргументы

- *const  Math::[dvec3](../../../../../api/library/math/class.dvec3_cpp.md) &* **ig_pos** - Координаты точки в целевой системе координат.

### Возвращаемое значение

Вектор, представляющий поворот (*roll, pitch, yaw*) в координатах ENU (East-North-Up).
## Math:: dvec3 ENUtoTARGET ( const Math:: dvec3 & enu_pos ) const

Преобразует координаты точки, заданной в системе ENU (East-North-Up), в целевую систему координат (см. *[setTargetCoordinateSystem()](../../../../...md#setTargetCoordinateSystem_int_void)*).
### Аргументы

- *const  Math::[dvec3](../../../../../api/library/math/class.dvec3_cpp.md) &* **enu_pos** - Вектор, представляющий поворот (*roll, pitch, yaw*) в координатах ENU (East-North-Up).

### Возвращаемое значение

Координаты точки в целевой системе координат.
## Math:: vec3 ENUtoNED ( const Math:: vec3 & enu_pos ) const

Преобразует координаты точки, заданной в системе ENU (East-North-Up), в NED (North-East-Down).
### Аргументы

- *const  Math::[vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **enu_pos** - Координаты точки в системе ENU (East-North-Up).

### Возвращаемое значение

Координаты точки в системе NED (North-East-Down).
## Math:: vec3 NEDtoENU ( const Math:: vec3 & ned_pos ) const

Преобразует координаты точки, заданной в системе NED (North-East-Down), в ENU (East-North-Up).
### Аргументы

- *const  Math::[vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **ned_pos** - Координаты точки в системе NED (North-East-Down).

### Возвращаемое значение

Координаты точки в системе ENU (East-North-Up).
## Math:: vec3 TARGETtoENU ( const Math:: vec3 & ig_pos ) const

Преобразует координаты точки, заданной в целевой системе координат (см. *[setTargetCoordinateSystem()](../../../../...md#setTargetCoordinateSystem_int_void)*), в ENU (East-North-Up).
### Аргументы

- *const  Math::[vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **ig_pos** - Координаты точки в целевой системе координат.

### Возвращаемое значение

Координаты точки в системе ENU (East-North-Up).
## Math:: vec3 ENUtoTARGET ( const Math:: vec3 & enu_pos ) const

Преобразует координаты точки, заданной в системе ENU (East-North-Up), в целевую систему координат (см. *[setTargetCoordinateSystem()](../../../../...md#setTargetCoordinateSystem_int_void)*).
### Аргументы

- *const  Math::[vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **enu_pos** - Координаты точки в системе ENU (East-North-Up).

### Возвращаемое значение

Координаты точки в целевой системе координат.
## Math:: quat eulerENUToRotation ( const Math:: vec3 & euler ) const

Преобразует указанный вектор поворота Эйлера в координатах ENU (East-North-Up) в кватернион поворота.
> **Notice:** Unigine использует ориентацию ENU!
>
>
> Порядок осей: Yaw -> Pitch -> Roll (ENU: Z -> X -> Y, NED: Z -> Y -> X)
>
>
> - `final_rotation =zero_rotation* entity_local_rotation`
> - `entity_local_rotation = final_rotation * inverse(zero_rotation)`


### Аргументы

- *const  Math::[vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **euler** - Вектор, представляющий поворот (*roll, pitch, yaw*) в координатах ENU (East-North-Up).

### Возвращаемое значение

Кватернион поворота.
## Math:: quat eulerNEDToRotation ( const Math:: vec3 & euler ) const

Преобразует указанный вектор поворота Эйлера в координатах NED (North-East-Down) в кватернион поворота.
> **Notice:** Unigine использует ориентацию ENU!
>
>
> Порядок осей: Yaw -> Pitch -> Roll (ENU: Z -> X -> Y, NED: Z -> Y -> X)
>
>
> - `final_rotation =zero_rotation* entity_local_rotation`
> - `entity_local_rotation = final_rotation * inverse(zero_rotation)`


### Аргументы

- *const  Math::[vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **euler** - Вектор, представляющий поворот Эйлера (*roll, pitch, yaw*) в координатах NED (North-East-Down).

### Возвращаемое значение

Кватернион поворота.
## Math:: quat eulerTARGETToRotation ( const Math:: vec3 & euler ) const

Преобразует указанный вектор поворота Эйлера в целевой системе координат (см. *[setTargetCoordinateSystem()](../../../../...md#setTargetCoordinateSystem_int_void)*) в кватернион поворота.
### Аргументы

- *const  Math::[vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **euler** - Вектор, представляющий поворот Эйлера (*roll, pitch, yaw*) в целевой системе координат.

### Возвращаемое значение

Кватернион поворота.
## Math:: vec3 rotationToEulerENU ( const Math:: quat & rotation ) const

Преобразует указанный кватернион поворота в вектор поворота Эйлера в координатах ENU (East-North-Up).
> **Notice:** Unigine использует ориентацию ENU!
>
>
> Порядок осей: Yaw -> Pitch -> Roll (ENU: Z -> X -> Y, NED: Z -> Y -> X)
>
>
> - `final_rotation =zero_rotation* entity_local_rotation`
> - `entity_local_rotation = final_rotation * inverse(zero_rotation)`


### Аргументы

- *const  Math::[quat](../../../../../api/library/math/class.quat_cpp.md) &* **rotation** - Кватернион поворота.

## Math:: vec3 rotationToEulerNED ( const Math:: quat & rotation ) const

Преобразует указанный кватернион поворота в вектор поворота Эйлера в координатах NED (North-East-Down).
> **Notice:** Unigine использует ориентацию ENU!
>
>
> Порядок осей: Yaw -> Pitch -> Roll (ENU: Z -> X -> Y, NED: Z -> Y -> X)
>
>
> - `final_rotation =zero_rotation* entity_local_rotation`
> - `entity_local_rotation = final_rotation * inverse(zero_rotation)`


### Аргументы

- *const  Math::[quat](../../../../../api/library/math/class.quat_cpp.md) &* **rotation** - Кватернион поворота.

### Возвращаемое значение

Вектор, представляющий поворот Эйлера (*roll, pitch, yaw*) в координатах NED (North-East-Down).
## Math:: vec3 rotationToEulerTARGET ( const Math:: quat & rotation ) const

Преобразует указанный кватернион поворота в вектор поворота Эйлера в целевой системе координат (см. *[setTargetCoordinateSystem()](../../../../...md#setTargetCoordinateSystem_int_void)*).
### Аргументы

- *const  Math::[quat](../../../../../api/library/math/class.quat_cpp.md) &* **rotation** - Кватернион поворота.

### Возвращаемое значение

Вектор, представляющий поворот Эйлера (*roll, pitch, yaw*) в целевой системе координат.
