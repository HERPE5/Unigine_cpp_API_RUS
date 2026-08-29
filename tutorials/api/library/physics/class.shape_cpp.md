# Unigine::Shape Class (CPP)

**Header:** #include <UniginePhysics.h>


Этот класс создаёт коллизионные формы, аппроксимирующие конечный объём физических [bodies](../../../api/library/physics/class.body_cpp.md) и позволяющие им сталкиваться. Формы [assigned to a body](#setBody_Body_void) и [positioned](../../../api/library/physics/class.body_cpp.md#setShapeTransform_int_mat4_void) в его локальных координатах.


### См. также


- Пример использования [Enabling Selective Surface-Based Collision](../../../code/usage/enabling_collision/index_cpp.md), демонстрирующий применение маски столкновений
- Раздел *[Collision Shapes](../../../code/uniginescript/samples/collision_shapes.md)* в UnigineScript samples


## Shape Class

### Перечисления

## TYPE

Типы коллизионных форм.
| Имя | Описание |
|---|---|
| **SHAPE_SPHERE** = 0 | Sphere. |
| **SHAPE_CAPSULE** = 1 | Capsule. |
| **SHAPE_CYLINDER** = 2 | Cylinder. |
| **SHAPE_BOX** = 3 | Box. |
| **SHAPE_CONVEX** = 4 | Convex hull. |
| **NUM_SHAPES** = 5 | Количество типов форм для *Particles Field Spacer*. |

### Методы класса

---

## Math:: vec3 getArea ( ) const

Возвращает площади проекций формы на три оси: *x*, *y* и *z*.
### Возвращаемое значение

Тройка значений площадей проекций.
## void setBody ( const Ptr < Body > & body )

Задаёт тело, которому принадлежит форма.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body** - Тело, которому принадлежит форма.

## Ptr < Body > getBody ( ) const

Возвращает тело, которому принадлежит форма.
### Возвращаемое значение

Тело, которому принадлежит форма.
## void setBodyShapeTransform ( const Math:: mat4 & transform )

Задаёт матрицу трансформации формы (в координатах тела). Эта матрица описывает позицию и ориентацию формы. Этот метод идентичен [setShapeTransform()](../../../api/library/physics/class.body_cpp.md#setShapeTransform_int_mat4_void).
### Аргументы

- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации

## Math:: mat4 getBodyShapeTransform ( ) const

Возвращает матрицу трансформации формы (в координатах тела). Эта матрица описывает позицию и ориентацию формы. Этот метод идентичен [getShapeTransform()](../../../api/library/physics/class.body_cpp.md#getShapeTransform_int_mat4).
### Возвращаемое значение

Матрица трансформации
## Math:: vec3 getCenterOfMass ( ) const

Возвращает локальные координаты центра масс формы.
### Возвращаемое значение

Координаты центра масс.
## int getCollision ( Vector < Ptr < ShapeContact >> & OUT_contacts , float ifps ) const

Выполняет проверку столкновений для формы и помещает информацию обо всех контактах в выходной буфер.
Столкновения с поверхностью могут быть обнаружены только при выполнении следующих условий:


1. Поверхность включена.
2. Флаг [Collision](../../../api/library/objects/class.object_cpp.md#setCollision_int_int_void) для этой поверхности включён.
3. Поверхности назначен материал.


> **Notice:** Форма должна быть [enabled](#setEnabled_int_void).


### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[ShapeContact](../../../api/library/physics/class.shapecontact_cpp.md)>> &* **OUT_contacts** - Выходной буфер, содержащий информацию обо всех обнаруженных физических контактах для формы (если есть). Информацию о каждом контакте можно обработать с помощью [ShapeContact class](../../../api/library/physics/class.shapecontact_cpp.md). > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *float* **ifps** - Значение обратного FPS.

### Возвращаемое значение

1, если столкновения найдены; иначе 0.
## int getCollision ( const Ptr < Object > & object , Vector < Ptr < ShapeContact >> & OUT_contacts , float ifps ) const

Выполняет проверку столкновений для формы и помещает информацию обо всех контактах и объекте контакта в выходной буфер.
Столкновения с поверхностью могут быть обнаружены только при выполнении следующих условий:


1. Поверхность включена.
2. Флаг [Collision](../../../api/library/objects/class.object_cpp.md#setCollision_int_int_void) для этой поверхности включён.
3. Поверхности назначен материал.


> **Notice:** Форма должна быть [enabled](#setEnabled_int_void).


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)> &* **object** - Объект, игнорируемый при обнаружении столкновений. Этот параметр используется, когда нужно игнорировать столкновения формы с объектом, которому она принадлежит.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[ShapeContact](../../../api/library/physics/class.shapecontact_cpp.md)>> &* **OUT_contacts** - Выходной буфер, содержащий информацию обо всех обнаруженных физических контактах для формы (если есть). Информацию о каждом контакте можно обработать с помощью [ShapeContact class](../../../api/library/physics/class.shapecontact_cpp.md). > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *float* **ifps** - Значение обратного FPS.

### Возвращаемое значение

1, если столкновения найдены; иначе 0.
## void setCollisionMask ( int mask )

Задаёт маску столкновений для формы. Два объекта сталкиваются, если у обоих совпадающие маски. См. также подробности о дополнительной [collision exclusion mask](#setExclusionMask_int_void).
### Аргументы

- *int* **mask** - Целое число, каждый бит которого является маской.

## int getCollisionMask ( ) const

Возвращает маску столкновений актора. Два объекта сталкиваются, если у обоих совпадающие маски. См. также подробности о дополнительной [collision exclusion mask](#getExclusionMask_int).
### Возвращаемое значение

Целое число, каждый бит которого является маской.
## void setContinuous ( bool continuous )

Включает или отключает непрерывное обнаружение столкновений (CCD) для [spheres](../../../api/library/physics/class.shapesphere_cpp.md) или [capsules](../../../api/library/physics/class.shapecapsule_cpp.md). Включённый CCD практически не влияет на производительность. Отключение CCD позволяет избежать артефактов физики, если они возникают.
### Аргументы

- *bool* **continuous** - Положительное значение, чтобы включить CCD; **0**, чтобы отключить.

## bool isContinuous ( ) const

Возвращает значение, указывающее, включено ли непрерывное обнаружение столкновений (CCD) для [spheres](../../../api/library/physics/class.shapesphere_cpp.md) или [capsules](../../../api/library/physics/class.shapecapsule_cpp.md). Включённый CCD практически не влияет на производительность. Отключение CCD позволяет избежать артефактов физики, если они возникают.
### Возвращаемое значение

**1**, если CCD включён; иначе **0**.
## void setDensity ( float density )

Задаёт плотность формы. Изменение плотности влияет на массу, которая вычисляется путём умножения объёма формы на плотность.
### Аргументы

- *float* **density** - Значение плотности. Если указано отрицательное значение, вместо него используется **0**.

## float getDensity ( ) const

Возвращает текущую плотность формы.
### Возвращаемое значение

Значение плотности.
## void setEnabled ( bool enable )

Включает или отключает физические взаимодействия с формой.
### Аргументы

- *bool* **enable** - Положительное число, чтобы включить физические взаимодействия, **0**, чтобы отключить.

## bool isEnabled ( ) const

Возвращает значение, указывающее, включены ли физические взаимодействия с формой.
### Возвращаемое значение

true, если физические взаимодействия с формой включены; иначе false.
## bool isEnabledSelf ( ) const

Возвращает значение, указывающее, включена ли форма.
### Возвращаемое значение

true, если форма включена; иначе false.
## void setExclusionMask ( int mask )

Задаёт битовую маску для предотвращения столкновений формы с другими формами. Эта маска не зависит от [collision mask](#setCollisionMask_int_void). Чтобы формы с совпадающими масками столкновений не сталкивались, должен совпадать хотя бы один бит их маски исключения.
### Аргументы

- *int* **mask** - Целое число, каждый бит которого является маской.

## int getExclusionMask ( ) const

Возвращает битовую маску, предотвращающую столкновения формы с другими формами. Эта маска не зависит от [collision mask](#getCollisionMask_int). Чтобы формы с совпадающими масками столкновений не сталкивались, должен совпадать хотя бы один бит их маски исключения.
### Возвращаемое значение

Целое число, каждый бит которого является маской.
## void setFriction ( float friction )

Задаёт коэффициент трения для поверхности формы.
### Аргументы

- *float* **friction** - Коэффициент трения для поверхности формы. Если указано отрицательное значение, вместо него используется **0**.

## float getFriction ( ) const

Возвращает коэффициент трения для поверхности формы.
### Возвращаемое значение

Коэффициент трения для поверхности формы.
## void setID ( int id )

Задаёт уникальный ID для формы.
### Аргументы

- *int* **id** - Уникальный ID.

## int getID ( ) const

Возвращает уникальный ID формы.
### Возвращаемое значение

Уникальный ID.
## Math:: mat3 getInertia ( ) const

Возвращает матрицу, представляющую тензор инерции, описывающий сопротивление тела вращению в разных направлениях. Определяется распределением массы по объёму тела.
### Возвращаемое значение

Тензор инерции.
## int getIntersection ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , const Ptr < PhysicsIntersectionNormal > & intersection ) const


Выполняет трассировку от точки p0 до точки p1 для поиска формы, пересекаемой этой линией. Пересечение находится только для объектов с совпадающей маской пересечений.


> **Notice:** Для этой функции используются координаты мирового пространства.


### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальная точка линии.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечная точка линии.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[PhysicsIntersectionNormal](../../../api/library/physics/class.physicsintersectionnormal_cpp.md)> &* **intersection** - Экземпляр класса [PhysicsIntersectionNormal](../../../api/library/physics/class.physicsintersectionnormal_cpp.md), содержащий информацию о пересечении

### Возвращаемое значение

1, если пересечение обнаружено; иначе - 0.
## int getIntersection ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , const Ptr < PhysicsIntersection > & intersection ) const


Выполняет трассировку от точки p0 до точки p1 для поиска формы, пересекаемой этой линией. Пересечение находится только для объектов с совпадающей маской пересечений.


> **Notice:** Для этой функции используются координаты мирового пространства.


**Пример использования**


Следующий пример показывает, как можно получить информацию о пересечении с помощью класса PhysicsIntersection. В этом примере линия — это невидимая трассируемая линия от точки камеры (vec3 p0) до точки указателя мыши (vec3 p1). Предполагается, что у вас есть динамический меш с назначенными телом и формой. Последовательность выполнения следующая:

- Определить и инициализировать две точки (p0 и p1) с помощью функции *[Player::getDirectionFromScreen()](../../../api/library/players/class.player_cpp.md#getDirectionFromScreen_Vec3_Vec3_int_int_int_int_int_int_void)*.
- Создать экземпляр класса PhysicsIntersection для получения информации о точке пересечения.
- Проверить, есть ли пересечение с формой, и сохранить результат в целочисленной переменной.
- В этом примере, если есть пересечение направления мыши с формой, экземпляр класса PhysicsIntersection получает точку пересечения. Результат выводится в консоль.


```cpp
// инициализируем точки направления мыши
Vec3 p0, p1;

// получаем текущего игрока (камеру)
PlayerPtr player = Game::getPlayer();
if (player.get() == NULL)
	return 0;

// получаем ширину и высоту текущего окна приложения
ivec2 main_size = ivec2_one;
EngineWindowPtr main_window = WindowManager::getMainWindow();
if (!main_window)
	Engine::get()->quit();

main_size = main_window->getSize();

// получаем текущие координаты X и Y указателя мыши
int mouse_x = Input::getMousePosition().x - main_window->getPosition().x;
int mouse_y = Input::getMousePosition().y - main_window->getPosition().y;

// получаем направление мыши от позиции игрока (p0) до курсора мыши (p1)
player->getDirectionFromScreen(p0, p1, 0, 0, mouse_x, mouse_y, main_size.x, main_size.y);

// создаём экземпляр объекта PhysicsIntersection для сохранения информации о пересечении
PhysicsIntersectionPtr intersection = PhysicsIntersection::create();
// создаём целочисленную переменную для проверки результата пересечения
int result = 0;
result = shape->getIntersection(p0, p1, intersection);
// если пересечение было, выводим сообщение в консоль
if (result != 0)
{
	Log::message("Intersection point: (%f %f %f) \n", intersection->getPoint().x, intersection->getPoint().y, intersection->getPoint().z);
}
/* ... */


```


### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальная точка линии.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечная точка линии.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[PhysicsIntersection](../../../api/library/physics/class.physicsintersection_cpp.md)> &* **intersection** - Экземпляр класса [PhysicsIntersection](../../../api/library/physics/class.physicsintersection_cpp.md), содержащий информацию о пересечении.

### Возвращаемое значение

1, если пересечение обнаружено; иначе - 0.
## int getIntersection ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , Math:: Vec3 * OUT_ret_point , Math:: vec3 * OUT_ret_normal ) const


Выполняет трассировку от точки p0 до точки p1 для поиска формы, пересекаемой этой линией. Пересечение находится только для объектов с совпадающей маской пересечений.


> **Notice:** Для этой функции используются координаты мирового пространства.


### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальная точка линии (в мировых координатах).
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечная точка линии (в мировых координатах).
- *Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) ** **OUT_ret_point** - Контейнер, в который будут помещены координаты точки контакта (если есть), в мировой системе координат. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) ** **OUT_ret_normal** - Контейнер, в который будут помещены координаты нормали точки контакта (если есть), в мировой системе координат. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

### Возвращаемое значение

1, если пересечение обнаружено; иначе - 0.
## void setPhysicsIntersectionMask ( int mask )

Задаёт [physics intersection mask](../../../principles/bit_masking/index.md#physics_intersection_mask) для формы.
### Аргументы

- *int* **mask** - Целое число, каждый бит которого является маской.

## int getPhysicsIntersectionMask ( ) const

Возвращает [physics intersection mask](../../../principles/bit_masking/index.md#physics_intersection_mask) формы.
### Возвращаемое значение

Целое число, каждый бит которого является маской.
## void setMass ( float mass )

Задаёт массу формы. Изменение массы влияет на плотность, которая вычисляется путём деления массы на объём формы.
> **Notice:** Если *g* (гравитация Земли) равна 9.8 м/с², а 1 единица равна 1 м, форма со значением массы **1** весит 1 кг.


### Аргументы

- *float* **mass** - Масса формы. Если указано отрицательное значение, вместо него используется **0**.

## float getMass ( ) const

Возвращает массу формы.
> **Notice:** Если *g* (гравитация Земли) равна 9.8 м/с², а 1 единица равна 1 м, масса измеряется в килограммах.


### Возвращаемое значение

Масса формы.
## void setName ( const char * name )

Задаёт имя формы.
### Аргументы

- *const char ** **name** - Имя формы.

## const char * getName ( ) const

Возвращает имя формы.
### Возвращаемое значение

Имя формы.
## int getNumber ( ) const

Возвращает количество экземпляров формы.
### Возвращаемое значение

Количество экземпляров формы.
## void setRestitution ( float restitution )

Задаёт упругость поверхности формы.
### Аргументы

- *float* **restitution** - Упругость поверхности формы. Указанное значение будет ограничено диапазоном **[0; 1]**.

## float getRestitution ( ) const

Возвращает упругость поверхности формы.
### Возвращаемое значение

Упругость поверхности формы.
## void setPosition ( const Math:: Vec3 & position )

Задаёт позицию формы. Этот метод сбрасывает [velocity](#setVelocity_vec3_float_void) формы в 0.
> **Notice:** Этот метод следует вызывать только из объекта, владеющего этой формой. Если форма принадлежит телу, настоятельно рекомендуется использовать метод [setShapeTransform()](../../../api/library/physics/class.body_cpp.md#setShapeTransform_int_mat4_void) владеющего тела.


### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **position** - Новая позиция формы, в мировых координатах.

## Math:: Vec3 getPosition ( ) const

Возвращает текущую позицию формы объекта, в мировых координатах.
### Возвращаемое значение

Текущая позиция формы, в мировых координатах.
## bool isIdentity ( ) const

Возвращает значение, указывающее, имеет ли форма масштаб, равный 1, и отсутствие поворота.
### Возвращаемое значение

**1**, если форма имеет масштаб, равный 1, и отсутствие поворота; иначе **0**.
## void setTransform ( const Math:: Mat4 & transform )

Задаёт матрицу трансформации формы объекта (в мировых координатах). Эта матрица описывает позицию и ориентацию формы. Этот метод сбрасывает линейную скорость формы в **0**.
> **Notice:** Этот метод следует вызывать только из объекта, владеющего этой формой. Если форма принадлежит телу, настоятельно рекомендуется использовать метод [setShapeTransform()](../../../api/library/physics/class.body_cpp.md#setShapeTransform_int_mat4_void) владеющего тела.


### Аргументы

- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации

## Math:: Mat4 getTransform ( ) const

Возвращает матрицу трансформации формы объекта (в мировых координатах). Эта матрица описывает позицию и ориентацию формы.
### Возвращаемое значение

Матрица трансформации
## Shape::TYPE getType ( ) const

Возвращает тип формы.
### Возвращаемое значение

Одна из предопределённых переменных *SHAPE_**.
## const char * getTypeName ( ) const

Возвращает имя типа формы.
### Возвращаемое значение

Имя типа формы.
## const char * getTypeName ( int type )

Возвращает имя типа формы с указанным ID.
### Аргументы

- *int* **type** - ID типа формы. Одно из значений *[SHAPE_*](#SHAPE_BOX)*.

### Возвращаемое значение

Имя типа формы.
## void setVelocity ( const Math:: vec3 & velocity , float ifps )

Задаёт новый вектор скорости формы.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **velocity** - Вектор скорости, каждый компонент которого представляет скорость формы вдоль соответствующей оси, в единицах в секунду.
- *float* **ifps** - Значение обратного FPS.

## Math:: vec3 getVelocity ( ) const

Возвращает текущий вектор скорости формы.
### Возвращаемое значение

Текущий вектор скорости, каждый компонент которого представляет скорость формы вдоль соответствующей оси, в единицах в секунду.
## float getVolume ( ) const

Возвращает объём формы.
### Возвращаемое значение

Объём формы, в кубических единицах.
## Ptr < Shape > clone ( ) const

Клонирует форму.
### Возвращаемое значение

Копия формы.
## void renderVisualizer ( const Math:: vec4 & color )

Отрисовывает форму.
> **Notice:** Необходимо включить визуализатор движка консольной командой **show_visualizer 1**.


### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, в котором будет отрисована форма.

## bool saveState ( const Ptr < Stream > & stream ) const

Сохраняет состояние указанного узла в двоичный поток.
- Если узел является родительским для других узлов, состояния этих дочерних узлов нужно сохранять вручную.
- Чтобы сохранить состояние из [buffer](../../../api/library/common/class.blob_cpp.md), [file](../../../api/library/filesystem/class.file_cpp.md) или сообщения из [socket](../../../api/library/networking/class.socket_cpp.md), убедитесь, что поток [opened](../../../api/library/common/class.stream_cpp.md#isOpened_int). Для буферов и файлов также необходимо задать правильную позицию для чтения.


**Пример** использования методов saveState() и [restoreState()](#restoreState_Stream_int):


```cpp
// задаём состояние формы
shape->setFriction(0.8f);

// сохраняем состояние
BlobPtr blob_state = Blob::create();
shape->saveState(blob_state);

// изменяем состояние
shape->setFriction(0.4f);

// восстанавливаем состояние
blob_state->seekSet(0);       // возвращаем каретку в начало blob'а
shape->restoreState(blob_state);


```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток для сохранения данных состояния узла.

### Возвращаемое значение

true, если состояние узла успешно сохранено; иначе false.
## int restoreState ( const Ptr < Stream > & stream )

Восстанавливает состояние указанного узла из двоичного потока.
- Если узел является родительским для других узлов, состояния этих дочерних узлов нужно восстанавливать вручную.
- Чтобы сохранить состояние в [buffer](../../../api/library/common/class.blob_cpp.md), [file](../../../api/library/filesystem/class.file_cpp.md) или сообщение в [socket](../../../api/library/networking/class.socket_cpp.md), убедитесь, что поток [opened](../../../api/library/common/class.stream_cpp.md#isOpened_int). При необходимости для буферов и файлов можно задать позицию для записи.


**Пример** использования методов [saveState()](#saveState_Stream_int) и restoreState():


```cpp
// задаём состояние формы
shape->setFriction(0.8f);

// сохраняем состояние
BlobPtr blob_state = Blob::create();
shape->saveState(blob_state);

// изменяем состояние
shape->setFriction(0.4f);

// восстанавливаем состояние
blob_state->seekSet(0);       // возвращаем каретку в начало blob'а
shape->restoreState(blob_state);


```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток с сохранёнными данными состояния узла.

### Возвращаемое значение

true, если состояние узла успешно восстановлено; иначе false.
## void swap ( const Ptr < Shape > & shape )

Меняет местами формы, сохраняя указатели.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Shape](../../../api/library/physics/class.shape_cpp.md)> &* **shape** - Форма для обмена.

## Ptr < Shape > createShape ( int type )

Создаёт новую форму указанного типа.
### Аргументы

- *int* **type** - Тип тела. Одно из значений [SHAPE_*](#SHAPE_BOX).

### Возвращаемое значение

Умный указатель на новую созданную форму.
## Ptr < Shape > createShape ( const char * type_name )

Создаёт новую форму указанного типа.
### Аргументы

- *const char ** **type_name** - Имя типа формы.

### Возвращаемое значение

Умный указатель на новую созданную форму.
## Shape::TYPE getTypeID ( const char * type )

### Аргументы

- *const char ** **type**

## Math:: WorldBoundBox getBoundBox ( ) const

## Math:: WorldBoundSphere getBoundSphere ( ) const
