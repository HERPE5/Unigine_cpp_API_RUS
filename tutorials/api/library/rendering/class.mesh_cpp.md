# Unigine.Mesh Class (CPP)

**Header:** #include <UnigineMesh.h>


Класс *Mesh* - это контейнер, предоставляющий интерфейс для загрузки, изменения и сохранения мешей.


С помощью этого класса вы можете создать меш, добавить в него геометрию (например, поверхность box, plane, capsule или cylinder), а затем использовать его для создания следующих объектов:

- [Static mesh](../../../api/library/objects/class.objectmeshstatic_cpp.md)
- [Dynamic mesh](../../../api/library/objects/class.objectmeshdynamic_cpp.md)
- [Decal mesh](../../../api/library/decals/class.decalmesh_cpp.md)
- [Gui mesh](../../../api/library/objects/class.objectguimesh_cpp.md)
- [Water mesh](../../../api/library/objects/class.objectwatermesh_cpp.md)


Вы также можете получить доступ к геометрии всех этих объектов через класс Mesh.


Особенности Mesh:


- **Тангенциальный базис на основе кватернионов** Тангенциальное пространство (normal, tangent, bitangent) для каждой поверхности закодировано с использованием кватернионов.
- **8-битные цвета вершин** Цвета вершин хранятся с точностью 8 бит на канал.
- **Двойная система индексации** Каждая вершина связана с двумя буферами:

  - Coordinate buffer: хранит позиции вершин
  - Triangle buffer: хранит уникальные атрибуты вершин
- **Два набора UV на вершину** Поверхности поддерживают два набора текстурных координат на вершину.


### Структура Mesh


Каждый экземпляр Mesh содержит:


- *[A Bounding Box](../../../api/library/rendering/class.mesh_cpp.md#BoundBox)*
- *[A Bounding Sphere](../../../api/library/rendering/class.mesh_cpp.md#BoundSphere)*
- Одну или несколько поверхностей


> **Notice:** Большинство методов, работающих с поверхностями, по умолчанию используют индекс поверхности 0. Если метод должен работать со всеми поверхностями, вместо этого используйте -1. Эти значения обычно заданы как параметры методов по умолчанию.


**Поверхности**


Поверхность - это подмножество геометрии объекта (т.е. меша), не пересекающееся с другими подмножествами. Каждая поверхность меша содержит:


- **[Name](../../../api/library/rendering/class.mesh_cpp.md#setSurfaceName_int_cstr_void)** Уникальная строка, используемая для идентификации поверхности внутри меша.
- **[A Bounding Box](../../../api/library/rendering/class.mesh_cpp.md#getBoundBox_int_BoundBox)** Параллелепипед, выровненный по осям, охватывающий геометрию поверхности.
- **[Bounding Sphere](../../../api/library/rendering/class.mesh_cpp.md#getBoundSphere_int_BoundSphere)** Сферическая граница вокруг геометрии поверхности.
- **Текстурные координаты (наборы UV)** Каждая вершина хранит два набора UV-координат: первый обычно используется для базовых текстур, второй - для карт освещения (lightmaps) или дополнительных эффектов.
- **Цвета вершин** Каждая вершина может опционально хранить цвет RGBA, обычно закодированный с точностью 8 бит на канал. Хотя сам меш не рендерит цвета вершин напрямую, они могут быть доступны и использованы в материалах для эффектов, таких как смешивание, маскирование или процедурное затенение. См. [example](../../../content/materials/graph/samples/vertex_color/index.md) использования цветов вершин в материале.
- **Рёбра и пространственное дерево** Каждая поверхность хранит данные о рёбрах и пространственное дерево для ускорения пространственных запросов, таких как определение пересечений и столкновений.
- **Координатные и треугольные индексы** Каждая поверхность включает два буфера индексов: координатные индексы и треугольные индексы. Их назначение подробно описано ниже.


### Данные вершин и индексы


Каждая поверхность меша состоит из треугольников, причём каждый треугольник имеет 3 вершины. Таким образом, общее количество вершин на поверхность вычисляется как:


**Общее число вершин = *3 * Число треугольников***.


Если вершина используется несколькими треугольниками, обычно её пришлось бы хранить несколько раз, причём каждая копия содержала бы такие данные, как позиция, нормаль, тангенс, текстурные координаты и т.д. Чтобы минимизировать избыточность и повысить производительность загрузки, UNIGINE использует оптимизированную компоновку, разделяющую данные вершин на два отдельных буфера:


- **Буфер координатных вершин (*CVertices*)**, хранящий только координаты вершин.
- **Буфер треугольных вершин (*TVertices*)**, хранящий атрибуты вершин, такие как normal, binormal, tangent, цвет, UV-координаты.


На изображении ниже стрелками показаны [normals](#diff_normals):


![](tcindices.png)

*Поверхность, содержащая 2 смежных треугольника. Здесь C0...C3 - координатные вершины, T0...T5 - треугольные вершины*


Координатный буфер - это массив **уникальных позиций вершин**. Чтобы уменьшить дублирование данных, вершины поверхности с одинаковыми координатами хранятся в буфере **только один раз**.


Например, координатный буфер для поверхности, представленной на изображении выше, выглядит следующим образом:


```text
CVertices = [C0, C1, C2, C3]
```


Каждый треугольник поверхности имеет 3 координаты. У нас 2 треугольника, следовательно, у нас 6 вершин, но в буфере CVertices мы сохраняем только 4, потому что 2 из них (C1 и C3) имеют одинаковые координаты. Каждая координатная вершина содержит координаты (*float[3]*) вершины.


> **Notice:** Поскольку координатный буфер хранит только неповторяющиеся позиции вершин, общее количество вершин в меше и количество записей в буфере CVertices совпадают.


Треугольный буфер - это массив **записей атрибутов вершин для каждого треугольника**. Например, треугольный буфер для поверхности, представленной на изображении выше, выглядит следующим образом:


```text
TVertices = [T0, T1, T2, T3, T4, T5]
```


Каждая треугольная вершина может хранить:


- Normal (нормаль)
- Binormal (бинормаль)
- Tangent (тангенс)
- Текстурные координаты 1-й карты UV
- Текстурные координаты 2-й карты UV
- Цвет


> **Notice:** Количество вершин и треугольных вершин может отличаться.


Количество записей в треугольном буфере (TVertices) зависит от того, как вершина используется в разных треугольниках:


- Если вершина используется несколькими треугольниками, но имеет разные атрибуты (например, разные нормали или тангенсы), будет сохранено несколько записей атрибутов - по одной для каждого варианта. На изображении выше координатная вершина **C1** соответствует двум треугольным вершинам: **T1** и **T2**.
- Если вершина используется несколькими треугольниками и её атрибуты идентичны для всех треугольников, достаточно одной записи атрибутов, которая будет использована повторно.


И координатная, и треугольная вершины **индексируются**. Существует **2 буфера индексов** для получения корректных данных CVertex и TVertex для каждой вершины каждого треугольника меша:


- **Буфер координатных индексов (CIndices)** - координатные индексы, являющиеся ссылками на данные [CVertices](#cvertex).
- **Буфер треугольных индексов (TIndices)** - треугольные индексы, являющиеся ссылками на данные [TVertices](#tvertex).


Количество элементов в этих буферах индексов равно [total number of vertices](#total_vertex_number) поверхности меша.


> **Notice:** Фактически структуры с названием "треугольная вершина" не существует. Все атрибуты вершин (нормали, тангенсы, UV и т.д.) хранятся отдельно и связываются через буферы индексов. Термин "треугольная вершина" используется здесь только для удобства описания того, как атрибуты связаны с позициями вершин.
> Подробнее об организации структуры меша с точки зрения формата файла см. статью ***[Mesh File Formats](../../../code/formats/file_formats.md#mesh)***.


#### Координатные индексы


Каждая вершина поверхности меша имеет **координатный индекс** - номер соответствующего элемента [coordinate buffer](#indices), где хранятся данные. Для данной поверхности массив координатных индексов выглядит следующим образом:


```text
CIndices = [Ci0, Ci1, Ci3, Ci1, Ci2, Ci3]
```


Здесь:


- Первые 3 элемента - координатные индексы первого (нижнего) треугольника.
- Вторые 3 элемента - координатные индексы второго (верхнего) треугольника.


#### Треугольные индексы


Каждая вершина поверхности меша также имеет **треугольный индекс** - номер соответствующего элемента [triangle buffer](#indices), где хранятся данные. Для данной поверхности массив треугольных индексов выглядит следующим образом:


```text
TIndices = [Ti0, Ti1, Ti5, Ti2, Ti3, Ti4]
```


Здесь:


- Первые 3 элемента - треугольные индексы первого (нижнего) треугольника.
- Вторые 3 элемента - треугольные индексы второго (верхнего) треугольника.


> **Notice:** Количество координатных и треугольных индексов совпадает.


### Сериализация


Вы можете сохранить созданный меш в файл для последующего использования с помощью метода [*save()*](#save_cstr_int). Позже вы можете создать новый меш из этого файла с помощью [constructor](#Mesh_constchar) или загрузить меш с помощью метода [*load()*](#load_cstr_int).


> **Notice:** Нормали меша не сериализуются. Вместо них сериализуется весь [tangent basis](#createTangents_int_int).


Таким образом, чтобы получить нормали из сохранённого меша, необходимо сделать следующее:


```cpp
// добавляем поверхность и вершины в меш
MeshPtr mesh = Unigine::Mesh::create();
// добавляем поверхность и вершины в меш
mesh->addSurface("0");
mesh->addVertex(Unigine::Math::vec3(1.f, 1.f, 0.f), 0);
mesh->addVertex(Unigine::Math::vec3(1.f, 0.f, 1.f), 0);
mesh->addVertex(Unigine::Math::vec3(0.f, 1.f, 1.f), 0);

// создаём нормали
mesh->addNormal(Unigine::Math::vec3(0.f, 0.f, 1.f), 0);
mesh->addNormal(Unigine::Math::vec3(0.f, 0.f, 1.f), 0);
mesh->addNormal(Unigine::Math::vec3(0.f, 0.f, 1.f), 0);

// добавляем индексы вершин
mesh->addIndex(0, 0);
mesh->addIndex(1, 0);
mesh->addIndex(2, 0);

// создаём сериализуемый тангенциальный базис
mesh->createTangents();

// сохраняем меш в файл
mesh->save("hello.mesh");

```


Теперь, чтобы получить нормали после создания меша из файла:


```cpp
// создаём меш из ранее сохранённого файла
MeshPtr mesh = Unigine::Mesh::create("hello.mesh");

// получаем общее количество записей тангенсов вершин для первой поверхности меша
auto numTangents = mesh->getNumTangents(0);

// извлекаем нормали из тангенциального базиса для первой точки первой поверхности меша
auto normal = mesh->getTangent(0, 0).getNormal();

```


### См. также


- Статья [Mesh File Formats](../../../code/formats/file_formats.md#mesh)
- [Mesh Class Usage Example](../../../code/usage/mesh_class/index_cpp.md)


## Mesh Class

### Перечисления

## LIGHTMAP_RESOLUTION

Разрешение [lightmaps](../../../editor2/lighting/gi/lightmaps.md), генерируемых для поверхности.
| Name | Description |
|---|---|
| **LIGHTMAP_RESOLUTION_MODE_32** = 0 | Разрешение [Lightmap](../../../editor2/lighting/gi/lightmaps.md) 32 x 32. |
| **LIGHTMAP_RESOLUTION_MODE_64** = 1 | Разрешение [Lightmap](../../../editor2/lighting/gi/lightmaps.md) 64 x 64. |
| **LIGHTMAP_RESOLUTION_MODE_128** = 2 | Разрешение [Lightmap](../../../editor2/lighting/gi/lightmaps.md) 128 x 128. |
| **LIGHTMAP_RESOLUTION_MODE_256** = 3 | Разрешение [Lightmap](../../../editor2/lighting/gi/lightmaps.md) 256 x 256. |
| **LIGHTMAP_RESOLUTION_MODE_512** = 4 | Разрешение [Lightmap](../../../editor2/lighting/gi/lightmaps.md) 512 x 512. |
| **LIGHTMAP_RESOLUTION_MODE_1024** = 5 | Разрешение [Lightmap](../../../editor2/lighting/gi/lightmaps.md) 1024 x 1024. |
| **LIGHTMAP_RESOLUTION_MODE_2048** = 6 | Разрешение [Lightmap](../../../editor2/lighting/gi/lightmaps.md) 2048 x 2048. |
| **LIGHTMAP_RESOLUTION_MODE_4096** = 7 | Разрешение [Lightmap](../../../editor2/lighting/gi/lightmaps.md) 4096 x 4096. |

### Методы класса

---

## static MeshPtr create ( )

Конструктор. Создаёт пустой меш.
## static MeshPtr create ( const char * path )

Конструктор. Создаёт меш, используя заданный файл.
### Аргументы

- *const char ** **path** - Путь к файлу меша.

## static MeshPtr create ( const Ptr <ConstMesh> & constmesh )

Конструктор.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<ConstMesh> &* **constmesh** - Экземпляр константного меша (Constant Mesh).

## void assignFrom ( const Ptr <ConstMesh> & mesh )

Копирует данные, включая кости, поверхности и анимации, из заданного исходного меша.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<ConstMesh> &* **mesh** - Экземпляр исходного меша.

## void swap ( const Ptr < Mesh > & mesh )

Меняет местами все внутренние данные между этим мешем и заданным. Используется для эффективного обмена данными геометрии без копирования памяти.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh** - Меш, с которым обмениваются данными.

## void setBoundBox ( const Math:: BoundBox & bb , int surface )

Задаёт ограничивающий параллелепипед для заданной поверхности меша.
### Аргументы

- *const  Math::[BoundBox](../../../api/library/math/bounds/class.boundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед для задания.
- *int* **surface** - Номер поверхности меша.

## void setBoundBox ( const Math:: BoundBox & bb )

Задаёт ограничивающий параллелепипед для текущего меша.
### Аргументы

- *const  Math::[BoundBox](../../../api/library/math/bounds/class.boundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед для задания.

## Math:: BoundBox getBoundBox ( int surface ) const

Возвращает ограничивающий параллелепипед заданной поверхности меша.
### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Ограничивающий параллелепипед.
## Math:: BoundBox getBoundBox ( ) const

Возвращает ограничивающий параллелепипед текущего меша.
### Возвращаемое значение

Ограничивающий параллелепипед.
## void setBoundSphere ( const Math:: BoundSphere & bs )

Задаёт ограничивающую сферу для текущего меша.
### Аргументы

- *const  Math::[BoundSphere](../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Ограничивающая сфера для задания.

## void setBoundSphere ( const Math:: BoundSphere & bs , int surface )

Задаёт ограничивающую сферу для заданной поверхности меша.
### Аргументы

- *const  Math::[BoundSphere](../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Ограничивающая сфера для задания.
- *int* **surface** - Номер поверхности меша.

## Math:: BoundSphere getBoundSphere ( ) const

Возвращает ограничивающую сферу текущего меша.
### Возвращаемое значение

Ограничивающая сфера.
## Math:: BoundSphere getBoundSphere ( int surface ) const

Возвращает ограничивающую сферу заданной поверхности меша.
### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Ограничивающая сфера.
## void setCIndex ( int num , int index , int surface = 0 )

Задаёт новый [coordinate index](#cindices) для заданной вершины заданной поверхности.
### Аргументы

- *int* **num** - Номер вершины в диапазоне от 0 до общего количества координатных индексов заданной поверхности. > **Notice:** Чтобы получить общее количество координатных индексов заданной поверхности, используйте метод [getNumCIndices()](#getNumCIndices_int_int).
- *int* **index** - Задаваемый координатный индекс в диапазоне от 0 до общего количества координатных вершин заданной поверхности. > **Notice:** Чтобы получить общее количество координатных вершин заданной поверхности, используйте метод [getNumCVertex()](#getNumCVertex_int_int).
- *int* **surface** - Номер поверхности меша.

## int getCIndex ( int num , int surface = 0 ) const

Возвращает [coordinate index](#cindices) заданной вершины заданной поверхности.
### Аргументы

- *int* **num** - Номер вершины в диапазоне от 0 до общего количества координатных индексов заданной поверхности. > **Notice:** Чтобы получить общее количество координатных индексов заданной поверхности, используйте метод [getNumCIndices()](#getNumCIndices_int_int).
- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Координатный индекс.
## void setColor ( int num , const Math:: vec4 & color , int surface = 0 )

Задаёт цвет для заданной [triangle vertex](#tvertex) заданной поверхности.
### Аргументы

- *int* **num** - Номер [triangle vertex](#tvertex) в диапазоне от 0 до общего количества записей цветов вершин заданной поверхности. > **Notice:** Чтобы получить общее количество записей цветов вершин поверхности, вызовите метод [*getNumColors()*](#getNumColors_int_int).
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Задаваемый цвет вершины.
- *int* **surface** - Номер поверхности меша.

## Math:: vec4 getColor ( int num , int surface = 0 ) const

Возвращает цвет заданной [triangle vertex](#tvertex) заданной поверхности.
### Аргументы

- *int* **num** - Номер [triangle vertex](#tvertex) в диапазоне от 0 до общего количества записей цветов вершин заданной поверхности. > **Notice:** Чтобы получить общее количество записей цветов вершин поверхности, вызовите метод [*getNumColors()*](#getNumColors_int_int).
- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Цвет вершины.
## void setIndex ( int num , int index , int surface = 0 )

Задаёт оба индекса - [coordinate](#cindices) и [triangle](#tindices) - для заданной вершины заданной поверхности равными заданному индексу.
### Аргументы

- *int* **num** - Номер вершины в диапазоне от 0 до общего количества координатных индексов заданной поверхности. > **Notice:** Чтобы получить общее количество координатных индексов поверхности, используйте метод [getNumCIndices()](#getNumCIndices_int_int).
- *int* **index** - Задаваемый индекс в диапазоне от 0 до общего количества координатных вершин. > **Notice:** Чтобы получить общее количество координатных вершин, используйте метод [getNumVertex()](#getNumVertex_int_int).
- *int* **surface** - Номер поверхности меша.

## int getIndex ( int num , int surface = 0 ) const

Возвращает [coordinate index](#cindices) заданной вершины заданной поверхности, если координатный индекс равен [triangle index](#tindices).
### Аргументы

- *int* **num** - Номер вершины в диапазоне от 0 до общего количества координатных индексов заданной поверхности. > **Notice:** Чтобы получить общее количество координатных индексов поверхности, используйте метод [getNumCIndices()](#getNumCIndices_int_int).
- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

[Coordinate index](#cindices).
## bool getIntersection ( const Math:: vec3 & p0 , const Math:: vec3 & p1 , Math:: vec3 * OUT_ret_point , Math:: vec3 * OUT_ret_normal , int * OUT_ret_index , int surface ) const

Выполняет поиск пересечения заданной поверхности с заданной трассируемой линией.
> **Notice:** В этом методе используются координаты локального пространства меша.


### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Координаты начальной точки.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Координаты конечной точки.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) ** **OUT_ret_point** - Возвращаемый массив для записи координат точки пересечения. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) ** **OUT_ret_normal** - Возвращаемый массив для записи нормали точки пересечения. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *int ** **OUT_ret_index** - Возвращаемый массив для записи индексов точки пересечения. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

1, если пересечение найдено; иначе 0.
## void setNormal ( int num , const Math:: vec3 & normal , int surface = 0 )

Задаёт нормаль для заданной [triangle vertex](#tvertex) заданной поверхности.
> **Notice:** Нормаль вершины не будет записана в файл `*.mesh`. Она будет храниться только в памяти.


### Аргументы

- *int* **num** - Номер [triangle vertex](#tvertex) в диапазоне от 0 до общего количества записей нормалей вершин заданной поверхности. > **Notice:** Чтобы получить общее количество записей нормалей вершин поверхности, вызовите метод [*getNumNormals()*](#getNumNormals_int_int).
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **normal** - Задаваемая нормаль.
- *int* **surface** - Номер поверхности меша.

## Math:: vec3 getNormal ( int num , int surface = 0 ) const

Возвращает нормаль заданной [triangle vertex](#tvertex) заданной поверхности.
### Аргументы

- *int* **num** - Номер [triangle vertex](#tvertex) в диапазоне от 0 до общего количества записей нормалей вершин заданной поверхности. > **Notice:** Чтобы получить общее количество записей нормалей вершин поверхности, вызовите метод [*getNumNormals()*](#getNumNormals_int_int).
- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Нормаль вершины.
## void setNumCIndices ( int size , int surface = 0 )

Задаёт общее количество [coordinate indices](#cindices) для заданной поверхности.
### Аргументы

- *int* **size** - Задаваемое количество координатных индексов.
- *int* **surface** - Номер поверхности меша.

## int getNumCIndices ( int surface = 0 ) const

Возвращает общее количество [coordinate indices](#cindices) для заданной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Количество координатных индексов.
## void setNumColors ( int size , int surface = 0 )

Задаёт общее количество записей цветов вершин для заданной поверхности.
> **Notice:** Цвета задаются для [triangle vertices](#tvertex).


### Аргументы

- *int* **size** - Задаваемое количество записей цветов вершин.
- *int* **surface** - Номер поверхности меша.

## int getNumColors ( int surface = 0 ) const

Возвращает общее количество записей цветов вершин для заданной поверхности.
> **Notice:** Цвета задаются для [triangle vertices](#tvertex).


### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Количество записей цветов вершин.
## int getNumCVertex ( int surface = 0 ) const

Возвращает количество [coordinate vertices](#cvertex) заданной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Количество координатных вершин.
## void setNumIndices ( int size , int surface = 0 )

Задаёт количество [indices](#indices) для заданной поверхности: обновляет количество координатных и треугольных индексов. Например, если передать 5 в качестве первого аргумента, количество координатных индексов и количество треугольных индексов будет задано равным 5.
### Аргументы

- *int* **size** - Задаваемое количество индексов.
- *int* **surface** - Номер поверхности меша.

## int getNumIndices ( int surface = 0 ) const

Возвращает количество [coordinate indices](#cindices) заданной поверхности, если количество координатных индексов равно количеству треугольных индексов.
### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Количество координатных индексов.
## void setNumNormals ( int size , int surface = 0 )

Задаёт общее количество записей нормалей вершин для заданной поверхности.
> **Notice:** Нормали задаются для [triangle vertices](#tvertex).


### Аргументы

- *int* **size** - Задаваемое количество записей нормалей вершин.
- *int* **surface** - Номер поверхности меша.

## int getNumNormals ( int surface = 0 ) const

Возвращает общее количество записей нормалей вершин для заданной поверхности.
> **Notice:** Нормали задаются для [triangle vertices](#tvertex).


### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Количество записей нормалей вершин для заданной поверхности.
## int getNumSurfaces ( ) const

Возвращает общее количество поверхностей меша.
### Возвращаемое значение

Количество поверхностей меша.
## void setNumTangents ( int size , int surface = 0 )

Задаёт общее количество записей тангенсов вершин для заданной поверхности.
> **Notice:** Тангенсы задаются для [triangle vertices](#tvertex).


### Аргументы

- *int* **size** - Задаваемое количество записей тангенсов вершин.
- *int* **surface** - Номер поверхности меша.

## int getNumTangents ( int surface ) const

Возвращает общее количество записей тангенсов вершин для заданной поверхности.
> **Notice:** Тангенсы задаются для [triangle vertices](#tvertex).


### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Количество записей тангенсов вершин.
## void setNumTexCoords0 ( int size , int surface = 0 )

Задаёт общее количество записей текстурных координат первой карты UV для заданной поверхности меша.
> **Notice:** Текстурные координаты первой карты UV задаются для [triangle vertices](#tvertex).


### Аргументы

- *int* **size** - Задаваемое количество записей текстурных координат первой карты UV.
- *int* **surface** - Номер поверхности меша.

## int getNumTexCoords0 ( int surface = 0 ) const

Returns the total number of the first UV map texture coordinate entries for the given mesh surface.
> **Notice:** First UV map texture coordinates are specified for [triangle vertices](#tvertex).


### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Общее количество записей текстурных координат первой карты UV.
## void setNumTexCoords1 ( int size , int surface )

Задаёт общее количество записей текстурных координат второй карты UV для заданной поверхности меша.
> **Notice:** Текстурные координаты второй карты UV задаются для [triangle vertices](#tvertex).


### Аргументы

- *int* **size** - Задаваемое количество текстурных координат второй карты UV.
- *int* **surface** - Номер поверхности меша.

## int getNumTexCoords1 ( int surface = 0 ) const

Возвращает общее количество записей текстурных координат второй карты UV для заданной поверхности меша.
> **Notice:** Текстурные координаты второй карты UV задаются для [triangle vertices](#tvertex).


### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Общее количество записей текстурных координат второй карты UV.
## void setNumTIndices ( int size , int surface = 0 )

Задаёт общее количество [triangle indices](#tindices) для заданной поверхности.
### Аргументы

- *int* **size** - Задаваемое количество треугольных индексов.
- *int* **surface** - Номер поверхности меша.

## int getNumTIndices ( int surface = 0 ) const

Возвращает общее количество [triangle indices](#tindices) для заданной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Количество треугольных индексов.
## int getNumTVertex ( int surface = 0 ) const

Возвращает количество [triangle vertices](#tvertex) для заданной поверхности меша.
### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Количество треугольных вершин.
## void setNumVertex ( int size , int surface = 0 )

Задаёт общее количество вершин для заданной поверхности.
> **Notice:** Количество вершин и [coordinate vertices](#cvertex) совпадает.


### Аргументы

- *int* **size** - Задаваемое количество вершин.
- *int* **surface** - Номер поверхности меша.

## getNumVertex ( int surface ) const

Возвращает общее количество вершин для заданной поверхности.
> **Notice:** Количество вершин и [coordinate vertices](#cvertex) совпадает.


### Аргументы

- *int* **surface** - Номер поверхности меша.

## void setSurfaceName ( int surface , const char * name )

Задаёт имя для заданной поверхности меша.
### Аргументы

- *int* **surface** - Номер поверхности меша.
- *const char ** **name** - Задаваемое имя поверхности.

## const char * getSurfaceName ( int surface ) const

Возвращает имя заданной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Имя поверхности.
## int setSurfaceTransform ( const Math:: mat4 & transform , int surface = -1 )

Задаёт матрицу трансформации для заданной поверхности.
### Аргументы

- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Задаваемая матрица трансформации.
- *int* **surface** - Номер поверхности меша. Значение по умолчанию -1 (применяется ко всем поверхностям меша).

### Возвращаемое значение

1, если матрица трансформации успешно задана; иначе 0.
## void setSurfaceLightmapUVChannel ( int surface , char uv_channel )

Задаёт новый канал UV, используемый для [lightmaps](../../../editor2/lighting/gi/lightmaps.md) поверхности с заданным номером.
### Аргументы

- *int* **surface** - Номер поверхности меша.
- *char* **uv_channel** - Канал UV, используемый для карт освещения поверхности с заданным номером.

## char getSurfaceLightmapUVChannel ( int surface ) const

Возвращает текущий канал UV, используемый для [lightmaps](../../../editor2/lighting/gi/lightmaps.md) поверхности с заданным номером.
### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Канал UV, в данный момент используемый для карт освещения поверхности с заданным номером.
## void setSurfaceLightmapResolution ( int surface , Mesh::LIGHTMAP_RESOLUTION resolution )

Задаёт новое разрешение [lightmap](../../../editor2/lighting/gi/lightmaps.md) для поверхности с заданным номером.
### Аргументы

- *int* **surface** - Номер поверхности меша.
- *[Mesh::LIGHTMAP_RESOLUTION](../../../api/library/rendering/class.mesh_cpp.md#LIGHTMAP_RESOLUTION)* **resolution** - Разрешение карты освещения, используемое для поверхности с заданным номером.

## Mesh::LIGHTMAP_RESOLUTION getSurfaceLightmapResolution ( int surface ) const

Возвращает текущее разрешение [lightmap](../../../editor2/lighting/gi/lightmaps.md) для поверхности с заданным номером.
### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Текущее разрешение карты освещения для поверхности с заданным номером.
## void setTangent ( int num , const Math:: quat & tangent , int surface = 0 )

Задаёт новый тангенс для заданной [triangle vertex](#tvertex) заданной поверхности.
### Аргументы

- *int* **num** - Номер [triangle vertex](#tvertex) в диапазоне от 0 до общего количества записей тангенсов вершин заданной поверхности. > **Notice:** Чтобы получить общее количество записей тангенсов вершин поверхности, вызовите метод [getNumTangents()](#getNumTangents_int_int).
- *const  Math::[quat](../../../api/library/math/class.quat_cpp.md) &* **tangent** - Задаваемый тангенс.
- *int* **surface** - Номер поверхности меша.

## Math:: quat getTangent ( int num , int surface = 0 ) const

Возвращает тангенс заданной [triangle vertex](#tvertex) заданной поверхности.
### Аргументы

- *int* **num** - Номер [triangle vertex](#tvertex) в диапазоне от 0 до общего количества записей тангенсов вершин заданной поверхности. > **Notice:** Чтобы получить общее количество записей тангенсов вершин поверхности, вызовите метод [getNumTangents()](#getNumTangents_int_int).
- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Тангенс вершины.
## void setTexCoord0 ( int num , const Math:: vec2 & texcoord , int surface )

Задаёт текстурные координаты первой карты UV для заданной [triangle vertex](#tvertex) заданной поверхности.
### Аргументы

- *int* **num** - Номер [triangle vertex](#tvertex) в диапазоне от 0 до общего количества записей текстурных координат первой карты UV заданной поверхности. > **Notice:** Чтобы получить общее количество записей текстурных координат первой карты UV поверхности, вызовите метод [getNumTexCoords0()](#getNumTexCoords0_int_int).
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **texcoord** - Задаваемые текстурные координаты первой карты UV.
- *int* **surface** - Номер поверхности меша.

## Math:: vec2 getTexCoord0 ( int num , int surface ) const

Возвращает текстурные координаты первой карты UV заданной [triangle vertex](#tvertex) заданной поверхности.
### Аргументы

- *int* **num** - Номер [triangle vertex](#tvertex) в диапазоне от 0 до общего количества записей текстурных координат первой карты UV заданной поверхности. > **Notice:** Чтобы получить общее количество записей текстурных координат первой карты UV поверхности, вызовите метод [getNumTexCoords0()](#getNumTexCoords0_int_int).
- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Текстурные координаты первой карты UV.
## void setTexCoord1 ( int num , const Math:: vec2 & texcoord , int surface = 0 )

Задаёт текстурные координаты второй карты UV для заданной [triangle vertex](#tvertex) заданной поверхности.
### Аргументы

- *int* **num** - Номер [triangle vertex](#tvertex) в диапазоне от 0 до общего количества записей текстурных координат второй карты UV заданной поверхности. > **Notice:** Чтобы получить общее количество записей текстурных координат второй карты UV поверхности, вызовите метод [getNumTexCoords1()](#getNumTexCoords1_int_int).
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **texcoord** - Задаваемые текстурные координаты второй карты UV.
- *int* **surface** - Номер поверхности меша.

## Math:: vec2 getTexCoord1 ( int num , int surface = 0 ) const

Возвращает текстурные координаты второй карты UV заданной [triangle vertex](#tvertex) заданной поверхности.
### Аргументы

- *int* **num** - Номер [triangle vertex](#tvertex) в диапазоне от 0 до общего количества записей текстурных координат второй карты UV заданной поверхности. > **Notice:** Чтобы получить общее количество записей текстурных координат второй карты UV поверхности, вызовите метод [getNumTexCoords1()](#getNumTexCoords1_int_int).
- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Текстурные координаты второй карты UV.
## void setTIndex ( int num , int index , int surface = 0 )

Задаёт новый [triangle index](#tindices) для заданной вершины заданной поверхности.
### Аргументы

- *int* **num** - Номер вершины в диапазоне от 0 до общего количества треугольных индексов заданной поверхности. > **Notice:** Чтобы получить общее количество треугольных индексов, используйте метод [getNumTIndices()](#getNumTIndices_int_int).
- *int* **index** - Задаваемый треугольный индекс в диапазоне от 0 до общего количества треугольных вершин заданной поверхности. > **Notice:** Чтобы получить общее количество треугольных вершин заданной поверхности, используйте метод [getNumTVertex()](#getNumTVertex_int_int).
- *int* **surface** - Номер поверхности меша.

## int getTIndex ( int num , int surface = 0 ) const

Возвращает [triangle index](#tindices) для заданной поверхности по номеру индекса.
### Аргументы

- *int* **num** - Номер вершины в диапазоне от 0 до общего количества треугольных индексов заданной поверхности. > **Notice:** Чтобы получить общее количество треугольных индексов заданной поверхности, используйте метод [getNumTIndices()](#getNumTIndices_int_int).
- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Треугольный индекс.
## void setVertex ( int num , const Math:: vec3 & vertex , int surface = 0 )

Задаёт координаты заданной [coordinate vertex](#cvertex) заданной поверхности.
### Аргументы

- *int* **num** - Номер [coordinate vertex](#cvertex) в диапазоне от 0 до общего количества координатных вершин заданной поверхности. > **Notice:** Чтобы получить общее количество координатных вершин заданной поверхности, используйте метод [getNumCVertex()](#getNumCVertex_int_int).
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **vertex** - Задаваемые координаты вершины.
- *int* **surface** - Номер поверхности меша.

## Math:: vec3 getVertex ( int num , int surface = 0 ) const

Возвращает координаты заданной [coordinate vertex](#cvertex) заданной поверхности.
### Аргументы

- *int* **num** - Номер [coordinate vertex](#cvertex) в диапазоне от 0 до общего количества координатных вершин заданной поверхности. > **Notice:** Чтобы получить общее количество координатных вершин заданной поверхности, используйте метод [getNumCVertex()](#getNumCVertex_int_int).
- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Координаты вершины.
## int addBoxSurface ( const char * name , const Math:: vec3 & size , int collision_data_flags = COLLISION_DATA_ALL )

Добавляет поверхность box к текущему мешу.
```cpp
// создаём экземпляр меша
MeshPtr mesh = Mesh::create();
// добавляем поверхность box с именем "box_surface", размер поверхности - Vec3(1.0, 1.0, 1.0)
mesh->addBoxSurface("box_surface", Math::Vec3(1.0f));

// создаём ObjectMeshDynamic из объекта Mesh
ObjectMeshDynamicPtr dynamicMesh = ObjectMeshDynamic::create(mesh);

// задаём позицию меша
dynamicMesh->setWorldTransform(translate(Math::Vec3(10.0f,10.0f,10.0f)));

// задаём имя меша
dynamicMesh->setName("Dynamic Mesh");

```


Меш появится.


![](create_box_surface.png)


### Аргументы

- *const char ** **name** - Имя поверхности.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **size** - Размер box по осям X, Y и Z.
- *int* **collision_data_flags** - Битовая маска, определяющая, какие [types of collision data](#COLLISION_DATA_BOUNDS) генерировать для новой поверхности.

### Возвращаемое значение

Номер добавленной поверхности.
## int addCapsuleSurface ( const char * name , float radius , float height , int stacks , int slices , int collision_data_flags = COLLISION_DATA_ALL )

Добавляет поверхность capsule к текущему мешу. Stacks и slices определяют подразделение поверхности.
```cpp
// create a mesh instance
MeshPtr mesh = Mesh::create();
// add capsule surface with the name "capsule_surface".
// the radius of the capsule is 1.0, the height is 2.0,
// stacks и slices равны 200 и 100 соответственно
mesh->addCapsuleSurface("box_surface", 1.0f, 2.0f, 200, 100);

// создаём ObjectMeshDynamic из объекта Mesh
ObjectMeshDynamicPtr dynamicMesh = ObjectMeshDynamic::create(mesh);

// задаём позицию меша
dynamicMesh->setWorldTransform(translate(Math::Vec3(10.0f,10.0f,10.0f)));

// задаём имя меша
dynamicMesh->setName("Dynamic Mesh");

```


Меш появится.


![](create_capsule_surface.png)


### Аргументы

- *const char ** **name** - Имя поверхности.
- *float* **radius** - Радиус capsule.
- *float* **height** - Высота capsule.
- *int* **stacks** - Количество stacks, делящих capsule радиально.
- *int* **slices** - Количество slices, делящих capsule горизонтально.
- *int* **collision_data_flags** - Битовая маска, определяющая, какие [types of collision data](#COLLISION_DATA_BOUNDS) генерировать для новой поверхности.

### Возвращаемое значение

Номер добавленной поверхности.
## void addCIndex ( int index , int surface = 0 )

Добавляет новый [coordinate index](#cindices) в массив координатных индексов заданной поверхности.
### Аргументы

- *int* **index** - Добавляемый [coordinate index](#cindices) в диапазоне от 0 до общего количества координатных вершин. > **Notice:** Чтобы получить общее количество координатных вершин заданной поверхности, используйте метод [getNumCVertex()](#getNumCVertex_int_int).
- *int* **surface** - Номер поверхности меша.

## void addColor ( const Math:: vec4 & color , int surface = 0 )

Добавляет заданный цвет в массив цветов вершин заданной поверхности.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Добавляемый цвет.
- *int* **surface** - Номер поверхности меша.

## int addCylinderSurface ( const char * name , float radius , float height , int stacks , int slices , int collision_data_flags = COLLISION_DATA_ALL )

Добавляет поверхность cylinder к текущему мешу. Stacks и slices определяют подразделение поверхности.
```cpp
// создаём экземпляр меша
MeshPtr mesh = Mesh::create();
// добавляем поверхность cylinder с именем "cylinder_surface".
// радиус cylinder равен 1.0, высота 2.0,
// stacks и slices равны 200 и 100 соответственно
mesh->addCylinderSurface("cylinder_surface", 1.0f, 2.0f, 200, 100);

// создаём ObjectMeshDynamic из объекта Mesh
ObjectMeshDynamicPtr dynamicMesh = ObjectMeshDynamic::create(mesh);

// задаём позицию меша
dynamicMesh->setWorldTransform(translate(Math::Vec3(10.0f,10.0f,10.0f)));

// задаём имя меша
dynamicMesh->setName("Dynamic Mesh");

```


Меш появится.


![](create_cylinder_surface.png)


### Аргументы

- *const char ** **name** - Имя поверхности.
- *float* **radius** - Радиус cylinder.
- *float* **height** - Высота cylinder.
- *int* **stacks** - Количество stacks, делящих cylinder радиально.
- *int* **slices** - Количество slices, делящих cylinder горизонтально.
- *int* **collision_data_flags** - Битовая маска, определяющая, какие [types of collision data](#COLLISION_DATA_BOUNDS) генерировать для новой поверхности.

### Возвращаемое значение

Номер добавленной поверхности.
## int addDodecahedronSurface ( const char * name , float radius , int collision_data_flags = COLLISION_DATA_ALL )

Добавляет поверхность dodecahedron к текущему мешу.
```cpp
// создаём экземпляр меша
MeshPtr mesh = Mesh::create();
// добавляем поверхность dodecahedron с именем "dodecahedron_surface".
// радиус dodecahedron равен 1.0
mesh->addDodecahedronSurface("dodecahedron_surface", 1.0f);

// создаём ObjectMeshDynamic из объекта Mesh
ObjectMeshDynamicPtr dynamicMesh = ObjectMeshDynamic::create(mesh);

// задаём позицию меша
dynamicMesh->setWorldTransform(translate(Math::Vec3(10.0f,10.0f,10.0f)));

// задаём имя меша
dynamicMesh->setName("Dynamic Mesh");

```


Меш появится.


![](create_dodecahedron_surface.png)


### Аргументы

- *const char ** **name** - Имя поверхности.
- *float* **radius** - Радиус dodecahedron.
- *int* **collision_data_flags** - Битовая маска, определяющая, какие [types of collision data](#COLLISION_DATA_BOUNDS) генерировать для новой поверхности.

### Возвращаемое значение

Номер добавленной поверхности.
## int addEmptySurface ( const char * name , int num_vertex , int num_indices )

Добавляет новую пустую поверхность к текущему мешу.
> **Notice:** Эта функция выделяет только массивы вершин и индексов. Массивы текстурных координат, тангенциального базиса, весов и цветов должны выделяться вручную.


### Аргументы

- *const char ** **name** - Имя поверхности.
- *int* **num_vertex** - Количество вершин поверхности.
- *int* **num_indices** - Количество индексов поверхности.

### Возвращаемое значение

Количество поверхностей меша.
## int addIcosahedronSurface ( const char * name , float radius , int collision_data_flags = COLLISION_DATA_ALL )

Добавляет поверхность icosahedron к текущему мешу.
```cpp
// create a mesh instance
MeshPtr mesh = Mesh::create();
// добавляем поверхность icosahedron с именем "icosahedron_surface".
// радиус icosahedron равен 1.0
mesh->addIcosahedronSurface("icosahedron_surface", 1.0f);

// создаём ObjectMeshDynamic из объекта Mesh
ObjectMeshDynamicPtr dynamicMesh = ObjectMeshDynamic::create(mesh);

// задаём позицию меша
dynamicMesh->setWorldTransform(translate(Math::Vec3(10.0f,10.0f,10.0f)));

// задаём имя меша
dynamicMesh->setName("Dynamic Mesh");

```


Меш появится.


![](create_icosahedron_surface.png)


### Аргументы

- *const char ** **name** - Имя поверхности.
- *float* **radius** - Радиус icosahedron.
- *int* **collision_data_flags** - Битовая маска, определяющая, какие [types of collision data](#COLLISION_DATA_BOUNDS) генерировать для новой поверхности.

### Возвращаемое значение

Номер добавленной поверхности.
## void addIndex ( int index , int surface = 0 )

Добавляет заданный индекс в массивы [coordinate](#cindices) и [triangle](#tindices) индексов заданной поверхности.
### Аргументы

- *int* **index** - Добавляемый индекс в диапазоне от 0 до общего количества [coordinate vertices](#cvertex) поверхности. > **Notice:** Чтобы получить общее количество координатных вершин поверхности, используйте метод [getNumCVertex()](#getNumCVertex_int_int).
- *int* **surface** - Номер поверхности меша.

## int addMeshSurface ( const char * v , const Ptr <ConstMesh> & mesh , int surface , int collision_data_flags = COLLISION_DATA_ALL )

Добавляет поверхность исходного меша к текущему мешу как новую поверхность.
Следующий пример показывает, как добавить поверхность из одного меша в другой.


```cpp
// создаём экземпляры мешей
MeshPtr mesh_1 = Mesh::create();
MeshPtr mesh_2 = Mesh::create();

// добавляем поверхности для добавляемых мешей
mesh_1->addCapsuleSurface("capsule_surface", 1.0f, 2.0f, 200, 100);
mesh_2->addBoxSurface("box_surface", Math::vec3(2.2));

// добавляем поверхность из mesh_2 в mesh_1 как новую поверхность
// с именем "new_box_surface"
mesh_1->addMeshSurface("new_box_surface", mesh_2, 0);

// создаём ObjectMeshDynamic из объекта mesh_1
ObjectMeshDynamicPtr dynamicMesh = ObjectMeshDynamic::create(mesh_1);

// задаём позицию меша
dynamicMesh->setWorldTransform(translate(Math::Vec3(10.0f,10.0f,10.0f)));

// задаём имя меша
dynamicMesh->setName("Dynamic Mesh");

```


Меш появится.


| ![](add_mesh_surface.png) |
|---|
| ![](add_mesh_new_surface.png) |


### Аргументы

- *const char ** **v** - Имя новой поверхности, добавляемой к текущему мешу.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<ConstMesh> &* **mesh** - Исходный меш, из которого копируется поверхность.
- *int* **surface** - Номер копируемой поверхности исходного меша.
- *int* **collision_data_flags** - Битовая маска, определяющая, какие [types of collision data](#COLLISION_DATA_BOUNDS) генерировать для новой поверхности.

### Возвращаемое значение

Номер последней добавленной поверхности.
## int addMeshSurface ( int v , const Ptr <ConstMesh> & mesh , int surface , int collision_data_flags = COLLISION_DATA_ALL )

Добавляет поверхность исходного меша к существующей поверхности текущего меша.
Следующий пример показывает, как добавить поверхность из одного меша в другой.


```cpp
// создаём экземпляры мешей
MeshPtr mesh_1 = Mesh::create();
MeshPtr mesh_2 = Mesh::create();

// добавляем поверхности для добавляемых мешей
mesh_1->addCapsuleSurface("capsule_surface", 1.0f, 2.0f, 200, 100);
mesh_2->addBoxSurface("box_surface", Math::vec3(2.2));

// добавляем поверхность из mesh_2 в mesh_1 как новую поверхность
// с именем "new_box_surface"
mesh_1->addMeshSurface(0, mesh_2, 0);

// создаём ObjectMeshDynamic из объекта mesh_1
ObjectMeshDynamicPtr dynamicMesh = ObjectMeshDynamic::create(mesh_1);

// задаём позицию меша
dynamicMesh>setWorldTransform(translate(Math::Vec3(10.0f,10.0f,10.0f)));

// задаём имя меша
dynamicMesh>setName("Dynamic Mesh");

```


Меш появится.


| ![](add_mesh_surface.png) |
|---|
| ![](add_mesh_existing_surface.png) |


### Аргументы

- *int* **v** - Номер существующей поверхности текущего меша, к которой добавляется геометрия.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<ConstMesh> &* **mesh** - Исходный меш, из которого копируется поверхность.
- *int* **surface** - Номер копируемой поверхности исходного меша.
- *int* **collision_data_flags** - Битовая маска, определяющая, какие [types of collision data](#COLLISION_DATA_BOUNDS) генерировать для новой поверхности.

### Возвращаемое значение

Номер последней добавленной поверхности.
## void addNormal ( const Math:: vec3 & normal , int surface = 0 )

Добавляет заданную нормаль в массив нормалей заданной поверхности.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **normal** - Добавляемая нормаль.
- *int* **surface** - Номер поверхности меша.

## int addPlaneSurface ( const char * name , float width , float height , float step , int collision_data_flags = COLLISION_DATA_ALL )

Добавляет поверхность plane к текущему мешу. Plane делится на равные квадраты, размер которых определяется заданным шагом.
```cpp
// create a mesh instance
MeshPtr mesh = Mesh::create();
// добавляем поверхность plane с именем "plane_surface".
// ширина равна 2, высота равна 3
mesh->addPlaneSurface("plane_surface", 2.0f, 3.0f, 1.0f);

// создаём ObjectMeshDynamic из объекта Mesh
ObjectMeshDynamicPtr dynamicMesh = ObjectMeshDynamic::create(mesh);

// задаём позицию меша
dynamicMesh->setWorldTransform(translate(Math::Vec3(10.0f,10.0f,10.0f)));

// задаём имя меша
dynamicMesh->setName("Dynamic Mesh");

```


Меш появится. Вы увидите, что plane разделена на равные квадраты с шагом 1 единица.


![](create_plane_surface.png)


### Аргументы

- *const char ** **name** - Имя поверхности.
- *float* **width** - Ширина plane.
- *float* **height** - Высота plane.
- *float* **step** - Шаг подразделения поверхности (вертикально и горизонтально).
- *int* **collision_data_flags** - Битовая маска, определяющая, какие [types of collision data](#COLLISION_DATA_BOUNDS) генерировать для новой поверхности.

### Возвращаемое значение

Номер добавленной поверхности.
## int addPrismSurface ( const char * name , float size_0 , float size_1 , float height , int sides , int collision_data_flags = COLLISION_DATA_ALL )

Добавляет поверхность prism к текущему мешу.
```cpp
// create a mesh instance
MeshPtr mesh = Mesh::create();
// добавляем поверхность prism с именем "prism_surface".
// радиус верха равен 1.0f, низа - 2.0f
// высота prism равна 3.0f, и у неё 4 стороны
mesh->addPrismSurface("prism_surface", 1.0f, 2.0f, 3.0f, 4);

// создаём ObjectMeshDynamic из объекта Mesh
ObjectMeshDynamicPtr dynamicMesh = ObjectMeshDynamic::create(mesh);

// задаём позицию меша
dynamicMesh->setWorldTransform(translate(Math::Vec3(10.0f,10.0f,10.0f)));

// задаём имя меша
dynamicMesh->setName("Dynamic Mesh");

```


Меш появится.


![](create_prism_surface.png)


### Аргументы

- *const char ** **name** - Имя поверхности.
- *float* **size_0** - Радиус окружности, описанной вокруг верхнего основания prism.
- *float* **size_1** - Радиус окружности, описанной вокруг нижнего основания prism.
- *float* **height** - Высота prism.
- *int* **sides** - Количество граней prism.
- *int* **collision_data_flags**

### Возвращаемое значение

Номер добавленной поверхности.
## int addSphereSurface ( const char * name , float radius , int stacks , int slices , int collision_data_flags = COLLISION_DATA_ALL )

Добавляет поверхность sphere к текущему мешу. Stacks и slices определяют подразделение поверхности.
```cpp
// create a mesh instance
MeshPtr mesh = Mesh::create();
// добавляем поверхность sphere с именем "sphere_surface".
// радиус sphere равен 1.0f
// и у неё 200 stacks и 100 slices
mesh->addSphereSurface("sphere_surface", 1.0f, 200, 100);

// создаём ObjectMeshDynamic из объекта Mesh
ObjectMeshDynamicPtr dynamicMesh = ObjectMeshDynamic::create(mesh);

// задаём позицию меша
dynamicMesh->setWorldTransform(translate(Math::Vec3(10.0f,10.0f,10.0f)));

// задаём имя меша
dynamicMesh->setName("Dynamic Mesh");

```


Меш появится.


![](create_sphere_surface.png)


### Аргументы

- *const char ** **name** - Имя поверхности.
- *float* **radius** - Радиус sphere.
- *int* **stacks** - Количество stacks, делящих sphere радиально.
- *int* **slices** - Количество slices, делящих sphere горизонтально.
- *int* **collision_data_flags** - Битовая маска, определяющая, какие [types of collision data](#COLLISION_DATA_BOUNDS) генерировать для новой поверхности.

### Возвращаемое значение

Номер добавленной поверхности.
## int addSurface ( const char * name = 0 )

Добавляет новую поверхность с заданным именем к текущему мешу.
В следующем примере мы создаём новую поверхность и добавляем вершины и индексы для создания plane.


```cpp
// создаём экземпляр меша
MeshPtr mesh = Mesh::create();

// добавляем новую поверхность
mesh->addSurface("surface_0");

// добавляем вершины plane
mesh->addVertex(Math::vec3(0.0f,0.0f,0.0f),0);
mesh->addVertex(Math::vec3(0.0f,0.0f,1.0f),0);
mesh->addVertex(Math::vec3(0.0f,1.0f,0.0f),0);
mesh->addVertex(Math::vec3(0.0f,1.0f,1.0f),0);

// добавляем индексы
mesh->addIndex(0,0);
mesh->addIndex(1,0);
mesh->addIndex(2,0);

mesh->addIndex(3,0);
mesh->addIndex(2,0);
mesh->addIndex(1,0);

// создаём тангенсы
mesh->createTangents();

// создаём границы меша
mesh->createBounds(0);

// create the ObjectMeshDynamic from the Mesh object
ObjectMeshDynamicPtr dynamicMesh = ObjectMeshDynamic::create(mesh);

// set the position of the mesh
dynamicMesh->setWorldTransform(translate(Math::Vec3(10.0f,10.0f,10.0f)));

// set the name of the mesh
dynamicMesh->setName("new_mesh");

```


### Аргументы

- *const char ** **name** - Имя поверхности. По умолчанию этот аргумент пуст.

### Возвращаемое значение

Количество поверхностей меша.
## void addTangent ( const Math:: quat & tangent , int surface = 0 )

Добавляет заданный тангенс в массив тангенсов заданной поверхности.
### Аргументы

- *const  Math::[quat](../../../api/library/math/class.quat_cpp.md) &* **tangent** - Добавляемый тангенс.
- *int* **surface** - Номер поверхности.

## void addTexCoord0 ( const Math:: vec2 & texcoord , int surface )

Добавляет текстурные координаты в массив координат первой карты UV заданной поверхности меша.
### Аргументы

- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **texcoord** - Добавляемые координаты первой карты UV.
- *int* **surface** - Номер поверхности меша.

## void addTexCoord1 ( const Math:: vec2 & texcoord , int surface = 0 )

Добавляет текстурные координаты в массив координат второй карты UV заданной поверхности меша.
### Аргументы

- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **texcoord** - Добавляемые координаты второй карты UV.
- *int* **surface** - Номер поверхности меша.

## void addTIndex ( int index , int surface = 0 )

Добавляет индекс [triangle vertex](#tvertex) в массив треугольных индексов заданной поверхности.
### Аргументы

- *int* **index** - Номер индекса вершины в [triangle buffer](#indices) в диапазоне от 0 до общего количества треугольных вершин. > **Notice:** Чтобы получить общее количество треугольных вершин заданной поверхности, используйте метод [getNumTVertex()](#getNumTVertex_int_int).
- *int* **surface** - Номер поверхности, к которой добавляется треугольный индекс.

## void addVertex ( const Math:: vec3 & vertex , int surface = 0 )

Добавляет новую [coordinate vertex](#cvertex) с заданными координатами к поверхности меша.
В следующем примере мы создаём новую поверхность и добавляем к ней 4 вершины. Мы используем локальные координаты для определения вершины и указания поверхности. После этого мы задаём 6 индексов для создания plane с использованием определённых вершин.


```cpp
// создаём экземпляр меша
MeshPtr mesh = Mesh::create();

// добавляем новую поверхность
mesh->addSurface("surface_0");

// добавляем вершины plane
mesh->addVertex(Math::vec3(0.0f,0.0f,0.0f),0);
mesh->addVertex(Math::vec3(0.0f,0.0f,1.0f),0);
mesh->addVertex(Math::vec3(0.0f,1.0f,0.0f),0);
mesh->addVertex(Math::vec3(0.0f,1.0f,1.0f),0);

// добавляем индексы
mesh->addIndex(0,0);
mesh->addIndex(1,0);
mesh->addIndex(2,0);

mesh->addIndex(3,0);
mesh->addIndex(2,0);
mesh->addIndex(1,0);

// создаём тангенсы
mesh->createTangents();

// создаём границы меша
mesh->createBounds(0);

// create the ObjectMeshDynamic from the Mesh object
ObjectMeshDynamicPtr dynamicMesh = ObjectMeshDynamic::create(mesh);

// set the position of the mesh
dynamicMesh->setWorldTransform(translate(Math::Vec3(10.0f,10.0f,10.0f)));

// set the name of the mesh
dynamicMesh->setName("new_mesh");

```


### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **vertex** - Добавляемые координаты вершины.
- *int* **surface** - Номер поверхности меша.

## void clear ( )

Очищает меш (включая его кости, анимацию, поверхности и границы).
## void createBounds ( int surface = -1 )

Создаёт границы (ограничивающий параллелепипед и ограничивающую сферу) для заданной поверхности. Если в качестве аргумента используется значение по умолчанию, границы будут созданы для всех поверхностей меша.
### Аргументы

- *int* **surface** - Номер поверхности меша. Значение по умолчанию -1 (все поверхности меша).

## bool createIndices ( int surface = -1 )

Создаёт индексы для заданной поверхности. Если в качестве аргумента используется значение по умолчанию, индексы будут созданы для всех поверхностей меша.
### Аргументы

- *int* **surface** - Номер поверхности меша. Значение по умолчанию -1 (все поверхности меша).

### Возвращаемое значение

1, если индексы успешно созданы; иначе 0.
## int createNormals ( int surface = -1 )

Создаёт нормали для заданной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности меша. Значение по умолчанию -1 (все поверхности меша).

### Возвращаемое значение

1, если нормали успешно созданы; иначе 0.
## int createNormals ( float angle , int surface = -1 )

Создаёт нормали для заданной поверхности.
### Аргументы

- *float* **angle** - Угол между нормалями, используемый для вычисления средней нормали вершины.
- *int* **surface** - Номер поверхности меша. **-1** означает все поверхности меша.

### Возвращаемое значение

1, если нормали успешно созданы; иначе 0.
## int createTangents ( int surface = -1 )

Создаёт тангенсы для заданной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности меша. -1 означает все поверхности меша.

### Возвращаемое значение

1, если тангенсы успешно созданы; иначе 0.
## bool createTangents ( float angle , const Vector <int> & surfaces )

Создаёт тангенсы для всех поверхностей в списке.
### Аргументы

- *float* **angle** - Угол между нормалями, используемый для вычисления средней нормали вершины.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **surfaces** - Список номеров поверхностей, для которых создаются тангенсы.

### Возвращаемое значение

1, если тангенсы успешно созданы; иначе 0.
## int findSurface ( const char * name ) const

Ищет номер поверхности по её имени.
### Аргументы

- *const char ** **name** - Имя поверхности меша.

### Возвращаемое значение

Номер поверхности меша, если она найдена; иначе -1.
## bool flipTangent ( int surface = -1 )

Меняет знак компонента бинормали тангенциального пространства поверхности.
### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

1, если знак компонента бинормали успешно изменён; иначе 0.
## bool flipYZ ( int surface = -1 )

Меняет местами оси Y и Z для заданной поверхности:
- Ось Y становится равной -Z
- Ось Z становится равной Y


### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

1, если оси успешно поменяны местами; иначе 0.
## int info ( const char * path ) const

Возвращает информацию о заданном меше или анимации.
### Аргументы

- *const char ** **path** - Имя меша или анимации.

### Возвращаемое значение

## int load ( const char * path )

Загружает меш с заданным именем в текущий меш.
### Аргументы

- *const char ** **path** - Имя меша.

### Возвращаемое значение

1, если меш успешно загружен; иначе 0.
## bool optimizeIndices ( int flags , int surface = -1 )

Оптимизирует индексы заданной поверхности меша. По мере добавления полигонов к поверхности вершины смежных полигонов дублируются (количество таких вершин можно получить с помощью [getNumTVertex()](#getNumTVertex_int_int)), поскольку нормали, текстурные координаты и тангенсы таких вершин отличаются в зависимости от того, к какому полигону принадлежит вершина. Функция optimizeIndices() служит для уменьшения количества таких вершин и создания для них индексов, которые будут храниться в соответствующих нормалях, тангенсах и текстурных координатах.
### Аргументы

- *int* **flags** - Один из флагов, используемых для оптимизации индексов: [*MESH_BACK_TO_FRONT*](#BACK_TO_FRONT) или [*MESH_VERTEX_CACHE*](#VERTEX_CACHE).
- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

1, если индексы успешно оптимизированы; иначе 0.
## void remapCVertex ( int surface = 0 )

Задаёт размер массива [coordinate indices](#cindices) равным размеру массива [triangle indices](#tindices) и увеличивает размер буфера вершин до размера массива [triangle vertices](#tvertex) путём дублирования координатных вершин.
### Аргументы

- *int* **surface** - Номер поверхности меша.

## bool removeIndices ( int surface = -1 )

Очищает координатные и [triangle indices](#tindices) заданной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности меша. -1 означает все поверхности меша.

### Возвращаемое значение

1, если индексы успешно очищены; иначе 0.
## int save ( const char * path ) const

Сохраняет заданный меш в формате файла *[MESH](../../../code/formats/file_formats.md#mesh_ff)*. Создаёт заданный путь к мешу, если он ещё не существует (включая подкаталоги).
### Аргументы

- *const char ** **path** - Путь к мешу, включая имя файла и расширение — `*.mesh`.

### Возвращаемое значение

1, если меш успешно сохранён; иначе 0.
## void sortSurfaces ( )

Сортирует все поверхности по их именам.
## void addVertex ( const Vector < Math:: vec3 > & vertices , int surface = 0 )

Добавляет координаты заданной [coordinate vertex](#cvertex) к заданной поверхности.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[vec3](../../../api/library/math/class.vec3_cpp.md)> &* **vertices** - Координаты вершины.
- *int* **surface** - Номер поверхности меша.

## void addTexCoords0 ( const Vector < Math:: vec2 > & texcoords , int surface )

Добавляет текстурные координаты первой карты UV к заданной поверхности.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[vec2](../../../api/library/math/class.vec2_cpp.md)> &* **texcoords** - Текстурные координаты первой карты UV.
- *int* **surface** - Номер поверхности меша.

## void addTexCoords1 ( const Vector < Math:: vec2 > & texcoords , int surface = 0 )

Добавляет текстурные координаты второй карты UV к заданной поверхности.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[vec2](../../../api/library/math/class.vec2_cpp.md)> &* **texcoords** - Текстурные координаты второй карты UV.
- *int* **surface** - Номер поверхности меша.

## void addNormals ( const Vector < Math:: vec3 > & normals , int surface = 0 )

Добавляет нормали к заданной поверхности.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[vec3](../../../api/library/math/class.vec3_cpp.md)> &* **normals** - Нормали поверхности.
- *int* **surface** - Номер поверхности меша.

## void addTangents ( const Vector < Math:: quat > & tangents , int surface = 0 )

Добавляет тангенсы к заданной поверхности.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[quat](../../../api/library/math/class.quat_cpp.md)> &* **tangents**
- *int* **surface** - Номер поверхности меша.

## void addColors ( const Vector < Math:: vec4 > & colors , int surface = 0 )

Добавляет цвета вершин к заданной поверхности.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[vec4](../../../api/library/math/class.vec4_cpp.md)> &* **colors** - Цвета вершин.
- *int* **surface** - Номер поверхности меша.

## void addCIndices ( const Vector <int> & indices , int surface = 0 )

Добавляет координатные индексы всех вершин к заданной поверхности.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **indices** - Координатные индексы.
- *int* **surface** - Номер поверхности меша.

## void addTIndices ( const Vector <int> & indices , int surface = 0 )

Добавляет треугольные индексы к заданной поверхности.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **indices** - Треугольные индексы.
- *int* **surface** - Номер поверхности меша.

## void addIndices ( const Vector <int> & indices , int surface = 0 )

Добавляет индексы к заданной поверхности.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **indices** - Координаты индексов меша.
- *int* **surface** - Номер поверхности меша.

## Vector < Math:: vec3 > & getVertices ( int surface = 0 )

Возвращает координаты заданной [coordinate vertex](#cvertex) заданной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Координаты вершины.
## Vector < Math:: vec3 > & getNormals ( int surface = 0 )

Возвращает нормали заданной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Нормали поверхности.
## Vector < Math:: quat > & getTangents ( int surface = 0 )

Возвращает тангенсы заданной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Тангенсы поверхности.
## Vector < Math:: vec2 > & getTexCoords0 ( int surface = 0 )

Возвращает текстурные координаты первой карты UV заданной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Текстурные координаты первой карты UV.
## Vector < Math:: vec2 > & getTexCoords1 ( int surface = 0 )

Возвращает текстурные координаты второй карты UV заданной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Текстурные координаты второй карты UV.
## Vector < Math:: bvec4 > & getColors ( int surface = 0 )

Возвращает цвета вершин заданной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Цвета вершин.
## Vector <int> & getCIndices ( int surface = 0 )

Возвращает координатные индексы всех вершин заданной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Координатные индексы.
## Vector <int> & getTIndices ( int surface = 0 )

Возвращает треугольные индексы заданной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Треугольные индексы.
## size_t getMemoryUsage ( ) const

Возвращает объём памяти, используемой мешем, в байтах.
### Возвращаемое значение

Используемая память в байтах.
## bool hasSpatialTree ( int surface ) const

Возвращает значение, указывающее, есть ли у заданной поверхности меша пространственное дерево.
### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

true, если у меша есть пространственное дерево; иначе false.
## void createSpatialTree ( int surface = -1 )

Генерирует пространственное дерево для меша (или заданной поверхности), если его ещё нет.
### Аргументы

- *int* **surface** - Номер поверхности меша.

## void setSpatialTreeTriangles ( int triangles )


Задаёт количество треугольников, хранящихся в каждом листовом узле пространственного дерева меша.


Меньшие значения (по умолчанию 4) повышают точность определения пересечений и столкновений, но увеличивают время генерации пространственного дерева и потребление памяти.


Большие значения снижают затраты на генерацию и потребление памяти за счёт точности определения пересечений и столкновений. Полезно для высокополигональных мешей или часто обновляемой процедурной геометрии.


### Аргументы

- *int* **triangles** - Количество треугольников на листовой узел пространственного дерева.

## int getSpatialTreeTriangles ( ) const

Возвращает текущее заданное количество треугольников на листовой узел пространственного дерева.
### Возвращаемое значение

Количество треугольников на листовой узел (по умолчанию 4).
## bool hasEdges ( int surface = -1 ) const


Проверяет, были ли сгенерированы данные о рёбрах для заданной поверхности. Если передано -1, проверяются все поверхности.


### Аргументы

- *int* **surface** - Индекс проверяемой поверхности. Если передано -1, будут обновлены все поверхности.

### Возвращаемое значение


Возвращает true, если данные о рёбрах существуют, либо если у поверхности нет геометрии (в этом случае предполагаются пустые рёбра).


Возвращает false, если у поверхности есть геометрия, но данные о рёбрах не были сгенерированы.


## void createEdges ( int surface = -1 )

Генерирует данные о рёбрах для заданной поверхности. Если передано -1, данные о рёбрах будут сгенерированы для всех поверхностей.
### Аргументы

- *int* **surface** - Индекс поверхности. Если передано -1, операция будет выполнена для всех поверхностей.

## void clearCollisionData ( int surface = -1 , int flags = COLLISION_DATA_ALL )

Очищает заданные типы данных коллизий для заданной поверхности. Поведение управляется параметром flags, который определяет, какие типы данных очищать. Если для параметра surface передано -1, операция будет выполнена для всех поверхностей.
### Аргументы

- *int* **surface** - Индекс поверхности. Если передано -1, данные коллизий будут очищены для всех поверхностей.
- *int* **flags** - Битовая маска, определяющая, какие [types of collision data](#COLLISION_DATA_BOUNDS) очищать.

## void createCollisionData ( int surface = -1 , int flags = COLLISION_DATA_ALL )


Генерирует заданные типы данных коллизий для заданной поверхности. Поведение управляется параметром flags, который определяет, какие типы данных создаются.


> **Notice:** Этот метод **обязательно** должен вызываться после **любой** модификации геометрии меша.
> В противном случае определение пересечений и столкновений может давать **некорректные результаты** из-за устаревших внутренних структур меша.


### Аргументы

- *int* **surface** - Индекс обрабатываемой поверхности. Если передано -1, будут обновлены все поверхности.
- *int* **flags** - Битовая маска, определяющая, какие [types of collision data](#COLLISION_DATA_BOUNDS) генерировать.

## bool hasCollisionData ( int surface = -1 , int flags = COLLISION_DATA_ALL ) const


Проверяет, существуют ли заданные типы данных коллизий для заданной поверхности. Проверка управляется параметром flags, определяющим, какие типы данных проверять. Если для параметра surface передано -1, проверяются все поверхности меша.


Этот метод не проверяет содержимое геометрии. Вместо этого, если у поверхности нет корректной геометрии (например, нет индексов, пустые цели), считается, что данные коллизий для неё не требуются, и функция возвращает true.


### Аргументы

- *int* **surface** - Индекс проверяемой поверхности. Если передано -1, проверяются все поверхности меша.
- *int* **flags** - Битовая маска, определяющая, какие [types of collision data](#COLLISION_DATA_BOUNDS) проверять.

### Возвращаемое значение

Возвращает true, если данные коллизий существуют или у поверхности нет корректной геометрии; иначе false.
## void clearSurface ( int surface = -1 )

Очищает данные вершин для заданной поверхности. Если передано -1, будут очищены все поверхности.
### Аргументы

- *int* **surface** - Индекс очищаемой поверхности. Если передано -1, будут очищены все поверхности.

## bool getRandomPoint ( Math:: vec3 & ret_point , Math:: vec3 & ret_normal , Math:: vec3 & ret_velocity , int surface ) const

Генерирует случайную точку на заданной поверхности вместе с её нормалью. Скорость всегда равна нулю.
### Аргументы

- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret_point** - Сгенерированная точка на поверхности.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret_normal** - Интерполированная нормаль в точке.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret_velocity** - Всегда ноль.
- *int* **surface** - Индекс поверхности, на которой генерируется случайная точка.

### Возвращаемое значение

Возвращает true, если найдена корректная поверхность и точка сгенерирована; иначе false.
## bool getSurfaceCollision ( const Math:: BoundBox & bb , Vector <int> & OUT_surfaces ) const

Проверяет коллизии на уровне поверхностей между мешем и ограничивающим параллелепипедом.
### Аргументы

- *const  Math::[BoundBox](../../../api/library/math/bounds/class.boundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед для проверки коллизий.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **OUT_surfaces** - Выходной вектор для получения индексов пересекающихся поверхностей. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

### Возвращаемое значение

Возвращает true, если хотя бы одна поверхность столкнулась с заданным ограничивающим параллелепипедом; иначе false.
## bool getSurfaceCollision ( Math:: BoundFrustum & bf , Vector <int> & OUT_surfaces ) const

Проверяет коллизии на уровне поверхностей между мешем и ограничивающим frustum.
### Аргументы

- *Math::[BoundFrustum](../../../api/library/math/bounds/class.boundfrustum_cpp.md) &* **bf** - Ограничивающий frustum для проверки коллизий.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **OUT_surfaces** - Выходной вектор для получения индексов пересекающихся поверхностей. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

### Возвращаемое значение

Возвращает true, если хотя бы одна поверхность столкнулась с заданным ограничивающим frustum; иначе false.
## bool getSurfaceCollision ( const Math:: vec3 & p0 , const Math:: vec3 & p1 , Vector <int> & OUT_surfaces ) const

Проверяет коллизии на уровне поверхностей между мешем и отрезком линии.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальная точка отрезка.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечная точка отрезка.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **OUT_surfaces** - Выходной вектор для получения индексов пересекающихся поверхностей. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

### Возвращаемое значение

Возвращает true, если хотя бы одна поверхность столкнулась с заданным отрезком; иначе false.
## bool getTriangleCollision ( const Math:: BoundBox & bb , Vector <int> & OUT_triangles , int surface ) const

Проверяет коллизии между заданным ограничивающим параллелепипедом и треугольниками заданной поверхности. Если какие-либо треугольники пересекают параллелепипед, их индексы добавляются в массив *OUT_triangles*.
### Аргументы

- *const  Math::[BoundBox](../../../api/library/math/bounds/class.boundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед для проверки коллизий.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **OUT_triangles** - Выходной вектор для хранения индексов пересечённых треугольников. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *int* **surface** - Индекс проверяемой поверхности.

### Возвращаемое значение

true, если был пересечён хотя бы один треугольник; иначе false.
## bool getTriangleCollision ( const Math:: BoundFrustum & bf , Vector <int> & OUT_triangles , int surface ) const

Проверяет коллизии между заданным frustum и треугольниками заданной поверхности. Если какие-либо треугольники пересекают frustum, их индексы записываются в массив *OUT_triangles*.
### Аргументы

- *const  Math::[BoundFrustum](../../../api/library/math/bounds/class.boundfrustum_cpp.md) &* **bf** - Bounding frustum to check for collisions.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **OUT_triangles** - Выходной вектор для хранения индексов пересечённых треугольников. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *int* **surface** - Индекс проверяемой поверхности.

### Возвращаемое значение

true, если был пересечён хотя бы один треугольник; иначе false.
## bool getTriangleCollision ( const Math:: vec3 & p0 , const Math:: vec3 & p1 , Vector <int> & OUT_triangles , int surface ) const

Проверяет коллизии между отрезком, заданным точками *p0* и *p1*, и треугольниками заданной поверхности. Если какие-либо треугольники пересекают отрезок, их индексы добавляются в *OUT_triangles*.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальная точка отрезка.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечная точка отрезка.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **OUT_triangles** - Выходной вектор для хранения индексов пересечённых треугольников. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *int* **surface** - Индекс проверяемой поверхности.

### Возвращаемое значение

true, если был пересечён хотя бы один треугольник; иначе false.
## bool getIntersection ( const Math:: dvec3 & p0 , const Math:: dvec3 & p1 , Math:: dvec3 * OUT_ret_point , Math:: vec3 * OUT_ret_normal , int * OUT_ret_index , int surface ) const


Выполняет проверку пересечения луча с треугольниками для заданной поверхности.


Если пересечение произошло, ближайшая точка пересечения, её нормаль и индекс треугольника возвращаются через соответствующие выходные аргументы.


### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **p0** - Начальная точка луча в мировых координатах.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **p1** - Конечная точка луча в мировых координатах.
- *Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) ** **OUT_ret_point** - Указатель для хранения точки пересечения. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) ** **OUT_ret_normal** - Указатель для хранения нормали поверхности в точке пересечения. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *int ** **OUT_ret_index** - Указатель для хранения индекса треугольника пересечения. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *int* **surface** - Индекс тестируемой поверхности.

### Возвращаемое значение

Возвращает true, если луч пересекает любой треугольник внутри меша; иначе false.
## void clearSpatialTree ( int surface = -1 )

Очищает данные пространственного дерева для заданной поверхности. Если передано -1, пространственное дерево будет очищено для всех поверхностей.
### Аргументы

- *int* **surface** - Индекс поверхности. Если передано -1, пространственные деревья будут очищены для всех поверхностей меша.

## void clearEdges ( int surface = -1 )

Очищает данные о рёбрах для заданной поверхности. Если передано -1, данные о рёбрах будут очищены для всех поверхностей меша.
### Аргументы

- *int* **surface** - Индекс поверхности. Если передано -1, данные о рёбрах будут очищены для всех поверхностей меша.

## void getSurfaceCollision ( CollisionFilter filter , CollisionResult surface_index_result )

Выполняет пространственный запрос по всем поверхностям меша, применяя пользовательский фильтр ограничивающих параллелепипедов и вызывая callback для каждого подходящего индекса поверхности. Это может быть полезно, если вы хотите реализовать собственную логику определения коллизий на основе ограничивающих параллелепипедов.
### Аргументы

- *CollisionFilter* **filter** - Указатель на функцию или лямбда со следующей сигнатурой: *bool filter(const Math::BoundBox& bb)*. Функция должна возвращать true, если ограничивающий параллелепипед следует учитывать для коллизии; иначе false.
- *CollisionResult* **surface_index_result** - Указатель на функцию или лямбда со следующей сигнатурой: *void surface_index_result(int index)*. Функция вызывается для каждого индекса поверхности, ограничивающий параллелепипед которой проходит *filter*.

## void getTriangleCollision ( CollisionFilter filter , CollisionResult triangle_index_result , int surface )

Выполняет пространственный запрос на конкретной поверхности для определения сталкивающихся треугольников. Для каждого треугольника, ограничивающий объём которого проходит заданный фильтр, вызывается callback-функция с его индексом. Если у поверхности есть пространственное дерево, поиск выполняется быстрее благодаря оптимизированному обходу.
### Аргументы

- *CollisionFilter* **filter** - Указатель на функцию или лямбда со следующей сигнатурой: *bool filter(const Math::BoundBox& bb)*. Функция должна возвращать true, если ограничивающий параллелепипед следует учитывать для коллизии; иначе false.
- *CollisionResult* **triangle_index_result** - Указатель на функцию или лямбда со следующей сигнатурой: *void triangle_index_result(int index)*. Функция вызывается для каждого индекса треугольника, ограничивающий параллелепипед которого проходит *filter*.
- *int* **surface** - Индекс запрашиваемой поверхности.
