# Unigine::NavigationMesh Class (CPP)

**Header:** #include <UniginePathFinding.h>

**Inherits from:** Navigation


Этот класс позволяет создать область навигации над поверхностью произвольного меша. По сути, navigation mesh — это область заданной [height](#setHeight_float_void) над полигонами меша, доступная для поиска пути.

> **Notice:** Меш, используемый в качестве основы для navigation mesh, должен соответствовать требованиям, описанным [here](../../../objects/navigations/navigation/navigation_mesh/index.md#create).


#### См. также


- Статья [Navigation Mesh](../../../objects/navigations/navigation/navigation_mesh/index.md)
- C++ samples:

  -
  -
- C# samples:

  -
  -

  -
  -


## NavigationMesh Class

### Методы класса

## const char * getMeshPath () const

Возвращает текущий путь к файлу `*.mesh`, используемому в качестве основы для navigation mesh.
### Возвращаемое значение

Текущий путь к файлу `*.mesh`.
## void setHeight ( float height = 1.0f )

Задаёт новое расстояние над полигонами navigation mesh, доступное для поиска пути.
### Аргументы

- *float* **height** - Высота, в единицах. Значение по умолчанию: 1.0.

## float getHeight () const

Возвращает текущее расстояние над полигонами navigation mesh, доступное для поиска пути.
### Возвращаемое значение

Текущая высота, в единицах. Значение по умолчанию: 1.0.
## void setDepth ( int depth )

Задаёт новое значение глубины. Чем больше значение глубины, тем лучше контроль над точностью и скоростью расчёта маршрута.
### Аргументы

- *int* **depth** - Глубина, целочисленное значение в диапазоне [0;4].

## int getDepth () const

Возвращает текущее значение глубины. Чем больше значение глубины, тем лучше контроль над точностью и скоростью расчёта маршрута.
### Возвращаемое значение

Текущая глубина, целочисленное значение в диапазоне [0;4].
---

## static NavigationMeshPtr create ( )

Конструктор. Создаёт пустой navigation mesh.
## static NavigationMeshPtr create ( const char * arg1 )

Создаёт navigation mesh из указанного файла `*.mesh`.
### Аргументы

- *const char ** **arg1** - Путь к файлу `*.mesh`.

## int setMesh ( const Ptr < Mesh > & mesh )

Копирует указанный меш в меш, на котором основан текущий navigation mesh.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh** - Копируемый меш.

### Возвращаемое значение

1, если меш успешно скопирован; иначе 0.
## int getMesh ( const Ptr < Mesh > & mesh )

Копирует меш, используемый в качестве основы для текущего navigation mesh, в полученный меш.
> **Notice:** Меш, используемый в качестве основы для navigation mesh, должен соответствовать требованиям, описанным [here](../../../objects/navigations/navigation/navigation_mesh/index.md#create).


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh** - Меш, в который копируется текущий меш.

### Возвращаемое значение

1, если меш успешно скопирован; иначе 0.
## int setMeshPath ( const char * path , int force_load = 0 )

Задаёт новый путь для меша, используемого в качестве основы для navigation mesh, и принудительно загружает меш по новому пути для текущего navigation mesh.
### Аргументы

- *const char ** **path** - Новый путь к файлу `*.mesh`.
- *int* **force_load** - Флаг принудительной загрузки.

  - Если указано 1, меш по новому пути будет загружен немедленно.
  - Если указано 0, будет обновлён только путь к мешу.

### Возвращаемое значение

true, если:
- Текущий путь к мешу совпадает с новым путём.
- Меш по новому пути был успешно загружен.
- Флаг принудительной загрузки установлен в 0.

 В остальных случаях — false.
## int loadMesh ( const char * path )

Загружает из файла меш, на котором основан navigation mesh. Эта функция не изменяет имя меша.
### Аргументы

- *const char ** **path** - Относительный путь к файлу `*.mesh`.

### Возвращаемое значение

1, если меш успешно загружен; иначе 0.
## int saveMesh ( const char * path )

Сохраняет в файл меш, на котором основан navigation mesh.
### Аргументы

- *const char ** **path** - Относительный путь к файлу `*.mesh`.

### Возвращаемое значение

1, если меш успешно сохранён; иначе 0.
## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [Navigation](../../../api/library/pathfinding/class.navigation_cpp.md).
